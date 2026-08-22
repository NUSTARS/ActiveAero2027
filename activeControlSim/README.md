# activeControl

## Setup

From MATLAB, run `setupPaths` once per session (from anywhere -- it
locates the repo root from its own file location):

```matlab
run('<repoRoot>/setupPaths.m')
```

This recursively adds every folder in the repo to the path (skipping
version control, generated Simulink/code-gen artifacts, and saved
results), so models and scripts run regardless of your current folder.
New folders -- another `models/<name>/`, a new script subfolder -- are
picked up automatically; nothing needs to be named here.

## File structure

- `models/<name>/` -- one folder per model (`plant`, `control`,
  `navigation`), each holding its `.slx` and the `.sldd` linked to it
- `dataDictionaries/` -- one `define*.m` function per data dictionary,
  each returning that dictionary's param struct
- `scripts/` -- build/run/plotting scripts, with generic reusable
  helpers under `scripts/helpers/`
- `results/` -- saved sim outputs from `runModel.m` (gitignored)

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
re-run `buildDataDictionaries.m`. It skips any dictionary whose `.sldd`
is already newer than its `define*.m` -- set `forceRebuild = true` in
the workspace first to rebuild everything regardless.

**Gotcha:** a model's `DataDictionary` property resolves by bare
filename via MATLAB's current folder/path, not a stored path. It just
works when you open a model from within its own `models/<name>/`
folder; from elsewhere you'll see "unable to find data dictionary" and
the model won't simulate unless you've run `setupPaths` (see Setup,
above).

## Running a sim

`scripts/runModel.m` rebuilds/links any out-of-date data dictionary in
`buildDataDictionaries.m`'s `CONFIG` (so parameter edits are always
picked up), simulates the model, and saves `out` to
`results/simResults.mat`, overwriting any previous run. It's a script,
not a function -- it leaves `out` in the workspace:

```matlab
scripts/runModel.m       % defaults to modelName = 'plant'
```

To simulate a different model or force a dictionary rebuild, set the
relevant variable in the workspace first:

```matlab
modelName = 'plant';
forceRebuild = true;
scripts/runModel.m
```

## Plotting workflow

`scripts/plotRocketTrajectory.m` is a function with three call forms:

```matlab
plotRocketTrajectory()                     % plot `out` from the workspace
plotRocketTrajectory('results/simResults.mat')          % plot one saved run
plotRocketTrajectory('runA.mat', 'runB.mat')             % overlay two saved runs
```

Each `.mat` file must contain an `out` variable (e.g. `results/simResults.mat`,
as saved by `runModel.m`). It expects `out.simout` as nested bus structs
(`eom_bus`, `aeroParams_bus`) and opens two fixed-number figures so
re-running overwrites them instead of piling up new windows:

- **Figure 101 (States):** position, velocity, tilt & roll, angle of
  attack, body angular rates, raw quaternion
- **Figure 102 (Trajectory):** 3D flight path with nose/velocity triads

When overlaying two runs, each is colored separately and every legend
entry is tagged with the run's label (its filename, or `workspace`).

Optional name-value overrides, after any file arguments:
`'numFrames'`, `'bodyScale'`, `'forwardAxis'`, e.g.
`plotRocketTrajectory('numFrames', 30)`.
