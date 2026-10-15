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
 * C/C++ source code generated on : Wed Oct 14 21:16:34 2026
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
#include <string.h>

/* Named constants for State Transition Table: '<S409>/State Transition Table' */
#define autocod_IN_PastLockoutThreshold ((uint8_T)6U)
#define autocodeM_IN_PastCoastThreshold ((uint8_T)5U)
#define autocodeMode_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define autocodeModel_IN_Active        ((uint8_T)1U)
#define autocodeModel_IN_Boost         ((uint8_T)2U)
#define autocodeModel_IN_Idle          ((uint8_T)3U)
#define autocodeModel_IN_Lockout       ((uint8_T)4U)

extern const real_T rtCP_pooled_JIXvzcabvSoM[9];
extern const real_T rtCP_pooled_Qcj6ValmO9nO[3];

#define rtCP__Constant_Value_m         rtCP_pooled_JIXvzcabvSoM  /* Expression: navControl.gyroG
                                                                  * Referenced by: '<S422>/Constant'
                                                                  */
#define rtCP__Constant_Value_bn        rtCP_pooled_Qcj6ValmO9nO  /* Expression: navControl.gravityNed_mps2
                                                                  * Referenced by: '<S450>/Constant'
                                                                  */

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
  0.0,                                 /* dynPressureEst_Pa */

  { 0.0, 0.0, 0.0 },                   /* accelBias_mps2 */

  { 0.0, 0.0, 0.0 },                   /* gyroBias_rps */
  0.0,                                 /* xVelEst_mps */
  0.0,                                 /* yVelEst_mps */
  0.0,                                 /* zVelEst_mps */
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
  0.0                                  /* baroMeas_Pa */
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
  real_T rtb_QuaternionstoDirectionCosin[9];
  real_T rtb_Sum_o[4];
  real_T AccelFilter_tmp[3];
  real_T AccelFilter_tmp_j[3];
  real_T DiscreteTransferFcn1_tmp[3];
  real_T GyroFilter_tmp[3];
  real_T Switch1[3];
  real_T rtb_DiscreteFIRFilter[3];
  real_T rtb_MathFunction[3];
  real_T rtb_accBdyEst_mps2[3];
  real_T rtb_accelFilt_mps2[3];
  real_T rtb_accelFilt_mps2_c[3];
  real_T rtb_gyroBias_rps[3];
  real_T rtb_gyroFilt_rps[3];
  real_T rtb_wBdyEst_rps[3];
  real_T absxk;
  real_T rtb_Divide_l;
  real_T rtb_Filter_a;
  real_T rtb_Gain;
  real_T rtb_Integrator_d;
  real_T rtb_Integrator_l;
  real_T rtb_MatrixMultiply_idx_0;
  real_T rtb_MatrixMultiply_idx_1;
  real_T rtb_MatrixMultiply_idx_2;
  real_T rtb_NProdOut_k;
  real_T rtb_Product1_ek;
  real_T rtb_Product1_g3;
  real_T rtb_Product1_i;
  real_T rtb_Product1_k;
  real_T rtb_Product1_l;
  real_T rtb_Product1_nt;
  real_T rtb_Product1_o;
  real_T rtb_Product2_a;
  real_T rtb_QuaternionstoDirectionCos_0;
  real_T rtb_QuaternionstoDirectionCos_1;
  real_T rtb_Sum1_e_idx_1_tmp;
  real_T rtb_Sum1_j;
  real_T rtb_Sum2;
  real_T rtb_Sum4_idx_0;
  real_T rtb_Sum4_idx_1;
  real_T rtb_Sum4_idx_2;
  real_T rtb_Sum5_idx_0;
  real_T rtb_Sum5_idx_1;
  real_T rtb_Sum5_idx_2;
  real_T rtb_Sum_a;
  real_T rtb_Switch2;
  real_T rtb_Switch2_b;
  real_T rtb_Switch2_d;
  real_T rtb_Switch2_f;
  real_T rtb_Switch2_j;
  real_T rtb_Switch2_m;
  real_T rtb_UkYk1_b;
  real_T rtb_UkYk1_g;
  real_T rtb_UkYk1_h;
  real_T rtb_accelBias_mps2_idx_0;
  real_T rtb_accelBias_mps2_idx_1;
  real_T rtb_accelBias_mps2_idx_2;
  real_T rtb_deltafalllimit;
  real_T rtb_deltafalllimit_fs;
  real_T rtb_rateCmd_rps;
  real_T rtb_sqrt;
  real_T rtb_zPosEst_m;
  real_T scale;
  real_T t;
  int32_T exitg1;
  int32_T i;
  int32_T uIdx;
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LogicalOperator1;
  boolean_T rtb_LogicalOperator1_au;
  boolean_T rtb_LogicalOperator1_b;
  boolean_T rtb_LogicalOperator1_f;
  boolean_T rtb_LogicalOperator1_l;
  boolean_T rtb_LogicalOperator1_m4;
  boolean_T rtb_LogicalOperator_c;
  boolean_T rtb_LogicalOperator_dg;
  boolean_T rtb_LogicalOperator_e;
  boolean_T rtb_LogicalOperator_k;
  boolean_T rtb_LogicalOperator_nf;
  flightMode rtb_flightMode_enum;

  /* Quat2Dcm: '<S450>/Quaternions to  Direction Cosine Matrix' incorporates:
   *  Quat2Dcm: '<S407>/C-'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Sum1_e_idx_1_tmp = 1.0 / sqrt(((rtDW->UnitDelay_2_DSTATE[0] *
    rtDW->UnitDelay_2_DSTATE[0] + rtDW->UnitDelay_2_DSTATE[1] *
    rtDW->UnitDelay_2_DSTATE[1]) + rtDW->UnitDelay_2_DSTATE[2] *
    rtDW->UnitDelay_2_DSTATE[2]) + rtDW->UnitDelay_2_DSTATE[3] *
    rtDW->UnitDelay_2_DSTATE[3]);
  rtb_MatrixMultiply_idx_1 = rtb_Sum1_e_idx_1_tmp * rtDW->UnitDelay_2_DSTATE[1];
  rtb_MatrixMultiply_idx_2 = rtb_Sum1_e_idx_1_tmp * rtDW->UnitDelay_2_DSTATE[2];
  rtb_zPosEst_m = rtb_Sum1_e_idx_1_tmp * rtDW->UnitDelay_2_DSTATE[3];
  rtb_MatrixMultiply_idx_0 = rtb_Sum1_e_idx_1_tmp * rtDW->UnitDelay_2_DSTATE[0];
  rtb_Integrator_l = rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_0;
  rtb_rateCmd_rps = rtb_MatrixMultiply_idx_1 * rtb_MatrixMultiply_idx_1;
  rtb_Sum_a = rtb_MatrixMultiply_idx_2 * rtb_MatrixMultiply_idx_2;
  rtb_Filter_a = rtb_zPosEst_m * rtb_zPosEst_m;
  rtb_QuaternionstoDirectionCos_1 = ((rtb_Integrator_l + rtb_rateCmd_rps) -
    rtb_Sum_a) - rtb_Filter_a;
  rtb_QuaternionstoDirectionCosin[0] = rtb_QuaternionstoDirectionCos_1;
  rtb_QuaternionstoDirectionCos_0 = rtb_MatrixMultiply_idx_1 *
    rtb_MatrixMultiply_idx_2;
  rtb_Sum1_e_idx_1_tmp = rtb_MatrixMultiply_idx_0 * rtb_zPosEst_m;
  rtb_Integrator_d = (rtb_QuaternionstoDirectionCos_0 + rtb_Sum1_e_idx_1_tmp) *
    2.0;
  rtb_QuaternionstoDirectionCosin[3] = rtb_Integrator_d;
  rtb_Product1_o = rtb_MatrixMultiply_idx_1 * rtb_zPosEst_m;
  rtb_sqrt = rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_2;
  rtb_Product2_a = (rtb_Product1_o - rtb_sqrt) * 2.0;
  rtb_QuaternionstoDirectionCosin[6] = rtb_Product2_a;
  rtb_QuaternionstoDirectionCos_0 = (rtb_QuaternionstoDirectionCos_0 -
    rtb_Sum1_e_idx_1_tmp) * 2.0;
  rtb_QuaternionstoDirectionCosin[1] = rtb_QuaternionstoDirectionCos_0;
  rtb_Integrator_l -= rtb_rateCmd_rps;
  rtb_rateCmd_rps = (rtb_Integrator_l + rtb_Sum_a) - rtb_Filter_a;
  rtb_QuaternionstoDirectionCosin[4] = rtb_rateCmd_rps;
  rtb_Sum1_e_idx_1_tmp = rtb_MatrixMultiply_idx_2 * rtb_zPosEst_m;
  rtb_MatrixMultiply_idx_1 *= rtb_MatrixMultiply_idx_0;
  rtb_MatrixMultiply_idx_2 = (rtb_Sum1_e_idx_1_tmp + rtb_MatrixMultiply_idx_1) *
    2.0;
  rtb_QuaternionstoDirectionCosin[7] = rtb_MatrixMultiply_idx_2;
  rtb_Product1_o = (rtb_Product1_o + rtb_sqrt) * 2.0;
  rtb_QuaternionstoDirectionCosin[2] = rtb_Product1_o;
  rtb_Sum1_e_idx_1_tmp = (rtb_Sum1_e_idx_1_tmp - rtb_MatrixMultiply_idx_1) * 2.0;
  rtb_QuaternionstoDirectionCosin[5] = rtb_Sum1_e_idx_1_tmp;
  rtb_Integrator_l = (rtb_Integrator_l - rtb_Sum_a) + rtb_Filter_a;
  rtb_QuaternionstoDirectionCosin[8] = rtb_Integrator_l;

  /* Quat2Dcm: '<S407>/C-' incorporates:
   *  Math: '<S414>/Math Function'
   */
  rtb_MathFunction_k[0] = rtb_QuaternionstoDirectionCos_1;
  rtb_MathFunction_k[3] = rtb_Integrator_d;
  rtb_MathFunction_k[6] = rtb_Product2_a;
  rtb_MathFunction_k[1] = rtb_QuaternionstoDirectionCos_0;
  rtb_MathFunction_k[4] = rtb_rateCmd_rps;
  rtb_MathFunction_k[7] = rtb_MatrixMultiply_idx_2;
  rtb_MathFunction_k[2] = rtb_Product1_o;
  rtb_MathFunction_k[5] = rtb_Sum1_e_idx_1_tmp;
  rtb_MathFunction_k[8] = rtb_Integrator_l;

  /* DotProduct: '<S407>/Dot Product' */
  rtb_Integrator_l = 0.0;
  for (i = 0; i < 3; i++) {
    /* Sum: '<S411>/Sum' incorporates:
     *  Inport: '<Root>/sensor_bus'
     *  UnitDelay generated from: '<S406>/Unit Delay'
     */
    rtb_Filter_a = rtU_sensor_bus_e->wBdyMeas_rps[i] - rtDW->
      UnitDelay_14_DSTATE[i];
    rtb_wBdyEst_rps[i] = rtb_Filter_a;

    /* DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1' */
    uIdx = i << 1;
    rtb_rateCmd_rps = rtDW->DiscreteTransferFcn1_states[uIdx];
    rtb_Sum_a = rtDW->DiscreteTransferFcn1_states[uIdx + 1];
    rtb_zPosEst_m = (rtb_Filter_a - -0.7478 * rtb_rateCmd_rps) - rtb_Sum_a *
      0.2722;
    DiscreteTransferFcn1_tmp[i] = rtb_zPosEst_m;

    /* Gain: '<S407>/Gain1' incorporates:
     *  DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1'
     */
    rtb_rateCmd_rps = ((0.1311 * rtb_zPosEst_m + 0.2622 * rtb_rateCmd_rps) +
                       rtb_Sum_a * 0.1311) * 0.01;
    rtb_gyroFilt_rps[i] = rtb_rateCmd_rps;

    /* DotProduct: '<S407>/Dot Product' */
    rtb_Integrator_l += rtb_rateCmd_rps * rtb_rateCmd_rps;
  }

  /* Sqrt: '<S407>/Sqrt' */
  rtb_Filter_a = sqrt(rtb_Integrator_l);

  /* Gain: '<S407>/Gain2' */
  rtb_Integrator_l = 0.5 * rtb_Filter_a;

  /* Trigonometry: '<S407>/Cos' */
  rtb_Sum_o[0] = cos(rtb_Integrator_l);

  /* Trigonometry: '<S407>/Sin' */
  rtb_Integrator_l = sin(rtb_Integrator_l);
  for (i = 0; i < 3; i++) {
    /* Product: '<S407>/Divide' incorporates:
     *  Bias: '<S407>/Bias'
     */
    rtb_Sum_o[i + 1] = rtb_Integrator_l * rtb_gyroFilt_rps[i] / (rtb_Filter_a +
      1.0E-12);

    /* DiscreteTransferFcn: '<S424>/Gyro Filter' */
    uIdx = i << 1;
    rtb_rateCmd_rps = rtDW->GyroFilter_states[uIdx];
    rtb_Sum_a = rtDW->GyroFilter_states[uIdx + 1];
    rtb_zPosEst_m = (rtb_wBdyEst_rps[i] - 0.9428 * rtb_rateCmd_rps) - rtb_Sum_a *
      0.3333;
    GyroFilter_tmp[i] = rtb_zPosEst_m;
    rtb_gyroFilt_rps[i] = (0.569 * rtb_zPosEst_m + 1.1381 * rtb_rateCmd_rps) +
      rtb_Sum_a * 0.569;
  }

  /* Sum: '<S418>/Sum' incorporates:
   *  Product: '<S418>/Product'
   *  Product: '<S418>/Product1'
   *  Product: '<S418>/Product2'
   *  Product: '<S418>/Product3'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Integrator_l = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Sum_o[3] +
                       rtDW->UnitDelay_2_DSTATE[1] * rtb_Sum_o[2]) - rtb_Sum_o[1]
                      * rtDW->UnitDelay_2_DSTATE[2]) + rtb_Sum_o[0] *
    rtDW->UnitDelay_2_DSTATE[3];

  /* Sum: '<S415>/Sum' incorporates:
   *  Product: '<S415>/Product'
   *  Product: '<S415>/Product1'
   *  Product: '<S415>/Product2'
   *  Product: '<S415>/Product3'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Sum_a = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Sum_o[0] -
                rtDW->UnitDelay_2_DSTATE[1] * rtb_Sum_o[1]) -
               rtDW->UnitDelay_2_DSTATE[2] * rtb_Sum_o[2]) -
    rtDW->UnitDelay_2_DSTATE[3] * rtb_Sum_o[3];

  /* Sum: '<S416>/Sum' incorporates:
   *  Product: '<S416>/Product'
   *  Product: '<S416>/Product1'
   *  Product: '<S416>/Product2'
   *  Product: '<S416>/Product3'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Integrator_d = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Sum_o[1] + rtb_Sum_o[0]
                       * rtDW->UnitDelay_2_DSTATE[1]) + rtDW->
                      UnitDelay_2_DSTATE[2] * rtb_Sum_o[3]) - rtb_Sum_o[2] *
    rtDW->UnitDelay_2_DSTATE[3];

  /* Sum: '<S417>/Sum' incorporates:
   *  Product: '<S417>/Product'
   *  Product: '<S417>/Product1'
   *  Product: '<S417>/Product2'
   *  Product: '<S417>/Product3'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_rateCmd_rps = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Sum_o[2] -
                      rtDW->UnitDelay_2_DSTATE[1] * rtb_Sum_o[3]) + rtb_Sum_o[0]
                     * rtDW->UnitDelay_2_DSTATE[2]) + rtb_Sum_o[1] *
    rtDW->UnitDelay_2_DSTATE[3];

  /* Sqrt: '<S419>/sqrt' incorporates:
   *  Product: '<S420>/Product'
   *  Product: '<S420>/Product1'
   *  Product: '<S420>/Product2'
   *  Product: '<S420>/Product3'
   *  Sum: '<S420>/Sum'
   */
  rtb_Filter_a = sqrt(((rtb_Sum_a * rtb_Sum_a + rtb_Integrator_d *
                        rtb_Integrator_d) + rtb_rateCmd_rps * rtb_rateCmd_rps) +
                      rtb_Integrator_l * rtb_Integrator_l);

  /* Product: '<S413>/Product3' */
  rtb_Integrator_l /= rtb_Filter_a;

  /* Product: '<S413>/Product2' */
  rtb_rateCmd_rps /= rtb_Filter_a;

  /* Product: '<S413>/Product1' */
  rtb_Integrator_d /= rtb_Filter_a;

  /* Product: '<S413>/Product' */
  rtb_Filter_a = rtb_Sum_a / rtb_Filter_a;

  /* Quat2Dcm: '<S407>/C+' incorporates:
   *  Quat2Dcm: '<S427>/C-'
   *  SignalConversion generated from: '<S407>/C+'
   */
  rtb_Sum2 = 1.0 / sqrt(((rtb_Filter_a * rtb_Filter_a + rtb_Integrator_d *
    rtb_Integrator_d) + rtb_rateCmd_rps * rtb_rateCmd_rps) + rtb_Integrator_l *
                        rtb_Integrator_l);
  rtb_MatrixMultiply_idx_2 = rtb_Sum2 * rtb_Integrator_d;
  rtb_MatrixMultiply_idx_1 = rtb_Sum2 * rtb_rateCmd_rps;
  rtb_Sum_a = rtb_Sum2 * rtb_Integrator_l;
  rtb_MatrixMultiply_idx_0 = rtb_Sum2 * rtb_Filter_a;
  rtb_QuaternionstoDirectionCos_1 = rtb_MatrixMultiply_idx_0 *
    rtb_MatrixMultiply_idx_0;
  rtb_QuaternionstoDirectionCos_0 = rtb_MatrixMultiply_idx_2 *
    rtb_MatrixMultiply_idx_2;
  rtb_Sum1_e_idx_1_tmp = rtb_MatrixMultiply_idx_1 * rtb_MatrixMultiply_idx_1;
  rtb_zPosEst_m = rtb_Sum_a * rtb_Sum_a;
  rtb_Product1_o = ((rtb_QuaternionstoDirectionCos_1 +
                     rtb_QuaternionstoDirectionCos_0) - rtb_Sum1_e_idx_1_tmp) -
    rtb_zPosEst_m;
  rtb_C_l[0] = rtb_Product1_o;
  rtb_sqrt = rtb_MatrixMultiply_idx_2 * rtb_MatrixMultiply_idx_1;
  rtb_Product2_a = rtb_MatrixMultiply_idx_0 * rtb_Sum_a;
  rtb_Product1_g3 = (rtb_sqrt + rtb_Product2_a) * 2.0;
  rtb_C_l[3] = rtb_Product1_g3;
  rtb_Switch2 = rtb_MatrixMultiply_idx_2 * rtb_Sum_a;
  rtb_Product1_i = rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_1;
  rtb_Gain = (rtb_Switch2 - rtb_Product1_i) * 2.0;
  rtb_C_l[6] = rtb_Gain;
  rtb_sqrt = (rtb_sqrt - rtb_Product2_a) * 2.0;
  rtb_C_l[1] = rtb_sqrt;
  rtb_QuaternionstoDirectionCos_1 -= rtb_QuaternionstoDirectionCos_0;
  rtb_QuaternionstoDirectionCos_0 = (rtb_QuaternionstoDirectionCos_1 +
    rtb_Sum1_e_idx_1_tmp) - rtb_zPosEst_m;
  rtb_C_l[4] = rtb_QuaternionstoDirectionCos_0;
  rtb_Product2_a = rtb_MatrixMultiply_idx_1 * rtb_Sum_a;
  rtb_Sum_a = rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_2;
  rtb_MatrixMultiply_idx_1 = (rtb_Product2_a + rtb_Sum_a) * 2.0;
  rtb_C_l[7] = rtb_MatrixMultiply_idx_1;
  rtb_Switch2 = (rtb_Switch2 + rtb_Product1_i) * 2.0;
  rtb_C_l[2] = rtb_Switch2;
  rtb_Product2_a = (rtb_Product2_a - rtb_Sum_a) * 2.0;
  rtb_C_l[5] = rtb_Product2_a;
  rtb_QuaternionstoDirectionCos_1 = (rtb_QuaternionstoDirectionCos_1 -
    rtb_Sum1_e_idx_1_tmp) + rtb_zPosEst_m;
  rtb_C_l[8] = rtb_QuaternionstoDirectionCos_1;

  /* Quat2Dcm: '<S427>/C-' */
  rtb_C[0] = rtb_Product1_o;
  rtb_C[3] = rtb_Product1_g3;
  rtb_C[6] = rtb_Gain;
  rtb_C[1] = rtb_sqrt;
  rtb_C[4] = rtb_QuaternionstoDirectionCos_0;
  rtb_C[7] = rtb_MatrixMultiply_idx_1;
  rtb_C[2] = rtb_Switch2;
  rtb_C[5] = rtb_Product2_a;
  rtb_C[8] = rtb_QuaternionstoDirectionCos_1;

  /* UnitDelay generated from: '<S406>/Unit Delay' */
  rtb_flightMode_enum = rtDW->UnitDelay_1_DSTATE;

  /* If: '<S423>/If' incorporates:
   *  Constant: '<S428>/Constant'
   *  RelationalOperator: '<S428>/Compare'
   */
  if (rtb_flightMode_enum <= IDLE) {
    /* Outputs for IfAction SubSystem: '<S423>/Complementary Filter' incorporates:
     *  ActionPort: '<S429>/Action Port'
     */
    /* Product: '<S429>/Matrix Multiply' incorporates:
     *  Delay generated from: '<S429>/Delay'
     *  Gain: '<S429>/Gain2'
     *  Quat2Dcm: '<S429>/Quaternions to  Direction Cosine Matrix'
     */
    rtb_MatrixMultiply_idx_0 = 0.0;
    rtb_MatrixMultiply_idx_1 = 0.0;
    rtb_MatrixMultiply_idx_2 = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_zPosEst_m = -rtDW->Delay_3_DSTATE_e[i];
      rtb_MatrixMultiply_idx_0 += rtConstB.QuaternionstoDirectionCosin[3 * i] *
        rtb_zPosEst_m;
      rtb_MatrixMultiply_idx_1 += rtConstB.QuaternionstoDirectionCosin[3 * i + 1]
        * rtb_zPosEst_m;
      rtb_MatrixMultiply_idx_2 += rtConstB.QuaternionstoDirectionCosin[3 * i + 2]
        * rtb_zPosEst_m;
    }

    /* End of Product: '<S429>/Matrix Multiply' */

    /* Math: '<S431>/Math Function1' incorporates:
     *  Math: '<S431>/Math Function'
     *  Sum: '<S431>/Sum of Elements'
     *
     * About '<S431>/Math Function1':
     *  Operator: sqrt
     */
    rtb_zPosEst_m = sqrt((rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_0 +
                          rtb_MatrixMultiply_idx_1 * rtb_MatrixMultiply_idx_1) +
                         rtb_MatrixMultiply_idx_2 * rtb_MatrixMultiply_idx_2);

    /* Switch: '<S431>/Switch' incorporates:
     *  Constant: '<S431>/Constant'
     *  Product: '<S431>/Product'
     */
    if (!(rtb_zPosEst_m > 0.0)) {
      rtb_MatrixMultiply_idx_0 *= 0.0;
      rtb_MatrixMultiply_idx_1 *= 0.0;
      rtb_MatrixMultiply_idx_2 *= 0.0;
      rtb_zPosEst_m = 1.0;
    }

    /* End of Switch: '<S431>/Switch' */

    /* Product: '<S431>/Divide' */
    rtb_MatrixMultiply_idx_1 /= rtb_zPosEst_m;
    rtb_MatrixMultiply_idx_2 /= rtb_zPosEst_m;

    /* Angle2Quat: '<S433>/Rotation Angles to Quaternions' incorporates:
     *  Math: '<S429>/Square'
     *  Math: '<S429>/Square1'
     *  Product: '<S431>/Divide'
     *  Sqrt: '<S429>/Sqrt'
     *  Sum: '<S429>/Sum'
     *  Trigonometry: '<S429>/Atan1'
     *  Trigonometry: '<S429>/Atan2'
     *  UnaryMinus: '<S429>/Unary Minus'
     */
    rtb_QuaternionstoDirectionCos_1 = rt_atan2d_snf(rtb_MatrixMultiply_idx_1,
      rtb_MatrixMultiply_idx_2) / 2.0;
    rtb_Sum_a = cos(rtb_QuaternionstoDirectionCos_1);
    rtb_QuaternionstoDirectionCos_0 = rt_atan2d_snf(-(rtb_MatrixMultiply_idx_0 /
      rtb_zPosEst_m), sqrt(rtb_MatrixMultiply_idx_1 * rtb_MatrixMultiply_idx_1 +
      rtb_MatrixMultiply_idx_2 * rtb_MatrixMultiply_idx_2)) / 2.0;
    rtb_zPosEst_m = cos(rtb_QuaternionstoDirectionCos_0);
    rtb_Product1_o = sin(rtb_QuaternionstoDirectionCos_1);
    rtb_sqrt = sin(rtb_QuaternionstoDirectionCos_0);
    rtb_QuaternionstoDirectionCos_1 = rtb_Sum_a * rtb_zPosEst_m;
    rtb_QuaternionstoDirectionCos_0 = rtb_Product1_o * rtb_sqrt;
    rtb_MatrixMultiply_idx_0 = rtb_QuaternionstoDirectionCos_0 * 0.0 +
      rtb_QuaternionstoDirectionCos_1;
    rtb_Sum1_e_idx_1_tmp = rtb_Product1_o * rtb_zPosEst_m;
    rtb_Sum_a *= rtb_sqrt;
    rtb_MatrixMultiply_idx_1 = rtb_Sum1_e_idx_1_tmp - rtb_Sum_a * 0.0;
    rtb_MatrixMultiply_idx_2 = rtb_Sum1_e_idx_1_tmp * 0.0 + rtb_Sum_a;
    rtb_zPosEst_m = rtb_QuaternionstoDirectionCos_1 * 0.0 -
      rtb_QuaternionstoDirectionCos_0;

    /* Sum: '<S438>/Sum' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S438>/Product'
     *  Product: '<S438>/Product1'
     *  Sum: '<S440>/Sum'
     */
    rtb_QuaternionstoDirectionCos_1 = rtb_MatrixMultiply_idx_0 *
      0.7071067811860949 - rtb_MatrixMultiply_idx_1 * -0.0;

    /* Product: '<S438>/Product2' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S440>/Product2'
     */
    rtb_Sum1_e_idx_1_tmp = rtb_MatrixMultiply_idx_2 * 0.7071067811860949;

    /* Product: '<S438>/Product3' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S440>/Product3'
     */
    rtb_Product1_o = rtb_zPosEst_m * -0.0;

    /* Sum: '<S438>/Sum' incorporates:
     *  Product: '<S438>/Product2'
     *  Product: '<S438>/Product3'
     */
    rtb_Sum_a = (rtb_QuaternionstoDirectionCos_1 - rtb_Sum1_e_idx_1_tmp) -
      rtb_Product1_o;

    /* Sum: '<S439>/Sum' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S439>/Product'
     *  Product: '<S439>/Product1'
     *  Sum: '<S441>/Sum'
     */
    rtb_QuaternionstoDirectionCos_0 = rtb_MatrixMultiply_idx_0 * -0.0 +
      0.7071067811860949 * rtb_MatrixMultiply_idx_1;

    /* Product: '<S439>/Product2' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S441>/Product2'
     */
    rtb_MatrixMultiply_idx_1 = rtb_MatrixMultiply_idx_2 * -0.0;

    /* Product: '<S439>/Product3' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S441>/Product3'
     */
    rtb_MatrixMultiply_idx_2 = 0.7071067811860949 * rtb_zPosEst_m;

    /* Sum: '<S439>/Sum' incorporates:
     *  Product: '<S439>/Product2'
     *  Product: '<S439>/Product3'
     */
    rtb_zPosEst_m = (rtb_QuaternionstoDirectionCos_0 + rtb_MatrixMultiply_idx_1)
      - rtb_MatrixMultiply_idx_2;

    /* Sum: '<S440>/Sum' */
    rtb_Product2_a = (rtb_QuaternionstoDirectionCos_1 + rtb_Sum1_e_idx_1_tmp) +
      rtb_Product1_o;

    /* Sum: '<S441>/Sum' */
    rtb_Product1_o = (rtb_QuaternionstoDirectionCos_0 - rtb_MatrixMultiply_idx_1)
      + rtb_MatrixMultiply_idx_2;

    /* Sqrt: '<S442>/sqrt' incorporates:
     *  Product: '<S443>/Product'
     *  Product: '<S443>/Product1'
     *  Product: '<S443>/Product2'
     *  Product: '<S443>/Product3'
     *  Sum: '<S443>/Sum'
     */
    rtb_sqrt = sqrt(((rtb_Sum_a * rtb_Sum_a + rtb_zPosEst_m * rtb_zPosEst_m) +
                     rtb_Product2_a * rtb_Product2_a) + rtb_Product1_o *
                    rtb_Product1_o);

    /* Sum: '<S429>/Sum1' incorporates:
     *  Gain: '<S429>/Gain'
     *  Gain: '<S429>/Gain1'
     *  Product: '<S437>/Product'
     *  Product: '<S437>/Product1'
     *  Product: '<S437>/Product2'
     *  Product: '<S437>/Product3'
     */
    rtb_MatrixMultiply_idx_0 = rtb_Sum_a / rtb_sqrt * 0.010000000000000009 +
      0.99 * rtb_Filter_a;
    rtb_MatrixMultiply_idx_1 = rtb_zPosEst_m / rtb_sqrt * 0.010000000000000009 +
      0.99 * rtb_Integrator_d;
    rtb_MatrixMultiply_idx_2 = rtb_Product2_a / rtb_sqrt * 0.010000000000000009
      + 0.99 * rtb_rateCmd_rps;
    rtb_zPosEst_m = rtb_Product1_o / rtb_sqrt * 0.010000000000000009 + 0.99 *
      rtb_Integrator_l;

    /* Sqrt: '<S434>/sqrt' incorporates:
     *  Product: '<S435>/Product'
     *  Product: '<S435>/Product1'
     *  Product: '<S435>/Product2'
     *  Product: '<S435>/Product3'
     *  Sum: '<S435>/Sum'
     */
    rtb_sqrt = sqrt(((rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_0 +
                      rtb_MatrixMultiply_idx_1 * rtb_MatrixMultiply_idx_1) +
                     rtb_MatrixMultiply_idx_2 * rtb_MatrixMultiply_idx_2) +
                    rtb_zPosEst_m * rtb_zPosEst_m);

    /* Product: '<S432>/Product' incorporates:
     *  Merge: '<S423>/Merge'
     */
    rtDW->qEst_na[0] = rtb_MatrixMultiply_idx_0 / rtb_sqrt;

    /* Product: '<S432>/Product1' incorporates:
     *  Merge: '<S423>/Merge'
     */
    rtDW->qEst_na[1] = rtb_MatrixMultiply_idx_1 / rtb_sqrt;

    /* Product: '<S432>/Product2' incorporates:
     *  Merge: '<S423>/Merge'
     */
    rtDW->qEst_na[2] = rtb_MatrixMultiply_idx_2 / rtb_sqrt;

    /* Product: '<S432>/Product3' incorporates:
     *  Merge: '<S423>/Merge'
     */
    rtDW->qEst_na[3] = rtb_zPosEst_m / rtb_sqrt;

    /* Update for Delay generated from: '<S429>/Delay' incorporates:
     *  Inport: '<Root>/sensor_bus'
     */
    for (i = 0; i < 9; i++) {
      uIdx = (i + 1) * 3;
      rtDW->Delay_3_DSTATE_e[i * 3] = rtDW->Delay_3_DSTATE_e[uIdx];
      rtDW->Delay_3_DSTATE_e[i * 3 + 1] = rtDW->Delay_3_DSTATE_e[uIdx + 1];
      rtDW->Delay_3_DSTATE_e[i * 3 + 2] = rtDW->Delay_3_DSTATE_e[uIdx + 2];
    }

    rtDW->Delay_3_DSTATE_e[27] = rtU_sensor_bus_e->fBdyMeas_mps2[0];
    rtDW->Delay_3_DSTATE_e[28] = rtU_sensor_bus_e->fBdyMeas_mps2[1];
    rtDW->Delay_3_DSTATE_e[29] = rtU_sensor_bus_e->fBdyMeas_mps2[2];

    /* End of Update for Delay generated from: '<S429>/Delay' */
    /* End of Outputs for SubSystem: '<S423>/Complementary Filter' */
  } else {
    /* Outputs for IfAction SubSystem: '<S423>/Pass Through' incorporates:
     *  ActionPort: '<S430>/Action Port'
     */
    /* Merge: '<S423>/Merge' incorporates:
     *  SignalConversion generated from: '<S430>/qEst_na'
     */
    rtDW->qEst_na[0] = rtb_Filter_a;
    rtDW->qEst_na[1] = rtb_Integrator_d;
    rtDW->qEst_na[2] = rtb_rateCmd_rps;
    rtDW->qEst_na[3] = rtb_Integrator_l;

    /* End of Outputs for SubSystem: '<S423>/Pass Through' */
  }

  /* End of If: '<S423>/If' */

  /* Product: '<S445>/Product1' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S447>/Product1'
   */
  rtb_Integrator_l = rtDW->qEst_na[1] * 0.0;

  /* Product: '<S445>/Product3' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S447>/Product3'
   */
  rtb_rateCmd_rps = rtDW->qEst_na[3] * 0.0;

  /* SignalConversion generated from: '<S425>/Quaternions to Rotation Angles' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S445>/Product'
   *  Product: '<S445>/Product1'
   *  Product: '<S445>/Product2'
   *  Product: '<S445>/Product3'
   *  Sum: '<S445>/Sum'
   */
  rtb_Sum_o[0] = ((rtDW->qEst_na[0] * 0.707106781187 - rtb_Integrator_l) -
                  rtDW->qEst_na[2] * -0.707106781187) - rtb_rateCmd_rps;

  /* Product: '<S446>/Product' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S448>/Product'
   */
  rtb_Sum_a = rtDW->qEst_na[0] * 0.0;

  /* Product: '<S446>/Product2' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S448>/Product2'
   */
  rtb_Filter_a = rtDW->qEst_na[2] * 0.0;

  /* SignalConversion generated from: '<S425>/Quaternions to Rotation Angles' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S446>/Product'
   *  Product: '<S446>/Product1'
   *  Product: '<S446>/Product2'
   *  Product: '<S446>/Product3'
   *  Product: '<S447>/Product'
   *  Product: '<S447>/Product2'
   *  Product: '<S448>/Product1'
   *  Product: '<S448>/Product3'
   *  Sum: '<S446>/Sum'
   *  Sum: '<S447>/Sum'
   *  Sum: '<S448>/Sum'
   */
  rtb_Sum_o[1] = ((0.707106781187 * rtDW->qEst_na[1] + rtb_Sum_a) + rtb_Filter_a)
    - -0.707106781187 * rtDW->qEst_na[3];
  rtb_Sum_o[2] = ((rtDW->qEst_na[0] * -0.707106781187 - rtb_Integrator_l) +
                  0.707106781187 * rtDW->qEst_na[2]) + rtb_rateCmd_rps;
  rtb_Sum_o[3] = ((rtDW->qEst_na[1] * -0.707106781187 + rtb_Sum_a) -
                  rtb_Filter_a) + 0.707106781187 * rtDW->qEst_na[3];

  /* Quat2Angle: '<S425>/Quaternions to Rotation Angles' */
  rtb_UkYk1_h = 1.0 / sqrt(((rtb_Sum_o[0] * rtb_Sum_o[0] + rtb_Sum_o[1] *
    rtb_Sum_o[1]) + rtb_Sum_o[2] * rtb_Sum_o[2]) + rtb_Sum_o[3] * rtb_Sum_o[3]);
  rtb_MatrixMultiply_idx_0 = rtb_UkYk1_h * rtb_Sum_o[0];
  rtb_MatrixMultiply_idx_2 = rtb_UkYk1_h * rtb_Sum_o[1];
  rtb_MatrixMultiply_idx_1 = rtb_UkYk1_h * rtb_Sum_o[2];
  rtb_Sum_a = rtb_UkYk1_h * rtb_Sum_o[3];
  rtb_UkYk1_h = rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_0;
  rtb_QuaternionstoDirectionCos_1 = rtb_MatrixMultiply_idx_2 *
    rtb_MatrixMultiply_idx_2;
  rtb_Integrator_l = rtb_MatrixMultiply_idx_1 * rtb_MatrixMultiply_idx_1;
  rtb_rateCmd_rps = rtb_Sum_a * rtb_Sum_a;
  rtb_Integrator_d = ((rtb_UkYk1_h + rtb_QuaternionstoDirectionCos_1) -
                      rtb_Integrator_l) - rtb_rateCmd_rps;
  rtb_QuaternionstoDirectionCos_0 = rtb_MatrixMultiply_idx_2 *
    rtb_MatrixMultiply_idx_1;
  rtb_Sum1_e_idx_1_tmp = rtb_MatrixMultiply_idx_0 * rtb_Sum_a;
  rtb_Product1_o = (rtb_QuaternionstoDirectionCos_0 + rtb_Sum1_e_idx_1_tmp) *
    2.0;
  rtb_zPosEst_m = rtb_MatrixMultiply_idx_2 * rtb_Sum_a;
  rtb_Filter_a = rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_1;
  rtb_Product2_a = (rtb_zPosEst_m - rtb_Filter_a) * 2.0;
  rtb_sqrt = (rtb_QuaternionstoDirectionCos_0 - rtb_Sum1_e_idx_1_tmp) * 2.0;
  rtb_QuaternionstoDirectionCos_1 = rtb_UkYk1_h -
    rtb_QuaternionstoDirectionCos_1;
  rtb_Product1_g3 = (rtb_QuaternionstoDirectionCos_1 + rtb_Integrator_l) -
    rtb_rateCmd_rps;
  rtb_NProdOut_k = rtb_MatrixMultiply_idx_1 * rtb_Sum_a;
  rtb_Sum_a = rtb_MatrixMultiply_idx_0 * rtb_MatrixMultiply_idx_2;
  rtb_Switch2 = (rtb_NProdOut_k + rtb_Sum_a) * 2.0;
  rtb_MatrixMultiply_idx_1 = (rtb_zPosEst_m + rtb_Filter_a) * 2.0;
  rtb_Product1_i = (rtb_NProdOut_k - rtb_Sum_a) * 2.0;
  rtb_Gain = (rtb_QuaternionstoDirectionCos_1 - rtb_Integrator_l) +
    rtb_rateCmd_rps;
  if (-rtb_Product2_a <= -1.0) {
    rtb_Filter_a = -1.0;
  } else if (-rtb_Product2_a >= 1.0) {
    rtb_Filter_a = 1.0;
  } else {
    rtb_Filter_a = -rtb_Product2_a;
  }

  rtb_QuaternionstoDirectionCos_1 = asin(rtb_Filter_a);
  if (fabs(rtb_Filter_a) == 1.0) {
    Switch1[0] = rt_atan2d_snf(-rtb_sqrt, rtb_Product1_g3);
    rtb_QuaternionstoDirectionCos_0 = 0.0;
    rtb_Sum1_e_idx_1_tmp = 0.0;
  } else {
    rtb_QuaternionstoDirectionCos_0 = rt_atan2d_snf(rtb_Product1_o,
      rtb_Integrator_d);
    rtb_Sum1_e_idx_1_tmp = rt_atan2d_snf(rtb_Switch2, rtb_Gain);
    Switch1[0] = 0.0;
  }

  rtb_Sum_a = cos(rtb_Sum1_e_idx_1_tmp);
  rtb_Filter_a = sin(rtb_Sum1_e_idx_1_tmp);
  rtb_Integrator_l = cos(rtb_QuaternionstoDirectionCos_1);
  rtb_rateCmd_rps = sin(rtb_QuaternionstoDirectionCos_1);
  rtb_UkYk1_h = 0.0 * rtb_rateCmd_rps;
  rtb_MatrixMultiply_idx_0 = rtb_UkYk1_h + rtb_Integrator_l;
  rtb_zPosEst_m = 0.0 * rtb_Integrator_l;
  rtb_Product1_k = rtb_zPosEst_m - rtb_rateCmd_rps;
  rtb_Sum2 = rtb_Sum_a * 0.0;
  rtb_MatrixMultiply_idx_2 = (rtb_zPosEst_m + rtb_Sum2) + rtb_Filter_a *
    rtb_rateCmd_rps;
  rtb_Switch2_f = rtb_Filter_a * 0.0 + rtb_Sum_a;
  rtb_NProdOut_k = 0.0 * -rtb_rateCmd_rps;
  rtb_Product1_nt = (rtb_NProdOut_k + rtb_Sum2) + rtb_Filter_a *
    rtb_Integrator_l;
  rtb_deltafalllimit_fs = -rtb_Filter_a * 0.0;
  rtb_Switch2_m = (rtb_zPosEst_m + rtb_deltafalllimit_fs) + rtb_rateCmd_rps *
    rtb_Sum_a;
  rtb_Sum2 -= rtb_Filter_a;
  rtb_deltafalllimit_fs = (rtb_NProdOut_k + rtb_deltafalllimit_fs) + rtb_Sum_a *
    rtb_Integrator_l;
  rtb_Sum_a = cos(rtb_QuaternionstoDirectionCos_0);
  rtb_Filter_a = sin(rtb_QuaternionstoDirectionCos_0);
  rtb_UkYk1_h += rtb_zPosEst_m;
  rtb_Switch2_j = rtb_NProdOut_k + rtb_zPosEst_m;
  rtb_UkYk1_b = rtb_zPosEst_m + rtb_rateCmd_rps;
  rtb_NProdOut_k += rtb_Integrator_l;
  rtb_Integrator_l = cos(Switch1[0]);
  rtb_rateCmd_rps = sin(Switch1[0]);
  rtb_zPosEst_m = rtb_Product1_k * 0.0;
  rtb_deltafalllimit = rtb_Switch2_j * 0.0;
  rtb_UkYk1_g = 0.0 * -rtb_rateCmd_rps;
  rtb_accelBias_mps2_idx_0 = 0.0 * rtb_Integrator_l;
  rtb_accelBias_mps2_idx_1 = rtb_NProdOut_k * 0.0;
  rtb_Product2_a = fabs(rtb_Product2_a - (rtb_MatrixMultiply_idx_0 * 0.0 +
    rtb_Product1_k));
  rtb_Product1_k = rtb_Product1_nt * 0.0;
  rtb_accelBias_mps2_idx_2 = rtb_deltafalllimit_fs * 0.0;
  if ((((((((fabs(rtb_Integrator_d - ((rtb_MatrixMultiply_idx_0 *
                rtb_Integrator_l + rtb_UkYk1_g) + rtb_zPosEst_m)) + fabs
             (rtb_Product1_o - ((rtb_MatrixMultiply_idx_0 * rtb_rateCmd_rps +
                rtb_accelBias_mps2_idx_0) + rtb_zPosEst_m))) + rtb_Product2_a) +
           fabs(rtb_sqrt - ((rtb_Integrator_l * rtb_UkYk1_h - rtb_rateCmd_rps) +
             rtb_deltafalllimit))) + fabs(rtb_Product1_g3 - ((rtb_rateCmd_rps *
             rtb_UkYk1_h + rtb_Integrator_l) + rtb_deltafalllimit))) + fabs
         (rtb_Switch2 - (rtb_UkYk1_h * 0.0 + rtb_Switch2_j))) + fabs
        (rtb_MatrixMultiply_idx_1 - ((rtb_Integrator_l * rtb_UkYk1_b +
           rtb_UkYk1_g) + rtb_accelBias_mps2_idx_1))) + fabs(rtb_Product1_i -
        ((rtb_rateCmd_rps * rtb_UkYk1_b + rtb_accelBias_mps2_idx_0) +
         rtb_accelBias_mps2_idx_1))) + fabs(rtb_Gain - (rtb_UkYk1_b * 0.0 +
        rtb_NProdOut_k)) <= (((((((fabs(rtb_Integrator_d -
              ((rtb_MatrixMultiply_idx_0 * rtb_Sum_a + 0.0 * -rtb_Filter_a) +
               rtb_zPosEst_m)) + fabs(rtb_Product1_o -
              ((rtb_MatrixMultiply_idx_0 * rtb_Filter_a + 0.0 * rtb_Sum_a) +
               rtb_zPosEst_m))) + rtb_Product2_a) + fabs(rtb_sqrt - ((rtb_Sum_a *
              rtb_MatrixMultiply_idx_2 + -rtb_Filter_a * rtb_Switch2_f) +
             rtb_Product1_k))) + fabs(rtb_Product1_g3 - ((rtb_Filter_a *
             rtb_MatrixMultiply_idx_2 + rtb_Switch2_f * rtb_Sum_a) +
            rtb_Product1_k))) + fabs(rtb_Switch2 - ((rtb_MatrixMultiply_idx_2 *
            0.0 + rtb_Switch2_f * 0.0) + rtb_Product1_nt))) + fabs
        (rtb_MatrixMultiply_idx_1 - ((rtb_Sum_a * rtb_Switch2_m + -rtb_Filter_a *
           rtb_Sum2) + rtb_accelBias_mps2_idx_2))) + fabs(rtb_Product1_i -
        ((rtb_Filter_a * rtb_Switch2_m + rtb_Sum_a * rtb_Sum2) +
         rtb_accelBias_mps2_idx_2))) + fabs(rtb_Gain - ((rtb_Switch2_m * 0.0 +
         rtb_Sum2 * 0.0) + rtb_deltafalllimit_fs))) {
    rtb_QuaternionstoDirectionCos_0 = Switch1[0];
    rtb_Sum1_e_idx_1_tmp = 0.0;
  }

  /* Product: '<S327>/NProd Out' incorporates:
   *  Constant: '<S224>/Constant4'
   *  Constant: '<S2>/Constant'
   *  DiscreteIntegrator: '<S319>/Filter'
   *  Product: '<S317>/DProd Out'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum2'
   *  Sum: '<S319>/SumD'
   */
  rtb_Integrator_l = ((0.0 - rtb_QuaternionstoDirectionCos_0) * 0.0 -
                      rtDW->Filter_DSTATE) * 100.0;

  /* Product: '<S286>/Product1' incorporates:
   *  Constant: '<S224>/Constant4'
   *  Constant: '<S2>/Constant'
   *  DiscreteIntegrator: '<S324>/Integrator'
   *  Product: '<S329>/PProd Out'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum2'
   *  Sum: '<S333>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_g3 = (((0.0 - rtb_QuaternionstoDirectionCos_0) * 4.0 +
                      rtDW->Integrator_DSTATE) + rtb_Integrator_l) * (real_T)
    rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S345>/Switch2' incorporates:
   *  Constant: '<S224>/Constant2'
   *  Constant: '<S224>/Constant3'
   *  RelationalOperator: '<S345>/LowerRelop1'
   *  RelationalOperator: '<S345>/UpperRelop'
   *  Switch: '<S345>/Switch'
   */
  if (rtb_Product1_g3 > 2.0) {
    rtb_Switch2 = 2.0;
  } else if (rtb_Product1_g3 < -2.0) {
    /* Switch: '<S345>/Switch' incorporates:
     *  Constant: '<S224>/Constant3'
     */
    rtb_Switch2 = -2.0;
  } else {
    rtb_Switch2 = rtb_Product1_g3;
  }

  /* End of Switch: '<S345>/Switch2' */

  /* Delay: '<S343>/Delay' */
  if (rtDW->icLoad) {
    rtDW->Delay_DSTATE = rtb_Switch2;
  }

  /* Product: '<S343>/delta rise limit' incorporates:
   *  Constant: '<S224>/Constant'
   *  SampleTimeMath: '<S343>/sample time'
   *
   * About '<S343>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_rateCmd_rps = 0.05;

  /* Sum: '<S343>/Difference Inputs1' incorporates:
   *  Delay: '<S343>/Delay'
   *
   * Block description for '<S343>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Sum_a = rtb_Switch2 - rtDW->Delay_DSTATE;

  /* Switch: '<S344>/Switch2' incorporates:
   *  RelationalOperator: '<S344>/LowerRelop1'
   */
  if (!(rtb_Sum_a > 0.05)) {
    /* Switch: '<S344>/Switch' incorporates:
     *  RelationalOperator: '<S344>/UpperRelop'
     */
    if (rtb_Sum_a < -0.05) {
      rtb_rateCmd_rps = -0.05;
    } else {
      rtb_rateCmd_rps = rtb_Sum_a;
    }

    /* End of Switch: '<S344>/Switch' */
  }

  /* End of Switch: '<S344>/Switch2' */

  /* Sum: '<S343>/Difference Inputs2' incorporates:
   *  Delay: '<S343>/Delay'
   *
   * Block description for '<S343>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_rateCmd_rps += rtDW->Delay_DSTATE;

  /* Sum: '<S8>/Sum' incorporates:
   *  UnaryMinus: '<S224>/Unary Minus'
   */
  rtb_Sum_a = -rtb_rateCmd_rps - rtb_gyroFilt_rps[0];

  /* Product: '<S125>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S117>/Filter'
   *  Product: '<S115>/DProd Out'
   *  Sum: '<S117>/SumD'
   */
  rtb_Integrator_d = rtb_Sum_a * 0.0 - rtDW->Filter_DSTATE_p;

  /* Product: '<S82>/Product1' incorporates:
   *  DiscreteIntegrator: '<S122>/Integrator'
   *  Product: '<S127>/PProd Out'
   *  Sum: '<S131>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_i = ((rtb_Sum_a * 3.5999999999999996 + rtDW->Integrator_DSTATE_b)
                    + rtb_Integrator_d) * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Gain: '<S84>/Gain' */
  rtb_Gain = 0.5 * rtb_Product1_i;

  /* Switch: '<S151>/Switch2' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant3'
   *  RelationalOperator: '<S151>/LowerRelop1'
   *  RelationalOperator: '<S151>/UpperRelop'
   *  Switch: '<S151>/Switch'
   */
  if (rtb_Gain > 5.0) {
    rtb_Switch2_f = 5.0;
  } else if (rtb_Gain < -5.0) {
    /* Switch: '<S151>/Switch' incorporates:
     *  Constant: '<S10>/Constant3'
     */
    rtb_Switch2_f = -5.0;
  } else {
    rtb_Switch2_f = rtb_Gain;
  }

  /* End of Switch: '<S151>/Switch2' */

  /* Delay: '<S149>/Delay' */
  if (rtDW->icLoad_k) {
    rtDW->Delay_DSTATE_p = rtb_Switch2_f;
  }

  /* Product: '<S149>/delta rise limit' incorporates:
   *  Constant: '<S10>/Constant'
   *  SampleTimeMath: '<S149>/sample time'
   *
   * About '<S149>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_zPosEst_m = 0.9;

  /* Sum: '<S149>/Difference Inputs1' incorporates:
   *  Delay: '<S149>/Delay'
   *
   * Block description for '<S149>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Product2_a = rtb_Switch2_f - rtDW->Delay_DSTATE_p;

  /* Switch: '<S150>/Switch2' incorporates:
   *  RelationalOperator: '<S150>/LowerRelop1'
   */
  if (!(rtb_Product2_a > 0.9)) {
    /* Switch: '<S150>/Switch' incorporates:
     *  RelationalOperator: '<S150>/UpperRelop'
     */
    if (rtb_Product2_a < -0.9) {
      rtb_zPosEst_m = -0.9;
    } else {
      rtb_zPosEst_m = rtb_Product2_a;
    }

    /* End of Switch: '<S150>/Switch' */
  }

  /* End of Switch: '<S150>/Switch2' */

  /* Sum: '<S149>/Difference Inputs2' incorporates:
   *  Delay: '<S149>/Delay'
   *
   * Block description for '<S149>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_Product2_a = rtb_zPosEst_m + rtDW->Delay_DSTATE_p;

  /* Product: '<S267>/NProd Out' incorporates:
   *  Constant: '<S223>/Constant4'
   *  Constant: '<S2>/Constant1'
   *  DiscreteIntegrator: '<S259>/Filter'
   *  Product: '<S257>/DProd Out'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum1'
   *  Sum: '<S259>/SumD'
   */
  rtb_Product1_o = (0.0 - rtb_QuaternionstoDirectionCos_1) * 0.0 -
    rtDW->Filter_DSTATE_n;

  /* Product: '<S226>/Product1' incorporates:
   *  Constant: '<S223>/Constant4'
   *  Constant: '<S2>/Constant1'
   *  DiscreteIntegrator: '<S264>/Integrator'
   *  Product: '<S269>/PProd Out'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum1'
   *  Sum: '<S273>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_nt = (((0.0 - rtb_QuaternionstoDirectionCos_1) * 2.0 +
                      rtDW->Integrator_DSTATE_g) + rtb_Product1_o) * (real_T)
    rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S285>/Switch2' incorporates:
   *  Constant: '<S223>/Constant2'
   *  Constant: '<S223>/Constant3'
   *  RelationalOperator: '<S285>/LowerRelop1'
   *  RelationalOperator: '<S285>/UpperRelop'
   *  Switch: '<S285>/Switch'
   */
  if (rtb_Product1_nt > 0.25) {
    rtb_Switch2_m = 0.25;
  } else if (rtb_Product1_nt < -0.25) {
    /* Switch: '<S285>/Switch' incorporates:
     *  Constant: '<S223>/Constant3'
     */
    rtb_Switch2_m = -0.25;
  } else {
    rtb_Switch2_m = rtb_Product1_nt;
  }

  /* End of Switch: '<S285>/Switch2' */

  /* Delay: '<S283>/Delay' */
  if (rtDW->icLoad_a) {
    rtDW->Delay_DSTATE_c = rtb_Switch2_m;
  }

  /* Product: '<S283>/delta rise limit' incorporates:
   *  Constant: '<S223>/Constant'
   *  SampleTimeMath: '<S283>/sample time'
   *
   * About '<S283>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Sum2 = 0.005;

  /* Sum: '<S283>/Difference Inputs1' incorporates:
   *  Delay: '<S283>/Delay'
   *
   * Block description for '<S283>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_sqrt = rtb_Switch2_m - rtDW->Delay_DSTATE_c;

  /* Switch: '<S284>/Switch2' incorporates:
   *  RelationalOperator: '<S284>/LowerRelop1'
   */
  if (!(rtb_sqrt > 0.005)) {
    /* Switch: '<S284>/Switch' incorporates:
     *  RelationalOperator: '<S284>/UpperRelop'
     */
    if (rtb_sqrt < -0.005) {
      rtb_Sum2 = -0.005;
    } else {
      rtb_Sum2 = rtb_sqrt;
    }

    /* End of Switch: '<S284>/Switch' */
  }

  /* End of Switch: '<S284>/Switch2' */

  /* Sum: '<S283>/Difference Inputs2' incorporates:
   *  Delay: '<S283>/Delay'
   *
   * Block description for '<S283>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_sqrt = rtb_Sum2 + rtDW->Delay_DSTATE_c;

  /* Sum: '<S8>/Sum2' */
  rtb_Sum2 = rtb_sqrt - rtb_gyroFilt_rps[1];

  /* Product: '<S55>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S47>/Filter'
   *  Product: '<S45>/DProd Out'
   *  Sum: '<S47>/SumD'
   */
  rtb_deltafalllimit_fs = (rtb_Sum2 * 0.0 - rtDW->Filter_DSTATE_l) * 10.0;

  /* Product: '<S12>/Product1' incorporates:
   *  DiscreteIntegrator: '<S52>/Integrator'
   *  Product: '<S57>/PProd Out'
   *  Sum: '<S61>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_k = ((rtb_Sum2 * 1200.0 + rtDW->Integrator_DSTATE_p) +
                    rtb_deltafalllimit_fs) * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S14>/Divide' incorporates:
   *  Constant: '<S410>/Constant1'
   *  Gain: '<S14>/Gain'
   */
  rtb_Filter_a = -6756.0 * rtb_Product1_k / 100000.0;

  /* Switch: '<S81>/Switch2' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  RelationalOperator: '<S81>/LowerRelop1'
   *  RelationalOperator: '<S81>/UpperRelop'
   *  Switch: '<S81>/Switch'
   */
  if (rtb_Filter_a > 45.0) {
    rtb_Switch2_j = 45.0;
  } else if (rtb_Filter_a < -45.0) {
    /* Switch: '<S81>/Switch' incorporates:
     *  Constant: '<S9>/Constant3'
     */
    rtb_Switch2_j = -45.0;
  } else {
    rtb_Switch2_j = rtb_Filter_a;
  }

  /* End of Switch: '<S81>/Switch2' */

  /* Delay: '<S79>/Delay' */
  if (rtDW->icLoad_f) {
    rtDW->Delay_DSTATE_f = rtb_Switch2_j;
  }

  /* Product: '<S79>/delta rise limit' incorporates:
   *  Constant: '<S9>/Constant'
   *  SampleTimeMath: '<S79>/sample time'
   *
   * About '<S79>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_MatrixMultiply_idx_1 = 1.8;

  /* Sum: '<S79>/Difference Inputs1' incorporates:
   *  Delay: '<S79>/Delay'
   *
   * Block description for '<S79>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_h = rtb_Switch2_j - rtDW->Delay_DSTATE_f;

  /* Switch: '<S80>/Switch2' incorporates:
   *  RelationalOperator: '<S80>/LowerRelop1'
   */
  if (!(rtb_UkYk1_h > 1.8)) {
    /* Switch: '<S80>/Switch' incorporates:
     *  RelationalOperator: '<S80>/UpperRelop'
     */
    if (rtb_UkYk1_h < -1.8) {
      rtb_MatrixMultiply_idx_1 = -1.8;
    } else {
      rtb_MatrixMultiply_idx_1 = rtb_UkYk1_h;
    }

    /* End of Switch: '<S80>/Switch' */
  }

  /* End of Switch: '<S80>/Switch2' */

  /* Sum: '<S79>/Difference Inputs2' incorporates:
   *  Delay: '<S79>/Delay'
   *
   * Block description for '<S79>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_UkYk1_h = rtb_MatrixMultiply_idx_1 + rtDW->Delay_DSTATE_f;

  /* Product: '<S387>/NProd Out' incorporates:
   *  Constant: '<S225>/Constant4'
   *  Constant: '<S2>/Constant2'
   *  DiscreteIntegrator: '<S379>/Filter'
   *  Product: '<S377>/DProd Out'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum'
   *  Sum: '<S379>/SumD'
   */
  rtb_NProdOut_k = (0.0 - rtb_Sum1_e_idx_1_tmp) * 0.0 - rtDW->Filter_DSTATE_c;

  /* Product: '<S346>/Product1' incorporates:
   *  Constant: '<S225>/Constant4'
   *  Constant: '<S2>/Constant2'
   *  DiscreteIntegrator: '<S384>/Integrator'
   *  Product: '<S389>/PProd Out'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum'
   *  Sum: '<S393>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_ek = (((0.0 - rtb_Sum1_e_idx_1_tmp) * 2.0 +
                      rtDW->Integrator_DSTATE_l) + rtb_NProdOut_k) * (real_T)
    rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S405>/Switch2' incorporates:
   *  Constant: '<S225>/Constant2'
   *  Constant: '<S225>/Constant3'
   *  RelationalOperator: '<S405>/LowerRelop1'
   *  RelationalOperator: '<S405>/UpperRelop'
   *  Switch: '<S405>/Switch'
   */
  if (rtb_Product1_ek > 0.25) {
    rtb_Switch2_d = 0.25;
  } else if (rtb_Product1_ek < -0.25) {
    /* Switch: '<S405>/Switch' incorporates:
     *  Constant: '<S225>/Constant3'
     */
    rtb_Switch2_d = -0.25;
  } else {
    rtb_Switch2_d = rtb_Product1_ek;
  }

  /* End of Switch: '<S405>/Switch2' */

  /* Delay: '<S403>/Delay' */
  if (rtDW->icLoad_c) {
    rtDW->Delay_DSTATE_h = rtb_Switch2_d;
  }

  /* Product: '<S403>/delta rise limit' incorporates:
   *  Constant: '<S225>/Constant'
   *  SampleTimeMath: '<S403>/sample time'
   *
   * About '<S403>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Sum1_j = 0.005;

  /* Sum: '<S403>/Difference Inputs1' incorporates:
   *  Delay: '<S403>/Delay'
   *
   * Block description for '<S403>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_b = rtb_Switch2_d - rtDW->Delay_DSTATE_h;

  /* Switch: '<S404>/Switch2' incorporates:
   *  RelationalOperator: '<S404>/LowerRelop1'
   */
  if (!(rtb_UkYk1_b > 0.005)) {
    /* Switch: '<S404>/Switch' incorporates:
     *  RelationalOperator: '<S404>/UpperRelop'
     */
    if (rtb_UkYk1_b < -0.005) {
      rtb_Sum1_j = -0.005;
    } else {
      rtb_Sum1_j = rtb_UkYk1_b;
    }

    /* End of Switch: '<S404>/Switch' */
  }

  /* End of Switch: '<S404>/Switch2' */

  /* Sum: '<S403>/Difference Inputs2' incorporates:
   *  Delay: '<S403>/Delay'
   *
   * Block description for '<S403>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_UkYk1_b = rtb_Sum1_j + rtDW->Delay_DSTATE_h;

  /* Sum: '<S8>/Sum1' */
  rtb_Sum1_j = rtb_UkYk1_b - rtb_gyroFilt_rps[2];

  /* Product: '<S195>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S187>/Filter'
   *  Product: '<S185>/DProd Out'
   *  Sum: '<S187>/SumD'
   */
  rtb_deltafalllimit = (rtb_Sum1_j * 0.0 - rtDW->Filter_DSTATE_g) * 10.0;

  /* Product: '<S152>/Product1' incorporates:
   *  DiscreteIntegrator: '<S192>/Integrator'
   *  Product: '<S197>/PProd Out'
   *  Sum: '<S201>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_l = ((rtb_Sum1_j * 1200.0 + rtDW->Integrator_DSTATE_e) +
                    rtb_deltafalllimit) * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S154>/Divide' incorporates:
   *  Constant: '<S410>/Constant1'
   *  Gain: '<S154>/Gain'
   */
  rtb_Divide_l = -6756.0 * rtb_Product1_l / 100000.0;

  /* Switch: '<S221>/Switch2' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Constant: '<S11>/Constant3'
   *  RelationalOperator: '<S221>/LowerRelop1'
   *  RelationalOperator: '<S221>/UpperRelop'
   *  Switch: '<S221>/Switch'
   */
  if (rtb_Divide_l > 45.0) {
    rtb_Switch2_b = 45.0;
  } else if (rtb_Divide_l < -45.0) {
    /* Switch: '<S221>/Switch' incorporates:
     *  Constant: '<S11>/Constant3'
     */
    rtb_Switch2_b = -45.0;
  } else {
    rtb_Switch2_b = rtb_Divide_l;
  }

  /* End of Switch: '<S221>/Switch2' */

  /* Delay: '<S219>/Delay' */
  if (rtDW->icLoad_d) {
    rtDW->Delay_DSTATE_e = rtb_Switch2_b;
  }

  /* Product: '<S219>/delta rise limit' incorporates:
   *  Constant: '<S11>/Constant'
   *  SampleTimeMath: '<S219>/sample time'
   *
   * About '<S219>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_zPosEst_m = 1.8;

  /* Sum: '<S219>/Difference Inputs1' incorporates:
   *  Delay: '<S219>/Delay'
   *
   * Block description for '<S219>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_g = rtb_Switch2_b - rtDW->Delay_DSTATE_e;

  /* Switch: '<S220>/Switch2' incorporates:
   *  RelationalOperator: '<S220>/LowerRelop1'
   */
  if (!(rtb_UkYk1_g > 1.8)) {
    /* Switch: '<S220>/Switch' incorporates:
     *  RelationalOperator: '<S220>/UpperRelop'
     */
    if (rtb_UkYk1_g < -1.8) {
      rtb_zPosEst_m = -1.8;
    } else {
      rtb_zPosEst_m = rtb_UkYk1_g;
    }

    /* End of Switch: '<S220>/Switch' */
  }

  /* End of Switch: '<S220>/Switch2' */

  /* Sum: '<S219>/Difference Inputs2' incorporates:
   *  Delay: '<S219>/Delay'
   *
   * Block description for '<S219>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_UkYk1_g = rtb_zPosEst_m + rtDW->Delay_DSTATE_e;

  /* Sum: '<S5>/Sum' incorporates:
   *  Product: '<S5>/Product'
   *  UnaryMinus: '<S5>/Unary Minus'
   *  UnaryMinus: '<S5>/Unary Minus2'
   */
  rtb_Sum_o[0] = rtb_UkYk1_h + rtb_Product2_a;
  rtb_Sum_o[1] = -rtb_UkYk1_g - rtb_Product2_a;
  rtb_Sum_o[2] = -rtb_UkYk1_h + rtb_Product2_a;
  rtb_Sum_o[3] = rtb_UkYk1_g - rtb_Product2_a;

  /* Outport: '<Root>/control_deg' */
  rtY_control_deg[0] = rtb_Sum_o[0];
  rtY_control_deg[1] = rtb_Sum_o[1];
  rtY_control_deg[2] = rtb_Sum_o[2];
  rtY_control_deg[3] = rtb_Sum_o[3];

  /* RelationalOperator: '<S426>/Compare' incorporates:
   *  Constant: '<S426>/Constant'
   */
  rtb_LogicalOperator1_m4 = (rtb_flightMode_enum == IDLE);

  /* Switch: '<S422>/Switch1' */
  if (rtb_LogicalOperator1_m4) {
    /* Switch: '<S422>/Switch1' incorporates:
     *  Constant: '<S427>/Constant'
     *  Delay generated from: '<S422>/Delay'
     *  Product: '<S427>/Matrix Multiply'
     *  Quat2Dcm: '<S427>/C-'
     *  Sum: '<S422>/Sum'
     */
    for (i = 0; i < 3; i++) {
      Switch1[i] = ((rtb_C[i + 3] * 0.0 + rtb_C[i] * 0.0) + rtb_C[i + 6] * 9.81)
        + rtDW->Delay_3_DSTATE[i];
    }
  } else {
    /* Switch: '<S422>/Switch1' incorporates:
     *  UnitDelay: '<S422>/Unit Delay1'
     */
    Switch1[0] = rtDW->UnitDelay1_DSTATE[0];
    Switch1[1] = rtDW->UnitDelay1_DSTATE[1];
    Switch1[2] = rtDW->UnitDelay1_DSTATE[2];
  }

  /* End of Switch: '<S422>/Switch1' */

  /* DiscreteFir: '<S422>/Discrete FIR Filter1' */
  rtb_zPosEst_m = Switch1[0] * 0.01;
  for (i = rtDW->DiscreteFIRFilter1_circBuf; i < 99; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter1_states[i] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter1_circBuf; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter1_states[i] * 0.01;
  }

  rtb_accelBias_mps2_idx_0 = rtb_zPosEst_m;

  /* Switch: '<S422>/Switch' */
  if (rtb_LogicalOperator1_m4) {
    /* Switch: '<S422>/Switch' incorporates:
     *  Delay generated from: '<S422>/Delay'
     */
    rtb_MatrixMultiply_idx_0 = rtDW->Delay_4_DSTATE[0];
  } else {
    /* Switch: '<S422>/Switch' incorporates:
     *  UnitDelay: '<S422>/Unit Delay'
     */
    rtb_MatrixMultiply_idx_0 = rtDW->UnitDelay_DSTATE[0];
  }

  /* DiscreteFir: '<S422>/Discrete FIR Filter1' */
  rtb_zPosEst_m = Switch1[1] * 0.01;
  for (i = rtDW->DiscreteFIRFilter1_circBuf; i < 99; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter1_states[i + 99] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter1_circBuf; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter1_states[i + 99] * 0.01;
  }

  rtb_accelBias_mps2_idx_1 = rtb_zPosEst_m;

  /* Switch: '<S422>/Switch' */
  if (rtb_LogicalOperator1_m4) {
    /* Switch: '<S422>/Switch' incorporates:
     *  Delay generated from: '<S422>/Delay'
     */
    rtb_MatrixMultiply_idx_1 = rtDW->Delay_4_DSTATE[1];
  } else {
    /* Switch: '<S422>/Switch' incorporates:
     *  UnitDelay: '<S422>/Unit Delay'
     */
    rtb_MatrixMultiply_idx_1 = rtDW->UnitDelay_DSTATE[1];
  }

  /* DiscreteFir: '<S422>/Discrete FIR Filter1' */
  rtb_zPosEst_m = Switch1[2] * 0.01;
  for (i = rtDW->DiscreteFIRFilter1_circBuf; i < 99; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter1_states[i + 198] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter1_circBuf; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter1_states[i + 198] * 0.01;
  }

  rtb_accelBias_mps2_idx_2 = rtb_zPosEst_m;

  /* Switch: '<S422>/Switch' */
  if (rtb_LogicalOperator1_m4) {
    /* Switch: '<S422>/Switch' incorporates:
     *  Delay generated from: '<S422>/Delay'
     */
    rtb_MatrixMultiply_idx_2 = rtDW->Delay_4_DSTATE[2];
  } else {
    /* Switch: '<S422>/Switch' incorporates:
     *  UnitDelay: '<S422>/Unit Delay'
     */
    rtb_MatrixMultiply_idx_2 = rtDW->UnitDelay_DSTATE[2];
  }

  /* DiscreteFir: '<S422>/Discrete FIR Filter' */
  rtb_zPosEst_m = rtb_MatrixMultiply_idx_0 * 0.01;
  for (i = rtDW->DiscreteFIRFilter_circBuf; i < 99; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter_states[i] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter_circBuf; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter_states[i] * 0.01;
  }

  rtb_DiscreteFIRFilter[0] = rtb_zPosEst_m;

  /* Sum: '<S411>/Sum2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_MathFunction[0] = rtU_sensor_bus_e->fBdyMeas_mps2[0] -
    rtDW->UnitDelay_13_DSTATE[0];

  /* DiscreteFir: '<S422>/Discrete FIR Filter' */
  rtb_zPosEst_m = rtb_MatrixMultiply_idx_1 * 0.01;
  for (i = rtDW->DiscreteFIRFilter_circBuf; i < 99; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter_states[i + 99] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter_circBuf; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter_states[i + 99] * 0.01;
  }

  rtb_DiscreteFIRFilter[1] = rtb_zPosEst_m;

  /* Sum: '<S411>/Sum2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_MathFunction[1] = rtU_sensor_bus_e->fBdyMeas_mps2[1] -
    rtDW->UnitDelay_13_DSTATE[1];

  /* DiscreteFir: '<S422>/Discrete FIR Filter' */
  rtb_zPosEst_m = rtb_MatrixMultiply_idx_2 * 0.01;
  for (i = rtDW->DiscreteFIRFilter_circBuf; i < 99; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter_states[i + 198] * 0.01;
  }

  for (i = 0; i < rtDW->DiscreteFIRFilter_circBuf; i++) {
    rtb_zPosEst_m += rtDW->DiscreteFIRFilter_states[i + 198] * 0.01;
  }

  rtb_DiscreteFIRFilter[2] = rtb_zPosEst_m;

  /* Sum: '<S411>/Sum2' incorporates:
   *  Inport: '<Root>/sensor_bus'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_MathFunction[2] = rtU_sensor_bus_e->fBdyMeas_mps2[2] -
    rtDW->UnitDelay_13_DSTATE[2];

  /* Product: '<S422>/Product' incorporates:
   *  Constant: '<S422>/Constant'
   */
  rtb_Sum5_idx_0 = rtb_MathFunction[1];
  rtb_Sum5_idx_1 = rtb_MathFunction[0];
  rtb_Sum5_idx_2 = rtb_MathFunction[2];

  /* Product: '<S450>/Matrix Multiply' */
  rtb_Sum4_idx_0 = 0.0;
  rtb_Sum4_idx_1 = 0.0;
  rtb_Sum4_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    /* Sum: '<S422>/Sum1' incorporates:
     *  Constant: '<S422>/Constant'
     *  Product: '<S422>/Product'
     */
    rtb_gyroBias_rps[i] = ((rtCP__Constant_Value_m[i + 3] * rtb_Sum5_idx_0 +
      rtCP__Constant_Value_m[i] * rtb_Sum5_idx_1) + rtCP__Constant_Value_m[i + 6]
      * rtb_Sum5_idx_2) + rtb_DiscreteFIRFilter[i];

    /* Product: '<S450>/Matrix Multiply' incorporates:
     *  Constant: '<S450>/Constant'
     *  Quat2Dcm: '<S450>/Quaternions to  Direction Cosine Matrix'
     */
    rtb_zPosEst_m = rtCP__Constant_Value_bn[i];
    rtb_Sum4_idx_0 += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_zPosEst_m;
    rtb_Sum4_idx_1 += rtb_QuaternionstoDirectionCosin[3 * i + 1] * rtb_zPosEst_m;
    rtb_Sum4_idx_2 += rtb_QuaternionstoDirectionCosin[3 * i + 2] * rtb_zPosEst_m;
  }

  /* Product: '<S450>/Matrix Multiply' */
  rtb_accelFilt_mps2_c[2] = rtb_Sum4_idx_2;
  rtb_accelFilt_mps2_c[1] = rtb_Sum4_idx_1;
  rtb_accelFilt_mps2_c[0] = rtb_Sum4_idx_0;
  for (i = 0; i < 3; i++) {
    /* Sum: '<S411>/Sum1' */
    rtb_Sum4_idx_0 = rtb_accelFilt_mps2_c[i] + rtb_MathFunction[i];
    rtb_accBdyEst_mps2[i] = rtb_Sum4_idx_0;

    /* DiscreteTransferFcn: '<S424>/Accel Filter' */
    rtb_Sum4_idx_1 = rtDW->AccelFilter_states[i];
    rtb_zPosEst_m = rtb_Sum4_idx_0 - 0.0 * rtb_Sum4_idx_1;
    AccelFilter_tmp[i] = rtb_zPosEst_m;
    rtb_accelFilt_mps2_c[i] = 0.5 * rtb_zPosEst_m + 0.5 * rtb_Sum4_idx_1;

    /* DiscreteTransferFcn: '<S407>/Accel Filter' */
    rtb_Sum4_idx_1 = rtDW->AccelFilter_states_p[i];
    rtb_zPosEst_m = rtb_Sum4_idx_0 - 0.0 * rtb_Sum4_idx_1;
    AccelFilter_tmp_j[i] = rtb_zPosEst_m;
    rtb_accelFilt_mps2[i] = 0.5 * rtb_zPosEst_m + 0.5 * rtb_Sum4_idx_1;

    /* Gain: '<S407>/Gain' incorporates:
     *  Math: '<S414>/Math Function'
     *  Quat2Dcm: '<S407>/C+'
     *  Sum: '<S407>/Sum'
     */
    rtb_QuaternionstoDirectionCosin[3 * i] = (rtb_C_l[i] + rtb_MathFunction_k[i])
      * 0.5;
    rtb_QuaternionstoDirectionCosin[3 * i + 1] = (rtb_C_l[i + 3] +
      rtb_MathFunction_k[i + 3]) * 0.5;
    rtb_QuaternionstoDirectionCosin[3 * i + 2] = (rtb_C_l[i + 6] +
      rtb_MathFunction_k[i + 6]) * 0.5;

    /* Product: '<S407>/Product' */
    rtb_MathFunction[i] = 0.0;
  }

  /* Product: '<S407>/Product' */
  rtb_Sum5_idx_0 = rtb_MathFunction[0];
  rtb_Sum5_idx_1 = rtb_MathFunction[1];
  rtb_Sum5_idx_2 = rtb_MathFunction[2];
  for (i = 0; i < 3; i++) {
    rtb_zPosEst_m = rtb_accelFilt_mps2[i];
    rtb_Sum5_idx_0 += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_zPosEst_m;
    rtb_Sum5_idx_1 += rtb_QuaternionstoDirectionCosin[3 * i + 1] * rtb_zPosEst_m;
    rtb_Sum5_idx_2 += rtb_QuaternionstoDirectionCosin[3 * i + 2] * rtb_zPosEst_m;
  }

  /* Sum: '<S407>/Sum4' incorporates:
   *  Gain: '<S407>/Gain3'
   *  Product: '<S407>/Product'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Sum4_idx_0 = 0.01 * rtb_Sum5_idx_0 + rtDW->UnitDelay_15_DSTATE;
  rtb_Sum4_idx_1 = 0.01 * rtb_Sum5_idx_1 + rtDW->UnitDelay_16_DSTATE;
  rtb_Sum4_idx_2 = 0.01 * rtb_Sum5_idx_2 + rtDW->UnitDelay_17_DSTATE;

  /* Sum: '<S407>/Sum5' incorporates:
   *  Gain: '<S407>/Gain4'
   *  Gain: '<S407>/Gain5'
   *  Product: '<S407>/Product'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Sum5_idx_0 = (0.01 * rtb_Sum4_idx_0 + rtDW->UnitDelay_18_DSTATE) - 5.0E-5 *
    rtb_Sum5_idx_0;
  rtb_Sum5_idx_1 = (0.01 * rtb_Sum4_idx_1 + rtDW->UnitDelay_19_DSTATE) - 5.0E-5 *
    rtb_Sum5_idx_1;
  rtb_Sum5_idx_2 = (0.01 * rtb_Sum4_idx_2 + rtDW->UnitDelay_20_DSTATE) - 5.0E-5 *
    rtb_Sum5_idx_2;

  /* State Transition Table: '<S409>/State Transition Table' incorporates:
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
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
        rtDW->lockoutThreshold_b = ((rtb_wBdyEst_rps[1] > 1.0) ||
          ((rtb_wBdyEst_rps[2] > 1.0) || ((rtb_QuaternionstoDirectionCos_1 > 0.4)
          || (rtb_Sum1_e_idx_1_tmp > 0.4))));
      }
      break;

     case autocodeModel_IN_Boost:
      rtDW->flightMode_enum = BOOST;
      if (rtDW->coastThreshold_b) {
        rtDW->temporalCounter_i1 = 0U;
        rtDW->is_c4_autocodeModel = autocodeM_IN_PastCoastThreshold;
      } else {
        rtDW->coastThreshold_b = (rtb_accBdyEst_mps2[0] < 0.0);
      }
      break;

     case autocodeModel_IN_Idle:
      rtDW->flightMode_enum = IDLE;
      if (rtDW->boostThreshold_b) {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Boost;
        rtDW->flightMode_enum = BOOST;
        rtDW->coastThreshold_b = false;
      } else {
        scale = 3.312168642111238E-170;
        absxk = fabs(rtb_accBdyEst_mps2[0]);
        if (absxk > 3.312168642111238E-170) {
          rtb_zPosEst_m = 1.0;
          scale = absxk;
        } else {
          t = absxk / 3.312168642111238E-170;
          rtb_zPosEst_m = t * t;
        }

        absxk = fabs(rtb_accBdyEst_mps2[1]);
        if (absxk > scale) {
          t = scale / absxk;
          rtb_zPosEst_m = rtb_zPosEst_m * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          rtb_zPosEst_m += t * t;
        }

        absxk = fabs(rtb_accBdyEst_mps2[2]);
        if (absxk > scale) {
          t = scale / absxk;
          rtb_zPosEst_m = rtb_zPosEst_m * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          rtb_zPosEst_m += t * t;
        }

        rtb_zPosEst_m = scale * sqrt(rtb_zPosEst_m);
        if (rtIsNaN(rtb_zPosEst_m)) {
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
              rtb_zPosEst_m = (rtInf);
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        rtDW->boostThreshold_b = (rtb_zPosEst_m > 50.0);
      }
      break;

     case autocodeModel_IN_Lockout:
      rtDW->flightMode_enum = LOCKOUT;
      break;

     case autocodeM_IN_PastCoastThreshold:
      if (!rtDW->coastThreshold_b) {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Boost;
        rtDW->flightMode_enum = BOOST;
      } else if ((real_T)rtDW->temporalCounter_i1 * 0.01 > 0.1) {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Active;
        rtDW->flightMode_enum = ACTIVE;
        rtDW->lockoutThreshold_b = false;
      } else {
        rtDW->coastThreshold_b = (rtb_accBdyEst_mps2[0] < 0.0);
      }
      break;

     default:
      /* case IN_PastLockoutThreshold: */
      if (!rtDW->lockoutThreshold_b) {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Active;
        rtDW->flightMode_enum = ACTIVE;
      } else if ((real_T)rtDW->temporalCounter_i1 * 0.01 > 0.1) {
        rtDW->is_c4_autocodeModel = autocodeModel_IN_Lockout;
        rtDW->flightMode_enum = LOCKOUT;
      } else {
        rtDW->lockoutThreshold_b = ((rtb_wBdyEst_rps[1] > 1.0) ||
          ((rtb_wBdyEst_rps[2] > 1.0) || ((rtb_QuaternionstoDirectionCos_1 > 0.4)
          || (rtb_Sum1_e_idx_1_tmp > 0.4))));
      }
      break;
    }
  }

  /* End of State Transition Table: '<S409>/State Transition Table' */

  /* BusCreator generated from: '<Root>/navigation_bus' incorporates:
   *  Constant: '<S410>/Constant1'
   *  Outport: '<Root>/navigation_bus'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   */
  rtY_navigation_bus_d->flightMode_enum = rtDW->flightMode_enum;
  rtY_navigation_bus_d->qEst_na[0] = rtDW->qEst_na[0];
  rtY_navigation_bus_d->qEst_na[1] = rtDW->qEst_na[1];
  rtY_navigation_bus_d->qEst_na[2] = rtDW->qEst_na[2];
  rtY_navigation_bus_d->qEst_na[3] = rtDW->qEst_na[3];
  rtY_navigation_bus_d->phiEst_rad = rtb_QuaternionstoDirectionCos_0;
  rtY_navigation_bus_d->thetaEst_rad = rtb_QuaternionstoDirectionCos_1;
  rtY_navigation_bus_d->psiEst_rad = rtb_Sum1_e_idx_1_tmp;
  rtY_navigation_bus_d->pEst_rps = rtb_gyroFilt_rps[0];
  rtY_navigation_bus_d->qEst_rps = rtb_gyroFilt_rps[1];
  rtY_navigation_bus_d->rEst_rps = rtb_gyroFilt_rps[2];
  rtY_navigation_bus_d->xAccEst_mps2 = rtb_accelFilt_mps2_c[0];
  rtY_navigation_bus_d->yAccEst_mps2 = rtb_accelFilt_mps2_c[1];
  rtY_navigation_bus_d->zAccEst_mps2 = rtb_accelFilt_mps2_c[2];
  rtY_navigation_bus_d->dynPressureEst_Pa = 100000.0;
  rtY_navigation_bus_d->accelBias_mps2[0] = rtb_accelBias_mps2_idx_0;
  rtY_navigation_bus_d->gyroBias_rps[0] = rtb_gyroBias_rps[0];
  rtY_navigation_bus_d->accelBias_mps2[1] = rtb_accelBias_mps2_idx_1;
  rtY_navigation_bus_d->gyroBias_rps[1] = rtb_gyroBias_rps[1];
  rtY_navigation_bus_d->accelBias_mps2[2] = rtb_accelBias_mps2_idx_2;
  rtY_navigation_bus_d->gyroBias_rps[2] = rtb_gyroBias_rps[2];
  rtY_navigation_bus_d->xVelEst_mps = rtb_Sum4_idx_0;
  rtY_navigation_bus_d->yVelEst_mps = rtb_Sum4_idx_1;
  rtY_navigation_bus_d->zVelEst_mps = rtb_Sum4_idx_2;
  rtY_navigation_bus_d->xPosEst_m = rtb_Sum5_idx_0;
  rtY_navigation_bus_d->yPosEst_m = rtb_Sum5_idx_1;
  rtY_navigation_bus_d->zPosEst_m = rtb_Sum5_idx_2;

  /* SampleTimeMath: '<S282>/TSamp'
   *
   * About '<S282>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Switch2_m *= 100.0;

  /* Sum: '<S282>/Diff' incorporates:
   *  UnitDelay: '<S282>/UD'
   *
   * Block description for '<S282>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S282>/UD':
   *
   *  Store in Global RAM
   */
  rtb_zPosEst_m = rtb_Switch2_m - rtDW->UD_DSTATE;

  /* Logic: '<S227>/Logical Operator1' incorporates:
   *  Constant: '<S223>/Constant'
   *  Constant: '<S223>/Constant1'
   *  RelationalOperator: '<S227>/Relational Operator'
   *  RelationalOperator: '<S227>/Relational Operator1'
   */
  rtb_LogicalOperator1_m4 = ((rtb_zPosEst_m >= 0.5) || (rtb_zPosEst_m <= -0.5));

  /* Logic: '<S228>/Logical Operator1' incorporates:
   *  Constant: '<S223>/Constant2'
   *  Constant: '<S223>/Constant3'
   *  RelationalOperator: '<S228>/Relational Operator'
   *  RelationalOperator: '<S228>/Relational Operator1'
   */
  rtb_LogicalOperator = ((rtb_Product1_nt >= 0.25) || (rtb_Product1_nt <= -0.25));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.rateCmd_rps = rtb_sqrt;
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1_m4;
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.saturated_b =
    rtb_LogicalOperator;

  /* SampleTimeMath: '<S402>/TSamp'
   *
   * About '<S402>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_nt = rtb_Switch2_d * 100.0;

  /* Sum: '<S402>/Diff' incorporates:
   *  UnitDelay: '<S402>/UD'
   *
   * Block description for '<S402>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S402>/UD':
   *
   *  Store in Global RAM
   */
  rtb_zPosEst_m = rtb_Product1_nt - rtDW->UD_DSTATE_p;

  /* Logic: '<S347>/Logical Operator1' incorporates:
   *  Constant: '<S225>/Constant'
   *  Constant: '<S225>/Constant1'
   *  RelationalOperator: '<S347>/Relational Operator'
   *  RelationalOperator: '<S347>/Relational Operator1'
   */
  rtb_LogicalOperator1 = ((rtb_zPosEst_m >= 0.5) || (rtb_zPosEst_m <= -0.5));

  /* Logic: '<S348>/Logical Operator1' incorporates:
   *  Constant: '<S225>/Constant2'
   *  Constant: '<S225>/Constant3'
   *  RelationalOperator: '<S348>/Relational Operator'
   *  RelationalOperator: '<S348>/Relational Operator1'
   */
  rtb_LogicalOperator_k = ((rtb_Product1_ek >= 0.25) || (rtb_Product1_ek <=
    -0.25));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.rateCmd_rps = rtb_UkYk1_b;
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1;
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_k;

  /* SampleTimeMath: '<S342>/TSamp'
   *
   * About '<S342>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Switch2 *= 100.0;

  /* Sum: '<S342>/Diff' incorporates:
   *  UnitDelay: '<S342>/UD'
   *
   * Block description for '<S342>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S342>/UD':
   *
   *  Store in Global RAM
   */
  rtb_zPosEst_m = rtb_Switch2 - rtDW->UD_DSTATE_a;

  /* Logic: '<S287>/Logical Operator1' incorporates:
   *  Constant: '<S224>/Constant'
   *  Constant: '<S224>/Constant1'
   *  RelationalOperator: '<S287>/Relational Operator'
   *  RelationalOperator: '<S287>/Relational Operator1'
   */
  rtb_LogicalOperator1_f = ((rtb_zPosEst_m >= 5.0) || (rtb_zPosEst_m <= -5.0));

  /* Logic: '<S288>/Logical Operator1' incorporates:
   *  Constant: '<S224>/Constant2'
   *  Constant: '<S224>/Constant3'
   *  RelationalOperator: '<S288>/Relational Operator'
   *  RelationalOperator: '<S288>/Relational Operator1'
   */
  rtb_LogicalOperator_dg = ((rtb_Product1_g3 >= 2.0) || (rtb_Product1_g3 <= -2.0));

  /* BusCreator generated from: '<Root>/controller_bus' incorporates:
   *  UnaryMinus: '<S224>/Unary Minus'
   */
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.rateCmd_rps =
    -rtb_rateCmd_rps;
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1_f;
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_dg;

  /* SampleTimeMath: '<S78>/TSamp'
   *
   * About '<S78>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_g3 = rtb_Switch2_j * 100.0;

  /* Sum: '<S78>/Diff' incorporates:
   *  UnitDelay: '<S78>/UD'
   *
   * Block description for '<S78>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S78>/UD':
   *
   *  Store in Global RAM
   */
  rtb_zPosEst_m = rtb_Product1_g3 - rtDW->UD_DSTATE_k;

  /* Logic: '<S15>/Logical Operator1' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  RelationalOperator: '<S15>/Relational Operator'
   *  RelationalOperator: '<S15>/Relational Operator1'
   */
  rtb_LogicalOperator1_b = ((rtb_zPosEst_m >= 180.0) || (rtb_zPosEst_m <= -180.0));

  /* Logic: '<S16>/Logical Operator1' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  RelationalOperator: '<S16>/Relational Operator'
   *  RelationalOperator: '<S16>/Relational Operator1'
   */
  rtb_LogicalOperator_nf = ((rtb_Filter_a >= 45.0) || (rtb_Filter_a <= -45.0));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.control_deg =
    rtb_UkYk1_h;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_k;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator1_b;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_nf;

  /* SampleTimeMath: '<S218>/TSamp'
   *
   * About '<S218>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_k = rtb_Switch2_b * 100.0;

  /* Sum: '<S218>/Diff' incorporates:
   *  UnitDelay: '<S218>/UD'
   *
   * Block description for '<S218>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S218>/UD':
   *
   *  Store in Global RAM
   */
  rtb_zPosEst_m = rtb_Product1_k - rtDW->UD_DSTATE_l;

  /* Logic: '<S155>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S11>/Constant1'
   *  RelationalOperator: '<S155>/Relational Operator'
   *  RelationalOperator: '<S155>/Relational Operator1'
   */
  rtb_LogicalOperator1_l = ((rtb_zPosEst_m >= 180.0) || (rtb_zPosEst_m <= -180.0));

  /* Logic: '<S156>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Constant: '<S11>/Constant3'
   *  RelationalOperator: '<S156>/Relational Operator'
   *  RelationalOperator: '<S156>/Relational Operator1'
   */
  rtb_LogicalOperator_e = ((rtb_Divide_l >= 45.0) || (rtb_Divide_l <= -45.0));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.control_deg = rtb_UkYk1_g;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_l;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator1_l;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_e;

  /* SampleTimeMath: '<S148>/TSamp'
   *
   * About '<S148>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Switch2_f *= 100.0;

  /* Sum: '<S148>/Diff' incorporates:
   *  UnitDelay: '<S148>/UD'
   *
   * Block description for '<S148>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S148>/UD':
   *
   *  Store in Global RAM
   */
  rtb_zPosEst_m = rtb_Switch2_f - rtDW->UD_DSTATE_n;

  /* Logic: '<S85>/Logical Operator1' incorporates:
   *  Constant: '<S10>/Constant'
   *  Constant: '<S10>/Constant1'
   *  RelationalOperator: '<S85>/Relational Operator'
   *  RelationalOperator: '<S85>/Relational Operator1'
   */
  rtb_LogicalOperator1_au = ((rtb_zPosEst_m >= 90.0) || (rtb_zPosEst_m <= -90.0));

  /* Logic: '<S86>/Logical Operator1' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant3'
   *  RelationalOperator: '<S86>/Relational Operator'
   *  RelationalOperator: '<S86>/Relational Operator1'
   */
  rtb_LogicalOperator_c = ((rtb_Gain >= 5.0) || (rtb_Gain <= -5.0));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.control_deg =
    rtb_Product2_a;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_i;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator1_au;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_c;

  /* Product: '<S119>/IProd Out' incorporates:
   *  Logic: '<S10>/Logical Operator'
   *  Product: '<S82>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Sum_a *= (real_T)(!rtb_LogicalOperator_c && !rtb_LogicalOperator1_au) *
    1.7999999999999998 * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S189>/IProd Out' incorporates:
   *  Logic: '<S11>/Logical Operator'
   *  Product: '<S152>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_i = (real_T)(!rtb_LogicalOperator_e && !rtb_LogicalOperator1_l) *
    18000.0 * (real_T)rtDW->UnitDelay_DSTATE_n * rtb_Sum1_j;

  /* Product: '<S49>/IProd Out' incorporates:
   *  Logic: '<S9>/Logical Operator'
   *  Product: '<S12>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Gain = (real_T)(!rtb_LogicalOperator_nf && !rtb_LogicalOperator1_b) *
    18000.0 * (real_T)rtDW->UnitDelay_DSTATE_n * rtb_Sum2;

  /* Product: '<S321>/IProd Out' incorporates:
   *  Constant: '<S224>/Constant4'
   *  Constant: '<S2>/Constant'
   *  Logic: '<S224>/Logical Operator'
   *  Product: '<S286>/Product'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum2'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Filter_a = (real_T)(!rtb_LogicalOperator_dg && !rtb_LogicalOperator1_f) *
    3.0 * (real_T)rtDW->UnitDelay_DSTATE_n * (0.0 -
    rtb_QuaternionstoDirectionCos_0);

  /* Product: '<S381>/IProd Out' incorporates:
   *  Constant: '<S225>/Constant4'
   *  Constant: '<S2>/Constant2'
   *  Logic: '<S225>/Logical Operator'
   *  Product: '<S346>/Product'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Sum2 = (real_T)(!rtb_LogicalOperator_k && !rtb_LogicalOperator1) * 0.5 *
    (real_T)rtDW->UnitDelay_DSTATE_n * (0.0 - rtb_Sum1_e_idx_1_tmp);

  /* Product: '<S226>/Product' incorporates:
   *  Constant: '<S223>/Constant4'
   *  Logic: '<S223>/Logical Operator'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_zPosEst_m = (real_T)(!rtb_LogicalOperator && !rtb_LogicalOperator1_m4) *
    0.5 * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* BusCreator generated from: '<Root>/controller_bus' incorporates:
   *  Outport: '<Root>/controller_bus'
   */
  rtY_controller_bus_f->control_deg[0] = rtb_Sum_o[0];

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[0] = rtDW->qEst_na[0];

  /* BusCreator generated from: '<Root>/controller_bus' incorporates:
   *  Outport: '<Root>/controller_bus'
   */
  rtY_controller_bus_f->control_deg[1] = rtb_Sum_o[1];

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[1] = rtDW->qEst_na[1];

  /* BusCreator generated from: '<Root>/controller_bus' incorporates:
   *  Outport: '<Root>/controller_bus'
   */
  rtY_controller_bus_f->control_deg[2] = rtb_Sum_o[2];

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[2] = rtDW->qEst_na[2];

  /* BusCreator generated from: '<Root>/controller_bus' incorporates:
   *  Outport: '<Root>/controller_bus'
   */
  rtY_controller_bus_f->control_deg[3] = rtb_Sum_o[3];

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[3] = rtDW->qEst_na[3];

  /* Update for UnitDelay: '<S4>/Unit Delay' incorporates:
   *  Constant: '<S4>/Constant2'
   *  RelationalOperator: '<S4>/Equal'
   */
  rtDW->UnitDelay_DSTATE_n = (rtDW->flightMode_enum == ACTIVE);

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_14_DSTATE[0] = rtb_gyroBias_rps[0];

  /* Update for DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[1] = rtDW->DiscreteTransferFcn1_states[0];
  rtDW->DiscreteTransferFcn1_states[0] = DiscreteTransferFcn1_tmp[0];

  /* Update for DiscreteTransferFcn: '<S424>/Gyro Filter' */
  rtDW->GyroFilter_states[1] = rtDW->GyroFilter_states[0];
  rtDW->GyroFilter_states[0] = GyroFilter_tmp[0];

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_14_DSTATE[1] = rtb_gyroBias_rps[1];

  /* Update for DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[3] = rtDW->DiscreteTransferFcn1_states[2];
  rtDW->DiscreteTransferFcn1_states[2] = DiscreteTransferFcn1_tmp[1];

  /* Update for DiscreteTransferFcn: '<S424>/Gyro Filter' */
  rtDW->GyroFilter_states[3] = rtDW->GyroFilter_states[2];
  rtDW->GyroFilter_states[2] = GyroFilter_tmp[1];

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_14_DSTATE[2] = rtb_gyroBias_rps[2];

  /* Update for DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[5] = rtDW->DiscreteTransferFcn1_states[4];
  rtDW->DiscreteTransferFcn1_states[4] = DiscreteTransferFcn1_tmp[2];

  /* Update for DiscreteTransferFcn: '<S424>/Gyro Filter' */
  rtDW->GyroFilter_states[5] = rtDW->GyroFilter_states[4];
  rtDW->GyroFilter_states[4] = GyroFilter_tmp[2];

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_1_DSTATE = rtDW->flightMode_enum;

  /* Update for DiscreteIntegrator: '<S324>/Integrator' */
  rtDW->Integrator_DSTATE += 0.01 * rtb_Filter_a;

  /* Update for DiscreteIntegrator: '<S319>/Filter' */
  rtDW->Filter_DSTATE += 0.01 * rtb_Integrator_l;

  /* Update for Delay: '<S343>/Delay' */
  rtDW->icLoad = false;
  rtDW->Delay_DSTATE = rtb_rateCmd_rps;

  /* Update for DiscreteIntegrator: '<S122>/Integrator' */
  rtDW->Integrator_DSTATE_b += 0.01 * rtb_Sum_a;

  /* Update for DiscreteIntegrator: '<S117>/Filter' */
  rtDW->Filter_DSTATE_p += 0.01 * rtb_Integrator_d;

  /* Update for Delay: '<S149>/Delay' */
  rtDW->icLoad_k = false;
  rtDW->Delay_DSTATE_p = rtb_Product2_a;

  /* Update for DiscreteIntegrator: '<S264>/Integrator' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Product: '<S261>/IProd Out'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum1'
   */
  rtDW->Integrator_DSTATE_g += (0.0 - rtb_QuaternionstoDirectionCos_1) *
    rtb_zPosEst_m * 0.01;

  /* Update for DiscreteIntegrator: '<S259>/Filter' */
  rtDW->Filter_DSTATE_n += 0.01 * rtb_Product1_o;

  /* Update for Delay: '<S283>/Delay' */
  rtDW->icLoad_a = false;
  rtDW->Delay_DSTATE_c = rtb_sqrt;

  /* Update for DiscreteIntegrator: '<S52>/Integrator' */
  rtDW->Integrator_DSTATE_p += 0.01 * rtb_Gain;

  /* Update for DiscreteIntegrator: '<S47>/Filter' */
  rtDW->Filter_DSTATE_l += 0.01 * rtb_deltafalllimit_fs;

  /* Update for Delay: '<S79>/Delay' */
  rtDW->icLoad_f = false;
  rtDW->Delay_DSTATE_f = rtb_UkYk1_h;

  /* Update for DiscreteIntegrator: '<S384>/Integrator' */
  rtDW->Integrator_DSTATE_l += 0.01 * rtb_Sum2;

  /* Update for DiscreteIntegrator: '<S379>/Filter' */
  rtDW->Filter_DSTATE_c += 0.01 * rtb_NProdOut_k;

  /* Update for Delay: '<S403>/Delay' */
  rtDW->icLoad_c = false;
  rtDW->Delay_DSTATE_h = rtb_UkYk1_b;

  /* Update for DiscreteIntegrator: '<S192>/Integrator' */
  rtDW->Integrator_DSTATE_e += 0.01 * rtb_Product1_i;

  /* Update for DiscreteIntegrator: '<S187>/Filter' */
  rtDW->Filter_DSTATE_g += 0.01 * rtb_deltafalllimit;

  /* Update for Delay: '<S219>/Delay' */
  rtDW->icLoad_d = false;
  rtDW->Delay_DSTATE_e = rtb_UkYk1_g;

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  for (i = 0; i < 9; i++) {
    uIdx = (i + 1) * 3;
    rtDW->Delay_3_DSTATE[i * 3] = rtDW->Delay_3_DSTATE[uIdx];
    rtDW->Delay_3_DSTATE[i * 3 + 1] = rtDW->Delay_3_DSTATE[uIdx + 1];
    rtDW->Delay_3_DSTATE[i * 3 + 2] = rtDW->Delay_3_DSTATE[uIdx + 2];
  }

  rtDW->Delay_3_DSTATE[27] = rtU_sensor_bus_e->fBdyMeas_mps2[0];

  /* Update for UnitDelay: '<S422>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[0] = rtb_accelBias_mps2_idx_0;

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_3_DSTATE[28] = rtU_sensor_bus_e->fBdyMeas_mps2[1];

  /* Update for UnitDelay: '<S422>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[1] = rtb_accelBias_mps2_idx_1;

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_3_DSTATE[29] = rtU_sensor_bus_e->fBdyMeas_mps2[2];

  /* Update for UnitDelay: '<S422>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[2] = rtb_accelBias_mps2_idx_2;

  /* Update for DiscreteFir: '<S422>/Discrete FIR Filter1' */
  /* Update circular buffer index */
  rtDW->DiscreteFIRFilter1_circBuf--;
  if (rtDW->DiscreteFIRFilter1_circBuf < 0) {
    rtDW->DiscreteFIRFilter1_circBuf = 98;
  }

  /* Update circular buffer */
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf] = Switch1[0];
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf + 99] =
    Switch1[1];
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf + 198] =
    Switch1[2];

  /* End of Update for DiscreteFir: '<S422>/Discrete FIR Filter1' */

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  for (i = 0; i < 9; i++) {
    uIdx = (i + 1) * 3;
    rtDW->Delay_4_DSTATE[i * 3] = rtDW->Delay_4_DSTATE[uIdx];
    rtDW->Delay_4_DSTATE[i * 3 + 1] = rtDW->Delay_4_DSTATE[uIdx + 1];
    rtDW->Delay_4_DSTATE[i * 3 + 2] = rtDW->Delay_4_DSTATE[uIdx + 2];
  }

  rtDW->Delay_4_DSTATE[27] = rtU_sensor_bus_e->wBdyMeas_rps[0];

  /* Update for UnitDelay: '<S422>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[0] = rtb_DiscreteFIRFilter[0];

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_4_DSTATE[28] = rtU_sensor_bus_e->wBdyMeas_rps[1];

  /* Update for UnitDelay: '<S422>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[1] = rtb_DiscreteFIRFilter[1];

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_4_DSTATE[29] = rtU_sensor_bus_e->wBdyMeas_rps[2];

  /* Update for UnitDelay: '<S422>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[2] = rtb_DiscreteFIRFilter[2];

  /* Update for DiscreteFir: '<S422>/Discrete FIR Filter' */
  /* Update circular buffer index */
  rtDW->DiscreteFIRFilter_circBuf--;
  if (rtDW->DiscreteFIRFilter_circBuf < 0) {
    rtDW->DiscreteFIRFilter_circBuf = 98;
  }

  /* Update circular buffer */
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf] =
    rtb_MatrixMultiply_idx_0;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[0] = rtb_accelBias_mps2_idx_0;

  /* Update for DiscreteTransferFcn: '<S424>/Accel Filter' */
  rtDW->AccelFilter_states[0] = AccelFilter_tmp[0];

  /* Update for DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtDW->AccelFilter_states_p[0] = AccelFilter_tmp_j[0];

  /* Update for DiscreteFir: '<S422>/Discrete FIR Filter' */
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf + 99] =
    rtb_MatrixMultiply_idx_1;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[1] = rtb_accelBias_mps2_idx_1;

  /* Update for DiscreteTransferFcn: '<S424>/Accel Filter' */
  rtDW->AccelFilter_states[1] = AccelFilter_tmp[1];

  /* Update for DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtDW->AccelFilter_states_p[1] = AccelFilter_tmp_j[1];

  /* Update for DiscreteFir: '<S422>/Discrete FIR Filter' */
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf + 198] =
    rtb_MatrixMultiply_idx_2;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[2] = rtb_accelBias_mps2_idx_2;

  /* Update for DiscreteTransferFcn: '<S424>/Accel Filter' */
  rtDW->AccelFilter_states[2] = AccelFilter_tmp[2];

  /* Update for DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtDW->AccelFilter_states_p[2] = AccelFilter_tmp_j[2];

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_15_DSTATE = rtb_Sum4_idx_0;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_16_DSTATE = rtb_Sum4_idx_1;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_17_DSTATE = rtb_Sum4_idx_2;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_18_DSTATE = rtb_Sum5_idx_0;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_19_DSTATE = rtb_Sum5_idx_1;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_20_DSTATE = rtb_Sum5_idx_2;

  /* Update for UnitDelay: '<S282>/UD'
   *
   * Block description for '<S282>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE = rtb_Switch2_m;

  /* Update for UnitDelay: '<S402>/UD'
   *
   * Block description for '<S402>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_p = rtb_Product1_nt;

  /* Update for UnitDelay: '<S342>/UD'
   *
   * Block description for '<S342>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_a = rtb_Switch2;

  /* Update for UnitDelay: '<S78>/UD'
   *
   * Block description for '<S78>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_k = rtb_Product1_g3;

  /* Update for UnitDelay: '<S218>/UD'
   *
   * Block description for '<S218>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_l = rtb_Product1_k;

  /* Update for UnitDelay: '<S148>/UD'
   *
   * Block description for '<S148>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_n = rtb_Switch2_f;
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

  /* InitializeConditions for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[0] = 0.7071;
  rtDW->UnitDelay_2_DSTATE[1] = 0.0;
  rtDW->UnitDelay_2_DSTATE[2] = 0.7071;
  rtDW->UnitDelay_2_DSTATE[3] = 0.0;

  /* InitializeConditions for Delay: '<S343>/Delay' */
  rtDW->icLoad = true;

  /* InitializeConditions for Delay: '<S149>/Delay' */
  rtDW->icLoad_k = true;

  /* InitializeConditions for Delay: '<S283>/Delay' */
  rtDW->icLoad_a = true;

  /* InitializeConditions for Delay: '<S79>/Delay' */
  rtDW->icLoad_f = true;

  /* InitializeConditions for Delay: '<S403>/Delay' */
  rtDW->icLoad_c = true;

  /* InitializeConditions for Delay: '<S219>/Delay' */
  rtDW->icLoad_d = true;

  /* InitializeConditions for DiscreteFir: '<S422>/Discrete FIR Filter1' */
  rtDW->DiscreteFIRFilter1_circBuf = 0;

  /* InitializeConditions for DiscreteFir: '<S422>/Discrete FIR Filter' */
  rtDW->DiscreteFIRFilter_circBuf = 0;

  /* InitializeConditions for DiscreteFir: '<S422>/Discrete FIR Filter1' */
  memset(&rtDW->DiscreteFIRFilter1_states[0], 0, 297U * sizeof(real_T));

  /* InitializeConditions for DiscreteFir: '<S422>/Discrete FIR Filter' */
  memset(&rtDW->DiscreteFIRFilter_states[0], 0, 297U * sizeof(real_T));

  /* SystemInitialize for Merge: '<S423>/Merge' */
  rtDW->qEst_na[0] = 0.0;
  rtDW->qEst_na[1] = 0.0;
  rtDW->qEst_na[2] = 0.0;
  rtDW->qEst_na[3] = 0.0;

  /* SystemInitialize for State Transition Table: '<S409>/State Transition Table' */
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
