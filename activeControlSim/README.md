# activeControl

## Setup

From MATLAB, run `setupPaths` once per session (from anywhere -- it
locates the repo root from its own file location):

```matlab
run('<repoRoot>/setupPaths.m')
```

This adds `scripts/`, `scripts/helpers/`, `dataDictionaries/`, and every
`models/<name>/` folder to the path, so models and scripts run
regardless of your current folder.

## File structure

- `models/<name>/` -- one folder per model (`plant`, `control`,
  `navigation`), each holding its `.slx` and the `.sldd` linked to it
- `dataDictionaries/` -- one `define*.m` function per data dictionary,
  each returning that dictionary's param struct
- `scripts/` -- build/plotting scripts, with generic reusable helpers
  under `scripts/helpers/`

## Data dictionary workflow

Each model's constants (mass, initial conditions, lookup tables, ...)
live in one `dataDictionaries/define*.m` function, returning a single
struct grouped by field, e.g. for the plant model:

```
P.vehicleParams.mass_kg = 18;
P.icParams.eul0_rad     = [0, pi/2, 0];
...
```

`scripts/buildDataDictionaries.m` holds a `CONFIG` table listing every
model/dictionary pair:

```
% modelFile                 dictName        defineFcn
'models/plant/plant.slx',   'plantParams',  @definePlantDD
```

Running it loops over `CONFIG` and, for each row, calls `defineFcn` and
links the resulting `.sldd` to `modelFile` via
`scripts/helpers/linkDataDictionary.m` (a generic helper -- it doesn't
know or care which model/dictionary it's given).

**To add a model's dictionary:** write `dataDictionaries/define<Name>DD.m`
returning its param struct, then add a row to `CONFIG`.

**To change a parameter value:** edit the relevant `define*.m`, then
re-run `buildDataDictionaries.m`.

**Gotcha:** a model's `DataDictionary` property resolves by bare
filename via MATLAB's current folder/path, not a stored path. It just
works when you open a model from within its own `models/<name>/`
folder; from elsewhere you'll see "unable to find data dictionary" and
the model won't simulate unless you've run `setupPaths` (see Setup,
above).

## Plotting workflow

Run the sim, then run the plotting script (it's a script, not a
function -- it reads `out` from the workspace):

```matlab
out = sim('plant');
scripts/plotRocketTrajectory.m
```

It expects `out.simout` as nested bus structs (`eom_bus`,
`aeroParams_bus`) and opens two fixed-number figures so re-running
overwrites them instead of piling up new windows:

- **Figure 101 (States):** position, velocity, tilt & roll, angle of
  attack, body angular rates, raw quaternion
- **Figure 102 (Trajectory):** 3D flight path with nose/velocity triads

Optional overrides (set in the workspace before running): `numFrames`,
`bodyScale`, `forwardAxis`.
