/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: autocodePlant.h
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

#ifndef autocodePlant_h_
#define autocodePlant_h_
#ifndef autocodePlant_COMMON_INCLUDES_
#define autocodePlant_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* autocodePlant_COMMON_INCLUDES_ */

#include "autocodePlant_types.h"
#include <string.h>
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_defines.h"

/* Includes for objects with custom storage classes */
#include "autocodePlantParams_calibration.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T UnitConversion;               /* '<S119>/Unit Conversion' */
  real_T sigma_wg;                     /* '<S138>/sigma_wg ' */
  real_T Product[4];                   /* '<S130>/Product' */
  real_T UnitConversion_e;             /* '<S123>/Unit Conversion' */
  real_T Subtract1[3];                 /* '<S9>/Subtract1' */
  real_T Subtract1_m[3];               /* '<S10>/Subtract1' */
  real_T Windspeedatreferenceheight[3];
                                   /* '<S118>/Wind speed at reference height' */
  real_T Sum;                          /* '<S53>/Sum' */
  real_T Sum_c;                        /* '<S54>/Sum' */
  real_T Sum_b;                        /* '<S55>/Sum' */
  real_T Sum_m;                        /* '<S47>/Sum' */
  real_T Sum_b1;                       /* '<S48>/Sum' */
  real_T Sum_k;                        /* '<S49>/Sum' */
  real_T Sum2[3];                      /* '<S10>/Sum2' */
  real_T Backlash[4];                  /* '<S7>/Backlash' */
  real_T Sum_bx;                       /* '<S33>/Sum' */
  real_T Sum_l;                        /* '<S34>/Sum' */
  real_T Sum_cx;                       /* '<S35>/Sum' */
  real_T Sum_f;                        /* '<S27>/Sum' */
  real_T Sum_i;                        /* '<S28>/Sum' */
  real_T Sum_e;                        /* '<S29>/Sum' */
  real_T Sum2_i[3];                    /* '<S9>/Sum2' */
  real_T Subtract1_k[3];               /* '<S11>/Subtract1' */
  real_T Sum_a;                        /* '<S73>/Sum' */
  real_T Sum_ia;                       /* '<S74>/Sum' */
  real_T Sum_bt;                       /* '<S75>/Sum' */
  real_T Sum_o;                        /* '<S67>/Sum' */
  real_T Sum_er;                       /* '<S68>/Sum' */
  real_T Sum_g;                        /* '<S69>/Sum' */
  real_T Sum2_iw[3];                   /* '<S11>/Sum2' */
  real_T Subtract1_j[3];               /* '<S12>/Subtract1' */
  real_T Sum_d;                        /* '<S93>/Sum' */
  real_T Sum_o3;                       /* '<S94>/Sum' */
  real_T Sum_j;                        /* '<S95>/Sum' */
  real_T Sum_dm;                       /* '<S87>/Sum' */
  real_T Sum_b4;                       /* '<S88>/Sum' */
  real_T Sum_ln;                       /* '<S89>/Sum' */
  real_T Sum2_a[3];                    /* '<S12>/Sum2' */
  real_T Switch;                       /* '<S209>/Switch' */
  real_T Merge;                        /* '<S211>/Merge' */
  real_T Switch_l;                     /* '<S208>/Switch' */
  real_T olat;                         /* '<S221>/olat' */
  real_T Gain;                         /* '<S189>/Gain' */
  real_T oalt;                         /* '<S221>/oalt' */
  real_T Product_h[3];                 /* '<S162>/Product' */
  real_T Delay;                        /* '<S6>/Delay' */
  real_T Sum_ah[3];                    /* '<S162>/Sum' */
  real_T fBdy_mps2[3];                 /* '<S170>/fBdy_mps2' */
  real_T DiscreteTransferFcn;          /* '<S174>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1;         /* '<S174>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn2;         /* '<S174>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn3;         /* '<S174>/Discrete Transfer Fcn3' */
  real_T DiscreteTransferFcn4;         /* '<S174>/Discrete Transfer Fcn4' */
  real_T DiscreteTransferFcn5;         /* '<S174>/Discrete Transfer Fcn5' */
  real_T FlatEarthtoLLA_o1[2];         /* '<S174>/Flat Earth to LLA' */
  real_T ZeroOrderHold[6];             /* '<S174>/Zero-Order Hold' */
  real_T Output_g;                     /* '<S185>/Output' */
  real_T Output_o[3];                  /* '<S176>/Output' */
  real_T Output_e[3];                  /* '<S186>/Output' */
  real_T Output_n;                     /* '<S184>/Output' */
  real_T RateTransition[6];            /* '<S174>/Rate Transition' */
  real_T OutportBufferForcp13[13];
  real_T OutportBufferForsp13[13];
  real_T Assignment[11];               /* '<S266>/Assignment' */
  real_T Assignment1[11];              /* '<S266>/Assignment1' */
  real_T sqrt_b;                       /* '<S218>/sqrt' */
  real_T Product11;                    /* '<S258>/Product11' */
  real_T Product12;                    /* '<S264>/Product12' */
  real_T Product4;                     /* '<S259>/Product4' */
  real_T sqrt_k;                       /* '<S265>/sqrt' */
  real_T Sum2_m;                       /* '<S226>/Sum2' */
  real_T Sum3;                         /* '<S226>/Sum3' */
  real_T Sum1_p;                       /* '<S226>/Sum1' */
  real_T Sum5;                         /* '<S226>/Sum5' */
  real_T Assignment_o[169];            /* '<S228>/Assignment' */
  real_T Sum2_p[169];                  /* '<S228>/Sum2' */
  real_T Assignment2[169];             /* '<S256>/Assignment2' */
  real_T Merge_b;                      /* '<S227>/Merge' */
  real_T Assignment_snorm[169];        /* '<S227>/Assignment_snorm' */
  real_T Merge1_i;                     /* '<S227>/Merge1' */
  real_T Assignment_h[169];            /* '<S227>/Assignment' */
  real_T Product2;                     /* '<S229>/Product2' */
  real_T Assignment2_a[13];            /* '<S234>/Assignment2' */
  real_T Assignment2_m[13];            /* '<S233>/Assignment2' */
  real_T w[2];                         /* '<S136>/w' */
  real_T w_h[2];                       /* '<S136>/w ' */
  real_T LwgV1[2];                     /* '<S136>/Lwg//V 1' */
  real_T w_c[2];                       /* '<S135>/w' */
  real_T w_j[2];                       /* '<S135>/w ' */
  real_T w1[2];                        /* '<S135>/w 1' */
  real_T w_d[2];                       /* '<S134>/w' */
  real_T w1_c[2];                      /* '<S134>/w1' */
  real_T w_g[2];                       /* '<S133>/w' */
  real_T w_j5[2];                      /* '<S132>/w' */
  real_T UnaryMinus[2];                /* '<S132>/Unary Minus' */
  real_T w4;                           /* '<S131>/w4' */
  real_T u16;                          /* '<S131>/u^1//6' */
  real_T w_p[2];                       /* '<S131>/w' */
  real_T sigma_w[2];                   /* '<S131>/sigma_w' */
  boolean_T RelationalOperator;        /* '<S174>/Relational Operator' */
  boolean_T RateTransition1;           /* '<S174>/Rate Transition1' */
} B_autocodePlant_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE[90];             /* '<S174>/Delay' */
  real_T UnitDelay_DSTATE[6];          /* '<S174>/Unit Delay' */
  real_T UnitDelay_DSTATE_h[4];        /* '<S7>/Unit Delay' */
  real_T Delay_DSTATE_h[2000];         /* '<S6>/Delay' */
  real_T DiscreteTransferFcn2_states;  /* '<S170>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn1_states;  /* '<S170>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn3_states;  /* '<S170>/Discrete Transfer Fcn3' */
  real_T UnitDelay_DSTATE_c[3];        /* '<S172>/Unit Delay' */
  real_T DiscreteTransferFcn_states;   /* '<S172>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_states_b;/* '<S172>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn2_states_g;/* '<S172>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn_states_k; /* '<S174>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_states_bi;/* '<S174>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn2_states_d;/* '<S174>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn3_states_g;/* '<S174>/Discrete Transfer Fcn3' */
  real_T DiscreteTransferFcn4_states;  /* '<S174>/Discrete Transfer Fcn4' */
  real_T DiscreteTransferFcn5_states;  /* '<S174>/Discrete Transfer Fcn5' */
  real_T DiscreteTransferFcn2_states_h;/* '<S171>/Discrete Transfer Fcn2' */
  real_T UnitDelay_DSTATE_i;           /* '<S169>/Unit Delay' */
  real_T UnitDelay1_DSTATE[2];         /* '<S266>/Unit Delay1' */
  real_T UnitDelay2_DSTATE[4];         /* '<S217>/Unit Delay2' */
  real_T UnitDelay_DSTATE_e[169];      /* '<S228>/Unit Delay' */
  real_T UnitDelay_DSTATE_k[169];      /* '<S255>/Unit Delay' */
  real_T UnitDelay_DSTATE_o[169];      /* '<S227>/Unit Delay' */
  real_T UnitDelay1_DSTATE_c[169];     /* '<S227>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_b[13];      /* '<S229>/Unit Delay1' */
  real_T NextOutput[4];                /* '<S130>/White Noise' */
  real_T UniformRandomNumber_NextOutput;/* '<S174>/Uniform Random Number' */
  real_T PrevY[4];                     /* '<S7>/Backlash' */
  real_T otime_PreviousInput;          /* '<S223>/otime' */
  real_T olon_PreviousInput;           /* '<S222>/olon' */
  real_T olat_PreviousInput;           /* '<S221>/olat' */
  real_T oalt_PreviousInput;           /* '<S221>/oalt' */
  real_T NextOutput_f;                 /* '<S177>/White Noise' */
  real_T NextOutput_b;                 /* '<S190>/White Noise' */
  real_T NextOutput_i;                 /* '<S187>/White Noise' */
  real_T NextOutput_h;                 /* '<S276>/White Noise' */
  real_T DiscreteTransferFcn_tmp;      /* '<S174>/Discrete Transfer Fcn' */
  real_T NextOutput_m;                 /* '<S277>/White Noise' */
  real_T DiscreteTransferFcn1_tmp;     /* '<S174>/Discrete Transfer Fcn1' */
  real_T NextOutput_a;                 /* '<S278>/White Noise' */
  real_T DiscreteTransferFcn2_tmp;     /* '<S174>/Discrete Transfer Fcn2' */
  real_T NextOutput_k;                 /* '<S274>/White Noise' */
  real_T DiscreteTransferFcn3_tmp;     /* '<S174>/Discrete Transfer Fcn3' */
  real_T NextOutput_n;                 /* '<S275>/White Noise' */
  real_T DiscreteTransferFcn4_tmp;     /* '<S174>/Discrete Transfer Fcn4' */
  real_T NextOutput_p;                 /* '<S279>/White Noise' */
  real_T DiscreteTransferFcn5_tmp;     /* '<S174>/Discrete Transfer Fcn5' */
  real_T NextOutput_e;                 /* '<S185>/White Noise' */
  real_T NextOutput_kd;                /* '<S176>/White Noise' */
  real_T NextOutput_ae;                /* '<S186>/White Noise' */
  real_T NextOutput_mv;                /* '<S184>/White Noise' */
  real_T RateTransition_Buffer0[6];    /* '<S174>/Rate Transition' */
  uint32_T PreLookUpIndexSearchprobofexcee;
                        /* '<S137>/PreLook-Up Index Search  (prob of exceed)' */
  uint32_T PreLookUpIndexSearchaltitude_DW;
                              /* '<S137>/PreLook-Up Index Search  (altitude)' */
  uint32_T RandSeed[4];                /* '<S130>/White Noise' */
  uint32_T RandSeed_j;                 /* '<S174>/Uniform Random Number' */
  uint32_T RandSeed_e;                 /* '<S177>/White Noise' */
  uint32_T RandSeed_a;                 /* '<S190>/White Noise' */
  uint32_T RandSeed_l;                 /* '<S187>/White Noise' */
  uint32_T RandSeed_c;                 /* '<S276>/White Noise' */
  uint32_T RandSeed_m;                 /* '<S277>/White Noise' */
  uint32_T RandSeed_e0;                /* '<S278>/White Noise' */
  uint32_T RandSeed_h;                 /* '<S274>/White Noise' */
  uint32_T RandSeed_b;                 /* '<S275>/White Noise' */
  uint32_T RandSeed_eu;                /* '<S279>/White Noise' */
  uint32_T RandSeed_bf;                /* '<S185>/White Noise' */
  uint32_T RandSeed_p;                 /* '<S176>/White Noise' */
  uint32_T RandSeed_pa;                /* '<S186>/White Noise' */
  uint32_T RandSeed_pb;                /* '<S184>/White Noise' */
  int8_T ifHeightMaxlowaltitudeelseifHei;
  /* '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  int8_T ifHeightMaxlowaltitudeelseifH_m;
  /* '<S125>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  int8_T If_ActiveSubsystem;           /* '<S211>/If' */
  boolean_T RateTransition1_Buffer0;   /* '<S174>/Rate Transition1' */
  boolean_T Convertfromgeodetictosphericalc;
                 /* '<S206>/Convert from geodetic to  spherical coordinates ' */
  boolean_T Convertfromgeodetictospherica_p;
                  /* '<S206>/Convert from geodetic to  spherical coordinates' */
  boolean_T SpecialcaseNorthSouthGeographic;
                      /* '<S226>/Special case - North//South Geographic Pole' */
  boolean_T Hwgws_MODE;                /* '<S121>/Hwgw(s)' */
  boolean_T Hvgws_MODE;                /* '<S121>/Hvgw(s)' */
  boolean_T Hugws_MODE;                /* '<S121>/Hugw(s)' */
  boolean_T Hrgw_MODE;                 /* '<S120>/Hrgw' */
  boolean_T Hqgw_MODE;                 /* '<S120>/Hqgw' */
  boolean_T Hpgw_MODE;                 /* '<S120>/Hpgw' */
} DW_autocodePlant_T;

/* Continuous states (default storage) */
typedef struct {
  real_T uDOFQuaternion_CSTATE[13];    /* '<S5>/6DOF (Quaternion)' */
  real_T wg_p1_CSTATE[2];              /* '<S136>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S136>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S135>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S135>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S134>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S133>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S132>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S131>/pgw_p' */
} X_autocodePlant_T;

/* State derivatives (default storage) */
typedef struct {
  real_T uDOFQuaternion_CSTATE[13];    /* '<S5>/6DOF (Quaternion)' */
  real_T wg_p1_CSTATE[2];              /* '<S136>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S136>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S135>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S135>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S134>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S133>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S132>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S131>/pgw_p' */
} XDot_autocodePlant_T;

/* State disabled  */
typedef struct {
  boolean_T uDOFQuaternion_CSTATE[13]; /* '<S5>/6DOF (Quaternion)' */
  boolean_T wg_p1_CSTATE[2];           /* '<S136>/wg_p1' */
  boolean_T wg_p2_CSTATE[2];           /* '<S136>/wg_p2' */
  boolean_T vg_p1_CSTATE[2];           /* '<S135>/vg_p1' */
  boolean_T vgw_p2_CSTATE[2];          /* '<S135>/vgw_p2' */
  boolean_T ug_p_CSTATE[2];            /* '<S134>/ug_p' */
  boolean_T rgw_p_CSTATE[2];           /* '<S133>/rgw_p' */
  boolean_T qgw_p_CSTATE[2];           /* '<S132>/qgw_p' */
  boolean_T pgw_p_CSTATE[2];           /* '<S131>/pgw_p' */
} XDis_autocodePlant_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T UnitConversion;         /* '<S157>/Unit Conversion' */
  const real_T PreLookUpIndexSearchprobofe;
                        /* '<S137>/PreLook-Up Index Search  (prob of exceed)' */
  const real_T constBlockForifHeightMaxlow;
  const real_T constBlockForifHeightMaxl_b;
  const real_T constBlockForifHeightMaxl_d;
  const real_T constBlockForifHeightMaxl_n;
  const real_T Sqrt[4];                /* '<S130>/Sqrt' */
  const real_T Sqrt1;                  /* '<S130>/Sqrt1' */
  const real_T Divide[4];              /* '<S130>/Divide' */
  const real_T lnref_heightz0;         /* '<S118>/ln(ref_height//z0)' */
  const real_T Product;                /* '<S164>/Product' */
  const real_T Switch;                 /* '<S164>/Switch' */
  const real_T Product_m[9];           /* '<S167>/Product' */
  const real_T dIdt[9];                /* '<S167>/Add' */
  const real_T a2;                     /* '<S218>/a2' */
  const real_T b2;                     /* '<S218>/b2' */
  const real_T c2;                     /* '<S261>/Sum1' */
  const real_T a4;                     /* '<S263>/a4' */
  const real_T b4;                     /* '<S263>/b4' */
  const real_T c4;                     /* '<S263>/Sum9' */
  const real_T c2_l;                   /* '<S264>/Sum1' */
  const real_T Sum;                    /* '<S147>/Sum' */
  const real_T Sum_i;                  /* '<S139>/Sum' */
  const real_T sqrt_g;                 /* '<S136>/sqrt' */
  const uint32_T PreLookUpIndexSearchprobo_j;
                        /* '<S137>/PreLook-Up Index Search  (prob of exceed)' */
} ConstB_autocodePlant_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_autocodePlant_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  B_autocodePlant_T *blockIO;
  X_autocodePlant_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_autocodePlant_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[29];
  real_T odeF[4][29];
  ODE4_IntgData intgData;
  DW_autocodePlant_T *dwork;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[4];
    } TaskCounters;

    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[4];
  } Timing;
};

/* External data declarations for dependent source files */
extern const sensor_bus autocodePlant_rtZsensor_bus;/* sensor_bus ground */
extern const plant_bus autocodePlant_rtZplant_bus;/* plant_bus ground */
extern const ConstB_autocodePlant_T autocodePlant_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void autocodePlant_initialize(RT_MODEL_autocodePlant_T *const
  autocodePlant_M, real_T autocodePlant_U_control_deg[4], sensor_bus
  *autocodePlant_Y_sensor_bus_i, plant_bus *autocodePlant_Y_plant_bus_e);
extern void autocodePlant_step(RT_MODEL_autocodePlant_T *const autocodePlant_M,
  real_T autocodePlant_U_control_deg[4], sensor_bus
  *autocodePlant_Y_sensor_bus_i, plant_bus *autocodePlant_Y_plant_bus_e);
extern void autocodePlant_terminate(RT_MODEL_autocodePlant_T *const
  autocodePlant_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S99>/Add' : Unused code path elimination
 * Block '<S99>/Constant' : Unused code path elimination
 * Block '<S99>/Constant1' : Unused code path elimination
 * Block '<S99>/Divide' : Unused code path elimination
 * Block '<S99>/Divide1' : Unused code path elimination
 * Block '<S103>/DynVisc Conversion' : Unused code path elimination
 * Block '<S99>/Gain' : Unused code path elimination
 * Block '<S105>/KineVisc Conversion' : Unused code path elimination
 * Block '<S99>/Power' : Unused code path elimination
 * Block '<S163>/Element Product' : Unused code path elimination
 * Block '<S163>/Sum' : Unused code path elimination
 * Block '<S160>/Sum' : Unused code path elimination
 * Block '<S165>/Unit Conversion' : Unused code path elimination
 * Block '<S204>/Unit Conversion' : Unused code path elimination
 * Block '<S205>/Unit Conversion' : Unused code path elimination
 * Block '<S102>/Density Conversion' : Eliminated nontunable gain of 1
 * Block '<S104>/Height Conversion' : Eliminated nontunable gain of 1
 * Block '<S107>/Pressure Conversion' : Eliminated nontunable gain of 1
 * Block '<S108>/Speed Conversion' : Eliminated nontunable gain of 1
 * Block '<S109>/Temperature Conversion' : Eliminated nontunable gain of 1
 * Block '<S117>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S117>/Cast To Double1' : Eliminate redundant data type conversion
 * Block '<S117>/Cast To Double2' : Eliminate redundant data type conversion
 * Block '<S117>/Cast To Double3' : Eliminate redundant data type conversion
 * Block '<S117>/Cast To Double4' : Eliminate redundant data type conversion
 * Block '<S143>/Reshape' : Reshape block reduction
 * Block '<S143>/Reshape1' : Reshape block reduction
 * Block '<S145>/Reshape' : Reshape block reduction
 * Block '<S151>/Reshape' : Reshape block reduction
 * Block '<S151>/Reshape1' : Reshape block reduction
 * Block '<S153>/Reshape' : Reshape block reduction
 * Block '<S118>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S118>/Reshape' : Reshape block reduction
 * Block '<S118>/Reshape1' : Reshape block reduction
 * Block '<S166>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S167>/Reshape' : Reshape block reduction
 * Block '<S201>/maxtype' : Eliminate redundant data type conversion
 * Block '<S201>/mintype' : Eliminate redundant data type conversion
 * Block '<S203>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S189>/Unit Conversion2' : Eliminated nontunable gain of 1
 * Block '<S234>/Reshape' : Reshape block reduction
 * Block '<S241>/Reshape' : Reshape block reduction
 * Block '<S242>/Reshape' : Reshape block reduction
 * Block '<S243>/Reshape' : Reshape block reduction
 * Block '<S243>/Reshape1' : Reshape block reduction
 * Block '<S219>/Gain' : Eliminated nontunable gain of 1
 * Block '<S219>/Gain1' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'autocodePlant'
 * '<S1>'   : 'autocodePlant/Plant'
 * '<S2>'   : 'autocodePlant/Sensor Plant'
 * '<S3>'   : 'autocodePlant/Plant/Aero Model'
 * '<S4>'   : 'autocodePlant/Plant/Enviroment'
 * '<S5>'   : 'autocodePlant/Plant/Equatons of Motion'
 * '<S6>'   : 'autocodePlant/Plant/Motor Model'
 * '<S7>'   : 'autocodePlant/Plant/Servo Model'
 * '<S8>'   : 'autocodePlant/Plant/Aero Model/Body'
 * '<S9>'   : 'autocodePlant/Plant/Aero Model/Fin 1'
 * '<S10>'  : 'autocodePlant/Plant/Aero Model/Fin 2'
 * '<S11>'  : 'autocodePlant/Plant/Aero Model/Fin 3'
 * '<S12>'  : 'autocodePlant/Plant/Aero Model/Fin 4'
 * '<S13>'  : 'autocodePlant/Plant/Aero Model/Body/            '
 * '<S14>'  : 'autocodePlant/Plant/Aero Model/Body/             '
 * '<S15>'  : 'autocodePlant/Plant/Aero Model/Body/Cross Product1'
 * '<S16>'  : 'autocodePlant/Plant/Aero Model/Body/Normalize Vector'
 * '<S17>'  : 'autocodePlant/Plant/Aero Model/Body/Radians to Degrees'
 * '<S18>'  : 'autocodePlant/Plant/Aero Model/Fin 1/           '
 * '<S19>'  : 'autocodePlant/Plant/Aero Model/Fin 1/             '
 * '<S20>'  : 'autocodePlant/Plant/Aero Model/Fin 1/              '
 * '<S21>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Cross Product'
 * '<S22>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Cross Product1'
 * '<S23>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation'
 * '<S24>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1'
 * '<S25>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Radians to Degrees'
 * '<S26>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize'
 * '<S27>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V1'
 * '<S28>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V2'
 * '<S29>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V3'
 * '<S30>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S31>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S32>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize'
 * '<S33>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V1'
 * '<S34>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V2'
 * '<S35>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V3'
 * '<S36>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S37>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S38>'  : 'autocodePlant/Plant/Aero Model/Fin 2/           '
 * '<S39>'  : 'autocodePlant/Plant/Aero Model/Fin 2/             '
 * '<S40>'  : 'autocodePlant/Plant/Aero Model/Fin 2/              '
 * '<S41>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Cross Product'
 * '<S42>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Cross Product1'
 * '<S43>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation'
 * '<S44>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1'
 * '<S45>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Radians to Degrees'
 * '<S46>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize'
 * '<S47>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V1'
 * '<S48>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V2'
 * '<S49>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V3'
 * '<S50>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S51>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S52>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize'
 * '<S53>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V1'
 * '<S54>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V2'
 * '<S55>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V3'
 * '<S56>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S57>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S58>'  : 'autocodePlant/Plant/Aero Model/Fin 3/           '
 * '<S59>'  : 'autocodePlant/Plant/Aero Model/Fin 3/             '
 * '<S60>'  : 'autocodePlant/Plant/Aero Model/Fin 3/              '
 * '<S61>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Cross Product'
 * '<S62>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Cross Product1'
 * '<S63>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation'
 * '<S64>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1'
 * '<S65>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Radians to Degrees'
 * '<S66>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize'
 * '<S67>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V1'
 * '<S68>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V2'
 * '<S69>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V3'
 * '<S70>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S71>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S72>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize'
 * '<S73>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V1'
 * '<S74>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V2'
 * '<S75>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V3'
 * '<S76>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S77>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S78>'  : 'autocodePlant/Plant/Aero Model/Fin 4/           '
 * '<S79>'  : 'autocodePlant/Plant/Aero Model/Fin 4/             '
 * '<S80>'  : 'autocodePlant/Plant/Aero Model/Fin 4/              '
 * '<S81>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Cross Product'
 * '<S82>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Cross Product1'
 * '<S83>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation'
 * '<S84>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1'
 * '<S85>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Radians to Degrees'
 * '<S86>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize'
 * '<S87>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V1'
 * '<S88>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V2'
 * '<S89>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V3'
 * '<S90>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S91>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S92>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize'
 * '<S93>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V1'
 * '<S94>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V2'
 * '<S95>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V3'
 * '<S96>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S97>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S98>'  : 'autocodePlant/Plant/Enviroment/Compare To Constant'
 * '<S99>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model'
 * '<S100>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation'
 * '<S101>' : 'autocodePlant/Plant/Enviroment/windModel'
 * '<S102>' : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Density Subsystem'
 * '<S103>' : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/DynVisc Subsystem'
 * '<S104>' : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Height Subsystem'
 * '<S105>' : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/KineVisc Subsystem'
 * '<S106>' : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Modelling'
 * '<S107>' : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Pressure Subsystem'
 * '<S108>' : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Speed Subsystem'
 * '<S109>' : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Temperature Subsystem'
 * '<S110>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize'
 * '<S111>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V1'
 * '<S112>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V2'
 * '<S113>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V3'
 * '<S114>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S115>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S116>' : 'autocodePlant/Plant/Enviroment/windModel/             '
 * '<S117>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))'
 * '<S118>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model'
 * '<S119>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Angle Conversion'
 * '<S120>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates'
 * '<S121>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities'
 * '<S122>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Length Conversion'
 * '<S123>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Length Conversion1'
 * '<S124>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities'
 * '<S125>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates'
 * '<S126>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities'
 * '<S127>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths'
 * '<S128>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Velocity Conversion'
 * '<S129>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Velocity Conversion2'
 * '<S130>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/White Noise'
 * '<S131>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hpgw'
 * '<S132>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hqgw'
 * '<S133>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hrgw'
 * '<S134>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hugw(s)'
 * '<S135>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hvgw(s)'
 * '<S136>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hwgw(s)'
 * '<S137>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities/High Altitude Intensity'
 * '<S138>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities/Low Altitude Intensity'
 * '<S139>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates'
 * '<S140>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates'
 * '<S141>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Medium//High  altitude rates'
 * '<S142>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Merge Subsystems'
 * '<S143>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates/wind to body transformation'
 * '<S144>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates/wind to body transformation/convert to earth coords'
 * '<S145>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates/wind to body transformation'
 * '<S146>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates/wind to body transformation/convert to earth coords'
 * '<S147>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities'
 * '<S148>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities'
 * '<S149>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Medium//High  altitude velocities'
 * '<S150>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Merge Subsystems'
 * '<S151>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities/wind to body transformation'
 * '<S152>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities/wind to body transformation/convert to earth coords'
 * '<S153>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities/wind to body transformation'
 * '<S154>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities/wind to body transformation/convert to earth coords'
 * '<S155>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Low altitude scale length'
 * '<S156>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Medium//High altitude scale length'
 * '<S157>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Medium//High altitude scale length/Length Conversion'
 * '<S158>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model/Angle Conversion'
 * '<S159>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model/Length Conversion'
 * '<S160>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration'
 * '<S161>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration'
 * '<S162>' : 'autocodePlant/Plant/Equatons of Motion/Rail Model'
 * '<S163>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Cross Product'
 * '<S164>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Total Force'
 * '<S165>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Velocity Conversion'
 * '<S166>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Velocity Conversion1'
 * '<S167>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration/Compute dIdt'
 * '<S168>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration/Cross Product'
 * '<S169>' : 'autocodePlant/Plant/Motor Model/clock'
 * '<S170>' : 'autocodePlant/Sensor Plant/Accelerometer'
 * '<S171>' : 'autocodePlant/Sensor Plant/Barometer'
 * '<S172>' : 'autocodePlant/Sensor Plant/Gyroscope'
 * '<S173>' : 'autocodePlant/Sensor Plant/Magnetometer'
 * '<S174>' : 'autocodePlant/Sensor Plant/Subsystem'
 * '<S175>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation'
 * '<S176>' : 'autocodePlant/Sensor Plant/Accelerometer/w(t)'
 * '<S177>' : 'autocodePlant/Sensor Plant/Accelerometer/w2(t)'
 * '<S178>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize'
 * '<S179>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V1'
 * '<S180>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V2'
 * '<S181>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V3'
 * '<S182>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S183>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S184>' : 'autocodePlant/Sensor Plant/Barometer/w(t)'
 * '<S185>' : 'autocodePlant/Sensor Plant/Barometer/white-noise'
 * '<S186>' : 'autocodePlant/Sensor Plant/Gyroscope/w(t)'
 * '<S187>' : 'autocodePlant/Sensor Plant/Gyroscope/w2(t)'
 * '<S188>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation'
 * '<S189>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model'
 * '<S190>' : 'autocodePlant/Sensor Plant/Magnetometer/white-noise'
 * '<S191>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize'
 * '<S192>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V1'
 * '<S193>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V2'
 * '<S194>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V3'
 * '<S195>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S196>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S197>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Altitude'
 * '<S198>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Latitude'
 * '<S199>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Longitude'
 * '<S200>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Compute x,y,z, and h components of magnetic field'
 * '<S201>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Is time within model limits'
 * '<S202>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap'
 * '<S203>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Length Conversion'
 * '<S204>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/MagField Conversion'
 * '<S205>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/MagField Conversion1'
 * '<S206>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag'
 * '<S207>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Compute x,y,z, and h components of magnetic field/Angle Conversion'
 * '<S208>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90'
 * '<S209>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Wrap Longitude'
 * '<S210>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Compare To Constant'
 * '<S211>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero'
 * '<S212>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Wrap Angle 180'
 * '<S213>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero/If Action Subsystem'
 * '<S214>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero/If Action Subsystem1'
 * '<S215>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
 * '<S216>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Wrap Longitude/Compare To Constant'
 * '<S217>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates'
 * '<S218>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates'
 * '<S219>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates '
 * '<S220>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Get Cosine and Sine  of Latitude and Longitude'
 * '<S221>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has altitude or latitude changed'
 * '<S222>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has longitude changed '
 * '<S223>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has time changed'
 * '<S224>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity'
 * '<S225>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem'
 * '<S226>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion'
 * '<S227>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations'
 * '<S228>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients'
 * '<S229>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole'
 * '<S230>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate  index'
 * '<S231>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values'
 * '<S232>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/special case'
 * '<S233>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem1'
 * '<S234>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2'
 * '<S235>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2/calculate  indices'
 * '<S236>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2/calculate  row and column'
 * '<S237>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem'
 * '<S238>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1'
 * '<S239>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1/m,n'
 * '<S240>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1/n,m-1'
 * '<S241>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem'
 * '<S242>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1'
 * '<S243>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2'
 * '<S244>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/calculate  index'
 * '<S245>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem/calculate  index'
 * '<S246>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem/calculate  row and column'
 * '<S247>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1/calculate  index'
 * '<S248>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1/calculate  row and column'
 * '<S249>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  indices'
 * '<S250>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  row and column1'
 * '<S251>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  row and column2'
 * '<S252>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/m<n-2'
 * '<S253>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/m<n-2 '
 * '<S254>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/If Action Subsystem'
 * '<S255>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)'
 * '<S256>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)/If Action Subsystem1'
 * '<S257>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)/If Action Subsystem2'
 * '<S258>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate ca'
 * '<S259>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate ct'
 * '<S260>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate d'
 * '<S261>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate q'
 * '<S262>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate q2'
 * '<S263>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate r2'
 * '<S264>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate sa'
 * '<S265>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate st'
 * '<S266>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates /For Iterator Subsystem'
 * '<S267>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Get Cosine and Sine  of Latitude and Longitude/Angle Conversion2'
 * '<S268>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate bx'
 * '<S269>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate by'
 * '<S270>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate bz'
 * '<S271>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity'
 * '<S272>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity/Angle Conversion'
 * '<S273>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity/Angle Conversion1'
 * '<S274>' : 'autocodePlant/Sensor Plant/Subsystem/Band-Limited White Noise1'
 * '<S275>' : 'autocodePlant/Sensor Plant/Subsystem/Band-Limited White Noise2'
 * '<S276>' : 'autocodePlant/Sensor Plant/Subsystem/Band-Limited White Noise3'
 * '<S277>' : 'autocodePlant/Sensor Plant/Subsystem/Band-Limited White Noise4'
 * '<S278>' : 'autocodePlant/Sensor Plant/Subsystem/Band-Limited White Noise5'
 * '<S279>' : 'autocodePlant/Sensor Plant/Subsystem/Band-Limited White Noise6'
 * '<S280>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Inverse'
 * '<S281>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Rotation'
 * '<S282>' : 'autocodePlant/Sensor Plant/Subsystem/Subsystem'
 * '<S283>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Inverse/Quaternion Conjugate'
 * '<S284>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Inverse/Quaternion Norm'
 * '<S285>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Rotation/Quaternion Normalize'
 * '<S286>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Rotation/V1'
 * '<S287>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Rotation/V2'
 * '<S288>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Rotation/V3'
 * '<S289>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S290>' : 'autocodePlant/Sensor Plant/Subsystem/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 */
#endif                                 /* autocodePlant_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
