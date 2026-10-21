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
 * C/C++ source code generated on : Wed Oct 14 21:16:03 2026
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
  real_T biasnoise[3];                 /* '<S154>/bias + noise' */
  real_T Delay;                        /* '<S6>/Delay' */
  real_T Sum[3];                       /* '<S146>/Sum' */
  real_T fBdy_mps2[3];                 /* '<S154>/fBdy_mps2' */
  real_T Output[3];                    /* '<S173>/Output' */
  real_T Switch;                       /* '<S192>/Switch' */
  real_T Merge;                        /* '<S194>/Merge' */
  real_T Switch_l;                     /* '<S191>/Switch' */
  real_T olat;                         /* '<S204>/olat' */
  real_T Gain;                         /* '<S172>/Gain' */
  real_T oalt;                         /* '<S204>/oalt' */
  real_T Output_g;                     /* '<S168>/Output' */
  real_T Product[3];                   /* '<S146>/Product' */
  real_T Product_d[4];                 /* '<S114>/Product' */
  real_T Output_o[3];                  /* '<S159>/Output' */
  real_T Output_n;                     /* '<S167>/Output' */
  real_T Output_e[3];                  /* '<S169>/Output' */
  real_T OutportBufferForcp13[13];
  real_T OutportBufferForsp13[13];
  real_T Assignment[11];               /* '<S249>/Assignment' */
  real_T Assignment1[11];              /* '<S249>/Assignment1' */
  real_T sqrt_b;                       /* '<S201>/sqrt' */
  real_T Product11;                    /* '<S241>/Product11' */
  real_T Product12;                    /* '<S247>/Product12' */
  real_T Product4;                     /* '<S242>/Product4' */
  real_T sqrt_k;                       /* '<S248>/sqrt' */
  real_T Sum2;                         /* '<S209>/Sum2' */
  real_T Sum3;                         /* '<S209>/Sum3' */
  real_T Sum1_p;                       /* '<S209>/Sum1' */
  real_T Sum5;                         /* '<S209>/Sum5' */
  real_T Assignment_o[169];            /* '<S211>/Assignment' */
  real_T Sum2_p[169];                  /* '<S211>/Sum2' */
  real_T Assignment2[169];             /* '<S239>/Assignment2' */
  real_T Merge_b;                      /* '<S210>/Merge' */
  real_T Assignment_snorm[169];        /* '<S210>/Assignment_snorm' */
  real_T Merge1_i;                     /* '<S210>/Merge1' */
  real_T Assignment_h[169];            /* '<S210>/Assignment' */
  real_T Product2;                     /* '<S212>/Product2' */
  real_T Assignment2_a[13];            /* '<S217>/Assignment2' */
  real_T Assignment2_m[13];            /* '<S216>/Assignment2' */
  real_T w[2];                         /* '<S120>/w' */
  real_T w_h[2];                       /* '<S120>/w ' */
  real_T LwgV1[2];                     /* '<S120>/Lwg//V 1' */
  real_T w_c[2];                       /* '<S119>/w' */
  real_T w_j[2];                       /* '<S119>/w ' */
  real_T w1[2];                        /* '<S119>/w 1' */
  real_T w_d[2];                       /* '<S118>/w' */
  real_T w_g[2];                       /* '<S117>/w' */
  real_T w_j5[2];                      /* '<S116>/w' */
  real_T w_p[2];                       /* '<S115>/w' */
} B_autocodePlant_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTransferFcn_states;   /* '<S156>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_states;  /* '<S156>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn2_states;  /* '<S156>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn2_states_k;/* '<S154>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn1_states_a;/* '<S154>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn3_states;  /* '<S154>/Discrete Transfer Fcn3' */
  real_T Delay_DSTATE[500];            /* '<S6>/Delay' */
  real_T UnitDelay_DSTATE[3];          /* '<S156>/Unit Delay' */
  real_T DiscreteTransferFcn2_states_h;/* '<S155>/Discrete Transfer Fcn2' */
  real_T UnitDelay_DSTATE_i;           /* '<S153>/Unit Delay' */
  real_T UnitDelay1_DSTATE[2];         /* '<S249>/Unit Delay1' */
  real_T UnitDelay2_DSTATE[4];         /* '<S200>/Unit Delay2' */
  real_T UnitDelay_DSTATE_e[169];      /* '<S211>/Unit Delay' */
  real_T UnitDelay_DSTATE_k[169];      /* '<S238>/Unit Delay' */
  real_T UnitDelay_DSTATE_o[169];      /* '<S210>/Unit Delay' */
  real_T UnitDelay1_DSTATE_c[169];     /* '<S210>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_b[13];      /* '<S212>/Unit Delay1' */
  real_T NextOutput;                   /* '<S160>/White Noise' */
  real_T NextOutput_i;                 /* '<S170>/White Noise' */
  real_T NextOutput_b;                 /* '<S173>/White Noise' */
  real_T otime_PreviousInput;          /* '<S206>/otime' */
  real_T olon_PreviousInput;           /* '<S205>/olon' */
  real_T olat_PreviousInput;           /* '<S204>/olat' */
  real_T oalt_PreviousInput;           /* '<S204>/oalt' */
  real_T NextOutput_e;                 /* '<S168>/White Noise' */
  real_T NextOutput_d[4];              /* '<S114>/White Noise' */
  real_T NextOutput_k;                 /* '<S159>/White Noise' */
  real_T NextOutput_m;                 /* '<S167>/White Noise' */
  real_T NextOutput_a;                 /* '<S169>/White Noise' */
  uint32_T PreLookUpIndexSearchprobofexcee;
                        /* '<S121>/PreLook-Up Index Search  (prob of exceed)' */
  uint32_T RandSeed;                   /* '<S160>/White Noise' */
  uint32_T RandSeed_l;                 /* '<S170>/White Noise' */
  uint32_T RandSeed_a;                 /* '<S173>/White Noise' */
  uint32_T RandSeed_b;                 /* '<S168>/White Noise' */
  uint32_T PreLookUpIndexSearchaltitude_DW;
                              /* '<S121>/PreLook-Up Index Search  (altitude)' */
  uint32_T RandSeed_i[4];              /* '<S114>/White Noise' */
  uint32_T RandSeed_p;                 /* '<S159>/White Noise' */
  uint32_T RandSeed_pb;                /* '<S167>/White Noise' */
  uint32_T RandSeed_pa;                /* '<S169>/White Noise' */
  int8_T If_ActiveSubsystem;           /* '<S194>/If' */
  int8_T ifHeightMaxlowaltitudeelseifHei;
  /* '<S109>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  int8_T ifHeightMaxlowaltitudeelseifH_f;
  /* '<S110>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  boolean_T Convertfromgeodetictosphericalc;
                 /* '<S189>/Convert from geodetic to  spherical coordinates ' */
  boolean_T Convertfromgeodetictospherica_p;
                  /* '<S189>/Convert from geodetic to  spherical coordinates' */
  boolean_T SpecialcaseNorthSouthGeographic;
                      /* '<S209>/Special case - North//South Geographic Pole' */
  boolean_T Hwgws_MODE;                /* '<S105>/Hwgw(s)' */
  boolean_T Hvgws_MODE;                /* '<S105>/Hvgw(s)' */
  boolean_T Hugws_MODE;                /* '<S105>/Hugw(s)' */
  boolean_T Hrgw_MODE;                 /* '<S104>/Hrgw' */
  boolean_T Hqgw_MODE;                 /* '<S104>/Hqgw' */
  boolean_T Hpgw_MODE;                 /* '<S104>/Hpgw' */
} DW_autocodePlant_T;

/* Continuous states (default storage) */
typedef struct {
  real_T uDOFQuaternion_CSTATE[13];    /* '<S5>/6DOF (Quaternion)' */
  real_T wg_p1_CSTATE[2];              /* '<S120>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S120>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S119>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S119>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S118>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S117>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S116>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S115>/pgw_p' */
} X_autocodePlant_T;

/* State derivatives (default storage) */
typedef struct {
  real_T uDOFQuaternion_CSTATE[13];    /* '<S5>/6DOF (Quaternion)' */
  real_T wg_p1_CSTATE[2];              /* '<S120>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S120>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S119>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S119>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S118>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S117>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S116>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S115>/pgw_p' */
} XDot_autocodePlant_T;

/* State disabled  */
typedef struct {
  boolean_T uDOFQuaternion_CSTATE[13]; /* '<S5>/6DOF (Quaternion)' */
  boolean_T wg_p1_CSTATE[2];           /* '<S120>/wg_p1' */
  boolean_T wg_p2_CSTATE[2];           /* '<S120>/wg_p2' */
  boolean_T vg_p1_CSTATE[2];           /* '<S119>/vg_p1' */
  boolean_T vgw_p2_CSTATE[2];          /* '<S119>/vgw_p2' */
  boolean_T ug_p_CSTATE[2];            /* '<S118>/ug_p' */
  boolean_T rgw_p_CSTATE[2];           /* '<S117>/rgw_p' */
  boolean_T qgw_p_CSTATE[2];           /* '<S116>/qgw_p' */
  boolean_T pgw_p_CSTATE[2];           /* '<S115>/pgw_p' */
} XDis_autocodePlant_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Product6[3];            /* '<S8>/Product6' */
  const real_T RotationAnglestoQuaternions[4];
                                     /* '<S8>/Rotation Angles to Quaternions' */
  const real_T Product;                /* '<S25>/Product' */
  const real_T Product1;               /* '<S25>/Product1' */
  const real_T Product2;               /* '<S25>/Product2' */
  const real_T Product3;               /* '<S25>/Product3' */
  const real_T Sum;                    /* '<S25>/Sum' */
  const real_T sqrt_b;                 /* '<S24>/sqrt' */
  const real_T Product_p;              /* '<S20>/Product' */
  const real_T Product1_j;             /* '<S20>/Product1' */
  const real_T Product2_h;             /* '<S20>/Product2' */
  const real_T Product3_a;             /* '<S20>/Product3' */
  const real_T Product_n;              /* '<S21>/Product' */
  const real_T Product1_k;             /* '<S21>/Product1' */
  const real_T Sum1;                   /* '<S21>/Sum1' */
  const real_T Gain;                   /* '<S21>/Gain' */
  const real_T Product2_b;             /* '<S21>/Product2' */
  const real_T Product3_k;             /* '<S21>/Product3' */
  const real_T Sum2;                   /* '<S21>/Sum2' */
  const real_T Gain1;                  /* '<S21>/Gain1' */
  const real_T Product6_n;             /* '<S21>/Product6' */
  const real_T Product7;               /* '<S21>/Product7' */
  const real_T Sum3;                   /* '<S21>/Sum3' */
  const real_T Gain2;                  /* '<S21>/Gain2' */
  const real_T Product4;               /* '<S21>/Product4' */
  const real_T Product5;               /* '<S21>/Product5' */
  const real_T Product8;               /* '<S21>/Product8' */
  const real_T Sum_f;                  /* '<S21>/Sum' */
  const real_T Product_e;              /* '<S22>/Product' */
  const real_T Product1_n;             /* '<S22>/Product1' */
  const real_T Sum1_l;                 /* '<S22>/Sum1' */
  const real_T Gain_i;                 /* '<S22>/Gain' */
  const real_T Product2_g;             /* '<S22>/Product2' */
  const real_T Product3_h;             /* '<S22>/Product3' */
  const real_T Sum2_e;                 /* '<S22>/Sum2' */
  const real_T Gain1_j;                /* '<S22>/Gain1' */
  const real_T Product6_g;             /* '<S22>/Product6' */
  const real_T Product7_f;             /* '<S22>/Product7' */
  const real_T Sum3_o;                 /* '<S22>/Sum3' */
  const real_T Gain2_p;                /* '<S22>/Gain2' */
  const real_T Product4_n;             /* '<S22>/Product4' */
  const real_T Product5_m;             /* '<S22>/Product5' */
  const real_T Product8_k;             /* '<S22>/Product8' */
  const real_T Sum_i;                  /* '<S22>/Sum' */
  const real_T Product_c;              /* '<S23>/Product' */
  const real_T Product1_h;             /* '<S23>/Product1' */
  const real_T Sum1_g;                 /* '<S23>/Sum1' */
  const real_T Gain_b;                 /* '<S23>/Gain' */
  const real_T Product2_l;             /* '<S23>/Product2' */
  const real_T Product3_kq;            /* '<S23>/Product3' */
  const real_T Sum2_m;                 /* '<S23>/Sum2' */
  const real_T Gain1_n;                /* '<S23>/Gain1' */
  const real_T Product6_l;             /* '<S23>/Product6' */
  const real_T Product7_g;             /* '<S23>/Product7' */
  const real_T Sum3_d;                 /* '<S23>/Sum3' */
  const real_T Gain2_b;                /* '<S23>/Gain2' */
  const real_T Product4_j;             /* '<S23>/Product4' */
  const real_T Product5_c;             /* '<S23>/Product5' */
  const real_T Product8_a;             /* '<S23>/Product8' */
  const real_T Sum_e;                  /* '<S23>/Sum' */
  const real_T Product_j;              /* '<S31>/Product' */
  const real_T Product1_i;             /* '<S31>/Product1' */
  const real_T Product2_m;             /* '<S31>/Product2' */
  const real_T Product3_m;             /* '<S31>/Product3' */
  const real_T Sum_i4;                 /* '<S31>/Sum' */
  const real_T sqrt_k;                 /* '<S30>/sqrt' */
  const real_T Product_eo;             /* '<S26>/Product' */
  const real_T Product1_iu;            /* '<S26>/Product1' */
  const real_T Product2_a;             /* '<S26>/Product2' */
  const real_T Product3_f;             /* '<S26>/Product3' */
  const real_T Product_a;              /* '<S27>/Product' */
  const real_T Product1_e;             /* '<S27>/Product1' */
  const real_T Sum1_p;                 /* '<S27>/Sum1' */
  const real_T Gain_p;                 /* '<S27>/Gain' */
  const real_T Product2_i;             /* '<S27>/Product2' */
  const real_T Product3_kx;            /* '<S27>/Product3' */
  const real_T Sum2_d;                 /* '<S27>/Sum2' */
  const real_T Gain1_o;                /* '<S27>/Gain1' */
  const real_T Product6_c;             /* '<S27>/Product6' */
  const real_T Product7_f5;            /* '<S27>/Product7' */
  const real_T Sum3_b;                 /* '<S27>/Sum3' */
  const real_T Gain2_po;               /* '<S27>/Gain2' */
  const real_T Product4_e;             /* '<S27>/Product4' */
  const real_T Product5_b;             /* '<S27>/Product5' */
  const real_T Product8_m;             /* '<S27>/Product8' */
  const real_T Sum_b;                  /* '<S27>/Sum' */
  const real_T Product_nc;             /* '<S28>/Product' */
  const real_T Product1_ne;            /* '<S28>/Product1' */
  const real_T Sum1_pw;                /* '<S28>/Sum1' */
  const real_T Gain_ip;                /* '<S28>/Gain' */
  const real_T Product2_j;             /* '<S28>/Product2' */
  const real_T Product3_mj;            /* '<S28>/Product3' */
  const real_T Sum2_p;                 /* '<S28>/Sum2' */
  const real_T Gain1_d;                /* '<S28>/Gain1' */
  const real_T Product6_f;             /* '<S28>/Product6' */
  const real_T Product7_p;             /* '<S28>/Product7' */
  const real_T Sum3_j;                 /* '<S28>/Sum3' */
  const real_T Gain2_k;                /* '<S28>/Gain2' */
  const real_T Product4_p;             /* '<S28>/Product4' */
  const real_T Product5_i;             /* '<S28>/Product5' */
  const real_T Product8_a4;            /* '<S28>/Product8' */
  const real_T Sum_l;                  /* '<S28>/Sum' */
  const real_T Product_l;              /* '<S29>/Product' */
  const real_T Product1_f;             /* '<S29>/Product1' */
  const real_T Sum1_b;                 /* '<S29>/Sum1' */
  const real_T Gain_f;                 /* '<S29>/Gain' */
  const real_T Product2_gv;            /* '<S29>/Product2' */
  const real_T Product3_fg;            /* '<S29>/Product3' */
  const real_T Sum2_k;                 /* '<S29>/Sum2' */
  const real_T Gain1_np;               /* '<S29>/Gain1' */
  const real_T Product6_fr;            /* '<S29>/Product6' */
  const real_T Product7_fy;            /* '<S29>/Product7' */
  const real_T Sum3_i;                 /* '<S29>/Sum3' */
  const real_T Gain2_o;                /* '<S29>/Gain2' */
  const real_T Product4_e2;            /* '<S29>/Product4' */
  const real_T Product5_b0;            /* '<S29>/Product5' */
  const real_T Product8_a3;            /* '<S29>/Product8' */
  const real_T Sum_c;                  /* '<S29>/Sum' */
  const real_T Subtract1[3];           /* '<S8>/Subtract1' */
  const real_T Sum2_i[3];              /* '<S8>/Sum2' */
  const real_T Product6_m[3];          /* '<S9>/Product6' */
  const real_T RotationAnglestoQuaternio_p[4];
                                     /* '<S9>/Rotation Angles to Quaternions' */
  const real_T Product_ji;             /* '<S42>/Product' */
  const real_T Product1_es;            /* '<S42>/Product1' */
  const real_T Product2_in;            /* '<S42>/Product2' */
  const real_T Product3_i;             /* '<S42>/Product3' */
  const real_T Sum_iy;                 /* '<S42>/Sum' */
  const real_T sqrt_i;                 /* '<S41>/sqrt' */
  const real_T Product_g;              /* '<S37>/Product' */
  const real_T Product1_d;             /* '<S37>/Product1' */
  const real_T Product2_my;            /* '<S37>/Product2' */
  const real_T Product3_ac;            /* '<S37>/Product3' */
  const real_T Product_k;              /* '<S38>/Product' */
  const real_T Product1_h3;            /* '<S38>/Product1' */
  const real_T Sum1_by;                /* '<S38>/Sum1' */
  const real_T Gain_d;                 /* '<S38>/Gain' */
  const real_T Product2_it;            /* '<S38>/Product2' */
  const real_T Product3_as;            /* '<S38>/Product3' */
  const real_T Sum2_c;                 /* '<S38>/Sum2' */
  const real_T Gain1_n0;               /* '<S38>/Gain1' */
  const real_T Product6_a;             /* '<S38>/Product6' */
  const real_T Product7_fk;            /* '<S38>/Product7' */
  const real_T Sum3_f;                 /* '<S38>/Sum3' */
  const real_T Gain2_a;                /* '<S38>/Gain2' */
  const real_T Product4_g;             /* '<S38>/Product4' */
  const real_T Product5_mk;            /* '<S38>/Product5' */
  const real_T Product8_e;             /* '<S38>/Product8' */
  const real_T Sum_m;                  /* '<S38>/Sum' */
  const real_T Product_kq;             /* '<S39>/Product' */
  const real_T Product1_c;             /* '<S39>/Product1' */
  const real_T Sum1_li;                /* '<S39>/Sum1' */
  const real_T Gain_e;                 /* '<S39>/Gain' */
  const real_T Product2_d;             /* '<S39>/Product2' */
  const real_T Product3_g;             /* '<S39>/Product3' */
  const real_T Sum2_n;                 /* '<S39>/Sum2' */
  const real_T Gain1_npp;              /* '<S39>/Gain1' */
  const real_T Product6_h;             /* '<S39>/Product6' */
  const real_T Product7_gx;            /* '<S39>/Product7' */
  const real_T Sum3_be;                /* '<S39>/Sum3' */
  const real_T Gain2_c;                /* '<S39>/Gain2' */
  const real_T Product4_f;             /* '<S39>/Product4' */
  const real_T Product5_l;             /* '<S39>/Product5' */
  const real_T Product8_m4;            /* '<S39>/Product8' */
  const real_T Sum_b1;                 /* '<S39>/Sum' */
  const real_T Product_ac;             /* '<S40>/Product' */
  const real_T Product1_hd;            /* '<S40>/Product1' */
  const real_T Sum1_n;                 /* '<S40>/Sum1' */
  const real_T Gain_a;                 /* '<S40>/Gain' */
  const real_T Product2_lr;            /* '<S40>/Product2' */
  const real_T Product3_hc;            /* '<S40>/Product3' */
  const real_T Sum2_pw;                /* '<S40>/Sum2' */
  const real_T Gain1_p;                /* '<S40>/Gain1' */
  const real_T Product6_d;             /* '<S40>/Product6' */
  const real_T Product7_h;             /* '<S40>/Product7' */
  const real_T Sum3_n;                 /* '<S40>/Sum3' */
  const real_T Gain2_ps;               /* '<S40>/Gain2' */
  const real_T Product4_k;             /* '<S40>/Product4' */
  const real_T Product5_e;             /* '<S40>/Product5' */
  const real_T Product8_m5;            /* '<S40>/Product8' */
  const real_T Sum_k;                  /* '<S40>/Sum' */
  const real_T Product_h;              /* '<S48>/Product' */
  const real_T Product1_cm;            /* '<S48>/Product1' */
  const real_T Product2_n;             /* '<S48>/Product2' */
  const real_T Product3_gd;            /* '<S48>/Product3' */
  const real_T Sum_h;                  /* '<S48>/Sum' */
  const real_T sqrt_l;                 /* '<S47>/sqrt' */
  const real_T Product_i;              /* '<S43>/Product' */
  const real_T Product1_l;             /* '<S43>/Product1' */
  const real_T Product2_gk;            /* '<S43>/Product2' */
  const real_T Product3_o;             /* '<S43>/Product3' */
  const real_T Product_ga;             /* '<S44>/Product' */
  const real_T Product1_p;             /* '<S44>/Product1' */
  const real_T Sum1_a;                 /* '<S44>/Sum1' */
  const real_T Gain_k;                 /* '<S44>/Gain' */
  const real_T Product2_e;             /* '<S44>/Product2' */
  const real_T Product3_j;             /* '<S44>/Product3' */
  const real_T Sum2_o;                 /* '<S44>/Sum2' */
  const real_T Gain1_k;                /* '<S44>/Gain1' */
  const real_T Product6_gg;            /* '<S44>/Product6' */
  const real_T Product7_n;             /* '<S44>/Product7' */
  const real_T Sum3_b0;                /* '<S44>/Sum3' */
  const real_T Gain2_cm;               /* '<S44>/Gain2' */
  const real_T Product4_gs;            /* '<S44>/Product4' */
  const real_T Product5_lz;            /* '<S44>/Product5' */
  const real_T Product8_g;             /* '<S44>/Product8' */
  const real_T Sum_k3;                 /* '<S44>/Sum' */
  const real_T Product_gu;             /* '<S45>/Product' */
  const real_T Product1_g;             /* '<S45>/Product1' */
  const real_T Sum1_j;                 /* '<S45>/Sum1' */
  const real_T Gain_o;                 /* '<S45>/Gain' */
  const real_T Product2_b3;            /* '<S45>/Product2' */
  const real_T Product3_af;            /* '<S45>/Product3' */
  const real_T Sum2_kc;                /* '<S45>/Sum2' */
  const real_T Gain1_h;                /* '<S45>/Gain1' */
  const real_T Product6_i;             /* '<S45>/Product6' */
  const real_T Product7_h0;            /* '<S45>/Product7' */
  const real_T Sum3_a;                 /* '<S45>/Sum3' */
  const real_T Gain2_pr;               /* '<S45>/Gain2' */
  const real_T Product4_ks;            /* '<S45>/Product4' */
  const real_T Product5_c3;            /* '<S45>/Product5' */
  const real_T Product8_p;             /* '<S45>/Product8' */
  const real_T Sum_cv;                 /* '<S45>/Sum' */
  const real_T Product_aa;             /* '<S46>/Product' */
  const real_T Product1_o;             /* '<S46>/Product1' */
  const real_T Sum1_h;                 /* '<S46>/Sum1' */
  const real_T Gain_of;                /* '<S46>/Gain' */
  const real_T Product2_dy;            /* '<S46>/Product2' */
  const real_T Product3_ja;            /* '<S46>/Product3' */
  const real_T Sum2_el;                /* '<S46>/Sum2' */
  const real_T Gain1_i;                /* '<S46>/Gain1' */
  const real_T Product6_fm;            /* '<S46>/Product6' */
  const real_T Product7_m;             /* '<S46>/Product7' */
  const real_T Sum3_jk;                /* '<S46>/Sum3' */
  const real_T Gain2_d;                /* '<S46>/Gain2' */
  const real_T Product4_o;             /* '<S46>/Product4' */
  const real_T Product5_h;             /* '<S46>/Product5' */
  const real_T Product8_l;             /* '<S46>/Product8' */
  const real_T Sum_b1v;                /* '<S46>/Sum' */
  const real_T Subtract1_m[3];         /* '<S9>/Subtract1' */
  const real_T Sum2_l[3];              /* '<S9>/Sum2' */
  const real_T Product6_c1[3];         /* '<S10>/Product6' */
  const real_T RotationAnglestoQuaternio_o[4];
                                    /* '<S10>/Rotation Angles to Quaternions' */
  const real_T Product_p4;             /* '<S59>/Product' */
  const real_T Product1_gn;            /* '<S59>/Product1' */
  const real_T Product2_c;             /* '<S59>/Product2' */
  const real_T Product3_it;            /* '<S59>/Product3' */
  const real_T Sum_ed;                 /* '<S59>/Sum' */
  const real_T sqrt_a;                 /* '<S58>/sqrt' */
  const real_T Product_hg;             /* '<S54>/Product' */
  const real_T Product1_cf;            /* '<S54>/Product1' */
  const real_T Product2_m0;            /* '<S54>/Product2' */
  const real_T Product3_m4;            /* '<S54>/Product3' */
  const real_T Product_ea;             /* '<S55>/Product' */
  const real_T Product1_ia;            /* '<S55>/Product1' */
  const real_T Sum1_aa;                /* '<S55>/Sum1' */
  const real_T Gain_eb;                /* '<S55>/Gain' */
  const real_T Product2_n0;            /* '<S55>/Product2' */
  const real_T Product3_or;            /* '<S55>/Product3' */
  const real_T Sum2_kn;                /* '<S55>/Sum2' */
  const real_T Gain1_b;                /* '<S55>/Gain1' */
  const real_T Product6_if;            /* '<S55>/Product6' */
  const real_T Product7_b;             /* '<S55>/Product7' */
  const real_T Sum3_l;                 /* '<S55>/Sum3' */
  const real_T Gain2_h;                /* '<S55>/Gain2' */
  const real_T Product4_pe;            /* '<S55>/Product4' */
  const real_T Product5_mh;            /* '<S55>/Product5' */
  const real_T Product8_et;            /* '<S55>/Product8' */
  const real_T Sum_o;                  /* '<S55>/Sum' */
  const real_T Product_o;              /* '<S56>/Product' */
  const real_T Product1_l2;            /* '<S56>/Product1' */
  const real_T Sum1_hw;                /* '<S56>/Sum1' */
  const real_T Gain_j;                 /* '<S56>/Gain' */
  const real_T Product2_jc;            /* '<S56>/Product2' */
  const real_T Product3_b;             /* '<S56>/Product3' */
  const real_T Sum2_ei;                /* '<S56>/Sum2' */
  const real_T Gain1_c;                /* '<S56>/Gain1' */
  const real_T Product6_md;            /* '<S56>/Product6' */
  const real_T Product7_m1;            /* '<S56>/Product7' */
  const real_T Sum3_p;                 /* '<S56>/Sum3' */
  const real_T Gain2_e;                /* '<S56>/Gain2' */
  const real_T Product4_i;             /* '<S56>/Product4' */
  const real_T Product5_n;             /* '<S56>/Product5' */
  const real_T Product8_lf;            /* '<S56>/Product8' */
  const real_T Sum_er;                 /* '<S56>/Sum' */
  const real_T Product_b;              /* '<S57>/Product' */
  const real_T Product1_jg;            /* '<S57>/Product1' */
  const real_T Sum1_ni;                /* '<S57>/Sum1' */
  const real_T Gain_h;                 /* '<S57>/Gain' */
  const real_T Product2_o;             /* '<S57>/Product2' */
  const real_T Product3_p;             /* '<S57>/Product3' */
  const real_T Sum2_np;                /* '<S57>/Sum2' */
  const real_T Gain1_d3;               /* '<S57>/Gain1' */
  const real_T Product6_ik;            /* '<S57>/Product6' */
  const real_T Product7_pd;            /* '<S57>/Product7' */
  const real_T Sum3_jg;                /* '<S57>/Sum3' */
  const real_T Gain2_eg;               /* '<S57>/Gain2' */
  const real_T Product4_l;             /* '<S57>/Product4' */
  const real_T Product5_cm;            /* '<S57>/Product5' */
  const real_T Product8_e2;            /* '<S57>/Product8' */
  const real_T Sum_g;                  /* '<S57>/Sum' */
  const real_T Product_au;             /* '<S65>/Product' */
  const real_T Product1_ho;            /* '<S65>/Product1' */
  const real_T Product2_db;            /* '<S65>/Product2' */
  const real_T Product3_f4;            /* '<S65>/Product3' */
  const real_T Sum_ou;                 /* '<S65>/Sum' */
  const real_T sqrt_c;                 /* '<S64>/sqrt' */
  const real_T Product_jk;             /* '<S60>/Product' */
  const real_T Product1_lz;            /* '<S60>/Product1' */
  const real_T Product2_ej;            /* '<S60>/Product2' */
  const real_T Product3_kd;            /* '<S60>/Product3' */
  const real_T Product_pn;             /* '<S61>/Product' */
  const real_T Product1_hg;            /* '<S61>/Product1' */
  const real_T Sum1_hp;                /* '<S61>/Sum1' */
  const real_T Gain_ju;                /* '<S61>/Gain' */
  const real_T Product2_lf;            /* '<S61>/Product2' */
  const real_T Product3_ok;            /* '<S61>/Product3' */
  const real_T Sum2_g;                 /* '<S61>/Sum2' */
  const real_T Gain1_bw;               /* '<S61>/Gain1' */
  const real_T Product6_p;             /* '<S61>/Product6' */
  const real_T Product7_fi;            /* '<S61>/Product7' */
  const real_T Sum3_a4;                /* '<S61>/Sum3' */
  const real_T Gain2_g;                /* '<S61>/Gain2' */
  const real_T Product4_pk;            /* '<S61>/Product4' */
  const real_T Product5_cq;            /* '<S61>/Product5' */
  const real_T Product8_i;             /* '<S61>/Product8' */
  const real_T Sum_a;                  /* '<S61>/Sum' */
  const real_T Product_f;              /* '<S62>/Product' */
  const real_T Product1_m;             /* '<S62>/Product1' */
  const real_T Sum1_jr;                /* '<S62>/Sum1' */
  const real_T Gain_f1;                /* '<S62>/Gain' */
  const real_T Product2_mf;            /* '<S62>/Product2' */
  const real_T Product3_hu;            /* '<S62>/Product3' */
  const real_T Sum2_dz;                /* '<S62>/Sum2' */
  const real_T Gain1_nr;               /* '<S62>/Gain1' */
  const real_T Product6_g5;            /* '<S62>/Product6' */
  const real_T Product7_d;             /* '<S62>/Product7' */
  const real_T Sum3_fs;                /* '<S62>/Sum3' */
  const real_T Gain2_o0;               /* '<S62>/Gain2' */
  const real_T Product4_d;             /* '<S62>/Product4' */
  const real_T Product5_k;             /* '<S62>/Product5' */
  const real_T Product8_pt;            /* '<S62>/Product8' */
  const real_T Sum_ia;                 /* '<S62>/Sum' */
  const real_T Product_p4q;            /* '<S63>/Product' */
  const real_T Product1_a;             /* '<S63>/Product1' */
  const real_T Sum1_a5;                /* '<S63>/Sum1' */
  const real_T Gain_kb;                /* '<S63>/Gain' */
  const real_T Product2_p;             /* '<S63>/Product2' */
  const real_T Product3_e;             /* '<S63>/Product3' */
  const real_T Sum2_j;                 /* '<S63>/Sum2' */
  const real_T Gain1_nt;               /* '<S63>/Gain1' */
  const real_T Product6_o;             /* '<S63>/Product6' */
  const real_T Product7_gc;            /* '<S63>/Product7' */
  const real_T Sum3_n2;                /* '<S63>/Sum3' */
  const real_T Gain2_j;                /* '<S63>/Gain2' */
  const real_T Product4_b;             /* '<S63>/Product4' */
  const real_T Product5_d;             /* '<S63>/Product5' */
  const real_T Product8_c;             /* '<S63>/Product8' */
  const real_T Sum_bt;                 /* '<S63>/Sum' */
  const real_T Subtract1_k[3];         /* '<S10>/Subtract1' */
  const real_T Sum2_iw[3];             /* '<S10>/Sum2' */
  const real_T Product6_ok[3];         /* '<S11>/Product6' */
  const real_T RotationAnglestoQuaternio_g[4];
                                    /* '<S11>/Rotation Angles to Quaternions' */
  const real_T Product_k2;             /* '<S76>/Product' */
  const real_T Product1_dq;            /* '<S76>/Product1' */
  const real_T Product2_e5;            /* '<S76>/Product2' */
  const real_T Product3_h5;            /* '<S76>/Product3' */
  const real_T Sum_b3;                 /* '<S76>/Sum' */
  const real_T sqrt_e;                 /* '<S75>/sqrt' */
  const real_T Product_jz;             /* '<S71>/Product' */
  const real_T Product1_e3;            /* '<S71>/Product1' */
  const real_T Product2_hp;            /* '<S71>/Product2' */
  const real_T Product3_ix;            /* '<S71>/Product3' */
  const real_T Product_m;              /* '<S72>/Product' */
  const real_T Product1_ay;            /* '<S72>/Product1' */
  const real_T Sum1_g5;                /* '<S72>/Sum1' */
  const real_T Gain_fg;                /* '<S72>/Gain' */
  const real_T Product2_pv;            /* '<S72>/Product2' */
  const real_T Product3_n;             /* '<S72>/Product3' */
  const real_T Sum2_b;                 /* '<S72>/Sum2' */
  const real_T Gain1_e;                /* '<S72>/Gain1' */
  const real_T Product6_dg;            /* '<S72>/Product6' */
  const real_T Product7_dv;            /* '<S72>/Product7' */
  const real_T Sum3_c;                 /* '<S72>/Sum3' */
  const real_T Gain2_ol;               /* '<S72>/Gain2' */
  const real_T Product4_gu;            /* '<S72>/Product4' */
  const real_T Product5_lb;            /* '<S72>/Product5' */
  const real_T Product8_h;             /* '<S72>/Product8' */
  const real_T Sum_d;                  /* '<S72>/Sum' */
  const real_T Product_el;             /* '<S73>/Product' */
  const real_T Product1_lk;            /* '<S73>/Product1' */
  const real_T Sum1_f;                 /* '<S73>/Sum1' */
  const real_T Gain_p0;                /* '<S73>/Gain' */
  const real_T Product2_br;            /* '<S73>/Product2' */
  const real_T Product3_hx;            /* '<S73>/Product3' */
  const real_T Sum2_a;                 /* '<S73>/Sum2' */
  const real_T Gain1_ns;               /* '<S73>/Gain1' */
  const real_T Product6_hn;            /* '<S73>/Product6' */
  const real_T Product7_ph;            /* '<S73>/Product7' */
  const real_T Sum3_ly;                /* '<S73>/Sum3' */
  const real_T Gain2_bm;               /* '<S73>/Gain2' */
  const real_T Product4_dp;            /* '<S73>/Product4' */
  const real_T Product5_ep;            /* '<S73>/Product5' */
  const real_T Product8_mj;            /* '<S73>/Product8' */
  const real_T Sum_b4;                 /* '<S73>/Sum' */
  const real_T Product_fg;             /* '<S74>/Product' */
  const real_T Product1_f0;            /* '<S74>/Product1' */
  const real_T Sum1_b3;                /* '<S74>/Sum1' */
  const real_T Gain_d3;                /* '<S74>/Gain' */
  const real_T Product2_e4;            /* '<S74>/Product2' */
  const real_T Product3_fe;            /* '<S74>/Product3' */
  const real_T Sum2_om;                /* '<S74>/Sum2' */
  const real_T Gain1_m;                /* '<S74>/Gain1' */
  const real_T Product6_nr;            /* '<S74>/Product6' */
  const real_T Product7_a;             /* '<S74>/Product7' */
  const real_T Sum3_ob;                /* '<S74>/Sum3' */
  const real_T Gain2_ky;               /* '<S74>/Gain2' */
  const real_T Product4_kc;            /* '<S74>/Product4' */
  const real_T Product5_i4;            /* '<S74>/Product5' */
  const real_T Product8_f;             /* '<S74>/Product8' */
  const real_T Sum_ln;                 /* '<S74>/Sum' */
  const real_T Product_my;             /* '<S82>/Product' */
  const real_T Product1_id;            /* '<S82>/Product1' */
  const real_T Product2_l4;            /* '<S82>/Product2' */
  const real_T Product3_k4;            /* '<S82>/Product3' */
  const real_T Sum_fj;                 /* '<S82>/Sum' */
  const real_T sqrt_j;                 /* '<S81>/sqrt' */
  const real_T Product_ez;             /* '<S77>/Product' */
  const real_T Product1_b;             /* '<S77>/Product1' */
  const real_T Product2_f;             /* '<S77>/Product2' */
  const real_T Product3_ec;            /* '<S77>/Product3' */
  const real_T Product_lg;             /* '<S78>/Product' */
  const real_T Product1_bj;            /* '<S78>/Product1' */
  const real_T Sum1_m;                 /* '<S78>/Sum1' */
  const real_T Gain_c;                 /* '<S78>/Gain' */
  const real_T Product2_p5;            /* '<S78>/Product2' */
  const real_T Product3_fd;            /* '<S78>/Product3' */
  const real_T Sum2_g0;                /* '<S78>/Sum2' */
  const real_T Gain1_f;                /* '<S78>/Gain1' */
  const real_T Product6_l0;            /* '<S78>/Product6' */
  const real_T Product7_a2;            /* '<S78>/Product7' */
  const real_T Sum3_dk;                /* '<S78>/Sum3' */
  const real_T Gain2_l;                /* '<S78>/Gain2' */
  const real_T Product4_pp;            /* '<S78>/Product4' */
  const real_T Product5_kd;            /* '<S78>/Product5' */
  const real_T Product8_ik;            /* '<S78>/Product8' */
  const real_T Sum_dx;                 /* '<S78>/Sum' */
  const real_T Product_fc;             /* '<S79>/Product' */
  const real_T Product1_eg;            /* '<S79>/Product1' */
  const real_T Sum1_c;                 /* '<S79>/Sum1' */
  const real_T Gain_ofb;               /* '<S79>/Gain' */
  const real_T Product2_itz;           /* '<S79>/Product2' */
  const real_T Product3_d;             /* '<S79>/Product3' */
  const real_T Sum2_cq;                /* '<S79>/Sum2' */
  const real_T Gain1_h5;               /* '<S79>/Gain1' */
  const real_T Product6_id;            /* '<S79>/Product6' */
  const real_T Product7_fm;            /* '<S79>/Product7' */
  const real_T Sum3_g;                 /* '<S79>/Sum3' */
  const real_T Gain2_jt;               /* '<S79>/Gain2' */
  const real_T Product4_bz;            /* '<S79>/Product4' */
  const real_T Product5_nd;            /* '<S79>/Product5' */
  const real_T Product8_fh;            /* '<S79>/Product8' */
  const real_T Sum_o3;                 /* '<S79>/Sum' */
  const real_T Product_os;             /* '<S80>/Product' */
  const real_T Product1_a2;            /* '<S80>/Product1' */
  const real_T Sum1_jru;               /* '<S80>/Sum1' */
  const real_T Gain_j3;                /* '<S80>/Gain' */
  const real_T Product2_dv;            /* '<S80>/Product2' */
  const real_T Product3_ks;            /* '<S80>/Product3' */
  const real_T Sum2_ay;                /* '<S80>/Sum2' */
  const real_T Gain1_ia;               /* '<S80>/Gain1' */
  const real_T Product6_lv;            /* '<S80>/Product6' */
  const real_T Product7_bx;            /* '<S80>/Product7' */
  const real_T Sum3_jt;                /* '<S80>/Sum3' */
  const real_T Gain2_i;                /* '<S80>/Gain2' */
  const real_T Product4_go;            /* '<S80>/Product4' */
  const real_T Product5_a;             /* '<S80>/Product5' */
  const real_T Product8_kf;            /* '<S80>/Product8' */
  const real_T Sum_j;                  /* '<S80>/Sum' */
  const real_T Subtract1_j[3];         /* '<S11>/Subtract1' */
  const real_T Sum2_ayz[3];            /* '<S11>/Sum2' */
  const real_T UnitConversion;         /* '<S103>/Unit Conversion' */
  const real_T UnitConversion_g;       /* '<S113>/Unit Conversion' */
  const real_T sigma_wg;               /* '<S122>/sigma_wg ' */
  const real_T UnitConversion_e;       /* '<S107>/Unit Conversion' */
  const real_T UnitConversion_k;       /* '<S141>/Unit Conversion' */
  const real_T PreLookUpIndexSearchprobofe;
                        /* '<S121>/PreLook-Up Index Search  (prob of exceed)' */
  const real_T constBlockForifHeightMaxlow;
  const real_T constBlockForifHeightMaxl_b;
  const real_T constBlockForifHeightMaxl_d;
  const real_T constBlockForifHeightMaxl_n;
  const real_T Sqrt[4];                /* '<S114>/Sqrt' */
  const real_T Sqrt1;                  /* '<S114>/Sqrt1' */
  const real_T Divide[4];              /* '<S114>/Divide' */
  const real_T Product_an;             /* '<S148>/Product' */
  const real_T Switch;                 /* '<S148>/Switch' */
  const real_T Product_mh[9];          /* '<S151>/Product' */
  const real_T dIdt[9];                /* '<S151>/Add' */
  const real_T Sum_dd;                 /* '<S189>/Sum' */
  const real_T a2;                     /* '<S201>/a2' */
  const real_T b2;                     /* '<S201>/b2' */
  const real_T c2;                     /* '<S244>/Sum1' */
  const real_T a4;                     /* '<S246>/a4' */
  const real_T b4;                     /* '<S246>/b4' */
  const real_T c4;                     /* '<S246>/Sum9' */
  const real_T c2_l;                   /* '<S247>/Sum1' */
  const real_T Sum_p;                  /* '<S131>/Sum' */
  const real_T Sum_is;                 /* '<S123>/Sum' */
  const real_T sqrt_g;                 /* '<S120>/sqrt' */
  const real_T w4;                     /* '<S115>/w4' */
  const real_T u16;                    /* '<S115>/u^1//6' */
  const uint32_T PreLookUpIndexSearchprobo_j;
                        /* '<S121>/PreLook-Up Index Search  (prob of exceed)' */
  const boolean_T min_relop;           /* '<S184>/min_relop' */
  const boolean_T max_relop;           /* '<S184>/max_relop' */
  const boolean_T conjunction;         /* '<S184>/conjunction' */
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
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S84>/Add' : Unused code path elimination
 * Block '<S84>/Constant' : Unused code path elimination
 * Block '<S84>/Constant1' : Unused code path elimination
 * Block '<S84>/Divide' : Unused code path elimination
 * Block '<S84>/Divide1' : Unused code path elimination
 * Block '<S88>/DynVisc Conversion' : Unused code path elimination
 * Block '<S84>/Gain' : Unused code path elimination
 * Block '<S90>/KineVisc Conversion' : Unused code path elimination
 * Block '<S84>/Power' : Unused code path elimination
 * Block '<S101>/Cast' : Unused code path elimination
 * Block '<S101>/Unit Conversion' : Unused code path elimination
 * Block '<S86>/Scope' : Unused code path elimination
 * Block '<S86>/Scope1' : Unused code path elimination
 * Block '<S86>/Scope2' : Unused code path elimination
 * Block '<S86>/Scope3' : Unused code path elimination
 * Block '<S147>/Element Product' : Unused code path elimination
 * Block '<S147>/Sum' : Unused code path elimination
 * Block '<S144>/Sum' : Unused code path elimination
 * Block '<S149>/Unit Conversion' : Unused code path elimination
 * Block '<S187>/Unit Conversion' : Unused code path elimination
 * Block '<S188>/Unit Conversion' : Unused code path elimination
 * Block '<S87>/Density Conversion' : Eliminated nontunable gain of 1
 * Block '<S89>/Height Conversion' : Eliminated nontunable gain of 1
 * Block '<S92>/Pressure Conversion' : Eliminated nontunable gain of 1
 * Block '<S93>/Speed Conversion' : Eliminated nontunable gain of 1
 * Block '<S94>/Temperature Conversion' : Eliminated nontunable gain of 1
 * Block '<S4>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S101>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S101>/Cast To Double1' : Eliminate redundant data type conversion
 * Block '<S101>/Cast To Double2' : Eliminate redundant data type conversion
 * Block '<S101>/Cast To Double3' : Eliminate redundant data type conversion
 * Block '<S101>/Cast To Double4' : Eliminate redundant data type conversion
 * Block '<S127>/Reshape' : Reshape block reduction
 * Block '<S127>/Reshape1' : Reshape block reduction
 * Block '<S129>/Reshape' : Reshape block reduction
 * Block '<S135>/Reshape' : Reshape block reduction
 * Block '<S135>/Reshape1' : Reshape block reduction
 * Block '<S137>/Reshape' : Reshape block reduction
 * Block '<S102>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S102>/Reshape' : Reshape block reduction
 * Block '<S102>/Reshape1' : Reshape block reduction
 * Block '<S150>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S151>/Reshape' : Reshape block reduction
 * Block '<S184>/maxtype' : Eliminate redundant data type conversion
 * Block '<S184>/mintype' : Eliminate redundant data type conversion
 * Block '<S186>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S172>/Unit Conversion2' : Eliminated nontunable gain of 1
 * Block '<S217>/Reshape' : Reshape block reduction
 * Block '<S224>/Reshape' : Reshape block reduction
 * Block '<S225>/Reshape' : Reshape block reduction
 * Block '<S226>/Reshape' : Reshape block reduction
 * Block '<S226>/Reshape1' : Reshape block reduction
 * Block '<S202>/Gain' : Eliminated nontunable gain of 1
 * Block '<S202>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S86>/Constant1' : Unused code path elimination
 * Block '<S86>/Sum' : Unused code path elimination
 * Block '<S102>/3ft-->inf' : Unused code path elimination
 * Block '<S142>/Unit Conversion' : Unused code path elimination
 * Block '<S143>/Unit Conversion' : Unused code path elimination
 * Block '<S102>/Product' : Unused code path elimination
 * Block '<S102>/Product1' : Unused code path elimination
 * Block '<S102>/SinCos' : Unused code path elimination
 * Block '<S102>/Transform from Inertial to Body axes' : Unused code path elimination
 * Block '<S102>/Wdeg1' : Unused code path elimination
 * Block '<S102>/Wind Direction' : Unused code path elimination
 * Block '<S102>/Wind speed at reference height' : Unused code path elimination
 * Block '<S102>/h//z0' : Unused code path elimination
 * Block '<S102>/ln(h//z0)' : Unused code path elimination
 * Block '<S102>/ln(ref_height//z0)' : Unused code path elimination
 * Block '<S102>/ref_height//z0' : Unused code path elimination
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
 * '<S7>'   : 'autocodePlant/Plant/Aero Model/Body'
 * '<S8>'   : 'autocodePlant/Plant/Aero Model/Fin 1'
 * '<S9>'   : 'autocodePlant/Plant/Aero Model/Fin 2'
 * '<S10>'  : 'autocodePlant/Plant/Aero Model/Fin 3'
 * '<S11>'  : 'autocodePlant/Plant/Aero Model/Fin 4'
 * '<S12>'  : 'autocodePlant/Plant/Aero Model/Body/Cross Product1'
 * '<S13>'  : 'autocodePlant/Plant/Aero Model/Body/Normalize Vector'
 * '<S14>'  : 'autocodePlant/Plant/Aero Model/Body/Radians to Degrees'
 * '<S15>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Cross Product'
 * '<S16>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Cross Product1'
 * '<S17>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation'
 * '<S18>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1'
 * '<S19>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Radians to Degrees'
 * '<S20>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize'
 * '<S21>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V1'
 * '<S22>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V2'
 * '<S23>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/V3'
 * '<S24>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S25>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S26>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize'
 * '<S27>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V1'
 * '<S28>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V2'
 * '<S29>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/V3'
 * '<S30>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S31>'  : 'autocodePlant/Plant/Aero Model/Fin 1/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S32>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Cross Product'
 * '<S33>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Cross Product1'
 * '<S34>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation'
 * '<S35>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1'
 * '<S36>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Radians to Degrees'
 * '<S37>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize'
 * '<S38>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V1'
 * '<S39>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V2'
 * '<S40>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/V3'
 * '<S41>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S42>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S43>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize'
 * '<S44>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V1'
 * '<S45>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V2'
 * '<S46>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/V3'
 * '<S47>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S48>'  : 'autocodePlant/Plant/Aero Model/Fin 2/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S49>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Cross Product'
 * '<S50>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Cross Product1'
 * '<S51>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation'
 * '<S52>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1'
 * '<S53>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Radians to Degrees'
 * '<S54>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize'
 * '<S55>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V1'
 * '<S56>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V2'
 * '<S57>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/V3'
 * '<S58>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S59>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S60>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize'
 * '<S61>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V1'
 * '<S62>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V2'
 * '<S63>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/V3'
 * '<S64>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S65>'  : 'autocodePlant/Plant/Aero Model/Fin 3/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S66>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Cross Product'
 * '<S67>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Cross Product1'
 * '<S68>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation'
 * '<S69>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1'
 * '<S70>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Radians to Degrees'
 * '<S71>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize'
 * '<S72>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V1'
 * '<S73>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V2'
 * '<S74>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/V3'
 * '<S75>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S76>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S77>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize'
 * '<S78>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V1'
 * '<S79>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V2'
 * '<S80>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/V3'
 * '<S81>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus'
 * '<S82>'  : 'autocodePlant/Plant/Aero Model/Fin 4/Quaternion Rotation1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S83>'  : 'autocodePlant/Plant/Enviroment/Compare To Constant'
 * '<S84>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model'
 * '<S85>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation'
 * '<S86>'  : 'autocodePlant/Plant/Enviroment/windModel'
 * '<S87>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Density Subsystem'
 * '<S88>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/DynVisc Subsystem'
 * '<S89>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Height Subsystem'
 * '<S90>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/KineVisc Subsystem'
 * '<S91>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Modelling'
 * '<S92>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Pressure Subsystem'
 * '<S93>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Speed Subsystem'
 * '<S94>'  : 'autocodePlant/Plant/Enviroment/ISA Atmosphere Model/Temperature Subsystem'
 * '<S95>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize'
 * '<S96>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V1'
 * '<S97>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V2'
 * '<S98>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/V3'
 * '<S99>'  : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S100>' : 'autocodePlant/Plant/Enviroment/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S101>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))'
 * '<S102>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model'
 * '<S103>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Angle Conversion'
 * '<S104>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on angular rates'
 * '<S105>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on velocities'
 * '<S106>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Length Conversion'
 * '<S107>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Length Conversion1'
 * '<S108>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/RMS turbulence  intensities'
 * '<S109>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates'
 * '<S110>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities'
 * '<S111>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Turbulence scale lengths'
 * '<S112>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Velocity Conversion'
 * '<S113>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Velocity Conversion2'
 * '<S114>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/White Noise'
 * '<S115>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on angular rates/Hpgw'
 * '<S116>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on angular rates/Hqgw'
 * '<S117>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on angular rates/Hrgw'
 * '<S118>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on velocities/Hugw(s)'
 * '<S119>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on velocities/Hvgw(s)'
 * '<S120>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Filters on velocities/Hwgw(s)'
 * '<S121>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/RMS turbulence  intensities/High Altitude Intensity'
 * '<S122>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/RMS turbulence  intensities/Low Altitude Intensity'
 * '<S123>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Interpolate  rates'
 * '<S124>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Low altitude  rates'
 * '<S125>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Medium//High  altitude rates'
 * '<S126>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Merge Subsystems'
 * '<S127>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Interpolate  rates/wind to body transformation'
 * '<S128>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Interpolate  rates/wind to body transformation/convert to earth coords'
 * '<S129>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Low altitude  rates/wind to body transformation'
 * '<S130>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select angular rates/Low altitude  rates/wind to body transformation/convert to earth coords'
 * '<S131>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Interpolate  velocities'
 * '<S132>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Low altitude  velocities'
 * '<S133>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Medium//High  altitude velocities'
 * '<S134>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Merge Subsystems'
 * '<S135>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Interpolate  velocities/wind to body transformation'
 * '<S136>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Interpolate  velocities/wind to body transformation/convert to earth coords'
 * '<S137>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Low altitude  velocities/wind to body transformation'
 * '<S138>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Select velocities/Low altitude  velocities/wind to body transformation/convert to earth coords'
 * '<S139>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Turbulence scale lengths/Low altitude scale length'
 * '<S140>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Turbulence scale lengths/Medium//High altitude scale length'
 * '<S141>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (+q +r))/Turbulence scale lengths/Medium//High altitude scale length/Length Conversion'
 * '<S142>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model/Angle Conversion'
 * '<S143>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model/Length Conversion'
 * '<S144>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration'
 * '<S145>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration'
 * '<S146>' : 'autocodePlant/Plant/Equatons of Motion/Rail Model'
 * '<S147>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Cross Product'
 * '<S148>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Total Force'
 * '<S149>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Velocity Conversion'
 * '<S150>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Velocity Conversion1'
 * '<S151>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration/Compute dIdt'
 * '<S152>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration/Cross Product'
 * '<S153>' : 'autocodePlant/Plant/Motor Model/clock'
 * '<S154>' : 'autocodePlant/Sensor Plant/Accelerometer'
 * '<S155>' : 'autocodePlant/Sensor Plant/Barometer'
 * '<S156>' : 'autocodePlant/Sensor Plant/Gyroscope'
 * '<S157>' : 'autocodePlant/Sensor Plant/Magnetometer'
 * '<S158>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation'
 * '<S159>' : 'autocodePlant/Sensor Plant/Accelerometer/w(t)'
 * '<S160>' : 'autocodePlant/Sensor Plant/Accelerometer/w2(t)'
 * '<S161>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize'
 * '<S162>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V1'
 * '<S163>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V2'
 * '<S164>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V3'
 * '<S165>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S166>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S167>' : 'autocodePlant/Sensor Plant/Barometer/w(t)'
 * '<S168>' : 'autocodePlant/Sensor Plant/Barometer/white-noise'
 * '<S169>' : 'autocodePlant/Sensor Plant/Gyroscope/w(t)'
 * '<S170>' : 'autocodePlant/Sensor Plant/Gyroscope/w2(t)'
 * '<S171>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation'
 * '<S172>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model'
 * '<S173>' : 'autocodePlant/Sensor Plant/Magnetometer/white-noise'
 * '<S174>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize'
 * '<S175>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V1'
 * '<S176>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V2'
 * '<S177>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V3'
 * '<S178>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S179>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S180>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Altitude'
 * '<S181>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Latitude'
 * '<S182>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Longitude'
 * '<S183>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Compute x,y,z, and h components of magnetic field'
 * '<S184>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Is time within model limits'
 * '<S185>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap'
 * '<S186>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Length Conversion'
 * '<S187>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/MagField Conversion'
 * '<S188>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/MagField Conversion1'
 * '<S189>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag'
 * '<S190>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Compute x,y,z, and h components of magnetic field/Angle Conversion'
 * '<S191>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90'
 * '<S192>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Wrap Longitude'
 * '<S193>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Compare To Constant'
 * '<S194>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero'
 * '<S195>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Wrap Angle 180'
 * '<S196>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero/If Action Subsystem'
 * '<S197>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero/If Action Subsystem1'
 * '<S198>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
 * '<S199>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Wrap Longitude/Compare To Constant'
 * '<S200>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates'
 * '<S201>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates'
 * '<S202>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates '
 * '<S203>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Get Cosine and Sine  of Latitude and Longitude'
 * '<S204>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has altitude or latitude changed'
 * '<S205>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has longitude changed '
 * '<S206>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has time changed'
 * '<S207>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity'
 * '<S208>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem'
 * '<S209>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion'
 * '<S210>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations'
 * '<S211>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients'
 * '<S212>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole'
 * '<S213>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate  index'
 * '<S214>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values'
 * '<S215>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/special case'
 * '<S216>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem1'
 * '<S217>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2'
 * '<S218>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2/calculate  indices'
 * '<S219>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2/calculate  row and column'
 * '<S220>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem'
 * '<S221>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1'
 * '<S222>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1/m,n'
 * '<S223>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1/n,m-1'
 * '<S224>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem'
 * '<S225>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1'
 * '<S226>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2'
 * '<S227>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/calculate  index'
 * '<S228>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem/calculate  index'
 * '<S229>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem/calculate  row and column'
 * '<S230>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1/calculate  index'
 * '<S231>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1/calculate  row and column'
 * '<S232>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  indices'
 * '<S233>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  row and column1'
 * '<S234>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  row and column2'
 * '<S235>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/m<n-2'
 * '<S236>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/m<n-2 '
 * '<S237>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/If Action Subsystem'
 * '<S238>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)'
 * '<S239>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)/If Action Subsystem1'
 * '<S240>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)/If Action Subsystem2'
 * '<S241>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate ca'
 * '<S242>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate ct'
 * '<S243>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate d'
 * '<S244>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate q'
 * '<S245>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate q2'
 * '<S246>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate r2'
 * '<S247>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate sa'
 * '<S248>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate st'
 * '<S249>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates /For Iterator Subsystem'
 * '<S250>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Get Cosine and Sine  of Latitude and Longitude/Angle Conversion2'
 * '<S251>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate bx'
 * '<S252>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate by'
 * '<S253>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate bz'
 * '<S254>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity'
 * '<S255>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity/Angle Conversion'
 * '<S256>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity/Angle Conversion1'
 */
#endif                                 /* autocodePlant_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
