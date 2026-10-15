# STM32 integration: autocodePlant

Compile the generated C sources under `Src/` and include headers from `Inc/`. Do not compile `ert_main.c`.

Call `autocodePlant_setup` once during startup, then call `autocodePlant_oneStep` once per generated base-rate interval from the STM32 timer/task. Do not step concurrently or re-entrantly.

```c
#include "autocodePlant_initialize.h"

void initializeModel(void)
{
    autocodePlant_setup();
}

void modelTick(void)
{
    autocodePlant_oneStep();
}
```

This model has no caller-owned bus inputs. Its bus outputs use model-owned storage.

## Shared generated dependencies

`autocodePlant` is secondary in `buildModels.m`; its `toIDE/` export omits shared headers and sources. In STM32CubeIDE, also add `build_autocodeModel/toIDE/Inc` to the include paths and compile the primary utility sources from `build_autocodeModel/toIDE/Src` exactly once: `rtGetInf.c`, `rtGetNaN.c`, `rt_atan2d_snf.c`, and `rt_nonfinite.c`. If these sources are already in the project, do not add duplicate entries.
