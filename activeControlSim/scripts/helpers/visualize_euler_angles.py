#!/usr/bin/env python3
"""Plot live Euler angles from a serial port with a lightweight Pygame renderer.

Expected input (Euler angles in radians, period in milliseconds)::

    MODE: IDLE | Period: 10.227 ms | EULER: Phi=0.1409 rad | Theta=1.5385 rad | Psi=-0.3906 rad

Legacy lines containing only the ``EULER:`` fields are accepted.

Install dependencies with ``py -m pip install pygame-ce pyserial``.
"""

from __future__ import annotations

import argparse
from collections import deque
import math
import queue
import re
import threading
import time
from typing import NamedTuple

import pygame
import serial


EulerAngles = tuple[float, float, float]


class TelemetrySample(NamedTuple):
    timestamp_s: float
    mode: str | None
    period_ms: float | None
    angles: EulerAngles


PLOT_WINDOW_SECONDS = 10.0
ANGLE_LIMIT = math.pi

NUMBER = r"-?\d+(?:\.\d*)?(?:[eE][+-]?\d+)?"
OUTPUT_LINE = re.compile(
    r"(?:MODE:\s*(?P<mode>[^|]+)\s*\|\s*Period:\s*(?P<period>" + NUMBER +
    r")\s*ms\s*\|\s*)?EULER:\s*Phi\s*=\s*(?P<phi>" + NUMBER + r")\s*rad\s*\|"
    r"\s*Theta\s*=\s*(?P<theta>" + NUMBER + r")\s*rad\s*\|\s*Psi\s*=\s*(?P<psi>" +
    NUMBER + r")\s*rad",
    re.IGNORECASE,
)
ANGLE_SERIES = (
    ("Phi", (210, 55, 55)),
    ("Theta", (30, 135, 75)),
    ("Psi", (45, 105, 205)),
)
Y_TICKS = (
    (-math.pi, "-π"),
    (-math.pi / 2, "-π/2"),
    (0.0, "0"),
    (math.pi / 2, "π/2"),
    (math.pi, "π"),
)


def parse_telemetry_line(
    line: str,
) -> tuple[str | None, float | None, EulerAngles] | None:
    """Parse optional MODE/Period metadata and Euler angles from one serial line."""
    match = OUTPUT_LINE.search(line)
    if match is None:
        return None
    groups = match.groupdict()
    mode = groups["mode"].strip() if groups["mode"] is not None else None
    period_ms = float(groups["period"]) if groups["period"] is not None else None
    angles = tuple(float(groups[name]) for name in ("phi", "theta", "psi"))
    return mode, period_ms, angles


def parse_euler_line(line: str) -> EulerAngles | None:
    """Return the Euler angles in radians, preserving the original parser API."""
    telemetry = parse_telemetry_line(line)
    return telemetry[2] if telemetry is not None else None


def chart_panels(width: int, height: int) -> list[pygame.Rect]:
    """Return three stacked chart panels sized to the current window."""
    left, right, top, bottom, gap = 80, 28, 132, 42, 16
    panel_height = max(80, (height - top - bottom - 2 * gap) // 3)
    panel_width = max(100, width - left - right)
    return [
        pygame.Rect(left, top + index * (panel_height + gap), panel_width, panel_height)
        for index in range(3)
    ]


def _plot_bounds(panel: pygame.Rect) -> tuple[int, int, int, int]:
    return panel.left + 48, panel.top + 23, panel.right - 10, panel.bottom - 8


def plot_series_points(history: deque[TelemetrySample], now: float, angle_index: int,
                       plot_bounds: tuple[int, int, int, int],
                       window_seconds: float = PLOT_WINDOW_SECONDS) -> list[tuple[int, int]]:
    """Project one angle history to plot pixels in a fixed [-pi, pi] range."""
    left, top, right, bottom = plot_bounds
    span_x = max(1, right - left)
    span_y = max(1, bottom - top)
    oldest = now - window_seconds
    points = []
    for sample in history:
        if sample.timestamp_s < oldest or sample.timestamp_s > now:
            continue
        x = round(right - (now - sample.timestamp_s) * span_x / window_seconds)
        value = max(-ANGLE_LIMIT, min(ANGLE_LIMIT, sample.angles[angle_index]))
        y = round(bottom - (value + ANGLE_LIMIT) * span_y / (2 * ANGLE_LIMIT))
        points.append((x, y))
    return points


def draw_frame(screen: pygame.Surface, history: deque[TelemetrySample],
               angles: EulerAngles | None, port_name: str, baudrate: int,
               title_font: pygame.font.Font, angle_font: pygame.font.Font,
               small_font: pygame.font.Font, now: float | None = None,
               mode: str | None = None, period_ms: float | None = None
               ) -> list[list[tuple[int, int]]]:
    """Draw a white-background scrolling plot and return its three line paths."""
    if now is None:
        now = time.monotonic()
    width, height = screen.get_size()
    screen.fill((255, 255, 255))

    title = title_font.render("Live Euler Angles", True, (25, 30, 38))
    screen.blit(title, (20, 16))
    status = small_font.render(
        f"{port_name} @ {baudrate} baud  |  last {PLOT_WINDOW_SECONDS:.0f} s  |  Escape/Q exits",
        True, (90, 98, 110),
    )
    screen.blit(status, (22, 54))

    mode_color = (35, 145, 80) if mode and mode.upper() == "IDLE" else (40, 85, 150)
    metadata_lines = (
        (small_font.render(f"MODE: {mode or '—'}", True, mode_color), 10),
        (small_font.render(
            f"PERIOD: {period_ms:.3f} ms" if period_ms is not None else "PERIOD: —",
            True, (55, 62, 72)
        ), 30),
    )
    for label, y in metadata_lines:
        screen.blit(label, (width - label.get_width() - 20, y))
    if angles is None:
        readout_lines = ("Waiting for EULER data…",)
    else:
        readout_lines = tuple(
            f"{name}: {value:+.4f} rad"
            for (name, _color), value in zip(ANGLE_SERIES, angles)
        )
    readouts = [angle_font.render(line, True, (30, 35, 43)) for line in readout_lines]
    y = 48
    for label in readouts:
        screen.blit(label, (width - label.get_width() - 20, y))
        y += label.get_height() + 1

    paths = []
    panels = chart_panels(width, height)
    for index, (panel, (name, color)) in enumerate(zip(panels, ANGLE_SERIES)):
        pygame.draw.rect(screen, (250, 251, 253), panel)
        pygame.draw.rect(screen, (205, 211, 220), panel, width=1)
        label = small_font.render(name, True, color)
        screen.blit(label, (panel.left + 9, panel.top + 4))
        left, top, right, bottom = _plot_bounds(panel)

        for value, tick_label in Y_TICKS:
            y_tick = round(bottom - (value + ANGLE_LIMIT) * (bottom - top) /
                           (2 * ANGLE_LIMIT))
            pygame.draw.line(screen, (224, 228, 234), (left, y_tick), (right, y_tick), 1)
            tick = small_font.render(tick_label, True, (90, 98, 110))
            screen.blit(tick, (panel.left + 5, y_tick - tick.get_height() // 2))
        for fraction in (0.0, 0.5, 1.0):
            x_tick = round(right - fraction * (right - left))
            pygame.draw.line(screen, (235, 238, 242), (x_tick, top), (x_tick, bottom), 1)

        points = plot_series_points(history, now, index, (left, top, right, bottom))
        paths.append(points)
        if len(points) > 1:
            pygame.draw.lines(screen, color, False, points, width=2)
        elif points:
            pygame.draw.circle(screen, color, points[0], radius=3)

    bottom_panel = panels[-1]
    left, _top, right, _bottom = _plot_bounds(bottom_panel)
    for fraction, label_text in ((0.0, "now"), (0.5, "-5 s"), (1.0, "-10 s")):
        x_tick = round(right - fraction * (right - left))
        label = small_font.render(label_text, True, (90, 98, 110))
        screen.blit(label, (x_tick - label.get_width() // 2, bottom_panel.bottom + 5))
    return paths


def _read_serial(port: serial.Serial, values: queue.Queue[TelemetrySample],
                 stop: threading.Event) -> None:
    while not stop.is_set():
        raw_line = port.readline()
        if not raw_line:
            continue
        line = raw_line.decode("utf-8", errors="replace").strip()
        telemetry = parse_telemetry_line(line)
        if telemetry is None:
            continue
        mode, period_ms, angles = telemetry
        sample = TelemetrySample(time.monotonic(), mode, period_ms, angles)
        try:
            values.put_nowait(sample)
        except queue.Full:
            try:
                values.get_nowait()
            except queue.Empty:
                pass
            values.put_nowait(sample)


def visualize(port_name: str = "COM4", baudrate: int = 115200) -> None:
    latest: queue.Queue[TelemetrySample] = queue.Queue(maxsize=4096)
    history: deque[TelemetrySample] = deque()
    stop = threading.Event()
    connection = serial.Serial(port_name, baudrate=baudrate, timeout=0.1)
    reader = threading.Thread(target=_read_serial,
                              args=(connection, latest, stop), daemon=True)

    pygame.init()
    screen = pygame.display.set_mode((1100, 760), pygame.RESIZABLE)
    pygame.display.set_caption("Live Euler angle plots")
    title_font = pygame.font.SysFont("Arial", 27, bold=True)
    angle_font = pygame.font.SysFont("Consolas", 19)
    small_font = pygame.font.SysFont("Arial", 14)
    clock = pygame.time.Clock()
    current_angles: EulerAngles | None = None
    current_mode: str | None = None
    current_period_ms: float | None = None
    reader.start()

    try:
        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                elif event.type == pygame.KEYDOWN and event.key in (pygame.K_ESCAPE, pygame.K_q):
                    running = False
            while True:
                try:
                    sample = latest.get_nowait()
                except queue.Empty:
                    break
                history.append(sample)
                current_angles = sample.angles
                current_mode = sample.mode
                current_period_ms = sample.period_ms
            now = time.monotonic()
            while history and history[0].timestamp_s < now - PLOT_WINDOW_SECONDS:
                history.popleft()
            draw_frame(screen, history, current_angles, port_name, baudrate,
                       title_font, angle_font, small_font, now,
                       current_mode, current_period_ms)
            pygame.display.flip()
            clock.tick(60)
    finally:
        stop.set()
        reader.join(timeout=0.5)
        connection.close()
        pygame.quit()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--port", default="COM4", help="serial port (default: COM4)")
    parser.add_argument("--baud", type=int, default=115200,
                        help="UART baud rate (default: 115200)")
    args = parser.parse_args()
    try:
        visualize(args.port, args.baud)
    except serial.SerialException as error:
        parser.error(f"could not open/read {args.port}: {error}")


if __name__ == "__main__":
    main()
