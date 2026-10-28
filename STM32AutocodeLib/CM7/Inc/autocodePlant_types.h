/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: autocodePlant_types.h
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

#ifndef autocodePlant_types_h_
#define autocodePlant_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_body_bus_
#define DEFINED_TYPEDEF_FOR_body_bus_

typedef struct {
  real_T bodyMoment_Nm[3];
  real_T bodyForce_N[3];
  real_T aoa_deg;
} body_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_fin_bus_
#define DEFINED_TYPEDEF_FOR_fin_bus_

typedef struct {
  real_T finMoment_Nm[3];
  real_T finForce_N[3];
  real_T aoa_deg;
  real_T liftSign_na;
  real_T airspeedFin_mps[3];
} fin_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_aero_bus_
#define DEFINED_TYPEDEF_FOR_aero_bus_

typedef struct {
  real_T aeroMoment_Nm[3];
  real_T aeroForce_N[3];
  fin_bus fin1_bus;
  fin_bus fin2_bus;
  fin_bus fin3_bus;
  fin_bus fin4_bus;
  body_bus body_bus;
} aero_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_environment_bus_
#define DEFINED_TYPEDEF_FOR_environment_bus_

typedef struct {
  real_T gravityForceBdy_N[3];
  real_T temp_K;
  real_T a_mps;
  real_T pressure_Pa;
  real_T rho_kgpm3;
  boolean_T onRail_b;
  real_T airspeed_mps[3];
  real_T windBdy_mps[3];
  real_T airW_rps[3];
} environment_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_eom_bus_
#define DEFINED_TYPEDEF_FOR_eom_bus_

typedef struct {
  real_T posNed_m[3];
  real_T q_na[4];
  real_T velBdy_mps[3];
  real_T wBdy_rps[3];
  real_T accBdy_mps2[3];
  real_T wDotBdy_rps2[3];
} eom_bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_plant_bus_
#define DEFINED_TYPEDEF_FOR_plant_bus_

typedef struct {
  environment_bus enviroment_bus;
  aero_bus aero_bus;
  eom_bus eom_bus;
} plant_bus;

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

/* Forward declaration for rtModel */
typedef struct tag_RTM_autocodePlant_T RT_MODEL_autocodePlant_T;

#endif                                 /* autocodePlant_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
