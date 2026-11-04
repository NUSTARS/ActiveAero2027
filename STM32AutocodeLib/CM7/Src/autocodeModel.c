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
 * C/C++ source code generated on : Thu Oct 29 16:34:18 2026
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

/* Named constants for State Transition Table: '<S411>/State Transition Table' */
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
                                                                  * Referenced by: '<S84>/Internal breakpoints'
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
                                                                  * Referenced by: '<S154>/Internal breakpoints'
                                                                  */
#define rtCP__Constant_Value_me        rtCP_pooled_JIXvzcabvSoM  /* Expression: navControl.gyroG
                                                                  * Referenced by: '<S426>/Constant'
                                                                  */
#define rtCP__Constant_Value_bn        rtCP_pooled_Qcj6ValmO9nO  /* Expression: navControl.gravityNed_mps2
                                                                  * Referenced by: '<S456>/Constant'
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
  real_T rtb_DProdOut;
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
  real_T rtb_Product1_g;
  real_T rtb_Product1_j3;
  real_T rtb_Product1_nd;
  real_T rtb_Product1_o;
  real_T rtb_Product2_a;
  real_T rtb_Product_l;
  real_T rtb_QuaternionstoDirectionCos_0;
  real_T rtb_Sin;
  real_T rtb_Sum1;
  real_T rtb_Sum3;
  real_T rtb_Sum4_a;
  real_T rtb_Sum5_idx_0;
  real_T rtb_Sum5_idx_1;
  real_T rtb_Sum5_idx_2;
  real_T rtb_Sum_mo;
  real_T rtb_Switch2_b;
  real_T rtb_Switch2_d;
  real_T rtb_Switch2_f;
  real_T rtb_Switch2_j;
  real_T rtb_Switch2_m;
  real_T rtb_Switch_oo_idx_0;
  real_T rtb_Switch_oo_idx_1;
  real_T rtb_Switch_oo_idx_2;
  real_T rtb_Switch_oo_idx_3;
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

  /* Quat2Dcm: '<S409>/C-' incorporates:
   *  Quat2Dcm: '<S456>/Quaternions to  Direction Cosine Matrix'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product_l = 1.0 / sqrt(((rtDW->UnitDelay_2_DSTATE[0] *
    rtDW->UnitDelay_2_DSTATE[0] + rtDW->UnitDelay_2_DSTATE[1] *
    rtDW->UnitDelay_2_DSTATE[1]) + rtDW->UnitDelay_2_DSTATE[2] *
    rtDW->UnitDelay_2_DSTATE[2]) + rtDW->UnitDelay_2_DSTATE[3] *
    rtDW->UnitDelay_2_DSTATE[3]);
  rtb_Switch_oo_idx_1 = rtb_Product_l * rtDW->UnitDelay_2_DSTATE[1];
  rtb_Switch_oo_idx_2 = rtb_Product_l * rtDW->UnitDelay_2_DSTATE[2];
  rtb_Switch_oo_idx_3 = rtb_Product_l * rtDW->UnitDelay_2_DSTATE[3];
  rtb_TmpSignalConversionAtCInp_2 = rtb_Product_l * rtDW->UnitDelay_2_DSTATE[0];
  rtb_TSamp_c5 = rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_2;
  rtb_TSamp_a = rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_1;
  rtb_Integrator_b = rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_2;
  rtb_Sin = rtb_Switch_oo_idx_3 * rtb_Switch_oo_idx_3;
  rtb_TSamp_d = ((rtb_TSamp_c5 + rtb_TSamp_a) - rtb_Integrator_b) - rtb_Sin;
  rtb_QuaternionstoDirectionCosin[0] = rtb_TSamp_d;
  rtb_TSamp_b0 = rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_2;
  rtb_TSamp_fe = rtb_TmpSignalConversionAtCInp_2 * rtb_Switch_oo_idx_3;
  rtb_TSamp_b = (rtb_TSamp_b0 + rtb_TSamp_fe) * 2.0;
  rtb_QuaternionstoDirectionCosin[3] = rtb_TSamp_b;
  rtb_Product_l = rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_3;
  rtb_Product1_ad = rtb_TmpSignalConversionAtCInp_2 * rtb_Switch_oo_idx_2;
  rtb_Product2_a = (rtb_Product_l - rtb_Product1_ad) * 2.0;
  rtb_QuaternionstoDirectionCosin[6] = rtb_Product2_a;
  rtb_TSamp_b0 = (rtb_TSamp_b0 - rtb_TSamp_fe) * 2.0;
  rtb_QuaternionstoDirectionCosin[1] = rtb_TSamp_b0;
  rtb_TSamp_c5 -= rtb_TSamp_a;
  rtb_TSamp_a = (rtb_TSamp_c5 + rtb_Integrator_b) - rtb_Sin;
  rtb_QuaternionstoDirectionCosin[4] = rtb_TSamp_a;
  rtb_TSamp_fe = rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_3;
  rtb_Sum_mo = rtb_TmpSignalConversionAtCInp_2 * rtb_Switch_oo_idx_1;
  rtb_QuaternionstoDirectionCos_0 = (rtb_TSamp_fe + rtb_Sum_mo) * 2.0;
  rtb_QuaternionstoDirectionCosin[7] = rtb_QuaternionstoDirectionCos_0;
  rtb_Product_l = (rtb_Product_l + rtb_Product1_ad) * 2.0;
  rtb_QuaternionstoDirectionCosin[2] = rtb_Product_l;
  rtb_TSamp_fe = (rtb_TSamp_fe - rtb_Sum_mo) * 2.0;
  rtb_QuaternionstoDirectionCosin[5] = rtb_TSamp_fe;
  rtb_TSamp_c5 = (rtb_TSamp_c5 - rtb_Integrator_b) + rtb_Sin;
  rtb_QuaternionstoDirectionCosin[8] = rtb_TSamp_c5;

  /* DotProduct: '<S409>/Dot Product' */
  rtb_Product1_ad = 0.0;
  for (i = 0; i < 3; i++) {
    /* Sum: '<S413>/Sum' incorporates:
     *  Inport: '<Root>/sensor_bus'
     *  UnitDelay generated from: '<S408>/Unit Delay'
     */
    rtb_Sum_mo = rtU_sensor_bus_e->wBdyMeas_rps[i] - rtDW->UnitDelay_13_DSTATE[i];
    rtb_wBdyEst_rps[i] = rtb_Sum_mo;

    /* DiscreteTransferFcn: '<S409>/Discrete Transfer Fcn1' */
    uIdx = i << 1;
    rtb_Integrator_b = rtDW->DiscreteTransferFcn1_states[uIdx];
    rtb_Sin = rtDW->DiscreteTransferFcn1_states[uIdx + 1];
    rtb_TSamp = (rtb_Sum_mo - -0.7478 * rtb_Integrator_b) - rtb_Sin * 0.2722;
    DiscreteTransferFcn1_tmp[i] = rtb_TSamp;

    /* Gain: '<S409>/Gain1' incorporates:
     *  DiscreteTransferFcn: '<S409>/Discrete Transfer Fcn1'
     */
    rtb_Switch_oo_idx_1 = ((0.1311 * rtb_TSamp + 0.2622 * rtb_Integrator_b) +
      rtb_Sin * 0.1311) * 0.01;
    rtb_Product_k4[i] = rtb_Switch_oo_idx_1;

    /* DotProduct: '<S409>/Dot Product' */
    rtb_Product1_ad += rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_1;
  }

  /* Sqrt: '<S409>/Sqrt' */
  rtb_Product1_ad = sqrt(rtb_Product1_ad);

  /* Gain: '<S409>/Gain2' */
  rtb_Integrator_b = 0.5 * rtb_Product1_ad;

  /* Trigonometry: '<S409>/Cos' */
  rtb_TmpSignalConversionAtCInp_0 = cos(rtb_Integrator_b);

  /* Trigonometry: '<S409>/Sin' */
  rtb_Sin = sin(rtb_Integrator_b);

  /* Switch: '<S414>/Switch' incorporates:
   *  Constant: '<S414>/Constant4'
   *  Constant: '<S414>/Constant5'
   */
  if (rtb_Product1_ad >= 0.0) {
    rtb_Integrator_b = 1.0;
  } else {
    rtb_Integrator_b = -1.0;
  }

  /* End of Switch: '<S414>/Switch' */

  /* Product: '<S414>/Product' incorporates:
   *  Constant: '<S414>/Constant'
   *  MinMax: '<S414>/Max'
   */
  rtb_Integrator_b *= fmax(1.0E-6, rtb_Product1_ad);

  /* Product: '<S409>/Divide' */
  rtb_TmpSignalConversionAtCInp_1 = rtb_Sin * rtb_Product_k4[0] /
    rtb_Integrator_b;
  rtb_TmpSignalConversionAtCInp_2 = rtb_Sin * rtb_Product_k4[1] /
    rtb_Integrator_b;
  rtb_Switch_oo_idx_1 = rtb_Sin * rtb_Product_k4[2] / rtb_Integrator_b;

  /* Product: '<S419>/Product1' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = rtDW->UnitDelay_2_DSTATE[1] *
    rtb_TmpSignalConversionAtCInp_1;

  /* Sum: '<S419>/Sum' incorporates:
   *  Product: '<S419>/Product'
   *  Product: '<S419>/Product2'
   *  Product: '<S419>/Product3'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Sin = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_TmpSignalConversionAtCInp_0 -
              rtb_Product1_ad) - rtDW->UnitDelay_2_DSTATE[2] *
             rtb_TmpSignalConversionAtCInp_2) - rtDW->UnitDelay_2_DSTATE[3] *
    rtb_Switch_oo_idx_1;

  /* Product: '<S420>/Product3' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = rtb_TmpSignalConversionAtCInp_2 * rtDW->UnitDelay_2_DSTATE[3];

  /* Sum: '<S420>/Sum' incorporates:
   *  Product: '<S420>/Product'
   *  Product: '<S420>/Product1'
   *  Product: '<S420>/Product2'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Integrator_b = ((rtDW->UnitDelay_2_DSTATE[0] *
                       rtb_TmpSignalConversionAtCInp_1 +
                       rtb_TmpSignalConversionAtCInp_0 *
                       rtDW->UnitDelay_2_DSTATE[1]) + rtDW->UnitDelay_2_DSTATE[2]
                      * rtb_Switch_oo_idx_1) - rtb_Product1_ad;

  /* Product: '<S421>/Product3' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = rtb_TmpSignalConversionAtCInp_1 * rtDW->UnitDelay_2_DSTATE[3];

  /* Sum: '<S421>/Sum' incorporates:
   *  Product: '<S421>/Product'
   *  Product: '<S421>/Product1'
   *  Product: '<S421>/Product2'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Sum_mo = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_TmpSignalConversionAtCInp_2 -
                 rtDW->UnitDelay_2_DSTATE[1] * rtb_Switch_oo_idx_1) +
                rtb_TmpSignalConversionAtCInp_0 * rtDW->UnitDelay_2_DSTATE[2]) +
    rtb_Product1_ad;

  /* Product: '<S422>/Product3' incorporates:
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_Product1_ad = rtb_TmpSignalConversionAtCInp_0 * rtDW->UnitDelay_2_DSTATE[3];

  /* Product: '<S422>/Product1' */
  rtb_Switch_oo_idx_3 = rtb_TmpSignalConversionAtCInp_2;

  /* Product: '<S422>/Product2' */
  rtb_Switch_oo_idx_2 = rtb_TmpSignalConversionAtCInp_1;

  /* SignalConversion generated from: '<S417>/Dot Product' incorporates:
   *  Product: '<S422>/Product'
   *  Product: '<S422>/Product1'
   *  Product: '<S422>/Product2'
   *  Sum: '<S422>/Sum'
   *  UnitDelay generated from: '<S408>/Unit Delay'
   */
  rtb_TmpSignalConversionAtCInp_0 = rtb_Sin;
  rtb_TmpSignalConversionAtCInp_1 = rtb_Integrator_b;
  rtb_TmpSignalConversionAtCInp_2 = rtb_Sum_mo;
  rtb_Switch_oo_idx_1 = ((rtDW->UnitDelay_2_DSTATE[0] * rtb_Switch_oo_idx_1 +
    rtDW->UnitDelay_2_DSTATE[1] * rtb_Switch_oo_idx_3) - rtb_Switch_oo_idx_2 *
    rtDW->UnitDelay_2_DSTATE[2]) + rtb_Product1_ad;

  /* Switch: '<S417>/Switch' incorporates:
   *  Constant: '<S417>/Constant'
   *  DotProduct: '<S417>/Dot Product'
   *  SignalConversion generated from: '<S417>/Dot Product'
   */
  if (!(((rtb_Sin * rtb_Sin + rtb_Integrator_b * rtb_Integrator_b) + rtb_Sum_mo *
         rtb_Sum_mo) + rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_1 > 1.0E-6)) {
    rtb_TmpSignalConversionAtCInp_0 = 1.0;
    rtb_TmpSignalConversionAtCInp_1 = 0.0;
    rtb_TmpSignalConversionAtCInp_2 = 0.0;
    rtb_Switch_oo_idx_1 = 0.0;
  }

  /* End of Switch: '<S417>/Switch' */

  /* Product: '<S424>/Product3' */
  rtb_Product1_ad = rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_1;

  /* Sqrt: '<S423>/sqrt' incorporates:
   *  Product: '<S424>/Product'
   *  Product: '<S424>/Product1'
   *  Product: '<S424>/Product2'
   *  Sum: '<S424>/Sum'
   */
  rtb_Sum_mo = sqrt(((rtb_TmpSignalConversionAtCInp_0 *
                      rtb_TmpSignalConversionAtCInp_0 +
                      rtb_TmpSignalConversionAtCInp_1 *
                      rtb_TmpSignalConversionAtCInp_1) +
                     rtb_TmpSignalConversionAtCInp_2 *
                     rtb_TmpSignalConversionAtCInp_2) + rtb_Product1_ad);

  /* Product: '<S416>/Product3' */
  rtb_Sin = rtb_Switch_oo_idx_1 / rtb_Sum_mo;

  /* Product: '<S416>/Product2' */
  rtb_Integrator_b = rtb_TmpSignalConversionAtCInp_2 / rtb_Sum_mo;

  /* Product: '<S416>/Product1' */
  rtb_Product1_ad = rtb_TmpSignalConversionAtCInp_1 / rtb_Sum_mo;

  /* Product: '<S416>/Product' */
  rtb_Sum_mo = rtb_TmpSignalConversionAtCInp_0 / rtb_Sum_mo;

  /* Quat2Dcm: '<S409>/C+' incorporates:
   *  Math: '<S418>/Math Function'
   *  Quat2Dcm: '<S431>/C-'
   *  SignalConversion generated from: '<S409>/C+'
   */
  rtb_TSamp = 1.0 / sqrt(((rtb_Sum_mo * rtb_Sum_mo + rtb_Product1_ad *
    rtb_Product1_ad) + rtb_Integrator_b * rtb_Integrator_b) + rtb_Sin * rtb_Sin);
  rtb_Switch_oo_idx_2 = rtb_TSamp * rtb_Product1_ad;
  rtb_Switch_oo_idx_1 = rtb_TSamp * rtb_Integrator_b;
  rtb_TmpSignalConversionAtCInp_0 = rtb_TSamp * rtb_Sin;
  rtb_TmpSignalConversionAtCInp_2 = rtb_TSamp * rtb_Sum_mo;
  rtb_TmpSignalConversionAtCInp_1 = rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_2;
  rtb_Switch_oo_idx_3 = rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_2;
  rtb_TSamp = rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_1;
  rtb_Switch_oo_idx_0 = rtb_TmpSignalConversionAtCInp_0 *
    rtb_TmpSignalConversionAtCInp_0;
  rtb_sqrt = ((rtb_TmpSignalConversionAtCInp_1 + rtb_Switch_oo_idx_3) -
              rtb_TSamp) - rtb_Switch_oo_idx_0;
  rtb_MathFunction_k[0] = rtb_sqrt;
  rtb_Filter_g = rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_1;
  rtb_MathFunction_m_tmp = rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_0;
  rtb_TSamp_gj = (rtb_Filter_g + rtb_MathFunction_m_tmp) * 2.0;
  rtb_MathFunction_k[3] = rtb_TSamp_gj;
  rtb_TSamp_jt = rtb_Switch_oo_idx_2 * rtb_TmpSignalConversionAtCInp_0;
  rtb_DProdOut = rtb_TmpSignalConversionAtCInp_2 * rtb_Switch_oo_idx_1;
  rtb_TSamp_k = (rtb_TSamp_jt - rtb_DProdOut) * 2.0;
  rtb_MathFunction_k[6] = rtb_TSamp_k;
  rtb_Filter_g = (rtb_Filter_g - rtb_MathFunction_m_tmp) * 2.0;
  rtb_MathFunction_k[1] = rtb_Filter_g;
  rtb_TmpSignalConversionAtCInp_1 -= rtb_Switch_oo_idx_3;
  rtb_Switch_oo_idx_3 = (rtb_TmpSignalConversionAtCInp_1 + rtb_TSamp) -
    rtb_Switch_oo_idx_0;
  rtb_MathFunction_k[4] = rtb_Switch_oo_idx_3;
  rtb_MathFunction_m_tmp = rtb_Switch_oo_idx_1 * rtb_TmpSignalConversionAtCInp_0;
  rtb_TmpSignalConversionAtCInp_0 = rtb_TmpSignalConversionAtCInp_2 *
    rtb_Switch_oo_idx_2;
  rtb_TmpSignalConversionAtCInp_2 = (rtb_MathFunction_m_tmp +
    rtb_TmpSignalConversionAtCInp_0) * 2.0;
  rtb_MathFunction_k[7] = rtb_TmpSignalConversionAtCInp_2;
  rtb_TSamp_jt = (rtb_TSamp_jt + rtb_DProdOut) * 2.0;
  rtb_MathFunction_k[2] = rtb_TSamp_jt;
  rtb_MathFunction_m_tmp = (rtb_MathFunction_m_tmp -
    rtb_TmpSignalConversionAtCInp_0) * 2.0;
  rtb_MathFunction_k[5] = rtb_MathFunction_m_tmp;
  rtb_TmpSignalConversionAtCInp_1 = (rtb_TmpSignalConversionAtCInp_1 - rtb_TSamp)
    + rtb_Switch_oo_idx_0;
  rtb_MathFunction_k[8] = rtb_TmpSignalConversionAtCInp_1;

  /* Gain: '<S409>/Gain' incorporates:
   *  Math: '<S418>/Math Function'
   *  Quat2Dcm: '<S456>/Quaternions to  Direction Cosine Matrix'
   *  Sum: '<S409>/Sum'
   */
  for (i = 0; i < 9; i++) {
    rtb_MathFunction_k[i] = (rtb_MathFunction_k[i] +
      rtb_QuaternionstoDirectionCosin[i]) * 0.5;
  }

  /* End of Gain: '<S409>/Gain' */

  /* Quat2Dcm: '<S431>/C-' */
  rtb_C[0] = rtb_sqrt;
  rtb_C[3] = rtb_TSamp_gj;
  rtb_C[6] = rtb_TSamp_k;
  rtb_C[1] = rtb_Filter_g;
  rtb_C[4] = rtb_Switch_oo_idx_3;
  rtb_C[7] = rtb_TmpSignalConversionAtCInp_2;
  rtb_C[2] = rtb_TSamp_jt;
  rtb_C[5] = rtb_MathFunction_m_tmp;
  rtb_C[8] = rtb_TmpSignalConversionAtCInp_1;

  /* Quat2Dcm: '<S456>/Quaternions to  Direction Cosine Matrix' */
  rtb_QuaternionstoDirectionCosin[0] = rtb_TSamp_d;
  rtb_QuaternionstoDirectionCosin[3] = rtb_TSamp_b;
  rtb_QuaternionstoDirectionCosin[6] = rtb_Product2_a;
  rtb_QuaternionstoDirectionCosin[1] = rtb_TSamp_b0;
  rtb_QuaternionstoDirectionCosin[4] = rtb_TSamp_a;
  rtb_QuaternionstoDirectionCosin[7] = rtb_QuaternionstoDirectionCos_0;
  rtb_QuaternionstoDirectionCosin[2] = rtb_Product_l;
  rtb_QuaternionstoDirectionCosin[5] = rtb_TSamp_fe;
  rtb_QuaternionstoDirectionCosin[8] = rtb_TSamp_c5;

  /* DiscreteTransferFcn: '<S428>/Gyro Filter' */
  rtb_TSamp_c5 = rtb_wBdyEst_rps[0] - 0.4142 * rtDW->GyroFilter_states[0];
  rtb_TSamp_a = 0.7071 * rtb_TSamp_c5 + 0.7071 * rtDW->GyroFilter_states[0];
  rtb_TSamp_d = rtb_wBdyEst_rps[1] - 0.4142 * rtDW->GyroFilter_states[1];
  rtb_TSamp_b0 = 0.7071 * rtb_TSamp_d + 0.7071 * rtDW->GyroFilter_states[1];
  rtb_TSamp_fe = rtb_wBdyEst_rps[2] - 0.4142 * rtDW->GyroFilter_states[2];
  rtb_TSamp_b = 0.7071 * rtb_TSamp_fe + 0.7071 * rtDW->GyroFilter_states[2];

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_flightMode_enum = rtDW->UnitDelay_1_DSTATE;

  /* If: '<S427>/If' incorporates:
   *  Constant: '<S432>/Constant'
   *  RelationalOperator: '<S432>/Compare'
   */
  if (rtb_flightMode_enum <= IDLE) {
    /* Outputs for IfAction SubSystem: '<S427>/Complementary Filter' incorporates:
     *  ActionPort: '<S433>/Action Port'
     */
    /* Product: '<S433>/Matrix Multiply' incorporates:
     *  Delay generated from: '<S433>/Delay'
     *  Gain: '<S433>/Gain2'
     *  Quat2Dcm: '<S433>/Quaternions to  Direction Cosine Matrix'
     */
    rtb_Switch_oo_idx_0 = 0.0;
    rtb_Switch_oo_idx_1 = 0.0;
    rtb_Switch_oo_idx_2 = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_TSamp = -rtDW->Delay_3_DSTATE_e[i];
      rtb_Switch_oo_idx_0 += rtConstB.QuaternionstoDirectionCosin[3 * i] *
        rtb_TSamp;
      rtb_Switch_oo_idx_1 += rtConstB.QuaternionstoDirectionCosin[3 * i + 1] *
        rtb_TSamp;
      rtb_Switch_oo_idx_2 += rtConstB.QuaternionstoDirectionCosin[3 * i + 2] *
        rtb_TSamp;
    }

    /* Math: '<S435>/Math Function1' incorporates:
     *  Math: '<S435>/Math Function'
     *  Product: '<S433>/Matrix Multiply'
     *  Sum: '<S435>/Sum of Elements'
     *
     * About '<S435>/Math Function1':
     *  Operator: sqrt
     */
    rtb_TmpSignalConversionAtCInp_2 = sqrt((rtb_Switch_oo_idx_0 *
      rtb_Switch_oo_idx_0 + rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_1) +
      rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_2);

    /* Switch: '<S435>/Switch' incorporates:
     *  Constant: '<S435>/Constant'
     *  Product: '<S433>/Matrix Multiply'
     *  Product: '<S435>/Product'
     */
    if (rtb_TmpSignalConversionAtCInp_2 > 1.0E-6) {
      rtb_Switch_oo_idx_3 = rtb_TmpSignalConversionAtCInp_2;
    } else {
      rtb_Switch_oo_idx_0 *= 0.0;
      rtb_Switch_oo_idx_1 *= 0.0;
      rtb_Switch_oo_idx_2 *= 0.0;
      rtb_Switch_oo_idx_3 = 1.0;
    }

    /* End of Switch: '<S435>/Switch' */

    /* UnaryMinus: '<S433>/Unary Minus1' incorporates:
     *  Product: '<S435>/Divide'
     */
    rtb_MatrixMultiply[1] = -(rtb_Switch_oo_idx_1 / rtb_Switch_oo_idx_3);
    rtb_MatrixMultiply[2] = -(rtb_Switch_oo_idx_2 / rtb_Switch_oo_idx_3);

    /* Angle2Quat: '<S438>/Rotation Angles to Quaternions' incorporates:
     *  Math: '<S433>/Square'
     *  Math: '<S433>/Square1'
     *  Product: '<S435>/Divide'
     *  Sqrt: '<S433>/Sqrt'
     *  Sum: '<S433>/Sum'
     *  Trigonometry: '<S433>/Atan1'
     *  Trigonometry: '<S433>/Atan2'
     *  UnaryMinus: '<S433>/Unary Minus2'
     */
    rtb_TmpSignalConversionAtCInp_0 = rt_atan2d_snf(rtb_Switch_oo_idx_0 /
      rtb_Switch_oo_idx_3, sqrt(rtb_MatrixMultiply[1] * rtb_MatrixMultiply[1] +
      rtb_MatrixMultiply[2] * rtb_MatrixMultiply[2])) / 2.0;
    rtb_TmpSignalConversionAtCInp_2 = cos(rtb_TmpSignalConversionAtCInp_0);
    rtb_Product_l = rt_atan2d_snf(-rtb_MatrixMultiply[1], rtb_MatrixMultiply[2])
      / 2.0;
    rtb_Product2_a = cos(rtb_Product_l);
    rtb_sqrt = sin(rtb_TmpSignalConversionAtCInp_0);
    rtb_DProdOut = sin(rtb_Product_l);
    rtb_TmpSignalConversionAtCInp_0 = 0.0 * rtb_sqrt;
    rtb_Switch_oo_idx_0 = rtb_TmpSignalConversionAtCInp_0 * rtb_DProdOut +
      rtb_TmpSignalConversionAtCInp_2 * rtb_Product2_a;
    rtb_Product_l = 0.0 * rtb_TmpSignalConversionAtCInp_2;
    rtb_Switch_oo_idx_1 = rtb_Product_l * rtb_Product2_a - rtb_sqrt *
      rtb_DProdOut;
    rtb_Switch_oo_idx_2 = rtb_Product_l * rtb_DProdOut + rtb_sqrt *
      rtb_Product2_a;
    rtb_Switch_oo_idx_3 = rtb_TmpSignalConversionAtCInp_2 * rtb_DProdOut -
      rtb_TmpSignalConversionAtCInp_0 * rtb_Product2_a;

    /* Product: '<S443>/Product2' incorporates:
     *  Constant: '<S438>/Constant'
     *  Product: '<S445>/Product'
     */
    rtb_Product2_a = 0.7071067811860949 * rtb_Switch_oo_idx_2;

    /* Product: '<S443>/Product3' incorporates:
     *  Constant: '<S438>/Constant'
     *  Product: '<S445>/Product1'
     */
    rtb_QuaternionstoDirectionCos_0 = -0.0 * rtb_Switch_oo_idx_3;

    /* Product: '<S443>/Product' incorporates:
     *  Constant: '<S438>/Constant'
     *  Product: '<S445>/Product2'
     */
    rtb_TmpSignalConversionAtCInp_1 = 0.7071067811860949 * rtb_Switch_oo_idx_0;

    /* Product: '<S443>/Product1' incorporates:
     *  Constant: '<S438>/Constant'
     *  Product: '<S445>/Product3'
     */
    rtb_TSamp = -0.0 * rtb_Switch_oo_idx_1;

    /* Sum: '<S443>/Sum' incorporates:
     *  Product: '<S443>/Product'
     *  Product: '<S443>/Product1'
     *  Product: '<S443>/Product2'
     *  Product: '<S443>/Product3'
     */
    rtb_Product_l = ((rtb_TmpSignalConversionAtCInp_1 - rtb_TSamp) -
                     rtb_Product2_a) - rtb_QuaternionstoDirectionCos_0;

    /* Product: '<S444>/Product2' incorporates:
     *  Constant: '<S438>/Constant'
     *  Product: '<S446>/Product'
     */
    rtb_TmpSignalConversionAtCInp_0 = 0.7071067811860949 * rtb_Switch_oo_idx_3;

    /* Product: '<S444>/Product3' incorporates:
     *  Constant: '<S438>/Constant'
     *  Product: '<S446>/Product1'
     */
    rtb_Switch_oo_idx_3 = rtb_Switch_oo_idx_2 * -0.0;

    /* Product: '<S444>/Product' incorporates:
     *  Constant: '<S438>/Constant'
     *  Product: '<S446>/Product2'
     */
    rtb_Switch_oo_idx_1 *= 0.7071067811860949;

    /* Product: '<S444>/Product1' incorporates:
     *  Constant: '<S438>/Constant'
     *  Product: '<S446>/Product3'
     */
    rtb_Switch_oo_idx_2 = rtb_Switch_oo_idx_0 * -0.0;

    /* Sum: '<S444>/Sum' incorporates:
     *  Product: '<S444>/Product'
     *  Product: '<S444>/Product1'
     *  Product: '<S444>/Product2'
     *  Product: '<S444>/Product3'
     */
    rtb_TmpSignalConversionAtCInp_2 = ((rtb_Switch_oo_idx_1 +
      rtb_Switch_oo_idx_2) + rtb_TmpSignalConversionAtCInp_0) -
      rtb_Switch_oo_idx_3;

    /* Sum: '<S445>/Sum' */
    rtb_Product2_a = ((rtb_Product2_a - rtb_QuaternionstoDirectionCos_0) +
                      rtb_TmpSignalConversionAtCInp_1) + rtb_TSamp;

    /* Sum: '<S446>/Sum' */
    rtb_Product1_nd = ((rtb_TmpSignalConversionAtCInp_0 + rtb_Switch_oo_idx_3) -
                       rtb_Switch_oo_idx_1) + rtb_Switch_oo_idx_2;

    /* Sqrt: '<S447>/sqrt' incorporates:
     *  Product: '<S448>/Product'
     *  Product: '<S448>/Product1'
     *  Product: '<S448>/Product2'
     *  Product: '<S448>/Product3'
     *  Sum: '<S448>/Sum'
     */
    rtb_sqrt = sqrt(((rtb_Product_l * rtb_Product_l +
                      rtb_TmpSignalConversionAtCInp_2 *
                      rtb_TmpSignalConversionAtCInp_2) + rtb_Product2_a *
                     rtb_Product2_a) + rtb_Product1_nd * rtb_Product1_nd);

    /* Sum: '<S433>/Sum1' incorporates:
     *  Gain: '<S433>/Gain'
     *  Gain: '<S433>/Gain1'
     *  Product: '<S442>/Product'
     *  Product: '<S442>/Product1'
     *  Product: '<S442>/Product2'
     *  Product: '<S442>/Product3'
     */
    rtb_Switch_oo_idx_0 = rtb_Product_l / rtb_sqrt * 0.0050000000000000044 +
      0.995 * rtb_Sum_mo;
    rtb_Switch_oo_idx_1 = rtb_TmpSignalConversionAtCInp_2 / rtb_sqrt *
      0.0050000000000000044 + 0.995 * rtb_Product1_ad;
    rtb_Switch_oo_idx_2 = rtb_Product2_a / rtb_sqrt * 0.0050000000000000044 +
      0.995 * rtb_Integrator_b;
    rtb_Switch_oo_idx_3 = rtb_Product1_nd / rtb_sqrt * 0.0050000000000000044 +
      0.995 * rtb_Sin;

    /* Switch: '<S437>/Switch' incorporates:
     *  Constant: '<S437>/Constant'
     *  DotProduct: '<S437>/Dot Product'
     */
    if (!(((rtb_Switch_oo_idx_0 * rtb_Switch_oo_idx_0 + rtb_Switch_oo_idx_1 *
            rtb_Switch_oo_idx_1) + rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_2) +
          rtb_Switch_oo_idx_3 * rtb_Switch_oo_idx_3 > 1.0E-6)) {
      rtb_Switch_oo_idx_0 = 1.0;
      rtb_Switch_oo_idx_1 = 0.0;
      rtb_Switch_oo_idx_2 = 0.0;
      rtb_Switch_oo_idx_3 = 0.0;
    }

    /* End of Switch: '<S437>/Switch' */

    /* Sqrt: '<S439>/sqrt' incorporates:
     *  Product: '<S440>/Product'
     *  Product: '<S440>/Product1'
     *  Product: '<S440>/Product2'
     *  Product: '<S440>/Product3'
     *  Sum: '<S440>/Sum'
     */
    rtb_sqrt = sqrt(((rtb_Switch_oo_idx_0 * rtb_Switch_oo_idx_0 +
                      rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_1) +
                     rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_2) +
                    rtb_Switch_oo_idx_3 * rtb_Switch_oo_idx_3);

    /* Product: '<S436>/Product' incorporates:
     *  Merge: '<S427>/Merge'
     */
    rtDW->qEst_na[0] = rtb_Switch_oo_idx_0 / rtb_sqrt;

    /* Product: '<S436>/Product1' incorporates:
     *  Merge: '<S427>/Merge'
     */
    rtDW->qEst_na[1] = rtb_Switch_oo_idx_1 / rtb_sqrt;

    /* Product: '<S436>/Product2' incorporates:
     *  Merge: '<S427>/Merge'
     */
    rtDW->qEst_na[2] = rtb_Switch_oo_idx_2 / rtb_sqrt;

    /* Product: '<S436>/Product3' incorporates:
     *  Merge: '<S427>/Merge'
     */
    rtDW->qEst_na[3] = rtb_Switch_oo_idx_3 / rtb_sqrt;

    /* Update for Delay generated from: '<S433>/Delay' incorporates:
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

    /* End of Update for Delay generated from: '<S433>/Delay' */
    /* End of Outputs for SubSystem: '<S427>/Complementary Filter' */
  } else {
    /* Outputs for IfAction SubSystem: '<S427>/Pass Through' incorporates:
     *  ActionPort: '<S434>/Action Port'
     */
    /* Merge: '<S427>/Merge' incorporates:
     *  SignalConversion generated from: '<S434>/qEst_na'
     */
    rtDW->qEst_na[0] = rtb_Sum_mo;
    rtDW->qEst_na[1] = rtb_Product1_ad;
    rtDW->qEst_na[2] = rtb_Integrator_b;
    rtDW->qEst_na[3] = rtb_Sin;

    /* End of Outputs for SubSystem: '<S427>/Pass Through' */
  }

  /* End of If: '<S427>/If' */

  /* Product: '<S450>/Product3' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S452>/Product1'
   */
  rtb_Integrator_b = 0.0 * rtDW->qEst_na[3];
  rtb_Product1_ad = rtb_Integrator_b;

  /* Product: '<S450>/Product1' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S452>/Product3'
   */
  rtb_Product2_a = 0.0 * rtDW->qEst_na[1];

  /* Sum: '<S450>/Sum' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S450>/Product'
   *  Product: '<S450>/Product1'
   *  Product: '<S450>/Product2'
   */
  rtb_Product_l = ((0.707106781187 * rtDW->qEst_na[0] - rtb_Product2_a) -
                   -0.707106781187 * rtDW->qEst_na[2]) - rtb_Product1_ad;

  /* Product: '<S451>/Product3' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S453>/Product1'
   */
  rtb_TmpSignalConversionAtCInp_0 = rtDW->qEst_na[2] * 0.0;
  rtb_Product1_ad = rtb_TmpSignalConversionAtCInp_0;

  /* Product: '<S451>/Product1' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S453>/Product3'
   */
  rtb_Sum_mo = rtDW->qEst_na[0] * 0.0;

  /* Sum: '<S451>/Sum' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S451>/Product'
   *  Product: '<S451>/Product1'
   *  Product: '<S451>/Product2'
   */
  rtb_Sin = ((0.707106781187 * rtDW->qEst_na[1] + rtb_Sum_mo) + -0.707106781187 *
             rtDW->qEst_na[3]) - rtb_Product1_ad;

  /* Product: '<S452>/Product3' */
  rtb_Product1_ad = rtb_Product2_a;

  /* Sum: '<S452>/Sum' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S452>/Product'
   *  Product: '<S452>/Product2'
   */
  rtb_Integrator_b = ((0.707106781187 * rtDW->qEst_na[2] - rtb_Integrator_b) +
                      rtDW->qEst_na[0] * -0.707106781187) + rtb_Product1_ad;

  /* Product: '<S453>/Product3' */
  rtb_Product1_ad = rtb_Sum_mo;

  /* SignalConversion generated from: '<S429>/Quaternions to Rotation Angles' incorporates:
   *  Constant: '<S429>/Constant'
   *  Product: '<S453>/Product'
   *  Product: '<S453>/Product2'
   *  Sum: '<S453>/Sum'
   */
  rtb_Switch_oo_idx_3 = ((0.707106781187 * rtDW->qEst_na[3] +
    rtb_TmpSignalConversionAtCInp_0) - rtDW->qEst_na[1] * -0.707106781187) +
    rtb_Product1_ad;

  /* Quat2Angle: '<S429>/Quaternions to Rotation Angles' incorporates:
   *  SignalConversion generated from: '<S429>/Quaternions to Rotation Angles'
   *  Trigonometry: '<S224>/Cos1'
   */
  rtb_MathFunction_idx_2 = 1.0 / sqrt(((rtb_Product_l * rtb_Product_l + rtb_Sin *
    rtb_Sin) + rtb_Integrator_b * rtb_Integrator_b) + rtb_Switch_oo_idx_3 *
    rtb_Switch_oo_idx_3);
  rtb_TmpSignalConversionAtCInp_2 = rtb_MathFunction_idx_2 * rtb_Product_l;
  rtb_Switch_oo_idx_2 = rtb_MathFunction_idx_2 * rtb_Sin;
  rtb_Switch_oo_idx_1 = rtb_MathFunction_idx_2 * rtb_Integrator_b;
  rtb_TmpSignalConversionAtCInp_0 = rtb_MathFunction_idx_2 * rtb_Switch_oo_idx_3;
  rtb_MathFunction_idx_2 = rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_2;
  rtb_Sum_mo = rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_2;
  rtb_Integrator_b = rtb_Switch_oo_idx_1 * rtb_Switch_oo_idx_1;
  rtb_Product_l = rtb_TmpSignalConversionAtCInp_0 *
    rtb_TmpSignalConversionAtCInp_0;
  rtb_Product1_ad = ((rtb_MathFunction_idx_2 + rtb_Sum_mo) - rtb_Integrator_b) -
    rtb_Product_l;
  rtb_QuaternionstoDirectionCos_0 = rtb_Switch_oo_idx_2 * rtb_Switch_oo_idx_1;
  rtb_TmpSignalConversionAtCInp_1 = rtb_TmpSignalConversionAtCInp_2 *
    rtb_TmpSignalConversionAtCInp_0;
  rtb_Switch_oo_idx_3 = (rtb_QuaternionstoDirectionCos_0 +
    rtb_TmpSignalConversionAtCInp_1) * 2.0;
  rtb_Sin = rtb_Switch_oo_idx_2 * rtb_TmpSignalConversionAtCInp_0;
  rtb_Product2_a = rtb_TmpSignalConversionAtCInp_2 * rtb_Switch_oo_idx_1;
  rtb_sqrt = (rtb_Sin - rtb_Product2_a) * 2.0;
  rtb_Switch_oo_idx_0 = (rtb_QuaternionstoDirectionCos_0 -
    rtb_TmpSignalConversionAtCInp_1) * 2.0;
  rtb_Sum_mo = rtb_MathFunction_idx_2 - rtb_Sum_mo;
  rtb_Filter_g = (rtb_Sum_mo + rtb_Integrator_b) - rtb_Product_l;
  rtb_Product1_j3 = rtb_Switch_oo_idx_1 * rtb_TmpSignalConversionAtCInp_0;
  rtb_TmpSignalConversionAtCInp_0 = rtb_TmpSignalConversionAtCInp_2 *
    rtb_Switch_oo_idx_2;
  rtb_MathFunction_m_tmp = (rtb_Product1_j3 + rtb_TmpSignalConversionAtCInp_0) *
    2.0;
  rtb_Switch_oo_idx_1 = (rtb_Sin + rtb_Product2_a) * 2.0;
  rtb_TSamp_gj = (rtb_Product1_j3 - rtb_TmpSignalConversionAtCInp_0) * 2.0;
  rtb_TSamp_jt = (rtb_Sum_mo - rtb_Integrator_b) + rtb_Product_l;
  if (-rtb_sqrt <= -1.0) {
    rtb_Product_l = -1.0;
  } else if (-rtb_sqrt >= 1.0) {
    rtb_Product_l = 1.0;
  } else {
    rtb_Product_l = -rtb_sqrt;
  }

  rtb_TmpSignalConversionAtCInp_0 = asin(rtb_Product_l);
  if (fabs(rtb_Product_l) == 1.0) {
    rtb_accBdyEst_mps2[0] = rt_atan2d_snf(-rtb_Switch_oo_idx_0, rtb_Filter_g);
    rtb_QuaternionstoDirectionCos_0 = 0.0;
    rtb_TmpSignalConversionAtCInp_1 = 0.0;
  } else {
    rtb_QuaternionstoDirectionCos_0 = rt_atan2d_snf(rtb_Switch_oo_idx_3,
      rtb_Product1_ad);
    rtb_TmpSignalConversionAtCInp_1 = rt_atan2d_snf(rtb_MathFunction_m_tmp,
      rtb_TSamp_jt);
    rtb_accBdyEst_mps2[0] = 0.0;
  }

  rtb_Product_l = cos(rtb_TmpSignalConversionAtCInp_1);
  rtb_Product2_a = sin(rtb_TmpSignalConversionAtCInp_1);
  rtb_Sum_mo = cos(rtb_TmpSignalConversionAtCInp_0);
  rtb_Integrator_b = sin(rtb_TmpSignalConversionAtCInp_0);
  rtb_MathFunction_idx_2 = 0.0 * rtb_Integrator_b;
  rtb_TmpSignalConversionAtCInp_2 = rtb_MathFunction_idx_2 + rtb_Sum_mo;
  rtb_Sin = 0.0 * rtb_Sum_mo;
  rtb_Product1_o = rtb_Sin - rtb_Integrator_b;
  rtb_TSamp = rtb_Product_l * 0.0;
  rtb_Switch_oo_idx_2 = (rtb_Sin + rtb_TSamp) + rtb_Product2_a *
    rtb_Integrator_b;
  rtb_DProdOut = rtb_Product2_a * 0.0 + rtb_Product_l;
  rtb_Product1_j3 = 0.0 * -rtb_Integrator_b;
  rtb_TSamp_k = (rtb_Product1_j3 + rtb_TSamp) + rtb_Product2_a * rtb_Sum_mo;
  rtb_MathFunction_idx_1 = -rtb_Product2_a * 0.0;
  rtb_Product1_nd = (rtb_Sin + rtb_MathFunction_idx_1) + rtb_Integrator_b *
    rtb_Product_l;
  rtb_MathFunction_idx_0 = rtb_TSamp - rtb_Product2_a;
  rtb_MathFunction_idx_1 = (rtb_Product1_j3 + rtb_MathFunction_idx_1) +
    rtb_Product_l * rtb_Sum_mo;
  rtb_Product_l = cos(rtb_QuaternionstoDirectionCos_0);
  rtb_Product2_a = sin(rtb_QuaternionstoDirectionCos_0);
  rtb_Gain_a = rtb_Sin + rtb_MathFunction_idx_2;
  rtb_Switch2_f = rtb_Product1_j3 + rtb_Sin;
  rtb_Sum4_a = rtb_Sin + rtb_Integrator_b;
  rtb_Product1_j3 += rtb_Sum_mo;
  rtb_Sin = cos(rtb_accBdyEst_mps2[0]);
  rtb_Integrator_b = sin(rtb_accBdyEst_mps2[0]);
  rtb_TSamp = rtb_Product1_o * 0.0;
  rtb_MathFunction_idx_2 = rtb_Switch2_f * 0.0;
  rtb_Switch2_m = 0.0 * -rtb_Integrator_b;
  rtb_UkYk1_l = 0.0 * rtb_Sin;
  rtb_PProdOut_b = rtb_Product1_j3 * 0.0;
  rtb_sqrt = fabs(rtb_sqrt - (rtb_TmpSignalConversionAtCInp_2 * 0.0 +
    rtb_Product1_o));
  rtb_Product1_o = rtb_TSamp_k * 0.0;
  rtb_Sum1 = rtb_MathFunction_idx_1 * 0.0;
  if ((((((((fabs(rtb_Product1_ad - ((rtb_TmpSignalConversionAtCInp_2 * rtb_Sin
                + rtb_Switch2_m) + rtb_TSamp)) + fabs(rtb_Switch_oo_idx_3 -
              ((rtb_TmpSignalConversionAtCInp_2 * rtb_Integrator_b + rtb_UkYk1_l)
               + rtb_TSamp))) + rtb_sqrt) + fabs(rtb_Switch_oo_idx_0 - ((rtb_Sin
              * rtb_Gain_a - rtb_Integrator_b) + rtb_MathFunction_idx_2))) +
          fabs(rtb_Filter_g - ((rtb_Integrator_b * rtb_Gain_a + rtb_Sin) +
            rtb_MathFunction_idx_2))) + fabs(rtb_MathFunction_m_tmp -
          (rtb_Gain_a * 0.0 + rtb_Switch2_f))) + fabs(rtb_Switch_oo_idx_1 -
         ((rtb_Sin * rtb_Sum4_a + rtb_Switch2_m) + rtb_PProdOut_b))) + fabs
       (rtb_TSamp_gj - ((rtb_Integrator_b * rtb_Sum4_a + rtb_UkYk1_l) +
                        rtb_PProdOut_b))) + fabs(rtb_TSamp_jt - (rtb_Sum4_a *
        0.0 + rtb_Product1_j3)) <= (((((((fabs(rtb_Product1_ad -
              ((rtb_TmpSignalConversionAtCInp_2 * rtb_Product_l + 0.0 *
                -rtb_Product2_a) + rtb_TSamp)) + fabs(rtb_Switch_oo_idx_3 -
              ((rtb_TmpSignalConversionAtCInp_2 * rtb_Product2_a + 0.0 *
                rtb_Product_l) + rtb_TSamp))) + rtb_sqrt) + fabs
           (rtb_Switch_oo_idx_0 - ((rtb_Product_l * rtb_Switch_oo_idx_2 +
              -rtb_Product2_a * rtb_DProdOut) + rtb_Product1_o))) + fabs
          (rtb_Filter_g - ((rtb_Product2_a * rtb_Switch_oo_idx_2 + rtb_DProdOut *
             rtb_Product_l) + rtb_Product1_o))) + fabs(rtb_MathFunction_m_tmp -
          ((rtb_Switch_oo_idx_2 * 0.0 + rtb_DProdOut * 0.0) + rtb_TSamp_k))) +
        fabs(rtb_Switch_oo_idx_1 - ((rtb_Product_l * rtb_Product1_nd +
           -rtb_Product2_a * rtb_MathFunction_idx_0) + rtb_Sum1))) + fabs
       (rtb_TSamp_gj - ((rtb_Product2_a * rtb_Product1_nd + rtb_Product_l *
                         rtb_MathFunction_idx_0) + rtb_Sum1))) + fabs
      (rtb_TSamp_jt - ((rtb_Product1_nd * 0.0 + rtb_MathFunction_idx_0 * 0.0) +
                       rtb_MathFunction_idx_1))) {
    rtb_QuaternionstoDirectionCos_0 = rtb_accBdyEst_mps2[0];
    rtb_TmpSignalConversionAtCInp_1 = 0.0;
  }

  /* Product: '<S319>/DProd Out' incorporates:
   *  Constant: '<S226>/Constant4'
   *  Constant: '<S2>/Constant'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   *  Sum: '<S224>/Sum2'
   */
  rtb_Product1_ad = (0.0 - rtb_TmpSignalConversionAtCInp_1) * 0.0;

  /* Sum: '<S321>/SumD' incorporates:
   *  DiscreteIntegrator: '<S321>/Filter'
   */
  rtb_Product1_ad -= rtDW->Filter_DSTATE;

  /* Product: '<S329>/NProd Out' incorporates:
   *  Constant: '<S226>/Constant4'
   */
  rtb_Product_l = rtb_Product1_ad * 100.0;

  /* Product: '<S288>/Product1' incorporates:
   *  Constant: '<S2>/Constant'
   *  DiscreteIntegrator: '<S326>/Integrator'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   *  Sum: '<S224>/Sum2'
   *  Sum: '<S335>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product2_a = (((0.0 - rtb_TmpSignalConversionAtCInp_1) +
                     rtDW->Integrator_DSTATE) + rtb_Product_l) * (real_T)
    rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S347>/Switch2' incorporates:
   *  Constant: '<S226>/Constant2'
   *  Constant: '<S226>/Constant3'
   *  RelationalOperator: '<S347>/LowerRelop1'
   *  RelationalOperator: '<S347>/UpperRelop'
   *  Switch: '<S347>/Switch'
   */
  if (rtb_Product2_a > 2.0) {
    rtb_sqrt = 2.0;
  } else if (rtb_Product2_a < -2.0) {
    /* Switch: '<S347>/Switch' incorporates:
     *  Constant: '<S226>/Constant3'
     */
    rtb_sqrt = -2.0;
  } else {
    rtb_sqrt = rtb_Product2_a;
  }

  /* End of Switch: '<S347>/Switch2' */

  /* Delay: '<S345>/Delay' */
  if (rtDW->icLoad) {
    rtDW->Delay_DSTATE = rtb_sqrt;
  }

  /* Product: '<S345>/delta rise limit' incorporates:
   *  Constant: '<S226>/Constant'
   *  SampleTimeMath: '<S345>/sample time'
   *
   * About '<S345>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_TmpSignalConversionAtCInp_2 = 0.05;

  /* Sum: '<S345>/Difference Inputs1' incorporates:
   *  Delay: '<S345>/Delay'
   *
   * Block description for '<S345>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Sin = rtb_sqrt - rtDW->Delay_DSTATE;

  /* Switch: '<S346>/Switch2' incorporates:
   *  RelationalOperator: '<S346>/LowerRelop1'
   */
  if (!(rtb_Sin > 0.05)) {
    /* Switch: '<S346>/Switch' incorporates:
     *  RelationalOperator: '<S346>/UpperRelop'
     */
    if (rtb_Sin < -0.05) {
      rtb_TmpSignalConversionAtCInp_2 = -0.05;
    } else {
      rtb_TmpSignalConversionAtCInp_2 = rtb_Sin;
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
  rtb_Sin = rtb_TmpSignalConversionAtCInp_2 + rtDW->Delay_DSTATE;

  /* Sum: '<S8>/Sum' incorporates:
   *  DiscreteTransferFcn: '<S428>/Gyro Filter'
   */
  rtb_TmpSignalConversionAtCInp_2 = rtb_Sin - rtb_TSamp_a;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_Product1_ad = rtDW->UnitDelay_15_DSTATE;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_Filter_g = rtDW->UnitDelay_16_DSTATE;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_Integrator_b = rtDW->UnitDelay_17_DSTATE;

  /* Product: '<S456>/Matrix Multiply' incorporates:
   *  Constant: '<S456>/Constant'
   *  Quat2Dcm: '<S456>/Quaternions to  Direction Cosine Matrix'
   */
  rtb_Switch_oo_idx_1 = 0.0;
  rtb_Switch_oo_idx_3 = 0.0;
  rtb_Switch_oo_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    rtb_TSamp = rtCP__Constant_Value_bn[i];
    rtb_Switch_oo_idx_1 += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_TSamp;
    rtb_Switch_oo_idx_3 += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
      rtb_TSamp;
    rtb_Switch_oo_idx_2 += rtb_QuaternionstoDirectionCosin[3 * i + 2] *
      rtb_TSamp;

    /* Sum: '<S413>/Sum2' incorporates:
     *  Constant: '<S456>/Constant'
     *  Inport: '<Root>/sensor_bus'
     *  Quat2Dcm: '<S456>/Quaternions to  Direction Cosine Matrix'
     *  UnitDelay generated from: '<S408>/Unit Delay'
     */
    rtb_Product_k4[i] = rtU_sensor_bus_e->fBdyMeas_mps2[i] -
      rtDW->UnitDelay_12_DSTATE[i];
  }

  /* Sum: '<S413>/Sum1' incorporates:
   *  Product: '<S456>/Matrix Multiply'
   */
  rtb_MathFunction_m_tmp = rtb_Switch_oo_idx_1 + rtb_Product_k4[0];
  rtb_accBdyEst_mps2[0] = rtb_MathFunction_m_tmp;

  /* DiscreteTransferFcn: '<S409>/Accel Filter' */
  rtb_TSamp_gj = rtb_MathFunction_m_tmp - 0.0 * rtDW->AccelFilter_states[0];

  /* Sum: '<S413>/Sum1' incorporates:
   *  Product: '<S456>/Matrix Multiply'
   */
  rtb_MathFunction_m_tmp = rtb_Switch_oo_idx_3 + rtb_Product_k4[1];
  rtb_accBdyEst_mps2[1] = rtb_MathFunction_m_tmp;

  /* DiscreteTransferFcn: '<S409>/Accel Filter' */
  rtb_TSamp_jt = rtb_MathFunction_m_tmp - 0.0 * rtDW->AccelFilter_states[1];
  rtb_TSamp = 0.5 * rtb_TSamp_jt + 0.5 * rtDW->AccelFilter_states[1];

  /* Sum: '<S413>/Sum1' incorporates:
   *  Product: '<S456>/Matrix Multiply'
   */
  rtb_MathFunction_m_tmp = rtb_Switch_oo_idx_2 + rtb_Product_k4[2];
  rtb_accBdyEst_mps2[2] = rtb_MathFunction_m_tmp;

  /* DiscreteTransferFcn: '<S409>/Accel Filter' */
  rtb_TSamp_k = rtb_MathFunction_m_tmp - 0.0 * rtDW->AccelFilter_states[2];

  /* Product: '<S409>/Product' incorporates:
   *  DiscreteTransferFcn: '<S409>/Accel Filter'
   *  Math: '<S418>/Math Function'
   */
  rtb_Switch_oo_idx_1 = 0.5 * rtb_TSamp_gj + 0.5 * rtDW->AccelFilter_states[0];
  rtb_Switch_oo_idx_3 = 0.5 * rtb_TSamp_k + 0.5 * rtDW->AccelFilter_states[2];
  for (i = 0; i < 3; i++) {
    rtb_MatrixMultiply[i] = (rtb_MathFunction_k[3 * i + 1] * rtb_TSamp +
      rtb_MathFunction_k[3 * i] * rtb_Switch_oo_idx_1) + rtb_MathFunction_k[3 *
      i + 2] * rtb_Switch_oo_idx_3;
  }

  /* End of Product: '<S409>/Product' */

  /* Sum: '<S409>/Sum4' incorporates:
   *  Gain: '<S409>/Gain3'
   */
  rtb_MathFunction_idx_0 = 0.01 * rtb_MatrixMultiply[0] + rtb_Product1_ad;
  rtb_MathFunction_idx_1 = 0.01 * rtb_MatrixMultiply[1] + rtb_Filter_g;
  rtb_MathFunction_idx_2 = 0.01 * rtb_MatrixMultiply[2] + rtb_Integrator_b;

  /* DotProduct: '<S455>/Dot Product' */
  rtb_Integrator_b = (rtb_MathFunction_idx_0 * rtb_MathFunction_idx_0 +
                      rtb_MathFunction_idx_1 * rtb_MathFunction_idx_1) +
    rtb_MathFunction_idx_2 * rtb_MathFunction_idx_2;

  /* Gain: '<S455>/Gain1' incorporates:
   *  Gain: '<S455>/Gain'
   */
  rtb_Integrator_b = 0.5 * rtb_Integrator_b * 1.225;

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
  LookUp_real_T_real_T( &(rtb_Filter_g), rtCP__Constant4_Value, rtb_Integrator_b,
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
  LookUp_real_T_real_T( &(rtb_Product1_ad), rtCP__Constant6_Value,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Value, 2U);

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
  LookUp_real_T_real_T( &(rtb_Filter_b), rtCP__Constant7_Value, rtb_Integrator_b,
                       rtCP__Internalbreakpoints_Value, 2U);

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
  LookUp_real_T_real_T( &(rtb_Product1_g), rtCP__Constant4_Value_l,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Val_d, 2U);

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
  LookUp_real_T_real_T( &(rtb_Filter_e), rtCP__Constant6_Value_e,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Val_d, 2U);

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
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_k), rtCP__Constant7_Value_n,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Val_d, 2U);

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
  LookUp_real_T_real_T( &(rtb_Integrator_g), rtCP__Constant4_Value_c,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Val_f, 2U);

  /* Product: '<S128>/PProd Out' */
  rtb_Product1_nd = rtb_TmpSignalConversionAtCInp_2 * rtb_Integrator_g;

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
  LookUp_real_T_real_T( &(rtb_Filter_c), rtCP__Constant6_Value_p,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Val_f, 2U);

  /* Product: '<S116>/DProd Out' */
  rtb_DProdOut = rtb_TmpSignalConversionAtCInp_2 * rtb_Filter_c;

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
  LookUp_real_T_real_T( &(rtb_Integrator_fe), rtCP__Constant7_Value_o,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Val_f, 2U);

  /* Product: '<S126>/NProd Out' incorporates:
   *  Sum: '<S118>/SumD'
   */
  rtb_Filter_c = (rtb_DProdOut - rtb_Filter_c) * rtb_Integrator_fe;

  /* Sum: '<S132>/Sum' */
  rtb_Integrator_fe = (rtb_Product1_nd + rtb_Integrator_g) + rtb_Filter_c;

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
  if (rtb_Gain_a > 5.0) {
    rtb_Switch2_f = 5.0;
  } else if (rtb_Gain_a < -5.0) {
    /* Switch: '<S152>/Switch' incorporates:
     *  Constant: '<S10>/Constant3'
     */
    rtb_Switch2_f = -5.0;
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
  rtb_Integrator_fe = 0.9;

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
  if (!(rtb_Integrator_g > 0.9)) {
    /* Switch: '<S151>/Switch' incorporates:
     *  RelationalOperator: '<S151>/UpperRelop'
     */
    if (rtb_Integrator_g < -0.9) {
      rtb_Integrator_fe = -0.9;
    } else {
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
  rtb_Integrator_fe = cos(rtb_TmpSignalConversionAtCInp_1);

  /* Trigonometry: '<S224>/Sin' incorporates:
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   */
  rtb_Sum1 = sin(rtb_TmpSignalConversionAtCInp_1);

  /* Sum: '<S224>/Sum4' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Product: '<S224>/Product'
   *  Product: '<S224>/Product1'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   *  Sum: '<S224>/Sum'
   *  Sum: '<S224>/Sum1'
   */
  rtb_Sum4_a = (0.0 - rtb_TmpSignalConversionAtCInp_0) * rtb_Integrator_fe +
    rtb_Sum1 * rtb_Sum_mo * (0.0 - rtb_QuaternionstoDirectionCos_0);

  /* Product: '<S269>/NProd Out' incorporates:
   *  Constant: '<S225>/Constant4'
   *  DiscreteIntegrator: '<S261>/Filter'
   *  Product: '<S259>/DProd Out'
   *  Sum: '<S261>/SumD'
   */
  rtb_Product1_nd = rtb_Sum4_a * 0.0 - rtDW->Filter_DSTATE_n;

  /* Product: '<S228>/Product1' incorporates:
   *  Constant: '<S225>/Constant4'
   *  DiscreteIntegrator: '<S266>/Integrator'
   *  Product: '<S271>/PProd Out'
   *  Sum: '<S275>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_j3 = ((rtb_Sum4_a * 2.0 + rtDW->Integrator_DSTATE_g) +
                     rtb_Product1_nd) * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S287>/Switch2' incorporates:
   *  Constant: '<S225>/Constant2'
   *  Constant: '<S225>/Constant3'
   *  RelationalOperator: '<S287>/LowerRelop1'
   *  RelationalOperator: '<S287>/UpperRelop'
   *  Switch: '<S287>/Switch'
   */
  if (rtb_Product1_j3 > 0.4) {
    rtb_Switch2_m = 0.4;
  } else if (rtb_Product1_j3 < -0.4) {
    /* Switch: '<S287>/Switch' incorporates:
     *  Constant: '<S225>/Constant3'
     */
    rtb_Switch2_m = -0.4;
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
   *  SampleTimeMath: '<S285>/sample time'
   *
   * About '<S285>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_DProdOut = 0.005;

  /* Sum: '<S285>/Difference Inputs1' incorporates:
   *  Delay: '<S285>/Delay'
   *
   * Block description for '<S285>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_UkYk1_l = rtb_Switch2_m - rtDW->Delay_DSTATE_c;

  /* Switch: '<S286>/Switch2' incorporates:
   *  RelationalOperator: '<S286>/LowerRelop1'
   */
  if (!(rtb_UkYk1_l > 0.005)) {
    /* Switch: '<S286>/Switch' incorporates:
     *  RelationalOperator: '<S286>/UpperRelop'
     */
    if (rtb_UkYk1_l < -0.005) {
      rtb_DProdOut = -0.005;
    } else {
      rtb_DProdOut = rtb_UkYk1_l;
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
  rtb_UkYk1_l = rtb_DProdOut + rtDW->Delay_DSTATE_c;

  /* Sum: '<S8>/Sum2' incorporates:
   *  DiscreteTransferFcn: '<S428>/Gyro Filter'
   */
  rtb_DProdOut = rtb_UkYk1_l - rtb_TSamp_b0;

  /* Product: '<S57>/PProd Out' */
  rtb_PProdOut_b = rtb_DProdOut * rtb_Filter_g;

  /* DiscreteIntegrator: '<S47>/Filter' */
  rtb_Filter_g = rtDW->Filter_DSTATE_l;

  /* Product: '<S55>/NProd Out' incorporates:
   *  Product: '<S45>/DProd Out'
   *  Sum: '<S47>/SumD'
   */
  rtb_Filter_g = (rtb_DProdOut * rtb_Product1_ad - rtb_Filter_g) * rtb_Filter_b;

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
  if (rtb_Divide > 45.0) {
    rtb_Switch2_j = 45.0;
  } else if (rtb_Divide < -45.0) {
    /* Switch: '<S82>/Switch' incorporates:
     *  Constant: '<S9>/Constant3'
     */
    rtb_Switch2_j = -45.0;
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
   *  SampleTimeMath: '<S80>/sample time'
   *
   * About '<S80>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Filter_b = 1.8;

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
  if (!(rtb_PProdOut_b > 1.8)) {
    /* Switch: '<S81>/Switch' incorporates:
     *  RelationalOperator: '<S81>/UpperRelop'
     */
    if (rtb_PProdOut_b < -1.8) {
      rtb_Filter_b = -1.8;
    } else {
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
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Product: '<S224>/Product2'
   *  Product: '<S224>/Product3'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   *  Sum: '<S224>/Sum'
   *  Sum: '<S224>/Sum1'
   *  UnaryMinus: '<S224>/Unary Minus'
   */
  rtb_Sum3 = (0.0 - rtb_TmpSignalConversionAtCInp_0) * -rtb_Sum1 +
    rtb_Integrator_fe * rtb_Sum_mo * (0.0 - rtb_QuaternionstoDirectionCos_0);

  /* Product: '<S379>/DProd Out' incorporates:
   *  Constant: '<S227>/Constant4'
   */
  rtb_Integrator_fe = rtb_Sum3 * 0.0;

  /* DiscreteIntegrator: '<S381>/Filter' */
  rtb_Filter_b = rtDW->Filter_DSTATE_c;

  /* Product: '<S389>/NProd Out' incorporates:
   *  Sum: '<S381>/SumD'
   */
  rtb_Filter_b = rtb_Integrator_fe - rtb_Filter_b;

  /* Product: '<S348>/Product1' incorporates:
   *  Constant: '<S227>/Constant4'
   *  DiscreteIntegrator: '<S386>/Integrator'
   *  Product: '<S391>/PProd Out'
   *  Sum: '<S395>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Sum_mo = ((rtb_Sum3 * 2.0 + rtDW->Integrator_DSTATE_l) + rtb_Filter_b) *
    (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Switch: '<S407>/Switch2' incorporates:
   *  Constant: '<S227>/Constant2'
   *  Constant: '<S227>/Constant3'
   *  RelationalOperator: '<S407>/LowerRelop1'
   *  RelationalOperator: '<S407>/UpperRelop'
   *  Switch: '<S407>/Switch'
   */
  if (rtb_Sum_mo > 0.4) {
    rtb_Switch2_d = 0.4;
  } else if (rtb_Sum_mo < -0.4) {
    /* Switch: '<S407>/Switch' incorporates:
     *  Constant: '<S227>/Constant3'
     */
    rtb_Switch2_d = -0.4;
  } else {
    rtb_Switch2_d = rtb_Sum_mo;
  }

  /* End of Switch: '<S407>/Switch2' */

  /* Delay: '<S405>/Delay' */
  if (rtDW->icLoad_c) {
    rtDW->Delay_DSTATE_h = rtb_Switch2_d;
  }

  /* Product: '<S405>/delta rise limit' incorporates:
   *  Constant: '<S227>/Constant'
   *  SampleTimeMath: '<S405>/sample time'
   *
   * About '<S405>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Sum1 = 0.005;

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
  if (!(rtb_Integrator_fe > 0.005)) {
    /* Switch: '<S406>/Switch' incorporates:
     *  RelationalOperator: '<S406>/UpperRelop'
     */
    if (rtb_Integrator_fe < -0.005) {
      rtb_Sum1 = -0.005;
    } else {
      rtb_Sum1 = rtb_Integrator_fe;
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
  rtb_Integrator_i = rtb_Sum1 + rtDW->Delay_DSTATE_h;

  /* Sum: '<S8>/Sum1' incorporates:
   *  DiscreteTransferFcn: '<S428>/Gyro Filter'
   */
  rtb_Sum1 = rtb_Integrator_i - rtb_TSamp_b;

  /* DiscreteIntegrator: '<S193>/Integrator' */
  rtb_Integrator_fe = rtDW->Integrator_DSTATE_e;

  /* Product: '<S186>/DProd Out' */
  rtb_DProdOut_m = rtb_Sum1 * rtb_Filter_e;

  /* DiscreteIntegrator: '<S188>/Filter' */
  rtb_Filter_e = rtDW->Filter_DSTATE_g;

  /* Product: '<S196>/NProd Out' incorporates:
   *  Sum: '<S188>/SumD'
   */
  rtb_Filter_e = (rtb_DProdOut_m - rtb_Filter_e) * rtb_GainDynamicLookup_k;

  /* Sum: '<S202>/Sum' incorporates:
   *  Product: '<S198>/PProd Out'
   */
  rtb_GainDynamicLookup_k = (rtb_Sum1 * rtb_Product1_g + rtb_Integrator_fe) +
    rtb_Filter_e;

  /* Product: '<S153>/Product1' incorporates:
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product1_g = rtb_GainDynamicLookup_k * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S155>/Divide' incorporates:
   *  Gain: '<S155>/Gain'
   */
  rtb_Divide_l = -6756.0 * rtb_Product1_g / 50000.0;

  /* Switch: '<S223>/Switch2' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Constant: '<S11>/Constant3'
   *  RelationalOperator: '<S223>/LowerRelop1'
   *  RelationalOperator: '<S223>/UpperRelop'
   *  Switch: '<S223>/Switch'
   */
  if (rtb_Divide_l > 45.0) {
    rtb_Switch2_b = 45.0;
  } else if (rtb_Divide_l < -45.0) {
    /* Switch: '<S223>/Switch' incorporates:
     *  Constant: '<S11>/Constant3'
     */
    rtb_Switch2_b = -45.0;
  } else {
    rtb_Switch2_b = rtb_Divide_l;
  }

  /* End of Switch: '<S223>/Switch2' */

  /* Delay: '<S221>/Delay' */
  if (rtDW->icLoad_d) {
    rtDW->Delay_DSTATE_e = rtb_Switch2_b;
  }

  /* Product: '<S221>/delta rise limit' incorporates:
   *  Constant: '<S11>/Constant'
   *  SampleTimeMath: '<S221>/sample time'
   *
   * About '<S221>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_GainDynamicLookup_k = 1.8;

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
  if (!(rtb_Integrator_fe > 1.8)) {
    /* Switch: '<S222>/Switch' incorporates:
     *  RelationalOperator: '<S222>/UpperRelop'
     */
    if (rtb_Integrator_fe < -1.8) {
      rtb_GainDynamicLookup_k = -1.8;
    } else {
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
  rtb_Switch_oo_idx_0 = rtb_PProdOut_b + rtb_Integrator_g;
  rtb_Switch_oo_idx_1 = rtb_GainDynamicLookup_k - rtb_Integrator_g;
  rtb_Switch_oo_idx_2 = rtb_GainDynamicLookup_b + rtb_Integrator_g;
  rtb_Switch_oo_idx_3 = rtb_Integrator_fe - rtb_Integrator_g;

  /* Outport: '<Root>/control_deg' */
  rtY_control_deg[0] = rtb_Switch_oo_idx_0;
  rtY_control_deg[1] = rtb_Switch_oo_idx_1;
  rtY_control_deg[2] = rtb_Switch_oo_idx_2;
  rtY_control_deg[3] = rtb_Switch_oo_idx_3;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_GainDynamicLookup_b = rtDW->UnitDelay_18_DSTATE;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_GainDynamicLookup_k = rtDW->UnitDelay_19_DSTATE;

  /* UnitDelay generated from: '<S408>/Unit Delay' */
  rtb_DProdOut_m = rtDW->UnitDelay_20_DSTATE;

  /* Gain: '<S409>/Gain4' */
  rtb_MatrixMultiply[0] *= 5.0E-5;
  rtb_MatrixMultiply[1] *= 5.0E-5;
  rtb_MatrixMultiply[2] *= 5.0E-5;

  /* Sum: '<S409>/Sum5' incorporates:
   *  Gain: '<S409>/Gain5'
   */
  rtb_Sum5_idx_0 = (0.01 * rtb_MathFunction_idx_0 + rtb_GainDynamicLookup_b) -
    rtb_MatrixMultiply[0];
  rtb_Sum5_idx_1 = (0.01 * rtb_MathFunction_idx_1 + rtb_GainDynamicLookup_k) -
    rtb_MatrixMultiply[1];
  rtb_Sum5_idx_2 = (0.01 * rtb_MathFunction_idx_2 + rtb_DProdOut_m) -
    rtb_MatrixMultiply[2];

  /* RelationalOperator: '<S430>/Compare' incorporates:
   *  Constant: '<S430>/Constant'
   */
  rtb_LogicalOperator1_j = (rtb_flightMode_enum == IDLE);

  /* DiscreteTransferFcn: '<S428>/Accel Filter' */
  rtb_TSamp_ge = rtb_accBdyEst_mps2[0] - 0.0 * rtDW->AccelFilter_states_l[0];

  /* Switch: '<S426>/Switch' */
  if (rtb_LogicalOperator1_j) {
    /* Switch: '<S426>/Switch' incorporates:
     *  Delay generated from: '<S426>/Delay'
     */
    Switch[0] = rtDW->Delay_4_DSTATE[0];
    Switch[1] = rtDW->Delay_4_DSTATE[1];
    Switch[2] = rtDW->Delay_4_DSTATE[2];
  } else {
    /* Switch: '<S426>/Switch' incorporates:
     *  UnitDelay: '<S426>/Unit Delay'
     */
    Switch[0] = rtDW->UnitDelay_DSTATE[0];
    Switch[1] = rtDW->UnitDelay_DSTATE[1];
    Switch[2] = rtDW->UnitDelay_DSTATE[2];
  }

  /* End of Switch: '<S426>/Switch' */

  /* DiscreteTransferFcn: '<S428>/Accel Filter' incorporates:
   *  Sum: '<S413>/Sum1'
   */
  rtb_TSamp_i = rtb_accBdyEst_mps2[1] - 0.0 * rtDW->AccelFilter_states_l[1];
  rtb_TSamp_h = rtb_MathFunction_m_tmp - 0.0 * rtDW->AccelFilter_states_l[2];
  for (i = 0; i < 3; i++) {
    /* DiscreteFir: '<S426>/Discrete FIR Filter' */
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

    /* Sum: '<S426>/Sum1' incorporates:
     *  Constant: '<S426>/Constant'
     *  DiscreteFir: '<S426>/Discrete FIR Filter'
     *  Product: '<S426>/Product'
     */
    rtb_MatrixMultiply[i] = ((rtCP__Constant_Value_me[i + 3] * rtb_Product_k4[1]
      + rtCP__Constant_Value_me[i] * rtb_Product_k4[0]) +
      rtCP__Constant_Value_me[i + 6] * rtb_Product_k4[2]) + rtb_TSamp;
  }

  /* Switch: '<S426>/Switch1' */
  if (rtb_LogicalOperator1_j) {
    /* Switch: '<S426>/Switch1' incorporates:
     *  Constant: '<S431>/Constant'
     *  Delay generated from: '<S426>/Delay'
     *  Product: '<S431>/Matrix Multiply'
     *  Quat2Dcm: '<S431>/C-'
     *  Sum: '<S426>/Sum'
     */
    for (i = 0; i < 3; i++) {
      rtb_Product_k4[i] = ((rtb_C[i + 3] * 0.0 + rtb_C[i] * 0.0) + rtb_C[i + 6] *
                           9.81) + rtDW->Delay_3_DSTATE[i];
    }
  } else {
    /* Switch: '<S426>/Switch1' incorporates:
     *  UnitDelay: '<S426>/Unit Delay1'
     */
    rtb_Product_k4[0] = rtDW->UnitDelay1_DSTATE[0];
    rtb_Product_k4[1] = rtDW->UnitDelay1_DSTATE[1];
    rtb_Product_k4[2] = rtDW->UnitDelay1_DSTATE[2];
  }

  /* End of Switch: '<S426>/Switch1' */

  /* DiscreteFir: '<S426>/Discrete FIR Filter1' */
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

  /* End of DiscreteFir: '<S426>/Discrete FIR Filter1' */

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
  LookUp_real_T_real_T( &(rtb_DProdOut_m), rtCP__Constant5_Value,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Value, 2U);

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
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_b), rtCP__Constant5_Value_m,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Val_f, 2U);

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
  LookUp_real_T_real_T( &(rtb_GainDynamicLookup_k), rtCP__Constant5_Value_l,
                       rtb_Integrator_b, rtCP__Internalbreakpoints_Val_d, 2U);

  /* SampleTimeMath: '<S220>/TSamp'
   *
   * About '<S220>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp = rtb_Switch2_b * 100.0;

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
  rtb_Switch2_b = rtb_TSamp - rtDW->UD_DSTATE;

  /* Logic: '<S156>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S11>/Constant1'
   *  RelationalOperator: '<S156>/Relational Operator'
   *  RelationalOperator: '<S156>/Relational Operator1'
   */
  rtb_LogicalOperator1_j = ((rtb_Switch2_b >= 180.0) || (rtb_Switch2_b <= -180.0));

  /* Logic: '<S157>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Constant: '<S11>/Constant3'
   *  RelationalOperator: '<S157>/Relational Operator'
   *  RelationalOperator: '<S157>/Relational Operator1'
   */
  rtb_LogicalOperator_i = ((rtb_Divide_l >= 45.0) || (rtb_Divide_l <= -45.0));

  /* Product: '<S190>/IProd Out' incorporates:
   *  Logic: '<S11>/Logical Operator'
   *  Product: '<S153>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_GainDynamicLookup_k = (real_T)(!rtb_LogicalOperator_i &&
    !rtb_LogicalOperator1_j) * rtb_GainDynamicLookup_k * (real_T)
    rtDW->UnitDelay_DSTATE_n * rtb_Sum1;

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.control_deg =
    rtb_Integrator_fe;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.controlMoment_Nm =
    rtb_Product1_g;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.rateLimted_b =
    rtb_LogicalOperator1_j;
  rtY_controller_bus_f->innerLoop_bus.yawInnerLoop_bus.saturated_b =
    rtb_LogicalOperator_i;

  /* SampleTimeMath: '<S79>/TSamp'
   *
   * About '<S79>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Product1_g = rtb_Switch2_j * 100.0;

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
  rtb_LogicalOperator1_j = ((rtb_Switch2_b >= 90.0) || (rtb_Switch2_b <= -90.0));

  /* Logic: '<S87>/Logical Operator1' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant3'
   *  RelationalOperator: '<S87>/Relational Operator'
   *  RelationalOperator: '<S87>/Relational Operator1'
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
  rtb_LogicalOperator1 = ((rtb_Switch2_b >= 0.5) || (rtb_Switch2_b <= -0.5));

  /* Logic: '<S230>/Logical Operator1' incorporates:
   *  Constant: '<S225>/Constant2'
   *  Constant: '<S225>/Constant3'
   *  RelationalOperator: '<S230>/Relational Operator'
   *  RelationalOperator: '<S230>/Relational Operator1'
   */
  rtb_LogicalOperator_ni = ((rtb_Product1_j3 >= 0.4) || (rtb_Product1_j3 <= -0.4));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.rateCmd_rps =
    rtb_UkYk1_l;
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1;
  rtY_controller_bus_f->outerLoop_bus.pitchOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_ni;

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
  rtb_LogicalOperator1_i = ((rtb_Switch2_b >= 0.5) || (rtb_Switch2_b <= -0.5));

  /* Logic: '<S350>/Logical Operator1' incorporates:
   *  Constant: '<S227>/Constant2'
   *  Constant: '<S227>/Constant3'
   *  RelationalOperator: '<S350>/Relational Operator'
   *  RelationalOperator: '<S350>/Relational Operator1'
   */
  rtb_LogicalOperator_a = ((rtb_Sum_mo >= 0.4) || (rtb_Sum_mo <= -0.4));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.rateCmd_rps =
    rtb_Integrator_i;
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1_i;
  rtY_controller_bus_f->outerLoop_bus.yawOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_a;

  /* SampleTimeMath: '<S344>/TSamp'
   *
   * About '<S344>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_sqrt *= 100.0;

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
  rtb_Switch2_b = rtb_sqrt - rtDW->UD_DSTATE_a;

  /* Logic: '<S289>/Logical Operator1' incorporates:
   *  Constant: '<S226>/Constant'
   *  Constant: '<S226>/Constant1'
   *  RelationalOperator: '<S289>/Relational Operator'
   *  RelationalOperator: '<S289>/Relational Operator1'
   */
  rtb_LogicalOperator1_a2 = ((rtb_Switch2_b >= 5.0) || (rtb_Switch2_b <= -5.0));

  /* Logic: '<S290>/Logical Operator1' incorporates:
   *  Constant: '<S226>/Constant2'
   *  Constant: '<S226>/Constant3'
   *  RelationalOperator: '<S290>/Relational Operator'
   *  RelationalOperator: '<S290>/Relational Operator1'
   */
  rtb_LogicalOperator_j = ((rtb_Product2_a >= 2.0) || (rtb_Product2_a <= -2.0));

  /* BusCreator generated from: '<Root>/controller_bus' */
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.rateCmd_rps = rtb_Sin;
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.rateLimited_b =
    rtb_LogicalOperator1_a2;
  rtY_controller_bus_f->outerLoop_bus.rollOuterLoop_bus.saturated_b =
    rtb_LogicalOperator_j;

  /* BusCreator generated from: '<Root>/controller_bus' incorporates:
   *  Outport: '<Root>/controller_bus'
   */
  rtY_controller_bus_f->control_deg[0] = rtb_Switch_oo_idx_0;
  rtY_controller_bus_f->control_deg[1] = rtb_Switch_oo_idx_1;
  rtY_controller_bus_f->control_deg[2] = rtb_Switch_oo_idx_2;
  rtY_controller_bus_f->control_deg[3] = rtb_Switch_oo_idx_3;

  /* Product: '<S323>/IProd Out' incorporates:
   *  Constant: '<S226>/Constant4'
   *  Constant: '<S2>/Constant'
   *  Logic: '<S226>/Logical Operator'
   *  Product: '<S288>/Product'
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   *  Sum: '<S224>/Sum2'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Sum_mo = (real_T)(!rtb_LogicalOperator_j && !rtb_LogicalOperator1_a2) *
    2.0 * (real_T)rtDW->UnitDelay_DSTATE_n * (0.0 -
    rtb_TmpSignalConversionAtCInp_1);

  /* Product: '<S383>/IProd Out' incorporates:
   *  Constant: '<S227>/Constant4'
   *  Logic: '<S227>/Logical Operator'
   *  Product: '<S348>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Product2_a = (real_T)(!rtb_LogicalOperator_a && !rtb_LogicalOperator1_i) *
    0.4 * (real_T)rtDW->UnitDelay_DSTATE_n * rtb_Sum3;

  /* Product: '<S263>/IProd Out' incorporates:
   *  Constant: '<S225>/Constant4'
   *  Logic: '<S225>/Logical Operator'
   *  Product: '<S228>/Product'
   *  UnitDelay: '<S4>/Unit Delay'
   */
  rtb_Sum4_a *= (real_T)(!rtb_LogicalOperator_ni && !rtb_LogicalOperator1) * 0.4
    * (real_T)rtDW->UnitDelay_DSTATE_n;

  /* Product: '<S120>/IProd Out' incorporates:
   *  Logic: '<S10>/Logical Operator'
   *  Product: '<S83>/Product'
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

  /* State Transition Table: '<S411>/State Transition Table' incorporates:
   *  Quat2Angle: '<S429>/Quaternions to Rotation Angles'
   *  Sum: '<S413>/Sum1'
   *  UnaryMinus: '<S411>/Unary Minus'
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
          (rtb_wBdyEst_rps[2]) > 1.0) || ((fabs(rtb_TmpSignalConversionAtCInp_0)
          > 1.0) || (fabs(rtb_QuaternionstoDirectionCos_0) > 1.0))));
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
          (rtb_wBdyEst_rps[2]) > 1.0) || ((fabs(rtb_TmpSignalConversionAtCInp_0)
          > 1.0) || (fabs(rtb_QuaternionstoDirectionCos_0) > 1.0))));
      }
      break;
    }
  }

  /* End of State Transition Table: '<S411>/State Transition Table' */

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
  rtY_navigation_bus_d->phiEst_rad = rtb_TmpSignalConversionAtCInp_1;
  rtY_navigation_bus_d->thetaEst_rad = rtb_TmpSignalConversionAtCInp_0;
  rtY_navigation_bus_d->psiEst_rad = rtb_QuaternionstoDirectionCos_0;
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
  rtY_navigation_bus_d->dynPressureEst_Pa = rtb_Integrator_b;
  rtY_navigation_bus_d->xVelEst_mps = rtb_MathFunction_idx_0;
  rtY_navigation_bus_d->yVelEst_mps = rtb_MathFunction_idx_1;
  rtY_navigation_bus_d->zVelEst_mps = rtb_MathFunction_idx_2;
  rtY_navigation_bus_d->xPosEst_m = rtb_Sum5_idx_0;
  rtY_navigation_bus_d->yPosEst_m = rtb_Sum5_idx_1;
  rtY_navigation_bus_d->zPosEst_m = rtb_Sum5_idx_2;

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
  rtDW->Integrator_DSTATE += 0.01 * rtb_Sum_mo;

  /* Update for DiscreteIntegrator: '<S321>/Filter' */
  rtDW->Filter_DSTATE += 0.01 * rtb_Product_l;

  /* Update for Delay: '<S345>/Delay' */
  rtDW->icLoad = false;
  rtDW->Delay_DSTATE = rtb_Sin;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_15_DSTATE = rtb_MathFunction_idx_0;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_16_DSTATE = rtb_MathFunction_idx_1;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_17_DSTATE = rtb_MathFunction_idx_2;

  /* Update for DiscreteIntegrator: '<S123>/Integrator' */
  rtDW->Integrator_DSTATE_b += 0.01 * rtb_TmpSignalConversionAtCInp_2;

  /* Update for DiscreteIntegrator: '<S118>/Filter' */
  rtDW->Filter_DSTATE_p += 0.01 * rtb_Filter_c;

  /* Update for Delay: '<S150>/Delay' */
  rtDW->icLoad_k = false;
  rtDW->Delay_DSTATE_p = rtb_Integrator_g;

  /* Update for DiscreteIntegrator: '<S266>/Integrator' */
  rtDW->Integrator_DSTATE_g += 0.01 * rtb_Sum4_a;

  /* Update for DiscreteIntegrator: '<S261>/Filter' */
  rtDW->Filter_DSTATE_n += 0.01 * rtb_Product1_nd;

  /* Update for Delay: '<S285>/Delay' */
  rtDW->icLoad_a = false;
  rtDW->Delay_DSTATE_c = rtb_UkYk1_l;

  /* Update for DiscreteIntegrator: '<S52>/Integrator' incorporates:
   *  Product: '<S49>/IProd Out'
   */
  rtDW->Integrator_DSTATE_p += rtb_DProdOut * rtb_Switch2_b * 0.01;

  /* Update for DiscreteIntegrator: '<S47>/Filter' */
  rtDW->Filter_DSTATE_l += 0.01 * rtb_Filter_g;

  /* Update for Delay: '<S80>/Delay' */
  rtDW->icLoad_f = false;
  rtDW->Delay_DSTATE_f = rtb_PProdOut_b;

  /* Update for DiscreteIntegrator: '<S386>/Integrator' */
  rtDW->Integrator_DSTATE_l += 0.01 * rtb_Product2_a;

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
  rtDW->UnitDelay_18_DSTATE = rtb_Sum5_idx_0;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_19_DSTATE = rtb_Sum5_idx_1;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_20_DSTATE = rtb_Sum5_idx_2;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[0] = rtb_MatrixMultiply[0];

  /* Update for DiscreteTransferFcn: '<S409>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[1] = rtDW->DiscreteTransferFcn1_states[0];
  rtDW->DiscreteTransferFcn1_states[0] = DiscreteTransferFcn1_tmp[0];

  /* Update for DiscreteTransferFcn: '<S428>/Gyro Filter' */
  rtDW->GyroFilter_states[0] = rtb_TSamp_c5;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_12_DSTATE[0] = rtb_accelBias_mps2_idx_0;

  /* Update for DiscreteTransferFcn: '<S409>/Accel Filter' */
  rtDW->AccelFilter_states[0] = rtb_TSamp_gj;

  /* Update for DiscreteTransferFcn: '<S428>/Accel Filter' */
  rtDW->AccelFilter_states_l[0] = rtb_TSamp_ge;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[1] = rtb_MatrixMultiply[1];

  /* Update for DiscreteTransferFcn: '<S409>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[3] = rtDW->DiscreteTransferFcn1_states[2];
  rtDW->DiscreteTransferFcn1_states[2] = DiscreteTransferFcn1_tmp[1];

  /* Update for DiscreteTransferFcn: '<S428>/Gyro Filter' */
  rtDW->GyroFilter_states[1] = rtb_TSamp_d;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_12_DSTATE[1] = rtb_accelBias_mps2_idx_1;

  /* Update for DiscreteTransferFcn: '<S409>/Accel Filter' */
  rtDW->AccelFilter_states[1] = rtb_TSamp_jt;

  /* Update for DiscreteTransferFcn: '<S428>/Accel Filter' */
  rtDW->AccelFilter_states_l[1] = rtb_TSamp_i;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_13_DSTATE[2] = rtb_MatrixMultiply[2];

  /* Update for DiscreteTransferFcn: '<S409>/Discrete Transfer Fcn1' */
  rtDW->DiscreteTransferFcn1_states[5] = rtDW->DiscreteTransferFcn1_states[4];
  rtDW->DiscreteTransferFcn1_states[4] = DiscreteTransferFcn1_tmp[2];

  /* Update for DiscreteTransferFcn: '<S428>/Gyro Filter' */
  rtDW->GyroFilter_states[2] = rtb_TSamp_fe;

  /* Update for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_12_DSTATE[2] = rtb_accelBias_mps2_idx_2;

  /* Update for DiscreteTransferFcn: '<S409>/Accel Filter' */
  rtDW->AccelFilter_states[2] = rtb_TSamp_k;

  /* Update for DiscreteTransferFcn: '<S428>/Accel Filter' */
  rtDW->AccelFilter_states_l[2] = rtb_TSamp_h;

  /* Update for Delay generated from: '<S426>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  for (i = 0; i < 499; i++) {
    uIdx = (i + 1) * 3;
    rtDW->Delay_4_DSTATE[i * 3] = rtDW->Delay_4_DSTATE[uIdx];
    rtDW->Delay_4_DSTATE[i * 3 + 1] = rtDW->Delay_4_DSTATE[uIdx + 1];
    rtDW->Delay_4_DSTATE[i * 3 + 2] = rtDW->Delay_4_DSTATE[uIdx + 2];
  }

  rtDW->Delay_4_DSTATE[1497] = rtU_sensor_bus_e->wBdyMeas_rps[0];

  /* Update for UnitDelay: '<S426>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[0] = rtb_DiscreteFIRFilter[0];

  /* Update for Delay generated from: '<S426>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_4_DSTATE[1498] = rtU_sensor_bus_e->wBdyMeas_rps[1];

  /* Update for UnitDelay: '<S426>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[1] = rtb_DiscreteFIRFilter[1];

  /* Update for Delay generated from: '<S426>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_4_DSTATE[1499] = rtU_sensor_bus_e->wBdyMeas_rps[2];

  /* Update for UnitDelay: '<S426>/Unit Delay' */
  rtDW->UnitDelay_DSTATE[2] = rtb_DiscreteFIRFilter[2];

  /* Update for DiscreteFir: '<S426>/Discrete FIR Filter' */
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

  /* End of Update for DiscreteFir: '<S426>/Discrete FIR Filter' */

  /* Update for Delay generated from: '<S426>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  for (i = 0; i < 499; i++) {
    uIdx = (i + 1) * 3;
    rtDW->Delay_3_DSTATE[i * 3] = rtDW->Delay_3_DSTATE[uIdx];
    rtDW->Delay_3_DSTATE[i * 3 + 1] = rtDW->Delay_3_DSTATE[uIdx + 1];
    rtDW->Delay_3_DSTATE[i * 3 + 2] = rtDW->Delay_3_DSTATE[uIdx + 2];
  }

  rtDW->Delay_3_DSTATE[1497] = rtU_sensor_bus_e->fBdyMeas_mps2[0];

  /* Update for UnitDelay: '<S426>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[0] = rtb_accelBias_mps2_idx_0;

  /* Update for Delay generated from: '<S426>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_3_DSTATE[1498] = rtU_sensor_bus_e->fBdyMeas_mps2[1];

  /* Update for UnitDelay: '<S426>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[1] = rtb_accelBias_mps2_idx_1;

  /* Update for Delay generated from: '<S426>/Delay' incorporates:
   *  Inport: '<Root>/sensor_bus'
   */
  rtDW->Delay_3_DSTATE[1499] = rtU_sensor_bus_e->fBdyMeas_mps2[2];

  /* Update for UnitDelay: '<S426>/Unit Delay1' */
  rtDW->UnitDelay1_DSTATE[2] = rtb_accelBias_mps2_idx_2;

  /* Update for DiscreteFir: '<S426>/Discrete FIR Filter1' */
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

  /* End of Update for DiscreteFir: '<S426>/Discrete FIR Filter1' */

  /* Update for UnitDelay: '<S220>/UD'
   *
   * Block description for '<S220>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE = rtb_TSamp;

  /* Update for UnitDelay: '<S79>/UD'
   *
   * Block description for '<S79>/UD':
   *
   *  Store in Global RAM
   */
  rtDW->UD_DSTATE_k = rtb_Product1_g;

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
  rtDW->UD_DSTATE_a = rtb_sqrt;
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

  /* InitializeConditions for UnitDelay generated from: '<S408>/Unit Delay' */
  rtDW->UnitDelay_2_DSTATE[0] = 0.7071;
  rtDW->UnitDelay_2_DSTATE[1] = 0.0;
  rtDW->UnitDelay_2_DSTATE[2] = 0.7071;
  rtDW->UnitDelay_2_DSTATE[3] = 0.0;

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

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter' */
  rtDW->DiscreteFIRFilter_circBuf = 0;

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter1' */
  rtDW->DiscreteFIRFilter1_circBuf = 0;

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter' */
  memset(&rtDW->DiscreteFIRFilter_states[0], 0, 297U * sizeof(real_T));

  /* InitializeConditions for DiscreteFir: '<S426>/Discrete FIR Filter1' */
  memset(&rtDW->DiscreteFIRFilter1_states[0], 0, 297U * sizeof(real_T));

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
