/* Auto-extracted from autocodeModel/ert_main.c. Never compile ert_main.c into CubeIDE. */
#include <stddef.h>
#include "autocodeModel_initialize.h"

static RT_MODEL rtM_;
static RT_MODEL *const rtMPtr = &rtM_; /* Real-time model */
static DW rtDW;                        /* Observable states */

/* '<Root>/sensor_bus' */
static sensor_bus rtU_sensor_bus_e;

/* '<Root>/navigation_bus' */
static navigation_bus rtY_navigation_bus_d;

/* '<Root>/controller_bus' */
static controller_bus rtY_controller_bus_f;

/* '<Root>/control_deg' */
static real_T rtY_control_deg[4];

void rt_OneStep_autocodeModel(RT_MODEL *const rtM)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  autocodeModel_step(rtM, &rtU_sensor_bus_e, &rtY_navigation_bus_d,
                     &rtY_controller_bus_f, rtY_control_deg);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

void autocodeModel_setup(void)
{
    RT_MODEL *const rtM = rtMPtr;
    rtM->dwork = &rtDW;
    autocodeModel_initialize(rtM, &rtU_sensor_bus_e, &rtY_navigation_bus_d,
    &rtY_controller_bus_f, rtY_control_deg);
}

void autocodeModel_oneStep(void)
{
    rt_OneStep_autocodeModel(rtMPtr);
}

RT_MODEL *autocodeModel_getModel(void)
{
    return rtMPtr;
}
