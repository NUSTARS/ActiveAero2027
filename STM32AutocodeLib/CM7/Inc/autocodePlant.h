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
 * C/C++ source code generated on : Tue Oct 27 19:08:19 2026
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
  real_T biasnoise[3];                 /* '<S155>/bias + noise' */
  real_T Delay;                        /* '<S6>/Delay' */
  real_T Backlash[4];                  /* '<S7>/Backlash' */
  real_T Sum[3];                       /* '<S147>/Sum' */
  real_T fBdy_mps2[3];                 /* '<S155>/fBdy_mps2' */
  real_T Output[3];                    /* '<S174>/Output' */
  real_T Switch;                       /* '<S193>/Switch' */
  real_T Merge;                        /* '<S195>/Merge' */
  real_T Switch_l;                     /* '<S192>/Switch' */
  real_T olat;                         /* '<S205>/olat' */
  real_T Gain;                         /* '<S173>/Gain' */
  real_T oalt;                         /* '<S205>/oalt' */
  real_T Output_g;                     /* '<S169>/Output' */
  real_T Product[3];                   /* '<S147>/Product' */
  real_T Product_d[4];                 /* '<S115>/Product' */
  real_T Output_o[3];                  /* '<S160>/Output' */
  real_T Output_n;                     /* '<S168>/Output' */
  real_T Output_e[3];                  /* '<S170>/Output' */
  real_T OutportBufferForcp13[13];
  real_T OutportBufferForsp13[13];
  real_T Assignment[11];               /* '<S250>/Assignment' */
  real_T Assignment1[11];              /* '<S250>/Assignment1' */
  real_T sqrt_b;                       /* '<S202>/sqrt' */
  real_T Product11;                    /* '<S242>/Product11' */
  real_T Product12;                    /* '<S248>/Product12' */
  real_T Product4;                     /* '<S243>/Product4' */
  real_T sqrt_k;                       /* '<S249>/sqrt' */
  real_T Sum2;                         /* '<S210>/Sum2' */
  real_T Sum3;                         /* '<S210>/Sum3' */
  real_T Sum1_p;                       /* '<S210>/Sum1' */
  real_T Sum5;                         /* '<S210>/Sum5' */
  real_T Assignment_o[169];            /* '<S212>/Assignment' */
  real_T Sum2_p[169];                  /* '<S212>/Sum2' */
  real_T Assignment2[169];             /* '<S240>/Assignment2' */
  real_T Merge_b;                      /* '<S211>/Merge' */
  real_T Assignment_snorm[169];        /* '<S211>/Assignment_snorm' */
  real_T Merge1_i;                     /* '<S211>/Merge1' */
  real_T Assignment_h[169];            /* '<S211>/Assignment' */
  real_T Product2;                     /* '<S213>/Product2' */
  real_T Assignment2_a[13];            /* '<S218>/Assignment2' */
  real_T Assignment2_m[13];            /* '<S217>/Assignment2' */
  real_T w[2];                         /* '<S121>/w' */
  real_T w_h[2];                       /* '<S121>/w ' */
  real_T LwgV1[2];                     /* '<S121>/Lwg//V 1' */
  real_T w_c[2];                       /* '<S120>/w' */
  real_T w_j[2];                       /* '<S120>/w ' */
  real_T w1[2];                        /* '<S120>/w 1' */
  real_T w_d[2];                       /* '<S119>/w' */
  real_T w_g[2];                       /* '<S118>/w' */
  real_T w_j5[2];                      /* '<S117>/w' */
  real_T w_p[2];                       /* '<S116>/w' */
} B_autocodePlant_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTransferFcn_states;   /* '<S157>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_states;  /* '<S157>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn2_states;  /* '<S157>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn2_states_k;/* '<S155>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn1_states_a;/* '<S155>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn3_states;  /* '<S155>/Discrete Transfer Fcn3' */
  real_T Delay_DSTATE[2000];           /* '<S6>/Delay' */
  real_T UnitDelay_DSTATE[4];          /* '<S7>/Unit Delay' */
  real_T UnitDelay_DSTATE_c[3];        /* '<S157>/Unit Delay' */
  real_T DiscreteTransferFcn2_states_h;/* '<S156>/Discrete Transfer Fcn2' */
  real_T UnitDelay_DSTATE_i;           /* '<S154>/Unit Delay' */
  real_T UnitDelay1_DSTATE[2];         /* '<S250>/Unit Delay1' */
  real_T UnitDelay2_DSTATE[4];         /* '<S201>/Unit Delay2' */
  real_T UnitDelay_DSTATE_e[169];      /* '<S212>/Unit Delay' */
  real_T UnitDelay_DSTATE_k[169];      /* '<S239>/Unit Delay' */
  real_T UnitDelay_DSTATE_o[169];      /* '<S211>/Unit Delay' */
  real_T UnitDelay1_DSTATE_c[169];     /* '<S211>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_b[13];      /* '<S213>/Unit Delay1' */
  real_T NextOutput;                   /* '<S161>/White Noise' */
  real_T PrevY[4];                     /* '<S7>/Backlash' */
  real_T NextOutput_i;                 /* '<S171>/White Noise' */
  real_T NextOutput_b;                 /* '<S174>/White Noise' */
  real_T otime_PreviousInput;          /* '<S207>/otime' */
  real_T olon_PreviousInput;           /* '<S206>/olon' */
  real_T olat_PreviousInput;           /* '<S205>/olat' */
  real_T oalt_PreviousInput;           /* '<S205>/oalt' */
  real_T NextOutput_e;                 /* '<S169>/White Noise' */
  real_T NextOutput_d[4];              /* '<S115>/White Noise' */
  real_T NextOutput_k;                 /* '<S160>/White Noise' */
  real_T NextOutput_m;                 /* '<S168>/White Noise' */
  real_T NextOutput_a;                 /* '<S170>/White Noise' */
  uint32_T PreLookUpIndexSearchprobofexcee;
                        /* '<S122>/PreLook-Up Index Search  (prob of exceed)' */
  uint32_T RandSeed;                   /* '<S161>/White Noise' */
  uint32_T RandSeed_l;                 /* '<S171>/White Noise' */
  uint32_T RandSeed_a;                 /* '<S174>/White Noise' */
  uint32_T RandSeed_b;                 /* '<S169>/White Noise' */
  uint32_T PreLookUpIndexSearchaltitude_DW;
                              /* '<S122>/PreLook-Up Index Search  (altitude)' */
  uint32_T RandSeed_i[4];              /* '<S115>/White Noise' */
  uint32_T RandSeed_p;                 /* '<S160>/White Noise' */
  uint32_T RandSeed_pb;                /* '<S168>/White Noise' */
  uint32_T RandSeed_pa;                /* '<S170>/White Noise' */
  int8_T If_ActiveSubsystem;           /* '<S195>/If' */
  int8_T ifHeightMaxlowaltitudeelseifHei;
  /* '<S110>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  int8_T ifHeightMaxlowaltitudeelseifH_f;
  /* '<S111>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  boolean_T Convertfromgeodetictosphericalc;
                 /* '<S190>/Convert from geodetic to  spherical coordinates ' */
  boolean_T Convertfromgeodetictospherica_p;
                  /* '<S190>/Convert from geodetic to  spherical coordinates' */
  boolean_T SpecialcaseNorthSouthGeographic;
                      /* '<S210>/Special case - North//South Geographic Pole' */
  boolean_T Hwgws_MODE;                /* '<S106>/Hwgw(s)' */
  boolean_T Hvgws_MODE;                /* '<S106>/Hvgw(s)' */
  boolean_T Hugws_MODE;                /* '<S106>/Hugw(s)' */
  boolean_T Hrgw_MODE;                 /* '<S105>/Hrgw' */
  boolean_T Hqgw_MODE;                 /* '<S105>/Hqgw' */
  boolean_T Hpgw_MODE;                 /* '<S105>/Hpgw' */
} DW_autocodePlant_T;

/* Continuous states (default storage) */
typedef struct {
  real_T uDOFQuaternion_CSTATE[13];    /* '<S5>/6DOF (Quaternion)' */
  real_T wg_p1_CSTATE[2];              /* '<S121>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S121>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S120>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S120>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S119>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S118>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S117>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S116>/pgw_p' */
} X_autocodePlant_T;

/* State derivatives (default storage) */
typedef struct {
  real_T uDOFQuaternion_CSTATE[13];    /* '<S5>/6DOF (Quaternion)' */
  real_T wg_p1_CSTATE[2];              /* '<S121>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S121>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S120>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S120>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S119>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S118>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S117>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S116>/pgw_p' */
} XDot_autocodePlant_T;

/* State disabled  */
typedef struct {
  boolean_T uDOFQuaternion_CSTATE[13]; /* '<S5>/6DOF (Quaternion)' */
  boolean_T wg_p1_CSTATE[2];           /* '<S121>/wg_p1' */
  boolean_T wg_p2_CSTATE[2];           /* '<S121>/wg_p2' */
  boolean_T vg_p1_CSTATE[2];           /* '<S120>/vg_p1' */
  boolean_T vgw_p2_CSTATE[2];          /* '<S120>/vgw_p2' */
  boolean_T ug_p_CSTATE[2];            /* '<S119>/ug_p' */
  boolean_T rgw_p_CSTATE[2];           /* '<S118>/rgw_p' */
  boolean_T qgw_p_CSTATE[2];           /* '<S117>/qgw_p' */
  boolean_T pgw_p_CSTATE[2];           /* '<S116>/pgw_p' */
} XDis_autocodePlant_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Product6[3];            /* '<S9>/Product6' */
  const real_T RotationAnglestoQuaternions[4];
                                     /* '<S9>/Rotation Angles to Quaternions' */
  const real_T Product;                /* '<S26>/Product' */
  const real_T Product1;               /* '<S26>/Product1' */
  const real_T Product2;               /* '<S26>/Product2' */
  const real_T Product3;               /* '<S26>/Product3' */
  const real_T Sum;                    /* '<S26>/Sum' */
  const real_T sqrt_b;                 /* '<S25>/sqrt' */
  const real_T Product_p;              /* '<S21>/Product' */
  const real_T Product1_j;             /* '<S21>/Product1' */
  const real_T Product2_h;             /* '<S21>/Product2' */
  const real_T Product3_a;             /* '<S21>/Product3' */
  const real_T Product_n;              /* '<S22>/Product' */
  const real_T Product1_k;             /* '<S22>/Product1' */
  const real_T Sum1;                   /* '<S22>/Sum1' */
  const real_T Gain;                   /* '<S22>/Gain' */
  const real_T Product2_b;             /* '<S22>/Product2' */
  const real_T Product3_k;             /* '<S22>/Product3' */
  const real_T Sum2;                   /* '<S22>/Sum2' */
  const real_T Gain1;                  /* '<S22>/Gain1' */
  const real_T Product6_n;             /* '<S22>/Product6' */
  const real_T Product7;               /* '<S22>/Product7' */
  const real_T Sum3;                   /* '<S22>/Sum3' */
  const real_T Gain2;                  /* '<S22>/Gain2' */
  const real_T Product4;               /* '<S22>/Product4' */
  const real_T Product5;               /* '<S22>/Product5' */
  const real_T Product8;               /* '<S22>/Product8' */
  const real_T Sum_f;                  /* '<S22>/Sum' */
  const real_T Product_e;              /* '<S23>/Product' */
  const real_T Product1_n;             /* '<S23>/Product1' */
  const real_T Sum1_l;                 /* '<S23>/Sum1' */
  const real_T Gain_i;                 /* '<S23>/Gain' */
  const real_T Product2_g;             /* '<S23>/Product2' */
  const real_T Product3_h;             /* '<S23>/Product3' */
  const real_T Sum2_e;                 /* '<S23>/Sum2' */
  const real_T Gain1_j;                /* '<S23>/Gain1' */
  const real_T Product6_g;             /* '<S23>/Product6' */
  const real_T Product7_f;             /* '<S23>/Product7' */
  const real_T Sum3_o;                 /* '<S23>/Sum3' */
  const real_T Gain2_p;                /* '<S23>/Gain2' */
  const real_T Product4_n;             /* '<S23>/Product4' */
  const real_T Product5_m;             /* '<S23>/Product5' */
  const real_T Product8_k;             /* '<S23>/Product8' */
  const real_T Sum_i;                  /* '<S23>/Sum' */
  const real_T Product_c;              /* '<S24>/Product' */
  const real_T Product1_h;             /* '<S24>/Product1' */
  const real_T Sum1_g;                 /* '<S24>/Sum1' */
  const real_T Gain_b;                 /* '<S24>/Gain' */
  const real_T Product2_l;             /* '<S24>/Product2' */
  const real_T Product3_kq;            /* '<S24>/Product3' */
  const real_T Sum2_m;                 /* '<S24>/Sum2' */
  const real_T Gain1_n;                /* '<S24>/Gain1' */
  const real_T Product6_l;             /* '<S24>/Product6' */
  const real_T Product7_g;             /* '<S24>/Product7' */
  const real_T Sum3_d;                 /* '<S24>/Sum3' */
  const real_T Gain2_b;                /* '<S24>/Gain2' */
  const real_T Product4_j;             /* '<S24>/Product4' */
  const real_T Product5_c;             /* '<S24>/Product5' */
  const real_T Product8_a;             /* '<S24>/Product8' */
  const real_T Sum_e;                  /* '<S24>/Sum' */
  const real_T Product_j;              /* '<S32>/Product' */
  const real_T Product1_i;             /* '<S32>/Product1' */
  const real_T Product2_m;             /* '<S32>/Product2' */
  const real_T Product3_m;             /* '<S32>/Product3' */
  const real_T Sum_i4;                 /* '<S32>/Sum' */
  const real_T sqrt_k;                 /* '<S31>/sqrt' */
  const real_T Product_eo;             /* '<S27>/Product' */
  const real_T Product1_iu;            /* '<S27>/Product1' */
  const real_T Product2_a;             /* '<S27>/Product2' */
  const real_T Product3_f;             /* '<S27>/Product3' */
  const real_T Product_a;              /* '<S28>/Product' */
  const real_T Product1_e;             /* '<S28>/Product1' */
  const real_T Sum1_p;                 /* '<S28>/Sum1' */
  const real_T Gain_p;                 /* '<S28>/Gain' */
  const real_T Product2_i;             /* '<S28>/Product2' */
  const real_T Product3_kx;            /* '<S28>/Product3' */
  const real_T Sum2_d;                 /* '<S28>/Sum2' */
  const real_T Gain1_o;                /* '<S28>/Gain1' */
  const real_T Product6_c;             /* '<S28>/Product6' */
  const real_T Product7_f5;            /* '<S28>/Product7' */
  const real_T Sum3_b;                 /* '<S28>/Sum3' */
  const real_T Gain2_po;               /* '<S28>/Gain2' */
  const real_T Product4_e;             /* '<S28>/Product4' */
  const real_T Product5_b;             /* '<S28>/Product5' */
  const real_T Product8_m;             /* '<S28>/Product8' */
  const real_T Sum_b;                  /* '<S28>/Sum' */
  const real_T Product_nc;             /* '<S29>/Product' */
  const real_T Product1_ne;            /* '<S29>/Product1' */
  const real_T Sum1_pw;                /* '<S29>/Sum1' */
  const real_T Gain_ip;                /* '<S29>/Gain' */
  const real_T Product2_j;             /* '<S29>/Product2' */
  const real_T Product3_mj;            /* '<S29>/Product3' */
  const real_T Sum2_p;                 /* '<S29>/Sum2' */
  const real_T Gain1_d;                /* '<S29>/Gain1' */
  const real_T Product6_f;             /* '<S29>/Product6' */
  const real_T Product7_p;             /* '<S29>/Product7' */
  const real_T Sum3_j;                 /* '<S29>/Sum3' */
  const real_T Gain2_k;                /* '<S29>/Gain2' */
  const real_T Product4_p;             /* '<S29>/Product4' */
  const real_T Product5_i;             /* '<S29>/Product5' */
  const real_T Product8_a4;            /* '<S29>/Product8' */
  const real_T Sum_l;                  /* '<S29>/Sum' */
  const real_T Product_l;              /* '<S30>/Product' */
  const real_T Product1_f;             /* '<S30>/Product1' */
  const real_T Sum1_b;                 /* '<S30>/Sum1' */
  const real_T Gain_f;                 /* '<S30>/Gain' */
  const real_T Product2_gv;            /* '<S30>/Product2' */
  const real_T Product3_fg;            /* '<S30>/Product3' */
  const real_T Sum2_k;                 /* '<S30>/Sum2' */
  const real_T Gain1_np;               /* '<S30>/Gain1' */
  const real_T Product6_fr;            /* '<S30>/Product6' */
  const real_T Product7_fy;            /* '<S30>/Product7' */
  const real_T Sum3_i;                 /* '<S30>/Sum3' */
  const real_T Gain2_o;                /* '<S30>/Gain2' */
  const real_T Product4_e2;            /* '<S30>/Product4' */
  const real_T Product5_b0;            /* '<S30>/Product5' */
  const real_T Product8_a3;            /* '<S30>/Product8' */
  const real_T Sum_c;                  /* '<S30>/Sum' */
  const real_T Subtract1[3];           /* '<S9>/Subtract1' */
  const real_T Sum2_i[3];              /* '<S9>/Sum2' */
  const real_T Product6_m[3];          /* '<S10>/Product6' */
  const real_T RotationAnglestoQuaternio_p[4];
                                    /* '<S10>/Rotation Angles to Quaternions' */
  const real_T Product_ji;             /* '<S43>/Product' */
  const real_T Product1_es;            /* '<S43>/Product1' */
  const real_T Product2_in;            /* '<S43>/Product2' */
  const real_T Product3_i;             /* '<S43>/Product3' */
  const real_T Sum_iy;                 /* '<S43>/Sum' */
  const real_T sqrt_i;                 /* '<S42>/sqrt' */
  const real_T Product_g;              /* '<S38>/Product' */
  const real_T Product1_d;             /* '<S38>/Product1' */
  const real_T Product2_my;            /* '<S38>/Product2' */
  const real_T Product3_ac;            /* '<S38>/Product3' */
  const real_T Product_k;              /* '<S39>/Product' */
  const real_T Product1_h3;            /* '<S39>/Product1' */
  const real_T Sum1_by;                /* '<S39>/Sum1' */
  const real_T Gain_d;                 /* '<S39>/Gain' */
  const real_T Product2_it;            /* '<S39>/Product2' */
  const real_T Product3_as;            /* '<S39>/Product3' */
  const real_T Sum2_c;                 /* '<S39>/Sum2' */
  const real_T Gain1_n0;               /* '<S39>/Gain1' */
  const real_T Product6_a;             /* '<S39>/Product6' */
  const real_T Product7_fk;            /* '<S39>/Product7' */
  const real_T Sum3_f;                 /* '<S39>/Sum3' */
  const real_T Gain2_a;                /* '<S39>/Gain2' */
  const real_T Product4_g;             /* '<S39>/Product4' */
  const real_T Product5_mk;            /* '<S39>/Product5' */
  const real_T Product8_e;             /* '<S39>/Product8' */
  const real_T Sum_m;                  /* '<S39>/Sum' */
  const real_T Product_kq;             /* '<S40>/Product' */
  const real_T Product1_c;             /* '<S40>/Product1' */
  const real_T Sum1_li;                /* '<S40>/Sum1' */
  const real_T Gain_e;                 /* '<S40>/Gain' */
  const real_T Product2_d;             /* '<S40>/Product2' */
  const real_T Product3_g;             /* '<S40>/Product3' */
  const real_T Sum2_n;                 /* '<S40>/Sum2' */
  const real_T Gain1_npp;              /* '<S40>/Gain1' */
  const real_T Product6_h;             /* '<S40>/Product6' */
  const real_T Product7_gx;            /* '<S40>/Product7' */
  const real_T Sum3_be;                /* '<S40>/Sum3' */
  const real_T Gain2_c;                /* '<S40>/Gain2' */
  const real_T Product4_f;             /* '<S40>/Product4' */
  const real_T Product5_l;             /* '<S40>/Product5' */
  const real_T Product8_m4;            /* '<S40>/Product8' */
  const real_T Sum_b1;                 /* '<S40>/Sum' */
  const real_T Product_ac;             /* '<S41>/Product' */
  const real_T Product1_hd;            /* '<S41>/Product1' */
  const real_T Sum1_n;                 /* '<S41>/Sum1' */
  const real_T Gain_a;                 /* '<S41>/Gain' */
  const real_T Product2_lr;            /* '<S41>/Product2' */
  const real_T Product3_hc;            /* '<S41>/Product3' */
  const real_T Sum2_pw;                /* '<S41>/Sum2' */
  const real_T Gain1_p;                /* '<S41>/Gain1' */
  const real_T Product6_d;             /* '<S41>/Product6' */
  const real_T Product7_h;             /* '<S41>/Product7' */
  const real_T Sum3_n;                 /* '<S41>/Sum3' */
  const real_T Gain2_ps;               /* '<S41>/Gain2' */
  const real_T Product4_k;             /* '<S41>/Product4' */
  const real_T Product5_e;             /* '<S41>/Product5' */
  const real_T Product8_m5;            /* '<S41>/Product8' */
  const real_T Sum_k;                  /* '<S41>/Sum' */
  const real_T Product_h;              /* '<S49>/Product' */
  const real_T Product1_cm;            /* '<S49>/Product1' */
  const real_T Product2_n;             /* '<S49>/Product2' */
  const real_T Product3_gd;            /* '<S49>/Product3' */
  const real_T Sum_h;                  /* '<S49>/Sum' */
  const real_T sqrt_l;                 /* '<S48>/sqrt' */
  const real_T Product_i;              /* '<S44>/Product' */
  const real_T Product1_l;             /* '<S44>/Product1' */
  const real_T Product2_gk;            /* '<S44>/Product2' */
  const real_T Product3_o;             /* '<S44>/Product3' */
  const real_T Product_ga;             /* '<S45>/Product' */
  const real_T Product1_p;             /* '<S45>/Product1' */
  const real_T Sum1_a;                 /* '<S45>/Sum1' */
  const real_T Gain_k;                 /* '<S45>/Gain' */
  const real_T Product2_e;             /* '<S45>/Product2' */
  const real_T Product3_j;             /* '<S45>/Product3' */
  const real_T Sum2_o;                 /* '<S45>/Sum2' */
  const real_T Gain1_k;                /* '<S45>/Gain1' */
  const real_T Product6_gg;            /* '<S45>/Product6' */
  const real_T Product7_n;             /* '<S45>/Product7' */
  const real_T Sum3_b0;                /* '<S45>/Sum3' */
  const real_T Gain2_cm;               /* '<S45>/Gain2' */
  const real_T Product4_gs;            /* '<S45>/Product4' */
  const real_T Product5_lz;            /* '<S45>/Product5' */
  const real_T Product8_g;             /* '<S45>/Product8' */
  const real_T Sum_k3;                 /* '<S45>/Sum' */
  const real_T Product_gu;             /* '<S46>/Product' */
  const real_T Product1_g;             /* '<S46>/Product1' */
  const real_T Sum1_j;                 /* '<S46>/Sum1' */
  const real_T Gain_o;                 /* '<S46>/Gain' */
  const real_T Product2_b3;            /* '<S46>/Product2' */
  const real_T Product3_af;            /* '<S46>/Product3' */
  const real_T Sum2_kc;                /* '<S46>/Sum2' */
  const real_T Gain1_h;                /* '<S46>/Gain1' */
  const real_T Product6_i;             /* '<S46>/Product6' */
  const real_T Product7_h0;            /* '<S46>/Product7' */
  const real_T Sum3_a;                 /* '<S46>/Sum3' */
  const real_T Gain2_pr;               /* '<S46>/Gain2' */
  const real_T Product4_ks;            /* '<S46>/Product4' */
  const real_T Product5_c3;            /* '<S46>/Product5' */
  const real_T Product8_p;             /* '<S46>/Product8' */
  const real_T Sum_cv;                 /* '<S46>/Sum' */
  const real_T Product_aa;             /* '<S47>/Product' */
  const real_T Product1_o;             /* '<S47>/Product1' */
  const real_T Sum1_h;                 /* '<S47>/Sum1' */
  const real_T Gain_of;                /* '<S47>/Gain' */
  const real_T Product2_dy;            /* '<S47>/Product2' */
  const real_T Product3_ja;            /* '<S47>/Product3' */
  const real_T Sum2_el;                /* '<S47>/Sum2' */
  const real_T Gain1_i;                /* '<S47>/Gain1' */
  const real_T Product6_fm;            /* '<S47>/Product6' */
  const real_T Product7_m;             /* '<S47>/Product7' */
  const real_T Sum3_jk;                /* '<S47>/Sum3' */
  const real_T Gain2_d;                /* '<S47>/Gain2' */
  const real_T Product4_o;             /* '<S47>/Product4' */
  const real_T Product5_h;             /* '<S47>/Product5' */
  const real_T Product8_l;             /* '<S47>/Product8' */
  const real_T Sum_b1v;                /* '<S47>/Sum' */
  const real_T Subtract1_m[3];         /* '<S10>/Subtract1' */
  const real_T Sum2_l[3];              /* '<S10>/Sum2' */
  const real_T Product6_c1[3];         /* '<S11>/Product6' */
  const real_T RotationAnglestoQuaternio_o[4];
                                    /* '<S11>/Rotation Angles to Quaternions' */
  const real_T Product_p4;             /* '<S60>/Product' */
  const real_T Product1_gn;            /* '<S60>/Product1' */
  const real_T Product2_c;             /* '<S60>/Product2' */
  const real_T Product3_it;            /* '<S60>/Product3' */
  const real_T Sum_ed;                 /* '<S60>/Sum' */
  const real_T sqrt_a;                 /* '<S59>/sqrt' */
  const real_T Product_hg;             /* '<S55>/Product' */
  const real_T Product1_cf;            /* '<S55>/Product1' */
  const real_T Product2_m0;            /* '<S55>/Product2' */
  const real_T Product3_m4;            /* '<S55>/Product3' */
  const real_T Product_ea;             /* '<S56>/Product' */
  const real_T Product1_ia;            /* '<S56>/Product1' */
  const real_T Sum1_aa;                /* '<S56>/Sum1' */
  const real_T Gain_eb;                /* '<S56>/Gain' */
  const real_T Product2_n0;            /* '<S56>/Product2' */
  const real_T Product3_or;            /* '<S56>/Product3' */
  const real_T Sum2_kn;                /* '<S56>/Sum2' */
  const real_T Gain1_b;                /* '<S56>/Gain1' */
  const real_T Product6_if;            /* '<S56>/Product6' */
  const real_T Product7_b;             /* '<S56>/Product7' */
  const real_T Sum3_l;                 /* '<S56>/Sum3' */
  const real_T Gain2_h;                /* '<S56>/Gain2' */
  const real_T Product4_pe;            /* '<S56>/Product4' */
  const real_T Product5_mh;            /* '<S56>/Product5' */
  const real_T Product8_et;            /* '<S56>/Product8' */
  const real_T Sum_o;                  /* '<S56>/Sum' */
  const real_T Product_o;              /* '<S57>/Product' */
  const real_T Product1_l2;            /* '<S57>/Product1' */
  const real_T Sum1_hw;                /* '<S57>/Sum1' */
  const real_T Gain_j;                 /* '<S57>/Gain' */
  const real_T Product2_jc;            /* '<S57>/Product2' */
  const real_T Product3_b;             /* '<S57>/Product3' */
  const real_T Sum2_ei;                /* '<S57>/Sum2' */
  const real_T Gain1_c;                /* '<S57>/Gain1' */
  const real_T Product6_md;            /* '<S57>/Product6' */
  const real_T Product7_m1;            /* '<S57>/Product7' */
  const real_T Sum3_p;                 /* '<S57>/Sum3' */
  const real_T Gain2_e;                /* '<S57>/Gain2' */
  const real_T Product4_i;             /* '<S57>/Product4' */
  const real_T Product5_n;             /* '<S57>/Product5' */
  const real_T Product8_lf;            /* '<S57>/Product8' */
  const real_T Sum_er;                 /* '<S57>/Sum' */
  const real_T Product_b;              /* '<S58>/Product' */
  const real_T Product1_jg;            /* '<S58>/Product1' */
  const real_T Sum1_ni;                /* '<S58>/Sum1' */
  const real_T Gain_h;                 /* '<S58>/Gain' */
  const real_T Product2_o;             /* '<S58>/Product2' */
  const real_T Product3_p;             /* '<S58>/Product3' */
  const real_T Sum2_np;                /* '<S58>/Sum2' */
  const real_T Gain1_d3;               /* '<S58>/Gain1' */
  const real_T Product6_ik;            /* '<S58>/Product6' */
  const real_T Product7_pd;            /* '<S58>/Product7' */
  const real_T Sum3_jg;                /* '<S58>/Sum3' */
  const real_T Gain2_eg;               /* '<S58>/Gain2' */
  const real_T Product4_l;             /* '<S58>/Product4' */
  const real_T Product5_cm;            /* '<S58>/Product5' */
  const real_T Product8_e2;            /* '<S58>/Product8' */
  const real_T Sum_g;                  /* '<S58>/Sum' */
  const real_T Product_au;             /* '<S66>/Product' */
  const real_T Product1_ho;            /* '<S66>/Product1' */
  const real_T Product2_db;            /* '<S66>/Product2' */
  const real_T Product3_f4;            /* '<S66>/Product3' */
  const real_T Sum_ou;                 /* '<S66>/Sum' */
  const real_T sqrt_c;                 /* '<S65>/sqrt' */
  const real_T Product_jk;             /* '<S61>/Product' */
  const real_T Product1_lz;            /* '<S61>/Product1' */
  const real_T Product2_ej;            /* '<S61>/Product2' */
  const real_T Product3_kd;            /* '<S61>/Product3' */
  const real_T Product_pn;             /* '<S62>/Product' */
  const real_T Product1_hg;            /* '<S62>/Product1' */
  const real_T Sum1_hp;                /* '<S62>/Sum1' */
  const real_T Gain_ju;                /* '<S62>/Gain' */
  const real_T Product2_lf;            /* '<S62>/Product2' */
  const real_T Product3_ok;            /* '<S62>/Product3' */
  const real_T Sum2_g;                 /* '<S62>/Sum2' */
  const real_T Gain1_bw;               /* '<S62>/Gain1' */
  const real_T Product6_p;             /* '<S62>/Product6' */
  const real_T Product7_fi;            /* '<S62>/Product7' */
  const real_T Sum3_a4;                /* '<S62>/Sum3' */
  const real_T Gain2_g;                /* '<S62>/Gain2' */
  const real_T Product4_pk;            /* '<S62>/Product4' */
  const real_T Product5_cq;            /* '<S62>/Product5' */
  const real_T Product8_i;             /* '<S62>/Product8' */
  const real_T Sum_a;                  /* '<S62>/Sum' */
  const real_T Product_f;              /* '<S63>/Product' */
  const real_T Product1_m;             /* '<S63>/Product1' */
  const real_T Sum1_jr;                /* '<S63>/Sum1' */
  const real_T Gain_f1;                /* '<S63>/Gain' */
  const real_T Product2_mf;            /* '<S63>/Product2' */
  const real_T Product3_hu;            /* '<S63>/Product3' */
  const real_T Sum2_dz;                /* '<S63>/Sum2' */
  const real_T Gain1_nr;               /* '<S63>/Gain1' */
  const real_T Product6_g5;            /* '<S63>/Product6' */
  const real_T Product7_d;             /* '<S63>/Product7' */
  const real_T Sum3_fs;                /* '<S63>/Sum3' */
  const real_T Gain2_o0;               /* '<S63>/Gain2' */
  const real_T Product4_d;             /* '<S63>/Product4' */
  const real_T Product5_k;             /* '<S63>/Product5' */
  const real_T Product8_pt;            /* '<S63>/Product8' */
  const real_T Sum_ia;                 /* '<S63>/Sum' */
  const real_T Product_p4q;            /* '<S64>/Product' */
  const real_T Product1_a;             /* '<S64>/Product1' */
  const real_T Sum1_a5;                /* '<S64>/Sum1' */
  const real_T Gain_kb;                /* '<S64>/Gain' */
  const real_T Product2_p;             /* '<S64>/Product2' */
  const real_T Product3_e;             /* '<S64>/Product3' */
  const real_T Sum2_j;                 /* '<S64>/Sum2' */
  const real_T Gain1_nt;               /* '<S64>/Gain1' */
  const real_T Product6_o;             /* '<S64>/Product6' */
  const real_T Product7_gc;            /* '<S64>/Product7' */
  const real_T Sum3_n2;                /* '<S64>/Sum3' */
  const real_T Gain2_j;                /* '<S64>/Gain2' */
  const real_T Product4_b;             /* '<S64>/Product4' */
  const real_T Product5_d;             /* '<S64>/Product5' */
  const real_T Product8_c;             /* '<S64>/Product8' */
  const real_T Sum_bt;                 /* '<S64>/Sum' */
  const real_T Subtract1_k[3];         /* '<S11>/Subtract1' */
  const real_T Sum2_iw[3];             /* '<S11>/Sum2' */
  const real_T Product6_ok[3];         /* '<S12>/Product6' */
  const real_T RotationAnglestoQuaternio_g[4];
                                    /* '<S12>/Rotation Angles to Quaternions' */
  const real_T Product_k2;             /* '<S77>/Product' */
  const real_T Product1_dq;            /* '<S77>/Product1' */
  const real_T Product2_e5;            /* '<S77>/Product2' */
  const real_T Product3_h5;            /* '<S77>/Product3' */
  const real_T Sum_b3;                 /* '<S77>/Sum' */
  const real_T sqrt_e;                 /* '<S76>/sqrt' */
  const real_T Product_jz;             /* '<S72>/Product' */
  const real_T Product1_e3;            /* '<S72>/Product1' */
  const real_T Product2_hp;            /* '<S72>/Product2' */
  const real_T Product3_ix;            /* '<S72>/Product3' */
  const real_T Product_m;              /* '<S73>/Product' */
  const real_T Product1_ay;            /* '<S73>/Product1' */
  const real_T Sum1_g5;                /* '<S73>/Sum1' */
  const real_T Gain_fg;                /* '<S73>/Gain' */
  const real_T Product2_pv;            /* '<S73>/Product2' */
  const real_T Product3_n;             /* '<S73>/Product3' */
  const real_T Sum2_b;                 /* '<S73>/Sum2' */
  const real_T Gain1_e;                /* '<S73>/Gain1' */
  const real_T Product6_dg;            /* '<S73>/Product6' */
  const real_T Product7_dv;            /* '<S73>/Product7' */
  const real_T Sum3_c;                 /* '<S73>/Sum3' */
  const real_T Gain2_ol;               /* '<S73>/Gain2' */
  const real_T Product4_gu;            /* '<S73>/Product4' */
  const real_T Product5_lb;            /* '<S73>/Product5' */
  const real_T Product8_h;             /* '<S73>/Product8' */
  const real_T Sum_d;                  /* '<S73>/Sum' */
  const real_T Product_el;             /* '<S74>/Product' */
  const real_T Product1_lk;            /* '<S74>/Product1' */
  const real_T Sum1_f;                 /* '<S74>/Sum1' */
  const real_T Gain_p0;                /* '<S74>/Gain' */
  const real_T Product2_br;            /* '<S74>/Product2' */
  const real_T Product3_hx;            /* '<S74>/Product3' */
  const real_T Sum2_a;                 /* '<S74>/Sum2' */
  const real_T Gain1_ns;               /* '<S74>/Gain1' */
  const real_T Product6_hn;            /* '<S74>/Product6' */
  const real_T Product7_ph;            /* '<S74>/Product7' */
  const real_T Sum3_ly;                /* '<S74>/Sum3' */
  const real_T Gain2_bm;               /* '<S74>/Gain2' */
  const real_T Product4_dp;            /* '<S74>/Product4' */
  const real_T Product5_ep;            /* '<S74>/Product5' */
  const real_T Product8_mj;            /* '<S74>/Product8' */
  const real_T Sum_b4;                 /* '<S74>/Sum' */
  const real_T Product_fg;             /* '<S75>/Product' */
  const real_T Product1_f0;            /* '<S75>/Product1' */
  const real_T Sum1_b3;                /* '<S75>/Sum1' */
  const real_T Gain_d3;                /* '<S75>/Gain' */
  const real_T Product2_e4;            /* '<S75>/Product2' */
  const real_T Product3_fe;            /* '<S75>/Product3' */
  const real_T Sum2_om;                /* '<S75>/Sum2' */
  const real_T Gain1_m;                /* '<S75>/Gain1' */
  const real_T Product6_nr;            /* '<S75>/Product6' */
  const real_T Product7_a;             /* '<S75>/Product7' */
  const real_T Sum3_ob;                /* '<S75>/Sum3' */
  const real_T Gain2_ky;               /* '<S75>/Gain2' */
  const real_T Product4_kc;            /* '<S75>/Product4' */
  const real_T Product5_i4;            /* '<S75>/Product5' */
  const real_T Product8_f;             /* '<S75>/Product8' */
  const real_T Sum_ln;                 /* '<S75>/Sum' */
  const real_T Product_my;             /* '<S83>/Product' */
  const real_T Product1_id;            /* '<S83>/Product1' */
  const real_T Product2_l4;            /* '<S83>/Product2' */
  const real_T Product3_k4;            /* '<S83>/Product3' */
  const real_T Sum_fj;                 /* '<S83>/Sum' */
  const real_T sqrt_j;                 /* '<S82>/sqrt' */
  const real_T Product_ez;             /* '<S78>/Product' */
  const real_T Product1_b;             /* '<S78>/Product1' */
  const real_T Product2_f;             /* '<S78>/Product2' */
  const real_T Product3_ec;            /* '<S78>/Product3' */
  const real_T Product_lg;             /* '<S79>/Product' */
  const real_T Product1_bj;            /* '<S79>/Product1' */
  const real_T Sum1_m;                 /* '<S79>/Sum1' */
  const real_T Gain_c;                 /* '<S79>/Gain' */
  const real_T Product2_p5;            /* '<S79>/Product2' */
  const real_T Product3_fd;            /* '<S79>/Product3' */
  const real_T Sum2_g0;                /* '<S79>/Sum2' */
  const real_T Gain1_f;                /* '<S79>/Gain1' */
  const real_T Product6_l0;            /* '<S79>/Product6' */
  const real_T Product7_a2;            /* '<S79>/Product7' */
  const real_T Sum3_dk;                /* '<S79>/Sum3' */
  const real_T Gain2_l;                /* '<S79>/Gain2' */
  const real_T Product4_pp;            /* '<S79>/Product4' */
  const real_T Product5_kd;            /* '<S79>/Product5' */
  const real_T Product8_ik;            /* '<S79>/Product8' */
  const real_T Sum_dx;                 /* '<S79>/Sum' */
  const real_T Product_fc;             /* '<S80>/Product' */
  const real_T Product1_eg;            /* '<S80>/Product1' */
  const real_T Sum1_c;                 /* '<S80>/Sum1' */
  const real_T Gain_ofb;               /* '<S80>/Gain' */
  const real_T Product2_itz;           /* '<S80>/Product2' */
  const real_T Product3_d;             /* '<S80>/Product3' */
  const real_T Sum2_cq;                /* '<S80>/Sum2' */
  const real_T Gain1_h5;               /* '<S80>/Gain1' */
  const real_T Product6_id;            /* '<S80>/Product6' */
  const real_T Product7_fm;            /* '<S80>/Product7' */
  const real_T Sum3_g;                 /* '<S80>/Sum3' */
  const real_T Gain2_jt;               /* '<S80>/Gain2' */
  const real_T Product4_bz;            /* '<S80>/Product4' */
  const real_T Product5_nd;            /* '<S80>/Product5' */
  const real_T Product8_fh;            /* '<S80>/Product8' */
  const real_T Sum_o3;                 /* '<S80>/Sum' */
  const real_T Product_os;             /* '<S81>/Product' */
  const real_T Product1_a2;            /* '<S81>/Product1' */
  const real_T Sum1_jru;               /* '<S81>/Sum1' */
  const real_T Gain_j3;                /* '<S81>/Gain' */
  const real_T Product2_dv;            /* '<S81>/Product2' */
  const real_T Product3_ks;            /* '<S81>/Product3' */
  const real_T Sum2_ay;                /* '<S81>/Sum2' */
  const real_T Gain1_ia;               /* '<S81>/Gain1' */
  const real_T Product6_lv;            /* '<S81>/Product6' */
  const real_T Product7_bx;            /* '<S81>/Product7' */
  const real_T Sum3_jt;                /* '<S81>/Sum3' */
  const real_T Gain2_i;                /* '<S81>/Gain2' */
  const real_T Product4_go;            /* '<S81>/Product4' */
  const real_T Product5_a;             /* '<S81>/Product5' */
  const real_T Product8_kf;            /* '<S81>/Product8' */
  const real_T Sum_j;                  /* '<S81>/Sum' */
  const real_T Subtract1_j[3];         /* '<S12>/Subtract1' */
  const real_T Sum2_ayz[3];            /* '<S12>/Sum2' */
  const real_T UnitConversion;         /* '<S104>/Unit Conversion' */
  const real_T UnitConversion_g;       /* '<S114>/Unit Conversion' */
  const real_T sigma_wg;               /* '<S123>/sigma_wg ' */
  const real_T UnitConversion_e;       /* '<S108>/Unit Conversion' */
  const real_T UnitConversion_k;       /* '<S142>/Unit Conversion' */
  const real_T PreLookUpIndexSearchprobofe;
                        /* '<S122>/PreLook-Up Index Search  (prob of exceed)' */
  const real_T constBlockForifHeightMaxlow;
  const real_T constBlockForifHeightMaxl_b;
  const real_T constBlockForifHeightMaxl_d;
  const real_T constBlockForifHeightMaxl_n;
  const real_T Sqrt[4];                /* '<S115>/Sqrt' */
  const real_T Sqrt1;                  /* '<S115>/Sqrt1' */
  const real_T Divide[4];              /* '<S115>/Divide' */
  const real_T Product_an;             /* '<S149>/Product' */
  const real_T Switch;                 /* '<S149>/Switch' */
  const real_T Product_mh[9];          /* '<S152>/Product' */
  const real_T dIdt[9];                /* '<S152>/Add' */
  const real_T Sum_dd;                 /* '<S190>/Sum' */
  const real_T a2;                     /* '<S202>/a2' */
  const real_T b2;                     /* '<S202>/b2' */
  const real_T c2;                     /* '<S245>/Sum1' */
  const real_T a4;                     /* '<S247>/a4' */
  const real_T b4;                     /* '<S247>/b4' */
  const real_T c4;                     /* '<S247>/Sum9' */
  const real_T c2_l;                   /* '<S248>/Sum1' */
  const real_T Sum_p;                  /* '<S132>/Sum' */
  const real_T Sum_is;                 /* '<S124>/Sum' */
  const real_T sqrt_g;                 /* '<S121>/sqrt' */
  const real_T w4;                     /* '<S116>/w4' */
  const real_T u16;                    /* '<S116>/u^1//6' */
  const uint32_T PreLookUpIndexSearchprobo_j;
                        /* '<S122>/PreLook-Up Index Search  (prob of exceed)' */
  const boolean_T min_relop;           /* '<S185>/min_relop' */
  const boolean_T max_relop;           /* '<S185>/max_relop' */
  const boolean_T conjunction;         /* '<S185>/conjunction' */
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
      uint8_T TID[3];
    } TaskCounters;

    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
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
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S85>/Add' : Unused code path elimination
 * Block '<S85>/Constant' : Unused code path elimination
 * Block '<S85>/Constant1' : Unused code path elimination
 * Block '<S85>/Divide' : Unused code path elimination
 * Block '<S85>/Divide1' : Unused code path elimination
 * Block '<S89>/DynVisc Conversion' : Unused code path elimination
 * Block '<S85>/Gain' : Unused code path elimination
 * Block '<S91>/KineVisc Conversion' : Unused code path elimination
 * Block '<S85>/Power' : Unused code path elimination
 * Block '<S102>/Cast' : Unused code path elimination
 * Block '<S102>/Unit Conversion' : Unused code path elimination
 * Block '<S87>/Scope' : Unused code path elimination
 * Block '<S87>/Scope1' : Unused code path elimination
 * Block '<S87>/Scope2' : Unused code path elimination
 * Block '<S87>/Scope3' : Unused code path elimination
 * Block '<S148>/Element Product' : Unused code path elimination
 * Block '<S148>/Sum' : Unused code path elimination
 * Block '<S145>/Sum' : Unused code path elimination
 * Block '<S150>/Unit Conversion' : Unused code path elimination
 * Block '<S188>/Unit Conversion' : Unused code path elimination
 * Block '<S189>/Unit Conversion' : Unused code path elimination
 * Block '<S88>/Density Conversion' : Eliminated nontunable gain of 1
 * Block '<S90>/Height Conversion' : Eliminated nontunable gain of 1
 * Block '<S93>/Pressure Conversion' : Eliminated nontunable gain of 1
 * Block '<S94>/Speed Conversion' : Eliminated nontunable gain of 1
 * Block '<S95>/Temperature Conversion' : Eliminated nontunable gain of 1
 * Block '<S4>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S102>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S102>/Cast To Double1' : Eliminate redundant data type conversion
 * Block '<S102>/Cast To Double2' : Eliminate redundant data type conversion
 * Block '<S102>/Cast To Double3' : Eliminate redundant data type conversion
 * Block '<S102>/Cast To Double4' : Eliminate redundant data type conversion
 * Block '<S128>/Reshape' : Reshape block reduction
 * Block '<S128>/Reshape1' : Reshape block reduction
 * Block '<S130>/Reshape' : Reshape block reduction
 * Block '<S136>/Reshape' : Reshape block reduction
 * Block '<S136>/Reshape1' : Reshape block reduction
 * Block '<S138>/Reshape' : Reshape block reduction
 * Block '<S103>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S103>/Reshape' : Reshape block reduction
 * Block '<S103>/Reshape1' : Reshape block reduction
 * Block '<S151>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S152>/Reshape' : Reshape block reduction
 * Block '<S185>/maxtype' : Eliminate redundant data type conversion
 * Block '<S185>/mintype' : Eliminate redundant data type conversion
 * Block '<S187>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S173>/Unit Conversion2' : Eliminated nontunable gain of 1
 * Block '<S218>/Reshape' : Reshape block reduction
 * Block '<S225>/Reshape' : Reshape block reduction
 * Block '<S226>/Reshape' : Reshape block reduction
 * Block '<S227>/Reshape' : Reshape block reduction
 * Block '<S227>/Reshape1' : Reshape block reduction
 * Block '<S203>/Gain' : Eliminated nontunable gain of 1
 * Block '<S203>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S87>/Constant1' : Unused code path elimination
 * Block '<S87>/Sum' : Unused code path elimination
 * Block '<S103>/3ft-->inf' : Unused code path elimination
 * Block '<S143>/Unit Conversion' : Unused code path elimination
 * Block '<S144>/Unit Conversion' : Unused code path elimination
 * Block '<S103>/Product' : Unused code path elimination
 * Block '<S103>/Product1' : Unused code path elimination
 * Block '<S103>/SinCos' : Unused code path elimination
 * Block '<S103>/Transform from Inertial to Body axes' : Unused code path elimination
 * Block '<S103>/Wdeg1' : Unused code path elimination
 * Block '<S103>/Wind Direction' : Unused code path elimination
 * Block '<S103>/Wind speed at reference height' : Unused code path elimination
 * Block '<S103>/h//z0' : Unused code path elimination
 * Block '<S103>/ln(h//z0)' : Unused code path elimination
 * Block '<S103>/ln(ref_height//z0)' : Unused code path elimination
 * Block '<S103>/ref_height//z0' : Unused code path elimination
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
 * '<S13>'  : 'autocodePlant/Plant/Aero Model/Body/Cross Product1'
 * '<S14>'  : 'autocodePlant/Plant/Aero Model/Body/Normalize Vector'
 * '<S15>'  : 'autocodePlant/Plant/Aero Model/Body/Radians to Degrees'
 * '<S16>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Cross Product'
 * '<S17>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Cross Product1'
 * '<S18>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation'
 * '<S19>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1'
 * '<S20>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Radians to Degrees'
 * '<S21>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize'
 * '<S22>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V1'
 * '<S23>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V2'
 * '<S24>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V3'
 * '<S25>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S26>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S27>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize'
 * '<S28>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V1'
 * '<S29>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V2'
 * '<S30>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V3'
 * '<S31>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S32>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S33>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Cross Product'
 * '<S34>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Cross Product1'
 * '<S35>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation'
 * '<S36>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1'
 * '<S37>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Radians to Degrees'
 * '<S38>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize'
 * '<S39>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V1'
 * '<S40>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V2'
 * '<S41>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V3'
 * '<S42>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S43>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S44>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize'
 * '<S45>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V1'
 * '<S46>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V2'
 * '<S47>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V3'
 * '<S48>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S49>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S50>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Cross Product'
 * '<S51>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Cross Product1'
 * '<S52>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation'
 * '<S53>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1'
 * '<S54>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Radians to Degrees'
 * '<S55>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize'
 * '<S56>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V1'
 * '<S57>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V2'
 * '<S58>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V3'
 * '<S59>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S60>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S61>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize'
 * '<S62>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V1'
 * '<S63>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V2'
 * '<S64>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V3'
 * '<S65>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S66>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S67>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Cross Product'
 * '<S68>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Cross Product1'
 * '<S69>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation'
 * '<S70>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1'
 * '<S71>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Radians to Degrees'
 * '<S72>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize'
 * '<S73>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V1'
 * '<S74>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V2'
 * '<S75>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V3'
 * '<S76>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S77>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S78>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize'
 * '<S79>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V1'
 * '<S80>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V2'
 * '<S81>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V3'
 * '<S82>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S83>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S84>'  : 'autocodePlant/Plant/Enviroment/Compare To Constant'
 * '<S85>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model'
 * '<S86>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation'
 * '<S87>'  : 'autocodePlant/Plant/Enviroment/windModel'
 * '<S88>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Density Subsystem'
 * '<S89>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/DynVisc Subsystem'
 * '<S90>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Height Subsystem'
 * '<S91>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/KineVisc Subsystem'
 * '<S92>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Modelling'
 * '<S93>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Pressure Subsystem'
 * '<S94>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Speed Subsystem'
 * '<S95>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Temperature Subsystem'
 * '<S96>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize'
 * '<S97>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V1'
 * '<S98>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V2'
 * '<S99>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V3'
 * '<S100>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S101>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S102>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))'
 * '<S103>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model'
 * '<S104>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Angle Conversion'
 * '<S105>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on angular rates'
 * '<S106>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on velocities'
 * '<S107>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Length Conversion'
 * '<S108>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Length Conversion1'
 * '<S109>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/RMS turbulence  intensities'
 * '<S110>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates'
 * '<S111>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities'
 * '<S112>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Turbulence scale lengths'
 * '<S113>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Velocity Conversion'
 * '<S114>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Velocity Conversion2'
 * '<S115>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/White Noise'
 * '<S116>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on angular rates/Hpgw'
 * '<S117>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on angular rates/Hqgw'
 * '<S118>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on angular rates/Hrgw'
 * '<S119>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on velocities/Hugw(s)'
 * '<S120>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on velocities/Hvgw(s)'
 * '<S121>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on velocities/Hwgw(s)'
 * '<S122>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/RMS turbulence  intensities/High Altitude Intensity'
 * '<S123>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/RMS turbulence  intensities/Low Altitude Intensity'
 * '<S124>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Interpolate  rates'
 * '<S125>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Low altitude  rates'
 * '<S126>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Medium//High  altitude rates'
 * '<S127>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Merge Subsystems'
 * '<S128>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Interpolate  rates/wind to body transformation'
 * '<S129>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Interpolate  rates/wind to body transformation/convert to earth coords'
 * '<S130>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Low altitude  rates/wind to body transformation'
 * '<S131>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Low altitude  rates/wind to body transformation/convert to earth coords'
 * '<S132>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Interpolate  velocities'
 * '<S133>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Low altitude  velocities'
 * '<S134>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Medium//High  altitude velocities'
 * '<S135>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Merge Subsystems'
 * '<S136>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Interpolate  velocities/wind to body transformation'
 * '<S137>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Interpolate  velocities/wind to body transformation/convert to earth coords'
 * '<S138>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Low altitude  velocities/wind to body transformation'
 * '<S139>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Low altitude  velocities/wind to body transformation/convert to earth coords'
 * '<S140>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Turbulence scale lengths/Low altitude scale length'
 * '<S141>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Turbulence scale lengths/Medium//High altitude scale length'
 * '<S142>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Turbulence scale lengths/Medium//High altitude scale length/Length Conversion'
 * '<S143>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model/Angle Conversion'
 * '<S144>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model/Length Conversion'
 * '<S145>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration'
 * '<S146>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration'
 * '<S147>' : 'autocodePlant/Plant/Equatons of Motion/Rail Model'
 * '<S148>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Cross Product'
 * '<S149>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Total Force'
 * '<S150>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Velocity Conversion'
 * '<S151>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Velocity Conversion1'
 * '<S152>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration/Compute dIdt'
 * '<S153>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration/Cross Product'
 * '<S154>' : 'autocodePlant/Plant/Motor Model/clock'
 * '<S155>' : 'autocodePlant/Sensor Plant/Accelerometer'
 * '<S156>' : 'autocodePlant/Sensor Plant/Barometer'
 * '<S157>' : 'autocodePlant/Sensor Plant/Gyroscope'
 * '<S158>' : 'autocodePlant/Sensor Plant/Magnetometer'
 * '<S159>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation'
 * '<S160>' : 'autocodePlant/Sensor Plant/Accelerometer/w(t)'
 * '<S161>' : 'autocodePlant/Sensor Plant/Accelerometer/w2(t)'
 * '<S162>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize'
 * '<S163>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V1'
 * '<S164>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V2'
 * '<S165>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V3'
 * '<S166>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S167>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S168>' : 'autocodePlant/Sensor Plant/Barometer/w(t)'
 * '<S169>' : 'autocodePlant/Sensor Plant/Barometer/white-noise'
 * '<S170>' : 'autocodePlant/Sensor Plant/Gyroscope/w(t)'
 * '<S171>' : 'autocodePlant/Sensor Plant/Gyroscope/w2(t)'
 * '<S172>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation'
 * '<S173>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model'
 * '<S174>' : 'autocodePlant/Sensor Plant/Magnetometer/white-noise'
 * '<S175>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize'
 * '<S176>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V1'
 * '<S177>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V2'
 * '<S178>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V3'
 * '<S179>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S180>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S181>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Altitude'
 * '<S182>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Latitude'
 * '<S183>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Longitude'
 * '<S184>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Compute x,y,z, and h components of magnetic field'
 * '<S185>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Is time within model limits'
 * '<S186>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap'
 * '<S187>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Length Conversion'
 * '<S188>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/MagField Conversion'
 * '<S189>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/MagField Conversion1'
 * '<S190>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag'
 * '<S191>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Compute x,y,z, and h components of magnetic field/Angle Conversion'
 * '<S192>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90'
 * '<S193>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Wrap Longitude'
 * '<S194>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Compare To Constant'
 * '<S195>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero'
 * '<S196>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Wrap Angle 180'
 * '<S197>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero/If Action Subsystem'
 * '<S198>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero/If Action Subsystem1'
 * '<S199>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
 * '<S200>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Wrap Longitude/Compare To Constant'
 * '<S201>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates'
 * '<S202>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates'
 * '<S203>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates '
 * '<S204>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Get Cosine and Sine  of Latitude and Longitude'
 * '<S205>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has altitude or latitude changed'
 * '<S206>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has longitude changed '
 * '<S207>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has time changed'
 * '<S208>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity'
 * '<S209>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem'
 * '<S210>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion'
 * '<S211>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations'
 * '<S212>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients'
 * '<S213>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole'
 * '<S214>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate  index'
 * '<S215>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values'
 * '<S216>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/special case'
 * '<S217>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem1'
 * '<S218>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2'
 * '<S219>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2/calculate  indices'
 * '<S220>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2/calculate  row and column'
 * '<S221>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem'
 * '<S222>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1'
 * '<S223>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1/m,n'
 * '<S224>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1/n,m-1'
 * '<S225>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem'
 * '<S226>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1'
 * '<S227>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2'
 * '<S228>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/calculate  index'
 * '<S229>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem/calculate  index'
 * '<S230>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem/calculate  row and column'
 * '<S231>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1/calculate  index'
 * '<S232>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1/calculate  row and column'
 * '<S233>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  indices'
 * '<S234>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  row and column1'
 * '<S235>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  row and column2'
 * '<S236>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/m<n-2'
 * '<S237>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/m<n-2 '
 * '<S238>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/If Action Subsystem'
 * '<S239>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)'
 * '<S240>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)/If Action Subsystem1'
 * '<S241>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)/If Action Subsystem2'
 * '<S242>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate ca'
 * '<S243>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate ct'
 * '<S244>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate d'
 * '<S245>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate q'
 * '<S246>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate q2'
 * '<S247>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate r2'
 * '<S248>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate sa'
 * '<S249>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate st'
 * '<S250>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates /For Iterator Subsystem'
 * '<S251>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Get Cosine and Sine  of Latitude and Longitude/Angle Conversion2'
 * '<S252>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate bx'
 * '<S253>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate by'
 * '<S254>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate bz'
 * '<S255>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity'
 * '<S256>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity/Angle Conversion'
 * '<S257>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity/Angle Conversion1'
 */
#endif                                 /* autocodePlant_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
