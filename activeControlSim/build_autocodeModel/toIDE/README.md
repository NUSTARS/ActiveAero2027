# STM32 integration: autocodeModel

Compile the generated C sources under `Src/` and include headers from `Inc/`. Do not compile `ert_main.c`.

Call `autocodeModel_setup` once during startup, then call `autocodeModel_oneStep` once per generated base-rate interval from the STM32 timer/task. Do not step concurrently or re-entrantly.

```c
#include "autocodeModel_initialize.h"
static sensor_bus input_sensor_bus_e;
static Vector3f_t polledAccel;
static Vector3f_t polledGyro;
static real_T polledPressure_Pa;

void initializeModel(void)
{
    autocodeModel_setup(&input_sensor_bus_e);
}

void modelTick(void)
{
    /* Populate accel/gyro in source units and pressure in Pa. */
    autocodeModel_initializeSensorBus(&input_sensor_bus_e, &polledAccel, &polledGyro, NULL, polledPressure_Pa);
    autocodeModel_oneStep();
}
```

`initializeSensorBus` copies x/y/z from caller-selected `Vector3f_t` accel/gyro fields, converts gyro from deg/s to rad/s, and copies pressure in Pa. Populate those values from BMI088/LSM6DSO and BMP581/BMP585 as appropriate. Pass `NULL` when no magnetometer is available; later pass a `Vector3f_t` magnetometer pointer if available. The helper zeros the magnetometer and unavailable `truth_bus` bias fields.

## STM32CubeIDE project settings

Keep `autocodeLib_CM7` imported in the same workspace as the application, add it under the application project's `Project References`, and build the library for the same CM7 target, configuration, and floating-point ABI as the application.

The generated wrapper uses `userdefTypes.h` from `CM7/Inc`; it does not depend on application-owned type headers. In `autocodeLib_CM7 > Properties > C/C++ Build > Settings > MCU GCC Compiler > Include paths`, keep `../Inc` and include the HAL/CMSIS directories required by the selected CM7 target, resolving paths relative to the library project: `STM32H7xx_HAL_Driver/Inc`, `STM32H7xx_HAL_Driver/Inc/Legacy`, `CMSIS/Device/ST/STM32H7xx/Include`, and `CMSIS/Include`. Copy the application C compiler's preprocessor symbols into the library configuration too. A CM7 STM32H755 target typically needs `CORE_CM7`, `USE_HAL_DRIVER`, `STM32H755xx`, and `USE_PWR_DIRECT_SMPS_SUPPLY`; retain the matching Debug/Release and board-specific definitions for the selected target.

In the application compiler include paths, include its own `Core/Inc` and `${workspace_loc:/autocodeLib/CM7/Inc}` for the generated API headers.

In the application's `Properties > C/C++ Build > Settings > MCU GCC Linker > Libraries`, set the Debug library search path to `${workspace_loc:/autocodeLib/CM7/Debug}` and add library `autocodeLib_CM7` (omit the `lib` prefix and `.a` suffix). For Release, build the library's Release configuration and use its matching `Release` output directory. Link the archive or compile the generated model sources directly, but do not do both.
