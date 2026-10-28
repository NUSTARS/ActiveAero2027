/* Auto-extracted from autocodePlant/ert_main.c. Never compile ert_main.c into CubeIDE. */
#include <stddef.h>
#include "autocodePlant_initialize.h"

static RT_MODEL_autocodePlant_T autocodePlant_M_;
static RT_MODEL_autocodePlant_T *const autocodePlant_MPtr = &autocodePlant_M_;/* Real-time model */
static B_autocodePlant_T autocodePlant_B;/* Observable signals */
static DW_autocodePlant_T autocodePlant_DW;/* Observable states */
static X_autocodePlant_T autocodePlant_X;/* Observable continuous states */
static XDis_autocodePlant_T autocodePlant_XDis;/* Continuous states Disabled */

/* '<Root>/control_deg' */
static real_T autocodePlant_U_control_deg[4];

/* '<Root>/sensor_bus' */
static sensor_bus autocodePlant_Y_sensor_bus_i;

/* '<Root>/plant_bus' */
static plant_bus autocodePlant_Y_plant_bus_e;

void rt_OneStep_autocodePlant(RT_MODEL_autocodePlant_T *const autocodePlant_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(autocodePlant_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  autocodePlant_step(autocodePlant_M, autocodePlant_U_control_deg,
                     &autocodePlant_Y_sensor_bus_i, &autocodePlant_Y_plant_bus_e);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

void autocodePlant_setup(void)
{
    RT_MODEL_autocodePlant_T *const autocodePlant_M = autocodePlant_MPtr;
    autocodePlant_M->blockIO = &autocodePlant_B;
    autocodePlant_M->dwork = &autocodePlant_DW;
    autocodePlant_M->contStates = &autocodePlant_X;
    autocodePlant_M->contStateDisabled = &autocodePlant_XDis;
    autocodePlant_initialize(autocodePlant_M, autocodePlant_U_control_deg,
    &autocodePlant_Y_sensor_bus_i, &autocodePlant_Y_plant_bus_e);
}

void autocodePlant_oneStep(void)
{
    rt_OneStep_autocodePlant(autocodePlant_MPtr);
}

void autocodePlant_shutdown(void)
{
    RT_MODEL_autocodePlant_T *const autocodePlant_M = autocodePlant_MPtr;
    autocodePlant_terminate(autocodePlant_M);
}

RT_MODEL_autocodePlant_T *autocodePlant_getModel(void)
{
    return autocodePlant_MPtr;
}
