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
 * C/C++ source code generated on : Thu Nov  5 20:49:28 2026
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
#include "rt_urand_Upu32_Yd_f_pw_snf.h"
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

static void rate_scheduler(RT_MODEL_autocodePlant_T *const autocodePlant_M);
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
  0.0,                                 /* baroMeas_Pa */

  { 0.0, 0.0, 0.0 },                   /* velNedMeas_mps */

  { 0.0, 0.0, 0.0 },                   /* gpsLLA_na */
  false                                /* gpsFix_b */
};

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(RT_MODEL_autocodePlant_T *const autocodePlant_M)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (autocodePlant_M->Timing.TaskCounters.TID[2])++;
  if ((autocodePlant_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.1s, 0.0s] */
    autocodePlant_M->Timing.TaskCounters.TID[2] = 0;
  }

  (autocodePlant_M->Timing.TaskCounters.TID[3])++;
  if ((autocodePlant_M->Timing.TaskCounters.TID[3]) > 99) {/* Sample time: [1.0s, 0.0s] */
    autocodePlant_M->Timing.TaskCounters.TID[3] = 0;
  }
}

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
    real_T rtb_Delay[6];
    real_T rtb_ElementProduct[6];
    real_T Gdependent[3];
    real_T biasnoise_d[3];
    real_T rtb_MathFunction[3];
    real_T rtb_Product6_kk[3];
    real_T rtb_Product_fn[3];
    real_T rtb_Product_ne[3];
    real_T rtb_Sum1_a1[3];
    real_T rtb_Sum1_b[3];
    real_T rtb_Sum1_hn[3];
    real_T rtb_Sum1_ju[3];
    real_T rtb_Sum1_o5[3];
    real_T rtb_Sum_aw[3];
    real_T rtb_Sum_dj[3];
    real_T rtb_Sum_el[3];
    real_T rtb_Sum_hp[3];
    real_T rtb_Sum_k[3];
    real_T rtb_Sum_mu[3];
    real_T rtb_Sum_n3[3];
    real_T rtb_VectorConcatenate[3];
    real_T rtb_VectorConcatenate_h[3];
    real_T rtb_ZeroOrderHold[3];
    real_T rtb_ZeroOrderHold_a[3];
    real_T rtb_ZeroOrderHold_c[3];
    real_T rtb_finMomentArm_m[3];
    real_T rtb_gravityForceBdy_N[3];
    real_T rtb_velBdy_mps[3];
    real_T rtb_wBdy_rps[3];
    real_T rtb_Product1_l3[2];
    real_T Merge_n;
    real_T localProduct;
    real_T rtb_FlatEarthtoLLA_o1_idx_1;
    real_T rtb_Gain_l;
    real_T rtb_Gain_oa;
    real_T rtb_Lw_idx_0;
    real_T rtb_Lw_idx_1;
    real_T rtb_Product1_hx;
    real_T rtb_Product1_jv;
    real_T rtb_Product2_l3;
    real_T rtb_Product3_ax;
    real_T rtb_Product_h5;
    real_T rtb_Product_n;
    real_T rtb_Sign1;
    real_T rtb_Sign1_e;
    real_T rtb_Sign1_i;
    real_T rtb_Sum;
    real_T rtb_Sum1_k3;
    real_T rtb_Sum1_n;
    real_T rtb_Sum2_fl;
    real_T rtb_Sum_d0;
    real_T rtb_Sum_ls;
    real_T rtb_Sum_oc;
    real_T rtb_Switch_a_idx_0;
    real_T rtb_Switch_a_idx_1;
    real_T rtb_Switch_a_idx_2;
    real_T rtb_Switch_a_idx_3;
    real_T rtb_Switch_d_idx_0;
    real_T rtb_Switch_d_idx_1;
    real_T rtb_Switch_d_idx_2;
    real_T rtb_TT0gLR;
    real_T rtb_TmpSignalConversionAtProd_0;
    real_T rtb_UnaryMinus1_k4;
    real_T rtb_UnaryMinus1_o;
    real_T rtb_UnaryMinus_a;
    real_T rtb_VectorConcatenate_tmp;
    real_T rtb_a;
    real_T rtb_sincos_o1_idx_1;
    real_T rtb_sincos_o2_idx_0;
    real_T rtb_truth_bus_accBiasTrue_mps2_;
    real_T rtb_truth_bus_accBiasTrue_mps_0;
    real_T rtb_truth_bus_gyroBiasTrue_rp_0;
    real_T rtb_truth_bus_gyroBiasTrue_rp_1;
    real_T rtb_truth_bus_gyroBiasTrue_rps_;
    real_T rtb_w3;
    int32_T Merge_b_tmp;
    int32_T i;
    int32_T rtb_Sum2_ct;
    int32_T s225_iter;
    int32_T s266_iter;
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

    /* Outputs for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' incorporates:
     *  EnablePort: '<S218>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hugw(s)' incorporates:
     *  EnablePort: '<S134>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S120>/Hrgw' incorporates:
     *  EnablePort: '<S133>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hvgw(s)' incorporates:
     *  EnablePort: '<S135>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S120>/Hqgw' incorporates:
     *  EnablePort: '<S132>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hwgw(s)' incorporates:
     *  EnablePort: '<S136>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S120>/Hpgw' incorporates:
     *  EnablePort: '<S131>/Enable'
     */
    /* RateTransition: '<S174>/Rate Transition' */
    tmp = (rtmIsMajorTimeStep(autocodePlant_M) &&
           autocodePlant_M->Timing.TaskCounters.TID[1] == 0);

    /* End of Outputs for SubSystem: '<S120>/Hpgw' */
    /* End of Outputs for SubSystem: '<S121>/Hwgw(s)' */
    /* End of Outputs for SubSystem: '<S120>/Hqgw' */
    /* End of Outputs for SubSystem: '<S121>/Hvgw(s)' */
    /* End of Outputs for SubSystem: '<S120>/Hrgw' */
    /* End of Outputs for SubSystem: '<S121>/Hugw(s)' */
    /* End of Outputs for SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' */
    if (tmp) {
      /* Sum: '<S172>/bias' incorporates:
       *  Constant: '<S172>/  '
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn'
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn2'
       */
      rtb_ZeroOrderHold_a[0] = autocodePlant_DW->DiscreteTransferFcn_states +
        0.007805089418666159;
      rtb_ZeroOrderHold_a[1] = autocodePlant_DW->DiscreteTransferFcn1_states +
        0.007805089418666159;
      rtb_ZeroOrderHold_a[2] = autocodePlant_DW->DiscreteTransferFcn2_states +
        0.007805089418666159;

      /* Sum: '<S170>/bias' incorporates:
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn2'
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn3'
       */
      rtb_ZeroOrderHold_c[0] = autocodePlant_DW->DiscreteTransferFcn2_states_k -
        0.01056034519496827;
      rtb_ZeroOrderHold_c[1] = autocodePlant_DW->DiscreteTransferFcn1_states_a -
        0.01056034519496827;
      rtb_ZeroOrderHold_c[2] = autocodePlant_DW->DiscreteTransferFcn3_states -
        0.01056034519496827;

      /* RandomNumber: '<S177>/White Noise' */
      localProduct = autocodePlant_DW->NextOutput;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S172>/  '
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn2'
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn'
       *  Sum: '<S170>/bias'
       *  Sum: '<S172>/bias'
       */
      rtb_truth_bus_gyroBiasTrue_rps_ =
        autocodePlant_DW->DiscreteTransferFcn_states + 0.007805089418666159;
      rtb_Sum_oc = autocodePlant_DW->DiscreteTransferFcn2_states_k -
        0.01056034519496827;

      /* Sum: '<S170>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn2'
       *  Gain: '<S177>/Output'
       *  RandomNumber: '<S177>/White Noise'
       *  Sum: '<S170>/bias'
       */
      autocodePlant_B->biasnoise[0] =
        (autocodePlant_DW->DiscreteTransferFcn2_states_k - 0.01056034519496827)
        + 0.0073574999999999995 * autocodePlant_DW->NextOutput;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S172>/  '
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn1'
       *  Sum: '<S170>/bias'
       *  Sum: '<S172>/bias'
       */
      rtb_truth_bus_gyroBiasTrue_rp_0 =
        autocodePlant_DW->DiscreteTransferFcn1_states + 0.007805089418666159;
      rtb_truth_bus_accBiasTrue_mps2_ =
        autocodePlant_DW->DiscreteTransferFcn1_states_a - 0.01056034519496827;

      /* Sum: '<S170>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn1'
       *  Gain: '<S177>/Output'
       *  RandomNumber: '<S177>/White Noise'
       *  Sum: '<S170>/bias'
       */
      autocodePlant_B->biasnoise[1] =
        (autocodePlant_DW->DiscreteTransferFcn1_states_a - 0.01056034519496827)
        + 0.0073574999999999995 * autocodePlant_DW->NextOutput;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S172>/  '
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn3'
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn2'
       *  Sum: '<S170>/bias'
       *  Sum: '<S172>/bias'
       */
      rtb_truth_bus_gyroBiasTrue_rp_1 =
        autocodePlant_DW->DiscreteTransferFcn2_states + 0.007805089418666159;
      rtb_truth_bus_accBiasTrue_mps_0 =
        autocodePlant_DW->DiscreteTransferFcn3_states - 0.01056034519496827;

      /* Sum: '<S170>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn3'
       *  Gain: '<S177>/Output'
       *  RandomNumber: '<S177>/White Noise'
       *  Sum: '<S170>/bias'
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
    rtb_Sum1_ju[0] = autocodePlant_X->uDOFQuaternion_CSTATE[3];
    rtb_Sum1_ju[1] = autocodePlant_X->uDOFQuaternion_CSTATE[4];
    rtb_Sum1_ju[2] = autocodePlant_X->uDOFQuaternion_CSTATE[5];
    rtb_wBdy_rps[0] = autocodePlant_X->uDOFQuaternion_CSTATE[6];
    rtb_wBdy_rps[1] = autocodePlant_X->uDOFQuaternion_CSTATE[7];
    rtb_wBdy_rps[2] = autocodePlant_X->uDOFQuaternion_CSTATE[8];
    rtb_Switch_a_idx_0 = autocodePlant_X->uDOFQuaternion_CSTATE[9];
    rtb_Switch_a_idx_1 = autocodePlant_X->uDOFQuaternion_CSTATE[10];
    rtb_Switch_a_idx_2 = autocodePlant_X->uDOFQuaternion_CSTATE[11];
    rtb_Switch_a_idx_3 = autocodePlant_X->uDOFQuaternion_CSTATE[12];

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
    rtb_w3 = rtb_TT0gLR * rtb_Gain_l;

    /* Product: '<S113>/Product3' incorporates:
     *  Product: '<S112>/Product3'
     */
    rtb_Sum1_k3 = rtb_Sign1_e * rtb_Sign1;

    /* Product: '<S113>/Product5' incorporates:
     *  Constant: '<S4>/gNed_mps2'
     *  Gain: '<S113>/Gain1'
     *  Product: '<S113>/Product2'
     *  Product: '<S113>/Product3'
     *  Sum: '<S113>/Sum2'
     */
    rtb_a = (rtb_Sum1_k3 - rtb_w3) * 2.0 * 0.0;

    /* Product: '<S111>/Product7' incorporates:
     *  Product: '<S112>/Product7'
     */
    rtb_Product2_l3 = rtb_Sign1 * rtb_Sign1;

    /* Product: '<S111>/Product' incorporates:
     *  Product: '<S112>/Product'
     */
    rtb_Product_n = rtb_Gain_l * rtb_Sign1_e;

    /* Product: '<S111>/Product1' incorporates:
     *  Product: '<S112>/Product1'
     */
    rtb_Sign1_i = rtb_TT0gLR * rtb_Sign1;

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
    rtb_gravityForceBdy_N[0] = ((((0.5 - rtb_Sign1_e) - rtb_Product2_l3) * 2.0 *
      0.0 + (rtb_Product_n + rtb_Sign1_i) * 2.0 * 0.0) + (rtb_Sign1 - rtb_TT0gLR)
      * 2.0 * 9.81) * 17.5;

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
    rtb_gravityForceBdy_N[1] = (((rtb_Gain_l - rtb_Product2_l3) * 2.0 * 0.0 +
      (rtb_Product_n - rtb_Sign1_i) * 2.0 * 0.0) + (rtb_w3 + rtb_Sum1_k3) * 2.0 *
      9.81) * 17.5;
    rtb_gravityForceBdy_N[2] = (((rtb_Sign1 + rtb_TT0gLR) * 2.0 * 0.0 + rtb_a) +
      (rtb_Gain_l - rtb_Sign1_e) * 2.0 * 9.81) * 17.5;

    /* UnitConversion: '<S122>/Unit Conversion' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  UnaryMinus: '<S101>/Unary Minus'
     */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    rtb_Gain_l = 3.280839895013123 * -autocodePlant_X->uDOFQuaternion_CSTATE[5];

    /* Saturate: '<S155>/Limit Function 10ft to 1000ft' */
    if (rtb_Gain_l > 1000.0) {
      rtb_Sum1_k3 = 1000.0;
    } else if (rtb_Gain_l < 10.0) {
      rtb_Sum1_k3 = 10.0;
    } else {
      rtb_Sum1_k3 = rtb_Gain_l;
    }

    /* End of Saturate: '<S155>/Limit Function 10ft to 1000ft' */

    /* Gain: '<S127>/Lw' */
    rtb_Lw_idx_1 = autocodePlant_ConstB.UnitConversion_k;

    /* Interpolation_n-D: '<S137>/Medium//High Altitude Intensity' incorporates:
     *  PreLookup: '<S137>/PreLook-Up Index Search  (altitude)'
     *  PreLookup: '<S137>/PreLook-Up Index Search  (prob of exceed)'
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
      /* Product: '<S130>/Product' incorporates:
       *  RandomNumber: '<S130>/White Noise'
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
    rtb_w3 = (autocodePlant_X->uDOFQuaternion_CSTATE[0] *
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
    if (rtb_w3 >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* UnitConversion: '<S128>/Unit Conversion' incorporates:
     *  Constant: '<S116>/Constant'
     *  DotProduct: '<S101>/Dot Product'
     *  MinMax: '<S116>/Max'
     *  Product: '<S116>/Product'
     *  Sqrt: '<S101>/Sqrt'
     *  Switch: '<S116>/Switch'
     */
    rtb_TT0gLR = sqrt((real_T)i * fmax(1.0E-6, rtb_w3)) * 3.280839895013123;

    /* Outputs for Enabled SubSystem: '<S120>/Hpgw' incorporates:
     *  EnablePort: '<S131>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hpgw_MODE) {
      (void) memset(&(autocodePlant_XDis->pgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S131>/pgw_p' */
      autocodePlant_X->pgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->pgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hpgw_MODE = true;
    }

    if (autocodePlant_DW->Hpgw_MODE) {
      /* Fcn: '<S131>/sqrt(0.8//V)' */
      rtb_Product3_ax = sqrt(0.8 / rtb_TT0gLR);

      /* Product: '<S131>/w3' */
      rtb_w3 = rtb_TT0gLR * autocodePlant_ConstB.w4;

      /* Product: '<S131>/w' incorporates:
       *  Fcn: '<S131>/sqrt(0.8//V)'
       *  Gain: '<S127>/Lw'
       *  Integrator: '<S131>/pgw_p'
       *  Math: '<S131>/L^1//3'
       *  Product: '<S131>/Lug//V1'
       *  Product: '<S131>/w1'
       *  Product: '<S131>/w2'
       *  Sum: '<S131>/Sum'
       */
      autocodePlant_B->w_p[0] = (rtb_Product3_ax / rt_powd_snf(rtb_Sum1_k3,
        0.3333333333333333) * autocodePlant_ConstB.u16 *
        autocodePlant_B->Product[3] - autocodePlant_X->pgw_p_CSTATE[0]) * rtb_w3;

      /* Math: '<S131>/L^1//3' */
      if (rtb_Lw_idx_1 < 0.0) {
        rtb_Sign1 = -rt_powd_snf(-rtb_Lw_idx_1, 0.3333333333333333);
      } else {
        rtb_Sign1 = rt_powd_snf(rtb_Lw_idx_1, 0.3333333333333333);
      }

      /* Product: '<S131>/w' incorporates:
       *  Fcn: '<S131>/sqrt(0.8//V)'
       *  Integrator: '<S131>/pgw_p'
       *  Product: '<S131>/Lug//V1'
       *  Product: '<S131>/w1'
       *  Product: '<S131>/w2'
       *  Sum: '<S131>/Sum'
       */
      autocodePlant_B->w_p[1] = (rtb_Product3_ax / rtb_Sign1 *
        autocodePlant_ConstB.u16 * autocodePlant_B->Product[3] -
        autocodePlant_X->pgw_p_CSTATE[1]) * rtb_w3;

      /* Product: '<S131>/sigma_w' incorporates:
       *  Integrator: '<S131>/pgw_p'
       */
      autocodePlant_B->sigma_w[0] = autocodePlant_ConstB.sigma_wg *
        autocodePlant_X->pgw_p_CSTATE[0];
      autocodePlant_B->sigma_w[1] = rtb_a * autocodePlant_X->pgw_p_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S120>/Hpgw' */

    /* Outputs for Enabled SubSystem: '<S121>/Hwgw(s)' incorporates:
     *  EnablePort: '<S136>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hwgws_MODE) {
      (void) memset(&(autocodePlant_XDis->wg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S136>/wg_p1' */
      autocodePlant_X->wg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S136>/wg_p2' */
      autocodePlant_X->wg_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S136>/wg_p1' */
      autocodePlant_X->wg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S136>/wg_p2' */
      autocodePlant_X->wg_p2_CSTATE[1] = 0.0;
      autocodePlant_DW->Hwgws_MODE = true;
    }

    if (autocodePlant_DW->Hwgws_MODE) {
      /* Product: '<S136>/Lwg//V' incorporates:
       *  Gain: '<S127>/Lw'
       */
      rtb_w3 = rtb_Sum1_k3 / rtb_TT0gLR;

      /* Product: '<S136>/w' incorporates:
       *  Gain: '<S136>/1//pi'
       *  Integrator: '<S136>/wg_p1'
       *  Product: '<S136>/Lug//V1'
       *  Sqrt: '<S136>/sqrt1'
       *  Sum: '<S136>/Sum'
       */
      rtb_Sign1 = (sqrt(0.3183098861837907 * rtb_w3) * autocodePlant_B->Product
                   [2] - autocodePlant_X->wg_p1_CSTATE[0]) / rtb_w3;
      autocodePlant_B->w[0] = rtb_Sign1;

      /* Product: '<S136>/w ' incorporates:
       *  Integrator: '<S136>/wg_p1'
       *  Integrator: '<S136>/wg_p2'
       *  Product: '<S136>/Lwg//V '
       *  Sum: '<S136>/Sum1'
       */
      autocodePlant_B->w_h[0] = (rtb_Sign1 * autocodePlant_ConstB.sqrt_g *
        rtb_w3 + (autocodePlant_X->wg_p1_CSTATE[0] -
                  autocodePlant_X->wg_p2_CSTATE[0])) / rtb_w3;

      /* Product: '<S136>/Lwg//V' */
      rtb_w3 = rtb_Lw_idx_1 / rtb_TT0gLR;

      /* Product: '<S136>/w' incorporates:
       *  Gain: '<S136>/1//pi'
       *  Integrator: '<S136>/wg_p1'
       *  Product: '<S136>/Lug//V1'
       *  Sqrt: '<S136>/sqrt1'
       *  Sum: '<S136>/Sum'
       */
      rtb_Sign1 = (sqrt(0.3183098861837907 * rtb_w3) * autocodePlant_B->Product
                   [2] - autocodePlant_X->wg_p1_CSTATE[1]) / rtb_w3;
      autocodePlant_B->w[1] = rtb_Sign1;

      /* Product: '<S136>/w ' incorporates:
       *  Integrator: '<S136>/wg_p1'
       *  Integrator: '<S136>/wg_p2'
       *  Product: '<S136>/Lwg//V '
       *  Sum: '<S136>/Sum1'
       */
      autocodePlant_B->w_h[1] = (rtb_Sign1 * autocodePlant_ConstB.sqrt_g *
        rtb_w3 + (autocodePlant_X->wg_p1_CSTATE[1] -
                  autocodePlant_X->wg_p2_CSTATE[1])) / rtb_w3;

      /* Product: '<S136>/Lwg//V 1' incorporates:
       *  Integrator: '<S136>/wg_p2'
       */
      autocodePlant_B->LwgV1[0] = autocodePlant_ConstB.sigma_wg *
        autocodePlant_X->wg_p2_CSTATE[0];
      autocodePlant_B->LwgV1[1] = rtb_a * autocodePlant_X->wg_p2_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S121>/Hwgw(s)' */

    /* Outputs for Enabled SubSystem: '<S120>/Hqgw' incorporates:
     *  EnablePort: '<S132>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hqgw_MODE) {
      (void) memset(&(autocodePlant_XDis->qgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S132>/qgw_p' */
      autocodePlant_X->qgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->qgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hqgw_MODE = true;
    }

    if (autocodePlant_DW->Hqgw_MODE) {
      /* Gain: '<S132>/pi//4' */
      rtb_w3 = 0.7853981633974483 * rtb_TT0gLR;

      /* Product: '<S132>/w' incorporates:
       *  Integrator: '<S132>/qgw_p'
       *  Product: '<S132>/wg//V'
       *  Sum: '<S132>/Sum'
       */
      rtb_Sign1 = (autocodePlant_B->LwgV1[0] / rtb_TT0gLR -
                   autocodePlant_X->qgw_p_CSTATE[0]) * (rtb_w3 /
        autocodePlant_ConstB.UnitConversion_e);
      autocodePlant_B->w_j5[0] = rtb_Sign1;

      /* UnaryMinus: '<S132>/Unary Minus' */
      autocodePlant_B->UnaryMinus[0] = -rtb_Sign1;

      /* Product: '<S132>/w' incorporates:
       *  Integrator: '<S132>/qgw_p'
       *  Product: '<S132>/wg//V'
       *  Sum: '<S132>/Sum'
       */
      rtb_Sign1 = (autocodePlant_B->LwgV1[1] / rtb_TT0gLR -
                   autocodePlant_X->qgw_p_CSTATE[1]) * (rtb_w3 /
        autocodePlant_ConstB.UnitConversion_e);
      autocodePlant_B->w_j5[1] = rtb_Sign1;

      /* UnaryMinus: '<S132>/Unary Minus' */
      autocodePlant_B->UnaryMinus[1] = -rtb_Sign1;
    }

    /* End of Outputs for SubSystem: '<S120>/Hqgw' */

    /* Saturate: '<S138>/Limit Height h<1000ft' */
    if (rtb_Gain_l > 1000.0) {
      rtb_Product3_ax = 1000.0;
    } else if (rtb_Gain_l < 0.0) {
      rtb_Product3_ax = 0.0;
    } else {
      rtb_Product3_ax = rtb_Gain_l;
    }

    /* Product: '<S138>/sigma_ug, sigma_vg' incorporates:
     *  Fcn: '<S138>/Low Altitude Intensity'
     *  Saturate: '<S138>/Limit Height h<1000ft'
     */
    rtb_Sign1 = 1.0 / rt_powd_snf(0.000823 * rtb_Product3_ax + 0.177, 0.4) *
      autocodePlant_ConstB.sigma_wg;

    /* Fcn: '<S155>/Low Altitude Scale Length' */
    rtb_Sum1_k3 /= rt_powd_snf(0.000823 * rtb_Sum1_k3 + 0.177, 1.2);

    /* Gain: '<S127>/Lv' */
    rtb_Lw_idx_1 = autocodePlant_ConstB.UnitConversion_k;

    /* Outputs for Enabled SubSystem: '<S121>/Hvgw(s)' incorporates:
     *  EnablePort: '<S135>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hvgws_MODE) {
      (void) memset(&(autocodePlant_XDis->vg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S135>/vg_p1' */
      autocodePlant_X->vg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S135>/vgw_p2' */
      autocodePlant_X->vgw_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S135>/vg_p1' */
      autocodePlant_X->vg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S135>/vgw_p2' */
      autocodePlant_X->vgw_p2_CSTATE[1] = 0.0;
      autocodePlant_DW->Hvgws_MODE = true;
    }

    if (autocodePlant_DW->Hvgws_MODE) {
      /* Product: '<S135>/Lvg//V' incorporates:
       *  Gain: '<S127>/Lv'
       */
      rtb_w3 = rtb_Sum1_k3 / rtb_TT0gLR;

      /* Product: '<S135>/w' incorporates:
       *  Gain: '<S135>/(1//pi)'
       *  Integrator: '<S135>/vg_p1'
       *  Product: '<S135>/Lug//V1'
       *  Sqrt: '<S135>/sqrt'
       *  Sum: '<S135>/Sum'
       */
      rtb_Product2_l3 = (sqrt(0.3183098861837907 * rtb_w3) *
                         autocodePlant_B->Product[1] -
                         autocodePlant_X->vg_p1_CSTATE[0]) / rtb_w3;
      autocodePlant_B->w_c[0] = rtb_Product2_l3;

      /* Product: '<S135>/w ' incorporates:
       *  Gain: '<S135>/sqrt(3)'
       *  Integrator: '<S135>/vg_p1'
       *  Integrator: '<S135>/vgw_p2'
       *  Product: '<S135>/Lvg//V '
       *  Sum: '<S135>/Sum1'
       */
      autocodePlant_B->w_j[0] = (rtb_Product2_l3 * rtb_w3 * 1.7320508075688772 +
        (autocodePlant_X->vg_p1_CSTATE[0] - autocodePlant_X->vgw_p2_CSTATE[0])) /
        rtb_w3;

      /* Product: '<S135>/Lvg//V' */
      rtb_w3 = rtb_Lw_idx_1 / rtb_TT0gLR;

      /* Product: '<S135>/w' incorporates:
       *  Gain: '<S135>/(1//pi)'
       *  Integrator: '<S135>/vg_p1'
       *  Product: '<S135>/Lug//V1'
       *  Sqrt: '<S135>/sqrt'
       *  Sum: '<S135>/Sum'
       */
      rtb_Product2_l3 = (sqrt(0.3183098861837907 * rtb_w3) *
                         autocodePlant_B->Product[1] -
                         autocodePlant_X->vg_p1_CSTATE[1]) / rtb_w3;
      autocodePlant_B->w_c[1] = rtb_Product2_l3;

      /* Product: '<S135>/w ' incorporates:
       *  Gain: '<S135>/sqrt(3)'
       *  Integrator: '<S135>/vg_p1'
       *  Integrator: '<S135>/vgw_p2'
       *  Product: '<S135>/Lvg//V '
       *  Sum: '<S135>/Sum1'
       */
      autocodePlant_B->w_j[1] = (rtb_Product2_l3 * rtb_w3 * 1.7320508075688772 +
        (autocodePlant_X->vg_p1_CSTATE[1] - autocodePlant_X->vgw_p2_CSTATE[1])) /
        rtb_w3;

      /* Product: '<S135>/w 1' incorporates:
       *  Integrator: '<S135>/vgw_p2'
       */
      autocodePlant_B->w1[0] = rtb_Sign1 * autocodePlant_X->vgw_p2_CSTATE[0];
      autocodePlant_B->w1[1] = rtb_a * autocodePlant_X->vgw_p2_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S121>/Hvgw(s)' */

    /* Outputs for Enabled SubSystem: '<S120>/Hrgw' incorporates:
     *  EnablePort: '<S133>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hrgw_MODE) {
      (void) memset(&(autocodePlant_XDis->rgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S133>/rgw_p' */
      autocodePlant_X->rgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->rgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hrgw_MODE = true;
    }

    if (autocodePlant_DW->Hrgw_MODE) {
      /* Gain: '<S133>/pi//3' */
      rtb_w3 = 1.0471975511965976 * rtb_TT0gLR;

      /* Product: '<S133>/w' incorporates:
       *  Integrator: '<S133>/rgw_p'
       *  Product: '<S133>/vg//V'
       *  Sum: '<S133>/Sum'
       */
      autocodePlant_B->w_g[0] = (autocodePlant_B->w1[0] / rtb_TT0gLR -
        autocodePlant_X->rgw_p_CSTATE[0]) * (rtb_w3 /
        autocodePlant_ConstB.UnitConversion_e);
      autocodePlant_B->w_g[1] = (autocodePlant_B->w1[1] / rtb_TT0gLR -
        autocodePlant_X->rgw_p_CSTATE[1]) * (rtb_w3 /
        autocodePlant_ConstB.UnitConversion_e);
    }

    /* End of Outputs for SubSystem: '<S120>/Hrgw' */

    /* Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix' incorporates:
     *  DotProduct: '<S282>/Dot Product'
     *  Sqrt: '<S182>/sqrt'
     *  Sum: '<S183>/Sum'
     */
    rtb_w3 = ((rtb_Switch_a_idx_0 * rtb_Switch_a_idx_0 + rtb_Switch_a_idx_1 *
               rtb_Switch_a_idx_1) + rtb_Switch_a_idx_2 * rtb_Switch_a_idx_2) +
      rtb_Switch_a_idx_3 * rtb_Switch_a_idx_3;
    rtb_FlatEarthtoLLA_o1_idx_1 = sqrt(rtb_w3);
    rtb_Product2_l3 = 1.0 / rtb_FlatEarthtoLLA_o1_idx_1;
    rtb_Switch_d_idx_1 = rtb_Product2_l3 * rtb_Switch_a_idx_1;
    rtb_Switch_d_idx_2 = rtb_Product2_l3 * rtb_Switch_a_idx_2;
    rtb_Sum_d0 = rtb_Product2_l3 * rtb_Switch_a_idx_3;
    rtb_Product2_l3 *= rtb_Switch_a_idx_0;
    rtb_Product_n = rtb_Product2_l3 * rtb_Product2_l3;
    rtb_Sign1_e = rtb_Switch_d_idx_1 * rtb_Switch_d_idx_1;
    rtb_Sign1_i = rtb_Switch_d_idx_2 * rtb_Switch_d_idx_2;
    rtb_Gain_oa = rtb_Sum_d0 * rtb_Sum_d0;
    rtb_QuaternionstoDirectionCosin[0] = ((rtb_Product_n + rtb_Sign1_e) -
      rtb_Sign1_i) - rtb_Gain_oa;
    rtb_UnaryMinus1_k4 = rtb_Switch_d_idx_1 * rtb_Switch_d_idx_2;
    rtb_Product_h5 = rtb_Product2_l3 * rtb_Sum_d0;
    rtb_QuaternionstoDirectionCosin[3] = (rtb_UnaryMinus1_k4 + rtb_Product_h5) *
      2.0;
    rtb_UnaryMinus1_o = rtb_Switch_d_idx_1 * rtb_Sum_d0;
    rtb_Sum_ls = rtb_Product2_l3 * rtb_Switch_d_idx_2;
    rtb_QuaternionstoDirectionCosin[6] = (rtb_UnaryMinus1_o - rtb_Sum_ls) * 2.0;
    rtb_QuaternionstoDirectionCosin[1] = (rtb_UnaryMinus1_k4 - rtb_Product_h5) *
      2.0;
    rtb_Product_n -= rtb_Sign1_e;
    rtb_QuaternionstoDirectionCosin[4] = (rtb_Product_n + rtb_Sign1_i) -
      rtb_Gain_oa;
    rtb_Sign1_e = rtb_Switch_d_idx_2 * rtb_Sum_d0;
    rtb_UnaryMinus1_k4 = rtb_Product2_l3 * rtb_Switch_d_idx_1;
    rtb_QuaternionstoDirectionCosin[7] = (rtb_Sign1_e + rtb_UnaryMinus1_k4) *
      2.0;
    rtb_QuaternionstoDirectionCosin[2] = (rtb_UnaryMinus1_o + rtb_Sum_ls) * 2.0;
    rtb_QuaternionstoDirectionCosin[5] = (rtb_Sign1_e - rtb_UnaryMinus1_k4) *
      2.0;
    rtb_QuaternionstoDirectionCosin[8] = (rtb_Product_n - rtb_Sign1_i) +
      rtb_Gain_oa;

    /* If: '<S125>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    rtPrevAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      if (rtb_Gain_l <= 1000.0) {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = 0;
      } else if (rtb_Gain_l >= 2000.0) {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = 1;
      } else {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = 2;
      }
    }

    if (rtPrevAction != autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&autocodePlant_M->solverInfo,
        true);
    }

    /* End of If: '<S125>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */

    /* Sum: '<S4>/Sum1' */
    rtb_VectorConcatenate_h[0] = rtb_wBdy_rps[0];
    rtb_VectorConcatenate_h[1] = rtb_wBdy_rps[1];
    rtb_VectorConcatenate_h[2] = rtb_wBdy_rps[2];

    /* Product: '<S21>/Element Product' incorporates:
     *  Sum: '<S4>/Sum1'
     */
    rtb_ElementProduct[0] = rtb_wBdy_rps[1] * autocodePlant_ConstB.Subtract1[2];
    rtb_ElementProduct[1] = autocodePlant_ConstB.Subtract1[0] * rtb_wBdy_rps[2];
    rtb_ElementProduct[2] = rtb_wBdy_rps[0] * autocodePlant_ConstB.Subtract1[1];
    rtb_ElementProduct[3] = autocodePlant_ConstB.Subtract1[1] * rtb_wBdy_rps[2];
    rtb_ElementProduct[4] = rtb_wBdy_rps[0] * autocodePlant_ConstB.Subtract1[2];
    rtb_ElementProduct[5] = autocodePlant_ConstB.Subtract1[0] * rtb_wBdy_rps[1];

    /* UnitConversion: '<S159>/Unit Conversion' incorporates:
     *  UnaryMinus: '<S101>/Unary Minus'
     */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    rtb_Sign1_i = 3.280839895013123 * -rtb_Sum1_ju[2];

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
    rtb_Product2_l3 = 0.0;
    rtb_Sign1_i = 0.0;
    rtb_Product_n = 0.0;

    /* Product: '<S118>/Transform from Inertial to Body axes' */
    rtb_UnaryMinus1_k4 = 0.0;
    rtb_Gain_oa = 0.0;
    rtb_Sign1_e = 0.0;
    for (i = 0; i < 3; i++) {
      /* Product: '<S101>/Matrix Multiply' incorporates:
       *  Constant: '<S101>/Constant'
       *  Product: '<S118>/Transform from Inertial to Body axes'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       */
      rtb_Product3_ax = rtCP__Constant_Value_dx[i];
      rtb_Lw_idx_1 = rtb_QuaternionstoDirectionCosin[3 * i];
      rtb_Product2_l3 += rtb_Lw_idx_1 * rtb_Product3_ax;
      rtb_Switch_d_idx_1 = rtb_QuaternionstoDirectionCosin[3 * i + 1];
      rtb_Sign1_i += rtb_Switch_d_idx_1 * rtb_Product3_ax;
      rtb_Switch_d_idx_2 = rtb_QuaternionstoDirectionCosin[3 * i + 2];
      rtb_Product_n += rtb_Switch_d_idx_2 * rtb_Product3_ax;

      /* Product: '<S118>/Transform from Inertial to Body axes' incorporates:
       *  Product: '<S118>/Product1'
       */
      rtb_Product3_ax = rtb_Product_h5 *
        autocodePlant_ConstB.Windspeedatreferenceheight[i];
      rtb_UnaryMinus1_k4 += rtb_Lw_idx_1 * rtb_Product3_ax;
      rtb_Gain_oa += rtb_Switch_d_idx_1 * rtb_Product3_ax;
      rtb_Sign1_e += rtb_Switch_d_idx_2 * rtb_Product3_ax;
    }

    /* Outputs for Enabled SubSystem: '<S121>/Hugw(s)' incorporates:
     *  EnablePort: '<S134>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hugws_MODE) {
      (void) memset(&(autocodePlant_XDis->ug_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S134>/ug_p' */
      autocodePlant_X->ug_p_CSTATE[0] = 0.0;
      autocodePlant_X->ug_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hugws_MODE = true;
    }

    if (autocodePlant_DW->Hugws_MODE) {
      /* Product: '<S134>/Lug//V' */
      rtb_Sum1_k3 /= rtb_TT0gLR;
      rtb_TT0gLR = autocodePlant_ConstB.UnitConversion_k / rtb_TT0gLR;

      /* Product: '<S134>/w' incorporates:
       *  Gain: '<S134>/(2//pi)'
       *  Integrator: '<S134>/ug_p'
       *  Product: '<S134>/Lug//V1'
       *  Sqrt: '<S134>/sqrt'
       *  Sum: '<S134>/Sum'
       */
      autocodePlant_B->w_d[0] = (sqrt(0.6366197723675814 * rtb_Sum1_k3) *
        autocodePlant_B->Product[0] - autocodePlant_X->ug_p_CSTATE[0]) /
        rtb_Sum1_k3;
      autocodePlant_B->w_d[1] = (sqrt(0.6366197723675814 * rtb_TT0gLR) *
        autocodePlant_B->Product[0] - autocodePlant_X->ug_p_CSTATE[1]) /
        rtb_TT0gLR;

      /* Product: '<S134>/w1' incorporates:
       *  Integrator: '<S134>/ug_p'
       */
      autocodePlant_B->w1_c[0] = autocodePlant_X->ug_p_CSTATE[0] * rtb_Sign1;
      autocodePlant_B->w1_c[1] = autocodePlant_X->ug_p_CSTATE[1] * rtb_a;
    }

    /* End of Outputs for SubSystem: '<S121>/Hugw(s)' */

    /* If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
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
      /* Outputs for IfAction SubSystem: '<S126>/Low altitude  velocities' incorporates:
       *  ActionPort: '<S148>/Action Port'
       */
      /* SignalConversion generated from: '<S153>/Vector Concatenate' */
      rtb_Product_fn[2] = autocodePlant_B->LwgV1[0];

      /* Trigonometry: '<S154>/Trigonometric Function' incorporates:
       *  UnitConversion: '<S119>/Unit Conversion'
       */
      rtb_Sum1_k3 = sin(autocodePlant_ConstB.UnitConversion);
      rtb_a = cos(autocodePlant_ConstB.UnitConversion);

      /* Sum: '<S154>/Sum' incorporates:
       *  Product: '<S154>/Product1'
       *  Product: '<S154>/Product2'
       */
      rtb_Product_fn[0] = autocodePlant_B->w1_c[0] * rtb_a - rtb_Sum1_k3 *
        autocodePlant_B->w1[0];

      /* Sum: '<S154>/Sum1' incorporates:
       *  Product: '<S154>/Product1'
       *  Product: '<S154>/Product2'
       */
      rtb_Product_fn[1] = rtb_Sum1_k3 * autocodePlant_B->w1_c[0] +
        autocodePlant_B->w1[0] * rtb_a;

      /* Product: '<S153>/Product' incorporates:
       *  Concatenate: '<S153>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       *  Reshape: '<S153>/Reshape1'
       */
      rtb_TmpSignalConversionAtProd_0 = 0.0;
      rtb_Product1_hx = 0.0;
      rtb_Sum1_k3 = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_Product3_ax = rtb_Product_fn[i];
        rtb_TmpSignalConversionAtProd_0 += rtb_QuaternionstoDirectionCosin[3 * i]
          * rtb_Product3_ax;
        rtb_Product1_hx += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
          rtb_Product3_ax;
        rtb_Sum1_k3 += rtb_QuaternionstoDirectionCosin[3 * i + 2] *
          rtb_Product3_ax;
      }

      rtb_VectorConcatenate[2] = rtb_Sum1_k3;
      rtb_VectorConcatenate[1] = rtb_Product1_hx;
      rtb_VectorConcatenate[0] = rtb_TmpSignalConversionAtProd_0;

      /* End of Product: '<S153>/Product' */
      /* End of Outputs for SubSystem: '<S126>/Low altitude  velocities' */
      break;

     case 1:
      /* Outputs for IfAction SubSystem: '<S126>/Medium//High  altitude velocities' incorporates:
       *  ActionPort: '<S149>/Action Port'
       */
      /* Gain: '<S149>/Gain' */
      rtb_VectorConcatenate[0] = autocodePlant_B->w1_c[1];
      rtb_VectorConcatenate[1] = autocodePlant_B->w1[1];
      rtb_VectorConcatenate[2] = autocodePlant_B->LwgV1[1];

      /* End of Outputs for SubSystem: '<S126>/Medium//High  altitude velocities' */
      break;

     default:
      /* Outputs for IfAction SubSystem: '<S126>/Interpolate  velocities' incorporates:
       *  ActionPort: '<S147>/Action Port'
       */
      /* Trigonometry: '<S152>/Trigonometric Function' incorporates:
       *  UnitConversion: '<S119>/Unit Conversion'
       */
      rtb_Sum1_k3 = sin(autocodePlant_ConstB.UnitConversion);
      rtb_a = cos(autocodePlant_ConstB.UnitConversion);

      /* Sum: '<S152>/Sum' incorporates:
       *  Product: '<S152>/Product1'
       *  Product: '<S152>/Product2'
       */
      rtb_VectorConcatenate[0] = autocodePlant_B->w1_c[0] * rtb_a - rtb_Sum1_k3 *
        autocodePlant_B->w1[0];

      /* Sum: '<S152>/Sum1' incorporates:
       *  Product: '<S152>/Product1'
       *  Product: '<S152>/Product2'
       */
      rtb_VectorConcatenate[1] = rtb_Sum1_k3 * autocodePlant_B->w1_c[0] +
        autocodePlant_B->w1[0] * rtb_a;

      /* SignalConversion generated from: '<S151>/Vector Concatenate' */
      rtb_VectorConcatenate[2] = autocodePlant_B->LwgV1[0];

      /* Product: '<S151>/Product' incorporates:
       *  Concatenate: '<S151>/Vector Concatenate'
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

      /* Sum: '<S147>/Sum3' incorporates:
       *  Constant: '<S147>/max_height_low'
       *  Product: '<S147>/Product1'
       *  Product: '<S151>/Product'
       *  Sum: '<S147>/Sum1'
       *  Sum: '<S147>/Sum2'
       */
      rtb_VectorConcatenate[0] = (autocodePlant_B->w1_c[1] - rtb_TT0gLR) *
        (rtb_Gain_l - 1000.0) / autocodePlant_ConstB.Sum_p + rtb_TT0gLR;
      rtb_VectorConcatenate[1] = (autocodePlant_B->w1[1] - rtb_Product_h5) *
        (rtb_Gain_l - 1000.0) / autocodePlant_ConstB.Sum_p + rtb_Product_h5;
      rtb_VectorConcatenate[2] = (autocodePlant_B->LwgV1[1] - rtb_Sign1) *
        (rtb_Gain_l - 1000.0) / autocodePlant_ConstB.Sum_p + rtb_Sign1;

      /* End of Outputs for SubSystem: '<S126>/Interpolate  velocities' */
      break;
    }

    /* End of If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */

    /* Saturate: '<S106>/Limit  altitude  to troposhere' incorporates:
     *  Constant: '<S4>/Constant'
     *  Sum: '<S4>/Sum'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    /* Unit Conversion - from: ft/s to: m/s
       Expression: output = (0.3048*input) + (0) */
    if (182.0 - rtb_Sum1_ju[2] > 11000.0) {
      rtb_Product3_ax = 11000.0;
    } else if (182.0 - rtb_Sum1_ju[2] < 0.0) {
      rtb_Product3_ax = 0.0;
    } else {
      rtb_Product3_ax = 182.0 - rtb_Sum1_ju[2];
    }

    /* Sum: '<S106>/Sum1' incorporates:
     *  Constant: '<S106>/Sea Level  Temperature'
     *  Gain: '<S106>/Lapse Rate'
     *  Saturate: '<S106>/Limit  altitude  to troposhere'
     */
    rtb_Sum1_k3 = 288.15 - 0.0065 * rtb_Product3_ax;

    /* Sqrt: '<S106>/a' incorporates:
     *  Gain: '<S106>/gamma*R'
     */
    rtb_a = sqrt(401.87433999999996 * rtb_Sum1_k3);

    /* Sum: '<S101>/Sum' incorporates:
     *  Product: '<S101>/Matrix Multiply'
     *  Product: '<S101>/Product'
     *  Product: '<S101>/Product2'
     *  Product: '<S118>/Transform from Inertial to Body axes'
     *  UnitConversion: '<S117>/Unit Conversion'
     */
    rtb_Product2_l3 = (rtb_UnaryMinus1_k4 * 0.0 + rtb_Product2_l3) + 0.3048 *
      rtb_VectorConcatenate[0] * 0.0;
    rtb_Product_ne[0] = rtb_Product2_l3;

    /* Sum: '<S4>/Sum2' */
    rtb_TmpSignalConversionAtProd_0 = rtb_velBdy_mps[0] - rtb_Product2_l3;
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
     *  Product: '<S101>/Product'
     *  Product: '<S101>/Product2'
     *  Product: '<S118>/Transform from Inertial to Body axes'
     *  UnitConversion: '<S117>/Unit Conversion'
     */
    rtb_Product2_l3 = (rtb_Gain_oa * 0.0 + rtb_Sign1_i) + 0.3048 *
      rtb_VectorConcatenate[1] * 0.0;
    rtb_Product_ne[1] = rtb_Product2_l3;

    /* Sum: '<S4>/Sum2' */
    rtb_TmpSignalConversionAtProd_0 = rtb_velBdy_mps[1] - rtb_Product2_l3;
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
     *  Product: '<S101>/Product'
     *  Product: '<S101>/Product2'
     *  Product: '<S118>/Transform from Inertial to Body axes'
     *  UnitConversion: '<S117>/Unit Conversion'
     */
    rtb_Product2_l3 = (rtb_Sign1_e * 0.0 + rtb_Product_n) + 0.3048 *
      rtb_VectorConcatenate[2] * 0.0;
    rtb_Product_ne[2] = rtb_Product2_l3;

    /* Sum: '<S4>/Sum2' */
    rtb_TmpSignalConversionAtProd_0 = rtb_velBdy_mps[2] - rtb_Product2_l3;
    rtb_VectorConcatenate[2] = rtb_TmpSignalConversionAtProd_0;

    /* Sum: '<S9>/Sum' incorporates:
     *  Sum: '<S21>/Sum'
     */
    rtb_TT0gLR = (rtb_ElementProduct[2] - rtb_ElementProduct[5]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product_fn[2] = rtb_TT0gLR;

    /* Product: '<S9>/Product8' */
    rtb_Product2_l3 = rtb_TT0gLR * autocodePlant_ConstB.Sum2_i[2];

    /* DotProduct: '<S9>/Dot Product1' */
    rtb_Product_n = (rtb_UnaryMinus1_k4 * rtb_UnaryMinus1_k4 + rtb_Gain_l *
                     rtb_Gain_l) + rtb_Product2_l3 * rtb_Product2_l3;

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
    rtb_Sum_ls = fmax(1.0E-6, rtb_a);

    /* Product: '<S9>/Divide1' incorporates:
     *  DotProduct: '<S9>/Dot Product4'
     *  MinMax: '<S18>/Max'
     *  Product: '<S18>/Product'
     *  Sqrt: '<S9>/Sqrt1'
     *  Switch: '<S18>/Switch'
     */
    rtb_Sign1_i = sqrt(rtb_Gain_oa) / ((real_T)i * rtb_Sum_ls);

    /* Switch: '<S20>/Switch' incorporates:
     *  Constant: '<S20>/Constant4'
     *  Constant: '<S20>/Constant5'
     *  DotProduct: '<S9>/Dot Product1'
     */
    if (rtb_Product_n >= 0.0) {
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
               autocodePlant_ConstB.Sum_c * rtb_Product2_l3) / sqrt((real_T)i *
      fmax(1.0E-6, rtb_Product_n));

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
    rtb_Product2_l3 = 0.00347041471455839 * rtb_Sum1_k3;

    /* Math: '<S106>/(T//T0)^(g//LR) ' incorporates:
     *  Constant: '<S106>/Constant'
     */
    rtb_TT0gLR = rt_powd_snf(rtb_Product2_l3, 5.255875601466713);

    /* Product: '<S106>/Product' */
    rtb_Product_n = rtb_TT0gLR / rtb_Product2_l3;

    /* Saturate: '<S106>/Limit  altitude  to Stratosphere' incorporates:
     *  Constant: '<S106>/Altitude of Troposphere'
     *  Constant: '<S4>/Constant'
     *  Sum: '<S106>/Sum'
     *  Sum: '<S4>/Sum'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    if (11000.0 - (182.0 - rtb_Sum1_ju[2]) > 0.0) {
      rtb_Product3_ax = 0.0;
    } else if (11000.0 - (182.0 - rtb_Sum1_ju[2]) < -9000.0) {
      rtb_Product3_ax = -9000.0;
    } else {
      rtb_Product3_ax = 11000.0 - (182.0 - rtb_Sum1_ju[2]);
    }

    /* Math: '<S106>/Stratosphere Model' incorporates:
     *  Gain: '<S106>/g//R'
     *  Product: '<S106>/Product1'
     *  Saturate: '<S106>/Limit  altitude  to Stratosphere'
     *
     * About '<S106>/Stratosphere Model':
     *  Operator: exp
     */
    rtb_Product2_l3 = exp(1.0 / rtb_Sum1_k3 * (0.03416319140953364 *
      rtb_Product3_ax));

    /* Product: '<S106>/Product3' incorporates:
     *  Gain: '<S106>/rho0'
     */
    rtb_Product_n = 1.225 * rtb_Product_n * rtb_Product2_l3;

    /* Product: '<S9>/Product' incorporates:
     *  Constant: '<S9>/Constant1'
     *  Product: '<S10>/Product'
     *  Product: '<S11>/Product'
     *  Product: '<S12>/Product'
     *  Product: '<S8>/Product'
     */
    rtb_UnaryMinus_a = 0.5 * rtb_Product_n;
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
    rtb_Sum1_a1[0] = rtb_Sign1_i * autocodePlant_ConstB.Sum_f * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_b;
    rtb_Sum1_a1[1] = rtb_Sign1_i * autocodePlant_ConstB.Sum_i * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_l;
    rtb_Sum1_a1[2] = rtb_Sign1_i * autocodePlant_ConstB.Sum_e * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_c;

    /* Sum: '<S22>/Sum' incorporates:
     *  Product: '<S22>/Element Product'
     */
    rtb_Sum_hp[0] = autocodePlant_ConstB.Subtract1[1] * rtb_Sum1_a1[2] -
      rtb_Sum1_a1[1] * autocodePlant_ConstB.Subtract1[2];
    rtb_Sum_hp[1] = rtb_Sum1_a1[0] * autocodePlant_ConstB.Subtract1[2] -
      autocodePlant_ConstB.Subtract1[0] * rtb_Sum1_a1[2];
    rtb_Sum_hp[2] = autocodePlant_ConstB.Subtract1[0] * rtb_Sum1_a1[1] -
      rtb_Sum1_a1[0] * autocodePlant_ConstB.Subtract1[1];

    /* Sum: '<S10>/Sum' incorporates:
     *  Product: '<S41>/Element Product'
     *  Sum: '<S41>/Sum'
     *  Sum: '<S4>/Sum1'
     */
    rtb_Sign1_e = (rtb_wBdy_rps[1] * autocodePlant_ConstB.Subtract1_m[2] -
                   autocodePlant_ConstB.Subtract1_m[1] * rtb_wBdy_rps[2]) +
      rtb_VectorConcatenate[0];
    rtb_Sum_dj[0] = rtb_Sign1_e;

    /* Product: '<S10>/Product8' */
    rtb_Sum_d0 = rtb_Sign1_e * autocodePlant_ConstB.Sum2_l[0];

    /* Sum: '<S10>/Sum' incorporates:
     *  Product: '<S41>/Element Product'
     *  Sum: '<S41>/Sum'
     *  Sum: '<S4>/Sum1'
     */
    rtb_Sign1_i = (autocodePlant_ConstB.Subtract1_m[0] * rtb_wBdy_rps[2] -
                   rtb_wBdy_rps[0] * autocodePlant_ConstB.Subtract1_m[2]) +
      rtb_VectorConcatenate[1];
    rtb_Sum_dj[1] = rtb_Sign1_i;

    /* Product: '<S10>/Product8' */
    rtb_Gain_oa = rtb_Sign1_i * autocodePlant_ConstB.Sum2_l[1];

    /* Sum: '<S10>/Sum' incorporates:
     *  Product: '<S41>/Element Product'
     *  Sum: '<S41>/Sum'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S4>/Sum2'
     */
    rtb_UnaryMinus1_o = (rtb_wBdy_rps[0] * autocodePlant_ConstB.Subtract1_m[1] -
                         autocodePlant_ConstB.Subtract1_m[0] * rtb_wBdy_rps[1])
      + rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_dj[2] = rtb_UnaryMinus1_o;

    /* Product: '<S10>/Product8' */
    rtb_Switch_d_idx_1 = rtb_UnaryMinus1_o * autocodePlant_ConstB.Sum2_l[2];

    /* DotProduct: '<S10>/Dot Product1' */
    rtb_Switch_d_idx_2 = (rtb_Sum_d0 * rtb_Sum_d0 + rtb_Gain_oa * rtb_Gain_oa) +
      rtb_Switch_d_idx_1 * rtb_Switch_d_idx_1;

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
    rtb_Product_h5 = sqrt(rtb_UnaryMinus1_k4) / ((real_T)i * rtb_Sum_ls);

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
    rtb_Sum = ((autocodePlant_ConstB.Sum_k3 * rtb_Sum_d0 +
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
    rtb_Sum_d0 = (autocodePlant_ConstB.Sum_m * rtb_Sign1_e +
                  autocodePlant_ConstB.Sum_b1 * rtb_Sign1_i) +
      autocodePlant_ConstB.Sum_k * rtb_UnaryMinus1_o;

    /* Switch: '<S39>/Switch' incorporates:
     *  Constant: '<S39>/Constant4'
     *  Constant: '<S39>/Constant5'
     *  DotProduct: '<S10>/Dot Product2'
     */
    if (rtb_Sum_d0 >= 0.0) {
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
    rtb_Switch_d_idx_1 = (real_T)i * fmax(1.0E-6, fabs(rtb_Sum_d0));

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
    rtb_Sum1_hn[0] = rtb_UnaryMinus1_k4 * autocodePlant_ConstB.Sum_m *
      rtb_Sign1_e + rtb_Sign1_i * autocodePlant_ConstB.Sum_k3;
    rtb_Sum1_hn[1] = rtb_UnaryMinus1_k4 * autocodePlant_ConstB.Sum_b1 *
      rtb_Sign1_e + rtb_Sign1_i * autocodePlant_ConstB.Sum_cv;
    rtb_Sum1_hn[2] = rtb_UnaryMinus1_k4 * autocodePlant_ConstB.Sum_k *
      rtb_Sign1_e + rtb_Sign1_i * autocodePlant_ConstB.Sum_b1v;

    /* Sum: '<S42>/Sum' incorporates:
     *  Product: '<S42>/Element Product'
     */
    rtb_Sum_k[0] = autocodePlant_ConstB.Subtract1_m[1] * rtb_Sum1_hn[2] -
      rtb_Sum1_hn[1] * autocodePlant_ConstB.Subtract1_m[2];
    rtb_Sum_k[1] = rtb_Sum1_hn[0] * autocodePlant_ConstB.Subtract1_m[2] -
      autocodePlant_ConstB.Subtract1_m[0] * rtb_Sum1_hn[2];
    rtb_Sum_k[2] = autocodePlant_ConstB.Subtract1_m[0] * rtb_Sum1_hn[1] -
      rtb_Sum1_hn[0] * autocodePlant_ConstB.Subtract1_m[1];

    /* Sum: '<S11>/Sum' incorporates:
     *  Product: '<S61>/Element Product'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S61>/Sum'
     */
    rtb_Sign1_i = (rtb_wBdy_rps[1] * autocodePlant_ConstB.Subtract1_k[2] -
                   autocodePlant_ConstB.Subtract1_k[1] * rtb_wBdy_rps[2]) +
      rtb_VectorConcatenate[0];
    rtb_Sum_el[0] = rtb_Sign1_i;

    /* Product: '<S11>/Product8' */
    rtb_Switch_d_idx_1 = rtb_Sign1_i * autocodePlant_ConstB.Sum2_iw[0];

    /* Sum: '<S11>/Sum' incorporates:
     *  Product: '<S61>/Element Product'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S61>/Sum'
     */
    rtb_Product_h5 = (autocodePlant_ConstB.Subtract1_k[0] * rtb_wBdy_rps[2] -
                      rtb_wBdy_rps[0] * autocodePlant_ConstB.Subtract1_k[2]) +
      rtb_VectorConcatenate[1];
    rtb_Sum_el[1] = rtb_Product_h5;

    /* Product: '<S11>/Product8' */
    rtb_UnaryMinus1_k4 = rtb_Product_h5 * autocodePlant_ConstB.Sum2_iw[1];

    /* Sum: '<S11>/Sum' incorporates:
     *  Product: '<S61>/Element Product'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S4>/Sum2'
     *  Sum: '<S61>/Sum'
     */
    rtb_Sum_d0 = (rtb_wBdy_rps[0] * autocodePlant_ConstB.Subtract1_k[1] -
                  autocodePlant_ConstB.Subtract1_k[0] * rtb_wBdy_rps[1]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_el[2] = rtb_Sum_d0;

    /* Product: '<S11>/Product8' */
    rtb_Switch_d_idx_2 = rtb_Sum_d0 * autocodePlant_ConstB.Sum2_iw[2];

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
                         rtb_Product_h5) + rtb_Sum_d0 * rtb_Sum_d0;

    /* Product: '<S11>/Divide1' incorporates:
     *  DotProduct: '<S11>/Dot Product4'
     *  Product: '<S58>/Product'
     *  Sqrt: '<S11>/Sqrt1'
     *  Switch: '<S58>/Switch'
     */
    rtb_Product1_hx = sqrt(rtb_UnaryMinus1_o) / ((real_T)i * rtb_Sum_ls);

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
      autocodePlant_ConstB.Sum_g * rtb_Sum_d0;

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
     *  Product: '<S191>/Product1'
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
     *  Product: '<S191>/Product1'
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
    rtb_Sum1_b[0] = rtb_UnaryMinus1_o * autocodePlant_ConstB.Sum_o * rtb_Sign1_i
      + rtb_Product_h5 * autocodePlant_ConstB.Sum_a;
    rtb_Sum1_b[1] = rtb_UnaryMinus1_o * autocodePlant_ConstB.Sum_er *
      rtb_Sign1_i + rtb_Product_h5 * autocodePlant_ConstB.Sum_ia;
    rtb_Sum1_b[2] = rtb_UnaryMinus1_o * autocodePlant_ConstB.Sum_g * rtb_Sign1_i
      + rtb_Product_h5 * autocodePlant_ConstB.Sum_bt;

    /* Sum: '<S62>/Sum' incorporates:
     *  Product: '<S62>/Element Product'
     */
    rtb_Sum_n3[0] = autocodePlant_ConstB.Subtract1_k[1] * rtb_Sum1_b[2] -
      rtb_Sum1_b[1] * autocodePlant_ConstB.Subtract1_k[2];
    rtb_Sum_n3[1] = rtb_Sum1_b[0] * autocodePlant_ConstB.Subtract1_k[2] -
      autocodePlant_ConstB.Subtract1_k[0] * rtb_Sum1_b[2];
    rtb_Sum_n3[2] = autocodePlant_ConstB.Subtract1_k[0] * rtb_Sum1_b[1] -
      rtb_Sum1_b[0] * autocodePlant_ConstB.Subtract1_k[1];

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S81>/Element Product'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S81>/Sum'
     */
    rtb_Product_h5 = (rtb_wBdy_rps[1] * autocodePlant_ConstB.Subtract1_j[2] -
                      autocodePlant_ConstB.Subtract1_j[1] * rtb_wBdy_rps[2]) +
      rtb_VectorConcatenate[0];
    rtb_Sum_aw[0] = rtb_Product_h5;

    /* Product: '<S12>/Product8' */
    rtb_Product1_hx = rtb_Product_h5 * autocodePlant_ConstB.Sum2_ayz[0];

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S81>/Element Product'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S81>/Sum'
     */
    rtb_Switch_d_idx_1 = (autocodePlant_ConstB.Subtract1_j[0] * rtb_wBdy_rps[2]
                          - rtb_wBdy_rps[0] * autocodePlant_ConstB.Subtract1_j[2])
      + rtb_VectorConcatenate[1];
    rtb_Sum_aw[1] = rtb_Switch_d_idx_1;

    /* Product: '<S12>/Product8' */
    rtb_UnaryMinus1_o = rtb_Switch_d_idx_1 * autocodePlant_ConstB.Sum2_ayz[1];

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S81>/Element Product'
     *  Sum: '<S4>/Sum1'
     *  Sum: '<S4>/Sum2'
     *  Sum: '<S81>/Sum'
     */
    rtb_Switch_d_idx_2 = (rtb_wBdy_rps[0] * autocodePlant_ConstB.Subtract1_j[1]
                          - autocodePlant_ConstB.Subtract1_j[0] * rtb_wBdy_rps[1])
      + rtb_TmpSignalConversionAtProd_0;
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
    rtb_Sum_d0 = (rtb_Product_h5 * rtb_Product_h5 + rtb_Switch_d_idx_1 *
                  rtb_Switch_d_idx_1) + rtb_Switch_d_idx_2 * rtb_Switch_d_idx_2;

    /* Product: '<S12>/Divide1' incorporates:
     *  DotProduct: '<S12>/Dot Product4'
     *  Product: '<S78>/Product'
     *  Sqrt: '<S12>/Sqrt1'
     *  Switch: '<S78>/Switch'
     */
    rtb_Product3_ax = sqrt(rtb_Sum_d0) / ((real_T)i * rtb_Sum_ls);

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
     *  Product: '<S12>/Product7'
     *  Product: '<S191>/Product3'
     *  Product: '<S287>/Product8'
     */
    bpIndices_5[0U] = plook_binx(rtb_Product3_ax, rtCP__CALookupTable_bp01Data_k,
      9U, &rtb_Switch_d_idx_1);
    rtb_Product6_kk[0U] = rtb_Switch_d_idx_1;
    bpIndices_5[1U] = plook_binx(rtb_UnaryMinus1_o,
      rtCP__CALookupTable_bp02Data_f, 2U, &rtb_Switch_d_idx_1);
    rtb_Product6_kk[1U] = rtb_Switch_d_idx_1;
    bpIndices_5[2U] = plook_binx(autocodePlant_B->Backlash[3] * rtb_Product_h5,
      rtCP__CALookupTable_bp03Data_b, 4U, &rtb_Switch_d_idx_1);
    rtb_Product6_kk[2U] = rtb_Switch_d_idx_1;
    rtb_Product1_hx = intrp3d_l_pw(bpIndices_5, rtb_Product6_kk,
      rtCP__CALookupTable_tableData_l, rtCP__CALookupTable_dimSizes_a);

    /* Product: '<S12>/Product' */
    rtb_Sum_d0 *= rtb_UnaryMinus_a;

    /* UnaryMinus: '<S12>/Unary Minus' incorporates:
     *  Constant: '<S12>/   '
     *  Product: '<S12>/Product1'
     */
    rtb_Switch_d_idx_2 = -(rtb_Product1_hx * rtb_Sum_d0 * 0.018);

    /* Lookup_n-D: '<S12>/CN Lookup Table' incorporates:
     *  Product: '<S12>/Product5'
     *  Product: '<S191>/Product3'
     *  Product: '<S287>/Product8'
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
    rtb_Sum_d0 = -(rtb_Product3_ax * rtb_Sum_d0 * 0.018);

    /* Sum: '<S12>/Sum1' incorporates:
     *  Product: '<S12>/Product3'
     *  Product: '<S12>/Product4'
     *  SignalConversion generated from: '<S12>/Dot Product2'
     */
    rtb_Sum1_o5[0] = rtb_Sum_d0 * autocodePlant_ConstB.Sum_d * rtb_Product_h5 +
      rtb_Switch_d_idx_2 * autocodePlant_ConstB.Sum_dx;
    rtb_Sum1_o5[1] = rtb_Sum_d0 * autocodePlant_ConstB.Sum_b4 * rtb_Product_h5 +
      rtb_Switch_d_idx_2 * autocodePlant_ConstB.Sum_o3;
    rtb_Sum1_o5[2] = rtb_Sum_d0 * autocodePlant_ConstB.Sum_ln * rtb_Product_h5 +
      rtb_Switch_d_idx_2 * autocodePlant_ConstB.Sum_j;

    /* Sum: '<S82>/Sum' incorporates:
     *  Product: '<S82>/Element Product'
     */
    rtb_Sum_mu[0] = autocodePlant_ConstB.Subtract1_j[1] * rtb_Sum1_o5[2] -
      rtb_Sum1_o5[1] * autocodePlant_ConstB.Subtract1_j[2];
    rtb_Sum_mu[1] = rtb_Sum1_o5[0] * autocodePlant_ConstB.Subtract1_j[2] -
      autocodePlant_ConstB.Subtract1_j[0] * rtb_Sum1_o5[2];
    rtb_Sum_mu[2] = autocodePlant_ConstB.Subtract1_j[0] * rtb_Sum1_o5[1] -
      rtb_Sum1_o5[0] * autocodePlant_ConstB.Subtract1_j[1];

    /* DotProduct: '<S8>/Dot Product1' incorporates:
     *  DotProduct: '<S8>/Dot Product4'
     *  Math: '<S16>/Math Function'
     *  Sum: '<S4>/Sum2'
     */
    rtb_Sum1_n = rtb_VectorConcatenate[1] * rtb_VectorConcatenate[1];
    rtb_VectorConcatenate_tmp = rtb_TmpSignalConversionAtProd_0 *
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product1_hx = (rtb_VectorConcatenate[0] * rtb_VectorConcatenate[0] +
                       rtb_Sum1_n) + rtb_VectorConcatenate_tmp;

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
    rtb_Sum_d0 = sqrt(rtb_Product1_hx) / ((real_T)i * rtb_Sum_ls);

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
    rtb_Sum_ls = 57.29577951308232 * acos(rtb_Sum);

    /* Sum: '<S8>/Sum' incorporates:
     *  Constant: '<S3>/Constant'
     *  Lookup_n-D: '<S8>/CP Lookup Table'
     *  Sum: '<S286>/Sum'
     *  Sum: '<S288>/Sum'
     */
    rtb_Sum = 1.8117856235712473 - look2_binlcpw(rtb_Sum_d0, rtb_Sum_ls,
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
    rtb_Product3_ax = rtb_Sum * 0.0;

    /* Product: '<S8>/Product' incorporates:
     *  DotProduct: '<S8>/Dot Product3'
     */
    rtb_Product1_hx *= rtb_UnaryMinus_a;

    /* UnaryMinus: '<S8>/Unary Minus' incorporates:
     *  Constant: '<S8>/   '
     *  Lookup_n-D: '<S8>/CA Lookup Table'
     *  Product: '<S8>/Product1'
     *  Sum: '<S286>/Sum'
     *  Sum: '<S288>/Sum'
     */
    rtb_UnaryMinus_a = -(look2_binlxpw(rtb_Sum_d0, rtb_Sum_ls,
      rtCP__CALookupTable_bp01Data_j, rtCP__CALookupTable_bp02Data_b,
      rtCP__CALookupTable_tableData_e, rtCP__CALookupTable_maxIndex_j, 10U) *
                         rtb_Product1_hx * 0.018);

    /* UnaryMinus: '<S8>/Unary Minus1' incorporates:
     *  Constant: '<S8>/ '
     *  Lookup_n-D: '<S8>/CN Lookup Table'
     *  Product: '<S8>/Product2'
     *  Sum: '<S286>/Sum'
     *  Sum: '<S288>/Sum'
     */
    rtb_Product1_hx = -(look2_binlxpw(rtb_Sum_d0, rtb_Sum_ls,
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
    rtb_Sum_d0 = sqrt((rtb_Switch_d_idx_0 * rtb_Switch_d_idx_0 + rtb_Sum1_n) +
                      rtb_VectorConcatenate_tmp);

    /* Switch: '<S16>/Switch' incorporates:
     *  Constant: '<S16>/Constant'
     *  DotProduct: '<S8>/Dot Product3'
     *  Product: '<S16>/Product'
     *  Product: '<S8>/Product6'
     *  Sum: '<S4>/Sum2'
     */
    if (rtb_Sum_d0 > 1.0E-6) {
      rtb_Switch_d_idx_1 = rtb_VectorConcatenate[1];
      rtb_Switch_d_idx_2 = rtb_TmpSignalConversionAtProd_0;
    } else {
      rtb_Switch_d_idx_0 *= 0.0;
      rtb_Sum_d0 = 1.0;
    }

    /* Sum: '<S8>/Sum1' incorporates:
     *  Product: '<S16>/Divide'
     *  Product: '<S8>/Product3'
     *  Product: '<S8>/Product4'
     */
    rtb_Product6_kk[0] = rtb_Switch_d_idx_0 / rtb_Sum_d0 * rtb_Product1_hx +
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
    rtb_Product6_kk[1] = rtb_Switch_d_idx_1 / rtb_Sum_d0 * rtb_Product1_hx +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product6_kk[2] = rtb_Switch_d_idx_2 / rtb_Sum_d0 * rtb_Product1_hx +
      rtb_TmpSignalConversionAtProd_0;

    /* Product: '<S15>/Element Product' incorporates:
     *  Product: '<S8>/Product5'
     */
    rtb_TmpSignalConversionAtProd_0 = rtb_Product6_kk[0] * rtb_Product3_ax;

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_a = rtb_Product3_ax * rtb_Product6_kk[2] - rtb_Product6_kk[1]
      * rtb_Product3_ax;
    rtb_finMomentArm_m[0] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[0] = (((rtb_Sum_hp[0] + rtb_Sum_k[0]) + rtb_Sum_n3[0]) + rtb_Sum_mu
                  [0]) + rtb_UnaryMinus_a;
    rtb_Add[3] = (((rtb_Sum1_a1[0] + rtb_Sum1_hn[0]) + rtb_Sum1_b[0]) +
                  rtb_Sum1_o5[0]) + rtb_Product6_kk[0];

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_a = rtb_TmpSignalConversionAtProd_0 - rtb_Sum *
      rtb_Product6_kk[2];
    rtb_finMomentArm_m[1] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[1] = (((rtb_Sum_hp[1] + rtb_Sum_k[1]) + rtb_Sum_n3[1]) + rtb_Sum_mu
                  [1]) + rtb_UnaryMinus_a;
    rtb_Add[4] = (((rtb_Sum1_a1[1] + rtb_Sum1_hn[1]) + rtb_Sum1_b[1]) +
                  rtb_Sum1_o5[1]) + rtb_Product6_kk[1];

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_a = rtb_Sum * rtb_Product6_kk[1] -
      rtb_TmpSignalConversionAtProd_0;
    rtb_finMomentArm_m[2] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[2] = (((rtb_Sum_hp[2] + rtb_Sum_k[2]) + rtb_Sum_n3[2]) + rtb_Sum_mu
                  [2]) + rtb_UnaryMinus_a;
    rtb_Add[5] = (((rtb_Sum1_a1[2] + rtb_Sum1_hn[2]) + rtb_Sum1_b[2]) +
                  rtb_Sum1_o5[2]) + rtb_Product6_kk[2];

    /* Sum: '<S5>/Sum' */
    rtb_TmpSignalConversionAtProd_0 = (autocodePlant_B->Delay +
      rtb_gravityForceBdy_N[0]) + rtb_Add[3];

    /* Logic: '<S162>/Logical Operator' */
    rtb_max_relop_c = !rtb_Compare_n;

    /* Sum: '<S162>/Sum' incorporates:
     *  Constant: '<S162>/Constant'
     *  Constant: '<S6>/Constant2'
     *  MinMax: '<S162>/Max1'
     *  Product: '<S162>/Product1'
     *  Product: '<S162>/Product2'
     *  Sum: '<S5>/Sum'
     */
    autocodePlant_B->Sum[0] = fmax((real_T)rtb_Compare_n *
      rtb_TmpSignalConversionAtProd_0, 0.0) + rtb_TmpSignalConversionAtProd_0 *
      (real_T)rtb_max_relop_c;
    autocodePlant_B->Sum[1] = (rtb_gravityForceBdy_N[1] + rtb_Add[4]) * (real_T)
      rtb_max_relop_c;
    autocodePlant_B->Sum[2] = (rtb_gravityForceBdy_N[2] + rtb_Add[5]) * (real_T)
      rtb_max_relop_c;

    /* Product: '<S160>/Divide' incorporates:
     *  Constant: '<S5>/Constant'
     *  Sum: '<S164>/Sum1'
     */
    rtb_MathFunction[0] = (autocodePlant_B->Sum[0] + autocodePlant_ConstB.Switch)
      / 17.5;
    rtb_MathFunction[1] = (autocodePlant_B->Sum[1] + autocodePlant_ConstB.Switch)
      / 17.5;
    rtb_MathFunction[2] = (autocodePlant_B->Sum[2] + autocodePlant_ConstB.Switch)
      / 17.5;

    /* Product: '<S178>/Product2' incorporates:
     *  Product: '<S191>/Product2'
     */
    rtb_Lw_idx_1 = rtb_Switch_a_idx_2 / rtb_FlatEarthtoLLA_o1_idx_1;

    /* Product: '<S178>/Product3' */
    rtb_Product3_ax = rtb_Switch_a_idx_3 / rtb_FlatEarthtoLLA_o1_idx_1;

    /* Product: '<S178>/Product1' incorporates:
     *  Product: '<S191>/Product1'
     */
    rtb_Switch_d_idx_0 = rtb_Switch_a_idx_1 / rtb_FlatEarthtoLLA_o1_idx_1;

    /* Product: '<S178>/Product' incorporates:
     *  Product: '<S191>/Product'
     */
    rtb_FlatEarthtoLLA_o1_idx_1 = rtb_Switch_a_idx_0 /
      rtb_FlatEarthtoLLA_o1_idx_1;

    /* Product: '<S179>/Product7' incorporates:
     *  Product: '<S180>/Product7'
     */
    rtb_Switch_d_idx_1 = rtb_Product3_ax * rtb_Product3_ax;

    /* Product: '<S179>/Product' incorporates:
     *  Product: '<S178>/Product1'
     *  Product: '<S178>/Product2'
     *  Product: '<S180>/Product'
     */
    rtb_Switch_d_idx_2 = rtb_Switch_d_idx_0 * rtb_Lw_idx_1;

    /* Product: '<S179>/Product1' incorporates:
     *  Product: '<S178>/Product'
     *  Product: '<S180>/Product1'
     */
    rtb_Product1_hx = rtb_FlatEarthtoLLA_o1_idx_1 * rtb_Product3_ax;

    /* Product: '<S179>/Product3' incorporates:
     *  Product: '<S178>/Product1'
     *  Product: '<S181>/Product'
     */
    rtb_TmpSignalConversionAtProd_0 = rtb_Switch_d_idx_0 * rtb_Product3_ax;

    /* Product: '<S179>/Product2' incorporates:
     *  Product: '<S178>/Product'
     *  Product: '<S178>/Product2'
     *  Product: '<S181>/Product1'
     */
    rtb_UnaryMinus_a = rtb_FlatEarthtoLLA_o1_idx_1 * rtb_Lw_idx_1;

    /* Product: '<S179>/Product6' incorporates:
     *  Product: '<S178>/Product2'
     *  Product: '<S181>/Product7'
     */
    rtb_Sum_d0 = rtb_Lw_idx_1 * rtb_Lw_idx_1;

    /* Gain: '<S179>/Gain2' incorporates:
     *  Constant: '<S179>/Constant'
     *  Gain: '<S192>/Gain2'
     *  Product: '<S179>/Product6'
     *  Product: '<S179>/Product7'
     *  Sum: '<S179>/Sum3'
     *  Sum: '<S192>/Sum'
     */
    rtb_Sum = ((0.5 - rtb_Sum_d0) - rtb_Switch_d_idx_1) * 2.0;

    /* Gain: '<S179>/Gain' incorporates:
     *  Gain: '<S192>/Gain'
     *  Product: '<S179>/Product'
     *  Product: '<S179>/Product1'
     *  Sum: '<S179>/Sum1'
     *  Sum: '<S192>/Sum'
     */
    rtb_Sum1_n = (rtb_Switch_d_idx_2 + rtb_Product1_hx) * 2.0;

    /* Gain: '<S179>/Gain1' incorporates:
     *  Gain: '<S192>/Gain1'
     *  Product: '<S179>/Product2'
     *  Product: '<S179>/Product3'
     *  Sum: '<S179>/Sum2'
     *  Sum: '<S192>/Sum'
     */
    rtb_VectorConcatenate_tmp = (rtb_TmpSignalConversionAtProd_0 -
      rtb_UnaryMinus_a) * 2.0;

    /* Sum: '<S170>/fBdy_mps2' incorporates:
     *  Constant: '<S170>/gNed_mps2'
     *  Gain: '<S179>/Gain'
     *  Gain: '<S179>/Gain1'
     *  Gain: '<S179>/Gain2'
     *  Product: '<S179>/Product4'
     *  Product: '<S179>/Product5'
     *  Product: '<S179>/Product8'
     *  Sum: '<S179>/Sum'
     */
    autocodePlant_B->fBdy_mps2[0] = rtb_MathFunction[0] - ((rtb_Sum * 0.0 +
      rtb_Sum1_n * 0.0) + rtb_VectorConcatenate_tmp * 9.81);

    /* Product: '<S180>/Product3' incorporates:
     *  Product: '<S178>/Product2'
     *  Product: '<S181>/Product3'
     */
    rtb_Product3_ax *= rtb_Lw_idx_1;

    /* Product: '<S180>/Product2' incorporates:
     *  Product: '<S178>/Product'
     *  Product: '<S178>/Product1'
     *  Product: '<S181>/Product2'
     */
    rtb_FlatEarthtoLLA_o1_idx_1 *= rtb_Switch_d_idx_0;

    /* Sum: '<S180>/Sum3' incorporates:
     *  Constant: '<S180>/Constant'
     *  Product: '<S178>/Product1'
     *  Product: '<S180>/Product6'
     *  Sum: '<S181>/Sum3'
     */
    rtb_Switch_d_idx_0 = 0.5 - rtb_Switch_d_idx_0 * rtb_Switch_d_idx_0;

    /* Gain: '<S180>/Gain2' incorporates:
     *  Gain: '<S193>/Gain2'
     *  Sum: '<S180>/Sum3'
     *  Sum: '<S193>/Sum'
     */
    rtb_Switch_d_idx_1 = (rtb_Switch_d_idx_0 - rtb_Switch_d_idx_1) * 2.0;

    /* Gain: '<S180>/Gain' incorporates:
     *  Gain: '<S193>/Gain'
     *  Sum: '<S180>/Sum1'
     *  Sum: '<S193>/Sum'
     */
    rtb_Switch_d_idx_2 = (rtb_Switch_d_idx_2 - rtb_Product1_hx) * 2.0;

    /* Gain: '<S180>/Gain1' incorporates:
     *  Gain: '<S193>/Gain1'
     *  Product: '<S180>/Product2'
     *  Product: '<S180>/Product3'
     *  Sum: '<S180>/Sum2'
     *  Sum: '<S193>/Sum'
     */
    rtb_Product1_hx = (rtb_FlatEarthtoLLA_o1_idx_1 + rtb_Product3_ax) * 2.0;

    /* Sum: '<S170>/fBdy_mps2' incorporates:
     *  Constant: '<S170>/gNed_mps2'
     *  Gain: '<S180>/Gain'
     *  Gain: '<S180>/Gain1'
     *  Gain: '<S180>/Gain2'
     *  Product: '<S180>/Product4'
     *  Product: '<S180>/Product5'
     *  Product: '<S180>/Product8'
     *  Sum: '<S180>/Sum'
     */
    autocodePlant_B->fBdy_mps2[1] = rtb_MathFunction[1] - ((rtb_Switch_d_idx_1 *
      0.0 + rtb_Switch_d_idx_2 * 0.0) + rtb_Product1_hx * 9.81);

    /* Gain: '<S181>/Gain' incorporates:
     *  Gain: '<S194>/Gain'
     *  Sum: '<S181>/Sum1'
     *  Sum: '<S194>/Sum'
     */
    rtb_TmpSignalConversionAtProd_0 = (rtb_TmpSignalConversionAtProd_0 +
      rtb_UnaryMinus_a) * 2.0;

    /* Gain: '<S181>/Gain1' incorporates:
     *  Gain: '<S194>/Gain1'
     *  Sum: '<S181>/Sum2'
     *  Sum: '<S194>/Sum'
     */
    rtb_UnaryMinus_a = (rtb_Product3_ax - rtb_FlatEarthtoLLA_o1_idx_1) * 2.0;

    /* Gain: '<S181>/Gain2' incorporates:
     *  Gain: '<S194>/Gain2'
     *  Sum: '<S181>/Sum3'
     *  Sum: '<S194>/Sum'
     */
    rtb_Sum_d0 = (rtb_Switch_d_idx_0 - rtb_Sum_d0) * 2.0;

    /* Sum: '<S170>/fBdy_mps2' incorporates:
     *  Constant: '<S170>/gNed_mps2'
     *  Gain: '<S181>/Gain'
     *  Gain: '<S181>/Gain1'
     *  Gain: '<S181>/Gain2'
     *  Product: '<S181>/Product4'
     *  Product: '<S181>/Product5'
     *  Product: '<S181>/Product8'
     *  Sum: '<S181>/Sum'
     */
    autocodePlant_B->fBdy_mps2[2] = rtb_MathFunction[2] -
      ((rtb_TmpSignalConversionAtProd_0 * 0.0 + rtb_UnaryMinus_a * 0.0) +
       rtb_Sum_d0 * 9.81);
    if (tmp) {
      /* Product: '<S170>/scale factor and  cross-coupling' incorporates:
       *  Constant: '<S170>/Constant'
       */
      localProduct = autocodePlant_B->fBdy_mps2[1];
      rtb_Switch_d_idx_0 = autocodePlant_B->fBdy_mps2[0];
      rtb_FlatEarthtoLLA_o1_idx_1 = autocodePlant_B->fBdy_mps2[2];

      /* Product: '<S172>/Product1' */
      rtb_Lw_idx_1 = 0.0;
      rtb_sincos_o2_idx_0 = 0.0;
      rtb_Sum2_fl = 0.0;
      for (i = 0; i < 3; i++) {
        /* ZeroOrderHold: '<S170>/Zero-Order Hold' incorporates:
         *  Constant: '<S170>/Constant'
         *  Product: '<S170>/scale factor and  cross-coupling'
         *  Sum: '<S170>/sum'
         */
        rtb_ZeroOrderHold_c[i] = ((rtCP__Constant_Value_dxg[i + 3] *
          localProduct + rtCP__Constant_Value_dxg[i] * rtb_Switch_d_idx_0) +
          rtCP__Constant_Value_dxg[i + 6] * rtb_FlatEarthtoLLA_o1_idx_1) +
          autocodePlant_B->biasnoise[i];

        /* Sum: '<S172>/bias + noise' incorporates:
         *  Gain: '<S187>/Output'
         *  RandomNumber: '<S187>/White Noise'
         */
        biasnoise_d[i] = 6.1075E-5 * autocodePlant_DW->NextOutput_i +
          rtb_ZeroOrderHold_a[i];

        /* Product: '<S172>/Product1' incorporates:
         *  Constant: '<S172>/Gs'
         *  UnitDelay: '<S172>/Unit Delay'
         */
        rtb_Product3_ax = autocodePlant_DW->UnitDelay_DSTATE_c[i];
        rtb_Lw_idx_1 += rtCP__Gs_Value[3 * i] * rtb_Product3_ax;
        rtb_sincos_o2_idx_0 += rtCP__Gs_Value[3 * i + 1] * rtb_Product3_ax;
        rtb_Sum2_fl += rtCP__Gs_Value[3 * i + 2] * rtb_Product3_ax;
      }

      /* Product: '<S172>/Product1' */
      Gdependent[2] = rtb_Sum2_fl;
      Gdependent[1] = rtb_sincos_o2_idx_0;
      Gdependent[0] = rtb_Lw_idx_1;

      /* Product: '<S172>/Product' incorporates:
       *  Constant: '<S172>/   '
       */
      localProduct = rtb_wBdy_rps[1];
      rtb_Product3_ax = rtb_wBdy_rps[0];
      rtb_Switch_d_idx_0 = rtb_wBdy_rps[2];
      for (i = 0; i < 3; i++) {
        /* ZeroOrderHold: '<S172>/Zero-Order Hold' incorporates:
         *  Constant: '<S172>/   '
         *  Product: '<S172>/Product'
         *  Sum: '<S172>/      '
         */
        rtb_ZeroOrderHold_a[i] = (((rtCP___Value_n[i + 3] * localProduct +
          rtCP___Value_n[i] * rtb_Product3_ax) + rtCP___Value_n[i + 6] *
          rtb_Switch_d_idx_0) + biasnoise_d[i]) + Gdependent[i];

        /* Gain: '<S190>/Output' incorporates:
         *  RandomNumber: '<S190>/White Noise'
         */
        autocodePlant_B->Output[i] = 140.0 * autocodePlant_DW->NextOutput_b;
      }

      /* Memory: '<S223>/otime' */
      localProduct = autocodePlant_DW->otime_PreviousInput;

      /* RelationalOperator: '<S223>/Relational Operator' incorporates:
       *  Constant: '<S173>/decimal year'
       *  Memory: '<S223>/otime'
       */
      rtb_RelationalOperator = (autocodePlant_DW->otime_PreviousInput !=
        2026.6657534246576);
    }

    /* FlatEarth2LLA: '<S173>/Flat Earth to LLA' */
    rtb_Product3_ax = (rtb_Sum1_ju[0] - 0.0 * rtb_Sum1_ju[1]) /
      6.3354393272928195E+6;
    rtb_Switch_d_idx_0 = fabs(rtb_Product3_ax);
    rtb_FlatEarthtoLLA_o1_idx_1 = (0.0 * rtb_Sum1_ju[0] + rtb_Sum1_ju[1]) /
      6.378137E+6 + 0.17453292519943295;
    if (rtb_Switch_d_idx_0 > 3.141592653589793) {
      rtb_Product3_ax = rt_modd_snf(rtb_Product3_ax + 3.141592653589793,
        6.283185307179586) - 3.141592653589793;
      rtb_Switch_d_idx_0 = fabs(rtb_Product3_ax);
    }

    if (rtb_Switch_d_idx_0 > 1.5707963267948966) {
      rtb_FlatEarthtoLLA_o1_idx_1 += 3.141592653589793;
      if (rtIsNaN(rtb_Product3_ax)) {
        rtb_Product3_ax = (rtNaN);
      } else if (rtb_Product3_ax < 0.0) {
        rtb_Product3_ax = -1.0;
      } else {
        rtb_Product3_ax = (rtb_Product3_ax > 0.0);
      }

      rtb_Product3_ax *= 1.5707963267948966 - (rtb_Switch_d_idx_0 -
        1.5707963267948966);
    }

    if (fabs(rtb_FlatEarthtoLLA_o1_idx_1) > 3.141592653589793) {
      rtb_Switch_d_idx_0 = rt_remd_snf(rtb_FlatEarthtoLLA_o1_idx_1,
        6.283185307179586);
      rtb_FlatEarthtoLLA_o1_idx_1 = rtb_Switch_d_idx_0 - trunc
        (rtb_Switch_d_idx_0 / 3.141592653589793) * 6.283185307179586;
    }

    rtb_Switch_d_idx_0 = rtb_Product3_ax * 180.0 / 3.141592653589793;
    rtb_FlatEarthtoLLA_o1_idx_1 = rtb_FlatEarthtoLLA_o1_idx_1 * 180.0 /
      3.141592653589793;

    /* Switch: '<S212>/Switch' incorporates:
     *  Abs: '<S212>/Abs'
     *  Bias: '<S212>/Bias'
     *  Bias: '<S212>/Bias1'
     *  Constant: '<S212>/Constant2'
     *  Constant: '<S215>/Constant'
     *  Math: '<S212>/Math Function1'
     *  RelationalOperator: '<S215>/Compare'
     */
    if (fabs(rtb_Switch_d_idx_0) > 180.0) {
      rtb_Product3_ax = rt_modd_snf(rtb_Switch_d_idx_0 + 180.0, 360.0) - 180.0;
    } else {
      rtb_Product3_ax = rtb_Switch_d_idx_0;
    }

    /* End of Switch: '<S212>/Switch' */

    /* Abs: '<S208>/Abs1' */
    rtb_Lw_idx_1 = fabs(rtb_Product3_ax);

    /* RelationalOperator: '<S210>/Compare' incorporates:
     *  Constant: '<S210>/Constant'
     */
    rtb_min_relop_n = (rtb_Lw_idx_1 > 90.0);

    /* Switch: '<S202>/Switch1' incorporates:
     *  Constant: '<S202>/Constant'
     *  Constant: '<S202>/Constant1'
     */
    if (rtb_min_relop_n) {
      i = 180;
    } else {
      i = 0;
    }

    /* Sum: '<S202>/Sum' incorporates:
     *  Switch: '<S202>/Switch1'
     */
    autocodePlant_B->Switch = (real_T)i + rtb_FlatEarthtoLLA_o1_idx_1;

    /* Switch: '<S209>/Switch' incorporates:
     *  Abs: '<S209>/Abs'
     *  Constant: '<S216>/Constant'
     *  RelationalOperator: '<S216>/Compare'
     */
    if (fabs(autocodePlant_B->Switch) > 180.0) {
      /* Sum: '<S202>/Sum' incorporates:
       *  Bias: '<S209>/Bias'
       *  Bias: '<S209>/Bias1'
       *  Constant: '<S209>/Constant2'
       *  Math: '<S209>/Math Function1'
       *  Switch: '<S209>/Switch'
       */
      autocodePlant_B->Switch = rt_modd_snf(autocodePlant_B->Switch + 180.0,
        360.0) - 180.0;
    }

    /* End of Switch: '<S209>/Switch' */

    /* If: '<S211>/If' incorporates:
     *  Abs: '<S211>/Abs'
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
      /* Outputs for IfAction SubSystem: '<S211>/If Action Subsystem' incorporates:
       *  ActionPort: '<S213>/Action Port'
       */
      /* Merge: '<S211>/Merge' incorporates:
       *  Abs: '<S211>/Abs'
       *  Product: '<S213>/Divide'
       */
      autocodePlant_B->Merge = rtb_Product3_ax / rtb_Lw_idx_1;

      /* End of Outputs for SubSystem: '<S211>/If Action Subsystem' */

      /* Outputs for IfAction SubSystem: '<S211>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S214>/Action Port'
       */
    } else if (rtmIsMajorTimeStep(autocodePlant_M) &&
               autocodePlant_M->Timing.TaskCounters.TID[1] == 0) {
      /* Merge: '<S211>/Merge' incorporates:
       *  Constant: '<S214>/Constant'
       *  SignalConversion generated from: '<S214>/zero'
       */
      autocodePlant_B->Merge = 0.0;

      /* End of Outputs for SubSystem: '<S211>/If Action Subsystem1' */
    }

    /* End of If: '<S211>/If' */

    /* Switch: '<S208>/Switch' */
    if (rtb_min_relop_n) {
      /* Switch: '<S208>/Switch' incorporates:
       *  Bias: '<S208>/Bias'
       *  Bias: '<S208>/Bias1'
       *  Gain: '<S208>/Gain'
       *  Product: '<S208>/Divide1'
       */
      autocodePlant_B->Switch_l = (-(rtb_Lw_idx_1 - 90.0) + 90.0) *
        autocodePlant_B->Merge;
    } else {
      /* Switch: '<S208>/Switch' */
      autocodePlant_B->Switch_l = rtb_Product3_ax;
    }

    /* End of Switch: '<S208>/Switch' */

    /* UnitConversion: '<S267>/Unit Conversion' */
    /* Unit Conversion - from: deg to: rad
       Expression: output = (0.0174533*input) + (0) */
    rtb_Lw_idx_0 = 0.017453292519943295 * autocodePlant_B->Switch;
    rtb_Lw_idx_1 = 0.017453292519943295 * autocodePlant_B->Switch_l;

    /* Trigonometry: '<S220>/sincos' */
    rtb_Product3_ax = sin(rtb_Lw_idx_0);
    rtb_sincos_o2_idx_0 = cos(rtb_Lw_idx_0);
    rtb_sincos_o1_idx_1 = sin(rtb_Lw_idx_1);
    rtb_Lw_idx_1 = cos(rtb_Lw_idx_1);

    /* Outputs for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates ' incorporates:
     *  EnablePort: '<S219>/Enable'
     */
    if (tmp) {
      if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
        /* RelationalOperator: '<S222>/Relational Operator' incorporates:
         *  Memory: '<S222>/olon'
         */
        autocodePlant_DW->Convertfromgeodetictosphericalc =
          (autocodePlant_B->Switch != autocodePlant_DW->olon_PreviousInput);
      }

      /* Memory: '<S221>/olat' */
      autocodePlant_B->olat = autocodePlant_DW->olat_PreviousInput;
    }

    if (autocodePlant_DW->Convertfromgeodetictosphericalc) {
      if (rtmIsMajorTimeStep(autocodePlant_M) &&
          autocodePlant_M->Timing.TaskCounters.TID[1] == 0) {
        /* Outputs for Iterator SubSystem: '<S219>/For Iterator Subsystem' incorporates:
         *  ForIterator: '<S266>/For Iterator'
         */
        for (s266_iter = 0; s266_iter < 11; s266_iter++) {
          /* Switch: '<S266>/cp[m-1] sp[m-1]' incorporates:
           *  SignalConversion generated from: '<S219>/cp[2]'
           *  SignalConversion generated from: '<S219>/sp[2]'
           *  UnitDelay: '<S266>/Unit Delay1'
           */
          if (s266_iter > 0) {
            localProduct = autocodePlant_DW->UnitDelay1_DSTATE[0];
            rtb_Lw_idx_0 = autocodePlant_DW->UnitDelay1_DSTATE[1];
          } else {
            localProduct = rtb_sincos_o2_idx_0;
            rtb_Lw_idx_0 = rtb_Product3_ax;
          }

          /* End of Switch: '<S266>/cp[m-1] sp[m-1]' */

          /* Sum: '<S266>/Sum2' incorporates:
           *  Product: '<S266>/Product1'
           *  Product: '<S266>/Product2'
           *  SignalConversion generated from: '<S219>/cp[2]'
           *  SignalConversion generated from: '<S219>/sp[2]'
           */
          rtb_Sum2_fl = localProduct * rtb_Product3_ax + rtb_Lw_idx_0 *
            rtb_sincos_o2_idx_0;

          /* Product: '<S266>/Product3' incorporates:
           *  SignalConversion generated from: '<S219>/cp[2]'
           */
          localProduct *= rtb_sincos_o2_idx_0;

          /* Sum: '<S266>/Sum1' incorporates:
           *  Product: '<S266>/Product3'
           *  Product: '<S266>/Product8'
           *  SignalConversion generated from: '<S219>/sp[2]'
           */
          rtb_Lw_idx_0 = localProduct - rtb_Lw_idx_0 * rtb_Product3_ax;

          /* Assignment: '<S266>/Assignment' incorporates:
           *  Assignment: '<S266>/Assignment1'
           *  Constant: '<S266>/Constant'
           */
          if (s266_iter == 0) {
            memcpy(&autocodePlant_B->Assignment[0], &rtCP__Constant_Value_f[0],
                   11U * sizeof(real_T));

            /* Assignment: '<S266>/Assignment1' incorporates:
             *  Constant: '<S266>/Constant'
             *  Constant: '<S266>/Constant1'
             */
            memcpy(&autocodePlant_B->Assignment1[0], &rtCP__Constant1_Value_a[0],
                   11U * sizeof(real_T));
          }

          autocodePlant_B->Assignment[s266_iter] = rtb_Sum2_fl;

          /* End of Assignment: '<S266>/Assignment' */

          /* Assignment: '<S266>/Assignment1' */
          autocodePlant_B->Assignment1[s266_iter] = rtb_Lw_idx_0;

          /* Update for UnitDelay: '<S266>/Unit Delay1' */
          autocodePlant_DW->UnitDelay1_DSTATE[0] = rtb_Lw_idx_0;
          autocodePlant_DW->UnitDelay1_DSTATE[1] = rtb_Sum2_fl;
        }

        /* End of Outputs for SubSystem: '<S219>/For Iterator Subsystem' */
      }

      /* SignalConversion generated from: '<S219>/cp[13]' incorporates:
       *  Constant: '<S219>/cp[1]'
       *  SignalConversion generated from: '<S219>/cp[2]'
       */
      autocodePlant_B->OutportBufferForcp13[0] = 1.0;
      autocodePlant_B->OutportBufferForcp13[1] = rtb_sincos_o2_idx_0;

      /* SignalConversion generated from: '<S219>/sp[13]' incorporates:
       *  Constant: '<S219>/sp[1]'
       *  SignalConversion generated from: '<S219>/sp[2]'
       */
      autocodePlant_B->OutportBufferForsp13[0] = 0.0;
      autocodePlant_B->OutportBufferForsp13[1] = rtb_Product3_ax;

      /* SignalConversion generated from: '<S219>/cp[13]' */
      memcpy(&autocodePlant_B->OutportBufferForcp13[2],
             &autocodePlant_B->Assignment1[0], 11U * sizeof(real_T));

      /* SignalConversion generated from: '<S219>/sp[13]' */
      memcpy(&autocodePlant_B->OutportBufferForsp13[2],
             &autocodePlant_B->Assignment[0], 11U * sizeof(real_T));
    }

    /* End of Outputs for SubSystem: '<S206>/Convert from geodetic to  spherical coordinates ' */

    /* Gain: '<S189>/Gain' incorporates:
     *  Constant: '<S173>/ground altitude'
     *  FlatEarth2LLA: '<S173>/Flat Earth to LLA'
     */
    autocodePlant_B->Gain = -(rtb_Sum1_ju[2] + 182.0) * 0.001;
    if (tmp) {
      /* Memory: '<S221>/oalt' */
      autocodePlant_B->oalt = autocodePlant_DW->oalt_PreviousInput;
    }

    /* Logic: '<S221>/Logical Operator' incorporates:
     *  RelationalOperator: '<S221>/Relational Operator'
     *  RelationalOperator: '<S221>/Relational Operator1'
     */
    rtb_min_relop_n = ((autocodePlant_B->Switch_l != autocodePlant_B->olat) ||
                       (autocodePlant_B->Gain != autocodePlant_B->oalt));

    /* Product: '<S220>/Product' */
    rtb_Lw_idx_0 = rtb_sincos_o1_idx_1 * rtb_sincos_o1_idx_1;

    /* Product: '<S220>/Product1' */
    rtb_Product1_jv = rtb_Lw_idx_1 * rtb_Lw_idx_1;

    /* Outputs for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' incorporates:
     *  EnablePort: '<S218>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      autocodePlant_DW->Convertfromgeodetictospherica_p = rtb_min_relop_n;
    }

    if (autocodePlant_DW->Convertfromgeodetictospherica_p) {
      /* Sqrt: '<S260>/sqrt' incorporates:
       *  Product: '<S260>/Product10'
       *  Product: '<S260>/Product9'
       *  Sum: '<S260>/Sum7'
       */
      rtb_sincos_o2_idx_0 = sqrt(rtb_Product1_jv * autocodePlant_ConstB.a2 +
        autocodePlant_ConstB.b2 * rtb_Lw_idx_0);

      /* Sqrt: '<S261>/sqrt' incorporates:
       *  Product: '<S261>/Product'
       *  Sum: '<S261>/Sum'
       */
      rtb_Product3_ax = sqrt(autocodePlant_ConstB.a2 - rtb_Lw_idx_0 *
        autocodePlant_ConstB.c2);

      /* Product: '<S218>/Product1' */
      rtb_Sum2_fl = rtb_Product3_ax * autocodePlant_B->Gain;

      /* Sqrt: '<S218>/sqrt' incorporates:
       *  Gain: '<S263>/Gain'
       *  Product: '<S263>/Product1'
       *  Product: '<S263>/Product6'
       *  Product: '<S263>/Product7'
       *  Product: '<S263>/Product8'
       *  Sum: '<S263>/Sum5'
       *  Sum: '<S263>/Sum6'
       */
      autocodePlant_B->sqrt_b = sqrt((autocodePlant_ConstB.a4 -
        autocodePlant_ConstB.c4 * rtb_Lw_idx_0) / (rtb_Product3_ax *
        rtb_Product3_ax) + (2.0 * rtb_Sum2_fl + autocodePlant_B->Gain *
                            autocodePlant_B->Gain));

      /* Product: '<S258>/Product11' incorporates:
       *  Sum: '<S258>/Sum8'
       */
      autocodePlant_B->Product11 = (autocodePlant_B->Gain + rtb_sincos_o2_idx_0)
        / autocodePlant_B->sqrt_b;

      /* Product: '<S264>/Product12' incorporates:
       *  Product: '<S264>/Product1'
       */
      autocodePlant_B->Product12 = autocodePlant_ConstB.c2_l /
        (autocodePlant_B->sqrt_b * rtb_sincos_o2_idx_0) * rtb_Lw_idx_1 *
        rtb_sincos_o1_idx_1;

      /* Sum: '<S262>/Sum2' */
      rtb_sincos_o2_idx_0 = autocodePlant_ConstB.a2 + rtb_Sum2_fl;

      /* Sum: '<S262>/Sum1' */
      rtb_Sum2_fl += autocodePlant_ConstB.b2;

      /* Product: '<S259>/Product4' incorporates:
       *  Product: '<S259>/Product3'
       *  Product: '<S262>/Product1'
       *  Product: '<S262>/Product2'
       *  Sqrt: '<S259>/sqrt'
       *  Sum: '<S259>/Sum3'
       */
      autocodePlant_B->Product4 = rtb_sincos_o1_idx_1 / sqrt(rtb_sincos_o2_idx_0
        * rtb_sincos_o2_idx_0 / (rtb_Sum2_fl * rtb_Sum2_fl) * rtb_Product1_jv +
        rtb_Lw_idx_0);

      /* Sqrt: '<S265>/sqrt' incorporates:
       *  Constant: '<S265>/Constant'
       *  Product: '<S265>/Product5'
       *  Sum: '<S265>/Sum4'
       */
      autocodePlant_B->sqrt_k = sqrt(1.0 - autocodePlant_B->Product4 *
        autocodePlant_B->Product4);
    }

    /* End of Outputs for SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' */

    /* Product: '<S206>/aor' incorporates:
     *  Constant: '<S206>/re'
     */
    rtb_Lw_idx_1 = 6371.2 / autocodePlant_B->sqrt_b;
    if (tmp) {
      /* Outputs for Iterator SubSystem: '<S206>/Compute magnetic vector in spherical coordinates' incorporates:
       *  ForIterator: '<S217>/For Iterator'
       */
      /* InitializeConditions for UnitDelay: '<S217>/Unit Delay2' */
      autocodePlant_DW->UnitDelay2_DSTATE[0] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[1] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[2] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[3] = 0.0;

      /* InitializeConditions for UnitDelay: '<S217>/Unit Delay' */
      rtb_sincos_o2_idx_0 = 0.0;
      for (s266_iter = 0; s266_iter < 12; s266_iter++) {
        /* UnitDelay: '<S217>/Unit Delay' */
        localProduct = rtb_sincos_o2_idx_0;

        /* Switch: '<S217>/ar(n)' incorporates:
         *  Product: '<S206>/ar'
         */
        if (s266_iter <= 0) {
          localProduct = rtb_Lw_idx_1 * rtb_Lw_idx_1;
        }

        /* End of Switch: '<S217>/ar(n)' */

        /* Product: '<S217>/Product8' incorporates:
         *  UnitDelay: '<S217>/Unit Delay'
         */
        rtb_sincos_o2_idx_0 = localProduct * rtb_Lw_idx_1;

        /* Outputs for Iterator SubSystem: '<S217>/For Iterator Subsystem' incorporates:
         *  ForIterator: '<S225>/For Iterator'
         */
        /* InitializeConditions for UnitDelay: '<S226>/Unit Delay3' */
        rtb_Sum2_fl = 0.0;

        /* InitializeConditions for UnitDelay: '<S226>/Unit Delay2' */
        rtb_sincos_o1_idx_1 = 0.0;

        /* InitializeConditions for UnitDelay: '<S226>/Unit Delay1' */
        rtb_Lw_idx_0 = 0.0;

        /* InitializeConditions for UnitDelay: '<S226>/Unit Delay4' */
        rtb_Product1_jv = 0.0;
        for (i = 0; i < 6; i++) {
          ForIterator_IterationMarker[i] = 1U;
        }

        /* Sum: '<S217>/Sum' incorporates:
         *  Constant: '<S232>/Constant'
         *  Constant: '<S232>/Constant1'
         *  Logic: '<S232>/Logical Operator'
         *  RelationalOperator: '<S232>/Relational Operator'
         *  RelationalOperator: '<S232>/Relational Operator1'
         *  SignalConversion generated from: '<S227>/Enable'
         *  Sum: '<S225>/Sum1'
         */
        for (s225_iter = 1; s225_iter <= s266_iter + 2; s225_iter++) {
          /* Outputs for Enabled SubSystem: '<S225>/Time adjust the gauss coefficients' incorporates:
           *  EnablePort: '<S228>/Enable'
           */
          if (rtb_RelationalOperator) {
            /* Assignment: '<S228>/Assignment' */
            if (ForIterator_IterationMarker[4] < 2) {
              ForIterator_IterationMarker[4] = 2U;

              /* Assignment: '<S228>/Assignment' incorporates:
               *  UnitDelay: '<S228>/Unit Delay'
               */
              memcpy(&autocodePlant_B->Assignment_o[0],
                     &autocodePlant_DW->UnitDelay_DSTATE_e[0], 169U * sizeof
                     (real_T));
            }

            /* Outputs for Atomic SubSystem: '<S228>/If Action Subsystem' */
            /* Selector: '<S254>/c[m][n]' incorporates:
             *  Assignment: '<S228>/Assignment'
             *  Constant: '<S228>/cd[maxdef][maxdef]'
             *  Selector: '<S254>/cd[m][n]'
             *  Sum: '<S254>/Sum2'
             */
            i = ((s266_iter + 1) * 13 + s225_iter) - 1;

            /* Assignment: '<S228>/Assignment' incorporates:
             *  Constant: '<S228>/c[maxdef][maxdef]'
             *  Constant: '<S228>/cd[maxdef][maxdef]'
             *  Product: '<S254>/Product'
             *  Selector: '<S254>/c[m][n]'
             *  Selector: '<S254>/cd[m][n]'
             *  Sum: '<S254>/Sum'
             */
            autocodePlant_B->Assignment_o[i] = rtCP__cdmaxdefmaxdef_Value[i] *
              autocodePlant_ConstB.Sum_dd + rtCP__cmaxdefmaxdef_Value[i];

            /* End of Outputs for SubSystem: '<S228>/If Action Subsystem' */

            /* Switch: '<S255>/tc_old' incorporates:
             *  UnitDelay: '<S255>/Unit Delay'
             */
            if (s266_iter <= 0) {
              memset(&autocodePlant_DW->UnitDelay_DSTATE_k[0], 0, 169U * sizeof
                     (real_T));
            }

            /* End of Switch: '<S255>/tc_old' */

            /* If: '<S255>/If' incorporates:
             *  Sum: '<S225>/Sum1'
             */
            if (s225_iter - 1 != 0) {
              /* Outputs for IfAction SubSystem: '<S255>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S256>/Action Port'
               */
              /* Assignment: '<S256>/Assignment2' */
              if (ForIterator_IterationMarker[5] < 2) {
                ForIterator_IterationMarker[5] = 2U;

                /* Assignment: '<S256>/Assignment2' incorporates:
                 *  Switch: '<S255>/tc_old'
                 */
                memcpy(&autocodePlant_B->Assignment2[0],
                       &autocodePlant_DW->UnitDelay_DSTATE_k[0], 169U * sizeof
                       (real_T));
              }

              /* Selector: '<S256>/c[m][n]' incorporates:
               *  Assignment: '<S256>/Assignment2'
               *  Constant: '<S228>/cd[maxdef][maxdef]'
               *  Selector: '<S256>/cd[m][n]'
               *  Sum: '<S256>/Sum2'
               */
              i = ((s225_iter - 2) * 13 + s266_iter) + 1;

              /* Assignment: '<S256>/Assignment2' incorporates:
               *  Constant: '<S228>/c[maxdef][maxdef]'
               *  Constant: '<S228>/cd[maxdef][maxdef]'
               *  Product: '<S256>/Product'
               *  Selector: '<S256>/c[m][n]'
               *  Selector: '<S256>/cd[m][n]'
               *  Sum: '<S256>/Sum'
               *  Sum: '<S256>/Sum2'
               */
              autocodePlant_B->Assignment2[i] = rtCP__cdmaxdefmaxdef_Value[i] *
                autocodePlant_ConstB.Sum_dd + rtCP__cmaxdefmaxdef_Value[i];

              /* Gain: '<S256>/Gain' incorporates:
               *  Assignment: '<S256>/Assignment2'
               *  Merge: '<S255>/Merge'
               *  UnitDelay: '<S255>/Unit Delay'
               */
              memcpy(&autocodePlant_DW->UnitDelay_DSTATE_k[0],
                     &autocodePlant_B->Assignment2[0], 169U * sizeof(real_T));

              /* End of Outputs for SubSystem: '<S255>/If Action Subsystem1' */
            }

            /* End of If: '<S255>/If' */
            for (i = 0; i < 169; i++) {
              /* Sum: '<S228>/Sum2' incorporates:
               *  Assignment: '<S228>/Assignment'
               */
              localProduct = autocodePlant_B->Assignment_o[i];

              /* Sum: '<S228>/Sum2' incorporates:
               *  Assignment: '<S228>/Assignment'
               *  Merge: '<S255>/Merge'
               *  UnitDelay: '<S255>/Unit Delay'
               */
              autocodePlant_B->Sum2_p[i] = localProduct +
                autocodePlant_DW->UnitDelay_DSTATE_k[i];

              /* Update for UnitDelay: '<S228>/Unit Delay' incorporates:
               *  Assignment: '<S228>/Assignment'
               */
              autocodePlant_DW->UnitDelay_DSTATE_e[i] = localProduct;
            }
          }

          /* End of Outputs for SubSystem: '<S225>/Time adjust the gauss coefficients' */

          /* If: '<S231>/If' incorporates:
           *  Sum: '<S225>/Sum1'
           */
          if (s225_iter - 1 == 0) {
            /* Outputs for IfAction SubSystem: '<S231>/If Action Subsystem' incorporates:
             *  ActionPort: '<S237>/Action Port'
             */
            /* Product: '<S237>/Product' incorporates:
             *  Constant: '<S237>/Constant'
             *  Selector: '<S237>/Selector'
             *  Sum: '<S237>/Sum'
             */
            i = (s266_iter + 1) * 13;

            /* Merge: '<S231>/Merge' incorporates:
             *  Gain: '<S237>/Gain1'
             *  Product: '<S237>/Product'
             *  Selector: '<S231>/cp[m+1]'
             *  Selector: '<S237>/Selector'
             *  Sum: '<S228>/Sum2'
             */
            Merge_n = autocodePlant_B->OutportBufferForcp13[s225_iter - 1] *
              autocodePlant_B->Sum2_p[i];

            /* Merge: '<S231>/Merge1' incorporates:
             *  Gain: '<S237>/Gain2'
             *  Product: '<S237>/Product'
             *  Selector: '<S231>/sp[m+1]'
             *  Selector: '<S237>/Selector'
             *  Sum: '<S228>/Sum2'
             */
            localProduct = autocodePlant_B->OutportBufferForsp13[s225_iter - 1] *
              autocodePlant_B->Sum2_p[i];

            /* End of Outputs for SubSystem: '<S231>/If Action Subsystem' */
          } else {
            /* Outputs for IfAction SubSystem: '<S231>/If Action Subsystem1' incorporates:
             *  ActionPort: '<S238>/Action Port'
             */
            /* Product: '<S238>/Product' incorporates:
             *  Constant: '<S239>/Constant'
             *  Selector: '<S238>/Selector'
             *  Sum: '<S239>/Sum'
             */
            i = ((s266_iter + 1) * 13 + s225_iter) - 1;

            /* Product: '<S238>/Product1' incorporates:
             *  Selector: '<S238>/Selector1'
             *  Sum: '<S240>/Sum'
             */
            rtb_Sum2_ct = ((s225_iter - 2) * 13 + s266_iter) + 1;

            /* Merge: '<S231>/Merge' incorporates:
             *  Product: '<S238>/Product'
             *  Product: '<S238>/Product1'
             *  Selector: '<S231>/cp[m+1]'
             *  Selector: '<S231>/sp[m+1]'
             *  Selector: '<S238>/Selector'
             *  Selector: '<S238>/Selector1'
             *  Sum: '<S228>/Sum2'
             *  Sum: '<S238>/Sum'
             */
            Merge_n = autocodePlant_B->OutportBufferForcp13[s225_iter - 1] *
              autocodePlant_B->Sum2_p[i] + autocodePlant_B->
              OutportBufferForsp13[s225_iter - 1] * autocodePlant_B->
              Sum2_p[rtb_Sum2_ct];

            /* Merge: '<S231>/Merge1' incorporates:
             *  Product: '<S238>/Product'
             *  Product: '<S238>/Product1'
             *  Selector: '<S231>/cp[m+1]'
             *  Selector: '<S231>/sp[m+1]'
             *  Selector: '<S238>/Selector'
             *  Selector: '<S238>/Selector1'
             *  Sum: '<S228>/Sum2'
             *  Sum: '<S238>/Sum1'
             */
            localProduct = autocodePlant_B->OutportBufferForsp13[s225_iter - 1] *
              autocodePlant_B->Sum2_p[i] - autocodePlant_B->
              OutportBufferForcp13[s225_iter - 1] * autocodePlant_B->
              Sum2_p[rtb_Sum2_ct];

            /* End of Outputs for SubSystem: '<S231>/If Action Subsystem1' */
          }

          /* End of If: '<S231>/If' */

          /* Outputs for Enabled SubSystem: '<S225>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' incorporates:
           *  EnablePort: '<S227>/Enable'
           */
          if (rtb_min_relop_n) {
            /* If: '<S227>/if n == m elseif (n==1&m==0) elseif (n>1&m~=n)' incorporates:
             *  Sum: '<S225>/Sum1'
             */
            if (s266_iter + 1 == s225_iter - 1) {
              /* Outputs for IfAction SubSystem: '<S227>/If Action Subsystem' incorporates:
               *  ActionPort: '<S241>/Action Port'
               */
              /* Selector: '<S241>/Selector' incorporates:
               *  Gain: '<S245>/Gain'
               *  Sum: '<S245>/Sum1'
               *  Sum: '<S245>/Sum2'
               */
              rtb_Sum2_ct = mul_s32_sat(13, s225_iter - 2);
              if (rtb_Sum2_ct > 2147483646 - s266_iter) {
                i = MAX_int32_T;
              } else {
                i = (s266_iter + rtb_Sum2_ct) + 1;
              }

              /* Merge: '<S227>/Merge1' incorporates:
               *  Product: '<S241>/Product'
               *  Product: '<S241>/Product2'
               *  Selector: '<S241>/Selector'
               *  Selector: '<S241>/Selector1'
               *  Sum: '<S241>/Sum'
               *  Sum: '<S245>/Sum1'
               *  UnitDelay: '<S227>/Unit Delay'
               *  UnitDelay: '<S227>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = autocodePlant_DW->UnitDelay_DSTATE_o
                [(13 * s266_iter + s225_iter) - 2] * autocodePlant_B->sqrt_k +
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->Product4;

              /* Selector: '<S241>/Selector' incorporates:
               *  Sum: '<S245>/Sum1'
               */
              if (rtb_Sum2_ct > 2147483646 - s266_iter) {
                i = MAX_int32_T;
              } else {
                i = (s266_iter + rtb_Sum2_ct) + 1;
              }

              /* Merge: '<S227>/Merge' incorporates:
               *  Product: '<S241>/Product1'
               *  Selector: '<S241>/Selector'
               *  Sum: '<S245>/Sum1'
               *  UnitDelay: '<S227>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->sqrt_k;

              /* End of Outputs for SubSystem: '<S227>/If Action Subsystem' */
            } else if ((s266_iter == 0) && (s225_iter - 1 == 0)) {
              /* Outputs for IfAction SubSystem: '<S227>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S242>/Action Port'
               */
              /* Selector: '<S242>/Selector' incorporates:
               *  Gain: '<S247>/Gain'
               *  Sum: '<S247>/Sum1'
               */
              rtb_Sum2_ct = mul_s32_sat(13, 0);
              if (rtb_Sum2_ct > 2147483646) {
                i = MAX_int32_T;
              } else {
                i = rtb_Sum2_ct + 1;
              }

              /* Merge: '<S227>/Merge1' incorporates:
               *  Product: '<S242>/Product'
               *  Product: '<S242>/Product2'
               *  Selector: '<S242>/Selector'
               *  Selector: '<S242>/Selector1'
               *  Sum: '<S242>/Sum'
               *  Sum: '<S247>/Sum1'
               *  Sum: '<S248>/Sum'
               *  UnitDelay: '<S227>/Unit Delay'
               *  UnitDelay: '<S227>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = autocodePlant_B->Product4 *
                autocodePlant_DW->UnitDelay_DSTATE_o[0] -
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->sqrt_k;

              /* Selector: '<S242>/Selector' incorporates:
               *  Sum: '<S247>/Sum1'
               */
              if (rtb_Sum2_ct > 2147483646) {
                i = MAX_int32_T;
              } else {
                i = rtb_Sum2_ct + 1;
              }

              /* Merge: '<S227>/Merge' incorporates:
               *  Product: '<S242>/Product3'
               *  Selector: '<S242>/Selector'
               *  Sum: '<S247>/Sum1'
               *  UnitDelay: '<S227>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->Product4;

              /* End of Outputs for SubSystem: '<S227>/If Action Subsystem1' */
            } else if ((s266_iter > 0) && (s266_iter + 1 != s225_iter - 1)) {
              /* Outputs for IfAction SubSystem: '<S227>/If Action Subsystem2' incorporates:
               *  ActionPort: '<S243>/Action Port'
               */
              /* Gain: '<S249>/Gain' */
              rtb_Sum2_ct = mul_s32_sat(13, s225_iter - 1);

              /* Switch: '<S243>/Switch1' incorporates:
               *  Constant: '<S243>/Constant1'
               *  RelationalOperator: '<S253>/Relational Operator'
               *  Selector: '<S243>/Selector'
               *  Sum: '<S249>/Sum1'
               *  Sum: '<S253>/Sum2'
               *  UnitDelay: '<S227>/Unit Delay1'
               */
              if (s266_iter - 1 >= s225_iter - 1) {
                /* Selector: '<S243>/Selector' incorporates:
                 *  Sum: '<S249>/Sum1'
                 */
                if (rtb_Sum2_ct > MAX_int32_T - s266_iter) {
                  i = MAX_int32_T;
                } else {
                  i = s266_iter + rtb_Sum2_ct;
                }

                rtb_Product3_ax = autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1];
              } else {
                rtb_Product3_ax = 0.0;
              }

              /* Selector: '<S243>/Selector' incorporates:
               *  Sum: '<S249>/Sum1'
               */
              if (rtb_Sum2_ct > 2147483646 - s266_iter) {
                i = MAX_int32_T;
              } else {
                i = (s266_iter + rtb_Sum2_ct) + 1;
              }

              /* Selector: '<S243>/Selector2' incorporates:
               *  Constant: '<S243>/k[13][13]'
               *  Sum: '<S250>/Sum'
               */
              Merge_b_tmp = ((s266_iter + 1) * 13 + s225_iter) - 1;

              /* Merge: '<S227>/Merge' incorporates:
               *  Constant: '<S243>/k[13][13]'
               *  Product: '<S243>/Product2'
               *  Product: '<S243>/Product3'
               *  Selector: '<S243>/Selector'
               *  Selector: '<S243>/Selector2'
               *  Sum: '<S243>/Sum1'
               *  Sum: '<S249>/Sum1'
               *  Switch: '<S243>/Switch1'
               *  UnitDelay: '<S227>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->Product4 -
                rtCP__k1313_Value_j[Merge_b_tmp] * rtb_Product3_ax;

              /* Switch: '<S243>/Switch' incorporates:
               *  Constant: '<S243>/Constant'
               *  RelationalOperator: '<S252>/Relational Operator'
               *  Selector: '<S243>/Selector1'
               *  Sum: '<S252>/Sum2'
               *  UnitDelay: '<S227>/Unit Delay'
               */
              if (s266_iter - 1 >= s225_iter - 1) {
                rtb_Product3_ax = autocodePlant_DW->UnitDelay_DSTATE_o
                  [((s266_iter - 1) * 13 + s225_iter) - 1];
              } else {
                rtb_Product3_ax = 0.0;
              }

              /* Selector: '<S243>/Selector' incorporates:
               *  Sum: '<S249>/Sum1'
               */
              if (rtb_Sum2_ct > 2147483646 - s266_iter) {
                i = MAX_int32_T;
              } else {
                i = (s266_iter + rtb_Sum2_ct) + 1;
              }

              /* Merge: '<S227>/Merge1' incorporates:
               *  Constant: '<S243>/k[13][13]'
               *  Product: '<S243>/Product'
               *  Product: '<S243>/Product1'
               *  Product: '<S243>/Product4'
               *  Selector: '<S243>/Selector'
               *  Selector: '<S243>/Selector1'
               *  Selector: '<S243>/Selector2'
               *  Sum: '<S243>/Sum'
               *  Sum: '<S249>/Sum1'
               *  Switch: '<S243>/Switch'
               *  UnitDelay: '<S227>/Unit Delay'
               *  UnitDelay: '<S227>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = (autocodePlant_DW->UnitDelay_DSTATE_o
                [(13 * s266_iter + s225_iter) - 1] * autocodePlant_B->Product4 -
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->sqrt_k) - rtCP__k1313_Value_j[Merge_b_tmp] *
                rtb_Product3_ax;

              /* End of Outputs for SubSystem: '<S227>/If Action Subsystem2' */
            }

            /* End of If: '<S227>/if n == m elseif (n==1&m==0) elseif (n>1&m~=n)' */

            /* Assignment: '<S227>/Assignment_snorm' */
            if (ForIterator_IterationMarker[3] < 2) {
              ForIterator_IterationMarker[3] = 2U;

              /* Assignment: '<S227>/Assignment_snorm' incorporates:
               *  UnitDelay: '<S227>/Unit Delay1'
               */
              memcpy(&autocodePlant_B->Assignment_snorm[0],
                     &autocodePlant_DW->UnitDelay1_DSTATE_c[0], 169U * sizeof
                     (real_T));
            }

            /* Sum: '<S244>/Sum1' incorporates:
             *  Gain: '<S244>/Gain'
             *  Sum: '<S227>/Sum'
             *  Sum: '<S244>/Sum2'
             */
            i = mul_s32_sat(13, s225_iter - 1);
            if (i > 2147483645 - s266_iter) {
              i = MAX_int32_T;
            } else {
              i = (s266_iter + i) + 2;
            }

            /* Assignment: '<S227>/Assignment_snorm' incorporates:
             *  Sum: '<S244>/Sum1'
             */
            autocodePlant_B->Assignment_snorm[i - 1] = autocodePlant_B->Merge_b;

            /* Assignment: '<S227>/Assignment' incorporates:
             *  Sum: '<S227>/Sum'
             *  UnitDelay: '<S227>/Unit Delay'
             */
            if (ForIterator_IterationMarker[2] < 2) {
              ForIterator_IterationMarker[2] = 2U;
              memcpy(&autocodePlant_B->Assignment_h[0],
                     &autocodePlant_DW->UnitDelay_DSTATE_o[0], 169U * sizeof
                     (real_T));
            }

            autocodePlant_B->Assignment_h[(s225_iter + 13 * (s266_iter + 1)) - 1]
              = autocodePlant_B->Merge1_i;

            /* End of Assignment: '<S227>/Assignment' */

            /* Update for UnitDelay: '<S227>/Unit Delay' incorporates:
             *  Assignment: '<S227>/Assignment'
             */
            memcpy(&autocodePlant_DW->UnitDelay_DSTATE_o[0],
                   &autocodePlant_B->Assignment_h[0], 169U * sizeof(real_T));

            /* Update for UnitDelay: '<S227>/Unit Delay1' */
            memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_c[0],
                   &autocodePlant_B->Assignment_snorm[0], 169U * sizeof(real_T));
          }

          /* End of Outputs for SubSystem: '<S225>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */

          /* Selector: '<S226>/snorm[n+m*13]' incorporates:
           *  Gain: '<S230>/Gain'
           *  SignalConversion generated from: '<S227>/Enable'
           *  Sum: '<S225>/Sum1'
           *  Sum: '<S230>/Sum1'
           */
          i = mul_s32_sat(13, s225_iter - 1);
          if (i > 2147483645 - s266_iter) {
            i = MAX_int32_T;
          } else {
            i = (s266_iter + i) + 2;
          }

          /* Product: '<S226>/par' incorporates:
           *  Selector: '<S226>/snorm[n+m*13]'
           *  Sum: '<S230>/Sum1'
           *  UnitDelay: '<S217>/Unit Delay'
           */
          rtb_Product3_ax = autocodePlant_B->Assignment_snorm[i - 1] *
            rtb_sincos_o2_idx_0;

          /* Sum: '<S226>/Sum2' incorporates:
           *  Constant: '<S226>/fm'
           *  Product: '<S226>/Product1'
           *  Selector: '<S226>/fm[m]'
           *  UnitDelay: '<S226>/Unit Delay3'
           */
          autocodePlant_B->Sum2_m = rtCP__fm_Value[s225_iter - 1] *
            rtb_Product3_ax * localProduct + rtb_Sum2_fl;

          /* Sum: '<S226>/Sum3' incorporates:
           *  Constant: '<S226>/fn'
           *  Product: '<S226>/Product2'
           *  Selector: '<S226>/fn[m]'
           *  Sum: '<S226>/Sum4'
           *  UnitDelay: '<S226>/Unit Delay2'
           */
          autocodePlant_B->Sum3 = rtCP__fn_Value[s266_iter + 1] *
            rtb_Product3_ax * Merge_n + rtb_sincos_o1_idx_1;

          /* Outputs for Enabled SubSystem: '<S226>/Special case - North//South Geographic Pole' incorporates:
           *  EnablePort: '<S229>/Enable'
           */
          /* Outputs for IfAction SubSystem: '<S229>/If Action Subsystem2' incorporates:
           *  ActionPort: '<S234>/Action Port'
           */
          /* If: '<S229>/n ==1' incorporates:
           *  Constant: '<S234>/k[13][13]'
           *  Selector: '<S226>/dp[n][m]'
           *  Selector: '<S234>/Selector2'
           *  Sum: '<S226>/Sum'
           */
          rtb_Sum2_ct = (s266_iter + 1) * 13;

          /* End of Outputs for SubSystem: '<S229>/If Action Subsystem2' */
          /* End of Outputs for SubSystem: '<S226>/Special case - North//South Geographic Pole' */

          /* Sum: '<S226>/Sum1' incorporates:
           *  Assignment: '<S227>/Assignment'
           *  Product: '<S226>/Product'
           *  Selector: '<S226>/dp[n][m]'
           *  UnitDelay: '<S217>/Unit Delay'
           *  UnitDelay: '<S226>/Unit Delay1'
           */
          autocodePlant_B->Sum1_p = rtb_Lw_idx_0 - autocodePlant_B->
            Assignment_h[(rtb_Sum2_ct + s225_iter) - 1] * Merge_n *
            rtb_sincos_o2_idx_0;

          /* Outputs for Enabled SubSystem: '<S226>/Special case - North//South Geographic Pole' incorporates:
           *  EnablePort: '<S229>/Enable'
           */
          if ((autocodePlant_B->sqrt_k == 0.0) && (s225_iter - 1 == 1)) {
            autocodePlant_DW->SpecialcaseNorthSouthGeographic = true;

            /* If: '<S229>/n ==1' incorporates:
             *  Assignment: '<S234>/Assignment2'
             */
            if (s266_iter == 0) {
              /* Outputs for IfAction SubSystem: '<S229>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S233>/Action Port'
               */
              /* Assignment: '<S233>/Assignment2' incorporates:
               *  Selector: '<S233>/pp[n-1]'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              if (ForIterator_IterationMarker[0] < 2) {
                ForIterator_IterationMarker[0] = 2U;
                memcpy(&autocodePlant_B->Assignment2_m[0],
                       &autocodePlant_DW->UnitDelay1_DSTATE_b[0], 13U * sizeof
                       (real_T));
              }

              autocodePlant_B->Assignment2_m[1] =
                autocodePlant_DW->UnitDelay1_DSTATE_b[0];

              /* End of Assignment: '<S233>/Assignment2' */
              /* End of Outputs for SubSystem: '<S229>/If Action Subsystem1' */
            } else {
              /* Outputs for IfAction SubSystem: '<S229>/If Action Subsystem2' incorporates:
               *  ActionPort: '<S234>/Action Port'
               */
              if (ForIterator_IterationMarker[1] < 2) {
                /* Assignment: '<S234>/Assignment2' */
                ForIterator_IterationMarker[1] = 2U;

                /* Assignment: '<S234>/Assignment2' incorporates:
                 *  UnitDelay: '<S229>/Unit Delay1'
                 */
                memcpy(&autocodePlant_B->Assignment2_a[0],
                       &autocodePlant_DW->UnitDelay1_DSTATE_b[0], 13U * sizeof
                       (real_T));
              }

              /* Assignment: '<S234>/Assignment2' incorporates:
               *  Constant: '<S234>/k[13][13]'
               *  Product: '<S234>/Product1'
               *  Product: '<S234>/Product2'
               *  Selector: '<S234>/Selector2'
               *  Selector: '<S234>/pp[n-2] pp[n-1]'
               *  Sum: '<S234>/Sum1'
               *  Sum: '<S234>/Sum2'
               *  UnitDelay: '<S229>/Unit Delay1'
               */
              autocodePlant_B->Assignment2_a[s266_iter + 1] =
                autocodePlant_B->Product4 *
                autocodePlant_DW->UnitDelay1_DSTATE_b[s266_iter] -
                rtCP__k1313_Value[rtb_Sum2_ct + 1] *
                autocodePlant_DW->UnitDelay1_DSTATE_b[s266_iter - 1];

              /* End of Outputs for SubSystem: '<S229>/If Action Subsystem2' */
            }

            /* SignalConversion generated from: '<S229>/pp[n]' */
            autocodePlant_DW->UnitDelay1_DSTATE_b[1] =
              autocodePlant_B->Assignment2_m[1];
            memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_b[2],
                   &autocodePlant_B->Assignment2_a[2], 11U * sizeof(real_T));

            /* Product: '<S229>/Product2' incorporates:
             *  Selector: '<S229>/pp[n]'
             *  UnitDelay: '<S217>/Unit Delay'
             */
            autocodePlant_B->Product2 = autocodePlant_DW->
              UnitDelay1_DSTATE_b[s266_iter + 1] * rtb_sincos_o2_idx_0 *
              localProduct;
          } else if (autocodePlant_DW->SpecialcaseNorthSouthGeographic) {
            /* Disable for Product: '<S229>/Product2' incorporates:
             *  Outport: '<S229>/bpp'
             */
            autocodePlant_B->Product2 = 0.0;
            autocodePlant_DW->SpecialcaseNorthSouthGeographic = false;
          }

          /* End of Outputs for SubSystem: '<S226>/Special case - North//South Geographic Pole' */

          /* UnitDelay: '<S226>/Unit Delay4' incorporates:
           *  Constant: '<S232>/Constant'
           *  Constant: '<S232>/Constant1'
           *  Logic: '<S232>/Logical Operator'
           *  RelationalOperator: '<S232>/Relational Operator'
           *  RelationalOperator: '<S232>/Relational Operator1'
           *  Sum: '<S225>/Sum1'
           */
          localProduct = rtb_Product1_jv;

          /* Sum: '<S226>/Sum5' incorporates:
           *  UnitDelay: '<S226>/Unit Delay4'
           */
          autocodePlant_B->Sum5 = rtb_Product1_jv + autocodePlant_B->Product2;

          /* Update for UnitDelay: '<S226>/Unit Delay3' */
          rtb_Sum2_fl = autocodePlant_B->Sum2_m;

          /* Update for UnitDelay: '<S226>/Unit Delay2' */
          rtb_sincos_o1_idx_1 = autocodePlant_B->Sum3;

          /* Update for UnitDelay: '<S226>/Unit Delay1' */
          rtb_Lw_idx_0 = autocodePlant_B->Sum1_p;

          /* Update for UnitDelay: '<S226>/Unit Delay4' */
          rtb_Product1_jv = autocodePlant_B->Sum5;
        }

        /* End of Sum: '<S217>/Sum' */
        /* End of Outputs for SubSystem: '<S217>/For Iterator Subsystem' */

        /* Sum: '<S217>/Sum1' incorporates:
         *  UnitDelay: '<S217>/Unit Delay2'
         */
        rtb_Product3_ax = autocodePlant_DW->UnitDelay2_DSTATE[0];
        rtb_Sum2_fl = autocodePlant_DW->UnitDelay2_DSTATE[1];
        rtb_sincos_o1_idx_1 = autocodePlant_DW->UnitDelay2_DSTATE[2];
        rtb_Lw_idx_0 = autocodePlant_DW->UnitDelay2_DSTATE[3];
        autocodePlant_DW->UnitDelay2_DSTATE[0] = rtb_Product3_ax +
          autocodePlant_B->Sum1_p;
        autocodePlant_DW->UnitDelay2_DSTATE[1] = rtb_Sum2_fl +
          autocodePlant_B->Sum2_m;
        autocodePlant_DW->UnitDelay2_DSTATE[2] = rtb_sincos_o1_idx_1 +
          autocodePlant_B->Sum3;
        autocodePlant_DW->UnitDelay2_DSTATE[3] = rtb_Lw_idx_0 +
          autocodePlant_B->Sum5;
      }

      /* End of Outputs for SubSystem: '<S206>/Compute magnetic vector in spherical coordinates' */
    }

    /* Switch: '<S269>/Switch' incorporates:
     *  Product: '<S269>/Product'
     *  UnitDelay: '<S217>/Unit Delay2'
     */
    if (autocodePlant_B->sqrt_k != 0.0) {
      rtb_sincos_o2_idx_0 = autocodePlant_DW->UnitDelay2_DSTATE[1] /
        autocodePlant_B->sqrt_k;
    } else {
      rtb_sincos_o2_idx_0 = autocodePlant_DW->UnitDelay2_DSTATE[3];
    }

    /* End of Switch: '<S269>/Switch' */

    /* Sum: '<S268>/Sum1' incorporates:
     *  Product: '<S268>/Product1'
     *  Product: '<S268>/Product4'
     *  UnitDelay: '<S217>/Unit Delay2'
     */
    rtb_Product3_ax = (0.0 - autocodePlant_B->Product11 *
                       autocodePlant_DW->UnitDelay2_DSTATE[0]) -
      autocodePlant_DW->UnitDelay2_DSTATE[2] * autocodePlant_B->Product12;

    /* Trigonometry: '<S271>/Trigonometric Function1' */
    rtb_Sum2_fl = rt_atan2d_snf(rtb_sincos_o2_idx_0, rtb_Product3_ax);

    /* Sum: '<S270>/Sum1' incorporates:
     *  Product: '<S270>/Product1'
     *  Product: '<S270>/Product4'
     *  UnitDelay: '<S217>/Unit Delay2'
     */
    /* Unit Conversion - from: rad to: deg
       Expression: output = (57.2958*input) + (0) */
    rtb_sincos_o1_idx_1 = autocodePlant_B->Product12 *
      autocodePlant_DW->UnitDelay2_DSTATE[0] -
      autocodePlant_DW->UnitDelay2_DSTATE[2] * autocodePlant_B->Product11;

    /* Sum: '<S271>/Sum' incorporates:
     *  Product: '<S271>/Product'
     *  Product: '<S271>/Product1'
     */
    rtb_sincos_o2_idx_0 = rtb_sincos_o2_idx_0 * rtb_sincos_o2_idx_0 +
      rtb_Product3_ax * rtb_Product3_ax;

    /* UnitConversion: '<S207>/Unit Conversion' incorporates:
     *  Sqrt: '<S271>/sqrt1'
     *  Trigonometry: '<S271>/Trigonometric Function'
     *  UnitConversion: '<S272>/Unit Conversion'
     *  UnitConversion: '<S273>/Unit Conversion'
     */
    /* Unit Conversion - from: rad to: deg
       Expression: output = (57.2958*input) + (0) */
    /* Unit Conversion - from: deg to: rad
       Expression: output = (0.0174533*input) + (0) */
    rtb_Lw_idx_0 = 57.29577951308232 * rtb_Sum2_fl * 0.017453292519943295;
    rtb_Lw_idx_1 = 57.29577951308232 * rt_atan2d_snf(rtb_sincos_o1_idx_1, sqrt
      (rtb_sincos_o2_idx_0)) * 0.017453292519943295;

    /* Sqrt: '<S271>/sqrt' incorporates:
     *  Product: '<S271>/Product2'
     *  Sum: '<S271>/Sum1'
     */
    rtb_sincos_o2_idx_0 = sqrt(rtb_sincos_o1_idx_1 * rtb_sincos_o1_idx_1 +
      rtb_sincos_o2_idx_0);

    /* Product: '<S200>/h1' incorporates:
     *  Trigonometry: '<S200>/sincos'
     */
    rtb_Product3_ax = cos(rtb_Lw_idx_1) * rtb_sincos_o2_idx_0;

    /* Product: '<S200>/x1' incorporates:
     *  Trigonometry: '<S200>/sincos'
     */
    rtb_Sum2_fl = cos(rtb_Lw_idx_0) * rtb_Product3_ax;

    /* Product: '<S200>/y1' incorporates:
     *  Trigonometry: '<S200>/sincos'
     */
    rtb_Product3_ax *= sin(rtb_Lw_idx_0);

    /* Product: '<S200>/z1' incorporates:
     *  Trigonometry: '<S200>/sincos'
     */
    rtb_sincos_o2_idx_0 *= sin(rtb_Lw_idx_1);

    /* Product: '<S106>/Product2' incorporates:
     *  Gain: '<S106>/P0'
     */
    rtb_Product2_l3 *= 101325.0 * rtb_TT0gLR;
    if (tmp) {
      /* SignalConversion generated from: '<S173>/Product' incorporates:
       *  Product: '<S192>/Product4'
       *  Product: '<S192>/Product5'
       *  Product: '<S192>/Product8'
       *  Product: '<S193>/Product4'
       *  Product: '<S193>/Product5'
       *  Product: '<S193>/Product8'
       *  Product: '<S194>/Product4'
       *  Product: '<S194>/Product5'
       *  Product: '<S194>/Product8'
       *  Sum: '<S192>/Sum'
       *  Sum: '<S193>/Sum'
       *  Sum: '<S194>/Sum'
       */
      localProduct = (rtb_Sum * rtb_Sum2_fl + rtb_Sum1_n * rtb_Product3_ax) +
        rtb_VectorConcatenate_tmp * rtb_sincos_o2_idx_0;
      rtb_Switch_d_idx_1 = (rtb_Switch_d_idx_1 * rtb_Product3_ax +
                            rtb_Switch_d_idx_2 * rtb_Sum2_fl) + rtb_Product1_hx *
        rtb_sincos_o2_idx_0;
      rtb_TmpSignalConversionAtProd_0 = (rtb_TmpSignalConversionAtProd_0 *
        rtb_Sum2_fl + rtb_UnaryMinus_a * rtb_Product3_ax) + rtb_Sum_d0 *
        rtb_sincos_o2_idx_0;

      /* ZeroOrderHold: '<S173>/Zero-Order Hold' incorporates:
       *  Constant: '<S173>/hardironBdy_nT'
       *  Constant: '<S173>/soft iron matrix'
       *  Product: '<S173>/Product'
       *  Sum: '<S173>/Sum'
       */
      for (i = 0; i < 3; i++) {
        rtb_ZeroOrderHold[i] = (((rtCP__softironmatrix_Value[i + 3] *
          rtb_Switch_d_idx_1 + rtCP__softironmatrix_Value[i] * localProduct) +
          rtCP__softironmatrix_Value[i + 6] * rtb_TmpSignalConversionAtProd_0) +
          autocodePlant_B->Output[i]) + rtCP__hardironBdy_nT_Value[i];
      }

      /* End of ZeroOrderHold: '<S173>/Zero-Order Hold' */

      /* Gain: '<S185>/Output' incorporates:
       *  RandomNumber: '<S185>/White Noise'
       */
      autocodePlant_B->Output_g = 0.19999999999999998 *
        autocodePlant_DW->NextOutput_e;

      /* ZeroOrderHold: '<S171>/Zero-Order Hold' incorporates:
       *  DiscreteTransferFcn: '<S171>/Discrete Transfer Fcn2'
       *  Sum: '<S171>/Sum1'
       */
      localProduct = (autocodePlant_B->Output_g + rtb_Product2_l3) +
        autocodePlant_DW->DiscreteTransferFcn2_states_h;

      /* Delay: '<S174>/Delay' */
      for (i = 0; i < 6; i++) {
        rtb_Delay[i] = autocodePlant_DW->Delay_DSTATE_o[i];
      }

      /* End of Delay: '<S174>/Delay' */
    }

    /* RateTransition: '<S174>/Rate Transition1' */
    rtb_RelationalOperator = (rtmIsMajorTimeStep(autocodePlant_M) &&
      autocodePlant_M->Timing.TaskCounters.TID[3] == 0);
    if (rtb_RelationalOperator) {
      /* RelationalOperator: '<S174>/Relational Operator' incorporates:
       *  Constant: '<S174>/Constant'
       *  UniformRandomNumber: '<S174>/Uniform Random Number'
       */
      autocodePlant_B->RelationalOperator_f =
        (autocodePlant_DW->UniformRandomNumber_NextOutput >= 0.1);
    }

    if (tmp) {
      /* Switch: '<S174>/Switch' incorporates:
       *  UnitDelay: '<S174>/Unit Delay'
       */
      if (autocodePlant_B->RelationalOperator_f) {
        for (i = 0; i < 6; i++) {
          autocodePlant_DW->UnitDelay_DSTATE_a[i] = rtb_Delay[i];
        }
      }

      /* End of Switch: '<S174>/Switch' */

      /* RateTransition: '<S174>/Rate Transition1' */
      if (rtb_RelationalOperator) {
        autocodePlant_Y_sensor_bus_i->gpsFix_b =
          autocodePlant_DW->RateTransition1_Buffer0;
      }

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Outport: '<Root>/sensor_bus'
       *  UnitDelay: '<S174>/Unit Delay'
       */
      autocodePlant_Y_sensor_bus_i->baroMeas_Pa = localProduct;
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[0] =
        rtb_truth_bus_gyroBiasTrue_rps_;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[0] = rtb_Sum_oc;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[0] = rtb_ZeroOrderHold_c[0];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[0] = rtb_ZeroOrderHold_a[0];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[0] = rtb_ZeroOrderHold[0];
      autocodePlant_Y_sensor_bus_i->velNedMeas_mps[0] =
        autocodePlant_DW->UnitDelay_DSTATE_a[3];
      autocodePlant_Y_sensor_bus_i->gpsLLA_na[0] =
        autocodePlant_DW->UnitDelay_DSTATE_a[0];
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[1] =
        rtb_truth_bus_gyroBiasTrue_rp_0;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[1] =
        rtb_truth_bus_accBiasTrue_mps2_;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[1] = rtb_ZeroOrderHold_c[1];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[1] = rtb_ZeroOrderHold_a[1];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[1] = rtb_ZeroOrderHold[1];
      autocodePlant_Y_sensor_bus_i->velNedMeas_mps[1] =
        autocodePlant_DW->UnitDelay_DSTATE_a[4];
      autocodePlant_Y_sensor_bus_i->gpsLLA_na[1] =
        autocodePlant_DW->UnitDelay_DSTATE_a[1];
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[2] =
        rtb_truth_bus_gyroBiasTrue_rp_1;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[2] =
        rtb_truth_bus_accBiasTrue_mps_0;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[2] = rtb_ZeroOrderHold_c[2];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[2] = rtb_ZeroOrderHold_a[2];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[2] = rtb_ZeroOrderHold[2];
      autocodePlant_Y_sensor_bus_i->velNedMeas_mps[2] =
        autocodePlant_DW->UnitDelay_DSTATE_a[5];
      autocodePlant_Y_sensor_bus_i->gpsLLA_na[2] =
        autocodePlant_DW->UnitDelay_DSTATE_a[2];
    }

    /* Product: '<S162>/Product' */
    autocodePlant_B->Product_h[0] = rtb_Add[0] * (real_T)rtb_max_relop_c;
    autocodePlant_B->Product_h[1] = rtb_Add[1] * (real_T)rtb_max_relop_c;
    autocodePlant_B->Product_h[2] = rtb_Add[2] * (real_T)rtb_max_relop_c;

    /* Outport: '<Root>/plant_bus' incorporates:
     *  BusCreator generated from: '<Root>/plant_bus'
     */
    autocodePlant_Y_plant_bus_e->enviroment_bus.temp_K = rtb_Sum1_k3;
    autocodePlant_Y_plant_bus_e->enviroment_bus.a_mps = rtb_a;
    autocodePlant_Y_plant_bus_e->enviroment_bus.pressure_Pa = rtb_Product2_l3;
    autocodePlant_Y_plant_bus_e->enviroment_bus.rho_kgpm3 = rtb_Product_n;
    autocodePlant_Y_plant_bus_e->enviroment_bus.onRail_b = rtb_Compare_n;
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.aoa_deg = rtb_Gain_l;
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.liftSign_na = rtb_Sign1;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.aoa_deg = rtb_Gain_oa;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.liftSign_na = rtb_Sign1_e;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.aoa_deg = rtb_UnaryMinus1_k4;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.liftSign_na = rtb_Sign1_i;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.aoa_deg = rtb_UnaryMinus1_o;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.liftSign_na = rtb_Product_h5;
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.aoa_deg = rtb_Sum_ls;

    /* Product: '<S161>/Matrix Multiply' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    rtb_truth_bus_gyroBiasTrue_rps_ = 0.0;
    rtb_Sum_oc = 0.0;
    rtb_truth_bus_gyroBiasTrue_rp_0 = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_Product3_ax = rtb_wBdy_rps[i];
      rtb_truth_bus_gyroBiasTrue_rps_ += rtCP__Constant1_Value_fo[3 * i] *
        rtb_Product3_ax;
      rtb_Sum_oc += rtCP__Constant1_Value_fo[3 * i + 1] * rtb_Product3_ax;
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
        rtb_Sum1_a1[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.airspeedFin_mps[i] =
        rtb_Product_fn[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finMoment_Nm[i] =
        rtb_Sum_k[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finForce_N[i] =
        rtb_Sum1_hn[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.airspeedFin_mps[i] =
        rtb_Sum_dj[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finMoment_Nm[i] =
        rtb_Sum_n3[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finForce_N[i] =
        rtb_Sum1_b[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.airspeedFin_mps[i] =
        rtb_Sum_el[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finMoment_Nm[i] =
        rtb_Sum_mu[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finForce_N[i] =
        rtb_Sum1_o5[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.airspeedFin_mps[i] =
        rtb_Sum_aw[i];
      autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyMoment_Nm[i] =
        rtb_finMomentArm_m[i];
      autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyForce_N[i] =
        rtb_Product6_kk[i];
      autocodePlant_Y_plant_bus_e->eom_bus.posNed_m[i] = rtb_Sum1_ju[i];
    }

    /* Product: '<S168>/Element Product' incorporates:
     *  Product: '<S161>/Matrix Multiply'
     */
    rtb_ElementProduct[0] = rtb_wBdy_rps[1] * rtb_truth_bus_gyroBiasTrue_rp_0;
    rtb_ElementProduct[1] = rtb_truth_bus_gyroBiasTrue_rps_ * rtb_wBdy_rps[2];
    rtb_ElementProduct[2] = rtb_wBdy_rps[0] * rtb_Sum_oc;
    rtb_ElementProduct[3] = rtb_Sum_oc * rtb_wBdy_rps[2];
    rtb_ElementProduct[4] = rtb_wBdy_rps[0] * rtb_truth_bus_gyroBiasTrue_rp_0;
    rtb_ElementProduct[5] = rtb_truth_bus_gyroBiasTrue_rps_ * rtb_wBdy_rps[1];

    /* Outport: '<Root>/plant_bus' incorporates:
     *  BusCreator generated from: '<Root>/plant_bus'
     */
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[0] = rtb_Switch_a_idx_0;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[1] = rtb_Switch_a_idx_1;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[2] = rtb_Switch_a_idx_2;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[3] = rtb_Switch_a_idx_3;
    for (i = 0; i < 3; i++) {
      autocodePlant_Y_plant_bus_e->eom_bus.velBdy_mps[i] = rtb_velBdy_mps[i];
      autocodePlant_Y_plant_bus_e->eom_bus.wBdy_rps[i] = rtb_wBdy_rps[i];
      autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[i] = rtb_MathFunction[i];

      /* Sum: '<S161>/Subtract' incorporates:
       *  Product: '<S161>/Matrix Multiply1'
       *  Sum: '<S167>/Add'
       *  Sum: '<S168>/Sum'
       */
      rtb_ZeroOrderHold_a[i] = (autocodePlant_B->Product_h[i] -
        (rtb_ElementProduct[i] - rtb_ElementProduct[i + 3])) -
        ((autocodePlant_ConstB.dIdt[i + 3] * rtb_wBdy_rps[1] +
          autocodePlant_ConstB.dIdt[i] * rtb_wBdy_rps[0]) +
         autocodePlant_ConstB.dIdt[i + 6] * rtb_wBdy_rps[2]);
    }

    /* Product: '<S161>/Product1' incorporates:
     *  Constant: '<S5>/Constant1'
     *  Outport: '<Root>/plant_bus'
     */
    rt_mldivide_U1d3x3_U2d_9O8lG8ax(rtCP__Constant1_Value_fo,
      rtb_ZeroOrderHold_a, autocodePlant_Y_plant_bus_e->eom_bus.wDotBdy_rps2);
    if (tmp) {
      /* Lookup_n-D: '<S6>/1-D Lookup Table' incorporates:
       *  UnitDelay: '<S169>/Unit Delay'
       */
      rtb_uDLookupTable = look1_binlcpw(autocodePlant_DW->UnitDelay_DSTATE_i,
        rtCP__uDLookupTable_bp01Data, rtCP__uDLookupTable_tableData, 25U);

      /* Sum: '<S169>/Sum' incorporates:
       *  Constant: '<S169>/Constant'
       *  UnitDelay: '<S169>/Unit Delay'
       */
      autocodePlant_DW->UnitDelay_DSTATE_i += 0.01;

      /* Gain: '<S184>/Output' incorporates:
       *  RandomNumber: '<S184>/White Noise'
       */
      autocodePlant_B->Output_n = 3.7947521660754644 *
        autocodePlant_DW->NextOutput_m;

      /* Gain: '<S176>/Output' incorporates:
       *  RandomNumber: '<S176>/White Noise'
       */
      autocodePlant_B->Output_o[0] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S186>/Output' incorporates:
       *  RandomNumber: '<S186>/White Noise'
       */
      autocodePlant_B->Output_e[0] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Gain: '<S176>/Output' incorporates:
       *  RandomNumber: '<S176>/White Noise'
       */
      autocodePlant_B->Output_o[1] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S186>/Output' incorporates:
       *  RandomNumber: '<S186>/White Noise'
       */
      autocodePlant_B->Output_e[1] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Gain: '<S176>/Output' incorporates:
       *  RandomNumber: '<S176>/White Noise'
       */
      autocodePlant_B->Output_o[2] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S186>/Output' incorporates:
       *  RandomNumber: '<S186>/White Noise'
       */
      autocodePlant_B->Output_e[2] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Assertion: '<S197>/Assertion' incorporates:
       *  Constant: '<S173>/ground altitude'
       *  Constant: '<S197>/max_val'
       *  Constant: '<S197>/min_val'
       *  FlatEarth2LLA: '<S173>/Flat Earth to LLA'
       *  Logic: '<S197>/conjunction'
       *  RelationalOperator: '<S197>/max_relop'
       *  RelationalOperator: '<S197>/min_relop'
       */
      utAssert((-(rtb_Sum1_ju[2] + 182.0) >= -1000.0) && (-(rtb_Sum1_ju[2] +
                 182.0) <= 850000.0));

      /* Assertion: '<S198>/Assertion' incorporates:
       *  Constant: '<S198>/max_val'
       *  Constant: '<S198>/min_val'
       *  Logic: '<S198>/conjunction'
       *  RelationalOperator: '<S198>/max_relop'
       *  RelationalOperator: '<S198>/min_relop'
       */
      utAssert((rtb_Switch_d_idx_0 >= -90.0) && (rtb_Switch_d_idx_0 <= 90.0));

      /* Assertion: '<S199>/Assertion' incorporates:
       *  Constant: '<S199>/max_val'
       *  Constant: '<S199>/min_val'
       *  Logic: '<S199>/conjunction'
       *  RelationalOperator: '<S199>/max_relop'
       *  RelationalOperator: '<S199>/min_relop'
       */
      utAssert((rtb_FlatEarthtoLLA_o1_idx_1 >= -180.0) &&
               (rtb_FlatEarthtoLLA_o1_idx_1 <= 180.0));

      /* Assertion: '<S201>/Assertion' */
      utAssert(autocodePlant_ConstB.conjunction);
    }

    /* RateTransition: '<S174>/Rate Transition' incorporates:
     *  ZeroOrderHold: '<S174>/Zero-Order Hold'
     */
    rtb_RelationalOperator = (rtmIsMajorTimeStep(autocodePlant_M) &&
      autocodePlant_M->Timing.TaskCounters.TID[2] == 0);
    if (rtb_RelationalOperator) {
      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn' incorporates:
       *  Gain: '<S276>/Output'
       *  RandomNumber: '<S276>/White Noise'
       */
      autocodePlant_DW->DiscreteTransferFcn_tmp = 0.31622776601683794 *
        autocodePlant_DW->NextOutput_h - 0.005 *
        autocodePlant_DW->DiscreteTransferFcn_states_k;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn' */
      autocodePlant_B->DiscreteTransferFcn = 0.0 *
        autocodePlant_DW->DiscreteTransferFcn_states_k +
        autocodePlant_DW->DiscreteTransferFcn_tmp;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn1' incorporates:
       *  Gain: '<S277>/Output'
       *  RandomNumber: '<S277>/White Noise'
       */
      autocodePlant_DW->DiscreteTransferFcn1_tmp = 0.31622776601683794 *
        autocodePlant_DW->NextOutput_md - 0.005 *
        autocodePlant_DW->DiscreteTransferFcn1_states_b;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn1' */
      autocodePlant_B->DiscreteTransferFcn1 = 0.0 *
        autocodePlant_DW->DiscreteTransferFcn1_states_b +
        autocodePlant_DW->DiscreteTransferFcn1_tmp;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn2' incorporates:
       *  Gain: '<S278>/Output'
       *  RandomNumber: '<S278>/White Noise'
       */
      autocodePlant_DW->DiscreteTransferFcn2_tmp = 0.7071067811865475 *
        autocodePlant_DW->NextOutput_av - 0.005 *
        autocodePlant_DW->DiscreteTransferFcn2_states_d;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn2' */
      autocodePlant_B->DiscreteTransferFcn2_b = 0.0 *
        autocodePlant_DW->DiscreteTransferFcn2_states_d +
        autocodePlant_DW->DiscreteTransferFcn2_tmp;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn3' incorporates:
       *  Gain: '<S274>/Output'
       *  RandomNumber: '<S274>/White Noise'
       */
      autocodePlant_DW->DiscreteTransferFcn3_tmp = 0.03162277660168379 *
        autocodePlant_DW->NextOutput_kf - 0.005 *
        autocodePlant_DW->DiscreteTransferFcn3_states_g;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn3' */
      autocodePlant_B->DiscreteTransferFcn3 = 0.0 *
        autocodePlant_DW->DiscreteTransferFcn3_states_g +
        autocodePlant_DW->DiscreteTransferFcn3_tmp;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn4' incorporates:
       *  Gain: '<S275>/Output'
       *  RandomNumber: '<S275>/White Noise'
       */
      autocodePlant_DW->DiscreteTransferFcn4_tmp = 0.03162277660168379 *
        autocodePlant_DW->NextOutput_n - 0.005 *
        autocodePlant_DW->DiscreteTransferFcn4_states;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn4' */
      autocodePlant_B->DiscreteTransferFcn4 = 0.0 *
        autocodePlant_DW->DiscreteTransferFcn4_states +
        autocodePlant_DW->DiscreteTransferFcn4_tmp;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn5' incorporates:
       *  Gain: '<S279>/Output'
       *  RandomNumber: '<S279>/White Noise'
       */
      autocodePlant_DW->DiscreteTransferFcn5_tmp = 0.07071067811865475 *
        autocodePlant_DW->NextOutput_p - 0.005 *
        autocodePlant_DW->DiscreteTransferFcn5_states;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn5' */
      autocodePlant_B->DiscreteTransferFcn5 = 0.0 *
        autocodePlant_DW->DiscreteTransferFcn5_states +
        autocodePlant_DW->DiscreteTransferFcn5_tmp;
    }

    /* Sum: '<S174>/Sum1' */
    rtb_Sum1_ju[0] += autocodePlant_B->DiscreteTransferFcn;
    rtb_Sum1_ju[1] += autocodePlant_B->DiscreteTransferFcn1;

    /* FlatEarth2LLA: '<S174>/Flat Earth to LLA' */
    rtb_Product3_ax = (rtb_Sum1_ju[0] - 0.0 * rtb_Sum1_ju[1]) /
      6.364093718556922E+6 + 0.7340319991259698;
    rtb_Switch_d_idx_0 = fabs(rtb_Product3_ax);
    rtb_FlatEarthtoLLA_o1_idx_1 = (0.0 * rtb_Sum1_ju[0] + rtb_Sum1_ju[1]) /
      4.7427650164783625E+6 - 1.5302472054346188;
    if (rtb_Switch_d_idx_0 > 3.141592653589793) {
      rtb_Product3_ax = rt_modd_snf(rtb_Product3_ax + 3.141592653589793,
        6.283185307179586) - 3.141592653589793;
      rtb_Switch_d_idx_0 = fabs(rtb_Product3_ax);
    }

    if (rtb_Switch_d_idx_0 > 1.5707963267948966) {
      rtb_FlatEarthtoLLA_o1_idx_1 += 3.141592653589793;
      if (rtIsNaN(rtb_Product3_ax)) {
        rtb_Product3_ax = (rtNaN);
      } else if (rtb_Product3_ax < 0.0) {
        rtb_Product3_ax = -1.0;
      } else {
        rtb_Product3_ax = (rtb_Product3_ax > 0.0);
      }

      rtb_Product3_ax *= 1.5707963267948966 - (rtb_Switch_d_idx_0 -
        1.5707963267948966);
    }

    if (fabs(rtb_FlatEarthtoLLA_o1_idx_1) > 3.141592653589793) {
      rtb_Switch_d_idx_0 = rt_remd_snf(rtb_FlatEarthtoLLA_o1_idx_1,
        6.283185307179586);
      rtb_FlatEarthtoLLA_o1_idx_1 = rtb_Switch_d_idx_0 - trunc
        (rtb_Switch_d_idx_0 / 3.141592653589793) * 6.283185307179586;
    }

    autocodePlant_B->FlatEarthtoLLA_o1[0] = rtb_Product3_ax * 180.0 /
      3.141592653589793;
    autocodePlant_B->FlatEarthtoLLA_o1[1] = rtb_FlatEarthtoLLA_o1_idx_1 * 180.0 /
      3.141592653589793;

    /* Switch: '<S282>/Switch' incorporates:
     *  Constant: '<S282>/Constant'
     */
    if (!(rtb_w3 > 1.0E-6)) {
      rtb_Switch_a_idx_0 = 1.0;
      rtb_Switch_a_idx_1 = 0.0;
      rtb_Switch_a_idx_2 = 0.0;
      rtb_Switch_a_idx_3 = 0.0;
    }

    /* End of Switch: '<S282>/Switch' */

    /* Sum: '<S284>/Sum' incorporates:
     *  Product: '<S284>/Product'
     *  Product: '<S284>/Product1'
     *  Product: '<S284>/Product2'
     *  Product: '<S284>/Product3'
     */
    rtb_Sum_oc = ((rtb_Switch_a_idx_0 * rtb_Switch_a_idx_0 + rtb_Switch_a_idx_1 *
                   rtb_Switch_a_idx_1) + rtb_Switch_a_idx_2 * rtb_Switch_a_idx_2)
      + rtb_Switch_a_idx_3 * rtb_Switch_a_idx_3;

    /* Product: '<S280>/Divide' */
    rtb_sincos_o2_idx_0 = rtb_Switch_a_idx_0 / rtb_Sum_oc;

    /* Product: '<S280>/Divide1' incorporates:
     *  UnaryMinus: '<S283>/Unary Minus'
     */
    rtb_Product3_ax = -rtb_Switch_a_idx_1 / rtb_Sum_oc;

    /* Product: '<S280>/Divide2' incorporates:
     *  UnaryMinus: '<S283>/Unary Minus1'
     */
    rtb_Sum2_fl = -rtb_Switch_a_idx_2 / rtb_Sum_oc;

    /* Product: '<S280>/Divide3' incorporates:
     *  UnaryMinus: '<S283>/Unary Minus2'
     */
    rtb_sincos_o1_idx_1 = -rtb_Switch_a_idx_3 / rtb_Sum_oc;

    /* Sqrt: '<S289>/sqrt' incorporates:
     *  Product: '<S290>/Product'
     *  Product: '<S290>/Product1'
     *  Product: '<S290>/Product2'
     *  Product: '<S290>/Product3'
     *  Sum: '<S290>/Sum'
     */
    rtb_Sum_oc = sqrt(((rtb_sincos_o2_idx_0 * rtb_sincos_o2_idx_0 +
                        rtb_Product3_ax * rtb_Product3_ax) + rtb_Sum2_fl *
                       rtb_Sum2_fl) + rtb_sincos_o1_idx_1 * rtb_sincos_o1_idx_1);

    /* Product: '<S285>/Product' */
    rtb_sincos_o2_idx_0 /= rtb_Sum_oc;

    /* Product: '<S285>/Product1' */
    rtb_Product3_ax /= rtb_Sum_oc;

    /* Product: '<S285>/Product2' */
    rtb_Sum2_fl /= rtb_Sum_oc;

    /* Product: '<S285>/Product3' */
    rtb_sincos_o1_idx_1 /= rtb_Sum_oc;

    /* RateTransition: '<S174>/Rate Transition' */
    if (tmp) {
      /* RateTransition: '<S174>/Rate Transition' */
      for (i = 0; i < 6; i++) {
        if (rtb_RelationalOperator) {
          autocodePlant_B->RateTransition[i] =
            autocodePlant_DW->RateTransition_Buffer0[i];
        }
      }

      /* End of RateTransition: '<S174>/Rate Transition' */
    }

    /* ZeroOrderHold: '<S174>/Zero-Order Hold' */
    if (rtb_RelationalOperator) {
      /* ZeroOrderHold: '<S174>/Zero-Order Hold' incorporates:
       *  Constant: '<S174>/Constant1'
       *  FlatEarth2LLA: '<S174>/Flat Earth to LLA'
       *  Sum: '<S174>/Sum1'
       */
      autocodePlant_B->ZeroOrderHold[0] = autocodePlant_B->FlatEarthtoLLA_o1[0];
      autocodePlant_B->ZeroOrderHold[1] = autocodePlant_B->FlatEarthtoLLA_o1[1];
      autocodePlant_B->ZeroOrderHold[2] = -((rtb_Sum1_ju[2] +
        autocodePlant_B->DiscreteTransferFcn2_b) + 182.0);

      /* Product: '<S286>/Product7' incorporates:
       *  Product: '<S287>/Product7'
       */
      rtb_Switch_a_idx_0 = rtb_sincos_o1_idx_1 * rtb_sincos_o1_idx_1;

      /* Product: '<S286>/Product' incorporates:
       *  Product: '<S287>/Product'
       */
      rtb_Switch_a_idx_1 = rtb_Product3_ax * rtb_Sum2_fl;

      /* Product: '<S286>/Product1' incorporates:
       *  Product: '<S287>/Product1'
       */
      rtb_Switch_a_idx_2 = rtb_sincos_o2_idx_0 * rtb_sincos_o1_idx_1;

      /* Product: '<S286>/Product3' incorporates:
       *  Product: '<S288>/Product'
       */
      rtb_Switch_a_idx_3 = rtb_Product3_ax * rtb_sincos_o1_idx_1;

      /* Product: '<S286>/Product2' incorporates:
       *  Product: '<S288>/Product1'
       */
      rtb_truth_bus_gyroBiasTrue_rps_ = rtb_sincos_o2_idx_0 * rtb_Sum2_fl;

      /* Product: '<S286>/Product6' incorporates:
       *  Product: '<S288>/Product7'
       */
      rtb_Sum_oc = rtb_Sum2_fl * rtb_Sum2_fl;

      /* ZeroOrderHold: '<S174>/Zero-Order Hold' incorporates:
       *  Constant: '<S286>/Constant'
       *  Gain: '<S286>/Gain'
       *  Gain: '<S286>/Gain1'
       *  Gain: '<S286>/Gain2'
       *  Product: '<S286>/Product'
       *  Product: '<S286>/Product1'
       *  Product: '<S286>/Product2'
       *  Product: '<S286>/Product3'
       *  Product: '<S286>/Product4'
       *  Product: '<S286>/Product5'
       *  Product: '<S286>/Product6'
       *  Product: '<S286>/Product7'
       *  Product: '<S286>/Product8'
       *  Sum: '<S174>/Sum2'
       *  Sum: '<S286>/Sum'
       *  Sum: '<S286>/Sum1'
       *  Sum: '<S286>/Sum2'
       *  Sum: '<S286>/Sum3'
       */
      autocodePlant_B->ZeroOrderHold[3] = ((((0.5 - rtb_Sum_oc) -
        rtb_Switch_a_idx_0) * 2.0 * rtb_velBdy_mps[0] + (rtb_Switch_a_idx_1 +
        rtb_Switch_a_idx_2) * 2.0 * rtb_velBdy_mps[1]) + (rtb_Switch_a_idx_3 -
        rtb_truth_bus_gyroBiasTrue_rps_) * 2.0 * rtb_velBdy_mps[2]) +
        autocodePlant_B->DiscreteTransferFcn3;

      /* Product: '<S287>/Product3' incorporates:
       *  Product: '<S288>/Product3'
       */
      rtb_truth_bus_gyroBiasTrue_rp_0 = rtb_Sum2_fl * rtb_sincos_o1_idx_1;

      /* Product: '<S287>/Product2' incorporates:
       *  Product: '<S288>/Product2'
       */
      rtb_truth_bus_accBiasTrue_mps2_ = rtb_sincos_o2_idx_0 * rtb_Product3_ax;

      /* Sum: '<S287>/Sum3' incorporates:
       *  Constant: '<S287>/Constant'
       *  Product: '<S287>/Product6'
       *  Sum: '<S288>/Sum3'
       */
      rtb_truth_bus_gyroBiasTrue_rp_1 = 0.5 - rtb_Product3_ax * rtb_Product3_ax;

      /* ZeroOrderHold: '<S174>/Zero-Order Hold' incorporates:
       *  Gain: '<S287>/Gain'
       *  Gain: '<S287>/Gain1'
       *  Gain: '<S287>/Gain2'
       *  Gain: '<S288>/Gain'
       *  Gain: '<S288>/Gain1'
       *  Gain: '<S288>/Gain2'
       *  Product: '<S287>/Product2'
       *  Product: '<S287>/Product3'
       *  Product: '<S287>/Product4'
       *  Product: '<S287>/Product5'
       *  Product: '<S287>/Product8'
       *  Product: '<S288>/Product4'
       *  Product: '<S288>/Product5'
       *  Product: '<S288>/Product8'
       *  Sum: '<S174>/Sum2'
       *  Sum: '<S287>/Sum'
       *  Sum: '<S287>/Sum1'
       *  Sum: '<S287>/Sum2'
       *  Sum: '<S287>/Sum3'
       *  Sum: '<S288>/Sum'
       *  Sum: '<S288>/Sum1'
       *  Sum: '<S288>/Sum2'
       *  Sum: '<S288>/Sum3'
       */
      autocodePlant_B->ZeroOrderHold[4] = (((rtb_truth_bus_gyroBiasTrue_rp_1 -
        rtb_Switch_a_idx_0) * 2.0 * rtb_velBdy_mps[1] + (rtb_Switch_a_idx_1 -
        rtb_Switch_a_idx_2) * 2.0 * rtb_velBdy_mps[0]) +
        (rtb_truth_bus_accBiasTrue_mps2_ + rtb_truth_bus_gyroBiasTrue_rp_0) *
        2.0 * rtb_velBdy_mps[2]) + autocodePlant_B->DiscreteTransferFcn4;
      autocodePlant_B->ZeroOrderHold[5] = (((rtb_Switch_a_idx_3 +
        rtb_truth_bus_gyroBiasTrue_rps_) * 2.0 * rtb_velBdy_mps[0] +
        (rtb_truth_bus_gyroBiasTrue_rp_0 - rtb_truth_bus_accBiasTrue_mps2_) *
        2.0 * rtb_velBdy_mps[1]) + (rtb_truth_bus_gyroBiasTrue_rp_1 - rtb_Sum_oc)
        * 2.0 * rtb_velBdy_mps[2]) + autocodePlant_B->DiscreteTransferFcn5;
    }
  }

/* STM32_CURRENT_SAMPLE_FEEDBACK */
  if (rtmIsMajorTimeStep(autocodePlant_M) && autocodePlant_feedback != NULL) {
    if (!autocodePlant_feedback(autocodePlant_Y_sensor_bus_i,
                                autocodePlant_Y_plant_bus_e,
                                autocodePlant_U_control_deg)) return;
  }

  if (rtmIsMajorTimeStep(autocodePlant_M)) {
    int32_T i;
    boolean_T tmp;
    tmp = (rtmIsMajorTimeStep(autocodePlant_M) &&
           autocodePlant_M->Timing.TaskCounters.TID[1] == 0);
    if (tmp) {
      /* Update for DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn' */
      autocodePlant_DW->DiscreteTransferFcn_states = autocodePlant_B->Output_e[0]
        - 0.99995 * autocodePlant_DW->DiscreteTransferFcn_states;

      /* Update for DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states = autocodePlant_B->Output_e
        [1] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn1_states;

      /* Update for DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states = autocodePlant_B->Output_e
        [2] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn2_states;

      /* Update for DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_k =
        autocodePlant_B->Output_o[0] - 0.99995 *
        autocodePlant_DW->DiscreteTransferFcn2_states_k;

      /* Update for DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states_a =
        autocodePlant_B->Output_o[1] - 0.99995 *
        autocodePlant_DW->DiscreteTransferFcn1_states_a;

      /* Update for DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn3' */
      autocodePlant_DW->DiscreteTransferFcn3_states = autocodePlant_B->Output_o
        [2] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn3_states;

      /* Update for RandomNumber: '<S177>/White Noise' */
      autocodePlant_DW->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed);

      /* Update for Delay: '<S6>/Delay' */
      for (i = 0; i < 1199; i++) {
        autocodePlant_DW->Delay_DSTATE[i] = autocodePlant_DW->Delay_DSTATE[i + 1];
      }

      autocodePlant_DW->Delay_DSTATE[1199] = rtb_uDLookupTable;

      /* End of Update for Delay: '<S6>/Delay' */

      /* Update for RandomNumber: '<S130>/White Noise' */
      autocodePlant_DW->NextOutput_d[0] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[0]);

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE[0] = autocodePlant_U_control_deg[0];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[0] = autocodePlant_B->Backlash[0];

      /* Update for RandomNumber: '<S130>/White Noise' */
      autocodePlant_DW->NextOutput_d[1] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[1]);

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE[1] = autocodePlant_U_control_deg[1];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[1] = autocodePlant_B->Backlash[1];

      /* Update for RandomNumber: '<S130>/White Noise' */
      autocodePlant_DW->NextOutput_d[2] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[2]);

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE[2] = autocodePlant_U_control_deg[2];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[2] = autocodePlant_B->Backlash[2];

      /* Update for RandomNumber: '<S130>/White Noise' */
      autocodePlant_DW->NextOutput_d[3] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[3]);

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE[3] = autocodePlant_U_control_deg[3];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[3] = autocodePlant_B->Backlash[3];

      /* Update for RandomNumber: '<S187>/White Noise' */
      autocodePlant_DW->NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_l);

      /* Update for UnitDelay: '<S172>/Unit Delay' */
      autocodePlant_DW->UnitDelay_DSTATE_c[0] = autocodePlant_B->fBdy_mps2[0];
      autocodePlant_DW->UnitDelay_DSTATE_c[1] = autocodePlant_B->fBdy_mps2[1];
      autocodePlant_DW->UnitDelay_DSTATE_c[2] = autocodePlant_B->fBdy_mps2[2];

      /* Update for RandomNumber: '<S190>/White Noise' */
      autocodePlant_DW->NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_a);

      /* Update for Memory: '<S223>/otime' incorporates:
       *  Constant: '<S173>/decimal year'
       */
      autocodePlant_DW->otime_PreviousInput = 2026.6657534246576;

      /* Update for Memory: '<S222>/olon' */
      autocodePlant_DW->olon_PreviousInput = autocodePlant_B->Switch;

      /* Update for Memory: '<S221>/olat' */
      autocodePlant_DW->olat_PreviousInput = autocodePlant_B->Switch_l;

      /* Update for Memory: '<S221>/oalt' */
      autocodePlant_DW->oalt_PreviousInput = autocodePlant_B->Gain;

      /* Update for RandomNumber: '<S185>/White Noise' */
      autocodePlant_DW->NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_b);

      /* Update for DiscreteTransferFcn: '<S171>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_h =
        autocodePlant_B->Output_n - 0.99998 *
        autocodePlant_DW->DiscreteTransferFcn2_states_h;

      /* Update for Delay: '<S174>/Delay' */
      for (i = 0; i < 84; i++) {
        autocodePlant_DW->Delay_DSTATE_o[i] = autocodePlant_DW->Delay_DSTATE_o[i
          + 6];
      }

      for (i = 0; i < 6; i++) {
        autocodePlant_DW->Delay_DSTATE_o[i + 84] =
          autocodePlant_B->RateTransition[i];
      }

      /* End of Update for Delay: '<S174>/Delay' */
    }

    /* Update for RateTransition: '<S174>/Rate Transition1' */
    if (rtmIsMajorTimeStep(autocodePlant_M) &&
        autocodePlant_M->Timing.TaskCounters.TID[3] == 0) {
      /* Update for UniformRandomNumber: '<S174>/Uniform Random Number' */
      autocodePlant_DW->UniformRandomNumber_NextOutput =
        rt_urand_Upu32_Yd_f_pw_snf(&autocodePlant_DW->RandSeed_j);
      autocodePlant_DW->RateTransition1_Buffer0 =
        autocodePlant_B->RelationalOperator_f;
    }

    /* End of Update for RateTransition: '<S174>/Rate Transition1' */
    if (tmp) {
      /* Update for RandomNumber: '<S176>/White Noise' */
      autocodePlant_DW->NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_p);

      /* Update for RandomNumber: '<S184>/White Noise' */
      autocodePlant_DW->NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_pb);

      /* Update for RandomNumber: '<S186>/White Noise' */
      autocodePlant_DW->NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_pa);
    }

    if (rtmIsMajorTimeStep(autocodePlant_M) &&
        autocodePlant_M->Timing.TaskCounters.TID[2] == 0) {
      /* Update for RandomNumber: '<S274>/White Noise' */
      autocodePlant_DW->NextOutput_kf = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_h);

      /* Update for RandomNumber: '<S275>/White Noise' */
      autocodePlant_DW->NextOutput_n = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_bu);

      /* Update for RandomNumber: '<S276>/White Noise' */
      autocodePlant_DW->NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_c);

      /* Update for RandomNumber: '<S277>/White Noise' */
      autocodePlant_DW->NextOutput_md = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_m);

      /* Update for RandomNumber: '<S278>/White Noise' */
      autocodePlant_DW->NextOutput_av = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_e);

      /* Update for RandomNumber: '<S279>/White Noise' */
      autocodePlant_DW->NextOutput_p = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_eu);

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn' */
      autocodePlant_DW->DiscreteTransferFcn_states_k =
        autocodePlant_DW->DiscreteTransferFcn_tmp;

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states_b =
        autocodePlant_DW->DiscreteTransferFcn1_tmp;

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_d =
        autocodePlant_DW->DiscreteTransferFcn2_tmp;

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn3' */
      autocodePlant_DW->DiscreteTransferFcn3_states_g =
        autocodePlant_DW->DiscreteTransferFcn3_tmp;

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn4' */
      autocodePlant_DW->DiscreteTransferFcn4_states =
        autocodePlant_DW->DiscreteTransferFcn4_tmp;

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn5' */
      autocodePlant_DW->DiscreteTransferFcn5_states =
        autocodePlant_DW->DiscreteTransferFcn5_tmp;

      /* Update for RateTransition: '<S174>/Rate Transition' */
      for (i = 0; i < 6; i++) {
        autocodePlant_DW->RateTransition_Buffer0[i] =
          autocodePlant_B->ZeroOrderHold[i];
      }

      /* End of Update for RateTransition: '<S174>/Rate Transition' */
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

    rate_scheduler(autocodePlant_M);
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

  /* Derivatives for Enabled SubSystem: '<S120>/Hpgw' */
  if (autocodePlant_DW->Hpgw_MODE) {
    /* Derivatives for Integrator: '<S131>/pgw_p' */
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

  /* End of Derivatives for SubSystem: '<S120>/Hpgw' */

  /* Derivatives for Enabled SubSystem: '<S121>/Hwgw(s)' */
  if (autocodePlant_DW->Hwgws_MODE) {
    /* Derivatives for Integrator: '<S136>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[0] = autocodePlant_B->w[0];

    /* Derivatives for Integrator: '<S136>/wg_p2' */
    _rtXdot->wg_p2_CSTATE[0] = autocodePlant_B->w_h[0];

    /* Derivatives for Integrator: '<S136>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[1] = autocodePlant_B->w[1];

    /* Derivatives for Integrator: '<S136>/wg_p2' */
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

  /* End of Derivatives for SubSystem: '<S121>/Hwgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S120>/Hqgw' */
  if (autocodePlant_DW->Hqgw_MODE) {
    /* Derivatives for Integrator: '<S132>/qgw_p' */
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

  /* End of Derivatives for SubSystem: '<S120>/Hqgw' */

  /* Derivatives for Enabled SubSystem: '<S121>/Hvgw(s)' */
  if (autocodePlant_DW->Hvgws_MODE) {
    /* Derivatives for Integrator: '<S135>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[0] = autocodePlant_B->w_c[0];

    /* Derivatives for Integrator: '<S135>/vgw_p2' */
    _rtXdot->vgw_p2_CSTATE[0] = autocodePlant_B->w_j[0];

    /* Derivatives for Integrator: '<S135>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[1] = autocodePlant_B->w_c[1];

    /* Derivatives for Integrator: '<S135>/vgw_p2' */
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

  /* End of Derivatives for SubSystem: '<S121>/Hvgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S120>/Hrgw' */
  if (autocodePlant_DW->Hrgw_MODE) {
    /* Derivatives for Integrator: '<S133>/rgw_p' */
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

  /* End of Derivatives for SubSystem: '<S120>/Hrgw' */

  /* Derivatives for Enabled SubSystem: '<S121>/Hugw(s)' */
  if (autocodePlant_DW->Hugws_MODE) {
    /* Derivatives for Integrator: '<S134>/ug_p' */
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

  /* End of Derivatives for SubSystem: '<S121>/Hugw(s)' */
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

    /* Start for If: '<S125>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = -1;

    /* Start for If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f = -1;

    /* Start for If: '<S211>/If' */
    autocodePlant_DW->If_ActiveSubsystem = -1;

    /* InitializeConditions for RandomNumber: '<S177>/White Noise' */
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
    autocodePlant_X->uDOFQuaternion_CSTATE[9] = -0.5131192175459772;
    autocodePlant_X->uDOFQuaternion_CSTATE[10] = -0.43219435473128404;
    autocodePlant_X->uDOFQuaternion_CSTATE[11] = -0.5671791957001987;
    autocodePlant_X->uDOFQuaternion_CSTATE[12] = 0.4777284461786727;

    /* InitializeConditions for RandomNumber: '<S130>/White Noise' */
    autocodePlant_DW->RandSeed_i[0] = 1529675776U;
    autocodePlant_DW->NextOutput_d[0] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[0]);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[0] = 0.0;

    /* InitializeConditions for RandomNumber: '<S130>/White Noise' */
    autocodePlant_DW->RandSeed_i[1] = 1529741312U;
    autocodePlant_DW->NextOutput_d[1] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[1]);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[1] = 0.0;

    /* InitializeConditions for RandomNumber: '<S130>/White Noise' */
    autocodePlant_DW->RandSeed_i[2] = 1529806848U;
    autocodePlant_DW->NextOutput_d[2] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[2]);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[2] = 0.0;

    /* InitializeConditions for RandomNumber: '<S130>/White Noise' */
    autocodePlant_DW->RandSeed_i[3] = 1529872384U;
    autocodePlant_DW->NextOutput_d[3] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[3]);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[3] = 0.0;

    /* InitializeConditions for RandomNumber: '<S187>/White Noise' */
    autocodePlant_DW->RandSeed_l = 1529675776U;
    autocodePlant_DW->NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_l);

    /* InitializeConditions for RandomNumber: '<S190>/White Noise' */
    autocodePlant_DW->RandSeed_a = 1529675776U;
    autocodePlant_DW->NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_a);

    /* InitializeConditions for Memory: '<S223>/otime' */
    autocodePlant_DW->otime_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S222>/olon' */
    autocodePlant_DW->olon_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S221>/olat' */
    autocodePlant_DW->olat_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S221>/oalt' */
    autocodePlant_DW->oalt_PreviousInput = -1000.0;

    /* InitializeConditions for RandomNumber: '<S185>/White Noise' */
    autocodePlant_DW->RandSeed_b = 1529675776U;
    autocodePlant_DW->NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_b);

    /* InitializeConditions for UniformRandomNumber: '<S174>/Uniform Random Number' */
    autocodePlant_DW->RandSeed_j = 1144108930U;
    autocodePlant_DW->UniformRandomNumber_NextOutput =
      rt_urand_Upu32_Yd_f_pw_snf(&autocodePlant_DW->RandSeed_j);

    /* InitializeConditions for RandomNumber: '<S176>/White Noise' */
    autocodePlant_DW->RandSeed_p = 1529675776U;
    autocodePlant_DW->NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_p);

    /* InitializeConditions for RandomNumber: '<S184>/White Noise' */
    autocodePlant_DW->RandSeed_pb = 1529675776U;
    autocodePlant_DW->NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_pb);

    /* InitializeConditions for RandomNumber: '<S186>/White Noise' */
    autocodePlant_DW->RandSeed_pa = 1529675776U;
    autocodePlant_DW->NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_pa);

    /* InitializeConditions for RandomNumber: '<S274>/White Noise' */
    autocodePlant_DW->RandSeed_h = 196608U;
    autocodePlant_DW->NextOutput_kf = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_h);

    /* InitializeConditions for RandomNumber: '<S275>/White Noise' */
    autocodePlant_DW->RandSeed_bu = 262144U;
    autocodePlant_DW->NextOutput_n = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_bu);

    /* InitializeConditions for RandomNumber: '<S276>/White Noise' */
    autocodePlant_DW->RandSeed_c = 1144108930U;
    autocodePlant_DW->NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_c);

    /* InitializeConditions for RandomNumber: '<S277>/White Noise' */
    autocodePlant_DW->RandSeed_m = 65536U;
    autocodePlant_DW->NextOutput_md = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_m);

    /* InitializeConditions for RandomNumber: '<S278>/White Noise' */
    autocodePlant_DW->RandSeed_e = 131072U;
    autocodePlant_DW->NextOutput_av = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_e);

    /* InitializeConditions for RandomNumber: '<S279>/White Noise' */
    autocodePlant_DW->RandSeed_eu = 327680U;
    autocodePlant_DW->NextOutput_p = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_eu);

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hpgw' */
    /* InitializeConditions for Integrator: '<S131>/pgw_p' */
    autocodePlant_X->pgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hpgw' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hwgw(s)' */
    /* InitializeConditions for Integrator: '<S136>/wg_p1' */
    autocodePlant_X->wg_p1_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S136>/wg_p2' */
    autocodePlant_X->wg_p2_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hwgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hqgw' */
    /* InitializeConditions for Integrator: '<S132>/qgw_p' */
    autocodePlant_X->qgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hqgw' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hvgw(s)' */
    /* InitializeConditions for Integrator: '<S135>/vg_p1' */
    autocodePlant_X->vg_p1_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S135>/vgw_p2' */
    autocodePlant_X->vgw_p2_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hvgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hrgw' */
    /* InitializeConditions for Integrator: '<S133>/rgw_p' */
    autocodePlant_X->rgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hrgw' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hugw(s)' */
    /* InitializeConditions for Integrator: '<S134>/ug_p' */
    autocodePlant_X->ug_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hugw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hpgw' */
    /* InitializeConditions for Integrator: '<S131>/pgw_p' */
    autocodePlant_X->pgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hpgw' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hwgw(s)' */
    /* InitializeConditions for Integrator: '<S136>/wg_p1' */
    autocodePlant_X->wg_p1_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S136>/wg_p2' */
    autocodePlant_X->wg_p2_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hwgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hqgw' */
    /* InitializeConditions for Integrator: '<S132>/qgw_p' */
    autocodePlant_X->qgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hqgw' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hvgw(s)' */
    /* InitializeConditions for Integrator: '<S135>/vg_p1' */
    autocodePlant_X->vg_p1_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S135>/vgw_p2' */
    autocodePlant_X->vgw_p2_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hvgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hrgw' */
    /* InitializeConditions for Integrator: '<S133>/rgw_p' */
    autocodePlant_X->rgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hrgw' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hugw(s)' */
    /* InitializeConditions for Integrator: '<S134>/ug_p' */
    autocodePlant_X->ug_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hugw(s)' */

    /* SystemInitialize for Merge: '<S211>/Merge' */
    autocodePlant_B->Merge = 1.0;

    /* SystemInitialize for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates ' */
    /* SystemInitialize for Iterator SubSystem: '<S219>/For Iterator Subsystem' */
    /* SystemInitialize for Assignment: '<S266>/Assignment' incorporates:
     *  Outport: '<S266>/sp[11]'
     */
    memcpy(&autocodePlant_B->Assignment[0], &rtCP__sp11_Y0[0], 11U * sizeof
           (real_T));

    /* SystemInitialize for Assignment: '<S266>/Assignment1' incorporates:
     *  Outport: '<S266>/cp[11]'
     */
    memcpy(&autocodePlant_B->Assignment1[0], &rtCP__cp11_Y0[0], 11U * sizeof
           (real_T));

    /* End of SystemInitialize for SubSystem: '<S219>/For Iterator Subsystem' */

    /* SystemInitialize for SignalConversion generated from: '<S219>/sp[13]' incorporates:
     *  Outport: '<S219>/sp[13]'
     */
    memcpy(&autocodePlant_B->OutportBufferForsp13[0], &rtCP__sp13_Y0[0], 13U *
           sizeof(real_T));

    /* SystemInitialize for SignalConversion generated from: '<S219>/cp[13]' incorporates:
     *  Outport: '<S219>/cp[13]'
     */
    memcpy(&autocodePlant_B->OutportBufferForcp13[0], &rtCP__cp13_Y0[0], 13U *
           sizeof(real_T));

    /* End of SystemInitialize for SubSystem: '<S206>/Convert from geodetic to  spherical coordinates ' */

    /* SystemInitialize for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' */
    /* SystemInitialize for Sqrt: '<S218>/sqrt' incorporates:
     *  Outport: '<S218>/r'
     */
    autocodePlant_B->sqrt_b = 6378.137;

    /* SystemInitialize for Product: '<S259>/Product4' incorporates:
     *  Outport: '<S218>/ct'
     */
    autocodePlant_B->Product4 = 1.0;

    /* End of SystemInitialize for SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' */

    /* SystemInitialize for Iterator SubSystem: '<S206>/Compute magnetic vector in spherical coordinates' */
    /* InitializeConditions for UnitDelay: '<S217>/Unit Delay2' */
    autocodePlant_DW->UnitDelay2_DSTATE[0] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[1] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[2] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[3] = 0.0;

    /* SystemInitialize for Iterator SubSystem: '<S217>/For Iterator Subsystem' */
    /* SystemInitialize for Enabled SubSystem: '<S225>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */
    /* SystemInitialize for Merge: '<S227>/Merge' */
    autocodePlant_B->Merge_b = 0.0;

    /* SystemInitialize for Merge: '<S227>/Merge1' */
    autocodePlant_B->Merge1_i = 0.0;

    /* InitializeConditions for UnitDelay: '<S227>/Unit Delay1' */
    memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_c[0],
           &rtCP__UnitDelay1_InitialCondi_n[0], 169U * sizeof(real_T));

    /* SystemInitialize for Assignment: '<S227>/Assignment_snorm' incorporates:
     *  Outport: '<S227>/snorm[169]'
     */
    memcpy(&autocodePlant_B->Assignment_snorm[0], &rtCP__snorm169_Y0[0], 169U *
           sizeof(real_T));

    /* End of SystemInitialize for SubSystem: '<S225>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */

    /* SystemInitialize for Enabled SubSystem: '<S226>/Special case - North//South Geographic Pole' */
    /* SystemInitialize for IfAction SubSystem: '<S229>/If Action Subsystem2' */
    /* SystemInitialize for IfAction SubSystem: '<S229>/If Action Subsystem1' */
    for (i = 0; i < 13; i++) {
      /* InitializeConditions for UnitDelay: '<S229>/Unit Delay1' */
      autocodePlant_DW->UnitDelay1_DSTATE_b[i] = 1.0;

      /* SystemInitialize for Assignment: '<S233>/Assignment2' incorporates:
       *  Outport: '<S233>/pp[13]'
       */
      autocodePlant_B->Assignment2_m[i] = 1.0;

      /* SystemInitialize for Assignment: '<S234>/Assignment2' incorporates:
       *  Outport: '<S234>/pp[13]'
       */
      autocodePlant_B->Assignment2_a[i] = 1.0;
    }

    /* End of SystemInitialize for SubSystem: '<S229>/If Action Subsystem1' */
    /* End of SystemInitialize for SubSystem: '<S229>/If Action Subsystem2' */
    /* End of SystemInitialize for SubSystem: '<S226>/Special case - North//South Geographic Pole' */
    /* End of SystemInitialize for SubSystem: '<S217>/For Iterator Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S206>/Compute magnetic vector in spherical coordinates' */
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
