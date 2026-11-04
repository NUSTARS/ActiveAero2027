"""Decode NUFLIGHT v2 (self-described, SECDED + CRC-32) or legacy 154-byte logs.

Examples:
    py decodeflightdata.py flight.bin flight.csv
    py decodeflightdata.py --input flight.bin --output flight.csv
Run without arguments to enter paths interactively. Existing CSVs require --force.
"""
from __future__ import annotations
import argparse
import csv
from dataclasses import dataclass
from pathlib import Path
import re
import struct
import sys
import zlib

MAGIC = b"NUFLIGHT"
PREFIX = struct.Struct("<8sBBBBHHHH")
DESCRIPTOR = struct.Struct("<24sBBH")
MARKER = b"PKT2"
TYPES = {1: ("B", "uint8"), 2: ("H", "uint16"), 3: ("I", "uint32"),
         4: ("i", "int32"), 5: ("f", "float32"), 6: ("d", "float64")}
LEGACY_FORMAT = "<II" + "d" * 12 + "f" * 4 + "dd" + "f" * 4 + "BB"
LEGACY_FIELDS = [
    ("timestamp_us", 3, 1), ("packet_counter", 3, 1),
    ("bmi_accel", 6, 3), ("bmi_gyro", 6, 3),
    ("lsm_accel", 6, 3), ("lsm_gyro", 6, 3),
    ("bmp581_pressure", 5, 1), ("bmp581_temperature", 5, 1),
    ("bmp585_pressure", 5, 1), ("bmp585_temperature", 5, 1),
    ("latitude", 6, 1), ("longitude", 6, 1), ("altitude", 5, 1),
    ("velocity_north", 5, 1), ("velocity_east", 5, 1), ("velocity_down", 5, 1),
    ("gnss_fix_type", 1, 1), ("gnss_satellites", 1, 1)]

class FormatError(ValueError):
    pass

class PacketError(ValueError):
    pass

@dataclass(frozen=True)
class Field:
    name: str
    kind: int
    count: int
    offset: int

    @property
    def unpacker(self):
        return struct.Struct("<" + TYPES[self.kind][0] * self.count)

    @property
    def columns(self):
        if self.count == 1:
            return [self.name]
        suffixes = ("x", "y", "z") if self.count == 3 else tuple(map(str, range(self.count)))
        return [f"{self.name}_{suffix}" for suffix in suffixes]

@dataclass(frozen=True)
class Layout:
    version: int
    header_size: int
    payload_size: int
    packet_size: int
    fields: tuple[Field, ...]

    @property
    def columns(self):
        return [column for field in self.fields for column in field.columns]

    def values(self, payload):
        return [v for field in self.fields for v in field.unpacker.unpack_from(payload, field.offset)]


def legacy_layout():
    fields, offset = [], 0
    for name, kind, count in LEGACY_FIELDS:
        field = Field(name, kind, count, offset)
        fields.append(field)
        offset += field.unpacker.size
    assert offset == struct.calcsize(LEGACY_FORMAT) == 154
    return Layout(0, 0, offset, offset, tuple(fields))


def read_layout(stream, force_legacy=False):
    prefix = stream.read(PREFIX.size)
    stream.seek(0)
    if not force_legacy and len(prefix) >= 8 and prefix[:8] != MAGIC:
        distance = sum((a ^ b).bit_count() for a, b in zip(prefix[:8], MAGIC))
        if distance <= 2 or prefix[8:12] == bytes((2, 1, 1, 1)):
            raise FormatError("Damaged NUFLIGHT magic; refusing to reinterpret header as legacy records")
    if force_legacy or prefix[:8] != MAGIC:
        # Headerless files cannot describe themselves. Only the known packed
        # double-vector ABI is inferred; padded/float-vector variants are not guessed.
        if not force_legacy:
            stream.seek(0, 2)
            size = stream.tell()
            stream.seek(0)
            if not size or size % 154:
                raise FormatError("No NUFLIGHT header; size is not a multiple of legacy 154-byte records. "
                                  "Use --legacy only if this is a known legacy file with a partial tail.")
        return legacy_layout()
    if len(prefix) != PREFIX.size:
        raise FormatError("Truncated NUFLIGHT header")
    _, version, endian, ecc, flags, header_size, payload_size, packet_size, field_count = PREFIX.unpack(prefix)
    if (version, endian, ecc, flags) != (2, 1, 1, 1):
        raise FormatError(f"Unsupported version/endian/ECC/flags: {version}/{endian}/{ecc}/{flags}")
    expected_header = PREFIX.size + field_count * DESCRIPTOR.size + 4
    expected_packet = 4 + ((payload_size + 4 + 7) // 8) * 9
    if not 1 <= field_count <= 128 or not 1 <= payload_size <= 8192:
        raise FormatError("Invalid field count or payload size")
    if header_size != expected_header or packet_size != expected_packet:
        raise FormatError("Header or packet length is inconsistent")
    header = stream.read(header_size)
    if len(header) != header_size:
        raise FormatError("Truncated field descriptors")
    if zlib.crc32(header[:-4]) != struct.unpack_from("<I", header, header_size - 4)[0]:
        raise FormatError("Header CRC-32 mismatch; refusing to guess field types")
    fields, used, names = [], set(), set()
    for index in range(field_count):
        raw_name, kind, count, offset = DESCRIPTOR.unpack_from(header, PREFIX.size + index * DESCRIPTOR.size)
        if b"\0" not in raw_name:
            raise FormatError("Field name is not NUL terminated")
        try:
            name = raw_name.split(b"\0", 1)[0].decode("ascii")
        except UnicodeDecodeError as error:
            raise FormatError("Non-ASCII field name") from error
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name) or kind not in TYPES or not count:
            raise FormatError(f"Invalid field descriptor {index}")
        field = Field(name, kind, count, offset)
        span = set(range(offset, offset + field.unpacker.size))
        if offset + field.unpacker.size > payload_size or span & used or set(field.columns) & names:
            raise FormatError(f"Overlapping, duplicate or out-of-range field: {name}")
        fields.append(field)
        used |= span
        names.update(field.columns)
    return Layout(2, header_size, payload_size, packet_size, tuple(fields))


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


def decode_packet(encoded, layout):
    if len(encoded) != layout.packet_size - 4:
        raise PacketError("Incomplete protected packet")
    data, corrected = bytearray(), 0
    for offset in range(0, len(encoded), 9):
        word, count = decode_word(encoded[offset:offset + 9])
        data.extend(word)
        corrected += count
    payload = bytes(data[:layout.payload_size])
    crc = struct.unpack_from("<I", data, layout.payload_size)[0]
    if zlib.crc32(payload) != crc:
        raise PacketError("Packet CRC-32 mismatch after SECDED decoding")
    if any(data[layout.payload_size + 4:]):
        raise PacketError("Nonzero protected padding")
    return payload, corrected


def describe(layout):
    if layout.version == 2:
        print(f"Detected NUFLIGHT v2: little-endian, {layout.header_size}-byte header, "
              f"{layout.payload_size}-byte payload, {layout.packet_size}-byte packets")
        print("Protection: Hamming SECDED(72,64) + payload CRC-32; header CRC-32")
    else:
        print("Detected legacy raw FlightData_t: little-endian, 154 bytes, double vectors, no integrity protection")
    for field in layout.fields:
        print(f"  offset {field.offset:3}: {field.name}: {TYPES[field.kind][1]}[{field.count}]")


def convert(input_path, output_path, *, force=False, force_legacy=False, strict=False):
    input_path, output_path = Path(input_path), Path(output_path)
    if input_path.resolve() == output_path.resolve():
        raise FormatError("Input and output paths must differ")
    stats = dict(packets=0, corrected_packets=0, corrected_bits=0, rejected_packets=0,
                 discarded_bytes=0, truncated_packets=0)
    with input_path.open("rb") as stream:
        layout = read_layout(stream, force_legacy)
        describe(layout)  # Report layout after reading BIN, before producing CSV.
        with output_path.open("w" if force else "x", newline="", encoding="utf-8") as output:
            writer = csv.writer(output)
            writer.writerow(layout.columns)
            while True:
                offset = stream.tell()
                if layout.version == 0:
                    payload = stream.read(layout.payload_size)
                    if not payload:
                        break
                    if len(payload) != layout.payload_size:
                        stats["truncated_packets"] += 1
                        print(f"WARNING: incomplete legacy packet at byte {offset}")
                        break
                    corrected = 0
                else:
                    marker = stream.read(4)
                    if not marker:
                        break
                    skipped = 0
                    while len(marker) == 4 and marker != MARKER:
                        skipped += 1
                        marker = marker[1:] + stream.read(1)
                    stats["discarded_bytes"] += skipped
                    if skipped:
                        print(f"WARNING: skipped {skipped} bytes while locating packet marker at {offset}")
                        if strict:
                            raise PacketError("Packet framing lost")
                    if marker != MARKER:
                        stats["truncated_packets"] += 1
                        print("WARNING: partial packet marker at end of file")
                        break
                    protected = stream.read(layout.packet_size - 4)
                    if len(protected) != layout.packet_size - 4:
                        stats["truncated_packets"] += 1
                        print(f"WARNING: incomplete protected packet at byte {offset}")
                        break
                    try:
                        payload, corrected = decode_packet(protected, layout)
                    except PacketError as error:
                        stats["rejected_packets"] += 1
                        print(f"WARNING: rejected packet at byte {offset}: {error}")
                        if strict:
                            raise
                        # Resume marker search one byte after this candidate:
                        # this also recovers after inserted/deleted bytes.
                        stream.seek(offset + skipped + 1)
                        continue
                writer.writerow(layout.values(payload))
                stats["packets"] += 1
                stats["corrected_bits"] += corrected
                stats["corrected_packets"] += bool(corrected)
    print(f"Converted {stats['packets']} packets; corrected {stats['corrected_bits']} bits "
          f"in {stats['corrected_packets']} packets; rejected {stats['rejected_packets']}; "
          f"discarded {stats['discarded_bytes']} framing bytes; incomplete {stats['truncated_packets']}.")
    print(f"Output: {output_path.resolve()}")
    return stats


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", nargs="?", help="input .bin path")
    parser.add_argument("output", nargs="?", help="output .csv path (default: beside input)")
    parser.add_argument("-i", "--input", dest="input_option")
    parser.add_argument("-o", "--output", dest="output_option")
    parser.add_argument("--force", action="store_true", help="overwrite an existing output CSV")
    parser.add_argument("--legacy", action="store_true", help="force known raw 154-byte legacy layout")
    parser.add_argument("--strict", action="store_true", help="stop at the first rejected packet or framing error")
    args = parser.parse_args(argv)
    try:
        interactive = not (args.input_option or args.input)
        entered = args.input_option or args.input or input("Input BIN file: ").strip().strip('"')
        source = Path(entered).expanduser()
        target = args.output_option or args.output
        if not target and interactive:
            target = input(f"Output CSV file [{source.with_suffix('.csv')}]: ").strip().strip('"')
        destination = Path(target).expanduser() if target else source.with_suffix(".csv")
        stats = convert(source, destination, force=args.force, force_legacy=args.legacy, strict=args.strict)
        return 1 if any(stats[k] for k in ("rejected_packets", "discarded_bytes", "truncated_packets")) else 0
    except (OSError, ValueError, EOFError) as error:
        parser.exit(2, f"error: {error}\n")

if __name__ == "__main__":
    sys.exit(main())
