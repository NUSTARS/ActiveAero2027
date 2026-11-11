/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: controllerParams_calibration_types.h
 *
 * Code generated for Simulink model 'autocodeModel'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Tue Nov 10 19:37:59 2026
 */

#ifndef controllerParams_calibration_types_h_
#define controllerParams_calibration_types_h_
#include "rtwtypes.h"

typedef struct {
  real_T phiCmd_rad;
  real_T thetaCmd_rad;
  real_T psiCmd_rad;
} cal_controllerParams_guidanceParams;

typedef struct {
  real_T upRateLimitPitchYaw_dps;
  real_T loRateLimitPitchYaw_dps;
  real_T upLimitPitchYaw_deg;
  real_T loLimitPitchYaw_deg;
  real_T upRateLimitRoll_dps;
  real_T loRateLimitRoll_dps;
  real_T upLimitRoll_deg;
  real_T loLimitRoll_deg;
  real_T fbkGainBreakpoints_Pa[3];
  real_T fbkGainPitchYawP_na[3];
  real_T fbkGainPitchYawI_na[3];
  real_T fbkGainPitchYawD_na[3];
  real_T fbkGainPitchYawN_na[3];
  real_T fbkGainRollP_na[3];
  real_T fbkGainRollI_na[3];
  real_T fbkGainRollD_na[3];
  real_T fbkGainRollN_na[3];
} cal_controllerParams_innerLoopParams;

typedef struct {
  real_T upRateLimitPitchYawRate_rps2;
  real_T loRateLimitPitchYawRate_rps2;
  real_T upLimitPitchYawRate_rps;
  real_T loLimitPitchYawRate_rps;
  real_T pitchYawGains[4];
  real_T upRateLimitRollRate_rps2;
  real_T loRateLimitRollRate_rps2;
  real_T upLimitRollRate_rps;
  real_T loLimitRollRate_rps;
  real_T rollGains[4];
} cal_controllerParams_outerLoopParams;

#endif                               /* controllerParams_calibration_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
