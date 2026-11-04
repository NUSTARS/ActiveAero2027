#include "autocodePlant_feedback.h"
#include <stddef.h>
static autocodePlant_FeedbackCallback autocodePlant_feedback;
void autocodePlant_SetFeedbackCallback(autocodePlant_FeedbackCallback callback)
{
  autocodePlant_feedback = callback;
}

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: autocodePlant.c
 *
 * Code generated for Simulink model 'autocodePlant'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Thu Oct 29 16:32:54 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M7 (MPS2)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "autocodePlant.h"
#include <math.h>
#include "rt_powd_snf.h"
#include "rt_nonfinite.h"
#include "rt_modd_snf.h"
#include "rt_remd_snf.h"
#include <string.h>
#include "rt_atan2d_snf.h"
#include "rt_mldivide_U1d3x3_U2d_9O8lG8ax.h"
#include "rt_assert.h"
#include "rtwtypes.h"
#include "autocodePlant_types.h"
#include "rt_nrand_Upu32_Yd_f_pw_snf.h"
#include "autocodePlant_private.h"
#include "plook_bincpa.h"
#include "intrp2d_la_pw.h"
#include "plook_binx.h"
#include "intrp3d_l_pw.h"
#include "look2_binlcpw.h"
#include "look2_binlxpw.h"
#include "mul_s32_sat.h"
#include "look1_binlcpw.h"

const plant_bus autocodePlant_rtZplant_bus = { { { 0.0, 0.0, 0.0 },/* gravityForceBdy_N */
    0.0,                               /* temp_K */
    0.0,                               /* a_mps */
    0.0,                               /* pressure_Pa */
    0.0,                               /* rho_kgpm3 */
    false,                             /* onRail_b */

    { 0.0, 0.0, 0.0 },                 /* airspeed_mps */

    { 0.0, 0.0, 0.0 },                 /* windBdy_mps */

    { 0.0, 0.0, 0.0 }                  /* airW_rps */
  },                                   /* enviroment_bus */

  { { 0.0, 0.0, 0.0 },                 /* aeroMoment_Nm */

    { 0.0, 0.0, 0.0 },                 /* aeroForce_N */

    { { 0.0, 0.0, 0.0 },               /* finMoment_Nm */

      { 0.0, 0.0, 0.0 },               /* finForce_N */
      0.0,                             /* aoa_deg */
      0.0,                             /* liftSign_na */

      { 0.0, 0.0, 0.0 }                /* airspeedFin_mps */
    },                                 /* fin1_bus */

    { { 0.0, 0.0, 0.0 },               /* finMoment_Nm */

      { 0.0, 0.0, 0.0 },               /* finForce_N */
      0.0,                             /* aoa_deg */
      0.0,                             /* liftSign_na */

      { 0.0, 0.0, 0.0 }                /* airspeedFin_mps */
    },                                 /* fin2_bus */

    { { 0.0, 0.0, 0.0 },               /* finMoment_Nm */

      { 0.0, 0.0, 0.0 },               /* finForce_N */
      0.0,                             /* aoa_deg */
      0.0,                             /* liftSign_na */

      { 0.0, 0.0, 0.0 }                /* airspeedFin_mps */
    },                                 /* fin3_bus */

    { { 0.0, 0.0, 0.0 },               /* finMoment_Nm */

      { 0.0, 0.0, 0.0 },               /* finForce_N */
      0.0,                             /* aoa_deg */
      0.0,                             /* liftSign_na */

      { 0.0, 0.0, 0.0 }                /* airspeedFin_mps */
    },                                 /* fin4_bus */

    { { 0.0, 0.0, 0.0 },               /* bodyMoment_Nm */

      { 0.0, 0.0, 0.0 },               /* bodyForce_N */
      0.0                              /* aoa_deg */
    }                                  /* body_bus */
  },                                   /* aero_bus */

  { { 0.0, 0.0, 0.0 },                 /* posNed_m */

    { 0.0, 0.0, 0.0, 0.0 },            /* q_na */

    { 0.0, 0.0, 0.0 },                 /* velBdy_mps */

    { 0.0, 0.0, 0.0 },                 /* wBdy_rps */

    { 0.0, 0.0, 0.0 },                 /* accBdy_mps2 */

    { 0.0, 0.0, 0.0 }                  /* wDotBdy_rps2 */
  }                                    /* eom_bus */
};

const sensor_bus autocodePlant_rtZsensor_bus = { { { 0.0, 0.0, 0.0 },/* gyroBiasTrue_rps */

    { 0.0, 0.0, 0.0 }                  /* accBiasTrue_mps2 */
  },                                   /* truth_bus */

  { 0.0, 0.0, 0.0 },                   /* fBdyMeas_mps2 */

  { 0.0, 0.0, 0.0 },                   /* wBdyMeas_rps */

  { 0.0, 0.0, 0.0 },                   /* magBdyMeas_nT */
  0.0                                  /* baroMeas_Pa */
};

/* Projection for root system: '<Root>' */
void autocodePlant_projection(RT_MODEL_autocodePlant_T *const autocodePlant_M)
{
  X_autocodePlant_T *autocodePlant_X = autocodePlant_M->contStates;
  real_T uDOFQuaternion_CSTATE_tmp;

  /* Projection for EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)' */
  uDOFQuaternion_CSTATE_tmp = 1.0 / sqrt
    (((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
       autocodePlant_X->uDOFQuaternion_CSTATE[9] +
       autocodePlant_X->uDOFQuaternion_CSTATE[10] *
       autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[11] *
      autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
     autocodePlant_X->uDOFQuaternion_CSTATE[12] *
     autocodePlant_X->uDOFQuaternion_CSTATE[12]);
  autocodePlant_X->uDOFQuaternion_CSTATE[9] *= uDOFQuaternion_CSTATE_tmp;
  autocodePlant_X->uDOFQuaternion_CSTATE[10] *= uDOFQuaternion_CSTATE_tmp;
  autocodePlant_X->uDOFQuaternion_CSTATE[11] *= uDOFQuaternion_CSTATE_tmp;
  autocodePlant_X->uDOFQuaternion_CSTATE[12] *= uDOFQuaternion_CSTATE_tmp;
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  RT_MODEL_autocodePlant_T *const autocodePlant_M, real_T
  autocodePlant_U_control_deg[4], sensor_bus *autocodePlant_Y_sensor_bus_i,
  plant_bus *autocodePlant_Y_plant_bus_e)
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 29;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  autocodePlant_derivatives(autocodePlant_M);

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  autocodePlant_step(autocodePlant_M, autocodePlant_U_control_deg,
                     autocodePlant_Y_sensor_bus_i, autocodePlant_Y_plant_bus_e);
  autocodePlant_derivatives(autocodePlant_M);

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  autocodePlant_step(autocodePlant_M, autocodePlant_U_control_deg,
                     autocodePlant_Y_sensor_bus_i, autocodePlant_Y_plant_bus_e);
  autocodePlant_derivatives(autocodePlant_M);

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  autocodePlant_step(autocodePlant_M, autocodePlant_U_control_deg,
                     autocodePlant_Y_sensor_bus_i, autocodePlant_Y_plant_bus_e);
  autocodePlant_derivatives(autocodePlant_M);

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  autocodePlant_step(autocodePlant_M, autocodePlant_U_control_deg,
                     autocodePlant_Y_sensor_bus_i, autocodePlant_Y_plant_bus_e);
  autocodePlant_projection(autocodePlant_M);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void autocodePlant_step(RT_MODEL_autocodePlant_T *const autocodePlant_M, real_T
  autocodePlant_U_control_deg[4], sensor_bus *autocodePlant_Y_sensor_bus_i,
  plant_bus *autocodePlant_Y_plant_bus_e)
{
  B_autocodePlant_T *autocodePlant_B = autocodePlant_M->blockIO;
  DW_autocodePlant_T *autocodePlant_DW = autocodePlant_M->dwork;
  X_autocodePlant_T *autocodePlant_X = autocodePlant_M->contStates;
  XDis_autocodePlant_T *autocodePlant_XDis = ((XDis_autocodePlant_T *)
    autocodePlant_M->contStateDisabled);

  /* local block i/o variables */
  real_T rtb_uDLookupTable;
  if (rtmIsMajorTimeStep(autocodePlant_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&autocodePlant_M->solverInfo,
                          ((autocodePlant_M->Timing.clockTick0+1)*
      autocodePlant_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(autocodePlant_M)) {
    autocodePlant_M->Timing.t[0] = rtsiGetT(&autocodePlant_M->solverInfo);
  }

  {
    real_T rtb_QuaternionstoDirectionCosin[9];
    real_T rtb_Add[6];
    real_T rtb_ElementProduct[6];
    real_T Gdependent[3];
    real_T biasnoise_d[3];
    real_T rtb_MathFunction[3];
    real_T rtb_Product6_f[3];
    real_T rtb_Product_fn[3];
    real_T rtb_Product_ne[3];
    real_T rtb_Sum1_b[3];
    real_T rtb_Sum1_lp[3];
    real_T rtb_Sum1_ny[3];
    real_T rtb_Sum1_p2[3];
    real_T rtb_Sum_aw[3];
    real_T rtb_Sum_dj[3];
    real_T rtb_Sum_el[3];
    real_T rtb_Sum_hp[3];
    real_T rtb_Sum_k[3];
    real_T rtb_Sum_mu[3];
    real_T rtb_Sum_n3[3];
    real_T rtb_VectorConcatenate[3];
    real_T rtb_VectorConcatenate_h[3];
    real_T rtb_ZeroOrderHold_a[3];
    real_T rtb_ZeroOrderHold_c[3];
    real_T rtb_finMomentArm_m[3];
    real_T rtb_gravityForceBdy_N[3];
    real_T rtb_posNed_m[3];
    real_T rtb_velBdy_mps[3];
    real_T rtb_wBdy_rps[3];
    real_T rtb_Product1_l3[2];
    real_T Merge1;
    real_T Merge_n;
    real_T rtb_FlatEarthtoLLA_o1_idx_0;
    real_T rtb_Gain_el;
    real_T rtb_Gain_l;
    real_T rtb_Gain_oa;
    real_T rtb_Lw_idx_1;
    real_T rtb_Product1_hx;
    real_T rtb_Product1_jv;
    real_T rtb_Product2_ml;
    real_T rtb_Product3_ax;
    real_T rtb_Product_h5;
    real_T rtb_Sign1;
    real_T rtb_Sign1_e;
    real_T rtb_Sign1_i;
    real_T rtb_Sum;
    real_T rtb_Sum1_n;
    real_T rtb_Sum1_oo;
    real_T rtb_Sum1_ox;
    real_T rtb_Sum2_fl;
    real_T rtb_Switch_d_idx_0;
    real_T rtb_Switch_d_idx_1;
    real_T rtb_Switch_d_idx_2;
    real_T rtb_TT0gLR;
    real_T rtb_TmpSignalConversionAtProd_0;
    real_T rtb_TrigonometricFunction_o2_o;
    real_T rtb_UnaryMinus1_k4;
    real_T rtb_UnaryMinus1_o;
    real_T rtb_UnaryMinus_a;
    real_T rtb_a;
    real_T rtb_pi3;
    real_T rtb_pi3_tmp;
    real_T rtb_q_na_idx_0;
    real_T rtb_q_na_idx_1;
    real_T rtb_q_na_idx_2;
    real_T rtb_q_na_idx_3;
    real_T rtb_sincos_o1_idx_0;
    real_T rtb_sincos_o2_idx_0;
    real_T rtb_truth_bus_accBiasTrue_mps2_;
    real_T rtb_truth_bus_accBiasTrue_mps_0;
    real_T rtb_truth_bus_accBiasTrue_mps_1;
    real_T rtb_truth_bus_gyroBiasTrue_rp_0;
    real_T rtb_truth_bus_gyroBiasTrue_rp_1;
    real_T rtb_truth_bus_gyroBiasTrue_rps_;
    int32_T Merge_b_tmp;
    int32_T i;
    int32_T rtb_Sum2_ct;
    int32_T s227_iter;
    int32_T s268_iter;
    uint32_T bpIndices[3];
    uint32_T bpIndices_0[3];
    uint32_T bpIndices_1[3];
    uint32_T bpIndices_2[3];
    uint32_T bpIndices_3[3];
    uint32_T bpIndices_4[3];
    uint32_T bpIndices_5[3];
    uint32_T bpIndices_6[3];
    uint32_T bpIndex[2];
    int8_T rtAction;
    int8_T rtPrevAction;
    uint8_T ForIterator_IterationMarker[6];
    boolean_T rtb_Compare_n;
    boolean_T rtb_RelationalOperator;
    boolean_T rtb_max_relop_c;
    boolean_T rtb_min_relop_n;
    boolean_T tmp;

    /* Outputs for Enabled SubSystem: '<S208>/Convert from geodetic to  spherical coordinates' incorporates:
     *  EnablePort: '<S220>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S122>/Hugw(s)' incorporates:
     *  EnablePort: '<S135>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hrgw' incorporates:
     *  EnablePort: '<S134>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S122>/Hvgw(s)' incorporates:
     *  EnablePort: '<S136>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hqgw' incorporates:
     *  EnablePort: '<S133>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S122>/Hwgw(s)' incorporates:
     *  EnablePort: '<S137>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hpgw' incorporates:
     *  EnablePort: '<S132>/Enable'
     */
    tmp = (rtmIsMajorTimeStep(autocodePlant_M) &&
           autocodePlant_M->Timing.TaskCounters.TID[1] == 0);

    /* End of Outputs for SubSystem: '<S121>/Hpgw' */
    /* End of Outputs for SubSystem: '<S122>/Hwgw(s)' */
    /* End of Outputs for SubSystem: '<S121>/Hqgw' */
    /* End of Outputs for SubSystem: '<S122>/Hvgw(s)' */
    /* End of Outputs for SubSystem: '<S121>/Hrgw' */
    /* End of Outputs for SubSystem: '<S122>/Hugw(s)' */
    /* End of Outputs for SubSystem: '<S208>/Convert from geodetic to  spherical coordinates' */
    if (tmp) {
      /* Sum: '<S175>/bias' incorporates:
       *  Constant: '<S175>/  '
       *  DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn'
       *  DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn2'
       */
      rtb_ZeroOrderHold_a[0] = autocodePlant_DW->DiscreteTransferFcn_states +
        0.007805089418666159;
      rtb_ZeroOrderHold_a[1] = autocodePlant_DW->DiscreteTransferFcn1_states +
        0.007805089418666159;
      rtb_ZeroOrderHold_a[2] = autocodePlant_DW->DiscreteTransferFcn2_states +
        0.007805089418666159;

      /* Sum: '<S173>/bias' incorporates:
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn2'
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn3'
       */
      rtb_ZeroOrderHold_c[0] = autocodePlant_DW->DiscreteTransferFcn2_states_k -
        0.01056034519496827;
      rtb_ZeroOrderHold_c[1] = autocodePlant_DW->DiscreteTransferFcn1_states_a -
        0.01056034519496827;
      rtb_ZeroOrderHold_c[2] = autocodePlant_DW->DiscreteTransferFcn3_states -
        0.01056034519496827;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S175>/  '
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn2'
       *  DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn'
       *  Sum: '<S173>/bias'
       *  Sum: '<S175>/bias'
       */
      rtb_truth_bus_gyroBiasTrue_rps_ =
        autocodePlant_DW->DiscreteTransferFcn_states + 0.007805089418666159;
      rtb_truth_bus_accBiasTrue_mps2_ =
        autocodePlant_DW->DiscreteTransferFcn2_states_k - 0.01056034519496827;

      /* Sum: '<S173>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn2'
       *  Gain: '<S179>/Output'
       *  RandomNumber: '<S179>/White Noise'
       *  Sum: '<S173>/bias'
       */
      autocodePlant_B->biasnoise[0] =
        (autocodePlant_DW->DiscreteTransferFcn2_states_k - 0.01056034519496827)
        + 0.0073574999999999995 * autocodePlant_DW->NextOutput;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S175>/  '
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn1'
       *  Sum: '<S173>/bias'
       *  Sum: '<S175>/bias'
       */
      rtb_truth_bus_gyroBiasTrue_rp_0 =
        autocodePlant_DW->DiscreteTransferFcn1_states + 0.007805089418666159;
      rtb_truth_bus_accBiasTrue_mps_0 =
        autocodePlant_DW->DiscreteTransferFcn1_states_a - 0.01056034519496827;

      /* Sum: '<S173>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn1'
       *  Gain: '<S179>/Output'
       *  RandomNumber: '<S179>/White Noise'
       *  Sum: '<S173>/bias'
       */
      autocodePlant_B->biasnoise[1] =
        (autocodePlant_DW->DiscreteTransferFcn1_states_a - 0.01056034519496827)
        + 0.0073574999999999995 * autocodePlant_DW->NextOutput;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S175>/  '
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn3'
       *  DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn2'
       *  Sum: '<S173>/bias'
       *  Sum: '<S175>/bias'
       */
      rtb_truth_bus_gyroBiasTrue_rp_1 =
        autocodePlant_DW->DiscreteTransferFcn2_states + 0.007805089418666159;
      rtb_truth_bus_accBiasTrue_mps_1 =
        autocodePlant_DW->DiscreteTransferFcn3_states - 0.01056034519496827;

      /* Sum: '<S173>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn3'
       *  Gain: '<S179>/Output'
       *  RandomNumber: '<S179>/White Noise'
       *  Sum: '<S173>/bias'
       */
      autocodePlant_B->biasnoise[2] =
        (autocodePlant_DW->DiscreteTransferFcn3_states - 0.01056034519496827) +
        0.0073574999999999995 * autocodePlant_DW->NextOutput;

      /* Delay: '<S6>/Delay' */
      autocodePlant_B->Delay = autocodePlant_DW->Delay_DSTATE[0];
    }

    /* EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)' */
    rtb_velBdy_mps[0] = autocodePlant_X->uDOFQuaternion_CSTATE[0];
    rtb_velBdy_mps[1] = autocodePlant_X->uDOFQuaternion_CSTATE[1];
    rtb_velBdy_mps[2] = autocodePlant_X->uDOFQuaternion_CSTATE[2];
    rtb_posNed_m[0] = autocodePlant_X->uDOFQuaternion_CSTATE[3];
    rtb_posNed_m[1] = autocodePlant_X->uDOFQuaternion_CSTATE[4];
    rtb_posNed_m[2] = autocodePlant_X->uDOFQuaternion_CSTATE[5];
    rtb_wBdy_rps[0] = autocodePlant_X->uDOFQuaternion_CSTATE[6];
    rtb_wBdy_rps[1] = autocodePlant_X->uDOFQuaternion_CSTATE[7];
    rtb_wBdy_rps[2] = autocodePlant_X->uDOFQuaternion_CSTATE[8];
    rtb_q_na_idx_0 = autocodePlant_X->uDOFQuaternion_CSTATE[9];
    rtb_q_na_idx_1 = autocodePlant_X->uDOFQuaternion_CSTATE[10];
    rtb_q_na_idx_2 = autocodePlant_X->uDOFQuaternion_CSTATE[11];
    rtb_q_na_idx_3 = autocodePlant_X->uDOFQuaternion_CSTATE[12];

    /* RelationalOperator: '<S98>/Compare' incorporates:
     *  Constant: '<S98>/Constant'
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    rtb_Compare_n = (-autocodePlant_X->uDOFQuaternion_CSTATE[5] <= 4.0);

    /* Sqrt: '<S114>/sqrt' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S115>/Product'
     *  Product: '<S115>/Product1'
     *  Product: '<S115>/Product2'
     *  Product: '<S115>/Product3'
     *  Sum: '<S115>/Sum'
     */
    rtb_TT0gLR = sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
                        autocodePlant_X->uDOFQuaternion_CSTATE[9] +
                        autocodePlant_X->uDOFQuaternion_CSTATE[10] *
                        autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
                       autocodePlant_X->uDOFQuaternion_CSTATE[11] *
                       autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
                      autocodePlant_X->uDOFQuaternion_CSTATE[12] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[12]);

    /* Product: '<S110>/Product2' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Sign1_e = autocodePlant_X->uDOFQuaternion_CSTATE[11] / rtb_TT0gLR;

    /* Product: '<S110>/Product3' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Sign1 = autocodePlant_X->uDOFQuaternion_CSTATE[12] / rtb_TT0gLR;

    /* Product: '<S110>/Product1' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Gain_l = autocodePlant_X->uDOFQuaternion_CSTATE[10] / rtb_TT0gLR;

    /* Product: '<S110>/Product' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_TT0gLR = autocodePlant_X->uDOFQuaternion_CSTATE[9] / rtb_TT0gLR;

    /* Product: '<S113>/Product2' incorporates:
     *  Product: '<S112>/Product2'
     */
    rtb_Sum1_oo = rtb_TT0gLR * rtb_Gain_l;

    /* Product: '<S113>/Product3' incorporates:
     *  Product: '<S112>/Product3'
     */
    rtb_pi3 = rtb_Sign1_e * rtb_Sign1;

    /* Product: '<S113>/Product5' incorporates:
     *  Constant: '<S4>/gNed_mps2'
     *  Gain: '<S113>/Gain1'
     *  Product: '<S113>/Product2'
     *  Product: '<S113>/Product3'
     *  Sum: '<S113>/Sum2'
     */
    rtb_a = (rtb_pi3 - rtb_Sum1_oo) * 2.0 * 0.0;

    /* Product: '<S111>/Product7' incorporates:
     *  Product: '<S112>/Product7'
     */
    rtb_TrigonometricFunction_o2_o = rtb_Sign1 * rtb_Sign1;

    /* Product: '<S111>/Product' incorporates:
     *  Product: '<S112>/Product'
     */
    rtb_Sign1_i = rtb_Gain_l * rtb_Sign1_e;

    /* Product: '<S111>/Product1' incorporates:
     *  Product: '<S112>/Product1'
     */
    rtb_Gain_oa = rtb_TT0gLR * rtb_Sign1;

    /* Product: '<S111>/Product3' incorporates:
     *  Product: '<S113>/Product'
     */
    rtb_Sign1 *= rtb_Gain_l;

    /* Product: '<S111>/Product2' incorporates:
     *  Product: '<S113>/Product1'
     */
    rtb_TT0gLR *= rtb_Sign1_e;

    /* Product: '<S111>/Product6' incorporates:
     *  Product: '<S113>/Product7'
     */
    rtb_Sign1_e *= rtb_Sign1_e;

    /* Gain: '<S4>/mass' incorporates:
     *  Constant: '<S111>/Constant'
     *  Constant: '<S4>/gNed_mps2'
     *  Gain: '<S111>/Gain'
     *  Gain: '<S111>/Gain1'
     *  Gain: '<S111>/Gain2'
     *  Product: '<S111>/Product'
     *  Product: '<S111>/Product1'
     *  Product: '<S111>/Product2'
     *  Product: '<S111>/Product3'
     *  Product: '<S111>/Product4'
     *  Product: '<S111>/Product5'
     *  Product: '<S111>/Product6'
     *  Product: '<S111>/Product7'
     *  Product: '<S111>/Product8'
     *  Sum: '<S111>/Sum'
     *  Sum: '<S111>/Sum1'
     *  Sum: '<S111>/Sum2'
     *  Sum: '<S111>/Sum3'
     */
    rtb_gravityForceBdy_N[0] = ((((0.5 - rtb_Sign1_e) -
      rtb_TrigonometricFunction_o2_o) * 2.0 * 0.0 + (rtb_Sign1_i + rtb_Gain_oa) *
      2.0 * 0.0) + (rtb_Sign1 - rtb_TT0gLR) * 2.0 * 9.81) * 17.5;

    /* Sum: '<S112>/Sum3' incorporates:
     *  Constant: '<S112>/Constant'
     *  Product: '<S112>/Product6'
     *  Sum: '<S113>/Sum3'
     */
    rtb_Gain_l = 0.5 - rtb_Gain_l * rtb_Gain_l;

    /* Gain: '<S4>/mass' incorporates:
     *  Constant: '<S4>/gNed_mps2'
     *  Gain: '<S112>/Gain'
     *  Gain: '<S112>/Gain1'
     *  Gain: '<S112>/Gain2'
     *  Gain: '<S113>/Gain'
     *  Gain: '<S113>/Gain2'
     *  Product: '<S112>/Product4'
     *  Product: '<S112>/Product5'
     *  Product: '<S112>/Product8'
     *  Product: '<S113>/Product4'
     *  Product: '<S113>/Product8'
     *  Sum: '<S112>/Sum'
     *  Sum: '<S112>/Sum1'
     *  Sum: '<S112>/Sum2'
     *  Sum: '<S112>/Sum3'
     *  Sum: '<S113>/Sum'
     *  Sum: '<S113>/Sum1'
     *  Sum: '<S113>/Sum3'
     */
    rtb_gravityForceBdy_N[1] = (((rtb_Gain_l - rtb_TrigonometricFunction_o2_o) *
      2.0 * 0.0 + (rtb_Sign1_i - rtb_Gain_oa) * 2.0 * 0.0) + (rtb_Sum1_oo +
      rtb_pi3) * 2.0 * 9.81) * 17.5;
    rtb_gravityForceBdy_N[2] = (((rtb_Sign1 + rtb_TT0gLR) * 2.0 * 0.0 + rtb_a) +
      (rtb_Gain_l - rtb_Sign1_e) * 2.0 * 9.81) * 17.5;

    /* UnitConversion: '<S123>/Unit Conversion' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  UnaryMinus: '<S101>/Unary Minus'
     */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    rtb_Gain_l = 3.280839895013123 * -autocodePlant_X->uDOFQuaternion_CSTATE[5];

    /* Saturate: '<S156>/Limit Function 10ft to 1000ft' */
    if (rtb_Gain_l > 1000.0) {
      rtb_Sum1_oo = 1000.0;
    } else if (rtb_Gain_l < 10.0) {
      rtb_Sum1_oo = 10.0;
    } else {
      rtb_Sum1_oo = rtb_Gain_l;
    }

    /* End of Saturate: '<S156>/Limit Function 10ft to 1000ft' */

    /* Gain: '<S128>/Lw' */
    rtb_Lw_idx_1 = autocodePlant_ConstB.UnitConversion_k;

    /* Interpolation_n-D: '<S138>/Medium//High Altitude Intensity' incorporates:
     *  PreLookup: '<S138>/PreLook-Up Index Search  (altitude)'
     *  PreLookup: '<S138>/PreLook-Up Index Search  (prob of exceed)'
     *  Sqrt: '<S106>/a'
     */
    bpIndex[0] = plook_bincpa(rtb_Gain_l, rtCP__PreLookUpIndexSearchaltit, 11U,
      &rtb_a, &autocodePlant_DW->PreLookUpIndexSearchaltitude_DW);
    rtb_Product1_l3[0] = rtb_a;
    rtb_Product1_l3[1] = autocodePlant_ConstB.PreLookUpIndexSearchprobofe;
    bpIndex[1] = autocodePlant_ConstB.PreLookUpIndexSearchprobo_j;
    rtb_a = intrp2d_la_pw(bpIndex, rtb_Product1_l3,
                          rtCP__MediumHighAltitudeIntensi, 12U,
                          rtCP__MediumHighAltitudeInten_o);
    if (tmp) {
      /* Product: '<S131>/Product' incorporates:
       *  RandomNumber: '<S131>/White Noise'
       */
      autocodePlant_B->Product[0] = autocodePlant_ConstB.Divide[0] *
        autocodePlant_DW->NextOutput_d[0];
      autocodePlant_B->Product[1] = autocodePlant_ConstB.Divide[1] *
        autocodePlant_DW->NextOutput_d[1];
      autocodePlant_B->Product[2] = autocodePlant_ConstB.Divide[2] *
        autocodePlant_DW->NextOutput_d[2];
      autocodePlant_B->Product[3] = autocodePlant_ConstB.Divide[3] *
        autocodePlant_DW->NextOutput_d[3];
    }

    /* DotProduct: '<S101>/Dot Product' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_TT0gLR = (autocodePlant_X->uDOFQuaternion_CSTATE[0] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[0] +
                  autocodePlant_X->uDOFQuaternion_CSTATE[1] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[1]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[2] *
      autocodePlant_X->uDOFQuaternion_CSTATE[2];

    /* Switch: '<S116>/Switch' incorporates:
     *  Constant: '<S116>/Constant4'
     *  Constant: '<S116>/Constant5'
     *  DotProduct: '<S101>/Dot Product'
     */
    /* Unit Conversion - from: m/s to: ft/s
       Expression: output = (3.28084*input) + (0) */
    if (rtb_TT0gLR >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* UnitConversion: '<S129>/Unit Conversion' incorporates:
     *  Constant: '<S116>/Constant'
     *  DotProduct: '<S101>/Dot Product'
     *  MinMax: '<S116>/Max'
     *  Product: '<S116>/Product'
     *  Sqrt: '<S101>/Sqrt'
     *  Switch: '<S116>/Switch'
     */
    rtb_TT0gLR = sqrt((real_T)i * fmax(1.0E-6, rtb_TT0gLR)) * 3.280839895013123;

    /* Outputs for Enabled SubSystem: '<S121>/Hpgw' incorporates:
     *  EnablePort: '<S132>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hpgw_MODE) {
      (void) memset(&(autocodePlant_XDis->pgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S132>/pgw_p' */
      autocodePlant_X->pgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->pgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hpgw_MODE = true;
    }

    if (autocodePlant_DW->Hpgw_MODE) {
      /* Fcn: '<S132>/sqrt(0.8//V)' */
      rtb_Product3_ax = sqrt(0.8 / rtb_TT0gLR);

      /* Product: '<S132>/w3' */
      rtb_Sign1 = rtb_TT0gLR * autocodePlant_ConstB.w4;

      /* Product: '<S132>/w' incorporates:
       *  Fcn: '<S132>/sqrt(0.8//V)'
       *  Gain: '<S128>/Lw'
       *  Integrator: '<S132>/pgw_p'
       *  Math: '<S132>/L^1//3'
       *  Product: '<S132>/Lug//V1'
       *  Product: '<S132>/w1'
       *  Product: '<S132>/w2'
       *  Sum: '<S132>/Sum'
       */
      autocodePlant_B->w_p[0] = (rtb_Product3_ax / rt_powd_snf(rtb_Sum1_oo,
        0.3333333333333333) * autocodePlant_ConstB.u16 *
        autocodePlant_B->Product[3] - autocodePlant_X->pgw_p_CSTATE[0]) *
        rtb_Sign1;

      /* Math: '<S132>/L^1//3' */
      if (rtb_Lw_idx_1 < 0.0) {
        rtb_pi3 = -rt_powd_snf(-rtb_Lw_idx_1, 0.3333333333333333);
      } else {
        rtb_pi3 = rt_powd_snf(rtb_Lw_idx_1, 0.3333333333333333);
      }

      /* Product: '<S132>/w' incorporates:
       *  Fcn: '<S132>/sqrt(0.8//V)'
       *  Integrator: '<S132>/pgw_p'
       *  Product: '<S132>/Lug//V1'
       *  Product: '<S132>/w1'
       *  Product: '<S132>/w2'
       *  Sum: '<S132>/Sum'
       */
      autocodePlant_B->w_p[1] = (rtb_Product3_ax / rtb_pi3 *
        autocodePlant_ConstB.u16 * autocodePlant_B->Product[3] -
        autocodePlant_X->pgw_p_CSTATE[1]) * rtb_Sign1;

      /* Product: '<S132>/sigma_w' incorporates:
       *  Integrator: '<S132>/pgw_p'
       */
      autocodePlant_B->sigma_w[0] = autocodePlant_ConstB.sigma_wg *
        autocodePlant_X->pgw_p_CSTATE[0];
      autocodePlant_B->sigma_w[1] = rtb_a * autocodePlant_X->pgw_p_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S121>/Hpgw' */

    /* Outputs for Enabled SubSystem: '<S122>/Hwgw(s)' incorporates:
     *  EnablePort: '<S137>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hwgws_MODE) {
      (void) memset(&(autocodePlant_XDis->wg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S137>/wg_p1' */
      autocodePlant_X->wg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S137>/wg_p2' */
      autocodePlant_X->wg_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S137>/wg_p1' */
      autocodePlant_X->wg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S137>/wg_p2' */
      autocodePlant_X->wg_p2_CSTATE[1] = 0.0;
      autocodePlant_DW->Hwgws_MODE = true;
    }

    if (autocodePlant_DW->Hwgws_MODE) {
      /* Product: '<S137>/Lwg//V' incorporates:
       *  Gain: '<S128>/Lw'
       */
      rtb_pi3 = rtb_Sum1_oo / rtb_TT0gLR;

      /* Product: '<S137>/w' incorporates:
       *  Gain: '<S137>/1//pi'
       *  Integrator: '<S137>/wg_p1'
       *  Product: '<S137>/Lug//V1'
       *  Sqrt: '<S137>/sqrt1'
       *  Sum: '<S137>/Sum'
       */
      rtb_Sign1 = (sqrt(0.3183098861837907 * rtb_pi3) * autocodePlant_B->
                   Product[2] - autocodePlant_X->wg_p1_CSTATE[0]) / rtb_pi3;
      autocodePlant_B->w[0] = rtb_Sign1;

      /* Product: '<S137>/w ' incorporates:
       *  Integrator: '<S137>/wg_p1'
       *  Integrator: '<S137>/wg_p2'
       *  Product: '<S137>/Lwg//V '
       *  Sum: '<S137>/Sum1'
       */
      autocodePlant_B->w_h[0] = (rtb_Sign1 * autocodePlant_ConstB.sqrt_g *
        rtb_pi3 + (autocodePlant_X->wg_p1_CSTATE[0] -
                   autocodePlant_X->wg_p2_CSTATE[0])) / rtb_pi3;

      /* Product: '<S137>/Lwg//V' */
      rtb_pi3 = rtb_Lw_idx_1 / rtb_TT0gLR;

      /* Product: '<S137>/w' incorporates:
       *  Gain: '<S137>/1//pi'
       *  Integrator: '<S137>/wg_p1'
       *  Product: '<S137>/Lug//V1'
       *  Sqrt: '<S137>/sqrt1'
       *  Sum: '<S137>/Sum'
       */
      rtb_Sign1 = (sqrt(0.3183098861837907 * rtb_pi3) * autocodePlant_B->
                   Product[2] - autocodePlant_X->wg_p1_CSTATE[1]) / rtb_pi3;
      autocodePlant_B->w[1] = rtb_Sign1;

      /* Product: '<S137>/w ' incorporates:
       *  Integrator: '<S137>/wg_p1'
       *  Integrator: '<S137>/wg_p2'
       *  Product: '<S137>/Lwg//V '
       *  Sum: '<S137>/Sum1'
       */
      autocodePlant_B->w_h[1] = (rtb_Sign1 * autocodePlant_ConstB.sqrt_g *
        rtb_pi3 + (autocodePlant_X->wg_p1_CSTATE[1] -
                   autocodePlant_X->wg_p2_CSTATE[1])) / rtb_pi3;

      /* Product: '<S137>/Lwg//V 1' incorporates:
       *  Integrator: '<S137>/wg_p2'
       */
      autocodePlant_B->LwgV1[0] = autocodePlant_ConstB.sigma_wg *
        autocodePlant_X->wg_p2_CSTATE[0];
      autocodePlant_B->LwgV1[1] = rtb_a * autocodePlant_X->wg_p2_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S122>/Hwgw(s)' */

    /* Outputs for Enabled SubSystem: '<S121>/Hqgw' incorporates:
     *  EnablePort: '<S133>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hqgw_MODE) {
      (void) memset(&(autocodePlant_XDis->qgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S133>/qgw_p' */
      autocodePlant_X->qgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->qgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hqgw_MODE = true;
    }

    if (autocodePlant_DW->Hqgw_MODE) {
      /* Gain: '<S133>/pi//4' */
      rtb_Sign1 = 0.7853981633974483 * rtb_TT0gLR;

      /* Product: '<S133>/w' incorporates:
       *  Integrator: '<S133>/qgw_p'
       *  Product: '<S133>/wg//V'
       *  Sum: '<S133>/Sum'
       */
      rtb_pi3 = (autocodePlant_B->LwgV1[0] / rtb_TT0gLR -
                 autocodePlant_X->qgw_p_CSTATE[0]) * (rtb_Sign1 /
        autocodePlant_ConstB.UnitConversion_e);
      autocodePlant_B->w_j5[0] = rtb_pi3;

      /* UnaryMinus: '<S133>/Unary Minus' */
      autocodePlant_B->UnaryMinus[0] = -rtb_pi3;

      /* Product: '<S133>/w' incorporates:
       *  Integrator: '<S133>/qgw_p'
       *  Product: '<S133>/wg//V'
       *  Sum: '<S133>/Sum'
       */
      rtb_pi3 = (autocodePlant_B->LwgV1[1] / rtb_TT0gLR -
                 autocodePlant_X->qgw_p_CSTATE[1]) * (rtb_Sign1 /
        autocodePlant_ConstB.UnitConversion_e);
      autocodePlant_B->w_j5[1] = rtb_pi3;

      /* UnaryMinus: '<S133>/Unary Minus' */
      autocodePlant_B->UnaryMinus[1] = -rtb_pi3;
    }

    /* End of Outputs for SubSystem: '<S121>/Hqgw' */

    /* Saturate: '<S139>/Limit Height h<1000ft' */
    if (rtb_Gain_l > 1000.0) {
      rtb_Product3_ax = 1000.0;
    } else if (rtb_Gain_l < 0.0) {
      rtb_Product3_ax = 0.0;
    } else {
      rtb_Product3_ax = rtb_Gain_l;
    }

    /* Product: '<S139>/sigma_ug, sigma_vg' incorporates:
     *  Fcn: '<S139>/Low Altitude Intensity'
     *  Saturate: '<S139>/Limit Height h<1000ft'
     */
    rtb_Sign1 = 1.0 / rt_powd_snf(0.000823 * rtb_Product3_ax + 0.177, 0.4) *
      autocodePlant_ConstB.sigma_wg;

    /* Fcn: '<S156>/Low Altitude Scale Length' */
    rtb_Sum1_oo /= rt_powd_snf(0.000823 * rtb_Sum1_oo + 0.177, 1.2);

    /* Gain: '<S128>/Lv' */
    rtb_Lw_idx_1 = autocodePlant_ConstB.UnitConversion_k;

    /* Outputs for Enabled SubSystem: '<S122>/Hvgw(s)' incorporates:
     *  EnablePort: '<S136>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hvgws_MODE) {
      (void) memset(&(autocodePlant_XDis->vg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S136>/vg_p1' */
      autocodePlant_X->vg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S136>/vgw_p2' */
      autocodePlant_X->vgw_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S136>/vg_p1' */
      autocodePlant_X->vg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S136>/vgw_p2' */
      autocodePlant_X->vgw_p2_CSTATE[1] = 0.0;
      autocodePlant_DW->Hvgws_MODE = true;
    }

    if (autocodePlant_DW->Hvgws_MODE) {
      /* Product: '<S136>/Lvg//V' incorporates:
       *  Gain: '<S128>/Lv'
       */
      rtb_pi3 = rtb_Sum1_oo / rtb_TT0gLR;

      /* Product: '<S136>/w' incorporates:
       *  Gain: '<S136>/(1//pi)'
       *  Integrator: '<S136>/vg_p1'
       *  Product: '<S136>/Lug//V1'
       *  Sqrt: '<S136>/sqrt'
       *  Sum: '<S136>/Sum'
       */
      rtb_TrigonometricFunction_o2_o = (sqrt(0.3183098861837907 * rtb_pi3) *
        autocodePlant_B->Product[1] - autocodePlant_X->vg_p1_CSTATE[0]) /
        rtb_pi3;
      autocodePlant_B->w_c[0] = rtb_TrigonometricFunction_o2_o;

      /* Product: '<S136>/w ' incorporates:
       *  Gain: '<S136>/sqrt(3)'
       *  Integrator: '<S136>/vg_p1'
       *  Integrator: '<S136>/vgw_p2'
       *  Product: '<S136>/Lvg//V '
       *  Sum: '<S136>/Sum1'
       */
      autocodePlant_B->w_j[0] = (rtb_TrigonometricFunction_o2_o * rtb_pi3 *
        1.7320508075688772 + (autocodePlant_X->vg_p1_CSTATE[0] -
        autocodePlant_X->vgw_p2_CSTATE[0])) / rtb_pi3;

      /* Product: '<S136>/Lvg//V' */
      rtb_pi3 = rtb_Lw_idx_1 / rtb_TT0gLR;

      /* Product: '<S136>/w' incorporates:
       *  Gain: '<S136>/(1//pi)'
       *  Integrator: '<S136>/vg_p1'
       *  Product: '<S136>/Lug//V1'
       *  Sqrt: '<S136>/sqrt'
       *  Sum: '<S136>/Sum'
       */
      rtb_TrigonometricFunction_o2_o = (sqrt(0.3183098861837907 * rtb_pi3) *
        autocodePlant_B->Product[1] - autocodePlant_X->vg_p1_CSTATE[1]) /
        rtb_pi3;
      autocodePlant_B->w_c[1] = rtb_TrigonometricFunction_o2_o;

      /* Product: '<S136>/w ' incorporates:
       *  Gain: '<S136>/sqrt(3)'
       *  Integrator: '<S136>/vg_p1'
       *  Integrator: '<S136>/vgw_p2'
       *  Product: '<S136>/Lvg//V '
       *  Sum: '<S136>/Sum1'
       */
      autocodePlant_B->w_j[1] = (rtb_TrigonometricFunction_o2_o * rtb_pi3 *
        1.7320508075688772 + (autocodePlant_X->vg_p1_CSTATE[1] -
        autocodePlant_X->vgw_p2_CSTATE[1])) / rtb_pi3;

      /* Product: '<S136>/w 1' incorporates:
       *  Integrator: '<S136>/vgw_p2'
       */
      autocodePlant_B->w1[0] = rtb_Sign1 * autocodePlant_X->vgw_p2_CSTATE[0];
      autocodePlant_B->w1[1] = rtb_a * autocodePlant_X->vgw_p2_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S122>/Hvgw(s)' */

    /* Outputs for Enabled SubSystem: '<S121>/Hrgw' incorporates:
     *  EnablePort: '<S134>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hrgw_MODE) {
      (void) memset(&(autocodePlant_XDis->rgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S134>/rgw_p' */
      autocodePlant_X->rgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->rgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hrgw_MODE = true;
    }

    if (autocodePlant_DW->Hrgw_MODE) {
      /* Gain: '<S134>/pi//3' */
      rtb_pi3 = 1.0471975511965976 * rtb_TT0gLR;

      /* Product: '<S134>/w' incorporates:
       *  Integrator: '<S134>/rgw_p'
       *  Product: '<S134>/vg//V'
       *  Sum: '<S134>/Sum'
       */
      autocodePlant_B->w_g[0] = (autocodePlant_B->w1[0] / rtb_TT0gLR -
        autocodePlant_X->rgw_p_CSTATE[0]) * (rtb_pi3 /
        autocodePlant_ConstB.UnitConversion_e);
      autocodePlant_B->w_g[1] = (autocodePlant_B->w1[1] / rtb_TT0gLR -
        autocodePlant_X->rgw_p_CSTATE[1]) * (rtb_pi3 /
        autocodePlant_ConstB.UnitConversion_e);
    }

    /* End of Outputs for SubSystem: '<S121>/Hrgw' */

    /* Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix' incorporates:
     *  Sqrt: '<S184>/sqrt'
     */
    rtb_pi3_tmp = sqrt(((rtb_q_na_idx_0 * rtb_q_na_idx_0 + rtb_q_na_idx_1 *
                         rtb_q_na_idx_1) + rtb_q_na_idx_2 * rtb_q_na_idx_2) +
                       rtb_q_na_idx_3 * rtb_q_na_idx_3);
    rtb_pi3 = 1.0 / rtb_pi3_tmp;
    rtb_Switch_d_idx_1 = rtb_pi3 * rtb_q_na_idx_1;
    rtb_Switch_d_idx_2 = rtb_pi3 * rtb_q_na_idx_2;
    rtb_Product2_ml = rtb_pi3 * rtb_q_na_idx_3;
    rtb_pi3 *= rtb_q_na_idx_0;
    rtb_TrigonometricFunction_o2_o = rtb_pi3 * rtb_pi3;
    rtb_Sign1_e = rtb_Switch_d_idx_1 * rtb_Switch_d_idx_1;
    rtb_Sign1_i = rtb_Switch_d_idx_2 * rtb_Switch_d_idx_2;
    rtb_Gain_oa = rtb_Product2_ml * rtb_Product2_ml;
    rtb_QuaternionstoDirectionCosin[0] = ((rtb_TrigonometricFunction_o2_o +
      rtb_Sign1_e) - rtb_Sign1_i) - rtb_Gain_oa;
    rtb_UnaryMinus1_k4 = rtb_Switch_d_idx_1 * rtb_Switch_d_idx_2;
    rtb_Product_h5 = rtb_pi3 * rtb_Product2_ml;
    rtb_QuaternionstoDirectionCosin[3] = (rtb_UnaryMinus1_k4 + rtb_Product_h5) *
      2.0;
    rtb_UnaryMinus1_o = rtb_Switch_d_idx_1 * rtb_Product2_ml;
    rtb_Gain_el = rtb_pi3 * rtb_Switch_d_idx_2;
    rtb_QuaternionstoDirectionCosin[6] = (rtb_UnaryMinus1_o - rtb_Gain_el) * 2.0;
    rtb_QuaternionstoDirectionCosin[1] = (rtb_UnaryMinus1_k4 - rtb_Product_h5) *
      2.0;
    rtb_TrigonometricFunction_o2_o -= rtb_Sign1_e;
    rtb_QuaternionstoDirectionCosin[4] = (rtb_TrigonometricFunction_o2_o +
      rtb_Sign1_i) - rtb_Gain_oa;
    rtb_Sign1_e = rtb_Switch_d_idx_2 * rtb_Product2_ml;
    rtb_UnaryMinus1_k4 = rtb_pi3 * rtb_Switch_d_idx_1;
    rtb_QuaternionstoDirectionCosin[7] = (rtb_Sign1_e + rtb_UnaryMinus1_k4) *
      2.0;
    rtb_QuaternionstoDirectionCosin[2] = (rtb_UnaryMinus1_o + rtb_Gain_el) * 2.0;
    rtb_QuaternionstoDirectionCosin[5] = (rtb_Sign1_e - rtb_UnaryMinus1_k4) *
      2.0;
    rtb_QuaternionstoDirectionCosin[8] = (rtb_TrigonometricFunction_o2_o -
      rtb_Sign1_i) + rtb_Gain_oa;

    /* If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    rtPrevAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      if (rtb_Gain_l <= 1000.0) {
        rtAction = 0;
      } else if (rtb_Gain_l >= 2000.0) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = rtAction;
    } else {
      rtAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&autocodePlant_M->solverInfo,
        true);
    }

    switch (rtAction) {
     case 0:
      /* Outputs for IfAction SubSystem: '<S126>/Low altitude  rates' incorporates:
       *  ActionPort: '<S141>/Action Port'
       */
      /* SignalConversion generated from: '<S146>/Vector Concatenate' */
      rtb_Product_ne[2] = autocodePlant_B->w_g[0];

      /* Trigonometry: '<S147>/Trigonometric Function1' incorporates:
       *  UnitConversion: '<S120>/Unit Conversion'
       */
      rtb_pi3 = sin(autocodePlant_ConstB.UnitConversion);
      rtb_TrigonometricFunction_o2_o = cos(autocodePlant_ConstB.UnitConversion);

      /* Sum: '<S147>/Sum' incorporates:
       *  Product: '<S147>/Product1'
       *  Product: '<S147>/Product2'
       */
      rtb_Product_ne[0] = autocodePlant_B->sigma_w[0] *
        rtb_TrigonometricFunction_o2_o - rtb_pi3 * autocodePlant_B->UnaryMinus[0];

      /* Sum: '<S147>/Sum1' incorporates:
       *  Product: '<S147>/Product1'
       *  Product: '<S147>/Product2'
       */
      rtb_Product_ne[1] = rtb_pi3 * autocodePlant_B->sigma_w[0] +
        autocodePlant_B->UnaryMinus[0] * rtb_TrigonometricFunction_o2_o;

      /* Product: '<S146>/Product' incorporates:
       *  Concatenate: '<S146>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       *  Reshape: '<S146>/Reshape1'
       */
      rtb_pi3 = 0.0;
      rtb_TrigonometricFunction_o2_o = 0.0;
      rtb_Sign1_e = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_Product3_ax = rtb_Product_ne[i];
        rtb_pi3 += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_Product3_ax;
        rtb_TrigonometricFunction_o2_o += rtb_QuaternionstoDirectionCosin[3 * i
          + 1] * rtb_Product3_ax;
        rtb_Sign1_e += rtb_QuaternionstoDirectionCosin[3 * i + 2] *
          rtb_Product3_ax;
      }

      rtb_VectorConcatenate_h[2] = rtb_Sign1_e;
      rtb_VectorConcatenate_h[1] = rtb_TrigonometricFunction_o2_o;
      rtb_VectorConcatenate_h[0] = rtb_pi3;

      /* End of Product: '<S146>/Product' */
      /* End of Outputs for SubSystem: '<S126>/Low altitude  rates' */
      break;

     case 1:
      /* Outputs for IfAction SubSystem: '<S126>/Medium//High  altitude rates' incorporates:
       *  ActionPort: '<S142>/Action Port'
       */
      /* Gain: '<S142>/Gain' */
      rtb_VectorConcatenate_h[0] = autocodePlant_B->sigma_w[1];
      rtb_VectorConcatenate_h[1] = autocodePlant_B->UnaryMinus[1];
      rtb_VectorConcatenate_h[2] = autocodePlant_B->w_g[1];

      /* End of Outputs for SubSystem: '<S126>/Medium//High  altitude rates' */
      break;

     default:
      /* Outputs for IfAction SubSystem: '<S126>/Interpolate  rates' incorporates:
       *  ActionPort: '<S140>/Action Port'
       */
      /* Trigonometry: '<S145>/Trigonometric Function' incorporates:
       *  UnitConversion: '<S120>/Unit Conversion'
       */
      rtb_pi3 = sin(autocodePlant_ConstB.UnitConversion);
      rtb_TrigonometricFunction_o2_o = cos(autocodePlant_ConstB.UnitConversion);

      /* Sum: '<S145>/Sum' incorporates:
       *  Product: '<S145>/Product1'
       *  Product: '<S145>/Product2'
       */
      rtb_VectorConcatenate_h[0] = autocodePlant_B->sigma_w[0] *
        rtb_TrigonometricFunction_o2_o - rtb_pi3 * autocodePlant_B->UnaryMinus[0];

      /* Sum: '<S145>/Sum1' incorporates:
       *  Product: '<S145>/Product1'
       *  Product: '<S145>/Product2'
       */
      rtb_VectorConcatenate_h[1] = rtb_pi3 * autocodePlant_B->sigma_w[0] +
        autocodePlant_B->UnaryMinus[0] * rtb_TrigonometricFunction_o2_o;

      /* SignalConversion generated from: '<S144>/Vector Concatenate' */
      rtb_VectorConcatenate_h[2] = autocodePlant_B->w_g[0];

      /* Product: '<S144>/Product' incorporates:
       *  Concatenate: '<S144>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       */
      rtb_pi3 = 0.0;
      rtb_Sign1_i = 0.0;
      rtb_TrigonometricFunction_o2_o = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_Product3_ax = rtb_VectorConcatenate_h[i];
        rtb_pi3 += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_Product3_ax;
        rtb_Sign1_i += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
          rtb_Product3_ax;
        rtb_TrigonometricFunction_o2_o += rtb_QuaternionstoDirectionCosin[3 * i
          + 2] * rtb_Product3_ax;
      }

      /* Sum: '<S140>/Sum3' incorporates:
       *  Constant: '<S140>/max_height_low'
       *  Product: '<S140>/Product1'
       *  Product: '<S144>/Product'
       *  Sum: '<S140>/Sum1'
       *  Sum: '<S140>/Sum2'
       */
      rtb_VectorConcatenate_h[0] = (autocodePlant_B->sigma_w[1] - rtb_pi3) *
        (rtb_Gain_l - 1000.0) / autocodePlant_ConstB.Sum_is + rtb_pi3;
      rtb_VectorConcatenate_h[1] = (autocodePlant_B->UnaryMinus[1] - rtb_Sign1_i)
        * (rtb_Gain_l - 1000.0) / autocodePlant_ConstB.Sum_is + rtb_Sign1_i;
      rtb_VectorConcatenate_h[2] = (autocodePlant_B->w_g[1] -
        rtb_TrigonometricFunction_o2_o) * (rtb_Gain_l - 1000.0) /
        autocodePlant_ConstB.Sum_is + rtb_TrigonometricFunction_o2_o;

      /* End of Outputs for SubSystem: '<S126>/Interpolate  rates' */
      break;
    }

    /* End of If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */

    /* Sum: '<S4>/Sum1' incorporates:
     *  DataTypeConversion: '<S117>/Cast'
     */
    rtb_VectorConcatenate_h[0] = rtb_wBdy_rps[0] - (real_T)
      (rtb_VectorConcatenate_h[0] != 0.0);
    rtb_VectorConcatenate_h[1] = rtb_wBdy_rps[1] - (real_T)
      (rtb_VectorConcatenate_h[1] != 0.0);
    rtb_VectorConcatenate_h[2] = rtb_wBdy_rps[2] - (real_T)
      (rtb_VectorConcatenate_h[2] != 0.0);

    /* Product: '<S21>/Element Product' */
    rtb_ElementProduct[0] = rtb_VectorConcatenate_h[1] *
      autocodePlant_ConstB.Subtract1[2];
    rtb_ElementProduct[1] = autocodePlant_ConstB.Subtract1[0] *
      rtb_VectorConcatenate_h[2];
    rtb_ElementProduct[2] = rtb_VectorConcatenate_h[0] *
      autocodePlant_ConstB.Subtract1[1];
    rtb_ElementProduct[3] = autocodePlant_ConstB.Subtract1[1] *
      rtb_VectorConcatenate_h[2];
    rtb_ElementProduct[4] = rtb_VectorConcatenate_h[0] *
      autocodePlant_ConstB.Subtract1[2];
    rtb_ElementProduct[5] = autocodePlant_ConstB.Subtract1[0] *
      rtb_VectorConcatenate_h[1];

    /* UnitConversion: '<S160>/Unit Conversion' incorporates:
     *  UnaryMinus: '<S101>/Unary Minus'
     */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    rtb_Sign1_i = 3.280839895013123 * -rtb_posNed_m[2];

    /* Saturate: '<S118>/3ft-->inf' */
    if (rtb_Sign1_i <= 3.0) {
      rtb_Sign1_i = 3.0;
    }

    /* Product: '<S118>/Product' incorporates:
     *  Gain: '<S118>/h//z0'
     *  Math: '<S118>/ln(h//z0)'
     *  Saturate: '<S118>/3ft-->inf'
     *
     * About '<S118>/ln(h//z0)':
     *  Operator: log
     */
    rtb_Product_h5 = log(6.666666666666667 * rtb_Sign1_i) /
      autocodePlant_ConstB.lnref_heightz0;

    /* Product: '<S101>/Matrix Multiply' */
    rtb_pi3 = 0.0;
    rtb_Sign1_i = 0.0;
    rtb_TrigonometricFunction_o2_o = 0.0;

    /* Product: '<S118>/Transform from Inertial to Body axes' */
    rtb_UnaryMinus1_k4 = 0.0;
    rtb_Gain_oa = 0.0;
    rtb_Sign1_e = 0.0;
    for (i = 0; i < 3; i++) {
      /* Product: '<S101>/Matrix Multiply' incorporates:
       *  Product: '<S118>/Transform from Inertial to Body axes'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       */
      rtb_Lw_idx_1 = rtb_QuaternionstoDirectionCosin[3 * i];
      rtb_pi3 += rtb_Lw_idx_1 * 0.0;
      rtb_Switch_d_idx_1 = rtb_QuaternionstoDirectionCosin[3 * i + 1];
      rtb_Sign1_i += rtb_Switch_d_idx_1 * 0.0;
      rtb_Switch_d_idx_2 = rtb_QuaternionstoDirectionCosin[3 * i + 2];
      rtb_TrigonometricFunction_o2_o += rtb_Switch_d_idx_2 * 0.0;

      /* Product: '<S118>/Transform from Inertial to Body axes' incorporates:
       *  Product: '<S118>/Product1'
       */
      rtb_Product3_ax = rtb_Product_h5 *
        autocodePlant_ConstB.Windspeedatreferenceheight[i];
      rtb_UnaryMinus1_k4 += rtb_Lw_idx_1 * rtb_Product3_ax;
      rtb_Gain_oa += rtb_Switch_d_idx_1 * rtb_Product3_ax;
      rtb_Sign1_e += rtb_Switch_d_idx_2 * rtb_Product3_ax;
    }

    /* Outputs for Enabled SubSystem: '<S122>/Hugw(s)' incorporates:
     *  EnablePort: '<S135>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hugws_MODE) {
      (void) memset(&(autocodePlant_XDis->ug_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S135>/ug_p' */
      autocodePlant_X->ug_p_CSTATE[0] = 0.0;
      autocodePlant_X->ug_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hugws_MODE = true;
    }

    if (autocodePlant_DW->Hugws_MODE) {
      /* Product: '<S135>/Lug//V' */
      rtb_Sum1_oo /= rtb_TT0gLR;
      rtb_TT0gLR = autocodePlant_ConstB.UnitConversion_k / rtb_TT0gLR;

      /* Product: '<S135>/w' incorporates:
       *  Gain: '<S135>/(2//pi)'
       *  Integrator: '<S135>/ug_p'
       *  Product: '<S135>/Lug//V1'
       *  Sqrt: '<S135>/sqrt'
       *  Sum: '<S135>/Sum'
       */
      autocodePlant_B->w_d[0] = (sqrt(0.6366197723675814 * rtb_Sum1_oo) *
        autocodePlant_B->Product[0] - autocodePlant_X->ug_p_CSTATE[0]) /
        rtb_Sum1_oo;
      autocodePlant_B->w_d[1] = (sqrt(0.6366197723675814 * rtb_TT0gLR) *
        autocodePlant_B->Product[0] - autocodePlant_X->ug_p_CSTATE[1]) /
        rtb_TT0gLR;

      /* Product: '<S135>/w1' incorporates:
       *  Integrator: '<S135>/ug_p'
       */
      autocodePlant_B->w1_c[0] = autocodePlant_X->ug_p_CSTATE[0] * rtb_Sign1;
      autocodePlant_B->w1_c[1] = autocodePlant_X->ug_p_CSTATE[1] * rtb_a;
    }

    /* End of Outputs for SubSystem: '<S122>/Hugw(s)' */

    /* If: '<S127>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    rtPrevAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      if (rtb_Gain_l <= 1000.0) {
        rtAction = 0;
      } else if (rtb_Gain_l >= 2000.0) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f = rtAction;
    } else {
      rtAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&autocodePlant_M->solverInfo,
        true);
    }

    switch (rtAction) {
     case 0:
      /* Outputs for IfAction SubSystem: '<S127>/Low altitude  velocities' incorporates:
       *  ActionPort: '<S149>/Action Port'
       */
      /* SignalConversion generated from: '<S154>/Vector Concatenate' */
      rtb_Product_fn[2] = autocodePlant_B->LwgV1[0];

      /* Trigonometry: '<S155>/Trigonometric Function' incorporates:
       *  UnitConversion: '<S120>/Unit Conversion'
       */
      rtb_Sum1_oo = sin(autocodePlant_ConstB.UnitConversion);
      rtb_a = cos(autocodePlant_ConstB.UnitConversion);

      /* Sum: '<S155>/Sum' incorporates:
       *  Product: '<S155>/Product1'
       *  Product: '<S155>/Product2'
       */
      rtb_Product_fn[0] = autocodePlant_B->w1_c[0] * rtb_a - rtb_Sum1_oo *
        autocodePlant_B->w1[0];

      /* Sum: '<S155>/Sum1' incorporates:
       *  Product: '<S155>/Product1'
       *  Product: '<S155>/Product2'
       */
      rtb_Product_fn[1] = rtb_Sum1_oo * autocodePlant_B->w1_c[0] +
        autocodePlant_B->w1[0] * rtb_a;

      /* Product: '<S154>/Product' incorporates:
       *  Concatenate: '<S154>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       *  Reshape: '<S154>/Reshape1'
       */
      rtb_TmpSignalConversionAtProd_0 = 0.0;
      rtb_Product1_hx = 0.0;
      rtb_Sum1_oo = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_Product3_ax = rtb_Product_fn[i];
        rtb_TmpSignalConversionAtProd_0 += rtb_QuaternionstoDirectionCosin[3 * i]
          * rtb_Product3_ax;
        rtb_Product1_hx += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
          rtb_Product3_ax;
        rtb_Sum1_oo += rtb_QuaternionstoDirectionCosin[3 * i + 2] *
          rtb_Product3_ax;
      }

      rtb_VectorConcatenate[2] = rtb_Sum1_oo;
      rtb_VectorConcatenate[1] = rtb_Product1_hx;
      rtb_VectorConcatenate[0] = rtb_TmpSignalConversionAtProd_0;

      /* End of Product: '<S154>/Product' */
      /* End of Outputs for SubSystem: '<S127>/Low altitude  velocities' */
      break;

     case 1:
      /* Outputs for IfAction SubSystem: '<S127>/Medium//High  altitude velocities' incorporates:
       *  ActionPort: '<S150>/Action Port'
       */
      /* Gain: '<S150>/Gain' */
      rtb_VectorConcatenate[0] = autocodePlant_B->w1_c[1];
      rtb_VectorConcatenate[1] = autocodePlant_B->w1[1];
      rtb_VectorConcatenate[2] = autocodePlant_B->LwgV1[1];

      /* End of Outputs for SubSystem: '<S127>/Medium//High  altitude velocities' */
      break;

     default:
      /* Outputs for IfAction SubSystem: '<S127>/Interpolate  velocities' incorporates:
       *  ActionPort: '<S148>/Action Port'
       */
      /* Trigonometry: '<S153>/Trigonometric Function' incorporates:
       *  UnitConversion: '<S120>/Unit Conversion'
       */
      rtb_Sum1_oo = sin(autocodePlant_ConstB.UnitConversion);
      rtb_a = cos(autocodePlant_ConstB.UnitConversion);

      /* Sum: '<S153>/Sum' incorporates:
       *  Product: '<S153>/Product1'
       *  Product: '<S153>/Product2'
       */
      rtb_VectorConcatenate[0] = autocodePlant_B->w1_c[0] * rtb_a - rtb_Sum1_oo *
        autocodePlant_B->w1[0];

      /* Sum: '<S153>/Sum1' incorporates:
       *  Product: '<S153>/Product1'
       *  Product: '<S153>/Product2'
       */
      rtb_VectorConcatenate[1] = rtb_Sum1_oo * autocodePlant_B->w1_c[0] +
        autocodePlant_B->w1[0] * rtb_a;

      /* SignalConversion generated from: '<S152>/Vector Concatenate' */
      rtb_VectorConcatenate[2] = autocodePlant_B->LwgV1[0];

      /* Product: '<S152>/Product' incorporates:
       *  Concatenate: '<S152>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       */
      rtb_TT0gLR = 0.0;
      rtb_Product_h5 = 0.0;
      rtb_Sign1 = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_Product3_ax = rtb_VectorConcatenate[i];
        rtb_TT0gLR += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_Product3_ax;
        rtb_Product_h5 += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
          rtb_Product3_ax;
        rtb_Sign1 += rtb_QuaternionstoDirectionCosin[3 * i + 2] *
          rtb_Product3_ax;
      }

      /* Sum: '<S148>/Sum3' incorporates:
       *  Constant: '<S148>/max_height_low'
       *  Product: '<S148>/Product1'
       *  Product: '<S152>/Product'
       *  Sum: '<S148>/Sum1'
       *  Sum: '<S148>/Sum2'
       */
      rtb_VectorConcatenate[0] = (autocodePlant_B->w1_c[1] - rtb_TT0gLR) *
        (rtb_Gain_l - 1000.0) / autocodePlant_ConstB.Sum_p + rtb_TT0gLR;
      rtb_VectorConcatenate[1] = (autocodePlant_B->w1[1] - rtb_Product_h5) *
        (rtb_Gain_l - 1000.0) / autocodePlant_ConstB.Sum_p + rtb_Product_h5;
      rtb_VectorConcatenate[2] = (autocodePlant_B->LwgV1[1] - rtb_Sign1) *
        (rtb_Gain_l - 1000.0) / autocodePlant_ConstB.Sum_p + rtb_Sign1;

      /* End of Outputs for SubSystem: '<S127>/Interpolate  velocities' */
      break;
    }

    /* End of If: '<S127>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */

    /* Saturate: '<S106>/Limit  altitude  to troposhere' incorporates:
     *  Constant: '<S4>/Constant'
     *  Sum: '<S4>/Sum'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    /* Unit Conversion - from: ft/s to: m/s
       Expression: output = (0.3048*input) + (0) */
    if (182.0 - rtb_posNed_m[2] > 11000.0) {
      rtb_Product3_ax = 11000.0;
    } else if (182.0 - rtb_posNed_m[2] < 0.0) {
      rtb_Product3_ax = 0.0;
    } else {
      rtb_Product3_ax = 182.0 - rtb_posNed_m[2];
    }

    /* Sum: '<S106>/Sum1' incorporates:
     *  Constant: '<S106>/Sea Level  Temperature'
     *  Gain: '<S106>/Lapse Rate'
     *  Saturate: '<S106>/Limit  altitude  to troposhere'
     */
    rtb_Sum1_oo = 288.15 - 0.0065 * rtb_Product3_ax;

    /* Sqrt: '<S106>/a' incorporates:
     *  Gain: '<S106>/gamma*R'
     */
    rtb_a = sqrt(401.87433999999996 * rtb_Sum1_oo);

    /* Sum: '<S101>/Sum' incorporates:
     *  Product: '<S101>/Matrix Multiply'
     *  Product: '<S118>/Transform from Inertial to Body axes'
     *  UnitConversion: '<S117>/Unit Conversion'
     */
    rtb_pi3 = (rtb_pi3 + rtb_UnaryMinus1_k4) + 0.3048 * rtb_VectorConcatenate[0];
    rtb_Product_ne[0] = rtb_pi3;

    /* Sum: '<S4>/Sum2' */
    rtb_TmpSignalConversionAtProd_0 = rtb_velBdy_mps[0] - rtb_pi3;
    rtb_VectorConcatenate[0] = rtb_TmpSignalConversionAtProd_0;

    /* Sum: '<S9>/Sum' incorporates:
     *  Sum: '<S21>/Sum'
     */
    rtb_TT0gLR = (rtb_ElementProduct[0] - rtb_ElementProduct[3]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product_fn[0] = rtb_TT0gLR;

    /* DotProduct: '<S9>/Dot Product4' */
    rtb_Product_h5 = rtb_TT0gLR * rtb_TT0gLR;

    /* Product: '<S9>/Product8' */
    rtb_UnaryMinus1_k4 = rtb_TT0gLR * autocodePlant_ConstB.Sum2_i[0];

    /* Sum: '<S101>/Sum' incorporates:
     *  Product: '<S101>/Matrix Multiply'
     *  Product: '<S118>/Transform from Inertial to Body axes'
     *  UnitConversion: '<S117>/Unit Conversion'
     */
    rtb_pi3 = (rtb_Sign1_i + rtb_Gain_oa) + 0.3048 * rtb_VectorConcatenate[1];
    rtb_Product_ne[1] = rtb_pi3;

    /* Sum: '<S4>/Sum2' */
    rtb_TmpSignalConversionAtProd_0 = rtb_velBdy_mps[1] - rtb_pi3;
    rtb_VectorConcatenate[1] = rtb_TmpSignalConversionAtProd_0;

    /* Sum: '<S9>/Sum' incorporates:
     *  Sum: '<S21>/Sum'
     */
    rtb_Sign1 = (rtb_ElementProduct[1] - rtb_ElementProduct[4]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product_fn[1] = rtb_Sign1;

    /* Product: '<S9>/Product8' */
    rtb_Gain_l = rtb_Sign1 * autocodePlant_ConstB.Sum2_i[1];

    /* Sum: '<S101>/Sum' incorporates:
     *  Product: '<S101>/Matrix Multiply'
     *  Product: '<S118>/Transform from Inertial to Body axes'
     *  UnitConversion: '<S117>/Unit Conversion'
     */
    rtb_pi3 = (rtb_TrigonometricFunction_o2_o + rtb_Sign1_e) + 0.3048 *
      rtb_VectorConcatenate[2];
    rtb_Product_ne[2] = rtb_pi3;

    /* Sum: '<S4>/Sum2' */
    rtb_TmpSignalConversionAtProd_0 = rtb_velBdy_mps[2] - rtb_pi3;
    rtb_VectorConcatenate[2] = rtb_TmpSignalConversionAtProd_0;

    /* Sum: '<S9>/Sum' incorporates:
     *  Sum: '<S21>/Sum'
     */
    rtb_TT0gLR = (rtb_ElementProduct[2] - rtb_ElementProduct[5]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product_fn[2] = rtb_TT0gLR;

    /* Product: '<S9>/Product8' */
    rtb_pi3 = rtb_TT0gLR * autocodePlant_ConstB.Sum2_i[2];

    /* DotProduct: '<S9>/Dot Product1' */
    rtb_TrigonometricFunction_o2_o = (rtb_UnaryMinus1_k4 * rtb_UnaryMinus1_k4 +
      rtb_Gain_l * rtb_Gain_l) + rtb_pi3 * rtb_pi3;

    /* Switch: '<S18>/Switch' incorporates:
     *  Constant: '<S18>/Constant4'
     *  Constant: '<S18>/Constant5'
     */
    if (rtb_a >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S9>/Dot Product4' incorporates:
     *  DotProduct: '<S9>/Dot Product3'
     */
    rtb_Gain_oa = (rtb_Sign1 * rtb_Sign1 + rtb_Product_h5) + rtb_TT0gLR *
      rtb_TT0gLR;

    /* MinMax: '<S18>/Max' incorporates:
     *  Abs: '<S18>/Abs'
     *  Constant: '<S18>/Constant'
     *  MinMax: '<S14>/Max'
     *  MinMax: '<S38>/Max'
     *  MinMax: '<S58>/Max'
     *  MinMax: '<S78>/Max'
     */
    rtb_Gain_el = fmax(1.0E-6, rtb_a);

    /* Product: '<S9>/Divide1' incorporates:
     *  DotProduct: '<S9>/Dot Product4'
     *  MinMax: '<S18>/Max'
     *  Product: '<S18>/Product'
     *  Sqrt: '<S9>/Sqrt1'
     *  Switch: '<S18>/Switch'
     */
    rtb_Sign1_i = sqrt(rtb_Gain_oa) / ((real_T)i * rtb_Gain_el);

    /* Switch: '<S20>/Switch' incorporates:
     *  Constant: '<S20>/Constant4'
     *  Constant: '<S20>/Constant5'
     *  DotProduct: '<S9>/Dot Product1'
     */
    if (rtb_TrigonometricFunction_o2_o >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S9>/Divide' incorporates:
     *  Constant: '<S20>/Constant'
     *  DotProduct: '<S9>/Dot Product'
     *  DotProduct: '<S9>/Dot Product1'
     *  MinMax: '<S20>/Max'
     *  Product: '<S20>/Product'
     *  SignalConversion generated from: '<S9>/Dot Product'
     *  Sqrt: '<S9>/Sqrt'
     *  Switch: '<S20>/Switch'
     */
    rtb_Sum = ((autocodePlant_ConstB.Sum_b * rtb_UnaryMinus1_k4 +
                autocodePlant_ConstB.Sum_l * rtb_Gain_l) +
               autocodePlant_ConstB.Sum_c * rtb_pi3) / sqrt((real_T)i * fmax
      (1.0E-6, rtb_TrigonometricFunction_o2_o));

    /* Saturate: '<S9>/Saturation' */
    if (rtb_Sum > 1.0) {
      rtb_Sum = 1.0;
    } else if (rtb_Sum < -1.0) {
      rtb_Sum = -1.0;
    }

    /* Gain: '<S25>/Gain' incorporates:
     *  Saturate: '<S9>/Saturation'
     *  Trigonometry: '<S9>/Acos'
     */
    rtb_Gain_l = 57.29577951308232 * acos(rtb_Sum);
    if (tmp) {
      /* Backlash: '<S7>/Backlash' incorporates:
       *  UnitDelay: '<S7>/Unit Delay'
       */
      if (autocodePlant_DW->UnitDelay_DSTATE[0] < autocodePlant_DW->PrevY[0] -
          0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[0] = autocodePlant_DW->UnitDelay_DSTATE[0] +
          0.5;
      } else if (autocodePlant_DW->UnitDelay_DSTATE[0] <=
                 autocodePlant_DW->PrevY[0] + 0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[0] = autocodePlant_DW->PrevY[0];
      } else {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[0] = autocodePlant_DW->UnitDelay_DSTATE[0] -
          0.5;
      }

      if (autocodePlant_DW->UnitDelay_DSTATE[1] < autocodePlant_DW->PrevY[1] -
          0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[1] = autocodePlant_DW->UnitDelay_DSTATE[1] +
          0.5;
      } else if (autocodePlant_DW->UnitDelay_DSTATE[1] <=
                 autocodePlant_DW->PrevY[1] + 0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[1] = autocodePlant_DW->PrevY[1];
      } else {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[1] = autocodePlant_DW->UnitDelay_DSTATE[1] -
          0.5;
      }

      if (autocodePlant_DW->UnitDelay_DSTATE[2] < autocodePlant_DW->PrevY[2] -
          0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[2] = autocodePlant_DW->UnitDelay_DSTATE[2] +
          0.5;
      } else if (autocodePlant_DW->UnitDelay_DSTATE[2] <=
                 autocodePlant_DW->PrevY[2] + 0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[2] = autocodePlant_DW->PrevY[2];
      } else {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[2] = autocodePlant_DW->UnitDelay_DSTATE[2] -
          0.5;
      }

      if (autocodePlant_DW->UnitDelay_DSTATE[3] < autocodePlant_DW->PrevY[3] -
          0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[3] = autocodePlant_DW->UnitDelay_DSTATE[3] +
          0.5;
      } else if (autocodePlant_DW->UnitDelay_DSTATE[3] <=
                 autocodePlant_DW->PrevY[3] + 0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[3] = autocodePlant_DW->PrevY[3];
      } else {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[3] = autocodePlant_DW->UnitDelay_DSTATE[3] -
          0.5;
      }

      /* End of Backlash: '<S7>/Backlash' */
    }

    /* DotProduct: '<S9>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S9>/Dot Product2'
     *  Sum: '<S9>/Sum'
     */
    rtb_UnaryMinus1_k4 = (autocodePlant_ConstB.Sum_f * rtb_Product_fn[0] +
                          autocodePlant_ConstB.Sum_i * rtb_Sign1) +
      autocodePlant_ConstB.Sum_e * rtb_TT0gLR;

    /* Switch: '<S19>/Switch' incorporates:
     *  Constant: '<S19>/Constant4'
     *  Constant: '<S19>/Constant5'
     *  DotProduct: '<S9>/Dot Product2'
     */
    if (rtb_UnaryMinus1_k4 >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S19>/Product' incorporates:
     *  Abs: '<S19>/Abs'
     *  Constant: '<S19>/Constant'
     *  DotProduct: '<S9>/Dot Product2'
     *  MinMax: '<S19>/Max'
     *  Switch: '<S19>/Switch'
     */
    rtb_Switch_d_idx_1 = (real_T)i * fmax(1.0E-6, fabs(rtb_UnaryMinus1_k4));

    /* Signum: '<S9>/Sign1' */
    if (rtIsNaN(rtb_Switch_d_idx_1)) {
      rtb_Sign1 = (rtNaN);
    } else if (rtb_Switch_d_idx_1 < 0.0) {
      rtb_Sign1 = -1.0;
    } else {
      rtb_Sign1 = (rtb_Switch_d_idx_1 > 0.0);
    }

    /* End of Signum: '<S9>/Sign1' */

    /* Lookup_n-D: '<S9>/CA Lookup Table' incorporates:
     *  Gain: '<S25>/Gain'
     *  Product: '<S9>/Product7'
     *  Signum: '<S11>/Sign1'
     */
    bpIndices[0U] = plook_binx(rtb_Sign1_i, rtCP__CALookupTable_bp01Data, 9U,
      &rtb_Switch_d_idx_1);
    rtb_Sum_dj[0U] = rtb_Switch_d_idx_1;
    bpIndices[1U] = plook_binx(rtb_Gain_l, rtCP__CALookupTable_bp02Data, 2U,
      &rtb_Switch_d_idx_1);
    rtb_Sum_dj[1U] = rtb_Switch_d_idx_1;
    bpIndices[2U] = plook_binx(autocodePlant_B->Backlash[0] * rtb_Sign1,
      rtCP__CALookupTable_bp03Data, 4U, &rtb_Switch_d_idx_1);
    rtb_Sum_dj[2U] = rtb_Switch_d_idx_1;
    rtb_Sign1_e = intrp3d_l_pw(bpIndices, rtb_Sum_dj,
      rtCP__CALookupTable_tableData, rtCP__CALookupTable_dimSizes);

    /* Gain: '<S106>/1//T0' */
    rtb_pi3 = 0.00347041471455839 * rtb_Sum1_oo;

    /* Math: '<S106>/(T//T0)^(g//LR) ' incorporates:
     *  Constant: '<S106>/Constant'
     */
    rtb_TT0gLR = rt_powd_snf(rtb_pi3, 5.255875601466713);

    /* Product: '<S106>/Product' */
    rtb_TrigonometricFunction_o2_o = rtb_TT0gLR / rtb_pi3;

    /* Saturate: '<S106>/Limit  altitude  to Stratosphere' incorporates:
     *  Constant: '<S106>/Altitude of Troposphere'
     *  Constant: '<S4>/Constant'
     *  Sum: '<S106>/Sum'
     *  Sum: '<S4>/Sum'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    if (11000.0 - (182.0 - rtb_posNed_m[2]) > 0.0) {
      rtb_Product3_ax = 0.0;
    } else if (11000.0 - (182.0 - rtb_posNed_m[2]) < -9000.0) {
      rtb_Product3_ax = -9000.0;
    } else {
      rtb_Product3_ax = 11000.0 - (182.0 - rtb_posNed_m[2]);
    }

    /* Math: '<S106>/Stratosphere Model' incorporates:
     *  Gain: '<S106>/g//R'
     *  Product: '<S106>/Product1'
     *  Saturate: '<S106>/Limit  altitude  to Stratosphere'
     *
     * About '<S106>/Stratosphere Model':
     *  Operator: exp
     */
    rtb_pi3 = exp(1.0 / rtb_Sum1_oo * (0.03416319140953364 * rtb_Product3_ax));

    /* Product: '<S106>/Product3' incorporates:
     *  Gain: '<S106>/rho0'
     */
    rtb_TrigonometricFunction_o2_o = 1.225 * rtb_TrigonometricFunction_o2_o *
      rtb_pi3;

    /* Product: '<S9>/Product' incorporates:
     *  Constant: '<S9>/Constant1'
     *  Product: '<S10>/Product'
     *  Product: '<S11>/Product'
     *  Product: '<S12>/Product'
     *  Product: '<S8>/Product'
     */
    rtb_UnaryMinus_a = 0.5 * rtb_TrigonometricFunction_o2_o;
    rtb_Product_h5 = rtb_Gain_oa * rtb_UnaryMinus_a;

    /* UnaryMinus: '<S9>/Unary Minus' incorporates:
     *  Constant: '<S9>/   '
     *  Product: '<S9>/Product1'
     */
    rtb_Sign1_e = -(rtb_Sign1_e * rtb_Product_h5 * 0.018);

    /* Lookup_n-D: '<S9>/CN Lookup Table' incorporates:
     *  Gain: '<S25>/Gain'
     *  Product: '<S9>/Product5'
     *  Signum: '<S11>/Sign1'
     */
    bpIndices_0[0U] = plook_binx(rtb_Sign1_i, rtCP__CNLookupTable_bp01Data, 9U,
      &rtb_Switch_d_idx_1);
    rtb_Sum_k[0U] = rtb_Switch_d_idx_1;
    bpIndices_0[1U] = plook_binx(rtb_Gain_l, rtCP__CNLookupTable_bp02Data, 2U,
      &rtb_Switch_d_idx_1);
    rtb_Sum_k[1U] = rtb_Switch_d_idx_1;
    bpIndices_0[2U] = plook_binx(autocodePlant_B->Backlash[0] * rtb_Sign1,
      rtCP__CNLookupTable_bp03Data, 4U, &rtb_Switch_d_idx_1);
    rtb_Sum_k[2U] = rtb_Switch_d_idx_1;
    rtb_Sign1_i = intrp3d_l_pw(bpIndices_0, rtb_Sum_k,
      rtCP__CNLookupTable_tableData, rtCP__CNLookupTable_dimSizes);

    /* UnaryMinus: '<S9>/Unary Minus1' incorporates:
     *  Constant: '<S9>/ '
     *  Product: '<S9>/Product2'
     */
    rtb_Sign1_i = -(rtb_Sign1_i * rtb_Product_h5 * 0.018);

    /* Sum: '<S9>/Sum1' incorporates:
     *  Product: '<S9>/Product3'
     *  Product: '<S9>/Product4'
     *  SignalConversion generated from: '<S9>/Dot Product2'
     */
    rtb_Sum1_p2[0] = rtb_Sign1_i * autocodePlant_ConstB.Sum_f * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_b;
    rtb_Sum1_p2[1] = rtb_Sign1_i * autocodePlant_ConstB.Sum_i * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_l;
    rtb_Sum1_p2[2] = rtb_Sign1_i * autocodePlant_ConstB.Sum_e * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_c;

    /* Sum: '<S22>/Sum' incorporates:
     *  Product: '<S22>/Element Product'
     */
    rtb_Sum_hp[0] = autocodePlant_ConstB.Subtract1[1] * rtb_Sum1_p2[2] -
      rtb_Sum1_p2[1] * autocodePlant_ConstB.Subtract1[2];
    rtb_Sum_hp[1] = rtb_Sum1_p2[0] * autocodePlant_ConstB.Subtract1[2] -
      autocodePlant_ConstB.Subtract1[0] * rtb_Sum1_p2[2];
    rtb_Sum_hp[2] = autocodePlant_ConstB.Subtract1[0] * rtb_Sum1_p2[1] -
      rtb_Sum1_p2[0] * autocodePlant_ConstB.Subtract1[1];

    /* Sum: '<S10>/Sum' incorporates:
     *  Product: '<S41>/Element Product'
     *  Sum: '<S41>/Sum'
     */
    rtb_Sign1_e = (rtb_VectorConcatenate_h[1] *
                   autocodePlant_ConstB.Subtract1_m[2] -
                   autocodePlant_ConstB.Subtract1_m[1] *
                   rtb_VectorConcatenate_h[2]) + rtb_VectorConcatenate[0];
    rtb_Sum_dj[0] = rtb_Sign1_e;

    /* Product: '<S10>/Product8' */
    rtb_Product2_ml = rtb_Sign1_e * autocodePlant_ConstB.Sum2_l[0];

    /* Sum: '<S10>/Sum' incorporates:
     *  Product: '<S41>/Element Product'
     *  Sum: '<S41>/Sum'
     */
    rtb_Sign1_i = (autocodePlant_ConstB.Subtract1_m[0] *
                   rtb_VectorConcatenate_h[2] - rtb_VectorConcatenate_h[0] *
                   autocodePlant_ConstB.Subtract1_m[2]) + rtb_VectorConcatenate
      [1];
    rtb_Sum_dj[1] = rtb_Sign1_i;

    /* Product: '<S10>/Product8' */
    rtb_Gain_oa = rtb_Sign1_i * autocodePlant_ConstB.Sum2_l[1];

    /* Sum: '<S10>/Sum' incorporates:
     *  Product: '<S41>/Element Product'
     *  Sum: '<S41>/Sum'
     *  Sum: '<S4>/Sum2'
     */
    rtb_UnaryMinus1_o = (rtb_VectorConcatenate_h[0] *
                         autocodePlant_ConstB.Subtract1_m[1] -
                         autocodePlant_ConstB.Subtract1_m[0] *
                         rtb_VectorConcatenate_h[1]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_dj[2] = rtb_UnaryMinus1_o;

    /* Product: '<S10>/Product8' */
    rtb_Switch_d_idx_1 = rtb_UnaryMinus1_o * autocodePlant_ConstB.Sum2_l[2];

    /* DotProduct: '<S10>/Dot Product1' */
    rtb_Switch_d_idx_2 = (rtb_Product2_ml * rtb_Product2_ml + rtb_Gain_oa *
                          rtb_Gain_oa) + rtb_Switch_d_idx_1 * rtb_Switch_d_idx_1;

    /* Switch: '<S38>/Switch' incorporates:
     *  Constant: '<S38>/Constant4'
     *  Constant: '<S38>/Constant5'
     */
    if (rtb_a >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S10>/Dot Product4' incorporates:
     *  DotProduct: '<S10>/Dot Product3'
     */
    rtb_UnaryMinus1_k4 = (rtb_Sign1_e * rtb_Sign1_e + rtb_Sign1_i * rtb_Sign1_i)
      + rtb_UnaryMinus1_o * rtb_UnaryMinus1_o;

    /* Product: '<S10>/Divide1' incorporates:
     *  DotProduct: '<S10>/Dot Product4'
     *  Product: '<S38>/Product'
     *  Sqrt: '<S10>/Sqrt1'
     *  Switch: '<S38>/Switch'
     */
    rtb_Product_h5 = sqrt(rtb_UnaryMinus1_k4) / ((real_T)i * rtb_Gain_el);

    /* Switch: '<S40>/Switch' incorporates:
     *  Constant: '<S40>/Constant4'
     *  Constant: '<S40>/Constant5'
     *  DotProduct: '<S10>/Dot Product1'
     */
    if (rtb_Switch_d_idx_2 >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S10>/Divide' incorporates:
     *  Constant: '<S40>/Constant'
     *  DotProduct: '<S10>/Dot Product'
     *  DotProduct: '<S10>/Dot Product1'
     *  MinMax: '<S40>/Max'
     *  Product: '<S40>/Product'
     *  SignalConversion generated from: '<S10>/Dot Product'
     *  Sqrt: '<S10>/Sqrt'
     *  Switch: '<S40>/Switch'
     */
    rtb_Sum = ((autocodePlant_ConstB.Sum_k3 * rtb_Product2_ml +
                autocodePlant_ConstB.Sum_cv * rtb_Gain_oa) +
               autocodePlant_ConstB.Sum_b1v * rtb_Switch_d_idx_1) / sqrt((real_T)
      i * fmax(1.0E-6, rtb_Switch_d_idx_2));

    /* Saturate: '<S10>/Saturation' */
    if (rtb_Sum > 1.0) {
      rtb_Sum = 1.0;
    } else if (rtb_Sum < -1.0) {
      rtb_Sum = -1.0;
    }

    /* Gain: '<S45>/Gain' incorporates:
     *  Saturate: '<S10>/Saturation'
     *  Trigonometry: '<S10>/Acos'
     */
    rtb_Gain_oa = 57.29577951308232 * acos(rtb_Sum);

    /* DotProduct: '<S10>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S10>/Dot Product2'
     *  Sum: '<S10>/Sum'
     */
    rtb_Product2_ml = (autocodePlant_ConstB.Sum_m * rtb_Sign1_e +
                       autocodePlant_ConstB.Sum_b1 * rtb_Sign1_i) +
      autocodePlant_ConstB.Sum_k * rtb_UnaryMinus1_o;

    /* Switch: '<S39>/Switch' incorporates:
     *  Constant: '<S39>/Constant4'
     *  Constant: '<S39>/Constant5'
     *  DotProduct: '<S10>/Dot Product2'
     */
    if (rtb_Product2_ml >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S39>/Product' incorporates:
     *  Abs: '<S39>/Abs'
     *  Constant: '<S39>/Constant'
     *  DotProduct: '<S10>/Dot Product2'
     *  MinMax: '<S39>/Max'
     *  Switch: '<S39>/Switch'
     */
    rtb_Switch_d_idx_1 = (real_T)i * fmax(1.0E-6, fabs(rtb_Product2_ml));

    /* Signum: '<S10>/Sign1' */
    if (rtIsNaN(rtb_Switch_d_idx_1)) {
      rtb_Sign1_e = (rtNaN);
    } else if (rtb_Switch_d_idx_1 < 0.0) {
      rtb_Sign1_e = -1.0;
    } else {
      rtb_Sign1_e = (rtb_Switch_d_idx_1 > 0.0);
    }

    /* End of Signum: '<S10>/Sign1' */

    /* Lookup_n-D: '<S10>/CA Lookup Table' incorporates:
     *  Gain: '<S45>/Gain'
     *  Product: '<S10>/Product7'
     *  Signum: '<S12>/Sign1'
     */
    bpIndices_1[0U] = plook_binx(rtb_Product_h5, rtCP__CALookupTable_bp01Data_n,
      9U, &rtb_Switch_d_idx_1);
    rtb_Sum_el[0U] = rtb_Switch_d_idx_1;
    bpIndices_1[1U] = plook_binx(rtb_Gain_oa, rtCP__CALookupTable_bp02Data_h, 2U,
      &rtb_Switch_d_idx_1);
    rtb_Sum_el[1U] = rtb_Switch_d_idx_1;
    bpIndices_1[2U] = plook_binx(autocodePlant_B->Backlash[1] * rtb_Sign1_e,
      rtCP__CALookupTable_bp03Data_f, 4U, &rtb_Switch_d_idx_1);
    rtb_Sum_el[2U] = rtb_Switch_d_idx_1;
    rtb_Sign1_i = intrp3d_l_pw(bpIndices_1, rtb_Sum_el,
      rtCP__CALookupTable_tableData_b, rtCP__CALookupTable_dimSizes_c);

    /* Product: '<S10>/Product' */
    rtb_Product1_hx = rtb_UnaryMinus1_k4 * rtb_UnaryMinus_a;

    /* UnaryMinus: '<S10>/Unary Minus' incorporates:
     *  Constant: '<S10>/   '
     *  Product: '<S10>/Product1'
     */
    rtb_Sign1_i = -(rtb_Sign1_i * rtb_Product1_hx * 0.018);

    /* Lookup_n-D: '<S10>/CN Lookup Table' incorporates:
     *  Gain: '<S45>/Gain'
     *  Product: '<S10>/Product5'
     *  Signum: '<S12>/Sign1'
     */
    bpIndices_2[0U] = plook_binx(rtb_Product_h5, rtCP__CNLookupTable_bp01Data_f,
      9U, &rtb_Switch_d_idx_1);
    rtb_Sum_n3[0U] = rtb_Switch_d_idx_1;
    bpIndices_2[1U] = plook_binx(rtb_Gain_oa, rtCP__CNLookupTable_bp02Data_a, 2U,
      &rtb_Switch_d_idx_1);
    rtb_Sum_n3[1U] = rtb_Switch_d_idx_1;
    bpIndices_2[2U] = plook_binx(autocodePlant_B->Backlash[1] * rtb_Sign1_e,
      rtCP__CNLookupTable_bp03Data_p, 4U, &rtb_Switch_d_idx_1);
    rtb_Sum_n3[2U] = rtb_Switch_d_idx_1;
    rtb_Product_h5 = intrp3d_l_pw(bpIndices_2, rtb_Sum_n3,
      rtCP__CNLookupTable_tableData_f, rtCP__CNLookupTable_dimSizes_e);

    /* UnaryMinus: '<S10>/Unary Minus1' incorporates:
     *  Constant: '<S10>/ '
     *  Product: '<S10>/Product2'
     */
    rtb_UnaryMinus1_k4 = -(rtb_Product_h5 * rtb_Product1_hx * 0.018);

    /* Sum: '<S10>/Sum1' incorporates:
     *  Product: '<S10>/Product3'
     *  Product: '<S10>/Product4'
     *  SignalConversion generated from: '<S10>/Dot Product2'
     */
    rtb_Sum1_ny[0] = rtb_UnaryMinus1_k4 * autocodePlant_ConstB.Sum_m *
      rtb_Sign1_e + rtb_Sign1_i * autocodePlant_ConstB.Sum_k3;
    rtb_Sum1_ny[1] = rtb_UnaryMinus1_k4 * autocodePlant_ConstB.Sum_b1 *
      rtb_Sign1_e + rtb_Sign1_i * autocodePlant_ConstB.Sum_cv;
    rtb_Sum1_ny[2] = rtb_UnaryMinus1_k4 * autocodePlant_ConstB.Sum_k *
      rtb_Sign1_e + rtb_Sign1_i * autocodePlant_ConstB.Sum_b1v;

    /* Sum: '<S42>/Sum' incorporates:
     *  Product: '<S42>/Element Product'
     */
    rtb_Sum_k[0] = autocodePlant_ConstB.Subtract1_m[1] * rtb_Sum1_ny[2] -
      rtb_Sum1_ny[1] * autocodePlant_ConstB.Subtract1_m[2];
    rtb_Sum_k[1] = rtb_Sum1_ny[0] * autocodePlant_ConstB.Subtract1_m[2] -
      autocodePlant_ConstB.Subtract1_m[0] * rtb_Sum1_ny[2];
    rtb_Sum_k[2] = autocodePlant_ConstB.Subtract1_m[0] * rtb_Sum1_ny[1] -
      rtb_Sum1_ny[0] * autocodePlant_ConstB.Subtract1_m[1];

    /* Sum: '<S11>/Sum' incorporates:
     *  Product: '<S61>/Element Product'
     *  Sum: '<S61>/Sum'
     */
    rtb_Sign1_i = (rtb_VectorConcatenate_h[1] *
                   autocodePlant_ConstB.Subtract1_k[2] -
                   autocodePlant_ConstB.Subtract1_k[1] *
                   rtb_VectorConcatenate_h[2]) + rtb_VectorConcatenate[0];
    rtb_Sum_el[0] = rtb_Sign1_i;

    /* Product: '<S11>/Product8' */
    rtb_Switch_d_idx_1 = rtb_Sign1_i * autocodePlant_ConstB.Sum2_iw[0];

    /* Sum: '<S11>/Sum' incorporates:
     *  Product: '<S61>/Element Product'
     *  Sum: '<S61>/Sum'
     */
    rtb_Product_h5 = (autocodePlant_ConstB.Subtract1_k[0] *
                      rtb_VectorConcatenate_h[2] - rtb_VectorConcatenate_h[0] *
                      autocodePlant_ConstB.Subtract1_k[2]) +
      rtb_VectorConcatenate[1];
    rtb_Sum_el[1] = rtb_Product_h5;

    /* Product: '<S11>/Product8' */
    rtb_UnaryMinus1_k4 = rtb_Product_h5 * autocodePlant_ConstB.Sum2_iw[1];

    /* Sum: '<S11>/Sum' incorporates:
     *  Product: '<S61>/Element Product'
     *  Sum: '<S4>/Sum2'
     *  Sum: '<S61>/Sum'
     */
    rtb_Product2_ml = (rtb_VectorConcatenate_h[0] *
                       autocodePlant_ConstB.Subtract1_k[1] -
                       autocodePlant_ConstB.Subtract1_k[0] *
                       rtb_VectorConcatenate_h[1]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_el[2] = rtb_Product2_ml;

    /* Product: '<S11>/Product8' */
    rtb_Switch_d_idx_2 = rtb_Product2_ml * autocodePlant_ConstB.Sum2_iw[2];

    /* DotProduct: '<S11>/Dot Product1' */
    rtb_Sum = (rtb_Switch_d_idx_1 * rtb_Switch_d_idx_1 + rtb_UnaryMinus1_k4 *
               rtb_UnaryMinus1_k4) + rtb_Switch_d_idx_2 * rtb_Switch_d_idx_2;

    /* Switch: '<S58>/Switch' incorporates:
     *  Constant: '<S58>/Constant4'
     *  Constant: '<S58>/Constant5'
     */
    if (rtb_a >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S11>/Dot Product4' incorporates:
     *  DotProduct: '<S11>/Dot Product3'
     */
    rtb_UnaryMinus1_o = (rtb_Sign1_i * rtb_Sign1_i + rtb_Product_h5 *
                         rtb_Product_h5) + rtb_Product2_ml * rtb_Product2_ml;

    /* Product: '<S11>/Divide1' incorporates:
     *  DotProduct: '<S11>/Dot Product4'
     *  Product: '<S58>/Product'
     *  Sqrt: '<S11>/Sqrt1'
     *  Switch: '<S58>/Switch'
     */
    rtb_Product1_hx = sqrt(rtb_UnaryMinus1_o) / ((real_T)i * rtb_Gain_el);

    /* Switch: '<S60>/Switch' incorporates:
     *  Constant: '<S60>/Constant4'
     *  Constant: '<S60>/Constant5'
     *  DotProduct: '<S11>/Dot Product1'
     */
    if (rtb_Sum >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S11>/Divide' incorporates:
     *  Constant: '<S60>/Constant'
     *  DotProduct: '<S11>/Dot Product'
     *  DotProduct: '<S11>/Dot Product1'
     *  MinMax: '<S60>/Max'
     *  Product: '<S60>/Product'
     *  SignalConversion generated from: '<S11>/Dot Product'
     *  Sqrt: '<S11>/Sqrt'
     *  Switch: '<S60>/Switch'
     */
    rtb_Sum = ((autocodePlant_ConstB.Sum_a * rtb_Switch_d_idx_1 +
                autocodePlant_ConstB.Sum_ia * rtb_UnaryMinus1_k4) +
               autocodePlant_ConstB.Sum_bt * rtb_Switch_d_idx_2) / sqrt((real_T)
      i * fmax(1.0E-6, rtb_Sum));

    /* Saturate: '<S11>/Saturation' */
    if (rtb_Sum > 1.0) {
      rtb_Sum = 1.0;
    } else if (rtb_Sum < -1.0) {
      rtb_Sum = -1.0;
    }

    /* Gain: '<S65>/Gain' incorporates:
     *  Saturate: '<S11>/Saturation'
     *  Trigonometry: '<S11>/Acos'
     */
    rtb_UnaryMinus1_k4 = 57.29577951308232 * acos(rtb_Sum);

    /* DotProduct: '<S11>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S11>/Dot Product2'
     *  Sum: '<S11>/Sum'
     */
    rtb_Switch_d_idx_1 = (autocodePlant_ConstB.Sum_o * rtb_Sign1_i +
                          autocodePlant_ConstB.Sum_er * rtb_Product_h5) +
      autocodePlant_ConstB.Sum_g * rtb_Product2_ml;

    /* Switch: '<S59>/Switch' incorporates:
     *  Constant: '<S59>/Constant4'
     *  Constant: '<S59>/Constant5'
     *  DotProduct: '<S11>/Dot Product2'
     */
    if (rtb_Switch_d_idx_1 >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S59>/Product' incorporates:
     *  Abs: '<S59>/Abs'
     *  Constant: '<S59>/Constant'
     *  DotProduct: '<S11>/Dot Product2'
     *  MinMax: '<S59>/Max'
     *  Switch: '<S59>/Switch'
     */
    rtb_Switch_d_idx_1 = (real_T)i * fmax(1.0E-6, fabs(rtb_Switch_d_idx_1));

    /* Signum: '<S11>/Sign1' */
    if (rtIsNaN(rtb_Switch_d_idx_1)) {
      rtb_Sign1_i = (rtNaN);
    } else if (rtb_Switch_d_idx_1 < 0.0) {
      rtb_Sign1_i = -1.0;
    } else {
      rtb_Sign1_i = (rtb_Switch_d_idx_1 > 0.0);
    }

    /* End of Signum: '<S11>/Sign1' */

    /* Lookup_n-D: '<S11>/CA Lookup Table' incorporates:
     *  Gain: '<S65>/Gain'
     *  Product: '<S11>/Product7'
     *  Product: '<S193>/Product1'
     */
    bpIndices_3[0U] = plook_binx(rtb_Product1_hx, rtCP__CALookupTable_bp01Data_f,
      9U, &rtb_Switch_d_idx_1);
    rtb_Sum_aw[0U] = rtb_Switch_d_idx_1;
    bpIndices_3[1U] = plook_binx(rtb_UnaryMinus1_k4,
      rtCP__CALookupTable_bp02Data_e, 2U, &rtb_Switch_d_idx_1);
    rtb_Sum_aw[1U] = rtb_Switch_d_idx_1;
    bpIndices_3[2U] = plook_binx(autocodePlant_B->Backlash[2] * rtb_Sign1_i,
      rtCP__CALookupTable_bp03Data_fn, 4U, &rtb_Switch_d_idx_1);
    rtb_Sum_aw[2U] = rtb_Switch_d_idx_1;
    rtb_Product_h5 = intrp3d_l_pw(bpIndices_3, rtb_Sum_aw,
      rtCP__CALookupTable_tableData_n, rtCP__CALookupTable_dimSizes_e);

    /* Product: '<S11>/Product' */
    rtb_Product3_ax = rtb_UnaryMinus1_o * rtb_UnaryMinus_a;

    /* UnaryMinus: '<S11>/Unary Minus' incorporates:
     *  Constant: '<S11>/   '
     *  Product: '<S11>/Product1'
     */
    rtb_Product_h5 = -(rtb_Product_h5 * rtb_Product3_ax * 0.018);

    /* Lookup_n-D: '<S11>/CN Lookup Table' incorporates:
     *  Gain: '<S65>/Gain'
     *  Product: '<S11>/Product5'
     *  Product: '<S193>/Product1'
     */
    bpIndices_4[0U] = plook_binx(rtb_Product1_hx, rtCP__CNLookupTable_bp01Data_n,
      9U, &rtb_Switch_d_idx_1);
    rtb_Sum_mu[0U] = rtb_Switch_d_idx_1;
    bpIndices_4[1U] = plook_binx(rtb_UnaryMinus1_k4,
      rtCP__CNLookupTable_bp02Data_i, 2U, &rtb_Switch_d_idx_1);
    rtb_Sum_mu[1U] = rtb_Switch_d_idx_1;
    bpIndices_4[2U] = plook_binx(autocodePlant_B->Backlash[2] * rtb_Sign1_i,
      rtCP__CNLookupTable_bp03Data_l, 4U, &rtb_Switch_d_idx_1);
    rtb_Sum_mu[2U] = rtb_Switch_d_idx_1;
    rtb_Product1_hx = intrp3d_l_pw(bpIndices_4, rtb_Sum_mu,
      rtCP__CNLookupTable_tableData_j, rtCP__CNLookupTable_dimSizes_ex);

    /* UnaryMinus: '<S11>/Unary Minus1' incorporates:
     *  Constant: '<S11>/ '
     *  Product: '<S11>/Product2'
     */
    rtb_UnaryMinus1_o = -(rtb_Product1_hx * rtb_Product3_ax * 0.018);

    /* Sum: '<S11>/Sum1' incorporates:
     *  Product: '<S11>/Product3'
     *  Product: '<S11>/Product4'
     *  SignalConversion generated from: '<S11>/Dot Product2'
     */
    rtb_Sum1_lp[0] = rtb_UnaryMinus1_o * autocodePlant_ConstB.Sum_o *
      rtb_Sign1_i + rtb_Product_h5 * autocodePlant_ConstB.Sum_a;
    rtb_Sum1_lp[1] = rtb_UnaryMinus1_o * autocodePlant_ConstB.Sum_er *
      rtb_Sign1_i + rtb_Product_h5 * autocodePlant_ConstB.Sum_ia;
    rtb_Sum1_lp[2] = rtb_UnaryMinus1_o * autocodePlant_ConstB.Sum_g *
      rtb_Sign1_i + rtb_Product_h5 * autocodePlant_ConstB.Sum_bt;

    /* Sum: '<S62>/Sum' incorporates:
     *  Product: '<S62>/Element Product'
     */
    rtb_Sum_n3[0] = autocodePlant_ConstB.Subtract1_k[1] * rtb_Sum1_lp[2] -
      rtb_Sum1_lp[1] * autocodePlant_ConstB.Subtract1_k[2];
    rtb_Sum_n3[1] = rtb_Sum1_lp[0] * autocodePlant_ConstB.Subtract1_k[2] -
      autocodePlant_ConstB.Subtract1_k[0] * rtb_Sum1_lp[2];
    rtb_Sum_n3[2] = autocodePlant_ConstB.Subtract1_k[0] * rtb_Sum1_lp[1] -
      rtb_Sum1_lp[0] * autocodePlant_ConstB.Subtract1_k[1];

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S81>/Element Product'
     *  Sum: '<S81>/Sum'
     */
    rtb_Product_h5 = (rtb_VectorConcatenate_h[1] *
                      autocodePlant_ConstB.Subtract1_j[2] -
                      autocodePlant_ConstB.Subtract1_j[1] *
                      rtb_VectorConcatenate_h[2]) + rtb_VectorConcatenate[0];
    rtb_Sum_aw[0] = rtb_Product_h5;

    /* Product: '<S12>/Product8' */
    rtb_Product1_hx = rtb_Product_h5 * autocodePlant_ConstB.Sum2_ayz[0];

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S81>/Element Product'
     *  Sum: '<S81>/Sum'
     */
    rtb_Switch_d_idx_1 = (autocodePlant_ConstB.Subtract1_j[0] *
                          rtb_VectorConcatenate_h[2] - rtb_VectorConcatenate_h[0]
                          * autocodePlant_ConstB.Subtract1_j[2]) +
      rtb_VectorConcatenate[1];
    rtb_Sum_aw[1] = rtb_Switch_d_idx_1;

    /* Product: '<S12>/Product8' */
    rtb_UnaryMinus1_o = rtb_Switch_d_idx_1 * autocodePlant_ConstB.Sum2_ayz[1];

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S81>/Element Product'
     *  Sum: '<S4>/Sum2'
     *  Sum: '<S81>/Sum'
     */
    rtb_Switch_d_idx_2 = (rtb_VectorConcatenate_h[0] *
                          autocodePlant_ConstB.Subtract1_j[1] -
                          autocodePlant_ConstB.Subtract1_j[0] *
                          rtb_VectorConcatenate_h[1]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_aw[2] = rtb_Switch_d_idx_2;

    /* Product: '<S12>/Product8' */
    rtb_Sum = rtb_Switch_d_idx_2 * autocodePlant_ConstB.Sum2_ayz[2];

    /* DotProduct: '<S12>/Dot Product1' */
    rtb_Sum1_n = (rtb_Product1_hx * rtb_Product1_hx + rtb_UnaryMinus1_o *
                  rtb_UnaryMinus1_o) + rtb_Sum * rtb_Sum;

    /* Switch: '<S78>/Switch' incorporates:
     *  Constant: '<S78>/Constant4'
     *  Constant: '<S78>/Constant5'
     */
    if (rtb_a >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S12>/Dot Product4' incorporates:
     *  DotProduct: '<S12>/Dot Product3'
     */
    rtb_Product2_ml = (rtb_Product_h5 * rtb_Product_h5 + rtb_Switch_d_idx_1 *
                       rtb_Switch_d_idx_1) + rtb_Switch_d_idx_2 *
      rtb_Switch_d_idx_2;

    /* Product: '<S12>/Divide1' incorporates:
     *  DotProduct: '<S12>/Dot Product4'
     *  Product: '<S78>/Product'
     *  Sqrt: '<S12>/Sqrt1'
     *  Switch: '<S78>/Switch'
     */
    rtb_Product3_ax = sqrt(rtb_Product2_ml) / ((real_T)i * rtb_Gain_el);

    /* Switch: '<S80>/Switch' incorporates:
     *  Constant: '<S80>/Constant4'
     *  Constant: '<S80>/Constant5'
     *  DotProduct: '<S12>/Dot Product1'
     */
    if (rtb_Sum1_n >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S12>/Divide' incorporates:
     *  Constant: '<S80>/Constant'
     *  DotProduct: '<S12>/Dot Product'
     *  DotProduct: '<S12>/Dot Product1'
     *  MinMax: '<S80>/Max'
     *  Product: '<S80>/Product'
     *  SignalConversion generated from: '<S12>/Dot Product'
     *  Sqrt: '<S12>/Sqrt'
     *  Switch: '<S80>/Switch'
     */
    rtb_Sum = ((autocodePlant_ConstB.Sum_dx * rtb_Product1_hx +
                autocodePlant_ConstB.Sum_o3 * rtb_UnaryMinus1_o) +
               autocodePlant_ConstB.Sum_j * rtb_Sum) / sqrt((real_T)i * fmax
      (1.0E-6, rtb_Sum1_n));

    /* Saturate: '<S12>/Saturation' */
    if (rtb_Sum > 1.0) {
      rtb_Sum = 1.0;
    } else if (rtb_Sum < -1.0) {
      rtb_Sum = -1.0;
    }

    /* Gain: '<S85>/Gain' incorporates:
     *  Saturate: '<S12>/Saturation'
     *  Trigonometry: '<S12>/Acos'
     */
    rtb_UnaryMinus1_o = 57.29577951308232 * acos(rtb_Sum);

    /* DotProduct: '<S12>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S12>/Dot Product2'
     *  Sum: '<S12>/Sum'
     */
    rtb_Product1_hx = (autocodePlant_ConstB.Sum_d * rtb_Product_h5 +
                       autocodePlant_ConstB.Sum_b4 * rtb_Switch_d_idx_1) +
      autocodePlant_ConstB.Sum_ln * rtb_Switch_d_idx_2;

    /* Switch: '<S79>/Switch' incorporates:
     *  Constant: '<S79>/Constant4'
     *  Constant: '<S79>/Constant5'
     *  DotProduct: '<S12>/Dot Product2'
     */
    if (rtb_Product1_hx >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S79>/Product' incorporates:
     *  Abs: '<S79>/Abs'
     *  Constant: '<S79>/Constant'
     *  DotProduct: '<S12>/Dot Product2'
     *  MinMax: '<S79>/Max'
     *  Switch: '<S79>/Switch'
     */
    rtb_Switch_d_idx_1 = (real_T)i * fmax(1.0E-6, fabs(rtb_Product1_hx));

    /* Signum: '<S12>/Sign1' */
    if (rtIsNaN(rtb_Switch_d_idx_1)) {
      rtb_Product_h5 = (rtNaN);
    } else if (rtb_Switch_d_idx_1 < 0.0) {
      rtb_Product_h5 = -1.0;
    } else {
      rtb_Product_h5 = (rtb_Switch_d_idx_1 > 0.0);
    }

    /* End of Signum: '<S12>/Sign1' */

    /* Lookup_n-D: '<S12>/CA Lookup Table' incorporates:
     *  Gain: '<S85>/Gain'
     *  Product: '<S12>/Product7'
     *  Product: '<S193>/Product3'
     */
    bpIndices_5[0U] = plook_binx(rtb_Product3_ax, rtCP__CALookupTable_bp01Data_k,
      9U, &rtb_Switch_d_idx_1);
    rtb_Product6_f[0U] = rtb_Switch_d_idx_1;
    bpIndices_5[1U] = plook_binx(rtb_UnaryMinus1_o,
      rtCP__CALookupTable_bp02Data_f, 2U, &rtb_Switch_d_idx_1);
    rtb_Product6_f[1U] = rtb_Switch_d_idx_1;
    bpIndices_5[2U] = plook_binx(autocodePlant_B->Backlash[3] * rtb_Product_h5,
      rtCP__CALookupTable_bp03Data_b, 4U, &rtb_Switch_d_idx_1);
    rtb_Product6_f[2U] = rtb_Switch_d_idx_1;
    rtb_Product1_hx = intrp3d_l_pw(bpIndices_5, rtb_Product6_f,
      rtCP__CALookupTable_tableData_l, rtCP__CALookupTable_dimSizes_a);

    /* Product: '<S12>/Product' */
    rtb_Product2_ml *= rtb_UnaryMinus_a;

    /* UnaryMinus: '<S12>/Unary Minus' incorporates:
     *  Constant: '<S12>/   '
     *  Product: '<S12>/Product1'
     */
    rtb_Switch_d_idx_2 = -(rtb_Product1_hx * rtb_Product2_ml * 0.018);

    /* Lookup_n-D: '<S12>/CN Lookup Table' incorporates:
     *  Gain: '<S85>/Gain'
     *  Product: '<S12>/Product5'
     *  Product: '<S193>/Product3'
     */
    bpIndices_6[0U] = plook_binx(rtb_Product3_ax, rtCP__CNLookupTable_bp01Data_d,
      9U, &rtb_Switch_d_idx_1);
    rtb_finMomentArm_m[0U] = rtb_Switch_d_idx_1;
    bpIndices_6[1U] = plook_binx(rtb_UnaryMinus1_o,
      rtCP__CNLookupTable_bp02Data_av, 2U, &rtb_Switch_d_idx_1);
    rtb_finMomentArm_m[1U] = rtb_Switch_d_idx_1;
    bpIndices_6[2U] = plook_binx(autocodePlant_B->Backlash[3] * rtb_Product_h5,
      rtCP__CNLookupTable_bp03Data_g, 4U, &rtb_Switch_d_idx_1);
    rtb_finMomentArm_m[2U] = rtb_Switch_d_idx_1;
    rtb_Product3_ax = intrp3d_l_pw(bpIndices_6, rtb_finMomentArm_m,
      rtCP__CNLookupTable_tableData_d, rtCP__CNLookupTable_dimSizes_h);

    /* UnaryMinus: '<S12>/Unary Minus1' incorporates:
     *  Constant: '<S12>/ '
     *  Product: '<S12>/Product2'
     */
    rtb_Product2_ml = -(rtb_Product3_ax * rtb_Product2_ml * 0.018);

    /* Sum: '<S12>/Sum1' incorporates:
     *  Product: '<S12>/Product3'
     *  Product: '<S12>/Product4'
     *  SignalConversion generated from: '<S12>/Dot Product2'
     */
    rtb_Sum1_b[0] = rtb_Product2_ml * autocodePlant_ConstB.Sum_d *
      rtb_Product_h5 + rtb_Switch_d_idx_2 * autocodePlant_ConstB.Sum_dx;
    rtb_Sum1_b[1] = rtb_Product2_ml * autocodePlant_ConstB.Sum_b4 *
      rtb_Product_h5 + rtb_Switch_d_idx_2 * autocodePlant_ConstB.Sum_o3;
    rtb_Sum1_b[2] = rtb_Product2_ml * autocodePlant_ConstB.Sum_ln *
      rtb_Product_h5 + rtb_Switch_d_idx_2 * autocodePlant_ConstB.Sum_j;

    /* Sum: '<S82>/Sum' incorporates:
     *  Product: '<S82>/Element Product'
     */
    rtb_Sum_mu[0] = autocodePlant_ConstB.Subtract1_j[1] * rtb_Sum1_b[2] -
      rtb_Sum1_b[1] * autocodePlant_ConstB.Subtract1_j[2];
    rtb_Sum_mu[1] = rtb_Sum1_b[0] * autocodePlant_ConstB.Subtract1_j[2] -
      autocodePlant_ConstB.Subtract1_j[0] * rtb_Sum1_b[2];
    rtb_Sum_mu[2] = autocodePlant_ConstB.Subtract1_j[0] * rtb_Sum1_b[1] -
      rtb_Sum1_b[0] * autocodePlant_ConstB.Subtract1_j[1];

    /* DotProduct: '<S8>/Dot Product1' incorporates:
     *  DotProduct: '<S8>/Dot Product4'
     *  Math: '<S16>/Math Function'
     *  Sum: '<S4>/Sum2'
     */
    rtb_Sum1_n = rtb_VectorConcatenate[1] * rtb_VectorConcatenate[1];
    rtb_Product3_ax = rtb_TmpSignalConversionAtProd_0 *
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product1_hx = (rtb_VectorConcatenate[0] * rtb_VectorConcatenate[0] +
                       rtb_Sum1_n) + rtb_Product3_ax;

    /* Switch: '<S14>/Switch' incorporates:
     *  Constant: '<S14>/Constant4'
     *  Constant: '<S14>/Constant5'
     */
    if (rtb_a >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* Product: '<S8>/Divide1' incorporates:
     *  DotProduct: '<S8>/Dot Product4'
     *  Product: '<S14>/Product'
     *  Sqrt: '<S8>/Sqrt1'
     *  Switch: '<S14>/Switch'
     */
    rtb_Product2_ml = sqrt(rtb_Product1_hx) / ((real_T)i * rtb_Gain_el);

    /* Switch: '<S13>/Switch' incorporates:
     *  Constant: '<S13>/Constant4'
     *  Constant: '<S13>/Constant5'
     *  DotProduct: '<S8>/Dot Product1'
     */
    if (rtb_Product1_hx >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S8>/Dot Product' incorporates:
     *  DotProduct: '<S8>/Dot Product4'
     *  Product: '<S16>/Product'
     *  Sum: '<S4>/Sum2'
     *  Switch: '<S16>/Switch'
     */
    rtb_Switch_d_idx_1 = 0.0 * rtb_VectorConcatenate[1];
    rtb_Switch_d_idx_2 = 0.0 * rtb_TmpSignalConversionAtProd_0;

    /* Product: '<S8>/Divide' incorporates:
     *  Constant: '<S13>/Constant'
     *  DotProduct: '<S8>/Dot Product'
     *  DotProduct: '<S8>/Dot Product1'
     *  DotProduct: '<S8>/Dot Product4'
     *  MinMax: '<S13>/Max'
     *  Product: '<S13>/Product'
     *  Sqrt: '<S8>/Sqrt'
     *  Switch: '<S13>/Switch'
     */
    rtb_Sum = ((rtb_Switch_d_idx_1 + rtb_VectorConcatenate[0]) +
               rtb_Switch_d_idx_2) / sqrt((real_T)i * fmax(1.0E-6,
      rtb_Product1_hx));

    /* Saturate: '<S8>/Saturation' */
    if (rtb_Sum > 1.0) {
      rtb_Sum = 1.0;
    } else if (rtb_Sum < -1.0) {
      rtb_Sum = -1.0;
    }

    /* Gain: '<S17>/Gain' incorporates:
     *  Saturate: '<S8>/Saturation'
     *  Trigonometry: '<S8>/Acos'
     */
    rtb_Gain_el = 57.29577951308232 * acos(rtb_Sum);

    /* Sum: '<S8>/Sum' incorporates:
     *  Constant: '<S3>/Constant'
     *  Gain: '<S17>/Gain'
     *  Lookup_n-D: '<S8>/CP Lookup Table'
     *  Product: '<S193>/Product2'
     */
    rtb_Sum = 1.8117856235712473 - look2_binlcpw(rtb_Product2_ml, rtb_Gain_el,
      rtCP__CPLookupTable_bp01Data, rtCP__CPLookupTable_bp02Data,
      rtCP__CPLookupTable_tableData, rtCP__CPLookupTable_maxIndex, 10U);

    /* Product: '<S8>/Product6' incorporates:
     *  Constant: '<S8>/Constant3'
     *  DotProduct: '<S8>/Dot Product3'
     */
    rtb_Switch_d_idx_0 = rtb_VectorConcatenate[0] * 0.0;

    /* Product: '<S8>/Product5' incorporates:
     *  Constant: '<S8>/Constant2'
     */
    rtb_FlatEarthtoLLA_o1_idx_0 = rtb_Sum * 0.0;

    /* Product: '<S8>/Product' incorporates:
     *  DotProduct: '<S8>/Dot Product3'
     */
    rtb_Product1_hx *= rtb_UnaryMinus_a;

    /* UnaryMinus: '<S8>/Unary Minus' incorporates:
     *  Constant: '<S8>/   '
     *  Gain: '<S17>/Gain'
     *  Lookup_n-D: '<S8>/CA Lookup Table'
     *  Product: '<S193>/Product2'
     *  Product: '<S8>/Product1'
     */
    rtb_UnaryMinus_a = -(look2_binlxpw(rtb_Product2_ml, rtb_Gain_el,
      rtCP__CALookupTable_bp01Data_j, rtCP__CALookupTable_bp02Data_b,
      rtCP__CALookupTable_tableData_e, rtCP__CALookupTable_maxIndex_j, 10U) *
                         rtb_Product1_hx * 0.018);

    /* UnaryMinus: '<S8>/Unary Minus1' incorporates:
     *  Constant: '<S8>/ '
     *  Gain: '<S17>/Gain'
     *  Lookup_n-D: '<S8>/CN Lookup Table'
     *  Product: '<S193>/Product2'
     *  Product: '<S8>/Product2'
     */
    rtb_Product1_hx = -(look2_binlxpw(rtb_Product2_ml, rtb_Gain_el,
      rtCP__CNLookupTable_bp01Data_a, rtCP__CNLookupTable_bp02Data_o,
      rtCP__CNLookupTable_tableData_i, rtCP__CNLookupTable_maxIndex_a, 10U) *
                        rtb_Product1_hx * 0.018);

    /* Math: '<S16>/Math Function1' incorporates:
     *  Math: '<S16>/Math Function'
     *  Sum: '<S16>/Sum of Elements'
     *
     * About '<S16>/Math Function1':
     *  Operator: sqrt
     */
    rtb_Product2_ml = sqrt((rtb_Switch_d_idx_0 * rtb_Switch_d_idx_0 + rtb_Sum1_n)
      + rtb_Product3_ax);

    /* Switch: '<S16>/Switch' incorporates:
     *  Constant: '<S16>/Constant'
     *  DotProduct: '<S8>/Dot Product3'
     *  Product: '<S16>/Product'
     *  Product: '<S8>/Product6'
     *  Sum: '<S4>/Sum2'
     */
    if (rtb_Product2_ml > 1.0E-6) {
      rtb_Switch_d_idx_1 = rtb_VectorConcatenate[1];
      rtb_Switch_d_idx_2 = rtb_TmpSignalConversionAtProd_0;
    } else {
      rtb_Switch_d_idx_0 *= 0.0;
      rtb_Product2_ml = 1.0;
    }

    /* Sum: '<S8>/Sum1' incorporates:
     *  Product: '<S16>/Divide'
     *  Product: '<S8>/Product3'
     *  Product: '<S8>/Product4'
     */
    rtb_Product6_f[0] = rtb_Switch_d_idx_0 / rtb_Product2_ml * rtb_Product1_hx +
      rtb_UnaryMinus_a;

    /* Product: '<S8>/Product3' incorporates:
     *  Constant: '<S8>/Constant'
     */
    rtb_TmpSignalConversionAtProd_0 = rtb_UnaryMinus_a * 0.0;

    /* Sum: '<S8>/Sum1' incorporates:
     *  Product: '<S16>/Divide'
     *  Product: '<S8>/Product3'
     *  Product: '<S8>/Product4'
     */
    rtb_Product6_f[1] = rtb_Switch_d_idx_1 / rtb_Product2_ml * rtb_Product1_hx +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product6_f[2] = rtb_Switch_d_idx_2 / rtb_Product2_ml * rtb_Product1_hx +
      rtb_TmpSignalConversionAtProd_0;

    /* Product: '<S15>/Element Product' incorporates:
     *  Product: '<S8>/Product5'
     */
    rtb_TmpSignalConversionAtProd_0 = rtb_Product6_f[0] *
      rtb_FlatEarthtoLLA_o1_idx_0;

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_a = rtb_FlatEarthtoLLA_o1_idx_0 * rtb_Product6_f[2] -
      rtb_Product6_f[1] * rtb_FlatEarthtoLLA_o1_idx_0;
    rtb_finMomentArm_m[0] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[0] = (((rtb_Sum_hp[0] + rtb_Sum_k[0]) + rtb_Sum_n3[0]) + rtb_Sum_mu
                  [0]) + rtb_UnaryMinus_a;
    rtb_Add[3] = (((rtb_Sum1_p2[0] + rtb_Sum1_ny[0]) + rtb_Sum1_lp[0]) +
                  rtb_Sum1_b[0]) + rtb_Product6_f[0];

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_a = rtb_TmpSignalConversionAtProd_0 - rtb_Sum *
      rtb_Product6_f[2];
    rtb_finMomentArm_m[1] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[1] = (((rtb_Sum_hp[1] + rtb_Sum_k[1]) + rtb_Sum_n3[1]) + rtb_Sum_mu
                  [1]) + rtb_UnaryMinus_a;
    rtb_Add[4] = (((rtb_Sum1_p2[1] + rtb_Sum1_ny[1]) + rtb_Sum1_lp[1]) +
                  rtb_Sum1_b[1]) + rtb_Product6_f[1];

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_a = rtb_Sum * rtb_Product6_f[1] -
      rtb_TmpSignalConversionAtProd_0;
    rtb_finMomentArm_m[2] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[2] = (((rtb_Sum_hp[2] + rtb_Sum_k[2]) + rtb_Sum_n3[2]) + rtb_Sum_mu
                  [2]) + rtb_UnaryMinus_a;
    rtb_Add[5] = (((rtb_Sum1_p2[2] + rtb_Sum1_ny[2]) + rtb_Sum1_lp[2]) +
                  rtb_Sum1_b[2]) + rtb_Product6_f[2];

    /* Sum: '<S5>/Sum' */
    rtb_TmpSignalConversionAtProd_0 = (autocodePlant_B->Delay +
      rtb_gravityForceBdy_N[0]) + rtb_Add[3];

    /* Logic: '<S165>/Logical Operator' */
    rtb_max_relop_c = !rtb_Compare_n;

    /* Sum: '<S165>/Sum' incorporates:
     *  Constant: '<S165>/Constant'
     *  Constant: '<S6>/Constant2'
     *  MinMax: '<S165>/Max1'
     *  Product: '<S165>/Product1'
     *  Product: '<S165>/Product2'
     *  Sum: '<S5>/Sum'
     */
    autocodePlant_B->Sum[0] = fmax((real_T)rtb_Compare_n *
      rtb_TmpSignalConversionAtProd_0, 0.0) + rtb_TmpSignalConversionAtProd_0 *
      (real_T)rtb_max_relop_c;
    autocodePlant_B->Sum[1] = (rtb_gravityForceBdy_N[1] + rtb_Add[4]) * (real_T)
      rtb_max_relop_c;
    autocodePlant_B->Sum[2] = (rtb_gravityForceBdy_N[2] + rtb_Add[5]) * (real_T)
      rtb_max_relop_c;

    /* Product: '<S163>/Divide' incorporates:
     *  Constant: '<S5>/Constant'
     *  Sum: '<S167>/Sum1'
     */
    rtb_MathFunction[0] = (autocodePlant_B->Sum[0] + autocodePlant_ConstB.Switch)
      / 17.5;
    rtb_MathFunction[1] = (autocodePlant_B->Sum[1] + autocodePlant_ConstB.Switch)
      / 17.5;
    rtb_MathFunction[2] = (autocodePlant_B->Sum[2] + autocodePlant_ConstB.Switch)
      / 17.5;

    /* Product: '<S180>/Product2' incorporates:
     *  Product: '<S193>/Product2'
     */
    rtb_Lw_idx_1 = rtb_q_na_idx_2 / rtb_pi3_tmp;

    /* Product: '<S180>/Product3' */
    rtb_Product3_ax = rtb_q_na_idx_3 / rtb_pi3_tmp;

    /* Product: '<S180>/Product1' incorporates:
     *  Product: '<S193>/Product1'
     */
    rtb_FlatEarthtoLLA_o1_idx_0 = rtb_q_na_idx_1 / rtb_pi3_tmp;

    /* Product: '<S180>/Product' incorporates:
     *  Product: '<S193>/Product'
     */
    rtb_Switch_d_idx_0 = rtb_q_na_idx_0 / rtb_pi3_tmp;

    /* Product: '<S181>/Product7' incorporates:
     *  Product: '<S182>/Product7'
     */
    rtb_Product2_ml = rtb_Product3_ax * rtb_Product3_ax;

    /* Product: '<S181>/Product' incorporates:
     *  Product: '<S180>/Product1'
     *  Product: '<S180>/Product2'
     *  Product: '<S182>/Product'
     */
    rtb_Switch_d_idx_1 = rtb_FlatEarthtoLLA_o1_idx_0 * rtb_Lw_idx_1;

    /* Product: '<S181>/Product1' incorporates:
     *  Product: '<S180>/Product'
     *  Product: '<S182>/Product1'
     */
    rtb_Switch_d_idx_2 = rtb_Switch_d_idx_0 * rtb_Product3_ax;

    /* Product: '<S181>/Product3' incorporates:
     *  Product: '<S180>/Product1'
     *  Product: '<S183>/Product'
     */
    rtb_pi3_tmp = rtb_FlatEarthtoLLA_o1_idx_0 * rtb_Product3_ax;

    /* Product: '<S181>/Product2' incorporates:
     *  Product: '<S180>/Product'
     *  Product: '<S180>/Product2'
     *  Product: '<S183>/Product1'
     */
    rtb_TmpSignalConversionAtProd_0 = rtb_Switch_d_idx_0 * rtb_Lw_idx_1;

    /* Product: '<S181>/Product6' incorporates:
     *  Product: '<S180>/Product2'
     *  Product: '<S183>/Product7'
     */
    rtb_UnaryMinus_a = rtb_Lw_idx_1 * rtb_Lw_idx_1;

    /* Gain: '<S181>/Gain2' incorporates:
     *  Constant: '<S181>/Constant'
     *  Gain: '<S194>/Gain2'
     *  Product: '<S181>/Product6'
     *  Product: '<S181>/Product7'
     *  Sum: '<S181>/Sum3'
     *  Sum: '<S194>/Sum'
     */
    rtb_Product1_hx = ((0.5 - rtb_UnaryMinus_a) - rtb_Product2_ml) * 2.0;

    /* Gain: '<S181>/Gain' incorporates:
     *  Gain: '<S194>/Gain'
     *  Product: '<S181>/Product'
     *  Product: '<S181>/Product1'
     *  Sum: '<S181>/Sum1'
     *  Sum: '<S194>/Sum'
     */
    rtb_Sum = (rtb_Switch_d_idx_1 + rtb_Switch_d_idx_2) * 2.0;

    /* Gain: '<S181>/Gain1' incorporates:
     *  Gain: '<S194>/Gain1'
     *  Product: '<S181>/Product2'
     *  Product: '<S181>/Product3'
     *  Sum: '<S181>/Sum2'
     *  Sum: '<S194>/Sum'
     */
    rtb_Sum1_n = (rtb_pi3_tmp - rtb_TmpSignalConversionAtProd_0) * 2.0;

    /* Sum: '<S173>/fBdy_mps2' incorporates:
     *  Constant: '<S173>/gNed_mps2'
     *  Gain: '<S181>/Gain'
     *  Gain: '<S181>/Gain1'
     *  Gain: '<S181>/Gain2'
     *  Product: '<S181>/Product4'
     *  Product: '<S181>/Product5'
     *  Product: '<S181>/Product8'
     *  Sum: '<S181>/Sum'
     */
    autocodePlant_B->fBdy_mps2[0] = rtb_MathFunction[0] - ((rtb_Product1_hx *
      0.0 + rtb_Sum * 0.0) + rtb_Sum1_n * 9.81);

    /* Product: '<S182>/Product3' incorporates:
     *  Product: '<S180>/Product2'
     *  Product: '<S183>/Product3'
     */
    rtb_Product3_ax *= rtb_Lw_idx_1;

    /* Product: '<S182>/Product2' incorporates:
     *  Product: '<S180>/Product'
     *  Product: '<S180>/Product1'
     *  Product: '<S183>/Product2'
     */
    rtb_Switch_d_idx_0 *= rtb_FlatEarthtoLLA_o1_idx_0;

    /* Sum: '<S182>/Sum3' incorporates:
     *  Constant: '<S182>/Constant'
     *  Product: '<S180>/Product1'
     *  Product: '<S182>/Product6'
     *  Sum: '<S183>/Sum3'
     */
    rtb_FlatEarthtoLLA_o1_idx_0 = 0.5 - rtb_FlatEarthtoLLA_o1_idx_0 *
      rtb_FlatEarthtoLLA_o1_idx_0;

    /* Gain: '<S182>/Gain2' incorporates:
     *  Gain: '<S195>/Gain2'
     *  Sum: '<S182>/Sum3'
     *  Sum: '<S195>/Sum'
     */
    rtb_Product2_ml = (rtb_FlatEarthtoLLA_o1_idx_0 - rtb_Product2_ml) * 2.0;

    /* Gain: '<S182>/Gain' incorporates:
     *  Gain: '<S195>/Gain'
     *  Sum: '<S182>/Sum1'
     *  Sum: '<S195>/Sum'
     */
    rtb_Switch_d_idx_1 = (rtb_Switch_d_idx_1 - rtb_Switch_d_idx_2) * 2.0;

    /* Gain: '<S182>/Gain1' incorporates:
     *  Gain: '<S195>/Gain1'
     *  Product: '<S182>/Product2'
     *  Product: '<S182>/Product3'
     *  Sum: '<S182>/Sum2'
     *  Sum: '<S195>/Sum'
     */
    rtb_Switch_d_idx_2 = (rtb_Switch_d_idx_0 + rtb_Product3_ax) * 2.0;

    /* Sum: '<S173>/fBdy_mps2' incorporates:
     *  Constant: '<S173>/gNed_mps2'
     *  Gain: '<S182>/Gain'
     *  Gain: '<S182>/Gain1'
     *  Gain: '<S182>/Gain2'
     *  Product: '<S182>/Product4'
     *  Product: '<S182>/Product5'
     *  Product: '<S182>/Product8'
     *  Sum: '<S182>/Sum'
     */
    autocodePlant_B->fBdy_mps2[1] = rtb_MathFunction[1] - ((rtb_Product2_ml *
      0.0 + rtb_Switch_d_idx_1 * 0.0) + rtb_Switch_d_idx_2 * 9.81);

    /* Gain: '<S183>/Gain' incorporates:
     *  Gain: '<S196>/Gain'
     *  Sum: '<S183>/Sum1'
     *  Sum: '<S196>/Sum'
     */
    rtb_pi3_tmp = (rtb_pi3_tmp + rtb_TmpSignalConversionAtProd_0) * 2.0;

    /* Gain: '<S183>/Gain1' incorporates:
     *  Gain: '<S196>/Gain1'
     *  Sum: '<S183>/Sum2'
     *  Sum: '<S196>/Sum'
     */
    rtb_TmpSignalConversionAtProd_0 = (rtb_Product3_ax - rtb_Switch_d_idx_0) *
      2.0;

    /* Gain: '<S183>/Gain2' incorporates:
     *  Gain: '<S196>/Gain2'
     *  Sum: '<S183>/Sum3'
     *  Sum: '<S196>/Sum'
     */
    rtb_UnaryMinus_a = (rtb_FlatEarthtoLLA_o1_idx_0 - rtb_UnaryMinus_a) * 2.0;

    /* Sum: '<S173>/fBdy_mps2' incorporates:
     *  Constant: '<S173>/gNed_mps2'
     *  Gain: '<S183>/Gain'
     *  Gain: '<S183>/Gain1'
     *  Gain: '<S183>/Gain2'
     *  Product: '<S183>/Product4'
     *  Product: '<S183>/Product5'
     *  Product: '<S183>/Product8'
     *  Sum: '<S183>/Sum'
     */
    autocodePlant_B->fBdy_mps2[2] = rtb_MathFunction[2] - ((rtb_pi3_tmp * 0.0 +
      rtb_TmpSignalConversionAtProd_0 * 0.0) + rtb_UnaryMinus_a * 9.81);
    if (tmp) {
      /* Product: '<S173>/scale factor and  cross-coupling' incorporates:
       *  Constant: '<S173>/Constant'
       */
      rtb_FlatEarthtoLLA_o1_idx_0 = autocodePlant_B->fBdy_mps2[1];
      rtb_Switch_d_idx_0 = autocodePlant_B->fBdy_mps2[0];
      rtb_Lw_idx_1 = autocodePlant_B->fBdy_mps2[2];

      /* Product: '<S175>/Product1' */
      rtb_sincos_o1_idx_0 = 0.0;
      rtb_sincos_o2_idx_0 = 0.0;
      rtb_Sum2_fl = 0.0;
      for (i = 0; i < 3; i++) {
        /* ZeroOrderHold: '<S173>/Zero-Order Hold' incorporates:
         *  Constant: '<S173>/Constant'
         *  Product: '<S173>/scale factor and  cross-coupling'
         *  Sum: '<S173>/sum'
         */
        rtb_ZeroOrderHold_c[i] = ((rtCP__Constant_Value_dxg[i + 3] *
          rtb_FlatEarthtoLLA_o1_idx_0 + rtCP__Constant_Value_dxg[i] *
          rtb_Switch_d_idx_0) + rtCP__Constant_Value_dxg[i + 6] * rtb_Lw_idx_1)
          + autocodePlant_B->biasnoise[i];

        /* Sum: '<S175>/bias + noise' incorporates:
         *  Gain: '<S189>/Output'
         *  RandomNumber: '<S189>/White Noise'
         */
        biasnoise_d[i] = 6.1075E-5 * autocodePlant_DW->NextOutput_i +
          rtb_ZeroOrderHold_a[i];

        /* Product: '<S175>/Product1' incorporates:
         *  Constant: '<S175>/Gs'
         *  UnitDelay: '<S175>/Unit Delay'
         */
        rtb_Product3_ax = autocodePlant_DW->UnitDelay_DSTATE_c[i];
        rtb_sincos_o1_idx_0 += rtCP__Gs_Value[3 * i] * rtb_Product3_ax;
        rtb_sincos_o2_idx_0 += rtCP__Gs_Value[3 * i + 1] * rtb_Product3_ax;
        rtb_Sum2_fl += rtCP__Gs_Value[3 * i + 2] * rtb_Product3_ax;
      }

      /* Product: '<S175>/Product1' */
      Gdependent[2] = rtb_Sum2_fl;
      Gdependent[1] = rtb_sincos_o2_idx_0;
      Gdependent[0] = rtb_sincos_o1_idx_0;

      /* Product: '<S175>/Product' incorporates:
       *  Constant: '<S175>/   '
       */
      rtb_Product3_ax = rtb_wBdy_rps[1];
      rtb_FlatEarthtoLLA_o1_idx_0 = rtb_wBdy_rps[0];
      rtb_Switch_d_idx_0 = rtb_wBdy_rps[2];
      for (i = 0; i < 3; i++) {
        /* ZeroOrderHold: '<S175>/Zero-Order Hold' incorporates:
         *  Constant: '<S175>/   '
         *  Product: '<S175>/Product'
         *  Sum: '<S175>/      '
         */
        rtb_ZeroOrderHold_a[i] = (((rtCP___Value_n[i + 3] * rtb_Product3_ax +
          rtCP___Value_n[i] * rtb_FlatEarthtoLLA_o1_idx_0) + rtCP___Value_n[i +
          6] * rtb_Switch_d_idx_0) + biasnoise_d[i]) + Gdependent[i];

        /* Gain: '<S192>/Output' incorporates:
         *  RandomNumber: '<S192>/White Noise'
         */
        autocodePlant_B->Output[i] = 140.0 * autocodePlant_DW->NextOutput_b;
      }

      /* RelationalOperator: '<S225>/Relational Operator' incorporates:
       *  Constant: '<S176>/decimal year'
       *  Memory: '<S225>/otime'
       */
      rtb_RelationalOperator = (autocodePlant_DW->otime_PreviousInput !=
        2026.6657534246576);
    }

    /* FlatEarth2LLA: '<S176>/Flat Earth to LLA' */
    rtb_Product3_ax = (rtb_posNed_m[0] - 0.0 * rtb_posNed_m[1]) /
      6.3354393272928195E+6;
    rtb_FlatEarthtoLLA_o1_idx_0 = fabs(rtb_Product3_ax);
    rtb_Switch_d_idx_0 = (0.0 * rtb_posNed_m[0] + rtb_posNed_m[1]) / 6.378137E+6
      + 0.17453292519943295;
    if (rtb_FlatEarthtoLLA_o1_idx_0 > 3.141592653589793) {
      rtb_Product3_ax = rt_modd_snf(rtb_Product3_ax + 3.141592653589793,
        6.283185307179586) - 3.141592653589793;
      rtb_FlatEarthtoLLA_o1_idx_0 = fabs(rtb_Product3_ax);
    }

    if (rtb_FlatEarthtoLLA_o1_idx_0 > 1.5707963267948966) {
      rtb_Switch_d_idx_0 += 3.141592653589793;
      if (rtIsNaN(rtb_Product3_ax)) {
        rtb_Product3_ax = (rtNaN);
      } else if (rtb_Product3_ax < 0.0) {
        rtb_Product3_ax = -1.0;
      } else {
        rtb_Product3_ax = (rtb_Product3_ax > 0.0);
      }

      rtb_Product3_ax *= 1.5707963267948966 - (rtb_FlatEarthtoLLA_o1_idx_0 -
        1.5707963267948966);
    }

    if (fabs(rtb_Switch_d_idx_0) > 3.141592653589793) {
      rtb_FlatEarthtoLLA_o1_idx_0 = rt_remd_snf(rtb_Switch_d_idx_0,
        6.283185307179586);
      rtb_Switch_d_idx_0 = rtb_FlatEarthtoLLA_o1_idx_0 - trunc
        (rtb_FlatEarthtoLLA_o1_idx_0 / 3.141592653589793) * 6.283185307179586;
    }

    rtb_FlatEarthtoLLA_o1_idx_0 = rtb_Product3_ax * 180.0 / 3.141592653589793;
    rtb_Switch_d_idx_0 = rtb_Switch_d_idx_0 * 180.0 / 3.141592653589793;

    /* Switch: '<S214>/Switch' incorporates:
     *  Abs: '<S214>/Abs'
     *  Bias: '<S214>/Bias'
     *  Bias: '<S214>/Bias1'
     *  Constant: '<S214>/Constant2'
     *  Constant: '<S217>/Constant'
     *  Math: '<S214>/Math Function1'
     *  RelationalOperator: '<S217>/Compare'
     */
    if (fabs(rtb_FlatEarthtoLLA_o1_idx_0) > 180.0) {
      rtb_Product3_ax = rt_modd_snf(rtb_FlatEarthtoLLA_o1_idx_0 + 180.0, 360.0)
        - 180.0;
    } else {
      rtb_Product3_ax = rtb_FlatEarthtoLLA_o1_idx_0;
    }

    /* End of Switch: '<S214>/Switch' */

    /* Abs: '<S210>/Abs1' */
    rtb_Lw_idx_1 = fabs(rtb_Product3_ax);

    /* RelationalOperator: '<S212>/Compare' incorporates:
     *  Constant: '<S212>/Constant'
     */
    rtb_min_relop_n = (rtb_Lw_idx_1 > 90.0);

    /* Switch: '<S204>/Switch1' incorporates:
     *  Constant: '<S204>/Constant'
     *  Constant: '<S204>/Constant1'
     */
    if (rtb_min_relop_n) {
      i = 180;
    } else {
      i = 0;
    }

    /* Sum: '<S204>/Sum' incorporates:
     *  Switch: '<S204>/Switch1'
     */
    autocodePlant_B->Switch = (real_T)i + rtb_Switch_d_idx_0;

    /* Switch: '<S211>/Switch' incorporates:
     *  Abs: '<S211>/Abs'
     *  Constant: '<S218>/Constant'
     *  RelationalOperator: '<S218>/Compare'
     */
    if (fabs(autocodePlant_B->Switch) > 180.0) {
      /* Sum: '<S204>/Sum' incorporates:
       *  Bias: '<S211>/Bias'
       *  Bias: '<S211>/Bias1'
       *  Constant: '<S211>/Constant2'
       *  Math: '<S211>/Math Function1'
       *  Switch: '<S211>/Switch'
       */
      autocodePlant_B->Switch = rt_modd_snf(autocodePlant_B->Switch + 180.0,
        360.0) - 180.0;
    }

    /* End of Switch: '<S211>/Switch' */

    /* If: '<S213>/If' incorporates:
     *  Abs: '<S213>/Abs'
     */
    rtPrevAction = autocodePlant_DW->If_ActiveSubsystem;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      rtAction = (int8_T)!(rtb_Lw_idx_1 > 0.0);
      autocodePlant_DW->If_ActiveSubsystem = rtAction;
    } else {
      rtAction = autocodePlant_DW->If_ActiveSubsystem;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&autocodePlant_M->solverInfo,
        true);
    }

    if (rtAction == 0) {
      /* Outputs for IfAction SubSystem: '<S213>/If Action Subsystem' incorporates:
       *  ActionPort: '<S215>/Action Port'
       */
      /* Merge: '<S213>/Merge' incorporates:
       *  Abs: '<S213>/Abs'
       *  Product: '<S215>/Divide'
       */
      autocodePlant_B->Merge = rtb_Product3_ax / rtb_Lw_idx_1;

      /* End of Outputs for SubSystem: '<S213>/If Action Subsystem' */

      /* Outputs for IfAction SubSystem: '<S213>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S216>/Action Port'
       */
    } else if (rtmIsMajorTimeStep(autocodePlant_M) &&
               autocodePlant_M->Timing.TaskCounters.TID[1] == 0) {
      /* Merge: '<S213>/Merge' incorporates:
       *  Constant: '<S216>/Constant'
       *  SignalConversion generated from: '<S216>/zero'
       */
      autocodePlant_B->Merge = 0.0;

      /* End of Outputs for SubSystem: '<S213>/If Action Subsystem1' */
    }

    /* End of If: '<S213>/If' */

    /* Switch: '<S210>/Switch' */
    if (rtb_min_relop_n) {
      /* Switch: '<S210>/Switch' incorporates:
       *  Bias: '<S210>/Bias'
       *  Bias: '<S210>/Bias1'
       *  Gain: '<S210>/Gain'
       *  Product: '<S210>/Divide1'
       */
      autocodePlant_B->Switch_l = (-(rtb_Lw_idx_1 - 90.0) + 90.0) *
        autocodePlant_B->Merge;
    } else {
      /* Switch: '<S210>/Switch' */
      autocodePlant_B->Switch_l = rtb_Product3_ax;
    }

    /* End of Switch: '<S210>/Switch' */

    /* UnitConversion: '<S269>/Unit Conversion' */
    /* Unit Conversion - from: deg to: rad
       Expression: output = (0.0174533*input) + (0) */
    rtb_Product3_ax = 0.017453292519943295 * autocodePlant_B->Switch;
    rtb_Lw_idx_1 = 0.017453292519943295 * autocodePlant_B->Switch_l;

    /* Trigonometry: '<S222>/sincos' */
    rtb_sincos_o1_idx_0 = sin(rtb_Product3_ax);
    rtb_sincos_o2_idx_0 = cos(rtb_Product3_ax);
    rtb_Product3_ax = sin(rtb_Lw_idx_1);
    rtb_Lw_idx_1 = cos(rtb_Lw_idx_1);

    /* Outputs for Enabled SubSystem: '<S208>/Convert from geodetic to  spherical coordinates ' incorporates:
     *  EnablePort: '<S221>/Enable'
     */
    if (tmp) {
      if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
        /* RelationalOperator: '<S224>/Relational Operator' incorporates:
         *  Memory: '<S224>/olon'
         */
        autocodePlant_DW->Convertfromgeodetictosphericalc =
          (autocodePlant_B->Switch != autocodePlant_DW->olon_PreviousInput);
      }

      /* Memory: '<S223>/olat' */
      autocodePlant_B->olat = autocodePlant_DW->olat_PreviousInput;
    }

    if (autocodePlant_DW->Convertfromgeodetictosphericalc) {
      if (rtmIsMajorTimeStep(autocodePlant_M) &&
          autocodePlant_M->Timing.TaskCounters.TID[1] == 0) {
        /* Outputs for Iterator SubSystem: '<S221>/For Iterator Subsystem' incorporates:
         *  ForIterator: '<S268>/For Iterator'
         */
        for (s268_iter = 0; s268_iter < 11; s268_iter++) {
          /* Switch: '<S268>/cp[m-1] sp[m-1]' incorporates:
           *  SignalConversion generated from: '<S221>/cp[2]'
           *  SignalConversion generated from: '<S221>/sp[2]'
           *  UnitDelay: '<S268>/Unit Delay1'
           */
          if (s268_iter > 0) {
            rtb_Sum1_ox = autocodePlant_DW->UnitDelay1_DSTATE[0];
            rtb_Product1_jv = autocodePlant_DW->UnitDelay1_DSTATE[1];
          } else {
            rtb_Sum1_ox = rtb_sincos_o2_idx_0;
            rtb_Product1_jv = rtb_sincos_o1_idx_0;
          }

          /* End of Switch: '<S268>/cp[m-1] sp[m-1]' */

          /* Sum: '<S268>/Sum2' incorporates:
           *  Product: '<S268>/Product1'
           *  Product: '<S268>/Product2'
           *  SignalConversion generated from: '<S221>/cp[2]'
           *  SignalConversion generated from: '<S221>/sp[2]'
           */
          rtb_Sum2_fl = rtb_Sum1_ox * rtb_sincos_o1_idx_0 + rtb_Product1_jv *
            rtb_sincos_o2_idx_0;

          /* Sum: '<S268>/Sum1' incorporates:
           *  Product: '<S268>/Product3'
           *  Product: '<S268>/Product8'
           *  SignalConversion generated from: '<S221>/cp[2]'
           *  SignalConversion generated from: '<S221>/sp[2]'
           */
          rtb_Sum1_ox = rtb_Sum1_ox * rtb_sincos_o2_idx_0 - rtb_Product1_jv *
            rtb_sincos_o1_idx_0;

          /* Assignment: '<S268>/Assignment' incorporates:
           *  Assignment: '<S268>/Assignment1'
           *  Constant: '<S268>/Constant'
           */
          if (s268_iter == 0) {
            memcpy(&autocodePlant_B->Assignment[0], &rtCP__Constant_Value_f[0],
                   11U * sizeof(real_T));

            /* Assignment: '<S268>/Assignment1' incorporates:
             *  Constant: '<S268>/Constant'
             *  Constant: '<S268>/Constant1'
             */
            memcpy(&autocodePlant_B->Assignment1[0], &rtCP__Constant1_Value_a[0],
                   11U * sizeof(real_T));
          }

          autocodePlant_B->Assignment[s268_iter] = rtb_Sum2_fl;

          /* End of Assignment: '<S268>/Assignment' */

          /* Assignment: '<S268>/Assignment1' */
          autocodePlant_B->Assignment1[s268_iter] = rtb_Sum1_ox;

          /* Update for UnitDelay: '<S268>/Unit Delay1' */
          autocodePlant_DW->UnitDelay1_DSTATE[0] = rtb_Sum1_ox;
          autocodePlant_DW->UnitDelay1_DSTATE[1] = rtb_Sum2_fl;
        }

        /* End of Outputs for SubSystem: '<S221>/For Iterator Subsystem' */
      }

      /* SignalConversion generated from: '<S221>/cp[13]' incorporates:
       *  Constant: '<S221>/cp[1]'
       *  SignalConversion generated from: '<S221>/cp[2]'
       */
      autocodePlant_B->OutportBufferForcp13[0] = 1.0;
      autocodePlant_B->OutportBufferForcp13[1] = rtb_sincos_o2_idx_0;

      /* SignalConversion generated from: '<S221>/sp[13]' incorporates:
       *  Constant: '<S221>/sp[1]'
       *  SignalConversion generated from: '<S221>/sp[2]'
       */
      autocodePlant_B->OutportBufferForsp13[0] = 0.0;
      autocodePlant_B->OutportBufferForsp13[1] = rtb_sincos_o1_idx_0;

      /* SignalConversion generated from: '<S221>/cp[13]' */
      memcpy(&autocodePlant_B->OutportBufferForcp13[2],
             &autocodePlant_B->Assignment1[0], 11U * sizeof(real_T));

      /* SignalConversion generated from: '<S221>/sp[13]' */
      memcpy(&autocodePlant_B->OutportBufferForsp13[2],
             &autocodePlant_B->Assignment[0], 11U * sizeof(real_T));
    }

    /* End of Outputs for SubSystem: '<S208>/Convert from geodetic to  spherical coordinates ' */

    /* Gain: '<S191>/Gain' incorporates:
     *  Constant: '<S176>/ground altitude'
     *  FlatEarth2LLA: '<S176>/Flat Earth to LLA'
     */
    autocodePlant_B->Gain = -(rtb_posNed_m[2] + 182.0) * 0.001;
    if (tmp) {
      /* Memory: '<S223>/oalt' */
      autocodePlant_B->oalt = autocodePlant_DW->oalt_PreviousInput;
    }

    /* Logic: '<S223>/Logical Operator' incorporates:
     *  RelationalOperator: '<S223>/Relational Operator'
     *  RelationalOperator: '<S223>/Relational Operator1'
     */
    rtb_min_relop_n = ((autocodePlant_B->Switch_l != autocodePlant_B->olat) ||
                       (autocodePlant_B->Gain != autocodePlant_B->oalt));

    /* Product: '<S222>/Product' */
    rtb_Sum1_ox = rtb_Product3_ax * rtb_Product3_ax;

    /* Product: '<S222>/Product1' */
    rtb_Product1_jv = rtb_Lw_idx_1 * rtb_Lw_idx_1;

    /* Outputs for Enabled SubSystem: '<S208>/Convert from geodetic to  spherical coordinates' incorporates:
     *  EnablePort: '<S220>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      autocodePlant_DW->Convertfromgeodetictospherica_p = rtb_min_relop_n;
    }

    if (autocodePlant_DW->Convertfromgeodetictospherica_p) {
      /* Sqrt: '<S262>/sqrt' incorporates:
       *  Product: '<S262>/Product10'
       *  Product: '<S262>/Product9'
       *  Sum: '<S262>/Sum7'
       */
      rtb_sincos_o1_idx_0 = sqrt(rtb_Product1_jv * autocodePlant_ConstB.a2 +
        autocodePlant_ConstB.b2 * rtb_Sum1_ox);

      /* Sqrt: '<S263>/sqrt' incorporates:
       *  Product: '<S263>/Product'
       *  Sum: '<S263>/Sum'
       */
      rtb_sincos_o2_idx_0 = sqrt(autocodePlant_ConstB.a2 - rtb_Sum1_ox *
        autocodePlant_ConstB.c2);

      /* Product: '<S220>/Product1' */
      rtb_Sum2_fl = rtb_sincos_o2_idx_0 * autocodePlant_B->Gain;

      /* Sqrt: '<S220>/sqrt' incorporates:
       *  Gain: '<S265>/Gain'
       *  Product: '<S265>/Product1'
       *  Product: '<S265>/Product6'
       *  Product: '<S265>/Product7'
       *  Product: '<S265>/Product8'
       *  Sum: '<S265>/Sum5'
       *  Sum: '<S265>/Sum6'
       */
      autocodePlant_B->sqrt_b = sqrt((autocodePlant_ConstB.a4 -
        autocodePlant_ConstB.c4 * rtb_Sum1_ox) / (rtb_sincos_o2_idx_0 *
        rtb_sincos_o2_idx_0) + (2.0 * rtb_Sum2_fl + autocodePlant_B->Gain *
        autocodePlant_B->Gain));

      /* Product: '<S260>/Product11' incorporates:
       *  Sum: '<S260>/Sum8'
       */
      autocodePlant_B->Product11 = (autocodePlant_B->Gain + rtb_sincos_o1_idx_0)
        / autocodePlant_B->sqrt_b;

      /* Product: '<S266>/Product12' incorporates:
       *  Product: '<S266>/Product1'
       */
      autocodePlant_B->Product12 = autocodePlant_ConstB.c2_l /
        (autocodePlant_B->sqrt_b * rtb_sincos_o1_idx_0) * rtb_Lw_idx_1 *
        rtb_Product3_ax;

      /* Sum: '<S264>/Sum2' */
      rtb_sincos_o1_idx_0 = autocodePlant_ConstB.a2 + rtb_Sum2_fl;

      /* Sum: '<S264>/Sum1' */
      rtb_Sum2_fl += autocodePlant_ConstB.b2;

      /* Product: '<S261>/Product4' incorporates:
       *  Product: '<S261>/Product3'
       *  Product: '<S264>/Product1'
       *  Product: '<S264>/Product2'
       *  Sqrt: '<S261>/sqrt'
       *  Sum: '<S261>/Sum3'
       */
      autocodePlant_B->Product4 = rtb_Product3_ax / sqrt(rtb_sincos_o1_idx_0 *
        rtb_sincos_o1_idx_0 / (rtb_Sum2_fl * rtb_Sum2_fl) * rtb_Product1_jv +
        rtb_Sum1_ox);

      /* Sqrt: '<S267>/sqrt' incorporates:
       *  Constant: '<S267>/Constant'
       *  Product: '<S267>/Product5'
       *  Sum: '<S267>/Sum4'
       */
      autocodePlant_B->sqrt_k = sqrt(1.0 - autocodePlant_B->Product4 *
        autocodePlant_B->Product4);
    }

    /* End of Outputs for SubSystem: '<S208>/Convert from geodetic to  spherical coordinates' */

    /* Product: '<S208>/aor' incorporates:
     *  Constant: '<S208>/re'
     */
    rtb_Lw_idx_1 = 6371.2 / autocodePlant_B->sqrt_b;
    if (tmp) {
      /* Outputs for Iterator SubSystem: '<S208>/Compute magnetic vector in spherical coordinates' incorporates:
       *  ForIterator: '<S219>/For Iterator'
       */
      /* InitializeConditions for UnitDelay: '<S219>/Unit Delay2' */
      autocodePlant_DW->UnitDelay2_DSTATE[0] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[1] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[2] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[3] = 0.0;

      /* InitializeConditions for UnitDelay: '<S219>/Unit Delay' */
      rtb_sincos_o1_idx_0 = 0.0;
      for (s268_iter = 0; s268_iter < 12; s268_iter++) {
        /* Switch: '<S219>/ar(n)' incorporates:
         *  Product: '<S208>/ar'
         */
        if (s268_iter <= 0) {
          rtb_sincos_o1_idx_0 = rtb_Lw_idx_1 * rtb_Lw_idx_1;
        }

        /* End of Switch: '<S219>/ar(n)' */

        /* Product: '<S219>/Product8' incorporates:
         *  UnitDelay: '<S219>/Unit Delay'
         */
        rtb_sincos_o1_idx_0 *= rtb_Lw_idx_1;

        /* Outputs for Iterator SubSystem: '<S219>/For Iterator Subsystem' incorporates:
         *  ForIterator: '<S227>/For Iterator'
         */
        /* InitializeConditions for UnitDelay: '<S228>/Unit Delay3' */
        rtb_sincos_o2_idx_0 = 0.0;

        /* InitializeConditions for UnitDelay: '<S228>/Unit Delay2' */
        rtb_Sum2_fl = 0.0;

        /* InitializeConditions for UnitDelay: '<S228>/Unit Delay1' */
        rtb_Sum1_ox = 0.0;

        /* InitializeConditions for UnitDelay: '<S228>/Unit Delay4' */
        rtb_Product1_jv = 0.0;
        for (i = 0; i < 6; i++) {
          ForIterator_IterationMarker[i] = 1U;
        }

        /* Sum: '<S219>/Sum' incorporates:
         *  Constant: '<S234>/Constant'
         *  Constant: '<S234>/Constant1'
         *  Logic: '<S234>/Logical Operator'
         *  RelationalOperator: '<S234>/Relational Operator'
         *  RelationalOperator: '<S234>/Relational Operator1'
         *  SignalConversion generated from: '<S229>/Enable'
         *  Sum: '<S227>/Sum1'
         */
        for (s227_iter = 1; s227_iter <= s268_iter + 2; s227_iter++) {
          /* Outputs for Enabled SubSystem: '<S227>/Time adjust the gauss coefficients' incorporates:
           *  EnablePort: '<S230>/Enable'
           */
          if (rtb_RelationalOperator) {
            /* Assignment: '<S230>/Assignment' */
            if (ForIterator_IterationMarker[4] < 2) {
              ForIterator_IterationMarker[4] = 2U;

              /* Assignment: '<S230>/Assignment' incorporates:
               *  UnitDelay: '<S230>/Unit Delay'
               */
              memcpy(&autocodePlant_B->Assignment_o[0],
                     &autocodePlant_DW->UnitDelay_DSTATE_e[0], 169U * sizeof
                     (real_T));
            }

            /* Outputs for Atomic SubSystem: '<S230>/If Action Subsystem' */
            /* Selector: '<S256>/c[m][n]' incorporates:
             *  Assignment: '<S230>/Assignment'
             *  Constant: '<S230>/cd[maxdef][maxdef]'
             *  Selector: '<S256>/cd[m][n]'
             *  Sum: '<S256>/Sum2'
             */
            i = ((s268_iter + 1) * 13 + s227_iter) - 1;

            /* Assignment: '<S230>/Assignment' incorporates:
             *  Constant: '<S230>/c[maxdef][maxdef]'
             *  Constant: '<S230>/cd[maxdef][maxdef]'
             *  Product: '<S256>/Product'
             *  Selector: '<S256>/c[m][n]'
             *  Selector: '<S256>/cd[m][n]'
             *  Sum: '<S256>/Sum'
             */
            autocodePlant_B->Assignment_o[i] = rtCP__cdmaxdefmaxdef_Value[i] *
              autocodePlant_ConstB.Sum_dd + rtCP__cmaxdefmaxdef_Value[i];

            /* End of Outputs for SubSystem: '<S230>/If Action Subsystem' */

            /* Switch: '<S257>/tc_old' incorporates:
             *  UnitDelay: '<S257>/Unit Delay'
             */
            if (s268_iter <= 0) {
              memset(&autocodePlant_DW->UnitDelay_DSTATE_k[0], 0, 169U * sizeof
                     (real_T));
            }

            /* End of Switch: '<S257>/tc_old' */

            /* If: '<S257>/If' incorporates:
             *  Sum: '<S227>/Sum1'
             */
            if (s227_iter - 1 != 0) {
              /* Outputs for IfAction SubSystem: '<S257>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S258>/Action Port'
               */
              /* Assignment: '<S258>/Assignment2' */
              if (ForIterator_IterationMarker[5] < 2) {
                ForIterator_IterationMarker[5] = 2U;

                /* Assignment: '<S258>/Assignment2' incorporates:
                 *  Switch: '<S257>/tc_old'
                 */
                memcpy(&autocodePlant_B->Assignment2[0],
                       &autocodePlant_DW->UnitDelay_DSTATE_k[0], 169U * sizeof
                       (real_T));
              }

              /* Selector: '<S258>/c[m][n]' incorporates:
               *  Assignment: '<S258>/Assignment2'
               *  Constant: '<S230>/cd[maxdef][maxdef]'
               *  Selector: '<S258>/cd[m][n]'
               *  Sum: '<S258>/Sum2'
               */
              i = ((s227_iter - 2) * 13 + s268_iter) + 1;

              /* Assignment: '<S258>/Assignment2' incorporates:
               *  Constant: '<S230>/c[maxdef][maxdef]'
               *  Constant: '<S230>/cd[maxdef][maxdef]'
               *  Product: '<S258>/Product'
               *  Selector: '<S258>/c[m][n]'
               *  Selector: '<S258>/cd[m][n]'
               *  Sum: '<S258>/Sum'
               *  Sum: '<S258>/Sum2'
               */
              autocodePlant_B->Assignment2[i] = rtCP__cdmaxdefmaxdef_Value[i] *
                autocodePlant_ConstB.Sum_dd + rtCP__cmaxdefmaxdef_Value[i];

              /* Gain: '<S258>/Gain' incorporates:
               *  Assignment: '<S258>/Assignment2'
               *  Merge: '<S257>/Merge'
               *  UnitDelay: '<S257>/Unit Delay'
               */
              memcpy(&autocodePlant_DW->UnitDelay_DSTATE_k[0],
                     &autocodePlant_B->Assignment2[0], 169U * sizeof(real_T));

              /* End of Outputs for SubSystem: '<S257>/If Action Subsystem1' */
            }

            /* End of If: '<S257>/If' */
            for (i = 0; i < 169; i++) {
              /* Sum: '<S230>/Sum2' incorporates:
               *  Assignment: '<S230>/Assignment'
               */
              rtb_Product3_ax = autocodePlant_B->Assignment_o[i];

              /* Sum: '<S230>/Sum2' incorporates:
               *  Assignment: '<S230>/Assignment'
               *  Merge: '<S257>/Merge'
               *  UnitDelay: '<S257>/Unit Delay'
               */
              autocodePlant_B->Sum2_p[i] = rtb_Product3_ax +
                autocodePlant_DW->UnitDelay_DSTATE_k[i];

              /* Update for UnitDelay: '<S230>/Unit Delay' incorporates:
               *  Assignment: '<S230>/Assignment'
               */
              autocodePlant_DW->UnitDelay_DSTATE_e[i] = rtb_Product3_ax;
            }
          }

          /* End of Outputs for SubSystem: '<S227>/Time adjust the gauss coefficients' */

          /* If: '<S233>/If' incorporates:
           *  Sum: '<S227>/Sum1'
           */
          if (s227_iter - 1 == 0) {
            /* Outputs for IfAction SubSystem: '<S233>/If Action Subsystem' incorporates:
             *  ActionPort: '<S239>/Action Port'
             */
            /* Product: '<S239>/Product' incorporates:
             *  Constant: '<S239>/Constant'
             *  Selector: '<S239>/Selector'
             *  Sum: '<S239>/Sum'
             */
            i = (s268_iter + 1) * 13;

            /* Merge: '<S233>/Merge' incorporates:
             *  Gain: '<S239>/Gain1'
             *  Product: '<S239>/Product'
             *  Selector: '<S233>/cp[m+1]'
             *  Selector: '<S239>/Selector'
             *  Sum: '<S230>/Sum2'
             */
            Merge_n = autocodePlant_B->OutportBufferForcp13[s227_iter - 1] *
              autocodePlant_B->Sum2_p[i];

            /* Merge: '<S233>/Merge1' incorporates:
             *  Gain: '<S239>/Gain2'
             *  Product: '<S239>/Product'
             *  Selector: '<S233>/sp[m+1]'
             *  Selector: '<S239>/Selector'
             *  Sum: '<S230>/Sum2'
             */
            Merge1 = autocodePlant_B->OutportBufferForsp13[s227_iter - 1] *
              autocodePlant_B->Sum2_p[i];

            /* End of Outputs for SubSystem: '<S233>/If Action Subsystem' */
          } else {
            /* Outputs for IfAction SubSystem: '<S233>/If Action Subsystem1' incorporates:
             *  ActionPort: '<S240>/Action Port'
             */
            /* Product: '<S240>/Product' incorporates:
             *  Constant: '<S241>/Constant'
             *  Selector: '<S240>/Selector'
             *  Sum: '<S241>/Sum'
             */
            i = ((s268_iter + 1) * 13 + s227_iter) - 1;

            /* Product: '<S240>/Product1' incorporates:
             *  Selector: '<S240>/Selector1'
             *  Sum: '<S242>/Sum'
             */
            rtb_Sum2_ct = ((s227_iter - 2) * 13 + s268_iter) + 1;

            /* Merge: '<S233>/Merge' incorporates:
             *  Product: '<S240>/Product'
             *  Product: '<S240>/Product1'
             *  Selector: '<S233>/cp[m+1]'
             *  Selector: '<S233>/sp[m+1]'
             *  Selector: '<S240>/Selector'
             *  Selector: '<S240>/Selector1'
             *  Sum: '<S230>/Sum2'
             *  Sum: '<S240>/Sum'
             */
            Merge_n = autocodePlant_B->OutportBufferForcp13[s227_iter - 1] *
              autocodePlant_B->Sum2_p[i] + autocodePlant_B->
              OutportBufferForsp13[s227_iter - 1] * autocodePlant_B->
              Sum2_p[rtb_Sum2_ct];

            /* Merge: '<S233>/Merge1' incorporates:
             *  Product: '<S240>/Product'
             *  Product: '<S240>/Product1'
             *  Selector: '<S233>/cp[m+1]'
             *  Selector: '<S233>/sp[m+1]'
             *  Selector: '<S240>/Selector'
             *  Selector: '<S240>/Selector1'
             *  Sum: '<S230>/Sum2'
             *  Sum: '<S240>/Sum1'
             */
            Merge1 = autocodePlant_B->OutportBufferForsp13[s227_iter - 1] *
              autocodePlant_B->Sum2_p[i] - autocodePlant_B->
              OutportBufferForcp13[s227_iter - 1] * autocodePlant_B->
              Sum2_p[rtb_Sum2_ct];

            /* End of Outputs for SubSystem: '<S233>/If Action Subsystem1' */
          }

          /* End of If: '<S233>/If' */

          /* Outputs for Enabled SubSystem: '<S227>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' incorporates:
           *  EnablePort: '<S229>/Enable'
           */
          if (rtb_min_relop_n) {
            /* If: '<S229>/if n == m elseif (n==1&m==0) elseif (n>1&m~=n)' incorporates:
             *  Sum: '<S227>/Sum1'
             */
            if (s268_iter + 1 == s227_iter - 1) {
              /* Outputs for IfAction SubSystem: '<S229>/If Action Subsystem' incorporates:
               *  ActionPort: '<S243>/Action Port'
               */
              /* Selector: '<S243>/Selector' incorporates:
               *  Gain: '<S247>/Gain'
               *  Sum: '<S247>/Sum1'
               *  Sum: '<S247>/Sum2'
               */
              rtb_Sum2_ct = mul_s32_sat(13, s227_iter - 2);
              if (rtb_Sum2_ct > 2147483646 - s268_iter) {
                i = MAX_int32_T;
              } else {
                i = (s268_iter + rtb_Sum2_ct) + 1;
              }

              /* Merge: '<S229>/Merge1' incorporates:
               *  Product: '<S243>/Product'
               *  Product: '<S243>/Product2'
               *  Selector: '<S243>/Selector'
               *  Selector: '<S243>/Selector1'
               *  Sum: '<S243>/Sum'
               *  Sum: '<S247>/Sum1'
               *  UnitDelay: '<S229>/Unit Delay'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = autocodePlant_DW->UnitDelay_DSTATE_o
                [(13 * s268_iter + s227_iter) - 2] * autocodePlant_B->sqrt_k +
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->Product4;

              /* Selector: '<S243>/Selector' incorporates:
               *  Sum: '<S247>/Sum1'
               */
              if (rtb_Sum2_ct > 2147483646 - s268_iter) {
                i = MAX_int32_T;
              } else {
                i = (s268_iter + rtb_Sum2_ct) + 1;
              }

              /* Merge: '<S229>/Merge' incorporates:
               *  Product: '<S243>/Product1'
               *  Selector: '<S243>/Selector'
               *  Sum: '<S247>/Sum1'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->sqrt_k;

              /* End of Outputs for SubSystem: '<S229>/If Action Subsystem' */
            } else if ((s268_iter == 0) && (s227_iter - 1 == 0)) {
              /* Outputs for IfAction SubSystem: '<S229>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S244>/Action Port'
               */
              /* Selector: '<S244>/Selector' incorporates:
               *  Gain: '<S249>/Gain'
               *  Sum: '<S249>/Sum1'
               */
              rtb_Sum2_ct = mul_s32_sat(13, 0);
              if (rtb_Sum2_ct > 2147483646) {
                i = MAX_int32_T;
              } else {
                i = rtb_Sum2_ct + 1;
              }

              /* Merge: '<S229>/Merge1' incorporates:
               *  Product: '<S244>/Product'
               *  Product: '<S244>/Product2'
               *  Selector: '<S244>/Selector'
               *  Selector: '<S244>/Selector1'
               *  Sum: '<S244>/Sum'
               *  Sum: '<S249>/Sum1'
               *  Sum: '<S250>/Sum'
               *  UnitDelay: '<S229>/Unit Delay'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = autocodePlant_B->Product4 *
                autocodePlant_DW->UnitDelay_DSTATE_o[0] -
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->sqrt_k;

              /* Selector: '<S244>/Selector' incorporates:
               *  Sum: '<S249>/Sum1'
               */
              if (rtb_Sum2_ct > 2147483646) {
                i = MAX_int32_T;
              } else {
                i = rtb_Sum2_ct + 1;
              }

              /* Merge: '<S229>/Merge' incorporates:
               *  Product: '<S244>/Product3'
               *  Selector: '<S244>/Selector'
               *  Sum: '<S249>/Sum1'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->Product4;

              /* End of Outputs for SubSystem: '<S229>/If Action Subsystem1' */
            } else if ((s268_iter > 0) && (s268_iter + 1 != s227_iter - 1)) {
              /* Outputs for IfAction SubSystem: '<S229>/If Action Subsystem2' incorporates:
               *  ActionPort: '<S245>/Action Port'
               */
              /* Gain: '<S251>/Gain' */
              rtb_Sum2_ct = mul_s32_sat(13, s227_iter - 1);

              /* Switch: '<S245>/Switch1' incorporates:
               *  Constant: '<S245>/Constant1'
               *  RelationalOperator: '<S255>/Relational Operator'
               *  Selector: '<S245>/Selector'
               *  Sum: '<S251>/Sum1'
               *  Sum: '<S255>/Sum2'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              if (s268_iter - 1 >= s227_iter - 1) {
                /* Selector: '<S245>/Selector' incorporates:
                 *  Sum: '<S251>/Sum1'
                 */
                if (rtb_Sum2_ct > MAX_int32_T - s268_iter) {
                  i = MAX_int32_T;
                } else {
                  i = s268_iter + rtb_Sum2_ct;
                }

                rtb_Product3_ax = autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1];
              } else {
                rtb_Product3_ax = 0.0;
              }

              /* Selector: '<S245>/Selector' incorporates:
               *  Sum: '<S251>/Sum1'
               */
              if (rtb_Sum2_ct > 2147483646 - s268_iter) {
                i = MAX_int32_T;
              } else {
                i = (s268_iter + rtb_Sum2_ct) + 1;
              }

              /* Selector: '<S245>/Selector2' incorporates:
               *  Constant: '<S245>/k[13][13]'
               *  Sum: '<S252>/Sum'
               */
              Merge_b_tmp = ((s268_iter + 1) * 13 + s227_iter) - 1;

              /* Merge: '<S229>/Merge' incorporates:
               *  Constant: '<S245>/k[13][13]'
               *  Product: '<S245>/Product2'
               *  Product: '<S245>/Product3'
               *  Selector: '<S245>/Selector'
               *  Selector: '<S245>/Selector2'
               *  Sum: '<S245>/Sum1'
               *  Sum: '<S251>/Sum1'
               *  Switch: '<S245>/Switch1'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->Product4 -
                rtCP__k1313_Value_j[Merge_b_tmp] * rtb_Product3_ax;

              /* Switch: '<S245>/Switch' incorporates:
               *  Constant: '<S245>/Constant'
               *  RelationalOperator: '<S254>/Relational Operator'
               *  Selector: '<S245>/Selector1'
               *  Sum: '<S254>/Sum2'
               *  UnitDelay: '<S229>/Unit Delay'
               */
              if (s268_iter - 1 >= s227_iter - 1) {
                rtb_Product3_ax = autocodePlant_DW->UnitDelay_DSTATE_o
                  [((s268_iter - 1) * 13 + s227_iter) - 1];
              } else {
                rtb_Product3_ax = 0.0;
              }

              /* Selector: '<S245>/Selector' incorporates:
               *  Sum: '<S251>/Sum1'
               */
              if (rtb_Sum2_ct > 2147483646 - s268_iter) {
                i = MAX_int32_T;
              } else {
                i = (s268_iter + rtb_Sum2_ct) + 1;
              }

              /* Merge: '<S229>/Merge1' incorporates:
               *  Constant: '<S245>/k[13][13]'
               *  Product: '<S245>/Product'
               *  Product: '<S245>/Product1'
               *  Product: '<S245>/Product4'
               *  Selector: '<S245>/Selector'
               *  Selector: '<S245>/Selector1'
               *  Selector: '<S245>/Selector2'
               *  Sum: '<S245>/Sum'
               *  Sum: '<S251>/Sum1'
               *  Switch: '<S245>/Switch'
               *  UnitDelay: '<S229>/Unit Delay'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = (autocodePlant_DW->UnitDelay_DSTATE_o
                [(13 * s268_iter + s227_iter) - 1] * autocodePlant_B->Product4 -
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->sqrt_k) - rtCP__k1313_Value_j[Merge_b_tmp] *
                rtb_Product3_ax;

              /* End of Outputs for SubSystem: '<S229>/If Action Subsystem2' */
            }

            /* End of If: '<S229>/if n == m elseif (n==1&m==0) elseif (n>1&m~=n)' */

            /* Assignment: '<S229>/Assignment_snorm' */
            if (ForIterator_IterationMarker[3] < 2) {
              ForIterator_IterationMarker[3] = 2U;

              /* Assignment: '<S229>/Assignment_snorm' incorporates:
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              memcpy(&autocodePlant_B->Assignment_snorm[0],
                     &autocodePlant_DW->UnitDelay1_DSTATE_c[0], 169U * sizeof
                     (real_T));
            }

            /* Sum: '<S246>/Sum1' incorporates:
             *  Gain: '<S246>/Gain'
             *  Sum: '<S229>/Sum'
             *  Sum: '<S246>/Sum2'
             */
            i = mul_s32_sat(13, s227_iter - 1);
            if (i > 2147483645 - s268_iter) {
              i = MAX_int32_T;
            } else {
              i = (s268_iter + i) + 2;
            }

            /* Assignment: '<S229>/Assignment_snorm' incorporates:
             *  Sum: '<S246>/Sum1'
             */
            autocodePlant_B->Assignment_snorm[i - 1] = autocodePlant_B->Merge_b;

            /* Assignment: '<S229>/Assignment' incorporates:
             *  Sum: '<S229>/Sum'
             *  UnitDelay: '<S229>/Unit Delay'
             */
            if (ForIterator_IterationMarker[2] < 2) {
              ForIterator_IterationMarker[2] = 2U;
              memcpy(&autocodePlant_B->Assignment_h[0],
                     &autocodePlant_DW->UnitDelay_DSTATE_o[0], 169U * sizeof
                     (real_T));
            }

            autocodePlant_B->Assignment_h[(s227_iter + 13 * (s268_iter + 1)) - 1]
              = autocodePlant_B->Merge1_i;

            /* End of Assignment: '<S229>/Assignment' */

            /* Update for UnitDelay: '<S229>/Unit Delay' incorporates:
             *  Assignment: '<S229>/Assignment'
             */
            memcpy(&autocodePlant_DW->UnitDelay_DSTATE_o[0],
                   &autocodePlant_B->Assignment_h[0], 169U * sizeof(real_T));

            /* Update for UnitDelay: '<S229>/Unit Delay1' */
            memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_c[0],
                   &autocodePlant_B->Assignment_snorm[0], 169U * sizeof(real_T));
          }

          /* End of Outputs for SubSystem: '<S227>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */

          /* Selector: '<S228>/snorm[n+m*13]' incorporates:
           *  Gain: '<S232>/Gain'
           *  SignalConversion generated from: '<S229>/Enable'
           *  Sum: '<S227>/Sum1'
           *  Sum: '<S232>/Sum1'
           */
          i = mul_s32_sat(13, s227_iter - 1);
          if (i > 2147483645 - s268_iter) {
            i = MAX_int32_T;
          } else {
            i = (s268_iter + i) + 2;
          }

          /* Product: '<S228>/par' incorporates:
           *  Selector: '<S228>/snorm[n+m*13]'
           *  Sum: '<S232>/Sum1'
           *  UnitDelay: '<S219>/Unit Delay'
           */
          rtb_Product3_ax = autocodePlant_B->Assignment_snorm[i - 1] *
            rtb_sincos_o1_idx_0;

          /* Sum: '<S228>/Sum2' incorporates:
           *  Constant: '<S228>/fm'
           *  Product: '<S228>/Product1'
           *  Selector: '<S228>/fm[m]'
           *  UnitDelay: '<S228>/Unit Delay3'
           */
          autocodePlant_B->Sum2 = rtCP__fm_Value[s227_iter - 1] *
            rtb_Product3_ax * Merge1 + rtb_sincos_o2_idx_0;

          /* Sum: '<S228>/Sum3' incorporates:
           *  Constant: '<S228>/fn'
           *  Product: '<S228>/Product2'
           *  Selector: '<S228>/fn[m]'
           *  Sum: '<S228>/Sum4'
           *  UnitDelay: '<S228>/Unit Delay2'
           */
          autocodePlant_B->Sum3 = rtCP__fn_Value[s268_iter + 1] *
            rtb_Product3_ax * Merge_n + rtb_Sum2_fl;

          /* Outputs for Enabled SubSystem: '<S228>/Special case - North//South Geographic Pole' incorporates:
           *  EnablePort: '<S231>/Enable'
           */
          /* Outputs for IfAction SubSystem: '<S231>/If Action Subsystem2' incorporates:
           *  ActionPort: '<S236>/Action Port'
           */
          /* If: '<S231>/n ==1' incorporates:
           *  Constant: '<S236>/k[13][13]'
           *  Selector: '<S228>/dp[n][m]'
           *  Selector: '<S236>/Selector2'
           *  Sum: '<S228>/Sum'
           */
          rtb_Sum2_ct = (s268_iter + 1) * 13;

          /* End of Outputs for SubSystem: '<S231>/If Action Subsystem2' */
          /* End of Outputs for SubSystem: '<S228>/Special case - North//South Geographic Pole' */

          /* Sum: '<S228>/Sum1' incorporates:
           *  Assignment: '<S229>/Assignment'
           *  Product: '<S228>/Product'
           *  Selector: '<S228>/dp[n][m]'
           *  UnitDelay: '<S219>/Unit Delay'
           *  UnitDelay: '<S228>/Unit Delay1'
           */
          autocodePlant_B->Sum1_p = rtb_Sum1_ox - autocodePlant_B->Assignment_h
            [(rtb_Sum2_ct + s227_iter) - 1] * Merge_n * rtb_sincos_o1_idx_0;

          /* Outputs for Enabled SubSystem: '<S228>/Special case - North//South Geographic Pole' incorporates:
           *  EnablePort: '<S231>/Enable'
           */
          if ((autocodePlant_B->sqrt_k == 0.0) && (s227_iter - 1 == 1)) {
            autocodePlant_DW->SpecialcaseNorthSouthGeographic = true;

            /* If: '<S231>/n ==1' incorporates:
             *  Assignment: '<S236>/Assignment2'
             */
            if (s268_iter == 0) {
              /* Outputs for IfAction SubSystem: '<S231>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S235>/Action Port'
               */
              /* Assignment: '<S235>/Assignment2' incorporates:
               *  Selector: '<S235>/pp[n-1]'
               *  UnitDelay: '<S231>/Unit Delay1'
               */
              if (ForIterator_IterationMarker[0] < 2) {
                ForIterator_IterationMarker[0] = 2U;
                memcpy(&autocodePlant_B->Assignment2_m[0],
                       &autocodePlant_DW->UnitDelay1_DSTATE_b[0], 13U * sizeof
                       (real_T));
              }

              autocodePlant_B->Assignment2_m[1] =
                autocodePlant_DW->UnitDelay1_DSTATE_b[0];

              /* End of Assignment: '<S235>/Assignment2' */
              /* End of Outputs for SubSystem: '<S231>/If Action Subsystem1' */
            } else {
              /* Outputs for IfAction SubSystem: '<S231>/If Action Subsystem2' incorporates:
               *  ActionPort: '<S236>/Action Port'
               */
              if (ForIterator_IterationMarker[1] < 2) {
                /* Assignment: '<S236>/Assignment2' */
                ForIterator_IterationMarker[1] = 2U;

                /* Assignment: '<S236>/Assignment2' incorporates:
                 *  UnitDelay: '<S231>/Unit Delay1'
                 */
                memcpy(&autocodePlant_B->Assignment2_a[0],
                       &autocodePlant_DW->UnitDelay1_DSTATE_b[0], 13U * sizeof
                       (real_T));
              }

              /* Assignment: '<S236>/Assignment2' incorporates:
               *  Constant: '<S236>/k[13][13]'
               *  Product: '<S236>/Product1'
               *  Product: '<S236>/Product2'
               *  Selector: '<S236>/Selector2'
               *  Selector: '<S236>/pp[n-2] pp[n-1]'
               *  Sum: '<S236>/Sum1'
               *  Sum: '<S236>/Sum2'
               *  UnitDelay: '<S231>/Unit Delay1'
               */
              autocodePlant_B->Assignment2_a[s268_iter + 1] =
                autocodePlant_B->Product4 *
                autocodePlant_DW->UnitDelay1_DSTATE_b[s268_iter] -
                rtCP__k1313_Value[rtb_Sum2_ct + 1] *
                autocodePlant_DW->UnitDelay1_DSTATE_b[s268_iter - 1];

              /* End of Outputs for SubSystem: '<S231>/If Action Subsystem2' */
            }

            /* SignalConversion generated from: '<S231>/pp[n]' */
            autocodePlant_DW->UnitDelay1_DSTATE_b[1] =
              autocodePlant_B->Assignment2_m[1];
            memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_b[2],
                   &autocodePlant_B->Assignment2_a[2], 11U * sizeof(real_T));

            /* Product: '<S231>/Product2' incorporates:
             *  Selector: '<S231>/pp[n]'
             *  UnitDelay: '<S219>/Unit Delay'
             */
            autocodePlant_B->Product2 = autocodePlant_DW->
              UnitDelay1_DSTATE_b[s268_iter + 1] * rtb_sincos_o1_idx_0 * Merge1;
          } else if (autocodePlant_DW->SpecialcaseNorthSouthGeographic) {
            /* Disable for Product: '<S231>/Product2' incorporates:
             *  Outport: '<S231>/bpp'
             */
            autocodePlant_B->Product2 = 0.0;
            autocodePlant_DW->SpecialcaseNorthSouthGeographic = false;
          }

          /* End of Outputs for SubSystem: '<S228>/Special case - North//South Geographic Pole' */

          /* Sum: '<S228>/Sum5' incorporates:
           *  Constant: '<S234>/Constant'
           *  Constant: '<S234>/Constant1'
           *  Logic: '<S234>/Logical Operator'
           *  RelationalOperator: '<S234>/Relational Operator'
           *  RelationalOperator: '<S234>/Relational Operator1'
           *  Sum: '<S227>/Sum1'
           *  UnitDelay: '<S228>/Unit Delay4'
           */
          autocodePlant_B->Sum5 = rtb_Product1_jv + autocodePlant_B->Product2;

          /* Update for UnitDelay: '<S228>/Unit Delay3' */
          rtb_sincos_o2_idx_0 = autocodePlant_B->Sum2;

          /* Update for UnitDelay: '<S228>/Unit Delay2' */
          rtb_Sum2_fl = autocodePlant_B->Sum3;

          /* Update for UnitDelay: '<S228>/Unit Delay1' */
          rtb_Sum1_ox = autocodePlant_B->Sum1_p;

          /* Update for UnitDelay: '<S228>/Unit Delay4' */
          rtb_Product1_jv = autocodePlant_B->Sum5;
        }

        /* End of Sum: '<S219>/Sum' */
        /* End of Outputs for SubSystem: '<S219>/For Iterator Subsystem' */

        /* Sum: '<S219>/Sum1' incorporates:
         *  UnitDelay: '<S219>/Unit Delay2'
         */
        rtb_Product3_ax = autocodePlant_DW->UnitDelay2_DSTATE[0];
        rtb_sincos_o2_idx_0 = autocodePlant_DW->UnitDelay2_DSTATE[1];
        rtb_Sum2_fl = autocodePlant_DW->UnitDelay2_DSTATE[2];
        rtb_Sum1_ox = autocodePlant_DW->UnitDelay2_DSTATE[3];
        autocodePlant_DW->UnitDelay2_DSTATE[0] = rtb_Product3_ax +
          autocodePlant_B->Sum1_p;
        autocodePlant_DW->UnitDelay2_DSTATE[1] = rtb_sincos_o2_idx_0 +
          autocodePlant_B->Sum2;
        autocodePlant_DW->UnitDelay2_DSTATE[2] = rtb_Sum2_fl +
          autocodePlant_B->Sum3;
        autocodePlant_DW->UnitDelay2_DSTATE[3] = rtb_Sum1_ox +
          autocodePlant_B->Sum5;
      }

      /* End of Outputs for SubSystem: '<S208>/Compute magnetic vector in spherical coordinates' */
    }

    /* Switch: '<S271>/Switch' incorporates:
     *  Product: '<S271>/Product'
     *  UnitDelay: '<S219>/Unit Delay2'
     */
    if (autocodePlant_B->sqrt_k != 0.0) {
      rtb_sincos_o1_idx_0 = autocodePlant_DW->UnitDelay2_DSTATE[1] /
        autocodePlant_B->sqrt_k;
    } else {
      rtb_sincos_o1_idx_0 = autocodePlant_DW->UnitDelay2_DSTATE[3];
    }

    /* End of Switch: '<S271>/Switch' */

    /* Sum: '<S270>/Sum1' incorporates:
     *  Product: '<S270>/Product1'
     *  Product: '<S270>/Product4'
     *  UnitDelay: '<S219>/Unit Delay2'
     */
    rtb_sincos_o2_idx_0 = (0.0 - autocodePlant_B->Product11 *
      autocodePlant_DW->UnitDelay2_DSTATE[0]) -
      autocodePlant_DW->UnitDelay2_DSTATE[2] * autocodePlant_B->Product12;

    /* Trigonometry: '<S273>/Trigonometric Function1' */
    rtb_Sum2_fl = rt_atan2d_snf(rtb_sincos_o1_idx_0, rtb_sincos_o2_idx_0);

    /* Sum: '<S272>/Sum1' incorporates:
     *  Product: '<S272>/Product1'
     *  Product: '<S272>/Product4'
     *  UnitDelay: '<S219>/Unit Delay2'
     */
    /* Unit Conversion - from: rad to: deg
       Expression: output = (57.2958*input) + (0) */
    rtb_Sum1_ox = autocodePlant_B->Product12 *
      autocodePlant_DW->UnitDelay2_DSTATE[0] -
      autocodePlant_DW->UnitDelay2_DSTATE[2] * autocodePlant_B->Product11;

    /* Sum: '<S273>/Sum' incorporates:
     *  Product: '<S273>/Product'
     *  Product: '<S273>/Product1'
     */
    rtb_sincos_o1_idx_0 = rtb_sincos_o1_idx_0 * rtb_sincos_o1_idx_0 +
      rtb_sincos_o2_idx_0 * rtb_sincos_o2_idx_0;

    /* UnitConversion: '<S209>/Unit Conversion' incorporates:
     *  Sqrt: '<S273>/sqrt1'
     *  Trigonometry: '<S273>/Trigonometric Function'
     *  UnitConversion: '<S274>/Unit Conversion'
     *  UnitConversion: '<S275>/Unit Conversion'
     */
    /* Unit Conversion - from: rad to: deg
       Expression: output = (57.2958*input) + (0) */
    /* Unit Conversion - from: deg to: rad
       Expression: output = (0.0174533*input) + (0) */
    rtb_Product3_ax = 57.29577951308232 * rtb_Sum2_fl * 0.017453292519943295;
    rtb_Lw_idx_1 = 57.29577951308232 * rt_atan2d_snf(rtb_Sum1_ox, sqrt
      (rtb_sincos_o1_idx_0)) * 0.017453292519943295;

    /* Sqrt: '<S273>/sqrt' incorporates:
     *  Product: '<S273>/Product2'
     *  Sum: '<S273>/Sum1'
     */
    rtb_sincos_o1_idx_0 = sqrt(rtb_Sum1_ox * rtb_Sum1_ox + rtb_sincos_o1_idx_0);

    /* Product: '<S202>/h1' incorporates:
     *  Trigonometry: '<S202>/sincos'
     */
    rtb_sincos_o2_idx_0 = cos(rtb_Lw_idx_1) * rtb_sincos_o1_idx_0;

    /* Product: '<S202>/x1' incorporates:
     *  Trigonometry: '<S202>/sincos'
     */
    rtb_Sum2_fl = cos(rtb_Product3_ax) * rtb_sincos_o2_idx_0;

    /* Product: '<S202>/y1' incorporates:
     *  Trigonometry: '<S202>/sincos'
     */
    rtb_sincos_o2_idx_0 *= sin(rtb_Product3_ax);

    /* Product: '<S202>/z1' incorporates:
     *  Trigonometry: '<S202>/sincos'
     */
    rtb_sincos_o1_idx_0 *= sin(rtb_Lw_idx_1);

    /* Product: '<S106>/Product2' incorporates:
     *  Gain: '<S106>/P0'
     */
    rtb_pi3 *= 101325.0 * rtb_TT0gLR;
    if (tmp) {
      /* SignalConversion generated from: '<S176>/Product' incorporates:
       *  Product: '<S194>/Product4'
       *  Product: '<S194>/Product5'
       *  Product: '<S194>/Product8'
       *  Product: '<S195>/Product4'
       *  Product: '<S195>/Product5'
       *  Product: '<S195>/Product8'
       *  Product: '<S196>/Product4'
       *  Product: '<S196>/Product5'
       *  Product: '<S196>/Product8'
       *  Sum: '<S194>/Sum'
       *  Sum: '<S195>/Sum'
       *  Sum: '<S196>/Sum'
       */
      rtb_Product1_hx = (rtb_Product1_hx * rtb_Sum2_fl + rtb_Sum *
                         rtb_sincos_o2_idx_0) + rtb_Sum1_n * rtb_sincos_o1_idx_0;
      rtb_Product2_ml = (rtb_Product2_ml * rtb_sincos_o2_idx_0 +
                         rtb_Switch_d_idx_1 * rtb_Sum2_fl) + rtb_Switch_d_idx_2 *
        rtb_sincos_o1_idx_0;
      rtb_pi3_tmp = (rtb_pi3_tmp * rtb_Sum2_fl + rtb_TmpSignalConversionAtProd_0
                     * rtb_sincos_o2_idx_0) + rtb_UnaryMinus_a *
        rtb_sincos_o1_idx_0;

      /* ZeroOrderHold: '<S176>/Zero-Order Hold' incorporates:
       *  Constant: '<S176>/hardironBdy_nT'
       *  Constant: '<S176>/soft iron matrix'
       *  Product: '<S176>/Product'
       *  Sum: '<S176>/Sum'
       */
      for (i = 0; i < 3; i++) {
        Gdependent[i] = (((rtCP__softironmatrix_Value[i + 3] * rtb_Product2_ml +
                           rtCP__softironmatrix_Value[i] * rtb_Product1_hx) +
                          rtCP__softironmatrix_Value[i + 6] * rtb_pi3_tmp) +
                         autocodePlant_B->Output[i]) +
          rtCP__hardironBdy_nT_Value[i];
      }

      /* End of ZeroOrderHold: '<S176>/Zero-Order Hold' */

      /* Gain: '<S187>/Output' incorporates:
       *  RandomNumber: '<S187>/White Noise'
       */
      autocodePlant_B->Output_g = 0.19999999999999998 *
        autocodePlant_DW->NextOutput_e;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn2'
       *  Outport: '<Root>/sensor_bus'
       *  Sum: '<S174>/Sum1'
       */
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[0] =
        rtb_truth_bus_gyroBiasTrue_rps_;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[0] =
        rtb_truth_bus_accBiasTrue_mps2_;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[0] = rtb_ZeroOrderHold_c[0];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[0] = rtb_ZeroOrderHold_a[0];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[0] = Gdependent[0];
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[1] =
        rtb_truth_bus_gyroBiasTrue_rp_0;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[1] =
        rtb_truth_bus_accBiasTrue_mps_0;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[1] = rtb_ZeroOrderHold_c[1];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[1] = rtb_ZeroOrderHold_a[1];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[1] = Gdependent[1];
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[2] =
        rtb_truth_bus_gyroBiasTrue_rp_1;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[2] =
        rtb_truth_bus_accBiasTrue_mps_1;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[2] = rtb_ZeroOrderHold_c[2];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[2] = rtb_ZeroOrderHold_a[2];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[2] = Gdependent[2];
      autocodePlant_Y_sensor_bus_i->baroMeas_Pa = (autocodePlant_B->Output_g +
        rtb_pi3) + autocodePlant_DW->DiscreteTransferFcn2_states_h;
    }

    /* Product: '<S165>/Product' */
    autocodePlant_B->Product_h[0] = rtb_Add[0] * (real_T)rtb_max_relop_c;
    autocodePlant_B->Product_h[1] = rtb_Add[1] * (real_T)rtb_max_relop_c;
    autocodePlant_B->Product_h[2] = rtb_Add[2] * (real_T)rtb_max_relop_c;

    /* Outport: '<Root>/plant_bus' incorporates:
     *  BusCreator generated from: '<Root>/plant_bus'
     */
    autocodePlant_Y_plant_bus_e->enviroment_bus.temp_K = rtb_Sum1_oo;
    autocodePlant_Y_plant_bus_e->enviroment_bus.a_mps = rtb_a;
    autocodePlant_Y_plant_bus_e->enviroment_bus.pressure_Pa = rtb_pi3;
    autocodePlant_Y_plant_bus_e->enviroment_bus.rho_kgpm3 =
      rtb_TrigonometricFunction_o2_o;
    autocodePlant_Y_plant_bus_e->enviroment_bus.onRail_b = rtb_Compare_n;
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.aoa_deg = rtb_Gain_l;
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.liftSign_na = rtb_Sign1;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.aoa_deg = rtb_Gain_oa;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.liftSign_na = rtb_Sign1_e;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.aoa_deg = rtb_UnaryMinus1_k4;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.liftSign_na = rtb_Sign1_i;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.aoa_deg = rtb_UnaryMinus1_o;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.liftSign_na = rtb_Product_h5;
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.aoa_deg = rtb_Gain_el;

    /* Product: '<S164>/Matrix Multiply' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    rtb_truth_bus_gyroBiasTrue_rps_ = 0.0;
    rtb_truth_bus_accBiasTrue_mps2_ = 0.0;
    rtb_truth_bus_gyroBiasTrue_rp_0 = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_Product3_ax = rtb_wBdy_rps[i];
      rtb_truth_bus_gyroBiasTrue_rps_ += rtCP__Constant1_Value_fo[3 * i] *
        rtb_Product3_ax;
      rtb_truth_bus_accBiasTrue_mps2_ += rtCP__Constant1_Value_fo[3 * i + 1] *
        rtb_Product3_ax;
      rtb_truth_bus_gyroBiasTrue_rp_0 += rtCP__Constant1_Value_fo[3 * i + 2] *
        rtb_Product3_ax;

      /* Outport: '<Root>/plant_bus' incorporates:
       *  BusCreator generated from: '<Root>/plant_bus'
       *  Constant: '<S5>/Constant1'
       */
      autocodePlant_Y_plant_bus_e->enviroment_bus.gravityForceBdy_N[i] =
        rtb_gravityForceBdy_N[i];
      autocodePlant_Y_plant_bus_e->enviroment_bus.airspeed_mps[i] =
        rtb_VectorConcatenate[i];
      autocodePlant_Y_plant_bus_e->enviroment_bus.windBdy_mps[i] =
        rtb_Product_ne[i];
      autocodePlant_Y_plant_bus_e->enviroment_bus.airW_rps[i] =
        rtb_VectorConcatenate_h[i];
      autocodePlant_Y_plant_bus_e->aero_bus.aeroMoment_Nm[i] = rtb_Add[i];
      autocodePlant_Y_plant_bus_e->aero_bus.aeroForce_N[i] = rtb_Add[i + 3];
      autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finMoment_Nm[i] =
        rtb_Sum_hp[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finForce_N[i] =
        rtb_Sum1_p2[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.airspeedFin_mps[i] =
        rtb_Product_fn[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finMoment_Nm[i] =
        rtb_Sum_k[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finForce_N[i] =
        rtb_Sum1_ny[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.airspeedFin_mps[i] =
        rtb_Sum_dj[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finMoment_Nm[i] =
        rtb_Sum_n3[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finForce_N[i] =
        rtb_Sum1_lp[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.airspeedFin_mps[i] =
        rtb_Sum_el[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finMoment_Nm[i] =
        rtb_Sum_mu[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finForce_N[i] =
        rtb_Sum1_b[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.airspeedFin_mps[i] =
        rtb_Sum_aw[i];
      autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyMoment_Nm[i] =
        rtb_finMomentArm_m[i];
      autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyForce_N[i] =
        rtb_Product6_f[i];
      autocodePlant_Y_plant_bus_e->eom_bus.posNed_m[i] = rtb_posNed_m[i];
    }

    /* Product: '<S171>/Element Product' incorporates:
     *  Product: '<S164>/Matrix Multiply'
     */
    rtb_ElementProduct[0] = rtb_wBdy_rps[1] * rtb_truth_bus_gyroBiasTrue_rp_0;
    rtb_ElementProduct[1] = rtb_truth_bus_gyroBiasTrue_rps_ * rtb_wBdy_rps[2];
    rtb_ElementProduct[2] = rtb_wBdy_rps[0] * rtb_truth_bus_accBiasTrue_mps2_;
    rtb_ElementProduct[3] = rtb_truth_bus_accBiasTrue_mps2_ * rtb_wBdy_rps[2];
    rtb_ElementProduct[4] = rtb_wBdy_rps[0] * rtb_truth_bus_gyroBiasTrue_rp_0;
    rtb_ElementProduct[5] = rtb_truth_bus_gyroBiasTrue_rps_ * rtb_wBdy_rps[1];

    /* Outport: '<Root>/plant_bus' incorporates:
     *  BusCreator generated from: '<Root>/plant_bus'
     */
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[0] = rtb_q_na_idx_0;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[1] = rtb_q_na_idx_1;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[2] = rtb_q_na_idx_2;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[3] = rtb_q_na_idx_3;
    for (i = 0; i < 3; i++) {
      autocodePlant_Y_plant_bus_e->eom_bus.velBdy_mps[i] = rtb_velBdy_mps[i];
      autocodePlant_Y_plant_bus_e->eom_bus.wBdy_rps[i] = rtb_wBdy_rps[i];
      autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[i] = rtb_MathFunction[i];

      /* Sum: '<S164>/Subtract' incorporates:
       *  Product: '<S164>/Matrix Multiply1'
       *  Sum: '<S170>/Add'
       *  Sum: '<S171>/Sum'
       */
      rtb_ZeroOrderHold_a[i] = (autocodePlant_B->Product_h[i] -
        (rtb_ElementProduct[i] - rtb_ElementProduct[i + 3])) -
        ((autocodePlant_ConstB.dIdt[i + 3] * rtb_wBdy_rps[1] +
          autocodePlant_ConstB.dIdt[i] * rtb_wBdy_rps[0]) +
         autocodePlant_ConstB.dIdt[i + 6] * rtb_wBdy_rps[2]);
    }

    /* Product: '<S164>/Product1' incorporates:
     *  Constant: '<S5>/Constant1'
     *  Outport: '<Root>/plant_bus'
     */
    rt_mldivide_U1d3x3_U2d_9O8lG8ax(rtCP__Constant1_Value_fo,
      rtb_ZeroOrderHold_a, autocodePlant_Y_plant_bus_e->eom_bus.wDotBdy_rps2);
    if (tmp) {
      /* Lookup_n-D: '<S6>/1-D Lookup Table' incorporates:
       *  UnitDelay: '<S172>/Unit Delay'
       */
      rtb_uDLookupTable = look1_binlcpw(autocodePlant_DW->UnitDelay_DSTATE_i,
        rtCP__uDLookupTable_bp01Data, rtCP__uDLookupTable_tableData, 25U);

      /* Sum: '<S172>/Sum' incorporates:
       *  Constant: '<S172>/Constant'
       *  UnitDelay: '<S172>/Unit Delay'
       */
      autocodePlant_DW->UnitDelay_DSTATE_i += 0.01;

      /* Gain: '<S186>/Output' incorporates:
       *  RandomNumber: '<S186>/White Noise'
       */
      autocodePlant_B->Output_n = 3.7947521660754644 *
        autocodePlant_DW->NextOutput_m;

      /* Gain: '<S178>/Output' incorporates:
       *  RandomNumber: '<S178>/White Noise'
       */
      autocodePlant_B->Output_o[0] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S188>/Output' incorporates:
       *  RandomNumber: '<S188>/White Noise'
       */
      autocodePlant_B->Output_e[0] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Gain: '<S178>/Output' incorporates:
       *  RandomNumber: '<S178>/White Noise'
       */
      autocodePlant_B->Output_o[1] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S188>/Output' incorporates:
       *  RandomNumber: '<S188>/White Noise'
       */
      autocodePlant_B->Output_e[1] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Gain: '<S178>/Output' incorporates:
       *  RandomNumber: '<S178>/White Noise'
       */
      autocodePlant_B->Output_o[2] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S188>/Output' incorporates:
       *  RandomNumber: '<S188>/White Noise'
       */
      autocodePlant_B->Output_e[2] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Assertion: '<S199>/Assertion' incorporates:
       *  Constant: '<S176>/ground altitude'
       *  Constant: '<S199>/max_val'
       *  Constant: '<S199>/min_val'
       *  FlatEarth2LLA: '<S176>/Flat Earth to LLA'
       *  Logic: '<S199>/conjunction'
       *  RelationalOperator: '<S199>/max_relop'
       *  RelationalOperator: '<S199>/min_relop'
       */
      utAssert((-(rtb_posNed_m[2] + 182.0) >= -1000.0) && (-(rtb_posNed_m[2] +
                 182.0) <= 850000.0));

      /* Assertion: '<S200>/Assertion' incorporates:
       *  Constant: '<S200>/max_val'
       *  Constant: '<S200>/min_val'
       *  Logic: '<S200>/conjunction'
       *  RelationalOperator: '<S200>/max_relop'
       *  RelationalOperator: '<S200>/min_relop'
       */
      utAssert((rtb_FlatEarthtoLLA_o1_idx_0 >= -90.0) &&
               (rtb_FlatEarthtoLLA_o1_idx_0 <= 90.0));

      /* Assertion: '<S201>/Assertion' incorporates:
       *  Constant: '<S201>/max_val'
       *  Constant: '<S201>/min_val'
       *  Logic: '<S201>/conjunction'
       *  RelationalOperator: '<S201>/max_relop'
       *  RelationalOperator: '<S201>/min_relop'
       */
      utAssert((rtb_Switch_d_idx_0 >= -180.0) && (rtb_Switch_d_idx_0 <= 180.0));

      /* Assertion: '<S203>/Assertion' */
      utAssert(autocodePlant_ConstB.conjunction);
    }
  }

/* STM32_CURRENT_SAMPLE_FEEDBACK */
  if (rtmIsMajorTimeStep(autocodePlant_M) && autocodePlant_feedback != NULL) {
    if (!autocodePlant_feedback(autocodePlant_Y_sensor_bus_i,
                                autocodePlant_Y_plant_bus_e,
                                autocodePlant_U_control_deg)) return;
  }

  if (rtmIsMajorTimeStep(autocodePlant_M)) {
    int32_T idxDelay;
    if (rtmIsMajorTimeStep(autocodePlant_M) &&
        autocodePlant_M->Timing.TaskCounters.TID[1] == 0) {
      /* Update for DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn' */
      autocodePlant_DW->DiscreteTransferFcn_states = autocodePlant_B->Output_e[0]
        - 0.99995 * autocodePlant_DW->DiscreteTransferFcn_states;

      /* Update for DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states = autocodePlant_B->Output_e
        [1] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn1_states;

      /* Update for DiscreteTransferFcn: '<S175>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states = autocodePlant_B->Output_e
        [2] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn2_states;

      /* Update for DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_k =
        autocodePlant_B->Output_o[0] - 0.99995 *
        autocodePlant_DW->DiscreteTransferFcn2_states_k;

      /* Update for DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states_a =
        autocodePlant_B->Output_o[1] - 0.99995 *
        autocodePlant_DW->DiscreteTransferFcn1_states_a;

      /* Update for DiscreteTransferFcn: '<S173>/Discrete Transfer Fcn3' */
      autocodePlant_DW->DiscreteTransferFcn3_states = autocodePlant_B->Output_o
        [2] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn3_states;

      /* Update for RandomNumber: '<S179>/White Noise' */
      autocodePlant_DW->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed);

      /* Update for Delay: '<S6>/Delay' */
      for (idxDelay = 0; idxDelay < 1999; idxDelay++) {
        autocodePlant_DW->Delay_DSTATE[idxDelay] =
          autocodePlant_DW->Delay_DSTATE[idxDelay + 1];
      }

      autocodePlant_DW->Delay_DSTATE[1999] = rtb_uDLookupTable;

      /* End of Update for Delay: '<S6>/Delay' */

      /* Update for RandomNumber: '<S131>/White Noise' */
      autocodePlant_DW->NextOutput_d[0] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[0]);

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE[0] = autocodePlant_U_control_deg[0];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[0] = autocodePlant_B->Backlash[0];

      /* Update for RandomNumber: '<S131>/White Noise' */
      autocodePlant_DW->NextOutput_d[1] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[1]);

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE[1] = autocodePlant_U_control_deg[1];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[1] = autocodePlant_B->Backlash[1];

      /* Update for RandomNumber: '<S131>/White Noise' */
      autocodePlant_DW->NextOutput_d[2] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[2]);

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE[2] = autocodePlant_U_control_deg[2];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[2] = autocodePlant_B->Backlash[2];

      /* Update for RandomNumber: '<S131>/White Noise' */
      autocodePlant_DW->NextOutput_d[3] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[3]);

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE[3] = autocodePlant_U_control_deg[3];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[3] = autocodePlant_B->Backlash[3];

      /* Update for RandomNumber: '<S189>/White Noise' */
      autocodePlant_DW->NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_l);

      /* Update for UnitDelay: '<S175>/Unit Delay' */
      autocodePlant_DW->UnitDelay_DSTATE_c[0] = autocodePlant_B->fBdy_mps2[0];
      autocodePlant_DW->UnitDelay_DSTATE_c[1] = autocodePlant_B->fBdy_mps2[1];
      autocodePlant_DW->UnitDelay_DSTATE_c[2] = autocodePlant_B->fBdy_mps2[2];

      /* Update for RandomNumber: '<S192>/White Noise' */
      autocodePlant_DW->NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_a);

      /* Update for Memory: '<S225>/otime' incorporates:
       *  Constant: '<S176>/decimal year'
       */
      autocodePlant_DW->otime_PreviousInput = 2026.6657534246576;

      /* Update for Memory: '<S224>/olon' */
      autocodePlant_DW->olon_PreviousInput = autocodePlant_B->Switch;

      /* Update for Memory: '<S223>/olat' */
      autocodePlant_DW->olat_PreviousInput = autocodePlant_B->Switch_l;

      /* Update for Memory: '<S223>/oalt' */
      autocodePlant_DW->oalt_PreviousInput = autocodePlant_B->Gain;

      /* Update for RandomNumber: '<S187>/White Noise' */
      autocodePlant_DW->NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_b);

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_h =
        autocodePlant_B->Output_n - 0.99998 *
        autocodePlant_DW->DiscreteTransferFcn2_states_h;

      /* Update for RandomNumber: '<S178>/White Noise' */
      autocodePlant_DW->NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_p);

      /* Update for RandomNumber: '<S186>/White Noise' */
      autocodePlant_DW->NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_pb);

      /* Update for RandomNumber: '<S188>/White Noise' */
      autocodePlant_DW->NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_pa);
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(autocodePlant_M)) {
    rt_ertODEUpdateContinuousStates(&autocodePlant_M->solverInfo,
      autocodePlant_M, autocodePlant_U_control_deg, autocodePlant_Y_sensor_bus_i,
      autocodePlant_Y_plant_bus_e);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++autocodePlant_M->Timing.clockTick0;
    autocodePlant_M->Timing.t[0] = rtsiGetSolverStopTime
      (&autocodePlant_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      autocodePlant_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void autocodePlant_derivatives(RT_MODEL_autocodePlant_T *const autocodePlant_M)
{
  B_autocodePlant_T *autocodePlant_B = autocodePlant_M->blockIO;
  DW_autocodePlant_T *autocodePlant_DW = autocodePlant_M->dwork;
  X_autocodePlant_T *autocodePlant_X = autocodePlant_M->contStates;
  XDot_autocodePlant_T *_rtXdot;
  real_T pData_idx_0;
  real_T pData_idx_1;
  real_T pData_idx_2;
  real_T pData_idx_3;
  real_T uDOFQuaternion_CSTATE_tmp;
  real_T uDOFQuaternion_CSTATE_tmp_0;
  real_T uDOFQuaternion_CSTATE_tmp_1;
  real_T uDOFQuaternion_CSTATE_tmp_2;
  real_T uDOFQuaternion_CSTATE_tmp_3;
  real_T uDOFQuaternion_CSTATE_tmp_4;
  real_T uDOFQuaternion_CSTATE_tmp_5;
  real_T uDOFQuaternion_CSTATE_tmp_6;
  _rtXdot = ((XDot_autocodePlant_T *) autocodePlant_M->derivs);

  /* Derivatives for EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)' */
  memset(&_rtXdot->uDOFQuaternion_CSTATE[0], 0, 13U * sizeof(real_T));
  _rtXdot->uDOFQuaternion_CSTATE[0] = autocodePlant_B->Sum[0] / 17.5 -
    (autocodePlant_X->uDOFQuaternion_CSTATE[2] *
     autocodePlant_X->uDOFQuaternion_CSTATE[7] -
     autocodePlant_X->uDOFQuaternion_CSTATE[1] *
     autocodePlant_X->uDOFQuaternion_CSTATE[8]);
  _rtXdot->uDOFQuaternion_CSTATE[1] = autocodePlant_B->Sum[1] / 17.5 -
    (autocodePlant_X->uDOFQuaternion_CSTATE[0] *
     autocodePlant_X->uDOFQuaternion_CSTATE[8] -
     autocodePlant_X->uDOFQuaternion_CSTATE[2] *
     autocodePlant_X->uDOFQuaternion_CSTATE[6]);
  _rtXdot->uDOFQuaternion_CSTATE[2] = autocodePlant_B->Sum[2] / 17.5 -
    (autocodePlant_X->uDOFQuaternion_CSTATE[1] *
     autocodePlant_X->uDOFQuaternion_CSTATE[6] -
     autocodePlant_X->uDOFQuaternion_CSTATE[0] *
     autocodePlant_X->uDOFQuaternion_CSTATE[7]);
  pData_idx_0 = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
    autocodePlant_X->uDOFQuaternion_CSTATE[9] +
    autocodePlant_X->uDOFQuaternion_CSTATE[10] *
    autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[11] *
    autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[12] *
    autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
    autocodePlant_X->uDOFQuaternion_CSTATE[9];
  pData_idx_1 = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
    autocodePlant_X->uDOFQuaternion_CSTATE[9] +
    autocodePlant_X->uDOFQuaternion_CSTATE[10] *
    autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[11] *
    autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[12] *
    autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
    autocodePlant_X->uDOFQuaternion_CSTATE[10];
  pData_idx_2 = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
    autocodePlant_X->uDOFQuaternion_CSTATE[9] +
    autocodePlant_X->uDOFQuaternion_CSTATE[10] *
    autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[11] *
    autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[12] *
    autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
    autocodePlant_X->uDOFQuaternion_CSTATE[11];
  pData_idx_3 = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
    autocodePlant_X->uDOFQuaternion_CSTATE[9] +
    autocodePlant_X->uDOFQuaternion_CSTATE[10] *
    autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[11] *
    autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[12] *
    autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
    autocodePlant_X->uDOFQuaternion_CSTATE[12];
  uDOFQuaternion_CSTATE_tmp = pData_idx_0 * pData_idx_0;
  uDOFQuaternion_CSTATE_tmp_0 = pData_idx_1 * pData_idx_1;
  uDOFQuaternion_CSTATE_tmp_1 = pData_idx_2 * pData_idx_2;
  uDOFQuaternion_CSTATE_tmp_2 = pData_idx_3 * pData_idx_3;
  uDOFQuaternion_CSTATE_tmp_3 = pData_idx_1 * pData_idx_2;
  uDOFQuaternion_CSTATE_tmp_4 = pData_idx_0 * pData_idx_3;
  uDOFQuaternion_CSTATE_tmp_5 = pData_idx_1 * pData_idx_3;
  uDOFQuaternion_CSTATE_tmp_6 = pData_idx_0 * pData_idx_2;
  _rtXdot->uDOFQuaternion_CSTATE[3] = ((((uDOFQuaternion_CSTATE_tmp +
    uDOFQuaternion_CSTATE_tmp_0) - uDOFQuaternion_CSTATE_tmp_1) -
    uDOFQuaternion_CSTATE_tmp_2) * autocodePlant_X->uDOFQuaternion_CSTATE[0] +
    (uDOFQuaternion_CSTATE_tmp_3 - uDOFQuaternion_CSTATE_tmp_4) * 2.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[1]) + (uDOFQuaternion_CSTATE_tmp_5 +
    uDOFQuaternion_CSTATE_tmp_6) * 2.0 * autocodePlant_X->uDOFQuaternion_CSTATE
    [2];
  pData_idx_2 *= pData_idx_3;
  pData_idx_0 *= pData_idx_1;
  uDOFQuaternion_CSTATE_tmp -= uDOFQuaternion_CSTATE_tmp_0;
  _rtXdot->uDOFQuaternion_CSTATE[4] = (((uDOFQuaternion_CSTATE_tmp +
    uDOFQuaternion_CSTATE_tmp_1) - uDOFQuaternion_CSTATE_tmp_2) *
    autocodePlant_X->uDOFQuaternion_CSTATE[1] + (uDOFQuaternion_CSTATE_tmp_3 +
    uDOFQuaternion_CSTATE_tmp_4) * 2.0 * autocodePlant_X->uDOFQuaternion_CSTATE
    [0]) + (pData_idx_2 - pData_idx_0) * 2.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[2];
  _rtXdot->uDOFQuaternion_CSTATE[5] = ((uDOFQuaternion_CSTATE_tmp_5 -
    uDOFQuaternion_CSTATE_tmp_6) * 2.0 * autocodePlant_X->uDOFQuaternion_CSTATE
    [0] + (pData_idx_2 + pData_idx_0) * 2.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[1]) + ((uDOFQuaternion_CSTATE_tmp -
    uDOFQuaternion_CSTATE_tmp_1) + uDOFQuaternion_CSTATE_tmp_2) *
    autocodePlant_X->uDOFQuaternion_CSTATE[2];
  pData_idx_0 = (0.053 * autocodePlant_X->uDOFQuaternion_CSTATE[6] + 0.0 *
                 autocodePlant_X->uDOFQuaternion_CSTATE[7]) + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[8];
  pData_idx_1 = (0.0 * autocodePlant_X->uDOFQuaternion_CSTATE[6] + 8.41 *
                 autocodePlant_X->uDOFQuaternion_CSTATE[7]) + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[8];
  pData_idx_2 = (0.0 * autocodePlant_X->uDOFQuaternion_CSTATE[6] + 0.0 *
                 autocodePlant_X->uDOFQuaternion_CSTATE[7]) + 8.41 *
    autocodePlant_X->uDOFQuaternion_CSTATE[8];
  uDOFQuaternion_CSTATE_tmp_0 = (autocodePlant_B->Product_h[0] -
    (autocodePlant_X->uDOFQuaternion_CSTATE[7] * pData_idx_2 -
     autocodePlant_X->uDOFQuaternion_CSTATE[8] * pData_idx_1)) - ((0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[6] + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[7]) + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[8]);
  uDOFQuaternion_CSTATE_tmp_1 = (autocodePlant_B->Product_h[1] -
    (autocodePlant_X->uDOFQuaternion_CSTATE[8] * pData_idx_0 -
     autocodePlant_X->uDOFQuaternion_CSTATE[6] * pData_idx_2)) - ((0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[6] + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[7]) + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[8]);
  pData_idx_2 = (autocodePlant_B->Product_h[2] -
                 (autocodePlant_X->uDOFQuaternion_CSTATE[6] * pData_idx_1 -
                  autocodePlant_X->uDOFQuaternion_CSTATE[7] * pData_idx_0)) -
    ((0.0 * autocodePlant_X->uDOFQuaternion_CSTATE[6] + 0.0 *
      autocodePlant_X->uDOFQuaternion_CSTATE[7]) + 0.0 *
     autocodePlant_X->uDOFQuaternion_CSTATE[8]);
  uDOFQuaternion_CSTATE_tmp = -0.0 * uDOFQuaternion_CSTATE_tmp_1;
  _rtXdot->uDOFQuaternion_CSTATE[6] = (18.867924528301888 *
    uDOFQuaternion_CSTATE_tmp_0 + uDOFQuaternion_CSTATE_tmp) + 0.0 * pData_idx_2;
  _rtXdot->uDOFQuaternion_CSTATE[7] = (-0.0 * uDOFQuaternion_CSTATE_tmp_0 +
    0.11890606420927469 * uDOFQuaternion_CSTATE_tmp_1) + -0.0 * pData_idx_2;
  _rtXdot->uDOFQuaternion_CSTATE[8] = (0.0 * uDOFQuaternion_CSTATE_tmp_0 +
    uDOFQuaternion_CSTATE_tmp) + 0.11890606420927469 * pData_idx_2;
  _rtXdot->uDOFQuaternion_CSTATE[9] = (((0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[9] +
    -autocodePlant_X->uDOFQuaternion_CSTATE[6] *
    autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
    -autocodePlant_X->uDOFQuaternion_CSTATE[7] *
    autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
    -autocodePlant_X->uDOFQuaternion_CSTATE[8] *
    autocodePlant_X->uDOFQuaternion_CSTATE[12]) * 0.5;
  _rtXdot->uDOFQuaternion_CSTATE[10] = (((autocodePlant_X->
    uDOFQuaternion_CSTATE[6] * autocodePlant_X->uDOFQuaternion_CSTATE[9] + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[8] *
    autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
    -autocodePlant_X->uDOFQuaternion_CSTATE[7] *
    autocodePlant_X->uDOFQuaternion_CSTATE[12]) * 0.5;
  _rtXdot->uDOFQuaternion_CSTATE[11] = (((autocodePlant_X->
    uDOFQuaternion_CSTATE[7] * autocodePlant_X->uDOFQuaternion_CSTATE[9] +
    -autocodePlant_X->uDOFQuaternion_CSTATE[8] *
    autocodePlant_X->uDOFQuaternion_CSTATE[10]) + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
    autocodePlant_X->uDOFQuaternion_CSTATE[6] *
    autocodePlant_X->uDOFQuaternion_CSTATE[12]) * 0.5;
  _rtXdot->uDOFQuaternion_CSTATE[12] = (((autocodePlant_X->
    uDOFQuaternion_CSTATE[8] * autocodePlant_X->uDOFQuaternion_CSTATE[9] +
    autocodePlant_X->uDOFQuaternion_CSTATE[7] *
    autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
    -autocodePlant_X->uDOFQuaternion_CSTATE[6] *
    autocodePlant_X->uDOFQuaternion_CSTATE[11]) + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[12]) * 0.5;

  /* Derivatives for Enabled SubSystem: '<S121>/Hpgw' */
  if (autocodePlant_DW->Hpgw_MODE) {
    /* Derivatives for Integrator: '<S132>/pgw_p' */
    _rtXdot->pgw_p_CSTATE[0] = autocodePlant_B->w_p[0];
    _rtXdot->pgw_p_CSTATE[1] = autocodePlant_B->w_p[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_autocodePlant_T *) autocodePlant_M->derivs)->pgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S121>/Hpgw' */

  /* Derivatives for Enabled SubSystem: '<S122>/Hwgw(s)' */
  if (autocodePlant_DW->Hwgws_MODE) {
    /* Derivatives for Integrator: '<S137>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[0] = autocodePlant_B->w[0];

    /* Derivatives for Integrator: '<S137>/wg_p2' */
    _rtXdot->wg_p2_CSTATE[0] = autocodePlant_B->w_h[0];

    /* Derivatives for Integrator: '<S137>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[1] = autocodePlant_B->w[1];

    /* Derivatives for Integrator: '<S137>/wg_p2' */
    _rtXdot->wg_p2_CSTATE[1] = autocodePlant_B->w_h[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_autocodePlant_T *) autocodePlant_M->derivs)->wg_p1_CSTATE[0]);
      for (i1=0; i1 < 4; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S122>/Hwgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S121>/Hqgw' */
  if (autocodePlant_DW->Hqgw_MODE) {
    /* Derivatives for Integrator: '<S133>/qgw_p' */
    _rtXdot->qgw_p_CSTATE[0] = autocodePlant_B->w_j5[0];
    _rtXdot->qgw_p_CSTATE[1] = autocodePlant_B->w_j5[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_autocodePlant_T *) autocodePlant_M->derivs)->qgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S121>/Hqgw' */

  /* Derivatives for Enabled SubSystem: '<S122>/Hvgw(s)' */
  if (autocodePlant_DW->Hvgws_MODE) {
    /* Derivatives for Integrator: '<S136>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[0] = autocodePlant_B->w_c[0];

    /* Derivatives for Integrator: '<S136>/vgw_p2' */
    _rtXdot->vgw_p2_CSTATE[0] = autocodePlant_B->w_j[0];

    /* Derivatives for Integrator: '<S136>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[1] = autocodePlant_B->w_c[1];

    /* Derivatives for Integrator: '<S136>/vgw_p2' */
    _rtXdot->vgw_p2_CSTATE[1] = autocodePlant_B->w_j[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_autocodePlant_T *) autocodePlant_M->derivs)->vg_p1_CSTATE[0]);
      for (i1=0; i1 < 4; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S122>/Hvgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S121>/Hrgw' */
  if (autocodePlant_DW->Hrgw_MODE) {
    /* Derivatives for Integrator: '<S134>/rgw_p' */
    _rtXdot->rgw_p_CSTATE[0] = autocodePlant_B->w_g[0];
    _rtXdot->rgw_p_CSTATE[1] = autocodePlant_B->w_g[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_autocodePlant_T *) autocodePlant_M->derivs)->rgw_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S121>/Hrgw' */

  /* Derivatives for Enabled SubSystem: '<S122>/Hugw(s)' */
  if (autocodePlant_DW->Hugws_MODE) {
    /* Derivatives for Integrator: '<S135>/ug_p' */
    _rtXdot->ug_p_CSTATE[0] = autocodePlant_B->w_d[0];
    _rtXdot->ug_p_CSTATE[1] = autocodePlant_B->w_d[1];
  } else {
    {
      real_T *dx;
      int_T i1;
      dx = &(((XDot_autocodePlant_T *) autocodePlant_M->derivs)->ug_p_CSTATE[0]);
      for (i1=0; i1 < 2; i1++) {
        dx[i1] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S122>/Hugw(s)' */
}

/* Model initialize function */
void autocodePlant_initialize(RT_MODEL_autocodePlant_T *const autocodePlant_M,
  real_T autocodePlant_U_control_deg[4], sensor_bus
  *autocodePlant_Y_sensor_bus_i, plant_bus *autocodePlant_Y_plant_bus_e)
{
  B_autocodePlant_T *autocodePlant_B = autocodePlant_M->blockIO;
  DW_autocodePlant_T *autocodePlant_DW = autocodePlant_M->dwork;
  X_autocodePlant_T *autocodePlant_X = autocodePlant_M->contStates;
  XDis_autocodePlant_T *autocodePlant_XDis = ((XDis_autocodePlant_T *)
    autocodePlant_M->contStateDisabled);

  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&autocodePlant_M->solverInfo,
                          &autocodePlant_M->Timing.simTimeStep);
    rtsiSetTPtr(&autocodePlant_M->solverInfo, &rtmGetTPtr(autocodePlant_M));
    rtsiSetStepSizePtr(&autocodePlant_M->solverInfo,
                       &autocodePlant_M->Timing.stepSize0);
    rtsiSetdXPtr(&autocodePlant_M->solverInfo, &autocodePlant_M->derivs);
    rtsiSetContStatesPtr(&autocodePlant_M->solverInfo, (real_T **)
                         &autocodePlant_M->contStates);
    rtsiSetNumContStatesPtr(&autocodePlant_M->solverInfo,
      &autocodePlant_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&autocodePlant_M->solverInfo,
      &autocodePlant_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&autocodePlant_M->solverInfo,
      &autocodePlant_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&autocodePlant_M->solverInfo,
      &autocodePlant_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&autocodePlant_M->solverInfo, (boolean_T**)
      &autocodePlant_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&autocodePlant_M->solverInfo, (&rtmGetErrorStatus
      (autocodePlant_M)));
    rtsiSetRTModelPtr(&autocodePlant_M->solverInfo, autocodePlant_M);
  }

  rtsiSetSimTimeStep(&autocodePlant_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&autocodePlant_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&autocodePlant_M->solverInfo, false);
  autocodePlant_M->intgData.y = autocodePlant_M->odeY;
  autocodePlant_M->intgData.f[0] = autocodePlant_M->odeF[0];
  autocodePlant_M->intgData.f[1] = autocodePlant_M->odeF[1];
  autocodePlant_M->intgData.f[2] = autocodePlant_M->odeF[2];
  autocodePlant_M->intgData.f[3] = autocodePlant_M->odeF[3];
  autocodePlant_M->contStates = ((X_autocodePlant_T *) autocodePlant_X);
  autocodePlant_M->contStateDisabled = ((XDis_autocodePlant_T *)
    autocodePlant_XDis);
  autocodePlant_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&autocodePlant_M->solverInfo, (void *)
                    &autocodePlant_M->intgData);
  rtsiSetSolverName(&autocodePlant_M->solverInfo,"ode4");
  rtmSetTPtr(autocodePlant_M, &autocodePlant_M->Timing.tArray[0]);
  autocodePlant_M->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) autocodePlant_B), 0,
                sizeof(B_autocodePlant_T));

  /* states (continuous) */
  {
    (void) memset((void *)autocodePlant_X, 0,
                  sizeof(X_autocodePlant_T));
  }

  /* disabled states */
  {
    (void) memset((void *)autocodePlant_XDis, 0,
                  sizeof(XDis_autocodePlant_T));
  }

  /* states (dwork) */
  (void) memset((void *)autocodePlant_DW, 0,
                sizeof(DW_autocodePlant_T));

  /* external inputs */
  (void)memset(&autocodePlant_U_control_deg[0], 0, sizeof(real_T) << 2U);

  /* external outputs */
  *autocodePlant_Y_sensor_bus_i = autocodePlant_rtZsensor_bus;
  *autocodePlant_Y_plant_bus_e = autocodePlant_rtZplant_bus;

  {
    int32_T i;

    /* Start for If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = -1;

    /* Start for If: '<S127>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f = -1;

    /* Start for If: '<S213>/If' */
    autocodePlant_DW->If_ActiveSubsystem = -1;

    /* InitializeConditions for RandomNumber: '<S179>/White Noise' */
    autocodePlant_DW->RandSeed = 1529675776U;
    autocodePlant_DW->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed);

    /* InitializeConditions for EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)' */
    autocodePlant_X->uDOFQuaternion_CSTATE[0] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[3] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[6] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[1] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[4] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[7] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[2] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[5] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[8] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[9] = 0.6708824723277448;
    autocodePlant_X->uDOFQuaternion_CSTATE[10] = 4.32797643155616E-18;
    autocodePlant_X->uDOFQuaternion_CSTATE[11] = 0.7415636913464768;
    autocodePlant_X->uDOFQuaternion_CSTATE[12] = 4.32797643155616E-18;

    /* InitializeConditions for RandomNumber: '<S131>/White Noise' */
    autocodePlant_DW->RandSeed_i[0] = 1529675776U;
    autocodePlant_DW->NextOutput_d[0] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[0]);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[0] = 0.0;

    /* InitializeConditions for RandomNumber: '<S131>/White Noise' */
    autocodePlant_DW->RandSeed_i[1] = 1529741312U;
    autocodePlant_DW->NextOutput_d[1] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[1]);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[1] = 0.0;

    /* InitializeConditions for RandomNumber: '<S131>/White Noise' */
    autocodePlant_DW->RandSeed_i[2] = 1529806848U;
    autocodePlant_DW->NextOutput_d[2] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[2]);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[2] = 0.0;

    /* InitializeConditions for RandomNumber: '<S131>/White Noise' */
    autocodePlant_DW->RandSeed_i[3] = 1529872384U;
    autocodePlant_DW->NextOutput_d[3] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[3]);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[3] = 0.0;

    /* InitializeConditions for RandomNumber: '<S189>/White Noise' */
    autocodePlant_DW->RandSeed_l = 1529675776U;
    autocodePlant_DW->NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_l);

    /* InitializeConditions for RandomNumber: '<S192>/White Noise' */
    autocodePlant_DW->RandSeed_a = 1529675776U;
    autocodePlant_DW->NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_a);

    /* InitializeConditions for Memory: '<S225>/otime' */
    autocodePlant_DW->otime_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S224>/olon' */
    autocodePlant_DW->olon_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S223>/olat' */
    autocodePlant_DW->olat_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S223>/oalt' */
    autocodePlant_DW->oalt_PreviousInput = -1000.0;

    /* InitializeConditions for RandomNumber: '<S187>/White Noise' */
    autocodePlant_DW->RandSeed_b = 1529675776U;
    autocodePlant_DW->NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_b);

    /* InitializeConditions for RandomNumber: '<S178>/White Noise' */
    autocodePlant_DW->RandSeed_p = 1529675776U;
    autocodePlant_DW->NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_p);

    /* InitializeConditions for RandomNumber: '<S186>/White Noise' */
    autocodePlant_DW->RandSeed_pb = 1529675776U;
    autocodePlant_DW->NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_pb);

    /* InitializeConditions for RandomNumber: '<S188>/White Noise' */
    autocodePlant_DW->RandSeed_pa = 1529675776U;
    autocodePlant_DW->NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_pa);

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hpgw' */
    /* InitializeConditions for Integrator: '<S132>/pgw_p' */
    autocodePlant_X->pgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hpgw' */

    /* SystemInitialize for Enabled SubSystem: '<S122>/Hwgw(s)' */
    /* InitializeConditions for Integrator: '<S137>/wg_p1' */
    autocodePlant_X->wg_p1_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S137>/wg_p2' */
    autocodePlant_X->wg_p2_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S122>/Hwgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hqgw' */
    /* InitializeConditions for Integrator: '<S133>/qgw_p' */
    autocodePlant_X->qgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hqgw' */

    /* SystemInitialize for Enabled SubSystem: '<S122>/Hvgw(s)' */
    /* InitializeConditions for Integrator: '<S136>/vg_p1' */
    autocodePlant_X->vg_p1_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S136>/vgw_p2' */
    autocodePlant_X->vgw_p2_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S122>/Hvgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hrgw' */
    /* InitializeConditions for Integrator: '<S134>/rgw_p' */
    autocodePlant_X->rgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hrgw' */

    /* SystemInitialize for Enabled SubSystem: '<S122>/Hugw(s)' */
    /* InitializeConditions for Integrator: '<S135>/ug_p' */
    autocodePlant_X->ug_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S122>/Hugw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hpgw' */
    /* InitializeConditions for Integrator: '<S132>/pgw_p' */
    autocodePlant_X->pgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hpgw' */

    /* SystemInitialize for Enabled SubSystem: '<S122>/Hwgw(s)' */
    /* InitializeConditions for Integrator: '<S137>/wg_p1' */
    autocodePlant_X->wg_p1_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S137>/wg_p2' */
    autocodePlant_X->wg_p2_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S122>/Hwgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hqgw' */
    /* InitializeConditions for Integrator: '<S133>/qgw_p' */
    autocodePlant_X->qgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hqgw' */

    /* SystemInitialize for Enabled SubSystem: '<S122>/Hvgw(s)' */
    /* InitializeConditions for Integrator: '<S136>/vg_p1' */
    autocodePlant_X->vg_p1_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S136>/vgw_p2' */
    autocodePlant_X->vgw_p2_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S122>/Hvgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hrgw' */
    /* InitializeConditions for Integrator: '<S134>/rgw_p' */
    autocodePlant_X->rgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hrgw' */

    /* SystemInitialize for Enabled SubSystem: '<S122>/Hugw(s)' */
    /* InitializeConditions for Integrator: '<S135>/ug_p' */
    autocodePlant_X->ug_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S122>/Hugw(s)' */

    /* SystemInitialize for Merge: '<S213>/Merge' */
    autocodePlant_B->Merge = 1.0;

    /* SystemInitialize for Enabled SubSystem: '<S208>/Convert from geodetic to  spherical coordinates ' */
    /* SystemInitialize for Iterator SubSystem: '<S221>/For Iterator Subsystem' */
    /* SystemInitialize for Assignment: '<S268>/Assignment' incorporates:
     *  Outport: '<S268>/sp[11]'
     */
    memcpy(&autocodePlant_B->Assignment[0], &rtCP__sp11_Y0[0], 11U * sizeof
           (real_T));

    /* SystemInitialize for Assignment: '<S268>/Assignment1' incorporates:
     *  Outport: '<S268>/cp[11]'
     */
    memcpy(&autocodePlant_B->Assignment1[0], &rtCP__cp11_Y0[0], 11U * sizeof
           (real_T));

    /* End of SystemInitialize for SubSystem: '<S221>/For Iterator Subsystem' */

    /* SystemInitialize for SignalConversion generated from: '<S221>/sp[13]' incorporates:
     *  Outport: '<S221>/sp[13]'
     */
    memcpy(&autocodePlant_B->OutportBufferForsp13[0], &rtCP__sp13_Y0[0], 13U *
           sizeof(real_T));

    /* SystemInitialize for SignalConversion generated from: '<S221>/cp[13]' incorporates:
     *  Outport: '<S221>/cp[13]'
     */
    memcpy(&autocodePlant_B->OutportBufferForcp13[0], &rtCP__cp13_Y0[0], 13U *
           sizeof(real_T));

    /* End of SystemInitialize for SubSystem: '<S208>/Convert from geodetic to  spherical coordinates ' */

    /* SystemInitialize for Enabled SubSystem: '<S208>/Convert from geodetic to  spherical coordinates' */
    /* SystemInitialize for Sqrt: '<S220>/sqrt' incorporates:
     *  Outport: '<S220>/r'
     */
    autocodePlant_B->sqrt_b = 6378.137;

    /* SystemInitialize for Product: '<S261>/Product4' incorporates:
     *  Outport: '<S220>/ct'
     */
    autocodePlant_B->Product4 = 1.0;

    /* End of SystemInitialize for SubSystem: '<S208>/Convert from geodetic to  spherical coordinates' */

    /* SystemInitialize for Iterator SubSystem: '<S208>/Compute magnetic vector in spherical coordinates' */
    /* InitializeConditions for UnitDelay: '<S219>/Unit Delay2' */
    autocodePlant_DW->UnitDelay2_DSTATE[0] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[1] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[2] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[3] = 0.0;

    /* SystemInitialize for Iterator SubSystem: '<S219>/For Iterator Subsystem' */
    /* SystemInitialize for Enabled SubSystem: '<S227>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */
    /* SystemInitialize for Merge: '<S229>/Merge' */
    autocodePlant_B->Merge_b = 0.0;

    /* SystemInitialize for Merge: '<S229>/Merge1' */
    autocodePlant_B->Merge1_i = 0.0;

    /* InitializeConditions for UnitDelay: '<S229>/Unit Delay1' */
    memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_c[0],
           &rtCP__UnitDelay1_InitialCondi_n[0], 169U * sizeof(real_T));

    /* SystemInitialize for Assignment: '<S229>/Assignment_snorm' incorporates:
     *  Outport: '<S229>/snorm[169]'
     */
    memcpy(&autocodePlant_B->Assignment_snorm[0], &rtCP__snorm169_Y0[0], 169U *
           sizeof(real_T));

    /* End of SystemInitialize for SubSystem: '<S227>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */

    /* SystemInitialize for Enabled SubSystem: '<S228>/Special case - North//South Geographic Pole' */
    /* SystemInitialize for IfAction SubSystem: '<S231>/If Action Subsystem2' */
    /* SystemInitialize for IfAction SubSystem: '<S231>/If Action Subsystem1' */
    for (i = 0; i < 13; i++) {
      /* InitializeConditions for UnitDelay: '<S231>/Unit Delay1' */
      autocodePlant_DW->UnitDelay1_DSTATE_b[i] = 1.0;

      /* SystemInitialize for Assignment: '<S235>/Assignment2' incorporates:
       *  Outport: '<S235>/pp[13]'
       */
      autocodePlant_B->Assignment2_m[i] = 1.0;

      /* SystemInitialize for Assignment: '<S236>/Assignment2' incorporates:
       *  Outport: '<S236>/pp[13]'
       */
      autocodePlant_B->Assignment2_a[i] = 1.0;
    }

    /* End of SystemInitialize for SubSystem: '<S231>/If Action Subsystem1' */
    /* End of SystemInitialize for SubSystem: '<S231>/If Action Subsystem2' */
    /* End of SystemInitialize for SubSystem: '<S228>/Special case - North//South Geographic Pole' */
    /* End of SystemInitialize for SubSystem: '<S219>/For Iterator Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S208>/Compute magnetic vector in spherical coordinates' */
  }
}

/* Model terminate function */
void autocodePlant_terminate(RT_MODEL_autocodePlant_T *const autocodePlant_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(autocodePlant_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
