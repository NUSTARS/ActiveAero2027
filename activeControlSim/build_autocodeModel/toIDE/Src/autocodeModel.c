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
 * C/C++ source code generated on : Tue Oct 27 19:09:50 2026
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
#include "LookUp_real_T_real_T.h"

/* Named constants for State Transition Table: '<S409>/State Transition Table' */
#define autocod_IN_PastLockoutThreshold ((uint8_T)6U)
#define autocodeM_IN_PastCoastThreshold ((uint8_T)5U)
#define autocodeMode_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define autocodeModel_IN_Active        ((uint8_T)1U)
#define autocodeModel_IN_Boost         ((uint8_T)2U)
#define autocodeModel_IN_Idle          ((uint8_T)3U)
#define autocodeModel_IN_Lockout       ((uint8_T)4U)

extern const real_T rtCP_pooled_vA5SDf3y1z9y[3];
extern const real_T rtCP_pooled_xh1hS6RTiaYE[3];
extern const real_T rtCP_pooled_IBfW69W5lTOo[3];
extern const real_T rtCP_pooled_yFJB7ZDVgVsO[3];
extern const real_T rtCP_pooled_5TzA8n11R6V0[3];
extern const real_T rtCP_pooled_V22b8eADTogt[3];
extern const real_T rtCP_pooled_JIXvzcabvSoM[9];
extern const real_T rtCP_pooled_Qcj6ValmO9nO[3];

#define rtCP__Constant4_Value          rtCP_pooled_vA5SDf3y1z9y  /* Expression: innerLoopParams.fbkGainPitchYawP_na
                                                                  * Referenced by: '<S9>/Constant4'
                                                                  */
#define rtCP__Constant5_Value          rtCP_pooled_xh1hS6RTiaYE  /* Expression: innerLoopParams.fbkGainPitchYawI_na
                                                                  * Referenced by: '<S9>/Constant5'
                                                                  */
#define rtCP__Constant6_Value          rtCP_pooled_IBfW69W5lTOo  /* Expression: innerLoopParams.fbkGainPitchYawD_na
                                                                  * Referenced by: '<S9>/Constant6'
                                                                  */
#define rtCP__Constant7_Value          rtCP_pooled_yFJB7ZDVgVsO  /* Expression: innerLoopParams.fbkGainPitchYawN_na
                                                                  * Referenced by: '<S9>/Constant7'
                                                                  */
#define rtCP__Internalbreakpoints_Value rtCP_pooled_5TzA8n11R6V0 /* Expression: GainArrayBreakpoints
                                                                  * Referenced by: '<S13>/Internal breakpoints'
                                                                  */
#define rtCP__Constant4_Value_c        rtCP_pooled_V22b8eADTogt  /* Expression: innerLoopParams.fbkGainRollP_na
                                                                  * Referenced by: '<S10>/Constant4'
                                                                  */
#define rtCP__Constant5_Value_m        rtCP_pooled_V22b8eADTogt  /* Expression: innerLoopParams.fbkGainRollI_na
                                                                  * Referenced by: '<S10>/Constant5'
                                                                  */
#define rtCP__Constant6_Value_p        rtCP_pooled_IBfW69W5lTOo  /* Expression: innerLoopParams.fbkGainRollD_na
                                                                  * Referenced by: '<S10>/Constant6'
                                                                  */
#define rtCP__Constant7_Value_o        rtCP_pooled_yFJB7ZDVgVsO  /* Expression: innerLoopParams.fbkGainRollN_na
                                                                  * Referenced by: '<S10>/Constant7'
                                                                  */
#define rtCP__Internalbreakpoints_Val_f rtCP_pooled_5TzA8n11R6V0 /* Expression: GainArrayBreakpoints
                                                                  * Referenced by: '<S83>/Internal breakpoints'
                                                                  */
#define rtCP__Constant4_Value_l        rtCP_pooled_vA5SDf3y1z9y  /* Expression: innerLoopParams.fbkGainPitchYawP_na
                                                                  * Referenced by: '<S11>/Constant4'
                                                                  */
#define rtCP__Constant5_Value_l        rtCP_pooled_xh1hS6RTiaYE  /* Expression: innerLoopParams.fbkGainPitchYawI_na
                                                                  * Referenced by: '<S11>/Constant5'
                                                                  */
#define rtCP__Constant6_Value_e        rtCP_pooled_IBfW69W5lTOo  /* Expression: innerLoopParams.fbkGainPitchYawD_na
                                                                  * Referenced by: '<S11>/Constant6'
                                                                  */
#define rtCP__Constant7_Value_n        rtCP_pooled_yFJB7ZDVgVsO  /* Expression: innerLoopParams.fbkGainPitchYawN_na
                                                                  * Referenced by: '<S11>/Constant7'
                                                                  */
#define rtCP__Internalbreakpoints_Val_d rtCP_pooled_5TzA8n11R6V0 /* Expression: GainArrayBreakpoints
                                                                  * Referenced by: '<S153>/Internal breakpoints'
                                                                  */
#define rtCP__Constant_Value_me        rtCP_pooled_JIXvzcabvSoM  /* Expression: navControl.gyroG
                                                                  * Referenced by: '<S422>/Constant'
                                                                  */
#define rtCP__Constant_Value_bn        rtCP_pooled_Qcj6ValmO9nO  /* Expression: navControl.gravityNed_mps2
                                                                  * Referenced by: '<S451>/Constant'
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

  { 0.0, 0.0, 0.0 },                   /* accelBias_mps2 */

  { 0.0, 0.0, 0.0 },                   /* gyroBias_rps */
  0.0,                                 /* dynPressureEst_Pa */
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
  real_T rtb_MathFunction_k[9];
  real_T rtb_QuaternionstoDirectionCosin[9];
  real_T DiscreteTransferFcn1_tmp[3];
  real_T Switch[3];
  real_T rtb_DiscreteFIRFilter[3];
  real_T rtb_MatrixMultiply[3];
  real_T rtb_Product_k4[3];
  real_T rtb_accBdyEst_mps2[3];
  real_T rtb_wBdyEst_rps[3];
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
  real_T rtb_MathFunction_m_tmp;
  real_T rtb_PProdOut_b;
  real_T rtb_Product1_ad;
  real_T rtb_Product1_da;
  real_T rtb_Product1_g;
  real_T rtb_Product1_j3;
  real_T rtb_Product1_nd;
  real_T rtb_Product1_o;
  real_T rtb_Product2_a;
  real_T rtb_Product3_i;
  real_T rtb_QuaternionstoDirectionCos_0;
  real_T rtb_Sin;
  real_T rtb_Sum1_idx_0;
  real_T rtb_Sum1_idx_1;
  real_T rtb_Sum1_idx_2;
  real_T rtb_Sum1_idx_3;
  real_T rtb_Sum3;
  real_T rtb_Sum4_a;
  real_T rtb_Sum5_idx_0;
  real_T rtb_Sum5_idx_1;
  real_T rtb_Sum5_idx_2;
  real_T rtb_Switch2_b;
  real_T rtb_Switch2_d;
  real_T rtb_Switch2_f;
  real_T rtb_Switch2_j;
  real_T rtb_Switch2_m;
  real_T rtb_TSamp;
  real_T rtb_TSamp_a;
  real_T rtb_TSamp_b;
  real_T rtb_TSamp_b0;
  real_T rtb_TSamp_c5;
  real_T rtb_TSamp_d;
  real_T rtb_TSamp_fe;
  real_T rtb_TSamp_ge;
  real_T rtb_TSamp_gj;
  real_T rtb_TSamp_h;
  real_T rtb_TSamp_i;
  real_T rtb_TSamp_jt;
  real_T rtb_TSamp_k;
  real_T rtb_TmpSignalConversionAtCInp_0;
  real_T rtb_TmpSignalConversionAtCInp_1;
  real_T rtb_TmpSignalConversionAtCInp_2;
  real_T rtb_TmpSignalConversionAtCInp_3;
  real_T rtb_TmpSignalConversionAtCInp_4;
  real_T rtb_UkYk1_l;
  real_T rtb_accelBias_mps2_idx_0;
  real_T rtb_accelBias_mps2_idx_1;
  real_T rtb_accelBias_mps2_idx_2;
  real_T rtb_sqrt;
  int32_T exitg1;
  int32_T i;
  int32_T idxWidth;
  int32_T uIdx;
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LogicalOperator1;
  boolean_T rtb_LogicalOperator1_a2;
  boolean_T rtb_LogicalOperator1_b;
  boolean_T rtb_LogicalOperator1_i;
  boolean_T rtb_LogicalOperator1_j;
  boolean_T rtb_LogicalOperator_a;
  boolean_T rtb_LogicalOperator_i;
  boolean_T rtb_LogicalOperator_j;
  boolean_T rtb_LogicalOperator_ni;
  flightMode rtb_flightMode_enum;

  /* Quat2Dcm: '<S407>/C-' incorporates:
   *  Quat2Dcm: '<S451>/Quaternions to  Direction Cosine Matrix'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Sin = 1.0 / sqrt(((rtDW->UnitDelay_2_DSTATE[0] * rtDW->UnitDelay_2_DSTATE
    [0] + rtDW->UnitDelay_2_DSTATE[1] * rtDW->UnitDelay_2_DSTATE[1]) +
                        rtDW->UnitDelay_2_DSTATE[2] * rtDW->UnitDelay_2_DSTATE[2])
                       + rtDW->UnitDelay_2_DSTATE[3] * rtDW->UnitDelay_2_DSTATE
                       [3]);
  rtb_Integrator_b = rtb_Sin * rtDW->UnitDelay_2_DSTATE[1];
  rtb_TmpSignalConversionAtCInp_2 = rtb_Sin * rtDW->UnitDelay_2_DSTATE[2];
  rtb_TmpSignalConversionAtCInp_4 = rtb_Sin * rtDW->UnitDelay_2_DSTATE[3];
  rtb_Product1_ad = rtb_Sin * rtDW->UnitDelay_2_DSTATE[0];
  rtb_TSamp_c5 = rtb_Product1_ad * rtb_Product1_ad;
  rtb_TSamp_a = rtb_Integrator_b * rtb_Integrator_b;
  rtb_Sin = rtb_TmpSignalConversionAtCInp_2 * rtb_TmpSignalConversionAtCInp_2;
  rtb_TmpSignalConversionAtCInp_0 = rtb_TmpSignalConversionAtCInp_4 *
    rtb_TmpSignalConversionAtCInp_4;
  rtb_TSamp_d = ((rtb_TSamp_c5 + rtb_TSamp_a) - rtb_Sin) -
    rtb_TmpSignalConversionAtCInp_0;
  rtb_QuaternionstoDirectionCosin[0] = rtb_TSamp_d;
  rtb_TSamp_b0 = rtb_Integrator_b * rtb_TmpSignalConversionAtCInp_2;
  rtb_TSamp_fe = rtb_Product1_ad * rtb_TmpSignalConversionAtCInp_4;
  rtb_TSamp_b = (rtb_TSamp_b0 + rtb_TSamp_fe) * 2.0;
  rtb_QuaternionstoDirectionCosin[3] = rtb_TSamp_b;
  rtb_Product3_i = rtb_Integrator_b * rtb_TmpSignalConversionAtCInp_4;
  rtb_TmpSignalConversionAtCInp_1 = rtb_Product1_ad *
    rtb_TmpSignalConversionAtCInp_2;
  rtb_QuaternionstoDirectionCos_0 = (rtb_Product3_i -
    rtb_TmpSignalConversionAtCInp_1) * 2.0;
  rtb_QuaternionstoDirectionCosin[6] = rtb_QuaternionstoDirectionCos_0;
  rtb_TSamp_b0 = (rtb_TSamp_b0 - rtb_TSamp_fe) * 2.0;
  rtb_QuaternionstoDirectionCosin[1] = rtb_TSamp_b0;
  rtb_TSamp_c5 -= rtb_TSamp_a;
  rtb_TSamp_a = (rtb_TSamp_c5 + rtb_Sin) - rtb_TmpSignalConversionAtCInp_0;
  rtb_QuaternionstoDirectionCosin[4] = rtb_TSamp_a;
  rtb_TSamp_fe = rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_4;
  rtb_Integrator_b *= rtb_Product1_ad;
  rtb_TmpSignalConversionAtCInp_4 = (rtb_TSamp_fe + rtb_Integrator_b) * 2.0;
  rtb_QuaternionstoDirectionCosin[7] = rtb_TmpSignalConversionAtCInp_4;
  rtb_Product3_i = (rtb_Product3_i + rtb_TmpSignalConversionAtCInp_1) * 2.0;
  rtb_QuaternionstoDirectionCosin[2] = rtb_Product3_i;
  rtb_TSamp_fe = (rtb_TSamp_fe - rtb_Integrator_b) * 2.0;
  rtb_QuaternionstoDirectionCosin[5] = rtb_TSamp_fe;
  rtb_TSamp_c5 = (rtb_TSamp_c5 - rtb_Sin) + rtb_TmpSignalConversionAtCInp_0;
  rtb_QuaternionstoDirectionCosin[8] = rtb_TSamp_c5;

  /* DotProduct: '<S407>/Dot Product' */
  rtb_Product1_ad = 0.0;
  for (i = 0; i < 3; i++) {
    /* Sum: '<S411>/Sum' incorporates:
     *  Inport: '<Root>/sensor_bus'
     *  UnitDelay generated from: '<S406>/Unit Delay'
     */
    rtb_TmpSignalConversionAtCInp_1 = rtU_sensor_bus_e->wBdyMeas_rps[i] -
      rtDW->UnitDelay_13_DSTATE[i];
    rtb_wBdyEst_rps[i] = rtb_TmpSignalConversionAtCInp_1;

    /* DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1' */
    uIdx = i << 1;
    rtb_Sin = rtDW->DiscreteTransferFcn1_states[uIdx];
    rtb_TmpSignalConversionAtCInp_0 = rtDW->DiscreteTransferFcn1_states[uIdx + 1];
    rtb_TSamp = (rtb_TmpSignalConversionAtCInp_1 - -0.7478 * rtb_Sin) -
      rtb_TmpSignalConversionAtCInp_0 * 0.2722;
    DiscreteTransferFcn1_tmp[i] = rtb_TSamp;

    /* Gain: '<S407>/Gain1' incorporates:
     *  DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1'
     */
    rtb_TmpSignalConversionAtCInp_1 = ((0.1311 * rtb_TSamp + 0.2622 * rtb_Sin) +
      rtb_TmpSignalConversionAtCInp_0 * 0.1311) * 0.01;
    rtb_Product_k4[i] = rtb_TmpSignalConversionAtCInp_1;

    /* DotProduct: '<S407>/Dot Product' */
    rtb_Product1_ad += rtb_TmpSignalConversionAtCInp_1 *
      rtb_TmpSignalConversionAtCInp_1;
  }

  /* Sqrt: '<S407>/Sqrt' */
  rtb_Product1_ad = sqrt(rtb_Product1_ad);

  /* Gain: '<S407>/Gain2' */
  rtb_Filter_g = 0.5 * rtb_Product1_ad;

  /* Trigonometry: '<S407>/Cos' */
  rtb_TmpSignalConversionAtCInp_0 = cos(rtb_Filter_g);

  /* Trigonometry: '<S407>/Sin' */
  rtb_Sin = sin(rtb_Filter_g);

  /* Product: '<S407>/Divide' incorporates:
   *  Bias: '<S407>/Bias'
   */
  rtb_TmpSignalConversionAtCInp_1 = rtb_Sin * rtb_Product_k4[0] /
    (rtb_Product1_ad + 1.0E-12);
  rtb_TmpSignalConversionAtCInp_2 = rtb_Sin * rtb_Product_k4[1] /
    (rtb_Product1_ad + 1.0E-12);
  rtb_TmpSignalConversionAtCInp_3 = rtb_Sin * rtb_Product_k4[2] /
    (rtb_Product1_ad + 1.0E-12);

  /* Product: '<S418>/Product' incorporates:
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Filter_g = rtDW->UnitDelay_2_DSTATE[0] * rtb_TmpSignalConversionAtCInp_3;

  /* Product: '<S418>/Product1' incorporates:
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Product1_ad = rtDW->UnitDelay_2_DSTATE[1] *
    rtb_TmpSignalConversionAtCInp_2;

  /* Product: '<S418>/Product3' incorporates:
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Sin = rtb_TmpSignalConversionAtCInp_0 * rtDW->UnitDelay_2_DSTATE[3];

  /* Sum: '<S418>/Sum' incorporates:
   *  Product: '<S418>/Product2'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Filter_g = ((rtb_Filter_g + rtb_Product1_ad) -
                  rtb_TmpSignalConversionAtCInp_1 * rtDW->UnitDelay_2_DSTATE[2])
    + rtb_Sin;

  /* Product: '<S415>/Product' incorporates:
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Sin = rtDW->UnitDelay_2_DSTATE[0] * rtb_TmpSignalConversionAtCInp_0;

  /* Product: '<S415>/Product2' incorporates:
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Product1_ad = rtDW->UnitDelay_2_DSTATE[2] *
    rtb_TmpSignalConversionAtCInp_2;

  /* Sum: '<S415>/Sum' incorporates:
   *  Product: '<S415>/Product1'
   *  Product: '<S415>/Product3'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Sin = ((rtb_Sin - rtDW->UnitDelay_2_DSTATE[1] *
              rtb_TmpSignalConversionAtCInp_1) - rtb_Product1_ad) -
    rtDW->UnitDelay_2_DSTATE[3] * rtb_TmpSignalConversionAtCInp_3;

  /* Product: '<S416>/Product2' incorporates:
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Product1_ad = rtDW->UnitDelay_2_DSTATE[2] *
    rtb_TmpSignalConversionAtCInp_3;

  /* Sum: '<S416>/Sum' incorporates:
   *  Product: '<S416>/Product'
   *  Product: '<S416>/Product1'
   *  Product: '<S416>/Product3'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Integrator_b = ((rtDW->UnitDelay_2_DSTATE[0] *
                       rtb_TmpSignalConversionAtCInp_1 +
                       rtb_TmpSignalConversionAtCInp_0 *
                       rtDW->UnitDelay_2_DSTATE[1]) + rtb_Product1_ad) -
    rtb_TmpSignalConversionAtCInp_2 * rtDW->UnitDelay_2_DSTATE[3];

  /* Product: '<S417>/Product2' incorporates:
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_Product1_ad = rtb_TmpSignalConversionAtCInp_0 * rtDW->UnitDelay_2_DSTATE[2];

  /* Sum: '<S417>/Sum' incorporates:
   *  Product: '<S417>/Product'
   *  Product: '<S417>/Product1'
   *  Product: '<S417>/Product3'
   *  UnitDelay generated from: '<S406>/Unit Delay'
   */
  rtb_TmpSignalConversionAtCInp_2 = ((rtDW->UnitDelay_2_DSTATE[0] *
    rtb_TmpSignalConversionAtCInp_2 - rtDW->UnitDelay_2_DSTATE[1] *
    rtb_TmpSignalConversionAtCInp_3) + rtb_Product1_ad) +
    rtb_TmpSignalConversionAtCInp_1 * rtDW->UnitDelay_2_DSTATE[3];

  /* Sqrt: '<S419>/sqrt' incorporates:
   *  Product: '<S420>/Product'
   *  Product: '<S420>/Product1'
   *  Product: '<S420>/Product2'
   *  Product: '<S420>/Product3'
   *  Sum: '<S420>/Sum'
   */
  rtb_TmpSignalConversionAtCInp_1 = sqrt(((rtb_Sin * rtb_Sin + rtb_Integrator_b *
    rtb_Integrator_b) + rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_2) + rtb_Filter_g * rtb_Filter_g);

  /* Product: '<S413>/Product3' */
  rtb_TmpSignalConversionAtCInp_0 = rtb_Filter_g /
    rtb_TmpSignalConversionAtCInp_1;

  /* Product: '<S413>/Product2' */
  rtb_TmpSignalConversionAtCInp_2 /= rtb_TmpSignalConversionAtCInp_1;

  /* Product: '<S413>/Product1' */
  rtb_Integrator_b /= rtb_TmpSignalConversionAtCInp_1;

  /* Product: '<S413>/Product' */
  rtb_Sin /= rtb_TmpSignalConversionAtCInp_1;

  /* Quat2Dcm: '<S407>/C+' incorporates:
   *  Math: '<S414>/Math Function'
   *  Quat2Dcm: '<S427>/C-'
   *  SignalConversion generated from: '<S407>/C+'
   */
  rtb_TmpSignalConversionAtCInp_1 = 1.0 / sqrt(((rtb_Sin * rtb_Sin +
    rtb_Integrator_b * rtb_Integrator_b) + rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_2) + rtb_TmpSignalConversionAtCInp_0 *
    rtb_TmpSignalConversionAtCInp_0);
  rtb_Sum1_idx_1 = rtb_TmpSignalConversionAtCInp_1 * rtb_Integrator_b;
  rtb_Sum1_idx_2 = rtb_TmpSignalConversionAtCInp_1 *
    rtb_TmpSignalConversionAtCInp_2;
  rtb_Sum1_idx_3 = rtb_TmpSignalConversionAtCInp_1 *
    rtb_TmpSignalConversionAtCInp_0;
  rtb_Product1_ad = rtb_TmpSignalConversionAtCInp_1 * rtb_Sin;
  rtb_TmpSignalConversionAtCInp_1 = rtb_Product1_ad * rtb_Product1_ad;
  rtb_TmpSignalConversionAtCInp_3 = rtb_Sum1_idx_1 * rtb_Sum1_idx_1;
  rtb_Filter_g = rtb_Sum1_idx_2 * rtb_Sum1_idx_2;
  rtb_TSamp = rtb_Sum1_idx_3 * rtb_Sum1_idx_3;
  rtb_Sum1_idx_0 = ((rtb_TmpSignalConversionAtCInp_1 +
                     rtb_TmpSignalConversionAtCInp_3) - rtb_Filter_g) -
    rtb_TSamp;
  rtb_MathFunction_k[0] = rtb_Sum1_idx_0;
  rtb_Product2_a = rtb_Sum1_idx_1 * rtb_Sum1_idx_2;
  rtb_Product1_nd = rtb_Product1_ad * rtb_Sum1_idx_3;
  rtb_sqrt = (rtb_Product2_a + rtb_Product1_nd) * 2.0;
  rtb_MathFunction_k[3] = rtb_sqrt;
  rtb_MathFunction_m_tmp = rtb_Sum1_idx_1 * rtb_Sum1_idx_3;
  rtb_TSamp_gj = rtb_Product1_ad * rtb_Sum1_idx_2;
  rtb_TSamp_jt = (rtb_MathFunction_m_tmp - rtb_TSamp_gj) * 2.0;
  rtb_MathFunction_k[6] = rtb_TSamp_jt;
  rtb_Product2_a = (rtb_Product2_a - rtb_Product1_nd) * 2.0;
  rtb_MathFunction_k[1] = rtb_Product2_a;
  rtb_TmpSignalConversionAtCInp_1 -= rtb_TmpSignalConversionAtCInp_3;
  rtb_TmpSignalConversionAtCInp_3 = (rtb_TmpSignalConversionAtCInp_1 +
    rtb_Filter_g) - rtb_TSamp;
  rtb_MathFunction_k[4] = rtb_TmpSignalConversionAtCInp_3;
  rtb_Product1_nd = rtb_Sum1_idx_2 * rtb_Sum1_idx_3;
  rtb_Sum1_idx_1 *= rtb_Product1_ad;
  rtb_Sum1_idx_3 = (rtb_Product1_nd + rtb_Sum1_idx_1) * 2.0;
  rtb_MathFunction_k[7] = rtb_Sum1_idx_3;
  rtb_MathFunction_m_tmp = (rtb_MathFunction_m_tmp + rtb_TSamp_gj) * 2.0;
  rtb_MathFunction_k[2] = rtb_MathFunction_m_tmp;
  rtb_Product1_nd = (rtb_Product1_nd - rtb_Sum1_idx_1) * 2.0;
  rtb_MathFunction_k[5] = rtb_Product1_nd;
  rtb_TmpSignalConversionAtCInp_1 = (rtb_TmpSignalConversionAtCInp_1 -
    rtb_Filter_g) + rtb_TSamp;
  rtb_MathFunction_k[8] = rtb_TmpSignalConversionAtCInp_1;

  /* Gain: '<S407>/Gain' incorporates:
   *  Math: '<S414>/Math Function'
   *  Quat2Dcm: '<S451>/Quaternions to  Direction Cosine Matrix'
   *  Sum: '<S407>/Sum'
   */
  for (i = 0; i < 9; i++) {
    rtb_MathFunction_k[i] = (rtb_MathFunction_k[i] +
      rtb_QuaternionstoDirectionCosin[i]) * 0.5;
  }

  /* End of Gain: '<S407>/Gain' */

  /* Quat2Dcm: '<S427>/C-' */
  rtb_C[0] = rtb_Sum1_idx_0;
  rtb_C[3] = rtb_sqrt;
  rtb_C[6] = rtb_TSamp_jt;
  rtb_C[1] = rtb_Product2_a;
  rtb_C[4] = rtb_TmpSignalConversionAtCInp_3;
  rtb_C[7] = rtb_Sum1_idx_3;
  rtb_C[2] = rtb_MathFunction_m_tmp;
  rtb_C[5] = rtb_Product1_nd;
  rtb_C[8] = rtb_TmpSignalConversionAtCInp_1;

  /* Quat2Dcm: '<S451>/Quaternions to  Direction Cosine Matrix' */
  rtb_QuaternionstoDirectionCosin[0] = rtb_TSamp_d;
  rtb_QuaternionstoDirectionCosin[3] = rtb_TSamp_b;
  rtb_QuaternionstoDirectionCosin[6] = rtb_QuaternionstoDirectionCos_0;
  rtb_QuaternionstoDirectionCosin[1] = rtb_TSamp_b0;
  rtb_QuaternionstoDirectionCosin[4] = rtb_TSamp_a;
  rtb_QuaternionstoDirectionCosin[7] = rtb_TmpSignalConversionAtCInp_4;
  rtb_QuaternionstoDirectionCosin[2] = rtb_Product3_i;
  rtb_QuaternionstoDirectionCosin[5] = rtb_TSamp_fe;
  rtb_QuaternionstoDirectionCosin[8] = rtb_TSamp_c5;

  /* DiscreteTransferFcn: '<S424>/Gyro Filter' */
  rtb_TSamp_c5 = rtb_wBdyEst_rps[0] - 0.4142 * rtDW->GyroFilter_states[0];
  rtb_TSamp_a = 0.7071 * rtb_TSamp_c5 + 0.7071 * rtDW->GyroFilter_states[0];
  rtb_TSamp_d = rtb_wBdyEst_rps[1] - 0.4142 * rtDW->GyroFilter_states[1];
  rtb_TSamp_b0 = 0.7071 * rtb_TSamp_d + 0.7071 * rtDW->GyroFilter_states[1];
  rtb_TSamp_fe = rtb_wBdyEst_rps[2] - 0.4142 * rtDW->GyroFilter_states[2];
  rtb_TSamp_b = 0.7071 * rtb_TSamp_fe + 0.7071 * rtDW->GyroFilter_states[2];

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
    rtb_Sum1_idx_0 = 0.0;
    rtb_Sum1_idx_1 = 0.0;
    rtb_Sum1_idx_2 = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_TSamp = -rtDW->Delay_3_DSTATE_e[i];
      rtb_Sum1_idx_0 += rtConstB.QuaternionstoDirectionCosin[3 * i] * rtb_TSamp;
      rtb_Sum1_idx_1 += rtConstB.QuaternionstoDirectionCosin[3 * i + 1] *
        rtb_TSamp;
      rtb_Sum1_idx_2 += rtConstB.QuaternionstoDirectionCosin[3 * i + 2] *
        rtb_TSamp;
    }

    /* Math: '<S431>/Math Function1' incorporates:
     *  Math: '<S431>/Math Function'
     *  Product: '<S429>/Matrix Multiply'
     *  Sum: '<S431>/Sum of Elements'
     *
     * About '<S431>/Math Function1':
     *  Operator: sqrt
     */
    rtb_Product2_a = sqrt((rtb_Sum1_idx_0 * rtb_Sum1_idx_0 + rtb_Sum1_idx_1 *
      rtb_Sum1_idx_1) + rtb_Sum1_idx_2 * rtb_Sum1_idx_2);

    /* Switch: '<S431>/Switch' incorporates:
     *  Constant: '<S431>/Constant'
     *  Product: '<S429>/Matrix Multiply'
     *  Product: '<S431>/Product'
     */
    if (rtb_Product2_a > 0.0) {
      rtb_Sum1_idx_3 = rtb_Product2_a;
    } else {
      rtb_Sum1_idx_0 *= 0.0;
      rtb_Sum1_idx_1 *= 0.0;
      rtb_Sum1_idx_2 *= 0.0;
      rtb_Sum1_idx_3 = 1.0;
    }

    /* End of Switch: '<S431>/Switch' */

    /* UnaryMinus: '<S429>/Unary Minus1' incorporates:
     *  Product: '<S431>/Divide'
     */
    rtb_MatrixMultiply[1] = -(rtb_Sum1_idx_1 / rtb_Sum1_idx_3);
    rtb_MatrixMultiply[2] = -(rtb_Sum1_idx_2 / rtb_Sum1_idx_3);

    /* Angle2Quat: '<S433>/Rotation Angles to Quaternions' incorporates:
     *  Math: '<S429>/Square'
     *  Math: '<S429>/Square1'
     *  Product: '<S431>/Divide'
     *  Sqrt: '<S429>/Sqrt'
     *  Sum: '<S429>/Sum'
     *  Trigonometry: '<S429>/Atan1'
     *  Trigonometry: '<S429>/Atan2'
     *  UnaryMinus: '<S429>/Unary Minus2'
     */
    rtb_QuaternionstoDirectionCos_0 = rt_atan2d_snf(rtb_Sum1_idx_0 /
      rtb_Sum1_idx_3, sqrt(rtb_MatrixMultiply[1] * rtb_MatrixMultiply[1] +
      rtb_MatrixMultiply[2] * rtb_MatrixMultiply[2])) / 2.0;
    rtb_Product3_i = cos(rtb_QuaternionstoDirectionCos_0);
    rtb_TmpSignalConversionAtCInp_1 = rt_atan2d_snf(-rtb_MatrixMultiply[1],
      rtb_MatrixMultiply[2]) / 2.0;
    rtb_Product2_a = cos(rtb_TmpSignalConversionAtCInp_1);
    rtb_sqrt = sin(rtb_QuaternionstoDirectionCos_0);
    rtb_Product1_ad = sin(rtb_TmpSignalConversionAtCInp_1);
    rtb_QuaternionstoDirectionCos_0 = 0.0 * rtb_sqrt;
    rtb_Sum1_idx_0 = rtb_QuaternionstoDirectionCos_0 * rtb_Product1_ad +
      rtb_Product3_i * rtb_Product2_a;
    rtb_TmpSignalConversionAtCInp_1 = 0.0 * rtb_Product3_i;
    rtb_Sum1_idx_1 = rtb_TmpSignalConversionAtCInp_1 * rtb_Product2_a - rtb_sqrt
      * rtb_Product1_ad;
    rtb_Sum1_idx_2 = rtb_TmpSignalConversionAtCInp_1 * rtb_Product1_ad +
      rtb_sqrt * rtb_Product2_a;
    rtb_Sum1_idx_3 = rtb_Product3_i * rtb_Product1_ad -
      rtb_QuaternionstoDirectionCos_0 * rtb_Product2_a;

    /* Product: '<S438>/Product2' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S440>/Product'
     */
    rtb_TmpSignalConversionAtCInp_4 = 0.7071067811860949 * rtb_Sum1_idx_2;

    /* Product: '<S438>/Product3' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S440>/Product1'
     */
    rtb_TmpSignalConversionAtCInp_3 = -0.0 * rtb_Sum1_idx_3;

    /* Product: '<S438>/Product' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S440>/Product2'
     */
    rtb_Product1_ad = 0.7071067811860949 * rtb_Sum1_idx_0;

    /* Product: '<S438>/Product1' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S440>/Product3'
     */
    rtb_Filter_g = -0.0 * rtb_Sum1_idx_1;

    /* Sum: '<S438>/Sum' incorporates:
     *  Product: '<S438>/Product'
     *  Product: '<S438>/Product1'
     *  Product: '<S438>/Product2'
     *  Product: '<S438>/Product3'
     */
    rtb_TmpSignalConversionAtCInp_1 = ((rtb_Product1_ad - rtb_Filter_g) -
      rtb_TmpSignalConversionAtCInp_4) - rtb_TmpSignalConversionAtCInp_3;

    /* Product: '<S439>/Product2' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S441>/Product'
     */
    rtb_QuaternionstoDirectionCos_0 = 0.7071067811860949 * rtb_Sum1_idx_3;

    /* Product: '<S439>/Product3' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S441>/Product1'
     */
    rtb_Sum1_idx_3 = rtb_Sum1_idx_2 * -0.0;

    /* Product: '<S439>/Product' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S441>/Product2'
     */
    rtb_Sum1_idx_1 *= 0.7071067811860949;

    /* Product: '<S439>/Product1' incorporates:
     *  Constant: '<S433>/Constant'
     *  Product: '<S441>/Product3'
     */
    rtb_Sum1_idx_2 = rtb_Sum1_idx_0 * -0.0;

    /* Sum: '<S439>/Sum' incorporates:
     *  Product: '<S439>/Product'
     *  Product: '<S439>/Product1'
     *  Product: '<S439>/Product2'
     *  Product: '<S439>/Product3'
     */
    rtb_Product3_i = ((rtb_Sum1_idx_1 + rtb_Sum1_idx_2) +
                      rtb_QuaternionstoDirectionCos_0) - rtb_Sum1_idx_3;

    /* Sum: '<S440>/Sum' */
    rtb_Product2_a = ((rtb_TmpSignalConversionAtCInp_4 -
                       rtb_TmpSignalConversionAtCInp_3) + rtb_Product1_ad) +
      rtb_Filter_g;

    /* Sum: '<S441>/Sum' */
    rtb_Product1_nd = ((rtb_QuaternionstoDirectionCos_0 + rtb_Sum1_idx_3) -
                       rtb_Sum1_idx_1) + rtb_Sum1_idx_2;

    /* Sqrt: '<S442>/sqrt' incorporates:
     *  Product: '<S443>/Product'
     *  Product: '<S443>/Product1'
     *  Product: '<S443>/Product2'
     *  Product: '<S443>/Product3'
     *  Sum: '<S443>/Sum'
     */
    rtb_sqrt = sqrt(((rtb_TmpSignalConversionAtCInp_1 *
                      rtb_TmpSignalConversionAtCInp_1 + rtb_Product3_i *
                      rtb_Product3_i) + rtb_Product2_a * rtb_Product2_a) +
                    rtb_Product1_nd * rtb_Product1_nd);

    /* Sum: '<S429>/Sum1' incorporates:
     *  Gain: '<S429>/Gain'
     *  Gain: '<S429>/Gain1'
     *  Product: '<S437>/Product'
     *  Product: '<S437>/Product1'
     *  Product: '<S437>/Product2'
     *  Product: '<S437>/Product3'
     */
    rtb_Sum1_idx_0 = rtb_TmpSignalConversionAtCInp_1 / rtb_sqrt *
      0.0050000000000000044 + 0.995 * rtb_Sin;
    rtb_Sum1_idx_1 = rtb_Product3_i / rtb_sqrt * 0.0050000000000000044 + 0.995 *
      rtb_Integrator_b;
    rtb_Sum1_idx_2 = rtb_Product2_a / rtb_sqrt * 0.0050000000000000044 + 0.995 *
      rtb_TmpSignalConversionAtCInp_2;
    rtb_Sum1_idx_3 = rtb_Product1_nd / rtb_sqrt * 0.0050000000000000044 + 0.995 *
      rtb_TmpSignalConversionAtCInp_0;

    /* Sqrt: '<S434>/sqrt' incorporates:
     *  Product: '<S435>/Product'
     *  Product: '<S435>/Product1'
     *  Product: '<S435>/Product2'
     *  Product: '<S435>/Product3'
     *  Sum: '<S435>/Sum'
     */
    rtb_sqrt = sqrt(((rtb_Sum1_idx_0 * rtb_Sum1_idx_0 + rtb_Sum1_idx_1 *
                      rtb_Sum1_idx_1) + rtb_Sum1_idx_2 * rtb_Sum1_idx_2) +
                    rtb_Sum1_idx_3 * rtb_Sum1_idx_3);

    /* Product: '<S432>/Product' incorporates:
     *  Merge: '<S423>/Merge'
     */
    rtDW->qEst_na[0] = rtb_Sum1_idx_0 / rtb_sqrt;

    /* Product: '<S432>/Product1' incorporates:
     *  Merge: '<S423>/Merge'
     */
    rtDW->qEst_na[1] = rtb_Sum1_idx_1 / rtb_sqrt;

    /* Product: '<S432>/Product2' incorporates:
     *  Merge: '<S423>/Merge'
     */
    rtDW->qEst_na[2] = rtb_Sum1_idx_2 / rtb_sqrt;

    /* Product: '<S432>/Product3' incorporates:
     *  Merge: '<S423>/Merge'
     */
    rtDW->qEst_na[3] = rtb_Sum1_idx_3 / rtb_sqrt;

    /* Update for Delay generated from: '<S429>/Delay' incorporates:
     *  Inport: '<Root>/sensor_bus'
     */
    for (i = 0; i < 499; i++) {
      uIdx = (i + 1) * 3;
      rtDW->Delay_3_DSTATE_e[i * 3] = rtDW->Delay_3_DSTATE_e[uIdx];
      rtDW->Delay_3_DSTATE_e[i * 3 + 1] = rtDW->Delay_3_DSTATE_e[uIdx + 1];
      rtDW->Delay_3_DSTATE_e[i * 3 + 2] = rtDW->Delay_3_DSTATE_e[uIdx + 2];
    }

    rtDW->Delay_3_DSTATE_e[1497] = rtU_sensor_bus_e->fBdyMeas_mps2[0];
    rtDW->Delay_3_DSTATE_e[1498] = rtU_sensor_bus_e->fBdyMeas_mps2[1];
    rtDW->Delay_3_DSTATE_e[1499] = rtU_sensor_bus_e->fBdyMeas_mps2[2];

    /* End of Update for Delay generated from: '<S429>/Delay' */
    /* End of Outputs for SubSystem: '<S423>/Complementary Filter' */
  } else {
    /* Outputs for IfAction SubSystem: '<S423>/Pass Through' incorporates:
     *  ActionPort: '<S430>/Action Port'
     */
    /* Merge: '<S423>/Merge' incorporates:
     *  SignalConversion generated from: '<S430>/qEst_na'
     */
    rtDW->qEst_na[0] = rtb_Sin;
    rtDW->qEst_na[1] = rtb_Integrator_b;
    rtDW->qEst_na[2] = rtb_TmpSignalConversionAtCInp_2;
    rtDW->qEst_na[3] = rtb_TmpSignalConversionAtCInp_0;

    /* End of Outputs for SubSystem: '<S423>/Pass Through' */
  }

  /* End of If: '<S423>/If' */

  /* Product: '<S445>/Product3' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S447>/Product1'
   */
  rtb_Sum1_idx_1 = 0.0 * rtDW->qEst_na[3];
  rtb_Sin = rtb_Sum1_idx_1;

  /* Product: '<S445>/Product1' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S447>/Product3'
   */
  rtb_TmpSignalConversionAtCInp_1 = 0.0 * rtDW->qEst_na[1];

  /* Sum: '<S445>/Sum' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S445>/Product'
   *  Product: '<S445>/Product1'
   *  Product: '<S445>/Product2'
   */
  rtb_TmpSignalConversionAtCInp_0 = ((0.707106781187 * rtDW->qEst_na[0] -
    rtb_TmpSignalConversionAtCInp_1) - -0.707106781187 * rtDW->qEst_na[2]) -
    rtb_Sin;

  /* Product: '<S446>/Product3' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S448>/Product1'
   */
  rtb_Product3_i = rtDW->qEst_na[2] * 0.0;
  rtb_Sin = rtb_Product3_i;

  /* Product: '<S446>/Product1' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S448>/Product3'
   */
  rtb_Integrator_b = rtDW->qEst_na[0] * 0.0;

  /* Sum: '<S446>/Sum' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S446>/Product'
   *  Product: '<S446>/Product1'
   *  Product: '<S446>/Product2'
   */
  rtb_TmpSignalConversionAtCInp_2 = ((0.707106781187 * rtDW->qEst_na[1] +
    rtb_Integrator_b) + -0.707106781187 * rtDW->qEst_na[3]) - rtb_Sin;

  /* Product: '<S447>/Product3' */
  rtb_Sin = rtb_TmpSignalConversionAtCInp_1;

  /* Sum: '<S447>/Sum' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S447>/Product'
   *  Product: '<S447>/Product2'
   */
  rtb_TmpSignalConversionAtCInp_1 = ((0.707106781187 * rtDW->qEst_na[2] -
    rtb_Sum1_idx_1) + rtDW->qEst_na[0] * -0.707106781187) + rtb_Sin;

  /* Product: '<S448>/Product3' */
  rtb_Sin = rtb_Integrator_b;

  /* SignalConversion generated from: '<S425>/Quaternions to Rotation Angles' incorporates:
   *  Constant: '<S425>/Constant'
   *  Product: '<S448>/Product'
   *  Product: '<S448>/Product2'
   *  Sum: '<S448>/Sum'
   */
  rtb_Sum1_idx_3 = ((0.707106781187 * rtDW->qEst_na[3] + rtb_Product3_i) -
                    rtDW->qEst_na[1] * -0.707106781187) + rtb_Sin;

  /* Quat2Angle: '<S425>/Quaternions to Rotation Angles' incorporates:
   *  SignalConversion generated from: '<S425>/Quaternions to Rotation Angles'
   *  Trigonometry: '<S222>/Cos1'
   */
  rtb_MathFunction_idx_2 = 1.0 / sqrt(((rtb_TmpSignalConversionAtCInp_0 *
    rtb_TmpSignalConversionAtCInp_0 + rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_2) + rtb_TmpSignalConversionAtCInp_1 *
    rtb_TmpSignalConversionAtCInp_1) + rtb_Sum1_idx_3 * rtb_Sum1_idx_3);
  rtb_Product1_ad = rtb_MathFunction_idx_2 * rtb_TmpSignalConversionAtCInp_0;
  rtb_TmpSignalConversionAtCInp_2 *= rtb_MathFunction_idx_2;
  rtb_Integrator_b = rtb_MathFunction_idx_2 * rtb_TmpSignalConversionAtCInp_1;
  rtb_TmpSignalConversionAtCInp_1 = rtb_MathFunction_idx_2 * rtb_Sum1_idx_3;
  rtb_MathFunction_idx_2 = rtb_Product1_ad * rtb_Product1_ad;
  rtb_QuaternionstoDirectionCos_0 = rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_2;
  rtb_Sin = rtb_Integrator_b * rtb_Integrator_b;
  rtb_TmpSignalConversionAtCInp_0 = rtb_TmpSignalConversionAtCInp_1 *
    rtb_TmpSignalConversionAtCInp_1;
  rtb_Sum1_idx_3 = ((rtb_MathFunction_idx_2 + rtb_QuaternionstoDirectionCos_0) -
                    rtb_Sin) - rtb_TmpSignalConversionAtCInp_0;
  rtb_TmpSignalConversionAtCInp_4 = rtb_TmpSignalConversionAtCInp_2 *
    rtb_Integrator_b;
  rtb_TmpSignalConversionAtCInp_3 = rtb_Product1_ad *
    rtb_TmpSignalConversionAtCInp_1;
  rtb_Sum1_idx_2 = (rtb_TmpSignalConversionAtCInp_4 +
                    rtb_TmpSignalConversionAtCInp_3) * 2.0;
  rtb_TSamp = rtb_TmpSignalConversionAtCInp_2 * rtb_TmpSignalConversionAtCInp_1;
  rtb_Product3_i = rtb_Product1_ad * rtb_Integrator_b;
  rtb_Sum1_idx_0 = (rtb_TSamp - rtb_Product3_i) * 2.0;
  rtb_Filter_g = (rtb_TmpSignalConversionAtCInp_4 -
                  rtb_TmpSignalConversionAtCInp_3) * 2.0;
  rtb_QuaternionstoDirectionCos_0 = rtb_MathFunction_idx_2 -
    rtb_QuaternionstoDirectionCos_0;
  rtb_Product2_a = (rtb_QuaternionstoDirectionCos_0 + rtb_Sin) -
    rtb_TmpSignalConversionAtCInp_0;
  rtb_Sum4_a = rtb_Integrator_b * rtb_TmpSignalConversionAtCInp_1;
  rtb_TmpSignalConversionAtCInp_1 = rtb_Product1_ad *
    rtb_TmpSignalConversionAtCInp_2;
  rtb_Product1_nd = (rtb_Sum4_a + rtb_TmpSignalConversionAtCInp_1) * 2.0;
  rtb_Integrator_b = (rtb_TSamp + rtb_Product3_i) * 2.0;
  rtb_sqrt = (rtb_Sum4_a - rtb_TmpSignalConversionAtCInp_1) * 2.0;
  rtb_MathFunction_m_tmp = (rtb_QuaternionstoDirectionCos_0 - rtb_Sin) +
    rtb_TmpSignalConversionAtCInp_0;
  if (-rtb_Sum1_idx_0 <= -1.0) {
    rtb_Sin = -1.0;
  } else if (-rtb_Sum1_idx_0 >= 1.0) {
    rtb_Sin = 1.0;
  } else {
    rtb_Sin = -rtb_Sum1_idx_0;
  }

  rtb_QuaternionstoDirectionCos_0 = asin(rtb_Sin);
  if (fabs(rtb_Sin) == 1.0) {
    rtb_accBdyEst_mps2[0] = rt_atan2d_snf(-rtb_Filter_g, rtb_Product2_a);
    rtb_TmpSignalConversionAtCInp_4 = 0.0;
    rtb_TmpSignalConversionAtCInp_3 = 0.0;
  } else {
    rtb_TmpSignalConversionAtCInp_4 = rt_atan2d_snf(rtb_Sum1_idx_2,
      rtb_Sum1_idx_3);
    rtb_TmpSignalConversionAtCInp_3 = rt_atan2d_snf(rtb_Product1_nd,
      rtb_MathFunction_m_tmp);
    rtb_accBdyEst_mps2[0] = 0.0;
  }

  rtb_Product3_i = cos(rtb_TmpSignalConversionAtCInp_3);
  rtb_TmpSignalConversionAtCInp_1 = sin(rtb_TmpSignalConversionAtCInp_3);
  rtb_Sum1_idx_1 = cos(rtb_QuaternionstoDirectionCos_0);
  rtb_Sin = rtb_Sum1_idx_1;
  rtb_TmpSignalConversionAtCInp_0 = sin(rtb_QuaternionstoDirectionCos_0);
  rtb_MathFunction_idx_2 = 0.0 * rtb_TmpSignalConversionAtCInp_0;
  rtb_Product1_ad = rtb_MathFunction_idx_2 + rtb_Sin;
  rtb_TSamp = 0.0 * rtb_Sin;
  rtb_Product1_o = rtb_TSamp - rtb_TmpSignalConversionAtCInp_0;
  rtb_MathFunction_idx_0 = rtb_Product3_i * 0.0;
  rtb_TmpSignalConversionAtCInp_2 = (rtb_TSamp + rtb_MathFunction_idx_0) +
    rtb_TmpSignalConversionAtCInp_1 * rtb_TmpSignalConversionAtCInp_0;
  rtb_TSamp_gj = rtb_TmpSignalConversionAtCInp_1 * 0.0 + rtb_Product3_i;
  rtb_Sum4_a = 0.0 * -rtb_TmpSignalConversionAtCInp_0;
  rtb_TSamp_jt = (rtb_Sum4_a + rtb_MathFunction_idx_0) +
    rtb_TmpSignalConversionAtCInp_1 * rtb_Sin;
  rtb_MathFunction_idx_1 = -rtb_TmpSignalConversionAtCInp_1 * 0.0;
  rtb_TSamp_k = (rtb_TSamp + rtb_MathFunction_idx_1) +
    rtb_TmpSignalConversionAtCInp_0 * rtb_Product3_i;
  rtb_MathFunction_idx_0 -= rtb_TmpSignalConversionAtCInp_1;
  rtb_MathFunction_idx_1 = (rtb_Sum4_a + rtb_MathFunction_idx_1) +
    rtb_Product3_i * rtb_Sin;
  rtb_Product3_i = cos(rtb_TmpSignalConversionAtCInp_4);
  rtb_TmpSignalConversionAtCInp_1 = sin(rtb_TmpSignalConversionAtCInp_4);
  rtb_Gain_a = rtb_TSamp + rtb_MathFunction_idx_2;
  rtb_Switch2_f = rtb_Sum4_a + rtb_TSamp;
  rtb_Product1_j3 = rtb_TSamp + rtb_TmpSignalConversionAtCInp_0;
  rtb_Sum4_a += rtb_Sin;
  rtb_Sin = cos(rtb_accBdyEst_mps2[0]);
  rtb_TmpSignalConversionAtCInp_0 = sin(rtb_accBdyEst_mps2[0]);
  rtb_TSamp = rtb_Product1_o * 0.0;
  rtb_MathFunction_idx_2 = rtb_Switch2_f * 0.0;
  rtb_Switch2_m = 0.0 * -rtb_TmpSignalConversionAtCInp_0;
  rtb_UkYk1_l = 0.0 * rtb_Sin;
  rtb_PProdOut_b = rtb_Sum4_a * 0.0;
  rtb_Sum1_idx_0 = fabs(rtb_Sum1_idx_0 - (rtb_Product1_ad * 0.0 + rtb_Product1_o));
  rtb_Product1_o = rtb_TSamp_jt * 0.0;
  rtb_Divide = rtb_MathFunction_idx_1 * 0.0;
  if ((((((((fabs(rtb_Sum1_idx_3 - ((rtb_Product1_ad * rtb_Sin + rtb_Switch2_m)
               + rtb_TSamp)) + fabs(rtb_Sum1_idx_2 - ((rtb_Product1_ad *
                rtb_TmpSignalConversionAtCInp_0 + rtb_UkYk1_l) + rtb_TSamp))) +
            rtb_Sum1_idx_0) + fabs(rtb_Filter_g - ((rtb_Sin * rtb_Gain_a -
              rtb_TmpSignalConversionAtCInp_0) + rtb_MathFunction_idx_2))) +
          fabs(rtb_Product2_a - ((rtb_TmpSignalConversionAtCInp_0 * rtb_Gain_a +
             rtb_Sin) + rtb_MathFunction_idx_2))) + fabs(rtb_Product1_nd -
          (rtb_Gain_a * 0.0 + rtb_Switch2_f))) + fabs(rtb_Integrator_b -
         ((rtb_Sin * rtb_Product1_j3 + rtb_Switch2_m) + rtb_PProdOut_b))) + fabs
       (rtb_sqrt - ((rtb_TmpSignalConversionAtCInp_0 * rtb_Product1_j3 +
                     rtb_UkYk1_l) + rtb_PProdOut_b))) + fabs
      (rtb_MathFunction_m_tmp - (rtb_Product1_j3 * 0.0 + rtb_Sum4_a)) <=
      (((((((fabs(rtb_Sum1_idx_3 - ((rtb_Product1_ad * rtb_Product3_i + 0.0 *
                -rtb_TmpSignalConversionAtCInp_1) + rtb_TSamp)) + fabs
             (rtb_Sum1_idx_2 - ((rtb_Product1_ad *
                rtb_TmpSignalConversionAtCInp_1 + 0.0 * rtb_Product3_i) +
               rtb_TSamp))) + rtb_Sum1_idx_0) + fabs(rtb_Filter_g -
            ((rtb_Product3_i * rtb_TmpSignalConversionAtCInp_2 +
              -rtb_TmpSignalConversionAtCInp_1 * rtb_TSamp_gj) + rtb_Product1_o)))
          + fabs(rtb_Product2_a - ((rtb_TmpSignalConversionAtCInp_1 *
             rtb_TmpSignalConversionAtCInp_2 + rtb_TSamp_gj * rtb_Product3_i) +
            rtb_Product1_o))) + fabs(rtb_Product1_nd -
          ((rtb_TmpSignalConversionAtCInp_2 * 0.0 + rtb_TSamp_gj * 0.0) +
           rtb_TSamp_jt))) + fabs(rtb_Integrator_b - ((rtb_Product3_i *
           rtb_TSamp_k + -rtb_TmpSignalConversionAtCInp_1 *
           rtb_MathFunction_idx_0) + rtb_Divide))) + fabs(rtb_sqrt -
        ((rtb_TmpSignalConversionAtCInp_1 * rtb_TSamp_k + rtb_Product3_i *
          rtb_MathFunction_idx_0) + rtb_Divide))) + fabs(rtb_MathFunction_m_tmp
       - ((rtb_TSamp_k * 0.0 + rtb_MathFunction_idx_0 * 0.0) +
          rtb_MathFunction_idx_1))) {
    rtb_TmpSignalConversionAtCInp_4 = rtb_accBdyEst_mps2[0];
    rtb_TmpSignalConversionAtCInp_3 = 0.0;
  }

  /* Product: '<S317>/DProd Out' incorporates:
   *  Constant: '<S224>/Constant4'
   *  Constant: '<S2>/Constant'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum2'
   */
  rtb_Sin = (0.0 - rtb_TmpSignalConversionAtCInp_3) * 0.0;

  /* Sum: '<S319>/SumD' incorporates:
   *  DiscreteIntegrator: '<S319>/Filter'
   */
  rtb_Sin -= rtDW->Filter_DSTATE;

  /* Product: '<S327>/NProd Out' incorporates:
   *  Constant: '<S224>/Constant4'
   */
  rtb_TmpSignalConversionAtCInp_0 = rtb_Sin * 100.0;

  /* Product: '<S286>/Product1' incorporates:
   *  Constant: '<S2>/Constant'
   *  DiscreteIntegrator: '<S324>/Integrator'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum2'
   *  Sum: '<S333>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product3_i = (((0.0 - rtb_TmpSignalConversionAtCInp_3) +
                     rtDW->Integrator_DSTATE) + rtb_TmpSignalConversionAtCInp_0)
    * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S345>/Switch2' incorporates:
   *  Constant: '<S224>/Constant2'
   *  Constant: '<S224>/Constant3'
   *  RelationalOperator: '<S345>/LowerRelop1'
   *  RelationalOperator: '<S345>/UpperRelop'
   *  Switch: '<S345>/Switch'
   */
  if (rtb_Product3_i > 2.0) {
    rtb_Product1_nd = 2.0;
  } else if (rtb_Product3_i < -2.0) {
    /* Switch: '<S345>/Switch' incorporates:
     *  Constant: '<S224>/Constant3'
     */
    rtb_Product1_nd = -2.0;
  } else {
    rtb_Product1_nd = rtb_Product3_i;
  }

  /* End of Switch: '<S345>/Switch2' */

  /* Delay: '<S343>/Delay' */
  if (rtDW->icLoad) {
    rtDW->Delay_DSTATE = rtb_Product1_nd;
  }

  /* Product: '<S343>/delta rise limit' incorporates:
   *  Constant: '<S224>/Constant'
   *  SampleTimeMath: '<S343>/sample time'
   *
   * About '<S343>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_TmpSignalConversionAtCInp_2 = 0.05;

  /* Sum: '<S343>/Difference Inputs1' incorporates:
   *  Delay: '<S343>/Delay'
   *
   * Block description for '<S343>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Sin = rtb_Product1_nd - rtDW->Delay_DSTATE;

  /* Switch: '<S344>/Switch2' incorporates:
   *  RelationalOperator: '<S344>/LowerRelop1'
   */
  if (!(rtb_Sin > 0.05)) {
    /* Switch: '<S344>/Switch' incorporates:
     *  RelationalOperator: '<S344>/UpperRelop'
     */
    if (rtb_Sin < -0.05) {
      rtb_TmpSignalConversionAtCInp_2 = -0.05;
    } else {
      rtb_TmpSignalConversionAtCInp_2 = rtb_Sin;
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
  rtb_Integrator_b = rtb_TmpSignalConversionAtCInp_2 + rtDW->Delay_DSTATE;

  /* Sum: '<S8>/Sum' incorporates:
   *  DiscreteTransferFcn: '<S424>/Gyro Filter'
   */
  rtb_TmpSignalConversionAtCInp_2 = rtb_Integrator_b - rtb_TSamp_a;

  /* UnitDelay generated from: '<S406>/Unit Delay' */
  rtb_Sin = rtDW->UnitDelay_15_DSTATE;

  /* UnitDelay generated from: '<S406>/Unit Delay' */
  rtb_Filter_g = rtDW->UnitDelay_16_DSTATE;

  /* UnitDelay generated from: '<S406>/Unit Delay' */
  rtb_Product1_ad = rtDW->UnitDelay_17_DSTATE;

  /* Product: '<S451>/Matrix Multiply' incorporates:
   *  Constant: '<S451>/Constant'
   *  Quat2Dcm: '<S451>/Quaternions to  Direction Cosine Matrix'
   */
  rtb_TmpSignalConversionAtCInp_1 = 0.0;
  rtb_Sum1_idx_3 = 0.0;
  rtb_Sum1_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    rtb_TSamp = rtCP__Constant_Value_bn[i];
    rtb_TmpSignalConversionAtCInp_1 += rtb_QuaternionstoDirectionCosin[3 * i] *
      rtb_TSamp;
    rtb_Sum1_idx_3 += rtb_QuaternionstoDirectionCosin[3 * i + 1] * rtb_TSamp;
    rtb_Sum1_idx_2 += rtb_QuaternionstoDirectionCosin[3 * i + 2] * rtb_TSamp;

    /* Sum: '<S411>/Sum2' incorporates:
     *  Constant: '<S451>/Constant'
     *  Inport: '<Root>/sensor_bus'
     *  Quat2Dcm: '<S451>/Quaternions to  Direction Cosine Matrix'
     *  UnitDelay generated from: '<S406>/Unit Delay'
     */
    rtb_Product_k4[i] = rtU_sensor_bus_e->fBdyMeas_mps2[i] -
      rtDW->UnitDelay_12_DSTATE[i];
  }

  /* Sum: '<S411>/Sum1' incorporates:
   *  Product: '<S451>/Matrix Multiply'
   */
  rtb_MathFunction_m_tmp = rtb_TmpSignalConversionAtCInp_1 + rtb_Product_k4[0];
  rtb_accBdyEst_mps2[0] = rtb_MathFunction_m_tmp;

  /* DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtb_TSamp_gj = rtb_MathFunction_m_tmp - 0.0 * rtDW->AccelFilter_states[0];

  /* Sum: '<S411>/Sum1' incorporates:
   *  Product: '<S451>/Matrix Multiply'
   */
  rtb_MathFunction_m_tmp = rtb_Sum1_idx_3 + rtb_Product_k4[1];
  rtb_accBdyEst_mps2[1] = rtb_MathFunction_m_tmp;

  /* DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtb_TSamp_jt = rtb_MathFunction_m_tmp - 0.0 * rtDW->AccelFilter_states[1];
  rtb_TSamp = 0.5 * rtb_TSamp_jt + 0.5 * rtDW->AccelFilter_states[1];

  /* Sum: '<S411>/Sum1' incorporates:
   *  Product: '<S451>/Matrix Multiply'
   */
  rtb_MathFunction_m_tmp = rtb_Sum1_idx_2 + rtb_Product_k4[2];
  rtb_accBdyEst_mps2[2] = rtb_MathFunction_m_tmp;

  /* DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtb_TSamp_k = rtb_MathFunction_m_tmp - 0.0 * rtDW->AccelFilter_states[2];

  /* Product: '<S407>/Product' incorporates:
   *  DiscreteTransferFcn: '<S407>/Accel Filter'
   *  Math: '<S414>/Math Function'
   */
  rtb_TmpSignalConversionAtCInp_1 = 0.5 * rtb_TSamp_gj + 0.5 *
    rtDW->AccelFilter_states[0];
  rtb_Sum1_idx_3 = 0.5 * rtb_TSamp_k + 0.5 * rtDW->AccelFilter_states[2];
  for (i = 0; i < 3; i++) {
    rtb_MatrixMultiply[i] = (rtb_MathFunction_k[3 * i + 1] * rtb_TSamp +
      rtb_MathFunction_k[3 * i] * rtb_TmpSignalConversionAtCInp_1) +
      rtb_MathFunction_k[3 * i + 2] * rtb_Sum1_idx_3;
  }

  /* End of Product: '<S407>/Product' */

  /* Sum: '<S407>/Sum4' incorporates:
   *  Gain: '<S407>/Gain3'
   */
  rtb_MathFunction_idx_0 = 0.01 * rtb_MatrixMultiply[0] + rtb_Sin;
  rtb_MathFunction_idx_1 = 0.01 * rtb_MatrixMultiply[1] + rtb_Filter_g;
  rtb_MathFunction_idx_2 = 0.01 * rtb_MatrixMultiply[2] + rtb_Product1_ad;

  /* DotProduct: '<S450>/Dot Product' */
  rtb_Sin = (rtb_MathFunction_idx_0 * rtb_MathFunction_idx_0 +
             rtb_MathFunction_idx_1 * rtb_MathFunction_idx_1) +
    rtb_MathFunction_idx_2 * rtb_MathFunction_idx_2;

  /* Gain: '<S450>/Gain1' incorporates:
   *  Gain: '<S450>/Gain'
   */
  rtb_Sin = 0.5 * rtb_Sin * 1.225;

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
  LookUp_real_T_real_T( &(rtb_Filter_g), rtCP__Constant4_Value, rtb_Sin,
                       rtCP__Internalbreakpoints_Value, 2U);

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
  LookUp_real_T_real_T( &(rtb_Product1_ad), rtCP__Constant6_Value, rtb_Sin,
                       rtCP__Internalbreakpoints_Value, 2U);

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
  LookUp_real_T_real_T( &(rtb_Filter_b), rtCP__Constant7_Value, rtb_Sin,
                       rtCP__Internalbreakpoints_Value, 2U);

  /* S-Function (sfix_look1_dyn): '<S217>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S11>/Constant4'
   *  Constant: '<S153>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S217>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Product1_g), rtCP__Constant4_Value_l, rtb_Sin,
                       rtCP__Internalbreakpoints_Val_d, 2U);

  /* S-Function (sfix_look1_dyn): '<S214>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S11>/Constant6'
   *  Constant: '<S153>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S214>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Filter_e), rtCP__Constant6_Value_e, rtb_Sin,
                       rtCP__Internalbreakpoints_Val_d, 2U);

  /* S-Function (sfix_look1_dyn): '<S216>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S11>/Constant7'
   *  Constant: '<S153>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S216>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_k), rtCP__Constant7_Value_n,
                       rtb_Sin, rtCP__Internalbreakpoints_Val_d, 2U);

  /* S-Function (sfix_look1_dyn): '<S147>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S10>/Constant4'
   *  Constant: '<S83>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S147>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Integrator_g), rtCP__Constant4_Value_c, rtb_Sin,
                       rtCP__Internalbreakpoints_Val_f, 2U);

  /* Product: '<S127>/PProd Out' */
  rtb_Product2_a = rtb_TmpSignalConversionAtCInp_2 * rtb_Integrator_g;

  /* DiscreteIntegrator: '<S122>/Integrator' */
  rtb_Integrator_g = rtDW->Integrator_DSTATE_b;

  /* S-Function (sfix_look1_dyn): '<S144>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S10>/Constant6'
   *  Constant: '<S83>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S144>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Filter_c), rtCP__Constant6_Value_p, rtb_Sin,
                       rtCP__Internalbreakpoints_Val_f, 2U);

  /* Product: '<S115>/DProd Out' */
  rtb_sqrt = rtb_TmpSignalConversionAtCInp_2 * rtb_Filter_c;

  /* DiscreteIntegrator: '<S117>/Filter' */
  rtb_Filter_c = rtDW->Filter_DSTATE_p;

  /* S-Function (sfix_look1_dyn): '<S146>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S83>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S146>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_Integrator_fe), rtCP__Constant7_Value_o, rtb_Sin,
                       rtCP__Internalbreakpoints_Val_f, 2U);

  /* Product: '<S125>/NProd Out' incorporates:
   *  Sum: '<S117>/SumD'
   */
  rtb_Filter_c = (rtb_sqrt - rtb_Filter_c) * rtb_Integrator_fe;

  /* Sum: '<S131>/Sum' */
  rtb_Integrator_fe = (rtb_Product2_a + rtb_Integrator_g) + rtb_Filter_c;

  /* Product: '<S82>/Product1' incorporates:
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_o = rtb_Integrator_fe * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Gain: '<S84>/Gain' */
  rtb_Gain_a = 0.5 * rtb_Product1_o;

  /* Switch: '<S151>/Switch2' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant3'
   *  RelationalOperator: '<S151>/LowerRelop1'
   *  RelationalOperator: '<S151>/UpperRelop'
   *  Switch: '<S151>/Switch'
   */
  if (rtb_Gain_a > 5.0) {
    rtb_Switch2_f = 5.0;
  } else if (rtb_Gain_a < -5.0) {
    /* Switch: '<S151>/Switch' incorporates:
     *  Constant: '<S10>/Constant3'
     */
    rtb_Switch2_f = -5.0;
  } else {
    rtb_Switch2_f = rtb_Gain_a;
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
  rtb_Integrator_fe = 0.9;

  /* Sum: '<S149>/Difference Inputs1' incorporates:
   *  Delay: '<S149>/Delay'
   *
   * Block description for '<S149>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Integrator_g = rtb_Switch2_f - rtDW->Delay_DSTATE_p;

  /* Switch: '<S150>/Switch2' incorporates:
   *  RelationalOperator: '<S150>/LowerRelop1'
   */
  if (!(rtb_Integrator_g > 0.9)) {
    /* Switch: '<S150>/Switch' incorporates:
     *  RelationalOperator: '<S150>/UpperRelop'
     */
    if (rtb_Integrator_g < -0.9) {
      rtb_Integrator_fe = -0.9;
    } else {
      rtb_Integrator_fe = rtb_Integrator_g;
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
  rtb_Integrator_g = rtb_Integrator_fe + rtDW->Delay_DSTATE_p;

  /* Trigonometry: '<S222>/Cos' incorporates:
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   */
  rtb_Integrator_fe = cos(rtb_TmpSignalConversionAtCInp_3);

  /* Trigonometry: '<S222>/Sin' incorporates:
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   */
  rtb_TmpSignalConversionAtCInp_1 = sin(rtb_TmpSignalConversionAtCInp_3);

  /* Sum: '<S222>/Sum4' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Product: '<S222>/Product'
   *  Product: '<S222>/Product1'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum'
   *  Sum: '<S222>/Sum1'
   */
  rtb_Sum4_a = (0.0 - rtb_QuaternionstoDirectionCos_0) * rtb_Integrator_fe +
    rtb_TmpSignalConversionAtCInp_1 * rtb_Sum1_idx_1 * (0.0 -
    rtb_TmpSignalConversionAtCInp_4);

  /* Product: '<S267>/NProd Out' incorporates:
   *  Constant: '<S223>/Constant4'
   *  DiscreteIntegrator: '<S259>/Filter'
   *  Product: '<S257>/DProd Out'
   *  Sum: '<S259>/SumD'
   */
  rtb_Product2_a = rtb_Sum4_a * 0.0 - rtDW->Filter_DSTATE_n;

  /* Product: '<S226>/Product1' incorporates:
   *  Constant: '<S223>/Constant4'
   *  DiscreteIntegrator: '<S264>/Integrator'
   *  Product: '<S269>/PProd Out'
   *  Sum: '<S273>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_j3 = ((rtb_Sum4_a * 2.0 + rtDW->Integrator_DSTATE_g) +
                     rtb_Product2_a) * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S285>/Switch2' incorporates:
   *  Constant: '<S223>/Constant2'
   *  Constant: '<S223>/Constant3'
   *  RelationalOperator: '<S285>/LowerRelop1'
   *  RelationalOperator: '<S285>/UpperRelop'
   *  Switch: '<S285>/Switch'
   */
  if (rtb_Product1_j3 > 0.4) {
    rtb_Switch2_m = 0.4;
  } else if (rtb_Product1_j3 < -0.4) {
    /* Switch: '<S285>/Switch' incorporates:
     *  Constant: '<S223>/Constant3'
     */
    rtb_Switch2_m = -0.4;
  } else {
    rtb_Switch2_m = rtb_Product1_j3;
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
  rtb_sqrt = 0.005;

  /* Sum: '<S283>/Difference Inputs1' incorporates:
   *  Delay: '<S283>/Delay'
   *
   * Block description for '<S283>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_l = rtb_Switch2_m - rtDW->Delay_DSTATE_c;

  /* Switch: '<S284>/Switch2' incorporates:
   *  RelationalOperator: '<S284>/LowerRelop1'
   */
  if (!(rtb_UkYk1_l > 0.005)) {
    /* Switch: '<S284>/Switch' incorporates:
     *  RelationalOperator: '<S284>/UpperRelop'
     */
    if (rtb_UkYk1_l < -0.005) {
      rtb_sqrt = -0.005;
    } else {
      rtb_sqrt = rtb_UkYk1_l;
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
  rtb_UkYk1_l = rtb_sqrt + rtDW->Delay_DSTATE_c;

  /* Sum: '<S8>/Sum2' incorporates:
   *  DiscreteTransferFcn: '<S424>/Gyro Filter'
   */
  rtb_sqrt = rtb_UkYk1_l - rtb_TSamp_b0;

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
   *  Constant: '<S14>/Constant'
   *  Gain: '<S14>/Gain'
   */
  rtb_Divide = -6756.0 * rtb_Product1_ad / 50000.0;

  /* Switch: '<S81>/Switch2' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  RelationalOperator: '<S81>/LowerRelop1'
   *  RelationalOperator: '<S81>/UpperRelop'
   *  Switch: '<S81>/Switch'
   */
  if (rtb_Divide > 45.0) {
    rtb_Switch2_j = 45.0;
  } else if (rtb_Divide < -45.0) {
    /* Switch: '<S81>/Switch' incorporates:
     *  Constant: '<S9>/Constant3'
     */
    rtb_Switch2_j = -45.0;
  } else {
    rtb_Switch2_j = rtb_Divide;
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
  rtb_Filter_b = 1.8;

  /* Sum: '<S79>/Difference Inputs1' incorporates:
   *  Delay: '<S79>/Delay'
   *
   * Block description for '<S79>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_PProdOut_b = rtb_Switch2_j - rtDW->Delay_DSTATE_f;

  /* Switch: '<S80>/Switch2' incorporates:
   *  RelationalOperator: '<S80>/LowerRelop1'
   */
  if (!(rtb_PProdOut_b > 1.8)) {
    /* Switch: '<S80>/Switch' incorporates:
     *  RelationalOperator: '<S80>/UpperRelop'
     */
    if (rtb_PProdOut_b < -1.8) {
      rtb_Filter_b = -1.8;
    } else {
      rtb_Filter_b = rtb_PProdOut_b;
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
  rtb_PProdOut_b = rtb_Filter_b + rtDW->Delay_DSTATE_f;

  /* Sum: '<S222>/Sum3' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Product: '<S222>/Product2'
   *  Product: '<S222>/Product3'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum'
   *  Sum: '<S222>/Sum1'
   *  UnaryMinus: '<S222>/Unary Minus'
   */
  rtb_Sum3 = (0.0 - rtb_QuaternionstoDirectionCos_0) *
    -rtb_TmpSignalConversionAtCInp_1 + rtb_Integrator_fe * rtb_Sum1_idx_1 * (0.0
    - rtb_TmpSignalConversionAtCInp_4);

  /* Product: '<S377>/DProd Out' incorporates:
   *  Constant: '<S225>/Constant4'
   */
  rtb_Integrator_fe = rtb_Sum3 * 0.0;

  /* DiscreteIntegrator: '<S379>/Filter' */
  rtb_Filter_b = rtDW->Filter_DSTATE_c;

  /* Product: '<S387>/NProd Out' incorporates:
   *  Sum: '<S379>/SumD'
   */
  rtb_Filter_b = rtb_Integrator_fe - rtb_Filter_b;

  /* Product: '<S346>/Product1' incorporates:
   *  Constant: '<S225>/Constant4'
   *  DiscreteIntegrator: '<S384>/Integrator'
   *  Product: '<S389>/PProd Out'
   *  Sum: '<S393>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_da = ((rtb_Sum3 * 2.0 + rtDW->Integrator_DSTATE_l) + rtb_Filter_b)
    * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S405>/Switch2' incorporates:
   *  Constant: '<S225>/Constant2'
   *  Constant: '<S225>/Constant3'
   *  RelationalOperator: '<S405>/LowerRelop1'
   *  RelationalOperator: '<S405>/UpperRelop'
   *  Switch: '<S405>/Switch'
   */
  if (rtb_Product1_da > 0.4) {
    rtb_Switch2_d = 0.4;
  } else if (rtb_Product1_da < -0.4) {
    /* Switch: '<S405>/Switch' incorporates:
     *  Constant: '<S225>/Constant3'
     */
    rtb_Switch2_d = -0.4;
  } else {
    rtb_Switch2_d = rtb_Product1_da;
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
  rtb_TmpSignalConversionAtCInp_1 = 0.005;

  /* Sum: '<S403>/Difference Inputs1' incorporates:
   *  Delay: '<S403>/Delay'
   *
   * Block description for '<S403>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Integrator_fe = rtb_Switch2_d - rtDW->Delay_DSTATE_h;

  /* Switch: '<S404>/Switch2' incorporates:
   *  RelationalOperator: '<S404>/LowerRelop1'
   */
  if (!(rtb_Integrator_fe > 0.005)) {
    /* Switch: '<S404>/Switch' incorporates:
     *  RelationalOperator: '<S404>/UpperRelop'
     */
    if (rtb_Integrator_fe < -0.005) {
      rtb_TmpSignalConversionAtCInp_1 = -0.005;
    } else {
      rtb_TmpSignalConversionAtCInp_1 = rtb_Integrator_fe;
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
  rtb_Integrator_i = rtb_TmpSignalConversionAtCInp_1 + rtDW->Delay_DSTATE_h;

  /* Sum: '<S8>/Sum1' incorporates:
   *  DiscreteTransferFcn: '<S424>/Gyro Filter'
   */
  rtb_TmpSignalConversionAtCInp_1 = rtb_Integrator_i - rtb_TSamp_b;

  /* DiscreteIntegrator: '<S192>/Integrator' */
  rtb_Integrator_fe = rtDW->Integrator_DSTATE_e;

  /* Product: '<S185>/DProd Out' */
  rtb_DProdOut_m = rtb_TmpSignalConversionAtCInp_1 * rtb_Filter_e;

  /* DiscreteIntegrator: '<S187>/Filter' */
  rtb_Filter_e = rtDW->Filter_DSTATE_g;

  /* Product: '<S195>/NProd Out' incorporates:
   *  Sum: '<S187>/SumD'
   */
  rtb_Filter_e = (rtb_DProdOut_m - rtb_Filter_e) * rtb_GainDynamicLookup_k;

  /* Sum: '<S201>/Sum' incorporates:
   *  Product: '<S197>/PProd Out'
   */
  rtb_GainDynamicLookup_k = (rtb_TmpSignalConversionAtCInp_1 * rtb_Product1_g +
    rtb_Integrator_fe) + rtb_Filter_e;

  /* Product: '<S152>/Product1' incorporates:
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_g = rtb_GainDynamicLookup_k * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S154>/Divide' incorporates:
   *  Constant: '<S154>/Constant'
   *  Gain: '<S154>/Gain'
   */
  rtb_Divide_l = -6756.0 * rtb_Product1_g / 50000.0;

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
  rtb_GainDynamicLookup_k = 1.8;

  /* Sum: '<S219>/Difference Inputs1' incorporates:
   *  Delay: '<S219>/Delay'
   *
   * Block description for '<S219>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Integrator_fe = rtb_Switch2_b - rtDW->Delay_DSTATE_e;

  /* Switch: '<S220>/Switch2' incorporates:
   *  RelationalOperator: '<S220>/LowerRelop1'
   */
  if (!(rtb_Integrator_fe > 1.8)) {
    /* Switch: '<S220>/Switch' incorporates:
     *  RelationalOperator: '<S220>/UpperRelop'
     */
    if (rtb_Integrator_fe < -1.8) {
      rtb_GainDynamicLookup_k = -1.8;
    } else {
      rtb_GainDynamicLookup_k = rtb_Integrator_fe;
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
  rtb_Integrator_fe = rtb_GainDynamicLookup_k + rtDW->Delay_DSTATE_e;

  /* UnaryMinus: '<S5>/Unary Minus2' */
  rtb_GainDynamicLookup_k = -rtb_Integrator_fe;

  /* UnaryMinus: '<S5>/Unary Minus' */
  rtb_GainDynamicLookup_b = -rtb_PProdOut_b;

  /* Sum: '<S5>/Sum' incorporates:
   *  Product: '<S5>/Product'
   */
  rtb_Sum1_idx_0 = rtb_PProdOut_b + rtb_Integrator_g;
  rtb_Sum1_idx_1 = rtb_GainDynamicLookup_k - rtb_Integrator_g;
  rtb_Sum1_idx_2 = rtb_GainDynamicLookup_b + rtb_Integrator_g;
  rtb_Sum1_idx_3 = rtb_Integrator_fe - rtb_Integrator_g;

  /* Outport: '<Root>/control_deg' */
  rtY_control_deg[0] = rtb_Sum1_idx_0;
  rtY_control_deg[1] = rtb_Sum1_idx_1;
  rtY_control_deg[2] = rtb_Sum1_idx_2;
  rtY_control_deg[3] = rtb_Sum1_idx_3;

  /* UnitDelay generated from: '<S406>/Unit Delay' */
  rtb_GainDynamicLookup_b = rtDW->UnitDelay_18_DSTATE;

  /* UnitDelay generated from: '<S406>/Unit Delay' */
  rtb_GainDynamicLookup_k = rtDW->UnitDelay_19_DSTATE;

  /* UnitDelay generated from: '<S406>/Unit Delay' */
  rtb_DProdOut_m = rtDW->UnitDelay_20_DSTATE;

  /* Gain: '<S407>/Gain4' */
  rtb_MatrixMultiply[0] *= 5.0E-5;
  rtb_MatrixMultiply[1] *= 5.0E-5;
  rtb_MatrixMultiply[2] *= 5.0E-5;

  /* Sum: '<S407>/Sum5' incorporates:
   *  Gain: '<S407>/Gain5'
   */
  rtb_Sum5_idx_0 = (0.01 * rtb_MathFunction_idx_0 + rtb_GainDynamicLookup_b) -
    rtb_MatrixMultiply[0];
  rtb_Sum5_idx_1 = (0.01 * rtb_MathFunction_idx_1 + rtb_GainDynamicLookup_k) -
    rtb_MatrixMultiply[1];
  rtb_Sum5_idx_2 = (0.01 * rtb_MathFunction_idx_2 + rtb_DProdOut_m) -
    rtb_MatrixMultiply[2];

  /* RelationalOperator: '<S426>/Compare' incorporates:
   *  Constant: '<S426>/Constant'
   */
  rtb_LogicalOperator1_j = (rtb_flightMode_enum == IDLE);

  /* DiscreteTransferFcn: '<S424>/Accel Filter' */
  rtb_TSamp_ge = rtb_accBdyEst_mps2[0] - 0.0 * rtDW->AccelFilter_states_l[0];

  /* Switch: '<S422>/Switch' */
  if (rtb_LogicalOperator1_j) {
    /* Switch: '<S422>/Switch' incorporates:
     *  Delay generated from: '<S422>/Delay'
     */
    Switch[0] = rtDW->Delay_4_DSTATE[0];
    Switch[1] = rtDW->Delay_4_DSTATE[1];
    Switch[2] = rtDW->Delay_4_DSTATE[2];
  } else {
    /* Switch: '<S422>/Switch' incorporates:
     *  UnitDelay: '<S422>/Unit Delay'
     */
    Switch[0] = rtDW->UnitDelay_DSTATE[0];
    Switch[1] = rtDW->UnitDelay_DSTATE[1];
    Switch[2] = rtDW->UnitDelay_DSTATE[2];
  }

  /* End of Switch: '<S422>/Switch' */

  /* DiscreteTransferFcn: '<S424>/Accel Filter' incorporates:
   *  Sum: '<S411>/Sum1'
   */
  rtb_TSamp_i = rtb_accBdyEst_mps2[1] - 0.0 * rtDW->AccelFilter_states_l[1];
  rtb_TSamp_h = rtb_MathFunction_m_tmp - 0.0 * rtDW->AccelFilter_states_l[2];
  for (i = 0; i < 3; i++) {
    /* DiscreteFir: '<S422>/Discrete FIR Filter' */
    uIdx = i * 99;
    rtb_TSamp = Switch[i] * 0.01;
    for (idxWidth = rtDW->DiscreteFIRFilter_circBuf; idxWidth < 99; idxWidth++)
    {
      rtb_TSamp += rtDW->DiscreteFIRFilter_states[uIdx + idxWidth] * 0.01;
    }

    for (idxWidth = 0; idxWidth < rtDW->DiscreteFIRFilter_circBuf; idxWidth++) {
      rtb_TSamp += rtDW->DiscreteFIRFilter_states[uIdx + idxWidth] * 0.01;
    }

    rtb_DiscreteFIRFilter[i] = rtb_TSamp;

    /* Sum: '<S422>/Sum1' incorporates:
     *  Constant: '<S422>/Constant'
     *  DiscreteFir: '<S422>/Discrete FIR Filter'
     *  Product: '<S422>/Product'
     */
    rtb_MatrixMultiply[i] = ((rtCP__Constant_Value_me[i + 3] * rtb_Product_k4[1]
      + rtCP__Constant_Value_me[i] * rtb_Product_k4[0]) +
      rtCP__Constant_Value_me[i + 6] * rtb_Product_k4[2]) + rtb_TSamp;
  }

  /* Switch: '<S422>/Switch1' */
  if (rtb_LogicalOperator1_j) {
    /* Switch: '<S422>/Switch1' incorporates:
     *  Constant: '<S427>/Constant'
     *  Delay generated from: '<S422>/Delay'
     *  Product: '<S427>/Matrix Multiply'
     *  Quat2Dcm: '<S427>/C-'
     *  Sum: '<S422>/Sum'
     */
    for (i = 0; i < 3; i++) {
      rtb_Product_k4[i] = ((rtb_C[i + 3] * 0.0 + rtb_C[i] * 0.0) + rtb_C[i + 6] *
                           9.81) + rtDW->Delay_3_DSTATE[i];
    }
  } else {
    /* Switch: '<S422>/Switch1' incorporates:
     *  UnitDelay: '<S422>/Unit Delay1'
     */
    rtb_Product_k4[0] = rtDW->UnitDelay1_DSTATE[0];
    rtb_Product_k4[1] = rtDW->UnitDelay1_DSTATE[1];
    rtb_Product_k4[2] = rtDW->UnitDelay1_DSTATE[2];
  }

  /* End of Switch: '<S422>/Switch1' */

  /* DiscreteFir: '<S422>/Discrete FIR Filter1' */
  rtb_TSamp = rtb_Product_k4[0] * 0.01;
  for (idxWidth = rtDW->DiscreteFIRFilter1_circBuf; idxWidth < 99; idxWidth++) {
    rtb_TSamp += rtDW->DiscreteFIRFilter1_states[idxWidth] * 0.01;
  }

  for (idxWidth = 0; idxWidth < rtDW->DiscreteFIRFilter1_circBuf; idxWidth++) {
    rtb_TSamp += rtDW->DiscreteFIRFilter1_states[idxWidth] * 0.01;
  }

  rtb_accelBias_mps2_idx_0 = rtb_TSamp;
  rtb_TSamp = rtb_Product_k4[1] * 0.01;
  for (idxWidth = rtDW->DiscreteFIRFilter1_circBuf; idxWidth < 99; idxWidth++) {
    rtb_TSamp += rtDW->DiscreteFIRFilter1_states[idxWidth + 99] * 0.01;
  }

  for (idxWidth = 0; idxWidth < rtDW->DiscreteFIRFilter1_circBuf; idxWidth++) {
    rtb_TSamp += rtDW->DiscreteFIRFilter1_states[idxWidth + 99] * 0.01;
  }

  rtb_accelBias_mps2_idx_1 = rtb_TSamp;
  rtb_TSamp = rtb_Product_k4[2] * 0.01;
  for (idxWidth = rtDW->DiscreteFIRFilter1_circBuf; idxWidth < 99; idxWidth++) {
    rtb_TSamp += rtDW->DiscreteFIRFilter1_states[idxWidth + 198] * 0.01;
  }

  for (idxWidth = 0; idxWidth < rtDW->DiscreteFIRFilter1_circBuf; idxWidth++) {
    rtb_TSamp += rtDW->DiscreteFIRFilter1_states[idxWidth + 198] * 0.01;
  }

  rtb_accelBias_mps2_idx_2 = rtb_TSamp;

  /* End of DiscreteFir: '<S422>/Discrete FIR Filter1' */

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
  LookUp_real_T_real_T( &(rtb_DProdOut_m), rtCP__Constant5_Value, rtb_Sin,
                       rtCP__Internalbreakpoints_Value, 2U);

  /* S-Function (sfix_look1_dyn): '<S145>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S10>/Constant5'
   *  Constant: '<S83>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S145>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_b), rtCP__Constant5_Value_m,
                       rtb_Sin, rtCP__Internalbreakpoints_Val_f, 2U);

  /* S-Function (sfix_look1_dyn): '<S215>/Gain Dynamic Lookup' incorporates:
   *  Constant: '<S11>/Constant5'
   *  Constant: '<S153>/Internal breakpoints'
   */
  /* Dynamic Look-Up Table Block: '<S215>/Gain Dynamic Lookup'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_k), rtCP__Constant5_Value_l,
                       rtb_Sin, rtCP__Internalbreakpoints_Val_d, 2U);

  /* SampleTimeMath: '<S218>/TSamp'
   *
   * About '<S218>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp = rtb_Switch2_b * 100.0;

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
  rtb_Switch2_b = rtb_TSamp - rtDW->UD_DSTATE;

  /* Logic: '<S155>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S11>/Constant1'
   *  RelationalOperator: '<S155>/Relational Operator'
   *  RelationalOperator: '<S155>/Relational Operator1'
   */
  rtb_LogicalOperator1_j = ((rtb_Switch2_b >= 180.0) || (rtb_Switch2_b <= -180.0));

  /* Logic: '<S156>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Constant: '<S11>/Constant3'
   *  RelationalOperator: '<S156>/Relational Operator'
   *  RelationalOperator: '<S156>/Relational Operator1'
   */
  rtb_LogicalOperator_i = ((rtb_Divide_l >= 45.0) || (rtb_Divide_l <= -45.0));

  /* Product: '<S189>/IProd Out' incorporates:
   *  Logic: '<S11>/Logical Operator'
   *  Product: '<S152>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_GainDynamicLookup_k = (real_T)(!rtb_LogicalOperator_i &&
    !rtb_LogicalOperator1_j) * rtb_GainDynamicLookup_k * (real_T)
    rtDW->UnitDelay_DSTATE_n * rtb_TmpSignalConversionAtCInp_1;

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.control_deg =
    rtb_Integrator_fe;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_g;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator1_j;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_i;

  /* SampleTimeMath: '<S78>/TSamp'
   *
   * About '<S78>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_g = rtb_Switch2_j * 100.0;

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
  rtb_Switch2_b = rtb_Product1_g - rtDW->UD_DSTATE_k;

  /* Logic: '<S15>/Logical Operator1' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  RelationalOperator: '<S15>/Relational Operator'
   *  RelationalOperator: '<S15>/Relational Operator1'
   */
  rtb_LogicalOperator1_b = ((rtb_Switch2_b >= 180.0) || (rtb_Switch2_b <= -180.0));

  /* Logic: '<S16>/Logical Operator1' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  RelationalOperator: '<S16>/Relational Operator'
   *  RelationalOperator: '<S16>/Relational Operator1'
   */
  rtb_LogicalOperator_i = ((rtb_Divide >= 45.0) || (rtb_Divide <= -45.0));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.control_deg =
    rtb_PProdOut_b;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_ad;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator1_b;
  rtY_controller_bus_f->innerLoop_bus.pitchInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_i;

  /* SampleTimeMath: '<S148>/TSamp'
   *
   * About '<S148>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_ad = rtb_Switch2_f * 100.0;

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
  rtb_Switch2_b = rtb_Product1_ad - rtDW->UD_DSTATE_n;

  /* Logic: '<S85>/Logical Operator1' incorporates:
   *  Constant: '<S10>/Constant'
   *  Constant: '<S10>/Constant1'
   *  RelationalOperator: '<S85>/Relational Operator'
   *  RelationalOperator: '<S85>/Relational Operator1'
   */
  rtb_LogicalOperator1_j = ((rtb_Switch2_b >= 90.0) || (rtb_Switch2_b <= -90.0));

  /* Logic: '<S86>/Logical Operator1' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant3'
   *  RelationalOperator: '<S86>/Relational Operator'
   *  RelationalOperator: '<S86>/Relational Operator1'
   */
  rtb_LogicalOperator = ((rtb_Gain_a >= 5.0) || (rtb_Gain_a <= -5.0));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.control_deg =
    rtb_Integrator_g;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_o;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator1_j;
  rtY_controller_bus_f->innerLoop_bus.rollInnerLoop_bus.saturated_b =
    rtb_LogicalOperator;

  /* SampleTimeMath: '<S282>/TSamp'
   *
   * About '<S282>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_o = rtb_Switch2_m * 100.0;

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
  rtb_Switch2_b = rtb_Product1_o - rtDW->UD_DSTATE_g;

  /* Logic: '<S227>/Logical Operator1' incorporates:
   *  Constant: '<S223>/Constant'
   *  Constant: '<S223>/Constant1'
   *  RelationalOperator: '<S227>/Relational Operator'
   *  RelationalOperator: '<S227>/Relational Operator1'
   */
  rtb_LogicalOperator1 = ((rtb_Switch2_b >= 0.5) || (rtb_Switch2_b <= -0.5));

  /* Logic: '<S228>/Logical Operator1' incorporates:
   *  Constant: '<S223>/Constant2'
   *  Constant: '<S223>/Constant3'
   *  RelationalOperator: '<S228>/Relational Operator'
   *  RelationalOperator: '<S228>/Relational Operator1'
   */
  rtb_LogicalOperator_ni = ((rtb_Product1_j3 >= 0.4) || (rtb_Product1_j3 <= -0.4));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.rateCmd_rps =
    rtb_UkYk1_l;
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1;
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_ni;

  /* SampleTimeMath: '<S402>/TSamp'
   *
   * About '<S402>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Gain_a = rtb_Switch2_d * 100.0;

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
  rtb_Switch2_b = rtb_Gain_a - rtDW->UD_DSTATE_p;

  /* Logic: '<S347>/Logical Operator1' incorporates:
   *  Constant: '<S225>/Constant'
   *  Constant: '<S225>/Constant1'
   *  RelationalOperator: '<S347>/Relational Operator'
   *  RelationalOperator: '<S347>/Relational Operator1'
   */
  rtb_LogicalOperator1_i = ((rtb_Switch2_b >= 0.5) || (rtb_Switch2_b <= -0.5));

  /* Logic: '<S348>/Logical Operator1' incorporates:
   *  Constant: '<S225>/Constant2'
   *  Constant: '<S225>/Constant3'
   *  RelationalOperator: '<S348>/Relational Operator'
   *  RelationalOperator: '<S348>/Relational Operator1'
   */
  rtb_LogicalOperator_a = ((rtb_Product1_da >= 0.4) || (rtb_Product1_da <= -0.4));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.rateCmd_rps =
    rtb_Integrator_i;
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1_i;
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_a;

  /* SampleTimeMath: '<S342>/TSamp'
   *
   * About '<S342>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_nd *= 100.0;

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
  rtb_Switch2_b = rtb_Product1_nd - rtDW->UD_DSTATE_a;

  /* Logic: '<S287>/Logical Operator1' incorporates:
   *  Constant: '<S224>/Constant'
   *  Constant: '<S224>/Constant1'
   *  RelationalOperator: '<S287>/Relational Operator'
   *  RelationalOperator: '<S287>/Relational Operator1'
   */
  rtb_LogicalOperator1_a2 = ((rtb_Switch2_b >= 5.0) || (rtb_Switch2_b <= -5.0));

  /* Logic: '<S288>/Logical Operator1' incorporates:
   *  Constant: '<S224>/Constant2'
   *  Constant: '<S224>/Constant3'
   *  RelationalOperator: '<S288>/Relational Operator'
   *  RelationalOperator: '<S288>/Relational Operator1'
   */
  rtb_LogicalOperator_j = ((rtb_Product3_i >= 2.0) || (rtb_Product3_i <= -2.0));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.rateCmd_rps =
    rtb_Integrator_b;
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1_a2;
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_j;

  /* BusCreator generated from: '<Root>/controller_bus' incorporates:
   *  Outport: '<Root>/controller_bus'
   */
  rtY_controller_bus_f->control_deg[0] = rtb_Sum1_idx_0;
  rtY_controller_bus_f->control_deg[1] = rtb_Sum1_idx_1;
  rtY_controller_bus_f->control_deg[2] = rtb_Sum1_idx_2;
  rtY_controller_bus_f->control_deg[3] = rtb_Sum1_idx_3;

  /* Product: '<S321>/IProd Out' incorporates:
   *  Constant: '<S224>/Constant4'
   *  Constant: '<S2>/Constant'
   *  Logic: '<S224>/Logical Operator'
   *  Product: '<S286>/Product'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S222>/Sum2'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_TmpSignalConversionAtCInp_1 = (real_T)(!rtb_LogicalOperator_j &&
    !rtb_LogicalOperator1_a2) * 2.0 * (real_T)rtDW->UnitDelay_DSTATE_n * (0.0 -
    rtb_TmpSignalConversionAtCInp_3);

  /* Product: '<S381>/IProd Out' incorporates:
   *  Constant: '<S225>/Constant4'
   *  Logic: '<S225>/Logical Operator'
   *  Product: '<S346>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product3_i = (real_T)(!rtb_LogicalOperator_a && !rtb_LogicalOperator1_i) *
    0.4 * (real_T)rtDW->UnitDelay_DSTATE_n * rtb_Sum3;

  /* Product: '<S261>/IProd Out' incorporates:
   *  Constant: '<S223>/Constant4'
   *  Logic: '<S223>/Logical Operator'
   *  Product: '<S226>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Sum4_a *= (real_T)(!rtb_LogicalOperator_ni && !rtb_LogicalOperator1) * 0.4
    * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S119>/IProd Out' incorporates:
   *  Logic: '<S10>/Logical Operator'
   *  Product: '<S82>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_TmpSignalConversionAtCInp_2 *= (real_T)(!rtb_LogicalOperator &&
    !rtb_LogicalOperator1_j) * rtb_GainDynamicLookup_b * (real_T)
    rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S12>/Product' incorporates:
   *  Logic: '<S9>/Logical Operator'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Switch2_b = (real_T)(!rtb_LogicalOperator_i && !rtb_LogicalOperator1_b) *
    rtb_DProdOut_m * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* State Transition Table: '<S409>/State Transition Table' incorporates:
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   *  Sum: '<S411>/Sum1'
   *  UnaryMinus: '<S409>/Unary Minus'
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
        rtDW->lockoutThreshold_b = ((fabs(rtb_wBdyEst_rps[1]) > 1.0) || ((fabs
          (rtb_wBdyEst_rps[2]) > 1.0) || ((fabs(rtb_QuaternionstoDirectionCos_0)
          > 1.0) || (fabs(rtb_TmpSignalConversionAtCInp_4) > 1.0))));
      }
      break;

     case autocodeModel_IN_Boost:
      rtDW->flightMode_enum = BOOST;
      if (rtDW->coastThreshold_b) {
        rtDW->temporalCounter_i1 = 0U;
        rtDW->is_c4_autocodeModel = autocodeM_IN_PastCoastThreshold;
      } else {
        rtDW->coastThreshold_b = ((-rtb_Sum5_idx_2 > 200.0) &&
          (rtb_accBdyEst_mps2[0] < 0.0));
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

        rtb_Product1_j3 = fabs(rtb_MathFunction_m_tmp);
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

        rtDW->boostThreshold_b = (rtb_Sum3 > 12.0);
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
        rtDW->coastThreshold_b = ((-rtb_Sum5_idx_2 > 200.0) &&
          (rtb_accBdyEst_mps2[0] < 0.0));
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
        rtDW->lockoutThreshold_b = ((fabs(rtb_wBdyEst_rps[1]) > 1.0) || ((fabs
          (rtb_wBdyEst_rps[2]) > 1.0) || ((fabs(rtb_QuaternionstoDirectionCos_0)
          > 1.0) || (fabs(rtb_TmpSignalConversionAtCInp_4) > 1.0))));
      }
      break;
    }
  }

  /* End of State Transition Table: '<S409>/State Transition Table' */

  /* BusCreator generated from: '<Root>/navigation_bus' incorporates:
   *  DiscreteTransferFcn: '<S424>/Accel Filter'
   *  DiscreteTransferFcn: '<S424>/Gyro Filter'
   *  Outport: '<Root>/navigation_bus'
   *  Quat2Angle: '<S425>/Quaternions to Rotation Angles'
   */
  rtY_navigation_bus_d->flightMode_enum = rtDW->flightMode_enum;
  rtY_navigation_bus_d->qEst_na[0] = rtDW->qEst_na[0];
  rtY_navigation_bus_d->qEst_na[1] = rtDW->qEst_na[1];
  rtY_navigation_bus_d->qEst_na[2] = rtDW->qEst_na[2];
  rtY_navigation_bus_d->qEst_na[3] = rtDW->qEst_na[3];
  rtY_navigation_bus_d->phiEst_rad = rtb_TmpSignalConversionAtCInp_3;
  rtY_navigation_bus_d->thetaEst_rad = rtb_QuaternionstoDirectionCos_0;
  rtY_navigation_bus_d->psiEst_rad = rtb_TmpSignalConversionAtCInp_4;
  rtY_navigation_bus_d->pEst_rps = rtb_TSamp_a;
  rtY_navigation_bus_d->qEst_rps = rtb_TSamp_b0;
  rtY_navigation_bus_d->rEst_rps = rtb_TSamp_b;
  rtY_navigation_bus_d->xAccEst_mps2 = 0.5 * rtb_TSamp_ge + 0.5 *
    rtDW->AccelFilter_states_l[0];
  rtY_navigation_bus_d->yAccEst_mps2 = 0.5 * rtb_TSamp_i + 0.5 *
    rtDW->AccelFilter_states_l[1];
  rtY_navigation_bus_d->zAccEst_mps2 = 0.5 * rtb_TSamp_h + 0.5 *
    rtDW->AccelFilter_states_l[2];
  rtY_navigation_bus_d->accelBias_mps2[0] = rtb_accelBias_mps2_idx_0;
  rtY_navigation_bus_d->gyroBias_rps[0] = rtb_MatrixMultiply[0];
  rtY_navigation_bus_d->accelBias_mps2[1] = rtb_accelBias_mps2_idx_1;
  rtY_navigation_bus_d->gyroBias_rps[1] = rtb_MatrixMultiply[1];
  rtY_navigation_bus_d->accelBias_mps2[2] = rtb_accelBias_mps2_idx_2;
  rtY_navigation_bus_d->gyroBias_rps[2] = rtb_MatrixMultiply[2];
  rtY_navigation_bus_d->dynPressureEst_Pa = rtb_Sin;
  rtY_navigation_bus_d->xVelEst_mps = rtb_MathFunction_idx_0;
  rtY_navigation_bus_d->yVelEst_mps = rtb_MathFunction_idx_1;
  rtY_navigation_bus_d->zVelEst_mps = rtb_MathFunction_idx_2;
  rtY_navigation_bus_d->xPosEst_m = rtb_Sum5_idx_0;
  rtY_navigation_bus_d->yPosEst_m = rtb_Sum5_idx_1;
  rtY_navigation_bus_d->zPosEst_m = rtb_Sum5_idx_2;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[0] = rtDW->qEst_na[0];
  rtDW->UnitDelay_2_DSTATE[1] = rtDW->qEst_na[1];
  rtDW->UnitDelay_2_DSTATE[2] = rtDW->qEst_na[2];
  rtDW->UnitDelay_2_DSTATE[3] = rtDW->qEst_na[3];

  /* Update for UnitDelay: '<S4>/Unit Delay' incorporates:
   *  Constant: '<S4>/Constant2'
   *  RelationalOperator: '<S4>/Equal'
   */
  rtDW->UnitDelay_DSTATE_n = (rtDW->flightMode_enum == ACTIVE);

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_1_DSTATE = rtDW->flightMode_enum;

  /* Update for DiscreteIntegrator: '<S324>/Integrator' */
  rtDW->Integrator_DSTATE += 0.01 * rtb_TmpSignalConversionAtCInp_1;

  /* Update for DiscreteIntegrator: '<S319>/Filter' */
  rtDW->Filter_DSTATE += 0.01 * rtb_TmpSignalConversionAtCInp_0;

  /* Update for Delay: '<S343>/Delay' */
  rtDW->icLoad = false;
  rtDW->Delay_DSTATE = rtb_Integrator_b;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_15_DSTATE = rtb_MathFunction_idx_0;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_16_DSTATE = rtb_MathFunction_idx_1;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_17_DSTATE = rtb_MathFunction_idx_2;

  /* Update for DiscreteIntegrator: '<S122>/Integrator' */
  rtDW->Integrator_DSTATE_b += 0.01 * rtb_TmpSignalConversionAtCInp_2;

  /* Update for DiscreteIntegrator: '<S117>/Filter' */
  rtDW->Filter_DSTATE_p += 0.01 * rtb_Filter_c;

  /* Update for Delay: '<S149>/Delay' */
  rtDW->icLoad_k = false;
  rtDW->Delay_DSTATE_p = rtb_Integrator_g;

  /* Update for DiscreteIntegrator: '<S264>/Integrator' */
  rtDW->Integrator_DSTATE_g += 0.01 * rtb_Sum4_a;

  /* Update for DiscreteIntegrator: '<S259>/Filter' */
  rtDW->Filter_DSTATE_n += 0.01 * rtb_Product2_a;

  /* Update for Delay: '<S283>/Delay' */
  rtDW->icLoad_a = false;
  rtDW->Delay_DSTATE_c = rtb_UkYk1_l;

  /* Update for DiscreteIntegrator: '<S52>/Integrator' incorporates:
   *  Product: '<S49>/IProd Out'
   */
  rtDW->Integrator_DSTATE_p += rtb_sqrt * rtb_Switch2_b * 0.01;

  /* Update for DiscreteIntegrator: '<S47>/Filter' */
  rtDW->Filter_DSTATE_l += 0.01 * rtb_Filter_g;

  /* Update for Delay: '<S79>/Delay' */
  rtDW->icLoad_f = false;
  rtDW->Delay_DSTATE_f = rtb_PProdOut_b;

  /* Update for DiscreteIntegrator: '<S384>/Integrator' */
  rtDW->Integrator_DSTATE_l += 0.01 * rtb_Product3_i;

  /* Update for DiscreteIntegrator: '<S379>/Filter' */
  rtDW->Filter_DSTATE_c += 0.01 * rtb_Filter_b;

  /* Update for Delay: '<S403>/Delay' */
  rtDW->icLoad_c = false;
  rtDW->Delay_DSTATE_h = rtb_Integrator_i;

  /* Update for DiscreteIntegrator: '<S192>/Integrator' */
  rtDW->Integrator_DSTATE_e += 0.01 * rtb_GainDynamicLookup_k;

  /* Update for DiscreteIntegrator: '<S187>/Filter' */
  rtDW->Filter_DSTATE_g += 0.01 * rtb_Filter_e;

  /* Update for Delay: '<S219>/Delay' */
  rtDW->icLoad_d = false;
  rtDW->Delay_DSTATE_e = rtb_Integrator_fe;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_18_DSTATE = rtb_Sum5_idx_0;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_19_DSTATE = rtb_Sum5_idx_1;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_20_DSTATE = rtb_Sum5_idx_2;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[0] = rtb_MatrixMultiply[0];

  /* Update for DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[1] = rtDW->DiscreteTransferFcn1_states[0];
  rtDW->DiscreteTransferFcn1_states[0] = DiscreteTransferFcn1_tmp[0];

  /* Update for DiscreteTransferFcn: '<S424>/Gyro Filter' */
  rtDW->GyroFilter_states[0] = rtb_TSamp_c5;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_12_DSTATE[0] = rtb_accelBias_mps2_idx_0;

  /* Update for DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtDW->AccelFilter_states[0] = rtb_TSamp_gj;

  /* Update for DiscreteTransferFcn: '<S424>/Accel Filter' */
  rtDW->AccelFilter_states_l[0] = rtb_TSamp_ge;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[1] = rtb_MatrixMultiply[1];

  /* Update for DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[3] = rtDW->DiscreteTransferFcn1_states[2];
  rtDW->DiscreteTransferFcn1_states[2] = DiscreteTransferFcn1_tmp[1];

  /* Update for DiscreteTransferFcn: '<S424>/Gyro Filter' */
  rtDW->GyroFilter_states[1] = rtb_TSamp_d;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_12_DSTATE[1] = rtb_accelBias_mps2_idx_1;

  /* Update for DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtDW->AccelFilter_states[1] = rtb_TSamp_jt;

  /* Update for DiscreteTransferFcn: '<S424>/Accel Filter' */
  rtDW->AccelFilter_states_l[1] = rtb_TSamp_i;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[2] = rtb_MatrixMultiply[2];

  /* Update for DiscreteTransferFcn: '<S407>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[5] = rtDW->DiscreteTransferFcn1_states[4];
  rtDW->DiscreteTransferFcn1_states[4] = DiscreteTransferFcn1_tmp[2];

  /* Update for DiscreteTransferFcn: '<S424>/Gyro Filter' */
  rtDW->GyroFilter_states[2] = rtb_TSamp_fe;

  /* Update for UnitDelay generated from: '<S406>/Unit Delay' */
  rtDW->UnitDelay_12_DSTATE[2] = rtb_accelBias_mps2_idx_2;

  /* Update for DiscreteTransferFcn: '<S407>/Accel Filter' */
  rtDW->AccelFilter_states[2] = rtb_TSamp_k;

  /* Update for DiscreteTransferFcn: '<S424>/Accel Filter' */
  rtDW->AccelFilter_states_l[2] = rtb_TSamp_h;

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  for (i = 0; i < 499; i++) {
    uIdx = (i + 1) * 3;
    rtDW->Delay_4_DSTATE[i * 3] = rtDW->Delay_4_DSTATE[uIdx];
    rtDW->Delay_4_DSTATE[i * 3 + 1] = rtDW->Delay_4_DSTATE[uIdx + 1];
    rtDW->Delay_4_DSTATE[i * 3 + 2] = rtDW->Delay_4_DSTATE[uIdx + 2];
  }

  rtDW->Delay_4_DSTATE[1497] = rtU_sensor_bus_e->wBdyMeas_rps[0];

  /* Update for UnitDelay: '<S422>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[0] = rtb_DiscreteFIRFilter[0];

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_4_DSTATE[1498] = rtU_sensor_bus_e->wBdyMeas_rps[1];

  /* Update for UnitDelay: '<S422>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[1] = rtb_DiscreteFIRFilter[1];

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_4_DSTATE[1499] = rtU_sensor_bus_e->wBdyMeas_rps[2];

  /* Update for UnitDelay: '<S422>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[2] = rtb_DiscreteFIRFilter[2];

  /* Update for DiscreteFir: '<S422>/Discrete FIR Filter' */
  /* Update circular buffer index */
  rtDW->DiscreteFIRFilter_circBuf--;
  if (rtDW->DiscreteFIRFilter_circBuf < 0) {
    rtDW->DiscreteFIRFilter_circBuf = 98;
  }

  /* Update circular buffer */
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf] = Switch[0];
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf + 99] = Switch
    [1];
  rtDW->DiscreteFIRFilter_states[rtDW->DiscreteFIRFilter_circBuf + 198] =
    Switch[2];

  /* End of Update for DiscreteFir: '<S422>/Discrete FIR Filter' */

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  for (i = 0; i < 499; i++) {
    uIdx = (i + 1) * 3;
    rtDW->Delay_3_DSTATE[i * 3] = rtDW->Delay_3_DSTATE[uIdx];
    rtDW->Delay_3_DSTATE[i * 3 + 1] = rtDW->Delay_3_DSTATE[uIdx + 1];
    rtDW->Delay_3_DSTATE[i * 3 + 2] = rtDW->Delay_3_DSTATE[uIdx + 2];
  }

  rtDW->Delay_3_DSTATE[1497] = rtU_sensor_bus_e->fBdyMeas_mps2[0];

  /* Update for UnitDelay: '<S422>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[0] = rtb_accelBias_mps2_idx_0;

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_3_DSTATE[1498] = rtU_sensor_bus_e->fBdyMeas_mps2[1];

  /* Update for UnitDelay: '<S422>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[1] = rtb_accelBias_mps2_idx_1;

  /* Update for Delay generated from: '<S422>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_3_DSTATE[1499] = rtU_sensor_bus_e->fBdyMeas_mps2[2];

  /* Update for UnitDelay: '<S422>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[2] = rtb_accelBias_mps2_idx_2;

  /* Update for DiscreteFir: '<S422>/Discrete FIR Filter1' */
  /* Update circular buffer index */
  rtDW->DiscreteFIRFilter1_circBuf--;
  if (rtDW->DiscreteFIRFilter1_circBuf < 0) {
    rtDW->DiscreteFIRFilter1_circBuf = 98;
  }

  /* Update circular buffer */
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf] =
    rtb_Product_k4[0];
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf + 99] =
    rtb_Product_k4[1];
  rtDW->DiscreteFIRFilter1_states[rtDW->DiscreteFIRFilter1_circBuf + 198] =
    rtb_Product_k4[2];

  /* End of Update for DiscreteFir: '<S422>/Discrete FIR Filter1' */

  /* Update for UnitDelay: '<S218>/UD'
   *
   * Block description for '<S218>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE = rtb_TSamp;

  /* Update for UnitDelay: '<S78>/UD'
   *
   * Block description for '<S78>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_k = rtb_Product1_g;

  /* Update for UnitDelay: '<S148>/UD'
   *
   * Block description for '<S148>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_n = rtb_Product1_ad;

  /* Update for UnitDelay: '<S282>/UD'
   *
   * Block description for '<S282>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_g = rtb_Product1_o;

  /* Update for UnitDelay: '<S402>/UD'
   *
   * Block description for '<S402>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_p = rtb_Gain_a;

  /* Update for UnitDelay: '<S342>/UD'
   *
   * Block description for '<S342>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_a = rtb_Product1_nd;
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

  /* InitializeConditions for DiscreteFir: '<S422>/Discrete FIR Filter' */
  rtDW->DiscreteFIRFilter_circBuf = 0;

  /* InitializeConditions for DiscreteFir: '<S422>/Discrete FIR Filter1' */
  rtDW->DiscreteFIRFilter1_circBuf = 0;

  /* InitializeConditions for DiscreteFir: '<S422>/Discrete FIR Filter' */
  memset(&rtDW->DiscreteFIRFilter_states[0], 0, 297U * sizeof(real_T));

  /* InitializeConditions for DiscreteFir: '<S422>/Discrete FIR Filter1' */
  memset(&rtDW->DiscreteFIRFilter1_states[0], 0, 297U * sizeof(real_T));

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
