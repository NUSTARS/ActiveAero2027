function N = defineNavDD()
%DEFINENAVDD  Assemble the nav model's parameters into one
%   struct, grouped by field. No Simulink calls here -- just data.
%

N.navControl.useNav_b = true;
N.navControl.useKalman_b = false;
N.navControl.dt_s = 1/100;
N.navControl.q0_na = [0.7071, 0, 0.7071, 0];
N.navControl.eulerCalcPreRotation = [0.7071, 0, -0.7071, 0];
N.navControl.eulerCalcPreRotationInv = quatinv(N.navControl.eulerCalcPreRotation);
N.navControl.gravityNed_mps2 = [0, 0, 9.81];

N.navStates.debounce_s = 0.1;
N.navStates.boostThreshold_mps2 = 50;
N.navStates.coastThresholdxAcc_mps2 = 0; 
N.navStates.coastThresholdAlt_m = 200;
N.navStates.controlTresholdPitchYaw_rad = 0.4;
N.navStates.controlTresholdPitchYawRate_rps = 1.0;

N.navComp.compGain = 0.99;

end
