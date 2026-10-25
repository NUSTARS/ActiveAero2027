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

`scripts/plotRocketTrajectory.m` is a script -- edit the CONFIG block at
its top, then run it:

```matlab
matFiles = {};                                  % plot `out` from the workspace
matFiles = {'results/simResults.mat'};          % plot one saved run
matFiles = {'runA.mat', 'runB.mat'};            % overlay two saved runs
```

Each `.mat` file must contain an `out` variable (e.g. `results/simResults.mat`,
as saved by `runModel.m`). It expects `out.simout` as nested bus structs
(`eom_bus`, `aero_bus.body_bus`) and opens two fixed-number figures so
re-running overwrites them instead of piling up new windows:

- **Figure 101 (States):** position, velocity, tilt & roll, angle of
  attack, body angular rates, raw quaternion -- each vector component
  in its own subplot, grouped into the same 2x3 layout the combined
  plots used to occupy
- **Figure 102 (Trajectory):** 3D flight path with nose/velocity triads

When overlaying two runs, each is colored separately and every legend
entry is tagged with the run's label (its filename, or `workspace`).

Other CONFIG variables: `numFrames`, `bodyScale`, `forwardAxis`.


## Model code generation

After `setupPaths`, run `scripts/buildModels.m` to rebuild `autocodePlant` and
`autocodeModel` on every run. The script post-processes shared generated
constants, exports STM32-ready files to each model's `toIDE/` folder, and
generates reusable harnesses.

## STM32 sensor input bus

`buildModels.m` generates `autocodeModel_initializeSensorBus` for the
`sensor_bus` input. The wrapper uses `Vector3f_t` from the STM32 project's
`main.h`; keep that header's directory on the CubeIDE include path. Call
`autocodeModel_setup` once with long-lived bus storage, then populate the
bus and step the model at its 10 ms base rate:

```c
#include "autocodeModel_initialize.h"

static sensor_bus sensorInput;
static FlightData_t polledSensors;

void initializeModel(void)
{
    autocodeModel_setup(&sensorInput);
}

void modelTick(void)
{
    /* Poll sensors; accel must be m/s^2, gyro deg/s, and pressure Pa. */
    autocodeModel_initializeSensorBus(&sensorInput,
        &polledSensors.bmi_accel, &polledSensors.bmi_gyro,
        NULL, polledSensors.bmp581_pressure);
    autocodeModel_oneStep();
}
```

Pass either IMU's `Vector3f_t` fields and either barometer pressure field.
The wrapper copies accel x/y/z and pressure, and converts gyro x/y/z from
degrees per second to radians per second. `FlightData_t` has no magnetometer,
so pass `NULL` to zero those readings for now. On a later board, pass a pointer
to a magnetometer `Vector3f_t` instead.

## STM32CubeIDE `autocodeLib_CM7` setup

The generated `autocodeModel_initialize.h` includes both `autocodeModel.h` and
the application's `main.h`; that `main.h` includes `stm32h7xx_hal.h`. The
library compile therefore needs the application's `Core/Inc` directory plus
the HAL/CMSIS include paths and compiler symbols required by that HAL header.

1. **Project context:** import `autocodeLib_CM7` into the same CubeIDE workspace
   as the application. Add it to the application's **Project References**.
   Build the library for the same CM7 target, configuration, and floating-point
   ABI as the application.
2. **Library compiler settings:** in `autocodeLib_CM7` > **Properties >
   C/C++ Build > Settings > MCU GCC Compiler**, add
   `${workspace_loc:/{Project}/Core/Inc}` to Include paths. Replace
   `{Project}` with the consumer CubeIDE project name so the library can find
   its `main.h`. Keep `../Inc` and copy the consumer's HAL/CMSIS include
   directories into the library settings (resolve the paths relative to the
   library project):
   - `STM32H7xx_HAL_Driver/Inc`
   - `STM32H7xx_HAL_Driver/Inc/Legacy`
   - `CMSIS/Device/ST/STM32H7xx/Include`
   - `CMSIS/Include`

   Also copy the consumer application's C compiler **Defined symbols (-D)**.
   A CM7 STM32H755 build typically needs `CORE_CM7`, `USE_HAL_DRIVER`,
   `STM32H755xx`, and `USE_PWR_DIRECT_SMPS_SUPPLY`; retain matching Debug and
   board-specific definitions.
3. **Application compiler include paths:** retain the application's own
   `Core/Inc` and add
   `${workspace_loc:/autocodeLib/CM7/Inc}` for the generated headers.
4. **Application linker:** under
   `Properties > C/C++ Build > Settings > MCU GCC Linker > Libraries`, add
   library search path `${workspace_loc:/autocodeLib/CM7/Debug}` and library
   `autocodeLib_CM7` (without the `lib` prefix or `.a` suffix). For Release,
   build the library's Release configuration and point to its Release output
   directory.

When updating the library, copy the generated `Inc/` and `Src/` files from
`build_autocodeModel/toIDE/` into the library project and rebuild it. Link the
archive or compile those model sources directly, never both; do not compile
`ert_main.c` into the application.
