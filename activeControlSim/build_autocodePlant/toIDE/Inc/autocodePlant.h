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
 * C/C++ source code generated on : Thu Oct 29 16:32:54 2026
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
  real_T biasnoise[3];                 /* '<S173>/bias + noise' */
  real_T Delay;                        /* '<S6>/Delay' */
  real_T Product[4];                   /* '<S131>/Product' */
  real_T Backlash[4];                  /* '<S7>/Backlash' */
  real_T Sum[3];                       /* '<S165>/Sum' */
  real_T fBdy_mps2[3];                 /* '<S173>/fBdy_mps2' */
  real_T Output[3];                    /* '<S192>/Output' */
  real_T Switch;                       /* '<S211>/Switch' */
  real_T Merge;                        /* '<S213>/Merge' */
  real_T Switch_l;                     /* '<S210>/Switch' */
  real_T olat;                         /* '<S223>/olat' */
  real_T Gain;                         /* '<S191>/Gain' */
  real_T oalt;                         /* '<S223>/oalt' */
  real_T Output_g;                     /* '<S187>/Output' */
  real_T Product_h[3];                 /* '<S165>/Product' */
  real_T Output_o[3];                  /* '<S178>/Output' */
  real_T Output_n;                     /* '<S186>/Output' */
  real_T Output_e[3];                  /* '<S188>/Output' */
  real_T OutportBufferForcp13[13];
  real_T OutportBufferForsp13[13];
  real_T Assignment[11];               /* '<S268>/Assignment' */
  real_T Assignment1[11];              /* '<S268>/Assignment1' */
  real_T sqrt_b;                       /* '<S220>/sqrt' */
  real_T Product11;                    /* '<S260>/Product11' */
  real_T Product12;                    /* '<S266>/Product12' */
  real_T Product4;                     /* '<S261>/Product4' */
  real_T sqrt_k;                       /* '<S267>/sqrt' */
  real_T Sum2;                         /* '<S228>/Sum2' */
  real_T Sum3;                         /* '<S228>/Sum3' */
  real_T Sum1_p;                       /* '<S228>/Sum1' */
  real_T Sum5;                         /* '<S228>/Sum5' */
  real_T Assignment_o[169];            /* '<S230>/Assignment' */
  real_T Sum2_p[169];                  /* '<S230>/Sum2' */
  real_T Assignment2[169];             /* '<S258>/Assignment2' */
  real_T Merge_b;                      /* '<S229>/Merge' */
  real_T Assignment_snorm[169];        /* '<S229>/Assignment_snorm' */
  real_T Merge1_i;                     /* '<S229>/Merge1' */
  real_T Assignment_h[169];            /* '<S229>/Assignment' */
  real_T Product2;                     /* '<S231>/Product2' */
  real_T Assignment2_a[13];            /* '<S236>/Assignment2' */
  real_T Assignment2_m[13];            /* '<S235>/Assignment2' */
  real_T w[2];                         /* '<S137>/w' */
  real_T w_h[2];                       /* '<S137>/w ' */
  real_T LwgV1[2];                     /* '<S137>/Lwg//V 1' */
  real_T w_c[2];                       /* '<S136>/w' */
  real_T w_j[2];                       /* '<S136>/w ' */
  real_T w1[2];                        /* '<S136>/w 1' */
  real_T w_d[2];                       /* '<S135>/w' */
  real_T w1_c[2];                      /* '<S135>/w1' */
  real_T w_g[2];                       /* '<S134>/w' */
  real_T w_j5[2];                      /* '<S133>/w' */
  real_T UnaryMinus[2];                /* '<S133>/Unary Minus' */
  real_T w_p[2];                       /* '<S132>/w' */
  real_T sigma_w[2];                   /* '<S132>/sigma_w' */
} B_autocodePlant_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTransferFcn_states;   /* '<S175>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn1_states;  /* '<S175>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn2_states;  /* '<S175>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn2_states_k;/* '<S173>/Discrete Transfer Fcn2' */
  real_T DiscreteTransferFcn1_states_a;/* '<S173>/Discrete Transfer Fcn1' */
  real_T DiscreteTransferFcn3_states;  /* '<S173>/Discrete Transfer Fcn3' */
  real_T Delay_DSTATE[2000];           /* '<S6>/Delay' */
  real_T UnitDelay_DSTATE[4];          /* '<S7>/Unit Delay' */
  real_T UnitDelay_DSTATE_c[3];        /* '<S175>/Unit Delay' */
  real_T DiscreteTransferFcn2_states_h;/* '<S174>/Discrete Transfer Fcn2' */
  real_T UnitDelay_DSTATE_i;           /* '<S172>/Unit Delay' */
  real_T UnitDelay1_DSTATE[2];         /* '<S268>/Unit Delay1' */
  real_T UnitDelay2_DSTATE[4];         /* '<S219>/Unit Delay2' */
  real_T UnitDelay_DSTATE_e[169];      /* '<S230>/Unit Delay' */
  real_T UnitDelay_DSTATE_k[169];      /* '<S257>/Unit Delay' */
  real_T UnitDelay_DSTATE_o[169];      /* '<S229>/Unit Delay' */
  real_T UnitDelay1_DSTATE_c[169];     /* '<S229>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_b[13];      /* '<S231>/Unit Delay1' */
  real_T NextOutput;                   /* '<S179>/White Noise' */
  real_T NextOutput_d[4];              /* '<S131>/White Noise' */
  real_T PrevY[4];                     /* '<S7>/Backlash' */
  real_T NextOutput_i;                 /* '<S189>/White Noise' */
  real_T NextOutput_b;                 /* '<S192>/White Noise' */
  real_T otime_PreviousInput;          /* '<S225>/otime' */
  real_T olon_PreviousInput;           /* '<S224>/olon' */
  real_T olat_PreviousInput;           /* '<S223>/olat' */
  real_T oalt_PreviousInput;           /* '<S223>/oalt' */
  real_T NextOutput_e;                 /* '<S187>/White Noise' */
  real_T NextOutput_k;                 /* '<S178>/White Noise' */
  real_T NextOutput_m;                 /* '<S186>/White Noise' */
  real_T NextOutput_a;                 /* '<S188>/White Noise' */
  uint32_T PreLookUpIndexSearchprobofexcee;
                        /* '<S138>/PreLook-Up Index Search  (prob of exceed)' */
  uint32_T RandSeed;                   /* '<S179>/White Noise' */
  uint32_T PreLookUpIndexSearchaltitude_DW;
                              /* '<S138>/PreLook-Up Index Search  (altitude)' */
  uint32_T RandSeed_i[4];              /* '<S131>/White Noise' */
  uint32_T RandSeed_l;                 /* '<S189>/White Noise' */
  uint32_T RandSeed_a;                 /* '<S192>/White Noise' */
  uint32_T RandSeed_b;                 /* '<S187>/White Noise' */
  uint32_T RandSeed_p;                 /* '<S178>/White Noise' */
  uint32_T RandSeed_pb;                /* '<S186>/White Noise' */
  uint32_T RandSeed_pa;                /* '<S188>/White Noise' */
  int8_T ifHeightMaxlowaltitudeelseifHei;
  /* '<S126>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  int8_T ifHeightMaxlowaltitudeelseifH_f;
  /* '<S127>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' */
  int8_T If_ActiveSubsystem;           /* '<S213>/If' */
  boolean_T Convertfromgeodetictosphericalc;
                 /* '<S208>/Convert from geodetic to  spherical coordinates ' */
  boolean_T Convertfromgeodetictospherica_p;
                  /* '<S208>/Convert from geodetic to  spherical coordinates' */
  boolean_T SpecialcaseNorthSouthGeographic;
                      /* '<S228>/Special case - North//South Geographic Pole' */
  boolean_T Hwgws_MODE;                /* '<S122>/Hwgw(s)' */
  boolean_T Hvgws_MODE;                /* '<S122>/Hvgw(s)' */
  boolean_T Hugws_MODE;                /* '<S122>/Hugw(s)' */
  boolean_T Hrgw_MODE;                 /* '<S121>/Hrgw' */
  boolean_T Hqgw_MODE;                 /* '<S121>/Hqgw' */
  boolean_T Hpgw_MODE;                 /* '<S121>/Hpgw' */
} DW_autocodePlant_T;

/* Continuous states (default storage) */
typedef struct {
  real_T uDOFQuaternion_CSTATE[13];    /* '<S5>/6DOF (Quaternion)' */
  real_T wg_p1_CSTATE[2];              /* '<S137>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S137>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S136>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S136>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S135>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S134>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S133>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S132>/pgw_p' */
} X_autocodePlant_T;

/* State derivatives (default storage) */
typedef struct {
  real_T uDOFQuaternion_CSTATE[13];    /* '<S5>/6DOF (Quaternion)' */
  real_T wg_p1_CSTATE[2];              /* '<S137>/wg_p1' */
  real_T wg_p2_CSTATE[2];              /* '<S137>/wg_p2' */
  real_T vg_p1_CSTATE[2];              /* '<S136>/vg_p1' */
  real_T vgw_p2_CSTATE[2];             /* '<S136>/vgw_p2' */
  real_T ug_p_CSTATE[2];               /* '<S135>/ug_p' */
  real_T rgw_p_CSTATE[2];              /* '<S134>/rgw_p' */
  real_T qgw_p_CSTATE[2];              /* '<S133>/qgw_p' */
  real_T pgw_p_CSTATE[2];              /* '<S132>/pgw_p' */
} XDot_autocodePlant_T;

/* State disabled  */
typedef struct {
  boolean_T uDOFQuaternion_CSTATE[13]; /* '<S5>/6DOF (Quaternion)' */
  boolean_T wg_p1_CSTATE[2];           /* '<S137>/wg_p1' */
  boolean_T wg_p2_CSTATE[2];           /* '<S137>/wg_p2' */
  boolean_T vg_p1_CSTATE[2];           /* '<S136>/vg_p1' */
  boolean_T vgw_p2_CSTATE[2];          /* '<S136>/vgw_p2' */
  boolean_T ug_p_CSTATE[2];            /* '<S135>/ug_p' */
  boolean_T rgw_p_CSTATE[2];           /* '<S134>/rgw_p' */
  boolean_T qgw_p_CSTATE[2];           /* '<S133>/qgw_p' */
  boolean_T pgw_p_CSTATE[2];           /* '<S132>/pgw_p' */
} XDis_autocodePlant_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Product6[3];            /* '<S9>/Product6' */
  const real_T RotationAnglestoQuaternions[4];
                                     /* '<S9>/Rotation Angles to Quaternions' */
  const real_T Product;                /* '<S31>/Product' */
  const real_T Product1;               /* '<S31>/Product1' */
  const real_T Product2;               /* '<S31>/Product2' */
  const real_T Product3;               /* '<S31>/Product3' */
  const real_T Sum;                    /* '<S31>/Sum' */
  const real_T sqrt_b;                 /* '<S30>/sqrt' */
  const real_T Product_p;              /* '<S26>/Product' */
  const real_T Product1_j;             /* '<S26>/Product1' */
  const real_T Product2_h;             /* '<S26>/Product2' */
  const real_T Product3_a;             /* '<S26>/Product3' */
  const real_T Product_n;              /* '<S27>/Product' */
  const real_T Product1_k;             /* '<S27>/Product1' */
  const real_T Sum1;                   /* '<S27>/Sum1' */
  const real_T Gain;                   /* '<S27>/Gain' */
  const real_T Product2_b;             /* '<S27>/Product2' */
  const real_T Product3_k;             /* '<S27>/Product3' */
  const real_T Sum2;                   /* '<S27>/Sum2' */
  const real_T Gain1;                  /* '<S27>/Gain1' */
  const real_T Product6_n;             /* '<S27>/Product6' */
  const real_T Product7;               /* '<S27>/Product7' */
  const real_T Sum3;                   /* '<S27>/Sum3' */
  const real_T Gain2;                  /* '<S27>/Gain2' */
  const real_T Product4;               /* '<S27>/Product4' */
  const real_T Product5;               /* '<S27>/Product5' */
  const real_T Product8;               /* '<S27>/Product8' */
  const real_T Sum_f;                  /* '<S27>/Sum' */
  const real_T Product_e;              /* '<S28>/Product' */
  const real_T Product1_n;             /* '<S28>/Product1' */
  const real_T Sum1_l;                 /* '<S28>/Sum1' */
  const real_T Gain_i;                 /* '<S28>/Gain' */
  const real_T Product2_g;             /* '<S28>/Product2' */
  const real_T Product3_h;             /* '<S28>/Product3' */
  const real_T Sum2_e;                 /* '<S28>/Sum2' */
  const real_T Gain1_j;                /* '<S28>/Gain1' */
  const real_T Product6_g;             /* '<S28>/Product6' */
  const real_T Product7_f;             /* '<S28>/Product7' */
  const real_T Sum3_o;                 /* '<S28>/Sum3' */
  const real_T Gain2_p;                /* '<S28>/Gain2' */
  const real_T Product4_n;             /* '<S28>/Product4' */
  const real_T Product5_m;             /* '<S28>/Product5' */
  const real_T Product8_k;             /* '<S28>/Product8' */
  const real_T Sum_i;                  /* '<S28>/Sum' */
  const real_T Product_c;              /* '<S29>/Product' */
  const real_T Product1_h;             /* '<S29>/Product1' */
  const real_T Sum1_g;                 /* '<S29>/Sum1' */
  const real_T Gain_b;                 /* '<S29>/Gain' */
  const real_T Product2_l;             /* '<S29>/Product2' */
  const real_T Product3_kq;            /* '<S29>/Product3' */
  const real_T Sum2_m;                 /* '<S29>/Sum2' */
  const real_T Gain1_n;                /* '<S29>/Gain1' */
  const real_T Product6_l;             /* '<S29>/Product6' */
  const real_T Product7_g;             /* '<S29>/Product7' */
  const real_T Sum3_d;                 /* '<S29>/Sum3' */
  const real_T Gain2_b;                /* '<S29>/Gain2' */
  const real_T Product4_j;             /* '<S29>/Product4' */
  const real_T Product5_c;             /* '<S29>/Product5' */
  const real_T Product8_a;             /* '<S29>/Product8' */
  const real_T Sum_e;                  /* '<S29>/Sum' */
  const real_T Product_j;              /* '<S37>/Product' */
  const real_T Product1_i;             /* '<S37>/Product1' */
  const real_T Product2_m;             /* '<S37>/Product2' */
  const real_T Product3_m;             /* '<S37>/Product3' */
  const real_T Sum_i4;                 /* '<S37>/Sum' */
  const real_T sqrt_k;                 /* '<S36>/sqrt' */
  const real_T Product_eo;             /* '<S32>/Product' */
  const real_T Product1_iu;            /* '<S32>/Product1' */
  const real_T Product2_a;             /* '<S32>/Product2' */
  const real_T Product3_f;             /* '<S32>/Product3' */
  const real_T Product_a;              /* '<S33>/Product' */
  const real_T Product1_e;             /* '<S33>/Product1' */
  const real_T Sum1_p;                 /* '<S33>/Sum1' */
  const real_T Gain_p;                 /* '<S33>/Gain' */
  const real_T Product2_i;             /* '<S33>/Product2' */
  const real_T Product3_kx;            /* '<S33>/Product3' */
  const real_T Sum2_d;                 /* '<S33>/Sum2' */
  const real_T Gain1_o;                /* '<S33>/Gain1' */
  const real_T Product6_c;             /* '<S33>/Product6' */
  const real_T Product7_f5;            /* '<S33>/Product7' */
  const real_T Sum3_b;                 /* '<S33>/Sum3' */
  const real_T Gain2_po;               /* '<S33>/Gain2' */
  const real_T Product4_e;             /* '<S33>/Product4' */
  const real_T Product5_b;             /* '<S33>/Product5' */
  const real_T Product8_m;             /* '<S33>/Product8' */
  const real_T Sum_b;                  /* '<S33>/Sum' */
  const real_T Product_nc;             /* '<S34>/Product' */
  const real_T Product1_ne;            /* '<S34>/Product1' */
  const real_T Sum1_pw;                /* '<S34>/Sum1' */
  const real_T Gain_ip;                /* '<S34>/Gain' */
  const real_T Product2_j;             /* '<S34>/Product2' */
  const real_T Product3_mj;            /* '<S34>/Product3' */
  const real_T Sum2_p;                 /* '<S34>/Sum2' */
  const real_T Gain1_d;                /* '<S34>/Gain1' */
  const real_T Product6_f;             /* '<S34>/Product6' */
  const real_T Product7_p;             /* '<S34>/Product7' */
  const real_T Sum3_j;                 /* '<S34>/Sum3' */
  const real_T Gain2_k;                /* '<S34>/Gain2' */
  const real_T Product4_p;             /* '<S34>/Product4' */
  const real_T Product5_i;             /* '<S34>/Product5' */
  const real_T Product8_a4;            /* '<S34>/Product8' */
  const real_T Sum_l;                  /* '<S34>/Sum' */
  const real_T Product_l;              /* '<S35>/Product' */
  const real_T Product1_f;             /* '<S35>/Product1' */
  const real_T Sum1_b;                 /* '<S35>/Sum1' */
  const real_T Gain_f;                 /* '<S35>/Gain' */
  const real_T Product2_gv;            /* '<S35>/Product2' */
  const real_T Product3_fg;            /* '<S35>/Product3' */
  const real_T Sum2_k;                 /* '<S35>/Sum2' */
  const real_T Gain1_np;               /* '<S35>/Gain1' */
  const real_T Product6_fr;            /* '<S35>/Product6' */
  const real_T Product7_fy;            /* '<S35>/Product7' */
  const real_T Sum3_i;                 /* '<S35>/Sum3' */
  const real_T Gain2_o;                /* '<S35>/Gain2' */
  const real_T Product4_e2;            /* '<S35>/Product4' */
  const real_T Product5_b0;            /* '<S35>/Product5' */
  const real_T Product8_a3;            /* '<S35>/Product8' */
  const real_T Sum_c;                  /* '<S35>/Sum' */
  const real_T Subtract1[3];           /* '<S9>/Subtract1' */
  const real_T Sum2_i[3];              /* '<S9>/Sum2' */
  const real_T Product6_m[3];          /* '<S10>/Product6' */
  const real_T RotationAnglestoQuaternio_p[4];
                                    /* '<S10>/Rotation Angles to Quaternions' */
  const real_T Product_ji;             /* '<S51>/Product' */
  const real_T Product1_es;            /* '<S51>/Product1' */
  const real_T Product2_in;            /* '<S51>/Product2' */
  const real_T Product3_i;             /* '<S51>/Product3' */
  const real_T Sum_iy;                 /* '<S51>/Sum' */
  const real_T sqrt_i;                 /* '<S50>/sqrt' */
  const real_T Product_g;              /* '<S46>/Product' */
  const real_T Product1_d;             /* '<S46>/Product1' */
  const real_T Product2_my;            /* '<S46>/Product2' */
  const real_T Product3_ac;            /* '<S46>/Product3' */
  const real_T Product_k;              /* '<S47>/Product' */
  const real_T Product1_h3;            /* '<S47>/Product1' */
  const real_T Sum1_by;                /* '<S47>/Sum1' */
  const real_T Gain_d;                 /* '<S47>/Gain' */
  const real_T Product2_it;            /* '<S47>/Product2' */
  const real_T Product3_as;            /* '<S47>/Product3' */
  const real_T Sum2_c;                 /* '<S47>/Sum2' */
  const real_T Gain1_n0;               /* '<S47>/Gain1' */
  const real_T Product6_a;             /* '<S47>/Product6' */
  const real_T Product7_fk;            /* '<S47>/Product7' */
  const real_T Sum3_f;                 /* '<S47>/Sum3' */
  const real_T Gain2_a;                /* '<S47>/Gain2' */
  const real_T Product4_g;             /* '<S47>/Product4' */
  const real_T Product5_mk;            /* '<S47>/Product5' */
  const real_T Product8_e;             /* '<S47>/Product8' */
  const real_T Sum_m;                  /* '<S47>/Sum' */
  const real_T Product_kq;             /* '<S48>/Product' */
  const real_T Product1_c;             /* '<S48>/Product1' */
  const real_T Sum1_li;                /* '<S48>/Sum1' */
  const real_T Gain_e;                 /* '<S48>/Gain' */
  const real_T Product2_d;             /* '<S48>/Product2' */
  const real_T Product3_g;             /* '<S48>/Product3' */
  const real_T Sum2_n;                 /* '<S48>/Sum2' */
  const real_T Gain1_npp;              /* '<S48>/Gain1' */
  const real_T Product6_h;             /* '<S48>/Product6' */
  const real_T Product7_gx;            /* '<S48>/Product7' */
  const real_T Sum3_be;                /* '<S48>/Sum3' */
  const real_T Gain2_c;                /* '<S48>/Gain2' */
  const real_T Product4_f;             /* '<S48>/Product4' */
  const real_T Product5_l;             /* '<S48>/Product5' */
  const real_T Product8_m4;            /* '<S48>/Product8' */
  const real_T Sum_b1;                 /* '<S48>/Sum' */
  const real_T Product_ac;             /* '<S49>/Product' */
  const real_T Product1_hd;            /* '<S49>/Product1' */
  const real_T Sum1_n;                 /* '<S49>/Sum1' */
  const real_T Gain_a;                 /* '<S49>/Gain' */
  const real_T Product2_lr;            /* '<S49>/Product2' */
  const real_T Product3_hc;            /* '<S49>/Product3' */
  const real_T Sum2_pw;                /* '<S49>/Sum2' */
  const real_T Gain1_p;                /* '<S49>/Gain1' */
  const real_T Product6_d;             /* '<S49>/Product6' */
  const real_T Product7_h;             /* '<S49>/Product7' */
  const real_T Sum3_n;                 /* '<S49>/Sum3' */
  const real_T Gain2_ps;               /* '<S49>/Gain2' */
  const real_T Product4_k;             /* '<S49>/Product4' */
  const real_T Product5_e;             /* '<S49>/Product5' */
  const real_T Product8_m5;            /* '<S49>/Product8' */
  const real_T Sum_k;                  /* '<S49>/Sum' */
  const real_T Product_h;              /* '<S57>/Product' */
  const real_T Product1_cm;            /* '<S57>/Product1' */
  const real_T Product2_n;             /* '<S57>/Product2' */
  const real_T Product3_gd;            /* '<S57>/Product3' */
  const real_T Sum_h;                  /* '<S57>/Sum' */
  const real_T sqrt_l;                 /* '<S56>/sqrt' */
  const real_T Product_i;              /* '<S52>/Product' */
  const real_T Product1_l;             /* '<S52>/Product1' */
  const real_T Product2_gk;            /* '<S52>/Product2' */
  const real_T Product3_o;             /* '<S52>/Product3' */
  const real_T Product_ga;             /* '<S53>/Product' */
  const real_T Product1_p;             /* '<S53>/Product1' */
  const real_T Sum1_a;                 /* '<S53>/Sum1' */
  const real_T Gain_k;                 /* '<S53>/Gain' */
  const real_T Product2_e;             /* '<S53>/Product2' */
  const real_T Product3_j;             /* '<S53>/Product3' */
  const real_T Sum2_o;                 /* '<S53>/Sum2' */
  const real_T Gain1_k;                /* '<S53>/Gain1' */
  const real_T Product6_gg;            /* '<S53>/Product6' */
  const real_T Product7_n;             /* '<S53>/Product7' */
  const real_T Sum3_b0;                /* '<S53>/Sum3' */
  const real_T Gain2_cm;               /* '<S53>/Gain2' */
  const real_T Product4_gs;            /* '<S53>/Product4' */
  const real_T Product5_lz;            /* '<S53>/Product5' */
  const real_T Product8_g;             /* '<S53>/Product8' */
  const real_T Sum_k3;                 /* '<S53>/Sum' */
  const real_T Product_gu;             /* '<S54>/Product' */
  const real_T Product1_g;             /* '<S54>/Product1' */
  const real_T Sum1_j;                 /* '<S54>/Sum1' */
  const real_T Gain_o;                 /* '<S54>/Gain' */
  const real_T Product2_b3;            /* '<S54>/Product2' */
  const real_T Product3_af;            /* '<S54>/Product3' */
  const real_T Sum2_kc;                /* '<S54>/Sum2' */
  const real_T Gain1_h;                /* '<S54>/Gain1' */
  const real_T Product6_i;             /* '<S54>/Product6' */
  const real_T Product7_h0;            /* '<S54>/Product7' */
  const real_T Sum3_a;                 /* '<S54>/Sum3' */
  const real_T Gain2_pr;               /* '<S54>/Gain2' */
  const real_T Product4_ks;            /* '<S54>/Product4' */
  const real_T Product5_c3;            /* '<S54>/Product5' */
  const real_T Product8_p;             /* '<S54>/Product8' */
  const real_T Sum_cv;                 /* '<S54>/Sum' */
  const real_T Product_aa;             /* '<S55>/Product' */
  const real_T Product1_o;             /* '<S55>/Product1' */
  const real_T Sum1_h;                 /* '<S55>/Sum1' */
  const real_T Gain_of;                /* '<S55>/Gain' */
  const real_T Product2_dy;            /* '<S55>/Product2' */
  const real_T Product3_ja;            /* '<S55>/Product3' */
  const real_T Sum2_el;                /* '<S55>/Sum2' */
  const real_T Gain1_i;                /* '<S55>/Gain1' */
  const real_T Product6_fm;            /* '<S55>/Product6' */
  const real_T Product7_m;             /* '<S55>/Product7' */
  const real_T Sum3_jk;                /* '<S55>/Sum3' */
  const real_T Gain2_d;                /* '<S55>/Gain2' */
  const real_T Product4_o;             /* '<S55>/Product4' */
  const real_T Product5_h;             /* '<S55>/Product5' */
  const real_T Product8_l;             /* '<S55>/Product8' */
  const real_T Sum_b1v;                /* '<S55>/Sum' */
  const real_T Subtract1_m[3];         /* '<S10>/Subtract1' */
  const real_T Sum2_l[3];              /* '<S10>/Sum2' */
  const real_T Product6_c1[3];         /* '<S11>/Product6' */
  const real_T RotationAnglestoQuaternio_o[4];
                                    /* '<S11>/Rotation Angles to Quaternions' */
  const real_T Product_p4;             /* '<S71>/Product' */
  const real_T Product1_gn;            /* '<S71>/Product1' */
  const real_T Product2_c;             /* '<S71>/Product2' */
  const real_T Product3_it;            /* '<S71>/Product3' */
  const real_T Sum_ed;                 /* '<S71>/Sum' */
  const real_T sqrt_a;                 /* '<S70>/sqrt' */
  const real_T Product_hg;             /* '<S66>/Product' */
  const real_T Product1_cf;            /* '<S66>/Product1' */
  const real_T Product2_m0;            /* '<S66>/Product2' */
  const real_T Product3_m4;            /* '<S66>/Product3' */
  const real_T Product_ea;             /* '<S67>/Product' */
  const real_T Product1_ia;            /* '<S67>/Product1' */
  const real_T Sum1_aa;                /* '<S67>/Sum1' */
  const real_T Gain_eb;                /* '<S67>/Gain' */
  const real_T Product2_n0;            /* '<S67>/Product2' */
  const real_T Product3_or;            /* '<S67>/Product3' */
  const real_T Sum2_kn;                /* '<S67>/Sum2' */
  const real_T Gain1_b;                /* '<S67>/Gain1' */
  const real_T Product6_if;            /* '<S67>/Product6' */
  const real_T Product7_b;             /* '<S67>/Product7' */
  const real_T Sum3_l;                 /* '<S67>/Sum3' */
  const real_T Gain2_h;                /* '<S67>/Gain2' */
  const real_T Product4_pe;            /* '<S67>/Product4' */
  const real_T Product5_mh;            /* '<S67>/Product5' */
  const real_T Product8_et;            /* '<S67>/Product8' */
  const real_T Sum_o;                  /* '<S67>/Sum' */
  const real_T Product_o;              /* '<S68>/Product' */
  const real_T Product1_l2;            /* '<S68>/Product1' */
  const real_T Sum1_hw;                /* '<S68>/Sum1' */
  const real_T Gain_j;                 /* '<S68>/Gain' */
  const real_T Product2_jc;            /* '<S68>/Product2' */
  const real_T Product3_b;             /* '<S68>/Product3' */
  const real_T Sum2_ei;                /* '<S68>/Sum2' */
  const real_T Gain1_c;                /* '<S68>/Gain1' */
  const real_T Product6_md;            /* '<S68>/Product6' */
  const real_T Product7_m1;            /* '<S68>/Product7' */
  const real_T Sum3_p;                 /* '<S68>/Sum3' */
  const real_T Gain2_e;                /* '<S68>/Gain2' */
  const real_T Product4_i;             /* '<S68>/Product4' */
  const real_T Product5_n;             /* '<S68>/Product5' */
  const real_T Product8_lf;            /* '<S68>/Product8' */
  const real_T Sum_er;                 /* '<S68>/Sum' */
  const real_T Product_b;              /* '<S69>/Product' */
  const real_T Product1_jg;            /* '<S69>/Product1' */
  const real_T Sum1_ni;                /* '<S69>/Sum1' */
  const real_T Gain_h;                 /* '<S69>/Gain' */
  const real_T Product2_o;             /* '<S69>/Product2' */
  const real_T Product3_p;             /* '<S69>/Product3' */
  const real_T Sum2_np;                /* '<S69>/Sum2' */
  const real_T Gain1_d3;               /* '<S69>/Gain1' */
  const real_T Product6_ik;            /* '<S69>/Product6' */
  const real_T Product7_pd;            /* '<S69>/Product7' */
  const real_T Sum3_jg;                /* '<S69>/Sum3' */
  const real_T Gain2_eg;               /* '<S69>/Gain2' */
  const real_T Product4_l;             /* '<S69>/Product4' */
  const real_T Product5_cm;            /* '<S69>/Product5' */
  const real_T Product8_e2;            /* '<S69>/Product8' */
  const real_T Sum_g;                  /* '<S69>/Sum' */
  const real_T Product_au;             /* '<S77>/Product' */
  const real_T Product1_ho;            /* '<S77>/Product1' */
  const real_T Product2_db;            /* '<S77>/Product2' */
  const real_T Product3_f4;            /* '<S77>/Product3' */
  const real_T Sum_ou;                 /* '<S77>/Sum' */
  const real_T sqrt_c;                 /* '<S76>/sqrt' */
  const real_T Product_jk;             /* '<S72>/Product' */
  const real_T Product1_lz;            /* '<S72>/Product1' */
  const real_T Product2_ej;            /* '<S72>/Product2' */
  const real_T Product3_kd;            /* '<S72>/Product3' */
  const real_T Product_pn;             /* '<S73>/Product' */
  const real_T Product1_hg;            /* '<S73>/Product1' */
  const real_T Sum1_hp;                /* '<S73>/Sum1' */
  const real_T Gain_ju;                /* '<S73>/Gain' */
  const real_T Product2_lf;            /* '<S73>/Product2' */
  const real_T Product3_ok;            /* '<S73>/Product3' */
  const real_T Sum2_g;                 /* '<S73>/Sum2' */
  const real_T Gain1_bw;               /* '<S73>/Gain1' */
  const real_T Product6_p;             /* '<S73>/Product6' */
  const real_T Product7_fi;            /* '<S73>/Product7' */
  const real_T Sum3_a4;                /* '<S73>/Sum3' */
  const real_T Gain2_g;                /* '<S73>/Gain2' */
  const real_T Product4_pk;            /* '<S73>/Product4' */
  const real_T Product5_cq;            /* '<S73>/Product5' */
  const real_T Product8_i;             /* '<S73>/Product8' */
  const real_T Sum_a;                  /* '<S73>/Sum' */
  const real_T Product_f;              /* '<S74>/Product' */
  const real_T Product1_m;             /* '<S74>/Product1' */
  const real_T Sum1_jr;                /* '<S74>/Sum1' */
  const real_T Gain_f1;                /* '<S74>/Gain' */
  const real_T Product2_mf;            /* '<S74>/Product2' */
  const real_T Product3_hu;            /* '<S74>/Product3' */
  const real_T Sum2_dz;                /* '<S74>/Sum2' */
  const real_T Gain1_nr;               /* '<S74>/Gain1' */
  const real_T Product6_g5;            /* '<S74>/Product6' */
  const real_T Product7_d;             /* '<S74>/Product7' */
  const real_T Sum3_fs;                /* '<S74>/Sum3' */
  const real_T Gain2_o0;               /* '<S74>/Gain2' */
  const real_T Product4_d;             /* '<S74>/Product4' */
  const real_T Product5_k;             /* '<S74>/Product5' */
  const real_T Product8_pt;            /* '<S74>/Product8' */
  const real_T Sum_ia;                 /* '<S74>/Sum' */
  const real_T Product_p4q;            /* '<S75>/Product' */
  const real_T Product1_a;             /* '<S75>/Product1' */
  const real_T Sum1_a5;                /* '<S75>/Sum1' */
  const real_T Gain_kb;                /* '<S75>/Gain' */
  const real_T Product2_p;             /* '<S75>/Product2' */
  const real_T Product3_e;             /* '<S75>/Product3' */
  const real_T Sum2_j;                 /* '<S75>/Sum2' */
  const real_T Gain1_nt;               /* '<S75>/Gain1' */
  const real_T Product6_o;             /* '<S75>/Product6' */
  const real_T Product7_gc;            /* '<S75>/Product7' */
  const real_T Sum3_n2;                /* '<S75>/Sum3' */
  const real_T Gain2_j;                /* '<S75>/Gain2' */
  const real_T Product4_b;             /* '<S75>/Product4' */
  const real_T Product5_d;             /* '<S75>/Product5' */
  const real_T Product8_c;             /* '<S75>/Product8' */
  const real_T Sum_bt;                 /* '<S75>/Sum' */
  const real_T Subtract1_k[3];         /* '<S11>/Subtract1' */
  const real_T Sum2_iw[3];             /* '<S11>/Sum2' */
  const real_T Product6_ok[3];         /* '<S12>/Product6' */
  const real_T RotationAnglestoQuaternio_g[4];
                                    /* '<S12>/Rotation Angles to Quaternions' */
  const real_T Product_k2;             /* '<S91>/Product' */
  const real_T Product1_dq;            /* '<S91>/Product1' */
  const real_T Product2_e5;            /* '<S91>/Product2' */
  const real_T Product3_h5;            /* '<S91>/Product3' */
  const real_T Sum_b3;                 /* '<S91>/Sum' */
  const real_T sqrt_e;                 /* '<S90>/sqrt' */
  const real_T Product_jz;             /* '<S86>/Product' */
  const real_T Product1_e3;            /* '<S86>/Product1' */
  const real_T Product2_hp;            /* '<S86>/Product2' */
  const real_T Product3_ix;            /* '<S86>/Product3' */
  const real_T Product_m;              /* '<S87>/Product' */
  const real_T Product1_ay;            /* '<S87>/Product1' */
  const real_T Sum1_g5;                /* '<S87>/Sum1' */
  const real_T Gain_fg;                /* '<S87>/Gain' */
  const real_T Product2_pv;            /* '<S87>/Product2' */
  const real_T Product3_n;             /* '<S87>/Product3' */
  const real_T Sum2_b;                 /* '<S87>/Sum2' */
  const real_T Gain1_e;                /* '<S87>/Gain1' */
  const real_T Product6_dg;            /* '<S87>/Product6' */
  const real_T Product7_dv;            /* '<S87>/Product7' */
  const real_T Sum3_c;                 /* '<S87>/Sum3' */
  const real_T Gain2_ol;               /* '<S87>/Gain2' */
  const real_T Product4_gu;            /* '<S87>/Product4' */
  const real_T Product5_lb;            /* '<S87>/Product5' */
  const real_T Product8_h;             /* '<S87>/Product8' */
  const real_T Sum_d;                  /* '<S87>/Sum' */
  const real_T Product_el;             /* '<S88>/Product' */
  const real_T Product1_lk;            /* '<S88>/Product1' */
  const real_T Sum1_f;                 /* '<S88>/Sum1' */
  const real_T Gain_p0;                /* '<S88>/Gain' */
  const real_T Product2_br;            /* '<S88>/Product2' */
  const real_T Product3_hx;            /* '<S88>/Product3' */
  const real_T Sum2_a;                 /* '<S88>/Sum2' */
  const real_T Gain1_ns;               /* '<S88>/Gain1' */
  const real_T Product6_hn;            /* '<S88>/Product6' */
  const real_T Product7_ph;            /* '<S88>/Product7' */
  const real_T Sum3_ly;                /* '<S88>/Sum3' */
  const real_T Gain2_bm;               /* '<S88>/Gain2' */
  const real_T Product4_dp;            /* '<S88>/Product4' */
  const real_T Product5_ep;            /* '<S88>/Product5' */
  const real_T Product8_mj;            /* '<S88>/Product8' */
  const real_T Sum_b4;                 /* '<S88>/Sum' */
  const real_T Product_fg;             /* '<S89>/Product' */
  const real_T Product1_f0;            /* '<S89>/Product1' */
  const real_T Sum1_b3;                /* '<S89>/Sum1' */
  const real_T Gain_d3;                /* '<S89>/Gain' */
  const real_T Product2_e4;            /* '<S89>/Product2' */
  const real_T Product3_fe;            /* '<S89>/Product3' */
  const real_T Sum2_om;                /* '<S89>/Sum2' */
  const real_T Gain1_m;                /* '<S89>/Gain1' */
  const real_T Product6_nr;            /* '<S89>/Product6' */
  const real_T Product7_a;             /* '<S89>/Product7' */
  const real_T Sum3_ob;                /* '<S89>/Sum3' */
  const real_T Gain2_ky;               /* '<S89>/Gain2' */
  const real_T Product4_kc;            /* '<S89>/Product4' */
  const real_T Product5_i4;            /* '<S89>/Product5' */
  const real_T Product8_f;             /* '<S89>/Product8' */
  const real_T Sum_ln;                 /* '<S89>/Sum' */
  const real_T Product_my;             /* '<S97>/Product' */
  const real_T Product1_id;            /* '<S97>/Product1' */
  const real_T Product2_l4;            /* '<S97>/Product2' */
  const real_T Product3_k4;            /* '<S97>/Product3' */
  const real_T Sum_fj;                 /* '<S97>/Sum' */
  const real_T sqrt_j;                 /* '<S96>/sqrt' */
  const real_T Product_ez;             /* '<S92>/Product' */
  const real_T Product1_b;             /* '<S92>/Product1' */
  const real_T Product2_f;             /* '<S92>/Product2' */
  const real_T Product3_ec;            /* '<S92>/Product3' */
  const real_T Product_lg;             /* '<S93>/Product' */
  const real_T Product1_bj;            /* '<S93>/Product1' */
  const real_T Sum1_m;                 /* '<S93>/Sum1' */
  const real_T Gain_c;                 /* '<S93>/Gain' */
  const real_T Product2_p5;            /* '<S93>/Product2' */
  const real_T Product3_fd;            /* '<S93>/Product3' */
  const real_T Sum2_g0;                /* '<S93>/Sum2' */
  const real_T Gain1_f;                /* '<S93>/Gain1' */
  const real_T Product6_l0;            /* '<S93>/Product6' */
  const real_T Product7_a2;            /* '<S93>/Product7' */
  const real_T Sum3_dk;                /* '<S93>/Sum3' */
  const real_T Gain2_l;                /* '<S93>/Gain2' */
  const real_T Product4_pp;            /* '<S93>/Product4' */
  const real_T Product5_kd;            /* '<S93>/Product5' */
  const real_T Product8_ik;            /* '<S93>/Product8' */
  const real_T Sum_dx;                 /* '<S93>/Sum' */
  const real_T Product_fc;             /* '<S94>/Product' */
  const real_T Product1_eg;            /* '<S94>/Product1' */
  const real_T Sum1_c;                 /* '<S94>/Sum1' */
  const real_T Gain_ofb;               /* '<S94>/Gain' */
  const real_T Product2_itz;           /* '<S94>/Product2' */
  const real_T Product3_d;             /* '<S94>/Product3' */
  const real_T Sum2_cq;                /* '<S94>/Sum2' */
  const real_T Gain1_h5;               /* '<S94>/Gain1' */
  const real_T Product6_id;            /* '<S94>/Product6' */
  const real_T Product7_fm;            /* '<S94>/Product7' */
  const real_T Sum3_g;                 /* '<S94>/Sum3' */
  const real_T Gain2_jt;               /* '<S94>/Gain2' */
  const real_T Product4_bz;            /* '<S94>/Product4' */
  const real_T Product5_nd;            /* '<S94>/Product5' */
  const real_T Product8_fh;            /* '<S94>/Product8' */
  const real_T Sum_o3;                 /* '<S94>/Sum' */
  const real_T Product_os;             /* '<S95>/Product' */
  const real_T Product1_a2;            /* '<S95>/Product1' */
  const real_T Sum1_jru;               /* '<S95>/Sum1' */
  const real_T Gain_j3;                /* '<S95>/Gain' */
  const real_T Product2_dv;            /* '<S95>/Product2' */
  const real_T Product3_ks;            /* '<S95>/Product3' */
  const real_T Sum2_ay;                /* '<S95>/Sum2' */
  const real_T Gain1_ia;               /* '<S95>/Gain1' */
  const real_T Product6_lv;            /* '<S95>/Product6' */
  const real_T Product7_bx;            /* '<S95>/Product7' */
  const real_T Sum3_jt;                /* '<S95>/Sum3' */
  const real_T Gain2_i;                /* '<S95>/Gain2' */
  const real_T Product4_go;            /* '<S95>/Product4' */
  const real_T Product5_a;             /* '<S95>/Product5' */
  const real_T Product8_kf;            /* '<S95>/Product8' */
  const real_T Sum_j;                  /* '<S95>/Sum' */
  const real_T Subtract1_j[3];         /* '<S12>/Subtract1' */
  const real_T Sum2_ayz[3];            /* '<S12>/Sum2' */
  const real_T UnitConversion;         /* '<S120>/Unit Conversion' */
  const real_T UnitConversion_g;       /* '<S130>/Unit Conversion' */
  const real_T sigma_wg;               /* '<S139>/sigma_wg ' */
  const real_T UnitConversion_e;       /* '<S124>/Unit Conversion' */
  const real_T UnitConversion_k;       /* '<S158>/Unit Conversion' */
  const real_T PreLookUpIndexSearchprobofe;
                        /* '<S138>/PreLook-Up Index Search  (prob of exceed)' */
  const real_T constBlockForifHeightMaxlow;
  const real_T constBlockForifHeightMaxl_b;
  const real_T constBlockForifHeightMaxl_d;
  const real_T constBlockForifHeightMaxl_n;
  const real_T Sqrt[4];                /* '<S131>/Sqrt' */
  const real_T Sqrt1;                  /* '<S131>/Sqrt1' */
  const real_T Divide[4];              /* '<S131>/Divide' */
  const real_T UnitConversion_m;       /* '<S159>/Unit Conversion' */
  const real_T Wy;                     /* '<S118>/SinCos' */
  const real_T Wx;                     /* '<S118>/SinCos' */
  const real_T Windspeedatreferenceheight[3];
                                   /* '<S118>/Wind speed at reference height' */
  const real_T lnref_heightz0;         /* '<S118>/ln(ref_height//z0)' */
  const real_T Product_an;             /* '<S167>/Product' */
  const real_T Switch;                 /* '<S167>/Switch' */
  const real_T Product_mh[9];          /* '<S170>/Product' */
  const real_T dIdt[9];                /* '<S170>/Add' */
  const real_T Sum_dd;                 /* '<S208>/Sum' */
  const real_T a2;                     /* '<S220>/a2' */
  const real_T b2;                     /* '<S220>/b2' */
  const real_T c2;                     /* '<S263>/Sum1' */
  const real_T a4;                     /* '<S265>/a4' */
  const real_T b4;                     /* '<S265>/b4' */
  const real_T c4;                     /* '<S265>/Sum9' */
  const real_T c2_l;                   /* '<S266>/Sum1' */
  const real_T Sum_p;                  /* '<S148>/Sum' */
  const real_T Sum_is;                 /* '<S140>/Sum' */
  const real_T sqrt_g;                 /* '<S137>/sqrt' */
  const real_T w4;                     /* '<S132>/w4' */
  const real_T u16;                    /* '<S132>/u^1//6' */
  const uint32_T PreLookUpIndexSearchprobo_j;
                        /* '<S138>/PreLook-Up Index Search  (prob of exceed)' */
  const boolean_T min_relop;           /* '<S203>/min_relop' */
  const boolean_T max_relop;           /* '<S203>/max_relop' */
  const boolean_T conjunction;         /* '<S203>/conjunction' */
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
      uint8_T TID[2];
    } TaskCounters;

    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
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
 * Block '<S119>/3ft-->inf' : Unused code path elimination
 * Block '<S161>/Unit Conversion' : Unused code path elimination
 * Block '<S119>/Cast To Double' : Unused code path elimination
 * Block '<S162>/Unit Conversion' : Unused code path elimination
 * Block '<S119>/Product' : Unused code path elimination
 * Block '<S119>/Product1' : Unused code path elimination
 * Block '<S119>/Reshape' : Unused code path elimination
 * Block '<S119>/Reshape1' : Unused code path elimination
 * Block '<S119>/SinCos' : Unused code path elimination
 * Block '<S119>/Transform from Inertial to Body axes' : Unused code path elimination
 * Block '<S119>/Wdeg1' : Unused code path elimination
 * Block '<S119>/Wind Direction' : Unused code path elimination
 * Block '<S119>/Wind speed at reference height' : Unused code path elimination
 * Block '<S119>/h//z0' : Unused code path elimination
 * Block '<S119>/ln(h//z0)' : Unused code path elimination
 * Block '<S119>/ln(ref_height//z0)' : Unused code path elimination
 * Block '<S119>/ref_height//z0' : Unused code path elimination
 * Block '<S166>/Element Product' : Unused code path elimination
 * Block '<S166>/Sum' : Unused code path elimination
 * Block '<S163>/Sum' : Unused code path elimination
 * Block '<S168>/Unit Conversion' : Unused code path elimination
 * Block '<S206>/Unit Conversion' : Unused code path elimination
 * Block '<S207>/Unit Conversion' : Unused code path elimination
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
 * Block '<S144>/Reshape' : Reshape block reduction
 * Block '<S144>/Reshape1' : Reshape block reduction
 * Block '<S146>/Reshape' : Reshape block reduction
 * Block '<S152>/Reshape' : Reshape block reduction
 * Block '<S152>/Reshape1' : Reshape block reduction
 * Block '<S154>/Reshape' : Reshape block reduction
 * Block '<S118>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S118>/Reshape' : Reshape block reduction
 * Block '<S118>/Reshape1' : Reshape block reduction
 * Block '<S169>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S170>/Reshape' : Reshape block reduction
 * Block '<S203>/maxtype' : Eliminate redundant data type conversion
 * Block '<S203>/mintype' : Eliminate redundant data type conversion
 * Block '<S205>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S191>/Unit Conversion2' : Eliminated nontunable gain of 1
 * Block '<S236>/Reshape' : Reshape block reduction
 * Block '<S243>/Reshape' : Reshape block reduction
 * Block '<S244>/Reshape' : Reshape block reduction
 * Block '<S245>/Reshape' : Reshape block reduction
 * Block '<S245>/Reshape1' : Reshape block reduction
 * Block '<S221>/Gain' : Eliminated nontunable gain of 1
 * Block '<S221>/Gain1' : Eliminated nontunable gain of 1
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
 * '<S119>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model1'
 * '<S120>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Angle Conversion'
 * '<S121>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates'
 * '<S122>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities'
 * '<S123>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Length Conversion'
 * '<S124>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Length Conversion1'
 * '<S125>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities'
 * '<S126>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates'
 * '<S127>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities'
 * '<S128>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths'
 * '<S129>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Velocity Conversion'
 * '<S130>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Velocity Conversion2'
 * '<S131>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/White Noise'
 * '<S132>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hpgw'
 * '<S133>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hqgw'
 * '<S134>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on angular rates/Hrgw'
 * '<S135>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hugw(s)'
 * '<S136>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hvgw(s)'
 * '<S137>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Filters on velocities/Hwgw(s)'
 * '<S138>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities/High Altitude Intensity'
 * '<S139>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/RMS turbulence  intensities/Low Altitude Intensity'
 * '<S140>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates'
 * '<S141>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates'
 * '<S142>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Medium//High  altitude rates'
 * '<S143>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Merge Subsystems'
 * '<S144>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates/wind to body transformation'
 * '<S145>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Interpolate  rates/wind to body transformation/convert to earth coords'
 * '<S146>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates/wind to body transformation'
 * '<S147>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select angular rates/Low altitude  rates/wind to body transformation/convert to earth coords'
 * '<S148>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities'
 * '<S149>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities'
 * '<S150>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Medium//High  altitude velocities'
 * '<S151>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Merge Subsystems'
 * '<S152>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities/wind to body transformation'
 * '<S153>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Interpolate  velocities/wind to body transformation/convert to earth coords'
 * '<S154>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities/wind to body transformation'
 * '<S155>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Select velocities/Low altitude  velocities/wind to body transformation/convert to earth coords'
 * '<S156>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Low altitude scale length'
 * '<S157>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Medium//High altitude scale length'
 * '<S158>' : 'autocodePlant/Plant/Enviroment/windModel/Dryden Wind Turbulence Model  (Continuous (-q +r))/Turbulence scale lengths/Medium//High altitude scale length/Length Conversion'
 * '<S159>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model/Angle Conversion'
 * '<S160>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model/Length Conversion'
 * '<S161>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model1/Angle Conversion'
 * '<S162>' : 'autocodePlant/Plant/Enviroment/windModel/Wind Shear Model1/Length Conversion'
 * '<S163>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration'
 * '<S164>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration'
 * '<S165>' : 'autocodePlant/Plant/Equatons of Motion/Rail Model'
 * '<S166>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Cross Product'
 * '<S167>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Total Force'
 * '<S168>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Velocity Conversion'
 * '<S169>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Acceleration/Velocity Conversion1'
 * '<S170>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration/Compute dIdt'
 * '<S171>' : 'autocodePlant/Plant/Equatons of Motion/6DOF Angular Acceleration/Cross Product'
 * '<S172>' : 'autocodePlant/Plant/Motor Model/clock'
 * '<S173>' : 'autocodePlant/Sensor Plant/Accelerometer'
 * '<S174>' : 'autocodePlant/Sensor Plant/Barometer'
 * '<S175>' : 'autocodePlant/Sensor Plant/Gyroscope'
 * '<S176>' : 'autocodePlant/Sensor Plant/Magnetometer'
 * '<S177>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation'
 * '<S178>' : 'autocodePlant/Sensor Plant/Accelerometer/w(t)'
 * '<S179>' : 'autocodePlant/Sensor Plant/Accelerometer/w2(t)'
 * '<S180>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize'
 * '<S181>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V1'
 * '<S182>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V2'
 * '<S183>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/V3'
 * '<S184>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S185>' : 'autocodePlant/Sensor Plant/Accelerometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S186>' : 'autocodePlant/Sensor Plant/Barometer/w(t)'
 * '<S187>' : 'autocodePlant/Sensor Plant/Barometer/white-noise'
 * '<S188>' : 'autocodePlant/Sensor Plant/Gyroscope/w(t)'
 * '<S189>' : 'autocodePlant/Sensor Plant/Gyroscope/w2(t)'
 * '<S190>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation'
 * '<S191>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model'
 * '<S192>' : 'autocodePlant/Sensor Plant/Magnetometer/white-noise'
 * '<S193>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize'
 * '<S194>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V1'
 * '<S195>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V2'
 * '<S196>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/V3'
 * '<S197>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
 * '<S198>' : 'autocodePlant/Sensor Plant/Magnetometer/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S199>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Altitude'
 * '<S200>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Latitude'
 * '<S201>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Check Longitude'
 * '<S202>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Compute x,y,z, and h components of magnetic field'
 * '<S203>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Is time within model limits'
 * '<S204>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap'
 * '<S205>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Length Conversion'
 * '<S206>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/MagField Conversion'
 * '<S207>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/MagField Conversion1'
 * '<S208>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag'
 * '<S209>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/Compute x,y,z, and h components of magnetic field/Angle Conversion'
 * '<S210>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90'
 * '<S211>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Wrap Longitude'
 * '<S212>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Compare To Constant'
 * '<S213>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero'
 * '<S214>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Wrap Angle 180'
 * '<S215>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero/If Action Subsystem'
 * '<S216>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Sign1 Or Zero/If Action Subsystem1'
 * '<S217>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
 * '<S218>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/LatLong wrap/Wrap Longitude/Compare To Constant'
 * '<S219>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates'
 * '<S220>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates'
 * '<S221>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates '
 * '<S222>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Get Cosine and Sine  of Latitude and Longitude'
 * '<S223>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has altitude or latitude changed'
 * '<S224>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has longitude changed '
 * '<S225>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Has time changed'
 * '<S226>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity'
 * '<S227>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem'
 * '<S228>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion'
 * '<S229>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations'
 * '<S230>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients'
 * '<S231>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole'
 * '<S232>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate  index'
 * '<S233>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values'
 * '<S234>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/special case'
 * '<S235>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem1'
 * '<S236>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2'
 * '<S237>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2/calculate  indices'
 * '<S238>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/Special case - North//South Geographic Pole/If Action Subsystem2/calculate  row and column'
 * '<S239>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem'
 * '<S240>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1'
 * '<S241>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1/m,n'
 * '<S242>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Accumulate terms of the  spherical harmonic expansion/calculate temp values/If Action Subsystem1/n,m-1'
 * '<S243>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem'
 * '<S244>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1'
 * '<S245>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2'
 * '<S246>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/calculate  index'
 * '<S247>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem/calculate  index'
 * '<S248>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem/calculate  row and column'
 * '<S249>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1/calculate  index'
 * '<S250>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem1/calculate  row and column'
 * '<S251>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  indices'
 * '<S252>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  row and column1'
 * '<S253>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/calculate  row and column2'
 * '<S254>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/m<n-2'
 * '<S255>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Compute unnormalized associated  legendre polynomials and  derivatives via recursion relations/If Action Subsystem2/m<n-2 '
 * '<S256>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/If Action Subsystem'
 * '<S257>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)'
 * '<S258>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)/If Action Subsystem1'
 * '<S259>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Compute magnetic vector in spherical coordinates/For Iterator Subsystem/Time adjust the gauss coefficients/if (m~=0)/If Action Subsystem2'
 * '<S260>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate ca'
 * '<S261>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate ct'
 * '<S262>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate d'
 * '<S263>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate q'
 * '<S264>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate q2'
 * '<S265>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate r2'
 * '<S266>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate sa'
 * '<S267>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates/calculate st'
 * '<S268>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Convert from geodetic to  spherical coordinates /For Iterator Subsystem'
 * '<S269>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Get Cosine and Sine  of Latitude and Longitude/Angle Conversion2'
 * '<S270>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate bx'
 * '<S271>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate by'
 * '<S272>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Calculate bz'
 * '<S273>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity'
 * '<S274>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity/Angle Conversion'
 * '<S275>' : 'autocodePlant/Sensor Plant/Magnetometer/World Magnetic Model/geomag/Rotate magnetic vector components  to geodetic from spherical and  compute declination, inclination  and total intensity/Compute declination, inclination,  and total intensity/Angle Conversion1'
 */
#endif                                 /* autocodePlant_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
