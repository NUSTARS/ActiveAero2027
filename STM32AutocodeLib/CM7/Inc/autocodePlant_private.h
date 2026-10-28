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
 * C/C++ source code generated on : Tue Oct 27 19:08:19 2026
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
extern const real_T rtCP_pooled_dv0Tl0SlWhXs[3];
extern const real_T rtCP_pooled_14ELQx6IKv5S[9];
extern const real_T rtCP_pooled_sBIJJlXDbIPs[9];
extern const real_T rtCP_pooled_JIXvzcabvSoM[9];
extern const real_T rtCP_pooled_ef9QsjHy4PWT[3];
extern const real_T rtCP_pooled_l4jm3STFDRtI[9];
extern const real_T rtCP_pooled_eAvIOzbeucLm[150];
extern const real_T rtCP_pooled_8SI81E8rkJpf[10];
extern const real_T rtCP_pooled_WNDZ2Qab58zn[3];
extern const real_T rtCP_pooled_EUbHB07NscWq[5];
extern const real_T rtCP_pooled_UvjEgMknWiW5[150];
extern const real_T rtCP_pooled_mp0rSfxeHTgT[30];
extern const real_T rtCP_pooled_QdRu7KTE4giD[30];
extern const real_T rtCP_pooled_3H9qc1cSvZnc[30];
extern const real_T rtCP_pooled_JSo03ipyAXHp[12];
extern const real_T rtCP_pooled_7gMUpNl9LMnN[84];
extern const real_T rtCP_pooled_Ypj7adFkGj9p[26];
extern const real_T rtCP_pooled_9qn6g4UeIonm[26];
extern const uint32_T rtCP_pooled_dTVRh1Zt8UHp[3];
extern const uint32_T rtCP_pooled_VXtezd9XA1ka[2];
extern const uint32_T rtCP_pooled_pJtn2I2I3lAZ[2];

#define rtCP__k1313_Value              rtCP_pooled_Xx6JxPt3qDMl  /* Expression: k
                                                                  * Referenced by: '<S218>/k[13][13]'
                                                                  */
#define rtCP__k1313_Value_j            rtCP_pooled_Xx6JxPt3qDMl  /* Expression: k
                                                                  * Referenced by: '<S227>/k[13][13]'
                                                                  */
#define rtCP__snorm169_Y0              rtCP_pooled_LGbvdPSmO37j  /* Expression: snorm
                                                                  * Referenced by: '<S211>/snorm[169]'
                                                                  */
#define rtCP__UnitDelay1_InitialCondi_n rtCP_pooled_LGbvdPSmO37j /* Expression: snorm
                                                                  * Referenced by: '<S211>/Unit Delay1'
                                                                  */
#define rtCP__cmaxdefmaxdef_Value      rtCP_pooled_8bV7r3D8ytRk  /* Expression: c
                                                                  * Referenced by: '<S212>/c[maxdef][maxdef]'
                                                                  */
#define rtCP__cdmaxdefmaxdef_Value     rtCP_pooled_6ZjlqwKmnCn7  /* Expression: cd
                                                                  * Referenced by: '<S212>/cd[maxdef][maxdef]'
                                                                  */
#define rtCP__fm_Value                 rtCP_pooled_1qQdvahcw3x7  /* Expression: fm
                                                                  * Referenced by: '<S210>/fm'
                                                                  */
#define rtCP__fn_Value                 rtCP_pooled_iFJY9irE5eYu  /* Expression: fn
                                                                  * Referenced by: '<S210>/fn'
                                                                  */
#define rtCP__sp11_Y0                  rtCP_pooled_NdeBycQJIW0T  /* Expression: (1:(maxdef-1))
                                                                  * Referenced by: '<S250>/sp[11]'
                                                                  */
#define rtCP__cp11_Y0                  rtCP_pooled_NdeBycQJIW0T  /* Expression: (1:(maxdef-1))
                                                                  * Referenced by: '<S250>/cp[11]'
                                                                  */
#define rtCP__Constant_Value_f         rtCP_pooled_NdeBycQJIW0T  /* Expression: [1:maxdef-1]
                                                                  * Referenced by: '<S250>/Constant'
                                                                  */
#define rtCP__Constant1_Value_a        rtCP_pooled_NdeBycQJIW0T  /* Expression: [1:maxdef-1]
                                                                  * Referenced by: '<S250>/Constant1'
                                                                  */
#define rtCP__sp13_Y0                  rtCP_pooled_M1CXqHf2LQgH  /* Expression: [0 0 (1:(maxdef-1))]
                                                                  * Referenced by: '<S203>/sp[13]'
                                                                  */
#define rtCP__cp13_Y0                  rtCP_pooled_DNIXYaNNqB8g  /* Expression: [1 1 (1:(maxdef-1))]
                                                                  * Referenced by: '<S203>/cp[13]'
                                                                  */
#define rtCP__Constant_Value_dx        rtCP_pooled_dv0Tl0SlWhXs  /* Expression: windParams.constantNed_mps
                                                                  * Referenced by: '<S87>/Constant'
                                                                  */
#define rtCP__Constant1_Value_fo       rtCP_pooled_14ELQx6IKv5S  /* Expression: vehicleParams.inertia_kgm2
                                                                  * Referenced by: '<S5>/Constant1'
                                                                  */
#define rtCP__Constant_Value_dxg       rtCP_pooled_sBIJJlXDbIPs  /* Expression: sensorParams.accScaleCoupling_na
                                                                  * Referenced by: '<S155>/Constant'
                                                                  */
#define rtCP___Value_n                 rtCP_pooled_sBIJJlXDbIPs  /* Expression: sensorParams.gyroScaleCoupling_na
                                                                  * Referenced by: '<S157>/   '
                                                                  */
#define rtCP__Gs_Value                 rtCP_pooled_JIXvzcabvSoM  /* Expression: sensorParams.gyroG
                                                                  * Referenced by: '<S157>/Gs'
                                                                  */
#define rtCP__hardironBdy_nT_Value     rtCP_pooled_ef9QsjHy4PWT  /* Expression: sensorParams.magBiasHIBdy_nT
                                                                  * Referenced by: '<S158>/hardironBdy_nT'
                                                                  */
#define rtCP__softironmatrix_Value     rtCP_pooled_l4jm3STFDRtI  /* Expression: sensorParams.magSI
                                                                  * Referenced by: '<S158>/soft iron matrix'
                                                                  */
#define rtCP__CALookupTable_tableData  rtCP_pooled_eAvIOzbeucLm  /* Expression: aeroParams.CaFin_na
                                                                  * Referenced by: '<S9>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp01Data   rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S9>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp02Data   rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S9>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp03Data   rtCP_pooled_EUbHB07NscWq  /* Expression: aeroParams.controlBreakpoints_deg
                                                                  * Referenced by: '<S9>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_tableData  rtCP_pooled_UvjEgMknWiW5  /* Expression: aeroParams.CnFin_na
                                                                  * Referenced by: '<S9>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp01Data   rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S9>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp02Data   rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S9>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp03Data   rtCP_pooled_EUbHB07NscWq  /* Expression: aeroParams.controlBreakpoints_deg
                                                                  * Referenced by: '<S9>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_tableData_b rtCP_pooled_eAvIOzbeucLm /* Expression: aeroParams.CaFin_na
                                                                  * Referenced by: '<S10>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp01Data_n rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S10>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp02Data_h rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S10>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp03Data_f rtCP_pooled_EUbHB07NscWq  /* Expression: aeroParams.controlBreakpoints_deg
                                                                  * Referenced by: '<S10>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_tableData_f rtCP_pooled_UvjEgMknWiW5 /* Expression: aeroParams.CnFin_na
                                                                  * Referenced by: '<S10>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp01Data_f rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S10>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp02Data_a rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S10>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp03Data_p rtCP_pooled_EUbHB07NscWq  /* Expression: aeroParams.controlBreakpoints_deg
                                                                  * Referenced by: '<S10>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_tableData_n rtCP_pooled_eAvIOzbeucLm /* Expression: aeroParams.CaFin_na
                                                                  * Referenced by: '<S11>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp01Data_f rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S11>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp02Data_e rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S11>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp03Data_fn rtCP_pooled_EUbHB07NscWq /* Expression: aeroParams.controlBreakpoints_deg
                                                                  * Referenced by: '<S11>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_tableData_j rtCP_pooled_UvjEgMknWiW5 /* Expression: aeroParams.CnFin_na
                                                                  * Referenced by: '<S11>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp01Data_n rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S11>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp02Data_i rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S11>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp03Data_l rtCP_pooled_EUbHB07NscWq  /* Expression: aeroParams.controlBreakpoints_deg
                                                                  * Referenced by: '<S11>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_tableData_l rtCP_pooled_eAvIOzbeucLm /* Expression: aeroParams.CaFin_na
                                                                  * Referenced by: '<S12>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp01Data_k rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S12>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp02Data_f rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S12>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp03Data_b rtCP_pooled_EUbHB07NscWq  /* Expression: aeroParams.controlBreakpoints_deg
                                                                  * Referenced by: '<S12>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_tableData_d rtCP_pooled_UvjEgMknWiW5 /* Expression: aeroParams.CnFin_na
                                                                  * Referenced by: '<S12>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp01Data_d rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S12>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp02Data_av rtCP_pooled_WNDZ2Qab58zn /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S12>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp03Data_g rtCP_pooled_EUbHB07NscWq  /* Expression: aeroParams.controlBreakpoints_deg
                                                                  * Referenced by: '<S12>/CN Lookup Table'
                                                                  */
#define rtCP__CPLookupTable_tableData  rtCP_pooled_mp0rSfxeHTgT  /* Expression: aeroParams.CpBase_m
                                                                  * Referenced by: '<S8>/CP Lookup Table'
                                                                  */
#define rtCP__CPLookupTable_bp01Data   rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S8>/CP Lookup Table'
                                                                  */
#define rtCP__CPLookupTable_bp02Data   rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S8>/CP Lookup Table'
                                                                  */
#define rtCP__CALookupTable_tableData_e rtCP_pooled_QdRu7KTE4giD /* Expression: aeroParams.CaBase_na
                                                                  * Referenced by: '<S8>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp01Data_j rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S8>/CA Lookup Table'
                                                                  */
#define rtCP__CALookupTable_bp02Data_b rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S8>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_tableData_i rtCP_pooled_3H9qc1cSvZnc /* Expression: aeroParams.CnBase_na
                                                                  * Referenced by: '<S8>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp01Data_a rtCP_pooled_8SI81E8rkJpf  /* Expression: aeroParams.machBreakpoints_na
                                                                  * Referenced by: '<S8>/CN Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_bp02Data_o rtCP_pooled_WNDZ2Qab58zn  /* Expression: aeroParams.aoaBreakpoints_deg
                                                                  * Referenced by: '<S8>/CN Lookup Table'
                                                                  */
#define rtCP__PreLookUpIndexSearchaltit rtCP_pooled_JSo03ipyAXHp /* Expression: h_vec
                                                                  * Referenced by: '<S122>/PreLook-Up Index Search  (altitude)'
                                                                  */
#define rtCP__MediumHighAltitudeIntensi rtCP_pooled_7gMUpNl9LMnN /* Expression: sigma_vec'
                                                                  * Referenced by: '<S122>/Medium//High Altitude Intensity'
                                                                  */
#define rtCP__uDLookupTable_tableData  rtCP_pooled_Ypj7adFkGj9p  /* Expression: motorParams.thrust
                                                                  * Referenced by: '<S6>/1-D Lookup Table'
                                                                  */
#define rtCP__uDLookupTable_bp01Data   rtCP_pooled_9qn6g4UeIonm  /* Expression: motorParams.time
                                                                  * Referenced by: '<S6>/1-D Lookup Table'
                                                                  */
#define rtCP__CALookupTable_dimSizes   rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CALookupTable_dimSizes
                                                                  * Referenced by: '<S9>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_dimSizes   rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CNLookupTable_dimSizes
                                                                  * Referenced by: '<S9>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_dimSizes_c rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CALookupTable_dimSizes_c
                                                                  * Referenced by: '<S10>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_dimSizes_e rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CNLookupTable_dimSizes_e
                                                                  * Referenced by: '<S10>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_dimSizes_e rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CALookupTable_dimSizes_e
                                                                  * Referenced by: '<S11>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_dimSizes_ex rtCP_pooled_dTVRh1Zt8UHp /* Computed Parameter: rtCP__CNLookupTable_dimSizes_ex
                                                                  * Referenced by: '<S11>/CN Lookup Table'
                                                                  */
#define rtCP__CALookupTable_dimSizes_a rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CALookupTable_dimSizes_a
                                                                  * Referenced by: '<S12>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_dimSizes_h rtCP_pooled_dTVRh1Zt8UHp  /* Computed Parameter: rtCP__CNLookupTable_dimSizes_h
                                                                  * Referenced by: '<S12>/CN Lookup Table'
                                                                  */
#define rtCP__CPLookupTable_maxIndex   rtCP_pooled_VXtezd9XA1ka  /* Computed Parameter: rtCP__CPLookupTable_maxIndex
                                                                  * Referenced by: '<S8>/CP Lookup Table'
                                                                  */
#define rtCP__CALookupTable_maxIndex_j rtCP_pooled_VXtezd9XA1ka  /* Computed Parameter: rtCP__CALookupTable_maxIndex_j
                                                                  * Referenced by: '<S8>/CA Lookup Table'
                                                                  */
#define rtCP__CNLookupTable_maxIndex_a rtCP_pooled_VXtezd9XA1ka  /* Computed Parameter: rtCP__CNLookupTable_maxIndex_a
                                                                  * Referenced by: '<S8>/CN Lookup Table'
                                                                  */
#define rtCP__MediumHighAltitudeInten_o rtCP_pooled_pJtn2I2I3lAZ /* Computed Parameter: rtCP__MediumHighAltitudeInten_o
                                                                  * Referenced by: '<S122>/Medium//High Altitude Intensity'
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
