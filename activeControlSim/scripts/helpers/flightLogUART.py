#!/usr/bin/env python3
"""Capture the firmware's CRC-protected simulation CSV over USB CDC or USART3.

Run from the ActiveAero2027 repository root, for example::

    py activeControlSim/scripts/helpers/flightLogUART.py --port COM4 --start-log-sim

The device emits READY, accepts START_LOG_SIM, runs the coupled plant/model
for 35 seconds at 100 Hz into SRAM, then sends sequenced
@<sequence>|<payload>|<CRC16> frames. Valid frames are ACKed; damaged or
missing frames are NAKed so the firmware retransmits them.
"""

from __future__ import annotations

import argparse
import csv
import math
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
import time
from typing import Any

try:
    import serial
except ImportError:  # Keep --help usable before pyserial is installed.
    serial = None


DEFAULT_PORT = "COM4"
DEFAULT_BAUD = 115200
SIMULATION_STEPS = 3501
SIMULATION_DT_S = 0.01
DEFAULT_FRAME_TIMEOUT_S = 45.0
SERIAL_READ_TIMEOUT_S = 0.2
CRC_POLYNOMIAL = 0x1021
CRC_INITIAL = 0xFFFF


class FrameError(ValueError):
    """A UART line could not be decoded as a log frame."""


class ProtocolError(RuntimeError):
    """The device and host disagreed about the log protocol or CSV."""


@dataclass(frozen=True)
class Capture:
    header: str
    header_fields: tuple[str, ...]
    rows: tuple[str, ...]
    crc_errors: int
    malformed_frames: int
    duplicate_frames: int


def crc16_ccitt_false(data: bytes) -> int:
    """Return CRC-16/CCITT-FALSE (poly 0x1021, init 0xFFFF, no xorout)."""
    crc = CRC_INITIAL
    for value in data:
        crc ^= value << 8
        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ CRC_POLYNOMIAL) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF
    return crc


def decode_frame(raw_line: bytes) -> tuple[int, str, bool]:
    """Decode a frame and report its CRC validity without losing its sequence."""
    line = raw_line.rstrip(b"\r\n")
    if not line.startswith(b"@"):
        raise FrameError("missing frame marker")

    parts = line[1:].split(b"|", 2)
    if len(parts) != 3:
        raise FrameError("expected sequence, payload, and CRC fields")
    sequence_text, payload_bytes, crc_text = parts
    if len(sequence_text) != 8 or len(crc_text) != 4:
        raise FrameError("invalid sequence or CRC width")
    if any(value not in b"0123456789abcdefABCDEF" for value in sequence_text):
        raise FrameError("sequence is not hexadecimal")
    if any(value not in b"0123456789abcdefABCDEF" for value in crc_text):
        raise FrameError("CRC is not hexadecimal")

    try:
        payload = payload_bytes.decode("ascii")
    except UnicodeDecodeError as error:
        raise FrameError("payload is not ASCII") from error

    sequence = int(sequence_text, 16)
    expected_crc = int(crc_text, 16)
    covered = sequence_text + b"|" + payload_bytes
    return sequence, payload, crc16_ccitt_false(covered) == expected_crc


def encode_ack(kind: str, sequence: int) -> bytes:
    if kind not in {"ACK", "NAK"}:
        raise ValueError(f"unsupported acknowledgement: {kind}")
    if not 0 <= sequence <= 0xFFFFFFFF:
        raise ValueError("sequence must fit in 32 bits")
    return f"{kind},{sequence:08X}\n".encode("ascii")


def _status_text(raw_line: bytes) -> str:
    return raw_line.decode("ascii", errors="replace").strip()


def _read_status(connection: Any, deadline: float, expected: str) -> None:
    while time.monotonic() < deadline:
        raw_line = connection.readline()
        if not raw_line:
            continue
        text = _status_text(raw_line)
        if text.startswith("ERR,"):
            raise ProtocolError(f"device reported {text}")
        if text == expected:
            return
        if text in {"READY", "STARTED"}:
            continue
        if text.startswith("@"):
            raise ProtocolError(f"received a data frame before {expected}")
    raise TimeoutError(f"timed out waiting for device status {expected}")


def _send_ack(connection: Any, kind: str, sequence: int) -> None:
    connection.write(encode_ack(kind, sequence))
    connection.flush()


def _csv_fields(payload: str, sequence: int) -> tuple[str, ...]:
    try:
        rows = list(csv.reader([payload], strict=True))
    except csv.Error as error:
        raise ProtocolError(f"invalid CSV payload at sequence {sequence}") from error
    if len(rows) != 1 or not rows[0]:
        raise ProtocolError(f"empty CSV payload at sequence {sequence}")
    return tuple(rows[0])


def _request_retry(connection: Any, expected_sequence: int) -> None:
    """Request retransmission of the frame currently pending in stop-and-wait."""
    _send_ack(connection, "NAK", expected_sequence)


def _receive_frames(connection: Any, frame_timeout_s: float) -> Capture:
    expected_sequence = 0
    header: str | None = None
    header_fields: tuple[str, ...] | None = None
    rows: list[str] = []
    end_count: int | None = None
    crc_errors = 0
    malformed_frames = 0
    duplicate_frames = 0
    last_activity = time.monotonic()

    while True:
        raw_line = connection.readline()
        if not raw_line:
            if time.monotonic() - last_activity >= frame_timeout_s:
                raise TimeoutError("timed out waiting for the next UART log frame")
            continue
        last_activity = time.monotonic()
        text = _status_text(raw_line)
        if text.startswith("ERR,"):
            raise ProtocolError(f"device reported {text}")
        if text.startswith("DONE,"):
            if end_count is None:
                raise ProtocolError("device reported DONE before the CRC-protected END frame")
            try:
                done_count = int(text.split(",", 1)[1], 10)
            except ValueError as error:
                raise ProtocolError(f"invalid completion status: {text}") from error
            if done_count != end_count or done_count != len(rows):
                raise ProtocolError(
                    f"completion count mismatch: END={end_count}, DONE={done_count}, rows={len(rows)}"
                )
            if header is None or header_fields is None:
                raise ProtocolError("completion received before the CSV header")
            return Capture(
                header=header,
                header_fields=header_fields,
                rows=tuple(rows),
                crc_errors=crc_errors,
                malformed_frames=malformed_frames,
                duplicate_frames=duplicate_frames,
            )
        if text in {"READY", "STARTED"}:
            continue

        try:
            sequence, payload, crc_ok = decode_frame(raw_line)
        except FrameError:
            malformed_frames += 1
            _request_retry(connection, expected_sequence)
            continue

        if not crc_ok:
            crc_errors += 1
            _request_retry(connection, expected_sequence)
            continue

        if sequence < expected_sequence:
            # The prior ACK may have been lost; acknowledge again without duplicating a CSV row.
            duplicate_frames += 1
            _send_ack(connection, "ACK", sequence)
            continue
        if sequence > expected_sequence:
            _send_ack(connection, "NAK", expected_sequence)
            continue

        if expected_sequence == 0:
            header = payload
            header_fields = _csv_fields(payload, sequence)
        elif payload.startswith("END,"):
            try:
                end_count = int(payload.split(",", 1)[1], 10)
            except ValueError as error:
                raise ProtocolError(f"invalid END payload at sequence {sequence}") from error
            if end_count != len(rows):
                raise ProtocolError(
                    f"END count mismatch: device={end_count}, received rows={len(rows)}"
                )
        else:
            if header_fields is None:
                raise ProtocolError("data row arrived before CSV header")
            fields = _csv_fields(payload, sequence)
            if len(fields) != len(header_fields):
                raise ProtocolError(
                    f"CSV width mismatch at sequence {sequence}: "
                    f"header={len(header_fields)}, row={len(fields)}"
                )
            rows.append(payload)

        _send_ack(connection, "ACK", sequence)
        expected_sequence += 1
        if len(rows) and len(rows) % 100 == 0:
            print(f"\rReceived {len(rows)} rows...", end="", flush=True)


def echo_test(connection: Any, timeout_s: float = 10.0) -> None:
    """Verify the UART in both directions before starting a simulation."""
    deadline = time.monotonic() + timeout_s
    _read_status(connection, deadline, "READY")
    connection.write(b"ECHO\n")
    connection.flush()
    _read_status(connection, deadline, "ECHO_OK")


def _start_log_simulation(
    connection: Any,
    startup_timeout_s: float,
    frame_timeout_s: float,
) -> Capture:
    connection.write(b"START_LOG_SIM\n")
    connection.flush()
    _read_status(connection, time.monotonic() + startup_timeout_s, "STARTED")
    print("Running coupled plant/model for 35 s; buffered UART transfer follows.", flush=True)
    capture = _receive_frames(connection, max(frame_timeout_s, DEFAULT_FRAME_TIMEOUT_S))
    validate_simulation_capture(capture)
    return capture


def capture_log_simulation(
    connection: Any,
    startup_timeout_s: float = 90.0,
    frame_timeout_s: float = DEFAULT_FRAME_TIMEOUT_S,
    echo_timeout_s: float = 10.0,
) -> Capture:
    """Echo-test the link, start one simulation, and receive its acknowledged CSV."""
    echo_test(connection, echo_timeout_s)
    return _start_log_simulation(connection, startup_timeout_s, frame_timeout_s)


def validate_simulation_capture(capture: Capture) -> None:
    """Reject truncated runs, malformed numeric output, and shifted sample times.

    NaN/Inf are retained as model diagnostics; the CLI reports their first row.
    """
    if len(capture.rows) != SIMULATION_STEPS:
        raise ProtocolError(f"expected {SIMULATION_STEPS} samples over 35 s, got {len(capture.rows)}")
    if capture.header_fields[:2] != ("model_sample_time_s", "plant_state_time_s"):
        raise ProtocolError("missing model/plant sample time columns")
    if len(capture.header_fields) != 28:
        raise ProtocolError("expected 28 coupled model/plant columns")
    for index, row in enumerate(capture.rows):
        try:
            values = tuple(float(value) for value in _csv_fields(row, index + 1))
        except ValueError as error:
            raise ProtocolError(f"non-numeric simulation row {index + 1}") from error
        if len(values) != 28:
            raise ProtocolError(f"invalid simulation width at row {index + 1}")
        if (abs(values[0] - index * SIMULATION_DT_S) > 0.000001 or
                abs(values[1] - index * SIMULATION_DT_S) > 0.000001):
            raise ProtocolError(f"incorrect model/plant time at row {index + 1}")


def prompt_csv_destination() -> Path:
    default = Path.cwd() / f"flight_log_{datetime.now():%Y%m%d_%H%M%S}.csv"
    while True:
        entered = input(f"Save CSV to [{default}]: ").strip()
        destination = Path(entered).expanduser() if entered else default
        if destination.suffix == "":
            destination = destination.with_suffix(".csv")
        elif destination.suffix.lower() != ".csv":
            print("Please enter a path ending in .csv.")
            continue

        if destination.exists():
            if destination.is_dir():
                print("That path is a directory; choose a CSV file path.")
                continue
            overwrite = input(f"{destination} exists. Overwrite? [y/N]: ").strip().lower()
            if overwrite not in {"y", "yes"}:
                continue
        return destination


def save_capture(capture: Capture, destination: Path) -> None:
    destination.parent.mkdir(parents=True, exist_ok=True)
    with destination.open("w", encoding="ascii", newline="") as output:
        output.write(capture.header)
        output.write("\r\n")
        for row in capture.rows:
            output.write(row)
            output.write("\r\n")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--port", default=DEFAULT_PORT, help=f"serial port (default: {DEFAULT_PORT})")
    parser.add_argument("--baud", type=int, default=DEFAULT_BAUD, help=f"UART baud rate (default: {DEFAULT_BAUD})")
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument(
        "--echo",
        action="store_true",
        help="test UART communication without starting a simulation",
    )
    mode.add_argument(
        "--start-log-sim",
        action="store_true",
        help="echo-test the UART, then capture the device simulation CSV",
    )
    parser.add_argument("--echo-timeout", type=float, default=10.0, help="seconds allowed for the UART echo test")
    parser.add_argument("--startup-timeout", type=float, default=90.0, help="seconds to wait for STARTED")
    parser.add_argument("--frame-timeout", type=float, default=DEFAULT_FRAME_TIMEOUT_S, help="seconds without a log frame (minimum 45 for buffered run)")
    parser.add_argument("--output", type=Path, help="save CSV here without an interactive prompt")
    args = parser.parse_args(argv)
    if serial is None:
        parser.exit(2, "error: pyserial is required; install it with `py -m pip install pyserial`\n")

    try:
        with serial.Serial(
            args.port,
            baudrate=args.baud,
            timeout=SERIAL_READ_TIMEOUT_S,
            write_timeout=2.0,
        ) as connection:
            connection.reset_input_buffer()
            echo_test(connection, args.echo_timeout)
            print(f"Serial echo passed on {args.port} at {args.baud} baud.")
            if args.start_log_sim:
                capture = _start_log_simulation(
                    connection,
                    startup_timeout_s=args.startup_timeout,
                    frame_timeout_s=args.frame_timeout,
                )
    except TimeoutError as error:
        parser.exit(
            1,
            f"error: {error}; check --port, --baud (firmware uses 115200), "
            "PD8 TX / PD9 RX crossover, shared ground, target power, and CM7 flashing\n",
        )
    except (serial.SerialException, ProtocolError, OSError) as error:
        parser.exit(1, f"error: {error}\n")
    if args.echo:
        return 0


    print(
        f"Received {len(capture.rows)} rows; CRC errors={capture.crc_errors}, "
        f"malformed frames={capture.malformed_frames}, "
        f"duplicate frames={capture.duplicate_frames}."
    )
    # Non-finite plant/controller output is simulation evidence, not UART damage.
    # Preserve it in the log and report it instead of discarding the whole capture.
    for index, row in enumerate(capture.rows):
        fields = _csv_fields(row, index + 1)
        invalid = [name for name, value in zip(capture.header_fields, fields)
                   if not math.isfinite(float(value))]
        if invalid:
            print(f"WARNING: non-finite model/plant output starts at row {index + 1}, "
                  f"model time {fields[0]} s: {', '.join(invalid)}. "
                  "The complete capture is preserved; inspect the generated model's dynamics.")
            break
    destination = args.output if args.output is not None else prompt_csv_destination()
    try:
        save_capture(capture, destination)
    except OSError as error:
        parser.exit(1, f"error saving {destination}: {error}\n")
    print(f"Saved {len(capture.rows)} rows to {destination}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
