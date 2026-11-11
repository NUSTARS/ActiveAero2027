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
 * C/C++ source code generated on : Tue Nov 10 19:36:56 2026
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
#include "autocodePlantParams_calibration_types.h"
#include "autocodePlant_types.h"
#include "rt_nrand_Upu32_Yd_f_pw_snf.h"
#include "rt_urand_Upu32_Yd_f_pw_snf.h"
#include "autocodePlant_private.h"
#include "plook_bincpa.h"
#include "intrp2d_la_pw.h"
#include "plook_binx.h"
#include "intrp3d_l_pw.h"
#include "look2_binlxpw.h"
#include "look2_binlcpw.h"
#include "mul_s32_sat.h"
#include "look1_binlcpw.h"
#include "autocodePlantParams_calibration.h"

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
    real_T rtb_Delay[6];
    real_T rtb_ElementProduct[6];
    real_T rtb_ElementProduct_k[6];
    real_T Gdependent[3];
    real_T biasnoise_d[3];
    real_T rtb_MathFunction[3];
    real_T rtb_Product6_kk[3];
    real_T rtb_Product_ab[3];
    real_T rtb_Product_lj[3];
    real_T rtb_Sum1_gf[3];
    real_T rtb_Sum_aw[3];
    real_T rtb_Sum_cy[3];
    real_T rtb_Sum_e[3];
    real_T rtb_Sum_j[3];
    real_T rtb_Sum_k[3];
    real_T rtb_Sum_mu[3];
    real_T rtb_Sum_pz[3];
    real_T rtb_VectorConcatenate[3];
    real_T rtb_ZeroOrderHold[3];
    real_T rtb_ZeroOrderHold_g[3];
    real_T rtb_ZeroOrderHold_i[3];
    real_T rtb_bias[3];
    real_T rtb_bias_n[3];
    real_T rtb_velBdy_mps[3];
    real_T rtb_wBdy_rps[3];
    real_T rtb_Lv[2];
    real_T Merge1;
    real_T Merge_n;
    real_T Sum_a_tmp;
    real_T Sum_bx_tmp;
    real_T Sum_bx_tmp_0;
    real_T Sum_bx_tmp_1;
    real_T UnitDelay1_DSTATE_a;
    real_T UnitDelay4_DSTATE;
    real_T rtb_Abs1;
    real_T rtb_DiscreteTransferFcn1;
    real_T rtb_DiscreteTransferFcn2;
    real_T rtb_FlatEarthtoLLA_o1_idx_0;
    real_T rtb_FlatEarthtoLLA_o1_idx_1;
    real_T rtb_Gain_n;
    real_T rtb_Gain_nu;
    real_T rtb_LowAltitudeScaleLength;
    real_T rtb_Lw_idx_1;
    real_T rtb_MediumHighAltitudeIntensity;
    real_T rtb_Product1_do;
    real_T rtb_Product2_l3;
    real_T rtb_Product3_eg;
    real_T rtb_Product4_a;
    real_T rtb_Product8_ne;
    real_T rtb_Sign1;
    real_T rtb_Sign1_e;
    real_T rtb_Sign1_l;
    real_T rtb_Sum1_hj_idx_0;
    real_T rtb_Sum1_hj_idx_1;
    real_T rtb_Sum1_hwh_idx_1;
    real_T rtb_Sum1_nc_idx_0;
    real_T rtb_Sum1_ob;
    real_T rtb_Sum_a_idx_2;
    real_T rtb_Sum_b4;
    real_T rtb_Sum_gx;
    real_T rtb_Sum_o5;
    real_T rtb_Switch_d_idx_0;
    real_T rtb_Switch_d_idx_1;
    real_T rtb_Switch_d_idx_2;
    real_T rtb_TT0gLR;
    real_T rtb_UnaryMinus1;
    real_T rtb_UnaryMinus1_c;
    real_T rtb_UnaryMinus1_e;
    real_T rtb_UnaryMinus1_o;
    real_T rtb_UnaryMinus_n;
    real_T rtb_UnaryMinus_o3;
    real_T rtb_UnitConversion;
    real_T rtb_UnitConversion_e;
    real_T rtb_UnitDelay2_idx_0;
    real_T rtb_UnitDelay2_idx_1;
    real_T rtb_UnitDelay2_idx_3;
    real_T rtb_posNed_m_idx_0;
    real_T rtb_posNed_m_idx_1;
    real_T rtb_posNed_m_idx_2;
    real_T rtb_q_na_idx_0;
    real_T rtb_q_na_idx_1;
    real_T rtb_q_na_idx_2;
    real_T rtb_q_na_idx_3;
    real_T rtb_sigma_ugsigma_vg;
    real_T rtb_sincos_o1_idx_0;
    real_T rtb_sincos_o1_idx_1;
    real_T rtb_sincos_o2_f_idx_0;
    real_T tmp_1;
    real_T tmp_2;
    int32_T Merge_b_tmp;
    int32_T i;
    int32_T rtb_Sum2_p0;
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
    boolean_T rtb_RelationalOperator;
    boolean_T rtb_max_relop_c;
    boolean_T tmp;
    boolean_T tmp_0;

    /* EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)' */
    rtb_velBdy_mps[0] = autocodePlant_X->uDOFQuaternion_CSTATE[0];
    rtb_velBdy_mps[1] = autocodePlant_X->uDOFQuaternion_CSTATE[1];
    rtb_velBdy_mps[2] = autocodePlant_X->uDOFQuaternion_CSTATE[2];
    rtb_posNed_m_idx_0 = autocodePlant_X->uDOFQuaternion_CSTATE[3];
    rtb_posNed_m_idx_1 = autocodePlant_X->uDOFQuaternion_CSTATE[4];
    rtb_posNed_m_idx_2 = autocodePlant_X->uDOFQuaternion_CSTATE[5];
    rtb_wBdy_rps[0] = autocodePlant_X->uDOFQuaternion_CSTATE[6];
    rtb_wBdy_rps[1] = autocodePlant_X->uDOFQuaternion_CSTATE[7];
    rtb_wBdy_rps[2] = autocodePlant_X->uDOFQuaternion_CSTATE[8];
    rtb_q_na_idx_0 = autocodePlant_X->uDOFQuaternion_CSTATE[9];
    rtb_q_na_idx_1 = autocodePlant_X->uDOFQuaternion_CSTATE[10];
    rtb_q_na_idx_2 = autocodePlant_X->uDOFQuaternion_CSTATE[11];
    rtb_q_na_idx_3 = autocodePlant_X->uDOFQuaternion_CSTATE[12];

    /* Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix' incorporates:
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
    rtb_Sum_b4 = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
      autocodePlant_X->uDOFQuaternion_CSTATE[9] +
      autocodePlant_X->uDOFQuaternion_CSTATE[10] *
      autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[11] *
      autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[12] *
      autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
      autocodePlant_X->uDOFQuaternion_CSTATE[12];
    rtb_Product3_eg = 1.0 / sqrt(((autocodePlant_X->uDOFQuaternion_CSTATE[9] *
      autocodePlant_X->uDOFQuaternion_CSTATE[9] +
      autocodePlant_X->uDOFQuaternion_CSTATE[10] *
      autocodePlant_X->uDOFQuaternion_CSTATE[10]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[11] *
      autocodePlant_X->uDOFQuaternion_CSTATE[11]) +
      autocodePlant_X->uDOFQuaternion_CSTATE[12] *
      autocodePlant_X->uDOFQuaternion_CSTATE[12]) *
      autocodePlant_X->uDOFQuaternion_CSTATE[9];
    rtb_UnitConversion = rtb_Product3_eg * rtb_Product3_eg;
    rtb_UnitConversion_e = rtb_Switch_d_idx_1 * rtb_Switch_d_idx_1;
    rtb_MediumHighAltitudeIntensity = rtb_Switch_d_idx_2 * rtb_Switch_d_idx_2;
    rtb_sigma_ugsigma_vg = rtb_Sum_b4 * rtb_Sum_b4;
    rtb_QuaternionstoDirectionCosin[0] = ((rtb_UnitConversion +
      rtb_UnitConversion_e) - rtb_MediumHighAltitudeIntensity) -
      rtb_sigma_ugsigma_vg;
    rtb_sincos_o2_f_idx_0 = rtb_Switch_d_idx_1 * rtb_Switch_d_idx_2;
    rtb_LowAltitudeScaleLength = rtb_Product3_eg * rtb_Sum_b4;
    rtb_QuaternionstoDirectionCosin[3] = (rtb_sincos_o2_f_idx_0 +
      rtb_LowAltitudeScaleLength) * 2.0;
    rtb_Sign1 = rtb_Switch_d_idx_1 * rtb_Sum_b4;
    rtb_Product2_l3 = rtb_Product3_eg * rtb_Switch_d_idx_2;
    rtb_QuaternionstoDirectionCosin[6] = (rtb_Sign1 - rtb_Product2_l3) * 2.0;
    rtb_QuaternionstoDirectionCosin[1] = (rtb_sincos_o2_f_idx_0 -
      rtb_LowAltitudeScaleLength) * 2.0;
    rtb_UnitConversion -= rtb_UnitConversion_e;
    rtb_QuaternionstoDirectionCosin[4] = (rtb_UnitConversion +
      rtb_MediumHighAltitudeIntensity) - rtb_sigma_ugsigma_vg;
    rtb_UnitConversion_e = rtb_Switch_d_idx_2 * rtb_Sum_b4;
    rtb_sincos_o2_f_idx_0 = rtb_Product3_eg * rtb_Switch_d_idx_1;
    rtb_QuaternionstoDirectionCosin[7] = (rtb_UnitConversion_e +
      rtb_sincos_o2_f_idx_0) * 2.0;
    rtb_QuaternionstoDirectionCosin[2] = (rtb_Sign1 + rtb_Product2_l3) * 2.0;
    rtb_QuaternionstoDirectionCosin[5] = (rtb_UnitConversion_e -
      rtb_sincos_o2_f_idx_0) * 2.0;
    rtb_QuaternionstoDirectionCosin[8] = (rtb_UnitConversion -
      rtb_MediumHighAltitudeIntensity) + rtb_sigma_ugsigma_vg;

    /* UnitConversion: '<S122>/Unit Conversion' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     *  UnaryMinus: '<S101>/Unary Minus'
     */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    rtb_UnitConversion = 3.280839895013123 *
      -autocodePlant_X->uDOFQuaternion_CSTATE[5];

    /* Outputs for Enabled SubSystem: '<S120>/Hrgw' incorporates:
     *  EnablePort: '<S133>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S120>/Hqgw' incorporates:
     *  EnablePort: '<S132>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hugw(s)' incorporates:
     *  EnablePort: '<S134>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hvgw(s)' incorporates:
     *  EnablePort: '<S135>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S121>/Hwgw(s)' incorporates:
     *  EnablePort: '<S136>/Enable'
     */
    /* RateTransition: '<S174>/Rate Transition1' */
    tmp = (rtmIsMajorTimeStep(autocodePlant_M) &&
           autocodePlant_M->Timing.TaskCounters.TID[1] == 0);

    /* End of Outputs for SubSystem: '<S121>/Hwgw(s)' */
    /* End of Outputs for SubSystem: '<S121>/Hvgw(s)' */
    /* End of Outputs for SubSystem: '<S121>/Hugw(s)' */
    /* End of Outputs for SubSystem: '<S120>/Hqgw' */
    /* End of Outputs for SubSystem: '<S120>/Hrgw' */
    if (tmp) {
      /* UnitConversion: '<S119>/Unit Conversion' incorporates:
       *  Constant: '<S117>/Wind direction'
       */
      /* Unit Conversion - from: deg to: rad
         Expression: output = (0.0174533*input) + (0) */
      autocodePlant_B->UnitConversion = 0.017453292519943295 *
        windParams.lowAltWindDir_deg;
    }

    /* Saturate: '<S155>/Limit Function 10ft to 1000ft' */
    if (rtb_UnitConversion > 1000.0) {
      rtb_Product3_eg = 1000.0;
    } else if (rtb_UnitConversion < 10.0) {
      rtb_Product3_eg = 10.0;
    } else {
      rtb_Product3_eg = rtb_UnitConversion;
    }

    /* End of Saturate: '<S155>/Limit Function 10ft to 1000ft' */

    /* Gain: '<S127>/Lw' */
    rtb_Lw_idx_1 = autocodePlant_ConstB.UnitConversion;
    if (tmp) {
      /* Gain: '<S138>/sigma_wg ' incorporates:
       *  Constant: '<S117>/Windspeed at 20ft (6m)'
       *  UnitConversion: '<S129>/Unit Conversion'
       */
      /* Unit Conversion - from: m/s to: ft/s
         Expression: output = (3.28084*input) + (0) */
      autocodePlant_B->sigma_wg = 3.280839895013123 *
        windParams.lowAltWindSpeed_mps * 0.1;
    }

    /* Interpolation_n-D: '<S137>/Medium//High Altitude Intensity' incorporates:
     *  PreLookup: '<S137>/PreLook-Up Index Search  (altitude)'
     *  PreLookup: '<S137>/PreLook-Up Index Search  (prob of exceed)'
     */
    bpIndex[0] = plook_bincpa(rtb_UnitConversion,
      rtCP__PreLookUpIndexSearchaltit, 11U, &rtb_Lv[0],
      &autocodePlant_DW->PreLookUpIndexSearchaltitude_DW);
    rtb_Lv[1] = autocodePlant_ConstB.PreLookUpIndexSearchprobofe;
    bpIndex[1] = autocodePlant_ConstB.PreLookUpIndexSearchprobo_j;
    rtb_MediumHighAltitudeIntensity = intrp2d_la_pw(bpIndex, rtb_Lv,
      rtCP__MediumHighAltitudeIntensi, 12U, rtCP__MediumHighAltitudeInten_o);
    if (tmp) {
      /* Product: '<S130>/Product' incorporates:
       *  RandomNumber: '<S130>/White Noise'
       */
      autocodePlant_B->Product[0] = autocodePlant_ConstB.Divide[0] *
        autocodePlant_DW->NextOutput[0];
      autocodePlant_B->Product[1] = autocodePlant_ConstB.Divide[1] *
        autocodePlant_DW->NextOutput[1];
      autocodePlant_B->Product[2] = autocodePlant_ConstB.Divide[2] *
        autocodePlant_DW->NextOutput[2];
      autocodePlant_B->Product[3] = autocodePlant_ConstB.Divide[3] *
        autocodePlant_DW->NextOutput[3];
    }

    /* DotProduct: '<S101>/Dot Product' incorporates:
     *  EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)'
     */
    rtb_UnitConversion_e = (autocodePlant_X->uDOFQuaternion_CSTATE[0] *
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
    if (rtb_UnitConversion_e >= 0.0) {
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
    rtb_UnitConversion_e = sqrt((real_T)i * fmax(1.0E-6, rtb_UnitConversion_e)) *
      3.280839895013123;

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
      rtb_sincos_o2_f_idx_0 = rtb_Product3_eg / rtb_UnitConversion_e;

      /* Product: '<S136>/w' incorporates:
       *  Gain: '<S136>/1//pi'
       *  Integrator: '<S136>/wg_p1'
       *  Product: '<S136>/Lug//V1'
       *  Sqrt: '<S136>/sqrt1'
       *  Sum: '<S136>/Sum'
       */
      rtb_sigma_ugsigma_vg = (sqrt(0.3183098861837907 * rtb_sincos_o2_f_idx_0) *
        autocodePlant_B->Product[2] - autocodePlant_X->wg_p1_CSTATE[0]) /
        rtb_sincos_o2_f_idx_0;
      autocodePlant_B->w[0] = rtb_sigma_ugsigma_vg;

      /* Product: '<S136>/w ' incorporates:
       *  Integrator: '<S136>/wg_p1'
       *  Integrator: '<S136>/wg_p2'
       *  Product: '<S136>/Lwg//V '
       *  Sum: '<S136>/Sum1'
       */
      autocodePlant_B->w_h[0] = (rtb_sigma_ugsigma_vg *
        autocodePlant_ConstB.sqrt_g * rtb_sincos_o2_f_idx_0 +
        (autocodePlant_X->wg_p1_CSTATE[0] - autocodePlant_X->wg_p2_CSTATE[0])) /
        rtb_sincos_o2_f_idx_0;

      /* Product: '<S136>/Lwg//V' */
      rtb_sincos_o2_f_idx_0 = rtb_Lw_idx_1 / rtb_UnitConversion_e;

      /* Product: '<S136>/w' incorporates:
       *  Gain: '<S136>/1//pi'
       *  Integrator: '<S136>/wg_p1'
       *  Product: '<S136>/Lug//V1'
       *  Sqrt: '<S136>/sqrt1'
       *  Sum: '<S136>/Sum'
       */
      rtb_sigma_ugsigma_vg = (sqrt(0.3183098861837907 * rtb_sincos_o2_f_idx_0) *
        autocodePlant_B->Product[2] - autocodePlant_X->wg_p1_CSTATE[1]) /
        rtb_sincos_o2_f_idx_0;
      autocodePlant_B->w[1] = rtb_sigma_ugsigma_vg;

      /* Product: '<S136>/w ' incorporates:
       *  Integrator: '<S136>/wg_p1'
       *  Integrator: '<S136>/wg_p2'
       *  Product: '<S136>/Lwg//V '
       *  Sum: '<S136>/Sum1'
       */
      autocodePlant_B->w_h[1] = (rtb_sigma_ugsigma_vg *
        autocodePlant_ConstB.sqrt_g * rtb_sincos_o2_f_idx_0 +
        (autocodePlant_X->wg_p1_CSTATE[1] - autocodePlant_X->wg_p2_CSTATE[1])) /
        rtb_sincos_o2_f_idx_0;

      /* Product: '<S136>/Lwg//V 1' incorporates:
       *  Integrator: '<S136>/wg_p2'
       */
      autocodePlant_B->LwgV1[0] = autocodePlant_B->sigma_wg *
        autocodePlant_X->wg_p2_CSTATE[0];
      autocodePlant_B->LwgV1[1] = rtb_MediumHighAltitudeIntensity *
        autocodePlant_X->wg_p2_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S121>/Hwgw(s)' */

    /* Saturate: '<S138>/Limit Height h<1000ft' */
    if (rtb_UnitConversion > 1000.0) {
      rtb_UnaryMinus1_o = 1000.0;
    } else if (rtb_UnitConversion < 0.0) {
      rtb_UnaryMinus1_o = 0.0;
    } else {
      rtb_UnaryMinus1_o = rtb_UnitConversion;
    }

    /* Product: '<S138>/sigma_ug, sigma_vg' incorporates:
     *  Fcn: '<S138>/Low Altitude Intensity'
     *  Saturate: '<S138>/Limit Height h<1000ft'
     */
    rtb_sigma_ugsigma_vg = 1.0 / rt_powd_snf(0.000823 * rtb_UnaryMinus1_o +
      0.177, 0.4) * autocodePlant_B->sigma_wg;

    /* Fcn: '<S155>/Low Altitude Scale Length' */
    rtb_LowAltitudeScaleLength = rtb_Product3_eg / rt_powd_snf(0.000823 *
      rtb_Product3_eg + 0.177, 1.2);

    /* Gain: '<S127>/Lv' */
    rtb_Lv[1] = autocodePlant_ConstB.UnitConversion;

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
      rtb_sincos_o2_f_idx_0 = rtb_LowAltitudeScaleLength / rtb_UnitConversion_e;

      /* Product: '<S135>/w' incorporates:
       *  Gain: '<S135>/(1//pi)'
       *  Integrator: '<S135>/vg_p1'
       *  Product: '<S135>/Lug//V1'
       *  Sqrt: '<S135>/sqrt'
       *  Sum: '<S135>/Sum'
       */
      rtb_Sign1 = (sqrt(0.3183098861837907 * rtb_sincos_o2_f_idx_0) *
                   autocodePlant_B->Product[1] - autocodePlant_X->vg_p1_CSTATE[0])
        / rtb_sincos_o2_f_idx_0;
      autocodePlant_B->w_c[0] = rtb_Sign1;

      /* Product: '<S135>/w ' incorporates:
       *  Gain: '<S135>/sqrt(3)'
       *  Integrator: '<S135>/vg_p1'
       *  Integrator: '<S135>/vgw_p2'
       *  Product: '<S135>/Lvg//V '
       *  Sum: '<S135>/Sum1'
       */
      autocodePlant_B->w_j[0] = (rtb_Sign1 * rtb_sincos_o2_f_idx_0 *
        1.7320508075688772 + (autocodePlant_X->vg_p1_CSTATE[0] -
        autocodePlant_X->vgw_p2_CSTATE[0])) / rtb_sincos_o2_f_idx_0;

      /* Product: '<S135>/Lvg//V' */
      rtb_sincos_o2_f_idx_0 = rtb_Lv[1] / rtb_UnitConversion_e;

      /* Product: '<S135>/w' incorporates:
       *  Gain: '<S135>/(1//pi)'
       *  Integrator: '<S135>/vg_p1'
       *  Product: '<S135>/Lug//V1'
       *  Sqrt: '<S135>/sqrt'
       *  Sum: '<S135>/Sum'
       */
      rtb_Sign1 = (sqrt(0.3183098861837907 * rtb_sincos_o2_f_idx_0) *
                   autocodePlant_B->Product[1] - autocodePlant_X->vg_p1_CSTATE[1])
        / rtb_sincos_o2_f_idx_0;
      autocodePlant_B->w_c[1] = rtb_Sign1;

      /* Product: '<S135>/w ' incorporates:
       *  Gain: '<S135>/sqrt(3)'
       *  Integrator: '<S135>/vg_p1'
       *  Integrator: '<S135>/vgw_p2'
       *  Product: '<S135>/Lvg//V '
       *  Sum: '<S135>/Sum1'
       */
      autocodePlant_B->w_j[1] = (rtb_Sign1 * rtb_sincos_o2_f_idx_0 *
        1.7320508075688772 + (autocodePlant_X->vg_p1_CSTATE[1] -
        autocodePlant_X->vgw_p2_CSTATE[1])) / rtb_sincos_o2_f_idx_0;

      /* Product: '<S135>/w 1' incorporates:
       *  Integrator: '<S135>/vgw_p2'
       */
      autocodePlant_B->w1[0] = rtb_sigma_ugsigma_vg *
        autocodePlant_X->vgw_p2_CSTATE[0];
      autocodePlant_B->w1[1] = rtb_MediumHighAltitudeIntensity *
        autocodePlant_X->vgw_p2_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S121>/Hvgw(s)' */

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
      rtb_sincos_o2_f_idx_0 = rtb_LowAltitudeScaleLength / rtb_UnitConversion_e;
      rtb_LowAltitudeScaleLength = autocodePlant_ConstB.UnitConversion /
        rtb_UnitConversion_e;

      /* Product: '<S134>/w' incorporates:
       *  Gain: '<S134>/(2//pi)'
       *  Integrator: '<S134>/ug_p'
       *  Product: '<S134>/Lug//V1'
       *  Sqrt: '<S134>/sqrt'
       *  Sum: '<S134>/Sum'
       */
      autocodePlant_B->w_d[0] = (sqrt(0.6366197723675814 * rtb_sincos_o2_f_idx_0)
        * autocodePlant_B->Product[0] - autocodePlant_X->ug_p_CSTATE[0]) /
        rtb_sincos_o2_f_idx_0;
      autocodePlant_B->w_d[1] = (sqrt(0.6366197723675814 *
        rtb_LowAltitudeScaleLength) * autocodePlant_B->Product[0] -
        autocodePlant_X->ug_p_CSTATE[1]) / rtb_LowAltitudeScaleLength;

      /* Product: '<S134>/w1' incorporates:
       *  Integrator: '<S134>/ug_p'
       */
      autocodePlant_B->w1_c[0] = autocodePlant_X->ug_p_CSTATE[0] *
        rtb_sigma_ugsigma_vg;
      autocodePlant_B->w1_c[1] = autocodePlant_X->ug_p_CSTATE[1] *
        rtb_MediumHighAltitudeIntensity;
    }

    /* End of Outputs for SubSystem: '<S121>/Hugw(s)' */

    /* If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    rtPrevAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      if (rtb_UnitConversion <= 1000.0) {
        rtAction = 0;
      } else if (rtb_UnitConversion >= 2000.0) {
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
      /* Outputs for IfAction SubSystem: '<S126>/Low altitude  velocities' incorporates:
       *  ActionPort: '<S148>/Action Port'
       */
      /* SignalConversion generated from: '<S153>/Vector Concatenate' */
      rtb_Product_ab[2] = autocodePlant_B->LwgV1[0];

      /* Trigonometry: '<S154>/Trigonometric Function' */
      rtb_sigma_ugsigma_vg = sin(autocodePlant_B->UnitConversion);
      rtb_sincos_o2_f_idx_0 = cos(autocodePlant_B->UnitConversion);

      /* Sum: '<S154>/Sum' incorporates:
       *  Product: '<S154>/Product1'
       *  Product: '<S154>/Product2'
       */
      rtb_Product_ab[0] = autocodePlant_B->w1_c[0] * rtb_sincos_o2_f_idx_0 -
        rtb_sigma_ugsigma_vg * autocodePlant_B->w1[0];

      /* Sum: '<S154>/Sum1' incorporates:
       *  Product: '<S154>/Product1'
       *  Product: '<S154>/Product2'
       */
      rtb_Product_ab[1] = rtb_sigma_ugsigma_vg * autocodePlant_B->w1_c[0] +
        autocodePlant_B->w1[0] * rtb_sincos_o2_f_idx_0;

      /* Product: '<S153>/Product' incorporates:
       *  Concatenate: '<S153>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       *  Reshape: '<S153>/Reshape1'
       */
      rtb_Sum_b4 = 0.0;
      rtb_sigma_ugsigma_vg = 0.0;
      rtb_sincos_o2_f_idx_0 = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_UnaryMinus1_o = rtb_Product_ab[i];
        rtb_Sum_b4 += rtb_QuaternionstoDirectionCosin[3 * i] * rtb_UnaryMinus1_o;
        rtb_sigma_ugsigma_vg += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
          rtb_UnaryMinus1_o;
        rtb_sincos_o2_f_idx_0 += rtb_QuaternionstoDirectionCosin[3 * i + 2] *
          rtb_UnaryMinus1_o;
      }

      rtb_VectorConcatenate[2] = rtb_sincos_o2_f_idx_0;
      rtb_VectorConcatenate[1] = rtb_sigma_ugsigma_vg;
      rtb_VectorConcatenate[0] = rtb_Sum_b4;

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
      /* Trigonometry: '<S152>/Trigonometric Function' */
      rtb_sigma_ugsigma_vg = sin(autocodePlant_B->UnitConversion);
      rtb_sincos_o2_f_idx_0 = cos(autocodePlant_B->UnitConversion);

      /* Sum: '<S152>/Sum' incorporates:
       *  Product: '<S152>/Product1'
       *  Product: '<S152>/Product2'
       */
      rtb_VectorConcatenate[0] = autocodePlant_B->w1_c[0] *
        rtb_sincos_o2_f_idx_0 - rtb_sigma_ugsigma_vg * autocodePlant_B->w1[0];

      /* Sum: '<S152>/Sum1' incorporates:
       *  Product: '<S152>/Product1'
       *  Product: '<S152>/Product2'
       */
      rtb_VectorConcatenate[1] = rtb_sigma_ugsigma_vg * autocodePlant_B->w1_c[0]
        + autocodePlant_B->w1[0] * rtb_sincos_o2_f_idx_0;

      /* SignalConversion generated from: '<S151>/Vector Concatenate' */
      rtb_VectorConcatenate[2] = autocodePlant_B->LwgV1[0];

      /* Product: '<S151>/Product' incorporates:
       *  Concatenate: '<S151>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       */
      rtb_sigma_ugsigma_vg = 0.0;
      rtb_sincos_o2_f_idx_0 = 0.0;
      rtb_LowAltitudeScaleLength = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_UnaryMinus1_o = rtb_VectorConcatenate[i];
        rtb_sigma_ugsigma_vg += rtb_QuaternionstoDirectionCosin[3 * i] *
          rtb_UnaryMinus1_o;
        rtb_sincos_o2_f_idx_0 += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
          rtb_UnaryMinus1_o;
        rtb_LowAltitudeScaleLength += rtb_QuaternionstoDirectionCosin[3 * i + 2]
          * rtb_UnaryMinus1_o;
      }

      /* Sum: '<S147>/Sum3' incorporates:
       *  Constant: '<S147>/max_height_low'
       *  Product: '<S147>/Product1'
       *  Product: '<S151>/Product'
       *  Sum: '<S147>/Sum1'
       *  Sum: '<S147>/Sum2'
       */
      rtb_VectorConcatenate[0] = (autocodePlant_B->w1_c[1] -
        rtb_sigma_ugsigma_vg) * (rtb_UnitConversion - 1000.0) /
        autocodePlant_ConstB.Sum + rtb_sigma_ugsigma_vg;
      rtb_VectorConcatenate[1] = (autocodePlant_B->w1[1] - rtb_sincos_o2_f_idx_0)
        * (rtb_UnitConversion - 1000.0) / autocodePlant_ConstB.Sum +
        rtb_sincos_o2_f_idx_0;
      rtb_VectorConcatenate[2] = (autocodePlant_B->LwgV1[1] -
        rtb_LowAltitudeScaleLength) * (rtb_UnitConversion - 1000.0) /
        autocodePlant_ConstB.Sum + rtb_LowAltitudeScaleLength;

      /* End of Outputs for SubSystem: '<S126>/Interpolate  velocities' */
      break;
    }

    /* End of If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    if (tmp) {
      /* UnitConversion: '<S123>/Unit Conversion' incorporates:
       *  Constant: '<S117>/Wingspan'
       */
      /* Unit Conversion - from: m to: ft
         Expression: output = (3.28084*input) + (0) */
      autocodePlant_B->UnitConversion_e = 3.280839895013123 *
        vehicleParams.length_m;

      /* Outputs for Enabled SubSystem: '<S120>/Hpgw' incorporates:
       *  EnablePort: '<S131>/Enable'
       */
      if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo) &&
          !autocodePlant_DW->Hpgw_MODE) {
        (void) memset(&(autocodePlant_XDis->pgw_p_CSTATE), 0,
                      2*sizeof(boolean_T));

        /* InitializeConditions for Integrator: '<S131>/pgw_p' */
        autocodePlant_X->pgw_p_CSTATE[0] = 0.0;
        autocodePlant_X->pgw_p_CSTATE[1] = 0.0;
        autocodePlant_DW->Hpgw_MODE = true;
      }

      /* End of Outputs for SubSystem: '<S120>/Hpgw' */
    }

    /* Outputs for Enabled SubSystem: '<S120>/Hpgw' incorporates:
     *  EnablePort: '<S131>/Enable'
     */
    if (autocodePlant_DW->Hpgw_MODE) {
      if (rtmIsMajorTimeStep(autocodePlant_M) &&
          autocodePlant_M->Timing.TaskCounters.TID[1] == 0) {
        /* Product: '<S131>/w4' incorporates:
         *  Constant: '<S131>/Constant3'
         */
        autocodePlant_B->w4 = 0.7853981633974483 /
          autocodePlant_B->UnitConversion_e;

        /* Math: '<S131>/u^1//6' */
        if (autocodePlant_B->w4 < 0.0) {
          /* Math: '<S131>/u^1//6' incorporates:
           *  Constant: '<S131>/Constant2'
           */
          autocodePlant_B->u16 = -rt_powd_snf(-autocodePlant_B->w4,
            0.16666666666666666);
        } else {
          /* Math: '<S131>/u^1//6' incorporates:
           *  Constant: '<S131>/Constant2'
           */
          autocodePlant_B->u16 = rt_powd_snf(autocodePlant_B->w4,
            0.16666666666666666);
        }

        /* End of Math: '<S131>/u^1//6' */
      }

      /* Fcn: '<S131>/sqrt(0.8//V)' */
      rtb_UnaryMinus1_o = sqrt(0.8 / rtb_UnitConversion_e);

      /* Product: '<S131>/w3' */
      rtb_sigma_ugsigma_vg = rtb_UnitConversion_e * autocodePlant_B->w4;

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
      autocodePlant_B->w_p[0] = (rtb_UnaryMinus1_o / rt_powd_snf(rtb_Product3_eg,
        0.3333333333333333) * autocodePlant_B->u16 * autocodePlant_B->Product[3]
        - autocodePlant_X->pgw_p_CSTATE[0]) * rtb_sigma_ugsigma_vg;

      /* Math: '<S131>/L^1//3' */
      if (rtb_Lw_idx_1 < 0.0) {
        rtb_Product3_eg = -rt_powd_snf(-rtb_Lw_idx_1, 0.3333333333333333);
      } else {
        rtb_Product3_eg = rt_powd_snf(rtb_Lw_idx_1, 0.3333333333333333);
      }

      /* Product: '<S131>/w' incorporates:
       *  Fcn: '<S131>/sqrt(0.8//V)'
       *  Integrator: '<S131>/pgw_p'
       *  Product: '<S131>/Lug//V1'
       *  Product: '<S131>/w1'
       *  Product: '<S131>/w2'
       *  Sum: '<S131>/Sum'
       */
      autocodePlant_B->w_p[1] = (rtb_UnaryMinus1_o / rtb_Product3_eg *
        autocodePlant_B->u16 * autocodePlant_B->Product[3] -
        autocodePlant_X->pgw_p_CSTATE[1]) * rtb_sigma_ugsigma_vg;

      /* Product: '<S131>/sigma_w' incorporates:
       *  Integrator: '<S131>/pgw_p'
       */
      autocodePlant_B->sigma_w[0] = autocodePlant_B->sigma_wg *
        autocodePlant_X->pgw_p_CSTATE[0];
      autocodePlant_B->sigma_w[1] = rtb_MediumHighAltitudeIntensity *
        autocodePlant_X->pgw_p_CSTATE[1];
    }

    /* End of Outputs for SubSystem: '<S120>/Hpgw' */

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
      rtb_Product3_eg = 0.7853981633974483 * rtb_UnitConversion_e;

      /* Product: '<S132>/w' incorporates:
       *  Integrator: '<S132>/qgw_p'
       *  Product: '<S132>/wg//V'
       *  Sum: '<S132>/Sum'
       */
      rtb_MediumHighAltitudeIntensity = (autocodePlant_B->LwgV1[0] /
        rtb_UnitConversion_e - autocodePlant_X->qgw_p_CSTATE[0]) *
        (rtb_Product3_eg / autocodePlant_B->UnitConversion_e);
      autocodePlant_B->w_j5[0] = rtb_MediumHighAltitudeIntensity;

      /* UnaryMinus: '<S132>/Unary Minus' */
      autocodePlant_B->UnaryMinus[0] = -rtb_MediumHighAltitudeIntensity;

      /* Product: '<S132>/w' incorporates:
       *  Integrator: '<S132>/qgw_p'
       *  Product: '<S132>/wg//V'
       *  Sum: '<S132>/Sum'
       */
      rtb_MediumHighAltitudeIntensity = (autocodePlant_B->LwgV1[1] /
        rtb_UnitConversion_e - autocodePlant_X->qgw_p_CSTATE[1]) *
        (rtb_Product3_eg / autocodePlant_B->UnitConversion_e);
      autocodePlant_B->w_j5[1] = rtb_MediumHighAltitudeIntensity;

      /* UnaryMinus: '<S132>/Unary Minus' */
      autocodePlant_B->UnaryMinus[1] = -rtb_MediumHighAltitudeIntensity;
    }

    /* End of Outputs for SubSystem: '<S120>/Hqgw' */

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
      rtb_Product3_eg = 1.0471975511965976 * rtb_UnitConversion_e;

      /* Product: '<S133>/w' incorporates:
       *  Integrator: '<S133>/rgw_p'
       *  Product: '<S133>/vg//V'
       *  Sum: '<S133>/Sum'
       */
      autocodePlant_B->w_g[0] = (autocodePlant_B->w1[0] / rtb_UnitConversion_e -
        autocodePlant_X->rgw_p_CSTATE[0]) * (rtb_Product3_eg /
        autocodePlant_B->UnitConversion_e);
      autocodePlant_B->w_g[1] = (autocodePlant_B->w1[1] / rtb_UnitConversion_e -
        autocodePlant_X->rgw_p_CSTATE[1]) * (rtb_Product3_eg /
        autocodePlant_B->UnitConversion_e);
    }

    /* End of Outputs for SubSystem: '<S120>/Hrgw' */

    /* If: '<S125>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    rtPrevAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_m;
    if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
      if (rtb_UnitConversion <= 1000.0) {
        rtAction = 0;
      } else if (rtb_UnitConversion >= 2000.0) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_m = rtAction;
    } else {
      rtAction = autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_m;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&autocodePlant_M->solverInfo,
        true);
    }

    switch (rtAction) {
     case 0:
      /* Outputs for IfAction SubSystem: '<S125>/Low altitude  rates' incorporates:
       *  ActionPort: '<S140>/Action Port'
       */
      /* SignalConversion generated from: '<S145>/Vector Concatenate' */
      rtb_Product_lj[2] = autocodePlant_B->w_g[0];

      /* Trigonometry: '<S146>/Trigonometric Function1' */
      rtb_Product3_eg = sin(autocodePlant_B->UnitConversion);
      rtb_UnitConversion = cos(autocodePlant_B->UnitConversion);

      /* Sum: '<S146>/Sum' incorporates:
       *  Product: '<S146>/Product1'
       *  Product: '<S146>/Product2'
       */
      rtb_Product_lj[0] = autocodePlant_B->sigma_w[0] * rtb_UnitConversion -
        rtb_Product3_eg * autocodePlant_B->UnaryMinus[0];

      /* Sum: '<S146>/Sum1' incorporates:
       *  Product: '<S146>/Product1'
       *  Product: '<S146>/Product2'
       */
      rtb_Product_lj[1] = rtb_Product3_eg * autocodePlant_B->sigma_w[0] +
        autocodePlant_B->UnaryMinus[0] * rtb_UnitConversion;

      /* Product: '<S145>/Product' incorporates:
       *  Concatenate: '<S145>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       *  Reshape: '<S145>/Reshape1'
       */
      rtb_sigma_ugsigma_vg = 0.0;
      rtb_sincos_o2_f_idx_0 = 0.0;
      rtb_LowAltitudeScaleLength = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_UnaryMinus1_o = rtb_Product_lj[i];
        rtb_sigma_ugsigma_vg += rtb_QuaternionstoDirectionCosin[3 * i] *
          rtb_UnaryMinus1_o;
        rtb_sincos_o2_f_idx_0 += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
          rtb_UnaryMinus1_o;
        rtb_LowAltitudeScaleLength += rtb_QuaternionstoDirectionCosin[3 * i + 2]
          * rtb_UnaryMinus1_o;
      }

      rtb_Product_ab[2] = rtb_LowAltitudeScaleLength;
      rtb_Product_ab[1] = rtb_sincos_o2_f_idx_0;
      rtb_Product_ab[0] = rtb_sigma_ugsigma_vg;

      /* End of Product: '<S145>/Product' */
      /* End of Outputs for SubSystem: '<S125>/Low altitude  rates' */
      break;

     case 1:
      /* Outputs for IfAction SubSystem: '<S125>/Medium//High  altitude rates' incorporates:
       *  ActionPort: '<S141>/Action Port'
       */
      /* Gain: '<S141>/Gain' */
      rtb_Product_ab[0] = autocodePlant_B->sigma_w[1];
      rtb_Product_ab[1] = autocodePlant_B->UnaryMinus[1];
      rtb_Product_ab[2] = autocodePlant_B->w_g[1];

      /* End of Outputs for SubSystem: '<S125>/Medium//High  altitude rates' */
      break;

     default:
      /* Outputs for IfAction SubSystem: '<S125>/Interpolate  rates' incorporates:
       *  ActionPort: '<S139>/Action Port'
       */
      /* Trigonometry: '<S144>/Trigonometric Function' */
      rtb_Product3_eg = sin(autocodePlant_B->UnitConversion);
      rtb_UnitConversion_e = cos(autocodePlant_B->UnitConversion);

      /* Sum: '<S144>/Sum' incorporates:
       *  Product: '<S144>/Product1'
       *  Product: '<S144>/Product2'
       */
      rtb_Product_ab[0] = autocodePlant_B->sigma_w[0] * rtb_UnitConversion_e -
        rtb_Product3_eg * autocodePlant_B->UnaryMinus[0];

      /* Sum: '<S144>/Sum1' incorporates:
       *  Product: '<S144>/Product1'
       *  Product: '<S144>/Product2'
       */
      rtb_Product_ab[1] = rtb_Product3_eg * autocodePlant_B->sigma_w[0] +
        autocodePlant_B->UnaryMinus[0] * rtb_UnitConversion_e;

      /* SignalConversion generated from: '<S143>/Vector Concatenate' */
      rtb_Product_ab[2] = autocodePlant_B->w_g[0];

      /* Product: '<S143>/Product' incorporates:
       *  Concatenate: '<S143>/Vector Concatenate'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       */
      rtb_sincos_o2_f_idx_0 = 0.0;
      rtb_MediumHighAltitudeIntensity = 0.0;
      rtb_LowAltitudeScaleLength = 0.0;
      for (i = 0; i < 3; i++) {
        rtb_UnaryMinus1_o = rtb_Product_ab[i];
        rtb_sincos_o2_f_idx_0 += rtb_QuaternionstoDirectionCosin[3 * i] *
          rtb_UnaryMinus1_o;
        rtb_MediumHighAltitudeIntensity += rtb_QuaternionstoDirectionCosin[3 * i
          + 1] * rtb_UnaryMinus1_o;
        rtb_LowAltitudeScaleLength += rtb_QuaternionstoDirectionCosin[3 * i + 2]
          * rtb_UnaryMinus1_o;
      }

      /* Sum: '<S139>/Sum3' incorporates:
       *  Constant: '<S139>/max_height_low'
       *  Product: '<S139>/Product1'
       *  Product: '<S143>/Product'
       *  Sum: '<S139>/Sum1'
       *  Sum: '<S139>/Sum2'
       */
      rtb_Product_ab[0] = (autocodePlant_B->sigma_w[1] - rtb_sincos_o2_f_idx_0) *
        (rtb_UnitConversion - 1000.0) / autocodePlant_ConstB.Sum_i +
        rtb_sincos_o2_f_idx_0;
      rtb_Product_ab[1] = (autocodePlant_B->UnaryMinus[1] -
                           rtb_MediumHighAltitudeIntensity) *
        (rtb_UnitConversion - 1000.0) / autocodePlant_ConstB.Sum_i +
        rtb_MediumHighAltitudeIntensity;
      rtb_Product_ab[2] = (autocodePlant_B->w_g[1] - rtb_LowAltitudeScaleLength)
        * (rtb_UnitConversion - 1000.0) / autocodePlant_ConstB.Sum_i +
        rtb_LowAltitudeScaleLength;

      /* End of Outputs for SubSystem: '<S125>/Interpolate  rates' */
      break;
    }

    /* End of If: '<S125>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */

    /* Product: '<S161>/Matrix Multiply' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    rtb_sincos_o2_f_idx_0 = 0.0;
    rtb_MediumHighAltitudeIntensity = 0.0;
    rtb_LowAltitudeScaleLength = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_UnaryMinus1_o = rtb_wBdy_rps[i];
      rtb_sincos_o2_f_idx_0 += vehicleParams.inertia_kgm2[3 * i] *
        rtb_UnaryMinus1_o;
      rtb_MediumHighAltitudeIntensity += vehicleParams.inertia_kgm2[3 * i + 1] *
        rtb_UnaryMinus1_o;
      rtb_LowAltitudeScaleLength += vehicleParams.inertia_kgm2[3 * i + 2] *
        rtb_UnaryMinus1_o;
    }

    /* Product: '<S168>/Element Product' incorporates:
     *  Product: '<S161>/Matrix Multiply'
     */
    rtb_ElementProduct[0] = rtb_wBdy_rps[1] * rtb_LowAltitudeScaleLength;
    rtb_ElementProduct[1] = rtb_sincos_o2_f_idx_0 * rtb_wBdy_rps[2];
    rtb_ElementProduct[2] = rtb_wBdy_rps[0] * rtb_MediumHighAltitudeIntensity;
    rtb_ElementProduct[3] = rtb_MediumHighAltitudeIntensity * rtb_wBdy_rps[2];
    rtb_ElementProduct[4] = rtb_wBdy_rps[0] * rtb_LowAltitudeScaleLength;
    rtb_ElementProduct[5] = rtb_sincos_o2_f_idx_0 * rtb_wBdy_rps[1];
    if (tmp) {
      /* Delay: '<S174>/Delay' */
      for (i = 0; i < 6; i++) {
        rtb_Delay[i] = autocodePlant_DW->Delay_DSTATE[i];
      }

      /* End of Delay: '<S174>/Delay' */
    }

    /* RateTransition: '<S174>/Rate Transition1' */
    tmp_0 = (rtmIsMajorTimeStep(autocodePlant_M) &&
             autocodePlant_M->Timing.TaskCounters.TID[3] == 0);
    if (tmp_0) {
      /* RelationalOperator: '<S174>/Relational Operator' incorporates:
       *  Constant: '<S174>/Constant'
       *  UniformRandomNumber: '<S174>/Uniform Random Number'
       */
      autocodePlant_B->RelationalOperator =
        (autocodePlant_DW->UniformRandomNumber_NextOutput >=
         sensorParams.gpsOutageProbability_pct);
    }

    if (tmp) {
      /* Switch: '<S174>/Switch' incorporates:
       *  UnitDelay: '<S174>/Unit Delay'
       */
      if (autocodePlant_B->RelationalOperator) {
        for (i = 0; i < 6; i++) {
          autocodePlant_DW->UnitDelay_DSTATE[i] = rtb_Delay[i];
        }
      }

      /* End of Switch: '<S174>/Switch' */

      /* Sum: '<S9>/Subtract1' incorporates:
       *  Constant: '<S3>/Constant4'
       *  Constant: '<S9>/Constant4'
       *  Constant: '<S9>/Constant5'
       *  Product: '<S9>/Product6'
       */
      autocodePlant_B->Subtract1[0] = vehicleParams.cg_m - aeroParams.finCP1_m[0];
      autocodePlant_B->Subtract1[1] = vehicleParams.cg_m * 0.0 -
        aeroParams.finCP1_m[1];
      autocodePlant_B->Subtract1[2] = vehicleParams.cg_m * 0.0 -
        aeroParams.finCP1_m[2];

      /* Sum: '<S10>/Subtract1' incorporates:
       *  Constant: '<S10>/Constant4'
       *  Constant: '<S10>/Constant5'
       *  Constant: '<S3>/Constant3'
       *  Product: '<S10>/Product6'
       */
      autocodePlant_B->Subtract1_m[0] = vehicleParams.cg_m -
        aeroParams.finCP2_m[0];
      autocodePlant_B->Subtract1_m[1] = vehicleParams.cg_m * 0.0 -
        aeroParams.finCP2_m[1];
      autocodePlant_B->Subtract1_m[2] = vehicleParams.cg_m * 0.0 -
        aeroParams.finCP2_m[2];
    }

    /* Sum: '<S4>/Sum1' incorporates:
     *  Constant: '<S101>/Constant3'
     *  DataTypeConversion: '<S117>/Cast'
     *  Product: '<S101>/Product1'
     */
    rtb_Product_ab[0] = rtb_wBdy_rps[0] - (real_T)
      (windParams.useWindTurbulence_b ? rtb_Product_ab[0] != 0.0 : 0);
    rtb_Product_ab[1] = rtb_wBdy_rps[1] - (real_T)
      (windParams.useWindTurbulence_b ? rtb_Product_ab[1] != 0.0 : 0);
    rtb_Product_ab[2] = rtb_wBdy_rps[2] - (real_T)
      (windParams.useWindTurbulence_b ? rtb_Product_ab[2] != 0.0 : 0);

    /* Product: '<S41>/Element Product' */
    rtb_ElementProduct_k[0] = rtb_Product_ab[1] * autocodePlant_B->Subtract1_m[2];
    rtb_ElementProduct_k[1] = autocodePlant_B->Subtract1_m[0] * rtb_Product_ab[2];
    rtb_ElementProduct_k[2] = rtb_Product_ab[0] * autocodePlant_B->Subtract1_m[1];
    rtb_ElementProduct_k[3] = autocodePlant_B->Subtract1_m[1] * rtb_Product_ab[2];
    rtb_ElementProduct_k[4] = rtb_Product_ab[0] * autocodePlant_B->Subtract1_m[2];
    rtb_ElementProduct_k[5] = autocodePlant_B->Subtract1_m[0] * rtb_Product_ab[1];

    /* UnitConversion: '<S159>/Unit Conversion' incorporates:
     *  UnaryMinus: '<S101>/Unary Minus'
     */
    /* Unit Conversion - from: m to: ft
       Expression: output = (3.28084*input) + (0) */
    rtb_UnitConversion = 3.280839895013123 * -rtb_posNed_m_idx_2;

    /* Saturate: '<S118>/3ft-->inf' */
    if (rtb_UnitConversion <= 3.0) {
      rtb_UnitConversion = 3.0;
    }

    /* Product: '<S118>/Product' incorporates:
     *  Gain: '<S118>/h//z0'
     *  Math: '<S118>/ln(h//z0)'
     *  Saturate: '<S118>/3ft-->inf'
     *
     * About '<S118>/ln(h//z0)':
     *  Operator: log
     */
    rtb_Product3_eg = log(6.666666666666667 * rtb_UnitConversion) /
      autocodePlant_ConstB.lnref_heightz0;
    if (tmp) {
      /* UnitConversion: '<S158>/Unit Conversion' incorporates:
       *  Constant: '<S118>/Wind Direction'
       */
      /* Unit Conversion - from: deg to: rad
         Expression: output = (0.0174533*input) + (0) */
      rtb_UnitConversion = 0.017453292519943295 * windParams.lowAltWindDir_deg;

      /* Gain: '<S118>/Wind speed at reference height' incorporates:
       *  Constant: '<S118>/Wdeg1'
       *  Trigonometry: '<S118>/SinCos'
       */
      autocodePlant_B->Windspeedatreferenceheight[0] =
        -windParams.lowAltWindSpeed_mps * cos(rtb_UnitConversion);
      autocodePlant_B->Windspeedatreferenceheight[1] =
        -windParams.lowAltWindSpeed_mps * sin(rtb_UnitConversion);
      autocodePlant_B->Windspeedatreferenceheight[2] =
        -windParams.lowAltWindSpeed_mps * 0.0;
    }

    /* Product: '<S118>/Transform from Inertial to Body axes' incorporates:
     *  Product: '<S118>/Product1'
     *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
     */
    /* Unit Conversion - from: ft/s to: m/s
       Expression: output = (0.3048*input) + (0) */
    rtb_UnitConversion = 0.0;
    rtb_UnitConversion_e = 0.0;
    rtb_MediumHighAltitudeIntensity = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_UnaryMinus1_o = rtb_Product3_eg *
        autocodePlant_B->Windspeedatreferenceheight[i];
      rtb_UnitConversion += rtb_QuaternionstoDirectionCosin[3 * i] *
        rtb_UnaryMinus1_o;
      rtb_UnitConversion_e += rtb_QuaternionstoDirectionCosin[3 * i + 1] *
        rtb_UnaryMinus1_o;
      rtb_MediumHighAltitudeIntensity += rtb_QuaternionstoDirectionCosin[3 * i +
        2] * rtb_UnaryMinus1_o;
    }

    Gdependent[2] = rtb_MediumHighAltitudeIntensity;
    Gdependent[1] = rtb_UnitConversion_e;
    Gdependent[0] = rtb_UnitConversion;

    /* Sum: '<S4>/Sum' incorporates:
     *  Constant: '<S4>/Constant'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    rtb_Product3_eg = envParams.groundAlt_m - rtb_posNed_m_idx_2;

    /* Saturate: '<S106>/Limit  altitude  to troposhere' */
    if (rtb_Product3_eg > 11000.0) {
      rtb_UnaryMinus1_o = 11000.0;
    } else if (rtb_Product3_eg < 0.0) {
      rtb_UnaryMinus1_o = 0.0;
    } else {
      rtb_UnaryMinus1_o = rtb_Product3_eg;
    }

    /* Sum: '<S106>/Sum1' incorporates:
     *  Constant: '<S106>/Sea Level  Temperature'
     *  Gain: '<S106>/Lapse Rate'
     *  Saturate: '<S106>/Limit  altitude  to troposhere'
     */
    rtb_UnitConversion = 288.15 - 0.0065 * rtb_UnaryMinus1_o;

    /* Sqrt: '<S106>/a' incorporates:
     *  Gain: '<S106>/gamma*R'
     */
    rtb_UnitConversion_e = sqrt(401.87433999999996 * rtb_UnitConversion);

    /* DotProduct: '<S10>/Dot Product4' */
    rtb_MediumHighAltitudeIntensity = 0.0;

    /* Product: '<S101>/Matrix Multiply' incorporates:
     *  Constant: '<S101>/Constant'
     */
    rtb_sigma_ugsigma_vg = windParams.constantNed_mps[1];
    rtb_sincos_o2_f_idx_0 = windParams.constantNed_mps[0];
    rtb_LowAltitudeScaleLength = windParams.constantNed_mps[2];
    for (i = 0; i < 3; i++) {
      /* Sum: '<S101>/Sum' incorporates:
       *  Constant: '<S101>/Constant'
       *  Constant: '<S101>/Constant2'
       *  Constant: '<S101>/Constant3'
       *  Product: '<S101>/Matrix Multiply'
       *  Product: '<S101>/Product'
       *  Product: '<S101>/Product2'
       *  Product: '<S118>/Transform from Inertial to Body axes'
       *  Quat2Dcm: '<S101>/Quaternions to  Direction Cosine Matrix'
       *  UnitConversion: '<S117>/Unit Conversion'
       */
      rtb_Sign1 = (((rtb_QuaternionstoDirectionCosin[i + 3] *
                     rtb_sigma_ugsigma_vg + rtb_QuaternionstoDirectionCosin[i] *
                     rtb_sincos_o2_f_idx_0) + rtb_QuaternionstoDirectionCosin[i
                    + 6] * rtb_LowAltitudeScaleLength) + Gdependent[i] * (real_T)
                   windParams.useWindShear_b) + 0.3048 * rtb_VectorConcatenate[i]
        * (real_T)windParams.useWindTurbulence_b;
      rtb_Sum_e[i] = rtb_Sign1;

      /* Sum: '<S4>/Sum2' */
      rtb_Sum_b4 = rtb_velBdy_mps[i] - rtb_Sign1;
      rtb_VectorConcatenate[i] = rtb_Sum_b4;

      /* Sum: '<S10>/Sum' incorporates:
       *  Sum: '<S41>/Sum'
       */
      rtb_Sign1 = (rtb_ElementProduct_k[i] - rtb_ElementProduct_k[i + 3]) +
        rtb_Sum_b4;
      rtb_Sum_k[i] = rtb_Sign1;

      /* DotProduct: '<S10>/Dot Product4' */
      rtb_MediumHighAltitudeIntensity += rtb_Sign1 * rtb_Sign1;
    }

    /* Switch: '<S38>/Switch' incorporates:
     *  Constant: '<S38>/Constant4'
     *  Constant: '<S38>/Constant5'
     */
    if (rtb_UnitConversion_e >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* MinMax: '<S38>/Max' incorporates:
     *  Abs: '<S38>/Abs'
     *  Constant: '<S38>/Constant'
     *  MinMax: '<S14>/Max'
     *  MinMax: '<S18>/Max'
     *  MinMax: '<S58>/Max'
     *  MinMax: '<S78>/Max'
     */
    rtb_Gain_n = fmax(1.0E-6, rtb_UnitConversion_e);

    /* Product: '<S10>/Divide1' incorporates:
     *  MinMax: '<S38>/Max'
     *  Product: '<S38>/Product'
     *  Sqrt: '<S10>/Sqrt1'
     *  Switch: '<S38>/Switch'
     */
    rtb_MediumHighAltitudeIntensity = sqrt(rtb_MediumHighAltitudeIntensity) /
      ((real_T)i * rtb_Gain_n);
    if (tmp) {
      /* Angle2Quat: '<S10>/Rotation Angles to Quaternions' incorporates:
       *  Constant: '<S10>/liftDirection_na1'
       */
      rtb_UnitDelay2_idx_3 = cos(aeroParams.finAngles2_rad[2] / 2.0);
      rtb_UnitDelay2_idx_1 = cos(aeroParams.finAngles2_rad[1] / 2.0);
      rtb_UnaryMinus_n = cos(aeroParams.finAngles2_rad[0] / 2.0);
      rtb_Sum1_nc_idx_0 = sin(aeroParams.finAngles2_rad[2] / 2.0);
      rtb_FlatEarthtoLLA_o1_idx_0 = sin(aeroParams.finAngles2_rad[1] / 2.0);
      rtb_Switch_d_idx_1 = sin(aeroParams.finAngles2_rad[0] / 2.0);
      rtb_DiscreteTransferFcn2 = rtb_UnaryMinus_n * rtb_UnitDelay2_idx_1;
      rtb_Switch_d_idx_2 = rtb_Switch_d_idx_1 * rtb_FlatEarthtoLLA_o1_idx_0;
      rtb_UnitDelay2_idx_0 = rtb_DiscreteTransferFcn2 * rtb_UnitDelay2_idx_3 -
        rtb_Switch_d_idx_2 * rtb_Sum1_nc_idx_0;
      rtb_UnaryMinus_n *= rtb_FlatEarthtoLLA_o1_idx_0;
      rtb_Switch_d_idx_1 *= rtb_UnitDelay2_idx_1;
      rtb_UnitDelay2_idx_1 = rtb_UnaryMinus_n * rtb_Sum1_nc_idx_0 +
        rtb_Switch_d_idx_1 * rtb_UnitDelay2_idx_3;
      rtb_Switch_d_idx_1 = rtb_UnaryMinus_n * rtb_UnitDelay2_idx_3 -
        rtb_Switch_d_idx_1 * rtb_Sum1_nc_idx_0;
      rtb_UnitDelay2_idx_3 = rtb_DiscreteTransferFcn2 * rtb_Sum1_nc_idx_0 +
        rtb_Switch_d_idx_2 * rtb_UnitDelay2_idx_3;

      /* Sqrt: '<S56>/sqrt' incorporates:
       *  Product: '<S57>/Product'
       *  Product: '<S57>/Product1'
       *  Product: '<S57>/Product2'
       *  Product: '<S57>/Product3'
       *  Sqrt: '<S50>/sqrt'
       *  Sum: '<S57>/Sum'
       */
      rtb_sigma_ugsigma_vg = sqrt(((rtb_UnitDelay2_idx_0 * rtb_UnitDelay2_idx_0
        + rtb_UnitDelay2_idx_1 * rtb_UnitDelay2_idx_1) + rtb_Switch_d_idx_1 *
        rtb_Switch_d_idx_1) + rtb_UnitDelay2_idx_3 * rtb_UnitDelay2_idx_3);

      /* Product: '<S52>/Product2' incorporates:
       *  Sqrt: '<S56>/sqrt'
       */
      rtb_Product4_a = rtb_Switch_d_idx_1 / rtb_sigma_ugsigma_vg;

      /* Product: '<S52>/Product3' incorporates:
       *  Sqrt: '<S56>/sqrt'
       */
      rtb_UnitDelay2_idx_3 /= rtb_sigma_ugsigma_vg;

      /* Product: '<S52>/Product1' incorporates:
       *  Product: '<S46>/Product1'
       *  Sqrt: '<S56>/sqrt'
       */
      rtb_UnaryMinus1 = rtb_UnitDelay2_idx_1 / rtb_sigma_ugsigma_vg;

      /* Product: '<S52>/Product' incorporates:
       *  Sqrt: '<S56>/sqrt'
       */
      rtb_Product8_ne = rtb_UnitDelay2_idx_0 / rtb_sigma_ugsigma_vg;

      /* Product: '<S53>/Product7' incorporates:
       *  Product: '<S54>/Product7'
       */
      rtb_Sum_a_idx_2 = rtb_UnitDelay2_idx_3 * rtb_UnitDelay2_idx_3;

      /* Product: '<S53>/Product' incorporates:
       *  Product: '<S52>/Product1'
       *  Product: '<S54>/Product'
       */
      rtb_UnaryMinus_o3 = rtb_UnaryMinus1 * rtb_Product4_a;

      /* Product: '<S53>/Product1' incorporates:
       *  Product: '<S54>/Product1'
       */
      rtb_UnaryMinus1_c = rtb_Product8_ne * rtb_UnitDelay2_idx_3;

      /* Product: '<S53>/Product3' incorporates:
       *  Product: '<S52>/Product1'
       *  Product: '<S55>/Product'
       */
      rtb_Product2_l3 = rtb_UnaryMinus1 * rtb_UnitDelay2_idx_3;

      /* Product: '<S53>/Product2' incorporates:
       *  Product: '<S55>/Product1'
       */
      rtb_TT0gLR = rtb_Product8_ne * rtb_Product4_a;

      /* Product: '<S53>/Product6' incorporates:
       *  Product: '<S55>/Product7'
       */
      rtb_Sign1 = rtb_Product4_a * rtb_Product4_a;

      /* Gain: '<S53>/Gain2' incorporates:
       *  Constant: '<S53>/Constant'
       *  Gain: '<S47>/Gain2'
       *  Product: '<S53>/Product6'
       *  Product: '<S53>/Product7'
       *  Sum: '<S53>/Sum3'
       */
      rtb_sigma_ugsigma_vg = ((0.5 - rtb_Sign1) - rtb_Sum_a_idx_2) * 2.0;

      /* Product: '<S53>/Product4' incorporates:
       *  Constant: '<S10>/axialDirection_na'
       *  Gain: '<S53>/Gain'
       *  Product: '<S47>/Product4'
       *  Product: '<S53>/Product'
       *  Product: '<S53>/Product1'
       *  Sum: '<S53>/Sum1'
       */
      rtb_sincos_o2_f_idx_0 = (rtb_UnaryMinus_o3 + rtb_UnaryMinus1_c) * 2.0 *
        0.0;

      /* Gain: '<S53>/Gain1' incorporates:
       *  Gain: '<S47>/Gain1'
       *  Product: '<S53>/Product2'
       *  Product: '<S53>/Product3'
       *  Sum: '<S53>/Sum2'
       */
      rtb_LowAltitudeScaleLength = (rtb_Product2_l3 - rtb_TT0gLR) * 2.0;

      /* Sum: '<S53>/Sum' incorporates:
       *  Constant: '<S10>/axialDirection_na'
       *  Gain: '<S53>/Gain1'
       *  Gain: '<S53>/Gain2'
       *  Product: '<S53>/Product4'
       *  Product: '<S53>/Product5'
       */
      autocodePlant_B->Sum = (rtb_sigma_ugsigma_vg + rtb_sincos_o2_f_idx_0) +
        rtb_LowAltitudeScaleLength * 0.0;

      /* Product: '<S54>/Product3' incorporates:
       *  Product: '<S55>/Product3'
       */
      rtb_Sum1_hwh_idx_1 = rtb_Product4_a * rtb_UnitDelay2_idx_3;

      /* Product: '<S54>/Product2' incorporates:
       *  Product: '<S52>/Product1'
       *  Product: '<S55>/Product2'
       */
      rtb_Product8_ne *= rtb_UnaryMinus1;

      /* Sum: '<S54>/Sum3' incorporates:
       *  Constant: '<S54>/Constant'
       *  Product: '<S52>/Product1'
       *  Product: '<S54>/Product6'
       *  Sum: '<S55>/Sum3'
       */
      rtb_UnaryMinus1 = 0.5 - rtb_UnaryMinus1 * rtb_UnaryMinus1;

      /* Product: '<S54>/Product8' incorporates:
       *  Constant: '<S10>/axialDirection_na'
       *  Gain: '<S54>/Gain2'
       *  Product: '<S48>/Product8'
       *  Sum: '<S54>/Sum3'
       */
      rtb_Product4_a = (rtb_UnaryMinus1 - rtb_Sum_a_idx_2) * 2.0 * 0.0;

      /* Gain: '<S54>/Gain' incorporates:
       *  Gain: '<S48>/Gain'
       *  Sum: '<S54>/Sum1'
       */
      rtb_UnaryMinus_o3 = (rtb_UnaryMinus_o3 - rtb_UnaryMinus1_c) * 2.0;

      /* Gain: '<S54>/Gain1' incorporates:
       *  Gain: '<S48>/Gain1'
       *  Product: '<S54>/Product2'
       *  Product: '<S54>/Product3'
       *  Sum: '<S54>/Sum2'
       */
      rtb_UnaryMinus1_c = (rtb_Product8_ne + rtb_Sum1_hwh_idx_1) * 2.0;

      /* Sum: '<S54>/Sum' incorporates:
       *  Constant: '<S10>/axialDirection_na'
       *  Gain: '<S54>/Gain'
       *  Gain: '<S54>/Gain1'
       *  Product: '<S54>/Product5'
       *  Product: '<S54>/Product8'
       */
      autocodePlant_B->Sum_c = (rtb_Product4_a + rtb_UnaryMinus_o3) +
        rtb_UnaryMinus1_c * 0.0;

      /* Gain: '<S55>/Gain' incorporates:
       *  Gain: '<S49>/Gain'
       *  Sum: '<S55>/Sum1'
       */
      rtb_Product2_l3 = (rtb_Product2_l3 + rtb_TT0gLR) * 2.0;

      /* Product: '<S55>/Product5' incorporates:
       *  Constant: '<S10>/axialDirection_na'
       *  Gain: '<S55>/Gain1'
       *  Product: '<S49>/Product5'
       *  Sum: '<S55>/Sum2'
       */
      rtb_TT0gLR = (rtb_Sum1_hwh_idx_1 - rtb_Product8_ne) * 2.0 * 0.0;

      /* Gain: '<S55>/Gain2' incorporates:
       *  Gain: '<S49>/Gain2'
       *  Sum: '<S55>/Sum3'
       */
      rtb_Sign1 = (rtb_UnaryMinus1 - rtb_Sign1) * 2.0;

      /* Sum: '<S55>/Sum' incorporates:
       *  Constant: '<S10>/axialDirection_na'
       *  Gain: '<S55>/Gain'
       *  Gain: '<S55>/Gain2'
       *  Product: '<S55>/Product5'
       *  Product: '<S55>/Product8'
       */
      autocodePlant_B->Sum_b = (rtb_TT0gLR + rtb_Product2_l3) + rtb_Sign1 * 0.0;

      /* Sum: '<S47>/Sum' incorporates:
       *  Constant: '<S10>/normalDirection_na'
       *  Product: '<S47>/Product8'
       */
      autocodePlant_B->Sum_m = (rtb_sigma_ugsigma_vg * 0.0 +
        rtb_sincos_o2_f_idx_0) + rtb_LowAltitudeScaleLength;

      /* Sum: '<S48>/Sum' incorporates:
       *  Constant: '<S10>/normalDirection_na'
       *  Product: '<S48>/Product4'
       */
      autocodePlant_B->Sum_b1 = (rtb_UnaryMinus_o3 * 0.0 + rtb_Product4_a) +
        rtb_UnaryMinus1_c;

      /* Sum: '<S49>/Sum' incorporates:
       *  Constant: '<S10>/normalDirection_na'
       *  Product: '<S49>/Product4'
       */
      autocodePlant_B->Sum_k = (rtb_Product2_l3 * 0.0 + rtb_TT0gLR) + rtb_Sign1;

      /* Sum: '<S10>/Sum2' */
      autocodePlant_B->Sum2[0] = autocodePlant_B->Sum_m + autocodePlant_B->Sum;
      autocodePlant_B->Sum2[1] = autocodePlant_B->Sum_b1 +
        autocodePlant_B->Sum_c;
      autocodePlant_B->Sum2[2] = autocodePlant_B->Sum_k + autocodePlant_B->Sum_b;
    }

    /* Product: '<S10>/Product8' */
    rtb_sincos_o2_f_idx_0 = rtb_Sum_k[0] * autocodePlant_B->Sum2[0];
    rtb_sigma_ugsigma_vg = rtb_Sum_k[1] * autocodePlant_B->Sum2[1];
    rtb_LowAltitudeScaleLength = rtb_Sum_k[2] * autocodePlant_B->Sum2[2];

    /* DotProduct: '<S10>/Dot Product1' */
    rtb_Sign1 = (rtb_sincos_o2_f_idx_0 * rtb_sincos_o2_f_idx_0 +
                 rtb_sigma_ugsigma_vg * rtb_sigma_ugsigma_vg) +
      rtb_LowAltitudeScaleLength * rtb_LowAltitudeScaleLength;

    /* Switch: '<S40>/Switch' incorporates:
     *  Constant: '<S40>/Constant4'
     *  Constant: '<S40>/Constant5'
     *  DotProduct: '<S10>/Dot Product1'
     */
    if (rtb_Sign1 >= 0.0) {
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
    rtb_UnaryMinus_n = ((autocodePlant_B->Sum * rtb_sincos_o2_f_idx_0 +
                         autocodePlant_B->Sum_c * rtb_sigma_ugsigma_vg) +
                        autocodePlant_B->Sum_b * rtb_LowAltitudeScaleLength) /
      sqrt((real_T)i * fmax(1.0E-6, rtb_Sign1));

    /* Saturate: '<S10>/Saturation' */
    if (rtb_UnaryMinus_n > 1.0) {
      rtb_UnaryMinus_n = 1.0;
    } else if (rtb_UnaryMinus_n < -1.0) {
      rtb_UnaryMinus_n = -1.0;
    }

    /* Gain: '<S45>/Gain' incorporates:
     *  Saturate: '<S10>/Saturation'
     *  Trigonometry: '<S10>/Acos'
     */
    rtb_sigma_ugsigma_vg = 57.29577951308232 * acos(rtb_UnaryMinus_n);
    if (tmp) {
      /* Backlash: '<S7>/Backlash' incorporates:
       *  UnitDelay: '<S7>/Unit Delay'
       */
      if (autocodePlant_DW->UnitDelay_DSTATE_h[0] < autocodePlant_DW->PrevY[0] -
          0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[0] = autocodePlant_DW->UnitDelay_DSTATE_h[0] +
          0.5;
      } else if (autocodePlant_DW->UnitDelay_DSTATE_h[0] <=
                 autocodePlant_DW->PrevY[0] + 0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[0] = autocodePlant_DW->PrevY[0];
      } else {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[0] = autocodePlant_DW->UnitDelay_DSTATE_h[0] -
          0.5;
      }

      if (autocodePlant_DW->UnitDelay_DSTATE_h[1] < autocodePlant_DW->PrevY[1] -
          0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[1] = autocodePlant_DW->UnitDelay_DSTATE_h[1] +
          0.5;
      } else if (autocodePlant_DW->UnitDelay_DSTATE_h[1] <=
                 autocodePlant_DW->PrevY[1] + 0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[1] = autocodePlant_DW->PrevY[1];
      } else {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[1] = autocodePlant_DW->UnitDelay_DSTATE_h[1] -
          0.5;
      }

      if (autocodePlant_DW->UnitDelay_DSTATE_h[2] < autocodePlant_DW->PrevY[2] -
          0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[2] = autocodePlant_DW->UnitDelay_DSTATE_h[2] +
          0.5;
      } else if (autocodePlant_DW->UnitDelay_DSTATE_h[2] <=
                 autocodePlant_DW->PrevY[2] + 0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[2] = autocodePlant_DW->PrevY[2];
      } else {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[2] = autocodePlant_DW->UnitDelay_DSTATE_h[2] -
          0.5;
      }

      if (autocodePlant_DW->UnitDelay_DSTATE_h[3] < autocodePlant_DW->PrevY[3] -
          0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[3] = autocodePlant_DW->UnitDelay_DSTATE_h[3] +
          0.5;
      } else if (autocodePlant_DW->UnitDelay_DSTATE_h[3] <=
                 autocodePlant_DW->PrevY[3] + 0.5) {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[3] = autocodePlant_DW->PrevY[3];
      } else {
        /* Backlash: '<S7>/Backlash' */
        autocodePlant_B->Backlash[3] = autocodePlant_DW->UnitDelay_DSTATE_h[3] -
          0.5;
      }

      /* End of Backlash: '<S7>/Backlash' */
    }

    /* DotProduct: '<S10>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S10>/Dot Product2'
     */
    rtb_sincos_o2_f_idx_0 = (autocodePlant_B->Sum_m * rtb_Sum_k[0] +
      autocodePlant_B->Sum_b1 * rtb_Sum_k[1]) + autocodePlant_B->Sum_k *
      rtb_Sum_k[2];

    /* Switch: '<S39>/Switch' incorporates:
     *  Constant: '<S39>/Constant4'
     *  Constant: '<S39>/Constant5'
     *  DotProduct: '<S10>/Dot Product2'
     */
    if (rtb_sincos_o2_f_idx_0 >= 0.0) {
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
    rtb_Sum1_nc_idx_0 = (real_T)i * fmax(1.0E-6, fabs(rtb_sincos_o2_f_idx_0));

    /* Signum: '<S10>/Sign1' */
    if (rtIsNaN(rtb_Sum1_nc_idx_0)) {
      rtb_Sign1 = (rtNaN);
    } else if (rtb_Sum1_nc_idx_0 < 0.0) {
      rtb_Sign1 = -1.0;
    } else {
      rtb_Sign1 = (rtb_Sum1_nc_idx_0 > 0.0);
    }

    /* End of Signum: '<S10>/Sign1' */

    /* Lookup_n-D: '<S10>/CA Lookup Table' incorporates:
     *  Gain: '<S45>/Gain'
     *  Product: '<S10>/Product7'
     *  Signum: '<S9>/Sign1'
     */
    bpIndices[0U] = plook_binx(rtb_MediumHighAltitudeIntensity,
      &aeroParams.machBreakpoints_na[0], 9U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_j[0U] = rtb_Sum1_nc_idx_0;
    bpIndices[1U] = plook_binx(rtb_sigma_ugsigma_vg,
      &aeroParams.aoaBreakpoints_deg[0], 2U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_j[1U] = rtb_Sum1_nc_idx_0;
    bpIndices[2U] = plook_binx(autocodePlant_B->Backlash[1] * rtb_Sign1,
      &aeroParams.controlBreakpoints_deg[0], 4U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_j[2U] = rtb_Sum1_nc_idx_0;
    rtb_Sign1_e = intrp3d_l_pw(bpIndices, rtb_Sum_j, &aeroParams.CaFin_na[0],
      rtCP__CALookupTable_dimSizes);

    /* Gain: '<S106>/1//T0' */
    rtb_Product2_l3 = 0.00347041471455839 * rtb_UnitConversion;

    /* Math: '<S106>/(T//T0)^(g//LR) ' incorporates:
     *  Constant: '<S106>/Constant'
     */
    rtb_TT0gLR = rt_powd_snf(rtb_Product2_l3, 5.255875601466713);

    /* Product: '<S106>/Product' */
    rtb_sincos_o2_f_idx_0 = rtb_TT0gLR / rtb_Product2_l3;

    /* Saturate: '<S106>/Limit  altitude  to Stratosphere' incorporates:
     *  Constant: '<S106>/Altitude of Troposphere'
     *  Sum: '<S106>/Sum'
     */
    if (11000.0 - rtb_Product3_eg > 0.0) {
      rtb_UnaryMinus1_o = 0.0;
    } else if (11000.0 - rtb_Product3_eg < -9000.0) {
      rtb_UnaryMinus1_o = -9000.0;
    } else {
      rtb_UnaryMinus1_o = 11000.0 - rtb_Product3_eg;
    }

    /* Math: '<S106>/Stratosphere Model' incorporates:
     *  Gain: '<S106>/g//R'
     *  Product: '<S106>/Product1'
     *  Saturate: '<S106>/Limit  altitude  to Stratosphere'
     *
     * About '<S106>/Stratosphere Model':
     *  Operator: exp
     */
    rtb_Product2_l3 = exp(1.0 / rtb_UnitConversion * (0.03416319140953364 *
      rtb_UnaryMinus1_o));

    /* Product: '<S106>/Product3' incorporates:
     *  Gain: '<S106>/rho0'
     */
    rtb_Product3_eg = 1.225 * rtb_sincos_o2_f_idx_0 * rtb_Product2_l3;

    /* Product: '<S10>/Product' incorporates:
     *  Constant: '<S10>/Constant1'
     *  DotProduct: '<S10>/Dot Product3'
     *  Product: '<S11>/Product'
     *  Product: '<S12>/Product'
     *  Product: '<S8>/Product'
     *  Product: '<S9>/Product'
     */
    rtb_UnaryMinus1_o = 0.5 * rtb_Product3_eg;
    rtb_Sign1_l = ((rtb_Sum_k[0] * rtb_Sum_k[0] + rtb_Sum_k[1] * rtb_Sum_k[1]) +
                   rtb_Sum_k[2] * rtb_Sum_k[2]) * rtb_UnaryMinus1_o;

    /* UnaryMinus: '<S10>/Unary Minus' incorporates:
     *  Constant: '<S10>/   '
     *  Product: '<S10>/Product1'
     */
    rtb_Product8_ne = -(rtb_Sign1_e * rtb_Sign1_l * vehicleParams.area_m2);

    /* Lookup_n-D: '<S10>/CN Lookup Table' incorporates:
     *  Gain: '<S45>/Gain'
     *  Product: '<S10>/Product5'
     *  Signum: '<S9>/Sign1'
     */
    bpIndices_0[0U] = plook_binx(rtb_MediumHighAltitudeIntensity,
      &aeroParams.machBreakpoints_na[0], 9U, &rtb_Sum1_nc_idx_0);
    rtb_Sum1_gf[0U] = rtb_Sum1_nc_idx_0;
    bpIndices_0[1U] = plook_binx(rtb_sigma_ugsigma_vg,
      &aeroParams.aoaBreakpoints_deg[0], 2U, &rtb_Sum1_nc_idx_0);
    rtb_Sum1_gf[1U] = rtb_Sum1_nc_idx_0;
    bpIndices_0[2U] = plook_binx(autocodePlant_B->Backlash[1] * rtb_Sign1,
      &aeroParams.controlBreakpoints_deg[0], 4U, &rtb_Sum1_nc_idx_0);
    rtb_Sum1_gf[2U] = rtb_Sum1_nc_idx_0;
    rtb_MediumHighAltitudeIntensity = intrp3d_l_pw(bpIndices_0, rtb_Sum1_gf,
      &aeroParams.CnFin_na[0], rtCP__CNLookupTable_dimSizes);

    /* UnaryMinus: '<S10>/Unary Minus1' incorporates:
     *  Constant: '<S10>/ '
     *  Product: '<S10>/Product2'
     */
    rtb_UnaryMinus1 = -(rtb_MediumHighAltitudeIntensity * rtb_Sign1_l *
                        vehicleParams.area_m2);

    /* Sum: '<S10>/Sum1' incorporates:
     *  Product: '<S10>/Product3'
     *  Product: '<S10>/Product4'
     *  SignalConversion generated from: '<S10>/Dot Product2'
     */
    rtb_Product4_a = rtb_UnaryMinus1 * autocodePlant_B->Sum_m * rtb_Sign1 +
      rtb_Product8_ne * autocodePlant_B->Sum;

    /* Sum: '<S9>/Sum' incorporates:
     *  Product: '<S21>/Element Product'
     *  Sum: '<S21>/Sum'
     */
    rtb_sincos_o2_f_idx_0 = (rtb_Product_ab[1] * autocodePlant_B->Subtract1[2] -
      autocodePlant_B->Subtract1[1] * rtb_Product_ab[2]) +
      rtb_VectorConcatenate[0];
    rtb_Product_lj[0] = rtb_sincos_o2_f_idx_0;

    /* DotProduct: '<S9>/Dot Product4' */
    rtb_MediumHighAltitudeIntensity = rtb_sincos_o2_f_idx_0 *
      rtb_sincos_o2_f_idx_0;

    /* Sum: '<S10>/Sum1' incorporates:
     *  Product: '<S10>/Product3'
     *  Product: '<S10>/Product4'
     *  SignalConversion generated from: '<S10>/Dot Product2'
     */
    rtb_Sum1_hwh_idx_1 = rtb_UnaryMinus1 * autocodePlant_B->Sum_b1 * rtb_Sign1 +
      rtb_Product8_ne * autocodePlant_B->Sum_c;

    /* Sum: '<S9>/Sum' incorporates:
     *  Product: '<S21>/Element Product'
     *  Sum: '<S21>/Sum'
     */
    rtb_LowAltitudeScaleLength = (autocodePlant_B->Subtract1[0] *
      rtb_Product_ab[2] - rtb_Product_ab[0] * autocodePlant_B->Subtract1[2]) +
      rtb_VectorConcatenate[1];

    /* Sum: '<S10>/Sum1' incorporates:
     *  Product: '<S10>/Product3'
     *  Product: '<S10>/Product4'
     *  SignalConversion generated from: '<S10>/Dot Product2'
     */
    rtb_Product8_ne = rtb_UnaryMinus1 * autocodePlant_B->Sum_k * rtb_Sign1 +
      rtb_Product8_ne * autocodePlant_B->Sum_b;

    /* Sum: '<S9>/Sum' incorporates:
     *  Product: '<S21>/Element Product'
     *  Sum: '<S21>/Sum'
     */
    rtb_sincos_o2_f_idx_0 = (rtb_Product_ab[0] * autocodePlant_B->Subtract1[1] -
      autocodePlant_B->Subtract1[0] * rtb_Product_ab[1]) +
      rtb_VectorConcatenate[2];

    /* Switch: '<S18>/Switch' incorporates:
     *  Constant: '<S18>/Constant4'
     *  Constant: '<S18>/Constant5'
     */
    if (rtb_UnitConversion_e >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S9>/Dot Product4' incorporates:
     *  DotProduct: '<S9>/Dot Product3'
     */
    rtb_UnaryMinus_o3 = (rtb_LowAltitudeScaleLength * rtb_LowAltitudeScaleLength
                         + rtb_MediumHighAltitudeIntensity) +
      rtb_sincos_o2_f_idx_0 * rtb_sincos_o2_f_idx_0;

    /* Product: '<S9>/Divide1' incorporates:
     *  DotProduct: '<S9>/Dot Product4'
     *  Product: '<S18>/Product'
     *  Sqrt: '<S9>/Sqrt1'
     *  Switch: '<S18>/Switch'
     */
    rtb_Sign1_l = sqrt(rtb_UnaryMinus_o3) / ((real_T)i * rtb_Gain_n);
    if (tmp) {
      /* Angle2Quat: '<S9>/Rotation Angles to Quaternions' incorporates:
       *  Constant: '<S9>/liftDirection_na1'
       */
      rtb_UnitDelay2_idx_3 = cos(aeroParams.finAngles1_rad[2] / 2.0);
      rtb_UnitDelay2_idx_1 = cos(aeroParams.finAngles1_rad[1] / 2.0);
      rtb_UnaryMinus_n = cos(aeroParams.finAngles1_rad[0] / 2.0);
      rtb_Sum1_nc_idx_0 = sin(aeroParams.finAngles1_rad[2] / 2.0);
      rtb_FlatEarthtoLLA_o1_idx_0 = sin(aeroParams.finAngles1_rad[1] / 2.0);
      rtb_Switch_d_idx_1 = sin(aeroParams.finAngles1_rad[0] / 2.0);
      rtb_DiscreteTransferFcn2 = rtb_UnaryMinus_n * rtb_UnitDelay2_idx_1;
      rtb_Switch_d_idx_2 = rtb_Switch_d_idx_1 * rtb_FlatEarthtoLLA_o1_idx_0;
      rtb_UnitDelay2_idx_0 = rtb_DiscreteTransferFcn2 * rtb_UnitDelay2_idx_3 -
        rtb_Switch_d_idx_2 * rtb_Sum1_nc_idx_0;
      rtb_UnaryMinus_n *= rtb_FlatEarthtoLLA_o1_idx_0;
      rtb_Switch_d_idx_1 *= rtb_UnitDelay2_idx_1;
      rtb_UnitDelay2_idx_1 = rtb_UnaryMinus_n * rtb_Sum1_nc_idx_0 +
        rtb_Switch_d_idx_1 * rtb_UnitDelay2_idx_3;
      rtb_Switch_d_idx_1 = rtb_UnaryMinus_n * rtb_UnitDelay2_idx_3 -
        rtb_Switch_d_idx_1 * rtb_Sum1_nc_idx_0;
      rtb_UnitDelay2_idx_3 = rtb_DiscreteTransferFcn2 * rtb_Sum1_nc_idx_0 +
        rtb_Switch_d_idx_2 * rtb_UnitDelay2_idx_3;

      /* Sqrt: '<S36>/sqrt' incorporates:
       *  Product: '<S37>/Product'
       *  Product: '<S37>/Product1'
       *  Product: '<S37>/Product2'
       *  Product: '<S37>/Product3'
       *  Sqrt: '<S30>/sqrt'
       *  Sum: '<S37>/Sum'
       */
      rtb_Sum1_nc_idx_0 = sqrt(((rtb_UnitDelay2_idx_0 * rtb_UnitDelay2_idx_0 +
        rtb_UnitDelay2_idx_1 * rtb_UnitDelay2_idx_1) + rtb_Switch_d_idx_1 *
        rtb_Switch_d_idx_1) + rtb_UnitDelay2_idx_3 * rtb_UnitDelay2_idx_3);

      /* Product: '<S32>/Product2' incorporates:
       *  Sqrt: '<S36>/sqrt'
       */
      rtb_DiscreteTransferFcn1 = rtb_Switch_d_idx_1 / rtb_Sum1_nc_idx_0;

      /* Product: '<S32>/Product3' incorporates:
       *  Sqrt: '<S36>/sqrt'
       */
      rtb_DiscreteTransferFcn2 = rtb_UnitDelay2_idx_3 / rtb_Sum1_nc_idx_0;

      /* Product: '<S32>/Product1' incorporates:
       *  Sqrt: '<S36>/sqrt'
       */
      rtb_UnitDelay2_idx_3 = rtb_UnitDelay2_idx_1 / rtb_Sum1_nc_idx_0;

      /* Product: '<S32>/Product' incorporates:
       *  Product: '<S26>/Product'
       *  Sqrt: '<S36>/sqrt'
       */
      rtb_Sum1_nc_idx_0 = rtb_UnitDelay2_idx_0 / rtb_Sum1_nc_idx_0;

      /* Product: '<S33>/Product7' incorporates:
       *  Product: '<S34>/Product7'
       */
      rtb_Sign1_e = rtb_DiscreteTransferFcn2 * rtb_DiscreteTransferFcn2;

      /* Product: '<S33>/Product' incorporates:
       *  Product: '<S34>/Product'
       */
      rtb_UnaryMinus1_e = rtb_UnitDelay2_idx_3 * rtb_DiscreteTransferFcn1;

      /* Product: '<S33>/Product1' incorporates:
       *  Product: '<S32>/Product'
       *  Product: '<S34>/Product1'
       */
      Sum_bx_tmp = rtb_Sum1_nc_idx_0 * rtb_DiscreteTransferFcn2;

      /* Product: '<S33>/Product3' incorporates:
       *  Product: '<S35>/Product'
       */
      Sum_bx_tmp_0 = rtb_UnitDelay2_idx_3 * rtb_DiscreteTransferFcn2;

      /* Product: '<S33>/Product2' incorporates:
       *  Product: '<S32>/Product'
       *  Product: '<S35>/Product1'
       */
      Sum_bx_tmp_1 = rtb_Sum1_nc_idx_0 * rtb_DiscreteTransferFcn1;

      /* Product: '<S33>/Product6' incorporates:
       *  Product: '<S35>/Product7'
       */
      rtb_Sum_a_idx_2 = rtb_DiscreteTransferFcn1 * rtb_DiscreteTransferFcn1;

      /* Gain: '<S33>/Gain2' incorporates:
       *  Constant: '<S33>/Constant'
       *  Gain: '<S27>/Gain2'
       *  Product: '<S33>/Product6'
       *  Product: '<S33>/Product7'
       *  Sum: '<S33>/Sum3'
       */
      rtb_MediumHighAltitudeIntensity = ((0.5 - rtb_Sum_a_idx_2) - rtb_Sign1_e) *
        2.0;

      /* Product: '<S33>/Product4' incorporates:
       *  Constant: '<S9>/axialDirection_na'
       *  Gain: '<S33>/Gain'
       *  Product: '<S27>/Product4'
       *  Product: '<S33>/Product'
       *  Product: '<S33>/Product1'
       *  Sum: '<S33>/Sum1'
       */
      rtb_UnaryMinus1 = (rtb_UnaryMinus1_e + Sum_bx_tmp) * 2.0 * 0.0;

      /* Gain: '<S33>/Gain1' incorporates:
       *  Gain: '<S27>/Gain1'
       *  Product: '<S33>/Product2'
       *  Product: '<S33>/Product3'
       *  Sum: '<S33>/Sum2'
       */
      rtb_UnaryMinus1_c = (Sum_bx_tmp_0 - Sum_bx_tmp_1) * 2.0;

      /* Sum: '<S33>/Sum' incorporates:
       *  Constant: '<S9>/axialDirection_na'
       *  Gain: '<S33>/Gain1'
       *  Gain: '<S33>/Gain2'
       *  Product: '<S33>/Product4'
       *  Product: '<S33>/Product5'
       */
      autocodePlant_B->Sum_bx = (rtb_MediumHighAltitudeIntensity +
        rtb_UnaryMinus1) + rtb_UnaryMinus1_c * 0.0;

      /* Product: '<S34>/Product3' incorporates:
       *  Product: '<S35>/Product3'
       */
      rtb_Gain_nu = rtb_DiscreteTransferFcn1 * rtb_DiscreteTransferFcn2;

      /* Product: '<S34>/Product2' incorporates:
       *  Product: '<S32>/Product'
       *  Product: '<S35>/Product2'
       */
      rtb_Sum1_hj_idx_0 = rtb_Sum1_nc_idx_0 * rtb_UnitDelay2_idx_3;

      /* Sum: '<S34>/Sum3' incorporates:
       *  Constant: '<S34>/Constant'
       *  Product: '<S34>/Product6'
       *  Sum: '<S35>/Sum3'
       */
      rtb_Sum1_hj_idx_1 = 0.5 - rtb_UnitDelay2_idx_3 * rtb_UnitDelay2_idx_3;

      /* Product: '<S34>/Product8' incorporates:
       *  Constant: '<S9>/axialDirection_na'
       *  Gain: '<S34>/Gain2'
       *  Product: '<S28>/Product8'
       *  Sum: '<S34>/Sum3'
       */
      rtb_Sign1_e = (rtb_Sum1_hj_idx_1 - rtb_Sign1_e) * 2.0 * 0.0;

      /* Gain: '<S34>/Gain' incorporates:
       *  Gain: '<S28>/Gain'
       *  Sum: '<S34>/Sum1'
       */
      rtb_UnaryMinus1_e = (rtb_UnaryMinus1_e - Sum_bx_tmp) * 2.0;

      /* Gain: '<S34>/Gain1' incorporates:
       *  Gain: '<S28>/Gain1'
       *  Product: '<S34>/Product2'
       *  Product: '<S34>/Product3'
       *  Sum: '<S34>/Sum2'
       */
      Sum_bx_tmp = (rtb_Sum1_hj_idx_0 + rtb_Gain_nu) * 2.0;

      /* Sum: '<S34>/Sum' incorporates:
       *  Constant: '<S9>/axialDirection_na'
       *  Gain: '<S34>/Gain'
       *  Gain: '<S34>/Gain1'
       *  Product: '<S34>/Product5'
       *  Product: '<S34>/Product8'
       */
      autocodePlant_B->Sum_l = (rtb_Sign1_e + rtb_UnaryMinus1_e) + Sum_bx_tmp *
        0.0;

      /* Gain: '<S35>/Gain' incorporates:
       *  Gain: '<S29>/Gain'
       *  Sum: '<S35>/Sum1'
       */
      Sum_bx_tmp_0 = (Sum_bx_tmp_0 + Sum_bx_tmp_1) * 2.0;

      /* Product: '<S35>/Product5' incorporates:
       *  Constant: '<S9>/axialDirection_na'
       *  Gain: '<S35>/Gain1'
       *  Product: '<S29>/Product5'
       *  Sum: '<S35>/Sum2'
       */
      Sum_bx_tmp_1 = (rtb_Gain_nu - rtb_Sum1_hj_idx_0) * 2.0 * 0.0;

      /* Gain: '<S35>/Gain2' incorporates:
       *  Gain: '<S29>/Gain2'
       *  Sum: '<S35>/Sum3'
       */
      rtb_Sum_a_idx_2 = (rtb_Sum1_hj_idx_1 - rtb_Sum_a_idx_2) * 2.0;

      /* Sum: '<S35>/Sum' incorporates:
       *  Constant: '<S9>/axialDirection_na'
       *  Gain: '<S35>/Gain'
       *  Gain: '<S35>/Gain2'
       *  Product: '<S35>/Product5'
       *  Product: '<S35>/Product8'
       */
      autocodePlant_B->Sum_cx = (Sum_bx_tmp_1 + Sum_bx_tmp_0) + rtb_Sum_a_idx_2 *
        0.0;

      /* Sum: '<S27>/Sum' incorporates:
       *  Constant: '<S9>/normalDirection_na'
       *  Product: '<S27>/Product8'
       */
      autocodePlant_B->Sum_f = (rtb_MediumHighAltitudeIntensity * 0.0 +
        rtb_UnaryMinus1) + rtb_UnaryMinus1_c;

      /* Sum: '<S28>/Sum' incorporates:
       *  Constant: '<S9>/normalDirection_na'
       *  Product: '<S28>/Product4'
       */
      autocodePlant_B->Sum_i = (rtb_UnaryMinus1_e * 0.0 + rtb_Sign1_e) +
        Sum_bx_tmp;

      /* Sum: '<S29>/Sum' incorporates:
       *  Constant: '<S9>/normalDirection_na'
       *  Product: '<S29>/Product4'
       */
      autocodePlant_B->Sum_e = (Sum_bx_tmp_0 * 0.0 + Sum_bx_tmp_1) +
        rtb_Sum_a_idx_2;

      /* Sum: '<S9>/Sum2' */
      autocodePlant_B->Sum2_i[0] = autocodePlant_B->Sum_f +
        autocodePlant_B->Sum_bx;
      autocodePlant_B->Sum2_i[1] = autocodePlant_B->Sum_i +
        autocodePlant_B->Sum_l;
      autocodePlant_B->Sum2_i[2] = autocodePlant_B->Sum_e +
        autocodePlant_B->Sum_cx;
    }

    /* Product: '<S9>/Product8' incorporates:
     *  Sum: '<S9>/Sum'
     */
    rtb_MediumHighAltitudeIntensity = rtb_Product_lj[0] *
      autocodePlant_B->Sum2_i[0];
    rtb_UnaryMinus1 = rtb_LowAltitudeScaleLength * autocodePlant_B->Sum2_i[1];
    rtb_UnaryMinus1_c = rtb_sincos_o2_f_idx_0 * autocodePlant_B->Sum2_i[2];

    /* DotProduct: '<S9>/Dot Product1' */
    rtb_Sum_a_idx_2 = (rtb_MediumHighAltitudeIntensity *
                       rtb_MediumHighAltitudeIntensity + rtb_UnaryMinus1 *
                       rtb_UnaryMinus1) + rtb_UnaryMinus1_c * rtb_UnaryMinus1_c;

    /* Switch: '<S20>/Switch' incorporates:
     *  Constant: '<S20>/Constant4'
     *  Constant: '<S20>/Constant5'
     *  DotProduct: '<S9>/Dot Product1'
     */
    if (rtb_Sum_a_idx_2 >= 0.0) {
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
    rtb_UnaryMinus_n = ((autocodePlant_B->Sum_bx *
                         rtb_MediumHighAltitudeIntensity +
                         autocodePlant_B->Sum_l * rtb_UnaryMinus1) +
                        autocodePlant_B->Sum_cx * rtb_UnaryMinus1_c) / sqrt
      ((real_T)i * fmax(1.0E-6, rtb_Sum_a_idx_2));

    /* Saturate: '<S9>/Saturation' */
    if (rtb_UnaryMinus_n > 1.0) {
      rtb_UnaryMinus_n = 1.0;
    } else if (rtb_UnaryMinus_n < -1.0) {
      rtb_UnaryMinus_n = -1.0;
    }

    /* Gain: '<S25>/Gain' incorporates:
     *  Saturate: '<S9>/Saturation'
     *  Trigonometry: '<S9>/Acos'
     */
    rtb_UnaryMinus1 = 57.29577951308232 * acos(rtb_UnaryMinus_n);

    /* DotProduct: '<S9>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S9>/Dot Product2'
     *  Sum: '<S9>/Sum'
     */
    rtb_MediumHighAltitudeIntensity = (autocodePlant_B->Sum_f * rtb_Product_lj[0]
      + autocodePlant_B->Sum_i * rtb_LowAltitudeScaleLength) +
      autocodePlant_B->Sum_e * rtb_sincos_o2_f_idx_0;

    /* Switch: '<S19>/Switch' incorporates:
     *  Constant: '<S19>/Constant4'
     *  Constant: '<S19>/Constant5'
     *  DotProduct: '<S9>/Dot Product2'
     */
    if (rtb_MediumHighAltitudeIntensity >= 0.0) {
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
    rtb_Sum1_nc_idx_0 = (real_T)i * fmax(1.0E-6, fabs
      (rtb_MediumHighAltitudeIntensity));

    /* Signum: '<S9>/Sign1' */
    if (rtIsNaN(rtb_Sum1_nc_idx_0)) {
      rtb_MediumHighAltitudeIntensity = (rtNaN);
    } else if (rtb_Sum1_nc_idx_0 < 0.0) {
      rtb_MediumHighAltitudeIntensity = -1.0;
    } else {
      rtb_MediumHighAltitudeIntensity = (rtb_Sum1_nc_idx_0 > 0.0);
    }

    /* End of Signum: '<S9>/Sign1' */

    /* Lookup_n-D: '<S9>/CA Lookup Table' incorporates:
     *  Gain: '<S25>/Gain'
     *  Product: '<S9>/Product7'
     *  Signum: '<S12>/Sign1'
     */
    bpIndices_1[0U] = plook_binx(rtb_Sign1_l, &aeroParams.machBreakpoints_na[0],
      9U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_cy[0U] = rtb_Sum1_nc_idx_0;
    bpIndices_1[1U] = plook_binx(rtb_UnaryMinus1,
      &aeroParams.aoaBreakpoints_deg[0], 2U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_cy[1U] = rtb_Sum1_nc_idx_0;
    bpIndices_1[2U] = plook_binx(autocodePlant_B->Backlash[0] *
      rtb_MediumHighAltitudeIntensity, &aeroParams.controlBreakpoints_deg[0], 4U,
      &rtb_Sum1_nc_idx_0);
    rtb_Sum_cy[2U] = rtb_Sum1_nc_idx_0;
    rtb_Sign1_e = intrp3d_l_pw(bpIndices_1, rtb_Sum_cy, &aeroParams.CaFin_na[0],
      rtCP__CALookupTable_dimSizes_k);

    /* Product: '<S9>/Product' */
    rtb_Lw_idx_1 = rtb_UnaryMinus_o3 * rtb_UnaryMinus1_o;

    /* UnaryMinus: '<S9>/Unary Minus' incorporates:
     *  Constant: '<S9>/   '
     *  Product: '<S9>/Product1'
     */
    rtb_UnaryMinus_o3 = -(rtb_Sign1_e * rtb_Lw_idx_1 * vehicleParams.area_m2);

    /* Lookup_n-D: '<S9>/CN Lookup Table' incorporates:
     *  Gain: '<S25>/Gain'
     *  Product: '<S9>/Product5'
     *  Signum: '<S12>/Sign1'
     */
    bpIndices_2[0U] = plook_binx(rtb_Sign1_l, &aeroParams.machBreakpoints_na[0],
      9U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_pz[0U] = rtb_Sum1_nc_idx_0;
    bpIndices_2[1U] = plook_binx(rtb_UnaryMinus1,
      &aeroParams.aoaBreakpoints_deg[0], 2U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_pz[1U] = rtb_Sum1_nc_idx_0;
    bpIndices_2[2U] = plook_binx(autocodePlant_B->Backlash[0] *
      rtb_MediumHighAltitudeIntensity, &aeroParams.controlBreakpoints_deg[0], 4U,
      &rtb_Sum1_nc_idx_0);
    rtb_Sum_pz[2U] = rtb_Sum1_nc_idx_0;
    rtb_Sign1_l = intrp3d_l_pw(bpIndices_2, rtb_Sum_pz, &aeroParams.CnFin_na[0],
      rtCP__CNLookupTable_dimSizes_j);

    /* UnaryMinus: '<S9>/Unary Minus1' incorporates:
     *  Constant: '<S9>/ '
     *  Product: '<S9>/Product2'
     */
    rtb_UnaryMinus1_c = -(rtb_Sign1_l * rtb_Lw_idx_1 * vehicleParams.area_m2);

    /* Sum: '<S9>/Sum1' incorporates:
     *  Product: '<S9>/Product3'
     *  Product: '<S9>/Product4'
     *  SignalConversion generated from: '<S9>/Dot Product2'
     */
    rtb_Sum1_gf[0] = rtb_UnaryMinus1_c * autocodePlant_B->Sum_f *
      rtb_MediumHighAltitudeIntensity + rtb_UnaryMinus_o3 *
      autocodePlant_B->Sum_bx;
    rtb_Sum1_gf[1] = rtb_UnaryMinus1_c * autocodePlant_B->Sum_i *
      rtb_MediumHighAltitudeIntensity + rtb_UnaryMinus_o3 *
      autocodePlant_B->Sum_l;
    rtb_Sum1_gf[2] = rtb_UnaryMinus1_c * autocodePlant_B->Sum_e *
      rtb_MediumHighAltitudeIntensity + rtb_UnaryMinus_o3 *
      autocodePlant_B->Sum_cx;

    /* Sum: '<S22>/Sum' incorporates:
     *  Product: '<S22>/Element Product'
     */
    rtb_Sum_j[0] = autocodePlant_B->Subtract1[1] * rtb_Sum1_gf[2] - rtb_Sum1_gf
      [1] * autocodePlant_B->Subtract1[2];

    /* Sum: '<S42>/Sum' incorporates:
     *  Product: '<S42>/Element Product'
     */
    rtb_UnaryMinus_o3 = autocodePlant_B->Subtract1_m[1] * rtb_Product8_ne -
      rtb_Sum1_hwh_idx_1 * autocodePlant_B->Subtract1_m[2];

    /* Sum: '<S22>/Sum' incorporates:
     *  Product: '<S22>/Element Product'
     */
    rtb_Sum_j[1] = rtb_Sum1_gf[0] * autocodePlant_B->Subtract1[2] -
      autocodePlant_B->Subtract1[0] * rtb_Sum1_gf[2];

    /* Sum: '<S42>/Sum' incorporates:
     *  Product: '<S42>/Element Product'
     */
    rtb_UnaryMinus1_c = rtb_Product4_a * autocodePlant_B->Subtract1_m[2] -
      autocodePlant_B->Subtract1_m[0] * rtb_Product8_ne;

    /* Sum: '<S22>/Sum' incorporates:
     *  Product: '<S22>/Element Product'
     */
    rtb_Sum_j[2] = autocodePlant_B->Subtract1[0] * rtb_Sum1_gf[1] - rtb_Sum1_gf
      [0] * autocodePlant_B->Subtract1[1];

    /* Sum: '<S42>/Sum' incorporates:
     *  Product: '<S42>/Element Product'
     */
    rtb_Sum_a_idx_2 = autocodePlant_B->Subtract1_m[0] * rtb_Sum1_hwh_idx_1 -
      rtb_Product4_a * autocodePlant_B->Subtract1_m[1];
    if (tmp) {
      /* Sum: '<S11>/Subtract1' incorporates:
       *  Constant: '<S11>/Constant4'
       *  Constant: '<S11>/Constant5'
       *  Constant: '<S3>/Constant2'
       *  Product: '<S11>/Product6'
       */
      autocodePlant_B->Subtract1_k[0] = vehicleParams.cg_m -
        aeroParams.finCP3_m[0];
      autocodePlant_B->Subtract1_k[1] = vehicleParams.cg_m * 0.0 -
        aeroParams.finCP3_m[1];
      autocodePlant_B->Subtract1_k[2] = vehicleParams.cg_m * 0.0 -
        aeroParams.finCP3_m[2];
    }

    /* Sum: '<S11>/Sum' incorporates:
     *  Product: '<S61>/Element Product'
     *  Sum: '<S61>/Sum'
     */
    Sum_bx_tmp_0 = (rtb_Product_ab[1] * autocodePlant_B->Subtract1_k[2] -
                    autocodePlant_B->Subtract1_k[1] * rtb_Product_ab[2]) +
      rtb_VectorConcatenate[0];
    rtb_Sum_cy[0] = Sum_bx_tmp_0;

    /* DotProduct: '<S11>/Dot Product4' */
    rtb_Sign1_e = Sum_bx_tmp_0 * Sum_bx_tmp_0;

    /* Sum: '<S11>/Sum' incorporates:
     *  Product: '<S61>/Element Product'
     *  Sum: '<S61>/Sum'
     */
    Sum_bx_tmp_1 = (autocodePlant_B->Subtract1_k[0] * rtb_Product_ab[2] -
                    rtb_Product_ab[0] * autocodePlant_B->Subtract1_k[2]) +
      rtb_VectorConcatenate[1];
    Sum_bx_tmp_0 = (rtb_Product_ab[0] * autocodePlant_B->Subtract1_k[1] -
                    autocodePlant_B->Subtract1_k[0] * rtb_Product_ab[1]) +
      rtb_VectorConcatenate[2];

    /* Switch: '<S58>/Switch' incorporates:
     *  Constant: '<S58>/Constant4'
     *  Constant: '<S58>/Constant5'
     */
    if (rtb_UnitConversion_e >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S11>/Dot Product4' incorporates:
     *  DotProduct: '<S11>/Dot Product3'
     */
    rtb_Sum1_hj_idx_0 = (Sum_bx_tmp_1 * Sum_bx_tmp_1 + rtb_Sign1_e) +
      Sum_bx_tmp_0 * Sum_bx_tmp_0;

    /* Product: '<S11>/Divide1' incorporates:
     *  DotProduct: '<S11>/Dot Product4'
     *  Product: '<S58>/Product'
     *  Sqrt: '<S11>/Sqrt1'
     *  Switch: '<S58>/Switch'
     */
    rtb_Lw_idx_1 = sqrt(rtb_Sum1_hj_idx_0) / ((real_T)i * rtb_Gain_n);
    if (tmp) {
      /* Angle2Quat: '<S11>/Rotation Angles to Quaternions' incorporates:
       *  Constant: '<S11>/liftDirection_na1'
       */
      rtb_UnitDelay2_idx_3 = cos(aeroParams.finAngles3_rad[2] / 2.0);
      rtb_UnitDelay2_idx_1 = cos(aeroParams.finAngles3_rad[1] / 2.0);
      rtb_UnaryMinus_n = cos(aeroParams.finAngles3_rad[0] / 2.0);
      rtb_Sum1_nc_idx_0 = sin(aeroParams.finAngles3_rad[2] / 2.0);
      rtb_FlatEarthtoLLA_o1_idx_0 = sin(aeroParams.finAngles3_rad[1] / 2.0);
      rtb_Switch_d_idx_1 = sin(aeroParams.finAngles3_rad[0] / 2.0);
      rtb_DiscreteTransferFcn2 = rtb_UnaryMinus_n * rtb_UnitDelay2_idx_1;
      rtb_Switch_d_idx_2 = rtb_Switch_d_idx_1 * rtb_FlatEarthtoLLA_o1_idx_0;
      rtb_UnitDelay2_idx_0 = rtb_DiscreteTransferFcn2 * rtb_UnitDelay2_idx_3 -
        rtb_Switch_d_idx_2 * rtb_Sum1_nc_idx_0;
      rtb_UnaryMinus_n *= rtb_FlatEarthtoLLA_o1_idx_0;
      rtb_Switch_d_idx_1 *= rtb_UnitDelay2_idx_1;
      rtb_UnitDelay2_idx_1 = rtb_UnaryMinus_n * rtb_Sum1_nc_idx_0 +
        rtb_Switch_d_idx_1 * rtb_UnitDelay2_idx_3;
      rtb_Switch_d_idx_1 = rtb_UnaryMinus_n * rtb_UnitDelay2_idx_3 -
        rtb_Switch_d_idx_1 * rtb_Sum1_nc_idx_0;
      rtb_UnitDelay2_idx_3 = rtb_DiscreteTransferFcn2 * rtb_Sum1_nc_idx_0 +
        rtb_Switch_d_idx_2 * rtb_UnitDelay2_idx_3;

      /* Sqrt: '<S76>/sqrt' incorporates:
       *  Product: '<S77>/Product'
       *  Product: '<S77>/Product1'
       *  Product: '<S77>/Product2'
       *  Product: '<S77>/Product3'
       *  Sqrt: '<S70>/sqrt'
       *  Sum: '<S77>/Sum'
       */
      rtb_Sum1_nc_idx_0 = sqrt(((rtb_UnitDelay2_idx_0 * rtb_UnitDelay2_idx_0 +
        rtb_UnitDelay2_idx_1 * rtb_UnitDelay2_idx_1) + rtb_Switch_d_idx_1 *
        rtb_Switch_d_idx_1) + rtb_UnitDelay2_idx_3 * rtb_UnitDelay2_idx_3);

      /* Product: '<S72>/Product2' incorporates:
       *  Sqrt: '<S76>/sqrt'
       */
      rtb_DiscreteTransferFcn1 = rtb_Switch_d_idx_1 / rtb_Sum1_nc_idx_0;

      /* Product: '<S72>/Product3' incorporates:
       *  Sqrt: '<S76>/sqrt'
       */
      rtb_DiscreteTransferFcn2 = rtb_UnitDelay2_idx_3 / rtb_Sum1_nc_idx_0;

      /* Product: '<S72>/Product1' incorporates:
       *  Sqrt: '<S76>/sqrt'
       */
      rtb_UnitDelay2_idx_3 = rtb_UnitDelay2_idx_1 / rtb_Sum1_nc_idx_0;

      /* Product: '<S72>/Product' incorporates:
       *  Product: '<S66>/Product'
       *  Sqrt: '<S76>/sqrt'
       */
      rtb_Sum1_nc_idx_0 = rtb_UnitDelay2_idx_0 / rtb_Sum1_nc_idx_0;

      /* Product: '<S73>/Product7' incorporates:
       *  Product: '<S74>/Product7'
       */
      Sum_a_tmp = rtb_DiscreteTransferFcn2 * rtb_DiscreteTransferFcn2;

      /* Product: '<S73>/Product' incorporates:
       *  Product: '<S74>/Product'
       */
      rtb_UnitDelay2_idx_0 = rtb_UnitDelay2_idx_3 * rtb_DiscreteTransferFcn1;

      /* Product: '<S73>/Product1' incorporates:
       *  Product: '<S72>/Product'
       *  Product: '<S74>/Product1'
       */
      rtb_UnitDelay2_idx_1 = rtb_Sum1_nc_idx_0 * rtb_DiscreteTransferFcn2;

      /* Product: '<S73>/Product3' incorporates:
       *  Product: '<S75>/Product'
       */
      rtb_UnaryMinus1_e = rtb_UnitDelay2_idx_3 * rtb_DiscreteTransferFcn2;

      /* Product: '<S73>/Product2' incorporates:
       *  Product: '<S72>/Product'
       *  Product: '<S75>/Product1'
       */
      Sum_bx_tmp = rtb_Sum1_nc_idx_0 * rtb_DiscreteTransferFcn1;

      /* Product: '<S73>/Product6' incorporates:
       *  Product: '<S75>/Product7'
       */
      rtb_Sum1_hj_idx_1 = rtb_DiscreteTransferFcn1 * rtb_DiscreteTransferFcn1;

      /* Gain: '<S73>/Gain2' incorporates:
       *  Constant: '<S73>/Constant'
       *  Gain: '<S67>/Gain2'
       *  Product: '<S73>/Product6'
       *  Product: '<S73>/Product7'
       *  Sum: '<S73>/Sum3'
       */
      rtb_Sign1_e = ((0.5 - rtb_Sum1_hj_idx_1) - Sum_a_tmp) * 2.0;

      /* Product: '<S73>/Product4' incorporates:
       *  Constant: '<S11>/axialDirection_na'
       *  Gain: '<S73>/Gain'
       *  Product: '<S67>/Product4'
       *  Product: '<S73>/Product'
       *  Product: '<S73>/Product1'
       *  Sum: '<S73>/Sum1'
       */
      rtb_Gain_nu = (rtb_UnitDelay2_idx_0 + rtb_UnitDelay2_idx_1) * 2.0 * 0.0;

      /* Gain: '<S73>/Gain1' incorporates:
       *  Gain: '<S67>/Gain1'
       *  Product: '<S73>/Product2'
       *  Product: '<S73>/Product3'
       *  Sum: '<S73>/Sum2'
       */
      rtb_Sign1_l = (rtb_UnaryMinus1_e - Sum_bx_tmp) * 2.0;

      /* Sum: '<S73>/Sum' incorporates:
       *  Constant: '<S11>/axialDirection_na'
       *  Gain: '<S73>/Gain1'
       *  Gain: '<S73>/Gain2'
       *  Product: '<S73>/Product4'
       *  Product: '<S73>/Product5'
       */
      autocodePlant_B->Sum_a = (rtb_Sign1_e + rtb_Gain_nu) + rtb_Sign1_l * 0.0;

      /* Product: '<S74>/Product3' incorporates:
       *  Product: '<S75>/Product3'
       */
      rtb_Sum_b4 = rtb_DiscreteTransferFcn1 * rtb_DiscreteTransferFcn2;

      /* Product: '<S74>/Product2' incorporates:
       *  Product: '<S72>/Product'
       *  Product: '<S75>/Product2'
       */
      rtb_Sum1_nc_idx_0 *= rtb_UnitDelay2_idx_3;

      /* Sum: '<S74>/Sum3' incorporates:
       *  Constant: '<S74>/Constant'
       *  Product: '<S74>/Product6'
       *  Sum: '<S75>/Sum3'
       */
      rtb_UnitDelay2_idx_3 = 0.5 - rtb_UnitDelay2_idx_3 * rtb_UnitDelay2_idx_3;

      /* Product: '<S74>/Product8' incorporates:
       *  Constant: '<S11>/axialDirection_na'
       *  Gain: '<S74>/Gain2'
       *  Product: '<S68>/Product8'
       *  Sum: '<S74>/Sum3'
       */
      Sum_a_tmp = (rtb_UnitDelay2_idx_3 - Sum_a_tmp) * 2.0 * 0.0;

      /* Gain: '<S74>/Gain' incorporates:
       *  Gain: '<S68>/Gain'
       *  Sum: '<S74>/Sum1'
       */
      rtb_DiscreteTransferFcn2 = (rtb_UnitDelay2_idx_0 - rtb_UnitDelay2_idx_1) *
        2.0;

      /* Gain: '<S74>/Gain1' incorporates:
       *  Gain: '<S68>/Gain1'
       *  Product: '<S74>/Product2'
       *  Product: '<S74>/Product3'
       *  Sum: '<S74>/Sum2'
       */
      rtb_UnitDelay2_idx_0 = (rtb_Sum1_nc_idx_0 + rtb_Sum_b4) * 2.0;

      /* Sum: '<S74>/Sum' incorporates:
       *  Constant: '<S11>/axialDirection_na'
       *  Gain: '<S74>/Gain'
       *  Gain: '<S74>/Gain1'
       *  Product: '<S74>/Product5'
       *  Product: '<S74>/Product8'
       */
      autocodePlant_B->Sum_ia = (Sum_a_tmp + rtb_DiscreteTransferFcn2) +
        rtb_UnitDelay2_idx_0 * 0.0;

      /* Gain: '<S75>/Gain' incorporates:
       *  Gain: '<S69>/Gain'
       *  Sum: '<S75>/Sum1'
       */
      rtb_UnaryMinus1_e = (rtb_UnaryMinus1_e + Sum_bx_tmp) * 2.0;

      /* Product: '<S75>/Product5' incorporates:
       *  Constant: '<S11>/axialDirection_na'
       *  Gain: '<S75>/Gain1'
       *  Product: '<S69>/Product5'
       *  Sum: '<S75>/Sum2'
       */
      Sum_bx_tmp = (rtb_Sum_b4 - rtb_Sum1_nc_idx_0) * 2.0 * 0.0;

      /* Gain: '<S75>/Gain2' incorporates:
       *  Gain: '<S69>/Gain2'
       *  Sum: '<S75>/Sum3'
       */
      rtb_Sum1_hj_idx_1 = (rtb_UnitDelay2_idx_3 - rtb_Sum1_hj_idx_1) * 2.0;

      /* Sum: '<S75>/Sum' incorporates:
       *  Constant: '<S11>/axialDirection_na'
       *  Gain: '<S75>/Gain'
       *  Gain: '<S75>/Gain2'
       *  Product: '<S75>/Product5'
       *  Product: '<S75>/Product8'
       */
      autocodePlant_B->Sum_bt = (Sum_bx_tmp + rtb_UnaryMinus1_e) +
        rtb_Sum1_hj_idx_1 * 0.0;

      /* Sum: '<S67>/Sum' incorporates:
       *  Constant: '<S11>/normalDirection_na'
       *  Product: '<S67>/Product8'
       */
      autocodePlant_B->Sum_o = (rtb_Sign1_e * 0.0 + rtb_Gain_nu) + rtb_Sign1_l;

      /* Sum: '<S68>/Sum' incorporates:
       *  Constant: '<S11>/normalDirection_na'
       *  Product: '<S68>/Product4'
       */
      autocodePlant_B->Sum_er = (rtb_DiscreteTransferFcn2 * 0.0 + Sum_a_tmp) +
        rtb_UnitDelay2_idx_0;

      /* Sum: '<S69>/Sum' incorporates:
       *  Constant: '<S11>/normalDirection_na'
       *  Product: '<S69>/Product4'
       */
      autocodePlant_B->Sum_g = (rtb_UnaryMinus1_e * 0.0 + Sum_bx_tmp) +
        rtb_Sum1_hj_idx_1;

      /* Sum: '<S11>/Sum2' */
      autocodePlant_B->Sum2_iw[0] = autocodePlant_B->Sum_o +
        autocodePlant_B->Sum_a;
      autocodePlant_B->Sum2_iw[1] = autocodePlant_B->Sum_er +
        autocodePlant_B->Sum_ia;
      autocodePlant_B->Sum2_iw[2] = autocodePlant_B->Sum_g +
        autocodePlant_B->Sum_bt;
    }

    /* Product: '<S11>/Product8' incorporates:
     *  Sum: '<S11>/Sum'
     */
    rtb_Sign1_e = rtb_Sum_cy[0] * autocodePlant_B->Sum2_iw[0];
    rtb_Gain_nu = Sum_bx_tmp_1 * autocodePlant_B->Sum2_iw[1];
    rtb_Sign1_l = Sum_bx_tmp_0 * autocodePlant_B->Sum2_iw[2];

    /* DotProduct: '<S11>/Dot Product1' */
    rtb_Sum1_hj_idx_1 = (rtb_Sign1_e * rtb_Sign1_e + rtb_Gain_nu * rtb_Gain_nu)
      + rtb_Sign1_l * rtb_Sign1_l;

    /* Switch: '<S60>/Switch' incorporates:
     *  Constant: '<S60>/Constant4'
     *  Constant: '<S60>/Constant5'
     *  DotProduct: '<S11>/Dot Product1'
     */
    if (rtb_Sum1_hj_idx_1 >= 0.0) {
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
    rtb_UnaryMinus_n = ((autocodePlant_B->Sum_a * rtb_Sign1_e +
                         autocodePlant_B->Sum_ia * rtb_Gain_nu) +
                        autocodePlant_B->Sum_bt * rtb_Sign1_l) / sqrt((real_T)i *
      fmax(1.0E-6, rtb_Sum1_hj_idx_1));

    /* Saturate: '<S11>/Saturation' */
    if (rtb_UnaryMinus_n > 1.0) {
      rtb_UnaryMinus_n = 1.0;
    } else if (rtb_UnaryMinus_n < -1.0) {
      rtb_UnaryMinus_n = -1.0;
    }

    /* Gain: '<S65>/Gain' incorporates:
     *  Saturate: '<S11>/Saturation'
     *  Trigonometry: '<S11>/Acos'
     */
    rtb_Gain_nu = 57.29577951308232 * acos(rtb_UnaryMinus_n);

    /* DotProduct: '<S11>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S11>/Dot Product2'
     *  Sum: '<S11>/Sum'
     */
    rtb_Sign1_e = (autocodePlant_B->Sum_o * rtb_Sum_cy[0] +
                   autocodePlant_B->Sum_er * Sum_bx_tmp_1) +
      autocodePlant_B->Sum_g * Sum_bx_tmp_0;

    /* Switch: '<S59>/Switch' incorporates:
     *  Constant: '<S59>/Constant4'
     *  Constant: '<S59>/Constant5'
     *  DotProduct: '<S11>/Dot Product2'
     */
    if (rtb_Sign1_e >= 0.0) {
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
    rtb_Sum1_nc_idx_0 = (real_T)i * fmax(1.0E-6, fabs(rtb_Sign1_e));

    /* Signum: '<S11>/Sign1' */
    if (rtIsNaN(rtb_Sum1_nc_idx_0)) {
      rtb_Sign1_e = (rtNaN);
    } else if (rtb_Sum1_nc_idx_0 < 0.0) {
      rtb_Sign1_e = -1.0;
    } else {
      rtb_Sign1_e = (rtb_Sum1_nc_idx_0 > 0.0);
    }

    /* End of Signum: '<S11>/Sign1' */

    /* Lookup_n-D: '<S11>/CA Lookup Table' incorporates:
     *  Gain: '<S65>/Gain'
     *  Product: '<S11>/Product7'
     *  Sum: '<S286>/Sum'
     */
    bpIndices_3[0U] = plook_binx(rtb_Lw_idx_1, &aeroParams.machBreakpoints_na[0],
      9U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_aw[0U] = rtb_Sum1_nc_idx_0;
    bpIndices_3[1U] = plook_binx(rtb_Gain_nu, &aeroParams.aoaBreakpoints_deg[0],
      2U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_aw[1U] = rtb_Sum1_nc_idx_0;
    bpIndices_3[2U] = plook_binx(autocodePlant_B->Backlash[2] * rtb_Sign1_e,
      &aeroParams.controlBreakpoints_deg[0], 4U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_aw[2U] = rtb_Sum1_nc_idx_0;
    rtb_Sign1_l = intrp3d_l_pw(bpIndices_3, rtb_Sum_aw, &aeroParams.CaFin_na[0],
      rtCP__CALookupTable_dimSizes_e);

    /* Product: '<S11>/Product' */
    rtb_Sum_b4 = rtb_Sum1_hj_idx_0 * rtb_UnaryMinus1_o;

    /* UnaryMinus: '<S11>/Unary Minus' incorporates:
     *  Constant: '<S11>/   '
     *  Product: '<S11>/Product1'
     */
    rtb_Sign1_l = -(rtb_Sign1_l * rtb_Sum_b4 * vehicleParams.area_m2);

    /* Lookup_n-D: '<S11>/CN Lookup Table' incorporates:
     *  Gain: '<S65>/Gain'
     *  Product: '<S11>/Product5'
     *  Sum: '<S286>/Sum'
     */
    bpIndices_4[0U] = plook_binx(rtb_Lw_idx_1, &aeroParams.machBreakpoints_na[0],
      9U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_mu[0U] = rtb_Sum1_nc_idx_0;
    bpIndices_4[1U] = plook_binx(rtb_Gain_nu, &aeroParams.aoaBreakpoints_deg[0],
      2U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_mu[1U] = rtb_Sum1_nc_idx_0;
    bpIndices_4[2U] = plook_binx(autocodePlant_B->Backlash[2] * rtb_Sign1_e,
      &aeroParams.controlBreakpoints_deg[0], 4U, &rtb_Sum1_nc_idx_0);
    rtb_Sum_mu[2U] = rtb_Sum1_nc_idx_0;
    rtb_Lw_idx_1 = intrp3d_l_pw(bpIndices_4, rtb_Sum_mu, &aeroParams.CnFin_na[0],
      rtCP__CNLookupTable_dimSizes_e);

    /* UnaryMinus: '<S11>/Unary Minus1' incorporates:
     *  Constant: '<S11>/ '
     *  Product: '<S11>/Product2'
     */
    rtb_UnaryMinus1_e = -(rtb_Lw_idx_1 * rtb_Sum_b4 * vehicleParams.area_m2);

    /* Sum: '<S11>/Sum1' incorporates:
     *  Product: '<S11>/Product3'
     *  Product: '<S11>/Product4'
     *  SignalConversion generated from: '<S11>/Dot Product2'
     */
    rtb_Sum1_hj_idx_0 = rtb_UnaryMinus1_e * autocodePlant_B->Sum_o * rtb_Sign1_e
      + rtb_Sign1_l * autocodePlant_B->Sum_a;
    rtb_Sum1_hj_idx_1 = rtb_UnaryMinus1_e * autocodePlant_B->Sum_er *
      rtb_Sign1_e + rtb_Sign1_l * autocodePlant_B->Sum_ia;
    rtb_UnaryMinus1_e = rtb_UnaryMinus1_e * autocodePlant_B->Sum_g * rtb_Sign1_e
      + rtb_Sign1_l * autocodePlant_B->Sum_bt;

    /* Sum: '<S62>/Sum' incorporates:
     *  Product: '<S62>/Element Product'
     */
    rtb_Sum_pz[0] = autocodePlant_B->Subtract1_k[1] * rtb_UnaryMinus1_e -
      rtb_Sum1_hj_idx_1 * autocodePlant_B->Subtract1_k[2];
    rtb_Sum_pz[1] = rtb_Sum1_hj_idx_0 * autocodePlant_B->Subtract1_k[2] -
      autocodePlant_B->Subtract1_k[0] * rtb_UnaryMinus1_e;
    rtb_Sum_pz[2] = autocodePlant_B->Subtract1_k[0] * rtb_Sum1_hj_idx_1 -
      rtb_Sum1_hj_idx_0 * autocodePlant_B->Subtract1_k[1];
    if (tmp) {
      /* Sum: '<S12>/Subtract1' incorporates:
       *  Constant: '<S12>/Constant4'
       *  Constant: '<S12>/Constant5'
       *  Constant: '<S3>/Constant1'
       *  Product: '<S12>/Product6'
       */
      autocodePlant_B->Subtract1_j[0] = vehicleParams.cg_m -
        aeroParams.finCP4_m[0];
      autocodePlant_B->Subtract1_j[1] = vehicleParams.cg_m * 0.0 -
        aeroParams.finCP4_m[1];
      autocodePlant_B->Subtract1_j[2] = vehicleParams.cg_m * 0.0 -
        aeroParams.finCP4_m[2];
    }

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S81>/Element Product'
     *  Sum: '<S81>/Sum'
     */
    Sum_bx_tmp = (rtb_Product_ab[1] * autocodePlant_B->Subtract1_j[2] -
                  autocodePlant_B->Subtract1_j[1] * rtb_Product_ab[2]) +
      rtb_VectorConcatenate[0];
    rtb_Sum_aw[0] = Sum_bx_tmp;

    /* DotProduct: '<S12>/Dot Product4' */
    rtb_Sign1_l = Sum_bx_tmp * Sum_bx_tmp;

    /* Sum: '<S12>/Sum' incorporates:
     *  Product: '<S81>/Element Product'
     *  Sum: '<S81>/Sum'
     */
    Sum_a_tmp = (autocodePlant_B->Subtract1_j[0] * rtb_Product_ab[2] -
                 rtb_Product_ab[0] * autocodePlant_B->Subtract1_j[2]) +
      rtb_VectorConcatenate[1];
    Sum_bx_tmp = (rtb_Product_ab[0] * autocodePlant_B->Subtract1_j[1] -
                  autocodePlant_B->Subtract1_j[0] * rtb_Product_ab[1]) +
      rtb_VectorConcatenate[2];

    /* Switch: '<S78>/Switch' incorporates:
     *  Constant: '<S78>/Constant4'
     *  Constant: '<S78>/Constant5'
     */
    if (rtb_UnitConversion_e >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S12>/Dot Product4' incorporates:
     *  DotProduct: '<S12>/Dot Product3'
     */
    rtb_Abs1 = (Sum_a_tmp * Sum_a_tmp + rtb_Sign1_l) + Sum_bx_tmp * Sum_bx_tmp;

    /* Product: '<S12>/Divide1' incorporates:
     *  DotProduct: '<S12>/Dot Product4'
     *  Product: '<S78>/Product'
     *  Sqrt: '<S12>/Sqrt1'
     *  Switch: '<S78>/Switch'
     */
    rtb_Sum_b4 = sqrt(rtb_Abs1) / ((real_T)i * rtb_Gain_n);
    if (tmp) {
      /* Angle2Quat: '<S12>/Rotation Angles to Quaternions' incorporates:
       *  Constant: '<S12>/liftDirection_na1'
       */
      rtb_UnitDelay2_idx_3 = cos(aeroParams.finAngles4_rad[2] / 2.0);
      rtb_UnitDelay2_idx_1 = cos(aeroParams.finAngles4_rad[1] / 2.0);
      rtb_UnaryMinus_n = cos(aeroParams.finAngles4_rad[0] / 2.0);
      rtb_Sum1_nc_idx_0 = sin(aeroParams.finAngles4_rad[2] / 2.0);
      rtb_FlatEarthtoLLA_o1_idx_0 = sin(aeroParams.finAngles4_rad[1] / 2.0);
      rtb_Switch_d_idx_1 = sin(aeroParams.finAngles4_rad[0] / 2.0);
      rtb_DiscreteTransferFcn2 = rtb_UnaryMinus_n * rtb_UnitDelay2_idx_1;
      rtb_Switch_d_idx_2 = rtb_Switch_d_idx_1 * rtb_FlatEarthtoLLA_o1_idx_0;
      rtb_UnitDelay2_idx_0 = rtb_DiscreteTransferFcn2 * rtb_UnitDelay2_idx_3 -
        rtb_Switch_d_idx_2 * rtb_Sum1_nc_idx_0;
      rtb_UnaryMinus_n *= rtb_FlatEarthtoLLA_o1_idx_0;
      rtb_Switch_d_idx_1 *= rtb_UnitDelay2_idx_1;
      rtb_UnitDelay2_idx_1 = rtb_UnaryMinus_n * rtb_Sum1_nc_idx_0 +
        rtb_Switch_d_idx_1 * rtb_UnitDelay2_idx_3;
      rtb_Switch_d_idx_1 = rtb_UnaryMinus_n * rtb_UnitDelay2_idx_3 -
        rtb_Switch_d_idx_1 * rtb_Sum1_nc_idx_0;
      rtb_UnitDelay2_idx_3 = rtb_DiscreteTransferFcn2 * rtb_Sum1_nc_idx_0 +
        rtb_Switch_d_idx_2 * rtb_UnitDelay2_idx_3;

      /* Sqrt: '<S96>/sqrt' incorporates:
       *  Product: '<S97>/Product'
       *  Product: '<S97>/Product1'
       *  Product: '<S97>/Product2'
       *  Product: '<S97>/Product3'
       *  Sqrt: '<S90>/sqrt'
       *  Sum: '<S97>/Sum'
       */
      rtb_Sum1_nc_idx_0 = sqrt(((rtb_UnitDelay2_idx_0 * rtb_UnitDelay2_idx_0 +
        rtb_UnitDelay2_idx_1 * rtb_UnitDelay2_idx_1) + rtb_Switch_d_idx_1 *
        rtb_Switch_d_idx_1) + rtb_UnitDelay2_idx_3 * rtb_UnitDelay2_idx_3);

      /* Product: '<S92>/Product2' incorporates:
       *  Sqrt: '<S96>/sqrt'
       */
      rtb_DiscreteTransferFcn1 = rtb_Switch_d_idx_1 / rtb_Sum1_nc_idx_0;

      /* Product: '<S92>/Product3' incorporates:
       *  Sqrt: '<S96>/sqrt'
       */
      rtb_DiscreteTransferFcn2 = rtb_UnitDelay2_idx_3 / rtb_Sum1_nc_idx_0;

      /* Product: '<S92>/Product1' incorporates:
       *  Sqrt: '<S96>/sqrt'
       */
      rtb_UnitDelay2_idx_3 = rtb_UnitDelay2_idx_1 / rtb_Sum1_nc_idx_0;

      /* Product: '<S92>/Product' incorporates:
       *  Product: '<S86>/Product'
       *  Sqrt: '<S96>/sqrt'
       */
      rtb_Sum1_nc_idx_0 = rtb_UnitDelay2_idx_0 / rtb_Sum1_nc_idx_0;

      /* Product: '<S93>/Product7' incorporates:
       *  Product: '<S94>/Product7'
       */
      rtb_Lw_idx_1 = rtb_DiscreteTransferFcn2 * rtb_DiscreteTransferFcn2;

      /* Product: '<S93>/Product' incorporates:
       *  Product: '<S94>/Product'
       */
      rtb_FlatEarthtoLLA_o1_idx_1 = rtb_UnitDelay2_idx_3 *
        rtb_DiscreteTransferFcn1;

      /* Product: '<S93>/Product1' incorporates:
       *  Product: '<S92>/Product'
       *  Product: '<S94>/Product1'
       */
      rtb_Switch_d_idx_0 = rtb_Sum1_nc_idx_0 * rtb_DiscreteTransferFcn2;

      /* Product: '<S93>/Product3' incorporates:
       *  Product: '<S95>/Product'
       */
      rtb_Switch_d_idx_1 = rtb_UnitDelay2_idx_3 * rtb_DiscreteTransferFcn2;

      /* Product: '<S93>/Product2' incorporates:
       *  Product: '<S92>/Product'
       *  Product: '<S95>/Product1'
       */
      rtb_UnaryMinus_n = rtb_Sum1_nc_idx_0 * rtb_DiscreteTransferFcn1;

      /* Product: '<S93>/Product6' incorporates:
       *  Product: '<S95>/Product7'
       */
      rtb_Switch_d_idx_2 = rtb_DiscreteTransferFcn1 * rtb_DiscreteTransferFcn1;

      /* Gain: '<S93>/Gain2' incorporates:
       *  Constant: '<S93>/Constant'
       *  Gain: '<S87>/Gain2'
       *  Product: '<S93>/Product6'
       *  Product: '<S93>/Product7'
       *  Sum: '<S93>/Sum3'
       */
      rtb_Sign1_l = ((0.5 - rtb_Switch_d_idx_2) - rtb_Lw_idx_1) * 2.0;

      /* Product: '<S93>/Product4' incorporates:
       *  Constant: '<S12>/axialDirection_na'
       *  Gain: '<S93>/Gain'
       *  Product: '<S87>/Product4'
       *  Product: '<S93>/Product'
       *  Product: '<S93>/Product1'
       *  Sum: '<S93>/Sum1'
       */
      rtb_UnitDelay2_idx_0 = (rtb_FlatEarthtoLLA_o1_idx_1 + rtb_Switch_d_idx_0) *
        2.0 * 0.0;

      /* Gain: '<S93>/Gain1' incorporates:
       *  Gain: '<S87>/Gain1'
       *  Product: '<S93>/Product2'
       *  Product: '<S93>/Product3'
       *  Sum: '<S93>/Sum2'
       */
      rtb_UnitDelay2_idx_1 = (rtb_Switch_d_idx_1 - rtb_UnaryMinus_n) * 2.0;

      /* Sum: '<S93>/Sum' incorporates:
       *  Constant: '<S12>/axialDirection_na'
       *  Gain: '<S93>/Gain1'
       *  Gain: '<S93>/Gain2'
       *  Product: '<S93>/Product4'
       *  Product: '<S93>/Product5'
       */
      autocodePlant_B->Sum_d = (rtb_Sign1_l + rtb_UnitDelay2_idx_0) +
        rtb_UnitDelay2_idx_1 * 0.0;

      /* Product: '<S94>/Product3' incorporates:
       *  Product: '<S95>/Product3'
       */
      rtb_DiscreteTransferFcn2 *= rtb_DiscreteTransferFcn1;

      /* Product: '<S94>/Product2' incorporates:
       *  Product: '<S92>/Product'
       *  Product: '<S95>/Product2'
       */
      rtb_Sum1_nc_idx_0 *= rtb_UnitDelay2_idx_3;

      /* Sum: '<S94>/Sum3' incorporates:
       *  Constant: '<S94>/Constant'
       *  Product: '<S94>/Product6'
       *  Sum: '<S95>/Sum3'
       */
      rtb_FlatEarthtoLLA_o1_idx_0 = 0.5 - rtb_UnitDelay2_idx_3 *
        rtb_UnitDelay2_idx_3;

      /* Product: '<S94>/Product8' incorporates:
       *  Constant: '<S12>/axialDirection_na'
       *  Gain: '<S94>/Gain2'
       *  Product: '<S88>/Product8'
       *  Sum: '<S94>/Sum3'
       */
      rtb_UnitDelay2_idx_3 = (rtb_FlatEarthtoLLA_o1_idx_0 - rtb_Lw_idx_1) * 2.0 *
        0.0;

      /* Gain: '<S94>/Gain' incorporates:
       *  Gain: '<S88>/Gain'
       *  Sum: '<S94>/Sum1'
       */
      rtb_FlatEarthtoLLA_o1_idx_1 = (rtb_FlatEarthtoLLA_o1_idx_1 -
        rtb_Switch_d_idx_0) * 2.0;

      /* Gain: '<S94>/Gain1' incorporates:
       *  Gain: '<S88>/Gain1'
       *  Product: '<S94>/Product2'
       *  Product: '<S94>/Product3'
       *  Sum: '<S94>/Sum2'
       */
      rtb_Switch_d_idx_0 = (rtb_Sum1_nc_idx_0 + rtb_DiscreteTransferFcn2) * 2.0;

      /* Sum: '<S94>/Sum' incorporates:
       *  Constant: '<S12>/axialDirection_na'
       *  Gain: '<S94>/Gain'
       *  Gain: '<S94>/Gain1'
       *  Product: '<S94>/Product5'
       *  Product: '<S94>/Product8'
       */
      autocodePlant_B->Sum_o3 = (rtb_UnitDelay2_idx_3 +
        rtb_FlatEarthtoLLA_o1_idx_1) + rtb_Switch_d_idx_0 * 0.0;

      /* Gain: '<S95>/Gain' incorporates:
       *  Gain: '<S89>/Gain'
       *  Sum: '<S95>/Sum1'
       */
      rtb_Switch_d_idx_1 = (rtb_Switch_d_idx_1 + rtb_UnaryMinus_n) * 2.0;

      /* Product: '<S95>/Product5' incorporates:
       *  Constant: '<S12>/axialDirection_na'
       *  Gain: '<S95>/Gain1'
       *  Product: '<S89>/Product5'
       *  Sum: '<S95>/Sum2'
       */
      rtb_Sum1_nc_idx_0 = (rtb_DiscreteTransferFcn2 - rtb_Sum1_nc_idx_0) * 2.0 *
        0.0;

      /* Gain: '<S95>/Gain2' incorporates:
       *  Gain: '<S89>/Gain2'
       *  Sum: '<S95>/Sum3'
       */
      rtb_DiscreteTransferFcn2 = (rtb_FlatEarthtoLLA_o1_idx_0 -
        rtb_Switch_d_idx_2) * 2.0;

      /* Sum: '<S95>/Sum' incorporates:
       *  Constant: '<S12>/axialDirection_na'
       *  Gain: '<S95>/Gain'
       *  Gain: '<S95>/Gain2'
       *  Product: '<S95>/Product5'
       *  Product: '<S95>/Product8'
       */
      autocodePlant_B->Sum_j = (rtb_Sum1_nc_idx_0 + rtb_Switch_d_idx_1) +
        rtb_DiscreteTransferFcn2 * 0.0;

      /* Sum: '<S87>/Sum' incorporates:
       *  Constant: '<S12>/normalDirection_na'
       *  Product: '<S87>/Product8'
       */
      autocodePlant_B->Sum_dm = (rtb_Sign1_l * 0.0 + rtb_UnitDelay2_idx_0) +
        rtb_UnitDelay2_idx_1;

      /* Sum: '<S88>/Sum' incorporates:
       *  Constant: '<S12>/normalDirection_na'
       *  Product: '<S88>/Product4'
       */
      autocodePlant_B->Sum_b4 = (rtb_FlatEarthtoLLA_o1_idx_1 * 0.0 +
        rtb_UnitDelay2_idx_3) + rtb_Switch_d_idx_0;

      /* Sum: '<S89>/Sum' incorporates:
       *  Constant: '<S12>/normalDirection_na'
       *  Product: '<S89>/Product4'
       */
      autocodePlant_B->Sum_ln = (rtb_Switch_d_idx_1 * 0.0 + rtb_Sum1_nc_idx_0) +
        rtb_DiscreteTransferFcn2;

      /* Sum: '<S12>/Sum2' */
      autocodePlant_B->Sum2_a[0] = autocodePlant_B->Sum_dm +
        autocodePlant_B->Sum_d;
      autocodePlant_B->Sum2_a[1] = autocodePlant_B->Sum_b4 +
        autocodePlant_B->Sum_o3;
      autocodePlant_B->Sum2_a[2] = autocodePlant_B->Sum_ln +
        autocodePlant_B->Sum_j;
    }

    /* Product: '<S12>/Product8' incorporates:
     *  Sum: '<S12>/Sum'
     */
    rtb_Sign1_l = rtb_Sum_aw[0] * autocodePlant_B->Sum2_a[0];
    rtb_UnitDelay2_idx_3 = Sum_a_tmp * autocodePlant_B->Sum2_a[1];
    rtb_Sum1_nc_idx_0 = Sum_bx_tmp * autocodePlant_B->Sum2_a[2];

    /* DotProduct: '<S12>/Dot Product1' */
    rtb_DiscreteTransferFcn2 = (rtb_Sign1_l * rtb_Sign1_l + rtb_UnitDelay2_idx_3
      * rtb_UnitDelay2_idx_3) + rtb_Sum1_nc_idx_0 * rtb_Sum1_nc_idx_0;

    /* Switch: '<S80>/Switch' incorporates:
     *  Constant: '<S80>/Constant4'
     *  Constant: '<S80>/Constant5'
     *  DotProduct: '<S12>/Dot Product1'
     */
    if (rtb_DiscreteTransferFcn2 >= 0.0) {
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
    rtb_UnaryMinus_n = ((autocodePlant_B->Sum_d * rtb_Sign1_l +
                         autocodePlant_B->Sum_o3 * rtb_UnitDelay2_idx_3) +
                        autocodePlant_B->Sum_j * rtb_Sum1_nc_idx_0) / sqrt
      ((real_T)i * fmax(1.0E-6, rtb_DiscreteTransferFcn2));

    /* Saturate: '<S12>/Saturation' */
    if (rtb_UnaryMinus_n > 1.0) {
      rtb_UnaryMinus_n = 1.0;
    } else if (rtb_UnaryMinus_n < -1.0) {
      rtb_UnaryMinus_n = -1.0;
    }

    /* Gain: '<S85>/Gain' incorporates:
     *  Saturate: '<S12>/Saturation'
     *  Trigonometry: '<S12>/Acos'
     */
    rtb_UnitDelay2_idx_3 = 57.29577951308232 * acos(rtb_UnaryMinus_n);

    /* DotProduct: '<S12>/Dot Product2' incorporates:
     *  SignalConversion generated from: '<S12>/Dot Product2'
     *  Sum: '<S12>/Sum'
     */
    rtb_Sign1_l = (autocodePlant_B->Sum_dm * rtb_Sum_aw[0] +
                   autocodePlant_B->Sum_b4 * Sum_a_tmp) +
      autocodePlant_B->Sum_ln * Sum_bx_tmp;

    /* Switch: '<S79>/Switch' incorporates:
     *  Constant: '<S79>/Constant4'
     *  Constant: '<S79>/Constant5'
     *  DotProduct: '<S12>/Dot Product2'
     */
    if (rtb_Sign1_l >= 0.0) {
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
    rtb_Sum1_nc_idx_0 = (real_T)i * fmax(1.0E-6, fabs(rtb_Sign1_l));

    /* Signum: '<S12>/Sign1' */
    if (rtIsNaN(rtb_Sum1_nc_idx_0)) {
      rtb_Sign1_l = (rtNaN);
    } else if (rtb_Sum1_nc_idx_0 < 0.0) {
      rtb_Sign1_l = -1.0;
    } else {
      rtb_Sign1_l = (rtb_Sum1_nc_idx_0 > 0.0);
    }

    /* End of Signum: '<S12>/Sign1' */

    /* Lookup_n-D: '<S12>/CA Lookup Table' incorporates:
     *  Gain: '<S85>/Gain'
     *  Product: '<S12>/Product7'
     *  Sum: '<S288>/Sum'
     */
    bpIndices_5[0U] = plook_binx(rtb_Sum_b4, &aeroParams.machBreakpoints_na[0],
      9U, &rtb_Sum1_nc_idx_0);
    rtb_Product6_kk[0U] = rtb_Sum1_nc_idx_0;
    bpIndices_5[1U] = plook_binx(rtb_UnitDelay2_idx_3,
      &aeroParams.aoaBreakpoints_deg[0], 2U, &rtb_Sum1_nc_idx_0);
    rtb_Product6_kk[1U] = rtb_Sum1_nc_idx_0;
    bpIndices_5[2U] = plook_binx(autocodePlant_B->Backlash[3] * rtb_Sign1_l,
      &aeroParams.controlBreakpoints_deg[0], 4U, &rtb_Sum1_nc_idx_0);
    rtb_Product6_kk[2U] = rtb_Sum1_nc_idx_0;
    rtb_Lw_idx_1 = intrp3d_l_pw(bpIndices_5, rtb_Product6_kk,
      &aeroParams.CaFin_na[0], rtCP__CALookupTable_dimSizes_a);

    /* Product: '<S12>/Product' */
    rtb_UnitDelay2_idx_1 = rtb_Abs1 * rtb_UnaryMinus1_o;

    /* UnaryMinus: '<S12>/Unary Minus' incorporates:
     *  Constant: '<S12>/   '
     *  Product: '<S12>/Product1'
     */
    rtb_UnitDelay2_idx_0 = -(rtb_Lw_idx_1 * rtb_UnitDelay2_idx_1 *
      vehicleParams.area_m2);

    /* Lookup_n-D: '<S12>/CN Lookup Table' incorporates:
     *  Gain: '<S85>/Gain'
     *  Product: '<S12>/Product5'
     *  Sum: '<S288>/Sum'
     */
    bpIndices_6[0U] = plook_binx(rtb_Sum_b4, &aeroParams.machBreakpoints_na[0],
      9U, &rtb_Sum1_nc_idx_0);
    rtb_MathFunction[0U] = rtb_Sum1_nc_idx_0;
    bpIndices_6[1U] = plook_binx(rtb_UnitDelay2_idx_3,
      &aeroParams.aoaBreakpoints_deg[0], 2U, &rtb_Sum1_nc_idx_0);
    rtb_MathFunction[1U] = rtb_Sum1_nc_idx_0;
    bpIndices_6[2U] = plook_binx(autocodePlant_B->Backlash[3] * rtb_Sign1_l,
      &aeroParams.controlBreakpoints_deg[0], 4U, &rtb_Sum1_nc_idx_0);
    rtb_MathFunction[2U] = rtb_Sum1_nc_idx_0;
    rtb_Sum_b4 = intrp3d_l_pw(bpIndices_6, rtb_MathFunction,
      &aeroParams.CnFin_na[0], rtCP__CNLookupTable_dimSizes_h);

    /* UnaryMinus: '<S12>/Unary Minus1' incorporates:
     *  Constant: '<S12>/ '
     *  Product: '<S12>/Product2'
     */
    rtb_Sum_b4 = -(rtb_Sum_b4 * rtb_UnitDelay2_idx_1 * vehicleParams.area_m2);

    /* Sum: '<S12>/Sum1' incorporates:
     *  Product: '<S12>/Product3'
     *  Product: '<S12>/Product4'
     *  SignalConversion generated from: '<S12>/Dot Product2'
     */
    rtb_Sum1_nc_idx_0 = rtb_Sum_b4 * autocodePlant_B->Sum_dm * rtb_Sign1_l +
      rtb_UnitDelay2_idx_0 * autocodePlant_B->Sum_d;
    rtb_DiscreteTransferFcn2 = rtb_Sum_b4 * autocodePlant_B->Sum_b4 *
      rtb_Sign1_l + rtb_UnitDelay2_idx_0 * autocodePlant_B->Sum_o3;
    rtb_UnitDelay2_idx_0 = rtb_Sum_b4 * autocodePlant_B->Sum_ln * rtb_Sign1_l +
      rtb_UnitDelay2_idx_0 * autocodePlant_B->Sum_j;

    /* Sum: '<S82>/Sum' incorporates:
     *  Product: '<S82>/Element Product'
     */
    rtb_Sum_mu[0] = autocodePlant_B->Subtract1_j[1] * rtb_UnitDelay2_idx_0 -
      rtb_DiscreteTransferFcn2 * autocodePlant_B->Subtract1_j[2];

    /* Product: '<S8>/Product6' incorporates:
     *  Constant: '<S8>/Constant3'
     *  DotProduct: '<S8>/Dot Product4'
     */
    rtb_Switch_d_idx_0 = rtb_VectorConcatenate[0] * 0.0;

    /* Sum: '<S82>/Sum' incorporates:
     *  Product: '<S82>/Element Product'
     */
    rtb_Sum_mu[1] = rtb_Sum1_nc_idx_0 * autocodePlant_B->Subtract1_j[2] -
      autocodePlant_B->Subtract1_j[0] * rtb_UnitDelay2_idx_0;
    rtb_Sum_mu[2] = autocodePlant_B->Subtract1_j[0] * rtb_DiscreteTransferFcn2 -
      rtb_Sum1_nc_idx_0 * autocodePlant_B->Subtract1_j[1];

    /* DotProduct: '<S8>/Dot Product1' incorporates:
     *  DotProduct: '<S8>/Dot Product4'
     *  Math: '<S16>/Math Function'
     */
    rtb_FlatEarthtoLLA_o1_idx_0 = rtb_VectorConcatenate[1] *
      rtb_VectorConcatenate[1];
    rtb_FlatEarthtoLLA_o1_idx_1 = rtb_VectorConcatenate[2] *
      rtb_VectorConcatenate[2];
    rtb_Sum_b4 = (rtb_VectorConcatenate[0] * rtb_VectorConcatenate[0] +
                  rtb_FlatEarthtoLLA_o1_idx_0) + rtb_FlatEarthtoLLA_o1_idx_1;

    /* Switch: '<S14>/Switch' incorporates:
     *  Constant: '<S14>/Constant4'
     *  Constant: '<S14>/Constant5'
     */
    if (rtb_UnitConversion_e >= 0.0) {
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
    rtb_UnitDelay2_idx_1 = sqrt(rtb_Sum_b4) / ((real_T)i * rtb_Gain_n);

    /* Switch: '<S13>/Switch' incorporates:
     *  Constant: '<S13>/Constant4'
     *  Constant: '<S13>/Constant5'
     *  DotProduct: '<S8>/Dot Product1'
     */
    if (rtb_Sum_b4 >= 0.0) {
      i = 1;
    } else {
      i = -1;
    }

    /* DotProduct: '<S8>/Dot Product' incorporates:
     *  DotProduct: '<S8>/Dot Product4'
     *  Product: '<S16>/Product'
     *  Switch: '<S16>/Switch'
     */
    rtb_Switch_d_idx_1 = 0.0 * rtb_VectorConcatenate[1];
    rtb_Switch_d_idx_2 = 0.0 * rtb_VectorConcatenate[2];

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
    rtb_UnaryMinus_n = ((rtb_Switch_d_idx_1 + rtb_VectorConcatenate[0]) +
                        rtb_Switch_d_idx_2) / sqrt((real_T)i * fmax(1.0E-6,
      rtb_Sum_b4));

    /* Saturate: '<S8>/Saturation' */
    if (rtb_UnaryMinus_n > 1.0) {
      rtb_UnaryMinus_n = 1.0;
    } else if (rtb_UnaryMinus_n < -1.0) {
      rtb_UnaryMinus_n = -1.0;
    }

    /* Gain: '<S17>/Gain' incorporates:
     *  Saturate: '<S8>/Saturation'
     *  Trigonometry: '<S8>/Acos'
     */
    rtb_Gain_n = 57.29577951308232 * acos(rtb_UnaryMinus_n);

    /* Product: '<S8>/Product' incorporates:
     *  DotProduct: '<S8>/Dot Product3'
     */
    rtb_Lw_idx_1 = rtb_Sum_b4 * rtb_UnaryMinus1_o;

    /* UnaryMinus: '<S8>/Unary Minus' incorporates:
     *  Constant: '<S8>/   '
     *  FlatEarth2LLA: '<S173>/Flat Earth to LLA'
     *  Gain: '<S17>/Gain'
     *  Lookup_n-D: '<S8>/CA Lookup Table'
     *  Product: '<S8>/Product1'
     */
    rtb_UnaryMinus_n = -(look2_binlxpw(rtb_UnitDelay2_idx_1, rtb_Gain_n,
      &aeroParams.machBreakpoints_na[0], &aeroParams.aoaBreakpoints_deg[0],
      &aeroParams.CaBase_na[0], rtCP__CALookupTable_maxIndex_j, 10U) *
                         rtb_Lw_idx_1 * vehicleParams.area_m2);

    /* UnaryMinus: '<S8>/Unary Minus1' incorporates:
     *  Constant: '<S8>/ '
     *  FlatEarth2LLA: '<S173>/Flat Earth to LLA'
     *  Gain: '<S17>/Gain'
     *  Lookup_n-D: '<S8>/CN Lookup Table'
     *  Product: '<S8>/Product2'
     */
    rtb_UnaryMinus1_o = -(look2_binlxpw(rtb_UnitDelay2_idx_1, rtb_Gain_n,
      &aeroParams.machBreakpoints_na[0], &aeroParams.aoaBreakpoints_deg[0],
      &aeroParams.CnBase_na[0], rtCP__CNLookupTable_maxIndex_a, 10U) *
                          rtb_Lw_idx_1 * vehicleParams.area_m2);

    /* Math: '<S16>/Math Function1' incorporates:
     *  Math: '<S16>/Math Function'
     *  Sum: '<S16>/Sum of Elements'
     *
     * About '<S16>/Math Function1':
     *  Operator: sqrt
     */
    rtb_Sum_b4 = sqrt((rtb_Switch_d_idx_0 * rtb_Switch_d_idx_0 +
                       rtb_FlatEarthtoLLA_o1_idx_0) +
                      rtb_FlatEarthtoLLA_o1_idx_1);

    /* Switch: '<S16>/Switch' incorporates:
     *  Constant: '<S16>/Constant'
     *  DotProduct: '<S8>/Dot Product4'
     *  Product: '<S16>/Product'
     *  Product: '<S8>/Product6'
     */
    if (rtb_Sum_b4 > 1.0E-6) {
      rtb_Switch_d_idx_1 = rtb_VectorConcatenate[1];
      rtb_Switch_d_idx_2 = rtb_VectorConcatenate[2];
    } else {
      rtb_Switch_d_idx_0 *= 0.0;
      rtb_Sum_b4 = 1.0;
    }

    /* Sum: '<S8>/Sum' incorporates:
     *  Constant: '<S3>/Constant'
     *  FlatEarth2LLA: '<S173>/Flat Earth to LLA'
     *  Gain: '<S17>/Gain'
     *  Lookup_n-D: '<S8>/CP Lookup Table'
     */
    rtb_UnitDelay2_idx_1 = vehicleParams.cg_m - look2_binlcpw
      (rtb_UnitDelay2_idx_1, rtb_Gain_n, &aeroParams.machBreakpoints_na[0],
       &aeroParams.aoaBreakpoints_deg[0], &aeroParams.CpBase_m[0],
       rtCP__CPLookupTable_maxIndex, 10U);

    /* Sum: '<S8>/Sum1' incorporates:
     *  Product: '<S16>/Divide'
     *  Product: '<S8>/Product3'
     *  Product: '<S8>/Product4'
     */
    rtb_Product6_kk[0] = rtb_Switch_d_idx_0 / rtb_Sum_b4 * rtb_UnaryMinus1_o +
      rtb_UnaryMinus_n;

    /* Product: '<S8>/Product3' incorporates:
     *  Constant: '<S8>/Constant'
     */
    rtb_UnaryMinus_n *= 0.0;

    /* Sum: '<S8>/Sum1' incorporates:
     *  Product: '<S16>/Divide'
     *  Product: '<S8>/Product3'
     *  Product: '<S8>/Product4'
     */
    rtb_Product6_kk[1] = rtb_Switch_d_idx_1 / rtb_Sum_b4 * rtb_UnaryMinus1_o +
      rtb_UnaryMinus_n;

    /* Product: '<S8>/Product5' incorporates:
     *  Constant: '<S8>/Constant2'
     */
    rtb_Switch_d_idx_1 = rtb_UnitDelay2_idx_1 * 0.0;

    /* Sum: '<S8>/Sum1' incorporates:
     *  Product: '<S16>/Divide'
     *  Product: '<S8>/Product4'
     */
    rtb_Product6_kk[2] = rtb_Switch_d_idx_2 / rtb_Sum_b4 * rtb_UnaryMinus1_o +
      rtb_UnaryMinus_n;

    /* Product: '<S15>/Element Product' incorporates:
     *  Product: '<S8>/Product5'
     */
    rtb_Sum_b4 = rtb_Product6_kk[0] * rtb_Switch_d_idx_1;

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_n = rtb_Switch_d_idx_1 * rtb_Product6_kk[2] -
      rtb_Product6_kk[1] * rtb_Switch_d_idx_1;
    rtb_MathFunction[0] = rtb_UnaryMinus_n;

    /* Sum: '<S3>/Add' */
    rtb_Delay[0] = (((rtb_Sum_j[0] + rtb_UnaryMinus_o3) + rtb_Sum_pz[0]) +
                    rtb_Sum_mu[0]) + rtb_UnaryMinus_n;
    rtb_Delay[3] = (((rtb_Sum1_gf[0] + rtb_Product4_a) + rtb_Sum1_hj_idx_0) +
                    rtb_Sum1_nc_idx_0) + rtb_Product6_kk[0];

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_n = rtb_Sum_b4 - rtb_UnitDelay2_idx_1 * rtb_Product6_kk[2];
    rtb_MathFunction[1] = rtb_UnaryMinus_n;

    /* Sum: '<S3>/Add' */
    rtb_Delay[1] = (((rtb_Sum_j[1] + rtb_UnaryMinus1_c) + rtb_Sum_pz[1]) +
                    rtb_Sum_mu[1]) + rtb_UnaryMinus_n;
    rtb_Delay[4] = (((rtb_Sum1_gf[1] + rtb_Sum1_hwh_idx_1) + rtb_Sum1_hj_idx_1)
                    + rtb_DiscreteTransferFcn2) + rtb_Product6_kk[1];

    /* Sum: '<S15>/Sum' incorporates:
     *  Product: '<S15>/Element Product'
     *  Product: '<S8>/Product5'
     */
    rtb_UnaryMinus_n = rtb_UnitDelay2_idx_1 * rtb_Product6_kk[1] - rtb_Sum_b4;

    /* Sum: '<S3>/Add' */
    rtb_Delay[2] = (((rtb_Sum_j[2] + rtb_Sum_a_idx_2) + rtb_Sum_pz[2]) +
                    rtb_Sum_mu[2]) + rtb_UnaryMinus_n;
    rtb_Delay[5] = (((rtb_Sum1_gf[2] + rtb_Product8_ne) + rtb_UnaryMinus1_e) +
                    rtb_UnitDelay2_idx_0) + rtb_Product6_kk[2];

    /* DotProduct: '<S282>/Dot Product' incorporates:
     *  Sum: '<S115>/Sum'
     */
    rtb_UnaryMinus1_o = ((rtb_q_na_idx_0 * rtb_q_na_idx_0 + rtb_q_na_idx_1 *
                          rtb_q_na_idx_1) + rtb_q_na_idx_2 * rtb_q_na_idx_2) +
      rtb_q_na_idx_3 * rtb_q_na_idx_3;

    /* Switch: '<S282>/Switch' incorporates:
     *  Constant: '<S282>/Constant'
     *  DotProduct: '<S282>/Dot Product'
     */
    if (rtb_UnaryMinus1_o > 1.0E-6) {
      rtb_Switch_d_idx_0 = rtb_q_na_idx_0;
      rtb_Switch_d_idx_1 = rtb_q_na_idx_1;
      rtb_Switch_d_idx_2 = rtb_q_na_idx_2;
      rtb_Sum_b4 = rtb_q_na_idx_3;
    } else {
      rtb_Switch_d_idx_0 = 1.0;
      rtb_Switch_d_idx_1 = 0.0;
      rtb_Switch_d_idx_2 = 0.0;
      rtb_Sum_b4 = 0.0;
    }

    /* End of Switch: '<S282>/Switch' */
    if (tmp) {
      /* Sum: '<S206>/Sum' incorporates:
       *  Constant: '<S173>/decimal year'
       *  Constant: '<S206>/epoch'
       */
      rtb_Sum_gx = envParams.date_y - 2025.0;

      /* RelationalOperator: '<S223>/Relational Operator' incorporates:
       *  Constant: '<S173>/decimal year'
       *  Memory: '<S223>/otime'
       */
      rtb_RelationalOperator = (envParams.date_y !=
        autocodePlant_DW->otime_PreviousInput);
    }

    /* FlatEarth2LLA: '<S173>/Flat Earth to LLA' incorporates:
     *  Constant: '<S173>/ground altitude'
     */
    rtb_DiscreteTransferFcn1 = (rtb_posNed_m_idx_0 - 0.0 * rtb_posNed_m_idx_1) /
      6.3354393272928195E+6;
    rtb_Sum1_ob = fabs(rtb_DiscreteTransferFcn1);
    rtb_Product1_do = (0.0 * rtb_posNed_m_idx_0 + rtb_posNed_m_idx_1) /
      6.378137E+6 + 0.17453292519943295;
    if (rtb_Sum1_ob > 3.141592653589793) {
      rtb_DiscreteTransferFcn1 = rt_modd_snf(rtb_DiscreteTransferFcn1 +
        3.141592653589793, 6.283185307179586) - 3.141592653589793;
      rtb_Sum1_ob = fabs(rtb_DiscreteTransferFcn1);
    }

    if (rtb_Sum1_ob > 1.5707963267948966) {
      rtb_Product1_do += 3.141592653589793;
      if (rtIsNaN(rtb_DiscreteTransferFcn1)) {
        rtb_DiscreteTransferFcn1 = (rtNaN);
      } else if (rtb_DiscreteTransferFcn1 < 0.0) {
        rtb_DiscreteTransferFcn1 = -1.0;
      } else {
        rtb_DiscreteTransferFcn1 = (rtb_DiscreteTransferFcn1 > 0.0);
      }

      rtb_DiscreteTransferFcn1 *= 1.5707963267948966 - (rtb_Sum1_ob -
        1.5707963267948966);
    }

    if (fabs(rtb_Product1_do) > 3.141592653589793) {
      rtb_Sum1_ob = rt_remd_snf(rtb_Product1_do, 6.283185307179586);
      rtb_Product1_do = rtb_Sum1_ob - trunc(rtb_Sum1_ob / 3.141592653589793) *
        6.283185307179586;
    }

    rtb_FlatEarthtoLLA_o1_idx_0 = rtb_DiscreteTransferFcn1 * 180.0 /
      3.141592653589793;
    rtb_FlatEarthtoLLA_o1_idx_1 = rtb_Product1_do * 180.0 / 3.141592653589793;
    rtb_UnitDelay2_idx_1 = -(rtb_posNed_m_idx_2 + envParams.groundAlt_m);

    /* End of FlatEarth2LLA: '<S173>/Flat Earth to LLA' */

    /* Switch: '<S212>/Switch' incorporates:
     *  Abs: '<S212>/Abs'
     *  Bias: '<S212>/Bias'
     *  Bias: '<S212>/Bias1'
     *  Constant: '<S212>/Constant2'
     *  Constant: '<S215>/Constant'
     *  Math: '<S212>/Math Function1'
     *  RelationalOperator: '<S215>/Compare'
     */
    if (fabs(rtb_FlatEarthtoLLA_o1_idx_0) > 180.0) {
      rtb_Lw_idx_1 = rt_modd_snf(rtb_FlatEarthtoLLA_o1_idx_0 + 180.0, 360.0) -
        180.0;
    } else {
      rtb_Lw_idx_1 = rtb_FlatEarthtoLLA_o1_idx_0;
    }

    /* End of Switch: '<S212>/Switch' */

    /* Abs: '<S208>/Abs1' */
    rtb_Abs1 = fabs(rtb_Lw_idx_1);

    /* RelationalOperator: '<S210>/Compare' incorporates:
     *  Constant: '<S210>/Constant'
     */
    rtb_max_relop_c = (rtb_Abs1 > 90.0);

    /* Switch: '<S202>/Switch1' incorporates:
     *  Constant: '<S202>/Constant'
     *  Constant: '<S202>/Constant1'
     */
    if (rtb_max_relop_c) {
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
      rtAction = (int8_T)!(rtb_Abs1 > 0.0);
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
      autocodePlant_B->Merge = rtb_Lw_idx_1 / rtb_Abs1;

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
    if (rtb_max_relop_c) {
      /* Switch: '<S208>/Switch' incorporates:
       *  Bias: '<S208>/Bias'
       *  Bias: '<S208>/Bias1'
       *  Gain: '<S208>/Gain'
       *  Product: '<S208>/Divide1'
       */
      autocodePlant_B->Switch_l = (-(rtb_Abs1 - 90.0) + 90.0) *
        autocodePlant_B->Merge;
    } else {
      /* Switch: '<S208>/Switch' */
      autocodePlant_B->Switch_l = rtb_Lw_idx_1;
    }

    /* End of Switch: '<S208>/Switch' */

    /* UnitConversion: '<S267>/Unit Conversion' */
    /* Unit Conversion - from: deg to: rad
       Expression: output = (0.0174533*input) + (0) */
    rtb_Abs1 = 0.017453292519943295 * autocodePlant_B->Switch;
    rtb_Lw_idx_1 = 0.017453292519943295 * autocodePlant_B->Switch_l;

    /* Trigonometry: '<S220>/sincos' */
    rtb_sincos_o1_idx_0 = sin(rtb_Abs1);
    rtb_Abs1 = cos(rtb_Abs1);
    rtb_sincos_o1_idx_1 = sin(rtb_Lw_idx_1);
    rtb_DiscreteTransferFcn1 = cos(rtb_Lw_idx_1);
    if (tmp) {
      /* Outputs for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates ' incorporates:
       *  EnablePort: '<S219>/Enable'
       */
      if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
        /* RelationalOperator: '<S222>/Relational Operator' incorporates:
         *  Memory: '<S222>/olon'
         */
        autocodePlant_DW->Convertfromgeodetictosphericalc =
          (autocodePlant_B->Switch != autocodePlant_DW->olon_PreviousInput);
      }

      /* End of Outputs for SubSystem: '<S206>/Convert from geodetic to  spherical coordinates ' */

      /* Memory: '<S221>/olat' */
      autocodePlant_B->olat = autocodePlant_DW->olat_PreviousInput;
    }

    /* Outputs for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates ' incorporates:
     *  EnablePort: '<S219>/Enable'
     */
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
            rtb_Sum1_ob = autocodePlant_DW->UnitDelay1_DSTATE[0];
            rtb_Product1_do = autocodePlant_DW->UnitDelay1_DSTATE[1];
          } else {
            rtb_Sum1_ob = rtb_Abs1;
            rtb_Product1_do = rtb_sincos_o1_idx_0;
          }

          /* End of Switch: '<S266>/cp[m-1] sp[m-1]' */

          /* Sum: '<S266>/Sum2' incorporates:
           *  Product: '<S266>/Product1'
           *  Product: '<S266>/Product2'
           *  SignalConversion generated from: '<S219>/cp[2]'
           *  SignalConversion generated from: '<S219>/sp[2]'
           */
          rtb_Lw_idx_1 = rtb_Sum1_ob * rtb_sincos_o1_idx_0 + rtb_Product1_do *
            rtb_Abs1;

          /* Sum: '<S266>/Sum1' incorporates:
           *  Product: '<S266>/Product3'
           *  Product: '<S266>/Product8'
           *  SignalConversion generated from: '<S219>/cp[2]'
           *  SignalConversion generated from: '<S219>/sp[2]'
           */
          rtb_Sum1_ob = rtb_Sum1_ob * rtb_Abs1 - rtb_Product1_do *
            rtb_sincos_o1_idx_0;

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

          autocodePlant_B->Assignment[s266_iter] = rtb_Lw_idx_1;

          /* End of Assignment: '<S266>/Assignment' */

          /* Assignment: '<S266>/Assignment1' */
          autocodePlant_B->Assignment1[s266_iter] = rtb_Sum1_ob;

          /* Update for UnitDelay: '<S266>/Unit Delay1' */
          autocodePlant_DW->UnitDelay1_DSTATE[0] = rtb_Sum1_ob;
          autocodePlant_DW->UnitDelay1_DSTATE[1] = rtb_Lw_idx_1;
        }

        /* End of Outputs for SubSystem: '<S219>/For Iterator Subsystem' */
      }

      /* SignalConversion generated from: '<S219>/cp[13]' incorporates:
       *  Constant: '<S219>/cp[1]'
       *  SignalConversion generated from: '<S219>/cp[2]'
       */
      autocodePlant_B->OutportBufferForcp13[0] = 1.0;
      autocodePlant_B->OutportBufferForcp13[1] = rtb_Abs1;

      /* SignalConversion generated from: '<S219>/sp[13]' incorporates:
       *  Constant: '<S219>/sp[1]'
       *  SignalConversion generated from: '<S219>/sp[2]'
       */
      autocodePlant_B->OutportBufferForsp13[0] = 0.0;
      autocodePlant_B->OutportBufferForsp13[1] = rtb_sincos_o1_idx_0;

      /* SignalConversion generated from: '<S219>/cp[13]' */
      memcpy(&autocodePlant_B->OutportBufferForcp13[2],
             &autocodePlant_B->Assignment1[0], 11U * sizeof(real_T));

      /* SignalConversion generated from: '<S219>/sp[13]' */
      memcpy(&autocodePlant_B->OutportBufferForsp13[2],
             &autocodePlant_B->Assignment[0], 11U * sizeof(real_T));
    }

    /* End of Outputs for SubSystem: '<S206>/Convert from geodetic to  spherical coordinates ' */

    /* Gain: '<S189>/Gain' */
    autocodePlant_B->Gain = 0.001 * rtb_UnitDelay2_idx_1;
    if (tmp) {
      /* Memory: '<S221>/oalt' */
      autocodePlant_B->oalt = autocodePlant_DW->oalt_PreviousInput;
    }

    /* Logic: '<S221>/Logical Operator' incorporates:
     *  RelationalOperator: '<S221>/Relational Operator'
     *  RelationalOperator: '<S221>/Relational Operator1'
     */
    rtb_max_relop_c = ((autocodePlant_B->Switch_l != autocodePlant_B->olat) ||
                       (autocodePlant_B->Gain != autocodePlant_B->oalt));

    /* Product: '<S220>/Product' */
    rtb_Sum1_ob = rtb_sincos_o1_idx_1 * rtb_sincos_o1_idx_1;

    /* Product: '<S220>/Product1' */
    rtb_Product1_do = rtb_DiscreteTransferFcn1 * rtb_DiscreteTransferFcn1;
    if (tmp) {
      /* Outputs for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' incorporates:
       *  EnablePort: '<S218>/Enable'
       */
      if (rtsiIsModeUpdateTimeStep(&autocodePlant_M->solverInfo)) {
        /* SignalConversion generated from: '<S218>/Enable' */
        autocodePlant_DW->Convertfromgeodetictospherica_p = rtb_max_relop_c;
      }

      /* End of Outputs for SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' */
    }

    /* Outputs for Enabled SubSystem: '<S206>/Convert from geodetic to  spherical coordinates' incorporates:
     *  EnablePort: '<S218>/Enable'
     */
    if (autocodePlant_DW->Convertfromgeodetictospherica_p) {
      /* Sqrt: '<S260>/sqrt' incorporates:
       *  Product: '<S260>/Product10'
       *  Product: '<S260>/Product9'
       *  Sum: '<S260>/Sum7'
       */
      rtb_Sum_o5 = sqrt(rtb_Product1_do * autocodePlant_ConstB.a2 +
                        autocodePlant_ConstB.b2 * rtb_Sum1_ob);

      /* Sqrt: '<S261>/sqrt' incorporates:
       *  Product: '<S261>/Product'
       *  Sum: '<S261>/Sum'
       */
      rtb_Lw_idx_1 = sqrt(autocodePlant_ConstB.a2 - rtb_Sum1_ob *
                          autocodePlant_ConstB.c2);

      /* Product: '<S218>/Product1' */
      rtb_Abs1 = rtb_Lw_idx_1 * autocodePlant_B->Gain;

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
        autocodePlant_ConstB.c4 * rtb_Sum1_ob) / (rtb_Lw_idx_1 * rtb_Lw_idx_1) +
        (2.0 * rtb_Abs1 + autocodePlant_B->Gain * autocodePlant_B->Gain));

      /* Product: '<S258>/Product11' incorporates:
       *  Sum: '<S258>/Sum8'
       */
      autocodePlant_B->Product11 = (autocodePlant_B->Gain + rtb_Sum_o5) /
        autocodePlant_B->sqrt_b;

      /* Product: '<S264>/Product12' incorporates:
       *  Product: '<S264>/Product1'
       */
      autocodePlant_B->Product12 = autocodePlant_ConstB.c2_l /
        (autocodePlant_B->sqrt_b * rtb_Sum_o5) * rtb_DiscreteTransferFcn1 *
        rtb_sincos_o1_idx_1;

      /* Sum: '<S262>/Sum2' */
      rtb_Sum_o5 = autocodePlant_ConstB.a2 + rtb_Abs1;

      /* Sum: '<S262>/Sum1' */
      rtb_Abs1 += autocodePlant_ConstB.b2;

      /* Product: '<S259>/Product4' incorporates:
       *  Product: '<S259>/Product3'
       *  Product: '<S262>/Product1'
       *  Product: '<S262>/Product2'
       *  Sqrt: '<S259>/sqrt'
       *  Sum: '<S259>/Sum3'
       */
      autocodePlant_B->Product4 = rtb_sincos_o1_idx_1 / sqrt(rtb_Sum_o5 *
        rtb_Sum_o5 / (rtb_Abs1 * rtb_Abs1) * rtb_Product1_do + rtb_Sum1_ob);

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
      rtb_Abs1 = 0.0;
      for (s266_iter = 0; s266_iter < 12; s266_iter++) {
        /* Switch: '<S217>/ar(n)' incorporates:
         *  Product: '<S206>/ar'
         */
        if (s266_iter <= 0) {
          rtb_Abs1 = rtb_Lw_idx_1 * rtb_Lw_idx_1;
        }

        /* End of Switch: '<S217>/ar(n)' */

        /* Product: '<S217>/Product8' incorporates:
         *  UnitDelay: '<S217>/Unit Delay'
         */
        rtb_Abs1 *= rtb_Lw_idx_1;

        /* Outputs for Iterator SubSystem: '<S217>/For Iterator Subsystem' incorporates:
         *  ForIterator: '<S225>/For Iterator'
         */
        /* InitializeConditions for UnitDelay: '<S226>/Unit Delay3' */
        rtb_Sum1_ob = 0.0;

        /* InitializeConditions for UnitDelay: '<S226>/Unit Delay2' */
        rtb_Product1_do = 0.0;

        /* InitializeConditions for UnitDelay: '<S226>/Unit Delay1' */
        UnitDelay1_DSTATE_a = 0.0;

        /* InitializeConditions for UnitDelay: '<S226>/Unit Delay4' */
        UnitDelay4_DSTATE = 0.0;
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
              rtb_Sum_gx + rtCP__cmaxdefmaxdef_Value[i];

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
                rtb_Sum_gx + rtCP__cmaxdefmaxdef_Value[i];

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
              rtb_DiscreteTransferFcn1 = autocodePlant_B->Assignment_o[i];

              /* Sum: '<S228>/Sum2' incorporates:
               *  Assignment: '<S228>/Assignment'
               *  Merge: '<S255>/Merge'
               *  UnitDelay: '<S255>/Unit Delay'
               */
              autocodePlant_B->Sum2_p[i] = rtb_DiscreteTransferFcn1 +
                autocodePlant_DW->UnitDelay_DSTATE_k[i];

              /* Update for UnitDelay: '<S228>/Unit Delay' incorporates:
               *  Assignment: '<S228>/Assignment'
               */
              autocodePlant_DW->UnitDelay_DSTATE_e[i] = rtb_DiscreteTransferFcn1;
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
            Merge1 = autocodePlant_B->OutportBufferForsp13[s225_iter - 1] *
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
            rtb_Sum2_p0 = ((s225_iter - 2) * 13 + s266_iter) + 1;

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
              Sum2_p[rtb_Sum2_p0];

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
            Merge1 = autocodePlant_B->OutportBufferForsp13[s225_iter - 1] *
              autocodePlant_B->Sum2_p[i] - autocodePlant_B->
              OutportBufferForcp13[s225_iter - 1] * autocodePlant_B->
              Sum2_p[rtb_Sum2_p0];

            /* End of Outputs for SubSystem: '<S231>/If Action Subsystem1' */
          }

          /* End of If: '<S231>/If' */

          /* Outputs for Enabled SubSystem: '<S225>/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations' incorporates:
           *  EnablePort: '<S227>/Enable'
           */
          if (rtb_max_relop_c) {
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
              rtb_Sum2_p0 = mul_s32_sat(13, s225_iter - 2);
              if (rtb_Sum2_p0 > 2147483646 - s266_iter) {
                i = MAX_int32_T;
              } else {
                i = (s266_iter + rtb_Sum2_p0) + 1;
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
              if (rtb_Sum2_p0 > 2147483646 - s266_iter) {
                i = MAX_int32_T;
              } else {
                i = (s266_iter + rtb_Sum2_p0) + 1;
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
              rtb_Sum2_p0 = mul_s32_sat(13, 0);
              if (rtb_Sum2_p0 > 2147483646) {
                i = MAX_int32_T;
              } else {
                i = rtb_Sum2_p0 + 1;
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
              if (rtb_Sum2_p0 > 2147483646) {
                i = MAX_int32_T;
              } else {
                i = rtb_Sum2_p0 + 1;
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
              rtb_Sum2_p0 = mul_s32_sat(13, s225_iter - 1);

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
                if (rtb_Sum2_p0 > MAX_int32_T - s266_iter) {
                  i = MAX_int32_T;
                } else {
                  i = s266_iter + rtb_Sum2_p0;
                }

                rtb_DiscreteTransferFcn1 = autocodePlant_DW->
                  UnitDelay1_DSTATE_c[i - 1];
              } else {
                rtb_DiscreteTransferFcn1 = 0.0;
              }

              /* Selector: '<S243>/Selector' incorporates:
               *  Sum: '<S249>/Sum1'
               */
              if (rtb_Sum2_p0 > 2147483646 - s266_iter) {
                i = MAX_int32_T;
              } else {
                i = (s266_iter + rtb_Sum2_p0) + 1;
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
                rtCP__k1313_Value_j[Merge_b_tmp] * rtb_DiscreteTransferFcn1;

              /* Switch: '<S243>/Switch' incorporates:
               *  Constant: '<S243>/Constant'
               *  RelationalOperator: '<S252>/Relational Operator'
               *  Selector: '<S243>/Selector1'
               *  Sum: '<S252>/Sum2'
               *  UnitDelay: '<S227>/Unit Delay'
               */
              if (s266_iter - 1 >= s225_iter - 1) {
                rtb_DiscreteTransferFcn1 = autocodePlant_DW->UnitDelay_DSTATE_o
                  [((s266_iter - 1) * 13 + s225_iter) - 1];
              } else {
                rtb_DiscreteTransferFcn1 = 0.0;
              }

              /* Selector: '<S243>/Selector' incorporates:
               *  Sum: '<S249>/Sum1'
               */
              if (rtb_Sum2_p0 > 2147483646 - s266_iter) {
                i = MAX_int32_T;
              } else {
                i = (s266_iter + rtb_Sum2_p0) + 1;
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
                rtb_DiscreteTransferFcn1;

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
          rtb_DiscreteTransferFcn1 = autocodePlant_B->Assignment_snorm[i - 1] *
            rtb_Abs1;

          /* Sum: '<S226>/Sum2' incorporates:
           *  Constant: '<S226>/fm'
           *  Product: '<S226>/Product1'
           *  Selector: '<S226>/fm[m]'
           *  UnitDelay: '<S226>/Unit Delay3'
           */
          autocodePlant_B->Sum2_m = rtCP__fm_Value[s225_iter - 1] *
            rtb_DiscreteTransferFcn1 * Merge1 + rtb_Sum1_ob;

          /* Sum: '<S226>/Sum3' incorporates:
           *  Constant: '<S226>/fn'
           *  Product: '<S226>/Product2'
           *  Selector: '<S226>/fn[m]'
           *  Sum: '<S226>/Sum4'
           *  UnitDelay: '<S226>/Unit Delay2'
           */
          autocodePlant_B->Sum3 = rtCP__fn_Value[s266_iter + 1] *
            rtb_DiscreteTransferFcn1 * Merge_n + rtb_Product1_do;

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
          rtb_Sum2_p0 = (s266_iter + 1) * 13;

          /* End of Outputs for SubSystem: '<S229>/If Action Subsystem2' */
          /* End of Outputs for SubSystem: '<S226>/Special case - North//South Geographic Pole' */

          /* Sum: '<S226>/Sum1' incorporates:
           *  Assignment: '<S227>/Assignment'
           *  Product: '<S226>/Product'
           *  Selector: '<S226>/dp[n][m]'
           *  UnitDelay: '<S217>/Unit Delay'
           *  UnitDelay: '<S226>/Unit Delay1'
           */
          autocodePlant_B->Sum1_p = UnitDelay1_DSTATE_a -
            autocodePlant_B->Assignment_h[(rtb_Sum2_p0 + s225_iter) - 1] *
            Merge_n * rtb_Abs1;

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
                rtCP__k1313_Value[rtb_Sum2_p0 + 1] *
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
              UnitDelay1_DSTATE_b[s266_iter + 1] * rtb_Abs1 * Merge1;
          } else if (autocodePlant_DW->SpecialcaseNorthSouthGeographic) {
            /* Disable for Product: '<S229>/Product2' incorporates:
             *  Outport: '<S229>/bpp'
             */
            autocodePlant_B->Product2 = 0.0;
            autocodePlant_DW->SpecialcaseNorthSouthGeographic = false;
          }

          /* End of Outputs for SubSystem: '<S226>/Special case - North//South Geographic Pole' */

          /* Sum: '<S226>/Sum5' incorporates:
           *  Constant: '<S232>/Constant'
           *  Constant: '<S232>/Constant1'
           *  Logic: '<S232>/Logical Operator'
           *  RelationalOperator: '<S232>/Relational Operator'
           *  RelationalOperator: '<S232>/Relational Operator1'
           *  Sum: '<S225>/Sum1'
           *  UnitDelay: '<S226>/Unit Delay4'
           */
          autocodePlant_B->Sum5 = UnitDelay4_DSTATE + autocodePlant_B->Product2;

          /* Update for UnitDelay: '<S226>/Unit Delay3' */
          rtb_Sum1_ob = autocodePlant_B->Sum2_m;

          /* Update for UnitDelay: '<S226>/Unit Delay2' */
          rtb_Product1_do = autocodePlant_B->Sum3;

          /* Update for UnitDelay: '<S226>/Unit Delay1' */
          UnitDelay1_DSTATE_a = autocodePlant_B->Sum1_p;

          /* Update for UnitDelay: '<S226>/Unit Delay4' */
          UnitDelay4_DSTATE = autocodePlant_B->Sum5;
        }

        /* End of Sum: '<S217>/Sum' */
        /* End of Outputs for SubSystem: '<S217>/For Iterator Subsystem' */

        /* Sum: '<S217>/Sum1' incorporates:
         *  UnitDelay: '<S217>/Unit Delay2'
         */
        rtb_DiscreteTransferFcn1 = autocodePlant_DW->UnitDelay2_DSTATE[0];
        UnitDelay1_DSTATE_a = autocodePlant_DW->UnitDelay2_DSTATE[1];
        rtb_Sum1_ob = autocodePlant_DW->UnitDelay2_DSTATE[2];
        rtb_Product1_do = autocodePlant_DW->UnitDelay2_DSTATE[3];
        autocodePlant_DW->UnitDelay2_DSTATE[0] = rtb_DiscreteTransferFcn1 +
          autocodePlant_B->Sum1_p;
        autocodePlant_DW->UnitDelay2_DSTATE[1] = UnitDelay1_DSTATE_a +
          autocodePlant_B->Sum2_m;
        autocodePlant_DW->UnitDelay2_DSTATE[2] = rtb_Sum1_ob +
          autocodePlant_B->Sum3;
        autocodePlant_DW->UnitDelay2_DSTATE[3] = rtb_Product1_do +
          autocodePlant_B->Sum5;
      }

      /* End of Outputs for SubSystem: '<S206>/Compute magnetic vector in spherical coordinates' */

      /* Delay: '<S6>/Delay' */
      autocodePlant_B->Delay = autocodePlant_DW->Delay_DSTATE_h[0];
    }

    /* RelationalOperator: '<S98>/Compare' incorporates:
     *  Constant: '<S98>/Constant'
     *  UnaryMinus: '<S4>/Unary Minus'
     */
    rtb_max_relop_c = (-rtb_posNed_m_idx_2 <= 4.0);

    /* Logic: '<S162>/Logical Operator' */
    rtb_RelationalOperator = !rtb_max_relop_c;

    /* Product: '<S162>/Product' */
    autocodePlant_B->Product_h[0] = rtb_Delay[0] * (real_T)
      rtb_RelationalOperator;
    autocodePlant_B->Product_h[1] = rtb_Delay[1] * (real_T)
      rtb_RelationalOperator;
    autocodePlant_B->Product_h[2] = rtb_Delay[2] * (real_T)
      rtb_RelationalOperator;

    /* Sqrt: '<S114>/sqrt' incorporates:
     *  Sqrt: '<S182>/sqrt'
     *  Sqrt: '<S195>/sqrt'
     */
    rtb_Abs1 = sqrt(rtb_UnaryMinus1_o);

    /* Product: '<S110>/Product2' incorporates:
     *  Product: '<S191>/Product2'
     *  Sqrt: '<S114>/sqrt'
     */
    rtb_sincos_o1_idx_1 = rtb_q_na_idx_2 / rtb_Abs1;

    /* Product: '<S110>/Product3' incorporates:
     *  Sqrt: '<S114>/sqrt'
     */
    rtb_Lw_idx_1 = rtb_q_na_idx_3 / rtb_Abs1;

    /* Product: '<S110>/Product1' incorporates:
     *  Product: '<S191>/Product1'
     *  Sqrt: '<S114>/sqrt'
     */
    Merge1 = rtb_q_na_idx_1 / rtb_Abs1;

    /* Product: '<S110>/Product' incorporates:
     *  Product: '<S191>/Product'
     *  Sqrt: '<S114>/sqrt'
     */
    rtb_Abs1 = rtb_q_na_idx_0 / rtb_Abs1;

    /* Product: '<S111>/Product7' incorporates:
     *  Product: '<S112>/Product7'
     */
    rtb_UnaryMinus1_o = rtb_Lw_idx_1 * rtb_Lw_idx_1;

    /* Product: '<S111>/Product' incorporates:
     *  Product: '<S110>/Product1'
     *  Product: '<S110>/Product2'
     *  Product: '<S112>/Product'
     */
    rtb_DiscreteTransferFcn1 = Merge1 * rtb_sincos_o1_idx_1;

    /* Product: '<S111>/Product1' incorporates:
     *  Product: '<S110>/Product'
     *  Product: '<S112>/Product1'
     */
    UnitDelay1_DSTATE_a = rtb_Abs1 * rtb_Lw_idx_1;

    /* Product: '<S111>/Product3' incorporates:
     *  Product: '<S110>/Product1'
     *  Product: '<S113>/Product'
     */
    rtb_Sum1_ob = Merge1 * rtb_Lw_idx_1;

    /* Product: '<S111>/Product2' incorporates:
     *  Product: '<S110>/Product'
     *  Product: '<S110>/Product2'
     *  Product: '<S113>/Product1'
     */
    rtb_Product1_do = rtb_Abs1 * rtb_sincos_o1_idx_1;

    /* Product: '<S111>/Product6' incorporates:
     *  Product: '<S110>/Product2'
     *  Product: '<S113>/Product7'
     */
    UnitDelay4_DSTATE = rtb_sincos_o1_idx_1 * rtb_sincos_o1_idx_1;

    /* Gain: '<S111>/Gain2' incorporates:
     *  Constant: '<S111>/Constant'
     *  Gain: '<S179>/Gain2'
     *  Gain: '<S192>/Gain2'
     *  Product: '<S111>/Product6'
     *  Product: '<S111>/Product7'
     *  Sum: '<S111>/Sum3'
     *  Sum: '<S192>/Sum'
     */
    Merge_n = ((0.5 - UnitDelay4_DSTATE) - rtb_UnaryMinus1_o) * 2.0;

    /* Gain: '<S111>/Gain' incorporates:
     *  Gain: '<S179>/Gain'
     *  Gain: '<S192>/Gain'
     *  Product: '<S111>/Product'
     *  Product: '<S111>/Product1'
     *  Sum: '<S111>/Sum1'
     *  Sum: '<S192>/Sum'
     */
    tmp_1 = (rtb_DiscreteTransferFcn1 + UnitDelay1_DSTATE_a) * 2.0;

    /* Gain: '<S111>/Gain1' incorporates:
     *  Gain: '<S179>/Gain1'
     *  Gain: '<S192>/Gain1'
     *  Product: '<S111>/Product2'
     *  Product: '<S111>/Product3'
     *  Sum: '<S111>/Sum2'
     *  Sum: '<S192>/Sum'
     */
    tmp_2 = (rtb_Sum1_ob - rtb_Product1_do) * 2.0;

    /* Gain: '<S4>/mass' incorporates:
     *  Constant: '<S4>/gNed_mps2'
     *  Gain: '<S111>/Gain'
     *  Gain: '<S111>/Gain1'
     *  Gain: '<S111>/Gain2'
     *  Product: '<S111>/Product4'
     *  Product: '<S111>/Product5'
     *  Product: '<S111>/Product8'
     *  Sum: '<S111>/Sum'
     */
    autocodePlant_Y_plant_bus_e->enviroment_bus.gravityForceBdy_N[0] = ((Merge_n
      * envParams.gravityNed_mps2[0] + tmp_1 * envParams.gravityNed_mps2[1]) +
      tmp_2 * envParams.gravityNed_mps2[2]) * vehicleParams.mass_kg;

    /* Product: '<S112>/Product3' incorporates:
     *  Product: '<S110>/Product2'
     *  Product: '<S113>/Product3'
     */
    rtb_Lw_idx_1 *= rtb_sincos_o1_idx_1;

    /* Product: '<S112>/Product2' incorporates:
     *  Product: '<S110>/Product'
     *  Product: '<S110>/Product1'
     *  Product: '<S113>/Product2'
     */
    rtb_Abs1 *= Merge1;

    /* Sum: '<S112>/Sum3' incorporates:
     *  Constant: '<S112>/Constant'
     *  Product: '<S110>/Product1'
     *  Product: '<S112>/Product6'
     *  Sum: '<S113>/Sum3'
     */
    Merge1 = 0.5 - Merge1 * Merge1;

    /* Gain: '<S112>/Gain2' incorporates:
     *  Gain: '<S180>/Gain2'
     *  Gain: '<S193>/Gain2'
     *  Sum: '<S112>/Sum3'
     *  Sum: '<S193>/Sum'
     */
    rtb_UnaryMinus1_o = (Merge1 - rtb_UnaryMinus1_o) * 2.0;

    /* Gain: '<S112>/Gain' incorporates:
     *  Gain: '<S180>/Gain'
     *  Gain: '<S193>/Gain'
     *  Sum: '<S112>/Sum1'
     *  Sum: '<S193>/Sum'
     */
    rtb_DiscreteTransferFcn1 = (rtb_DiscreteTransferFcn1 - UnitDelay1_DSTATE_a) *
      2.0;

    /* Gain: '<S112>/Gain1' incorporates:
     *  Gain: '<S180>/Gain1'
     *  Gain: '<S193>/Gain1'
     *  Product: '<S112>/Product2'
     *  Product: '<S112>/Product3'
     *  Sum: '<S112>/Sum2'
     *  Sum: '<S193>/Sum'
     */
    UnitDelay1_DSTATE_a = (rtb_Abs1 + rtb_Lw_idx_1) * 2.0;

    /* Gain: '<S4>/mass' incorporates:
     *  Constant: '<S4>/gNed_mps2'
     *  Gain: '<S112>/Gain'
     *  Gain: '<S112>/Gain1'
     *  Gain: '<S112>/Gain2'
     *  Product: '<S112>/Product4'
     *  Product: '<S112>/Product5'
     *  Product: '<S112>/Product8'
     *  Sum: '<S112>/Sum'
     */
    autocodePlant_Y_plant_bus_e->enviroment_bus.gravityForceBdy_N[1] =
      ((rtb_UnaryMinus1_o * envParams.gravityNed_mps2[1] +
        rtb_DiscreteTransferFcn1 * envParams.gravityNed_mps2[0]) +
       UnitDelay1_DSTATE_a * envParams.gravityNed_mps2[2]) *
      vehicleParams.mass_kg;

    /* Gain: '<S113>/Gain' incorporates:
     *  Gain: '<S181>/Gain'
     *  Gain: '<S194>/Gain'
     *  Sum: '<S113>/Sum1'
     *  Sum: '<S194>/Sum'
     */
    rtb_Sum1_ob = (rtb_Sum1_ob + rtb_Product1_do) * 2.0;

    /* Gain: '<S113>/Gain1' incorporates:
     *  Gain: '<S181>/Gain1'
     *  Gain: '<S194>/Gain1'
     *  Sum: '<S113>/Sum2'
     *  Sum: '<S194>/Sum'
     */
    rtb_Product1_do = (rtb_Lw_idx_1 - rtb_Abs1) * 2.0;

    /* Gain: '<S113>/Gain2' incorporates:
     *  Gain: '<S181>/Gain2'
     *  Gain: '<S194>/Gain2'
     *  Sum: '<S113>/Sum3'
     *  Sum: '<S194>/Sum'
     */
    UnitDelay4_DSTATE = (Merge1 - UnitDelay4_DSTATE) * 2.0;

    /* Gain: '<S4>/mass' incorporates:
     *  Constant: '<S4>/gNed_mps2'
     *  Gain: '<S113>/Gain'
     *  Gain: '<S113>/Gain1'
     *  Gain: '<S113>/Gain2'
     *  Product: '<S113>/Product4'
     *  Product: '<S113>/Product5'
     *  Product: '<S113>/Product8'
     *  Sum: '<S113>/Sum'
     */
    autocodePlant_Y_plant_bus_e->enviroment_bus.gravityForceBdy_N[2] =
      ((rtb_Sum1_ob * envParams.gravityNed_mps2[0] + rtb_Product1_do *
        envParams.gravityNed_mps2[1]) + UnitDelay4_DSTATE *
       envParams.gravityNed_mps2[2]) * vehicleParams.mass_kg;

    /* Sum: '<S5>/Sum' */
    rtb_sincos_o1_idx_1 = (autocodePlant_B->Delay +
      autocodePlant_Y_plant_bus_e->enviroment_bus.gravityForceBdy_N[0]) +
      rtb_Delay[3];

    /* Product: '<S162>/Product1' incorporates:
     *  Constant: '<S6>/Constant2'
     *  Sum: '<S5>/Sum'
     */
    autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[0] = rtb_sincos_o1_idx_1 *
      (real_T)rtb_RelationalOperator;
    autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[1] =
      (autocodePlant_Y_plant_bus_e->enviroment_bus.gravityForceBdy_N[1] +
       rtb_Delay[4]) * (real_T)rtb_RelationalOperator;
    autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[2] =
      (autocodePlant_Y_plant_bus_e->enviroment_bus.gravityForceBdy_N[2] +
       rtb_Delay[5]) * (real_T)rtb_RelationalOperator;

    /* Sum: '<S162>/Sum' incorporates:
     *  Constant: '<S162>/Constant'
     *  MinMax: '<S162>/Max1'
     *  Product: '<S162>/Product2'
     */
    autocodePlant_B->Sum_ah[0] = fmax((real_T)rtb_max_relop_c *
      rtb_sincos_o1_idx_1, 0.0) +
      autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[0];
    autocodePlant_B->Sum_ah[1] =
      autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[1];
    autocodePlant_B->Sum_ah[2] =
      autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[2];

    /* Product: '<S160>/Divide' incorporates:
     *  Constant: '<S5>/Constant'
     *  Sum: '<S164>/Sum1'
     */
    autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[0] =
      (autocodePlant_B->Sum_ah[0] + autocodePlant_ConstB.Switch) /
      vehicleParams.mass_kg;
    autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[1] =
      (autocodePlant_B->Sum_ah[1] + autocodePlant_ConstB.Switch) /
      vehicleParams.mass_kg;
    autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[2] =
      (autocodePlant_B->Sum_ah[2] + autocodePlant_ConstB.Switch) /
      vehicleParams.mass_kg;

    /* Sum: '<S170>/fBdy_mps2' incorporates:
     *  Constant: '<S170>/gNed_mps2'
     *  Product: '<S179>/Product4'
     *  Product: '<S179>/Product5'
     *  Product: '<S179>/Product8'
     *  Product: '<S180>/Product4'
     *  Product: '<S180>/Product5'
     *  Product: '<S180>/Product8'
     *  Product: '<S181>/Product4'
     *  Product: '<S181>/Product5'
     *  Product: '<S181>/Product8'
     *  Sum: '<S179>/Sum'
     *  Sum: '<S180>/Sum'
     *  Sum: '<S181>/Sum'
     */
    autocodePlant_B->fBdy_mps2[0] =
      autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[0] - ((Merge_n *
      envParams.gravityNed_mps2[0] + tmp_1 * envParams.gravityNed_mps2[1]) +
      tmp_2 * envParams.gravityNed_mps2[2]);
    autocodePlant_B->fBdy_mps2[1] =
      autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[1] - ((rtb_UnaryMinus1_o *
      envParams.gravityNed_mps2[1] + rtb_DiscreteTransferFcn1 *
      envParams.gravityNed_mps2[0]) + UnitDelay1_DSTATE_a *
      envParams.gravityNed_mps2[2]);
    autocodePlant_B->fBdy_mps2[2] =
      autocodePlant_Y_plant_bus_e->eom_bus.accBdy_mps2[2] - ((rtb_Sum1_ob *
      envParams.gravityNed_mps2[0] + rtb_Product1_do *
      envParams.gravityNed_mps2[1]) + UnitDelay4_DSTATE *
      envParams.gravityNed_mps2[2]);
    if (tmp) {
      /* Sum: '<S170>/bias' incorporates:
       *  Constant: '<S170>/turnOnBias_mps2'
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn2'
       *  DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn3'
       */
      rtb_bias[0] = autocodePlant_DW->DiscreteTransferFcn2_states +
        sensorParams.accTurnOnBias_mps2[0];
      rtb_bias[1] = autocodePlant_DW->DiscreteTransferFcn1_states +
        sensorParams.accTurnOnBias_mps2[1];
      rtb_bias[2] = autocodePlant_DW->DiscreteTransferFcn3_states +
        sensorParams.accTurnOnBias_mps2[2];

      /* Product: '<S170>/scale factor and  cross-coupling' incorporates:
       *  Constant: '<S170>/Constant'
       */
      rtb_Lw_idx_1 = autocodePlant_B->fBdy_mps2[1];
      rtb_Abs1 = autocodePlant_B->fBdy_mps2[0];
      Merge1 = autocodePlant_B->fBdy_mps2[2];
      for (s266_iter = 0; s266_iter < 3; s266_iter++) {
        /* ZeroOrderHold: '<S170>/Zero-Order Hold' incorporates:
         *  Constant: '<S170>/Constant'
         *  Gain: '<S177>/Output'
         *  Product: '<S170>/scale factor and  cross-coupling'
         *  RandomNumber: '<S177>/White Noise'
         *  Sum: '<S170>/bias + noise'
         *  Sum: '<S170>/sum'
         */
        rtb_ZeroOrderHold[s266_iter] =
          ((sensorParams.accScaleCoupling_na[s266_iter + 3] * rtb_Lw_idx_1 +
            sensorParams.accScaleCoupling_na[s266_iter] * rtb_Abs1) +
           sensorParams.accScaleCoupling_na[s266_iter + 6] * Merge1) + (sqrt
          (sensorParams.accPSDWhite[s266_iter]) / 0.1 *
          autocodePlant_DW->NextOutput_f + rtb_bias[s266_iter]);
      }
    }

    /* Switch: '<S269>/Switch' incorporates:
     *  Product: '<S269>/Product'
     *  UnitDelay: '<S217>/Unit Delay2'
     */
    if (autocodePlant_B->sqrt_k != 0.0) {
      rtb_Sum_o5 = autocodePlant_DW->UnitDelay2_DSTATE[1] /
        autocodePlant_B->sqrt_k;
    } else {
      rtb_Sum_o5 = autocodePlant_DW->UnitDelay2_DSTATE[3];
    }

    /* End of Switch: '<S269>/Switch' */

    /* Sum: '<S268>/Sum1' incorporates:
     *  Product: '<S268>/Product1'
     *  Product: '<S268>/Product4'
     *  UnitDelay: '<S217>/Unit Delay2'
     */
    rtb_Lw_idx_1 = (0.0 - autocodePlant_B->Product11 *
                    autocodePlant_DW->UnitDelay2_DSTATE[0]) -
      autocodePlant_DW->UnitDelay2_DSTATE[2] * autocodePlant_B->Product12;

    /* Trigonometry: '<S271>/Trigonometric Function1' */
    rtb_Abs1 = rt_atan2d_snf(rtb_Sum_o5, rtb_Lw_idx_1);

    /* Sum: '<S270>/Sum1' incorporates:
     *  Product: '<S270>/Product1'
     *  Product: '<S270>/Product4'
     *  UnitDelay: '<S217>/Unit Delay2'
     */
    /* Unit Conversion - from: rad to: deg
       Expression: output = (57.2958*input) + (0) */
    Merge1 = autocodePlant_B->Product12 * autocodePlant_DW->UnitDelay2_DSTATE[0]
      - autocodePlant_DW->UnitDelay2_DSTATE[2] * autocodePlant_B->Product11;

    /* Sum: '<S271>/Sum' incorporates:
     *  Product: '<S271>/Product'
     *  Product: '<S271>/Product1'
     */
    rtb_Sum_o5 = rtb_Sum_o5 * rtb_Sum_o5 + rtb_Lw_idx_1 * rtb_Lw_idx_1;

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
    rtb_sincos_o1_idx_0 = 57.29577951308232 * rtb_Abs1 * 0.017453292519943295;
    rtb_sincos_o1_idx_1 = 57.29577951308232 * rt_atan2d_snf(Merge1, sqrt
      (rtb_Sum_o5)) * 0.017453292519943295;

    /* Sqrt: '<S271>/sqrt' incorporates:
     *  Product: '<S271>/Product2'
     *  Sum: '<S271>/Sum1'
     */
    rtb_Sum_o5 = sqrt(Merge1 * Merge1 + rtb_Sum_o5);

    /* Product: '<S200>/h1' incorporates:
     *  Trigonometry: '<S200>/sincos'
     */
    rtb_Lw_idx_1 = cos(rtb_sincos_o1_idx_1) * rtb_Sum_o5;

    /* Product: '<S200>/x1' incorporates:
     *  Trigonometry: '<S200>/sincos'
     */
    rtb_Abs1 = cos(rtb_sincos_o1_idx_0) * rtb_Lw_idx_1;

    /* Product: '<S200>/y1' incorporates:
     *  Trigonometry: '<S200>/sincos'
     */
    rtb_Lw_idx_1 *= sin(rtb_sincos_o1_idx_0);

    /* Product: '<S200>/z1' incorporates:
     *  Trigonometry: '<S200>/sincos'
     */
    rtb_Sum_o5 *= sin(rtb_sincos_o1_idx_1);
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
      Merge1 = (Merge_n * rtb_Abs1 + tmp_1 * rtb_Lw_idx_1) + tmp_2 * rtb_Sum_o5;
      rtb_DiscreteTransferFcn1 = (rtb_UnaryMinus1_o * rtb_Lw_idx_1 +
        rtb_DiscreteTransferFcn1 * rtb_Abs1) + UnitDelay1_DSTATE_a * rtb_Sum_o5;
      rtb_Lw_idx_1 = (rtb_Sum1_ob * rtb_Abs1 + rtb_Product1_do * rtb_Lw_idx_1) +
        UnitDelay4_DSTATE * rtb_Sum_o5;

      /* Sum: '<S172>/bias' incorporates:
       *  Constant: '<S172>/  '
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn'
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn1'
       *  DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn2'
       */
      rtb_bias_n[0] = autocodePlant_DW->DiscreteTransferFcn_states +
        sensorParams.gyroTurnOnBias_rps[0];
      rtb_bias_n[1] = autocodePlant_DW->DiscreteTransferFcn1_states_b +
        sensorParams.gyroTurnOnBias_rps[1];
      rtb_bias_n[2] = autocodePlant_DW->DiscreteTransferFcn2_states_g +
        sensorParams.gyroTurnOnBias_rps[2];

      /* Product: '<S172>/Product1' */
      rtb_Abs1 = 0.0;
      rtb_Sum1_ob = 0.0;
      rtb_Product1_do = 0.0;
      for (s266_iter = 0; s266_iter < 3; s266_iter++) {
        /* ZeroOrderHold: '<S173>/Zero-Order Hold' incorporates:
         *  Constant: '<S173>/hardironBdy_nT'
         *  Constant: '<S173>/soft iron matrix'
         *  Gain: '<S190>/Output'
         *  Product: '<S173>/Product'
         *  RandomNumber: '<S190>/White Noise'
         *  Sum: '<S173>/Sum'
         */
        rtb_ZeroOrderHold_g[s266_iter] = (((sensorParams.magSI[s266_iter + 3] *
          rtb_DiscreteTransferFcn1 + sensorParams.magSI[s266_iter] * Merge1) +
          sensorParams.magSI[s266_iter + 6] * rtb_Lw_idx_1) + sqrt
          (sensorParams.magPSDWhite[s266_iter]) / 0.1 *
          autocodePlant_DW->NextOutput_b) +
          sensorParams.magBiasHIBdy_nT[s266_iter];

        /* Product: '<S172>/Product1' incorporates:
         *  Constant: '<S172>/Gs'
         *  UnitDelay: '<S172>/Unit Delay'
         */
        rtb_UnaryMinus1_o = autocodePlant_DW->UnitDelay_DSTATE_c[s266_iter];
        rtb_Abs1 += sensorParams.gyroG[3 * s266_iter] * rtb_UnaryMinus1_o;
        rtb_Sum1_ob += sensorParams.gyroG[3 * s266_iter + 1] * rtb_UnaryMinus1_o;
        rtb_Product1_do += sensorParams.gyroG[3 * s266_iter + 2] *
          rtb_UnaryMinus1_o;

        /* Sum: '<S172>/bias + noise' incorporates:
         *  Gain: '<S187>/Output'
         *  RandomNumber: '<S187>/White Noise'
         */
        biasnoise_d[s266_iter] = sqrt(sensorParams.gyroPSDWhite[s266_iter]) /
          0.1 * autocodePlant_DW->NextOutput_i + rtb_bias_n[s266_iter];
      }

      /* Product: '<S172>/Product1' */
      Gdependent[2] = rtb_Product1_do;
      Gdependent[1] = rtb_Sum1_ob;
      Gdependent[0] = rtb_Abs1;

      /* Product: '<S172>/Product' incorporates:
       *  Constant: '<S172>/   '
       */
      rtb_UnaryMinus1_o = rtb_wBdy_rps[1];
      rtb_Lw_idx_1 = rtb_wBdy_rps[0];
      rtb_Abs1 = rtb_wBdy_rps[2];

      /* ZeroOrderHold: '<S172>/Zero-Order Hold' incorporates:
       *  Constant: '<S172>/   '
       *  Product: '<S172>/Product'
       *  Sum: '<S172>/      '
       */
      for (i = 0; i < 3; i++) {
        rtb_ZeroOrderHold_i[i] = (((sensorParams.gyroScaleCoupling_na[i + 3] *
          rtb_UnaryMinus1_o + sensorParams.gyroScaleCoupling_na[i] *
          rtb_Lw_idx_1) + sensorParams.gyroScaleCoupling_na[i + 6] * rtb_Abs1) +
          biasnoise_d[i]) + Gdependent[i];
      }

      /* End of ZeroOrderHold: '<S172>/Zero-Order Hold' */
    }

    /* ZeroOrderHold: '<S174>/Zero-Order Hold' incorporates:
     *  RateTransition: '<S174>/Rate Transition'
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
        autocodePlant_DW->NextOutput_m - 0.005 *
        autocodePlant_DW->DiscreteTransferFcn1_states_bi;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn1' */
      autocodePlant_B->DiscreteTransferFcn1 = 0.0 *
        autocodePlant_DW->DiscreteTransferFcn1_states_bi +
        autocodePlant_DW->DiscreteTransferFcn1_tmp;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn2' incorporates:
       *  Gain: '<S278>/Output'
       *  RandomNumber: '<S278>/White Noise'
       */
      autocodePlant_DW->DiscreteTransferFcn2_tmp = 0.7071067811865475 *
        autocodePlant_DW->NextOutput_a - 0.005 *
        autocodePlant_DW->DiscreteTransferFcn2_states_d;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn2' */
      autocodePlant_B->DiscreteTransferFcn2 = 0.0 *
        autocodePlant_DW->DiscreteTransferFcn2_states_d +
        autocodePlant_DW->DiscreteTransferFcn2_tmp;

      /* DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn3' incorporates:
       *  Gain: '<S274>/Output'
       *  RandomNumber: '<S274>/White Noise'
       */
      autocodePlant_DW->DiscreteTransferFcn3_tmp = 0.03162277660168379 *
        autocodePlant_DW->NextOutput_k - 0.005 *
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
    rtb_sincos_o1_idx_1 = rtb_posNed_m_idx_0 +
      autocodePlant_B->DiscreteTransferFcn;
    rtb_UnaryMinus1_o = rtb_posNed_m_idx_1 +
      autocodePlant_B->DiscreteTransferFcn1;

    /* Sum: '<S284>/Sum' incorporates:
     *  Product: '<S284>/Product'
     *  Product: '<S284>/Product1'
     *  Product: '<S284>/Product2'
     *  Product: '<S284>/Product3'
     */
    rtb_Sum_o5 = ((rtb_Switch_d_idx_0 * rtb_Switch_d_idx_0 + rtb_Switch_d_idx_1 *
                   rtb_Switch_d_idx_1) + rtb_Switch_d_idx_2 * rtb_Switch_d_idx_2)
      + rtb_Sum_b4 * rtb_Sum_b4;

    /* Product: '<S280>/Divide1' incorporates:
     *  UnaryMinus: '<S283>/Unary Minus'
     */
    rtb_Lw_idx_1 = -rtb_Switch_d_idx_1 / rtb_Sum_o5;

    /* Product: '<S280>/Divide' */
    rtb_Abs1 = rtb_Switch_d_idx_0 / rtb_Sum_o5;

    /* Product: '<S280>/Divide2' incorporates:
     *  UnaryMinus: '<S283>/Unary Minus1'
     */
    Merge1 = -rtb_Switch_d_idx_2 / rtb_Sum_o5;

    /* Product: '<S280>/Divide3' incorporates:
     *  UnaryMinus: '<S283>/Unary Minus2'
     */
    rtb_Sum_b4 = -rtb_Sum_b4 / rtb_Sum_o5;

    /* Sqrt: '<S289>/sqrt' incorporates:
     *  Product: '<S290>/Product'
     *  Product: '<S290>/Product1'
     *  Product: '<S290>/Product2'
     *  Product: '<S290>/Product3'
     *  Sum: '<S290>/Sum'
     */
    rtb_Sum_o5 = sqrt(((rtb_Abs1 * rtb_Abs1 + rtb_Lw_idx_1 * rtb_Lw_idx_1) +
                       Merge1 * Merge1) + rtb_Sum_b4 * rtb_Sum_b4);

    /* Product: '<S285>/Product1' */
    rtb_Lw_idx_1 /= rtb_Sum_o5;

    /* Product: '<S285>/Product2' */
    Merge1 /= rtb_Sum_o5;

    /* Product: '<S285>/Product' */
    rtb_Abs1 /= rtb_Sum_o5;

    /* Product: '<S285>/Product3' */
    rtb_Sum_b4 /= rtb_Sum_o5;

    /* FlatEarth2LLA: '<S174>/Flat Earth to LLA' */
    rtb_DiscreteTransferFcn1 = (rtb_sincos_o1_idx_1 - 0.0 * rtb_UnaryMinus1_o) /
      6.364093718556922E+6 + 0.7340319991259698;
    rtb_Sum1_ob = fabs(rtb_DiscreteTransferFcn1);
    rtb_Product1_do = (0.0 * rtb_sincos_o1_idx_1 + rtb_UnaryMinus1_o) /
      4.7427650164783625E+6 - 1.5302472054346188;
    if (rtb_Sum1_ob > 3.141592653589793) {
      rtb_DiscreteTransferFcn1 = rt_modd_snf(rtb_DiscreteTransferFcn1 +
        3.141592653589793, 6.283185307179586) - 3.141592653589793;
      rtb_Sum1_ob = fabs(rtb_DiscreteTransferFcn1);
    }

    if (rtb_Sum1_ob > 1.5707963267948966) {
      rtb_Product1_do += 3.141592653589793;
      if (rtIsNaN(rtb_DiscreteTransferFcn1)) {
        rtb_UnaryMinus1_o = (rtNaN);
      } else if (rtb_DiscreteTransferFcn1 < 0.0) {
        rtb_UnaryMinus1_o = -1.0;
      } else {
        rtb_UnaryMinus1_o = (rtb_DiscreteTransferFcn1 > 0.0);
      }

      rtb_DiscreteTransferFcn1 = (1.5707963267948966 - (rtb_Sum1_ob -
        1.5707963267948966)) * rtb_UnaryMinus1_o;
    }

    if (fabs(rtb_Product1_do) > 3.141592653589793) {
      rtb_Sum1_ob = rt_remd_snf(rtb_Product1_do, 6.283185307179586);
      rtb_Product1_do = rtb_Sum1_ob - trunc(rtb_Sum1_ob / 3.141592653589793) *
        6.283185307179586;
    }

    autocodePlant_B->FlatEarthtoLLA_o1[0] = rtb_DiscreteTransferFcn1 * 180.0 /
      3.141592653589793;
    autocodePlant_B->FlatEarthtoLLA_o1[1] = rtb_Product1_do * 180.0 /
      3.141592653589793;

    /* ZeroOrderHold: '<S174>/Zero-Order Hold' */
    if (rtb_RelationalOperator) {
      /* ZeroOrderHold: '<S174>/Zero-Order Hold' incorporates:
       *  Constant: '<S174>/Constant1'
       *  FlatEarth2LLA: '<S174>/Flat Earth to LLA'
       *  Sum: '<S174>/Sum1'
       */
      autocodePlant_B->ZeroOrderHold[0] = autocodePlant_B->FlatEarthtoLLA_o1[0];
      autocodePlant_B->ZeroOrderHold[1] = autocodePlant_B->FlatEarthtoLLA_o1[1];
      autocodePlant_B->ZeroOrderHold[2] = -((rtb_posNed_m_idx_2 +
        autocodePlant_B->DiscreteTransferFcn2) + envParams.groundAlt_m);

      /* Product: '<S286>/Product7' incorporates:
       *  Product: '<S287>/Product7'
       */
      rtb_UnaryMinus1_o = rtb_Sum_b4 * rtb_Sum_b4;

      /* Product: '<S286>/Product' incorporates:
       *  Product: '<S287>/Product'
       */
      rtb_Switch_d_idx_2 = rtb_Lw_idx_1 * Merge1;

      /* Product: '<S286>/Product1' incorporates:
       *  Product: '<S287>/Product1'
       */
      rtb_Switch_d_idx_1 = rtb_Abs1 * rtb_Sum_b4;

      /* Product: '<S286>/Product3' incorporates:
       *  Product: '<S288>/Product'
       */
      rtb_Switch_d_idx_0 = rtb_Lw_idx_1 * rtb_Sum_b4;

      /* Product: '<S286>/Product2' incorporates:
       *  Product: '<S288>/Product1'
       */
      rtb_DiscreteTransferFcn1 = rtb_Abs1 * Merge1;

      /* Product: '<S286>/Product6' incorporates:
       *  Product: '<S288>/Product7'
       */
      rtb_Sum1_ob = Merge1 * Merge1;

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
      autocodePlant_B->ZeroOrderHold[3] = ((((0.5 - rtb_Sum1_ob) -
        rtb_UnaryMinus1_o) * 2.0 * rtb_velBdy_mps[0] + (rtb_Switch_d_idx_2 +
        rtb_Switch_d_idx_1) * 2.0 * rtb_velBdy_mps[1]) + (rtb_Switch_d_idx_0 -
        rtb_DiscreteTransferFcn1) * 2.0 * rtb_velBdy_mps[2]) +
        autocodePlant_B->DiscreteTransferFcn3;

      /* Product: '<S287>/Product3' incorporates:
       *  Product: '<S288>/Product3'
       */
      rtb_Sum_b4 *= Merge1;

      /* Product: '<S287>/Product2' incorporates:
       *  Product: '<S288>/Product2'
       */
      rtb_Abs1 *= rtb_Lw_idx_1;

      /* Sum: '<S287>/Sum3' incorporates:
       *  Constant: '<S287>/Constant'
       *  Product: '<S287>/Product6'
       *  Sum: '<S288>/Sum3'
       */
      rtb_Lw_idx_1 = 0.5 - rtb_Lw_idx_1 * rtb_Lw_idx_1;

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
      autocodePlant_B->ZeroOrderHold[4] = (((rtb_Lw_idx_1 - rtb_UnaryMinus1_o) *
        2.0 * rtb_velBdy_mps[1] + (rtb_Switch_d_idx_2 - rtb_Switch_d_idx_1) *
        2.0 * rtb_velBdy_mps[0]) + (rtb_Abs1 + rtb_Sum_b4) * 2.0 *
        rtb_velBdy_mps[2]) + autocodePlant_B->DiscreteTransferFcn4;
      autocodePlant_B->ZeroOrderHold[5] = (((rtb_Switch_d_idx_0 +
        rtb_DiscreteTransferFcn1) * 2.0 * rtb_velBdy_mps[0] + (rtb_Sum_b4 -
        rtb_Abs1) * 2.0 * rtb_velBdy_mps[1]) + (rtb_Lw_idx_1 - rtb_Sum1_ob) *
        2.0 * rtb_velBdy_mps[2]) + autocodePlant_B->DiscreteTransferFcn5;
    }

    /* Product: '<S106>/Product2' incorporates:
     *  Gain: '<S106>/P0'
     */
    rtb_Product2_l3 *= 101325.0 * rtb_TT0gLR;

    /* RateTransition: '<S174>/Rate Transition1' */
    if (tmp) {
      if (tmp_0) {
        /* RateTransition: '<S174>/Rate Transition1' */
        autocodePlant_B->RateTransition1 =
          autocodePlant_DW->RateTransition1_Buffer0;
      }

      /* Gain: '<S185>/Output' incorporates:
       *  RandomNumber: '<S185>/White Noise'
       */
      autocodePlant_B->Output_g = sqrt(sensorParams.baroPSDWhite) / 0.1 *
        autocodePlant_DW->NextOutput_e;

      /* BusCreator generated from: '<Root>/sensor_bus' incorporates:
       *  DiscreteTransferFcn: '<S171>/Discrete Transfer Fcn2'
       *  Outport: '<Root>/sensor_bus'
       *  Sum: '<S171>/Sum1'
       *  UnitDelay: '<S174>/Unit Delay'
       */
      autocodePlant_Y_sensor_bus_i->baroMeas_Pa = (autocodePlant_B->Output_g +
        rtb_Product2_l3) + autocodePlant_DW->DiscreteTransferFcn2_states_h;
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[0] = rtb_bias_n[0];
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[0] = rtb_bias[0];
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[0] = rtb_ZeroOrderHold[0];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[0] = rtb_ZeroOrderHold_i[0];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[0] = rtb_ZeroOrderHold_g[0];
      autocodePlant_Y_sensor_bus_i->velNedMeas_mps[0] =
        autocodePlant_DW->UnitDelay_DSTATE[3];
      autocodePlant_Y_sensor_bus_i->gpsLLA_na[0] =
        autocodePlant_DW->UnitDelay_DSTATE[0];
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[1] = rtb_bias_n[1];
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[1] = rtb_bias[1];
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[1] = rtb_ZeroOrderHold[1];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[1] = rtb_ZeroOrderHold_i[1];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[1] = rtb_ZeroOrderHold_g[1];
      autocodePlant_Y_sensor_bus_i->velNedMeas_mps[1] =
        autocodePlant_DW->UnitDelay_DSTATE[4];
      autocodePlant_Y_sensor_bus_i->gpsLLA_na[1] =
        autocodePlant_DW->UnitDelay_DSTATE[1];
      autocodePlant_Y_sensor_bus_i->truth_bus.gyroBiasTrue_rps[2] = rtb_bias_n[2];
      autocodePlant_Y_sensor_bus_i->truth_bus.accBiasTrue_mps2[2] = rtb_bias[2];
      autocodePlant_Y_sensor_bus_i->fBdyMeas_mps2[2] = rtb_ZeroOrderHold[2];
      autocodePlant_Y_sensor_bus_i->wBdyMeas_rps[2] = rtb_ZeroOrderHold_i[2];
      autocodePlant_Y_sensor_bus_i->magBdyMeas_nT[2] = rtb_ZeroOrderHold_g[2];
      autocodePlant_Y_sensor_bus_i->velNedMeas_mps[2] =
        autocodePlant_DW->UnitDelay_DSTATE[5];
      autocodePlant_Y_sensor_bus_i->gpsLLA_na[2] =
        autocodePlant_DW->UnitDelay_DSTATE[2];
      autocodePlant_Y_sensor_bus_i->gpsFix_b = autocodePlant_B->RateTransition1;
    }

    /* Outport: '<Root>/plant_bus' incorporates:
     *  BusCreator generated from: '<Root>/plant_bus'
     *  Sum: '<S11>/Sum'
     *  Sum: '<S12>/Sum'
     *  Sum: '<S15>/Sum'
     *  Sum: '<S9>/Sum'
     */
    autocodePlant_Y_plant_bus_e->enviroment_bus.temp_K = rtb_UnitConversion;
    autocodePlant_Y_plant_bus_e->enviroment_bus.a_mps = rtb_UnitConversion_e;
    autocodePlant_Y_plant_bus_e->enviroment_bus.pressure_Pa = rtb_Product2_l3;
    autocodePlant_Y_plant_bus_e->enviroment_bus.rho_kgpm3 = rtb_Product3_eg;
    autocodePlant_Y_plant_bus_e->enviroment_bus.onRail_b = rtb_max_relop_c;
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.aoa_deg = rtb_UnaryMinus1;
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.liftSign_na =
      rtb_MediumHighAltitudeIntensity;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.aoa_deg =
      rtb_sigma_ugsigma_vg;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.liftSign_na = rtb_Sign1;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.aoa_deg = rtb_Gain_nu;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.liftSign_na = rtb_Sign1_e;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.aoa_deg =
      rtb_UnitDelay2_idx_3;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.liftSign_na = rtb_Sign1_l;
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.aoa_deg = rtb_Gain_n;
    autocodePlant_Y_plant_bus_e->enviroment_bus.airspeed_mps[0] =
      rtb_VectorConcatenate[0];
    autocodePlant_Y_plant_bus_e->enviroment_bus.windBdy_mps[0] = rtb_Sum_e[0];
    autocodePlant_Y_plant_bus_e->enviroment_bus.airW_rps[0] = rtb_Product_ab[0];
    autocodePlant_Y_plant_bus_e->aero_bus.aeroMoment_Nm[0] = rtb_Delay[0];
    autocodePlant_Y_plant_bus_e->aero_bus.aeroForce_N[0] = rtb_Delay[3];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finMoment_Nm[0] = rtb_Sum_j[0];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finForce_N[0] = rtb_Sum1_gf[0];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.airspeedFin_mps[0] =
      rtb_Product_lj[0];
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finMoment_Nm[0] =
      rtb_UnaryMinus_o3;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finForce_N[0] =
      rtb_Product4_a;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.airspeedFin_mps[0] =
      rtb_Sum_k[0];
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finMoment_Nm[0] = rtb_Sum_pz
      [0];
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finForce_N[0] =
      rtb_Sum1_hj_idx_0;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.airspeedFin_mps[0] =
      rtb_Sum_cy[0];
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finMoment_Nm[0] = rtb_Sum_mu
      [0];
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finForce_N[0] =
      rtb_Sum1_nc_idx_0;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.airspeedFin_mps[0] =
      rtb_Sum_aw[0];
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyMoment_Nm[0] =
      rtb_MathFunction[0];
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyForce_N[0] =
      rtb_Product6_kk[0];
    autocodePlant_Y_plant_bus_e->eom_bus.posNed_m[0] = rtb_posNed_m_idx_0;
    autocodePlant_Y_plant_bus_e->enviroment_bus.airspeed_mps[1] =
      rtb_VectorConcatenate[1];
    autocodePlant_Y_plant_bus_e->enviroment_bus.windBdy_mps[1] = rtb_Sum_e[1];
    autocodePlant_Y_plant_bus_e->enviroment_bus.airW_rps[1] = rtb_Product_ab[1];
    autocodePlant_Y_plant_bus_e->aero_bus.aeroMoment_Nm[1] = rtb_Delay[1];
    autocodePlant_Y_plant_bus_e->aero_bus.aeroForce_N[1] = rtb_Delay[4];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finMoment_Nm[1] = rtb_Sum_j[1];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finForce_N[1] = rtb_Sum1_gf[1];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.airspeedFin_mps[1] =
      rtb_LowAltitudeScaleLength;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finMoment_Nm[1] =
      rtb_UnaryMinus1_c;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finForce_N[1] =
      rtb_Sum1_hwh_idx_1;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.airspeedFin_mps[1] =
      rtb_Sum_k[1];
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finMoment_Nm[1] = rtb_Sum_pz
      [1];
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finForce_N[1] =
      rtb_Sum1_hj_idx_1;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.airspeedFin_mps[1] =
      Sum_bx_tmp_1;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finMoment_Nm[1] = rtb_Sum_mu
      [1];
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finForce_N[1] =
      rtb_DiscreteTransferFcn2;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.airspeedFin_mps[1] =
      Sum_a_tmp;
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyMoment_Nm[1] =
      rtb_MathFunction[1];
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyForce_N[1] =
      rtb_Product6_kk[1];
    autocodePlant_Y_plant_bus_e->eom_bus.posNed_m[1] = rtb_posNed_m_idx_1;
    autocodePlant_Y_plant_bus_e->enviroment_bus.airspeed_mps[2] =
      rtb_VectorConcatenate[2];
    autocodePlant_Y_plant_bus_e->enviroment_bus.windBdy_mps[2] = rtb_Sum_e[2];
    autocodePlant_Y_plant_bus_e->enviroment_bus.airW_rps[2] = rtb_Product_ab[2];
    autocodePlant_Y_plant_bus_e->aero_bus.aeroMoment_Nm[2] = rtb_Delay[2];
    autocodePlant_Y_plant_bus_e->aero_bus.aeroForce_N[2] = rtb_Delay[5];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finMoment_Nm[2] = rtb_Sum_j[2];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.finForce_N[2] = rtb_Sum1_gf[2];
    autocodePlant_Y_plant_bus_e->aero_bus.fin1_bus.airspeedFin_mps[2] =
      rtb_sincos_o2_f_idx_0;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finMoment_Nm[2] =
      rtb_Sum_a_idx_2;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.finForce_N[2] =
      rtb_Product8_ne;
    autocodePlant_Y_plant_bus_e->aero_bus.fin2_bus.airspeedFin_mps[2] =
      rtb_Sum_k[2];
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finMoment_Nm[2] = rtb_Sum_pz
      [2];
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.finForce_N[2] =
      rtb_UnaryMinus1_e;
    autocodePlant_Y_plant_bus_e->aero_bus.fin3_bus.airspeedFin_mps[2] =
      Sum_bx_tmp_0;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finMoment_Nm[2] = rtb_Sum_mu
      [2];
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.finForce_N[2] =
      rtb_UnitDelay2_idx_0;
    autocodePlant_Y_plant_bus_e->aero_bus.fin4_bus.airspeedFin_mps[2] =
      Sum_bx_tmp;
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyMoment_Nm[2] =
      rtb_UnaryMinus_n;
    autocodePlant_Y_plant_bus_e->aero_bus.body_bus.bodyForce_N[2] =
      rtb_Product6_kk[2];
    autocodePlant_Y_plant_bus_e->eom_bus.posNed_m[2] = rtb_posNed_m_idx_2;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[0] = rtb_q_na_idx_0;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[1] = rtb_q_na_idx_1;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[2] = rtb_q_na_idx_2;
    autocodePlant_Y_plant_bus_e->eom_bus.q_na[3] = rtb_q_na_idx_3;
    for (i = 0; i < 3; i++) {
      autocodePlant_Y_plant_bus_e->eom_bus.velBdy_mps[i] = rtb_velBdy_mps[i];
      autocodePlant_Y_plant_bus_e->eom_bus.wBdy_rps[i] = rtb_wBdy_rps[i];

      /* Sum: '<S161>/Subtract' incorporates:
       *  Product: '<S161>/Matrix Multiply1'
       *  Sum: '<S167>/Add'
       *  Sum: '<S168>/Sum'
       */
      rtb_VectorConcatenate[i] = (autocodePlant_B->Product_h[i] -
        (rtb_ElementProduct[i] - rtb_ElementProduct[i + 3])) -
        ((autocodePlant_ConstB.dIdt[i + 3] * rtb_wBdy_rps[1] +
          autocodePlant_ConstB.dIdt[i] * rtb_wBdy_rps[0]) +
         autocodePlant_ConstB.dIdt[i + 6] * rtb_wBdy_rps[2]);
    }

    /* Product: '<S161>/Product1' incorporates:
     *  Constant: '<S5>/Constant1'
     *  Outport: '<Root>/plant_bus'
     */
    rt_mldivide_U1d3x3_U2d_9O8lG8ax(&vehicleParams.inertia_kgm2[0],
      rtb_VectorConcatenate, autocodePlant_Y_plant_bus_e->eom_bus.wDotBdy_rps2);
    if (tmp) {
      /* Assertion: '<S197>/Assertion' incorporates:
       *  Constant: '<S197>/max_val'
       *  Constant: '<S197>/min_val'
       *  Logic: '<S197>/conjunction'
       *  RelationalOperator: '<S197>/max_relop'
       *  RelationalOperator: '<S197>/min_relop'
       */
      utAssert((rtb_UnitDelay2_idx_1 >= -1000.0) && (rtb_UnitDelay2_idx_1 <=
                850000.0));

      /* Assertion: '<S198>/Assertion' incorporates:
       *  Constant: '<S198>/max_val'
       *  Constant: '<S198>/min_val'
       *  Logic: '<S198>/conjunction'
       *  RelationalOperator: '<S198>/max_relop'
       *  RelationalOperator: '<S198>/min_relop'
       */
      utAssert((rtb_FlatEarthtoLLA_o1_idx_0 >= -90.0) &&
               (rtb_FlatEarthtoLLA_o1_idx_0 <= 90.0));

      /* Assertion: '<S199>/Assertion' incorporates:
       *  Constant: '<S199>/max_val'
       *  Constant: '<S199>/min_val'
       *  Logic: '<S199>/conjunction'
       *  RelationalOperator: '<S199>/max_relop'
       *  RelationalOperator: '<S199>/min_relop'
       */
      utAssert((rtb_FlatEarthtoLLA_o1_idx_1 >= -180.0) &&
               (rtb_FlatEarthtoLLA_o1_idx_1 <= 180.0));

      /* Assertion: '<S201>/Assertion' incorporates:
       *  Constant: '<S201>/max_val'
       *  Constant: '<S201>/min_val'
       *  Logic: '<S201>/conjunction'
       *  RelationalOperator: '<S201>/max_relop'
       *  RelationalOperator: '<S201>/min_relop'
       */
      utAssert((rtb_Sum_gx >= 0.0) && (rtb_Sum_gx <= 5.0));

      /* Gain: '<S176>/Output' */
      autocodePlant_B->Output_o[0] = sensorParams.accPSDGM[0];
      autocodePlant_B->Output_o[0] = sqrt(autocodePlant_B->Output_o[0]);

      /* Gain: '<S176>/Output' incorporates:
       *  RandomNumber: '<S176>/White Noise'
       */
      autocodePlant_B->Output_o[0] = autocodePlant_B->Output_o[0] / 0.1 *
        autocodePlant_DW->NextOutput_kd;

      /* Gain: '<S186>/Output' */
      autocodePlant_B->Output_e[0] = sensorParams.gyroPSDGM[0];
      autocodePlant_B->Output_e[0] = sqrt(autocodePlant_B->Output_e[0]);

      /* Gain: '<S186>/Output' incorporates:
       *  RandomNumber: '<S186>/White Noise'
       */
      autocodePlant_B->Output_e[0] = autocodePlant_B->Output_e[0] / 0.1 *
        autocodePlant_DW->NextOutput_ae;

      /* Gain: '<S176>/Output' */
      autocodePlant_B->Output_o[1] = sensorParams.accPSDGM[1];
      autocodePlant_B->Output_o[1] = sqrt(autocodePlant_B->Output_o[1]);

      /* Gain: '<S176>/Output' incorporates:
       *  RandomNumber: '<S176>/White Noise'
       */
      autocodePlant_B->Output_o[1] = autocodePlant_B->Output_o[1] / 0.1 *
        autocodePlant_DW->NextOutput_kd;

      /* Gain: '<S186>/Output' */
      autocodePlant_B->Output_e[1] = sensorParams.gyroPSDGM[1];
      autocodePlant_B->Output_e[1] = sqrt(autocodePlant_B->Output_e[1]);

      /* Gain: '<S186>/Output' incorporates:
       *  RandomNumber: '<S186>/White Noise'
       */
      autocodePlant_B->Output_e[1] = autocodePlant_B->Output_e[1] / 0.1 *
        autocodePlant_DW->NextOutput_ae;

      /* Gain: '<S176>/Output' */
      autocodePlant_B->Output_o[2] = sensorParams.accPSDGM[2];
      autocodePlant_B->Output_o[2] = sqrt(autocodePlant_B->Output_o[2]);

      /* Gain: '<S176>/Output' incorporates:
       *  RandomNumber: '<S176>/White Noise'
       */
      autocodePlant_B->Output_o[2] = autocodePlant_B->Output_o[2] / 0.1 *
        autocodePlant_DW->NextOutput_kd;

      /* Gain: '<S186>/Output' */
      autocodePlant_B->Output_e[2] = sensorParams.gyroPSDGM[2];
      autocodePlant_B->Output_e[2] = sqrt(autocodePlant_B->Output_e[2]);

      /* Gain: '<S186>/Output' incorporates:
       *  RandomNumber: '<S186>/White Noise'
       */
      autocodePlant_B->Output_e[2] = autocodePlant_B->Output_e[2] / 0.1 *
        autocodePlant_DW->NextOutput_ae;

      /* UnitDelay: '<S169>/Unit Delay' */
      rtb_Abs1 = autocodePlant_DW->UnitDelay_DSTATE_i;

      /* Sum: '<S169>/Sum' incorporates:
       *  Constant: '<S169>/Constant'
       *  UnitDelay: '<S169>/Unit Delay'
       */
      autocodePlant_DW->UnitDelay_DSTATE_i += simParams.dt_s;

      /* Lookup_n-D: '<S6>/1-D Lookup Table' incorporates:
       *  RandomNumber: '<S184>/White Noise'
       */
      rtb_uDLookupTable = look1_binlcpw(rtb_Abs1, &motorParams.time[0],
        &motorParams.thrust[0], 25U);

      /* Gain: '<S184>/Output' incorporates:
       *  RandomNumber: '<S184>/White Noise'
       */
      autocodePlant_B->Output_n = sqrt(sensorParams.baroPSDGM) / 0.1 *
        autocodePlant_DW->NextOutput_mv;

      /* RateTransition: '<S174>/Rate Transition' */
      if (rtb_RelationalOperator) {
        /* RateTransition: '<S174>/Rate Transition' */
        for (i = 0; i < 6; i++) {
          autocodePlant_B->RateTransition[i] =
            autocodePlant_DW->RateTransition_Buffer0[i];
        }

        /* End of RateTransition: '<S174>/Rate Transition' */
      }
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
    boolean_T tmp_0;
    boolean_T tmp_1;
    tmp = (rtmIsMajorTimeStep(autocodePlant_M) &&
           autocodePlant_M->Timing.TaskCounters.TID[1] == 0);
    if (tmp) {
      /* Update for RandomNumber: '<S130>/White Noise' */
      autocodePlant_DW->NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed[0]);
      autocodePlant_DW->NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed[1]);
      autocodePlant_DW->NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed[2]);
      autocodePlant_DW->NextOutput[3] = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed[3]);

      /* Update for Delay: '<S174>/Delay' */
      for (i = 0; i < 84; i++) {
        autocodePlant_DW->Delay_DSTATE[i] = autocodePlant_DW->Delay_DSTATE[i + 6];
      }

      for (i = 0; i < 6; i++) {
        autocodePlant_DW->Delay_DSTATE[i + 84] = autocodePlant_B->
          RateTransition[i];
      }

      /* End of Update for Delay: '<S174>/Delay' */
    }

    /* Update for RateTransition: '<S174>/Rate Transition1' */
    tmp_0 = (rtmIsMajorTimeStep(autocodePlant_M) &&
             autocodePlant_M->Timing.TaskCounters.TID[3] == 0);
    if (tmp_0) {
      /* Update for UniformRandomNumber: '<S174>/Uniform Random Number' */
      autocodePlant_DW->UniformRandomNumber_NextOutput =
        rt_urand_Upu32_Yd_f_pw_snf(&autocodePlant_DW->RandSeed_j);
    }

    if (tmp) {
      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE_h[0] = autocodePlant_U_control_deg[0];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[0] = autocodePlant_B->Backlash[0];

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE_h[1] = autocodePlant_U_control_deg[1];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[1] = autocodePlant_B->Backlash[1];

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE_h[2] = autocodePlant_U_control_deg[2];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[2] = autocodePlant_B->Backlash[2];

      /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
       *  Inport: '<Root>/control_deg'
       */
      autocodePlant_DW->UnitDelay_DSTATE_h[3] = autocodePlant_U_control_deg[3];

      /* Update for Backlash: '<S7>/Backlash' */
      autocodePlant_DW->PrevY[3] = autocodePlant_B->Backlash[3];

      /* Update for Memory: '<S223>/otime' incorporates:
       *  Constant: '<S173>/decimal year'
       */
      autocodePlant_DW->otime_PreviousInput = envParams.date_y;

      /* Update for Memory: '<S222>/olon' */
      autocodePlant_DW->olon_PreviousInput = autocodePlant_B->Switch;

      /* Update for Memory: '<S221>/olat' */
      autocodePlant_DW->olat_PreviousInput = autocodePlant_B->Switch_l;

      /* Update for Memory: '<S221>/oalt' */
      autocodePlant_DW->oalt_PreviousInput = autocodePlant_B->Gain;

      /* Update for Delay: '<S6>/Delay' */
      for (i = 0; i < 1999; i++) {
        autocodePlant_DW->Delay_DSTATE_h[i] = autocodePlant_DW->Delay_DSTATE_h[i
          + 1];
      }

      autocodePlant_DW->Delay_DSTATE_h[1999] = rtb_uDLookupTable;

      /* End of Update for Delay: '<S6>/Delay' */

      /* Update for DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states = autocodePlant_B->Output_o
        [0] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn2_states;

      /* Update for DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states = autocodePlant_B->Output_o
        [1] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn1_states;

      /* Update for DiscreteTransferFcn: '<S170>/Discrete Transfer Fcn3' */
      autocodePlant_DW->DiscreteTransferFcn3_states = autocodePlant_B->Output_o
        [2] - 0.99995 * autocodePlant_DW->DiscreteTransferFcn3_states;

      /* Update for RandomNumber: '<S177>/White Noise' */
      autocodePlant_DW->NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_e);

      /* Update for RandomNumber: '<S190>/White Noise' */
      autocodePlant_DW->NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_a);

      /* Update for UnitDelay: '<S172>/Unit Delay' */
      autocodePlant_DW->UnitDelay_DSTATE_c[0] = autocodePlant_B->fBdy_mps2[0];
      autocodePlant_DW->UnitDelay_DSTATE_c[1] = autocodePlant_B->fBdy_mps2[1];
      autocodePlant_DW->UnitDelay_DSTATE_c[2] = autocodePlant_B->fBdy_mps2[2];

      /* Update for DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn' */
      autocodePlant_DW->DiscreteTransferFcn_states = autocodePlant_B->Output_e[0]
        - 0.99995 * autocodePlant_DW->DiscreteTransferFcn_states;

      /* Update for DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states_b =
        autocodePlant_B->Output_e[1] - 0.99995 *
        autocodePlant_DW->DiscreteTransferFcn1_states_b;

      /* Update for DiscreteTransferFcn: '<S172>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_g =
        autocodePlant_B->Output_e[2] - 0.99995 *
        autocodePlant_DW->DiscreteTransferFcn2_states_g;

      /* Update for RandomNumber: '<S187>/White Noise' */
      autocodePlant_DW->NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_l);
    }

    /* Update for RateTransition: '<S174>/Rate Transition' */
    tmp_1 = (rtmIsMajorTimeStep(autocodePlant_M) &&
             autocodePlant_M->Timing.TaskCounters.TID[2] == 0);
    if (tmp_1) {
      /* Update for RandomNumber: '<S276>/White Noise' */
      autocodePlant_DW->NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_c);

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn' */
      autocodePlant_DW->DiscreteTransferFcn_states_k =
        autocodePlant_DW->DiscreteTransferFcn_tmp;

      /* Update for RandomNumber: '<S277>/White Noise' */
      autocodePlant_DW->NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_m);

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn1' */
      autocodePlant_DW->DiscreteTransferFcn1_states_bi =
        autocodePlant_DW->DiscreteTransferFcn1_tmp;

      /* Update for RandomNumber: '<S278>/White Noise' */
      autocodePlant_DW->NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_e0);

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_d =
        autocodePlant_DW->DiscreteTransferFcn2_tmp;

      /* Update for RandomNumber: '<S274>/White Noise' */
      autocodePlant_DW->NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_h);

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn3' */
      autocodePlant_DW->DiscreteTransferFcn3_states_g =
        autocodePlant_DW->DiscreteTransferFcn3_tmp;

      /* Update for RandomNumber: '<S275>/White Noise' */
      autocodePlant_DW->NextOutput_n = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_b);

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn4' */
      autocodePlant_DW->DiscreteTransferFcn4_states =
        autocodePlant_DW->DiscreteTransferFcn4_tmp;

      /* Update for RandomNumber: '<S279>/White Noise' */
      autocodePlant_DW->NextOutput_p = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_eu);

      /* Update for DiscreteTransferFcn: '<S174>/Discrete Transfer Fcn5' */
      autocodePlant_DW->DiscreteTransferFcn5_states =
        autocodePlant_DW->DiscreteTransferFcn5_tmp;
    }

    /* Update for RateTransition: '<S174>/Rate Transition1' */
    if (tmp_0) {
      autocodePlant_DW->RateTransition1_Buffer0 =
        autocodePlant_B->RelationalOperator;
    }

    if (tmp) {
      /* Update for RandomNumber: '<S185>/White Noise' */
      autocodePlant_DW->NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_bf);

      /* Update for DiscreteTransferFcn: '<S171>/Discrete Transfer Fcn2' */
      autocodePlant_DW->DiscreteTransferFcn2_states_h =
        autocodePlant_B->Output_n - 0.99998 *
        autocodePlant_DW->DiscreteTransferFcn2_states_h;

      /* Update for RandomNumber: '<S176>/White Noise' */
      autocodePlant_DW->NextOutput_kd = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_p);

      /* Update for RandomNumber: '<S186>/White Noise' */
      autocodePlant_DW->NextOutput_ae = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_pa);

      /* Update for RandomNumber: '<S184>/White Noise' */
      autocodePlant_DW->NextOutput_mv = rt_nrand_Upu32_Yd_f_pw_snf
        (&autocodePlant_DW->RandSeed_pb);
    }

    /* Update for RateTransition: '<S174>/Rate Transition' */
    if (tmp_1) {
      for (i = 0; i < 6; i++) {
        autocodePlant_DW->RateTransition_Buffer0[i] =
          autocodePlant_B->ZeroOrderHold[i];
      }
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
  _rtXdot->uDOFQuaternion_CSTATE[0] = autocodePlant_B->Sum_ah[0] /
    vehicleParams.mass_kg - (autocodePlant_X->uDOFQuaternion_CSTATE[2] *
    autocodePlant_X->uDOFQuaternion_CSTATE[7] -
    autocodePlant_X->uDOFQuaternion_CSTATE[1] *
    autocodePlant_X->uDOFQuaternion_CSTATE[8]);
  _rtXdot->uDOFQuaternion_CSTATE[1] = autocodePlant_B->Sum_ah[1] /
    vehicleParams.mass_kg - (autocodePlant_X->uDOFQuaternion_CSTATE[0] *
    autocodePlant_X->uDOFQuaternion_CSTATE[8] -
    autocodePlant_X->uDOFQuaternion_CSTATE[2] *
    autocodePlant_X->uDOFQuaternion_CSTATE[6]);
  _rtXdot->uDOFQuaternion_CSTATE[2] = autocodePlant_B->Sum_ah[2] /
    vehicleParams.mass_kg - (autocodePlant_X->uDOFQuaternion_CSTATE[1] *
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
  pData_idx_0 = (vehicleParams.inertia_kgm2[0] *
                 autocodePlant_X->uDOFQuaternion_CSTATE[6] +
                 vehicleParams.inertia_kgm2[3] *
                 autocodePlant_X->uDOFQuaternion_CSTATE[7]) +
    vehicleParams.inertia_kgm2[6] * autocodePlant_X->uDOFQuaternion_CSTATE[8];
  pData_idx_1 = (vehicleParams.inertia_kgm2[1] *
                 autocodePlant_X->uDOFQuaternion_CSTATE[6] +
                 vehicleParams.inertia_kgm2[4] *
                 autocodePlant_X->uDOFQuaternion_CSTATE[7]) +
    vehicleParams.inertia_kgm2[7] * autocodePlant_X->uDOFQuaternion_CSTATE[8];
  pData_idx_2 = (vehicleParams.inertia_kgm2[2] *
                 autocodePlant_X->uDOFQuaternion_CSTATE[6] +
                 vehicleParams.inertia_kgm2[5] *
                 autocodePlant_X->uDOFQuaternion_CSTATE[7]) +
    vehicleParams.inertia_kgm2[8] * autocodePlant_X->uDOFQuaternion_CSTATE[8];
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
  uDOFQuaternion_CSTATE_tmp = 1.0 / (((vehicleParams.inertia_kgm2[4] *
    vehicleParams.inertia_kgm2[8] - vehicleParams.inertia_kgm2[5] *
    vehicleParams.inertia_kgm2[7]) * vehicleParams.inertia_kgm2[0] -
    (vehicleParams.inertia_kgm2[1] * vehicleParams.inertia_kgm2[8] -
     vehicleParams.inertia_kgm2[2] * vehicleParams.inertia_kgm2[7]) *
    vehicleParams.inertia_kgm2[3]) + (vehicleParams.inertia_kgm2[1] *
    vehicleParams.inertia_kgm2[5] - vehicleParams.inertia_kgm2[2] *
    vehicleParams.inertia_kgm2[4]) * vehicleParams.inertia_kgm2[6]);
  _rtXdot->uDOFQuaternion_CSTATE[6] = ((vehicleParams.inertia_kgm2[4] *
    vehicleParams.inertia_kgm2[8] - vehicleParams.inertia_kgm2[5] *
    vehicleParams.inertia_kgm2[7]) * uDOFQuaternion_CSTATE_tmp *
    uDOFQuaternion_CSTATE_tmp_0 + -(vehicleParams.inertia_kgm2[3] *
    vehicleParams.inertia_kgm2[8] - vehicleParams.inertia_kgm2[5] *
    vehicleParams.inertia_kgm2[6]) * uDOFQuaternion_CSTATE_tmp *
    uDOFQuaternion_CSTATE_tmp_1) + (vehicleParams.inertia_kgm2[3] *
    vehicleParams.inertia_kgm2[7] - vehicleParams.inertia_kgm2[4] *
    vehicleParams.inertia_kgm2[6]) * uDOFQuaternion_CSTATE_tmp * pData_idx_2;
  _rtXdot->uDOFQuaternion_CSTATE[7] = (-(vehicleParams.inertia_kgm2[1] *
    vehicleParams.inertia_kgm2[8] - vehicleParams.inertia_kgm2[2] *
    vehicleParams.inertia_kgm2[7]) * uDOFQuaternion_CSTATE_tmp *
    uDOFQuaternion_CSTATE_tmp_0 + (vehicleParams.inertia_kgm2[0] *
    vehicleParams.inertia_kgm2[8] - vehicleParams.inertia_kgm2[2] *
    vehicleParams.inertia_kgm2[6]) * uDOFQuaternion_CSTATE_tmp *
    uDOFQuaternion_CSTATE_tmp_1) + -(vehicleParams.inertia_kgm2[0] *
    vehicleParams.inertia_kgm2[7] - vehicleParams.inertia_kgm2[1] *
    vehicleParams.inertia_kgm2[6]) * uDOFQuaternion_CSTATE_tmp * pData_idx_2;
  _rtXdot->uDOFQuaternion_CSTATE[8] = ((vehicleParams.inertia_kgm2[1] *
    vehicleParams.inertia_kgm2[5] - vehicleParams.inertia_kgm2[2] *
    vehicleParams.inertia_kgm2[4]) * uDOFQuaternion_CSTATE_tmp *
    uDOFQuaternion_CSTATE_tmp_0 + -(vehicleParams.inertia_kgm2[0] *
    vehicleParams.inertia_kgm2[5] - vehicleParams.inertia_kgm2[2] *
    vehicleParams.inertia_kgm2[3]) * uDOFQuaternion_CSTATE_tmp *
    uDOFQuaternion_CSTATE_tmp_1) + (vehicleParams.inertia_kgm2[0] *
    vehicleParams.inertia_kgm2[4] - vehicleParams.inertia_kgm2[1] *
    vehicleParams.inertia_kgm2[3]) * uDOFQuaternion_CSTATE_tmp * pData_idx_2;
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
    real_T cp;
    real_T cp_tmp;
    real_T cr;
    real_T cr_tmp;
    real_T cy;
    real_T cy_tmp;
    real_T sp;
    real_T uDOFQuaternion_CSTATE_tmp;
    int32_T i;

    /* Start for If: '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    autocodePlant_DW->ifHeightMaxlowaltitudeelseifHei = -1;

    /* Start for If: '<S125>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
    autocodePlant_DW->ifHeightMaxlowaltitudeelseifH_m = -1;

    /* Start for If: '<S211>/If' */
    autocodePlant_DW->If_ActiveSubsystem = -1;

    /* InitializeConditions for EOM6DOFBodyQuat: '<S5>/6DOF (Quaternion)' */
    autocodePlant_X->uDOFQuaternion_CSTATE[0] = icParams.velBdy_mps[0];
    autocodePlant_X->uDOFQuaternion_CSTATE[3] = icParams.posNed_m[0];
    autocodePlant_X->uDOFQuaternion_CSTATE[6] = icParams.rateBdy_rps[0];
    autocodePlant_X->uDOFQuaternion_CSTATE[1] = icParams.velBdy_mps[1];
    autocodePlant_X->uDOFQuaternion_CSTATE[4] = icParams.posNed_m[1];
    autocodePlant_X->uDOFQuaternion_CSTATE[7] = icParams.rateBdy_rps[1];
    autocodePlant_X->uDOFQuaternion_CSTATE[2] = icParams.velBdy_mps[2];
    autocodePlant_X->uDOFQuaternion_CSTATE[5] = icParams.posNed_m[2];
    autocodePlant_X->uDOFQuaternion_CSTATE[8] = icParams.rateBdy_rps[2];
    cr_tmp = icParams.eul_rad[0] / 2.0;
    cr = cos(cr_tmp);
    cp_tmp = icParams.eul_rad[1] / 2.0;
    cp = cos(cp_tmp);
    cy_tmp = icParams.eul_rad[2] / 2.0;
    cy = cos(cy_tmp);
    cr_tmp = sin(cr_tmp);
    sp = sin(cp_tmp);
    cy_tmp = sin(cy_tmp);
    cp_tmp = cr * cp;
    uDOFQuaternion_CSTATE_tmp = cr_tmp * sp;
    autocodePlant_X->uDOFQuaternion_CSTATE[9] = cp_tmp * cy +
      uDOFQuaternion_CSTATE_tmp * cy_tmp;
    cr *= sp;
    cp *= cr_tmp;
    autocodePlant_X->uDOFQuaternion_CSTATE[10] = cp * cy - cr * cy_tmp;
    autocodePlant_X->uDOFQuaternion_CSTATE[11] = cr * cy + cp * cy_tmp;
    autocodePlant_X->uDOFQuaternion_CSTATE[12] = cp_tmp * cy_tmp -
      uDOFQuaternion_CSTATE_tmp * cy;

    /* InitializeConditions for RandomNumber: '<S130>/White Noise' */
    autocodePlant_DW->RandSeed[0] = 1529675776U;
    autocodePlant_DW->NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed[0]);
    autocodePlant_DW->RandSeed[1] = 1529741312U;
    autocodePlant_DW->NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed[1]);
    autocodePlant_DW->RandSeed[2] = 1529806848U;
    autocodePlant_DW->NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed[2]);
    autocodePlant_DW->RandSeed[3] = 1529872384U;
    autocodePlant_DW->NextOutput[3] = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed[3]);

    /* InitializeConditions for UniformRandomNumber: '<S174>/Uniform Random Number' */
    autocodePlant_DW->RandSeed_j = 1144108930U;
    autocodePlant_DW->UniformRandomNumber_NextOutput =
      rt_urand_Upu32_Yd_f_pw_snf(&autocodePlant_DW->RandSeed_j);

    /* InitializeConditions for Backlash: '<S7>/Backlash' */
    autocodePlant_DW->PrevY[0] = 0.0;
    autocodePlant_DW->PrevY[1] = 0.0;
    autocodePlant_DW->PrevY[2] = 0.0;
    autocodePlant_DW->PrevY[3] = 0.0;

    /* InitializeConditions for Memory: '<S223>/otime' */
    autocodePlant_DW->otime_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S222>/olon' */
    autocodePlant_DW->olon_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S221>/olat' */
    autocodePlant_DW->olat_PreviousInput = -1000.0;

    /* InitializeConditions for Memory: '<S221>/oalt' */
    autocodePlant_DW->oalt_PreviousInput = -1000.0;

    /* InitializeConditions for RandomNumber: '<S177>/White Noise' */
    autocodePlant_DW->RandSeed_e = 1529675776U;
    autocodePlant_DW->NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_e);

    /* InitializeConditions for RandomNumber: '<S190>/White Noise' */
    autocodePlant_DW->RandSeed_a = 1529675776U;
    autocodePlant_DW->NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_a);

    /* InitializeConditions for RandomNumber: '<S187>/White Noise' */
    autocodePlant_DW->RandSeed_l = 1529675776U;
    autocodePlant_DW->NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_l);

    /* InitializeConditions for RandomNumber: '<S276>/White Noise' */
    autocodePlant_DW->RandSeed_c = 1144108930U;
    autocodePlant_DW->NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_c);

    /* InitializeConditions for RandomNumber: '<S277>/White Noise' */
    autocodePlant_DW->RandSeed_m = 65536U;
    autocodePlant_DW->NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_m);

    /* InitializeConditions for RandomNumber: '<S278>/White Noise' */
    autocodePlant_DW->RandSeed_e0 = 131072U;
    autocodePlant_DW->NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_e0);

    /* InitializeConditions for RandomNumber: '<S274>/White Noise' */
    autocodePlant_DW->RandSeed_h = 196608U;
    autocodePlant_DW->NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_h);

    /* InitializeConditions for RandomNumber: '<S275>/White Noise' */
    autocodePlant_DW->RandSeed_b = 262144U;
    autocodePlant_DW->NextOutput_n = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_b);

    /* InitializeConditions for RandomNumber: '<S279>/White Noise' */
    autocodePlant_DW->RandSeed_eu = 327680U;
    autocodePlant_DW->NextOutput_p = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_eu);

    /* InitializeConditions for RandomNumber: '<S185>/White Noise' */
    autocodePlant_DW->RandSeed_bf = 1529675776U;
    autocodePlant_DW->NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_bf);

    /* InitializeConditions for RandomNumber: '<S176>/White Noise' */
    autocodePlant_DW->RandSeed_p = 1529675776U;
    autocodePlant_DW->NextOutput_kd = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_p);

    /* InitializeConditions for RandomNumber: '<S186>/White Noise' */
    autocodePlant_DW->RandSeed_pa = 1529675776U;
    autocodePlant_DW->NextOutput_ae = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_pa);

    /* InitializeConditions for RandomNumber: '<S184>/White Noise' */
    autocodePlant_DW->RandSeed_pb = 1529675776U;
    autocodePlant_DW->NextOutput_mv = rt_nrand_Upu32_Yd_f_pw_snf
      (&autocodePlant_DW->RandSeed_pb);

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hwgw(s)' */
    /* InitializeConditions for Integrator: '<S136>/wg_p1' */
    autocodePlant_X->wg_p1_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S136>/wg_p2' */
    autocodePlant_X->wg_p2_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hwgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hvgw(s)' */
    /* InitializeConditions for Integrator: '<S135>/vg_p1' */
    autocodePlant_X->vg_p1_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S135>/vgw_p2' */
    autocodePlant_X->vgw_p2_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hvgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hugw(s)' */
    /* InitializeConditions for Integrator: '<S134>/ug_p' */
    autocodePlant_X->ug_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hugw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hpgw' */
    /* InitializeConditions for Integrator: '<S131>/pgw_p' */
    autocodePlant_X->pgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hpgw' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hqgw' */
    /* InitializeConditions for Integrator: '<S132>/qgw_p' */
    autocodePlant_X->qgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hqgw' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hrgw' */
    /* InitializeConditions for Integrator: '<S133>/rgw_p' */
    autocodePlant_X->rgw_p_CSTATE[0] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hrgw' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hwgw(s)' */
    /* InitializeConditions for Integrator: '<S136>/wg_p1' */
    autocodePlant_X->wg_p1_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S136>/wg_p2' */
    autocodePlant_X->wg_p2_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hwgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hvgw(s)' */
    /* InitializeConditions for Integrator: '<S135>/vg_p1' */
    autocodePlant_X->vg_p1_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S135>/vgw_p2' */
    autocodePlant_X->vgw_p2_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hvgw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S121>/Hugw(s)' */
    /* InitializeConditions for Integrator: '<S134>/ug_p' */
    autocodePlant_X->ug_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S121>/Hugw(s)' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hpgw' */
    /* InitializeConditions for Integrator: '<S131>/pgw_p' */
    autocodePlant_X->pgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hpgw' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hqgw' */
    /* InitializeConditions for Integrator: '<S132>/qgw_p' */
    autocodePlant_X->qgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hqgw' */

    /* SystemInitialize for Enabled SubSystem: '<S120>/Hrgw' */
    /* InitializeConditions for Integrator: '<S133>/rgw_p' */
    autocodePlant_X->rgw_p_CSTATE[1] = 0.0;

    /* End of SystemInitialize for SubSystem: '<S120>/Hrgw' */

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
