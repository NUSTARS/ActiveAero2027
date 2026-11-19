function C = defineControllerDD()
%DEFINECONTROLLERDD  Assemble the controller model's parameters into one
%   struct, grouped by field. No Simulink calls here -- just data.
%

%% Guidance (attitude commands)
C.guidanceParams.phiCmd_rad   = 0; % [rad] commanded roll angle
C.guidanceParams.thetaCmd_rad = 0.0; % [rad] commanded pitch angle
C.guidanceParams.psiCmd_rad   = 0.0; % [rad] commanded yaw angle

%% Inverse Plant
load('plantTable.mat', 'plantTable')
C.inversePlant.qBreakpoints_Pa = plantTable.dynPressure_Pa;

% Plant G(s) = (b1 s + b0)/(s^2 + a1 s + a0) -> ZOH -> Gd(z) = (c1 z + c0)/(z^2 + d1 z + d0).
% Gd's inverse alone is non-causal (2 zeros, 1 pole). The low-pass Q(z)
% after ZOH has one more pole than zero, so Q/Gd is exactly proper:
%
%   Q(z)/Gd(z) = (q1 z + q0)(z^2 + d1 z + d0) / ((z^2 + e1 z + e0)(c1 z + c0))
%
% 3rd order over 3rd order, no added delay. Stored as one block's
% coefficients (descending powers of z = ascending powers of z^-1),
% normalized so the leading denominator coefficient is 1 (the Discrete
% Transfer Fcn block has "a0 = 1" optimization on). Breakpoints 2 of the
% coefficient lookups must be [1 2 3 4], and Q must NOT also be applied
% as a separate block.
Ts_s = 0.01;
nPts = height(plantTable);

% Low-pass Q (critically damped 2nd order), same at every operating point.
% Kept separately for reference/plots only -- it's already folded into num_na/den_na.
qCutoffFreq = 2*pi*5;   % [rad/s]
qFiltCont = tf(qCutoffFreq^2, [1 2*qCutoffFreq qCutoffFreq^2]);
[qNum, qDen] = tfdata(c2d(qFiltCont, Ts_s, 'zoh'), 'v');   % qNum = [0 q1 q0], qDen = [1 e1 e0]
C.inversePlant.qFiltNum_na = qNum;
C.inversePlant.qFiltDen_na = qDen;

C.inversePlant.num_na = zeros(nPts, 3);
C.inversePlant.den_na = zeros(nPts, 3);
for i = 1:nPts
    % balred leaves a tiny s^2 numerator term (~1e-5..1e-3) = a far RHP
    % zero; after ZOH it lands outside the unit circle and would become an
    % unstable pole of the inverse. Drop it -- the plant is strictly proper.
    numC = plantTable.num(i, :);
    numC(1) = 0;
    dTF = c2d(tf(numC, plantTable.den(i, :)), Ts_s, 'zoh');
    [c, d] = tfdata(dTF, 'v');          % c = [0 c1 c0], d = [1 d1 d0]
    c1 = c(2); c0 = c(3);

    assert(abs(c0 / c1) < 1, 'defineControllerDD:unstableInverse', ...
        'Inverse plant at %.0f Pa is unstable (Gd zero at %.4f).', ...
        plantTable.dynPressure_Pa(i), -c0 / c1);

    %num = conv(qNum(2:3), d);        % (q1 z + q0)(z^2 + d1 z + d0)
    num = d;
    %den = conv(qDen, [c1 c0]);       % (z^2 + e1 z + e0)(c1 z + c0)
    den = [c1 c0 0];
    C.inversePlant.num_na(i, :) = num / den(1);
    C.inversePlant.den_na(i, :) = den / den(1);   % leading 1 required (a0 = 1 optimization)
end

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

C.innerLoopParams.fbkGainBreakpoints_Pa = [0 30e3 75e3];

% C.innerLoopParams.fbkGainPitchYawP_na = 8000*[1.2 0.6 0.4];
% C.innerLoopParams.fbkGainPitchYawI_na = 50000*[1.2 0.6 0.4];
% C.innerLoopParams.fbkGainPitchYawD_na = 0*[1.2 0.6 0.5];
% C.innerLoopParams.fbkGainPitchYawN_na = [10 10 10];
C.innerLoopParams.fbkGainPitchYawP_na = 200*[1.5 1.25 1.0];
C.innerLoopParams.fbkGainPitchYawI_na = 4000*[0.5 0.75 1.0];
C.innerLoopParams.fbkGainPitchYawD_na = 0*[1.5 1.25 1.0];
C.innerLoopParams.fbkGainPitchYawN_na = [1 1 1];

C.innerLoopParams.fbkGainRollP_na = 2.5*[1.1 1.05 1.0];
C.innerLoopParams.fbkGainRollI_na = 10*[2.0 1.2 1.0];
C.innerLoopParams.fbkGainRollD_na = [0 0 0];
C.innerLoopParams.fbkGainRollN_na = [1 1 1];

%% Outer Loop (attitude-loop PID output -> body rate command limits/gains)
% PID gain vectors are ordered [P, I, D, N] to match the PID Gain
% Scheduler block's Demux wiring in pitchYawOuterLoop/rollOuterLoop.
% Placeholder gains -- need tuning against the plant model.
C.outerLoopParams.upRateLimitPitchYawRate_rps2 = 0.5;    % [rad/s^2] max pitch/yaw rate-command slew rate
C.outerLoopParams.loRateLimitPitchYawRate_rps2 = -0.5;   % [rad/s^2] min pitch/yaw rate-command slew rate
C.outerLoopParams.upLimitPitchYawRate_rps      = 0.4;    % [rad/s] max commanded pitch/yaw rate
C.outerLoopParams.loLimitPitchYawRate_rps      = -0.4;   % [rad/s] min commanded pitch/yaw rate
C.outerLoopParams.pitchYawGains                = [2, 1, 0, 1]; % [P, I, D, N] pitch/yaw outer-loop PID gains

C.outerLoopParams.upRateLimitRollRate_rps2 = 5;    % [rad/s^2] max roll rate-command slew rate
C.outerLoopParams.loRateLimitRollRate_rps2 = -5;   % [rad/s^2] min roll rate-command slew rate
C.outerLoopParams.upLimitRollRate_rps      = 2;    % [rad/s] max commanded roll rate
C.outerLoopParams.loLimitRollRate_rps      = -2;   % [rad/s] min commanded roll rate
C.outerLoopParams.rollGains                = [1, 2, 0, 100]; % [P, I, D, N] roll outer-loop PID gains

end
