/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: autocodeModel.h
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

#ifndef autocodeModel_h_
#define autocodeModel_h_
#ifndef autocodeModel_COMMON_INCLUDES_
#define autocodeModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* autocodeModel_COMMON_INCLUDES_ */

#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_innerLoopAxis_bus_
#define DEFINED_TYPEDEF_FOR_innerLoopAxis_bus_

typedef struct {
  real_T control_deg;
  real_T controlMoment_Nm;
  boolean_T rateLimted_b;
  boolean_T saturated_b;
} innerLoopAxis_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_innerLoop_bus_
#define DEFINED_TYPEDEF_FOR_innerLoop_bus_

typedef struct {
  innerLoopAxis_bus pitchInnerLoop_bus;
  innerLoopAxis_bus yawInnerLoop_bus;
  innerLoopAxis_bus rollInnerLoop_bus;
} innerLoop_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_outerLoopAxis_bus_
#define DEFINED_TYPEDEF_FOR_outerLoopAxis_bus_

typedef struct {
  real_T rateCmd_rps;
  boolean_T rateLimited_b;
  boolean_T saturated_b;
} outerLoopAxis_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_outerLoop_bus_
#define DEFINED_TYPEDEF_FOR_outerLoop_bus_

typedef struct {
  outerLoopAxis_bus pitchOuterLoop_bus;
  outerLoopAxis_bus yawOuterLoop_bus;
  outerLoopAxis_bus rollOuterLoop_bus;
} outerLoop_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_controller_bus_
#define DEFINED_TYPEDEF_FOR_controller_bus_

typedef struct {
  outerLoop_bus outerLoop_bus;
  innerLoop_bus innerLoop_bus;
  real_T control_deg[4];
} controller_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_flightMode_
#define DEFINED_TYPEDEF_FOR_flightMode_

typedef enum {
  IDLE = 0,                            /* Default value */
  BOOST,
  ACTIVE,
  LOCKOUT
} flightMode;

#endif

#ifndef DEFINED_TYPEDEF_FOR_navigation_bus_
#define DEFINED_TYPEDEF_FOR_navigation_bus_

typedef struct {
  flightMode flightMode_enum;
  real_T qEst_na[4];
  real_T phiEst_rad;
  real_T thetaEst_rad;
  real_T psiEst_rad;
  real_T pEst_rps;
  real_T qEst_rps;
  real_T rEst_rps;
  real_T xAccEst_mps2;
  real_T yAccEst_mps2;
  real_T zAccEst_mps2;
  real_T accelBias_mps2[3];
  real_T gyroBias_rps[3];
  real_T dynPressureEst_Pa;
  real_T xVelEst_mps;
  real_T yVelEst_mps;
  real_T zVelEst_mps;
  real_T xPosEst_m;
  real_T yPosEst_m;
  real_T zPosEst_m;
} navigation_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_truth_bus_
#define DEFINED_TYPEDEF_FOR_truth_bus_

typedef struct {
  real_T gyroBiasTrue_rps[3];
  real_T accBiasTrue_mps2[3];
} truth_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_sensor_bus_
#define DEFINED_TYPEDEF_FOR_sensor_bus_

typedef struct {
  truth_bus truth_bus;
  real_T fBdyMeas_mps2[3];
  real_T wBdyMeas_rps[3];
  real_T magBdyMeas_nT[3];
  real_T baroMeas_Pa;
} sensor_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_cubQF2aidKgGXLVFilbPjH_
#define DEFINED_TYPEDEF_FOR_struct_cubQF2aidKgGXLVFilbPjH_

typedef struct {
  real_T debounce_s;
  real_T boostThreshold_mps2;
  real_T coastThresholdxAcc_mps2;
  real_T coastThresholdAlt_m;
  real_T controlTresholdPitchYaw_rad;
  real_T controlTresholdPitchYawRate_rps;
} struct_cubQF2aidKgGXLVFilbPjH;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T qEst_na[4];                   /* '<S423>/Merge' */
  real_T UnitDelay_2_DSTATE[4];        /* '<S406>/Unit Delay' */
  real_T UnitDelay_13_DSTATE[3];       /* '<S406>/Unit Delay' */
  real_T DiscreteTransferFcn1_states[6];/* '<S407>/Discrete Transfer Fcn1' */
  real_T GyroFilter_states[3];         /* '<S424>/Gyro Filter' */
  real_T UnitDelay_12_DSTATE[3];       /* '<S406>/Unit Delay' */
  real_T AccelFilter_states[3];        /* '<S407>/Accel Filter' */
  real_T AccelFilter_states_l[3];      /* '<S424>/Accel Filter' */
  real_T Delay_4_DSTATE[1500];         /* '<S422>/Delay' */
  real_T UnitDelay_DSTATE[3];          /* '<S422>/Unit Delay' */
  real_T DiscreteFIRFilter_states[297];/* '<S422>/Discrete FIR Filter' */
  real_T Delay_3_DSTATE[1500];         /* '<S422>/Delay' */
  real_T UnitDelay1_DSTATE[3];         /* '<S422>/Unit Delay1' */
  real_T DiscreteFIRFilter1_states[297];/* '<S422>/Discrete FIR Filter1' */
  real_T Delay_3_DSTATE_e[1500];       /* '<S429>/Delay' */
  real_T Integrator_DSTATE;            /* '<S324>/Integrator' */
  real_T Filter_DSTATE;                /* '<S319>/Filter' */
  real_T Delay_DSTATE;                 /* '<S343>/Delay' */
  real_T UnitDelay_15_DSTATE;          /* '<S406>/Unit Delay' */
  real_T UnitDelay_16_DSTATE;          /* '<S406>/Unit Delay' */
  real_T UnitDelay_17_DSTATE;          /* '<S406>/Unit Delay' */
  real_T Integrator_DSTATE_b;          /* '<S122>/Integrator' */
  real_T Filter_DSTATE_p;              /* '<S117>/Filter' */
  real_T Delay_DSTATE_p;               /* '<S149>/Delay' */
  real_T Integrator_DSTATE_g;          /* '<S264>/Integrator' */
  real_T Filter_DSTATE_n;              /* '<S259>/Filter' */
  real_T Delay_DSTATE_c;               /* '<S283>/Delay' */
  real_T Integrator_DSTATE_p;          /* '<S52>/Integrator' */
  real_T Filter_DSTATE_l;              /* '<S47>/Filter' */
  real_T Delay_DSTATE_f;               /* '<S79>/Delay' */
  real_T Integrator_DSTATE_l;          /* '<S384>/Integrator' */
  real_T Filter_DSTATE_c;              /* '<S379>/Filter' */
  real_T Delay_DSTATE_h;               /* '<S403>/Delay' */
  real_T Integrator_DSTATE_e;          /* '<S192>/Integrator' */
  real_T Filter_DSTATE_g;              /* '<S187>/Filter' */
  real_T Delay_DSTATE_e;               /* '<S219>/Delay' */
  real_T UnitDelay_18_DSTATE;          /* '<S406>/Unit Delay' */
  real_T UnitDelay_19_DSTATE;          /* '<S406>/Unit Delay' */
  real_T UnitDelay_20_DSTATE;          /* '<S406>/Unit Delay' */
  real_T UD_DSTATE;                    /* '<S218>/UD' */
  real_T UD_DSTATE_k;                  /* '<S78>/UD' */
  real_T UD_DSTATE_n;                  /* '<S148>/UD' */
  real_T UD_DSTATE_g;                  /* '<S282>/UD' */
  real_T UD_DSTATE_p;                  /* '<S402>/UD' */
  real_T UD_DSTATE_a;                  /* '<S342>/UD' */
  int32_T DiscreteFIRFilter_circBuf;   /* '<S422>/Discrete FIR Filter' */
  int32_T DiscreteFIRFilter1_circBuf;  /* '<S422>/Discrete FIR Filter1' */
  uint32_T temporalCounter_i1;         /* '<S409>/State Transition Table' */
  flightMode flightMode_enum;          /* '<S409>/State Transition Table' */
  flightMode UnitDelay_1_DSTATE;       /* '<S406>/Unit Delay' */
  uint8_T is_active_c4_autocodeModel;  /* '<S409>/State Transition Table' */
  uint8_T is_c4_autocodeModel;         /* '<S409>/State Transition Table' */
  boolean_T UnitDelay_DSTATE_n;        /* '<S4>/Unit Delay' */
  boolean_T icLoad;                    /* '<S343>/Delay' */
  boolean_T icLoad_k;                  /* '<S149>/Delay' */
  boolean_T icLoad_a;                  /* '<S283>/Delay' */
  boolean_T icLoad_f;                  /* '<S79>/Delay' */
  boolean_T icLoad_c;                  /* '<S403>/Delay' */
  boolean_T icLoad_d;                  /* '<S219>/Delay' */
  boolean_T boostThreshold_b;          /* '<S409>/State Transition Table' */
  boolean_T lockoutThreshold_b;        /* '<S409>/State Transition Table' */
  boolean_T coastThreshold_b;          /* '<S409>/State Transition Table' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T QuaternionstoDirectionCosin[9];
                          /* '<S429>/Quaternions to  Direction Cosine Matrix' */
} ConstB;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

/* External data declarations for dependent source files */
extern const sensor_bus autocodeModel_rtZsensor_bus;/* sensor_bus ground */
extern const navigation_bus autocodeModel_rtZnavigation_bus;/* navigation_bus ground */
extern const controller_bus autocodeModel_rtZcontroller_bus;/* controller_bus ground */
extern const ConstB rtConstB;          /* constant block i/o */

/* Model entry point functions */
extern void autocodeModel_initialize(RT_MODEL *const rtM, sensor_bus
  *rtU_sensor_bus_e, navigation_bus *rtY_navigation_bus_d, controller_bus
  *rtY_controller_bus_f, real_T rtY_control_deg[4]);
extern void autocodeModel_step(RT_MODEL *const rtM, sensor_bus *rtU_sensor_bus_e,
  navigation_bus *rtY_navigation_bus_d, controller_bus *rtY_controller_bus_f,
  real_T rtY_control_deg[4]);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S78>/Data Type Duplicate' : Unused code path elimination
 * Block '<S79>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S80>/Data Type Duplicate' : Unused code path elimination
 * Block '<S80>/Data Type Propagation' : Unused code path elimination
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate' : Unused code path elimination
 * Block '<S81>/Data Type Propagation' : Unused code path elimination
 * Block '<S148>/Data Type Duplicate' : Unused code path elimination
 * Block '<S149>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S150>/Data Type Duplicate' : Unused code path elimination
 * Block '<S150>/Data Type Propagation' : Unused code path elimination
 * Block '<S85>/Scope' : Unused code path elimination
 * Block '<S151>/Data Type Duplicate' : Unused code path elimination
 * Block '<S151>/Data Type Propagation' : Unused code path elimination
 * Block '<S218>/Data Type Duplicate' : Unused code path elimination
 * Block '<S219>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S220>/Data Type Duplicate' : Unused code path elimination
 * Block '<S220>/Data Type Propagation' : Unused code path elimination
 * Block '<S155>/Scope' : Unused code path elimination
 * Block '<S221>/Data Type Duplicate' : Unused code path elimination
 * Block '<S221>/Data Type Propagation' : Unused code path elimination
 * Block '<S282>/Data Type Duplicate' : Unused code path elimination
 * Block '<S283>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S284>/Data Type Duplicate' : Unused code path elimination
 * Block '<S284>/Data Type Propagation' : Unused code path elimination
 * Block '<S227>/Scope' : Unused code path elimination
 * Block '<S285>/Data Type Duplicate' : Unused code path elimination
 * Block '<S285>/Data Type Propagation' : Unused code path elimination
 * Block '<S342>/Data Type Duplicate' : Unused code path elimination
 * Block '<S343>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S344>/Data Type Duplicate' : Unused code path elimination
 * Block '<S344>/Data Type Propagation' : Unused code path elimination
 * Block '<S287>/Scope' : Unused code path elimination
 * Block '<S345>/Data Type Duplicate' : Unused code path elimination
 * Block '<S345>/Data Type Propagation' : Unused code path elimination
 * Block '<S402>/Data Type Duplicate' : Unused code path elimination
 * Block '<S403>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S404>/Data Type Duplicate' : Unused code path elimination
 * Block '<S404>/Data Type Propagation' : Unused code path elimination
 * Block '<S347>/Scope' : Unused code path elimination
 * Block '<S405>/Data Type Duplicate' : Unused code path elimination
 * Block '<S405>/Data Type Propagation' : Unused code path elimination
 * Block '<S431>/Data Type Duplicate' : Unused code path elimination
 * Block '<S79>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S149>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S219>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S283>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S343>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S403>/Zero-Order Hold' : Eliminated since input and output rates are identical
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'autocodeModel'
 * '<S1>'   : 'autocodeModel/Controller'
 * '<S2>'   : 'autocodeModel/Guidance'
 * '<S3>'   : 'autocodeModel/Navigation'
 * '<S4>'   : 'autocodeModel/Controller/controlActivation'
 * '<S5>'   : 'autocodeModel/Controller/controlMapping'
 * '<S6>'   : 'autocodeModel/Controller/innerLoop'
 * '<S7>'   : 'autocodeModel/Controller/outerLoop'
 * '<S8>'   : 'autocodeModel/Controller/innerLoop/calcErrorInnerLoop'
 * '<S9>'   : 'autocodeModel/Controller/innerLoop/pitchInnerLoop'
 * '<S10>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop'
 * '<S11>'  : 'autocodeModel/Controller/innerLoop/yawInnerLoop'
 * '<S12>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID'
 * '<S13>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler'
 * '<S14>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/momentMapping'
 * '<S15>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/rateLimiter'
 * '<S16>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/saturation'
 * '<S17>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller'
 * '<S18>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Anti-windup'
 * '<S19>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/D Gain'
 * '<S20>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/External Derivative'
 * '<S21>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Filter'
 * '<S22>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Filter ICs'
 * '<S23>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/I Gain'
 * '<S24>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Ideal P Gain'
 * '<S25>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S26>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Integrator'
 * '<S27>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Integrator ICs'
 * '<S28>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/N Copy'
 * '<S29>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/N Gain'
 * '<S30>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/P Copy'
 * '<S31>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Parallel P Gain'
 * '<S32>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Reset Signal'
 * '<S33>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Saturation'
 * '<S34>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Saturation Fdbk'
 * '<S35>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Sum'
 * '<S36>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Sum Fdbk'
 * '<S37>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Tracking Mode'
 * '<S38>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S39>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Tsamp - Integral'
 * '<S40>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S41>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/postSat Signal'
 * '<S42>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/preInt Signal'
 * '<S43>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/preSat Signal'
 * '<S44>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S45>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S46>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/External Derivative/Error'
 * '<S47>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S48>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S49>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S50>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S51>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S52>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Integrator/Discrete'
 * '<S53>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S54>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/N Copy/Disabled'
 * '<S55>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S56>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/P Copy/Disabled'
 * '<S57>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S58>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S59>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S60>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S61>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S62>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S63>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S64>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S65>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S66>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S67>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S68>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S69>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S70>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler/DGain Lookup'
 * '<S71>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler/IGain Lookup'
 * '<S72>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler/NGain Lookup'
 * '<S73>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler/PGain Lookup'
 * '<S74>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler/DGain Lookup/Enabled'
 * '<S75>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler/IGain Lookup/Enabled'
 * '<S76>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler/NGain Lookup/Enabled'
 * '<S77>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/PID Gain Scheduler/PGain Lookup/Enabled'
 * '<S78>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/rateLimiter/Discrete Derivative'
 * '<S79>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S80>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S81>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/saturation/Saturation Dynamic'
 * '<S82>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID'
 * '<S83>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler'
 * '<S84>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/momentMapping'
 * '<S85>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/rateLimiter'
 * '<S86>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/saturation'
 * '<S87>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller'
 * '<S88>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Anti-windup'
 * '<S89>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/D Gain'
 * '<S90>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/External Derivative'
 * '<S91>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Filter'
 * '<S92>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Filter ICs'
 * '<S93>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/I Gain'
 * '<S94>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Ideal P Gain'
 * '<S95>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S96>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Integrator'
 * '<S97>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Integrator ICs'
 * '<S98>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/N Copy'
 * '<S99>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/N Gain'
 * '<S100>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/P Copy'
 * '<S101>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Parallel P Gain'
 * '<S102>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Reset Signal'
 * '<S103>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Saturation'
 * '<S104>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Saturation Fdbk'
 * '<S105>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Sum'
 * '<S106>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Sum Fdbk'
 * '<S107>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tracking Mode'
 * '<S108>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S109>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tsamp - Integral'
 * '<S110>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S111>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/postSat Signal'
 * '<S112>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/preInt Signal'
 * '<S113>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/preSat Signal'
 * '<S114>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S115>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S116>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/External Derivative/Error'
 * '<S117>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S118>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S119>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S120>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S121>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S122>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Integrator/Discrete'
 * '<S123>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S124>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/N Copy/Disabled'
 * '<S125>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S126>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/P Copy/Disabled'
 * '<S127>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S128>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S129>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S130>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S131>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S132>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S133>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S134>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S135>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S136>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S137>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S138>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S139>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S140>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/DGain Lookup'
 * '<S141>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/IGain Lookup'
 * '<S142>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/NGain Lookup'
 * '<S143>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/PGain Lookup'
 * '<S144>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/DGain Lookup/Enabled'
 * '<S145>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/IGain Lookup/Enabled'
 * '<S146>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/NGain Lookup/Enabled'
 * '<S147>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/PGain Lookup/Enabled'
 * '<S148>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/rateLimiter/Discrete Derivative'
 * '<S149>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S150>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S151>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/saturation/Saturation Dynamic'
 * '<S152>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID'
 * '<S153>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler'
 * '<S154>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/momentMapping'
 * '<S155>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/rateLimiter'
 * '<S156>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/saturation'
 * '<S157>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller'
 * '<S158>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Anti-windup'
 * '<S159>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/D Gain'
 * '<S160>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/External Derivative'
 * '<S161>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Filter'
 * '<S162>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Filter ICs'
 * '<S163>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/I Gain'
 * '<S164>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Ideal P Gain'
 * '<S165>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S166>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Integrator'
 * '<S167>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Integrator ICs'
 * '<S168>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/N Copy'
 * '<S169>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/N Gain'
 * '<S170>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/P Copy'
 * '<S171>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Parallel P Gain'
 * '<S172>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Reset Signal'
 * '<S173>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Saturation'
 * '<S174>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Saturation Fdbk'
 * '<S175>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Sum'
 * '<S176>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Sum Fdbk'
 * '<S177>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tracking Mode'
 * '<S178>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S179>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tsamp - Integral'
 * '<S180>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S181>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/postSat Signal'
 * '<S182>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/preInt Signal'
 * '<S183>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/preSat Signal'
 * '<S184>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S185>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S186>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/External Derivative/Error'
 * '<S187>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S188>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S189>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S190>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S191>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S192>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Integrator/Discrete'
 * '<S193>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S194>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/N Copy/Disabled'
 * '<S195>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S196>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/P Copy/Disabled'
 * '<S197>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S198>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S199>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S200>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S201>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S202>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S203>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S204>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S205>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S206>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S207>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S208>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S209>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S210>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/DGain Lookup'
 * '<S211>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/IGain Lookup'
 * '<S212>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/NGain Lookup'
 * '<S213>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/PGain Lookup'
 * '<S214>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/DGain Lookup/Enabled'
 * '<S215>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/IGain Lookup/Enabled'
 * '<S216>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/NGain Lookup/Enabled'
 * '<S217>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/PGain Lookup/Enabled'
 * '<S218>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/rateLimiter/Discrete Derivative'
 * '<S219>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S220>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S221>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/saturation/Saturation Dynamic'
 * '<S222>' : 'autocodeModel/Controller/outerLoop/calcErrorOuterLoop'
 * '<S223>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop'
 * '<S224>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop'
 * '<S225>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop'
 * '<S226>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID'
 * '<S227>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/rateLimiter'
 * '<S228>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/saturation'
 * '<S229>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller'
 * '<S230>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Anti-windup'
 * '<S231>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/D Gain'
 * '<S232>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/External Derivative'
 * '<S233>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Filter'
 * '<S234>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Filter ICs'
 * '<S235>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/I Gain'
 * '<S236>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Ideal P Gain'
 * '<S237>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S238>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Integrator'
 * '<S239>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Integrator ICs'
 * '<S240>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/N Copy'
 * '<S241>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/N Gain'
 * '<S242>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/P Copy'
 * '<S243>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Parallel P Gain'
 * '<S244>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Reset Signal'
 * '<S245>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Saturation'
 * '<S246>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Saturation Fdbk'
 * '<S247>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Sum'
 * '<S248>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Sum Fdbk'
 * '<S249>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tracking Mode'
 * '<S250>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S251>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tsamp - Integral'
 * '<S252>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S253>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/postSat Signal'
 * '<S254>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/preInt Signal'
 * '<S255>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/preSat Signal'
 * '<S256>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S257>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S258>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/External Derivative/Error'
 * '<S259>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S260>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S261>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S262>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S263>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S264>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Integrator/Discrete'
 * '<S265>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S266>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/N Copy/Disabled'
 * '<S267>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S268>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/P Copy/Disabled'
 * '<S269>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S270>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S271>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S272>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S273>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S274>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S275>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S276>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S277>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S278>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S279>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S280>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S281>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S282>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/rateLimiter/Discrete Derivative'
 * '<S283>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S284>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S285>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/saturation/Saturation Dynamic'
 * '<S286>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID'
 * '<S287>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/rateLimiter'
 * '<S288>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/saturation'
 * '<S289>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller'
 * '<S290>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Anti-windup'
 * '<S291>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/D Gain'
 * '<S292>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/External Derivative'
 * '<S293>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Filter'
 * '<S294>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Filter ICs'
 * '<S295>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/I Gain'
 * '<S296>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Ideal P Gain'
 * '<S297>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S298>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Integrator'
 * '<S299>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Integrator ICs'
 * '<S300>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/N Copy'
 * '<S301>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/N Gain'
 * '<S302>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/P Copy'
 * '<S303>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Parallel P Gain'
 * '<S304>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Reset Signal'
 * '<S305>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Saturation'
 * '<S306>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Saturation Fdbk'
 * '<S307>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Sum'
 * '<S308>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Sum Fdbk'
 * '<S309>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tracking Mode'
 * '<S310>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S311>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tsamp - Integral'
 * '<S312>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S313>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/postSat Signal'
 * '<S314>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/preInt Signal'
 * '<S315>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/preSat Signal'
 * '<S316>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S317>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S318>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/External Derivative/Error'
 * '<S319>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S320>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S321>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S322>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S323>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S324>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Integrator/Discrete'
 * '<S325>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S326>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/N Copy/Disabled'
 * '<S327>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S328>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/P Copy/Disabled'
 * '<S329>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S330>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S331>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S332>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S333>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S334>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S335>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S336>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S337>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S338>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S339>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S340>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S341>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S342>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/rateLimiter/Discrete Derivative'
 * '<S343>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S344>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S345>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/saturation/Saturation Dynamic'
 * '<S346>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID'
 * '<S347>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/rateLimiter'
 * '<S348>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/saturation'
 * '<S349>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller'
 * '<S350>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Anti-windup'
 * '<S351>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/D Gain'
 * '<S352>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/External Derivative'
 * '<S353>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Filter'
 * '<S354>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Filter ICs'
 * '<S355>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/I Gain'
 * '<S356>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Ideal P Gain'
 * '<S357>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S358>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Integrator'
 * '<S359>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Integrator ICs'
 * '<S360>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/N Copy'
 * '<S361>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/N Gain'
 * '<S362>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/P Copy'
 * '<S363>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Parallel P Gain'
 * '<S364>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Reset Signal'
 * '<S365>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Saturation'
 * '<S366>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Saturation Fdbk'
 * '<S367>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Sum'
 * '<S368>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Sum Fdbk'
 * '<S369>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tracking Mode'
 * '<S370>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S371>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tsamp - Integral'
 * '<S372>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S373>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/postSat Signal'
 * '<S374>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/preInt Signal'
 * '<S375>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/preSat Signal'
 * '<S376>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S377>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S378>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/External Derivative/Error'
 * '<S379>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S380>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S381>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S382>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S383>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S384>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Integrator/Discrete'
 * '<S385>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S386>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/N Copy/Disabled'
 * '<S387>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S388>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/P Copy/Disabled'
 * '<S389>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S390>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S391>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S392>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S393>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S394>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S395>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S396>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S397>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S398>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S399>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S400>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S401>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S402>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/rateLimiter/Discrete Derivative'
 * '<S403>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S404>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S405>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/saturation/Saturation Dynamic'
 * '<S406>' : 'autocodeModel/Navigation/Navigation'
 * '<S407>' : 'autocodeModel/Navigation/Navigation/deadReckoning'
 * '<S408>' : 'autocodeModel/Navigation/Navigation/filter'
 * '<S409>' : 'autocodeModel/Navigation/Navigation/flightMode'
 * '<S410>' : 'autocodeModel/Navigation/Navigation/navBusCreator'
 * '<S411>' : 'autocodeModel/Navigation/Navigation/navPreProcessing'
 * '<S412>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication'
 * '<S413>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Normalize'
 * '<S414>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Transpose'
 * '<S415>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication/q0'
 * '<S416>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication/q1'
 * '<S417>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication/q2'
 * '<S418>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication/q3'
 * '<S419>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Normalize/Quaternion Modulus'
 * '<S420>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S421>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter'
 * '<S422>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation'
 * '<S423>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter'
 * '<S424>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Noise Filter'
 * '<S425>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles'
 * '<S426>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation/Compare To Constant'
 * '<S427>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation/gravityCalculation'
 * '<S428>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Compare To Constant'
 * '<S429>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter'
 * '<S430>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Pass Through'
 * '<S431>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/Normalize Vector1'
 * '<S432>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/Quaternion Normalize'
 * '<S433>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat'
 * '<S434>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/Quaternion Normalize/Quaternion Modulus'
 * '<S435>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S436>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat/Quaternion Multiplication'
 * '<S437>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat/Quaternion Normalize'
 * '<S438>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat/Quaternion Multiplication/q0'
 * '<S439>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat/Quaternion Multiplication/q1'
 * '<S440>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat/Quaternion Multiplication/q2'
 * '<S441>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat/Quaternion Multiplication/q3'
 * '<S442>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat/Quaternion Normalize/Quaternion Modulus'
 * '<S443>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Complementary Filter/eulerAngles2Quat/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S444>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication'
 * '<S445>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication/q0'
 * '<S446>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication/q1'
 * '<S447>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication/q2'
 * '<S448>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication/q3'
 * '<S449>' : 'autocodeModel/Navigation/Navigation/flightMode/State Transition Table'
 * '<S450>' : 'autocodeModel/Navigation/Navigation/navBusCreator/dynPressureEstimation'
 * '<S451>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/gravityCalculation'
 */
#endif                                 /* autocodeModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
