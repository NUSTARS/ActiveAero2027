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

Because `autocodeModel_initialize.h` includes `main.h`, add the consumer application's `Core/Inc` directory to the library compiler include paths (`autocodeLib_CM7` > `Properties > C/C++ Build > Settings > MCU GCC Compiler > Include paths`): `${workspace_loc:/{Project}/Core/Inc}`. Replace `{Project}` with the consumer CubeIDE project name. In the application compiler include paths, include both its own `Core/Inc` and `${workspace_loc:/autocodeLib/CM7/Inc}` for the generated API headers.

In the application's `Properties > C/C++ Build > Settings > MCU GCC Linker > Libraries`, set the Debug library search path to `${workspace_loc:/autocodeLib/CM7/Debug}` and add library `autocodeLib_CM7` (omit the `lib` prefix and `.a` suffix). For Release, build the library's Release configuration and use its matching `Release` output directory. Link the archive or compile the generated model sources directly, but do not do both.
