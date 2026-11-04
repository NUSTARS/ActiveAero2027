#ifndef AUTOCODEPLANT_FEEDBACK_H
#define AUTOCODEPLANT_FEEDBACK_H
#include "autocodePlant.h"
/* Called once per major step, after outputs and before state updates.
 * Return false to sample the final endpoint without advancing states. */
typedef boolean_T (*autocodePlant_FeedbackCallback)(sensor_bus *, plant_bus *, real_T [4]);
void autocodePlant_SetFeedbackCallback(autocodePlant_FeedbackCallback callback);
#endif
