/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: navParams_calibration_types.h
 *
 * Code generated for Simulink model 'autocodeModel'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Tue Nov 10 19:37:59 2026
 */

#ifndef navParams_calibration_types_h_
#define navParams_calibration_types_h_
#include "rtwtypes.h"

typedef struct {
  real_T qEst_na[4];
} cal_navParams_navControl_navIC_bus;

typedef struct {
  real_T M0_m;
  real_T N0_m;
} cal_navParams_gpsConversion;

typedef struct {
  real_T attitudeGain;
  real_T velGain;
  real_T posGain;
} cal_navParams_navComp;

typedef struct {
  boolean_T useNav_b;
  boolean_T useKalman_b;
  real_T dt_s;
  real_T roll0_rad;
  cal_navParams_navControl_navIC_bus navIC_bus;
  real_T posNed0_m[3];
  real_T velNed0_mps[3];
  real_T eulerCalcPreRotation[4];
  real_T eulerCalcPreRotationInv[4];
  real_T gravityNed_mps2[3];
  real_T rhoConst_kgpm3;
  real_T gyroG[9];
  real_T filterDelay_na;
  real_T biasWindowSamples;
} cal_navParams_navControl;

typedef struct {
  real_T debounce_s;
  real_T boostThreshold_mps2;
  real_T coastThresholdxAcc_mps2;
  real_T coastThresholdAlt_m;
  real_T controlTresholdPitchYaw_rad;
  real_T controlTresholdPitchYawRate_rps;
} cal_navParams_navStates;

#endif                                 /* navParams_calibration_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
