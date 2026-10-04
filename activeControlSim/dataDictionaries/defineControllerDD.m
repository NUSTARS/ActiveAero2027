function C = defineControllerDD()
%DEFINECONTROLLERDD  Assemble the controller model's parameters into one
%   struct, grouped by field. No Simulink calls here -- just data.
%

%% Guidance (attitude commands)
C.guidanceParams.phiCmd_rad   = 0; % [rad] commanded roll angle
C.guidanceParams.thetaCmd_rad = 0; % [rad] commanded pitch angle
C.guidanceParams.psiCmd_rad   = 0; % [rad] commanded yaw angle

%% Inner Loop (rate-loop PID output -> fin deflection limits)
% Note: rollInnerLoop currently reuses these same PitchYaw-named limits.
C.innerLoopParams.upRateLimitPitchYaw_dps = 180;  % [deg/s] max fin deflection rate
C.innerLoopParams.loRateLimitPitchYaw_dps = -180; % [deg/s] min fin deflection rate
C.innerLoopParams.upLimitPitchYaw_deg     = 45;   % [deg] max fin deflection angle
C.innerLoopParams.loLimitPitchYaw_deg     = -45;  % [deg] min fin deflection angle

C.innerLoopParams.upRateLimitRoll_dps = 90;  % [deg/s] max fin deflection rate
C.innerLoopParams.loRateLimitRoll_dps = -90; % [deg/s] min fin deflection rate
C.innerLoopParams.upLimitRoll_deg     = 5;   % [deg] max fin deflection angle
C.innerLoopParams.loLimitRoll_deg     = -5;  % [deg] min fin deflection angle

C.innerLoopParams.fbkGainBreakpoints_Pa = [0 5e3 1e5];

% C.innerLoopParams.fbkGainPitchYawP_na = 8000*[1.2 0.6 0.4];
% C.innerLoopParams.fbkGainPitchYawI_na = 50000*[1.2 0.6 0.4];
% C.innerLoopParams.fbkGainPitchYawD_na = 0*[1.2 0.6 0.5];
% C.innerLoopParams.fbkGainPitchYawN_na = [10 10 10];
C.innerLoopParams.fbkGainPitchYawP_na = 3000*[1.2 0.6 0.4];
C.innerLoopParams.fbkGainPitchYawI_na = 45000*[1.2 0.6 0.4];
C.innerLoopParams.fbkGainPitchYawD_na = 0*[1.2 0.6 0.5];
C.innerLoopParams.fbkGainPitchYawN_na = [10 10 10];

C.innerLoopParams.fbkGainRollP_na = 12*[1 0.5 0.3];
C.innerLoopParams.fbkGainRollI_na = 6*[1 0.5 0.3];
C.innerLoopParams.fbkGainRollD_na = [0 0 0];
C.innerLoopParams.fbkGainRollN_na = [1 1 1];

%% Outer Loop (attitude-loop PID output -> body rate command limits/gains)
% PID gain vectors are ordered [P, I, D, N] to match the PID Gain
% Scheduler block's Demux wiring in pitchYawOuterLoop/rollOuterLoop.
% Placeholder gains -- need tuning against the plant model.
C.outerLoopParams.upRateLimitPitchYawRate_rps2 = 0.5;    % [rad/s^2] max pitch/yaw rate-command slew rate
C.outerLoopParams.loRateLimitPitchYawRate_rps2 = -0.5;   % [rad/s^2] min pitch/yaw rate-command slew rate
C.outerLoopParams.upLimitPitchYawRate_rps      = 0.05;    % [rad/s] max commanded pitch/yaw rate
C.outerLoopParams.loLimitPitchYawRate_rps      = -0.05;   % [rad/s] min commanded pitch/yaw rate
C.outerLoopParams.pitchYawGains                = [2, 0.5, 0, 1]; % [P, I, D, N] pitch/yaw outer-loop PID gains

C.outerLoopParams.upRateLimitRollRate_rps2 = 5;    % [rad/s^2] max roll rate-command slew rate
C.outerLoopParams.loRateLimitRollRate_rps2 = -5;   % [rad/s^2] min roll rate-command slew rate
C.outerLoopParams.upLimitRollRate_rps      = 2;    % [rad/s] max commanded roll rate
C.outerLoopParams.loLimitRollRate_rps      = -2;   % [rad/s] min commanded roll rate
C.outerLoopParams.rollGains                = [4, 3, 0, 100]; % [P, I, D, N] roll outer-loop PID gains

end
