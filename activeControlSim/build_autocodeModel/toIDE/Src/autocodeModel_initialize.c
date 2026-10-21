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
static sensor_bus *rtU_sensor_bus_e_inputPtr = &rtU_sensor_bus_e;

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
  autocodeModel_step(rtM, rtU_sensor_bus_e_inputPtr, &rtY_navigation_bus_d,
                     &rtY_controller_bus_f, rtY_control_deg);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

void autocodeModel_setup(sensor_bus *input_sensor_bus_e)
{
    RT_MODEL *const rtM = rtMPtr;
    rtM->dwork = &rtDW;
    autocodeModel_initialize(rtM, &rtU_sensor_bus_e, &rtY_navigation_bus_d,
    &rtY_controller_bus_f, rtY_control_deg);
    rtU_sensor_bus_e_inputPtr = input_sensor_bus_e;
}

void autocodeModel_initializeSensorBus(sensor_bus *bus, const Vector3f_t *accel, const Vector3f_t *gyro, const Vector3f_t *mag, real_T baroMeas_Pa)
{
    const real_T DEG_TO_RAD = 3.14159265358979323846 / 180.0;
    size_t i;

    for (i = 0U; i < 3U; ++i) {
        bus->truth_bus.gyroBiasTrue_rps[i] = 0.0;
        bus->truth_bus.accBiasTrue_mps2[i] = 0.0;
        bus->magBdyMeas_nT[i] = 0.0;
    }
    if (mag != NULL) {
        bus->magBdyMeas_nT[0] = mag->x;
        bus->magBdyMeas_nT[1] = mag->y;
        bus->magBdyMeas_nT[2] = mag->z;
    }
    bus->fBdyMeas_mps2[0] = accel->x;
    bus->fBdyMeas_mps2[1] = accel->y;
    bus->fBdyMeas_mps2[2] = accel->z;
    bus->wBdyMeas_rps[0] = gyro->x * DEG_TO_RAD;
    bus->wBdyMeas_rps[1] = gyro->y * DEG_TO_RAD;
    bus->wBdyMeas_rps[2] = gyro->z * DEG_TO_RAD;
    bus->baroMeas_Pa = baroMeas_Pa;
}

void autocodeModel_oneStep(void)
{
    rt_OneStep_autocodeModel(rtMPtr);
}

RT_MODEL *autocodeModel_getModel(void)
{
    return rtMPtr;
}
