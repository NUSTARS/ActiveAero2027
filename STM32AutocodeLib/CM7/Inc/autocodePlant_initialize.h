/* Auto-extracted from autocodePlant. Do not edit; regenerate via buildModels.m. */
#ifndef AUTOCODEPLANT_INITIALIZE_H
#define AUTOCODEPLANT_INITIALIZE_H

#include "autocodePlant.h"

void autocodePlant_setup(void);
void rt_OneStep_autocodePlant(RT_MODEL_autocodePlant_T *const autocodePlant_M);
void autocodePlant_oneStep(void);
void autocodePlant_shutdown(void);
RT_MODEL_autocodePlant_T *autocodePlant_getModel(void);

#endif /* AUTOCODEPLANT_INITIALIZE_H */
