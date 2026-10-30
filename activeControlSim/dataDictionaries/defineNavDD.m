function N = defineNavDD()
%DEFINENAVDD  Assemble the nav model's parameters into one
%   struct, grouped by field. No Simulink calls here -- just data.
%

N.navControl.useNav_b = true;
N.navControl.useKalman_b = false;
N.navControl.dt_s = 1/100;
N.navControl.navIC_bus = struct('qEst_na', [0.7071, 0, 0.7071, 0]);
N.navControl.posNed0_m = [0 0 0];
N.navControl.velNed0_mps = [0 0 0];
N.navControl.eulerCalcPreRotation = [0.707106781187, 0, -0.707106781187, 0];
N.navControl.eulerCalcPreRotationInv = quatinv(N.navControl.eulerCalcPreRotation);
N.navControl.gravityNed_mps2 = [0, 0, 9.81];
N.navControl.rhoConst_kgpm3 = 1.225; 

gyroG = [0.05 0 0; 0 0.05 0; 0 0 0.05];
N.navControl.gyroG = gyroG * 0.01745 / 9.8065;

N.navControl.filterDelay_na = 500;

lat0_deg = 42.0569355774686; % [deg]

N.gpsConversion.M0_m = 6378137*(1-6.69437999014E-3)/(1-6.69437999014E-3*sin(lat0_deg)^2)^1.5;
N.gpsConversion.N0_m = 6378137/(1-6.69437999014E-3*sin(lat0_deg)^2)^0.5;

N.navStates.debounce_s = 0.1;
N.navStates.boostThreshold_mps2 = 12;
N.navStates.coastThresholdxAcc_mps2 = 0; 
N.navStates.coastThresholdAlt_m = 200;
N.navStates.controlTresholdPitchYaw_rad = 1.0;
N.navStates.controlTresholdPitchYawRate_rps = 1.0;

N.navComp.attitudeGain = 0.995;
N.navComp.velGain = 0.7;
N.navComp.posGain = 0.5;

end
