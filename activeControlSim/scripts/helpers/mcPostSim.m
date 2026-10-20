function s = mcPostSim(simOut)
%MCPOSTSIM  PostSimFcn for runMonteCarlo.m: reduce one run's output to
%   summary metrics, so parsim workers don't ship full logged timeseries
%   back to the client.
%
%   Each field of the returned struct becomes a property of that run's
%   Simulink.SimulationOutput (e.g. out(i).apogee_m), replacing the
%   logged data. ErrorMessage and SimulationMetadata are kept.
%
%   Lives in its own file (not a local function in runMonteCarlo.m) so
%   parsim workers can resolve it from the path.
%
%   METRICS (all scalars; NaN if the run failed or the signal isn't logged)
%     apogee_m
%     activeControlTime_s   time spent in flightMode.ACTIVE (controller on)
%     <group><Axis>ErrAvg_pct, <group><Axis>ErrMax_pct
%       mean and max of |error| over the controlled flight phase
%       (flightMode.ACTIVE), one pair per axis, as a percentage of the
%       reference signal's range (max - min over that phase; peak |value|
%       if the reference is constant). Same quantities
%       as the plotRocketTrajectory.m evaluation figures:
%         ol        outer loop: launch-frame Euler angle - guidance command
%                   (command taken as vertical, i.e. 0 in the launch
%                   frame), relative to the actual angle's range
%                   Pitch/Yaw/Roll
%         il        inner loop: outer-loop rate command - true body rate,
%                   relative to the rate command's range
%                   Pitch/Yaw/Roll (q/r/p)
%         navEul    nav - true launch-frame Euler angle, Pitch/Yaw/Roll
%         navRate   nav - true body rate, P/Q/R
%         navAcc    nav - true body accel, X/Y/Z
%         navPos    nav - true position, North/East/Up
%         navVel    nav - true velocity, North/East/Up
%         navAccelBias  nav - true accel bias, X/Y/Z
%         navGyroBias   nav - true gyro bias, X/Y/Z
%       nav errors are relative to the true signal's range.
%       e.g. s.olPitchErrMax_pct, s.navPosUpErrAvg_pct

% {prefix, axis labels}
groups = {
    'ol',           {'Pitch','Yaw','Roll'}
    'il',           {'Pitch','Yaw','Roll'}
    'navEul',       {'Pitch','Yaw','Roll'}
    'navRate',      {'P','Q','R'}
    'navAcc',       {'X','Y','Z'}
    'navPos',       {'North','East','Up'}
    'navVel',       {'North','East','Up'}
    'navAccelBias', {'X','Y','Z'}
    'navGyroBias',  {'X','Y','Z'}
};

s.apogee_m = NaN;
s.activeControlTime_s = NaN;
for g = 1:size(groups, 1)
    s = addErrMetrics_local(s, groups(g,:), nan(1, 3));
end

if ~isempty(simOut.ErrorMessage)
    return
end

posNed_m = simOut.simout.plant_bus.eom_bus.posNed_m.Data;
s.apogee_m = -min(posNed_m(:,3));

r = extractSimRun(simOut, 'mcRun', [1;0;0]);

% Launch-frame 3-2-1 Euler angles, as in plotRocketTrajectory.m: L =
% [Up, East, North], so a vertical rocket reads (0,0,0).
q_Ln = [sqrt(2)/2, 0, sqrt(2)/2, 0];
qEst = r.qEst_na;
if all(isnan(qEst(:)))
    qEst = euler3212quat_local(r.eulEst_rad);
end
eulL_deg    = quat2euler321_local(quatmult_local(quatconj_local(q_Ln), r.q_na));
eulLEst_deg = quat2euler321_local(quatmult_local(quatconj_local(q_Ln), qEst));

% [phi theta psi] / [p q r] columns -> Pitch/Yaw/Roll
pyr = [2, 3, 1];

wrap180 = @(a) mod(a + 180, 360) - 180;

% {error, reference signal the error is normalized by}
err = {
    wrap180(eulL_deg(:,pyr)),                           eulL_deg(:,pyr)          % ol
    r.outerRateCmd_rps - r.omega_body(:,pyr),           r.outerRateCmd_rps       % il
    wrap180(eulLEst_deg(:,pyr) - eulL_deg(:,pyr)),      eulL_deg(:,pyr)          % navEul
    r.omegaEst_rps - r.omega_body,                      r.omega_body             % navRate
    r.accEst_mps2 - r.acc_body,                         r.acc_body               % navAcc
    r.posEst_plot - r.pos_plot,                         r.pos_plot               % navPos
    r.velEst_plot - r.vel_plot,                         r.vel_plot               % navVel
    r.accelBiasEst_mps2 - r.accelBiasTrue_mps2,         r.accelBiasTrue_mps2     % navAccelBias
    r.gyroBiasEst_rps - r.gyroBiasTrue_rps,             r.gyroBiasTrue_rps       % navGyroBias
};

% Controlled flight phase: the controller only runs while the nav flight
% mode is ACTIVE, so both the errors and the ranges they're normalized
% by cover just those samples. No ACTIVE samples (or flight mode not
% logged) leaves the error metrics NaN.
active = r.flightMode_int == double(flightMode.ACTIVE);
if ~all(isnan(r.flightMode_int))
    s.activeControlTime_s = sum(diff(r.t) .* active(1:end-1));
end
if ~any(active)
    return
end

for g = 1:size(groups, 1)
    s = addErrMetrics_local(s, groups(g,:), ...
        pctOfRange_local(err{g,1}(active,:), err{g,2}(active,:)));
end

end

% ======================================================================
function pct = pctOfRange_local(err, ref)
    % err (Nx3) as a percentage of each ref column's range (max - min).
    % A constant ref column (range 0, e.g. a fixed true bias) falls back
    % to its peak |value|; an all-zero/all-NaN column gives NaN.
    scale = max(ref, [], 1, 'omitnan') - min(ref, [], 1, 'omitnan');
    peak  = max(abs(ref), [], 1, 'omitnan');
    flat  = ~(scale > 1e-9 * max(peak, 1));
    scale(flat) = peak(flat);
    scale(~(scale > 0)) = NaN;
    pct = 100 * err ./ scale;
end

% ======================================================================
function s = addErrMetrics_local(s, group, err)
    % Add <prefix><Axis>ErrAvg_pct / ErrMax_pct fields from the columns
    % of err (Nx3, [%]). max() of an all-NaN column stays NaN.
    [prefix, lbls] = group{:};
    for j = 1:3
        e = abs(err(:,j));
        s.(sprintf('%s%sErrAvg_pct', prefix, lbls{j})) = mean(e, 'omitnan');
        s.(sprintf('%s%sErrMax_pct', prefix, lbls{j})) = max(e, [], 'omitnan');
    end
end

% ======================================================================
function eul_deg = quat2euler321_local(q)
    % [phi theta psi] (deg) from a scalar-first quaternion, body<-reference.
    q0 = q(:,1); q1 = q(:,2); q2 = q(:,3); q3 = q(:,4);
    roll  = atan2(2*(q0.*q1 + q2.*q3), 1 - 2*(q1.^2 + q2.^2));
    pitch = asin(max(-1, min(1, 2*(q0.*q2 - q3.*q1))));
    yaw   = atan2(2*(q0.*q3 + q1.*q2), 1 - 2*(q2.^2 + q3.^2));
    eul_deg = rad2deg([roll, pitch, yaw]);
end

% ======================================================================
function q = euler3212quat_local(eul_rad)
    % Inverse of quat2euler321_local: [phi theta psi] (rad) -> quaternion.
    h = eul_rad / 2;
    cf = cos(h(:,1)); sf = sin(h(:,1));
    ct = cos(h(:,2)); st = sin(h(:,2));
    cp = cos(h(:,3)); sp = sin(h(:,3));
    q = [cf.*ct.*cp + sf.*st.*sp, ...
         sf.*ct.*cp - cf.*st.*sp, ...
         cf.*st.*cp + sf.*ct.*sp, ...
         cf.*ct.*sp - sf.*st.*cp];
end

% ======================================================================
function q = quatmult_local(a, b)
    % Hamilton product a (x) b, scalar-first; either input may be 1x4.
    n = max(size(a,1), size(b,1));
    a = repmat(a, n/size(a,1), 1); b = repmat(b, n/size(b,1), 1);
    q = [a(:,1).*b(:,1) - sum(a(:,2:4).*b(:,2:4), 2), ...
         a(:,1).*b(:,2:4) + b(:,1).*a(:,2:4) + cross(a(:,2:4), b(:,2:4), 2)];
end

% ======================================================================
function q = quatconj_local(q)
    q(:,2:4) = -q(:,2:4);
end
