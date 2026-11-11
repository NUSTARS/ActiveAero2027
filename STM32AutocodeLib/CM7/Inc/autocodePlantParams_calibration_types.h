/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: autocodePlantParams_calibration_types.h
 *
 * Code generated for Simulink model 'autocodePlant'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Tue Nov 10 19:36:56 2026
 */

#ifndef autocodePlantParams_calibration_types_h_
#define autocodePlantParams_calibration_types_h_
#include "rtwtypes.h"

typedef struct {
  uint8_T aeroFileName[14];
  real_T finStaticScale_na;
  real_T finControlScale_na;
  real_T finStaticInputScale_na;
  real_T finControlInputScale_na;
  real_T bodyScale_na;
  real_T CpBaseShift_m;
  real_T finCP1_m[3];
  real_T finCP2_m[3];
  real_T finCP3_m[3];
  real_T finCP4_m[3];
  real_T finAngles1_rad[3];
  real_T finAngles2_rad[3];
  real_T finAngles3_rad[3];
  real_T finAngles4_rad[3];
  real_T machBreakpoints_na[10];
  real_T aoaBreakpoints_deg[3];
  real_T controlBreakpoints_deg[5];
  real_T CpBase_m[30];
  real_T CaBase_na[30];
  real_T CnBase_na[30];
  real_T CnFin_na[150];
  real_T CaFin_na[150];
} cal_autocodePlantParams_aeroParams;

typedef struct {
  real_T gravityNed_mps2[3];
  real_T lon_deg;
  real_T lat_deg;
  real_T groundAlt_m;
  real_T date_y;
} cal_autocodePlantParams_envParams;

typedef struct {
  real_T velBdy_mps[3];
  real_T rateBdy_rps[3];
  real_T posNed_m[3];
  real_T eulIC_rad[3];
  real_T eul_rad[3];
} cal_autocodePlantParams_icParams;

typedef struct {
  uint8_T thrustDataFile[19];
  real_T startUpDelay;
  real_T thrustData[52];
  real_T time[26];
  real_T thrustScaling_na;
  real_T thrust[26];
} cal_autocodePlantParams_motorParams;

typedef struct {
  real_T imuPosBdy_m[3];
  real_T accMarkovGain_na;
  real_T accTurnOnBias_mps2[3];
  real_T accSigmaBias_mps2[3];
  real_T accPSDGM[3];
  real_T accPSDWhite[3];
  real_T accScaleCoupling_na[9];
  real_T accSampleTime_s;
  real_T gyroMarkovGain_na;
  real_T gyroSigmaBiasTurnOn_rps[3];
  real_T gyroSigmaBias_rps[3];
  real_T gyroTurnOnBias_rps[3];
  real_T gyroPSDWhite[3];
  real_T gyroPSDGM[3];
  real_T gyroG[9];
  real_T gyroScaleCoupling_na[9];
  real_T gyroSampleTime_s;
  real_T magBiasHIBdy_nT[3];
  real_T magSampleTime_s;
  real_T magPSDWhite[3];
  real_T baroBiasTurnOn_Pa;
  real_T baroMarkovGain_na;
  real_T baroSampleTime_s;
  real_T magSI[9];
  real_T baroPSDWhite;
  real_T baroPSDGM;
  real_T gpsSampleTime_s;
  real_T gpsDelay_na;
  real_T gpsOutageSampleTime_s;
  real_T gpsOutageProbability_pct;
} cal_autocodePlantParams_sensorParams;

typedef struct {
  real_T dt_s;
} cal_autocodePlantParams_simParams;

typedef struct {
  real_T length_m;
  real_T mass_kg;
  real_T area_m2;
  real_T cg_m;
  real_T inertia_kgm2[9];
} cal_autocodePlantParams_vehicleParams;

typedef struct {
  boolean_T useWindShear_b;
  boolean_T useWindTurbulence_b;
  real_T constantNed_mps[3];
  real_T lowAltWindSpeed_mps;
  real_T lowAltWindDir_deg;
} cal_autocodePlantParams_windParams;

#endif                            /* autocodePlantParams_calibration_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
