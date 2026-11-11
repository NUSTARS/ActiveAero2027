/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: autocodeModel.c
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

#include "autocodeModel.h"
#include "rtwtypes.h"
#include <math.h>
#include "rt_atan2d_snf.h"
#include "rt_nonfinite.h"
#include "navParams_calibration_types.h"
#include "controllerParams_calibration_types.h"
#include <string.h>
#include "InitCalcAtmosCOESA.h"
#include "CalcPAltCOESA.h"
#include "LookUp_real_T_real_T.h"
#include "navParams_calibration.h"
#include "controllerParams_calibration.h"

/* Named constants for State Transition Table: '<S411>/State Transition Table' */
#define autocod_IN_PastLockoutThreshold ((uint8_T)6U)
#define autocodeM_IN_PastCoastThreshold ((uint8_T)5U)
#define autocodeMode_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define autocodeModel_IN_Active        ((uint8_T)1U)
#define autocodeModel_IN_Boost         ((uint8_T)2U)
#define autocodeModel_IN_Idle          ((uint8_T)3U)
#define autocodeModel_IN_Lockout       ((uint8_T)4U)

void InitCalcAtmosCOESA(real_T *temperature76, real_T *pressureRatio76);
void CalcPAltCOESA(const real_T *pressure, real_T *altitude, real_T
                   *temperature76, real_T *pressureRatio76, int_T numPoints);
const controller_bus autocodeModel_rtZcontroller_bus = { { { 0.0,/* rateCmd_rps */
      false,                           /* rateLimited_b */
      false                            /* saturated_b */
    },                                 /* pitchOuterLoop_bus */

    { 0.0,                             /* rateCmd_rps */
      false,                           /* rateLimited_b */
      false                            /* saturated_b */
    },                                 /* yawOuterLoop_bus */

    { 0.0,                             /* rateCmd_rps */
      false,                           /* rateLimited_b */
      false                            /* saturated_b */
    }                                  /* rollOuterLoop_bus */
  },                                   /* outerLoop_bus */

  { { 0.0,                             /* control_deg */
      0.0,                             /* controlMoment_Nm */
      false,                           /* rateLimted_b */
      false                            /* saturated_b */
    },                                 /* pitchInnerLoop_bus */

    { 0.0,                             /* control_deg */
      0.0,                             /* controlMoment_Nm */
      false,                           /* rateLimted_b */
      false                            /* saturated_b */
    },                                 /* yawInnerLoop_bus */

    { 0.0,                             /* control_deg */
      0.0,                             /* controlMoment_Nm */
      false,                           /* rateLimted_b */
      false                            /* saturated_b */
    }                                  /* rollInnerLoop_bus */
  },                                   /* innerLoop_bus */

  { 0.0, 0.0, 0.0, 0.0 }               /* control_deg */
};

const navigation_bus autocodeModel_rtZnavigation_bus = { IDLE,/* flightMode_enum */
  { 0.0, 0.0, 0.0, 0.0 },              /* qEst_na */
  0.0,                                 /* phiEst_rad */
  0.0,                                 /* thetaEst_rad */
  0.0,                                 /* psiEst_rad */
  0.0,                                 /* pEst_rps */
  0.0,                                 /* qEst_rps */
  0.0,                                 /* rEst_rps */
  0.0,                                 /* xAccEst_mps2 */
  0.0,                                 /* yAccEst_mps2 */
  0.0,                                 /* zAccEst_mps2 */

  { 0.0, 0.0, 0.0 },                   /* accelBias_mps2 */

  { 0.0, 0.0, 0.0 },                   /* gyroBias_rps */
  0.0,                                 /* altitudeBias_m */

  { 0.0, 0.0, 0.0 },                   /* llaBias_na */
  0.0,                                 /* dynPressureEst_Pa */
  0.0,                                 /* xVelEstNed_mps */
  0.0,                                 /* yVelEstNed_mps */
  0.0,                                 /* zVelEstNed_mps */
  0.0,                                 /* xPosEst_m */
  0.0,                                 /* yPosEst_m */
  0.0                                  /* zPosEst_m */
};

const sensor_bus autocodeModel_rtZsensor_bus = { { { 0.0, 0.0, 0.0 },/* gyroBiasTrue_rps */

    { 0.0, 0.0, 0.0 }                  /* accBiasTrue_mps2 */
  },                                   /* truth_bus */

  { 0.0, 0.0, 0.0 },                   /* fBdyMeas_mps2 */

  { 0.0, 0.0, 0.0 },                   /* wBdyMeas_rps */

  { 0.0, 0.0, 0.0 },                   /* magBdyMeas_nT */
  0.0,                                 /* baroMeas_Pa */

  { 0.0, 0.0, 0.0 },                   /* velNedMeas_mps */

  { 0.0, 0.0, 0.0 },                   /* gpsLLA_na */
  false                                /* gpsFix_b */
};

/* Model step function */
void autocodeModel_step(RT_MODEL *const rtM, sensor_bus *rtU_sensor_bus_e,
  navigation_bus *rtY_navigation_bus_d, controller_bus *rtY_controller_bus_f,
  real_T rtY_control_deg[4])
{
  DW *rtDW = rtM->dwork;
  real_T rtb_C[9];
  real_T rtb_C_l[9];
  real_T rtb_MathFunction_k[9];
  real_T rtb_QuaternionstoDirectionCos_i[9];
  real_T rtb_QuaternionstoDirectionCosin[9];
  real_T AccelFilter_tmp[3];
  real_T DiscreteTransferFcn1_tmp[3];
  real_T GyroFilter_tmp[3];
  real_T Switch1[3];
  real_T rtb_TmpSignalConversionAtSFunct[3];
  real_T rtb_accBdyEst_mps2[3];
  real_T rtb_accelBias_mps2[3];
  real_T rtb_gyroBias_rps[3];
  real_T rtb_gyroFilt_rps[3];
  real_T rtb_wBdyEst_rps[3];
  real_T Switch3_idx_0;
  real_T Switch3_idx_1;
  real_T Switch3_idx_2;
  real_T Switch_idx_2;
  real_T rtb_Cos;
  real_T rtb_Cos_e;
  real_T rtb_Cos_k;
  real_T rtb_Cos_l;
  real_T rtb_Cos_m;
  real_T rtb_DProdOut_m;
  real_T rtb_Divide;
  real_T rtb_Divide_l;
  real_T rtb_Filter_b;
  real_T rtb_Filter_c;
  real_T rtb_Filter_e;
  real_T rtb_Filter_g;
  real_T rtb_GainDynamicLookup_b;
  real_T rtb_GainDynamicLookup_k;
  real_T rtb_Gain_a;
  real_T rtb_Integrator_b;
  real_T rtb_Integrator_fe;
  real_T rtb_Integrator_g;
  real_T rtb_Integrator_i;
  real_T rtb_MathFunction_idx_0;
  real_T rtb_MathFunction_idx_1;
  real_T rtb_MathFunction_idx_2;
  real_T rtb_MatrixMultiply1_idx_0;
  real_T rtb_MatrixMultiply1_idx_1;
  real_T rtb_MatrixMultiply1_idx_2;
  real_T rtb_PProdOut_b;
  real_T rtb_Product1_ad;
  real_T rtb_Product1_e;
  real_T rtb_Product1_j;
  real_T rtb_Product1_j3;
  real_T rtb_Product1_o;
  real_T rtb_Product1_p1;
  real_T rtb_Product2_l;
  real_T rtb_Product2_m;
  real_T rtb_Sin;
  real_T rtb_Sum1_j;
  real_T rtb_Sum2_p;
  real_T rtb_Sum3;
  real_T rtb_Sum4_a;
  real_T rtb_Sum_e;
  real_T rtb_Sum_kk_idx_0;
  real_T rtb_Sum_kk_idx_1;
  real_T rtb_Sum_kk_idx_2;
  real_T rtb_Sum_kk_idx_3;
  real_T rtb_Switch2;
  real_T rtb_Switch2_b;
  real_T rtb_Switch2_d;
  real_T rtb_Switch2_f;
  real_T rtb_Switch2_j;
  real_T rtb_Switch2_m;
  real_T rtb_Switch_ft_idx_1;
  real_T rtb_Switch_ft_idx_2;
  real_T rtb_Switch_ft_idx_3;
  real_T rtb_UkYk1_l;
  real_T rtb_llaBias_na_idx_0;
  real_T rtb_llaBias_na_idx_1;
  real_T rtb_llaBias_na_idx_2;
  real_T rtb_n_m;
  real_T rtb_sqrt;
  int32_T exitg1;
  int32_T i;
  int32_T rtb_QuaternionstoDirectionCos_1;
  int32_T uIdx;
  boolean_T rtb_Compare_p;
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LogicalOperator1;
  boolean_T rtb_LogicalOperator1_f;
  boolean_T rtb_LogicalOperator1_f3;
  boolean_T rtb_LogicalOperator1_kg;
  boolean_T rtb_LogicalOperator_a;
  boolean_T rtb_LogicalOperator_b;
  boolean_T rtb_LogicalOperator_ff;
  boolean_T rtb_LogicalOperator_l;
  boolean_T rtb_LogicalOperator_o;
  boolean_T rtb_LogicalOperator_p;
  flightMode rtb_flightMode_enum;

  /* Quat2Dcm: '<S470>/Quaternions to  Direction Cosine Matrix' incorporates:
   *  Quat2Dcm: '<S409>/C-'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = sqrt(((rtDW->UnitDelay_2_DSTATE[0] *
    rtDW->UnitDelay_2_DSTATE[0] + rtDW->UnitDelay_2_DSTATE[1] *
    rtDW->UnitDelay_2_DSTATE[1]) + rtDW->UnitDelay_2_DSTATE[2] *
    rtDW->UnitDelay_2_DSTATE[2]) + rtDW->UnitDelay_2_DSTATE[3] *
    rtDW->UnitDelay_2_DSTATE[3]);
  rtb_Product1_ad = 1.0 / rtb_Product1_ad;
  rtb_Switch_ft_idx_1 = rtb_Product1_ad * rtDW->UnitDelay_2_DSTATE[1];
  rtb_Switch_ft_idx_2 = rtb_Product1_ad * rtDW->UnitDelay_2_DSTATE[2];
  rtb_Switch_ft_idx_3 = rtb_Product1_ad * rtDW->UnitDelay_2_DSTATE[3];
  rtb_Product2_l = rtb_Product1_ad * rtDW->UnitDelay_2_DSTATE[0];
  rtb_Sin = rtb_Product2_l * rtb_Product2_l;
  rtb_Sum_e = rtb_Switch_ft_idx_1 * rtb_Switch_ft_idx_1;
  rtb_Integrator_b = rtb_Switch_ft_idx_2 * rtb_Switch_ft_idx_2;
  rtb_Cos = rtb_Switch_ft_idx_3 * rtb_Switch_ft_idx_3;
  rtb_Cos_e = ((rtb_Sin + rtb_Sum_e) - rtb_Integrator_b) - rtb_Cos;
  rtb_QuaternionstoDirectionCosin[0] = rtb_Cos_e;
  rtb_Cos_l = rtb_Switch_ft_idx_1 * rtb_Switch_ft_idx_2;
  rtb_Product1_ad = rtb_Product2_l * rtb_Switch_ft_idx_3;
  rtb_Sum2_p = (rtb_Cos_l + rtb_Product1_ad) * 2.0;
  rtb_QuaternionstoDirectionCosin[3] = rtb_Sum2_p;
  rtb_Product1_e = rtb_Switch_ft_idx_1 * rtb_Switch_ft_idx_3;
  rtb_Sum_kk_idx_3 = rtb_Product2_l * rtb_Switch_ft_idx_2;
  rtb_Switch2 = (rtb_Product1_e - rtb_Sum_kk_idx_3) * 2.0;
  rtb_QuaternionstoDirectionCosin[6] = rtb_Switch2;
  rtb_Cos_l = (rtb_Cos_l - rtb_Product1_ad) * 2.0;
  rtb_QuaternionstoDirectionCosin[1] = rtb_Cos_l;
  rtb_Sin -= rtb_Sum_e;
  rtb_Sum_e = (rtb_Sin + rtb_Integrator_b) - rtb_Cos;
  rtb_QuaternionstoDirectionCosin[4] = rtb_Sum_e;
  rtb_Product1_ad = rtb_Switch_ft_idx_2 * rtb_Switch_ft_idx_3;
  rtb_Switch_ft_idx_1 *= rtb_Product2_l;
  rtb_Switch_ft_idx_2 = (rtb_Product1_ad + rtb_Switch_ft_idx_1) * 2.0;
  rtb_QuaternionstoDirectionCosin[7] = rtb_Switch_ft_idx_2;
  rtb_Product1_e = (rtb_Product1_e + rtb_Sum_kk_idx_3) * 2.0;
  rtb_QuaternionstoDirectionCosin[2] = rtb_Product1_e;
  rtb_Product1_ad = (rtb_Product1_ad - rtb_Switch_ft_idx_1) * 2.0;
  rtb_QuaternionstoDirectionCosin[5] = rtb_Product1_ad;
  rtb_Sin = (rtb_Sin - rtb_Integrator_b) + rtb_Cos;
  rtb_QuaternionstoDirectionCosin[8] = rtb_Sin;

  /* Quat2Dcm: '<S409>/C-' incorporates:
   *  Math: '<S418>/Math Function'
   */
  rtb_MathFunction_k[0] = rtb_Cos_e;
  rtb_MathFunction_k[3] = rtb_Sum2_p;
  rtb_MathFunction_k[6] = rtb_Switch2;
  rtb_MathFunction_k[1] = rtb_Cos_l;
  rtb_MathFunction_k[4] = rtb_Sum_e;
  rtb_MathFunction_k[7] = rtb_Switch_ft_idx_2;
  rtb_MathFunction_k[2] = rtb_Product1_e;
  rtb_MathFunction_k[5] = rtb_Product1_ad;
  rtb_MathFunction_k[8] = rtb_Sin;

  /* DotProduct: '<S409>/Dot Product' */
  rtb_Product1_ad = 0.0;
  for (i = 0; i < 3; i++) {
    /* Sum: '<S413>/Sum' incorporates:
     *  Inport: '<Root>/sensor_bus'
     *  UnitDelay generated from: '<S408>/Unit Delay'
     */
    rtb_Cos = rtU_sensor_bus_e->wBdyMeas_rps[i] - rtDW->UnitDelay_13_DSTATE[i];
    rtb_wBdyEst_rps[i] = rtb_Cos;

    /* DiscreteTransferFcn: '<S409>/Discrete Transfer Fcn1' */
    uIdx = i * 3;
    rtb_Sin = rtDW->DiscreteTransferFcn1_states[uIdx];
    rtb_Sum_e = rtDW->DiscreteTransferFcn1_states[uIdx + 1];
    rtb_Integrator_b = rtDW->DiscreteTransferFcn1_states[uIdx + 2];
    rtb_Cos = ((rtb_Cos - -1.76 * rtb_Sin) - rtb_Sum_e * 1.1829) -
      rtb_Integrator_b * -0.2781;
    DiscreteTransferFcn1_tmp[i] = rtb_Cos;

    /* Gain: '<S409>/Gain1' incorporates:
     *  DiscreteTransferFcn: '<S409>/Discrete Transfer Fcn1'
     */
    rtb_Sin = (((0.0181 * rtb_Cos + 0.0543 * rtb_Sin) + rtb_Sum_e * 0.0543) +
               rtb_Integrator_b * 0.0181) * navControl.dt_s;
    rtb_gyroFilt_rps[i] = rtb_Sin;

    /* DotProduct: '<S409>/Dot Product' */
    rtb_Product1_ad += rtb_Sin * rtb_Sin;
  }

  /* Sqrt: '<S409>/Sqrt' */
  rtb_Product1_ad = sqrt(rtb_Product1_ad);

  /* Gain: '<S409>/Gain2' */
  rtb_Integrator_b = 0.5 * rtb_Product1_ad;

  /* Trigonometry: '<S409>/Cos' */
  rtb_Sum_kk_idx_0 = cos(rtb_Integrator_b);

  /* Trigonometry: '<S409>/Sin' */
  rtb_Sin = sin(rtb_Integrator_b);

  /* Switch: '<S414>/Switch' incorporates:
   *  Constant: '<S414>/Constant4'
   *  Constant: '<S414>/Constant5'
   */
  if (rtb_Product1_ad >= 0.0) {
    i = 1;
  } else {
    i = -1;
  }

  /* Product: '<S414>/Product' incorporates:
   *  Constant: '<S414>/Constant'
   *  MinMax: '<S414>/Max'
   *  Switch: '<S414>/Switch'
   */
  rtb_Integrator_b = (real_T)i * fmax(1.0E-6, rtb_Product1_ad);

  /* Product: '<S409>/Divide' */
  rtb_Sum_kk_idx_1 = rtb_Sin * rtb_gyroFilt_rps[0] / rtb_Integrator_b;
  rtb_Sum_kk_idx_2 = rtb_Sin * rtb_gyroFilt_rps[1] / rtb_Integrator_b;
  rtb_Sum_kk_idx_3 = rtb_Sin * rtb_gyroFilt_rps[2] / rtb_Integrator_b;

  /* Product: '<S419>/Product1' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = rtDW->UnitDelay_2_DSTATE[1] * rtb_Sum_kk_idx_1;

  /* Sum: '<S419>/Sum' incorporates:
   *  Product: '<S419>/Product'
   *  Product: '<S419>/Product2'
   *  Product: '<S419>/Product3'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Sin = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Sum_kk_idx_0 - rtb_Product1_ad)
             - rtDW->UnitDelay_2_DSTATE[2] * rtb_Sum_kk_idx_2) -
    rtDW->UnitDelay_2_DSTATE[3] * rtb_Sum_kk_idx_3;

  /* Product: '<S420>/Product3' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = rtb_Sum_kk_idx_2 * rtDW->UnitDelay_2_DSTATE[3];

  /* Sum: '<S420>/Sum' incorporates:
   *  Product: '<S420>/Product'
   *  Product: '<S420>/Product1'
   *  Product: '<S420>/Product2'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Integrator_b = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Sum_kk_idx_1 +
                       rtb_Sum_kk_idx_0 * rtDW->UnitDelay_2_DSTATE[1]) +
                      rtDW->UnitDelay_2_DSTATE[2] * rtb_Sum_kk_idx_3) -
    rtb_Product1_ad;

  /* Product: '<S421>/Product3' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = rtb_Sum_kk_idx_1 * rtDW->UnitDelay_2_DSTATE[3];

  /* Sum: '<S421>/Sum' incorporates:
   *  Product: '<S421>/Product'
   *  Product: '<S421>/Product1'
   *  Product: '<S421>/Product2'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Sum_e = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Sum_kk_idx_2 -
                rtDW->UnitDelay_2_DSTATE[1] * rtb_Sum_kk_idx_3) +
               rtb_Sum_kk_idx_0 * rtDW->UnitDelay_2_DSTATE[2]) + rtb_Product1_ad;

  /* Product: '<S422>/Product3' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = rtb_Sum_kk_idx_0 * rtDW->UnitDelay_2_DSTATE[3];

  /* Product: '<S422>/Product1' */
  rtb_Cos = rtb_Sum_kk_idx_2;

  /* Product: '<S422>/Product2' */
  rtb_Cos_e = rtb_Sum_kk_idx_1;

  /* SignalConversion generated from: '<S417>/Dot Product' incorporates:
   *  Product: '<S422>/Product'
   *  Product: '<S422>/Product1'
   *  Product: '<S422>/Product2'
   *  Sum: '<S422>/Sum'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Sum_kk_idx_0 = rtb_Sin;
  rtb_Sum_kk_idx_1 = rtb_Integrator_b;
  rtb_Sum_kk_idx_2 = rtb_Sum_e;
  rtb_Sum_kk_idx_3 = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Sum_kk_idx_3 +
                       rtDW->UnitDelay_2_DSTATE[1] * rtb_Cos) - rtb_Cos_e *
                      rtDW->UnitDelay_2_DSTATE[2]) + rtb_Product1_ad;

  /* Switch: '<S417>/Switch' incorporates:
   *  Constant: '<S417>/Constant'
   *  DotProduct: '<S417>/Dot Product'
   *  SignalConversion generated from: '<S417>/Dot Product'
   */
  if (!(((rtb_Sin * rtb_Sin + rtb_Integrator_b * rtb_Integrator_b) + rtb_Sum_e *
         rtb_Sum_e) + rtb_Sum_kk_idx_3 * rtb_Sum_kk_idx_3 > 1.0E-6)) {
    rtb_Sum_kk_idx_0 = 1.0;
    rtb_Sum_kk_idx_1 = 0.0;
    rtb_Sum_kk_idx_2 = 0.0;
    rtb_Sum_kk_idx_3 = 0.0;
  }

  /* End of Switch: '<S417>/Switch' */

  /* Product: '<S424>/Product3' */
  rtb_Product1_ad = rtb_Sum_kk_idx_3 * rtb_Sum_kk_idx_3;

  /* Sqrt: '<S423>/sqrt' incorporates:
   *  Product: '<S424>/Product'
   *  Product: '<S424>/Product1'
   *  Product: '<S424>/Product2'
   *  Sum: '<S424>/Sum'
   */
  rtb_Sum2_p = sqrt(((rtb_Sum_kk_idx_0 * rtb_Sum_kk_idx_0 + rtb_Sum_kk_idx_1 *
                      rtb_Sum_kk_idx_1) + rtb_Sum_kk_idx_2 * rtb_Sum_kk_idx_2) +
                    rtb_Product1_ad);

  /* Product: '<S416>/Product3' */
  rtb_Sin = rtb_Sum_kk_idx_3 / rtb_Sum2_p;

  /* Product: '<S416>/Product2' */
  rtb_Integrator_b = rtb_Sum_kk_idx_2 / rtb_Sum2_p;

  /* Product: '<S416>/Product1' */
  rtb_Sum_e = rtb_Sum_kk_idx_1 / rtb_Sum2_p;

  /* Product: '<S416>/Product' */
  rtb_Sum2_p = rtb_Sum_kk_idx_0 / rtb_Sum2_p;

  /* Quat2Dcm: '<S409>/C+' incorporates:
   *  Quat2Dcm: '<S433>/C-'
   *  SignalConversion generated from: '<S409>/C+'
   */
  rtb_Product1_ad = sqrt(((rtb_Sum2_p * rtb_Sum2_p + rtb_Sum_e * rtb_Sum_e) +
    rtb_Integrator_b * rtb_Integrator_b) + rtb_Sin * rtb_Sin);
  rtb_UkYk1_l = 1.0 / rtb_Product1_ad;
  rtb_Switch2 = rtb_UkYk1_l * rtb_Sum_e;
  rtb_Product1_e = rtb_UkYk1_l * rtb_Integrator_b;
  rtb_Product1_ad = rtb_UkYk1_l * rtb_Sin;
  rtb_Product2_l = rtb_UkYk1_l * rtb_Sum2_p;
  rtb_Cos = rtb_Product2_l * rtb_Product2_l;
  rtb_Cos_e = rtb_Switch2 * rtb_Switch2;
  rtb_Cos_l = rtb_Product1_e * rtb_Product1_e;
  rtb_Switch_ft_idx_1 = rtb_Product1_ad * rtb_Product1_ad;
  rtb_Switch_ft_idx_2 = ((rtb_Cos + rtb_Cos_e) - rtb_Cos_l) -
    rtb_Switch_ft_idx_1;
  rtb_C_l[0] = rtb_Switch_ft_idx_2;
  rtb_Switch_ft_idx_3 = rtb_Switch2 * rtb_Product1_e;
  rtb_Sum_kk_idx_3 = rtb_Product2_l * rtb_Product1_ad;
  rtb_Product2_m = (rtb_Switch_ft_idx_3 + rtb_Sum_kk_idx_3) * 2.0;
  rtb_C_l[3] = rtb_Product2_m;
  rtb_sqrt = rtb_Switch2 * rtb_Product1_ad;
  rtb_Filter_g = rtb_Product2_l * rtb_Product1_e;
  rtb_MathFunction_idx_0 = (rtb_sqrt - rtb_Filter_g) * 2.0;
  rtb_C_l[6] = rtb_MathFunction_idx_0;
  rtb_Switch_ft_idx_3 = (rtb_Switch_ft_idx_3 - rtb_Sum_kk_idx_3) * 2.0;
  rtb_C_l[1] = rtb_Switch_ft_idx_3;
  rtb_Cos -= rtb_Cos_e;
  rtb_Cos_e = (rtb_Cos + rtb_Cos_l) - rtb_Switch_ft_idx_1;
  rtb_C_l[4] = rtb_Cos_e;
  rtb_Sum_kk_idx_3 = rtb_Product1_e * rtb_Product1_ad;
  rtb_Product1_ad = rtb_Product2_l * rtb_Switch2;
  rtb_Product2_l = (rtb_Sum_kk_idx_3 + rtb_Product1_ad) * 2.0;
  rtb_C_l[7] = rtb_Product2_l;
  rtb_sqrt = (rtb_sqrt + rtb_Filter_g) * 2.0;
  rtb_C_l[2] = rtb_sqrt;
  rtb_Sum_kk_idx_3 = (rtb_Sum_kk_idx_3 - rtb_Product1_ad) * 2.0;
  rtb_C_l[5] = rtb_Sum_kk_idx_3;
  rtb_Cos = (rtb_Cos - rtb_Cos_l) + rtb_Switch_ft_idx_1;
  rtb_C_l[8] = rtb_Cos;

  /* Quat2Dcm: '<S433>/C-' */
  rtb_C[0] = rtb_Switch_ft_idx_2;
  rtb_C[3] = rtb_Product2_m;
  rtb_C[6] = rtb_MathFunction_idx_0;
  rtb_C[1] = rtb_Switch_ft_idx_3;
  rtb_C[4] = rtb_Cos_e;
  rtb_C[7] = rtb_Product2_l;
  rtb_C[2] = rtb_sqrt;
  rtb_C[5] = rtb_Sum_kk_idx_3;
  rtb_C[8] = rtb_Cos;

  /* DiscreteTransferFcn: '<S428>/Gyro Filter' */
  rtb_Cos = rtb_wBdyEst_rps[0] - 0.4142 * rtDW->GyroFilter_states[0];
  GyroFilter_tmp[0] = rtb_Cos;
  rtb_Cos = 0.7071 * rtb_Cos + 0.7071 * rtDW->GyroFilter_states[0];
  rtb_Cos_e = rtb_wBdyEst_rps[1] - 0.4142 * rtDW->GyroFilter_states[1];
  GyroFilter_tmp[1] = rtb_Cos_e;
  rtb_Cos_e = 0.7071 * rtb_Cos_e + 0.7071 * rtDW->GyroFilter_states[1];
  rtb_Cos_l = rtb_wBdyEst_rps[2] - 0.4142 * rtDW->GyroFilter_states[2];
  GyroFilter_tmp[2] = rtb_Cos_l;
  rtb_Cos_l = 0.7071 * rtb_Cos_l + 0.7071 * rtDW->GyroFilter_states[2];

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_flightMode_enum = rtDW->UnitDelay_1_DSTATE;

  /* If: '<S427>/If' incorporates:
   *  Constant: '<S438>/Constant'
   *  RelationalOperator: '<S438>/Compare'
   */
  if (rtb_flightMode_enum == IDLE) {
    /* Outputs for IfAction SubSystem: '<S427>/Attitude Complementary Filter' incorporates:
     *  ActionPort: '<S436>/Action Port'
     */
    /* Quat2Dcm: '<S436>/Quaternions to  Direction Cosine Matrix' incorporates:
     *  Constant: '<S436>/Constant1'
     */
    rtb_Product1_ad = sqrt(((navControl.eulerCalcPreRotationInv[0] *
      navControl.eulerCalcPreRotationInv[0] +
      navControl.eulerCalcPreRotationInv[1] *
      navControl.eulerCalcPreRotationInv[1]) +
      navControl.eulerCalcPreRotationInv[2] *
      navControl.eulerCalcPreRotationInv[2]) +
      navControl.eulerCalcPreRotationInv[3] *
      navControl.eulerCalcPreRotationInv[3]);
    rtb_UkYk1_l = 1.0 / rtb_Product1_ad;
    rtb_Switch2 = rtb_UkYk1_l * navControl.eulerCalcPreRotationInv[1];
    rtb_Product1_e = rtb_UkYk1_l * navControl.eulerCalcPreRotationInv[2];
    rtb_Product1_ad = rtb_UkYk1_l * navControl.eulerCalcPreRotationInv[3];
    rtb_Product2_l = rtb_UkYk1_l * navControl.eulerCalcPreRotationInv[0];
    rtb_Switch_ft_idx_1 = rtb_Product2_l * rtb_Product2_l;
    rtb_Switch_ft_idx_2 = rtb_Switch2 * rtb_Switch2;
    rtb_Switch_ft_idx_3 = rtb_Product1_e * rtb_Product1_e;
    rtb_Sum_kk_idx_3 = rtb_Product1_ad * rtb_Product1_ad;
    rtb_QuaternionstoDirectionCos_i[0] = ((rtb_Switch_ft_idx_1 +
      rtb_Switch_ft_idx_2) - rtb_Switch_ft_idx_3) - rtb_Sum_kk_idx_3;
    rtb_Product2_m = rtb_Switch2 * rtb_Product1_e;
    rtb_sqrt = rtb_Product2_l * rtb_Product1_ad;
    rtb_QuaternionstoDirectionCos_i[3] = (rtb_Product2_m + rtb_sqrt) * 2.0;
    rtb_Filter_g = rtb_Switch2 * rtb_Product1_ad;
    rtb_MathFunction_idx_0 = rtb_Product2_l * rtb_Product1_e;
    rtb_QuaternionstoDirectionCos_i[6] = (rtb_Filter_g - rtb_MathFunction_idx_0)
      * 2.0;
    rtb_QuaternionstoDirectionCos_i[1] = (rtb_Product2_m - rtb_sqrt) * 2.0;
    rtb_Switch_ft_idx_1 -= rtb_Switch_ft_idx_2;
    rtb_QuaternionstoDirectionCos_i[4] = (rtb_Switch_ft_idx_1 +
      rtb_Switch_ft_idx_3) - rtb_Sum_kk_idx_3;
    rtb_Switch_ft_idx_2 = rtb_Product1_e * rtb_Product1_ad;
    rtb_Product2_m = rtb_Product2_l * rtb_Switch2;
    rtb_QuaternionstoDirectionCos_i[7] = (rtb_Switch_ft_idx_2 + rtb_Product2_m) *
      2.0;
    rtb_QuaternionstoDirectionCos_i[2] = (rtb_Filter_g + rtb_MathFunction_idx_0)
      * 2.0;
    rtb_QuaternionstoDirectionCos_i[5] = (rtb_Switch_ft_idx_2 - rtb_Product2_m) *
      2.0;
    rtb_QuaternionstoDirectionCos_i[8] = (rtb_Switch_ft_idx_1 -
      rtb_Switch_ft_idx_3) + rtb_Sum_kk_idx_3;

    /* Product: '<S436>/Matrix Multiply' incorporates:
     *  Delay generated from: '<S436>/Delay'
     *  Gain: '<S436>/Gain2'
     *  Quat2Dcm: '<S436>/Quaternions to  Direction Cosine Matrix'
     */
    rtb_Product1_ad = 0.0;
    rtb_Switch_ft_idx_1 = 0.0;
    rtb_Switch_ft_idx_2 = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_Product2_m = -rtDW->Delay_3_DSTATE[i];
      rtb_Product1_ad += rtb_QuaternionstoDirectionCos_i[3 * i] * rtb_Product2_m;
      rtb_Switch_ft_idx_1 += rtb_QuaternionstoDirectionCos_i[3 * i + 1] *
        rtb_Product2_m;
      rtb_Switch_ft_idx_2 += rtb_QuaternionstoDirectionCos_i[3 * i + 2] *
        rtb_Product2_m;
    }

    rtb_gyroFilt_rps[2] = rtb_Switch_ft_idx_2;
    rtb_gyroFilt_rps[1] = rtb_Switch_ft_idx_1;
    rtb_gyroFilt_rps[0] = rtb_Product1_ad;

    /* End of Product: '<S436>/Matrix Multiply' */

    /* Product: '<S436>/Matrix Multiply1' incorporates:
     *  Angle2Dcm: '<S436>/Rotation Angles to Direction Cosine Matrix'
     */
    rtb_Sum_kk_idx_3 = 0.0;
    rtb_Switch_ft_idx_1 = 0.0;
    rtb_Switch_ft_idx_2 = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_Product2_m = rtb_gyroFilt_rps[i];
      rtb_Sum_kk_idx_3 += rtConstB.RotationAnglestoDirectionCo[3 * i] *
        rtb_Product2_m;
      rtb_Switch_ft_idx_1 += rtConstB.RotationAnglestoDirectionCo[3 * i + 1] *
        rtb_Product2_m;
      rtb_Switch_ft_idx_2 += rtConstB.RotationAnglestoDirectionCo[3 * i + 2] *
        rtb_Product2_m;
    }

    /* Math: '<S443>/Math Function1' incorporates:
     *  Math: '<S443>/Math Function'
     *  Product: '<S436>/Matrix Multiply1'
     *  Sum: '<S443>/Sum of Elements'
     *
     * About '<S443>/Math Function1':
     *  Operator: sqrt
     */
    rtb_Product2_l = sqrt((rtb_Sum_kk_idx_3 * rtb_Sum_kk_idx_3 +
      rtb_Switch_ft_idx_1 * rtb_Switch_ft_idx_1) + rtb_Switch_ft_idx_2 *
                          rtb_Switch_ft_idx_2);

    /* Switch: '<S443>/Switch' incorporates:
     *  Constant: '<S443>/Constant'
     *  Product: '<S436>/Matrix Multiply1'
     *  Product: '<S443>/Product'
     */
    if (rtb_Product2_l > 1.0E-6) {
      rtb_Switch_ft_idx_3 = rtb_Product2_l;
    } else {
      rtb_Sum_kk_idx_3 *= 0.0;
      rtb_Switch_ft_idx_1 *= 0.0;
      rtb_Switch_ft_idx_2 *= 0.0;
      rtb_Switch_ft_idx_3 = 1.0;
    }

    /* End of Switch: '<S443>/Switch' */

    /* UnaryMinus: '<S436>/Unary Minus1' incorporates:
     *  Product: '<S443>/Divide'
     */
    rtb_MatrixMultiply1_idx_1 = -(rtb_Switch_ft_idx_1 / rtb_Switch_ft_idx_3);
    rtb_MatrixMultiply1_idx_2 = -(rtb_Switch_ft_idx_2 / rtb_Switch_ft_idx_3);

    /* Angle2Quat: '<S446>/Rotation Angles to Quaternions' incorporates:
     *  Constant: '<S436>/Constant'
     *  Math: '<S436>/Square'
     *  Math: '<S436>/Square1'
     *  Product: '<S443>/Divide'
     *  SignalConversion generated from: '<S446>/Rotation Angles to Quaternions'
     *  Sqrt: '<S436>/Sqrt'
     *  Sum: '<S436>/Sum'
     *  Trigonometry: '<S436>/Atan1'
     *  Trigonometry: '<S436>/Atan2'
     *  UnaryMinus: '<S436>/Unary Minus2'
     */
    rtb_Switch_ft_idx_1 = navControl.roll0_rad / 2.0;
    rtb_Product1_ad = cos(rtb_Switch_ft_idx_1);
    rtb_Switch_ft_idx_2 = rt_atan2d_snf(rtb_Sum_kk_idx_3 / rtb_Switch_ft_idx_3,
      sqrt(rtb_MatrixMultiply1_idx_1 * rtb_MatrixMultiply1_idx_1 +
           rtb_MatrixMultiply1_idx_2 * rtb_MatrixMultiply1_idx_2)) / 2.0;
    rtb_Product2_l = cos(rtb_Switch_ft_idx_2);
    rtb_Switch_ft_idx_3 = rt_atan2d_snf(-rtb_MatrixMultiply1_idx_1,
      rtb_MatrixMultiply1_idx_2) / 2.0;
    rtb_Product2_m = cos(rtb_Switch_ft_idx_3);
    rtb_Product1_e = sin(rtb_Switch_ft_idx_1);
    rtb_sqrt = sin(rtb_Switch_ft_idx_2);
    rtb_Switch2 = sin(rtb_Switch_ft_idx_3);
    rtb_Switch_ft_idx_3 = rtb_Product1_ad * rtb_Product2_l;
    rtb_Filter_g = rtb_Product1_e * rtb_sqrt;
    rtb_Sum_kk_idx_3 = rtb_Switch_ft_idx_3 * rtb_Product2_m + rtb_Filter_g *
      rtb_Switch2;
    rtb_Product1_ad *= rtb_sqrt;
    rtb_Switch_ft_idx_2 = rtb_Product1_e * rtb_Product2_l;
    rtb_Switch_ft_idx_1 = rtb_Switch_ft_idx_2 * rtb_Product2_m - rtb_Product1_ad
      * rtb_Switch2;
    rtb_Switch_ft_idx_2 = rtb_Product1_ad * rtb_Product2_m + rtb_Switch_ft_idx_2
      * rtb_Switch2;
    rtb_Switch_ft_idx_3 = rtb_Switch_ft_idx_3 * rtb_Switch2 - rtb_Filter_g *
      rtb_Product2_m;

    /* Sum: '<S451>/Sum' incorporates:
     *  Constant: '<S446>/Constant'
     *  Product: '<S451>/Product'
     *  Product: '<S451>/Product1'
     *  Product: '<S451>/Product2'
     *  Product: '<S451>/Product3'
     */
    rtb_Product1_ad = ((navControl.eulerCalcPreRotationInv[0] * rtb_Sum_kk_idx_3
                        - navControl.eulerCalcPreRotationInv[1] *
                        rtb_Switch_ft_idx_1) -
                       navControl.eulerCalcPreRotationInv[2] *
                       rtb_Switch_ft_idx_2) -
      navControl.eulerCalcPreRotationInv[3] * rtb_Switch_ft_idx_3;

    /* Sum: '<S452>/Sum' incorporates:
     *  Constant: '<S446>/Constant'
     *  Product: '<S452>/Product'
     *  Product: '<S452>/Product1'
     *  Product: '<S452>/Product2'
     *  Product: '<S452>/Product3'
     */
    rtb_Product2_l = ((navControl.eulerCalcPreRotationInv[0] *
                       rtb_Switch_ft_idx_1 + rtb_Sum_kk_idx_3 *
                       navControl.eulerCalcPreRotationInv[1]) +
                      navControl.eulerCalcPreRotationInv[2] *
                      rtb_Switch_ft_idx_3) - rtb_Switch_ft_idx_2 *
      navControl.eulerCalcPreRotationInv[3];

    /* Sum: '<S453>/Sum' incorporates:
     *  Constant: '<S446>/Constant'
     *  Product: '<S453>/Product'
     *  Product: '<S453>/Product1'
     *  Product: '<S453>/Product2'
     *  Product: '<S453>/Product3'
     */
    rtb_Product2_m = ((navControl.eulerCalcPreRotationInv[0] *
                       rtb_Switch_ft_idx_2 - navControl.eulerCalcPreRotationInv
                       [1] * rtb_Switch_ft_idx_3) + rtb_Sum_kk_idx_3 *
                      navControl.eulerCalcPreRotationInv[2]) +
      rtb_Switch_ft_idx_1 * navControl.eulerCalcPreRotationInv[3];

    /* Sum: '<S454>/Sum' incorporates:
     *  Constant: '<S446>/Constant'
     *  Product: '<S454>/Product'
     *  Product: '<S454>/Product1'
     *  Product: '<S454>/Product2'
     *  Product: '<S454>/Product3'
     */
    rtb_Product1_e = ((navControl.eulerCalcPreRotationInv[0] *
                       rtb_Switch_ft_idx_3 + navControl.eulerCalcPreRotationInv
                       [1] * rtb_Switch_ft_idx_2) - rtb_Switch_ft_idx_1 *
                      navControl.eulerCalcPreRotationInv[2]) + rtb_Sum_kk_idx_3 *
      navControl.eulerCalcPreRotationInv[3];

    /* Sqrt: '<S455>/sqrt' incorporates:
     *  Product: '<S456>/Product'
     *  Product: '<S456>/Product1'
     *  Product: '<S456>/Product2'
     *  Product: '<S456>/Product3'
     *  Sum: '<S456>/Sum'
     */
    rtb_sqrt = sqrt(((rtb_Product1_ad * rtb_Product1_ad + rtb_Product2_l *
                      rtb_Product2_l) + rtb_Product2_m * rtb_Product2_m) +
                    rtb_Product1_e * rtb_Product1_e);

    /* Sum: '<S436>/Sum1' incorporates:
     *  Gain: '<S436>/Gain'
     *  Gain: '<S436>/Gain1'
     *  Product: '<S450>/Product'
     *  Product: '<S450>/Product1'
     *  Product: '<S450>/Product2'
     *  Product: '<S450>/Product3'
     */
    rtb_Sum_kk_idx_3 = (1.0 - navComp.attitudeGain) * (rtb_Product1_ad /
      rtb_sqrt) + navComp.attitudeGain * rtb_Sum2_p;
    rtb_Switch_ft_idx_1 = (1.0 - navComp.attitudeGain) * (rtb_Product2_l /
      rtb_sqrt) + navComp.attitudeGain * rtb_Sum_e;
    rtb_Switch_ft_idx_2 = (1.0 - navComp.attitudeGain) * (rtb_Product2_m /
      rtb_sqrt) + navComp.attitudeGain * rtb_Integrator_b;
    rtb_Switch_ft_idx_3 = (1.0 - navComp.attitudeGain) * (rtb_Product1_e /
      rtb_sqrt) + navComp.attitudeGain * rtb_Sin;

    /* Switch: '<S445>/Switch' incorporates:
     *  Constant: '<S445>/Constant'
     *  DotProduct: '<S445>/Dot Product'
     */
    if (!(((rtb_Sum_kk_idx_3 * rtb_Sum_kk_idx_3 + rtb_Switch_ft_idx_1 *
            rtb_Switch_ft_idx_1) + rtb_Switch_ft_idx_2 * rtb_Switch_ft_idx_2) +
          rtb_Switch_ft_idx_3 * rtb_Switch_ft_idx_3 > 1.0E-6)) {
      rtb_Sum_kk_idx_3 = 1.0;
      rtb_Switch_ft_idx_1 = 0.0;
      rtb_Switch_ft_idx_2 = 0.0;
      rtb_Switch_ft_idx_3 = 0.0;
    }

    /* End of Switch: '<S445>/Switch' */

    /* Sqrt: '<S447>/sqrt' incorporates:
     *  Product: '<S448>/Product'
     *  Product: '<S448>/Product1'
     *  Product: '<S448>/Product2'
     *  Product: '<S448>/Product3'
     *  Sum: '<S448>/Sum'
     */
    rtb_sqrt = sqrt(((rtb_Sum_kk_idx_3 * rtb_Sum_kk_idx_3 + rtb_Switch_ft_idx_1 *
                      rtb_Switch_ft_idx_1) + rtb_Switch_ft_idx_2 *
                     rtb_Switch_ft_idx_2) + rtb_Switch_ft_idx_3 *
                    rtb_Switch_ft_idx_3);

    /* Product: '<S444>/Product' incorporates:
     *  Merge: '<S427>/Merge'
     */
    rtDW->qEst_na[0] = rtb_Sum_kk_idx_3 / rtb_sqrt;

    /* Product: '<S444>/Product1' incorporates:
     *  Merge: '<S427>/Merge'
     */
    rtDW->qEst_na[1] = rtb_Switch_ft_idx_1 / rtb_sqrt;

    /* Product: '<S444>/Product2' incorporates:
     *  Merge: '<S427>/Merge'
     */
    rtDW->qEst_na[2] = rtb_Switch_ft_idx_2 / rtb_sqrt;

    /* Product: '<S444>/Product3' incorporates:
     *  Merge: '<S427>/Merge'
     */
    rtDW->qEst_na[3] = rtb_Switch_ft_idx_3 / rtb_sqrt;

    /* Update for Delay generated from: '<S436>/Delay' incorporates:
     *  Inport: '<Root>/sensor_bus'
     */
    for (i = 0; i < 499; i++) {
      uIdx = (i + 1) * 3;
      rtDW->Delay_3_DSTATE[i * 3] = rtDW->Delay_3_DSTATE[uIdx];
      rtDW->Delay_3_DSTATE[i * 3 + 1] = rtDW->Delay_3_DSTATE[uIdx + 1];
      rtDW->Delay_3_DSTATE[i * 3 + 2] = rtDW->Delay_3_DSTATE[uIdx + 2];
    }

    rtDW->Delay_3_DSTATE[1497] = rtU_sensor_bus_e->fBdyMeas_mps2[0];
    rtDW->Delay_3_DSTATE[1498] = rtU_sensor_bus_e->fBdyMeas_mps2[1];
    rtDW->Delay_3_DSTATE[1499] = rtU_sensor_bus_e->fBdyMeas_mps2[2];

    /* End of Update for Delay generated from: '<S436>/Delay' */
    /* End of Outputs for SubSystem: '<S427>/Attitude Complementary Filter' */
  } else {
    /* Outputs for IfAction SubSystem: '<S427>/Attitude Pass Through' incorporates:
     *  ActionPort: '<S437>/Action Port'
     */
    /* Merge: '<S427>/Merge' incorporates:
     *  SignalConversion generated from: '<S437>/qEst_na'
     */
    rtDW->qEst_na[0] = rtb_Sum2_p;
    rtDW->qEst_na[1] = rtb_Sum_e;
    rtDW->qEst_na[2] = rtb_Integrator_b;
    rtDW->qEst_na[3] = rtb_Sin;

    /* End of Outputs for SubSystem: '<S427>/Attitude Pass Through' */
  }

  /* End of If: '<S427>/If' */

  /* Product: '<S460>/Product3' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S462>/Product1'
   */
  rtb_Switch_ft_idx_1 = 0.0 * rtDW->qEst_na[3];
  rtb_Product1_ad = rtb_Switch_ft_idx_1;

  /* Product: '<S460>/Product1' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S462>/Product3'
   */
  rtb_Sum_e = 0.0 * rtDW->qEst_na[1];

  /* Sum: '<S460>/Sum' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S460>/Product'
   *  Product: '<S460>/Product1'
   *  Product: '<S460>/Product2'
   */
  rtb_Sin = ((0.707106781187 * rtDW->qEst_na[0] - rtb_Sum_e) - -0.707106781187 *
             rtDW->qEst_na[2]) - rtb_Product1_ad;

  /* Product: '<S461>/Product3' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S463>/Product1'
   */
  rtb_Sum2_p = rtDW->qEst_na[2] * 0.0;
  rtb_Product1_ad = rtb_Sum2_p;

  /* Product: '<S461>/Product1' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S463>/Product3'
   */
  rtb_Sum_kk_idx_3 = rtDW->qEst_na[0] * 0.0;

  /* Sum: '<S461>/Sum' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S461>/Product'
   *  Product: '<S461>/Product1'
   *  Product: '<S461>/Product2'
   */
  rtb_Integrator_b = ((0.707106781187 * rtDW->qEst_na[1] + rtb_Sum_kk_idx_3) +
                      -0.707106781187 * rtDW->qEst_na[3]) - rtb_Product1_ad;

  /* Product: '<S462>/Product3' */
  rtb_Product1_ad = rtb_Sum_e;

  /* Sum: '<S462>/Sum' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S462>/Product'
   *  Product: '<S462>/Product2'
   */
  rtb_Sum_e = ((0.707106781187 * rtDW->qEst_na[2] - rtb_Switch_ft_idx_1) +
               rtDW->qEst_na[0] * -0.707106781187) + rtb_Product1_ad;

  /* Product: '<S463>/Product3' */
  rtb_Product1_ad = rtb_Sum_kk_idx_3;

  /* SignalConversion generated from: '<S429>/Quaternions to Rotation Angles' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S463>/Product'
   *  Product: '<S463>/Product2'
   *  Sum: '<S463>/Sum'
   */
  rtb_Sum_kk_idx_3 = ((0.707106781187 * rtDW->qEst_na[3] + rtb_Sum2_p) -
                      rtDW->qEst_na[1] * -0.707106781187) + rtb_Product1_ad;

  /* Quat2Angle: '<S429>/Quaternions to Rotation Angles' incorporates:
   *  SignalConversion generated from: '<S429>/Quaternions to Rotation Angles'
   *  Trigonometry: '<S224>/Cos1'
   */
  rtb_Product1_ad = sqrt(((rtb_Sin * rtb_Sin + rtb_Integrator_b *
    rtb_Integrator_b) + rtb_Sum_e * rtb_Sum_e) + rtb_Sum_kk_idx_3 *
    rtb_Sum_kk_idx_3);
  rtb_Product2_m = 1.0 / rtb_Product1_ad;
  rtb_Product2_l = rtb_Product2_m * rtb_Sin;
  rtb_Switch2 = rtb_Product2_m * rtb_Integrator_b;
  rtb_Product1_e = rtb_Product2_m * rtb_Sum_e;
  rtb_Product1_ad = rtb_Product2_m * rtb_Sum_kk_idx_3;
  rtb_Product2_m = rtb_Product2_l * rtb_Product2_l;
  rtb_Switch_ft_idx_2 = rtb_Switch2 * rtb_Switch2;
  rtb_Sin = rtb_Product1_e * rtb_Product1_e;
  rtb_Sum_e = rtb_Product1_ad * rtb_Product1_ad;
  rtb_Sum2_p = ((rtb_Product2_m + rtb_Switch_ft_idx_2) - rtb_Sin) - rtb_Sum_e;
  rtb_Switch_ft_idx_3 = rtb_Switch2 * rtb_Product1_e;
  rtb_Sum_kk_idx_3 = rtb_Product2_l * rtb_Product1_ad;
  rtb_sqrt = (rtb_Switch_ft_idx_3 + rtb_Sum_kk_idx_3) * 2.0;
  rtb_Integrator_b = rtb_Switch2 * rtb_Product1_ad;
  rtb_Switch_ft_idx_1 = rtb_Product2_l * rtb_Product1_e;
  rtb_MathFunction_idx_0 = (rtb_Integrator_b - rtb_Switch_ft_idx_1) * 2.0;
  rtb_Filter_g = (rtb_Switch_ft_idx_3 - rtb_Sum_kk_idx_3) * 2.0;
  rtb_Switch_ft_idx_2 = rtb_Product2_m - rtb_Switch_ft_idx_2;
  rtb_MathFunction_idx_1 = (rtb_Switch_ft_idx_2 + rtb_Sin) - rtb_Sum_e;
  rtb_Switch2_f = rtb_Product1_e * rtb_Product1_ad;
  rtb_Product1_ad = rtb_Product2_l * rtb_Switch2;
  rtb_MathFunction_idx_2 = (rtb_Switch2_f + rtb_Product1_ad) * 2.0;
  rtb_Product1_e = (rtb_Integrator_b + rtb_Switch_ft_idx_1) * 2.0;
  rtb_Product1_o = (rtb_Switch2_f - rtb_Product1_ad) * 2.0;
  rtb_Gain_a = (rtb_Switch_ft_idx_2 - rtb_Sin) + rtb_Sum_e;
  if (-rtb_MathFunction_idx_0 <= -1.0) {
    rtb_Sin = -1.0;
  } else if (-rtb_MathFunction_idx_0 >= 1.0) {
    rtb_Sin = 1.0;
  } else {
    rtb_Sin = -rtb_MathFunction_idx_0;
  }

  rtb_Switch_ft_idx_1 = asin(rtb_Sin);
  if (fabs(rtb_Sin) == 1.0) {
    rtb_accBdyEst_mps2[0] = rt_atan2d_snf(-rtb_Filter_g, rtb_MathFunction_idx_1);
    rtb_Switch_ft_idx_2 = 0.0;
    rtb_Switch_ft_idx_3 = 0.0;
  } else {
    rtb_Switch_ft_idx_2 = rt_atan2d_snf(rtb_sqrt, rtb_Sum2_p);
    rtb_Switch_ft_idx_3 = rt_atan2d_snf(rtb_MathFunction_idx_2, rtb_Gain_a);
    rtb_accBdyEst_mps2[0] = 0.0;
  }

  rtb_Product1_ad = cos(rtb_Switch_ft_idx_3);
  rtb_Sin = sin(rtb_Switch_ft_idx_3);
  rtb_Sum_kk_idx_3 = cos(rtb_Switch_ft_idx_1);
  rtb_Sum_e = sin(rtb_Switch_ft_idx_1);
  rtb_Product2_m = 0.0 * rtb_Sum_e;
  rtb_Product2_l = rtb_Product2_m + rtb_Sum_kk_idx_3;
  rtb_Integrator_b = 0.0 * rtb_Sum_kk_idx_3;
  rtb_Sum1_j = rtb_Integrator_b - rtb_Sum_e;
  rtb_UkYk1_l = rtb_Product1_ad * 0.0;
  rtb_Switch2 = (rtb_Integrator_b + rtb_UkYk1_l) + rtb_Sin * rtb_Sum_e;
  rtb_Integrator_i = rtb_Sin * 0.0 + rtb_Product1_ad;
  rtb_Switch2_f = 0.0 * -rtb_Sum_e;
  rtb_Sum3 = (rtb_Switch2_f + rtb_UkYk1_l) + rtb_Sin * rtb_Sum_kk_idx_3;
  rtb_PProdOut_b = -rtb_Sin * 0.0;
  rtb_Sum4_a = (rtb_Integrator_b + rtb_PProdOut_b) + rtb_Sum_e * rtb_Product1_ad;
  rtb_UkYk1_l -= rtb_Sin;
  rtb_PProdOut_b = (rtb_Switch2_f + rtb_PProdOut_b) + rtb_Product1_ad *
    rtb_Sum_kk_idx_3;
  rtb_Product1_ad = cos(rtb_Switch_ft_idx_2);
  rtb_Sin = sin(rtb_Switch_ft_idx_2);
  rtb_Product1_j3 = rtb_Integrator_b + rtb_Product2_m;
  rtb_Switch2_m = rtb_Switch2_f + rtb_Integrator_b;
  rtb_Divide = rtb_Integrator_b + rtb_Sum_e;
  rtb_Switch2_j = rtb_Switch2_f + rtb_Sum_kk_idx_3;
  rtb_Integrator_b = cos(rtb_accBdyEst_mps2[0]);
  rtb_Sum_e = sin(rtb_accBdyEst_mps2[0]);
  rtb_Product2_m = rtb_Sum1_j * 0.0;
  rtb_Switch2_f = rtb_Switch2_m * 0.0;
  rtb_Sum_kk_idx_0 = 0.0 * -rtb_Sum_e;
  rtb_Sum_kk_idx_1 = 0.0 * rtb_Integrator_b;
  rtb_Sum_kk_idx_2 = rtb_Switch2_j * 0.0;
  rtb_MathFunction_idx_0 = fabs(rtb_MathFunction_idx_0 - (rtb_Product2_l * 0.0 +
    rtb_Sum1_j));
  rtb_Sum1_j = rtb_Sum3 * 0.0;
  rtb_Product1_j = rtb_PProdOut_b * 0.0;
  if ((((((((fabs(rtb_Sum2_p - ((rtb_Product2_l * rtb_Integrator_b +
                rtb_Sum_kk_idx_0) + rtb_Product2_m)) + fabs(rtb_sqrt -
              ((rtb_Product2_l * rtb_Sum_e + rtb_Sum_kk_idx_1) + rtb_Product2_m)))
            + rtb_MathFunction_idx_0) + fabs(rtb_Filter_g - ((rtb_Integrator_b *
              rtb_Product1_j3 - rtb_Sum_e) + rtb_Switch2_f))) + fabs
          (rtb_MathFunction_idx_1 - ((rtb_Sum_e * rtb_Product1_j3 +
             rtb_Integrator_b) + rtb_Switch2_f))) + fabs(rtb_MathFunction_idx_2
          - (rtb_Product1_j3 * 0.0 + rtb_Switch2_m))) + fabs(rtb_Product1_e -
         ((rtb_Integrator_b * rtb_Divide + rtb_Sum_kk_idx_0) + rtb_Sum_kk_idx_2)))
       + fabs(rtb_Product1_o - ((rtb_Sum_e * rtb_Divide + rtb_Sum_kk_idx_1) +
         rtb_Sum_kk_idx_2))) + fabs(rtb_Gain_a - (rtb_Divide * 0.0 +
        rtb_Switch2_j)) <= (((((((fabs(rtb_Sum2_p - ((rtb_Product2_l *
                rtb_Product1_ad + 0.0 * -rtb_Sin) + rtb_Product2_m)) + fabs
             (rtb_sqrt - ((rtb_Product2_l * rtb_Sin + 0.0 * rtb_Product1_ad) +
                          rtb_Product2_m))) + rtb_MathFunction_idx_0) + fabs
           (rtb_Filter_g - ((rtb_Product1_ad * rtb_Switch2 + -rtb_Sin *
              rtb_Integrator_i) + rtb_Sum1_j))) + fabs(rtb_MathFunction_idx_1 -
           ((rtb_Sin * rtb_Switch2 + rtb_Integrator_i * rtb_Product1_ad) +
            rtb_Sum1_j))) + fabs(rtb_MathFunction_idx_2 - ((rtb_Switch2 * 0.0 +
            rtb_Integrator_i * 0.0) + rtb_Sum3))) + fabs(rtb_Product1_e -
         ((rtb_Product1_ad * rtb_Sum4_a + -rtb_Sin * rtb_UkYk1_l) +
          rtb_Product1_j))) + fabs(rtb_Product1_o - ((rtb_Sin * rtb_Sum4_a +
          rtb_Product1_ad * rtb_UkYk1_l) + rtb_Product1_j))) + fabs(rtb_Gain_a -
       ((rtb_Sum4_a * 0.0 + rtb_UkYk1_l * 0.0) + rtb_PProdOut_b))) {
    rtb_Switch_ft_idx_2 = rtb_accBdyEst_mps2[0];
    rtb_Switch_ft_idx_3 = 0.0;
  }

  /* Sum: '<S224>/Sum2' incorporates:
   *  Constant: '<S2>/Constant'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   */
  rtb_Sum2_p = guidanceParams.phiCmd_rad - rtb_Switch_ft_idx_3;

  /* Product: '<S319>/DProd Out' incorporates:
   *  Constant: '<S226>/Constant4'
   */
  rtb_Product1_ad = rtb_Sum2_p * outerLoopParams.rollGains[2];

  /* Sum: '<S321>/SumD' incorporates:
   *  DiscreteIntegrator: '<S321>/Filter'
   */
  rtb_Product1_ad -= rtDW->Filter_DSTATE;

  /* Product: '<S329>/NProd Out' incorporates:
   *  Constant: '<S226>/Constant4'
   */
  rtb_Sin = rtb_Product1_ad * outerLoopParams.rollGains[3];

  /* Product: '<S288>/Product1' incorporates:
   *  Constant: '<S226>/Constant4'
   *  DiscreteIntegrator: '<S326>/Integrator'
   *  Product: '<S331>/PProd Out'
   *  Sum: '<S335>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_e = ((rtb_Sum2_p * outerLoopParams.rollGains[0] +
                     rtDW->Integrator_DSTATE) + rtb_Sin) * (real_T)
    rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S347>/Switch2' incorporates:
   *  Constant: '<S226>/Constant2'
   *  Constant: '<S226>/Constant3'
   *  RelationalOperator: '<S347>/LowerRelop1'
   *  RelationalOperator: '<S347>/UpperRelop'
   *  Switch: '<S347>/Switch'
   */
  if (rtb_Product1_e > outerLoopParams.upLimitRollRate_rps) {
    rtb_Switch2 = outerLoopParams.upLimitRollRate_rps;
  } else if (rtb_Product1_e < outerLoopParams.loLimitRollRate_rps) {
    /* Switch: '<S347>/Switch' incorporates:
     *  Constant: '<S226>/Constant3'
     */
    rtb_Switch2 = outerLoopParams.loLimitRollRate_rps;
  } else {
    rtb_Switch2 = rtb_Product1_e;
  }

  /* End of Switch: '<S347>/Switch2' */

  /* Delay: '<S345>/Delay' */
  if (rtDW->icLoad) {
    rtDW->Delay_DSTATE = rtb_Switch2;
  }

  /* Product: '<S345>/delta rise limit' incorporates:
   *  Constant: '<S226>/Constant'
   *  SampleTimeMath: '<S345>/sample time'
   *
   * About '<S345>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Product2_l = outerLoopParams.upRateLimitRollRate_rps2 * 0.01;

  /* Sum: '<S345>/Difference Inputs1' incorporates:
   *  Delay: '<S345>/Delay'
   *
   * Block description for '<S345>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Integrator_b = rtb_Switch2 - rtDW->Delay_DSTATE;

  /* Switch: '<S346>/Switch2' incorporates:
   *  RelationalOperator: '<S346>/LowerRelop1'
   */
  if (!(rtb_Integrator_b > rtb_Product2_l)) {
    /* Product: '<S345>/delta fall limit' incorporates:
     *  Constant: '<S226>/Constant1'
     *  SampleTimeMath: '<S345>/sample time'
     *
     * About '<S345>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Sum_e = 0.01 * outerLoopParams.loRateLimitRollRate_rps2;

    /* Switch: '<S346>/Switch' incorporates:
     *  RelationalOperator: '<S346>/UpperRelop'
     */
    if (rtb_Integrator_b < rtb_Sum_e) {
      rtb_Product2_l = rtb_Sum_e;
    } else {
      rtb_Product2_l = rtb_Integrator_b;
    }

    /* End of Switch: '<S346>/Switch' */
  }

  /* End of Switch: '<S346>/Switch2' */

  /* Sum: '<S345>/Difference Inputs2' incorporates:
   *  Delay: '<S345>/Delay'
   *
   * Block description for '<S345>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_Integrator_b = rtb_Product2_l + rtDW->Delay_DSTATE;

  /* Sum: '<S8>/Sum' incorporates:
   *  DiscreteTransferFcn: '<S428>/Gyro Filter'
   */
  rtb_Product2_l = rtb_Integrator_b - rtb_Cos;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_Filter_g = rtDW->UnitDelay_18_DSTATE;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_Sum_e = rtDW->UnitDelay_19_DSTATE;

  /* Sum: '<S477>/Diff' incorporates:
   *  Inport: '<Root>/sensor_bus'
   *  UnitDelay: '<S477>/UD'
   *
   * Block description for '<S477>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S477>/UD':
   *
   *  Store in Global RAM
   */
  rtb_sqrt = rtU_sensor_bus_e->gpsLLA_na[0] - rtDW->UD_DSTATE[0];
  rtb_MathFunction_idx_0 = rtU_sensor_bus_e->gpsLLA_na[1] - rtDW->UD_DSTATE[1];
  rtb_MathFunction_idx_1 = rtU_sensor_bus_e->gpsLLA_na[2] - rtDW->UD_DSTATE[2];

  /* DotProduct: '<S469>/Dot Product' */
  rtb_Product1_ad = (rtb_sqrt * rtb_sqrt + rtb_MathFunction_idx_0 *
                     rtb_MathFunction_idx_0) + rtb_MathFunction_idx_1 *
    rtb_MathFunction_idx_1;

  /* Logic: '<S469>/Logical Operator' incorporates:
   *  Constant: '<S476>/Constant'
   *  Inport: '<Root>/sensor_bus'
   *  RelationalOperator: '<S476>/Compare'
   */
  rtb_LogicalOperator = ((rtb_Product1_ad >= 1.0E-6) &&
    rtU_sensor_bus_e->gpsFix_b);

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_Product1_ad = rtDW->UnitDelay_17_DSTATE;

  /* Product: '<S470>/Matrix Multiply' incorporates:
   *  Constant: '<S470>/Constant'
   *  Quat2Dcm: '<S470>/Quaternions to  Direction Cosine Matrix'
   */
  rtb_sqrt = 0.0;
  rtb_MathFunction_idx_0 = 0.0;
  rtb_MathFunction_idx_1 = 0.0;
  for (i = 0; i < 3; i++) {
    rtb_Product2_m = navControl.gravityNed_mps2[i];
    rtb_sqrt += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_Product2_m;
    rtb_MathFunction_idx_0 += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
      rtb_Product2_m;
    rtb_MathFunction_idx_1 += rtb_QuaternionstoDirectionCosin[3 * i + 2] *
      rtb_Product2_m;
  }

  rtb_TmpSignalConversionAtSFunct[2] = rtb_MathFunction_idx_1;
  rtb_TmpSignalConversionAtSFunct[1] = rtb_MathFunction_idx_0;
  rtb_TmpSignalConversionAtSFunct[0] = rtb_sqrt;

  /* End of Product: '<S470>/Matrix Multiply' */

  /* Product: '<S409>/Product' */
  rtb_n_m = 0.0;
  rtb_Cos_k = 0.0;
  rtb_Cos_m = 0.0;
  for (i = 0; i < 3; i++) {
    /* Sum: '<S413>/Sum1' incorporates:
     *  Inport: '<Root>/sensor_bus'
     *  Sum: '<S413>/Sum2'
     *  UnitDelay generated from: '<S408>/Unit Delay'
     */
    rtb_sqrt = (rtU_sensor_bus_e->fBdyMeas_mps2[i] - rtDW->UnitDelay_12_DSTATE[i])
      + rtb_TmpSignalConversionAtSFunct[i];
    rtb_accBdyEst_mps2[i] = rtb_sqrt;

    /* DiscreteTransferFcn: '<S409>/Accel Filter' */
    rtb_Product2_m = rtDW->AccelFilter_states[i];
    rtb_MatrixMultiply1_idx_1 = rtb_sqrt - 0.0 * rtb_Product2_m;
    AccelFilter_tmp[i] = rtb_MatrixMultiply1_idx_1;
    rtb_TmpSignalConversionAtSFunct[i] = 0.5 * rtb_MatrixMultiply1_idx_1 + 0.5 *
      rtb_Product2_m;

    /* Gain: '<S409>/Gain' incorporates:
     *  Math: '<S418>/Math Function'
     *  Product: '<S409>/Product'
     *  Quat2Dcm: '<S409>/C+'
     *  Sum: '<S409>/Sum'
     */
    rtb_QuaternionstoDirectionCosin[3 * i] = (rtb_C_l[i] + rtb_MathFunction_k[i])
      * 0.5;
    uIdx = 3 * i + 1;
    rtb_QuaternionstoDirectionCosin[uIdx] = (rtb_C_l[i + 3] +
      rtb_MathFunction_k[i + 3]) * 0.5;
    rtb_QuaternionstoDirectionCos_1 = 3 * i + 2;
    rtb_QuaternionstoDirectionCosin[rtb_QuaternionstoDirectionCos_1] =
      (rtb_C_l[i + 6] + rtb_MathFunction_k[i + 6]) * 0.5;

    /* Product: '<S409>/Product' */
    rtb_Product2_m = rtb_TmpSignalConversionAtSFunct[i];
    rtb_n_m += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_Product2_m;
    rtb_Cos_k += rtb_QuaternionstoDirectionCosin[uIdx] * rtb_Product2_m;
    rtb_Cos_m += rtb_QuaternionstoDirectionCosin[rtb_QuaternionstoDirectionCos_1]
      * rtb_Product2_m;
  }

  /* Sum: '<S409>/Sum4' incorporates:
   *  Gain: '<S409>/Gain3'
   *  Product: '<S409>/Product'
   */
  rtb_MatrixMultiply1_idx_0 = navControl.dt_s * rtb_n_m + rtb_Product1_ad;
  rtb_MatrixMultiply1_idx_1 = navControl.dt_s * rtb_Cos_k + rtb_Filter_g;
  rtb_MatrixMultiply1_idx_2 = navControl.dt_s * rtb_Cos_m + rtb_Sum_e;

  /* If: '<S427>/If1' incorporates:
   *  Constant: '<S458>/Constant'
   *  RelationalOperator: '<S458>/Compare'
   *  Switch: '<S442>/Switch'
   */
  if (rtb_LogicalOperator) {
    /* Outputs for IfAction SubSystem: '<S427>/Vel Complementary Filter' incorporates:
     *  ActionPort: '<S441>/Action Port'
     */
    /* Sum: '<S441>/Sum1' incorporates:
     *  Gain: '<S441>/Gain'
     *  Gain: '<S441>/Gain1'
     *  Inport: '<Root>/sensor_bus'
     */
    rtb_MathFunction_idx_0 = (1.0 - navComp.velGain) *
      rtU_sensor_bus_e->velNedMeas_mps[0] + navComp.velGain *
      rtb_MatrixMultiply1_idx_0;
    rtb_MathFunction_idx_1 = (1.0 - navComp.velGain) *
      rtU_sensor_bus_e->velNedMeas_mps[1] + navComp.velGain *
      rtb_MatrixMultiply1_idx_1;
    rtb_MathFunction_idx_2 = (1.0 - navComp.velGain) *
      rtU_sensor_bus_e->velNedMeas_mps[2] + navComp.velGain *
      rtb_MatrixMultiply1_idx_2;

    /* End of Outputs for SubSystem: '<S427>/Vel Complementary Filter' */

    /* Outputs for IfAction SubSystem: '<S427>/Vel Pass Through' incorporates:
     *  ActionPort: '<S442>/Action Port'
     */
  } else if (rtb_flightMode_enum == IDLE) {
    /* Switch: '<S442>/Switch' incorporates:
     *  Gain: '<S442>/Gain'
     */
    rtb_MathFunction_idx_0 = navComp.velGain * rtb_MatrixMultiply1_idx_0;
    rtb_MathFunction_idx_1 = navComp.velGain * rtb_MatrixMultiply1_idx_1;
    rtb_MathFunction_idx_2 = navComp.velGain * rtb_MatrixMultiply1_idx_2;
  } else {
    /* Switch: '<S442>/Switch' */
    rtb_MathFunction_idx_0 = rtb_MatrixMultiply1_idx_0;
    rtb_MathFunction_idx_1 = rtb_MatrixMultiply1_idx_1;
    rtb_MathFunction_idx_2 = rtb_MatrixMultiply1_idx_2;

    /* End of Outputs for SubSystem: '<S427>/Vel Pass Through' */
  }

  /* End of If: '<S427>/If1' */

  /* DotProduct: '<S465>/Dot Product' */
  rtb_Sum_e = (rtb_MathFunction_idx_0 * rtb_MathFunction_idx_0 +
               rtb_MathFunction_idx_1 * rtb_MathFunction_idx_1) +
    rtb_MathFunction_idx_2 * rtb_MathFunction_idx_2;

  /* Gain: '<S465>/Gain1' incorporates:
   *  Gain: '<S465>/Gain'
   */
  rtb_Sum_e = 0.5 * rtb_Sum_e * navControl.rhoConst_kgpm3;

  /* Delay generated from: '<S426>/Delay2' */
  rtb_Filter_g = rtDW->Delay2_6_DSTATE[0];

  /* Switch: '<S430>/Switch' incorporates:
   *  Constant: '<S430>/Constant4'
   *  Constant: '<S430>/Constant5'
   */
  if (rtb_Filter_g >= 0.0) {
    rtb_Product1_ad = 1.0;
  } else {
    rtb_Product1_ad = -1.0;
  }

  /* End of Switch: '<S430>/Switch' */

  /* Abs: '<S430>/Abs' */
  rtb_Filter_g = fabs(rtb_Filter_g);

  /* Product: '<S430>/Product' incorporates:
   *  Constant: '<S430>/Constant'
   *  MinMax: '<S430>/Max'
   */
  rtDW->Product = rtb_Product1_ad * fmax(1.0E-6, rtb_Filter_g);

  /* S-Function (saeropalt): '<S432>/S-Function' */

  /* S-Function Block: <S432>/S-Function */
  {
    real_T *temp_table = (real_T *) rtDW->SFunction_temp_table;
    real_T *pres_table = (real_T *) rtDW->SFunction_pres_table;
    CalcPAltCOESA( &rtDW->Product, &rtDW->SFunction, temp_table, pres_table, 1);
  }

  /* S-Function (sfix_look1_dyn): '<S77>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S13>/Internal breakpoints'
   *  Constant: '<S9>/Constant4'
   */
  /* Dynamic Look-Up Table Block: '<S77>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Filter_g), &innerLoopParams.fbkGainPitchYawP_na[0],
                       rtb_Sum_e, &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* S-Function (sfix_look1_dyn): '<S74>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S13>/Internal breakpoints'
   *  Constant: '<S9>/Constant6'
   */
  /* Dynamic Look-Up Table Block: '<S74>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Product1_ad),
                       &innerLoopParams.fbkGainPitchYawD_na[0], rtb_Sum_e,
                       &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* S-Function (sfix_look1_dyn): '<S76>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S13>/Internal breakpoints'
   *  Constant: '<S9>/Constant7'
   */
  /* Dynamic Look-Up Table Block: '<S76>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Filter_b), &innerLoopParams.fbkGainPitchYawN_na[0],
                       rtb_Sum_e, &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* S-Function (sfix_look1_dyn): '<S218>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S11>/Constant4'
   *  Constant: '<S154>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S218>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Product1_p1),
                       &innerLoopParams.fbkGainPitchYawP_na[0], rtb_Sum_e,
                       &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* S-Function (sfix_look1_dyn): '<S215>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S11>/Constant6'
   *  Constant: '<S154>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S215>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Filter_e), &innerLoopParams.fbkGainPitchYawD_na[0],
                       rtb_Sum_e, &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* S-Function (sfix_look1_dyn): '<S217>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S11>/Constant7'
   *  Constant: '<S154>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S217>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_k),
                       &innerLoopParams.fbkGainPitchYawN_na[0], rtb_Sum_e,
                       &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* S-Function (sfix_look1_dyn): '<S148>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S10>/Constant4'
   *  Constant: '<S84>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S148>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Integrator_g), &innerLoopParams.fbkGainRollP_na[0],
                       rtb_Sum_e, &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* Product: '<S128>/PProd Out' */
  rtb_Product2_m = rtb_Product2_l * rtb_Integrator_g;

  /* DiscreteIntegrator: '<S123>/Integrator' */
  rtb_Integrator_g = rtDW->Integrator_DSTATE_b;

  /* S-Function (sfix_look1_dyn): '<S145>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S10>/Constant6'
   *  Constant: '<S84>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S145>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Filter_c), &innerLoopParams.fbkGainRollD_na[0],
                       rtb_Sum_e, &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* Product: '<S116>/DProd Out' */
  rtb_sqrt = rtb_Product2_l * rtb_Filter_c;

  /* DiscreteIntegrator: '<S118>/Filter' */
  rtb_Filter_c = rtDW->Filter_DSTATE_p;

  /* S-Function (sfix_look1_dyn): '<S147>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S84>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S147>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Integrator_fe), &innerLoopParams.fbkGainRollN_na[0],
                       rtb_Sum_e, &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* Product: '<S126>/NProd Out' incorporates:
   *  Sum: '<S118>/SumD'
   */
  rtb_Filter_c = (rtb_sqrt - rtb_Filter_c) * rtb_Integrator_fe;

  /* Sum: '<S132>/Sum' */
  rtb_Integrator_fe = (rtb_Product2_m + rtb_Integrator_g) + rtb_Filter_c;

  /* Product: '<S83>/Product1' incorporates:
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_o = rtb_Integrator_fe * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Gain: '<S85>/Gain' */
  rtb_Gain_a = 0.5 * rtb_Product1_o;

  /* Switch: '<S152>/Switch2' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant3'
   *  RelationalOperator: '<S152>/LowerRelop1'
   *  RelationalOperator: '<S152>/UpperRelop'
   *  Switch: '<S152>/Switch'
   */
  if (rtb_Gain_a > innerLoopParams.upLimitRoll_deg) {
    rtb_Switch2_f = innerLoopParams.upLimitRoll_deg;
  } else if (rtb_Gain_a < innerLoopParams.loLimitRoll_deg) {
    /* Switch: '<S152>/Switch' incorporates:
     *  Constant: '<S10>/Constant3'
     */
    rtb_Switch2_f = innerLoopParams.loLimitRoll_deg;
  } else {
    rtb_Switch2_f = rtb_Gain_a;
  }

  /* End of Switch: '<S152>/Switch2' */

  /* Delay: '<S150>/Delay' */
  if (rtDW->icLoad_k) {
    rtDW->Delay_DSTATE_p = rtb_Switch2_f;
  }

  /* Product: '<S150>/delta rise limit' incorporates:
   *  Constant: '<S10>/Constant'
   *  SampleTimeMath: '<S150>/sample time'
   *
   * About '<S150>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Integrator_fe = innerLoopParams.upRateLimitRoll_dps * 0.01;

  /* Sum: '<S150>/Difference Inputs1' incorporates:
   *  Delay: '<S150>/Delay'
   *
   * Block description for '<S150>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Integrator_g = rtb_Switch2_f - rtDW->Delay_DSTATE_p;

  /* Switch: '<S151>/Switch2' incorporates:
   *  RelationalOperator: '<S151>/LowerRelop1'
   */
  if (!(rtb_Integrator_g > rtb_Integrator_fe)) {
    /* Product: '<S150>/delta fall limit' incorporates:
     *  Constant: '<S10>/Constant1'
     *  SampleTimeMath: '<S150>/sample time'
     *
     * About '<S150>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Integrator_fe = 0.01 * innerLoopParams.loRateLimitRoll_dps;

    /* Switch: '<S151>/Switch' incorporates:
     *  RelationalOperator: '<S151>/UpperRelop'
     */
    if (!(rtb_Integrator_g < rtb_Integrator_fe)) {
      rtb_Integrator_fe = rtb_Integrator_g;
    }

    /* End of Switch: '<S151>/Switch' */
  }

  /* End of Switch: '<S151>/Switch2' */

  /* Sum: '<S150>/Difference Inputs2' incorporates:
   *  Delay: '<S150>/Delay'
   *
   * Block description for '<S150>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_Integrator_g = rtb_Integrator_fe + rtDW->Delay_DSTATE_p;

  /* Trigonometry: '<S224>/Cos' incorporates:
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   */
  rtb_Integrator_fe = cos(rtb_Switch_ft_idx_3);

  /* Sum: '<S224>/Sum1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   */
  rtb_Integrator_i = guidanceParams.thetaCmd_rad - rtb_Switch_ft_idx_1;

  /* Trigonometry: '<S224>/Sin' incorporates:
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   */
  rtb_Sum1_j = sin(rtb_Switch_ft_idx_3);

  /* Sum: '<S224>/Sum' incorporates:
   *  Constant: '<S2>/Constant2'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   */
  rtb_Sum3 = guidanceParams.psiCmd_rad - rtb_Switch_ft_idx_2;

  /* Sum: '<S224>/Sum4' incorporates:
   *  Product: '<S224>/Product'
   *  Product: '<S224>/Product1'
   */
  rtb_Sum4_a = rtb_Sum1_j * rtb_Sum_kk_idx_3 * rtb_Sum3 + rtb_Integrator_fe *
    rtb_Integrator_i;

  /* Product: '<S269>/NProd Out' incorporates:
   *  Constant: '<S225>/Constant4'
   *  DiscreteIntegrator: '<S261>/Filter'
   *  Product: '<S259>/DProd Out'
   *  Sum: '<S261>/SumD'
   */
  rtb_Product2_m = (rtb_Sum4_a * outerLoopParams.pitchYawGains[2] -
                    rtDW->Filter_DSTATE_n) * outerLoopParams.pitchYawGains[3];

  /* Product: '<S228>/Product1' incorporates:
   *  Constant: '<S225>/Constant4'
   *  DiscreteIntegrator: '<S266>/Integrator'
   *  Product: '<S271>/PProd Out'
   *  Sum: '<S275>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_j3 = ((rtb_Sum4_a * outerLoopParams.pitchYawGains[0] +
                      rtDW->Integrator_DSTATE_g) + rtb_Product2_m) * (real_T)
    rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S287>/Switch2' incorporates:
   *  Constant: '<S225>/Constant2'
   *  Constant: '<S225>/Constant3'
   *  RelationalOperator: '<S287>/LowerRelop1'
   *  RelationalOperator: '<S287>/UpperRelop'
   *  Switch: '<S287>/Switch'
   */
  if (rtb_Product1_j3 > outerLoopParams.upLimitPitchYawRate_rps) {
    rtb_Switch2_m = outerLoopParams.upLimitPitchYawRate_rps;
  } else if (rtb_Product1_j3 < outerLoopParams.loLimitPitchYawRate_rps) {
    /* Switch: '<S287>/Switch' incorporates:
     *  Constant: '<S225>/Constant3'
     */
    rtb_Switch2_m = outerLoopParams.loLimitPitchYawRate_rps;
  } else {
    rtb_Switch2_m = rtb_Product1_j3;
  }

  /* End of Switch: '<S287>/Switch2' */

  /* Delay: '<S285>/Delay' */
  if (rtDW->icLoad_a) {
    rtDW->Delay_DSTATE_c = rtb_Switch2_m;
  }

  /* Product: '<S285>/delta rise limit' incorporates:
   *  Constant: '<S225>/Constant'
   *  Product: '<S405>/delta rise limit'
   *  SampleTimeMath: '<S285>/sample time'
   *
   * About '<S285>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Sum_kk_idx_1 = outerLoopParams.upRateLimitPitchYawRate_rps2 * 0.01;
  rtb_sqrt = rtb_Sum_kk_idx_1;

  /* Sum: '<S285>/Difference Inputs1' incorporates:
   *  Delay: '<S285>/Delay'
   *
   * Block description for '<S285>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_l = rtb_Switch2_m - rtDW->Delay_DSTATE_c;

  /* Switch: '<S286>/Switch2' incorporates:
   *  Product: '<S285>/delta rise limit'
   *  RelationalOperator: '<S286>/LowerRelop1'
   */
  if (!(rtb_UkYk1_l > rtb_Sum_kk_idx_1)) {
    /* Product: '<S285>/delta fall limit' incorporates:
     *  Constant: '<S225>/Constant1'
     *  SampleTimeMath: '<S285>/sample time'
     *
     * About '<S285>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_sqrt = 0.01 * outerLoopParams.loRateLimitPitchYawRate_rps2;

    /* Switch: '<S286>/Switch' incorporates:
     *  RelationalOperator: '<S286>/UpperRelop'
     */
    if (!(rtb_UkYk1_l < rtb_sqrt)) {
      rtb_sqrt = rtb_UkYk1_l;
    }

    /* End of Switch: '<S286>/Switch' */
  }

  /* End of Switch: '<S286>/Switch2' */

  /* Sum: '<S285>/Difference Inputs2' incorporates:
   *  Delay: '<S285>/Delay'
   *
   * Block description for '<S285>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_UkYk1_l = rtb_sqrt + rtDW->Delay_DSTATE_c;

  /* Sum: '<S8>/Sum2' incorporates:
   *  DiscreteTransferFcn: '<S428>/Gyro Filter'
   */
  rtb_sqrt = rtb_UkYk1_l - rtb_Cos_e;

  /* Product: '<S57>/PProd Out' */
  rtb_PProdOut_b = rtb_sqrt * rtb_Filter_g;

  /* DiscreteIntegrator: '<S47>/Filter' */
  rtb_Filter_g = rtDW->Filter_DSTATE_l;

  /* Product: '<S55>/NProd Out' incorporates:
   *  Product: '<S45>/DProd Out'
   *  Sum: '<S47>/SumD'
   */
  rtb_Filter_g = (rtb_sqrt * rtb_Product1_ad - rtb_Filter_g) * rtb_Filter_b;

  /* Sum: '<S61>/Sum' incorporates:
   *  DiscreteIntegrator: '<S52>/Integrator'
   */
  rtb_Filter_b = (rtb_PProdOut_b + rtDW->Integrator_DSTATE_p) + rtb_Filter_g;

  /* Product: '<S12>/Product1' incorporates:
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_ad = rtb_Filter_b * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S14>/Divide' incorporates:
   *  Gain: '<S14>/Gain'
   */
  rtb_Divide = -6756.0 * rtb_Product1_ad / 50000.0;

  /* Switch: '<S82>/Switch2' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  RelationalOperator: '<S82>/LowerRelop1'
   *  RelationalOperator: '<S82>/UpperRelop'
   *  Switch: '<S82>/Switch'
   */
  if (rtb_Divide > innerLoopParams.upLimitPitchYaw_deg) {
    rtb_Switch2_j = innerLoopParams.upLimitPitchYaw_deg;
  } else if (rtb_Divide < innerLoopParams.loLimitPitchYaw_deg) {
    /* Switch: '<S82>/Switch' incorporates:
     *  Constant: '<S9>/Constant3'
     */
    rtb_Switch2_j = innerLoopParams.loLimitPitchYaw_deg;
  } else {
    rtb_Switch2_j = rtb_Divide;
  }

  /* End of Switch: '<S82>/Switch2' */

  /* Delay: '<S80>/Delay' */
  if (rtDW->icLoad_f) {
    rtDW->Delay_DSTATE_f = rtb_Switch2_j;
  }

  /* Product: '<S80>/delta rise limit' incorporates:
   *  Constant: '<S9>/Constant'
   *  Product: '<S221>/delta rise limit'
   *  SampleTimeMath: '<S80>/sample time'
   *
   * About '<S80>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Sum_kk_idx_0 = innerLoopParams.upRateLimitPitchYaw_dps * 0.01;
  rtb_Filter_b = rtb_Sum_kk_idx_0;

  /* Sum: '<S80>/Difference Inputs1' incorporates:
   *  Delay: '<S80>/Delay'
   *
   * Block description for '<S80>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_PProdOut_b = rtb_Switch2_j - rtDW->Delay_DSTATE_f;

  /* Switch: '<S81>/Switch2' incorporates:
   *  RelationalOperator: '<S81>/LowerRelop1'
   */
  if (!(rtb_PProdOut_b > rtb_Filter_b)) {
    /* Product: '<S80>/delta fall limit' incorporates:
     *  Constant: '<S9>/Constant1'
     *  SampleTimeMath: '<S80>/sample time'
     *
     * About '<S80>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Filter_b = 0.01 * innerLoopParams.loRateLimitPitchYaw_dps;

    /* Switch: '<S81>/Switch' incorporates:
     *  RelationalOperator: '<S81>/UpperRelop'
     */
    if (!(rtb_PProdOut_b < rtb_Filter_b)) {
      rtb_Filter_b = rtb_PProdOut_b;
    }

    /* End of Switch: '<S81>/Switch' */
  }

  /* End of Switch: '<S81>/Switch2' */

  /* Sum: '<S80>/Difference Inputs2' incorporates:
   *  Delay: '<S80>/Delay'
   *
   * Block description for '<S80>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_PProdOut_b = rtb_Filter_b + rtDW->Delay_DSTATE_f;

  /* Sum: '<S224>/Sum3' incorporates:
   *  Product: '<S224>/Product2'
   *  Product: '<S224>/Product3'
   *  UnaryMinus: '<S224>/Unary Minus'
   */
  rtb_Sum3 = rtb_Integrator_fe * rtb_Sum_kk_idx_3 * rtb_Sum3 + -rtb_Sum1_j *
    rtb_Integrator_i;

  /* Product: '<S379>/DProd Out' incorporates:
   *  Constant: '<S227>/Constant4'
   */
  rtb_Integrator_fe = rtb_Sum3 * outerLoopParams.pitchYawGains[2];

  /* DiscreteIntegrator: '<S381>/Filter' */
  rtb_Filter_b = rtDW->Filter_DSTATE_c;

  /* Sum: '<S381>/SumD' */
  rtb_Integrator_fe -= rtb_Filter_b;

  /* Product: '<S389>/NProd Out' incorporates:
   *  Constant: '<S227>/Constant4'
   */
  rtb_Filter_b = rtb_Integrator_fe * outerLoopParams.pitchYawGains[3];

  /* Product: '<S348>/Product1' incorporates:
   *  Constant: '<S227>/Constant4'
   *  DiscreteIntegrator: '<S386>/Integrator'
   *  Product: '<S391>/PProd Out'
   *  Sum: '<S395>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_j = ((rtb_Sum3 * outerLoopParams.pitchYawGains[0] +
                     rtDW->Integrator_DSTATE_l) + rtb_Filter_b) * (real_T)
    rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S407>/Switch2' incorporates:
   *  Constant: '<S227>/Constant2'
   *  Constant: '<S227>/Constant3'
   *  RelationalOperator: '<S407>/LowerRelop1'
   *  RelationalOperator: '<S407>/UpperRelop'
   *  Switch: '<S407>/Switch'
   */
  if (rtb_Product1_j > outerLoopParams.upLimitPitchYawRate_rps) {
    rtb_Switch2_d = outerLoopParams.upLimitPitchYawRate_rps;
  } else if (rtb_Product1_j < outerLoopParams.loLimitPitchYawRate_rps) {
    /* Switch: '<S407>/Switch' incorporates:
     *  Constant: '<S227>/Constant3'
     */
    rtb_Switch2_d = outerLoopParams.loLimitPitchYawRate_rps;
  } else {
    rtb_Switch2_d = rtb_Product1_j;
  }

  /* End of Switch: '<S407>/Switch2' */

  /* Delay: '<S405>/Delay' */
  if (rtDW->icLoad_c) {
    rtDW->Delay_DSTATE_h = rtb_Switch2_d;
  }

  /* Product: '<S405>/delta rise limit' */
  rtb_Sum1_j = rtb_Sum_kk_idx_1;

  /* Sum: '<S405>/Difference Inputs1' incorporates:
   *  Delay: '<S405>/Delay'
   *
   * Block description for '<S405>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Integrator_fe = rtb_Switch2_d - rtDW->Delay_DSTATE_h;

  /* Switch: '<S406>/Switch2' incorporates:
   *  RelationalOperator: '<S406>/LowerRelop1'
   */
  if (!(rtb_Integrator_fe > rtb_Sum_kk_idx_1)) {
    /* Product: '<S405>/delta fall limit' incorporates:
     *  Constant: '<S227>/Constant1'
     *  SampleTimeMath: '<S405>/sample time'
     *
     * About '<S405>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Integrator_i = 0.01 * outerLoopParams.loRateLimitPitchYawRate_rps2;

    /* Switch: '<S406>/Switch' incorporates:
     *  RelationalOperator: '<S406>/UpperRelop'
     */
    if (rtb_Integrator_fe < rtb_Integrator_i) {
      rtb_Sum1_j = rtb_Integrator_i;
    } else {
      rtb_Sum1_j = rtb_Integrator_fe;
    }

    /* End of Switch: '<S406>/Switch' */
  }

  /* End of Switch: '<S406>/Switch2' */

  /* Sum: '<S405>/Difference Inputs2' incorporates:
   *  Delay: '<S405>/Delay'
   *
   * Block description for '<S405>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_Integrator_i = rtb_Sum1_j + rtDW->Delay_DSTATE_h;

  /* Sum: '<S8>/Sum1' incorporates:
   *  DiscreteTransferFcn: '<S428>/Gyro Filter'
   */
  rtb_Sum1_j = rtb_Integrator_i - rtb_Cos_l;

  /* DiscreteIntegrator: '<S193>/Integrator' */
  rtb_Integrator_fe = rtDW->Integrator_DSTATE_e;

  /* Product: '<S186>/DProd Out' */
  rtb_DProdOut_m = rtb_Sum1_j * rtb_Filter_e;

  /* DiscreteIntegrator: '<S188>/Filter' */
  rtb_Filter_e = rtDW->Filter_DSTATE_g;

  /* Product: '<S196>/NProd Out' incorporates:
   *  Sum: '<S188>/SumD'
   */
  rtb_Filter_e = (rtb_DProdOut_m - rtb_Filter_e) * rtb_GainDynamicLookup_k;

  /* Sum: '<S202>/Sum' incorporates:
   *  Product: '<S198>/PProd Out'
   */
  rtb_GainDynamicLookup_k = (rtb_Sum1_j * rtb_Product1_p1 + rtb_Integrator_fe) +
    rtb_Filter_e;

  /* Product: '<S153>/Product1' incorporates:
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_p1 = rtb_GainDynamicLookup_k * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S155>/Divide' incorporates:
   *  Gain: '<S155>/Gain'
   */
  rtb_Divide_l = -6756.0 * rtb_Product1_p1 / 50000.0;

  /* Switch: '<S223>/Switch2' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Constant: '<S11>/Constant3'
   *  RelationalOperator: '<S223>/LowerRelop1'
   *  RelationalOperator: '<S223>/UpperRelop'
   *  Switch: '<S223>/Switch'
   */
  if (rtb_Divide_l > innerLoopParams.upLimitPitchYaw_deg) {
    rtb_Switch2_b = innerLoopParams.upLimitPitchYaw_deg;
  } else if (rtb_Divide_l < innerLoopParams.loLimitPitchYaw_deg) {
    /* Switch: '<S223>/Switch' incorporates:
     *  Constant: '<S11>/Constant3'
     */
    rtb_Switch2_b = innerLoopParams.loLimitPitchYaw_deg;
  } else {
    rtb_Switch2_b = rtb_Divide_l;
  }

  /* End of Switch: '<S223>/Switch2' */

  /* Delay: '<S221>/Delay' */
  if (rtDW->icLoad_d) {
    rtDW->Delay_DSTATE_e = rtb_Switch2_b;
  }

  /* Product: '<S221>/delta rise limit' */
  rtb_GainDynamicLookup_k = rtb_Sum_kk_idx_0;

  /* Sum: '<S221>/Difference Inputs1' incorporates:
   *  Delay: '<S221>/Delay'
   *
   * Block description for '<S221>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Integrator_fe = rtb_Switch2_b - rtDW->Delay_DSTATE_e;

  /* Switch: '<S222>/Switch2' incorporates:
   *  RelationalOperator: '<S222>/LowerRelop1'
   */
  if (!(rtb_Integrator_fe > rtb_GainDynamicLookup_k)) {
    /* Product: '<S221>/delta fall limit' incorporates:
     *  Constant: '<S11>/Constant1'
     *  SampleTimeMath: '<S221>/sample time'
     *
     * About '<S221>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_GainDynamicLookup_k = 0.01 * innerLoopParams.loRateLimitPitchYaw_dps;

    /* Switch: '<S222>/Switch' incorporates:
     *  RelationalOperator: '<S222>/UpperRelop'
     */
    if (!(rtb_Integrator_fe < rtb_GainDynamicLookup_k)) {
      rtb_GainDynamicLookup_k = rtb_Integrator_fe;
    }

    /* End of Switch: '<S222>/Switch' */
  }

  /* End of Switch: '<S222>/Switch2' */

  /* Sum: '<S221>/Difference Inputs2' incorporates:
   *  Delay: '<S221>/Delay'
   *
   * Block description for '<S221>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_Integrator_fe = rtb_GainDynamicLookup_k + rtDW->Delay_DSTATE_e;

  /* UnaryMinus: '<S5>/Unary Minus2' */
  rtb_GainDynamicLookup_k = -rtb_Integrator_fe;

  /* UnaryMinus: '<S5>/Unary Minus' */
  rtb_GainDynamicLookup_b = -rtb_PProdOut_b;

  /* Sum: '<S5>/Sum' incorporates:
   *  Product: '<S5>/Product'
   */
  rtb_Sum_kk_idx_0 = rtb_PProdOut_b + rtb_Integrator_g;
  rtb_Sum_kk_idx_1 = rtb_GainDynamicLookup_k - rtb_Integrator_g;
  rtb_Sum_kk_idx_2 = rtb_GainDynamicLookup_b + rtb_Integrator_g;
  rtb_Sum_kk_idx_3 = rtb_Integrator_fe - rtb_Integrator_g;

  /* Outport: '<Root>/control_deg' */
  rtY_control_deg[0] = rtb_Sum_kk_idx_0;
  rtY_control_deg[1] = rtb_Sum_kk_idx_1;
  rtY_control_deg[2] = rtb_Sum_kk_idx_2;
  rtY_control_deg[3] = rtb_Sum_kk_idx_3;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_GainDynamicLookup_b = rtDW->UnitDelay_20_DSTATE;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_GainDynamicLookup_k = rtDW->UnitDelay_21_DSTATE;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_DProdOut_m = rtDW->UnitDelay_22_DSTATE;

  /* Sum: '<S409>/Sum5' incorporates:
   *  Gain: '<S409>/Gain4'
   *  Gain: '<S409>/Gain5'
   *  Product: '<S409>/Product'
   */
  rtb_TmpSignalConversionAtSFunct[0] = (navControl.dt_s *
    rtb_MatrixMultiply1_idx_0 + rtb_GainDynamicLookup_b) - 5.0E-5 * rtb_n_m;
  rtb_TmpSignalConversionAtSFunct[1] = (navControl.dt_s *
    rtb_MatrixMultiply1_idx_1 + rtb_GainDynamicLookup_k) - 5.0E-5 * rtb_Cos_k;
  rtb_TmpSignalConversionAtSFunct[2] = (navControl.dt_s *
    rtb_MatrixMultiply1_idx_2 + rtb_DProdOut_m) - 5.0E-5 * rtb_Cos_m;

  /* Gain: '<S474>/Gain1' incorporates:
   *  Inport: '<Root>/sensor_bus'
   *  Sum: '<S468>/Sum'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_DProdOut_m = (rtU_sensor_bus_e->gpsLLA_na[1] - rtDW->UnitDelay_15_DSTATE[1])
    * 0.017453292519943295;

  /* Gain: '<S475>/Gain1' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_GainDynamicLookup_b = 0.017453292519943295 * rtDW->UnitDelay_15_DSTATE[0];

  /* Trigonometry: '<S468>/Cos' */
  rtb_MatrixMultiply1_idx_1 = cos(rtb_GainDynamicLookup_b);

  /* Sum: '<S468>/Sum2' incorporates:
   *  Constant: '<S468>/Constant2'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_GainDynamicLookup_b = gpsConversion.N0_m + rtDW->UnitDelay_15_DSTATE[2];

  /* Product: '<S468>/Product1' */
  rtb_Cos_k = rtb_DProdOut_m * rtb_MatrixMultiply1_idx_1 *
    rtb_GainDynamicLookup_b;

  /* Gain: '<S473>/Gain1' incorporates:
   *  Inport: '<Root>/sensor_bus'
   *  Sum: '<S468>/Sum'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_DProdOut_m = (rtU_sensor_bus_e->gpsLLA_na[0] - rtDW->UnitDelay_15_DSTATE[0])
    * 0.017453292519943295;

  /* Sum: '<S468>/Sum1' incorporates:
   *  Constant: '<S468>/Constant'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_GainDynamicLookup_b = gpsConversion.M0_m + rtDW->UnitDelay_15_DSTATE[2];

  /* Product: '<S468>/Product' */
  rtb_n_m = rtb_DProdOut_m * rtb_GainDynamicLookup_b;

  /* UnaryMinus: '<S468>/Unary Minus' incorporates:
   *  Inport: '<Root>/sensor_bus'
   *  Sum: '<S468>/Sum'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_DProdOut_m = -(rtU_sensor_bus_e->gpsLLA_na[2] - rtDW->UnitDelay_15_DSTATE
                     [2]);

  /* If: '<S427>/If2' incorporates:
   *  Constant: '<S457>/Constant'
   *  RelationalOperator: '<S457>/Compare'
   *  Switch: '<S439>/Switch'
   */
  if (rtb_LogicalOperator) {
    /* Outputs for IfAction SubSystem: '<S427>/Pos Complementary Filter w//GPS' incorporates:
     *  ActionPort: '<S440>/Action Port'
     */
    /* Sum: '<S440>/Sum1' incorporates:
     *  Gain: '<S440>/Gain'
     *  Gain: '<S440>/Gain1'
     *  UnaryMinus: '<S413>/Unary Minus'
     */
    rtb_gyroFilt_rps[0] = (1.0 - navComp.posGain) * rtb_n_m + navComp.posGain *
      rtb_TmpSignalConversionAtSFunct[0];
    rtb_gyroFilt_rps[1] = (1.0 - navComp.posGain) * rtb_Cos_k + navComp.posGain *
      rtb_TmpSignalConversionAtSFunct[1];
    rtb_gyroFilt_rps[2] = (1.0 - navComp.posGain) * rtb_DProdOut_m +
      navComp.posGain * rtb_TmpSignalConversionAtSFunct[2];

    /* End of Outputs for SubSystem: '<S427>/Pos Complementary Filter w//GPS' */

    /* Outputs for IfAction SubSystem: '<S427>/Pos Complementary Filter no GPS' incorporates:
     *  ActionPort: '<S439>/Action Port'
     */
  } else if (rtb_flightMode_enum == IDLE) {
    /* Switch: '<S439>/Switch' incorporates:
     *  Gain: '<S439>/Gain'
     *  Gain: '<S439>/Gain1'
     *  Gain: '<S439>/Gain2'
     *  Sum: '<S439>/Sum1'
     */
    rtb_gyroFilt_rps[0] = navComp.posGain * rtb_TmpSignalConversionAtSFunct[0];
    rtb_gyroFilt_rps[1] = navComp.posGain * rtb_TmpSignalConversionAtSFunct[1];
    rtb_gyroFilt_rps[2] = ((1.0 - navComp.posGain) *
      rtb_TmpSignalConversionAtSFunct[2] + navComp.posGain *
      rtb_TmpSignalConversionAtSFunct[2]) * navComp.posGain;
  } else {
    /* Switch: '<S439>/Switch' incorporates:
     *  Gain: '<S439>/Gain'
     *  Gain: '<S439>/Gain1'
     *  Sum: '<S439>/Sum1'
     */
    rtb_gyroFilt_rps[0] = rtb_TmpSignalConversionAtSFunct[0];
    rtb_gyroFilt_rps[1] = rtb_TmpSignalConversionAtSFunct[1];
    rtb_gyroFilt_rps[2] = (1.0 - navComp.posGain) *
      rtb_TmpSignalConversionAtSFunct[2] + navComp.posGain *
      rtb_TmpSignalConversionAtSFunct[2];

    /* End of Outputs for SubSystem: '<S427>/Pos Complementary Filter no GPS' */
  }

  /* End of If: '<S427>/If2' */

  /* DiscreteTransferFcn: '<S428>/Accel Filter' */
  rtb_n_m = rtb_accBdyEst_mps2[0] - 0.0 * rtDW->AccelFilter_states_k[0];
  rtb_Cos_k = rtb_accBdyEst_mps2[1] - 0.0 * rtDW->AccelFilter_states_k[1];
  rtb_Cos_m = rtb_accBdyEst_mps2[2] - 0.0 * rtDW->AccelFilter_states_k[2];

  /* RelationalOperator: '<S431>/Compare' incorporates:
   *  Constant: '<S431>/Constant'
   */
  rtb_Compare_p = (rtb_flightMode_enum == IDLE);

  /* Switch: '<S426>/Switch1' */
  if (rtb_Compare_p) {
    /* Product: '<S433>/Matrix Multiply' incorporates:
     *  Constant: '<S433>/Constant'
     */
    rtb_MatrixMultiply1_idx_1 = navControl.gravityNed_mps2[1];
    rtb_MatrixMultiply1_idx_2 = navControl.gravityNed_mps2[0];
    rtb_MatrixMultiply1_idx_0 = navControl.gravityNed_mps2[2];

    /* Switch: '<S426>/Switch1' incorporates:
     *  Constant: '<S433>/Constant'
     *  Delay generated from: '<S426>/Delay2'
     *  Product: '<S433>/Matrix Multiply'
     *  Quat2Dcm: '<S433>/C-'
     *  Sum: '<S426>/Sum'
     */
    for (i = 0; i < 3; i++) {
      Switch1[i] = ((rtb_C[i + 3] * rtb_MatrixMultiply1_idx_1 + rtb_C[i] *
                     rtb_MatrixMultiply1_idx_2) + rtb_C[i + 6] *
                    rtb_MatrixMultiply1_idx_0) + rtDW->Delay2_3_DSTATE[i];
    }
  } else {
    /* Switch: '<S426>/Switch1' incorporates:
     *  UnitDelay: '<S426>/Unit Delay1'
     */
    Switch1[0] = rtDW->UnitDelay1_DSTATE[0];
    Switch1[1] = rtDW->UnitDelay1_DSTATE[1];
    Switch1[2] = rtDW->UnitDelay1_DSTATE[2];
  }

  /* End of Switch: '<S426>/Switch1' */

  /* DiscreteFir: '<S426>/Discrete FIR Filter1' incorporates:
   *  DiscreteFir: '<S426>/Discrete FIR Filter'
   */
  Switch3_idx_2 = 1.0 / navControl.biasWindowSamples;
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_2 * Switch1[0];
  for (i = rtDW->DiscreteFIRFilter1_circBuf; i < 999; i++) {
    rtb_MatrixMultiply1_idx_1 += Switch3_idx_2 * rtDW->
      DiscreteFIRFilter1_states[i];
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter1_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += Switch3_idx_2 * rtDW->
      DiscreteFIRFilter1_states[i];
  }

  rtb_accelBias_mps2[0] = rtb_MatrixMultiply1_idx_1;

  /* Switch: '<S426>/Switch' */
  if (rtb_Compare_p) {
    /* Switch: '<S426>/Switch' incorporates:
     *  Delay generated from: '<S426>/Delay2'
     */
    rtb_MatrixMultiply1_idx_2 = rtDW->Delay2_4_DSTATE[0];
  } else {
    /* Switch: '<S426>/Switch' incorporates:
     *  UnitDelay: '<S426>/Unit Delay'
     */
    rtb_MatrixMultiply1_idx_2 = rtDW->UnitDelay_DSTATE[0];
  }

  /* DiscreteFir: '<S426>/Discrete FIR Filter1' */
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_2 * Switch1[1];
  for (i = rtDW->DiscreteFIRFilter1_circBuf; i < 999; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter1_states[i + 999] *
      Switch3_idx_2;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter1_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter1_states[i + 999] *
      Switch3_idx_2;
  }

  rtb_accelBias_mps2[1] = rtb_MatrixMultiply1_idx_1;

  /* Switch: '<S426>/Switch' */
  if (rtb_Compare_p) {
    /* Switch: '<S426>/Switch' incorporates:
     *  Delay generated from: '<S426>/Delay2'
     */
    rtb_MatrixMultiply1_idx_0 = rtDW->Delay2_4_DSTATE[1];
  } else {
    /* Switch: '<S426>/Switch' incorporates:
     *  UnitDelay: '<S426>/Unit Delay'
     */
    rtb_MatrixMultiply1_idx_0 = rtDW->UnitDelay_DSTATE[1];
  }

  /* DiscreteFir: '<S426>/Discrete FIR Filter1' */
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_2 * Switch1[2];
  for (i = rtDW->DiscreteFIRFilter1_circBuf; i < 999; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter1_states[i + 1998] *
      Switch3_idx_2;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter1_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter1_states[i + 1998] *
      Switch3_idx_2;
  }

  rtb_accelBias_mps2[2] = rtb_MatrixMultiply1_idx_1;

  /* Switch: '<S426>/Switch' */
  if (rtb_Compare_p) {
    /* Switch: '<S426>/Switch' incorporates:
     *  Delay generated from: '<S426>/Delay2'
     */
    Switch_idx_2 = rtDW->Delay2_4_DSTATE[2];
  } else {
    /* Switch: '<S426>/Switch' incorporates:
     *  UnitDelay: '<S426>/Unit Delay'
     */
    Switch_idx_2 = rtDW->UnitDelay_DSTATE[2];
  }

  /* Logic: '<S426>/Logical Operator' incorporates:
   *  Delay generated from: '<S426>/Delay1'
   */
  rtb_LogicalOperator_b = (rtb_Compare_p || rtDW->Delay1_6_DSTATE[0]);

  /* DiscreteFir: '<S426>/Discrete FIR Filter' */
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_2 * rtb_MatrixMultiply1_idx_2;
  for (i = rtDW->DiscreteFIRFilter_circBuf; i < 999; i++) {
    rtb_MatrixMultiply1_idx_1 += Switch3_idx_2 * rtDW->
      DiscreteFIRFilter_states[i];
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += Switch3_idx_2 * rtDW->
      DiscreteFIRFilter_states[i];
  }

  rtb_gyroBias_rps[0] = rtb_MatrixMultiply1_idx_1;

  /* Switch: '<S426>/Switch3' */
  if (rtb_LogicalOperator_b) {
    /* Switch: '<S426>/Switch3' incorporates:
     *  Delay generated from: '<S426>/Delay2'
     */
    Switch3_idx_0 = rtDW->Delay2_8_DSTATE[0];
  } else {
    /* Switch: '<S426>/Switch3' incorporates:
     *  UnitDelay: '<S426>/Unit Delay3'
     */
    Switch3_idx_0 = rtDW->UnitDelay3_DSTATE[0];
  }

  /* DiscreteFir: '<S426>/Discrete FIR Filter' */
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_2 * rtb_MatrixMultiply1_idx_0;
  for (i = rtDW->DiscreteFIRFilter_circBuf; i < 999; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter_states[i + 999] *
      Switch3_idx_2;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter_states[i + 999] *
      Switch3_idx_2;
  }

  rtb_gyroBias_rps[1] = rtb_MatrixMultiply1_idx_1;

  /* Switch: '<S426>/Switch3' */
  if (rtb_LogicalOperator_b) {
    /* Switch: '<S426>/Switch3' incorporates:
     *  Delay generated from: '<S426>/Delay2'
     */
    Switch3_idx_1 = rtDW->Delay2_8_DSTATE[1];
  } else {
    /* Switch: '<S426>/Switch3' incorporates:
     *  UnitDelay: '<S426>/Unit Delay3'
     */
    Switch3_idx_1 = rtDW->UnitDelay3_DSTATE[1];
  }

  /* DiscreteFir: '<S426>/Discrete FIR Filter' */
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_2 * Switch_idx_2;
  for (i = rtDW->DiscreteFIRFilter_circBuf; i < 999; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter_states[i + 1998] *
      Switch3_idx_2;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter_states[i + 1998] *
      Switch3_idx_2;
  }

  rtb_gyroBias_rps[2] = rtb_MatrixMultiply1_idx_1;

  /* Switch: '<S426>/Switch3' */
  if (rtb_LogicalOperator_b) {
    /* Switch: '<S426>/Switch3' incorporates:
     *  Delay generated from: '<S426>/Delay2'
     */
    Switch3_idx_2 = rtDW->Delay2_8_DSTATE[2];
  } else {
    /* Switch: '<S426>/Switch3' incorporates:
     *  UnitDelay: '<S426>/Unit Delay3'
     */
    Switch3_idx_2 = rtDW->UnitDelay3_DSTATE[2];
  }

  /* DiscreteFir: '<S426>/Discrete FIR Filter3' */
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_0 * 0.01;
  for (i = rtDW->DiscreteFIRFilter3_circBuf; i < 99; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter3_states[i] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter3_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter3_states[i] * 0.01;
  }

  rtb_llaBias_na_idx_0 = rtb_MatrixMultiply1_idx_1;
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_1 * 0.01;
  for (i = rtDW->DiscreteFIRFilter3_circBuf; i < 99; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter3_states[i + 99] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter3_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter3_states[i + 99] * 0.01;
  }

  rtb_llaBias_na_idx_1 = rtb_MatrixMultiply1_idx_1;
  rtb_MatrixMultiply1_idx_1 = Switch3_idx_2 * 0.01;
  for (i = rtDW->DiscreteFIRFilter3_circBuf; i < 99; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter3_states[i + 198] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter3_circBuf; i++) {
    rtb_MatrixMultiply1_idx_1 += rtDW->DiscreteFIRFilter3_states[i + 198] * 0.01;
  }

  rtb_llaBias_na_idx_2 = rtb_MatrixMultiply1_idx_1;

  /* End of DiscreteFir: '<S426>/Discrete FIR Filter3' */

  /* S-Function (sfix_look1_dyn): '<S75>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S13>/Internal breakpoints'
   *  Constant: '<S9>/Constant5'
   */
  /* Dynamic Look-Up Table Block: '<S75>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_DProdOut_m), &innerLoopParams.fbkGainPitchYawI_na
                       [0], rtb_Sum_e, &innerLoopParams.fbkGainBreakpoints_Pa[0],
                       2U);

  /* S-Function (sfix_look1_dyn): '<S146>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S10>/Constant5'
   *  Constant: '<S84>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S146>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_b),
                       &innerLoopParams.fbkGainRollI_na[0], rtb_Sum_e,
                       &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* S-Function (sfix_look1_dyn): '<S216>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S11>/Constant5'
   *  Constant: '<S154>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S216>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_k),
                       &innerLoopParams.fbkGainPitchYawI_na[0], rtb_Sum_e,
                       &innerLoopParams.fbkGainBreakpoints_Pa[0], 2U);

  /* Switch: '<S466>/Switch' incorporates:
   *  Constant: '<S466>/Constant4'
   *  Constant: '<S466>/Constant5'
   *  Inport: '<Root>/sensor_bus'
   */
  if (rtU_sensor_bus_e->baroMeas_Pa >= 0.0) {
    i = 1;
  } else {
    i = -1;
  }

  /* Product: '<S466>/Product' incorporates:
   *  Abs: '<S466>/Abs'
   *  Constant: '<S466>/Constant'
   *  Inport: '<Root>/sensor_bus'
   *  MinMax: '<S466>/Max'
   *  Switch: '<S466>/Switch'
   */
  rtDW->Product_d = (real_T)i * fmax(1.0E-6, fabs(rtU_sensor_bus_e->baroMeas_Pa));

  /* S-Function (saeropalt): '<S467>/S-Function' */

  /* S-Function Block: <S467>/S-Function */
  {
    real_T *temp_table = (real_T *) rtDW->SFunction_temp_table_m;
    real_T *pres_table = (real_T *) rtDW->SFunction_pres_table_c;
    CalcPAltCOESA( &rtDW->Product_d, &rtDW->SFunction_p, temp_table, pres_table,
                  1);
  }

  /* SampleTimeMath: '<S220>/TSamp'
   *
   * About '<S220>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_MatrixMultiply1_idx_1 = rtb_Switch2_b * 100.0;

  /* Sum: '<S220>/Diff' incorporates:
   *  UnitDelay: '<S220>/UD'
   *
   * Block description for '<S220>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S220>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Switch2_b = rtb_MatrixMultiply1_idx_1 - rtDW->UD_DSTATE_l;

  /* Logic: '<S156>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S11>/Constant1'
   *  RelationalOperator: '<S156>/Relational Operator'
   *  RelationalOperator: '<S156>/Relational Operator1'
   */
  rtb_LogicalOperator_b = ((innerLoopParams.upRateLimitPitchYaw_dps <=
    rtb_Switch2_b) || (rtb_Switch2_b <= innerLoopParams.loRateLimitPitchYaw_dps));

  /* Logic: '<S157>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Constant: '<S11>/Constant3'
   *  RelationalOperator: '<S157>/Relational Operator'
   *  RelationalOperator: '<S157>/Relational Operator1'
   */
  rtb_LogicalOperator_l = ((innerLoopParams.upLimitPitchYaw_deg <= rtb_Divide_l)
    || (rtb_Divide_l <= innerLoopParams.loLimitPitchYaw_deg));

  /* Product: '<S190>/IProd Out' incorporates:
   *  Logic: '<S11>/Logical Operator'
   *  Product: '<S153>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_GainDynamicLookup_k = (real_T)(!rtb_LogicalOperator_l &&
    !rtb_LogicalOperator_b) * rtb_GainDynamicLookup_k * (real_T)
    rtDW->UnitDelay_DSTATE_n * rtb_Sum1_j;

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.control_deg =
    rtb_Integrator_fe;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_p1;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator_b;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_l;

  /* SampleTimeMath: '<S79>/TSamp'
   *
   * About '<S79>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_p1 = rtb_Switch2_j * 100.0;

  /* Sum: '<S79>/Diff' incorporates:
   *  UnitDelay: '<S79>/UD'
   *
   * Block description for '<S79>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S79>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Switch2_b = rtb_Product1_p1 - rtDW->UD_DSTATE_k;

  /* Logic: '<S15>/Logical Operator1' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  RelationalOperator: '<S15>/Relational Operator'
   *  RelationalOperator: '<S15>/Relational Operator1'
   */
  rtb_LogicalOperator1_f = ((innerLoopParams.upRateLimitPitchYaw_dps <=
    rtb_Switch2_b) || (rtb_Switch2_b <= innerLoopParams.loRateLimitPitchYaw_dps));

  /* Logic: '<S16>/Logical Operator1' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  RelationalOperator: '<S16>/Relational Operator'
   *  RelationalOperator: '<S16>/Relational Operator1'
   */
  rtb_LogicalOperator_l = ((innerLoopParams.upLimitPitchYaw_deg <= rtb_Divide) ||
    (rtb_Divide <= innerLoopParams.loLimitPitchYaw_deg));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.control_deg =
    rtb_PProdOut_b;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_ad;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator1_f;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_l;

  /* SampleTimeMath: '<S149>/TSamp'
   *
   * About '<S149>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_ad = rtb_Switch2_f * 100.0;

  /* Sum: '<S149>/Diff' incorporates:
   *  UnitDelay: '<S149>/UD'
   *
   * Block description for '<S149>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S149>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Switch2_b = rtb_Product1_ad - rtDW->UD_DSTATE_n;

  /* Logic: '<S86>/Logical Operator1' incorporates:
   *  Constant: '<S10>/Constant'
   *  Constant: '<S10>/Constant1'
   *  RelationalOperator: '<S86>/Relational Operator'
   *  RelationalOperator: '<S86>/Relational Operator1'
   */
  rtb_LogicalOperator_b = ((innerLoopParams.upRateLimitRoll_dps <= rtb_Switch2_b)
    || (rtb_Switch2_b <= innerLoopParams.loRateLimitRoll_dps));

  /* Logic: '<S87>/Logical Operator1' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant3'
   *  RelationalOperator: '<S87>/Relational Operator'
   *  RelationalOperator: '<S87>/Relational Operator1'
   */
  rtb_LogicalOperator_p = ((innerLoopParams.upLimitRoll_deg <= rtb_Gain_a) ||
    (rtb_Gain_a <= innerLoopParams.loLimitRoll_deg));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.control_deg =
    rtb_Integrator_g;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_o;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator_b;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_p;

  /* SampleTimeMath: '<S284>/TSamp'
   *
   * About '<S284>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_o = rtb_Switch2_m * 100.0;

  /* Sum: '<S284>/Diff' incorporates:
   *  UnitDelay: '<S284>/UD'
   *
   * Block description for '<S284>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S284>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Switch2_b = rtb_Product1_o - rtDW->UD_DSTATE_g;

  /* Logic: '<S229>/Logical Operator1' incorporates:
   *  Constant: '<S225>/Constant'
   *  Constant: '<S225>/Constant1'
   *  RelationalOperator: '<S229>/Relational Operator'
   *  RelationalOperator: '<S229>/Relational Operator1'
   */
  rtb_LogicalOperator1 = ((outerLoopParams.upRateLimitPitchYawRate_rps2 <=
    rtb_Switch2_b) || (rtb_Switch2_b <=
                       outerLoopParams.loRateLimitPitchYawRate_rps2));

  /* Logic: '<S230>/Logical Operator1' incorporates:
   *  Constant: '<S225>/Constant2'
   *  Constant: '<S225>/Constant3'
   *  RelationalOperator: '<S230>/Relational Operator'
   *  RelationalOperator: '<S230>/Relational Operator1'
   */
  rtb_LogicalOperator_a = ((outerLoopParams.upLimitPitchYawRate_rps <=
    rtb_Product1_j3) || (rtb_Product1_j3 <=
    outerLoopParams.loLimitPitchYawRate_rps));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.rateCmd_rps =
    rtb_UkYk1_l;
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1;
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_a;

  /* SampleTimeMath: '<S404>/TSamp'
   *
   * About '<S404>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Gain_a = rtb_Switch2_d * 100.0;

  /* Sum: '<S404>/Diff' incorporates:
   *  UnitDelay: '<S404>/UD'
   *
   * Block description for '<S404>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S404>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Switch2_b = rtb_Gain_a - rtDW->UD_DSTATE_p;

  /* Logic: '<S349>/Logical Operator1' incorporates:
   *  Constant: '<S227>/Constant'
   *  Constant: '<S227>/Constant1'
   *  RelationalOperator: '<S349>/Relational Operator'
   *  RelationalOperator: '<S349>/Relational Operator1'
   */
  rtb_LogicalOperator1_kg = ((outerLoopParams.upRateLimitPitchYawRate_rps2 <=
    rtb_Switch2_b) || (rtb_Switch2_b <=
                       outerLoopParams.loRateLimitPitchYawRate_rps2));

  /* Logic: '<S350>/Logical Operator1' incorporates:
   *  Constant: '<S227>/Constant2'
   *  Constant: '<S227>/Constant3'
   *  RelationalOperator: '<S350>/Relational Operator'
   *  RelationalOperator: '<S350>/Relational Operator1'
   */
  rtb_LogicalOperator_o = ((outerLoopParams.upLimitPitchYawRate_rps <=
    rtb_Product1_j) || (rtb_Product1_j <=
                        outerLoopParams.loLimitPitchYawRate_rps));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.rateCmd_rps =
    rtb_Integrator_i;
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1_kg;
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_o;

  /* SampleTimeMath: '<S344>/TSamp'
   *
   * About '<S344>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Switch2 *= 100.0;

  /* Sum: '<S344>/Diff' incorporates:
   *  UnitDelay: '<S344>/UD'
   *
   * Block description for '<S344>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S344>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Switch2_b = rtb_Switch2 - rtDW->UD_DSTATE_a;

  /* Logic: '<S289>/Logical Operator1' incorporates:
   *  Constant: '<S226>/Constant'
   *  Constant: '<S226>/Constant1'
   *  RelationalOperator: '<S289>/Relational Operator'
   *  RelationalOperator: '<S289>/Relational Operator1'
   */
  rtb_LogicalOperator1_f3 = ((outerLoopParams.upRateLimitRollRate_rps2 <=
    rtb_Switch2_b) || (rtb_Switch2_b <= outerLoopParams.loRateLimitRollRate_rps2));

  /* Logic: '<S290>/Logical Operator1' incorporates:
   *  Constant: '<S226>/Constant2'
   *  Constant: '<S226>/Constant3'
   *  RelationalOperator: '<S290>/Relational Operator'
   *  RelationalOperator: '<S290>/Relational Operator1'
   */
  rtb_LogicalOperator_ff = ((outerLoopParams.upLimitRollRate_rps <=
    rtb_Product1_e) || (rtb_Product1_e <= outerLoopParams.loLimitRollRate_rps));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.rateCmd_rps =
    rtb_Integrator_b;
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1_f3;
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_ff;

  /* BusCreator generated from: '<Root>/controller_bus' incorporates:
   *  Outport: '<Root>/controller_bus'
   */
  rtY_controller_bus_f->control_deg[0] = rtb_Sum_kk_idx_0;
  rtY_controller_bus_f->control_deg[1] = rtb_Sum_kk_idx_1;
  rtY_controller_bus_f->control_deg[2] = rtb_Sum_kk_idx_2;
  rtY_controller_bus_f->control_deg[3] = rtb_Sum_kk_idx_3;

  /* Product: '<S323>/IProd Out' incorporates:
   *  Constant: '<S226>/Constant4'
   *  Logic: '<S226>/Logical Operator'
   *  Product: '<S288>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Sum2_p *= (real_T)(!rtb_LogicalOperator_ff && !rtb_LogicalOperator1_f3) *
    outerLoopParams.rollGains[1] * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S383>/IProd Out' incorporates:
   *  Constant: '<S227>/Constant4'
   *  Logic: '<S227>/Logical Operator'
   *  Product: '<S348>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_e = (real_T)(!rtb_LogicalOperator_o && !rtb_LogicalOperator1_kg) *
    outerLoopParams.pitchYawGains[1] * (real_T)rtDW->UnitDelay_DSTATE_n *
    rtb_Sum3;

  /* Product: '<S263>/IProd Out' incorporates:
   *  Constant: '<S225>/Constant4'
   *  Logic: '<S225>/Logical Operator'
   *  Product: '<S228>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Sum4_a *= (real_T)(!rtb_LogicalOperator_a && !rtb_LogicalOperator1) *
    outerLoopParams.pitchYawGains[1] * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S120>/IProd Out' incorporates:
   *  Logic: '<S10>/Logical Operator'
   *  Product: '<S83>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product2_l *= (real_T)(!rtb_LogicalOperator_p && !rtb_LogicalOperator_b) *
    rtb_GainDynamicLookup_b * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S12>/Product' incorporates:
   *  Logic: '<S9>/Logical Operator'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Switch2_b = (real_T)(!rtb_LogicalOperator_l && !rtb_LogicalOperator1_f) *
    rtb_DProdOut_m * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* State Transition Table: '<S411>/State Transition Table' incorporates:
   *  Constant: '<S411>/Constant'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   */
  if (rtDW->temporalCounter_i1 < MAX_uint32_T) {
    rtDW->temporalCounter_i1++;
  }

  if (rtDW->is_active_c4_autocodeModel == 0) {
    rtDW->is_active_c4_autocodeModel = 1U;
    rtDW->is_c4_autocodeModel = autocodeModel_IN_Idle;
    rtDW->flightMode_enum = IDLE;
    rtDW->boostThreshold_b = false;
  } else {
    switch (rtDW->is_c4_autocodeModel) {
     case autocodeModel_IN_Active:
      rtDW->flightMode_enum = ACTIVE;
      if (rtDW->lockoutThreshold_b) {
        rtDW->temporalCounter_i1 = 0U;
        rtDW->is_c4_autocodeModel = autocod_IN_PastLockoutThreshold;
      } else {
        rtDW->lockoutThreshold_b = ((fabs(rtb_wBdyEst_rps[1]) >
          navStates.controlTresholdPitchYawRate_rps) || ((fabs(rtb_wBdyEst_rps[2])
          > navStates.controlTresholdPitchYawRate_rps) || ((fabs
          (rtb_Switch_ft_idx_1) > navStates.controlTresholdPitchYaw_rad) ||
          (fabs(rtb_Switch_ft_idx_2) > navStates.controlTresholdPitchYaw_rad))));
      }
      break;

     case autocodeModel_IN_Boost:
      rtDW->flightMode_enum = BOOST;
      if (rtDW->coastThreshold_b) {
        rtDW->temporalCounter_i1 = 0U;
        rtDW->is_c4_autocodeModel = autocodeM_IN_PastCoastThreshold;
      } else {
        rtDW->coastThreshold_b = ((navStates.coastThresholdAlt_m < 2000.0) &&
          (rtb_accBdyEst_mps2[0] < navStates.coastThresholdxAcc_mps2));
      }
      break;

     case autocodeModel_IN_Idle:
      rtDW->flightMode_enum = IDLE;
      if (rtDW->boostThreshold_b) {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Boost;
        rtDW->flightMode_enum = BOOST;
        rtDW->coastThreshold_b = false;
      } else {
        rtb_Switch2_f = 3.312168642111238E-170;
        rtb_Product1_j3 = fabs(rtb_accBdyEst_mps2[0]);
        if (rtb_Product1_j3 > 3.312168642111238E-170) {
          rtb_Sum3 = 1.0;
          rtb_Switch2_f = rtb_Product1_j3;
        } else {
          rtb_Switch2_m = rtb_Product1_j3 / 3.312168642111238E-170;
          rtb_Sum3 = rtb_Switch2_m * rtb_Switch2_m;
        }

        rtb_Product1_j3 = fabs(rtb_accBdyEst_mps2[1]);
        if (rtb_Product1_j3 > rtb_Switch2_f) {
          rtb_Switch2_m = rtb_Switch2_f / rtb_Product1_j3;
          rtb_Sum3 = rtb_Sum3 * rtb_Switch2_m * rtb_Switch2_m + 1.0;
          rtb_Switch2_f = rtb_Product1_j3;
        } else {
          rtb_Switch2_m = rtb_Product1_j3 / rtb_Switch2_f;
          rtb_Sum3 += rtb_Switch2_m * rtb_Switch2_m;
        }

        rtb_Product1_j3 = fabs(rtb_accBdyEst_mps2[2]);
        if (rtb_Product1_j3 > rtb_Switch2_f) {
          rtb_Switch2_m = rtb_Switch2_f / rtb_Product1_j3;
          rtb_Sum3 = rtb_Sum3 * rtb_Switch2_m * rtb_Switch2_m + 1.0;
          rtb_Switch2_f = rtb_Product1_j3;
        } else {
          rtb_Switch2_m = rtb_Product1_j3 / rtb_Switch2_f;
          rtb_Sum3 += rtb_Switch2_m * rtb_Switch2_m;
        }

        rtb_Sum3 = rtb_Switch2_f * sqrt(rtb_Sum3);
        if (rtIsNaN(rtb_Sum3)) {
          i = 0;
          do {
            exitg1 = 0;
            if (i < 3) {
              if (rtIsNaN(rtb_accBdyEst_mps2[i])) {
                exitg1 = 1;
              } else {
                i++;
              }
            } else {
              rtb_Sum3 = (rtInf);
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        rtDW->boostThreshold_b = (rtb_Sum3 > navStates.boostThreshold_mps2);
      }
      break;

     case autocodeModel_IN_Lockout:
      rtDW->flightMode_enum = LOCKOUT;
      break;

     case autocodeM_IN_PastCoastThreshold:
      if (!rtDW->coastThreshold_b) {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Boost;
        rtDW->flightMode_enum = BOOST;
      } else if ((real_T)rtDW->temporalCounter_i1 * 0.01 > navStates.debounce_s)
      {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Active;
        rtDW->flightMode_enum = ACTIVE;
        rtDW->lockoutThreshold_b = false;
      } else {
        rtDW->coastThreshold_b = ((navStates.coastThresholdAlt_m < 2000.0) &&
          (rtb_accBdyEst_mps2[0] < navStates.coastThresholdxAcc_mps2));
      }
      break;

     default:
      /* case IN_PastLockoutThreshold: */
      if (!rtDW->lockoutThreshold_b) {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Active;
        rtDW->flightMode_enum = ACTIVE;
      } else if ((real_T)rtDW->temporalCounter_i1 * 0.01 > navStates.debounce_s)
      {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Lockout;
        rtDW->flightMode_enum = LOCKOUT;
      } else {
        rtDW->lockoutThreshold_b = ((fabs(rtb_wBdyEst_rps[1]) >
          navStates.controlTresholdPitchYawRate_rps) || ((fabs(rtb_wBdyEst_rps[2])
          > navStates.controlTresholdPitchYawRate_rps) || ((fabs
          (rtb_Switch_ft_idx_1) > navStates.controlTresholdPitchYaw_rad) ||
          (fabs(rtb_Switch_ft_idx_2) > navStates.controlTresholdPitchYaw_rad))));
      }
      break;
    }
  }

  /* End of State Transition Table: '<S411>/State Transition Table' */

  /* Switch: '<S426>/Switch2' */
  if (rtb_Compare_p) {
    /* Switch: '<S426>/Switch2' */
    rtb_Sum3 = rtDW->SFunction;
  } else {
    /* Switch: '<S426>/Switch2' incorporates:
     *  UnitDelay: '<S426>/Unit Delay2'
     */
    rtb_Sum3 = rtDW->UnitDelay2_DSTATE;
  }

  /* End of Switch: '<S426>/Switch2' */

  /* DiscreteFir: '<S426>/Discrete FIR Filter2' */
  rtb_Sum_kk_idx_3 = rtb_Sum3 * 0.1;
  for (i = rtDW->DiscreteFIRFilter2_circBuf; i < 9; i++) {
    rtb_Sum_kk_idx_3 += rtDW->DiscreteFIRFilter2_states[i] * 0.1;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter2_circBuf; i++) {
    rtb_Sum_kk_idx_3 += rtDW->DiscreteFIRFilter2_states[i] * 0.1;
  }

  /* End of DiscreteFir: '<S426>/Discrete FIR Filter2' */

  /* BusCreator generated from: '<Root>/navigation_bus' incorporates:
   *  DiscreteTransferFcn: '<S428>/Accel Filter'
   *  DiscreteTransferFcn: '<S428>/Gyro Filter'
   *  Outport: '<Root>/navigation_bus'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   */
  rtY_navigation_bus_d->flightMode_enum = rtDW->flightMode_enum;
  rtY_navigation_bus_d->qEst_na[0] = rtDW->qEst_na[0];
  rtY_navigation_bus_d->qEst_na[1] = rtDW->qEst_na[1];
  rtY_navigation_bus_d->qEst_na[2] = rtDW->qEst_na[2];
  rtY_navigation_bus_d->qEst_na[3] = rtDW->qEst_na[3];
  rtY_navigation_bus_d->phiEst_rad = rtb_Switch_ft_idx_3;
  rtY_navigation_bus_d->thetaEst_rad = rtb_Switch_ft_idx_1;
  rtY_navigation_bus_d->psiEst_rad = rtb_Switch_ft_idx_2;
  rtY_navigation_bus_d->pEst_rps = rtb_Cos;
  rtY_navigation_bus_d->qEst_rps = rtb_Cos_e;
  rtY_navigation_bus_d->rEst_rps = rtb_Cos_l;
  rtY_navigation_bus_d->xAccEst_mps2 = 0.5 * rtb_n_m + 0.5 *
    rtDW->AccelFilter_states_k[0];
  rtY_navigation_bus_d->yAccEst_mps2 = 0.5 * rtb_Cos_k + 0.5 *
    rtDW->AccelFilter_states_k[1];
  rtY_navigation_bus_d->zAccEst_mps2 = 0.5 * rtb_Cos_m + 0.5 *
    rtDW->AccelFilter_states_k[2];
  rtY_navigation_bus_d->altitudeBias_m = rtb_Sum_kk_idx_3;
  rtY_navigation_bus_d->accelBias_mps2[0] = rtb_accelBias_mps2[0];
  rtY_navigation_bus_d->gyroBias_rps[0] = rtb_gyroBias_rps[0];
  rtY_navigation_bus_d->llaBias_na[0] = rtb_llaBias_na_idx_0;
  rtY_navigation_bus_d->accelBias_mps2[1] = rtb_accelBias_mps2[1];
  rtY_navigation_bus_d->gyroBias_rps[1] = rtb_gyroBias_rps[1];
  rtY_navigation_bus_d->llaBias_na[1] = rtb_llaBias_na_idx_1;
  rtY_navigation_bus_d->accelBias_mps2[2] = rtb_accelBias_mps2[2];
  rtY_navigation_bus_d->gyroBias_rps[2] = rtb_gyroBias_rps[2];
  rtY_navigation_bus_d->llaBias_na[2] = rtb_llaBias_na_idx_2;
  rtY_navigation_bus_d->dynPressureEst_Pa = rtb_Sum_e;
  rtY_navigation_bus_d->xVelEstNed_mps = rtb_MathFunction_idx_0;
  rtY_navigation_bus_d->yVelEstNed_mps = rtb_MathFunction_idx_1;
  rtY_navigation_bus_d->zVelEstNed_mps = rtb_MathFunction_idx_2;
  rtY_navigation_bus_d->xPosEst_m = rtb_gyroFilt_rps[0];
  rtY_navigation_bus_d->yPosEst_m = rtb_gyroFilt_rps[1];
  rtY_navigation_bus_d->zPosEst_m = rtb_gyroFilt_rps[2];

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[0] = rtDW->qEst_na[0];
  rtDW->UnitDelay_2_DSTATE[1] = rtDW->qEst_na[1];
  rtDW->UnitDelay_2_DSTATE[2] = rtDW->qEst_na[2];
  rtDW->UnitDelay_2_DSTATE[3] = rtDW->qEst_na[3];

  /* Update for UnitDelay: '<S4>/Unit Delay' incorporates:
   *  Constant: '<S4>/Constant2'
   *  RelationalOperator: '<S4>/Equal'
   */
  rtDW->UnitDelay_DSTATE_n = (rtDW->flightMode_enum == ACTIVE);

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_1_DSTATE = rtDW->flightMode_enum;

  /* Update for DiscreteIntegrator: '<S326>/Integrator' */
  rtDW->Integrator_DSTATE += 0.01 * rtb_Sum2_p;

  /* Update for DiscreteIntegrator: '<S321>/Filter' */
  rtDW->Filter_DSTATE += 0.01 * rtb_Sin;

  /* Update for Delay: '<S345>/Delay' */
  rtDW->icLoad = false;
  rtDW->Delay_DSTATE = rtb_Integrator_b;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_17_DSTATE = rtb_MathFunction_idx_0;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_18_DSTATE = rtb_MathFunction_idx_1;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_19_DSTATE = rtb_MathFunction_idx_2;
  for (i = 0; i < 3; i++) {
    /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
    rtDW->UnitDelay_13_DSTATE[i] = rtb_gyroBias_rps[i];

    /* Update for DiscreteTransferFcn: '<S409>/Discrete Transfer Fcn1' */
    uIdx = i * 3;
    rtDW->DiscreteTransferFcn1_states[uIdx + 2] =
      rtDW->DiscreteTransferFcn1_states[uIdx + 1];
    rtDW->DiscreteTransferFcn1_states[uIdx + 1] =
      rtDW->DiscreteTransferFcn1_states[uIdx];
    rtDW->DiscreteTransferFcn1_states[uIdx] = DiscreteTransferFcn1_tmp[i];

    /* Update for DiscreteTransferFcn: '<S428>/Gyro Filter' */
    rtDW->GyroFilter_states[i] = GyroFilter_tmp[i];

    /* Update for UnitDelay: '<S477>/UD' incorporates:
     *  Inport: '<Root>/sensor_bus'
     *
     * Block description for '<S477>/UD':
     *
     *  Store in Global RAM
     */
    rtDW->UD_DSTATE[i] = rtU_sensor_bus_e->gpsLLA_na[i];

    /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
    rtDW->UnitDelay_12_DSTATE[i] = rtb_accelBias_mps2[i];

    /* Update for DiscreteTransferFcn: '<S409>/Accel Filter' */
    rtDW->AccelFilter_states[i] = AccelFilter_tmp[i];
  }

  /* Update for DiscreteIntegrator: '<S123>/Integrator' */
  rtDW->Integrator_DSTATE_b += 0.01 * rtb_Product2_l;

  /* Update for DiscreteIntegrator: '<S118>/Filter' */
  rtDW->Filter_DSTATE_p += 0.01 * rtb_Filter_c;

  /* Update for Delay: '<S150>/Delay' */
  rtDW->icLoad_k = false;
  rtDW->Delay_DSTATE_p = rtb_Integrator_g;

  /* Update for DiscreteIntegrator: '<S266>/Integrator' */
  rtDW->Integrator_DSTATE_g += 0.01 * rtb_Sum4_a;

  /* Update for DiscreteIntegrator: '<S261>/Filter' */
  rtDW->Filter_DSTATE_n += 0.01 * rtb_Product2_m;

  /* Update for Delay: '<S285>/Delay' */
  rtDW->icLoad_a = false;
  rtDW->Delay_DSTATE_c = rtb_UkYk1_l;

  /* Update for DiscreteIntegrator: '<S52>/Integrator' incorporates:
   *  Product: '<S49>/IProd Out'
   */
  rtDW->Integrator_DSTATE_p += rtb_sqrt * rtb_Switch2_b * 0.01;

  /* Update for DiscreteIntegrator: '<S47>/Filter' */
  rtDW->Filter_DSTATE_l += 0.01 * rtb_Filter_g;

  /* Update for Delay: '<S80>/Delay' */
  rtDW->icLoad_f = false;
  rtDW->Delay_DSTATE_f = rtb_PProdOut_b;

  /* Update for DiscreteIntegrator: '<S386>/Integrator' */
  rtDW->Integrator_DSTATE_l += 0.01 * rtb_Product1_e;

  /* Update for DiscreteIntegrator: '<S381>/Filter' */
  rtDW->Filter_DSTATE_c += 0.01 * rtb_Filter_b;

  /* Update for Delay: '<S405>/Delay' */
  rtDW->icLoad_c = false;
  rtDW->Delay_DSTATE_h = rtb_Integrator_i;

  /* Update for DiscreteIntegrator: '<S193>/Integrator' */
  rtDW->Integrator_DSTATE_e += 0.01 * rtb_GainDynamicLookup_k;

  /* Update for DiscreteIntegrator: '<S188>/Filter' */
  rtDW->Filter_DSTATE_g += 0.01 * rtb_Filter_e;

  /* Update for Delay: '<S221>/Delay' */
  rtDW->icLoad_d = false;
  rtDW->Delay_DSTATE_e = rtb_Integrator_fe;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_20_DSTATE = rtb_gyroFilt_rps[0];

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_21_DSTATE = rtb_gyroFilt_rps[1];

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_22_DSTATE = rtb_gyroFilt_rps[2];

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_15_DSTATE[0] = rtb_llaBias_na_idx_0;

  /* Update for DiscreteTransferFcn: '<S428>/Accel Filter' */
  rtDW->AccelFilter_states_k[0] = rtb_n_m;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_15_DSTATE[1] = rtb_llaBias_na_idx_1;

  /* Update for DiscreteTransferFcn: '<S428>/Accel Filter' */
  rtDW->AccelFilter_states_k[1] = rtb_Cos_k;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_15_DSTATE[2] = rtb_llaBias_na_idx_2;

  /* Update for DiscreteTransferFcn: '<S428>/Accel Filter' */
  rtDW->AccelFilter_states_k[2] = rtb_Cos_m;

  /* Update for Delay generated from: '<S426>/Delay2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  for (i = 0; i < 499; i++) {
    rtDW->Delay2_6_DSTATE[i] = rtDW->Delay2_6_DSTATE[i + 1];
    uIdx = (i + 1) * 3;
    rtDW->Delay2_3_DSTATE[i * 3] = rtDW->Delay2_3_DSTATE[uIdx];
    rtDW->Delay2_3_DSTATE[i * 3 + 1] = rtDW->Delay2_3_DSTATE[uIdx + 1];
    rtDW->Delay2_3_DSTATE[i * 3 + 2] = rtDW->Delay2_3_DSTATE[uIdx + 2];
  }

  rtDW->Delay2_6_DSTATE[499] = rtU_sensor_bus_e->baroMeas_Pa;

  /* Update for Delay generated from: '<S426>/Delay2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay2_3_DSTATE[1497] = rtU_sensor_bus_e->fBdyMeas_mps2[0];

  /* Update for UnitDelay: '<S426>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[0] = rtb_accelBias_mps2[0];

  /* Update for Delay generated from: '<S426>/Delay2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay2_3_DSTATE[1498] = rtU_sensor_bus_e->fBdyMeas_mps2[1];

  /* Update for UnitDelay: '<S426>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[1] = rtb_accelBias_mps2[1];

  /* Update for Delay generated from: '<S426>/Delay2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay2_3_DSTATE[1499] = rtU_sensor_bus_e->fBdyMeas_mps2[2];

  /* Update for UnitDelay: '<S426>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[2] = rtb_accelBias_mps2[2];

  /* Update for DiscreteFir: '<S426>/Discrete FIR Filter1' */
  /* Update circular buffer index */
  rtDW->DiscreteFIRFilter1_circBuf--;
  if (rtDW->DiscreteFIRFilter1_circBuf < 0) {
    rtDW->DiscreteFIRFilter1_circBuf = 998;
  }

  /* Update circular buffer */
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf] = Switch1[0];
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf + 999] =
    Switch1[1];
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf + 1998] =
    Switch1[2];

  /* End of Update for DiscreteFir: '<S426>/Discrete FIR Filter1' */

  /* Update for Delay generated from: '<S426>/Delay2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  for (i = 0; i < 499; i++) {
    uIdx = (i + 1) * 3;
    rtDW->Delay2_4_DSTATE[i * 3] = rtDW->Delay2_4_DSTATE[uIdx];
    rtDW->Delay2_4_DSTATE[i * 3 + 1] = rtDW->Delay2_4_DSTATE[uIdx + 1];
    rtDW->Delay2_4_DSTATE[i * 3 + 2] = rtDW->Delay2_4_DSTATE[uIdx + 2];
  }

  rtDW->Delay2_4_DSTATE[1497] = rtU_sensor_bus_e->wBdyMeas_rps[0];

  /* Update for UnitDelay: '<S426>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[0] = rtb_gyroBias_rps[0];

  /* Update for Delay generated from: '<S426>/Delay2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay2_4_DSTATE[1498] = rtU_sensor_bus_e->wBdyMeas_rps[1];

  /* Update for UnitDelay: '<S426>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[1] = rtb_gyroBias_rps[1];

  /* Update for Delay generated from: '<S426>/Delay2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay2_4_DSTATE[1499] = rtU_sensor_bus_e->wBdyMeas_rps[2];

  /* Update for UnitDelay: '<S426>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[2] = rtb_gyroBias_rps[2];

  /* Update for DiscreteFir: '<S426>/Discrete FIR Filter' */
  /* Update circular buffer index */
  rtDW->DiscreteFIRFilter_circBuf--;
  if (rtDW->DiscreteFIRFilter_circBuf < 0) {
    rtDW->DiscreteFIRFilter_circBuf = 998;
  }

  /* Update circular buffer */
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf] =
    rtb_MatrixMultiply1_idx_2;
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf + 999] =
    rtb_MatrixMultiply1_idx_0;
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf + 1998] =
    Switch_idx_2;

  /* End of Update for DiscreteFir: '<S426>/Discrete FIR Filter' */
  for (i = 0; i < 499; i++) {
    /* Update for Delay generated from: '<S426>/Delay2' */
    uIdx = (i + 1) * 3;
    rtDW->Delay2_8_DSTATE[i * 3] = rtDW->Delay2_8_DSTATE[uIdx];
    rtDW->Delay2_8_DSTATE[i * 3 + 1] = rtDW->Delay2_8_DSTATE[uIdx + 1];
    rtDW->Delay2_8_DSTATE[i * 3 + 2] = rtDW->Delay2_8_DSTATE[uIdx + 2];

    /* Update for Delay generated from: '<S426>/Delay1' */
    rtDW->Delay1_6_DSTATE[i] = rtDW->Delay1_6_DSTATE[i + 1];
  }

  /* Update for Delay generated from: '<S426>/Delay2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay2_8_DSTATE[1497] = rtU_sensor_bus_e->gpsLLA_na[0];
  rtDW->Delay2_8_DSTATE[1498] = rtU_sensor_bus_e->gpsLLA_na[1];
  rtDW->Delay2_8_DSTATE[1499] = rtU_sensor_bus_e->gpsLLA_na[2];

  /* Update for Delay generated from: '<S426>/Delay1' */
  rtDW->Delay1_6_DSTATE[499] = rtb_LogicalOperator;

  /* Update for UnitDelay: '<S426>/Unit Delay3' */
  rtDW->UnitDelay3_DSTATE[0] = rtb_llaBias_na_idx_0;
  rtDW->UnitDelay3_DSTATE[1] = rtb_llaBias_na_idx_1;
  rtDW->UnitDelay3_DSTATE[2] = rtb_llaBias_na_idx_2;

  /* Update for DiscreteFir: '<S426>/Discrete FIR Filter3' */
  /* Update circular buffer index */
  rtDW->DiscreteFIRFilter3_circBuf--;
  if (rtDW->DiscreteFIRFilter3_circBuf < 0) {
    rtDW->DiscreteFIRFilter3_circBuf = 98;
  }

  /* Update circular buffer */
  rtDW->DiscreteFIRFilter3_states[rtDW->DiscreteFIRFilter3_circBuf] =
    Switch3_idx_0;
  rtDW->DiscreteFIRFilter3_states[rtDW->DiscreteFIRFilter3_circBuf + 99] =
    Switch3_idx_1;
  rtDW->DiscreteFIRFilter3_states[rtDW->DiscreteFIRFilter3_circBuf + 198] =
    Switch3_idx_2;

  /* End of Update for DiscreteFir: '<S426>/Discrete FIR Filter3' */

  /* Update for UnitDelay: '<S220>/UD'
   *
   * Block description for '<S220>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_l = rtb_MatrixMultiply1_idx_1;

  /* Update for UnitDelay: '<S79>/UD'
   *
   * Block description for '<S79>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_k = rtb_Product1_p1;

  /* Update for UnitDelay: '<S149>/UD'
   *
   * Block description for '<S149>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_n = rtb_Product1_ad;

  /* Update for UnitDelay: '<S284>/UD'
   *
   * Block description for '<S284>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_g = rtb_Product1_o;

  /* Update for UnitDelay: '<S404>/UD'
   *
   * Block description for '<S404>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_p = rtb_Gain_a;

  /* Update for UnitDelay: '<S344>/UD'
   *
   * Block description for '<S344>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_a = rtb_Switch2;

  /* Update for UnitDelay: '<S426>/Unit Delay2' */
  rtDW->UnitDelay2_DSTATE = rtb_Sum_kk_idx_3;

  /* Update for DiscreteFir: '<S426>/Discrete FIR Filter2' */
  /* Update circular buffer index */
  rtDW->DiscreteFIRFilter2_circBuf--;
  if (rtDW->DiscreteFIRFilter2_circBuf < 0) {
    rtDW->DiscreteFIRFilter2_circBuf = 8;
  }

  /* Update circular buffer */
  rtDW->DiscreteFIRFilter2_states[rtDW->DiscreteFIRFilter2_circBuf] = rtb_Sum3;

  /* End of Update for DiscreteFir: '<S426>/Discrete FIR Filter2' */
}

/* Model initialize function */
void autocodeModel_initialize(RT_MODEL *const rtM, sensor_bus *rtU_sensor_bus_e,
  navigation_bus *rtY_navigation_bus_d, controller_bus *rtY_controller_bus_f,
  real_T rtY_control_deg[4])
{
  DW *rtDW = rtM->dwork;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  {
    rtDW->flightMode_enum = IDLE;
  }

  /* external inputs */
  *rtU_sensor_bus_e = autocodeModel_rtZsensor_bus;

  /* external outputs */
  (void)memset(&rtY_control_deg[0], 0, sizeof(real_T) << 2U);
  *rtY_navigation_bus_d = autocodeModel_rtZnavigation_bus;
  *rtY_controller_bus_f = autocodeModel_rtZcontroller_bus;

  /* Start for S-Function (saeropalt): '<S432>/S-Function' */
  {
    real_T *temp_table = (real_T *) rtDW->SFunction_temp_table;
    real_T *pres_table = (real_T *) rtDW->SFunction_pres_table;
    InitCalcAtmosCOESA( temp_table, pres_table );
  }

  /* Start for S-Function (saeropalt): '<S467>/S-Function' */
  {
    real_T *temp_table = (real_T *) rtDW->SFunction_temp_table_m;
    real_T *pres_table = (real_T *) rtDW->SFunction_pres_table_c;
    InitCalcAtmosCOESA( temp_table, pres_table );
  }

  /* InitializeConditions for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[0] = navControl.navIC_bus.qEst_na[0];
  rtDW->UnitDelay_2_DSTATE[1] = navControl.navIC_bus.qEst_na[1];
  rtDW->UnitDelay_2_DSTATE[2] = navControl.navIC_bus.qEst_na[2];
  rtDW->UnitDelay_2_DSTATE[3] = navControl.navIC_bus.qEst_na[3];

  /* InitializeConditions for Delay: '<S345>/Delay' */
  rtDW->icLoad = true;

  /* InitializeConditions for Delay: '<S150>/Delay' */
  rtDW->icLoad_k = true;

  /* InitializeConditions for Delay: '<S285>/Delay' */
  rtDW->icLoad_a = true;

  /* InitializeConditions for Delay: '<S80>/Delay' */
  rtDW->icLoad_f = true;

  /* InitializeConditions for Delay: '<S405>/Delay' */
  rtDW->icLoad_c = true;

  /* InitializeConditions for Delay: '<S221>/Delay' */
  rtDW->icLoad_d = true;

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter1' */
  rtDW->DiscreteFIRFilter1_circBuf = 0;

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter' */
  rtDW->DiscreteFIRFilter_circBuf = 0;

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter1' */
  memset(&rtDW->DiscreteFIRFilter1_states[0], 0, 2997U * sizeof(real_T));

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter' */
  memset(&rtDW->DiscreteFIRFilter_states[0], 0, 2997U * sizeof(real_T));

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter3' */
  rtDW->DiscreteFIRFilter3_circBuf = 0;
  memset(&rtDW->DiscreteFIRFilter3_states[0], 0, 297U * sizeof(real_T));

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter2' */
  rtDW->DiscreteFIRFilter2_circBuf = 0;
  memset(&rtDW->DiscreteFIRFilter2_states[0], 0, 9U * sizeof(real_T));

  /* SystemInitialize for Merge: '<S427>/Merge' */
  rtDW->qEst_na[0] = 0.0;
  rtDW->qEst_na[1] = 0.0;
  rtDW->qEst_na[2] = 0.0;
  rtDW->qEst_na[3] = 0.0;

  /* SystemInitialize for State Transition Table: '<S411>/State Transition Table' */
  rtDW->temporalCounter_i1 = 0U;
  rtDW->boostThreshold_b = false;
  rtDW->lockoutThreshold_b = false;
  rtDW->flightMode_enum = IDLE;
  rtDW->coastThreshold_b = false;
  rtDW->is_active_c4_autocodeModel = 0U;
  rtDW->is_c4_autocodeModel = autocodeMode_IN_NO_ACTIVE_CHILD;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
