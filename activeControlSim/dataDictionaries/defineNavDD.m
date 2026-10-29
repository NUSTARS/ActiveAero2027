function N = defineNavDD()
%DEFINENAVDD  Assemble the nav model's parameters into one
%   struct, grouped by field. No Simulink calls here -- just data.
%

N.navControl.useNav_b = true;
N.navControl.useKalman_b = true;
N.navControl.dt_s = 1/100;
N.navControl.navIC_bus = struct('qEst_na', [0.7071, 0, 0.7071, 0]);
N.navControl.posNed0_m = [0 0 0];
N.navControl.velNed0_mps = [0 0 0];
N.navControl.eulerCalcPreRotation = [0.707106781187, 0, -0.707106781187, 0];
N.navControl.eulerCalcPreRotationInv = quatinv(N.navControl.eulerCalcPreRotation);
N.navControl.gravityNed_mps2 = [0, 0, 9.81];
N.navControl.leverIMUtoGNSS_m = [0 0 0];
N.navControl.rhoConst_kgpm3 = 1.225; 
sigDummyQUEST_amin = 5; % [arcmin]
sigDummyQUEST_rad = sigDummyQUEST_amin * 0.0002908; % [rad]
N.navControl.varDummyQUEST_rad = sigDummyQUEST_rad^2 * [1 1 1]; % [rad^2]
sigDummyPosNE_m = 0.1; % [m]
sigDummyPosD_m = 0.2; % [m]
sigDummyVelNE_mps = 0.002; % [mps]
sigDummyVelD_mps = 0.004; % [mps]
N.navControl.varDummyPos_m = [sigDummyPosNE_m^2, sigDummyPosNE_m^2, sigDummyPosD_m^2]; % [m^2]
N.navControl.varDummyVel_mps = [sigDummyVelNE_mps^2, sigDummyVelNE_mps^2, sigDummyVelD_mps^2]; % [m^2/s^2]
gyroG = [0.05 0 0; 0 0.05 0; 0 0 0.05];
N.navControl.gyroG = gyroG * 0.01745 / 9.8065;


N.navControl.filterDelay_na = 500;

N.navStates.debounce_s = 0.1;
N.navStates.boostThreshold_mps2 = 12;
N.navStates.coastThresholdxAcc_mps2 = 0; 
N.navStates.coastThresholdAlt_m = 200;
N.navStates.controlTresholdPitchYaw_rad = 1.0;
N.navStates.controlTresholdPitchYawRate_rps = 1.0;

N.navComp.compGain = 0.995;


end
