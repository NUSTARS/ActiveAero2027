/* Edit parameter initializers here for STM32 builds.
 * Included only by controllerParams_calibration.c. Regenerated from the dictionary on MATLAB build.
 * Sample times, delay lengths, dimensions and inlined expressions remain
 * compiled into the model. See the MATLAB tunability warnings. */
#ifndef CONTROLLERPARAMS_CALIBRATION_VALUES_H
#define CONTROLLERPARAMS_CALIBRATION_VALUES_H

/* MATLAB assignments from defineControllerDD.m:
C.guidanceParams.phiCmd_rad   = 0; % [rad] commanded roll angle
C.guidanceParams.thetaCmd_rad = 0.0; % [rad] commanded pitch angle
C.guidanceParams.psiCmd_rad   = 0.0; % [rad] commanded yaw angle
C.innerLoopParams.upRateLimitPitchYaw_dps = 180;  % [deg/s] max fin deflection rate
C.innerLoopParams.loRateLimitPitchYaw_dps = -180; % [deg/s] min fin deflection rate
C.innerLoopParams.upLimitPitchYaw_deg     = 45;   % [deg] max fin deflection angle
C.innerLoopParams.loLimitPitchYaw_deg     = -45;  % [deg] min fin deflection angle
C.innerLoopParams.upRateLimitRoll_dps = 90;  % [deg/s] max fin deflection rate
C.innerLoopParams.loRateLimitRoll_dps = -90; % [deg/s] min fin deflection rate
C.innerLoopParams.upLimitRoll_deg     = 5;   % [deg] max fin deflection angle
C.innerLoopParams.loLimitRoll_deg     = -5;  % [deg] min fin deflection angle
C.innerLoopParams.fbkGainBreakpoints_Pa = [0 30e3 75e3];
C.innerLoopParams.fbkGainPitchYawP_na = 200*[1.5 1.25 1.0];
C.innerLoopParams.fbkGainPitchYawI_na = 4000*[0.5 0.75 1.0];
C.innerLoopParams.fbkGainPitchYawD_na = 0*[1.5 1.25 1.0];
C.innerLoopParams.fbkGainPitchYawN_na = [1 1 1];
C.innerLoopParams.fbkGainRollP_na = 2.5*[1.1 1.05 1.0];
C.innerLoopParams.fbkGainRollI_na = 10*[2.0 1.2 1.0];
C.innerLoopParams.fbkGainRollD_na = [0 0 0];
C.innerLoopParams.fbkGainRollN_na = [1 1 1];
C.outerLoopParams.upRateLimitPitchYawRate_rps2 = 0.5;    % [rad/s^2] max pitch/yaw rate-command slew rate
C.outerLoopParams.loRateLimitPitchYawRate_rps2 = -0.5;   % [rad/s^2] min pitch/yaw rate-command slew rate
C.outerLoopParams.upLimitPitchYawRate_rps      = 0.4;    % [rad/s] max commanded pitch/yaw rate
C.outerLoopParams.loLimitPitchYawRate_rps      = -0.4;   % [rad/s] min commanded pitch/yaw rate
C.outerLoopParams.pitchYawGains                = [2, 1, 0, 1]; % [P, I, D, N] pitch/yaw outer-loop PID gains
C.outerLoopParams.upRateLimitRollRate_rps2 = 5;    % [rad/s^2] max roll rate-command slew rate
C.outerLoopParams.loRateLimitRollRate_rps2 = -5;   % [rad/s^2] min roll rate-command slew rate
C.outerLoopParams.upLimitRollRate_rps      = 2;    % [rad/s] max commanded roll rate
C.outerLoopParams.loLimitRollRate_rps      = -2;   % [rad/s] min commanded roll rate
C.outerLoopParams.rollGains                = [1, 2, 0, 100]; % [P, I, D, N] roll outer-loop PID gains
 */
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
 * C/C++ source code generated on : Tue Nov 10 19:24:45 2026
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
  0.0,
  0.0,
  0.0
} ;

cal_controllerParams_innerLoopParams innerLoopParams = {
  180.0,
  -180.0,
  45.0,
  -45.0,
  90.0,
  -90.0,
  5.0,
  -5.0,

  { 0.0, 30000.0, 75000.0 },

  { 300.0, 250.0, 200.0 },

  { 2000.0, 3000.0, 4000.0 },

  { 0.0, 0.0, 0.0 },

  { 1.0, 1.0, 1.0 },

  { 2.75, 2.625, 2.5 },

  { 20.0, 12.0, 10.0 },

  { 0.0, 0.0, 0.0 },

  { 1.0, 1.0, 1.0 }
} ;

cal_controllerParams_outerLoopParams outerLoopParams = {
  0.5,
  -0.5,
  0.4,
  -0.4,

  { 2.0, 1.0, 0.0, 1.0 },
  5.0,
  -5.0,
  2.0,
  -2.0,

  { 1.0, 2.0, 0.0, 100.0 }
} ;

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
