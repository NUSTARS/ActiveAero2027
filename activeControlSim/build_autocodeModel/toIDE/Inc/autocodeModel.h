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
 * C/C++ source code generated on : Wed Nov  4 17:25:57 2026
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
  real_T altitudeBias_m;
  real_T llaBias_na[3];
  real_T dynPressureEst_Pa;
  real_T xVelEstNed_mps;
  real_T yVelEstNed_mps;
  real_T zVelEstNed_mps;
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
  real_T velNedMeas_mps[3];
  real_T gpsLLA_na[3];
  boolean_T gpsFix_b;
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
  real_T qEst_na[4];                   /* '<S427>/Merge' */
  real_T UnitDelay_2_DSTATE[4];        /* '<S408>/Unit Delay' */
  real_T UnitDelay_13_DSTATE[3];       /* '<S408>/Unit Delay' */
  real_T DiscreteTransferFcn1_states[6];/* '<S409>/Discrete Transfer Fcn1' */
  real_T GyroFilter_states[3];         /* '<S428>/Gyro Filter' */
  real_T UD_DSTATE[3];                 /* '<S477>/UD' */
  real_T UnitDelay_12_DSTATE[3];       /* '<S408>/Unit Delay' */
  real_T AccelFilter_states[3];        /* '<S409>/Accel Filter' */
  real_T Delay2_6_DSTATE[500];         /* '<S426>/Delay2' */
  real_T UnitDelay_15_DSTATE[3];       /* '<S408>/Unit Delay' */
  real_T AccelFilter_states_k[3];      /* '<S428>/Accel Filter' */
  real_T Delay2_3_DSTATE[1500];        /* '<S426>/Delay2' */
  real_T UnitDelay1_DSTATE[3];         /* '<S426>/Unit Delay1' */
  real_T DiscreteFIRFilter1_states[297];/* '<S426>/Discrete FIR Filter1' */
  real_T Delay2_4_DSTATE[1500];        /* '<S426>/Delay2' */
  real_T UnitDelay_DSTATE[3];          /* '<S426>/Unit Delay' */
  real_T DiscreteFIRFilter_states[297];/* '<S426>/Discrete FIR Filter' */
  real_T Delay2_8_DSTATE[1500];        /* '<S426>/Delay2' */
  real_T UnitDelay3_DSTATE[3];         /* '<S426>/Unit Delay3' */
  real_T DiscreteFIRFilter3_states[297];/* '<S426>/Discrete FIR Filter3' */
  real_T DiscreteFIRFilter2_states[99];/* '<S426>/Discrete FIR Filter2' */
  real_T Delay_3_DSTATE[1500];         /* '<S436>/Delay' */
  real_T SFunction_temp_table[8];      /* '<S432>/S-Function' */
  real_T SFunction_pres_table[8];      /* '<S432>/S-Function' */
  real_T SFunction_temp_table_m[8];    /* '<S467>/S-Function' */
  real_T SFunction_pres_table_c[8];    /* '<S467>/S-Function' */
  real_T Product;                      /* '<S430>/Product' */
  real_T SFunction;                    /* '<S432>/S-Function' */
  real_T Product_d;                    /* '<S466>/Product' */
  real_T SFunction_p;                  /* '<S467>/S-Function' */
  real_T Integrator_DSTATE;            /* '<S326>/Integrator' */
  real_T Filter_DSTATE;                /* '<S321>/Filter' */
  real_T Delay_DSTATE;                 /* '<S345>/Delay' */
  real_T UnitDelay_17_DSTATE;          /* '<S408>/Unit Delay' */
  real_T UnitDelay_18_DSTATE;          /* '<S408>/Unit Delay' */
  real_T UnitDelay_19_DSTATE;          /* '<S408>/Unit Delay' */
  real_T Integrator_DSTATE_b;          /* '<S123>/Integrator' */
  real_T Filter_DSTATE_p;              /* '<S118>/Filter' */
  real_T Delay_DSTATE_p;               /* '<S150>/Delay' */
  real_T Integrator_DSTATE_g;          /* '<S266>/Integrator' */
  real_T Filter_DSTATE_n;              /* '<S261>/Filter' */
  real_T Delay_DSTATE_c;               /* '<S285>/Delay' */
  real_T Integrator_DSTATE_p;          /* '<S52>/Integrator' */
  real_T Filter_DSTATE_l;              /* '<S47>/Filter' */
  real_T Delay_DSTATE_f;               /* '<S80>/Delay' */
  real_T Integrator_DSTATE_l;          /* '<S386>/Integrator' */
  real_T Filter_DSTATE_c;              /* '<S381>/Filter' */
  real_T Delay_DSTATE_h;               /* '<S405>/Delay' */
  real_T Integrator_DSTATE_e;          /* '<S193>/Integrator' */
  real_T Filter_DSTATE_g;              /* '<S188>/Filter' */
  real_T Delay_DSTATE_e;               /* '<S221>/Delay' */
  real_T UnitDelay_20_DSTATE;          /* '<S408>/Unit Delay' */
  real_T UnitDelay_21_DSTATE;          /* '<S408>/Unit Delay' */
  real_T UnitDelay_22_DSTATE;          /* '<S408>/Unit Delay' */
  real_T UD_DSTATE_l;                  /* '<S220>/UD' */
  real_T UD_DSTATE_k;                  /* '<S79>/UD' */
  real_T UD_DSTATE_n;                  /* '<S149>/UD' */
  real_T UD_DSTATE_g;                  /* '<S284>/UD' */
  real_T UD_DSTATE_p;                  /* '<S404>/UD' */
  real_T UD_DSTATE_a;                  /* '<S344>/UD' */
  real_T UnitDelay2_DSTATE;            /* '<S426>/Unit Delay2' */
  int32_T DiscreteFIRFilter1_circBuf;  /* '<S426>/Discrete FIR Filter1' */
  int32_T DiscreteFIRFilter_circBuf;   /* '<S426>/Discrete FIR Filter' */
  int32_T DiscreteFIRFilter3_circBuf;  /* '<S426>/Discrete FIR Filter3' */
  int32_T DiscreteFIRFilter2_circBuf;  /* '<S426>/Discrete FIR Filter2' */
  uint32_T temporalCounter_i1;         /* '<S411>/State Transition Table' */
  flightMode flightMode_enum;          /* '<S411>/State Transition Table' */
  flightMode UnitDelay_1_DSTATE;       /* '<S408>/Unit Delay' */
  uint8_T is_active_c4_autocodeModel;  /* '<S411>/State Transition Table' */
  uint8_T is_c4_autocodeModel;         /* '<S411>/State Transition Table' */
  boolean_T UnitDelay_DSTATE_n;        /* '<S4>/Unit Delay' */
  boolean_T icLoad;                    /* '<S345>/Delay' */
  boolean_T icLoad_k;                  /* '<S150>/Delay' */
  boolean_T icLoad_a;                  /* '<S285>/Delay' */
  boolean_T icLoad_f;                  /* '<S80>/Delay' */
  boolean_T icLoad_c;                  /* '<S405>/Delay' */
  boolean_T icLoad_d;                  /* '<S221>/Delay' */
  boolean_T boostThreshold_b;          /* '<S411>/State Transition Table' */
  boolean_T lockoutThreshold_b;        /* '<S411>/State Transition Table' */
  boolean_T coastThreshold_b;          /* '<S411>/State Transition Table' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T QuaternionstoDirectionCosin[9];
                          /* '<S436>/Quaternions to  Direction Cosine Matrix' */
  const real_T RotationAnglestoDirectionCo[9];
                       /* '<S436>/Rotation Angles to Direction Cosine Matrix' */
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
 * Block '<S79>/Data Type Duplicate' : Unused code path elimination
 * Block '<S80>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate' : Unused code path elimination
 * Block '<S81>/Data Type Propagation' : Unused code path elimination
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S82>/Data Type Duplicate' : Unused code path elimination
 * Block '<S82>/Data Type Propagation' : Unused code path elimination
 * Block '<S149>/Data Type Duplicate' : Unused code path elimination
 * Block '<S150>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S151>/Data Type Duplicate' : Unused code path elimination
 * Block '<S151>/Data Type Propagation' : Unused code path elimination
 * Block '<S86>/Scope' : Unused code path elimination
 * Block '<S152>/Data Type Duplicate' : Unused code path elimination
 * Block '<S152>/Data Type Propagation' : Unused code path elimination
 * Block '<S220>/Data Type Duplicate' : Unused code path elimination
 * Block '<S221>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S222>/Data Type Duplicate' : Unused code path elimination
 * Block '<S222>/Data Type Propagation' : Unused code path elimination
 * Block '<S156>/Scope' : Unused code path elimination
 * Block '<S223>/Data Type Duplicate' : Unused code path elimination
 * Block '<S223>/Data Type Propagation' : Unused code path elimination
 * Block '<S284>/Data Type Duplicate' : Unused code path elimination
 * Block '<S285>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S286>/Data Type Duplicate' : Unused code path elimination
 * Block '<S286>/Data Type Propagation' : Unused code path elimination
 * Block '<S229>/Scope' : Unused code path elimination
 * Block '<S287>/Data Type Duplicate' : Unused code path elimination
 * Block '<S287>/Data Type Propagation' : Unused code path elimination
 * Block '<S344>/Data Type Duplicate' : Unused code path elimination
 * Block '<S345>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S346>/Data Type Duplicate' : Unused code path elimination
 * Block '<S346>/Data Type Propagation' : Unused code path elimination
 * Block '<S289>/Scope' : Unused code path elimination
 * Block '<S347>/Data Type Duplicate' : Unused code path elimination
 * Block '<S347>/Data Type Propagation' : Unused code path elimination
 * Block '<S404>/Data Type Duplicate' : Unused code path elimination
 * Block '<S405>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S406>/Data Type Duplicate' : Unused code path elimination
 * Block '<S406>/Data Type Propagation' : Unused code path elimination
 * Block '<S349>/Scope' : Unused code path elimination
 * Block '<S407>/Data Type Duplicate' : Unused code path elimination
 * Block '<S407>/Data Type Propagation' : Unused code path elimination
 * Block '<S443>/Data Type Duplicate' : Unused code path elimination
 * Block '<S439>/Unary Minus' : Unused code path elimination
 * Block '<S411>/Unary Minus' : Unused code path elimination
 * Block '<S471>/Unit Conversion' : Unused code path elimination
 * Block '<S413>/Sum3' : Unused code path elimination
 * Block '<S80>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S150>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S221>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S285>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S345>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S405>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S434>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S435>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S472>/Unit Conversion' : Eliminated nontunable gain of 1
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
 * '<S78>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/momentMapping/             '
 * '<S79>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/rateLimiter/Discrete Derivative'
 * '<S80>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S81>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S82>'  : 'autocodeModel/Controller/innerLoop/pitchInnerLoop/saturation/Saturation Dynamic'
 * '<S83>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID'
 * '<S84>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler'
 * '<S85>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/momentMapping'
 * '<S86>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/rateLimiter'
 * '<S87>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/saturation'
 * '<S88>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller'
 * '<S89>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Anti-windup'
 * '<S90>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/D Gain'
 * '<S91>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/External Derivative'
 * '<S92>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Filter'
 * '<S93>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Filter ICs'
 * '<S94>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/I Gain'
 * '<S95>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Ideal P Gain'
 * '<S96>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S97>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Integrator'
 * '<S98>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Integrator ICs'
 * '<S99>'  : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/N Copy'
 * '<S100>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/N Gain'
 * '<S101>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/P Copy'
 * '<S102>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Parallel P Gain'
 * '<S103>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Reset Signal'
 * '<S104>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Saturation'
 * '<S105>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Saturation Fdbk'
 * '<S106>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Sum'
 * '<S107>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Sum Fdbk'
 * '<S108>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tracking Mode'
 * '<S109>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S110>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tsamp - Integral'
 * '<S111>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S112>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/postSat Signal'
 * '<S113>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/preInt Signal'
 * '<S114>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/preSat Signal'
 * '<S115>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S116>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S117>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/External Derivative/Error'
 * '<S118>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S119>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S120>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S121>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S122>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S123>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Integrator/Discrete'
 * '<S124>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S125>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/N Copy/Disabled'
 * '<S126>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S127>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/P Copy/Disabled'
 * '<S128>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S129>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S130>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S131>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S132>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S133>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S134>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S135>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S136>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S137>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S138>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S139>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S140>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S141>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/DGain Lookup'
 * '<S142>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/IGain Lookup'
 * '<S143>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/NGain Lookup'
 * '<S144>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/PGain Lookup'
 * '<S145>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/DGain Lookup/Enabled'
 * '<S146>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/IGain Lookup/Enabled'
 * '<S147>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/NGain Lookup/Enabled'
 * '<S148>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/PID Gain Scheduler/PGain Lookup/Enabled'
 * '<S149>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/rateLimiter/Discrete Derivative'
 * '<S150>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S151>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S152>' : 'autocodeModel/Controller/innerLoop/rollInnerLoop/saturation/Saturation Dynamic'
 * '<S153>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID'
 * '<S154>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler'
 * '<S155>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/momentMapping'
 * '<S156>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/rateLimiter'
 * '<S157>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/saturation'
 * '<S158>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller'
 * '<S159>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Anti-windup'
 * '<S160>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/D Gain'
 * '<S161>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/External Derivative'
 * '<S162>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Filter'
 * '<S163>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Filter ICs'
 * '<S164>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/I Gain'
 * '<S165>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Ideal P Gain'
 * '<S166>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S167>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Integrator'
 * '<S168>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Integrator ICs'
 * '<S169>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/N Copy'
 * '<S170>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/N Gain'
 * '<S171>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/P Copy'
 * '<S172>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Parallel P Gain'
 * '<S173>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Reset Signal'
 * '<S174>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Saturation'
 * '<S175>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Saturation Fdbk'
 * '<S176>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Sum'
 * '<S177>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Sum Fdbk'
 * '<S178>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tracking Mode'
 * '<S179>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S180>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tsamp - Integral'
 * '<S181>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S182>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/postSat Signal'
 * '<S183>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/preInt Signal'
 * '<S184>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/preSat Signal'
 * '<S185>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S186>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S187>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/External Derivative/Error'
 * '<S188>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S189>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S190>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S191>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S192>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S193>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Integrator/Discrete'
 * '<S194>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S195>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/N Copy/Disabled'
 * '<S196>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S197>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/P Copy/Disabled'
 * '<S198>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S199>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S200>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S201>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S202>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S203>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S204>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S205>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S206>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S207>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S208>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S209>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S210>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S211>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/DGain Lookup'
 * '<S212>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/IGain Lookup'
 * '<S213>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/NGain Lookup'
 * '<S214>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/PGain Lookup'
 * '<S215>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/DGain Lookup/Enabled'
 * '<S216>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/IGain Lookup/Enabled'
 * '<S217>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/NGain Lookup/Enabled'
 * '<S218>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/PID Gain Scheduler/PGain Lookup/Enabled'
 * '<S219>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/momentMapping/             '
 * '<S220>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/rateLimiter/Discrete Derivative'
 * '<S221>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S222>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S223>' : 'autocodeModel/Controller/innerLoop/yawInnerLoop/saturation/Saturation Dynamic'
 * '<S224>' : 'autocodeModel/Controller/outerLoop/calcErrorOuterLoop'
 * '<S225>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop'
 * '<S226>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop'
 * '<S227>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop'
 * '<S228>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID'
 * '<S229>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/rateLimiter'
 * '<S230>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/saturation'
 * '<S231>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller'
 * '<S232>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Anti-windup'
 * '<S233>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/D Gain'
 * '<S234>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/External Derivative'
 * '<S235>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Filter'
 * '<S236>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Filter ICs'
 * '<S237>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/I Gain'
 * '<S238>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Ideal P Gain'
 * '<S239>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S240>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Integrator'
 * '<S241>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Integrator ICs'
 * '<S242>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/N Copy'
 * '<S243>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/N Gain'
 * '<S244>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/P Copy'
 * '<S245>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Parallel P Gain'
 * '<S246>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Reset Signal'
 * '<S247>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Saturation'
 * '<S248>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Saturation Fdbk'
 * '<S249>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Sum'
 * '<S250>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Sum Fdbk'
 * '<S251>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tracking Mode'
 * '<S252>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S253>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tsamp - Integral'
 * '<S254>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S255>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/postSat Signal'
 * '<S256>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/preInt Signal'
 * '<S257>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/preSat Signal'
 * '<S258>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S259>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S260>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/External Derivative/Error'
 * '<S261>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S262>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S263>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S264>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S265>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S266>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Integrator/Discrete'
 * '<S267>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S268>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/N Copy/Disabled'
 * '<S269>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S270>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/P Copy/Disabled'
 * '<S271>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S272>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S273>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S274>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S275>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S276>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S277>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S278>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S279>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S280>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S281>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S282>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S283>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S284>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/rateLimiter/Discrete Derivative'
 * '<S285>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S286>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S287>' : 'autocodeModel/Controller/outerLoop/pitchOuterLoop/saturation/Saturation Dynamic'
 * '<S288>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID'
 * '<S289>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/rateLimiter'
 * '<S290>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/saturation'
 * '<S291>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller'
 * '<S292>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Anti-windup'
 * '<S293>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/D Gain'
 * '<S294>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/External Derivative'
 * '<S295>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Filter'
 * '<S296>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Filter ICs'
 * '<S297>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/I Gain'
 * '<S298>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Ideal P Gain'
 * '<S299>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S300>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Integrator'
 * '<S301>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Integrator ICs'
 * '<S302>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/N Copy'
 * '<S303>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/N Gain'
 * '<S304>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/P Copy'
 * '<S305>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Parallel P Gain'
 * '<S306>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Reset Signal'
 * '<S307>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Saturation'
 * '<S308>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Saturation Fdbk'
 * '<S309>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Sum'
 * '<S310>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Sum Fdbk'
 * '<S311>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tracking Mode'
 * '<S312>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S313>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tsamp - Integral'
 * '<S314>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S315>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/postSat Signal'
 * '<S316>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/preInt Signal'
 * '<S317>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/preSat Signal'
 * '<S318>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S319>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S320>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/External Derivative/Error'
 * '<S321>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S322>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S323>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S324>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S325>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S326>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Integrator/Discrete'
 * '<S327>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S328>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/N Copy/Disabled'
 * '<S329>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S330>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/P Copy/Disabled'
 * '<S331>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S332>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S333>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S334>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S335>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S336>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S337>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S338>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S339>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S340>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S341>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S342>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S343>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S344>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/rateLimiter/Discrete Derivative'
 * '<S345>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S346>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S347>' : 'autocodeModel/Controller/outerLoop/rollOuterLoop/saturation/Saturation Dynamic'
 * '<S348>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID'
 * '<S349>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/rateLimiter'
 * '<S350>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/saturation'
 * '<S351>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller'
 * '<S352>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Anti-windup'
 * '<S353>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/D Gain'
 * '<S354>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/External Derivative'
 * '<S355>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Filter'
 * '<S356>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Filter ICs'
 * '<S357>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/I Gain'
 * '<S358>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Ideal P Gain'
 * '<S359>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Ideal P Gain Fdbk'
 * '<S360>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Integrator'
 * '<S361>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Integrator ICs'
 * '<S362>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/N Copy'
 * '<S363>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/N Gain'
 * '<S364>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/P Copy'
 * '<S365>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Parallel P Gain'
 * '<S366>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Reset Signal'
 * '<S367>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Saturation'
 * '<S368>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Saturation Fdbk'
 * '<S369>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Sum'
 * '<S370>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Sum Fdbk'
 * '<S371>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tracking Mode'
 * '<S372>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tracking Mode Sum'
 * '<S373>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tsamp - Integral'
 * '<S374>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tsamp - Ngain'
 * '<S375>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/postSat Signal'
 * '<S376>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/preInt Signal'
 * '<S377>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/preSat Signal'
 * '<S378>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Anti-windup/Passthrough'
 * '<S379>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/D Gain/External Parameters'
 * '<S380>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/External Derivative/Error'
 * '<S381>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S382>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S383>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/I Gain/External Parameters'
 * '<S384>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Ideal P Gain/Passthrough'
 * '<S385>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S386>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Integrator/Discrete'
 * '<S387>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Integrator ICs/Internal IC'
 * '<S388>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/N Copy/Disabled'
 * '<S389>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/N Gain/External Parameters'
 * '<S390>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/P Copy/Disabled'
 * '<S391>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Parallel P Gain/External Parameters'
 * '<S392>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Reset Signal/Disabled'
 * '<S393>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Saturation/Passthrough'
 * '<S394>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Saturation Fdbk/Disabled'
 * '<S395>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Sum/Sum_PID'
 * '<S396>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Sum Fdbk/Disabled'
 * '<S397>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tracking Mode/Disabled'
 * '<S398>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S399>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S400>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S401>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/postSat Signal/Forward_Path'
 * '<S402>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/preInt Signal/Internal PreInt'
 * '<S403>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/PID/PID Controller/preSat Signal/Forward_Path'
 * '<S404>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/rateLimiter/Discrete Derivative'
 * '<S405>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/rateLimiter/Rate Limiter Dynamic'
 * '<S406>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/rateLimiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S407>' : 'autocodeModel/Controller/outerLoop/yawOuterLoop/saturation/Saturation Dynamic'
 * '<S408>' : 'autocodeModel/Navigation/Navigation'
 * '<S409>' : 'autocodeModel/Navigation/Navigation/deadReckoning'
 * '<S410>' : 'autocodeModel/Navigation/Navigation/filter'
 * '<S411>' : 'autocodeModel/Navigation/Navigation/flightMode'
 * '<S412>' : 'autocodeModel/Navigation/Navigation/navBusCreator'
 * '<S413>' : 'autocodeModel/Navigation/Navigation/navPreProcessing'
 * '<S414>' : 'autocodeModel/Navigation/Navigation/deadReckoning/              '
 * '<S415>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication'
 * '<S416>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Normalize'
 * '<S417>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Subsystem'
 * '<S418>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Transpose'
 * '<S419>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication/q0'
 * '<S420>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication/q1'
 * '<S421>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication/q2'
 * '<S422>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Multiplication/q3'
 * '<S423>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Normalize/Quaternion Modulus'
 * '<S424>' : 'autocodeModel/Navigation/Navigation/deadReckoning/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S425>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter'
 * '<S426>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation'
 * '<S427>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter'
 * '<S428>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Noise Filter'
 * '<S429>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles'
 * '<S430>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation/              '
 * '<S431>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation/Compare To Constant'
 * '<S432>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation/Pressure Altitude'
 * '<S433>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation/gravityCalculation'
 * '<S434>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation/Pressure Altitude/Length Conversion'
 * '<S435>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Bias Estimation/Pressure Altitude/Pressure Conversion'
 * '<S436>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter'
 * '<S437>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Pass Through'
 * '<S438>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Compare To Constant'
 * '<S439>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Pos Complementary Filter no GPS'
 * '<S440>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Pos Complementary Filter w//GPS'
 * '<S441>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Vel Complementary Filter'
 * '<S442>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Vel Pass Through'
 * '<S443>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/Normalize Vector1'
 * '<S444>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/Quaternion Normalize'
 * '<S445>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/Subsystem'
 * '<S446>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat'
 * '<S447>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/Quaternion Normalize/Quaternion Modulus'
 * '<S448>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S449>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat/Quaternion Multiplication'
 * '<S450>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat/Quaternion Normalize'
 * '<S451>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat/Quaternion Multiplication/q0'
 * '<S452>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat/Quaternion Multiplication/q1'
 * '<S453>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat/Quaternion Multiplication/q2'
 * '<S454>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat/Quaternion Multiplication/q3'
 * '<S455>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat/Quaternion Normalize/Quaternion Modulus'
 * '<S456>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Attitude Complementary Filter/eulerAngles2Quat/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S457>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Pos Complementary Filter no GPS/Compare To Constant'
 * '<S458>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/Complementary Filter/Vel Pass Through/Compare To Constant'
 * '<S459>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication'
 * '<S460>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication/q0'
 * '<S461>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication/q1'
 * '<S462>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication/q2'
 * '<S463>' : 'autocodeModel/Navigation/Navigation/filter/No Kalman Filter/quat2EulerAngles/Quaternion Multiplication/q3'
 * '<S464>' : 'autocodeModel/Navigation/Navigation/flightMode/State Transition Table'
 * '<S465>' : 'autocodeModel/Navigation/Navigation/navBusCreator/dynPressureEstimation'
 * '<S466>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/              '
 * '<S467>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/Pressure Altitude'
 * '<S468>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/Subsystem'
 * '<S469>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/gpsUpdateCheck'
 * '<S470>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/gravityCalculation'
 * '<S471>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/Pressure Altitude/Length Conversion'
 * '<S472>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/Pressure Altitude/Pressure Conversion'
 * '<S473>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/Subsystem/Degrees to Radians'
 * '<S474>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/Subsystem/Degrees to Radians1'
 * '<S475>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/Subsystem/Degrees to Radians2'
 * '<S476>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/gpsUpdateCheck/Compare To Constant'
 * '<S477>' : 'autocodeModel/Navigation/Navigation/navPreProcessing/gpsUpdateCheck/Difference'
 */
#endif                                 /* autocodeModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
