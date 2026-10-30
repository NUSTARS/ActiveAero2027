/* Auto-extracted from autocodeModel. Do not edit; regenerate via buildModels.m. */
#ifndef AUTOCODEMODEL_INITIALIZE_H
#define AUTOCODEMODEL_INITIALIZE_H

#include "autocodeModel.h"
#include <stddef.h>
#include "userdefTypes.h"

/* Pass caller-owned bus inputs; setup initializes the model before binding them. Keep them valid while stepping. */
void autocodeModel_setup(sensor_bus *input_sensor_bus_e);
/* Copy accel in m/s^2 and gyro in deg/s (converted to rad/s); pass NULL mag. */
void autocodeModel_initializeSensorBus(sensor_bus *bus, const Vector3f_t *accel, const Vector3f_t *gyro, const Vector3f_t *mag, real_T baroMeas_Pa);
void rt_OneStep_autocodeModel(RT_MODEL *const rtM);
void autocodeModel_oneStep(void);
RT_MODEL *autocodeModel_getModel(void);

#endif /* AUTOCODEMODEL_INITIALIZE_H */
