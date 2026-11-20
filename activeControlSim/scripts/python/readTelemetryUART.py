"""Read Hamming/CRC-protected navigation telemetry at 115200 baud.

    py readTelemetryUART.py --port COM4
    py readTelemetryUART.py --port COM4 --output telemetry.csv
    py readTelemetryUART.py --input captured_uart.bin --output telemetry.csv

COM4 is the mirrored board USB CDC stream. For physical USART3 PD8/PD9,
select the COM port belonging to the connected UART adapter. 8N1, no flow control.
Firmware switch: #define ENABLE_UART_TELEMETRY_PACKETS 1.
"""
from __future__ import annotations
import argparse
import csv
from contextlib import nullcontext
import json
from pathlib import Path
import struct
import sys
import time
import zlib
class PacketError(ValueError):
    pass


def decode_word(encoded):
    """Decode extended Hamming(72,64), correcting one flipped bit per word."""
    if len(encoded) != 9:
        raise PacketError("Incomplete SECDED word")
    bits = int.from_bytes(encoded, "little")
    syndrome = 0
    for pos in range(1, 72):
        if bits >> (pos - 1) & 1:
            syndrome ^= pos
    odd = bits.bit_count() & 1
    corrected = 0
    if syndrome and not odd:
        raise PacketError("SECDED detected a double-bit error")
    if odd:
        if syndrome > 71:
            raise PacketError("Invalid SECDED syndrome")
        bits ^= 1 << ((syndrome - 1) if syndrome else 71)
        corrected = 1
    data, index = 0, 0
    for pos in range(1, 72):
        if pos & (pos - 1):
            data |= ((bits >> (pos - 1)) & 1) << index
            index += 1
    return data.to_bytes(8, "little"), corrected

MAGIC = b"NTL1"
MAGIC_V3 = b"NTL3"
FRAME_SIZES = {MAGIC: 67, MAGIC_V3: 76}
PAYLOAD = struct.Struct("<BIIB9f")
PAYLOAD_V2 = struct.Struct("<BIIB9fB")
PAYLOAD_V3 = struct.Struct("<BIIB9fB3f")
BLOCKS = 7
FRAME_SIZE = 67
COLUMNS = (
    "packet_counter", "timestamp_us_delta", "nav_flightMode_enum",
    "nav_phiEst_rad", "nav_thetaEst_rad", "nav_psiEst_rad",
    "nav_xVelEstNed_mps", "nav_yVelEstNed_mps", "nav_zVelEstNed_mps",
    "nav_xPosEst_m", "nav_yPosEst_m", "nav_zPosEst_m", "gnssFixOK",
    "gps_velocity_north_mps", "gps_velocity_east_mps", "gps_velocity_down_mps", "ecc_corrected_bits")


def decode_frame(frame: bytes):
    if len(frame) != FRAME_SIZES.get(bytes(frame[:4])):
        raise PacketError("Invalid NTL1 frame length/marker")
    decoded = bytearray()
    corrected = 0
    for offset in range(4, len(frame), 9):
        word, count = decode_word(frame[offset:offset + 9])
        decoded.extend(word)
        corrected += count
    version = decoded[0]
    if version not in (1, 2, 3) or (version == 3) != (frame[:4] == MAGIC_V3):
        raise PacketError(f"Unsupported UART schema version {version}")
    layout = {1: PAYLOAD, 2: PAYLOAD_V2, 3: PAYLOAD_V3}[version]
    payload = bytes(decoded[:layout.size])
    crc = struct.unpack_from("<I", decoded, layout.size)[0]
    if zlib.crc32(payload) != crc:
        raise PacketError("UART packet CRC-32 mismatch after Hamming decoding")
    if any(decoded[layout.size + 4:]):
        raise PacketError("Nonzero UART packet padding")
    version, sequence, delta, mode, *values = layout.unpack(payload)
    gps_velocity = values[10:] if version == 3 else [None, None, None]
    fix_ok = values[9] if version >= 2 else None
    values = values[:9]
    if fix_ok not in (None, 0, 1):
        raise PacketError("Invalid gnssFixOK flag")
    return dict(zip(COLUMNS, (sequence, delta, mode, *values, fix_ok, *gps_velocity, corrected)))


class StreamDecoder:
    """Incremental parser tolerates boot text, chunk boundaries and lost bytes."""
    def __init__(self):
        self.buffer = bytearray()
        self.stats = dict(packets=0, corrected_packets=0, corrected_bits=0,
                          rejected_frames=0, ignored_bytes=0, missing_packets=0,
                          duplicates=0, counter_resets=0, incomplete_frames=0)
        self.last_sequence = None

    def feed(self, data: bytes, limit=None):
        self.buffer.extend(data)
        rows = []
        while True:
            offsets = [self.buffer.find(marker) for marker in FRAME_SIZES]
            offset = min((i for i in offsets if i >= 0), default=-1)
            if offset < 0:
                discard = max(0, len(self.buffer) - 3)
                self.stats["ignored_bytes"] += discard
                del self.buffer[:discard]
                break
            if offset:
                self.stats["ignored_bytes"] += offset
                del self.buffer[:offset]
            frame_size = FRAME_SIZES[bytes(self.buffer[:4])]
            if len(self.buffer) < frame_size:
                break
            try:
                row = decode_frame(bytes(self.buffer[:frame_size]))
            except PacketError:
                self.stats["rejected_frames"] += 1
                # Search from one byte later, recovering after insertion/deletion.
                del self.buffer[0]
                self.stats["ignored_bytes"] += 1
                continue
            del self.buffer[:frame_size]
            sequence = row["packet_counter"]
            if self.last_sequence is not None:
                increment = (sequence - self.last_sequence) & 0xFFFFFFFF
                if increment == 0:
                    self.stats["duplicates"] += 1
                    continue
                if increment < 0x80000000:
                    self.stats["missing_packets"] += increment - 1
                else:
                    self.stats["counter_resets"] += 1
            self.last_sequence = sequence
            self.stats["packets"] += 1
            self.stats["corrected_bits"] += row["ecc_corrected_bits"]
            self.stats["corrected_packets"] += bool(row["ecc_corrected_bits"])
            rows.append(row)
            if limit is not None and len(rows) >= limit:
                break
        return rows

    def finish(self, check_incomplete=True):
        tail = bytes(self.buffer)
        if check_incomplete and tail and any(tail.startswith(m) or m.startswith(tail) for m in FRAME_SIZES):
            self.stats["incomplete_frames"] += 1
        self.buffer.clear()
        return dict(self.stats)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    source = parser.add_mutually_exclusive_group()
    source.add_argument("--port", help="serial COM port (default COM4)")
    source.add_argument("--input", type=Path, help="decode an existing raw UART capture")
    parser.add_argument("-o", "--output", type=Path, help="enable CSV logging to this path (default: no CSV)")
    parser.add_argument("--baud", type=int, default=115200)
    parser.add_argument("--duration", type=float, help="stop capture after this many seconds")
    parser.add_argument("--count", type=int, help="stop after this many valid packets")
    parser.add_argument("--force", action="store_true", help="overwrite an existing CSV")
    parser.add_argument("--quiet", action="store_true", help="disable periodic live-value prints")
    args = parser.parse_args(argv)
    if args.duration is not None and args.duration <= 0:
        parser.error("--duration must be positive")
    if args.count is not None and args.count <= 0:
        parser.error("--count must be positive")
    destination = args.output
    if args.input and destination and args.input.resolve() == destination.resolve():
        parser.error("Input and output paths must differ")
    decoder = StreamDecoder()
    stream = None
    try:
        if args.input:
            stream = args.input.open("rb")
        else:
            try:
                import serial
            except ImportError:
                parser.error("pyserial is required: py -m pip install pyserial")
            stream = serial.Serial(args.port or "COM4", args.baud, timeout=0.1,
                                   write_timeout=1, rtscts=False, dsrdtr=False)
        print("Format: NTL3 v3, 76 bytes, raw GPS N/E/D velocity + navigation + gnssFixOK; legacy NTL1 v1/v2 supported. SECDED + CRC-32.")
        print("115200 baud 8N1 at 100 Hz: 76000 bit/s (66.0%); angles rad, NED velocity m/s, position m.")
        print("Timestamp deltas are per SD sample; sequence gaps indicate omitted UART samples. No elapsed time is invented across gaps.")
        print(f"Output: {destination.resolve()}" if destination else "CSV logging disabled; console only.")
        deadline = time.monotonic() + args.duration if args.duration else float("inf")
        if destination:
            destination.parent.mkdir(parents=True, exist_ok=True)
        count, last_print = 0, 0.0
        control_tail = b""
        device_stopped = False
        with (destination.open("w" if args.force else "x", newline="", encoding="utf-8")
              if destination else nullcontext(None)) as output:
            writer = csv.DictWriter(output, fieldnames=COLUMNS) if output else None
            if writer:
                writer.writeheader()
            try:
                done = False
                while not done and time.monotonic() < deadline:
                    data = stream.read(4096 if args.input else max(FRAME_SIZE, min(stream.in_waiting, 4096)))
                    if not data:
                        if args.input:
                            break
                        continue
                    control_tail = (control_tail + data)[-256:]
                    device_stopped = b"Logging stopped: 120 seconds after LOCKOUT\r\n" in control_tail
                    remaining = args.count - count if args.count else None
                    for row in decoder.feed(data, limit=remaining):
                        if writer:
                            writer.writerow(row)
                        count += 1
                        now = time.monotonic()
                        if now - last_print >= 1:
                            if output:
                                output.flush()
                            if not args.quiet:
                                print(json.dumps(row), flush=True)
                            last_print = now
                        if args.count and count >= args.count:
                            done = True
                            break
                    if device_stopped:
                        print("Device confirmed logging stopped 120 seconds after LOCKOUT.")
                        done = True
            except KeyboardInterrupt:
                print("\nCapture stopped by user.")
        stats = decoder.finish(check_incomplete=bool(args.input) and not done and time.monotonic() < deadline)
        stats["device_logging_stopped"] = device_stopped
        print(f"Saved {count} packets to {destination.resolve()}" if destination else f"Decoded {count} packets.")
        print("Integrity: " + json.dumps(stats, sort_keys=True))
        return 1 if stats["rejected_frames"] or stats["incomplete_frames"] else 0
    except (OSError, ValueError) as error:
        parser.exit(2, f"error: {error}\n")
    finally:
        if stream is not None:
            stream.close()


if __name__ == "__main__":
    sys.exit(main())
