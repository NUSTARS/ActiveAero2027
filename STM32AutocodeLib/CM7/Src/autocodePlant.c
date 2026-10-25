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
 * C/C++ source code generated on : Wed Oct 14 21:16:03 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M7 (MPS2)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "autocodePlant.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rt_powd_snf.h"
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
#include "plook_binx.h"
#include "intrp3d_l_pw.h"
#include "look2_binlcpw.h"
#include "look2_binlxpw.h"
#include "mul_s32_sat.h"
#include "plook_bincpa.h"
#include "intrp2d_la_pw.h"
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
  0.0                                  /* baroMeas_Pa */
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
    real_T rtb_ElementProduct[6];
    real_T Gdependent[3];
    real_T biasnoise_d[3];
    real_T rtb_MathFunction[3];
    real_T rtb_Product6_f[3];
    real_T rtb_Sum1_b[3];
    real_T rtb_Sum1_lp[3];
    real_T rtb_Sum1_ny[3];
    real_T rtb_Sum1_p2[3];
    real_T rtb_Sum_bq[3];
    real_T rtb_Sum_cu[3];
    real_T rtb_Sum_j[3];
    real_T rtb_Sum_jl[3];
    real_T rtb_Sum_kx[3];
    real_T rtb_Sum_l4[3];
    real_T rtb_Sum_ls[3];
    real_T rtb_Sum_pc[3];
    real_T rtb_Switch_f[3];
    real_T rtb_ZeroOrderHold_a[3];
    real_T rtb_ZeroOrderHold_c[3];
    real_T rtb_airspeed_mps[3];
    real_T rtb_finMomentArm_m[3];
    real_T rtb_gravityForceBdy_N[3];
    real_T rtb_posNed_m[3];
    real_T rtb_velBdy_mps[3];
    real_T rtb_wBdy_rps[3];
    real_T frac[2];
    real_T rtb_Gain_c;
    real_T rtb_Gain_e;
    real_T rtb_Gain_ii;
    real_T rtb_Gain_l;
    real_T rtb_Gain_oa;
    real_T rtb_LowAltitudeScaleLength;
    real_T rtb_PreLookUpIndexSearchaltit_0;
    real_T rtb_PreLookUpIndexSearchaltit_1;
    real_T rtb_PreLookUpIndexSearchaltit_2;
    real_T rtb_PreLookUpIndexSearchaltit_3;
    real_T rtb_Product1_kn;
    real_T rtb_Product2_e;
    real_T rtb_Product2_f;
    real_T rtb_Product3_ax;
    real_T rtb_Product_iw;
    real_T rtb_Product_kd;
    real_T rtb_Sign1;
    real_T rtb_Sign1_b;
    real_T rtb_Sign1_e;
    real_T rtb_Sign1_oh;
    real_T rtb_Sum;
    real_T rtb_Sum1_oo;
    real_T rtb_Sum1_ox;
    real_T rtb_Switch_d_idx_0;
    real_T rtb_Switch_d_idx_1;
    real_T rtb_Switch_d_idx_2;
    real_T rtb_TT0gLR;
    real_T rtb_TmpSignalConversionAtProd_0;
    real_T rtb_UnaryMinus_a;
    real_T rtb_a;
    real_T rtb_q_na_idx_0;
    real_T rtb_q_na_idx_1;
    real_T rtb_q_na_idx_2;
    real_T rtb_q_na_idx_3;
    real_T rtb_sigma_ugsigma_vg;
    real_T rtb_truth_bus_accBiasTrue_mps2_;
    real_T rtb_truth_bus_accBiasTrue_mps_0;
    real_T rtb_truth_bus_gyroBiasTrue_rps_;
    real_T rtb_ug_p_idx_0;
    real_T rtb_w3;
    int32_T Merge_b_tmp;
    int32_T i;
    int32_T rtb_Sum2_d;
    int32_T s208_iter;
    int32_T s249_iter;
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

    /* Outputs for Enabled SubSystem: '<S105>/Hugw(s)' incorporates:
     *  EnablePort: '<S118>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S104>/Hrgw' incorporates:
     *  EnablePort: '<S117>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S105>/Hvgw(s)' incorporates:
     *  EnablePort: '<S119>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S104>/Hqgw' incorporates:
     *  EnablePort: '<S116>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S105>/Hwgw(s)' incorporates:
     *  EnablePort: '<S120>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S104>/Hpgw' incorporates:
     *  EnablePort: '<S115>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S189>/Convert from geodetic to  spherical coordinates' incorporates:
     *  EnablePort: '<S201>/Enable'
     */
    tmp = (rtmIsMajorTimeStep(autocodePlant_M) &&
           autocodePlant_M->Timing.TaskCounters.TID[1] == 0);

    /* End of Outputs for SubSystem: '<S189>/Convert from geodetic to  spherical coordinates' */
    /* End of Outputs for SubSystem: '<S104>/Hpgw' */
    /* End of Outputs for SubSystem: '<S105>/Hwgw(s)' */
    /* End of Outputs for SubSystem: '<S104>/Hqgw' */
    /* End of Outputs for SubSystem: '<S105>/Hvgw(s)' */
    /* End of Outputs for SubSystem: '<S104>/Hrgw' */
    /* End of Outputs for SubSystem: '<S105>/Hugw(s)' */
    if (tmp) {
      /* Sum: '<S156>/bias' incorporates:
       *  Constant: '<S156>/  '
       *  DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn'
       *  DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn2'
       */
      rtb_ZeroOrderHold_a[0] = autocodePlant_DW->DiscreteTransferFcn_states +
        0.007805089418666159;
      rtb_ZeroOrderHold_a[1] = autocodePlant_DW->DiscreteTransferFcn1_states +
        0.007805089418666159;
      rtb_ZeroOrderHold_a[2] = autocodePlant_DW->DiscreteTransferFcn2_states +
        0.007805089418666159;

      /* Sum: '<S154>/bias' incorporates:
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn2'
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn3'
       */
      rtb_ZeroOrderHold_c[0] = autocodePlant_DW->DiscreteTransferFcn2_states_k -
        0.01056034519496827;
      rtb_ZeroOrderHold_c[1] = autocodePlant_DW->DiscreteTransferFcn1_states_a -
        0.01056034519496827;
      rtb_ZeroOrderHold_c[2] = autocodePlant_DW->DiscreteTransferFcn3_states -
        0.01056034519496827;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S156>/  '
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn2'
       *  DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn'
       *  Sum: '<S154>/bias'
       *  Sum: '<S156>/bias'
       */
      rtb_w3 = autocodePlant_DW->DiscreteTransferFcn_states +
        0.007805089418666159;
      rtb_sigma_ugsigma_vg = autocodePlant_DW->DiscreteTransferFcn2_states_k -
        0.01056034519496827;

      /* Sum: '<S154>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn2'
       *  Gain: '<S160>/Output'
       *  RandomNumber: '<S160>/White Noise'
       *  Sum: '<S154>/bias'
       */
      autocodePlant_B->biasnoise[0] =
        (autocodePlant_DW->DiscreteTransferFcn2_states_k - 0.01056034519496827)
        + 0.0073574999999999995 * autocodePlant_DW->NextOutput;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S156>/  '
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn1'
       *  Sum: '<S154>/bias'
       *  Sum: '<S156>/bias'
       */
      rtb_LowAltitudeScaleLength = autocodePlant_DW->DiscreteTransferFcn1_states
        + 0.007805089418666159;
      rtb_truth_bus_accBiasTrue_mps2_ =
        autocodePlant_DW->DiscreteTransferFcn1_states_a - 0.01056034519496827;

      /* Sum: '<S154>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn1'
       *  Gain: '<S160>/Output'
       *  RandomNumber: '<S160>/White Noise'
       *  Sum: '<S154>/bias'
       */
      autocodePlant_B->biasnoise[1] =
        (autocodePlant_DW->DiscreteTransferFcn1_states_a - 0.01056034519496827)
        + 0.0073574999999999995 * autocodePlant_DW->NextOutput;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  Constant: '<S156>/  '
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn3'
       *  DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn2'
       *  Sum: '<S154>/bias'
       *  Sum: '<S156>/bias'
       */
      rtb_truth_bus_gyroBiasTrue_rps_ =
        autocodePlant_DW->DiscreteTransferFcn2_states + 0.007805089418666159;
      rtb_truth_bus_accBiasTrue_mps_0 =
        autocodePlant_DW->DiscreteTransferFcn3_states - 0.01056034519496827;

      /* Sum: '<S154>/bias + noise' incorporates:
       *  DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn3'
       *  Gain: '<S160>/Output'
       *  RandomNumber: '<S160>/White Noise'
       *  Sum: '<S154>/bias'
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

    /* RelationalOperator: '<S83>/Compare' incorporates:
     *  Constant: '<S83>/Constant'
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    rtb_Compare_n = (-autocodePlant_X->uDOFQuaternion_CSTATE[5] <= 4.0);

    /* Sqrt: '<S99>/sqrt' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S100>/Product'
     *  Product: '<S100>/Product1'
     *  Product: '<S100>/Product2'
     *  Product: '<S100>/Product3'
     *  Sum: '<S100>/Sum'
     */
    rtb_TT0gLR = sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
                        autocodePlant_X->uDOFQuaternion_CSTATE[9] +
                        autocodePlant_X->uDOFQuaternion_CSTATE[10] *
                        autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
                       autocodePlant_X->uDOFQuaternion_CSTATE[11] *
                       autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
                      autocodePlant_X->uDOFQuaternion_CSTATE[12] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[12]);

    /* Product: '<S95>/Product2' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Sign1 = autocodePlant_X->uDOFQuaternion_CSTATE[11] / rtb_TT0gLR;

    /* Product: '<S95>/Product3' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Sign1_e = autocodePlant_X->uDOFQuaternion_CSTATE[12] / rtb_TT0gLR;

    /* Product: '<S95>/Product1' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Gain_l = autocodePlant_X->uDOFQuaternion_CSTATE[10] / rtb_TT0gLR;

    /* Product: '<S95>/Product' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_TT0gLR = autocodePlant_X->uDOFQuaternion_CSTATE[9] / rtb_TT0gLR;

    /* Product: '<S96>/Product7' incorporates:
     *  Product: '<S97>/Product7'
     */
    rtb_Sum1_oo = rtb_Sign1_e * rtb_Sign1_e;

    /* Product: '<S96>/Product' incorporates:
     *  Product: '<S97>/Product'
     */
    rtb_a = rtb_Gain_l * rtb_Sign1;

    /* Product: '<S96>/Product1' incorporates:
     *  Product: '<S97>/Product1'
     */
    rtb_Gain_oa = rtb_TT0gLR * rtb_Sign1_e;

    /* Product: '<S96>/Product3' incorporates:
     *  Product: '<S98>/Product'
     */
    rtb_Product2_f = rtb_Gain_l * rtb_Sign1_e;

    /* Product: '<S96>/Product2' incorporates:
     *  Product: '<S98>/Product1'
     */
    rtb_Product_iw = rtb_TT0gLR * rtb_Sign1;

    /* Product: '<S96>/Product6' incorporates:
     *  Product: '<S98>/Product7'
     */
    rtb_Sign1_oh = rtb_Sign1 * rtb_Sign1;

    /* Gain: '<S4>/mass' incorporates:
     *  Constant: '<S4>/gNed_mps2'
     *  Constant: '<S96>/Constant'
     *  Gain: '<S96>/Gain'
     *  Gain: '<S96>/Gain1'
     *  Gain: '<S96>/Gain2'
     *  Product: '<S96>/Product'
     *  Product: '<S96>/Product1'
     *  Product: '<S96>/Product2'
     *  Product: '<S96>/Product3'
     *  Product: '<S96>/Product4'
     *  Product: '<S96>/Product5'
     *  Product: '<S96>/Product6'
     *  Product: '<S96>/Product7'
     *  Product: '<S96>/Product8'
     *  Sum: '<S96>/Sum'
     *  Sum: '<S96>/Sum1'
     *  Sum: '<S96>/Sum2'
     *  Sum: '<S96>/Sum3'
     */
    rtb_gravityForceBdy_N[0] = ((((0.5 - rtb_Sign1_oh) - rtb_Sum1_oo) * 2.0 *
      0.0 + (rtb_a + rtb_Gain_oa) * 2.0 * 0.0) + (rtb_Product2_f -
      rtb_Product_iw) * 2.0 * 9.81) * 18.0;

    /* Product: '<S97>/Product3' incorporates:
     *  Product: '<S98>/Product3'
     */
    rtb_Sign1 *= rtb_Sign1_e;

    /* Product: '<S97>/Product2' incorporates:
     *  Product: '<S98>/Product2'
     */
    rtb_TT0gLR *= rtb_Gain_l;

    /* Sum: '<S97>/Sum3' incorporates:
     *  Constant: '<S97>/Constant'
     *  Product: '<S97>/Product6'
     *  Sum: '<S98>/Sum3'
     */
    rtb_Gain_l = 0.5 - rtb_Gain_l * rtb_Gain_l;

    /* Gain: '<S4>/mass' incorporates:
     *  Constant: '<S4>/gNed_mps2'
     *  Gain: '<S97>/Gain'
     *  Gain: '<S97>/Gain1'
     *  Gain: '<S97>/Gain2'
     *  Gain: '<S98>/Gain'
     *  Gain: '<S98>/Gain1'
     *  Gain: '<S98>/Gain2'
     *  Product: '<S97>/Product2'
     *  Product: '<S97>/Product3'
     *  Product: '<S97>/Product4'
     *  Product: '<S97>/Product5'
     *  Product: '<S97>/Product8'
     *  Product: '<S98>/Product4'
     *  Product: '<S98>/Product5'
     *  Product: '<S98>/Product8'
     *  Sum: '<S97>/Sum'
     *  Sum: '<S97>/Sum1'
     *  Sum: '<S97>/Sum2'
     *  Sum: '<S97>/Sum3'
     *  Sum: '<S98>/Sum'
     *  Sum: '<S98>/Sum1'
     *  Sum: '<S98>/Sum2'
     *  Sum: '<S98>/Sum3'
     */
    rtb_gravityForceBdy_N[1] = (((rtb_Gain_l - rtb_Sum1_oo) * 2.0 * 0.0 + (rtb_a
      - rtb_Gain_oa) * 2.0 * 0.0) + (rtb_TT0gLR + rtb_Sign1) * 2.0 * 9.81) *
      18.0;
    rtb_gravityForceBdy_N[2] = (((rtb_Product2_f + rtb_Product_iw) * 2.0 * 0.0 +
      (rtb_Sign1 - rtb_TT0gLR) * 2.0 * 0.0) + (rtb_Gain_l - rtb_Sign1_oh) * 2.0 *
      9.81) * 18.0;

    /* Quat2Dcm: '<S86>/Quaternions to  Direction Cosine Matrix' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Switch_d_idx_1 = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
      autocodePlant_X->uDOFQuaternion_CSTATE[9] +
      autocodePlant_X->uDOFQuaternion_CSTATE[10] *
      autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[11] *
      autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[12] *
      autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
      autocodePlant_X->uDOFQuaternion_CSTATE[10];
    rtb_Switch_d_idx_2 = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
      autocodePlant_X->uDOFQuaternion_CSTATE[9] +
      autocodePlant_X->uDOFQuaternion_CSTATE[10] *
      autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[11] *
      autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[12] *
      autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
      autocodePlant_X->uDOFQuaternion_CSTATE[11];
    rtb_Product2_e = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
      autocodePlant_X->uDOFQuaternion_CSTATE[9] +
      autocodePlant_X->uDOFQuaternion_CSTATE[10] *
      autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[11] *
      autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[12] *
      autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
      autocodePlant_X->uDOFQuaternion_CSTATE[12];
    rtb_Gain_l = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
      autocodePlant_X->uDOFQuaternion_CSTATE[9] +
      autocodePlant_X->uDOFQuaternion_CSTATE[10] *
      autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[11] *
      autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[12] *
      autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
      autocodePlant_X->uDOFQuaternion_CSTATE[9];
    rtb_Sum1_oo = rtb_Gain_l * rtb_Gain_l;
    rtb_a = rtb_Switch_d_idx_1 * rtb_Switch_d_idx_1;
    rtb_TT0gLR = rtb_Switch_d_idx_2 * rtb_Switch_d_idx_2;
    rtb_Sign1 = rtb_Product2_e * rtb_Product2_e;
    rtb_QuaternionstoDirectionCosin[0] = ((rtb_Sum1_oo + rtb_a) - rtb_TT0gLR) -
      rtb_Sign1;
    rtb_Gain_oa = rtb_Switch_d_idx_1 * rtb_Switch_d_idx_2;
    rtb_Product2_f = rtb_Gain_l * rtb_Product2_e;
    rtb_QuaternionstoDirectionCosin[3] = (rtb_Gain_oa + rtb_Product2_f) * 2.0;
    rtb_Product_iw = rtb_Switch_d_idx_1 * rtb_Product2_e;
    rtb_Sign1_e = rtb_Gain_l * rtb_Switch_d_idx_2;
    rtb_QuaternionstoDirectionCosin[6] = (rtb_Product_iw - rtb_Sign1_e) * 2.0;
    rtb_QuaternionstoDirectionCosin[1] = (rtb_Gain_oa - rtb_Product2_f) * 2.0;
    rtb_Sum1_oo -= rtb_a;
    rtb_QuaternionstoDirectionCosin[4] = (rtb_Sum1_oo + rtb_TT0gLR) - rtb_Sign1;
    rtb_a = rtb_Switch_d_idx_2 * rtb_Product2_e;
    rtb_Gain_oa = rtb_Gain_l * rtb_Switch_d_idx_1;
    rtb_QuaternionstoDirectionCosin[7] = (rtb_a + rtb_Gain_oa) * 2.0;
    rtb_QuaternionstoDirectionCosin[2] = (rtb_Product_iw + rtb_Sign1_e) * 2.0;
    rtb_QuaternionstoDirectionCosin[5] = (rtb_a - rtb_Gain_oa) * 2.0;
    rtb_QuaternionstoDirectionCosin[8] = (rtb_Sum1_oo - rtb_TT0gLR) + rtb_Sign1;

    /* Product: '<S86>/Matrix Multiply' incorporates:
     *  Constant: '<S86>/Constant'
     *  Quat2Dcm: '<S86>/Quaternions to  Direction Cosine Matrix'
     */
    rtb_TT0gLR = 0.0;
    rtb_Gain_l = 0.0;
    rtb_Gain_oa = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_Product2_e = rtCP__Constant_Value_dx[i];
      rtb_TT0gLR += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_Product2_e;
      rtb_Gain_l += rtb_QuaternionstoDirectionCosin[3 * i + 1] * rtb_Product2_e;
      rtb_Gain_oa += rtb_QuaternionstoDirectionCosin[3 * i + 2] * rtb_Product2_e;
    }

    rtb_Switch_f[2] = rtb_Gain_oa;
    rtb_Switch_f[1] = rtb_Gain_l;
    rtb_Switch_f[0] = rtb_TT0gLR;

    /* Saturate: '<S91>/Limit  altitude  to troposhere' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    if (-autocodePlant_X->uDOFQuaternion_CSTATE[5] > 11000.0) {
      rtb_Product2_e = 11000.0;
    } else if (-autocodePlant_X->uDOFQuaternion_CSTATE[5] < 0.0) {
      rtb_Product2_e = 0.0;
    } else {
      rtb_Product2_e = -autocodePlant_X->uDOFQuaternion_CSTATE[5];
    }

    /* Sum: '<S91>/Sum1' incorporates:
     *  Constant: '<S91>/Sea Level  Temperature'
     *  Gain: '<S91>/Lapse Rate'
     *  Saturate: '<S91>/Limit  altitude  to troposhere'
     */
    rtb_Sum1_oo = 288.15 - 0.0065 * rtb_Product2_e;

    /* Sqrt: '<S91>/a' incorporates:
     *  Gain: '<S91>/gamma*R'
     */
    rtb_a = sqrt(401.87433999999996 * rtb_Sum1_oo);

    /* Sum: '<S4>/Minus' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S86>/Matrix Multiply'
     */
    rtb_TmpSignalConversionAtProd_0 = autocodePlant_X->uDOFQuaternion_CSTATE[0]
      - rtb_TT0gLR;
    rtb_airspeed_mps[0] = rtb_TmpSignalConversionAtProd_0;

    /* Sum: '<S8>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S15>/Element Product'
     *  Sum: '<S15>/Sum'
     */
    rtb_TT0gLR = (autocodePlant_ConstB.Subtract1[2] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[7] -
                  autocodePlant_ConstB.Subtract1[1] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[8]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_jl[0] = rtb_TT0gLR;

    /* Product: '<S8>/Product8' */
    rtb_Sign1 = rtb_TT0gLR * autocodePlant_ConstB.Sum2_i[0];

    /* Sum: '<S4>/Minus' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S86>/Matrix Multiply'
     */
    rtb_TmpSignalConversionAtProd_0 = autocodePlant_X->uDOFQuaternion_CSTATE[1]
      - rtb_Gain_l;
    rtb_airspeed_mps[1] = rtb_TmpSignalConversionAtProd_0;

    /* Sum: '<S8>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S15>/Element Product'
     *  Sum: '<S15>/Sum'
     */
    rtb_Product2_f = (autocodePlant_ConstB.Subtract1[0] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[8] -
                      autocodePlant_ConstB.Subtract1[2] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[6]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_jl[1] = rtb_Product2_f;

    /* Product: '<S8>/Product8' */
    rtb_Gain_l = rtb_Product2_f * autocodePlant_ConstB.Sum2_i[1];

    /* Sum: '<S4>/Minus' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S86>/Matrix Multiply'
     */
    rtb_TmpSignalConversionAtProd_0 = autocodePlant_X->uDOFQuaternion_CSTATE[2]
      - rtb_Gain_oa;
    rtb_airspeed_mps[2] = rtb_TmpSignalConversionAtProd_0;

    /* Sum: '<S8>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S15>/Element Product'
     *  Sum: '<S15>/Sum'
     */
    rtb_Product_iw = (autocodePlant_ConstB.Subtract1[1] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[6] -
                      autocodePlant_ConstB.Subtract1[0] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[7]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_jl[2] = rtb_Product_iw;

    /* Product: '<S8>/Product8' */
    rtb_Sign1_e = rtb_Product_iw * autocodePlant_ConstB.Sum2_i[2];

    /* DotProduct: '<S8>/Dot Product4' incorporates:
     *  DotProduct: '<S8>/Dot Product3'
     */
    rtb_Sign1_oh = (rtb_TT0gLR * rtb_TT0gLR + rtb_Product2_f * rtb_Product2_f) +
      rtb_Product_iw * rtb_Product_iw;

    /* Product: '<S8>/Divide1' incorporates:
     *  DotProduct: '<S8>/Dot Product4'
     *  Sqrt: '<S8>/Sqrt1'
     */
    rtb_Gain_oa = sqrt(rtb_Sign1_oh) / rtb_a;

    /* Product: '<S8>/Divide' incorporates:
     *  DotProduct: '<S8>/Dot Product'
     *  DotProduct: '<S8>/Dot Product1'
     *  SignalConversion generated from: '<S8>/Dot Product'
     *  Sqrt: '<S8>/Sqrt'
     */
    rtb_Gain_ii = ((autocodePlant_ConstB.Sum_b * rtb_Sign1 +
                    autocodePlant_ConstB.Sum_l * rtb_Gain_l) +
                   autocodePlant_ConstB.Sum_c * rtb_Sign1_e) / sqrt((rtb_Sign1 *
      rtb_Sign1 + rtb_Gain_l * rtb_Gain_l) + rtb_Sign1_e * rtb_Sign1_e);

    /* Trigonometry: '<S8>/Acos' */
    if (rtb_Gain_ii > 1.0) {
      rtb_Gain_ii = 1.0;
    } else if (rtb_Gain_ii < -1.0) {
      rtb_Gain_ii = -1.0;
    }

    /* Gain: '<S19>/Gain' incorporates:
     *  Trigonometry: '<S8>/Acos'
     */
    rtb_Gain_l = 57.29577951308232 * acos(rtb_Gain_ii);

    /* DotProduct: '<S8>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S8>/Dot Product2'
     *  Sum: '<S8>/Sum'
     */
    rtb_Sign1 = (autocodePlant_ConstB.Sum_f * rtb_TT0gLR +
                 autocodePlant_ConstB.Sum_i * rtb_Product2_f) +
      autocodePlant_ConstB.Sum_e * rtb_Product_iw;

    /* Signum: '<S8>/Sign1' */
    if (rtIsNaN(rtb_Sign1)) {
      rtb_Sign1 = (rtNaN);
    } else if (rtb_Sign1 < 0.0) {
      rtb_Sign1 = -1.0;
    } else {
      rtb_Sign1 = (rtb_Sign1 > 0.0);
    }

    /* End of Signum: '<S8>/Sign1' */

    /* Lookup_n-D: '<S8>/CA Lookup Table' incorporates:
     *  Gain: '<S19>/Gain'
     *  Gain: '<S36>/Gain'
     *  Inport: '<Root>/control_deg'
     *  Product: '<S8>/Product7'
     */
    bpIndices[0U] = plook_binx(rtb_Gain_oa, rtCP__CALookupTable_bp01Data, 9U,
      &rtb_Gain_ii);
    rtb_Sum_ls[0U] = rtb_Gain_ii;
    bpIndices[1U] = plook_binx(rtb_Gain_l, rtCP__CALookupTable_bp02Data, 2U,
      &rtb_Gain_ii);
    rtb_Sum_ls[1U] = rtb_Gain_ii;
    bpIndices[2U] = plook_binx(autocodePlant_U_control_deg[0] * rtb_Sign1,
      rtCP__CALookupTable_bp03Data, 4U, &rtb_Gain_ii);
    rtb_Sum_ls[2U] = rtb_Gain_ii;
    rtb_Sign1_e = intrp3d_l_pw(bpIndices, rtb_Sum_ls,
      rtCP__CALookupTable_tableData, rtCP__CALookupTable_dimSizes);

    /* Gain: '<S91>/1//T0' */
    rtb_Product2_f = 0.00347041471455839 * rtb_Sum1_oo;

    /* Math: '<S91>/(T//T0)^(g//LR) ' incorporates:
     *  Constant: '<S91>/Constant'
     */
    rtb_TT0gLR = rt_powd_snf(rtb_Product2_f, 5.255875601466713);

    /* Product: '<S91>/Product' */
    rtb_Product_iw = rtb_TT0gLR / rtb_Product2_f;

    /* Saturate: '<S91>/Limit  altitude  to Stratosphere' incorporates:
     *  Constant: '<S91>/Altitude of Troposphere'
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Sum: '<S91>/Sum'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    if (11000.0 - (-autocodePlant_X->uDOFQuaternion_CSTATE[5]) > 0.0) {
      rtb_Product2_e = 0.0;
    } else if (11000.0 - (-autocodePlant_X->uDOFQuaternion_CSTATE[5]) < -9000.0)
    {
      rtb_Product2_e = -9000.0;
    } else {
      rtb_Product2_e = 11000.0 - (-autocodePlant_X->uDOFQuaternion_CSTATE[5]);
    }

    /* Math: '<S91>/Stratosphere Model' incorporates:
     *  Gain: '<S91>/g//R'
     *  Product: '<S91>/Product1'
     *  Saturate: '<S91>/Limit  altitude  to Stratosphere'
     *
     * About '<S91>/Stratosphere Model':
     *  Operator: exp
     */
    rtb_Product2_f = exp(1.0 / rtb_Sum1_oo * (0.03416319140953364 *
      rtb_Product2_e));

    /* Product: '<S91>/Product3' incorporates:
     *  Gain: '<S91>/rho0'
     */
    rtb_Product_iw = 1.225 * rtb_Product_iw * rtb_Product2_f;

    /* Product: '<S8>/Product' incorporates:
     *  Constant: '<S8>/Constant1'
     *  Product: '<S10>/Product'
     *  Product: '<S11>/Product'
     *  Product: '<S7>/Product'
     *  Product: '<S9>/Product'
     */
    rtb_UnaryMinus_a = 0.5 * rtb_Product_iw;
    rtb_Sign1_oh *= rtb_UnaryMinus_a;

    /* UnaryMinus: '<S8>/Unary Minus' incorporates:
     *  Constant: '<S8>/   '
     *  Product: '<S8>/Product1'
     */
    rtb_Sign1_e = -(rtb_Sign1_e * rtb_Sign1_oh * 0.018);

    /* Lookup_n-D: '<S8>/CN Lookup Table' incorporates:
     *  Gain: '<S19>/Gain'
     *  Gain: '<S36>/Gain'
     *  Inport: '<Root>/control_deg'
     *  Product: '<S8>/Product5'
     */
    bpIndices_0[0U] = plook_binx(rtb_Gain_oa, rtCP__CNLookupTable_bp01Data, 9U,
      &rtb_Gain_ii);
    rtb_Sum_l4[0U] = rtb_Gain_ii;
    bpIndices_0[1U] = plook_binx(rtb_Gain_l, rtCP__CNLookupTable_bp02Data, 2U,
      &rtb_Gain_ii);
    rtb_Sum_l4[1U] = rtb_Gain_ii;
    bpIndices_0[2U] = plook_binx(autocodePlant_U_control_deg[0] * rtb_Sign1,
      rtCP__CNLookupTable_bp03Data, 4U, &rtb_Gain_ii);
    rtb_Sum_l4[2U] = rtb_Gain_ii;
    rtb_Gain_oa = intrp3d_l_pw(bpIndices_0, rtb_Sum_l4,
      rtCP__CNLookupTable_tableData, rtCP__CNLookupTable_dimSizes);

    /* UnaryMinus: '<S8>/Unary Minus1' incorporates:
     *  Constant: '<S8>/ '
     *  Product: '<S8>/Product2'
     */
    rtb_Gain_oa = -(rtb_Gain_oa * rtb_Sign1_oh * 0.018);

    /* Sum: '<S8>/Sum1' incorporates:
     *  Product: '<S8>/Product3'
     *  Product: '<S8>/Product4'
     *  SignalConversion generated from: '<S8>/Dot Product2'
     */
    rtb_Sum1_p2[0] = rtb_Gain_oa * autocodePlant_ConstB.Sum_f * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_b;
    rtb_Sum1_p2[1] = rtb_Gain_oa * autocodePlant_ConstB.Sum_i * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_l;
    rtb_Sum1_p2[2] = rtb_Gain_oa * autocodePlant_ConstB.Sum_e * rtb_Sign1 +
      rtb_Sign1_e * autocodePlant_ConstB.Sum_c;

    /* Sum: '<S16>/Sum' incorporates:
     *  Product: '<S16>/Element Product'
     */
    rtb_Sum_j[0] = autocodePlant_ConstB.Subtract1[1] * rtb_Sum1_p2[2] -
      rtb_Sum1_p2[1] * autocodePlant_ConstB.Subtract1[2];
    rtb_Sum_j[1] = rtb_Sum1_p2[0] * autocodePlant_ConstB.Subtract1[2] -
      autocodePlant_ConstB.Subtract1[0] * rtb_Sum1_p2[2];
    rtb_Sum_j[2] = autocodePlant_ConstB.Subtract1[0] * rtb_Sum1_p2[1] -
      rtb_Sum1_p2[0] * autocodePlant_ConstB.Subtract1[1];

    /* Sum: '<S9>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S32>/Element Product'
     *  Sum: '<S32>/Sum'
     */
    rtb_Sign1_e = (autocodePlant_ConstB.Subtract1_m[2] *
                   autocodePlant_X->uDOFQuaternion_CSTATE[7] -
                   autocodePlant_ConstB.Subtract1_m[1] *
                   autocodePlant_X->uDOFQuaternion_CSTATE[8]) +
      rtb_airspeed_mps[0];
    rtb_Sum_ls[0] = rtb_Sign1_e;

    /* Product: '<S9>/Product8' */
    rtb_Gain_ii = rtb_Sign1_e * autocodePlant_ConstB.Sum2_l[0];

    /* Sum: '<S9>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S32>/Element Product'
     *  Sum: '<S32>/Sum'
     */
    rtb_Gain_c = (autocodePlant_ConstB.Subtract1_m[0] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[8] -
                  autocodePlant_ConstB.Subtract1_m[2] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[6]) + rtb_airspeed_mps
      [1];
    rtb_Sum_ls[1] = rtb_Gain_c;

    /* Product: '<S9>/Product8' */
    rtb_Gain_oa = rtb_Gain_c * autocodePlant_ConstB.Sum2_l[1];

    /* Sum: '<S9>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S32>/Element Product'
     *  Sum: '<S32>/Sum'
     *  Sum: '<S4>/Minus'
     */
    rtb_Gain_e = (autocodePlant_ConstB.Subtract1_m[1] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[6] -
                  autocodePlant_ConstB.Subtract1_m[0] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[7]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_ls[2] = rtb_Gain_e;

    /* Product: '<S9>/Product8' */
    rtb_Switch_d_idx_1 = rtb_Gain_e * autocodePlant_ConstB.Sum2_l[2];

    /* DotProduct: '<S9>/Dot Product4' incorporates:
     *  DotProduct: '<S9>/Dot Product3'
     */
    rtb_Sign1_b = (rtb_Sign1_e * rtb_Sign1_e + rtb_Gain_c * rtb_Gain_c) +
      rtb_Gain_e * rtb_Gain_e;

    /* Product: '<S9>/Divide1' incorporates:
     *  DotProduct: '<S9>/Dot Product4'
     *  Sqrt: '<S9>/Sqrt1'
     */
    rtb_Sign1_oh = sqrt(rtb_Sign1_b) / rtb_a;

    /* Product: '<S9>/Divide' incorporates:
     *  DotProduct: '<S9>/Dot Product'
     *  DotProduct: '<S9>/Dot Product1'
     *  SignalConversion generated from: '<S9>/Dot Product'
     *  Sqrt: '<S9>/Sqrt'
     */
    rtb_Gain_ii = ((autocodePlant_ConstB.Sum_k3 * rtb_Gain_ii +
                    autocodePlant_ConstB.Sum_cv * rtb_Gain_oa) +
                   autocodePlant_ConstB.Sum_b1v * rtb_Switch_d_idx_1) / sqrt
      ((rtb_Gain_ii * rtb_Gain_ii + rtb_Gain_oa * rtb_Gain_oa) +
       rtb_Switch_d_idx_1 * rtb_Switch_d_idx_1);

    /* Trigonometry: '<S9>/Acos' */
    if (rtb_Gain_ii > 1.0) {
      rtb_Gain_ii = 1.0;
    } else if (rtb_Gain_ii < -1.0) {
      rtb_Gain_ii = -1.0;
    }

    /* Gain: '<S36>/Gain' incorporates:
     *  Trigonometry: '<S9>/Acos'
     */
    rtb_Gain_oa = 57.29577951308232 * acos(rtb_Gain_ii);

    /* DotProduct: '<S9>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S9>/Dot Product2'
     *  Sum: '<S9>/Sum'
     */
    rtb_Gain_ii = (autocodePlant_ConstB.Sum_m * rtb_Sign1_e +
                   autocodePlant_ConstB.Sum_b1 * rtb_Gain_c) +
      autocodePlant_ConstB.Sum_k * rtb_Gain_e;

    /* Signum: '<S9>/Sign1' */
    if (rtIsNaN(rtb_Gain_ii)) {
      rtb_Sign1_e = (rtNaN);
    } else if (rtb_Gain_ii < 0.0) {
      rtb_Sign1_e = -1.0;
    } else {
      rtb_Sign1_e = (rtb_Gain_ii > 0.0);
    }

    /* End of Signum: '<S9>/Sign1' */

    /* Lookup_n-D: '<S9>/CA Lookup Table' incorporates:
     *  Gain: '<S36>/Gain'
     *  Inport: '<Root>/control_deg'
     *  Product: '<S9>/Product7'
     *  Signum: '<S10>/Sign1'
     */
    bpIndices_1[0U] = plook_binx(rtb_Sign1_oh, rtCP__CALookupTable_bp01Data_n,
      9U, &rtb_Gain_ii);
    rtb_Sum_cu[0U] = rtb_Gain_ii;
    bpIndices_1[1U] = plook_binx(rtb_Gain_oa, rtCP__CALookupTable_bp02Data_h, 2U,
      &rtb_Gain_ii);
    rtb_Sum_cu[1U] = rtb_Gain_ii;
    bpIndices_1[2U] = plook_binx(autocodePlant_U_control_deg[1] * rtb_Sign1_e,
      rtCP__CALookupTable_bp03Data_f, 4U, &rtb_Gain_ii);
    rtb_Sum_cu[2U] = rtb_Gain_ii;
    rtb_Gain_c = intrp3d_l_pw(bpIndices_1, rtb_Sum_cu,
      rtCP__CALookupTable_tableData_b, rtCP__CALookupTable_dimSizes_c);

    /* Product: '<S9>/Product' */
    rtb_Sign1_b *= rtb_UnaryMinus_a;

    /* UnaryMinus: '<S9>/Unary Minus' incorporates:
     *  Constant: '<S9>/   '
     *  Product: '<S9>/Product1'
     */
    rtb_Gain_c = -(rtb_Gain_c * rtb_Sign1_b * 0.018);

    /* Lookup_n-D: '<S9>/CN Lookup Table' incorporates:
     *  Gain: '<S36>/Gain'
     *  Inport: '<Root>/control_deg'
     *  Product: '<S9>/Product5'
     *  Signum: '<S10>/Sign1'
     */
    bpIndices_2[0U] = plook_binx(rtb_Sign1_oh, rtCP__CNLookupTable_bp01Data_f,
      9U, &rtb_Gain_ii);
    rtb_Sum_bq[0U] = rtb_Gain_ii;
    bpIndices_2[1U] = plook_binx(rtb_Gain_oa, rtCP__CNLookupTable_bp02Data_a, 2U,
      &rtb_Gain_ii);
    rtb_Sum_bq[1U] = rtb_Gain_ii;
    bpIndices_2[2U] = plook_binx(autocodePlant_U_control_deg[1] * rtb_Sign1_e,
      rtCP__CNLookupTable_bp03Data_p, 4U, &rtb_Gain_ii);
    rtb_Sum_bq[2U] = rtb_Gain_ii;
    rtb_Sign1_oh = intrp3d_l_pw(bpIndices_2, rtb_Sum_bq,
      rtCP__CNLookupTable_tableData_f, rtCP__CNLookupTable_dimSizes_e);

    /* UnaryMinus: '<S9>/Unary Minus1' incorporates:
     *  Constant: '<S9>/ '
     *  Product: '<S9>/Product2'
     */
    rtb_Sign1_oh = -(rtb_Sign1_oh * rtb_Sign1_b * 0.018);

    /* Sum: '<S9>/Sum1' incorporates:
     *  Product: '<S9>/Product3'
     *  Product: '<S9>/Product4'
     *  SignalConversion generated from: '<S9>/Dot Product2'
     */
    rtb_Sum1_ny[0] = rtb_Sign1_oh * autocodePlant_ConstB.Sum_m * rtb_Sign1_e +
      rtb_Gain_c * autocodePlant_ConstB.Sum_k3;
    rtb_Sum1_ny[1] = rtb_Sign1_oh * autocodePlant_ConstB.Sum_b1 * rtb_Sign1_e +
      rtb_Gain_c * autocodePlant_ConstB.Sum_cv;
    rtb_Sum1_ny[2] = rtb_Sign1_oh * autocodePlant_ConstB.Sum_k * rtb_Sign1_e +
      rtb_Gain_c * autocodePlant_ConstB.Sum_b1v;

    /* Sum: '<S33>/Sum' incorporates:
     *  Product: '<S33>/Element Product'
     */
    rtb_Sum_l4[0] = autocodePlant_ConstB.Subtract1_m[1] * rtb_Sum1_ny[2] -
      rtb_Sum1_ny[1] * autocodePlant_ConstB.Subtract1_m[2];
    rtb_Sum_l4[1] = rtb_Sum1_ny[0] * autocodePlant_ConstB.Subtract1_m[2] -
      autocodePlant_ConstB.Subtract1_m[0] * rtb_Sum1_ny[2];
    rtb_Sum_l4[2] = autocodePlant_ConstB.Subtract1_m[0] * rtb_Sum1_ny[1] -
      rtb_Sum1_ny[0] * autocodePlant_ConstB.Subtract1_m[1];

    /* Sum: '<S10>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S49>/Element Product'
     *  Sum: '<S49>/Sum'
     */
    rtb_Sign1_oh = (autocodePlant_ConstB.Subtract1_k[2] *
                    autocodePlant_X->uDOFQuaternion_CSTATE[7] -
                    autocodePlant_ConstB.Subtract1_k[1] *
                    autocodePlant_X->uDOFQuaternion_CSTATE[8]) +
      rtb_airspeed_mps[0];
    rtb_Sum_cu[0] = rtb_Sign1_oh;

    /* Product: '<S10>/Product8' */
    rtb_Gain_ii = rtb_Sign1_oh * autocodePlant_ConstB.Sum2_iw[0];

    /* Sum: '<S10>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S49>/Element Product'
     *  Sum: '<S49>/Sum'
     */
    rtb_Gain_e = (autocodePlant_ConstB.Subtract1_k[0] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[8] -
                  autocodePlant_ConstB.Subtract1_k[2] *
                  autocodePlant_X->uDOFQuaternion_CSTATE[6]) + rtb_airspeed_mps
      [1];
    rtb_Sum_cu[1] = rtb_Gain_e;

    /* Product: '<S10>/Product8' */
    rtb_Gain_c = rtb_Gain_e * autocodePlant_ConstB.Sum2_iw[1];

    /* Sum: '<S10>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S49>/Element Product'
     *  Sum: '<S49>/Sum'
     *  Sum: '<S4>/Minus'
     */
    rtb_Product2_e = (autocodePlant_ConstB.Subtract1_k[1] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[6] -
                      autocodePlant_ConstB.Subtract1_k[0] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[7]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_cu[2] = rtb_Product2_e;

    /* Product: '<S10>/Product8' */
    rtb_Product3_ax = rtb_Product2_e * autocodePlant_ConstB.Sum2_iw[2];

    /* DotProduct: '<S10>/Dot Product4' incorporates:
     *  DotProduct: '<S10>/Dot Product3'
     */
    rtb_Switch_d_idx_1 = (rtb_Sign1_oh * rtb_Sign1_oh + rtb_Gain_e * rtb_Gain_e)
      + rtb_Product2_e * rtb_Product2_e;

    /* Product: '<S10>/Divide1' incorporates:
     *  DotProduct: '<S10>/Dot Product4'
     *  Sqrt: '<S10>/Sqrt1'
     */
    rtb_Sign1_b = sqrt(rtb_Switch_d_idx_1) / rtb_a;

    /* Product: '<S10>/Divide' incorporates:
     *  DotProduct: '<S10>/Dot Product'
     *  DotProduct: '<S10>/Dot Product1'
     *  SignalConversion generated from: '<S10>/Dot Product'
     *  Sqrt: '<S10>/Sqrt'
     */
    rtb_Gain_ii = ((autocodePlant_ConstB.Sum_a * rtb_Gain_ii +
                    autocodePlant_ConstB.Sum_ia * rtb_Gain_c) +
                   autocodePlant_ConstB.Sum_bt * rtb_Product3_ax) / sqrt
      ((rtb_Gain_ii * rtb_Gain_ii + rtb_Gain_c * rtb_Gain_c) + rtb_Product3_ax *
       rtb_Product3_ax);

    /* Trigonometry: '<S10>/Acos' */
    if (rtb_Gain_ii > 1.0) {
      rtb_Gain_ii = 1.0;
    } else if (rtb_Gain_ii < -1.0) {
      rtb_Gain_ii = -1.0;
    }

    /* Gain: '<S53>/Gain' incorporates:
     *  Trigonometry: '<S10>/Acos'
     */
    rtb_Gain_c = 57.29577951308232 * acos(rtb_Gain_ii);

    /* DotProduct: '<S10>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S10>/Dot Product2'
     *  Sum: '<S10>/Sum'
     */
    rtb_Gain_ii = (autocodePlant_ConstB.Sum_o * rtb_Sign1_oh +
                   autocodePlant_ConstB.Sum_er * rtb_Gain_e) +
      autocodePlant_ConstB.Sum_g * rtb_Product2_e;

    /* Signum: '<S10>/Sign1' */
    if (rtIsNaN(rtb_Gain_ii)) {
      rtb_Sign1_oh = (rtNaN);
    } else if (rtb_Gain_ii < 0.0) {
      rtb_Sign1_oh = -1.0;
    } else {
      rtb_Sign1_oh = (rtb_Gain_ii > 0.0);
    }

    /* End of Signum: '<S10>/Sign1' */

    /* Lookup_n-D: '<S10>/CA Lookup Table' incorporates:
     *  Gain: '<S53>/Gain'
     *  Inport: '<Root>/control_deg'
     *  Product: '<S10>/Product7'
     *  Signum: '<S11>/Sign1'
     */
    bpIndices_3[0U] = plook_binx(rtb_Sign1_b, rtCP__CALookupTable_bp01Data_f, 9U,
      &rtb_Gain_ii);
    rtb_Sum_pc[0U] = rtb_Gain_ii;
    bpIndices_3[1U] = plook_binx(rtb_Gain_c, rtCP__CALookupTable_bp02Data_e, 2U,
      &rtb_Gain_ii);
    rtb_Sum_pc[1U] = rtb_Gain_ii;
    bpIndices_3[2U] = plook_binx(autocodePlant_U_control_deg[2] * rtb_Sign1_oh,
      rtCP__CALookupTable_bp03Data_fn, 4U, &rtb_Gain_ii);
    rtb_Sum_pc[2U] = rtb_Gain_ii;
    rtb_Gain_e = intrp3d_l_pw(bpIndices_3, rtb_Sum_pc,
      rtCP__CALookupTable_tableData_n, rtCP__CALookupTable_dimSizes_e);

    /* Product: '<S10>/Product' */
    rtb_Product1_kn = rtb_Switch_d_idx_1 * rtb_UnaryMinus_a;

    /* UnaryMinus: '<S10>/Unary Minus' incorporates:
     *  Constant: '<S10>/   '
     *  Product: '<S10>/Product1'
     */
    rtb_Gain_e = -(rtb_Gain_e * rtb_Product1_kn * 0.018);

    /* Lookup_n-D: '<S10>/CN Lookup Table' incorporates:
     *  Gain: '<S53>/Gain'
     *  Inport: '<Root>/control_deg'
     *  Product: '<S10>/Product5'
     *  Signum: '<S11>/Sign1'
     */
    bpIndices_4[0U] = plook_binx(rtb_Sign1_b, rtCP__CNLookupTable_bp01Data_n, 9U,
      &rtb_Gain_ii);
    rtb_Sum_kx[0U] = rtb_Gain_ii;
    bpIndices_4[1U] = plook_binx(rtb_Gain_c, rtCP__CNLookupTable_bp02Data_i, 2U,
      &rtb_Gain_ii);
    rtb_Sum_kx[1U] = rtb_Gain_ii;
    bpIndices_4[2U] = plook_binx(autocodePlant_U_control_deg[2] * rtb_Sign1_oh,
      rtCP__CNLookupTable_bp03Data_l, 4U, &rtb_Gain_ii);
    rtb_Sum_kx[2U] = rtb_Gain_ii;
    rtb_Sign1_b = intrp3d_l_pw(bpIndices_4, rtb_Sum_kx,
      rtCP__CNLookupTable_tableData_j, rtCP__CNLookupTable_dimSizes_ex);

    /* UnaryMinus: '<S10>/Unary Minus1' incorporates:
     *  Constant: '<S10>/ '
     *  Product: '<S10>/Product2'
     */
    rtb_Sign1_b = -(rtb_Sign1_b * rtb_Product1_kn * 0.018);

    /* Sum: '<S10>/Sum1' incorporates:
     *  Product: '<S10>/Product3'
     *  Product: '<S10>/Product4'
     *  SignalConversion generated from: '<S10>/Dot Product2'
     */
    rtb_Sum1_lp[0] = rtb_Sign1_b * autocodePlant_ConstB.Sum_o * rtb_Sign1_oh +
      rtb_Gain_e * autocodePlant_ConstB.Sum_a;
    rtb_Sum1_lp[1] = rtb_Sign1_b * autocodePlant_ConstB.Sum_er * rtb_Sign1_oh +
      rtb_Gain_e * autocodePlant_ConstB.Sum_ia;
    rtb_Sum1_lp[2] = rtb_Sign1_b * autocodePlant_ConstB.Sum_g * rtb_Sign1_oh +
      rtb_Gain_e * autocodePlant_ConstB.Sum_bt;

    /* Sum: '<S50>/Sum' incorporates:
     *  Product: '<S50>/Element Product'
     */
    rtb_Sum_bq[0] = autocodePlant_ConstB.Subtract1_k[1] * rtb_Sum1_lp[2] -
      rtb_Sum1_lp[1] * autocodePlant_ConstB.Subtract1_k[2];
    rtb_Sum_bq[1] = rtb_Sum1_lp[0] * autocodePlant_ConstB.Subtract1_k[2] -
      autocodePlant_ConstB.Subtract1_k[0] * rtb_Sum1_lp[2];
    rtb_Sum_bq[2] = autocodePlant_ConstB.Subtract1_k[0] * rtb_Sum1_lp[1] -
      rtb_Sum1_lp[0] * autocodePlant_ConstB.Subtract1_k[1];

    /* Sum: '<S11>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S66>/Element Product'
     *  Sum: '<S66>/Sum'
     */
    rtb_Sign1_b = (autocodePlant_ConstB.Subtract1_j[2] *
                   autocodePlant_X->uDOFQuaternion_CSTATE[7] -
                   autocodePlant_ConstB.Subtract1_j[1] *
                   autocodePlant_X->uDOFQuaternion_CSTATE[8]) +
      rtb_airspeed_mps[0];
    rtb_Sum_pc[0] = rtb_Sign1_b;

    /* Product: '<S11>/Product8' */
    rtb_Gain_ii = rtb_Sign1_b * autocodePlant_ConstB.Sum2_ayz[0];

    /* Sum: '<S11>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S66>/Element Product'
     *  Sum: '<S66>/Sum'
     */
    rtb_Product2_e = (autocodePlant_ConstB.Subtract1_j[0] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[8] -
                      autocodePlant_ConstB.Subtract1_j[2] *
                      autocodePlant_X->uDOFQuaternion_CSTATE[6]) +
      rtb_airspeed_mps[1];
    rtb_Sum_pc[1] = rtb_Product2_e;

    /* Product: '<S11>/Product8' */
    rtb_Gain_e = rtb_Product2_e * autocodePlant_ConstB.Sum2_ayz[1];

    /* Sum: '<S11>/Sum' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S66>/Element Product'
     *  Sum: '<S4>/Minus'
     *  Sum: '<S66>/Sum'
     */
    rtb_Product3_ax = (autocodePlant_ConstB.Subtract1_j[1] *
                       autocodePlant_X->uDOFQuaternion_CSTATE[6] -
                       autocodePlant_ConstB.Subtract1_j[0] *
                       autocodePlant_X->uDOFQuaternion_CSTATE[7]) +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Sum_pc[2] = rtb_Product3_ax;

    /* Product: '<S11>/Product8' */
    rtb_Switch_d_idx_2 = rtb_Product3_ax * autocodePlant_ConstB.Sum2_ayz[2];

    /* DotProduct: '<S11>/Dot Product4' incorporates:
     *  DotProduct: '<S11>/Dot Product3'
     */
    rtb_Switch_d_idx_1 = (rtb_Sign1_b * rtb_Sign1_b + rtb_Product2_e *
                          rtb_Product2_e) + rtb_Product3_ax * rtb_Product3_ax;

    /* Product: '<S11>/Divide1' incorporates:
     *  DotProduct: '<S11>/Dot Product4'
     *  Sqrt: '<S11>/Sqrt1'
     */
    rtb_Product1_kn = sqrt(rtb_Switch_d_idx_1) / rtb_a;

    /* Product: '<S11>/Divide' incorporates:
     *  DotProduct: '<S11>/Dot Product'
     *  DotProduct: '<S11>/Dot Product1'
     *  SignalConversion generated from: '<S11>/Dot Product'
     *  Sqrt: '<S11>/Sqrt'
     */
    rtb_Gain_ii = ((autocodePlant_ConstB.Sum_dx * rtb_Gain_ii +
                    autocodePlant_ConstB.Sum_o3 * rtb_Gain_e) +
                   autocodePlant_ConstB.Sum_j * rtb_Switch_d_idx_2) / sqrt
      ((rtb_Gain_ii * rtb_Gain_ii + rtb_Gain_e * rtb_Gain_e) +
       rtb_Switch_d_idx_2 * rtb_Switch_d_idx_2);

    /* Trigonometry: '<S11>/Acos' */
    if (rtb_Gain_ii > 1.0) {
      rtb_Gain_ii = 1.0;
    } else if (rtb_Gain_ii < -1.0) {
      rtb_Gain_ii = -1.0;
    }

    /* Gain: '<S70>/Gain' incorporates:
     *  Trigonometry: '<S11>/Acos'
     */
    rtb_Gain_e = 57.29577951308232 * acos(rtb_Gain_ii);

    /* DotProduct: '<S11>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S11>/Dot Product2'
     *  Sum: '<S11>/Sum'
     */
    rtb_Gain_ii = (autocodePlant_ConstB.Sum_d * rtb_Sign1_b +
                   autocodePlant_ConstB.Sum_b4 * rtb_Product2_e) +
      autocodePlant_ConstB.Sum_ln * rtb_Product3_ax;

    /* Signum: '<S11>/Sign1' */
    if (rtIsNaN(rtb_Gain_ii)) {
      rtb_Sign1_b = (rtNaN);
    } else if (rtb_Gain_ii < 0.0) {
      rtb_Sign1_b = -1.0;
    } else {
      rtb_Sign1_b = (rtb_Gain_ii > 0.0);
    }

    /* End of Signum: '<S11>/Sign1' */

    /* Lookup_n-D: '<S11>/CA Lookup Table' incorporates:
     *  Gain: '<S70>/Gain'
     *  Inport: '<Root>/control_deg'
     *  Product: '<S11>/Product7'
     *  Product: '<S174>/Product1'
     */
    bpIndices_5[0U] = plook_binx(rtb_Product1_kn, rtCP__CALookupTable_bp01Data_k,
      9U, &rtb_Gain_ii);
    rtb_Product6_f[0U] = rtb_Gain_ii;
    bpIndices_5[1U] = plook_binx(rtb_Gain_e, rtCP__CALookupTable_bp02Data_f, 2U,
      &rtb_Gain_ii);
    rtb_Product6_f[1U] = rtb_Gain_ii;
    bpIndices_5[2U] = plook_binx(autocodePlant_U_control_deg[3] * rtb_Sign1_b,
      rtCP__CALookupTable_bp03Data_b, 4U, &rtb_Gain_ii);
    rtb_Product6_f[2U] = rtb_Gain_ii;
    rtb_Gain_ii = intrp3d_l_pw(bpIndices_5, rtb_Product6_f,
      rtCP__CALookupTable_tableData_l, rtCP__CALookupTable_dimSizes_a);

    /* Product: '<S11>/Product' */
    rtb_Product3_ax = rtb_Switch_d_idx_1 * rtb_UnaryMinus_a;

    /* UnaryMinus: '<S11>/Unary Minus' incorporates:
     *  Constant: '<S11>/   '
     *  Product: '<S11>/Product1'
     */
    rtb_Switch_d_idx_1 = -(rtb_Gain_ii * rtb_Product3_ax * 0.018);

    /* Lookup_n-D: '<S11>/CN Lookup Table' incorporates:
     *  Gain: '<S70>/Gain'
     *  Inport: '<Root>/control_deg'
     *  Product: '<S11>/Product5'
     *  Product: '<S174>/Product1'
     */
    bpIndices_6[0U] = plook_binx(rtb_Product1_kn, rtCP__CNLookupTable_bp01Data_d,
      9U, &rtb_Gain_ii);
    rtb_finMomentArm_m[0U] = rtb_Gain_ii;
    bpIndices_6[1U] = plook_binx(rtb_Gain_e, rtCP__CNLookupTable_bp02Data_av, 2U,
      &rtb_Gain_ii);
    rtb_finMomentArm_m[1U] = rtb_Gain_ii;
    bpIndices_6[2U] = plook_binx(autocodePlant_U_control_deg[3] * rtb_Sign1_b,
      rtCP__CNLookupTable_bp03Data_g, 4U, &rtb_Gain_ii);
    rtb_finMomentArm_m[2U] = rtb_Gain_ii;
    rtb_Product1_kn = intrp3d_l_pw(bpIndices_6, rtb_finMomentArm_m,
      rtCP__CNLookupTable_tableData_d, rtCP__CNLookupTable_dimSizes_h);

    /* UnaryMinus: '<S11>/Unary Minus1' incorporates:
     *  Constant: '<S11>/ '
     *  Product: '<S11>/Product2'
     */
    rtb_Gain_ii = -(rtb_Product1_kn * rtb_Product3_ax * 0.018);

    /* Sum: '<S11>/Sum1' incorporates:
     *  Product: '<S11>/Product3'
     *  Product: '<S11>/Product4'
     *  SignalConversion generated from: '<S11>/Dot Product2'
     */
    rtb_Sum1_b[0] = rtb_Gain_ii * autocodePlant_ConstB.Sum_d * rtb_Sign1_b +
      rtb_Switch_d_idx_1 * autocodePlant_ConstB.Sum_dx;
    rtb_Sum1_b[1] = rtb_Gain_ii * autocodePlant_ConstB.Sum_b4 * rtb_Sign1_b +
      rtb_Switch_d_idx_1 * autocodePlant_ConstB.Sum_o3;
    rtb_Sum1_b[2] = rtb_Gain_ii * autocodePlant_ConstB.Sum_ln * rtb_Sign1_b +
      rtb_Switch_d_idx_1 * autocodePlant_ConstB.Sum_j;

    /* Sum: '<S67>/Sum' incorporates:
     *  Product: '<S67>/Element Product'
     */
    rtb_Sum_kx[0] = autocodePlant_ConstB.Subtract1_j[1] * rtb_Sum1_b[2] -
      rtb_Sum1_b[1] * autocodePlant_ConstB.Subtract1_j[2];
    rtb_Sum_kx[1] = rtb_Sum1_b[0] * autocodePlant_ConstB.Subtract1_j[2] -
      autocodePlant_ConstB.Subtract1_j[0] * rtb_Sum1_b[2];
    rtb_Sum_kx[2] = autocodePlant_ConstB.Subtract1_j[0] * rtb_Sum1_b[1] -
      rtb_Sum1_b[0] * autocodePlant_ConstB.Subtract1_j[1];

    /* DotProduct: '<S7>/Dot Product4' incorporates:
     *  DotProduct: '<S7>/Dot Product3'
     *  Math: '<S13>/Math Function'
     *  Sum: '<S4>/Minus'
     */
    rtb_Product1_kn = rtb_airspeed_mps[1] * rtb_airspeed_mps[1];
    rtb_Sum1_ox = rtb_TmpSignalConversionAtProd_0 *
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product2_e = (rtb_airspeed_mps[0] * rtb_airspeed_mps[0] +
                      rtb_Product1_kn) + rtb_Sum1_ox;

    /* Sqrt: '<S7>/Sqrt1' incorporates:
     *  DotProduct: '<S7>/Dot Product4'
     *  Sqrt: '<S7>/Sqrt'
     */
    rtb_Gain_ii = sqrt(rtb_Product2_e);

    /* Product: '<S7>/Divide1' incorporates:
     *  Sqrt: '<S7>/Sqrt1'
     */
    rtb_Product3_ax = rtb_Gain_ii / rtb_a;

    /* DotProduct: '<S7>/Dot Product' incorporates:
     *  DotProduct: '<S7>/Dot Product4'
     *  Product: '<S13>/Product'
     *  Sum: '<S4>/Minus'
     *  Switch: '<S13>/Switch'
     */
    rtb_Switch_d_idx_1 = 0.0 * rtb_airspeed_mps[1];
    rtb_Switch_d_idx_2 = 0.0 * rtb_TmpSignalConversionAtProd_0;

    /* Product: '<S7>/Divide' incorporates:
     *  DotProduct: '<S7>/Dot Product'
     *  DotProduct: '<S7>/Dot Product4'
     */
    rtb_Gain_ii = ((rtb_Switch_d_idx_1 + rtb_airspeed_mps[0]) +
                   rtb_Switch_d_idx_2) / rtb_Gain_ii;

    /* Trigonometry: '<S7>/Acos' */
    if (rtb_Gain_ii > 1.0) {
      rtb_Gain_ii = 1.0;
    } else if (rtb_Gain_ii < -1.0) {
      rtb_Gain_ii = -1.0;
    }

    /* Gain: '<S14>/Gain' incorporates:
     *  Trigonometry: '<S7>/Acos'
     */
    rtb_Gain_ii = 57.29577951308232 * acos(rtb_Gain_ii);

    /* Sum: '<S7>/Sum' incorporates:
     *  Constant: '<S3>/Constant'
     *  Gain: '<S14>/Gain'
     *  Lookup_n-D: '<S7>/CP Lookup Table'
     *  Product: '<S174>/Product3'
     */
    rtb_Sum = 1.8117856235712473 - look2_binlcpw(rtb_Product3_ax, rtb_Gain_ii,
      rtCP__CPLookupTable_bp01Data, rtCP__CPLookupTable_bp02Data,
      rtCP__CPLookupTable_tableData, rtCP__CPLookupTable_maxIndex, 10U);

    /* Product: '<S7>/Product6' incorporates:
     *  Constant: '<S7>/Constant3'
     *  DotProduct: '<S7>/Dot Product3'
     */
    rtb_Switch_d_idx_0 = rtb_airspeed_mps[0] * 0.0;

    /* Product: '<S7>/Product5' incorporates:
     *  Constant: '<S7>/Constant2'
     */
    rtb_Product_kd = rtb_Sum * 0.0;

    /* Product: '<S7>/Product' */
    rtb_Product2_e *= rtb_UnaryMinus_a;

    /* UnaryMinus: '<S7>/Unary Minus' incorporates:
     *  Constant: '<S7>/   '
     *  Gain: '<S14>/Gain'
     *  Lookup_n-D: '<S7>/CA Lookup Table'
     *  Product: '<S174>/Product3'
     *  Product: '<S7>/Product1'
     */
    rtb_UnaryMinus_a = -(look2_binlxpw(rtb_Product3_ax, rtb_Gain_ii,
      rtCP__CALookupTable_bp01Data_j, rtCP__CALookupTable_bp02Data_b,
      rtCP__CALookupTable_tableData_e, rtCP__CALookupTable_maxIndex_j, 10U) *
                         rtb_Product2_e * 0.018);

    /* UnaryMinus: '<S7>/Unary Minus1' incorporates:
     *  Constant: '<S7>/ '
     *  Gain: '<S14>/Gain'
     *  Lookup_n-D: '<S7>/CN Lookup Table'
     *  Product: '<S174>/Product3'
     *  Product: '<S7>/Product2'
     */
    rtb_Product3_ax = -(look2_binlxpw(rtb_Product3_ax, rtb_Gain_ii,
      rtCP__CNLookupTable_bp01Data_a, rtCP__CNLookupTable_bp02Data_o,
      rtCP__CNLookupTable_tableData_i, rtCP__CNLookupTable_maxIndex_a, 10U) *
                        rtb_Product2_e * 0.018);

    /* Math: '<S13>/Math Function1' incorporates:
     *  Math: '<S13>/Math Function'
     *  Sum: '<S13>/Sum of Elements'
     *
     * About '<S13>/Math Function1':
     *  Operator: sqrt
     */
    rtb_Product2_e = sqrt((rtb_Switch_d_idx_0 * rtb_Switch_d_idx_0 +
      rtb_Product1_kn) + rtb_Sum1_ox);

    /* Switch: '<S13>/Switch' incorporates:
     *  Constant: '<S13>/Constant'
     *  DotProduct: '<S7>/Dot Product3'
     *  Product: '<S13>/Product'
     *  Product: '<S7>/Product6'
     *  Sum: '<S4>/Minus'
     */
    if (rtb_Product2_e > 0.0) {
      rtb_Switch_d_idx_1 = rtb_airspeed_mps[1];
      rtb_Switch_d_idx_2 = rtb_TmpSignalConversionAtProd_0;
    } else {
      rtb_Switch_d_idx_0 *= 0.0;
      rtb_Product2_e = 1.0;
    }

    /* Sum: '<S7>/Sum1' incorporates:
     *  Product: '<S13>/Divide'
     *  Product: '<S7>/Product3'
     *  Product: '<S7>/Product4'
     */
    rtb_Product6_f[0] = rtb_Switch_d_idx_0 / rtb_Product2_e * rtb_Product3_ax +
      rtb_UnaryMinus_a;

    /* Product: '<S7>/Product3' incorporates:
     *  Constant: '<S7>/Constant'
     */
    rtb_TmpSignalConversionAtProd_0 = rtb_UnaryMinus_a * 0.0;

    /* Sum: '<S7>/Sum1' incorporates:
     *  Product: '<S13>/Divide'
     *  Product: '<S7>/Product3'
     *  Product: '<S7>/Product4'
     */
    rtb_Product6_f[1] = rtb_Switch_d_idx_1 / rtb_Product2_e * rtb_Product3_ax +
      rtb_TmpSignalConversionAtProd_0;
    rtb_Product6_f[2] = rtb_Switch_d_idx_2 / rtb_Product2_e * rtb_Product3_ax +
      rtb_TmpSignalConversionAtProd_0;

    /* Product: '<S12>/Element Product' incorporates:
     *  Product: '<S7>/Product5'
     */
    rtb_TmpSignalConversionAtProd_0 = rtb_Product6_f[0] * rtb_Product_kd;

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S12>/Element Product'
     *  Product: '<S7>/Product5'
     */
    rtb_UnaryMinus_a = rtb_Product_kd * rtb_Product6_f[2] - rtb_Product6_f[1] *
      rtb_Product_kd;
    rtb_finMomentArm_m[0] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[0] = (((rtb_Sum_j[0] + rtb_Sum_l4[0]) + rtb_Sum_bq[0]) + rtb_Sum_kx
                  [0]) + rtb_UnaryMinus_a;
    rtb_Add[3] = (((rtb_Sum1_p2[0] + rtb_Sum1_ny[0]) + rtb_Sum1_lp[0]) +
                  rtb_Sum1_b[0]) + rtb_Product6_f[0];

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S12>/Element Product'
     *  Product: '<S7>/Product5'
     */
    rtb_UnaryMinus_a = rtb_TmpSignalConversionAtProd_0 - rtb_Sum *
      rtb_Product6_f[2];
    rtb_finMomentArm_m[1] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[1] = (((rtb_Sum_j[1] + rtb_Sum_l4[1]) + rtb_Sum_bq[1]) + rtb_Sum_kx
                  [1]) + rtb_UnaryMinus_a;
    rtb_Add[4] = (((rtb_Sum1_p2[1] + rtb_Sum1_ny[1]) + rtb_Sum1_lp[1]) +
                  rtb_Sum1_b[1]) + rtb_Product6_f[1];

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S12>/Element Product'
     *  Product: '<S7>/Product5'
     */
    rtb_UnaryMinus_a = rtb_Sum * rtb_Product6_f[1] -
      rtb_TmpSignalConversionAtProd_0;
    rtb_finMomentArm_m[2] = rtb_UnaryMinus_a;

    /* Sum: '<S3>/Add' */
    rtb_Add[2] = (((rtb_Sum_j[2] + rtb_Sum_l4[2]) + rtb_Sum_bq[2]) + rtb_Sum_kx
                  [2]) + rtb_UnaryMinus_a;
    rtb_Add[5] = (((rtb_Sum1_p2[2] + rtb_Sum1_ny[2]) + rtb_Sum1_lp[2]) +
                  rtb_Sum1_b[2]) + rtb_Product6_f[2];

    /* Sum: '<S5>/Sum' */
    rtb_TmpSignalConversionAtProd_0 = (autocodePlant_B->Delay +
      rtb_gravityForceBdy_N[0]) + rtb_Add[3];

    /* Logic: '<S146>/Logical Operator' */
    rtb_max_relop_c = !rtb_Compare_n;

    /* Sum: '<S146>/Sum' incorporates:
     *  Constant: '<S146>/Constant'
     *  Constant: '<S6>/Constant2'
     *  MinMax: '<S146>/Max1'
     *  Product: '<S146>/Product1'
     *  Product: '<S146>/Product2'
     *  Sum: '<S5>/Sum'
     */
    autocodePlant_B->Sum[0] = fmax((real_T)rtb_Compare_n *
      rtb_TmpSignalConversionAtProd_0, 0.0) + rtb_TmpSignalConversionAtProd_0 *
      (real_T)rtb_max_relop_c;
    autocodePlant_B->Sum[1] = (rtb_gravityForceBdy_N[1] + rtb_Add[4]) * (real_T)
      rtb_max_relop_c;
    autocodePlant_B->Sum[2] = (rtb_gravityForceBdy_N[2] + rtb_Add[5]) * (real_T)
      rtb_max_relop_c;

    /* Product: '<S144>/Divide' incorporates:
     *  Constant: '<S5>/Constant'
     *  Sum: '<S148>/Sum1'
     */
    rtb_MathFunction[0] = (autocodePlant_B->Sum[0] + autocodePlant_ConstB.Switch)
      / 18.0;
    rtb_MathFunction[1] = (autocodePlant_B->Sum[1] + autocodePlant_ConstB.Switch)
      / 18.0;
    rtb_MathFunction[2] = (autocodePlant_B->Sum[2] + autocodePlant_ConstB.Switch)
      / 18.0;

    /* Sqrt: '<S165>/sqrt' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  Product: '<S166>/Product'
     *  Product: '<S166>/Product1'
     *  Product: '<S166>/Product2'
     *  Product: '<S166>/Product3'
     *  Sum: '<S166>/Sum'
     */
    rtb_Product2_e = sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
      autocodePlant_X->uDOFQuaternion_CSTATE[9] +
      autocodePlant_X->uDOFQuaternion_CSTATE[10] *
      autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[11] *
      autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
                          autocodePlant_X->uDOFQuaternion_CSTATE[12] *
                          autocodePlant_X->uDOFQuaternion_CSTATE[12]);

    /* Product: '<S161>/Product2' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Product_kd = autocodePlant_X->uDOFQuaternion_CSTATE[11] / rtb_Product2_e;

    /* Product: '<S161>/Product3' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Product3_ax = autocodePlant_X->uDOFQuaternion_CSTATE[12] /
      rtb_Product2_e;

    /* Product: '<S161>/Product1' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Sum = autocodePlant_X->uDOFQuaternion_CSTATE[10] / rtb_Product2_e;

    /* Product: '<S161>/Product' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_Product2_e = autocodePlant_X->uDOFQuaternion_CSTATE[9] / rtb_Product2_e;

    /* Product: '<S162>/Product7' incorporates:
     *  Product: '<S163>/Product7'
     */
    rtb_TmpSignalConversionAtProd_0 = rtb_Product3_ax * rtb_Product3_ax;

    /* Product: '<S162>/Product' incorporates:
     *  Product: '<S163>/Product'
     */
    rtb_UnaryMinus_a = rtb_Sum * rtb_Product_kd;

    /* Product: '<S162>/Product1' incorporates:
     *  Product: '<S163>/Product1'
     */
    rtb_Switch_d_idx_1 = rtb_Product2_e * rtb_Product3_ax;

    /* Product: '<S162>/Product3' incorporates:
     *  Product: '<S164>/Product'
     */
    rtb_Switch_d_idx_2 = rtb_Sum * rtb_Product3_ax;

    /* Product: '<S162>/Product2' incorporates:
     *  Product: '<S164>/Product1'
     */
    rtb_Product1_kn = rtb_Product2_e * rtb_Product_kd;

    /* Product: '<S162>/Product6' incorporates:
     *  Product: '<S164>/Product7'
     */
    rtb_Sum1_ox = rtb_Product_kd * rtb_Product_kd;

    /* Sum: '<S154>/fBdy_mps2' incorporates:
     *  Constant: '<S154>/gNed_mps2'
     *  Constant: '<S162>/Constant'
     *  Gain: '<S162>/Gain'
     *  Gain: '<S162>/Gain1'
     *  Gain: '<S162>/Gain2'
     *  Product: '<S162>/Product'
     *  Product: '<S162>/Product1'
     *  Product: '<S162>/Product2'
     *  Product: '<S162>/Product3'
     *  Product: '<S162>/Product4'
     *  Product: '<S162>/Product5'
     *  Product: '<S162>/Product6'
     *  Product: '<S162>/Product7'
     *  Product: '<S162>/Product8'
     *  Sum: '<S162>/Sum'
     *  Sum: '<S162>/Sum1'
     *  Sum: '<S162>/Sum2'
     *  Sum: '<S162>/Sum3'
     */
    autocodePlant_B->fBdy_mps2[0] = rtb_MathFunction[0] - ((((0.5 - rtb_Sum1_ox)
      - rtb_TmpSignalConversionAtProd_0) * 2.0 * 0.0 + (rtb_UnaryMinus_a +
      rtb_Switch_d_idx_1) * 2.0 * 0.0) + (rtb_Switch_d_idx_2 - rtb_Product1_kn) *
      2.0 * 9.81);

    /* Product: '<S163>/Product3' incorporates:
     *  Product: '<S164>/Product3'
     */
    rtb_Product3_ax *= rtb_Product_kd;

    /* Product: '<S163>/Product2' incorporates:
     *  Product: '<S164>/Product2'
     */
    rtb_Product2_e *= rtb_Sum;

    /* Sum: '<S163>/Sum3' incorporates:
     *  Constant: '<S163>/Constant'
     *  Product: '<S163>/Product6'
     *  Sum: '<S164>/Sum3'
     */
    rtb_Sum = 0.5 - rtb_Sum * rtb_Sum;

    /* Sum: '<S154>/fBdy_mps2' incorporates:
     *  Constant: '<S154>/gNed_mps2'
     *  Gain: '<S163>/Gain'
     *  Gain: '<S163>/Gain1'
     *  Gain: '<S163>/Gain2'
     *  Gain: '<S164>/Gain'
     *  Gain: '<S164>/Gain1'
     *  Gain: '<S164>/Gain2'
     *  Product: '<S163>/Product2'
     *  Product: '<S163>/Product3'
     *  Product: '<S163>/Product4'
     *  Product: '<S163>/Product5'
     *  Product: '<S163>/Product8'
     *  Product: '<S164>/Product4'
     *  Product: '<S164>/Product5'
     *  Product: '<S164>/Product8'
     *  Sum: '<S163>/Sum'
     *  Sum: '<S163>/Sum1'
     *  Sum: '<S163>/Sum2'
     *  Sum: '<S163>/Sum3'
     *  Sum: '<S164>/Sum'
     *  Sum: '<S164>/Sum1'
     *  Sum: '<S164>/Sum2'
     *  Sum: '<S164>/Sum3'
     */
    autocodePlant_B->fBdy_mps2[1] = rtb_MathFunction[1] - (((rtb_Sum -
      rtb_TmpSignalConversionAtProd_0) * 2.0 * 0.0 + (rtb_UnaryMinus_a -
      rtb_Switch_d_idx_1) * 2.0 * 0.0) + (rtb_Product2_e + rtb_Product3_ax) *
      2.0 * 9.81);
    autocodePlant_B->fBdy_mps2[2] = rtb_MathFunction[2] - (((rtb_Switch_d_idx_2
      + rtb_Product1_kn) * 2.0 * 0.0 + (rtb_Product3_ax - rtb_Product2_e) * 2.0 *
      0.0) + (rtb_Sum - rtb_Sum1_ox) * 2.0 * 9.81);
    if (tmp) {
      /* Product: '<S154>/scale factor and  cross-coupling' incorporates:
       *  Constant: '<S154>/Constant'
       */
      rtb_TmpSignalConversionAtProd_0 = autocodePlant_B->fBdy_mps2[1];
      rtb_UnaryMinus_a = autocodePlant_B->fBdy_mps2[0];
      rtb_Switch_d_idx_1 = autocodePlant_B->fBdy_mps2[2];

      /* Product: '<S156>/Product1' */
      rtb_Product3_ax = 0.0;
      rtb_Switch_d_idx_2 = 0.0;
      rtb_Sum = 0.0;
      for (i = 0; i < 3; i++) {
        /* ZeroOrderHold: '<S154>/Zero-Order Hold' incorporates:
         *  Constant: '<S154>/Constant'
         *  Product: '<S154>/scale factor and  cross-coupling'
         *  Sum: '<S154>/sum'
         */
        rtb_ZeroOrderHold_c[i] = ((rtCP__Constant_Value_dxg[i + 3] *
          rtb_TmpSignalConversionAtProd_0 + rtCP__Constant_Value_dxg[i] *
          rtb_UnaryMinus_a) + rtCP__Constant_Value_dxg[i + 6] *
          rtb_Switch_d_idx_1) + autocodePlant_B->biasnoise[i];

        /* Sum: '<S156>/bias + noise' incorporates:
         *  Gain: '<S170>/Output'
         *  RandomNumber: '<S170>/White Noise'
         */
        biasnoise_d[i] = 6.1075E-5 * autocodePlant_DW->NextOutput_i +
          rtb_ZeroOrderHold_a[i];

        /* Product: '<S156>/Product1' incorporates:
         *  Constant: '<S156>/Gs'
         *  UnitDelay: '<S156>/Unit Delay'
         */
        rtb_Product2_e = autocodePlant_DW->UnitDelay_DSTATE[i];
        rtb_Product3_ax += rtCP__Gs_Value[3 * i] * rtb_Product2_e;
        rtb_Switch_d_idx_2 += rtCP__Gs_Value[3 * i + 1] * rtb_Product2_e;
        rtb_Sum += rtCP__Gs_Value[3 * i + 2] * rtb_Product2_e;
      }

      /* Product: '<S156>/Product1' */
      Gdependent[2] = rtb_Sum;
      Gdependent[1] = rtb_Switch_d_idx_2;
      Gdependent[0] = rtb_Product3_ax;

      /* Product: '<S156>/Product' incorporates:
       *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
       */
      rtb_Product2_e = autocodePlant_X->uDOFQuaternion_CSTATE[7];
      rtb_TmpSignalConversionAtProd_0 = autocodePlant_X->uDOFQuaternion_CSTATE[6];
      rtb_UnaryMinus_a = autocodePlant_X->uDOFQuaternion_CSTATE[8];
      for (i = 0; i < 3; i++) {
        /* ZeroOrderHold: '<S156>/Zero-Order Hold' incorporates:
         *  Constant: '<S156>/   '
         *  Product: '<S156>/Product'
         *  Sum: '<S156>/      '
         */
        rtb_ZeroOrderHold_a[i] = (((rtCP___Value_n[i + 3] * rtb_Product2_e +
          rtCP___Value_n[i] * rtb_TmpSignalConversionAtProd_0) +
          rtCP___Value_n[i + 6] * rtb_UnaryMinus_a) + biasnoise_d[i]) +
          Gdependent[i];

        /* Gain: '<S173>/Output' incorporates:
         *  RandomNumber: '<S173>/White Noise'
         */
        autocodePlant_B->Output[i] = 140.0 * autocodePlant_DW->NextOutput_b;
      }

      /* RelationalOperator: '<S206>/Relational Operator' incorporates:
       *  Constant: '<S157>/decimal year'
       *  Memory: '<S206>/otime'
       */
      rtb_RelationalOperator = (autocodePlant_DW->otime_PreviousInput !=
        2026.6657534246576);
    }

    /* FlatEarth2LLA: '<S157>/Flat Earth to LLA' incorporates:
     *  Constant: '<S157>/ground altitude'
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_TmpSignalConversionAtProd_0 = fabs
      ((autocodePlant_X->uDOFQuaternion_CSTATE[3] - 0.0 *
        autocodePlant_X->uDOFQuaternion_CSTATE[4]) / 6.3354393272928195E+6);
    rtb_Switch_d_idx_1 = (autocodePlant_X->uDOFQuaternion_CSTATE[3] - 0.0 *
                          autocodePlant_X->uDOFQuaternion_CSTATE[4]) /
      6.3354393272928195E+6;
    rtb_UnaryMinus_a = (0.0 * autocodePlant_X->uDOFQuaternion_CSTATE[3] +
                        autocodePlant_X->uDOFQuaternion_CSTATE[4]) / 6.378137E+6
      + 0.17453292519943295;
    if (rtb_TmpSignalConversionAtProd_0 > 3.141592653589793) {
      rtb_Switch_d_idx_1 = rt_modd_snf((autocodePlant_X->uDOFQuaternion_CSTATE[3]
        - 0.0 * autocodePlant_X->uDOFQuaternion_CSTATE[4]) /
        6.3354393272928195E+6 + 3.141592653589793, 6.283185307179586) -
        3.141592653589793;
      rtb_TmpSignalConversionAtProd_0 = fabs(rtb_Switch_d_idx_1);
    }

    if (rtb_TmpSignalConversionAtProd_0 > 1.5707963267948966) {
      rtb_UnaryMinus_a = ((0.0 * autocodePlant_X->uDOFQuaternion_CSTATE[3] +
                           autocodePlant_X->uDOFQuaternion_CSTATE[4]) /
                          6.378137E+6 + 0.17453292519943295) + 3.141592653589793;
      if (rtIsNaN(rtb_Switch_d_idx_1)) {
        rtb_Product2_e = (rtNaN);
      } else if (rtb_Switch_d_idx_1 < 0.0) {
        rtb_Product2_e = -1.0;
      } else {
        rtb_Product2_e = (rtb_Switch_d_idx_1 > 0.0);
      }

      rtb_Switch_d_idx_1 = (1.5707963267948966 -
                            (rtb_TmpSignalConversionAtProd_0 -
        1.5707963267948966)) * rtb_Product2_e;
    }

    if (fabs(rtb_UnaryMinus_a) > 3.141592653589793) {
      rtb_TmpSignalConversionAtProd_0 = rt_remd_snf(rtb_UnaryMinus_a,
        6.283185307179586);
      rtb_UnaryMinus_a = rtb_TmpSignalConversionAtProd_0 - trunc
        (rtb_TmpSignalConversionAtProd_0 / 3.141592653589793) *
        6.283185307179586;
    }

    rtb_TmpSignalConversionAtProd_0 = rtb_Switch_d_idx_1 * 180.0 /
      3.141592653589793;
    rtb_UnaryMinus_a = rtb_UnaryMinus_a * 180.0 / 3.141592653589793;
    rtb_Switch_d_idx_1 = -(autocodePlant_X->uDOFQuaternion_CSTATE[5] + 182.0);

    /* End of FlatEarth2LLA: '<S157>/Flat Earth to LLA' */

    /* Switch: '<S195>/Switch' incorporates:
     *  Abs: '<S195>/Abs'
     *  Bias: '<S195>/Bias'
     *  Bias: '<S195>/Bias1'
     *  Constant: '<S195>/Constant2'
     *  Constant: '<S198>/Constant'
     *  Math: '<S195>/Math Function1'
     *  RelationalOperator: '<S198>/Compare'
     */
    if (fabs(rtb_TmpSignalConversionAtProd_0) > 180.0) {
      rtb_Product2_e = rt_modd_snf(rtb_TmpSignalConversionAtProd_0 + 180.0,
        360.0) - 180.0;
    } else {
      rtb_Product2_e = rtb_TmpSignalConversionAtProd_0;
    }

    /* End of Switch: '<S195>/Switch' */

    /* Abs: '<S191>/Abs1' */
    rtb_Product3_ax = fabs(rtb_Product2_e);

    /* RelationalOperator: '<S193>/Compare' incorporates:
     *  Constant: '<S193>/Constant'
     */
    rtb_min_relop_n = (rtb_Product3_ax > 90.0);

    /* Switch: '<S185>/Switch1' incorporates:
     *  Constant: '<S185>/Constant'
     *  Constant: '<S185>/Constant1'
     */
    if (rtb_min_relop_n) {
      i = 180;
    } else {
      i = 0;
    }

    /* Sum: '<S185>/Sum' incorporates:
     *  Switch: '<S185>/Switch1'
     */
    autocodePlant_B->Switch = (real_T)i + rtb_UnaryMinus_a;

    /* Switch: '<S192>/Switch' incorporates:
     *  Abs: '<S192>/Abs'
     *  Constant: '<S199>/Constant'
     *  RelationalOperator: '<S199>/Compare'
     */
    if (fabs(autocodePlant_B->Switch) > 180.0) {
      /* Sum: '<S185>/Sum' incorporates:
       *  Bias: '<S192>/Bias'
       *  Bias: '<S192>/Bias1'
       *  Constant: '<S192>/Constant2'
       *  Math: '<S192>/Math Function1'
       *  Switch: '<S192>/Switch'
       */
      autocodePlant_B->Switch = rt_modd_snf(autocodePlant_B->Switch + 180.0,
        360.0) - 180.0;
    }

    /* End of Switch: '<S192>/Switch' */

    /* If: '<S194>/If' incorporates:
     *  Abs: '<S194>/Abs'
     */
    rtPrevAction = autocodePlant_DW->If_ActiveSubsystem;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      rtAction = (int8_T)!(rtb_Product3_ax > 0.0);
      autocodePlant_DW->If_ActiveSubsystem = rtAction;
    } else {
      rtAction = autocodePlant_DW->If_ActiveSubsystem;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&autocodePlant_M->solverInfo,
        true);
    }

    if (rtAction == 0) {
      /* Outputs for IfAction SubSystem: '<S194>/If Action Subsystem' incorporates:
       *  ActionPort: '<S196>/Action Port'
       */
      /* Merge: '<S194>/Merge' incorporates:
       *  Abs: '<S194>/Abs'
       *  Product: '<S196>/Divide'
       */
      autocodePlant_B->Merge = rtb_Product2_e / rtb_Product3_ax;

      /* End of Outputs for SubSystem: '<S194>/If Action Subsystem' */

      /* Outputs for IfAction SubSystem: '<S194>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S197>/Action Port'
       */
    } else if (rtmIsMajorTimeStep(autocodePlant_M) &&
               autocodePlant_M->Timing.TaskCounters.TID[1] == 0) {
      /* Merge: '<S194>/Merge' incorporates:
       *  Constant: '<S197>/Constant'
       *  SignalConversion generated from: '<S197>/zero'
       */
      autocodePlant_B->Merge = 0.0;

      /* End of Outputs for SubSystem: '<S194>/If Action Subsystem1' */
    }

    /* End of If: '<S194>/If' */

    /* Switch: '<S191>/Switch' */
    if (rtb_min_relop_n) {
      /* Switch: '<S191>/Switch' incorporates:
       *  Bias: '<S191>/Bias'
       *  Bias: '<S191>/Bias1'
       *  Gain: '<S191>/Gain'
       *  Product: '<S191>/Divide1'
       */
      autocodePlant_B->Switch_l = (-(rtb_Product3_ax - 90.0) + 90.0) *
        autocodePlant_B->Merge;
    } else {
      /* Switch: '<S191>/Switch' */
      autocodePlant_B->Switch_l = rtb_Product2_e;
    }

    /* End of Switch: '<S191>/Switch' */

    /* UnitConversion: '<S250>/Unit Conversion' */
    /* Unit Conversion - from: deg to: rad
       Expression: output = (0.0174533*input) + (0) */
    rtb_ug_p_idx_0 = 0.017453292519943295 * autocodePlant_B->Switch;
    rtb_Switch_d_idx_0 = 0.017453292519943295 * autocodePlant_B->Switch_l;

    /* Trigonometry: '<S203>/sincos' */
    rtb_Switch_d_idx_2 = sin(rtb_ug_p_idx_0);
    rtb_Sum = cos(rtb_ug_p_idx_0);
    rtb_Product2_e = sin(rtb_Switch_d_idx_0);
    rtb_Product3_ax = cos(rtb_Switch_d_idx_0);

    /* Outputs for Enabled SubSystem: '<S189>/Convert from geodetic to  spherical coordinates ' incorporates:
     *  EnablePort: '<S202>/Enable'
     */
    if (tmp) {
      if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
        /* RelationalOperator: '<S205>/Relational Operator' incorporates:
         *  Memory: '<S205>/olon'
         */
        autocodePlant_DW->Convertfromgeodetictosphericalc =
          (autocodePlant_B->Switch != autocodePlant_DW->olon_PreviousInput);
      }

      /* Memory: '<S204>/olat' */
      autocodePlant_B->olat = autocodePlant_DW->olat_PreviousInput;
    }

    if (autocodePlant_DW->Convertfromgeodetictosphericalc) {
      if (rtmIsMajorTimeStep(autocodePlant_M) &&
          autocodePlant_M->Timing.TaskCounters.TID[1] == 0) {
        /* Outputs for Iterator SubSystem: '<S202>/For Iterator Subsystem' incorporates:
         *  ForIterator: '<S249>/For Iterator'
         */
        for (s249_iter = 0; s249_iter < 11; s249_iter++) {
          /* Switch: '<S249>/cp[m-1] sp[m-1]' incorporates:
           *  SignalConversion generated from: '<S202>/cp[2]'
           *  SignalConversion generated from: '<S202>/sp[2]'
           *  UnitDelay: '<S249>/Unit Delay1'
           */
          if (s249_iter > 0) {
            rtb_Sum1_ox = autocodePlant_DW->UnitDelay1_DSTATE[0];
            rtb_Product_kd = autocodePlant_DW->UnitDelay1_DSTATE[1];
          } else {
            rtb_Sum1_ox = rtb_Sum;
            rtb_Product_kd = rtb_Switch_d_idx_2;
          }

          /* End of Switch: '<S249>/cp[m-1] sp[m-1]' */

          /* Sum: '<S249>/Sum2' incorporates:
           *  Product: '<S249>/Product1'
           *  Product: '<S249>/Product2'
           *  SignalConversion generated from: '<S202>/cp[2]'
           *  SignalConversion generated from: '<S202>/sp[2]'
           */
          rtb_Product1_kn = rtb_Sum1_ox * rtb_Switch_d_idx_2 + rtb_Product_kd *
            rtb_Sum;

          /* Sum: '<S249>/Sum1' incorporates:
           *  Product: '<S249>/Product3'
           *  Product: '<S249>/Product8'
           *  SignalConversion generated from: '<S202>/cp[2]'
           *  SignalConversion generated from: '<S202>/sp[2]'
           */
          rtb_Sum1_ox = rtb_Sum1_ox * rtb_Sum - rtb_Product_kd *
            rtb_Switch_d_idx_2;

          /* Assignment: '<S249>/Assignment' incorporates:
           *  Assignment: '<S249>/Assignment1'
           *  Constant: '<S249>/Constant'
           */
          if (s249_iter == 0) {
            memcpy(&autocodePlant_B->Assignment[0], &rtCP__Constant_Value_f[0],
                   11U * sizeof(real_T));

            /* Assignment: '<S249>/Assignment1' incorporates:
             *  Constant: '<S249>/Constant'
             *  Constant: '<S249>/Constant1'
             */
            memcpy(&autocodePlant_B->Assignment1[0], &rtCP__Constant1_Value_a[0],
                   11U * sizeof(real_T));
          }

          autocodePlant_B->Assignment[s249_iter] = rtb_Product1_kn;

          /* End of Assignment: '<S249>/Assignment' */

          /* Assignment: '<S249>/Assignment1' */
          autocodePlant_B->Assignment1[s249_iter] = rtb_Sum1_ox;

          /* Update for UnitDelay: '<S249>/Unit Delay1' */
          autocodePlant_DW->UnitDelay1_DSTATE[0] = rtb_Sum1_ox;
          autocodePlant_DW->UnitDelay1_DSTATE[1] = rtb_Product1_kn;
        }

        /* End of Outputs for SubSystem: '<S202>/For Iterator Subsystem' */
      }

      /* SignalConversion generated from: '<S202>/cp[13]' incorporates:
       *  Constant: '<S202>/cp[1]'
       *  SignalConversion generated from: '<S202>/cp[2]'
       */
      autocodePlant_B->OutportBufferForcp13[0] = 1.0;
      autocodePlant_B->OutportBufferForcp13[1] = rtb_Sum;

      /* SignalConversion generated from: '<S202>/sp[13]' incorporates:
       *  Constant: '<S202>/sp[1]'
       *  SignalConversion generated from: '<S202>/sp[2]'
       */
      autocodePlant_B->OutportBufferForsp13[0] = 0.0;
      autocodePlant_B->OutportBufferForsp13[1] = rtb_Switch_d_idx_2;

      /* SignalConversion generated from: '<S202>/cp[13]' */
      memcpy(&autocodePlant_B->OutportBufferForcp13[2],
             &autocodePlant_B->Assignment1[0], 11U * sizeof(real_T));

      /* SignalConversion generated from: '<S202>/sp[13]' */
      memcpy(&autocodePlant_B->OutportBufferForsp13[2],
             &autocodePlant_B->Assignment[0], 11U * sizeof(real_T));
    }

    /* End of Outputs for SubSystem: '<S189>/Convert from geodetic to  spherical coordinates ' */

    /* Gain: '<S172>/Gain' */
    autocodePlant_B->Gain = 0.001 * rtb_Switch_d_idx_1;
    if (tmp) {
      /* Memory: '<S204>/oalt' */
      autocodePlant_B->oalt = autocodePlant_DW->oalt_PreviousInput;
    }

    /* Logic: '<S204>/Logical Operator' incorporates:
     *  RelationalOperator: '<S204>/Relational Operator'
     *  RelationalOperator: '<S204>/Relational Operator1'
     */
    rtb_min_relop_n = ((autocodePlant_B->Switch_l != autocodePlant_B->olat) ||
                       (autocodePlant_B->Gain != autocodePlant_B->oalt));

    /* Product: '<S203>/Product' */
    rtb_Product1_kn = rtb_Product2_e * rtb_Product2_e;

    /* Product: '<S203>/Product1' */
    rtb_Product_kd = rtb_Product3_ax * rtb_Product3_ax;

    /* Outputs for Enabled SubSystem: '<S189>/Convert from geodetic to  spherical coordinates' incorporates:
     *  EnablePort: '<S201>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      autocodePlant_DW->Convertfromgeodetictospherica_p = rtb_min_relop_n;
    }

    if (autocodePlant_DW->Convertfromgeodetictospherica_p) {
      /* Sqrt: '<S243>/sqrt' incorporates:
       *  Product: '<S243>/Product10'
       *  Product: '<S243>/Product9'
       *  Sum: '<S243>/Sum7'
       */
      rtb_Sum1_ox = sqrt(rtb_Product_kd * autocodePlant_ConstB.a2 +
                         autocodePlant_ConstB.b2 * rtb_Product1_kn);

      /* Sqrt: '<S244>/sqrt' incorporates:
       *  Product: '<S244>/Product'
       *  Sum: '<S244>/Sum'
       */
      rtb_Switch_d_idx_2 = sqrt(autocodePlant_ConstB.a2 - rtb_Product1_kn *
        autocodePlant_ConstB.c2);

      /* Product: '<S201>/Product1' */
      rtb_Sum = rtb_Switch_d_idx_2 * autocodePlant_B->Gain;

      /* Sqrt: '<S201>/sqrt' incorporates:
       *  Gain: '<S246>/Gain'
       *  Product: '<S246>/Product1'
       *  Product: '<S246>/Product6'
       *  Product: '<S246>/Product7'
       *  Product: '<S246>/Product8'
       *  Sum: '<S246>/Sum5'
       *  Sum: '<S246>/Sum6'
       */
      autocodePlant_B->sqrt_b = sqrt((autocodePlant_ConstB.a4 -
        autocodePlant_ConstB.c4 * rtb_Product1_kn) / (rtb_Switch_d_idx_2 *
        rtb_Switch_d_idx_2) + (2.0 * rtb_Sum + autocodePlant_B->Gain *
        autocodePlant_B->Gain));

      /* Product: '<S241>/Product11' incorporates:
       *  Sum: '<S241>/Sum8'
       */
      autocodePlant_B->Product11 = (autocodePlant_B->Gain + rtb_Sum1_ox) /
        autocodePlant_B->sqrt_b;

      /* Product: '<S247>/Product12' incorporates:
       *  Product: '<S247>/Product1'
       */
      autocodePlant_B->Product12 = autocodePlant_ConstB.c2_l /
        (autocodePlant_B->sqrt_b * rtb_Sum1_ox) * rtb_Product3_ax *
        rtb_Product2_e;

      /* Sum: '<S245>/Sum2' */
      rtb_Sum1_ox = autocodePlant_ConstB.a2 + rtb_Sum;

      /* Sum: '<S245>/Sum1' */
      rtb_Sum += autocodePlant_ConstB.b2;

      /* Product: '<S242>/Product4' incorporates:
       *  Product: '<S242>/Product3'
       *  Product: '<S245>/Product1'
       *  Product: '<S245>/Product2'
       *  Sqrt: '<S242>/sqrt'
       *  Sum: '<S242>/Sum3'
       */
      autocodePlant_B->Product4 = rtb_Product2_e / sqrt(rtb_Sum1_ox *
        rtb_Sum1_ox / (rtb_Sum * rtb_Sum) * rtb_Product_kd + rtb_Product1_kn);

      /* Sqrt: '<S248>/sqrt' incorporates:
       *  Constant: '<S248>/Constant'
       *  Product: '<S248>/Product5'
       *  Sum: '<S248>/Sum4'
       */
      autocodePlant_B->sqrt_k = sqrt(1.0 - autocodePlant_B->Product4 *
        autocodePlant_B->Product4);
    }

    /* End of Outputs for SubSystem: '<S189>/Convert from geodetic to  spherical coordinates' */

    /* Product: '<S189>/aor' incorporates:
     *  Constant: '<S189>/re'
     */
    rtb_Product3_ax = 6371.2 / autocodePlant_B->sqrt_b;
    if (tmp) {
      /* Outputs for Iterator SubSystem: '<S189>/Compute magnetic vector in spherical coordinates' incorporates:
       *  ForIterator: '<S200>/For Iterator'
       */
      /* InitializeConditions for UnitDelay: '<S200>/Unit Delay2' */
      autocodePlant_DW->UnitDelay2_DSTATE[0] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[1] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[2] = 0.0;
      autocodePlant_DW->UnitDelay2_DSTATE[3] = 0.0;

      /* InitializeConditions for UnitDelay: '<S200>/Unit Delay' */
      rtb_Switch_d_idx_2 = 0.0;
      for (s249_iter = 0; s249_iter < 12; s249_iter++) {
        /* Switch: '<S200>/ar(n)' incorporates:
         *  Product: '<S189>/ar'
         */
        if (s249_iter <= 0) {
          rtb_Switch_d_idx_2 = rtb_Product3_ax * rtb_Product3_ax;
        }

        /* End of Switch: '<S200>/ar(n)' */

        /* Product: '<S200>/Product8' incorporates:
         *  UnitDelay: '<S200>/Unit Delay'
         */
        rtb_Switch_d_idx_2 *= rtb_Product3_ax;

        /* Outputs for Iterator SubSystem: '<S200>/For Iterator Subsystem' incorporates:
         *  ForIterator: '<S208>/For Iterator'
         */
        /* InitializeConditions for UnitDelay: '<S209>/Unit Delay3' */
        rtb_Sum = 0.0;

        /* InitializeConditions for UnitDelay: '<S209>/Unit Delay2' */
        rtb_Product1_kn = 0.0;

        /* InitializeConditions for UnitDelay: '<S209>/Unit Delay1' */
        rtb_Sum1_ox = 0.0;

        /* InitializeConditions for UnitDelay: '<S209>/Unit Delay4' */
        rtb_Product_kd = 0.0;
        for (i = 0; i < 6; i++) {
          ForIterator_IterationMarker[i] = 1U;
        }

        /* Sum: '<S200>/Sum' incorporates:
         *  Constant: '<S215>/Constant'
         *  Constant: '<S215>/Constant1'
         *  Logic: '<S215>/Logical Operator'
         *  RelationalOperator: '<S215>/Relational Operator'
         *  RelationalOperator: '<S215>/Relational Operator1'
         *  SignalConversion generated from: '<S210>/Enable'
         *  Sum: '<S208>/Sum1'
         */
        for (s208_iter = 1; s208_iter <= s249_iter + 2; s208_iter++) {
          /* Outputs for Enabled SubSystem: '<S208>/Time adjust the gauss coefficients' incorporates:
           *  EnablePort: '<S211>/Enable'
           */
          if (rtb_RelationalOperator) {
            /* Assignment: '<S211>/Assignment' */
            if (ForIterator_IterationMarker[4] < 2) {
              ForIterator_IterationMarker[4] = 2U;

              /* Assignment: '<S211>/Assignment' incorporates:
               *  UnitDelay: '<S211>/Unit Delay'
               */
              memcpy(&autocodePlant_B->Assignment_o[0],
                     &autocodePlant_DW->UnitDelay_DSTATE_e[0], 169U * sizeof
                     (real_T));
            }

            /* Outputs for Atomic SubSystem: '<S211>/If Action Subsystem' */
            /* Selector: '<S237>/c[m][n]' incorporates:
             *  Assignment: '<S211>/Assignment'
             *  Constant: '<S211>/cd[maxdef][maxdef]'
             *  Selector: '<S237>/cd[m][n]'
             *  Sum: '<S237>/Sum2'
             */
            i = ((s249_iter + 1) * 13 + s208_iter) - 1;

            /* Assignment: '<S211>/Assignment' incorporates:
             *  Constant: '<S211>/c[maxdef][maxdef]'
             *  Constant: '<S211>/cd[maxdef][maxdef]'
             *  Product: '<S237>/Product'
             *  Selector: '<S237>/c[m][n]'
             *  Selector: '<S237>/cd[m][n]'
             *  Sum: '<S237>/Sum'
             */
            autocodePlant_B->Assignment_o[i] = rtCP__cdmaxdefmaxdef_Value[i] *
              autocodePlant_ConstB.Sum_dd + rtCP__cmaxdefmaxdef_Value[i];

            /* End of Outputs for SubSystem: '<S211>/If Action Subsystem' */

            /* Switch: '<S238>/tc_old' incorporates:
             *  UnitDelay: '<S238>/Unit Delay'
             */
            if (s249_iter <= 0) {
              memset(&autocodePlant_DW->UnitDelay_DSTATE_k[0], 0, 169U * sizeof
                     (real_T));
            }

            /* End of Switch: '<S238>/tc_old' */

            /* If: '<S238>/If' incorporates:
             *  Sum: '<S208>/Sum1'
             */
            if (s208_iter - 1 != 0) {
              /* Outputs for IfAction SubSystem: '<S238>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S239>/Action Port'
               */
              /* Assignment: '<S239>/Assignment2' */
              if (ForIterator_IterationMarker[5] < 2) {
                ForIterator_IterationMarker[5] = 2U;

                /* Assignment: '<S239>/Assignment2' incorporates:
                 *  Switch: '<S238>/tc_old'
                 */
                memcpy(&autocodePlant_B->Assignment2[0],
                       &autocodePlant_DW->UnitDelay_DSTATE_k[0], 169U * sizeof
                       (real_T));
              }

              /* Selector: '<S239>/c[m][n]' incorporates:
               *  Assignment: '<S239>/Assignment2'
               *  Constant: '<S211>/cd[maxdef][maxdef]'
               *  Selector: '<S239>/cd[m][n]'
               *  Sum: '<S239>/Sum2'
               */
              i = ((s208_iter - 2) * 13 + s249_iter) + 1;

              /* Assignment: '<S239>/Assignment2' incorporates:
               *  Constant: '<S211>/c[maxdef][maxdef]'
               *  Constant: '<S211>/cd[maxdef][maxdef]'
               *  Product: '<S239>/Product'
               *  Selector: '<S239>/c[m][n]'
               *  Selector: '<S239>/cd[m][n]'
               *  Sum: '<S239>/Sum'
               *  Sum: '<S239>/Sum2'
               */
              autocodePlant_B->Assignment2[i] = rtCP__cdmaxdefmaxdef_Value[i] *
                autocodePlant_ConstB.Sum_dd + rtCP__cmaxdefmaxdef_Value[i];

              /* Gain: '<S239>/Gain' incorporates:
               *  Assignment: '<S239>/Assignment2'
               *  Merge: '<S238>/Merge'
               *  UnitDelay: '<S238>/Unit Delay'
               */
              memcpy(&autocodePlant_DW->UnitDelay_DSTATE_k[0],
                     &autocodePlant_B->Assignment2[0], 169U * sizeof(real_T));

              /* End of Outputs for SubSystem: '<S238>/If Action Subsystem1' */
            }

            /* End of If: '<S238>/If' */
            for (i = 0; i < 169; i++) {
              /* Sum: '<S211>/Sum2' incorporates:
               *  Assignment: '<S211>/Assignment'
               */
              rtb_Product2_e = autocodePlant_B->Assignment_o[i];

              /* Sum: '<S211>/Sum2' incorporates:
               *  Assignment: '<S211>/Assignment'
               *  Merge: '<S238>/Merge'
               *  UnitDelay: '<S238>/Unit Delay'
               */
              autocodePlant_B->Sum2_p[i] = rtb_Product2_e +
                autocodePlant_DW->UnitDelay_DSTATE_k[i];

              /* Update for UnitDelay: '<S211>/Unit Delay' incorporates:
               *  Assignment: '<S211>/Assignment'
               */
              autocodePlant_DW->UnitDelay_DSTATE_e[i] = rtb_Product2_e;
            }
          }

          /* End of Outputs for SubSystem: '<S208>/Time adjust the gauss coefficients' */

          /* If: '<S214>/If' incorporates:
           *  Sum: '<S208>/Sum1'
           */
          if (s208_iter - 1 == 0) {
            /* Outputs for IfAction SubSystem: '<S214>/If Action Subsystem' incorporates:
             *  ActionPort: '<S220>/Action Port'
             */
            /* Product: '<S220>/Product' incorporates:
             *  Constant: '<S220>/Constant'
             *  Selector: '<S220>/Selector'
             *  Sum: '<S220>/Sum'
             */
            i = (s249_iter + 1) * 13;

            /* Merge: '<S214>/Merge' incorporates:
             *  Gain: '<S220>/Gain1'
             *  Product: '<S220>/Product'
             *  Selector: '<S214>/cp[m+1]'
             *  Selector: '<S220>/Selector'
             *  Sum: '<S211>/Sum2'
             */
            rtb_ug_p_idx_0 = autocodePlant_B->OutportBufferForcp13[s208_iter - 1]
              * autocodePlant_B->Sum2_p[i];

            /* Merge: '<S214>/Merge1' incorporates:
             *  Gain: '<S220>/Gain2'
             *  Product: '<S220>/Product'
             *  Selector: '<S214>/sp[m+1]'
             *  Selector: '<S220>/Selector'
             *  Sum: '<S211>/Sum2'
             */
            rtb_Switch_d_idx_0 = autocodePlant_B->OutportBufferForsp13[s208_iter
              - 1] * autocodePlant_B->Sum2_p[i];

            /* End of Outputs for SubSystem: '<S214>/If Action Subsystem' */
          } else {
            /* Outputs for IfAction SubSystem: '<S214>/If Action Subsystem1' incorporates:
             *  ActionPort: '<S221>/Action Port'
             */
            /* Product: '<S221>/Product' incorporates:
             *  Constant: '<S222>/Constant'
             *  Selector: '<S221>/Selector'
             *  Sum: '<S222>/Sum'
             */
            i = ((s249_iter + 1) * 13 + s208_iter) - 1;

            /* Product: '<S221>/Product1' incorporates:
             *  Selector: '<S221>/Selector1'
             *  Sum: '<S223>/Sum'
             */
            rtb_Sum2_d = ((s208_iter - 2) * 13 + s249_iter) + 1;

            /* Merge: '<S214>/Merge' incorporates:
             *  Product: '<S221>/Product'
             *  Product: '<S221>/Product1'
             *  Selector: '<S214>/cp[m+1]'
             *  Selector: '<S214>/sp[m+1]'
             *  Selector: '<S221>/Selector'
             *  Selector: '<S221>/Selector1'
             *  Sum: '<S211>/Sum2'
             *  Sum: '<S221>/Sum'
             */
            rtb_ug_p_idx_0 = autocodePlant_B->OutportBufferForcp13[s208_iter - 1]
              * autocodePlant_B->Sum2_p[i] +
              autocodePlant_B->OutportBufferForsp13[s208_iter - 1] *
              autocodePlant_B->Sum2_p[rtb_Sum2_d];

            /* Merge: '<S214>/Merge1' incorporates:
             *  Product: '<S221>/Product'
             *  Product: '<S221>/Product1'
             *  Selector: '<S214>/cp[m+1]'
             *  Selector: '<S214>/sp[m+1]'
             *  Selector: '<S221>/Selector'
             *  Selector: '<S221>/Selector1'
             *  Sum: '<S211>/Sum2'
             *  Sum: '<S221>/Sum1'
             */
            rtb_Switch_d_idx_0 = autocodePlant_B->OutportBufferForsp13[s208_iter
              - 1] * autocodePlant_B->Sum2_p[i] -
              autocodePlant_B->OutportBufferForcp13[s208_iter - 1] *
              autocodePlant_B->Sum2_p[rtb_Sum2_d];

            /* End of Outputs for SubSystem: '<S214>/If Action Subsystem1' */
          }

          /* End of If: '<S214>/If' */

          /* Outputs for Enabled SubSystem: '<S208>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' incorporates:
           *  EnablePort: '<S210>/Enable'
           */
          if (rtb_min_relop_n) {
            /* If: '<S210>/if n == m elseif (n==1&m==0) elseif (n>1&m~=n)' incorporates:
             *  Sum: '<S208>/Sum1'
             */
            if (s249_iter + 1 == s208_iter - 1) {
              /* Outputs for IfAction SubSystem: '<S210>/If Action Subsystem' incorporates:
               *  ActionPort: '<S224>/Action Port'
               */
              /* Selector: '<S224>/Selector' incorporates:
               *  Gain: '<S228>/Gain'
               *  Sum: '<S228>/Sum1'
               *  Sum: '<S228>/Sum2'
               */
              rtb_Sum2_d = mul_s32_sat(13, s208_iter - 2);
              if (rtb_Sum2_d > 2147483646 - s249_iter) {
                i = MAX_int32_T;
              } else {
                i = (s249_iter + rtb_Sum2_d) + 1;
              }

              /* Merge: '<S210>/Merge1' incorporates:
               *  Product: '<S224>/Product'
               *  Product: '<S224>/Product2'
               *  Selector: '<S224>/Selector'
               *  Selector: '<S224>/Selector1'
               *  Sum: '<S224>/Sum'
               *  Sum: '<S228>/Sum1'
               *  UnitDelay: '<S210>/Unit Delay'
               *  UnitDelay: '<S210>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = autocodePlant_DW->UnitDelay_DSTATE_o
                [(13 * s249_iter + s208_iter) - 2] * autocodePlant_B->sqrt_k +
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->Product4;

              /* Selector: '<S224>/Selector' incorporates:
               *  Sum: '<S228>/Sum1'
               */
              if (rtb_Sum2_d > 2147483646 - s249_iter) {
                i = MAX_int32_T;
              } else {
                i = (s249_iter + rtb_Sum2_d) + 1;
              }

              /* Merge: '<S210>/Merge' incorporates:
               *  Product: '<S224>/Product1'
               *  Selector: '<S224>/Selector'
               *  Sum: '<S228>/Sum1'
               *  UnitDelay: '<S210>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->sqrt_k;

              /* End of Outputs for SubSystem: '<S210>/If Action Subsystem' */
            } else if ((s249_iter == 0) && (s208_iter - 1 == 0)) {
              /* Outputs for IfAction SubSystem: '<S210>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S225>/Action Port'
               */
              /* Selector: '<S225>/Selector' incorporates:
               *  Gain: '<S230>/Gain'
               *  Sum: '<S230>/Sum1'
               */
              rtb_Sum2_d = mul_s32_sat(13, 0);
              if (rtb_Sum2_d > 2147483646) {
                i = MAX_int32_T;
              } else {
                i = rtb_Sum2_d + 1;
              }

              /* Merge: '<S210>/Merge1' incorporates:
               *  Product: '<S225>/Product'
               *  Product: '<S225>/Product2'
               *  Selector: '<S225>/Selector'
               *  Selector: '<S225>/Selector1'
               *  Sum: '<S225>/Sum'
               *  Sum: '<S230>/Sum1'
               *  Sum: '<S231>/Sum'
               *  UnitDelay: '<S210>/Unit Delay'
               *  UnitDelay: '<S210>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = autocodePlant_B->Product4 *
                autocodePlant_DW->UnitDelay_DSTATE_o[0] -
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->sqrt_k;

              /* Selector: '<S225>/Selector' incorporates:
               *  Sum: '<S230>/Sum1'
               */
              if (rtb_Sum2_d > 2147483646) {
                i = MAX_int32_T;
              } else {
                i = rtb_Sum2_d + 1;
              }

              /* Merge: '<S210>/Merge' incorporates:
               *  Product: '<S225>/Product3'
               *  Selector: '<S225>/Selector'
               *  Sum: '<S230>/Sum1'
               *  UnitDelay: '<S210>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->Product4;

              /* End of Outputs for SubSystem: '<S210>/If Action Subsystem1' */
            } else if ((s249_iter > 0) && (s249_iter + 1 != s208_iter - 1)) {
              /* Outputs for IfAction SubSystem: '<S210>/If Action Subsystem2' incorporates:
               *  ActionPort: '<S226>/Action Port'
               */
              /* Gain: '<S232>/Gain' */
              rtb_Sum2_d = mul_s32_sat(13, s208_iter - 1);

              /* Switch: '<S226>/Switch1' incorporates:
               *  Constant: '<S226>/Constant1'
               *  RelationalOperator: '<S236>/Relational Operator'
               *  Selector: '<S226>/Selector'
               *  Sum: '<S232>/Sum1'
               *  Sum: '<S236>/Sum2'
               *  UnitDelay: '<S210>/Unit Delay1'
               */
              if (s249_iter - 1 >= s208_iter - 1) {
                /* Selector: '<S226>/Selector' incorporates:
                 *  Sum: '<S232>/Sum1'
                 */
                if (rtb_Sum2_d > MAX_int32_T - s249_iter) {
                  i = MAX_int32_T;
                } else {
                  i = s249_iter + rtb_Sum2_d;
                }

                rtb_Product2_e = autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1];
              } else {
                rtb_Product2_e = 0.0;
              }

              /* Selector: '<S226>/Selector' incorporates:
               *  Sum: '<S232>/Sum1'
               */
              if (rtb_Sum2_d > 2147483646 - s249_iter) {
                i = MAX_int32_T;
              } else {
                i = (s249_iter + rtb_Sum2_d) + 1;
              }

              /* Selector: '<S226>/Selector2' incorporates:
               *  Constant: '<S226>/k[13][13]'
               *  Sum: '<S233>/Sum'
               */
              Merge_b_tmp = ((s249_iter + 1) * 13 + s208_iter) - 1;

              /* Merge: '<S210>/Merge' incorporates:
               *  Constant: '<S226>/k[13][13]'
               *  Product: '<S226>/Product2'
               *  Product: '<S226>/Product3'
               *  Selector: '<S226>/Selector'
               *  Selector: '<S226>/Selector2'
               *  Sum: '<S226>/Sum1'
               *  Sum: '<S232>/Sum1'
               *  Switch: '<S226>/Switch1'
               *  UnitDelay: '<S210>/Unit Delay1'
               */
              autocodePlant_B->Merge_b = autocodePlant_DW->UnitDelay1_DSTATE_c[i
                - 1] * autocodePlant_B->Product4 -
                rtCP__k1313_Value_j[Merge_b_tmp] * rtb_Product2_e;

              /* Switch: '<S226>/Switch' incorporates:
               *  Constant: '<S226>/Constant'
               *  RelationalOperator: '<S235>/Relational Operator'
               *  Selector: '<S226>/Selector1'
               *  Sum: '<S235>/Sum2'
               *  UnitDelay: '<S210>/Unit Delay'
               */
              if (s249_iter - 1 >= s208_iter - 1) {
                rtb_Product2_e = autocodePlant_DW->UnitDelay_DSTATE_o
                  [((s249_iter - 1) * 13 + s208_iter) - 1];
              } else {
                rtb_Product2_e = 0.0;
              }

              /* Selector: '<S226>/Selector' incorporates:
               *  Sum: '<S232>/Sum1'
               */
              if (rtb_Sum2_d > 2147483646 - s249_iter) {
                i = MAX_int32_T;
              } else {
                i = (s249_iter + rtb_Sum2_d) + 1;
              }

              /* Merge: '<S210>/Merge1' incorporates:
               *  Constant: '<S226>/k[13][13]'
               *  Product: '<S226>/Product'
               *  Product: '<S226>/Product1'
               *  Product: '<S226>/Product4'
               *  Selector: '<S226>/Selector'
               *  Selector: '<S226>/Selector1'
               *  Selector: '<S226>/Selector2'
               *  Sum: '<S226>/Sum'
               *  Sum: '<S232>/Sum1'
               *  Switch: '<S226>/Switch'
               *  UnitDelay: '<S210>/Unit Delay'
               *  UnitDelay: '<S210>/Unit Delay1'
               */
              autocodePlant_B->Merge1_i = (autocodePlant_DW->UnitDelay_DSTATE_o
                [(13 * s249_iter + s208_iter) - 1] * autocodePlant_B->Product4 -
                autocodePlant_DW->UnitDelay1_DSTATE_c[i - 1] *
                autocodePlant_B->sqrt_k) - rtCP__k1313_Value_j[Merge_b_tmp] *
                rtb_Product2_e;

              /* End of Outputs for SubSystem: '<S210>/If Action Subsystem2' */
            }

            /* End of If: '<S210>/if n == m elseif (n==1&m==0) elseif (n>1&m~=n)' */

            /* Assignment: '<S210>/Assignment_snorm' */
            if (ForIterator_IterationMarker[3] < 2) {
              ForIterator_IterationMarker[3] = 2U;

              /* Assignment: '<S210>/Assignment_snorm' incorporates:
               *  UnitDelay: '<S210>/Unit Delay1'
               */
              memcpy(&autocodePlant_B->Assignment_snorm[0],
                     &autocodePlant_DW->UnitDelay1_DSTATE_c[0], 169U * sizeof
                     (real_T));
            }

            /* Sum: '<S227>/Sum1' incorporates:
             *  Gain: '<S227>/Gain'
             *  Sum: '<S210>/Sum'
             *  Sum: '<S227>/Sum2'
             */
            i = mul_s32_sat(13, s208_iter - 1);
            if (i > 2147483645 - s249_iter) {
              i = MAX_int32_T;
            } else {
              i = (s249_iter + i) + 2;
            }

            /* Assignment: '<S210>/Assignment_snorm' incorporates:
             *  Sum: '<S227>/Sum1'
             */
            autocodePlant_B->Assignment_snorm[i - 1] = autocodePlant_B->Merge_b;

            /* Assignment: '<S210>/Assignment' incorporates:
             *  Sum: '<S210>/Sum'
             *  UnitDelay: '<S210>/Unit Delay'
             */
            if (ForIterator_IterationMarker[2] < 2) {
              ForIterator_IterationMarker[2] = 2U;
              memcpy(&autocodePlant_B->Assignment_h[0],
                     &autocodePlant_DW->UnitDelay_DSTATE_o[0], 169U * sizeof
                     (real_T));
            }

            autocodePlant_B->Assignment_h[(s208_iter + 13 * (s249_iter + 1)) - 1]
              = autocodePlant_B->Merge1_i;

            /* End of Assignment: '<S210>/Assignment' */

            /* Update for UnitDelay: '<S210>/Unit Delay' incorporates:
             *  Assignment: '<S210>/Assignment'
             */
            memcpy(&autocodePlant_DW->UnitDelay_DSTATE_o[0],
                   &autocodePlant_B->Assignment_h[0], 169U * sizeof(real_T));

            /* Update for UnitDelay: '<S210>/Unit Delay1' */
            memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_c[0],
                   &autocodePlant_B->Assignment_snorm[0], 169U * sizeof(real_T));
          }

          /* End of Outputs for SubSystem: '<S208>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */

          /* Selector: '<S209>/snorm[n+m*13]' incorporates:
           *  Gain: '<S213>/Gain'
           *  SignalConversion generated from: '<S210>/Enable'
           *  Sum: '<S208>/Sum1'
           *  Sum: '<S213>/Sum1'
           */
          i = mul_s32_sat(13, s208_iter - 1);
          if (i > 2147483645 - s249_iter) {
            i = MAX_int32_T;
          } else {
            i = (s249_iter + i) + 2;
          }

          /* Product: '<S209>/par' incorporates:
           *  Selector: '<S209>/snorm[n+m*13]'
           *  Sum: '<S213>/Sum1'
           *  UnitDelay: '<S200>/Unit Delay'
           */
          rtb_Product2_e = autocodePlant_B->Assignment_snorm[i - 1] *
            rtb_Switch_d_idx_2;

          /* Sum: '<S209>/Sum2' incorporates:
           *  Constant: '<S209>/fm'
           *  Product: '<S209>/Product1'
           *  Selector: '<S209>/fm[m]'
           *  UnitDelay: '<S209>/Unit Delay3'
           */
          autocodePlant_B->Sum2 = rtCP__fm_Value[s208_iter - 1] * rtb_Product2_e
            * rtb_Switch_d_idx_0 + rtb_Sum;

          /* Sum: '<S209>/Sum3' incorporates:
           *  Constant: '<S209>/fn'
           *  Product: '<S209>/Product2'
           *  Selector: '<S209>/fn[m]'
           *  Sum: '<S209>/Sum4'
           *  UnitDelay: '<S209>/Unit Delay2'
           */
          autocodePlant_B->Sum3 = rtCP__fn_Value[s249_iter + 1] * rtb_Product2_e
            * rtb_ug_p_idx_0 + rtb_Product1_kn;

          /* Outputs for Enabled SubSystem: '<S209>/Special case - North//South Geographic Pole' incorporates:
           *  EnablePort: '<S212>/Enable'
           */
          /* Outputs for IfAction SubSystem: '<S212>/If Action Subsystem2' incorporates:
           *  ActionPort: '<S217>/Action Port'
           */
          /* If: '<S212>/n ==1' incorporates:
           *  Constant: '<S217>/k[13][13]'
           *  Selector: '<S209>/dp[n][m]'
           *  Selector: '<S217>/Selector2'
           *  Sum: '<S209>/Sum'
           */
          rtb_Sum2_d = (s249_iter + 1) * 13;

          /* End of Outputs for SubSystem: '<S212>/If Action Subsystem2' */
          /* End of Outputs for SubSystem: '<S209>/Special case - North//South Geographic Pole' */

          /* Sum: '<S209>/Sum1' incorporates:
           *  Assignment: '<S210>/Assignment'
           *  Product: '<S209>/Product'
           *  Selector: '<S209>/dp[n][m]'
           *  UnitDelay: '<S200>/Unit Delay'
           *  UnitDelay: '<S209>/Unit Delay1'
           */
          autocodePlant_B->Sum1_p = rtb_Sum1_ox - autocodePlant_B->Assignment_h
            [(rtb_Sum2_d + s208_iter) - 1] * rtb_ug_p_idx_0 * rtb_Switch_d_idx_2;

          /* Outputs for Enabled SubSystem: '<S209>/Special case - North//South Geographic Pole' incorporates:
           *  EnablePort: '<S212>/Enable'
           */
          if ((autocodePlant_B->sqrt_k == 0.0) && (s208_iter - 1 == 1)) {
            autocodePlant_DW->SpecialcaseNorthSouthGeographic = true;

            /* If: '<S212>/n ==1' incorporates:
             *  Assignment: '<S217>/Assignment2'
             */
            if (s249_iter == 0) {
              /* Outputs for IfAction SubSystem: '<S212>/If Action Subsystem1' incorporates:
               *  ActionPort: '<S216>/Action Port'
               */
              /* Assignment: '<S216>/Assignment2' incorporates:
               *  Selector: '<S216>/pp[n-1]'
               *  UnitDelay: '<S212>/Unit Delay1'
               */
              if (ForIterator_IterationMarker[0] < 2) {
                ForIterator_IterationMarker[0] = 2U;
                memcpy(&autocodePlant_B->Assignment2_m[0],
                       &autocodePlant_DW->UnitDelay1_DSTATE_b[0], 13U * sizeof
                       (real_T));
              }

              autocodePlant_B->Assignment2_m[1] =
                autocodePlant_DW->UnitDelay1_DSTATE_b[0];

              /* End of Assignment: '<S216>/Assignment2' */
              /* End of Outputs for SubSystem: '<S212>/If Action Subsystem1' */
            } else {
              /* Outputs for IfAction SubSystem: '<S212>/If Action Subsystem2' incorporates:
               *  ActionPort: '<S217>/Action Port'
               */
              if (ForIterator_IterationMarker[1] < 2) {
                /* Assignment: '<S217>/Assignment2' */
                ForIterator_IterationMarker[1] = 2U;

                /* Assignment: '<S217>/Assignment2' incorporates:
                 *  UnitDelay: '<S212>/Unit Delay1'
                 */
                memcpy(&autocodePlant_B->Assignment2_a[0],
                       &autocodePlant_DW->UnitDelay1_DSTATE_b[0], 13U * sizeof
                       (real_T));
              }

              /* Assignment: '<S217>/Assignment2' incorporates:
               *  Constant: '<S217>/k[13][13]'
               *  Product: '<S217>/Product1'
               *  Product: '<S217>/Product2'
               *  Selector: '<S217>/Selector2'
               *  Selector: '<S217>/pp[n-2] pp[n-1]'
               *  Sum: '<S217>/Sum1'
               *  Sum: '<S217>/Sum2'
               *  UnitDelay: '<S212>/Unit Delay1'
               */
              autocodePlant_B->Assignment2_a[s249_iter + 1] =
                autocodePlant_B->Product4 *
                autocodePlant_DW->UnitDelay1_DSTATE_b[s249_iter] -
                rtCP__k1313_Value[rtb_Sum2_d + 1] *
                autocodePlant_DW->UnitDelay1_DSTATE_b[s249_iter - 1];

              /* End of Outputs for SubSystem: '<S212>/If Action Subsystem2' */
            }

            /* SignalConversion generated from: '<S212>/pp[n]' */
            autocodePlant_DW->UnitDelay1_DSTATE_b[1] =
              autocodePlant_B->Assignment2_m[1];
            memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_b[2],
                   &autocodePlant_B->Assignment2_a[2], 11U * sizeof(real_T));

            /* Product: '<S212>/Product2' incorporates:
             *  Selector: '<S212>/pp[n]'
             *  UnitDelay: '<S200>/Unit Delay'
             */
            autocodePlant_B->Product2 = autocodePlant_DW->
              UnitDelay1_DSTATE_b[s249_iter + 1] * rtb_Switch_d_idx_2 *
              rtb_Switch_d_idx_0;
          } else if (autocodePlant_DW->SpecialcaseNorthSouthGeographic) {
            /* Disable for Product: '<S212>/Product2' incorporates:
             *  Outport: '<S212>/bpp'
             */
            autocodePlant_B->Product2 = 0.0;
            autocodePlant_DW->SpecialcaseNorthSouthGeographic = false;
          }

          /* End of Outputs for SubSystem: '<S209>/Special case - North//South Geographic Pole' */

          /* Sum: '<S209>/Sum5' incorporates:
           *  Constant: '<S215>/Constant'
           *  Constant: '<S215>/Constant1'
           *  Logic: '<S215>/Logical Operator'
           *  RelationalOperator: '<S215>/Relational Operator'
           *  RelationalOperator: '<S215>/Relational Operator1'
           *  Sum: '<S208>/Sum1'
           *  UnitDelay: '<S209>/Unit Delay4'
           */
          autocodePlant_B->Sum5 = rtb_Product_kd + autocodePlant_B->Product2;

          /* Update for UnitDelay: '<S209>/Unit Delay3' */
          rtb_Sum = autocodePlant_B->Sum2;

          /* Update for UnitDelay: '<S209>/Unit Delay2' */
          rtb_Product1_kn = autocodePlant_B->Sum3;

          /* Update for UnitDelay: '<S209>/Unit Delay1' */
          rtb_Sum1_ox = autocodePlant_B->Sum1_p;

          /* Update for UnitDelay: '<S209>/Unit Delay4' */
          rtb_Product_kd = autocodePlant_B->Sum5;
        }

        /* End of Sum: '<S200>/Sum' */
        /* End of Outputs for SubSystem: '<S200>/For Iterator Subsystem' */

        /* Sum: '<S200>/Sum1' incorporates:
         *  UnitDelay: '<S200>/Unit Delay2'
         */
        rtb_Product2_e = autocodePlant_DW->UnitDelay2_DSTATE[0];
        rtb_Sum = autocodePlant_DW->UnitDelay2_DSTATE[1];
        rtb_Product1_kn = autocodePlant_DW->UnitDelay2_DSTATE[2];
        rtb_Sum1_ox = autocodePlant_DW->UnitDelay2_DSTATE[3];
        autocodePlant_DW->UnitDelay2_DSTATE[0] = rtb_Product2_e +
          autocodePlant_B->Sum1_p;
        autocodePlant_DW->UnitDelay2_DSTATE[1] = rtb_Sum + autocodePlant_B->Sum2;
        autocodePlant_DW->UnitDelay2_DSTATE[2] = rtb_Product1_kn +
          autocodePlant_B->Sum3;
        autocodePlant_DW->UnitDelay2_DSTATE[3] = rtb_Sum1_ox +
          autocodePlant_B->Sum5;
      }

      /* End of Outputs for SubSystem: '<S189>/Compute magnetic vector in spherical coordinates' */
    }

    /* Switch: '<S252>/Switch' incorporates:
     *  Product: '<S252>/Product'
     *  UnitDelay: '<S200>/Unit Delay2'
     */
    if (autocodePlant_B->sqrt_k != 0.0) {
      rtb_Sum1_ox = autocodePlant_DW->UnitDelay2_DSTATE[1] /
        autocodePlant_B->sqrt_k;
    } else {
      rtb_Sum1_ox = autocodePlant_DW->UnitDelay2_DSTATE[3];
    }

    /* End of Switch: '<S252>/Switch' */

    /* Sum: '<S251>/Sum1' incorporates:
     *  Product: '<S251>/Product1'
     *  Product: '<S251>/Product4'
     *  UnitDelay: '<S200>/Unit Delay2'
     */
    rtb_Switch_d_idx_2 = (0.0 - autocodePlant_B->Product11 *
                          autocodePlant_DW->UnitDelay2_DSTATE[0]) -
      autocodePlant_DW->UnitDelay2_DSTATE[2] * autocodePlant_B->Product12;

    /* Trigonometry: '<S254>/Trigonometric Function1' */
    rtb_Sum = rt_atan2d_snf(rtb_Sum1_ox, rtb_Switch_d_idx_2);

    /* Sum: '<S253>/Sum1' incorporates:
     *  Product: '<S253>/Product1'
     *  Product: '<S253>/Product4'
     *  UnitDelay: '<S200>/Unit Delay2'
     */
    /* Unit Conversion - from: rad to: deg
       Expression: output = (57.2958*input) + (0) */
    rtb_Product_kd = autocodePlant_B->Product12 *
      autocodePlant_DW->UnitDelay2_DSTATE[0] -
      autocodePlant_DW->UnitDelay2_DSTATE[2] * autocodePlant_B->Product11;

    /* Sum: '<S254>/Sum' incorporates:
     *  Product: '<S254>/Product'
     *  Product: '<S254>/Product1'
     */
    rtb_Sum1_ox = rtb_Sum1_ox * rtb_Sum1_ox + rtb_Switch_d_idx_2 *
      rtb_Switch_d_idx_2;

    /* UnitConversion: '<S190>/Unit Conversion' incorporates:
     *  Sqrt: '<S254>/sqrt1'
     *  Trigonometry: '<S254>/Trigonometric Function'
     *  UnitConversion: '<S255>/Unit Conversion'
     *  UnitConversion: '<S256>/Unit Conversion'
     */
    /* Unit Conversion - from: rad to: deg
       Expression: output = (57.2958*input) + (0) */
    /* Unit Conversion - from: deg to: rad
       Expression: output = (0.0174533*input) + (0) */
    rtb_ug_p_idx_0 = 57.29577951308232 * rtb_Sum * 0.017453292519943295;
    rtb_Switch_d_idx_0 = 57.29577951308232 * rt_atan2d_snf(rtb_Product_kd, sqrt
      (rtb_Sum1_ox)) * 0.017453292519943295;

    /* Sqrt: '<S254>/sqrt' incorporates:
     *  Product: '<S254>/Product2'
     *  Sum: '<S254>/Sum1'
     */
    rtb_Sum1_ox = sqrt(rtb_Product_kd * rtb_Product_kd + rtb_Sum1_ox);

    /* Product: '<S183>/h1' incorporates:
     *  Trigonometry: '<S183>/sincos'
     */
    rtb_Switch_d_idx_2 = cos(rtb_Switch_d_idx_0) * rtb_Sum1_ox;

    /* Product: '<S183>/x1' incorporates:
     *  Trigonometry: '<S183>/sincos'
     */
    rtb_Sum = cos(rtb_ug_p_idx_0) * rtb_Switch_d_idx_2;

    /* Sqrt: '<S178>/sqrt' incorporates:
     *  Product: '<S179>/Product'
     *  Product: '<S179>/Product1'
     *  Product: '<S179>/Product2'
     *  Product: '<S179>/Product3'
     *  Sum: '<S179>/Sum'
     */
    rtb_Product_kd = sqrt(((rtb_q_na_idx_0 * rtb_q_na_idx_0 + rtb_q_na_idx_1 *
      rtb_q_na_idx_1) + rtb_q_na_idx_2 * rtb_q_na_idx_2) + rtb_q_na_idx_3 *
                          rtb_q_na_idx_3);

    /* Product: '<S174>/Product2' */
    rtb_Product2_e = rtb_q_na_idx_2 / rtb_Product_kd;

    /* Product: '<S174>/Product3' */
    rtb_Product3_ax = rtb_q_na_idx_3 / rtb_Product_kd;

    /* Product: '<S174>/Product1' */
    rtb_Product1_kn = rtb_q_na_idx_1 / rtb_Product_kd;

    /* Product: '<S174>/Product' */
    rtb_Product_kd = rtb_q_na_idx_0 / rtb_Product_kd;

    /* Product: '<S183>/y1' incorporates:
     *  Trigonometry: '<S183>/sincos'
     */
    rtb_Switch_d_idx_2 *= sin(rtb_ug_p_idx_0);

    /* Product: '<S183>/z1' incorporates:
     *  Trigonometry: '<S183>/sincos'
     */
    rtb_Sum1_ox *= sin(rtb_Switch_d_idx_0);

    /* Product: '<S91>/Product2' incorporates:
     *  Gain: '<S91>/P0'
     */
    rtb_Product2_f *= 101325.0 * rtb_TT0gLR;
    if (tmp) {
      /* Sum: '<S175>/Sum' incorporates:
       *  Product: '<S175>/Product'
       *  Product: '<S175>/Product1'
       *  Product: '<S175>/Product2'
       *  Product: '<S175>/Product3'
       *  Product: '<S175>/Product6'
       *  Product: '<S175>/Product7'
       *  Product: '<S176>/Product'
       *  Product: '<S176>/Product1'
       *  Product: '<S176>/Product7'
       *  Product: '<S177>/Product'
       *  Product: '<S177>/Product1'
       *  Product: '<S177>/Product7'
       *  Sum: '<S176>/Sum'
       *  Sum: '<S177>/Sum'
       */
      rtb_TT0gLR = rtb_Product3_ax * rtb_Product3_ax;
      rtb_PreLookUpIndexSearchaltit_0 = rtb_Product1_kn * rtb_Product2_e;
      rtb_PreLookUpIndexSearchaltit_1 = rtb_Product_kd * rtb_Product3_ax;
      rtb_ug_p_idx_0 = rtb_Product1_kn * rtb_Product3_ax;
      rtb_PreLookUpIndexSearchaltit_2 = rtb_Product_kd * rtb_Product2_e;
      rtb_PreLookUpIndexSearchaltit_3 = rtb_Product2_e * rtb_Product2_e;

      /* SignalConversion generated from: '<S157>/Product' incorporates:
       *  Constant: '<S175>/Constant'
       *  Gain: '<S175>/Gain'
       *  Gain: '<S175>/Gain1'
       *  Gain: '<S175>/Gain2'
       *  Product: '<S175>/Product'
       *  Product: '<S175>/Product1'
       *  Product: '<S175>/Product2'
       *  Product: '<S175>/Product3'
       *  Product: '<S175>/Product4'
       *  Product: '<S175>/Product5'
       *  Product: '<S175>/Product6'
       *  Product: '<S175>/Product7'
       *  Product: '<S175>/Product8'
       *  Sum: '<S175>/Sum'
       *  Sum: '<S175>/Sum1'
       *  Sum: '<S175>/Sum2'
       *  Sum: '<S175>/Sum3'
       */
      rtb_Switch_d_idx_0 = (((0.5 - rtb_PreLookUpIndexSearchaltit_3) -
        rtb_TT0gLR) * 2.0 * rtb_Sum + (rtb_PreLookUpIndexSearchaltit_0 +
        rtb_PreLookUpIndexSearchaltit_1) * 2.0 * rtb_Switch_d_idx_2) +
        (rtb_ug_p_idx_0 - rtb_PreLookUpIndexSearchaltit_2) * 2.0 * rtb_Sum1_ox;

      /* Sum: '<S176>/Sum' incorporates:
       *  Constant: '<S176>/Constant'
       *  Product: '<S176>/Product2'
       *  Product: '<S176>/Product3'
       *  Product: '<S176>/Product6'
       *  Product: '<S177>/Product2'
       *  Product: '<S177>/Product3'
       *  Sum: '<S176>/Sum3'
       *  Sum: '<S177>/Sum'
       *  Sum: '<S177>/Sum3'
       */
      rtb_Product2_e *= rtb_Product3_ax;
      rtb_Product3_ax = rtb_Product_kd * rtb_Product1_kn;
      rtb_Product1_kn = 0.5 - rtb_Product1_kn * rtb_Product1_kn;

      /* SignalConversion generated from: '<S157>/Product' incorporates:
       *  Gain: '<S176>/Gain'
       *  Gain: '<S176>/Gain1'
       *  Gain: '<S176>/Gain2'
       *  Gain: '<S177>/Gain'
       *  Gain: '<S177>/Gain1'
       *  Gain: '<S177>/Gain2'
       *  Product: '<S176>/Product2'
       *  Product: '<S176>/Product3'
       *  Product: '<S176>/Product4'
       *  Product: '<S176>/Product5'
       *  Product: '<S176>/Product8'
       *  Product: '<S177>/Product4'
       *  Product: '<S177>/Product5'
       *  Product: '<S177>/Product8'
       *  Sum: '<S176>/Sum'
       *  Sum: '<S176>/Sum1'
       *  Sum: '<S176>/Sum2'
       *  Sum: '<S176>/Sum3'
       *  Sum: '<S177>/Sum'
       *  Sum: '<S177>/Sum1'
       *  Sum: '<S177>/Sum2'
       *  Sum: '<S177>/Sum3'
       */
      rtb_Product_kd = ((rtb_Product1_kn - rtb_TT0gLR) * 2.0 *
                        rtb_Switch_d_idx_2 + (rtb_PreLookUpIndexSearchaltit_0 -
        rtb_PreLookUpIndexSearchaltit_1) * 2.0 * rtb_Sum) + (rtb_Product3_ax +
        rtb_Product2_e) * 2.0 * rtb_Sum1_ox;
      rtb_Product2_e = ((rtb_ug_p_idx_0 + rtb_PreLookUpIndexSearchaltit_2) * 2.0
                        * rtb_Sum + (rtb_Product2_e - rtb_Product3_ax) * 2.0 *
                        rtb_Switch_d_idx_2) + (rtb_Product1_kn -
        rtb_PreLookUpIndexSearchaltit_3) * 2.0 * rtb_Sum1_ox;

      /* ZeroOrderHold: '<S157>/Zero-Order Hold' incorporates:
       *  Constant: '<S157>/hardironBdy_nT'
       *  Constant: '<S157>/soft iron matrix'
       *  Product: '<S157>/Product'
       *  Sum: '<S157>/Sum'
       */
      for (i = 0; i < 3; i++) {
        Gdependent[i] = (((rtCP__softironmatrix_Value[i + 3] * rtb_Product_kd +
                           rtCP__softironmatrix_Value[i] * rtb_Switch_d_idx_0) +
                          rtCP__softironmatrix_Value[i + 6] * rtb_Product2_e) +
                         autocodePlant_B->Output[i]) +
          rtCP__hardironBdy_nT_Value[i];
      }

      /* End of ZeroOrderHold: '<S157>/Zero-Order Hold' */

      /* Gain: '<S168>/Output' incorporates:
       *  RandomNumber: '<S168>/White Noise'
       */
      autocodePlant_B->Output_g = 0.19999999999999998 *
        autocodePlant_DW->NextOutput_e;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  DiscreteTransferFcn: '<S155>/Discrete Transfer Fcn2'
       *  Outport: '<Root>/sensor_bus'
       *  Sum: '<S155>/Sum1'
       */
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[0] = rtb_w3;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[0] =
        rtb_sigma_ugsigma_vg;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[0] = rtb_ZeroOrderHold_c[0];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[0] = rtb_ZeroOrderHold_a[0];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[0] = Gdependent[0];
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[1] =
        rtb_LowAltitudeScaleLength;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[1] =
        rtb_truth_bus_accBiasTrue_mps2_;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[1] = rtb_ZeroOrderHold_c[1];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[1] = rtb_ZeroOrderHold_a[1];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[1] = Gdependent[1];
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[2] =
        rtb_truth_bus_gyroBiasTrue_rps_;
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[2] =
        rtb_truth_bus_accBiasTrue_mps_0;
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[2] = rtb_ZeroOrderHold_c[2];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[2] = rtb_ZeroOrderHold_a[2];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[2] = Gdependent[2];
      autocodePlant_Y_sensor_bus_i->baroMeas_Pa = (autocodePlant_B->Output_g +
        rtb_Product2_f) + autocodePlant_DW->DiscreteTransferFcn2_states_h;
    }

    /* Product: '<S146>/Product' */
    autocodePlant_B->Product[0] = rtb_Add[0] * (real_T)rtb_max_relop_c;
    autocodePlant_B->Product[1] = rtb_Add[1] * (real_T)rtb_max_relop_c;
    autocodePlant_B->Product[2] = rtb_Add[2] * (real_T)rtb_max_relop_c;

    /* Outport: '<Root>/plant_bus' incorporates:
     *  BusCreator generated from: '<Root>/plant_bus'
     */
    autocodePlant_Y_plant_bus_e->enviroment_bus.temp_K = rtb_Sum1_oo;
    autocodePlant_Y_plant_bus_e->enviroment_bus.a_mps = rtb_a;
    autocodePlant_Y_plant_bus_e->enviroment_bus.pressure_Pa = rtb_Product2_f;
    autocodePlant_Y_plant_bus_e->enviroment_bus.rho_kgpm3 = rtb_Product_iw;
    autocodePlant_Y_plant_bus_e->enviroment_bus.onRail_b = rtb_Compare_n;
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.aoa_deg = rtb_Gain_l;
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.liftSign_na = rtb_Sign1;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.aoa_deg = rtb_Gain_oa;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.liftSign_na = rtb_Sign1_e;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.aoa_deg = rtb_Gain_c;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.liftSign_na = rtb_Sign1_oh;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.aoa_deg = rtb_Gain_e;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.liftSign_na = rtb_Sign1_b;
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.aoa_deg = rtb_Gain_ii;

    /* Product: '<S145>/Matrix Multiply' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    rtb_w3 = 0.0;
    rtb_sigma_ugsigma_vg = 0.0;
    rtb_LowAltitudeScaleLength = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_Product2_e = rtb_wBdy_rps[i];
      rtb_w3 += rtCP__Constant1_Value_fo[3 * i] * rtb_Product2_e;
      rtb_sigma_ugsigma_vg += rtCP__Constant1_Value_fo[3 * i + 1] *
        rtb_Product2_e;
      rtb_LowAltitudeScaleLength += rtCP__Constant1_Value_fo[3 * i + 2] *
        rtb_Product2_e;

      /* Outport: '<Root>/plant_bus' incorporates:
       *  BusCreator generated from: '<Root>/plant_bus'
       *  Constant: '<S5>/Constant1'
       */
      autocodePlant_Y_plant_bus_e->enviroment_bus.gravityForceBdy_N[i] =
        rtb_gravityForceBdy_N[i];
      autocodePlant_Y_plant_bus_e->enviroment_bus.airspeed_mps[i] =
        rtb_airspeed_mps[i];
      autocodePlant_Y_plant_bus_e->enviroment_bus.windBdy_mps[i] =
        rtb_Switch_f[i];
      autocodePlant_Y_plant_bus_e->enviroment_bus.airW_rps[i] = rtb_Product2_e;
      autocodePlant_Y_plant_bus_e->aero_bus.aeroMoment_Nm[i] = rtb_Add[i];
      autocodePlant_Y_plant_bus_e->aero_bus.aeroForce_N[i] = rtb_Add[i + 3];
      autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finMoment_Nm[i] =
        rtb_Sum_j[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finForce_N[i] =
        rtb_Sum1_p2[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.airspeedFin_mps[i] =
        rtb_Sum_jl[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finMoment_Nm[i] =
        rtb_Sum_l4[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finForce_N[i] =
        rtb_Sum1_ny[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.airspeedFin_mps[i] =
        rtb_Sum_ls[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finMoment_Nm[i] =
        rtb_Sum_bq[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finForce_N[i] =
        rtb_Sum1_lp[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.airspeedFin_mps[i] =
        rtb_Sum_cu[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finMoment_Nm[i] =
        rtb_Sum_kx[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finForce_N[i] =
        rtb_Sum1_b[i];
      autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.airspeedFin_mps[i] =
        rtb_Sum_pc[i];
      autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyMoment_Nm[i] =
        rtb_finMomentArm_m[i];
      autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyForce_N[i] =
        rtb_Product6_f[i];
      autocodePlant_Y_plant_bus_e->eom_bus.posNed_m[i] = rtb_posNed_m[i];
    }

    /* Product: '<S152>/Element Product' incorporates:
     *  Product: '<S145>/Matrix Multiply'
     */
    rtb_ElementProduct[0] = rtb_wBdy_rps[1] * rtb_LowAltitudeScaleLength;
    rtb_ElementProduct[1] = rtb_w3 * rtb_wBdy_rps[2];
    rtb_ElementProduct[2] = rtb_wBdy_rps[0] * rtb_sigma_ugsigma_vg;
    rtb_ElementProduct[3] = rtb_sigma_ugsigma_vg * rtb_wBdy_rps[2];
    rtb_ElementProduct[4] = rtb_wBdy_rps[0] * rtb_LowAltitudeScaleLength;
    rtb_ElementProduct[5] = rtb_w3 * rtb_wBdy_rps[1];

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

      /* Sum: '<S145>/Subtract' incorporates:
       *  Product: '<S145>/Matrix Multiply1'
       *  Sum: '<S151>/Add'
       *  Sum: '<S152>/Sum'
       */
      rtb_ZeroOrderHold_a[i] = (autocodePlant_B->Product[i] -
        (rtb_ElementProduct[i] - rtb_ElementProduct[i + 3])) -
        ((autocodePlant_ConstB.dIdt[i + 3] * rtb_wBdy_rps[1] +
          autocodePlant_ConstB.dIdt[i] * rtb_wBdy_rps[0]) +
         autocodePlant_ConstB.dIdt[i + 6] * rtb_wBdy_rps[2]);
    }

    /* Product: '<S145>/Product1' incorporates:
     *  Constant: '<S5>/Constant1'
     *  Outport: '<Root>/plant_bus'
     */
    rt_mldivide_U1d3x3_U2d_9O8lG8ax(rtCP__Constant1_Value_fo,
      rtb_ZeroOrderHold_a, autocodePlant_Y_plant_bus_e->eom_bus.wDotBdy_rps2);

    /* UnitConversion: '<S106>/Unit Conversion' incorporates:
     *  UnaryMinus: '<S86>/Unary Minus'
     */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    rtb_q_na_idx_0 = 3.280839895013123 * -rtb_posNed_m[2];

    /* Saturate: '<S139>/Limit Function 10ft to 1000ft' */
    if (rtb_q_na_idx_0 > 1000.0) {
      rtb_Switch_d_idx_2 = 1000.0;
    } else if (rtb_q_na_idx_0 < 10.0) {
      rtb_Switch_d_idx_2 = 10.0;
    } else {
      rtb_Switch_d_idx_2 = rtb_q_na_idx_0;
    }

    /* End of Saturate: '<S139>/Limit Function 10ft to 1000ft' */

    /* Gain: '<S111>/Lw' */
    rtb_q_na_idx_2 = autocodePlant_ConstB.UnitConversion_k;

    /* Interpolation_n-D: '<S121>/Medium//High Altitude Intensity' incorporates:
     *  PreLookup: '<S121>/PreLook-Up Index Search  (altitude)'
     *  PreLookup: '<S121>/PreLook-Up Index Search  (prob of exceed)'
     */
    bpIndex[0] = plook_bincpa(rtb_q_na_idx_0, rtCP__PreLookUpIndexSearchaltit,
      11U, &rtb_Sum, &autocodePlant_DW->PreLookUpIndexSearchaltitude_DW);
    frac[0] = rtb_Sum;
    frac[1] = autocodePlant_ConstB.PreLookUpIndexSearchprobofe;
    bpIndex[1] = autocodePlant_ConstB.PreLookUpIndexSearchprobo_j;
    rtb_q_na_idx_3 = intrp2d_la_pw(bpIndex, frac,
      rtCP__MediumHighAltitudeIntensi, 12U, rtCP__MediumHighAltitudeInten_o);
    if (rtmIsMajorTimeStep(autocodePlant_M) &&
        autocodePlant_M->Timing.TaskCounters.TID[2] == 0) {
      /* Product: '<S114>/Product' incorporates:
       *  RandomNumber: '<S114>/White Noise'
       */
      autocodePlant_B->Product_d[0] = autocodePlant_ConstB.Divide[0] *
        autocodePlant_DW->NextOutput_d[0];
      autocodePlant_B->Product_d[1] = autocodePlant_ConstB.Divide[1] *
        autocodePlant_DW->NextOutput_d[1];
      autocodePlant_B->Product_d[2] = autocodePlant_ConstB.Divide[2] *
        autocodePlant_DW->NextOutput_d[2];
      autocodePlant_B->Product_d[3] = autocodePlant_ConstB.Divide[3] *
        autocodePlant_DW->NextOutput_d[3];
    }

    /* UnitConversion: '<S112>/Unit Conversion' incorporates:
     *  DotProduct: '<S86>/Dot Product'
     *  Sqrt: '<S86>/Sqrt'
     */
    /* Unit Conversion - from: m/s to: ft/s
       Expression: output = (3.28084*input) + (0) */
    rtb_q_na_idx_1 = sqrt((rtb_velBdy_mps[0] * rtb_velBdy_mps[0] +
      rtb_velBdy_mps[1] * rtb_velBdy_mps[1]) + rtb_velBdy_mps[2] *
                          rtb_velBdy_mps[2]) * 3.280839895013123;

    /* Outputs for Enabled SubSystem: '<S104>/Hpgw' incorporates:
     *  EnablePort: '<S115>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hpgw_MODE) {
      (void) memset(&(autocodePlant_XDis->pgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S115>/pgw_p' */
      autocodePlant_X->pgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->pgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hpgw_MODE = true;
    }

    if (autocodePlant_DW->Hpgw_MODE) {
      /* Fcn: '<S115>/sqrt(0.8//V)' */
      rtb_Product2_e = sqrt(0.8 / rtb_q_na_idx_1);

      /* Product: '<S115>/w3' */
      rtb_w3 = rtb_q_na_idx_1 * autocodePlant_ConstB.w4;

      /* Product: '<S115>/w' incorporates:
       *  Fcn: '<S115>/sqrt(0.8//V)'
       *  Gain: '<S111>/Lw'
       *  Integrator: '<S115>/pgw_p'
       *  Math: '<S115>/L^1//3'
       *  Product: '<S115>/Lug//V1'
       *  Product: '<S115>/w1'
       *  Product: '<S115>/w2'
       *  Sum: '<S115>/Sum'
       */
      autocodePlant_B->w_p[0] = (rtb_Product2_e / rt_powd_snf(rtb_Switch_d_idx_2,
        0.3333333333333333) * autocodePlant_ConstB.u16 *
        autocodePlant_B->Product_d[3] - autocodePlant_X->pgw_p_CSTATE[0]) *
        rtb_w3;

      /* Math: '<S115>/L^1//3' */
      if (rtb_q_na_idx_2 < 0.0) {
        rtb_sigma_ugsigma_vg = -rt_powd_snf(-rtb_q_na_idx_2, 0.3333333333333333);
      } else {
        rtb_sigma_ugsigma_vg = rt_powd_snf(rtb_q_na_idx_2, 0.3333333333333333);
      }

      /* Product: '<S115>/w' incorporates:
       *  Fcn: '<S115>/sqrt(0.8//V)'
       *  Integrator: '<S115>/pgw_p'
       *  Product: '<S115>/Lug//V1'
       *  Product: '<S115>/w1'
       *  Product: '<S115>/w2'
       *  Sum: '<S115>/Sum'
       */
      autocodePlant_B->w_p[1] = (rtb_Product2_e / rtb_sigma_ugsigma_vg *
        autocodePlant_ConstB.u16 * autocodePlant_B->Product_d[3] -
        autocodePlant_X->pgw_p_CSTATE[1]) * rtb_w3;
    }

    /* End of Outputs for SubSystem: '<S104>/Hpgw' */

    /* Outputs for Enabled SubSystem: '<S105>/Hwgw(s)' incorporates:
     *  EnablePort: '<S120>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hwgws_MODE) {
      (void) memset(&(autocodePlant_XDis->wg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S120>/wg_p1' */
      autocodePlant_X->wg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S120>/wg_p2' */
      autocodePlant_X->wg_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S120>/wg_p1' */
      autocodePlant_X->wg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S120>/wg_p2' */
      autocodePlant_X->wg_p2_CSTATE[1] = 0.0;
      autocodePlant_DW->Hwgws_MODE = true;
    }

    if (autocodePlant_DW->Hwgws_MODE) {
      /* Product: '<S120>/Lwg//V' incorporates:
       *  Gain: '<S111>/Lw'
       */
      rtb_w3 = rtb_Switch_d_idx_2 / rtb_q_na_idx_1;

      /* Product: '<S120>/w' incorporates:
       *  Gain: '<S120>/1//pi'
       *  Integrator: '<S120>/wg_p1'
       *  Product: '<S120>/Lug//V1'
       *  Sqrt: '<S120>/sqrt1'
       *  Sum: '<S120>/Sum'
       */
      rtb_sigma_ugsigma_vg = (sqrt(0.3183098861837907 * rtb_w3) *
        autocodePlant_B->Product_d[2] - autocodePlant_X->wg_p1_CSTATE[0]) /
        rtb_w3;
      autocodePlant_B->w[0] = rtb_sigma_ugsigma_vg;

      /* Product: '<S120>/w ' incorporates:
       *  Integrator: '<S120>/wg_p1'
       *  Integrator: '<S120>/wg_p2'
       *  Product: '<S120>/Lwg//V '
       *  Sum: '<S120>/Sum1'
       */
      autocodePlant_B->w_h[0] = (rtb_sigma_ugsigma_vg *
        autocodePlant_ConstB.sqrt_g * rtb_w3 + (autocodePlant_X->wg_p1_CSTATE[0]
        - autocodePlant_X->wg_p2_CSTATE[0])) / rtb_w3;

      /* Product: '<S120>/Lwg//V' */
      rtb_w3 = rtb_q_na_idx_2 / rtb_q_na_idx_1;

      /* Product: '<S120>/w' incorporates:
       *  Gain: '<S120>/1//pi'
       *  Integrator: '<S120>/wg_p1'
       *  Product: '<S120>/Lug//V1'
       *  Sqrt: '<S120>/sqrt1'
       *  Sum: '<S120>/Sum'
       */
      rtb_sigma_ugsigma_vg = (sqrt(0.3183098861837907 * rtb_w3) *
        autocodePlant_B->Product_d[2] - autocodePlant_X->wg_p1_CSTATE[1]) /
        rtb_w3;
      autocodePlant_B->w[1] = rtb_sigma_ugsigma_vg;

      /* Product: '<S120>/w ' incorporates:
       *  Integrator: '<S120>/wg_p1'
       *  Integrator: '<S120>/wg_p2'
       *  Product: '<S120>/Lwg//V '
       *  Sum: '<S120>/Sum1'
       */
      autocodePlant_B->w_h[1] = (rtb_sigma_ugsigma_vg *
        autocodePlant_ConstB.sqrt_g * rtb_w3 + (autocodePlant_X->wg_p1_CSTATE[1]
        - autocodePlant_X->wg_p2_CSTATE[1])) / rtb_w3;

      /* Product: '<S120>/Lwg//V 1' incorporates:
       *  Integrator: '<S120>/wg_p2'
       */
      autocodePlant_B->LwgV1[0] = autocodePlant_ConstB.sigma_wg *
        autocodePlant_X->wg_p2_CSTATE[0];
      autocodePlant_B->LwgV1[1] = rtb_q_na_idx_3 * autocodePlant_X->
        wg_p2_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S105>/Hwgw(s)' */

    /* Outputs for Enabled SubSystem: '<S104>/Hqgw' incorporates:
     *  EnablePort: '<S116>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hqgw_MODE) {
      (void) memset(&(autocodePlant_XDis->qgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S116>/qgw_p' */
      autocodePlant_X->qgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->qgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hqgw_MODE = true;
    }

    if (autocodePlant_DW->Hqgw_MODE) {
      /* Gain: '<S116>/pi//4' */
      rtb_q_na_idx_2 = 0.7853981633974483 * rtb_q_na_idx_1;

      /* Product: '<S116>/w' incorporates:
       *  Integrator: '<S116>/qgw_p'
       *  Product: '<S116>/wg//V'
       *  Sum: '<S116>/Sum'
       */
      autocodePlant_B->w_j5[0] = (autocodePlant_B->LwgV1[0] / rtb_q_na_idx_1 -
        autocodePlant_X->qgw_p_CSTATE[0]) * (rtb_q_na_idx_2 /
        autocodePlant_ConstB.UnitConversion_e);
      autocodePlant_B->w_j5[1] = (autocodePlant_B->LwgV1[1] / rtb_q_na_idx_1 -
        autocodePlant_X->qgw_p_CSTATE[1]) * (rtb_q_na_idx_2 /
        autocodePlant_ConstB.UnitConversion_e);
    }

    /* End of Outputs for SubSystem: '<S104>/Hqgw' */

    /* Saturate: '<S122>/Limit Height h<1000ft' */
    if (rtb_q_na_idx_0 > 1000.0) {
      rtb_Product2_e = 1000.0;
    } else if (rtb_q_na_idx_0 < 0.0) {
      rtb_Product2_e = 0.0;
    } else {
      rtb_Product2_e = rtb_q_na_idx_0;
    }

    /* Product: '<S122>/sigma_ug, sigma_vg' incorporates:
     *  Fcn: '<S122>/Low Altitude Intensity'
     *  Saturate: '<S122>/Limit Height h<1000ft'
     */
    rtb_sigma_ugsigma_vg = 1.0 / rt_powd_snf(0.000823 * rtb_Product2_e + 0.177,
      0.4) * autocodePlant_ConstB.sigma_wg;

    /* Fcn: '<S139>/Low Altitude Scale Length' */
    rtb_LowAltitudeScaleLength = rtb_Switch_d_idx_2 / rt_powd_snf(0.000823 *
      rtb_Switch_d_idx_2 + 0.177, 1.2);

    /* Gain: '<S111>/Lv' */
    rtb_q_na_idx_2 = autocodePlant_ConstB.UnitConversion_k;

    /* Outputs for Enabled SubSystem: '<S105>/Hvgw(s)' incorporates:
     *  EnablePort: '<S119>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hvgws_MODE) {
      (void) memset(&(autocodePlant_XDis->vg_p1_CSTATE), 0,
                    4*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S119>/vg_p1' */
      autocodePlant_X->vg_p1_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S119>/vgw_p2' */
      autocodePlant_X->vgw_p2_CSTATE[0] = 0.0;

      /* InitializeConditions for Integrator: '<S119>/vg_p1' */
      autocodePlant_X->vg_p1_CSTATE[1] = 0.0;

      /* InitializeConditions for Integrator: '<S119>/vgw_p2' */
      autocodePlant_X->vgw_p2_CSTATE[1] = 0.0;
      autocodePlant_DW->Hvgws_MODE = true;
    }

    if (autocodePlant_DW->Hvgws_MODE) {
      /* Product: '<S119>/Lvg//V' incorporates:
       *  Gain: '<S111>/Lv'
       */
      rtb_w3 = rtb_LowAltitudeScaleLength / rtb_q_na_idx_1;

      /* Product: '<S119>/w' incorporates:
       *  Gain: '<S119>/(1//pi)'
       *  Integrator: '<S119>/vg_p1'
       *  Product: '<S119>/Lug//V1'
       *  Sqrt: '<S119>/sqrt'
       *  Sum: '<S119>/Sum'
       */
      rtb_truth_bus_accBiasTrue_mps2_ = (sqrt(0.3183098861837907 * rtb_w3) *
        autocodePlant_B->Product_d[1] - autocodePlant_X->vg_p1_CSTATE[0]) /
        rtb_w3;
      autocodePlant_B->w_c[0] = rtb_truth_bus_accBiasTrue_mps2_;

      /* Product: '<S119>/w ' incorporates:
       *  Gain: '<S119>/sqrt(3)'
       *  Integrator: '<S119>/vg_p1'
       *  Integrator: '<S119>/vgw_p2'
       *  Product: '<S119>/Lvg//V '
       *  Sum: '<S119>/Sum1'
       */
      autocodePlant_B->w_j[0] = (rtb_truth_bus_accBiasTrue_mps2_ * rtb_w3 *
        1.7320508075688772 + (autocodePlant_X->vg_p1_CSTATE[0] -
        autocodePlant_X->vgw_p2_CSTATE[0])) / rtb_w3;

      /* Product: '<S119>/Lvg//V' */
      rtb_w3 = rtb_q_na_idx_2 / rtb_q_na_idx_1;

      /* Product: '<S119>/w' incorporates:
       *  Gain: '<S119>/(1//pi)'
       *  Integrator: '<S119>/vg_p1'
       *  Product: '<S119>/Lug//V1'
       *  Sqrt: '<S119>/sqrt'
       *  Sum: '<S119>/Sum'
       */
      rtb_truth_bus_accBiasTrue_mps2_ = (sqrt(0.3183098861837907 * rtb_w3) *
        autocodePlant_B->Product_d[1] - autocodePlant_X->vg_p1_CSTATE[1]) /
        rtb_w3;
      autocodePlant_B->w_c[1] = rtb_truth_bus_accBiasTrue_mps2_;

      /* Product: '<S119>/w ' incorporates:
       *  Gain: '<S119>/sqrt(3)'
       *  Integrator: '<S119>/vg_p1'
       *  Integrator: '<S119>/vgw_p2'
       *  Product: '<S119>/Lvg//V '
       *  Sum: '<S119>/Sum1'
       */
      autocodePlant_B->w_j[1] = (rtb_truth_bus_accBiasTrue_mps2_ * rtb_w3 *
        1.7320508075688772 + (autocodePlant_X->vg_p1_CSTATE[1] -
        autocodePlant_X->vgw_p2_CSTATE[1])) / rtb_w3;

      /* Product: '<S119>/w 1' incorporates:
       *  Integrator: '<S119>/vgw_p2'
       */
      autocodePlant_B->w1[0] = rtb_sigma_ugsigma_vg *
        autocodePlant_X->vgw_p2_CSTATE[0];
      autocodePlant_B->w1[1] = rtb_q_na_idx_3 * autocodePlant_X->vgw_p2_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S105>/Hvgw(s)' */

    /* Outputs for Enabled SubSystem: '<S104>/Hrgw' incorporates:
     *  EnablePort: '<S117>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hrgw_MODE) {
      (void) memset(&(autocodePlant_XDis->rgw_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S117>/rgw_p' */
      autocodePlant_X->rgw_p_CSTATE[0] = 0.0;
      autocodePlant_X->rgw_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hrgw_MODE = true;
    }

    if (autocodePlant_DW->Hrgw_MODE) {
      /* Gain: '<S117>/pi//3' */
      rtb_q_na_idx_2 = 1.0471975511965976 * rtb_q_na_idx_1;

      /* Product: '<S117>/w' incorporates:
       *  Integrator: '<S117>/rgw_p'
       *  Product: '<S117>/vg//V'
       *  Sum: '<S117>/Sum'
       */
      autocodePlant_B->w_g[0] = (autocodePlant_B->w1[0] / rtb_q_na_idx_1 -
        autocodePlant_X->rgw_p_CSTATE[0]) * (rtb_q_na_idx_2 /
        autocodePlant_ConstB.UnitConversion_e);
      autocodePlant_B->w_g[1] = (autocodePlant_B->w1[1] / rtb_q_na_idx_1 -
        autocodePlant_X->rgw_p_CSTATE[1]) * (rtb_q_na_idx_2 /
        autocodePlant_ConstB.UnitConversion_e);
    }

    /* End of Outputs for SubSystem: '<S104>/Hrgw' */

    /* Outputs for Enabled SubSystem: '<S105>/Hugw(s)' incorporates:
     *  EnablePort: '<S118>/Enable'
     */
    if (tmp && rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
        !autocodePlant_DW->Hugws_MODE) {
      (void) memset(&(autocodePlant_XDis->ug_p_CSTATE), 0,
                    2*sizeof(boolean_T));

      /* InitializeConditions for Integrator: '<S118>/ug_p' */
      autocodePlant_X->ug_p_CSTATE[0] = 0.0;
      autocodePlant_X->ug_p_CSTATE[1] = 0.0;
      autocodePlant_DW->Hugws_MODE = true;
    }

    if (autocodePlant_DW->Hugws_MODE) {
      /* Product: '<S118>/Lug//V' */
      rtb_q_na_idx_3 = rtb_LowAltitudeScaleLength / rtb_q_na_idx_1;
      rtb_q_na_idx_2 = autocodePlant_ConstB.UnitConversion_k / rtb_q_na_idx_1;

      /* Product: '<S118>/w' incorporates:
       *  Gain: '<S118>/(2//pi)'
       *  Integrator: '<S118>/ug_p'
       *  Product: '<S118>/Lug//V1'
       *  Sqrt: '<S118>/sqrt'
       *  Sum: '<S118>/Sum'
       */
      autocodePlant_B->w_d[0] = (sqrt(0.6366197723675814 * rtb_q_na_idx_3) *
        autocodePlant_B->Product_d[0] - autocodePlant_X->ug_p_CSTATE[0]) /
        rtb_q_na_idx_3;
      autocodePlant_B->w_d[1] = (sqrt(0.6366197723675814 * rtb_q_na_idx_2) *
        autocodePlant_B->Product_d[0] - autocodePlant_X->ug_p_CSTATE[1]) /
        rtb_q_na_idx_2;
    }

    /* End of Outputs for SubSystem: '<S105>/Hugw(s)' */

    /* If: '<S109>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    rtPrevAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      if (rtb_q_na_idx_0 <= 1000.0) {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = 0;
      } else if (rtb_q_na_idx_0 >= 2000.0) {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = 1;
      } else {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = 2;
      }
    }

    if (rtPrevAction != autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&autocodePlant_M->solverInfo,
        true);
    }

    /* End of If: '<S109>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */

    /* If: '<S110>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    rtPrevAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      if (rtb_q_na_idx_0 <= 1000.0) {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f = 0;
      } else if (rtb_q_na_idx_0 >= 2000.0) {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f = 1;
      } else {
        autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f = 2;
      }
    }

    if (rtPrevAction != autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&autocodePlant_M->solverInfo,
        true);
    }

    /* End of If: '<S110>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    if (tmp) {
      /* Lookup_n-D: '<S6>/1-D Lookup Table' incorporates:
       *  UnitDelay: '<S153>/Unit Delay'
       */
      rtb_uDLookupTable = look1_binlcpw(autocodePlant_DW->UnitDelay_DSTATE_i,
        rtCP__uDLookupTable_bp01Data, rtCP__uDLookupTable_tableData, 25U);

      /* Sum: '<S153>/Sum' incorporates:
       *  Constant: '<S153>/Constant'
       *  UnitDelay: '<S153>/Unit Delay'
       */
      autocodePlant_DW->UnitDelay_DSTATE_i += 0.01;

      /* Gain: '<S167>/Output' incorporates:
       *  RandomNumber: '<S167>/White Noise'
       */
      autocodePlant_B->Output_n = 3.7947521660754644 *
        autocodePlant_DW->NextOutput_m;

      /* Gain: '<S159>/Output' incorporates:
       *  RandomNumber: '<S159>/White Noise'
       */
      autocodePlant_B->Output_o[0] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S169>/Output' incorporates:
       *  RandomNumber: '<S169>/White Noise'
       */
      autocodePlant_B->Output_e[0] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Gain: '<S159>/Output' incorporates:
       *  RandomNumber: '<S159>/White Noise'
       */
      autocodePlant_B->Output_o[1] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S169>/Output' incorporates:
       *  RandomNumber: '<S169>/White Noise'
       */
      autocodePlant_B->Output_e[1] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Gain: '<S159>/Output' incorporates:
       *  RandomNumber: '<S159>/White Noise'
       */
      autocodePlant_B->Output_o[2] = 0.0019620245256641326 *
        autocodePlant_DW->NextOutput_k;

      /* Gain: '<S169>/Output' incorporates:
       *  RandomNumber: '<S169>/White Noise'
       */
      autocodePlant_B->Output_e[2] = 0.0004848060601641038 *
        autocodePlant_DW->NextOutput_a;

      /* Assertion: '<S180>/Assertion' incorporates:
       *  Constant: '<S180>/max_val'
       *  Constant: '<S180>/min_val'
       *  Logic: '<S180>/conjunction'
       *  RelationalOperator: '<S180>/max_relop'
       *  RelationalOperator: '<S180>/min_relop'
       */
      utAssert((rtb_Switch_d_idx_1 >= -1000.0) && (rtb_Switch_d_idx_1 <=
                850000.0));

      /* Assertion: '<S181>/Assertion' incorporates:
       *  Constant: '<S181>/max_val'
       *  Constant: '<S181>/min_val'
       *  Logic: '<S181>/conjunction'
       *  RelationalOperator: '<S181>/max_relop'
       *  RelationalOperator: '<S181>/min_relop'
       */
      utAssert((rtb_TmpSignalConversionAtProd_0 >= -90.0) &&
               (rtb_TmpSignalConversionAtProd_0 <= 90.0));

      /* Assertion: '<S182>/Assertion' incorporates:
       *  Constant: '<S182>/max_val'
       *  Constant: '<S182>/min_val'
       *  Logic: '<S182>/conjunction'
       *  RelationalOperator: '<S182>/max_relop'
       *  RelationalOperator: '<S182>/min_relop'
       */
      utAssert((rtb_UnaryMinus_a >= -180.0) && (rtb_UnaryMinus_a <= 180.0));

      /* Assertion: '<S184>/Assertion' */
      utAssert(autocodePlant_ConstB.conjunction);
    }
  }

  if (rtmIsMajorTimeStep(autocodePlant_M)) {
    int32_T idxDelay;
    boolean_T tmp;
    tmp = (rtmIsMajorTimeStep(autocodePlant_M) &&
           autocodePlant_M->Timing.TaskCounters.TID[1] == 0);
    if (tmp) {
      /* Update for DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn' */
      autocodePlant_DW->DiscreteTransferFcn_states = autocodePlant_B->Output_e[0]
        - 0.99995 * autocodePlant_DW->DiscreteTransferFcn_states;

      /* Update for DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states = autocodePlant_B->Output_e
        [1] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn1_states;

      /* Update for DiscreteTransferFcn: '<S156>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states = autocodePlant_B->Output_e
        [2] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn2_states;

      /* Update for DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_k =
        autocodePlant_B->Output_o[0] - 0.99995 *
        autocodePlant_DW->DiscreteTransferFcn2_states_k;

      /* Update for DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states_a =
        autocodePlant_B->Output_o[1] - 0.99995 *
        autocodePlant_DW->DiscreteTransferFcn1_states_a;

      /* Update for DiscreteTransferFcn: '<S154>/Discrete Transfer Fcn3' */
      autocodePlant_DW->DiscreteTransferFcn3_states = autocodePlant_B->Output_o
        [2] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn3_states;

      /* Update for RandomNumber: '<S160>/White Noise' */
      autocodePlant_DW->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed);

      /* Update for Delay: '<S6>/Delay' */
      for (idxDelay = 0; idxDelay < 499; idxDelay++) {
        autocodePlant_DW->Delay_DSTATE[idxDelay] =
          autocodePlant_DW->Delay_DSTATE[idxDelay + 1];
      }

      autocodePlant_DW->Delay_DSTATE[499] = rtb_uDLookupTable;

      /* End of Update for Delay: '<S6>/Delay' */

      /* Update for RandomNumber: '<S170>/White Noise' */
      autocodePlant_DW->NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_l);

      /* Update for UnitDelay: '<S156>/Unit Delay' */
      autocodePlant_DW->UnitDelay_DSTATE[0] = autocodePlant_B->fBdy_mps2[0];
      autocodePlant_DW->UnitDelay_DSTATE[1] = autocodePlant_B->fBdy_mps2[1];
      autocodePlant_DW->UnitDelay_DSTATE[2] = autocodePlant_B->fBdy_mps2[2];

      /* Update for RandomNumber: '<S173>/White Noise' */
      autocodePlant_DW->NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_a);

      /* Update for Memory: '<S206>/otime' incorporates:
       *  Constant: '<S157>/decimal year'
       */
      autocodePlant_DW->otime_PreviousInput = 2026.6657534246576;

      /* Update for Memory: '<S205>/olon' */
      autocodePlant_DW->olon_PreviousInput = autocodePlant_B->Switch;

      /* Update for Memory: '<S204>/olat' */
      autocodePlant_DW->olat_PreviousInput = autocodePlant_B->Switch_l;

      /* Update for Memory: '<S204>/oalt' */
      autocodePlant_DW->oalt_PreviousInput = autocodePlant_B->Gain;

      /* Update for RandomNumber: '<S168>/White Noise' */
      autocodePlant_DW->NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_b);

      /* Update for DiscreteTransferFcn: '<S155>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_h =
        autocodePlant_B->Output_n - 0.99998 *
        autocodePlant_DW->DiscreteTransferFcn2_states_h;
    }

    if (rtmIsMajorTimeStep(autocodePlant_M) &&
        autocodePlant_M->Timing.TaskCounters.TID[2] == 0) {
      /* Update for RandomNumber: '<S114>/White Noise' */
      autocodePlant_DW->NextOutput_d[0] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[0]);
      autocodePlant_DW->NextOutput_d[1] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[1]);
      autocodePlant_DW->NextOutput_d[2] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[2]);
      autocodePlant_DW->NextOutput_d[3] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_i[3]);
    }

    if (tmp) {
      /* Update for RandomNumber: '<S159>/White Noise' */
      autocodePlant_DW->NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_p);

      /* Update for RandomNumber: '<S167>/White Noise' */
      autocodePlant_DW->NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_pb);

      /* Update for RandomNumber: '<S169>/White Noise' */
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
  _rtXdot->uDOFQuaternion_CSTATE[0] = autocodePlant_B->Sum[0] / 18.0 -
    (autocodePlant_X->uDOFQuaternion_CSTATE[2] *
     autocodePlant_X->uDOFQuaternion_CSTATE[7] -
     autocodePlant_X->uDOFQuaternion_CSTATE[1] *
     autocodePlant_X->uDOFQuaternion_CSTATE[8]);
  _rtXdot->uDOFQuaternion_CSTATE[1] = autocodePlant_B->Sum[1] / 18.0 -
    (autocodePlant_X->uDOFQuaternion_CSTATE[0] *
     autocodePlant_X->uDOFQuaternion_CSTATE[8] -
     autocodePlant_X->uDOFQuaternion_CSTATE[2] *
     autocodePlant_X->uDOFQuaternion_CSTATE[6]);
  _rtXdot->uDOFQuaternion_CSTATE[2] = autocodePlant_B->Sum[2] / 18.0 -
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
  uDOFQuaternion_CSTATE_tmp_0 = (autocodePlant_B->Product[0] -
    (autocodePlant_X->uDOFQuaternion_CSTATE[7] * pData_idx_2 -
     autocodePlant_X->uDOFQuaternion_CSTATE[8] * pData_idx_1)) - ((0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[6] + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[7]) + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[8]);
  uDOFQuaternion_CSTATE_tmp_1 = (autocodePlant_B->Product[1] -
    (autocodePlant_X->uDOFQuaternion_CSTATE[8] * pData_idx_0 -
     autocodePlant_X->uDOFQuaternion_CSTATE[6] * pData_idx_2)) - ((0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[6] + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[7]) + 0.0 *
    autocodePlant_X->uDOFQuaternion_CSTATE[8]);
  pData_idx_2 = (autocodePlant_B->Product[2] -
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

  /* Derivatives for Enabled SubSystem: '<S104>/Hpgw' */
  if (autocodePlant_DW->Hpgw_MODE) {
    /* Derivatives for Integrator: '<S115>/pgw_p' */
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

  /* End of Derivatives for SubSystem: '<S104>/Hpgw' */

  /* Derivatives for Enabled SubSystem: '<S105>/Hwgw(s)' */
  if (autocodePlant_DW->Hwgws_MODE) {
    /* Derivatives for Integrator: '<S120>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[0] = autocodePlant_B->w[0];

    /* Derivatives for Integrator: '<S120>/wg_p2' */
    _rtXdot->wg_p2_CSTATE[0] = autocodePlant_B->w_h[0];

    /* Derivatives for Integrator: '<S120>/wg_p1' */
    _rtXdot->wg_p1_CSTATE[1] = autocodePlant_B->w[1];

    /* Derivatives for Integrator: '<S120>/wg_p2' */
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

  /* End of Derivatives for SubSystem: '<S105>/Hwgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S104>/Hqgw' */
  if (autocodePlant_DW->Hqgw_MODE) {
    /* Derivatives for Integrator: '<S116>/qgw_p' */
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

  /* End of Derivatives for SubSystem: '<S104>/Hqgw' */

  /* Derivatives for Enabled SubSystem: '<S105>/Hvgw(s)' */
  if (autocodePlant_DW->Hvgws_MODE) {
    /* Derivatives for Integrator: '<S119>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[0] = autocodePlant_B->w_c[0];

    /* Derivatives for Integrator: '<S119>/vgw_p2' */
    _rtXdot->vgw_p2_CSTATE[0] = autocodePlant_B->w_j[0];

    /* Derivatives for Integrator: '<S119>/vg_p1' */
    _rtXdot->vg_p1_CSTATE[1] = autocodePlant_B->w_c[1];

    /* Derivatives for Integrator: '<S119>/vgw_p2' */
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

  /* End of Derivatives for SubSystem: '<S105>/Hvgw(s)' */

  /* Derivatives for Enabled SubSystem: '<S104>/Hrgw' */
  if (autocodePlant_DW->Hrgw_MODE) {
    /* Derivatives for Integrator: '<S117>/rgw_p' */
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

  /* End of Derivatives for SubSystem: '<S104>/Hrgw' */

  /* Derivatives for Enabled SubSystem: '<S105>/Hugw(s)' */
  if (autocodePlant_DW->Hugws_MODE) {
    /* Derivatives for Integrator: '<S118>/ug_p' */
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

  /* End of Derivatives for SubSystem: '<S105>/Hugw(s)' */
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

    /* Start for If: '<S194>/If' */
    autocodePlant_DW->If_ActiveSubsystem = -1;

    /* Start for If: '<S109>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = -1;

    /* Start for If: '<S110>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_f = -1;

    /* InitializeConditions for RandomNumber: '<S160>/White Noise' */
    autocodePlant_DW->RandSeed = 1529675776U;
    autocodePlant_DW->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed);

    /* InitializeConditions for EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)' */
    autocodePlant_X->uDOFQuaternion_CSTATE[0] = 0.001;
    autocodePlant_X->uDOFQuaternion_CSTATE[3] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[6] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[1] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[4] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[7] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[2] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[5] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[8] = 0.0;
    autocodePlant_X->uDOFQuaternion_CSTATE[9] = 0.6700440439317529;
    autocodePlant_X->uDOFQuaternion_CSTATE[10] = 0.033530148645199376;
    autocodePlant_X->uDOFQuaternion_CSTATE[11] = 0.7406369298317471;
    autocodePlant_X->uDOFQuaternion_CSTATE[12] = 0.037062737254794836;

    /* InitializeConditions for RandomNumber: '<S170>/White Noise' */
    autocodePlant_DW->RandSeed_l = 1529675776U;
    autocodePlant_DW->NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_l);

    /* InitializeConditions for RandomNumber: '<S173>/White Noise' */
    autocodePlant_DW->RandSeed_a = 1529675776U;
    autocodePlant_DW->NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_a);

    /* InitializeConditions for Memory: '<S206>/otime' */
    autocodePlant_DW->otime_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S205>/olon' */
    autocodePlant_DW->olon_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S204>/olat' */
    autocodePlant_DW->olat_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S204>/oalt' */
    autocodePlant_DW->oalt_PreviousInput = -1000.0;

    /* InitializeConditions for RandomNumber: '<S168>/White Noise' */
    autocodePlant_DW->RandSeed_b = 1529675776U;
    autocodePlant_DW->NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_b);

    /* InitializeConditions for RandomNumber: '<S114>/White Noise' */
    autocodePlant_DW->RandSeed_i[0] = 1529675776U;
    autocodePlant_DW->NextOutput_d[0] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[0]);
    autocodePlant_DW->RandSeed_i[1] = 1529741312U;
    autocodePlant_DW->NextOutput_d[1] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[1]);
    autocodePlant_DW->RandSeed_i[2] = 1529806848U;
    autocodePlant_DW->NextOutput_d[2] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[2]);
    autocodePlant_DW->RandSeed_i[3] = 1529872384U;
    autocodePlant_DW->NextOutput_d[3] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_i[3]);

    /* InitializeConditions for RandomNumber: '<S159>/White Noise' */
    autocodePlant_DW->RandSeed_p = 1529675776U;
    autocodePlant_DW->NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_p);

    /* InitializeConditions for RandomNumber: '<S167>/White Noise' */
    autocodePlant_DW->RandSeed_pb = 1529675776U;
    autocodePlant_DW->NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_pb);

    /* InitializeConditions for RandomNumber: '<S169>/White Noise' */
    autocodePlant_DW->RandSeed_pa = 1529675776U;
    autocodePlant_DW->NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_pa);

    /* SystemInitialize for Merge: '<S194>/Merge' */
    autocodePlant_B->Merge = 1.0;

    /* SystemInitialize for Enabled SubSystem: '<S189>/Convert from geodetic to  spherical coordinates ' */
    /* SystemInitialize for Iterator SubSystem: '<S202>/For Iterator Subsystem' */
    /* SystemInitialize for Assignment: '<S249>/Assignment' incorporates:
     *  Outport: '<S249>/sp[11]'
     */
    memcpy(&autocodePlant_B->Assignment[0], &rtCP__sp11_Y0[0], 11U * sizeof
           (real_T));

    /* SystemInitialize for Assignment: '<S249>/Assignment1' incorporates:
     *  Outport: '<S249>/cp[11]'
     */
    memcpy(&autocodePlant_B->Assignment1[0], &rtCP__cp11_Y0[0], 11U * sizeof
           (real_T));

    /* End of SystemInitialize for SubSystem: '<S202>/For Iterator Subsystem' */

    /* SystemInitialize for SignalConversion generated from: '<S202>/sp[13]' incorporates:
     *  Outport: '<S202>/sp[13]'
     */
    memcpy(&autocodePlant_B->OutportBufferForsp13[0], &rtCP__sp13_Y0[0], 13U *
           sizeof(real_T));

    /* SystemInitialize for SignalConversion generated from: '<S202>/cp[13]' incorporates:
     *  Outport: '<S202>/cp[13]'
     */
    memcpy(&autocodePlant_B->OutportBufferForcp13[0], &rtCP__cp13_Y0[0], 13U *
           sizeof(real_T));

    /* End of SystemInitialize for SubSystem: '<S189>/Convert from geodetic to  spherical coordinates ' */

    /* SystemInitialize for Enabled SubSystem: '<S189>/Convert from geodetic to  spherical coordinates' */
    /* SystemInitialize for Sqrt: '<S201>/sqrt' incorporates:
     *  Outport: '<S201>/r'
     */
    autocodePlant_B->sqrt_b = 6378.137;

    /* SystemInitialize for Product: '<S242>/Product4' incorporates:
     *  Outport: '<S201>/ct'
     */
    autocodePlant_B->Product4 = 1.0;

    /* End of SystemInitialize for SubSystem: '<S189>/Convert from geodetic to  spherical coordinates' */

    /* SystemInitialize for Iterator SubSystem: '<S189>/Compute magnetic vector in spherical coordinates' */
    /* InitializeConditions for UnitDelay: '<S200>/Unit Delay2' */
    autocodePlant_DW->UnitDelay2_DSTATE[0] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[1] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[2] = 0.0;
    autocodePlant_DW->UnitDelay2_DSTATE[3] = 0.0;

    /* SystemInitialize for Iterator SubSystem: '<S200>/For Iterator Subsystem' */
    /* SystemInitialize for Enabled SubSystem: '<S208>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */
    /* SystemInitialize for Merge: '<S210>/Merge' */
    autocodePlant_B->Merge_b = 0.0;

    /* SystemInitialize for Merge: '<S210>/Merge1' */
    autocodePlant_B->Merge1_i = 0.0;

    /* InitializeConditions for UnitDelay: '<S210>/Unit Delay1' */
    memcpy(&autocodePlant_DW->UnitDelay1_DSTATE_c[0],
           &rtCP__UnitDelay1_InitialCondi_n[0], 169U * sizeof(real_T));

    /* SystemInitialize for Assignment: '<S210>/Assignment_snorm' incorporates:
     *  Outport: '<S210>/snorm[169]'
     */
    memcpy(&autocodePlant_B->Assignment_snorm[0], &rtCP__snorm169_Y0[0], 169U *
           sizeof(real_T));

    /* End of SystemInitialize for SubSystem: '<S208>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' */

    /* SystemInitialize for Enabled SubSystem: '<S209>/Special case - North//South Geographic Pole' */
    /* SystemInitialize for IfAction SubSystem: '<S212>/If Action Subsystem2' */
    /* SystemInitialize for IfAction SubSystem: '<S212>/If Action Subsystem1' */
    for (i = 0; i < 13; i++) {
      /* InitializeConditions for UnitDelay: '<S212>/Unit Delay1' */
      autocodePlant_DW->UnitDelay1_DSTATE_b[i] = 1.0;

      /* SystemInitialize for Assignment: '<S216>/Assignment2' incorporates:
       *  Outport: '<S216>/pp[13]'
       */
      autocodePlant_B->Assignment2_m[i] = 1.0;

      /* SystemInitialize for Assignment: '<S217>/Assignment2' incorporates:
       *  Outport: '<S217>/pp[13]'
       */
      autocodePlant_B->Assignment2_a[i] = 1.0;
    }

    /* End of SystemInitialize for SubSystem: '<S212>/If Action Subsystem1' */
    /* End of SystemInitialize for SubSystem: '<S212>/If Action Subsystem2' */
    /* End of SystemInitialize for SubSystem: '<S209>/Special case - North//South Geographic Pole' */
    /* End of SystemInitialize for SubSystem: '<S200>/For Iterator Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S189>/Compute magnetic vector in spherical coordinates' */

    /* SystemInitialize for Enabled SubSystem: '<S104>/Hpgw' */
    /* InitializeConditions for Integrator: '<S115>/pgw_p' */
    autocodePlant_X->pgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S104>/Hpgw' */

    /* SystemInitialize for Enabled SubSystem: '<S105>/Hwgw(s)' */
    /* InitializeConditions for Integrator: '<S120>/wg_p1' */
    autocodePlant_X->wg_p1_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S120>/wg_p2' */
    autocodePlant_X->wg_p2_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S105>/Hwgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S104>/Hqgw' */
    /* InitializeConditions for Integrator: '<S116>/qgw_p' */
    autocodePlant_X->qgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S104>/Hqgw' */

    /* SystemInitialize for Enabled SubSystem: '<S105>/Hvgw(s)' */
    /* InitializeConditions for Integrator: '<S119>/vg_p1' */
    autocodePlant_X->vg_p1_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S119>/vgw_p2' */
    autocodePlant_X->vgw_p2_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S105>/Hvgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S104>/Hrgw' */
    /* InitializeConditions for Integrator: '<S117>/rgw_p' */
    autocodePlant_X->rgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S104>/Hrgw' */

    /* SystemInitialize for Enabled SubSystem: '<S105>/Hugw(s)' */
    /* InitializeConditions for Integrator: '<S118>/ug_p' */
    autocodePlant_X->ug_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S105>/Hugw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S104>/Hpgw' */
    /* InitializeConditions for Integrator: '<S115>/pgw_p' */
    autocodePlant_X->pgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S104>/Hpgw' */

    /* SystemInitialize for Enabled SubSystem: '<S105>/Hwgw(s)' */
    /* InitializeConditions for Integrator: '<S120>/wg_p1' */
    autocodePlant_X->wg_p1_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S120>/wg_p2' */
    autocodePlant_X->wg_p2_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S105>/Hwgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S104>/Hqgw' */
    /* InitializeConditions for Integrator: '<S116>/qgw_p' */
    autocodePlant_X->qgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S104>/Hqgw' */

    /* SystemInitialize for Enabled SubSystem: '<S105>/Hvgw(s)' */
    /* InitializeConditions for Integrator: '<S119>/vg_p1' */
    autocodePlant_X->vg_p1_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S119>/vgw_p2' */
    autocodePlant_X->vgw_p2_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S105>/Hvgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S104>/Hrgw' */
    /* InitializeConditions for Integrator: '<S117>/rgw_p' */
    autocodePlant_X->rgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S104>/Hrgw' */

    /* SystemInitialize for Enabled SubSystem: '<S105>/Hugw(s)' */
    /* InitializeConditions for Integrator: '<S118>/ug_p' */
    autocodePlant_X->ug_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S105>/Hugw(s)' */
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
