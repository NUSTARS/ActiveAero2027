/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: autocodePlant_private.h
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

#ifndef autocodePlant_private_h_
#define autocodePlant_private_h_
#include "rtwtypes.h"
#include "autocodePlant_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern const real_T rtCP_pooled_Xx6JxPt3qDMl[169];
extern const real_T rtCP_pooled_LGbvdPSmO37j[169];
extern const real_T rtCP_pooled_8bV7r3D8ytRk[169];
extern const real_T rtCP_pooled_6ZjlqwKmnCn7[169];
extern const real_T rtCP_pooled_1qQdvahcw3x7[13];
extern const real_T rtCP_pooled_iFJY9irE5eYu[13];
extern const real_T rtCP_pooled_NdeBycQJIW0T[11];
extern const real_T rtCP_pooled_M1CXqHf2LQgH[13];
extern const real_T rtCP_pooled_DNIXYaNNqB8g[13];
extern const real_T rtCP_pooled_JSo03ipyAXHp[12];
extern const real_T rtCP_pooled_7gMUpNl9LMnN[84];
extern const uint32_T rtCP_pooled_pJtn2I2I3lAZ[2];
extern const uint32_T rtCP_pooled_dTVRh1Zt8UHp[3];
extern const uint32_T rtCP_pooled_VXtezd9XA1ka[2];

#define rtCP__k1313_Value              rtCP_pooled_Xx6JxPt3qDMl  /* Expression: k
                                                                  * Referenced by: '<S234>/k[13][13]'
                                                                  */
#define rtCP__k1313_Value_j            rtCP_pooled_Xx6JxPt3qDMl  /* Expression: k
                                                                  * Referenced by: '<S243>/k[13][13]'
                                                                  */
#define rtCP__snorm169_Y0              rtCP_pooled_LGbvdPSmO37j  /* Expression: snorm
                                                                  * Referenced by: '<S227>/snorm[169]'
                                                                  */
#define rtCP__UnitDelay1_InitialCondi_n rtCP_pooled_LGbvdPSmO37j /* Expression: snorm
                                                                  * Referenced by: '<S227>/Unit Delay1'
                                                                  */
#define rtCP__cmaxdefmaxdef_Value      rtCP_pooled_8bV7r3D8ytRk  /* Expression: c
                                                                  * Referenced by: '<S228>/c[maxdef][maxdef]'
                                                                  */
#define rtCP__cdmaxdefmaxdef_Value     rtCP_pooled_6ZjlqwKmnCn7  /* Expression: cd
                                                                  * Referenced by: '<S228>/cd[maxdef][maxdef]'
                                                                  */
#define rtCP__fm_Value                 rtCP_pooled_1qQdvahcw3x7  /* Expression: fm
                                                                  * Referenced by: '<S226>/fm'
                                                                  */
#define rtCP__fn_Value                 rtCP_pooled_iFJY9irE5eYu  /* Expression: fn
                                                                  * Referenced by: '<S226>/fn'
                                                                  */
#define rtCP__sp11_Y0                  rtCP_pooled_NdeBycQJIW0T  /* Expression: (1:(maxdef-1))
                                                                  * Referenced by: '<S266>/sp[11]'
                                                                  */
#define rtCP__cp11_Y0                  rtCP_pooled_NdeBycQJIW0T  /* Expression: (1:(maxdef-1))
                                                                  * Referenced by: '<S266>/cp[11]'
                                                                  */
#define rtCP__Constant_Value_f         rtCP_pooled_NdeBycQJIW0T  /* Expression: [1:maxdef-1]
                                                                  * Referenced by: '<S266>/Constant'
                                                                  */
#define rtCP__Constant1_Value_a        rtCP_pooled_NdeBycQJIW0T  /* Expression: [1:maxdef-1]
                                                                  * Referenced by: '<S266>/Constant1'
                                                                  */
#define rtCP__sp13_Y0                  rtCP_pooled_M1CXqHf2LQgH  /* Expression: [0 0 (1:(maxdef-1))]
                                                                  * Referenced by: '<S219>/sp[13]'
                                                                  */
#define rtCP__cp13_Y0                  rtCP_pooled_DNIXYaNNqB8g  /* Expression: [1 1 (1:(maxdef-1))]
                                                                  * Referenced by: '<S219>/cp[13]'
                                                                  */
#define rtCP__PreLookUpIndexSearchaltit rtCP_pooled_JSo03ipyAXHp /* Expression: h_vec
                                                                  * Referenced by: '<S137>/PreLook-Up Index Search  (altitude)'
                                                                  */
#define rtCP__MediumHighAltitudeIntensi rtCP_pooled_7gMUpNl9LMnN /* Expression: sigma_vec'
                                                                  * Referenced by: '<S137>/Medium//High Altitude Intensity'
                                                                  */
#define rtCP__MediumHighAltitudeInten_o rtCP_pooled_pJtn2I2I3lAZ /* Computed Parameter: rtCP__MediumHighAltitudeInten_o
                                                                  * Referenced by: '<S137>/Medium//High Altitude Intensity'
                                                                  */
#define rtCP__CALookupTable_dimSizes   rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CALookupTable_dimSizes
                                                                  * Referenced by: '<S10>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_dimSizes   rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CNLookupTable_dimSizes
                                                                  * Referenced by: '<S10>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_dimSizes_k rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CALookupTable_dimSizes_k
                                                                  * Referenced by: '<S9>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_dimSizes_j rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CNLookupTable_dimSizes_j
                                                                  * Referenced by: '<S9>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_dimSizes_e rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CALookupTable_dimSizes_e
                                                                  * Referenced by: '<S11>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_dimSizes_e rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CNLookupTable_dimSizes_e
                                                                  * Referenced by: '<S11>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_dimSizes_a rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CALookupTable_dimSizes_a
                                                                  * Referenced by: '<S12>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_dimSizes_h rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CNLookupTable_dimSizes_h
                                                                  * Referenced by: '<S12>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_maxIndex_j rtCP_pooled_VXtezd9XA1ka  /* Computed Parameter: rtCP__CALookupTable_maxIndex_j
                                                                  * Referenced by: '<S8>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_maxIndex_a rtCP_pooled_VXtezd9XA1ka  /* Computed Parameter: rtCP__CNLookupTable_maxIndex_a
                                                                  * Referenced by: '<S8>/CN Lookup Table'
                                                                  */
#define rtCP__CPLookupTable_maxIndex   rtCP_pooled_VXtezd9XA1ka  /* Computed Parameter: rtCP__CPLookupTable_maxIndex
                                                                  * Referenced by: '<S8>/CP Lookup Table'
                                                                  */

/* private model entry point functions */
extern void autocodePlant_derivatives(RT_MODEL_autocodePlant_T *const
  autocodePlant_M);

#endif                                 /* autocodePlant_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
