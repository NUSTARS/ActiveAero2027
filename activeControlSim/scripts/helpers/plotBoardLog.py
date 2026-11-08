#!/usr/bin/env python3
"""Plot a flight-computer board log (e.g. data/board-test-11-4-26.csv).

Overlays raw sensor measurements against the matching navigation estimates
so the two can be compared directly:

  1. Gyro        LSM/BMI angular rate vs nav p/q/r (+ nav gyro bias)
  2. Accel       LSM/BMI specific force vs nav accel estimate (+ accel bias)
  3. Bias        nav gyro/accel/altitude/LLA bias (+ implied gyro bias)
  4. Attitude    nav Euler angles, quaternion components and norm
  5. Velocity    GNSS NED velocity vs nav NED velocity
  6. Position    GNSS lat/lon/alt (local NED about first fix) vs nav position
  7. Air data    barometers, nav dynamic pressure, nav altitude bias
  8. Status      flight mode, GNSS fix/sats/valid, loop timing
  9. Control     per-axis commands and individual fin deflections

Every time-series plot is shaded by nav flight mode (IDLE/BOOST/ACTIVE/
LOCKOUT). Columns that are identically zero (e.g. an unpopulated sensor) are
skipped automatically.

Set LOG_PATH and PLOT_WINDOW at the top of this file to choose the log and the
time range.

Examples (from activeControlSim/)::

    py scripts/helpers/plotBoardLog.py
    py scripts/helpers/plotBoardLog.py --only gyro accel
    py scripts/helpers/plotBoardLog.py --save results/board-test --no-show
"""

from __future__ import annotations

import argparse
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# ------------------------------------------------------------ user settings
# Board log to plot.
LOG_PATH = (Path(__file__).resolve().parents[2]
            / "data/nov-flight/FLIGHT_DATA.xlsx")

# (start, end) in seconds relative to launch, where t=0 is the first sample
# out of IDLE. Set to None to plot the whole log in time since log start.
PLOT_WINDOW = (-1.0, 20.0)

FLIGHT_MODES ={0: "IDLE", 1: "BOOST", 2: "ACTIVE", 3: "LOCKOUT"}
MODE_COLORS = {0: None, 1: "#f4a259", 2: "#5b8e7d", 3: "#bc4b51"}

# Fixed per-axis colors so "X" reads the same on every plot (matches
# scripts/plotSensorData.m).
AX_COLORS = ("#d95319", "#77ac30", "#0072bd")
EXTRA_COLORS = ("#7e2f8e", "#4dbeee", "#a2142f", "#edb120")

# Firmware logs gyro in deg/s; nav works in rad/s.
GYRO_RAW_UNITS = "deg/s"
EARTH_RADIUS_M = 6378137.0
UINT32_MAX = 4294967295


# ----------------------------------------------------------------- helpers
def load_log(path: Path) -> pd.DataFrame:
    df = pd.read_csv(path)
    df["t_s"] = df["timestamp_us_delta"].cumsum() * 1e-6
    return df


def launch_time(df: pd.DataFrame) -> float:
    """Log time [s] of launch: the first sample where nav leaves IDLE."""
    left_idle = df["nav_flightMode_enum"].to_numpy() != 0
    if not left_idle.any():
        raise SystemExit("No launch in this log: nav never leaves IDLE.")
    return float(df["t_s"].iloc[int(np.argmax(left_idle))])


def has_data(df: pd.DataFrame, col: str) -> bool:
    return col in df and np.any(df[col].to_numpy() != 0)


def shade_modes(ax, df: pd.DataFrame) -> None:
    """Shade spans of non-IDLE flight mode on an axis."""
    if "nav_flightMode_enum" not in df:
        return
    t = df["t_s"].to_numpy()
    mode = df["nav_flightMode_enum"].to_numpy()
    edges = np.flatnonzero(np.diff(mode)) + 1
    starts = np.r_[0, edges]
    ends = np.r_[edges, len(mode) - 1]
    for s, e in zip(starts, ends):
        color = MODE_COLORS.get(int(mode[s]))
        if color:
            ax.axvspan(t[s], t[e], color=color, alpha=0.12, lw=0)


def mode_legend_handles():
    from matplotlib.patches import Patch
    return [Patch(color=c, alpha=0.3, label=FLIGHT_MODES[m])
            for m, c in MODE_COLORS.items() if c]


def new_fig(title: str, nrows: int, ncols: int = 1, **kw):
    fig, axes = plt.subplots(nrows, ncols, sharex=True, squeeze=False,
                             figsize=kw.pop("figsize", (12, 2.6 * nrows + 1)),
                             **kw)
    fig.suptitle(title, fontweight="bold")
    return fig, axes.ravel()


def finish(fig, axes, df, note: str | None = None) -> None:
    if note:
        fig.suptitle(fig._suptitle.get_text() + "\n" + note,
                     fontweight="bold")
    for ax in axes:
        if not ax.has_data():
            ax.set_visible(False)
            continue
        shade_modes(ax, df)
        ax.grid(True, alpha=0.3)
        if ax.get_legend_handles_labels()[0]:
            ax.legend(loc="upper right", fontsize=8, ncol=3)
    visible = [ax for ax in axes if ax.get_visible()]
    if visible:
        visible[-1].set_xlabel(df.attrs.get("time_label", "Time [s]"))
        visible[-1].tick_params(labelbottom=True)
        # Mode legend once, on the figure.
        fig.legend(handles=mode_legend_handles(), loc="upper left",
                   fontsize=8, ncol=3, frameon=False)
    fig.tight_layout(rect=(0, 0, 1, 0.97))


def gnss_mask(df: pd.DataFrame) -> np.ndarray:
    """Rows where the GNSS solution is usable."""
    m = np.ones(len(df), dtype=bool)
    for col in ("gps_valid", "gnssFixOK"):
        if col in df:
            m &= df[col].to_numpy() != 0
    if "latitude" in df:
        m &= df["latitude"].to_numpy() != 0
    return m


def masked(series: pd.Series, mask: np.ndarray) -> np.ndarray:
    v = series.to_numpy(dtype=float).copy()
    v[~mask] = np.nan
    return v


# ------------------------------------------------------------------ figures
def plot_gyro(df):
    fig, axes = new_fig("Angular rate: raw gyro vs nav estimate", 4)
    d2r = np.pi / 180.0
    t = df["t_s"]
    for i, (axis, nav) in enumerate(zip("xyz", ("p", "q", "r"))):
        ax = axes[i]
        for sensor, ls in (("lsm", "-"), ("bmi", ":")):
            col = f"{sensor}_gyro_{axis}"
            if has_data(df, col):
                ax.plot(t, df[col] * d2r, ls, color=AX_COLORS[i], alpha=0.45,
                        lw=0.8, label=f"{sensor.upper()} raw")
        ax.plot(t, df[f"nav_{nav}Est_rps"], color="k", lw=1.0,
                label=f"nav {nav}Est")
        ax.set_ylabel(f"{axis.upper()} [rad/s]")
    ax = axes[3]
    for i, axis in enumerate("xyz"):
        ax.plot(t, df[f"nav_gyroBias_rps_{axis}"], color=AX_COLORS[i],
                label=f"bias {axis}")
    ax.set_ylabel("Gyro bias [rad/s]")
    finish(fig, axes, df, note=f"(raw converted from {GYRO_RAW_UNITS})")
    return fig


def plot_accel(df):
    fig, axes = new_fig("Acceleration: raw accelerometer vs nav estimate", 4)
    t = df["t_s"]
    for i, axis in enumerate("xyz"):
        ax = axes[i]
        for sensor, ls in (("lsm", "-"), ("bmi", ":")):
            col = f"{sensor}_accel_{axis}"
            if has_data(df, col):
                ax.plot(t, df[col], ls, color=AX_COLORS[i], alpha=0.45,
                        lw=0.8, label=f"{sensor.upper()} raw")
        ax.plot(t, df[f"nav_{axis}AccEst_mps2"], color="k", lw=1.0,
                label=f"nav {axis}AccEst")
        ax.set_ylabel(f"{axis.upper()} [m/s²]")
    ax = axes[3]
    for i, axis in enumerate("xyz"):
        ax.plot(t, df[f"nav_accelBias_mps2_{axis}"], color=AX_COLORS[i],
                label=f"bias {axis}")
    ax.set_ylabel("Accel bias [m/s²]")
    finish(fig, axes, df)
    return fig


def plot_attitude(df):
    fig, axes = new_fig("Nav attitude", 3)
    t = df["t_s"]
    r2d = 180.0 / np.pi
    for i, (name, lbl) in enumerate((("phi", "roll φ"), ("theta", "pitch θ"),
                                     ("psi", "yaw ψ"))):
        axes[0].plot(t, df[f"nav_{name}Est_rad"] * r2d, color=AX_COLORS[i],
                     label=lbl)
    axes[0].set_ylabel("Euler [deg]")
    q = np.column_stack([df[f"nav_qEst_na_{k}"] for k in range(4)])
    for k in range(4):
        axes[1].plot(t, q[:, k], color=(("k",) + AX_COLORS)[k], label=f"q{k}")
    axes[1].set_ylabel("Quaternion [-]")
    axes[2].plot(t, np.linalg.norm(q, axis=1) - 1.0, color="k")
    axes[2].set_ylabel("|q| − 1")
    finish(fig, axes, df)
    return fig


def plot_velocity(df):
    fig, axes = new_fig("NED velocity: GNSS vs nav estimate", 3)
    t = df["t_s"]
    m = gnss_mask(df)
    for i, (gcol, ncol, lbl) in enumerate((
            ("velocity_north", "nav_xVelEstNed_mps", "North"),
            ("velocity_east", "nav_yVelEstNed_mps", "East"),
            ("velocity_down", "nav_zVelEstNed_mps", "Down"))):
        ax = axes[i]
        ax.plot(t, masked(df[gcol], m), ".", ms=2, color=AX_COLORS[i],
                alpha=0.6, label="GNSS")
        ax.plot(t, df[ncol], color="k", lw=1.0, label="nav")
        ax.set_ylabel(f"{lbl} [m/s]")
    finish(fig, axes, df)
    return fig


def plot_position(df):
    fig, axes = new_fig("Position: GNSS (local NED about first fix) vs nav", 3)
    t = df["t_s"]
    m = gnss_mask(df)
    nav_cols = ("nav_xPosEst_m", "nav_yPosEst_m", "nav_zPosEst_m")
    if not m.any():
        for i, (c, lbl) in enumerate(zip(nav_cols, ("North", "East", "Down"))):
            axes[i].plot(t, df[c], color="k", label="nav")
            axes[i].set_ylabel(f"{lbl} [m]")
        finish(fig, axes, df)
        return fig

    i0 = int(np.flatnonzero(m)[0])
    lat0 = np.deg2rad(df["latitude"].iloc[i0])
    lon0 = np.deg2rad(df["longitude"].iloc[i0])
    alt0 = df["altitude"].iloc[i0]
    lat = np.deg2rad(masked(df["latitude"], m))
    lon = np.deg2rad(masked(df["longitude"], m))
    gnss_ned = (
        (lat - lat0) * EARTH_RADIUS_M,
        (lon - lon0) * EARTH_RADIUS_M * np.cos(lat0),
        -(masked(df["altitude"], m) - alt0),
    )
    # Nav position is referenced to its own origin; subtract its value at the
    # first fix so shapes line up, and report the offset that was removed.
    for i, (c, g, lbl) in enumerate(zip(nav_cols, gnss_ned,
                                        ("North", "East", "Down"))):
        ax = axes[i]
        offset = df[c].iloc[i0]
        ax.plot(t, g, ".", ms=2, color=AX_COLORS[i], alpha=0.6, label="GNSS")
        ax.plot(t, df[c] - offset, color="k", lw=1.0,
                label=f"nav − {offset:.4g} m")
        ax.set_ylabel(f"{lbl} [m]")
    finish(fig, axes, df,
           note=f"(origin: first valid fix at t={df['t_s'].iloc[i0]:.1f} s, "
                f"{np.rad2deg(lat0):.6f}, {np.rad2deg(lon0):.6f}, {alt0:.1f} m)")
    return fig


def plot_air_data(df):
    fig, axes = new_fig("Air data", 3)
    t = df["t_s"]
    for k, sensor in enumerate(("bmp581", "bmp585")):
        if df[f"{sensor}_pressure"].nunique() > 1 or has_data(df, f"{sensor}_pressure"):
            axes[0].plot(t, df[f"{sensor}_pressure"], color=EXTRA_COLORS[k],
                         label=sensor.upper())
        if has_data(df, f"{sensor}_temperature"):
            axes[1].plot(t, df[f"{sensor}_temperature"], color=EXTRA_COLORS[k],
                         label=sensor.upper())
    axes[0].set_ylabel("Pressure [raw]")
    axes[1].set_ylabel("Temperature [°C]")
    axes[2].plot(t, df["nav_dynPressureEst_Pa"], color="k", label="nav q̄")
    axes[2].set_ylabel("Dyn. pressure [Pa]")
    ax2 = axes[2].twinx()
    ax2.plot(t, df["nav_altitudeBias_m"], color=EXTRA_COLORS[2], lw=0.8,
             label="nav altitude bias")
    ax2.set_ylabel("Alt bias [m]", color=EXTRA_COLORS[2])
    finish(fig, axes, df)
    return fig


def plot_status(df):
    fig, axes = new_fig("Status and timing", 4)
    t = df["t_s"]
    axes[0].step(t, df["nav_flightMode_enum"], where="post", color="k")
    axes[0].set_yticks(list(FLIGHT_MODES), list(FLIGHT_MODES.values()))
    axes[0].set_ylabel("Flight mode")
    axes[1].step(t, df["gnss_fix_type"], where="post", color=AX_COLORS[2],
                 label="fix type")
    axes[1].step(t, df["gps_valid"], where="post", color=AX_COLORS[0],
                 label="gps_valid")
    if "gnssFixOK" in df:
        axes[1].step(t, df["gnssFixOK"] * 0.9, where="post", ls="--",
                     color=AX_COLORS[1], label="gnssFixOK (×0.9)")
    axes[1].set_ylabel("GNSS fix")
    axes[2].step(t, df["gnss_satellites"], where="post", color="k",
                 label="satellites")
    axes[2].set_ylabel("Satellites")
    if "gps_age_ms" in df:
        age = df["gps_age_ms"].astype(float).where(df["gps_age_ms"] != UINT32_MAX)
        ax2 = axes[2].twinx()
        ax2.plot(t, age, color=EXTRA_COLORS[0], lw=0.8)
        ax2.set_ylabel("GPS age [ms]", color=EXTRA_COLORS[0])
    dt_ms = df["timestamp_us_delta"] * 1e-3
    axes[3].plot(t, dt_ms, ".", ms=1.5, color="k")
    axes[3].set_ylabel("Loop dt [ms]")
    med = float(np.median(dt_ms[1:]))
    axes[3].set_title(f"median {med:.2f} ms, max {dt_ms.max():.1f} ms, "
                      f"{int(df['packet_counter'].diff().gt(1).sum())} "
                      "dropped-packet gaps", fontsize=9)
    finish(fig, axes, df)
    return fig


def plot_biases(df, smooth_s: float = 0.5):
    """All nav bias states in one place.

    Gyro bias is overlaid with the implied bias, raw gyro − nav rate,
    smoothed over `smooth_s` with a rolling median. If nav just subtracts
    its bias, the two lines should match.
    """
    lla_cols = [f"nav_llaBias_na_{a}" for a in "xyz" if f"nav_llaBias_na_{a}" in df]
    lla_live = [c for c in lla_cols if has_data(df, c)]
    fig, axes = new_fig("Nav bias estimates", 4 if lla_live else 3)
    t = df["t_s"]
    d2r = np.pi / 180.0
    dt = float(np.median(df["timestamp_us_delta"].iloc[1:])) * 1e-6 or 0.01
    win = max(1, int(round(smooth_s / dt)))

    ax = axes[0]
    for i, (axis, nav) in enumerate(zip("xyz", "pqr")):
        ax.plot(t, df[f"nav_gyroBias_rps_{axis}"], color=AX_COLORS[i],
                label=f"bias {axis}")
        if has_data(df, f"lsm_gyro_{axis}"):
            implied = (df[f"lsm_gyro_{axis}"] * d2r - df[f"nav_{nav}Est_rps"])
            ax.plot(t, implied.rolling(win, center=True, min_periods=1).median(),
                    ":", color=AX_COLORS[i], lw=0.9,
                    label=f"raw−nav {axis} ({smooth_s:g}s med)")
    ax.set_ylabel("Gyro bias [rad/s]")

    for i, axis in enumerate("xyz"):
        axes[1].plot(t, df[f"nav_accelBias_mps2_{axis}"], color=AX_COLORS[i],
                     label=f"bias {axis}")
    axes[1].set_ylabel("Accel bias [m/s²]")

    axes[2].plot(t, df["nav_altitudeBias_m"], color="k", label="altitude bias")
    axes[2].set_ylabel("Alt bias [m]")

    if lla_live:
        for i, col in enumerate(lla_live):
            axes[3].plot(t, df[col], color=AX_COLORS[i],
                         label=col.removeprefix("nav_"))
        axes[3].set_ylabel("LLA bias [-]")

    zero = [c for c in lla_cols if c not in lla_live]
    finish(fig, axes, df,
           note=f"({', '.join(zero)} all zero)" if zero else None)
    return fig


def plot_control(df):
    fig, axes = new_fig("Control", 4)
    t = df["t_s"]
    for i, axis in enumerate(("roll", "pitch", "yaw")):
        ax = axes[i]
        ax.plot(t, df[f"ctl_i_{axis}_control_deg"], color=AX_COLORS[i],
                label="inner control")
        ax.set_ylabel(f"{axis} [deg]")
        ax2 = ax.twinx()
        ax2.plot(t, df[f"ctl_o_{axis}_rateCmd_rps"], color="k", lw=0.8,
                 alpha=0.7)
        ax2.set_ylabel("rate cmd [rad/s]", fontsize=8)
        sat = df[f"ctl_i_{axis}_saturated"].to_numpy() != 0
        if sat.any():
            ax.plot(t[sat], df[f"ctl_i_{axis}_control_deg"][sat], "x",
                    ms=3, color=EXTRA_COLORS[2], label="saturated")
    for k in range(4):
        axes[3].plot(t, df[f"ctl_control_deg_{k}"],
                     color=(("k",) + AX_COLORS)[k], lw=0.9, label=f"fin {k}")
    axes[3].set_ylabel("Fin deflection [deg]")
    finish(fig, axes, df)
    return fig


FIGURES = {
    "gyro": plot_gyro,
    "accel": plot_accel,
    "bias": plot_biases,
    "attitude": plot_attitude,
    "velocity": plot_velocity,
    "position": plot_position,
    "airdata": plot_air_data,
    "status": plot_status,
    "control": plot_control,
}


# --------------------------------------------------------------------- main
def main() -> None:
    p = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    p.add_argument("--tmin", type=float,
                   help="start time since log start [s] (needs PLOT_WINDOW = None)")
    p.add_argument("--tmax", type=float,
                   help="end time since log start [s] (needs PLOT_WINDOW = None)")
    p.add_argument("--only", nargs="+", choices=list(FIGURES),
                   help="only draw these figures")
    p.add_argument("--save", type=Path, metavar="DIR",
                   help="write each figure as DIR/<csvname>_<figure>.png")
    p.add_argument("--no-show", action="store_true",
                   help="don't open interactive windows")
    args = p.parse_args()
    if PLOT_WINDOW and (args.tmin is not None or args.tmax is not None):
        p.error("--tmin/--tmax need PLOT_WINDOW = None")
    if PLOT_WINDOW and PLOT_WINDOW[0] >= PLOT_WINDOW[1]:
        p.error("PLOT_WINDOW start must be less than its end")

    df = load_log(LOG_PATH)
    if PLOT_WINDOW:
        t_launch = launch_time(df)
        print(f"launch at t={t_launch:.3f} s into the log")
        df["t_s"] -= t_launch
        df = df[df["t_s"].between(*PLOT_WINDOW)]
    if args.tmin is not None:
        df = df[df["t_s"] >= args.tmin]
    if args.tmax is not None:
        df = df[df["t_s"] <= args.tmax]
    df = df.reset_index(drop=True)
    if df.empty:
        raise SystemExit("No samples in the selected time window.")
    if PLOT_WINDOW:
        df.attrs["time_label"] = "Time since launch [s]"

    names = args.only or list(FIGURES)
    if args.save:
        args.save.mkdir(parents=True, exist_ok=True)
    for name in names:
        fig = FIGURES[name](df)
        if args.save:
            out = args.save / f"{LOG_PATH.stem}_{name}.png"
            fig.savefig(out, dpi=150)
            print(f"wrote {out}")
        if args.no_show:
            plt.close(fig)
    if not args.no_show:
        plt.show()


if __name__ == "__main__":
    main()
