# STM32 integration: autocodeModel

Compile the generated C sources under `Src/` and include headers from `Inc/`. Do not compile `ert_main.c`.

Call `autocodeModel_setup` once during startup, then call `autocodeModel_oneStep` once per generated base-rate interval from the STM32 timer/task. Do not step concurrently or re-entrantly.

```c
#include "autocodeModel_initialize.h"
static sensor_bus input_sensor_bus_e;
/* Include the STM32 directory containing main.h in the include path. */
static FlightData_t polledSensors;

void initializeModel(void)
{
    autocodeModel_setup(&input_sensor_bus_e);
}

void modelTick(void)
{
    /* Accel in m/s^2 and gyro in deg/s; helper converts gyro to rad/s. */
    autocodeModel_initializeSensorBus(&input_sensor_bus_e, &polledSensors.bmi_accel, &polledSensors.bmi_gyro, NULL, polledSensors.bmp581_pressure);
    autocodeModel_oneStep();
}
```

`initializeSensorBus` copies x/y/z from caller-selected `Vector3f_t` accel/gyro fields, converts gyro values from deg/s to rad/s, and copies pressure in Pa. Use BMI088 or LSM6DSO fields and BMP581 or BMP585 pressure as appropriate. `FlightData_t` has no magnetometer field, so pass `NULL` for now; later pass a pointer to a `Vector3f_t` magnetometer reading. A NULL magnetometer and unavailable `truth_bus` bias fields are zeroed.

## STM32CubeIDE project settings

Keep `autocodeLib_CM7` imported in the same workspace as the application, add it under the application project's `Project References`, and build the library for the same CM7 target, configuration, and floating-point ABI as the application.

Because `autocodeModel_initialize.h` includes `main.h`, and the application's `main.h` includes `stm32h7xx_hal.h`, the library C compiler needs the consumer application's `Core/Inc` directory. In `autocodeLib_CM7 > Properties > C/C++ Build > Settings > MCU GCC Compiler > Include paths`, add `${workspace_loc:/{Project}/Core/Inc}` and replace `{Project}` with the consumer CubeIDE project name. Keep `../Inc`; also copy the consumer's HAL/CMSIS include directories into the library compiler settings, resolving paths for the library project: `STM32H7xx_HAL_Driver/Inc`, `STM32H7xx_HAL_Driver/Inc/Legacy`, `CMSIS/Device/ST/STM32H7xx/Include`, and `CMSIS/Include`. Copy the application C compiler's preprocessor symbols into the library configuration too. A CM7 STM32H755 target typically needs `CORE_CM7`, `USE_HAL_DRIVER`, `STM32H755xx`, and `USE_PWR_DIRECT_SMPS_SUPPLY`; retain the matching Debug/Release and board-specific definitions for the selected target.

In the application compiler include paths, include its own `Core/Inc` and `${workspace_loc:/autocodeLib/CM7/Inc}` for the generated API headers.

In the application's `Properties > C/C++ Build > Settings > MCU GCC Linker > Libraries`, set the Debug library search path to `${workspace_loc:/autocodeLib/CM7/Debug}` and add library `autocodeLib_CM7` (omit the `lib` prefix and `.a` suffix). For Release, build the library's Release configuration and use its matching `Release` output directory. Link the archive or compile the generated model sources directly, but do not do both.
