/* Edit parameter initializers here for STM32 builds.
 * Included only by navParams_calibration.c. Regenerated from the dictionary on MATLAB build.
 * Sample times, delay lengths, dimensions and inlined expressions remain
 * compiled into the model. See the MATLAB tunability warnings. */
#ifndef NAVPARAMS_CALIBRATION_VALUES_H
#define NAVPARAMS_CALIBRATION_VALUES_H

/* MATLAB assignments from defineNavDD.m:
N.navControl.useNav_b = true;
N.navControl.useKalman_b = false;
N.navControl.dt_s = 1/100;
N.navControl.roll0_rad = 1.0;
N.navControl.navIC_bus = struct('qEst_na', [0.707106781187, 0, 0.707106781187, 0]);
N.navControl.posNed0_m = [0 0 0];
N.navControl.velNed0_mps = [0 0 0];
N.navControl.eulerCalcPreRotation = [0.707106781187, 0, -0.707106781187, 0];
N.navControl.eulerCalcPreRotationInv = quatinv(N.navControl.eulerCalcPreRotation);
N.navControl.gravityNed_mps2 = [0, 0, 9.81];
N.navControl.rhoConst_kgpm3 = 1.225; 
gyroG = [0.05 0 0; 0 0.05 0; 0 0 0.05];
N.navControl.gyroG = gyroG * 0.01745 / 9.8065;
N.navControl.filterDelay_na = 500;
N.navControl.biasWindowSamples = 1000;
lat0_deg = 42.0569355774686; % [deg]
N.gpsConversion.M0_m = 6378137*(1-6.69437999014E-3)/(1-6.69437999014E-3*sin(lat0_deg)^2)^1.5;
N.gpsConversion.N0_m = 6378137/(1-6.69437999014E-3*sind(lat0_deg)^2)^0.5;
N.navStates.debounce_s = 0.1;
N.navStates.boostThreshold_mps2 = 35;
N.navStates.coastThresholdxAcc_mps2 = 0; 
N.navStates.coastThresholdAlt_m = 200;
N.navStates.controlTresholdPitchYaw_rad = 1.0;
N.navStates.controlTresholdPitchYawRate_rps = 1.0;
N.navComp.attitudeGain = 0.995;
N.navComp.velGain = 0.4;
N.navComp.posGain = 0.4;
 */
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: navParams_calibration.c
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

#include "navParams_calibration.h"
#include "navParams_calibration_types.h"

/* Exported data definition */

/* Definition for custom storage class: ExportToFile */
cal_navParams_gpsConversion gpsConversion = {
  6391803.4646718353,
  6387738.3750610081
} ;

cal_navParams_navComp navComp = {
  0.995,
  0.4,
  0.4
} ;

cal_navParams_navControl navControl = {
  true,
  false,
  0.01,
  1.0,

  {
    { 0.707106781187, 0.0, 0.707106781187, 0.0 }
  },

  { 0.0, 0.0, 0.0 },

  { 0.0, 0.0, 0.0 },

  { 0.707106781187, 0.0, -0.707106781187, 0.0 },

  { 0.70710678118609493, -0.0, 0.70710678118609493, -0.0 },

  { 0.0, 0.0, 9.81 },
  1.225,

  { 8.8971600469076642e-5, 0.0, 0.0, 0.0, 8.8971600469076642e-5, 0.0, 0.0, 0.0,
    8.8971600469076642e-5 },
  500.0,
  1000.0
} ;

cal_navParams_navStates navStates = {
  0.1,
  35.0,
  0.0,
  200.0,
  1.0,
  1.0
} ;

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
