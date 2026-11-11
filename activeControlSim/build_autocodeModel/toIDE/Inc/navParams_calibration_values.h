/* Edit the parameter macros here for STM32 builds.
 * Included only by navParams_calibration.c. Regenerated from the dictionary on MATLAB build.
 * Sample times, delay lengths, dimensions and inlined expressions remain
 * compiled into the model. See the MATLAB tunability warnings. */
#ifndef NAVPARAMS_CALIBRATION_VALUES_H
#define NAVPARAMS_CALIBRATION_VALUES_H

#define CAL_GPSCONVERSION_M0_M /* MATLAB: N.gpsConversion.M0_m = 6378137*(1-6.69437999014E-3)/(1-6.69437999014E-3*sin(lat0_deg)^2)^1.5; */ 6391803.4646718353
#define CAL_GPSCONVERSION_N0_M /* MATLAB: N.gpsConversion.N0_m = 6378137/(1-6.69437999014E-3*sind(lat0_deg)^2)^0.5; */ 6387738.3750610081
#define CAL_NAVCOMP_ATTITUDEGAIN /* MATLAB: N.navComp.attitudeGain = 0.995; */ 0.995
#define CAL_NAVCOMP_VELGAIN /* MATLAB: N.navComp.velGain = 0.4; */ 0.4
#define CAL_NAVCOMP_POSGAIN /* MATLAB: N.navComp.posGain = 0.4; */ 0.4
#define CAL_NAVCONTROL_USENAV_B /* MATLAB: N.navControl.useNav_b = true; */ true
#define CAL_NAVCONTROL_USEKALMAN_B /* MATLAB: N.navControl.useKalman_b = false; */ false
#define CAL_NAVCONTROL_DT_S /* MATLAB: N.navControl.dt_s = 1/100; */ 0.01
#define CAL_NAVCONTROL_ROLL0_RAD /* MATLAB: N.navControl.roll0_rad = 1.0; */ 1.0
#define CAL_NAVCONTROL_NAVIC_BUS_QEST_NA /* navControl.navIC_bus.qEst_na */ { 0.707106781187, 0.0, 0.707106781187, 0.0 }
#define CAL_NAVCONTROL_POSNED0_M /* MATLAB: N.navControl.posNed0_m = [0 0 0]; */ { 0.0, 0.0, 0.0 }
#define CAL_NAVCONTROL_VELNED0_MPS /* MATLAB: N.navControl.velNed0_mps = [0 0 0]; */ { 0.0, 0.0, 0.0 }
#define CAL_NAVCONTROL_EULERCALCPREROTATION /* MATLAB: N.navControl.eulerCalcPreRotation = [0.707106781187, 0, -0.707106781187, 0]; */ { 0.707106781187, 0.0, -0.707106781187, 0.0 }
#define CAL_NAVCONTROL_EULERCALCPREROTATIONINV /* MATLAB: N.navControl.eulerCalcPreRotationInv = quatinv(N.navControl.eulerCalcPreRotation); */ { 0.70710678118609493, -0.0, 0.70710678118609493, -0.0 }
#define CAL_NAVCONTROL_GRAVITYNED_MPS2 /* MATLAB: N.navControl.gravityNed_mps2 = [0, 0, 9.81]; */ { 0.0, 0.0, 9.81 }
#define CAL_NAVCONTROL_RHOCONST_KGPM3 /* MATLAB: N.navControl.rhoConst_kgpm3 = 1.225; */ 1.225
#define CAL_NAVCONTROL_GYROG /* MATLAB: N.navControl.gyroG = gyroG * 0.01745 / 9.8065; */ { 8.8971600469076642e-5, 0.0, 0.0, 0.0, 8.8971600469076642e-5, 0.0, 0.0, 0.0, \
    8.8971600469076642e-5 }
#define CAL_NAVCONTROL_FILTERDELAY_NA /* MATLAB: N.navControl.filterDelay_na = 500; */ 500.0
#define CAL_NAVCONTROL_BIASWINDOWSAMPLES /* MATLAB: N.navControl.biasWindowSamples = 1000; */ 1000.0
#define CAL_NAVSTATES_DEBOUNCE_S /* MATLAB: N.navStates.debounce_s = 0.1; */ 0.1
#define CAL_NAVSTATES_BOOSTTHRESHOLD_MPS2 /* MATLAB: N.navStates.boostThreshold_mps2 = 35; */ 35.0
#define CAL_NAVSTATES_COASTTHRESHOLDXACC_MPS2 /* MATLAB: N.navStates.coastThresholdxAcc_mps2 = 0; */ 0.0
#define CAL_NAVSTATES_COASTTHRESHOLDALT_M /* MATLAB: N.navStates.coastThresholdAlt_m = 200; */ 200.0
#define CAL_NAVSTATES_CONTROLTRESHOLDPITCHYAW_RAD /* MATLAB: N.navStates.controlTresholdPitchYaw_rad = 1.0; */ 1.0
#define CAL_NAVSTATES_CONTROLTRESHOLDPITCHYAWRATE_RPS /* MATLAB: N.navStates.controlTresholdPitchYawRate_rps = 1.0; */ 1.0

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
 * C/C++ source code generated on : Tue Nov 10 19:37:59 2026
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
  CAL_GPSCONVERSION_M0_M,
  CAL_GPSCONVERSION_N0_M
} ;

cal_navParams_navComp navComp = {
  CAL_NAVCOMP_ATTITUDEGAIN,
  CAL_NAVCOMP_VELGAIN,
  CAL_NAVCOMP_POSGAIN
} ;

cal_navParams_navControl navControl = {
  CAL_NAVCONTROL_USENAV_B,
  CAL_NAVCONTROL_USEKALMAN_B,
  CAL_NAVCONTROL_DT_S,
  CAL_NAVCONTROL_ROLL0_RAD,

  {
    CAL_NAVCONTROL_NAVIC_BUS_QEST_NA
  },

  CAL_NAVCONTROL_POSNED0_M,

  CAL_NAVCONTROL_VELNED0_MPS,

  CAL_NAVCONTROL_EULERCALCPREROTATION,

  CAL_NAVCONTROL_EULERCALCPREROTATIONINV,

  CAL_NAVCONTROL_GRAVITYNED_MPS2,
  CAL_NAVCONTROL_RHOCONST_KGPM3,

  CAL_NAVCONTROL_GYROG,
  CAL_NAVCONTROL_FILTERDELAY_NA,
  CAL_NAVCONTROL_BIASWINDOWSAMPLES
} ;

cal_navParams_navStates navStates = {
  CAL_NAVSTATES_DEBOUNCE_S,
  CAL_NAVSTATES_BOOSTTHRESHOLD_MPS2,
  CAL_NAVSTATES_COASTTHRESHOLDXACC_MPS2,
  CAL_NAVSTATES_COASTTHRESHOLDALT_M,
  CAL_NAVSTATES_CONTROLTRESHOLDPITCHYAW_RAD,
  CAL_NAVSTATES_CONTROLTRESHOLDPITCHYAWRATE_RPS
} ;

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
