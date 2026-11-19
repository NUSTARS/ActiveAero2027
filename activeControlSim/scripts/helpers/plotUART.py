"""Real-time UART plots. Install: py -m pip install pygame pyserial

Run: py plotUART.py --port COM4
Preview without hardware: py plotUART.py --demo
Escape closes the window; Space pauses the display; R resets plotted history.
Uses readTelemetryUART.py beside this file for SECDED/CRC packet validation.
No files are recorded. Close other programs using the same COM port first.
"""
from __future__ import annotations

import argparse
from collections import deque
import math
import queue
import threading
import time

from readTelemetryUART import StreamDecoder

GROUPS = (
    ("Attitude (rad)", ("nav_phiEst_rad", "nav_thetaEst_rad", "nav_psiEst_rad"), ("phi", "theta", "psi")),
    ("NED velocity (m/s)", ("nav_xVelEstNed_mps", "nav_yVelEstNed_mps", "nav_zVelEstNed_mps"), ("north", "east", "down")),
    ("Raw GPS NED velocity (m/s)", ("gps_velocity_north_mps", "gps_velocity_east_mps", "gps_velocity_down_mps"), ("north", "east", "down")),
    ("Position (m)", ("nav_xPosEst_m", "nav_yPosEst_m", "nav_zPosEst_m"), ("x", "y", "z")),
)
COLORS = ((90, 195, 255), (255, 185, 80), (150, 225, 140))
MODES = {0: "IDLE", 1: "BOOST", 2: "ACTIVE", 3: "LOCKOUT"}


def expand_bounds(bounds, row, fields):
    """Retain session extrema, expanding only, with 10% headroom."""
    for field in fields:
        value = row.get(field)
        if value is None or not math.isfinite(value):
            continue
        if value < bounds[0]:
            bounds[0] = value - max(abs(value) * 0.1, 0.01)
        if value > bounds[1]:
            bounds[1] = value + max(abs(value) * 0.1, 0.01)


def receive(port, baud, events, stop):
    """Serial I/O stays outside the render loop; bounded queues limit latency."""
    decoder = StreamDecoder()
    try:
        import serial
        with serial.Serial(port, baud, timeout=0.1, rtscts=False, dsrdtr=False) as stream:
            while not stop.is_set():
                data = stream.read(max(67, min(stream.in_waiting, 4096)))
                if not data:
                    continue
                received = time.monotonic()
                rows = decoder.feed(data)
                for row in rows:
                    event = (received, row, dict(decoder.stats))
                    try:
                        events.put_nowait(event)
                    except queue.Full:
                        try:
                            events.get_nowait()
                        except queue.Empty:
                            pass
                        events.put_nowait(event)
    except Exception as error:
        # Surface a disconnected/busy COM port in the window and terminal.
        message = f"Serial error: {error}"
        print(message, flush=True)
        while not stop.is_set():
            try:
                events.put(message, timeout=0.1)
                break
            except queue.Full:
                continue


def demo_row(t, sequence):
    row = {"packet_counter": sequence, "gnssFixOK": int(t % 12 > 3),
           "nav_flightMode_enum": int(t // 5) % 4}
    for group, (_, fields, _) in enumerate(GROUPS):
        for axis, field in enumerate(fields):
            row[field] = (group * 10 + 1) * math.sin(t * 0.7 + axis)
    return row


def draw_plot(pg, screen, font, rect, title, fields, labels, samples, now, window, limits):
    pg.draw.rect(screen, (25, 32, 43), rect, border_radius=6)
    screen.blit(font.render(title, True, (230, 235, 245)), (rect.x + 12, rect.y + 9))
    plot = pg.Rect(rect.x + 78, rect.y + 40, max(20, rect.width - 100), max(20, rect.height - 94))
    low, high = limits
    clipped = False
    for i in range(5):
        y = plot.top + i * plot.height / 4
        pg.draw.line(screen, (49, 59, 73), (plot.left, y), (plot.right, y))
        label = font.render(f"{high - (high-low)*i/4:.3g}", True, (160, 172, 190))
        screen.blit(label, (rect.x + 6, y - 8))
    for i, (field, label) in enumerate(zip(fields, labels)):
        points = []
        for stamp, row in samples:
            value = row.get(field)
            if value is None or not math.isfinite(value):
                if len(points) > 1:
                    pg.draw.lines(screen, COLORS[i], False, points, 2)
                points = []
                continue
            x = plot.right - (now - stamp) / window * plot.width
            y = plot.bottom - (value - low) / (high - low) * plot.height
            clipped |= value < low or value > high
            y = max(plot.top, min(plot.bottom, y))
            points.append((max(plot.left, min(plot.right, x)), y))
        if len(points) > 1:
            pg.draw.lines(screen, COLORS[i], False, points, 2)
        value = samples[-1][1].get(field) if samples else None
        text = font.render(f"{label}: " + (f"{value:.4g}" if value is not None else "N/A"), True, COLORS[i])
        screen.blit(text, (plot.left + i * plot.width / 3, plot.bottom + 7))
    text = font.render(f"-{window:g}s                                      now (host reception time)", True, (155, 165, 180))
    screen.blit(text, (plot.left, rect.bottom - 18))
    if clipped:
        warning = font.render("OUT OF RANGE", True, (255, 150, 100))
        screen.blit(warning, (rect.right-warning.get_width()-12, rect.y+9))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--port", default="COM4")
    parser.add_argument("--baud", type=int, default=115200)
    parser.add_argument("--window", type=float, default=15, help="visible history in seconds (default 15)")
    parser.add_argument("--demo", action="store_true", help="show synthetic data without opening a serial port")
    parser.add_argument("--duration", type=float, help="close automatically after this many seconds")
    parser.add_argument("--angle-range", type=float, nargs=2, default=(-math.pi, math.pi), metavar=("MIN", "MAX"), help="fixed attitude bounds in rad")
    parser.add_argument("--velocity-range", type=float, nargs=2, default=(-1, 1), metavar=("MIN", "MAX"), help="initial model/GPS velocity bounds in m/s; expand without shrinking")
    parser.add_argument("--position-range", type=float, nargs=2, default=(-1, 1), metavar=("MIN", "MAX"), help="initial position bounds in m; expand without shrinking")
    args = parser.parse_args(argv)
    for limits in (args.angle_range, args.velocity_range, args.position_range):
        if not all(math.isfinite(v) for v in limits) or limits[0] >= limits[1]:
            parser.error("axis bounds must be finite with MIN < MAX")
    velocity_bounds = list(args.velocity_range)
    position_bounds = list(args.position_range)
    ranges = (args.angle_range, velocity_bounds, velocity_bounds, position_bounds)
    velocity_fields = GROUPS[1][1] + GROUPS[2][1]
    if not math.isfinite(args.window) or args.window <= 0:
        parser.error("--window must be finite and positive")
    if args.duration is not None and (not math.isfinite(args.duration) or args.duration <= 0):
        parser.error("--duration must be finite and positive")
    try:
        import pygame as pg
    except ImportError:
        parser.error("pygame is required: py -m pip install pygame pyserial")
    pg.init()
    desktop_width, desktop_height = pg.display.get_desktop_sizes()[0]
    screen = pg.display.set_mode((min(1100, desktop_width - 80), min(800, desktop_height - 150)), pg.RESIZABLE)
    pg.display.set_caption("UART Telemetry" + (" — DEMO" if args.demo else f" — {args.port}"))
    font = pg.font.SysFont("Consolas", 17)
    clock = pg.time.Clock()
    events = queue.Queue(maxsize=4096)
    stop = threading.Event()
    worker = None
    # Hard memory bound even if the requested window is very large.
    samples = deque(maxlen=120000)
    latest, stats = None, {}
    started = time.monotonic()
    last_received = None
    paused, running = False, True
    message = "DEMO: synthetic values" if args.demo else f"Waiting for valid telemetry on {args.port}..."
    if not args.demo:
        worker = threading.Thread(target=receive, args=(args.port, args.baud, events, stop), daemon=True)
        worker.start()
    try:
        while running:
            now = time.monotonic()
            for event in pg.event.get():
                if event.type == pg.QUIT or (event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE):
                    running = False
                elif event.type == pg.KEYDOWN and event.key == pg.K_SPACE:
                    paused = not paused
                    if not paused:
                        samples.clear()
                elif event.type == pg.KEYDOWN and event.key == pg.K_r:
                    samples.clear()
            if args.demo:
                latest = demo_row(now - started, int((now-started)*100))
                last_received = now
                if not paused:
                    expand_bounds(velocity_bounds, latest, velocity_fields)
                    expand_bounds(position_bounds, latest, GROUPS[3][1])
                    samples.append((now, latest))
            while True:
                try:
                    event = events.get_nowait()
                except queue.Empty:
                    break
                if isinstance(event, str):
                    message = event
                    continue
                last_received, latest, stats = event
                message = f"Receiving {args.port} | packets: {stats['packets']} | missing: {stats['missing_packets']} | rejected: {stats['rejected_frames']} | corrected bits: {stats['corrected_bits']}"
                if not paused:
                    expand_bounds(velocity_bounds, latest, velocity_fields)
                    expand_bounds(position_bounds, latest, GROUPS[3][1])
                    samples.append((last_received, latest))
            plot_now = samples[-1][0] if paused and samples else now
            while samples and plot_now - samples[0][0] > args.window:
                samples.popleft()
            screen.fill((14, 20, 29))
            width, height = screen.get_size()
            mode = MODES.get(latest["nav_flightMode_enum"], str(latest["nav_flightMode_enum"])) if latest else "UNKNOWN"
            fix = latest.get("gnssFixOK") if latest else None
            age = now - last_received if last_received is not None else None
            state_lines = (f"Flight mode: {mode}", "FIXOK: " + ("UNKNOWN (v1/no data)" if fix is None else "TRUE" if fix else "FALSE"),
                           "Link: " + ("WAITING" if age is None else f"STALE ({age:.1f}s)" if age > 2 else "LIVE"))
            for i, text in enumerate(state_lines):
                rendered = font.render(text, True, (255, 200, 95) if age is None or age > 2 else (170, 235, 185))
                screen.blit(rendered, (max(8, width - rendered.get_width() - 18), 10 + i * 22))
            screen.blit(font.render("UART TELEMETRY" + (" [PAUSED]" if paused else ""), True, (235, 240, 250)), (15, 12))
            screen.blit(font.render("Space: pause  R: clear  Esc: quit | Angles fixed; other axes expand", True, (160, 175, 195)), (15, 43))
            panel_height = max(100, (height - 130) // len(GROUPS))
            for i, (title, fields, labels) in enumerate(GROUPS):
                draw_plot(pg, screen, font, pg.Rect(12, 90 + i * panel_height, max(180, width - 24), panel_height - 8),
                          title, fields, labels, samples, plot_now, args.window, ranges[i])
            screen.blit(font.render(message, True, (180, 195, 215)), (14, height - 25))
            pg.display.flip()
            clock.tick(30)
            if args.duration and now - started >= args.duration:
                running = False
    finally:
        stop.set()
        if worker:
            worker.join(timeout=1)
        pg.quit()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
