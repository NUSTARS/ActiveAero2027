/* Edit parameter initializers here for STM32 builds.
 * Included only by autocodePlantParams_calibration.c. Regenerated from the dictionary on MATLAB build.
 * Sample times, delay lengths, dimensions and inlined expressions remain
 * compiled into the model. See the MATLAB tunability warnings. */
#ifndef AUTOCODEPLANTPARAMS_CALIBRATION_VALUES_H
#define AUTOCODEPLANTPARAMS_CALIBRATION_VALUES_H

/* MATLAB assignments from definePlantDD.m:
in2m = 1/39.37;
P.vehicleParams.length_m = 2.75;
P.vehicleParams.mass_kg = 17.5;                       
P.vehicleParams.area_m2 = 0.018;                      
P.vehicleParams.cg_m = 71.33*in2m;                         
P.vehicleParams.inertia_kgm2 = diag([0.053, 8.41, 8.41]);
P.simParams.dt_s = 1/100; % [s] Simulation time step
P.icParams.velBdy_mps  = [0, 0, 0];   % [m/s]
P.icParams.rateBdy_rps = [0, 0, 0];      % [rad/s]
P.icParams.posNed_m    = [0, 0, 0];      % [m]
P.icParams.eulIC_rad = [1.0, 0.1, 0.0];
P.envParams.gravityNed_mps2 = [0, 0, 9.81];   % [m/s^2]
P.envParams.lon_deg = -87.6767064830923; % [deg]
P.envParams.lat_deg = 42.0569355774686; % [deg]
P.envParams.groundAlt_m = 182; % [m] above ellipsoid surface (sea level)
P.envParams.date_y = decyear('01-September-2026','dd-mmm-yyyy'); % [y] year + fraction of year
P.windParams.useWindShear_b = false;
P.windParams.useWindTurbulence_b = false;
P.windParams.constantNed_mps = [5; 0; 0];
P.windParams.lowAltWindSpeed_mps = 5;
P.windParams.lowAltWindDir_deg = 180; % CW from north
P.motorParams.thrustDataFile = 'AeroTech_M1315W.csv'; % [N] Motor thrust data file name
P.motorParams.startUpDelay = 20; % [s] Motor start up delay 
P.motorParams.thrustData = readmatrix(P.motorParams.thrustDataFile);
P.motorParams.time = P.motorParams.thrustData(:,1);
P.motorParams.thrustScaling_na = 1.0;
P.aeroParams.aeroFileName = 'aeroTables.mat';
P.aeroParams.finStaticScale_na = 1.0;
P.aeroParams.finControlScale_na = 1.0;
P.aeroParams.finStaticInputScale_na = 1.0;
P.aeroParams.finControlInputScale_na = 1.0;
P.aeroParams.bodyScale_na = 1.0;
P.aeroParams.CpBaseShift_m = 0.0;
finCP_m = in2m*[105; 5; 0]; % should be in +Y
rot90Matrix = [1 0 0; 0 0 -1; 0 1 0];
P.aeroParams.finCP1_m = finCP_m;
P.aeroParams.finCP2_m = rot90Matrix*P.aeroParams.finCP1_m;
P.aeroParams.finCP3_m = rot90Matrix*P.aeroParams.finCP2_m;
P.aeroParams.finCP4_m = rot90Matrix*P.aeroParams.finCP3_m;
P.aeroParams.finAngles1_rad = [0, 0, 0];
P.aeroParams.finAngles2_rad = [pi/2, 0, 0];
P.aeroParams.finAngles3_rad = [pi, 0, 0];
P.aeroParams.finAngles4_rad = [3*pi/2, 0, 0];
P = derivePlantDD(P);
 */
/* MATLAB assignments from defineSensorDD.m:
biasOn = true;
S.sensorParams.imuPosBdy_m = [0, 0, 0];
accRate_Hz = 100;
accScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0];
accnoiseDensity_microgpsqHz = [75, 75, 75];
S.sensorParams.accMarkovGain_na = 0.99995;
accSigmaBias_mg = [0.2, 0.2, 0.2];
accSigmaBiasTurnOn_mg = [2.0, 2.0, 2.0];
accSigmaBiasTurnOn_mps2 = accSigmaBiasTurnOn_mg * 0.00981;
S.sensorParams.accTurnOnBias_mps2 = accSigmaBiasTurnOn_mps2 * randn(1, 1);
S.sensorParams.accSigmaBias_mps2 = accSigmaBias_mg * 0.00981; % [m/s^2]
accnoiseDensity_mps2psqHz = accnoiseDensity_microgpsqHz * 9.81e-6; % [m/s^2 / sqrt(Hz)]
S.sensorParams.accPSDGM = 2 * S.sensorParams.accSigmaBias_mps2 .* S.sensorParams.accSigmaBias_mps2 / (-1/(log(S.sensorParams.accMarkovGain_na)*accRate_Hz));
S.sensorParams.accPSDWhite = accnoiseDensity_mps2psqHz .* accnoiseDensity_mps2psqHz;
S.sensorParams.accScaleCoupling_na = eye(3) + accScaleCoupling_na;
S.sensorParams.accSampleTime_s = 1 / accRate_Hz;
gyroRate_Hz = 100; % [Hz]
gyroSigmaBias_degphr = [100, 100, 100];
gyroScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0];
S.sensorParams.gyroMarkovGain_na = 0.99995;
S.sensorParams.gyroSigmaBiasTurnOn_rps = [0.009, 0.009, 0.009];
gyroG = [0.05 0 0; 0 0.05 0; 0 0 0.05]; % [deg / s / g]
gyroSigmaBiasTurnOn_rps = [0.009, 0.009, 0.009];
S.sensorParams.gyroSigmaBias_rps = gyroSigmaBias_degphr * 4.848e-6; % [rad / s]
S.sensorParams.gyroTurnOnBias_rps = gyroSigmaBiasTurnOn_rps * randn(1, 1);
gyroNoiseDensity_degpspsqHz = [0.00035, 0.00035, 0.00035]; % [deg / s / sqrt(Hz)]
gryoNoiseDensity_radpspsqHz = gyroNoiseDensity_degpspsqHz * 0.01745; % [rad / s / sqrt(Hz)]
S.sensorParams.gyroPSDWhite = gryoNoiseDensity_radpspsqHz .* gryoNoiseDensity_radpspsqHz;
S.sensorParams.gyroPSDGM = 2 * S.sensorParams.gyroSigmaBias_rps .* S.sensorParams.gyroSigmaBias_rps / (-1/(log(S.sensorParams.gyroMarkovGain_na)*gyroRate_Hz));
S.sensorParams.gyroG = gyroG * 0.01745 / 9.8065; % [rad / s / (m/s)]
S.sensorParams.gyroScaleCoupling_na = eye(3) + gyroScaleCoupling_na;
S.sensorParams.gyroSampleTime_s = 1 / gyroRate_Hz;
magSI = [0.08 0.05 -0.03; 0.04 -0.07 0.02; -0.03 0.02 0.05];
S.sensorParams.magBiasHIBdy_nT = 1000 * [1.2, -0.8, 0.5];
magNoiseDensity_nTpsqHz = [14, 14, 14];
magRate_Hz = 100; % [Hz]
S.sensorParams.magSampleTime_s = 1 / magRate_Hz; % [s]
S.sensorParams.magPSDWhite = magNoiseDensity_nTpsqHz .* magNoiseDensity_nTpsqHz;
baroNoiseDensity_PapsqHz = 0.02;
S.sensorParams.baroBiasTurnOn_Pa = 40;
baroBiasSigma_Pa = 6; % [Pa]
S.sensorParams.baroMarkovGain_na = 0.99998;
baroRate_Hz = 100;
S.sensorParams.baroSampleTime_s = 1 / baroRate_Hz;
S.sensorParams.magSI = eye(3) + magSI;
S.sensorParams.baroPSDWhite = baroNoiseDensity_PapsqHz^2;
S.sensorParams.baroPSDGM = 2 * baroBiasSigma_Pa^2 / (-1/(log(S.sensorParams.baroMarkovGain_na)*baroRate_Hz));
S.sensorParams.gpsSampleTime_s = 0.1;
S.sensorParams.gpsDelay_na = 15; % At 100hz rate
S.sensorParams.gpsOutageSampleTime_s = 1;
S.sensorParams.gpsOutageProbability_pct = 0.1;
    S.sensorParams.accPSDWhite = zeros(3,1);
    S.sensorParams.accPSDGM = zeros(3,1);
    S.sensorParams.accTurnOnBias_mps2 = zeros(3,1);
    S.sensorParams.gyroPSDWhite = zeros(3,1);
    S.sensorParams.gyroPSDGM = zeros(3,1);
    S.sensorParams.gyroTurnOnBias_rps = zeros(3,1);
    S.sensorParams.gyroG = zeros(3,3);
 */
/* MATLAB assignments from defineSimDD.m:
S.sensorParams.imuPosBdy_m = [0, 0, 0]; % [m]
accScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0]; % [dimensionless][[0, 0, 0], [0, 0, 0], [0, 0, 0]]
S.sensorParams.accScaleCoupling_na = eye(3) + accScaleCoupling_na;
accnoiseDensity_microgpsqHz = [75, 75, 75]; % [microg/sqrt(Hz)]
accnoiseDensity_mps2psqHz = accnoiseDensity_microgpsqHz * 9.81e-6; % [m/s^2 / sqrt(Hz)]
S.sensorParams.accPSDWhite = accnoiseDensity_mps2psqHz .* accnoiseDensity_mps2psqHz;
S.sensorParams.accTau_s = 200; % [s]
accSigmaBias_mg = [0.2, 0.2, 0.2]; % [millig]
S.sensorParams.accSigmaBias_mps2 = accSigmaBias_mg * 0.00981; % [m/s^2]
S.sensorParams.accPSDGM = 2 * S.sensorParams.accSigmaBias_mps2 .* ...
    S.sensorParams.accSigmaBias_mps2 / S.sensorParams.accTau_s;
accSigmaBiasTurnOn_mg = [2.0, 2.0, 2.0]; % [millig]
accSigmaBiasTurnOn_mps2 = accSigmaBiasTurnOn_mg * 0.00981; % [m/s^2]
S.sensorParams.accTurnOnBias_mps2 = accSigmaBiasTurnOn_mps2 * randn(1, 1);
accRate_Hz = 100; % [Hz]
S.sensorParams.accSampleTime_s = 1 / accRate_Hz; % [s]
gyroScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0]; % [dimensionless]
S.sensorParams.gyroScaleCoupling_na = eye(3) + gyroScaleCoupling_na;
gyroNoiseDensity_degpspsqHz = [0.0035, 0.0035, 0.0035]; % [deg / s / sqrt(Hz)]
gryoNoiseDensity_radpspsqHz = gyroNoiseDensity_degpspsqHz * 0.01745; % [rad / s / sqrt(Hz)]
S.sensorParams.gyroPSDWhite = gryoNoiseDensity_radpspsqHz .* gryoNoiseDensity_radpspsqHz;
S.sensorParams.gyroTau_s = 2000; % [s]
gyroSigmaBias_degphr = [10000, 10000, 10000]; % [deg / hr]
S.sensorParams.gyroSigmaBias_rps = gyroSigmaBias_degphr * 4.848e-6; % [rad / s]
S.sensorParams.gyroPSDGM = 2 * S.sensorParams.gyroSigmaBias_rps .* ...
    S.sensorParams.gyroSigmaBias_rps / S.sensorParams.gyroTau_s;
S.sensorParams.gyroSigmaBiasTurnOn_rps = 0*[0.0005, 0.0005, 0.0005];
gyroRate_Hz = 100; % [Hz]
S.sensorParams.gyroSampleTime_s = 1 / gyroRate_Hz; % [s]
gyroG = [0.1 0 0; 0 0.1 0; 0 0 0.1]; % [deg / s / g
S.sensorParams.gyroG = gyroG * 0.01745 * 9.8065; % [rad / s / (m/s)]
gyroSigmaBiasTurnOn_rps = 0*[0.008, 0.008, 0.008]; % [rad / s]
S.sensorParams.gyroTurnOnBias_rps = gyroSigmaBiasTurnOn_rps * randn(1, 1);
magSI = [0.08 0.05 -0.03; 0.04 -0.07 0.02; -0.03 0.02 0.05]; % [dimensionless]
S.sensorParams.magSI = eye(3) + magSI;
S.sensorParams.magBiasHIBdy_nT = 1000 * [1.2, -0.8, 0.5]; % [nT]
magNoiseDensity_nTpsqHz = [14, 14, 14]; % [nT / sqrt(Hz)]
S.sensorParams.magPSDWhite = magNoiseDensity_nTpsqHz .* magNoiseDensity_nTpsqHz;
magRate_Hz = 100; % [Hz]
S.sensorParams.magSampleTime_s = 1 / magRate_Hz; % [s]
baroNoiseDensity_PapsqHz = 0.02; % [Pa /sqrt(Hz)]
S.sensorParams.baroPSDWhite = baroNoiseDensity_PapsqHz^2;
S.sensorParams.baroBiasTurnOn_Pa = 40; % [Pa]
baroBiasSigma_Pa = 6; % [Pa]
S.sensorParams.baroTau_s = 500; % [s]
S.sensorParams.baroPSDGM = 2 * baroBiasSigma_Pa^2 / S.sensorParams.baroTau_s;
baroRate_Hz = 100; % [Hz]
S.sensorParams.baroSampleTime_s = 1 / baroRate_Hz; % [s]
 */
/* MATLAB assignments from derivePlantDD.m:
in2m = 1/39.37;
P.motorParams.thrust = P.motorParams.thrustScaling_na.*P.motorParams.thrustData(:,2);
quatIC_na = eul2quat(fliplr(P.icParams.eulIC_rad), "ZYX");
quatRotIC_na = quatmultiply([0.707106781187, 0, 0.707106781187, 0], quatIC_na);
P.icParams.eul_rad = fliplr(quat2eul(quatRotIC_na, "ZYX"));  % [rad], NED Euler angles
P.aeroParams.machBreakpoints_na = aeroTables.machPoints;
P.aeroParams.aoaBreakpoints_deg = aeroTables.aoaPoints;
P.aeroParams.controlBreakpoints_deg = aeroTables.controlPoints;
P.aeroParams.CpBase_m = in2m.*aeroTables.CpBase + P.aeroParams.CpBaseShift_m;
P.aeroParams.CaBase_na = P.aeroParams.bodyScale_na.*aeroTables.CaBase;
P.aeroParams.CnBase_na = P.aeroParams.bodyScale_na.*aeroTables.CnBase;
CnFinRaw_na = aeroTables.CnFinControl;
CaFinRaw_na = aeroTables.CaFinControl;
gridRaw = {P.aeroParams.machBreakpoints_na, P.aeroParams.aoaBreakpoints_deg, P.aeroParams.controlBreakpoints_deg};
gridScaled = {P.aeroParams.machBreakpoints_na, ...
              P.aeroParams.finStaticInputScale_na.*P.aeroParams.aoaBreakpoints_deg, ...
              P.aeroParams.finControlInputScale_na.*P.aeroParams.controlBreakpoints_deg};
CnFinInterp = griddedInterpolant(gridRaw, CnFinRaw_na, 'linear', 'linear');
CaFinInterp = griddedInterpolant(gridRaw, CaFinRaw_na, 'linear', 'linear');
CnFinScaled_na = CnFinInterp(gridScaled);
CaFinScaled_na = CaFinInterp(gridScaled);
zeroAoaIndex = find(P.aeroParams.aoaBreakpoints_deg == 0);
zeroControlIndex = find(P.aeroParams.controlBreakpoints_deg == 0);
aoaEffectCn = CnFinScaled_na - CnFinScaled_na(:,zeroAoaIndex,:);
aoaEffectCa = CaFinScaled_na - CaFinScaled_na(:,zeroAoaIndex,:);
controlEffectCn = CnFinScaled_na - CnFinScaled_na(:,:,zeroControlIndex);
controlEffectCa = CaFinScaled_na - CaFinScaled_na(:,:,zeroControlIndex);
P.aeroParams.CnFin_na = CnFinScaled_na + (P.aeroParams.finStaticScale_na - 1).*aoaEffectCn + (P.aeroParams.finControlScale_na - 1).*controlEffectCn;
P.aeroParams.CaFin_na = CaFinScaled_na + (P.aeroParams.finStaticScale_na - 1).*aoaEffectCa + (P.aeroParams.finControlScale_na - 1).*controlEffectCa;
 */
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: autocodePlantParams_calibration.c
 *
 * Code generated for Simulink model 'autocodePlant'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Tue Nov 10 19:22:59 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M7 (MPS2)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "autocodePlantParams_calibration.h"
#include "autocodePlantParams_calibration_types.h"

/* Exported data definition */

/* Definition for custom storage class: ExportToFile */
cal_autocodePlantParams_aeroParams aeroParams = {
  { 97U, 101U, 114U, 111U, 84U, 97U, 98U, 108U, 101U, 115U, 46U, 109U, 97U, 116U
  },
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,

  { 2.6670053340106685, 0.12700025400050802, 0.0 },

  { 2.6670053340106685, 0.0, 0.12700025400050802 },

  { 2.6670053340106685, -0.12700025400050802, 0.0 },

  { 2.6670053340106685, 0.0, -0.12700025400050802 },

  { 0.0, 0.0, 0.0 },

  { 1.5707963267948966, 0.0, 0.0 },

  { 3.1415926535897931, 0.0, 0.0 },

  { 4.71238898038469, 0.0, 0.0 },

  { 0.1, 0.2, 0.30000000000000004, 0.4, 0.5, 0.6, 0.70000000000000007,
    0.79999999999999993, 0.9, 1.0 },

  { 0.0, 2.0, 4.0 },

  { -4.0, -2.0, 0.0, 2.0, 4.0 },

  { 0.42910845821691646, 0.42910845821691646, 0.42910845821691646,
    0.42910845821691646, 0.42910845821691646, 0.42910845821691646,
    0.42910845821691646, 0.42910845821691646, 0.42910845821691646,
    0.32720345440690884, 0.67317754635509275, 0.67317754635509275,
    0.67317754635509275, 0.67317754635509275, 0.67317754635509275,
    0.67317754635509275, 0.67317754635509275, 0.67317754635509275,
    0.67317754635509275, 0.61836423672847352, 0.82085344170688357,
    0.82085344170688357, 0.82085344170688357, 0.82085344170688357,
    0.82085344170688357, 0.82085344170688357, 0.82085344170688357,
    0.82085344170688357, 0.82085344170688357, 0.78691897383794784 },

  { 0.301, 0.3, 0.3, 0.299, 0.299, 0.299, 0.298, 0.298, 0.298, 0.415, 0.301,
    0.301, 0.3, 0.3, 0.3, 0.299, 0.299, 0.298, 0.298, 0.415, 0.302, 0.302, 0.301,
    0.301, 0.301, 0.3, 0.3, 0.3, 0.299, 0.417 },

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.109, 0.109, 0.109, 0.109,
    0.109, 0.109, 0.109, 0.109, 0.109, 0.101, 0.27, 0.27, 0.27, 0.27, 0.27, 0.27,
    0.27, 0.27, 0.27, 0.255 },

  { -0.038500000000000006, -0.038500000000000006, -0.038500000000000006,
    -0.038500000000000006, -0.038500000000000006, -0.038500000000000006,
    -0.038500000000000006, -0.038500000000000006, -0.038500000000000006, -0.0328,
    0.154, 0.154, 0.154, 0.154, 0.154, 0.154, 0.154, 0.154, 0.154,
    0.13119999999999998, 0.34650000000000003, 0.34650000000000003,
    0.34650000000000003, 0.34650000000000003, 0.34650000000000003,
    0.34650000000000003, 0.34650000000000003, 0.34650000000000003,
    0.34650000000000003, 0.2952, -0.019250000000000003, -0.019250000000000003,
    -0.019250000000000003, -0.019250000000000003, -0.019250000000000003,
    -0.019250000000000003, -0.019250000000000003, -0.019250000000000003,
    -0.019250000000000003, -0.016399999999999998, 0.17325000000000002,
    0.17325000000000002, 0.17325000000000002, 0.17325000000000002,
    0.17325000000000002, 0.17325000000000002, 0.17325000000000002,
    0.17325000000000002, 0.17325000000000002, 0.14759999999999998, 0.36575,
    0.36575, 0.36575, 0.36575, 0.36575, 0.36575, 0.36575, 0.36575, 0.36575,
    0.3116, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1925, 0.1925,
    0.1925, 0.1925, 0.1925, 0.1925, 0.1925, 0.1925, 0.1925, 0.16399999999999998,
    0.385, 0.385, 0.385, 0.385, 0.385, 0.385, 0.385, 0.385, 0.385, 0.328,
    0.019250000000000003, 0.019250000000000003, 0.019250000000000003,
    0.019250000000000003, 0.019250000000000003, 0.019250000000000003,
    0.019250000000000003, 0.019250000000000003, 0.019250000000000003,
    0.016399999999999998, 0.21175, 0.21175, 0.21175, 0.21175, 0.21175, 0.21175,
    0.21175, 0.21175, 0.21175, 0.18039999999999998, 0.40425, 0.40425, 0.40425,
    0.40425, 0.40425, 0.40425, 0.40425, 0.40425, 0.40425, 0.34440000000000004,
    0.038500000000000006, 0.038500000000000006, 0.038500000000000006,
    0.038500000000000006, 0.038500000000000006, 0.038500000000000006,
    0.038500000000000006, 0.038500000000000006, 0.038500000000000006, 0.0328,
    0.231, 0.231, 0.231, 0.231, 0.231, 0.231, 0.231, 0.231, 0.231,
    0.19679999999999997, 0.4235, 0.4235, 0.4235, 0.4235, 0.4235, 0.4235, 0.4235,
    0.4235, 0.4235, 0.3608 },

  { 0.03635, 0.03685, 0.0369, 0.038450000000000005, 0.03905,
    0.039650000000000005, 0.042300000000000004, 0.044000000000000011,
    0.046250000000000013, 0.043450000000000009, 0.03685, 0.03685, 0.0374,
    0.037950000000000005, 0.03855, 0.039650000000000005, 0.041800000000000004,
    0.044500000000000012, 0.046250000000000013, 0.043450000000000009, 0.03685,
    0.03685, 0.0374, 0.037950000000000005, 0.03905, 0.040150000000000005,
    0.041800000000000004, 0.044000000000000011, 0.046750000000000014,
    0.043450000000000009, 0.03635, 0.03685, 0.0369, 0.038450000000000005,
    0.039000000000000007, 0.0396, 0.042300000000000004, 0.044050000000000006,
    0.046200000000000012, 0.043450000000000009, 0.03685, 0.03685, 0.0374,
    0.037950000000000005, 0.038500000000000006, 0.0396, 0.041800000000000004,
    0.044550000000000006, 0.046200000000000012, 0.043450000000000009, 0.03685,
    0.03685, 0.0374, 0.037950000000000005, 0.039000000000000007,
    0.040100000000000004, 0.041800000000000004, 0.044050000000000006,
    0.046700000000000012, 0.043450000000000009, 0.0363, 0.03685, 0.03685,
    0.038500000000000006, 0.03905, 0.0396, 0.042350000000000006,
    0.044000000000000011, 0.046200000000000012, 0.043450000000000009, 0.0368,
    0.03685, 0.03735, 0.038000000000000006, 0.03855, 0.0396,
    0.041850000000000005, 0.044500000000000012, 0.046200000000000012,
    0.043450000000000009, 0.0368, 0.03685, 0.03735, 0.038000000000000006,
    0.03905, 0.040100000000000004, 0.041850000000000005, 0.044000000000000011,
    0.046700000000000012, 0.043450000000000009, 0.03635, 0.03685, 0.0369,
    0.038450000000000005, 0.039000000000000007, 0.0396, 0.042300000000000004,
    0.044050000000000006, 0.046200000000000012, 0.043450000000000009, 0.03685,
    0.03685, 0.0374, 0.037950000000000005, 0.038500000000000006, 0.0396,
    0.041800000000000004, 0.044550000000000006, 0.046200000000000012,
    0.043450000000000009, 0.03685, 0.03685, 0.0374, 0.037950000000000005,
    0.039000000000000007, 0.040100000000000004, 0.041800000000000004,
    0.044050000000000006, 0.046700000000000012, 0.043450000000000009, 0.03635,
    0.03685, 0.0369, 0.038450000000000005, 0.03905, 0.039650000000000005,
    0.042300000000000004, 0.044000000000000011, 0.046250000000000013,
    0.043450000000000009, 0.03685, 0.03685, 0.0374, 0.037950000000000005,
    0.03855, 0.039650000000000005, 0.041800000000000004, 0.044500000000000012,
    0.046250000000000013, 0.043450000000000009, 0.03685, 0.03685, 0.0374,
    0.037950000000000005, 0.03905, 0.040150000000000005, 0.041800000000000004,
    0.044000000000000011, 0.046750000000000014, 0.043450000000000009 }
} ;

cal_autocodePlantParams_envParams envParams = {
  { 0.0, 0.0, 9.81 },
  -87.6767064830923,
  42.0569355774686,
  182.0,
  2026.6657534246576
} ;

cal_autocodePlantParams_icParams icParams = {
  { 0.0, 0.0, 0.0 },

  { 0.0, 0.0, 0.0 },

  { 0.0, 0.0, 0.0 },

  { 1.0, 0.1, 0.0 },

  { -2.1415926535897931, 1.4707963267948971, 3.1415926535897927 }
} ;

cal_autocodePlantParams_motorParams motorParams = {
  { 65U, 101U, 114U, 111U, 84U, 101U, 99U, 104U, 95U, 77U, 49U, 51U, 49U, 53U,
    87U, 46U, 99U, 115U, 118U },
  20.0,

  { 0.116, 0.349, 0.582, 0.816, 1.049, 1.282, 1.516, 1.749, 1.982, 2.216, 2.449,
    2.682, 2.916, 3.149, 3.382, 3.616, 3.849, 4.082, 4.316, 4.549, 4.782, 5.016,
    5.249, 5.482, 5.716, 5.949, 1728.683, 1673.336, 1686.81, 1696.068, 1663.167,
    1631.243, 1620.471, 1619.702, 1621.042, 1615.32, 1567.089, 1493.722,
    1420.079, 1358.66, 1292.507, 1224.806, 1171.995, 928.809, 577.949, 395.445,
    314.006, 228.273, 159.803, 118.348, 109.782, 0.0 },

  { 0.116, 0.349, 0.582, 0.816, 1.049, 1.282, 1.516, 1.749, 1.982, 2.216, 2.449,
    2.682, 2.916, 3.149, 3.382, 3.616, 3.849, 4.082, 4.316, 4.549, 4.782, 5.016,
    5.249, 5.482, 5.716, 5.949 },
  1.0,

  { 1728.683, 1673.336, 1686.81, 1696.068, 1663.167, 1631.243, 1620.471,
    1619.702, 1621.042, 1615.32, 1567.089, 1493.722, 1420.079, 1358.66, 1292.507,
    1224.806, 1171.995, 928.809, 577.949, 395.445, 314.006, 228.273, 159.803,
    118.348, 109.782, 0.0 }
} ;

cal_autocodePlantParams_sensorParams sensorParams = {
  { 0.0, 0.0, 0.0 },
  0.99995,

  { -0.010560345194968269, -0.010560345194968269, -0.010560345194968269 },

  { 0.0019619999999999998, 0.0019619999999999998, 0.0019619999999999998 },

  { 3.8495402393075655e-8, 3.8495402393075655e-8, 3.8495402393075655e-8 },

  { 5.413280625e-7, 5.413280625e-7, 5.413280625e-7 },

  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 },
  0.01,
  0.99995,

  { 0.009, 0.009, 0.009 },

  { 0.0004848, 0.0004848, 0.0004848 },

  { 0.0078050894186661593, 0.0078050894186661593, 0.0078050894186661593 },

  { 3.7301556250000008e-11, 3.7301556250000008e-11, 3.7301556250000008e-11 },

  { 2.3503691597184066e-9, 2.3503691597184066e-9, 2.3503691597184066e-9 },

  { 8.8971600469076642e-5, 0.0, 0.0, 0.0, 8.8971600469076642e-5, 0.0, 0.0, 0.0,
    8.8971600469076642e-5 },

  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 },
  0.01,

  { 1200.0, -800.0, 500.0 },
  0.01,

  { 196.0, 196.0, 196.0 },
  40.0,
  0.99998,
  0.01,

  { 1.08, 0.04, -0.03, 0.05, 0.92999999999999994, 0.02, -0.03, 0.02, 1.05 },
  0.0004,
  0.14400144001934431,
  0.1,
  15.0,
  1.0,
  0.1
} ;

cal_autocodePlantParams_simParams simParams = {
  0.01
} ;

cal_autocodePlantParams_vehicleParams vehicleParams = {
  2.75,
  17.5,
  0.018,
  1.8117856235712473,

  { 0.053, 0.0, 0.0, 0.0, 8.41, 0.0, 0.0, 0.0, 8.41 }
} ;

cal_autocodePlantParams_windParams windParams = {
  false,
  false,

  { 5.0, 0.0, 0.0 },
  5.0,
  180.0
} ;

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
