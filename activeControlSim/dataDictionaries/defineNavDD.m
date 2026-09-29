function N = defineNavDD()
%DEFINENAVDD  Assemble the nav model's parameters into one
%   struct, grouped by field. No Simulink calls here -- just data.
%

N.navControl.useNav_b = true;
N.navControl.dt_s = 1/100;
P = definePlantDD();
e = P.icParams.eul_rad;                          % [phi theta psi]
N.navControl.q0_na = angle2quat(e(3), e(2), e(1)); % scalar-first, body<-NED

N.navStates.debounce_s = 0.1;
N.navStates.boostThreshold_mps2 = 50;
N.navStates.coastThresholdxAcc_mps2 = 0; 
N.navStates.coastThresholdAlt_m = 200;
N.navStates.controlTresholdPitchYaw_rad = 0.3;
N.navStates.controlTresholdPitchYawRate_rps = 1.0;

end
