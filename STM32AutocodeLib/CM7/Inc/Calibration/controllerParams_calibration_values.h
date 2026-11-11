/* Edit the parameter macros here for STM32 builds.
 * Included only by controllerParams_calibration.c. Regenerated from the dictionary on MATLAB build.
 * Sample times, delay lengths, dimensions and inlined expressions remain
 * compiled into the model. See the MATLAB tunability warnings. */
#ifndef CONTROLLERPARAMS_CALIBRATION_VALUES_H
#define CONTROLLERPARAMS_CALIBRATION_VALUES_H

#define CAL_GUIDANCEPARAMS_PHICMD_RAD /* MATLAB: C.guidanceParams.phiCmd_rad   = 0; % [rad] commanded roll angle */ 0.0
#define CAL_GUIDANCEPARAMS_THETACMD_RAD /* MATLAB: C.guidanceParams.thetaCmd_rad = 0.0; % [rad] commanded pitch angle */ 0.0
#define CAL_GUIDANCEPARAMS_PSICMD_RAD /* MATLAB: C.guidanceParams.psiCmd_rad   = 0.0; % [rad] commanded yaw angle */ 0.0
#define CAL_INNERLOOPPARAMS_UPRATELIMITPITCHYAW_DPS /* MATLAB: C.innerLoopParams.upRateLimitPitchYaw_dps = 180;  % [deg/s] max fin deflection rate */ 180.0
#define CAL_INNERLOOPPARAMS_LORATELIMITPITCHYAW_DPS /* MATLAB: C.innerLoopParams.loRateLimitPitchYaw_dps = -180; % [deg/s] min fin deflection rate */ -180.0
#define CAL_INNERLOOPPARAMS_UPLIMITPITCHYAW_DEG /* MATLAB: C.innerLoopParams.upLimitPitchYaw_deg     = 45;   % [deg] max fin deflection angle */ 45.0
#define CAL_INNERLOOPPARAMS_LOLIMITPITCHYAW_DEG /* MATLAB: C.innerLoopParams.loLimitPitchYaw_deg     = -45;  % [deg] min fin deflection angle */ -45.0
#define CAL_INNERLOOPPARAMS_UPRATELIMITROLL_DPS /* MATLAB: C.innerLoopParams.upRateLimitRoll_dps = 90;  % [deg/s] max fin deflection rate */ 90.0
#define CAL_INNERLOOPPARAMS_LORATELIMITROLL_DPS /* MATLAB: C.innerLoopParams.loRateLimitRoll_dps = -90; % [deg/s] min fin deflection rate */ -90.0
#define CAL_INNERLOOPPARAMS_UPLIMITROLL_DEG /* MATLAB: C.innerLoopParams.upLimitRoll_deg     = 5;   % [deg] max fin deflection angle */ 5.0
#define CAL_INNERLOOPPARAMS_LOLIMITROLL_DEG /* MATLAB: C.innerLoopParams.loLimitRoll_deg     = -5;  % [deg] min fin deflection angle */ -5.0
#define CAL_INNERLOOPPARAMS_FBKGAINBREAKPOINTS_PA /* MATLAB: C.innerLoopParams.fbkGainBreakpoints_Pa = [0 30e3 75e3]; */ { 0.0, 30000.0, 75000.0 }
#define CAL_INNERLOOPPARAMS_FBKGAINPITCHYAWP_NA /* MATLAB: C.innerLoopParams.fbkGainPitchYawP_na = 200*[1.5 1.25 1.0]; */ { 300.0, 250.0, 200.0 }
#define CAL_INNERLOOPPARAMS_FBKGAINPITCHYAWI_NA /* MATLAB: C.innerLoopParams.fbkGainPitchYawI_na = 4000*[0.5 0.75 1.0]; */ { 2000.0, 3000.0, 4000.0 }
#define CAL_INNERLOOPPARAMS_FBKGAINPITCHYAWD_NA /* MATLAB: C.innerLoopParams.fbkGainPitchYawD_na = 0*[1.5 1.25 1.0]; */ { 0.0, 0.0, 0.0 }
#define CAL_INNERLOOPPARAMS_FBKGAINPITCHYAWN_NA /* MATLAB: C.innerLoopParams.fbkGainPitchYawN_na = [1 1 1]; */ { 1.0, 1.0, 1.0 }
#define CAL_INNERLOOPPARAMS_FBKGAINROLLP_NA /* MATLAB: C.innerLoopParams.fbkGainRollP_na = 2.5*[1.1 1.05 1.0]; */ { 2.75, 2.625, 2.5 }
#define CAL_INNERLOOPPARAMS_FBKGAINROLLI_NA /* MATLAB: C.innerLoopParams.fbkGainRollI_na = 10*[2.0 1.2 1.0]; */ { 20.0, 12.0, 10.0 }
#define CAL_INNERLOOPPARAMS_FBKGAINROLLD_NA /* MATLAB: C.innerLoopParams.fbkGainRollD_na = [0 0 0]; */ { 0.0, 0.0, 0.0 }
#define CAL_INNERLOOPPARAMS_FBKGAINROLLN_NA /* MATLAB: C.innerLoopParams.fbkGainRollN_na = [1 1 1]; */ { 1.0, 1.0, 1.0 }
#define CAL_OUTERLOOPPARAMS_UPRATELIMITPITCHYAWRATE_RPS2 /* MATLAB: C.outerLoopParams.upRateLimitPitchYawRate_rps2 = 0.5;    % [rad/s^2] max pitch/yaw rate-command slew rate */ 0.5
#define CAL_OUTERLOOPPARAMS_LORATELIMITPITCHYAWRATE_RPS2 /* MATLAB: C.outerLoopParams.loRateLimitPitchYawRate_rps2 = -0.5;   % [rad/s^2] min pitch/yaw rate-command slew rate */ -0.5
#define CAL_OUTERLOOPPARAMS_UPLIMITPITCHYAWRATE_RPS /* MATLAB: C.outerLoopParams.upLimitPitchYawRate_rps      = 0.4;    % [rad/s] max commanded pitch/yaw rate */ 0.4
#define CAL_OUTERLOOPPARAMS_LOLIMITPITCHYAWRATE_RPS /* MATLAB: C.outerLoopParams.loLimitPitchYawRate_rps      = -0.4;   % [rad/s] min commanded pitch/yaw rate */ -0.4
#define CAL_OUTERLOOPPARAMS_PITCHYAWGAINS /* MATLAB: C.outerLoopParams.pitchYawGains                = [2, 1, 0, 1]; % [P, I, D, N] pitch/yaw outer-loop PID gains */ { 2.0, 1.0, 0.0, 1.0 }
#define CAL_OUTERLOOPPARAMS_UPRATELIMITROLLRATE_RPS2 /* MATLAB: C.outerLoopParams.upRateLimitRollRate_rps2 = 5;    % [rad/s^2] max roll rate-command slew rate */ 5.0
#define CAL_OUTERLOOPPARAMS_LORATELIMITROLLRATE_RPS2 /* MATLAB: C.outerLoopParams.loRateLimitRollRate_rps2 = -5;   % [rad/s^2] min roll rate-command slew rate */ -5.0
#define CAL_OUTERLOOPPARAMS_UPLIMITROLLRATE_RPS /* MATLAB: C.outerLoopParams.upLimitRollRate_rps      = 2;    % [rad/s] max commanded roll rate */ 2.0
#define CAL_OUTERLOOPPARAMS_LOLIMITROLLRATE_RPS /* MATLAB: C.outerLoopParams.loLimitRollRate_rps      = -2;   % [rad/s] min commanded roll rate */ -2.0
#define CAL_OUTERLOOPPARAMS_ROLLGAINS /* MATLAB: C.outerLoopParams.rollGains                = [1, 2, 0, 100]; % [P, I, D, N] roll outer-loop PID gains */ { 1.0, 2.0, 0.0, 100.0 }

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: controllerParams_calibration.c
 *
 * Code generated for Simulink model 'autocodeModel'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Tue Nov 10 19:37:59 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M7 (MPS2)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "controllerParams_calibration.h"
#include "controllerParams_calibration_types.h"

/* Exported data definition */

/* Definition for custom storage class: ExportToFile */
cal_controllerParams_guidanceParams guidanceParams = {
  CAL_GUIDANCEPARAMS_PHICMD_RAD,
  CAL_GUIDANCEPARAMS_THETACMD_RAD,
  CAL_GUIDANCEPARAMS_PSICMD_RAD
} ;

cal_controllerParams_innerLoopParams innerLoopParams = {
  CAL_INNERLOOPPARAMS_UPRATELIMITPITCHYAW_DPS,
  CAL_INNERLOOPPARAMS_LORATELIMITPITCHYAW_DPS,
  CAL_INNERLOOPPARAMS_UPLIMITPITCHYAW_DEG,
  CAL_INNERLOOPPARAMS_LOLIMITPITCHYAW_DEG,
  CAL_INNERLOOPPARAMS_UPRATELIMITROLL_DPS,
  CAL_INNERLOOPPARAMS_LORATELIMITROLL_DPS,
  CAL_INNERLOOPPARAMS_UPLIMITROLL_DEG,
  CAL_INNERLOOPPARAMS_LOLIMITROLL_DEG,

  CAL_INNERLOOPPARAMS_FBKGAINBREAKPOINTS_PA,

  CAL_INNERLOOPPARAMS_FBKGAINPITCHYAWP_NA,

  CAL_INNERLOOPPARAMS_FBKGAINPITCHYAWI_NA,

  CAL_INNERLOOPPARAMS_FBKGAINPITCHYAWD_NA,

  CAL_INNERLOOPPARAMS_FBKGAINPITCHYAWN_NA,

  CAL_INNERLOOPPARAMS_FBKGAINROLLP_NA,

  CAL_INNERLOOPPARAMS_FBKGAINROLLI_NA,

  CAL_INNERLOOPPARAMS_FBKGAINROLLD_NA,

  CAL_INNERLOOPPARAMS_FBKGAINROLLN_NA
} ;

cal_controllerParams_outerLoopParams outerLoopParams = {
  CAL_OUTERLOOPPARAMS_UPRATELIMITPITCHYAWRATE_RPS2,
  CAL_OUTERLOOPPARAMS_LORATELIMITPITCHYAWRATE_RPS2,
  CAL_OUTERLOOPPARAMS_UPLIMITPITCHYAWRATE_RPS,
  CAL_OUTERLOOPPARAMS_LOLIMITPITCHYAWRATE_RPS,

  CAL_OUTERLOOPPARAMS_PITCHYAWGAINS,
  CAL_OUTERLOOPPARAMS_UPRATELIMITROLLRATE_RPS2,
  CAL_OUTERLOOPPARAMS_LORATELIMITROLLRATE_RPS2,
  CAL_OUTERLOOPPARAMS_UPLIMITROLLRATE_RPS,
  CAL_OUTERLOOPPARAMS_LOLIMITROLLRATE_RPS,

  CAL_OUTERLOOPPARAMS_ROLLGAINS
} ;

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
