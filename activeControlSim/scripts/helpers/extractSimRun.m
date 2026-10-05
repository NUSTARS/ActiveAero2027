function r = extractSimRun(out, label, forwardAxis)
%EXTRACTSIMRUN  Pull one run's data out of a Simulink sim output and
%   derive the plotted/animated quantities (tilt/roll/nose/velocity in
%   NED, etc.). Shared by plotRocketTrajectory.m and
%   animateRocketTrajectory.m so both stay in sync with the model's
%   logging structure.
%
%   r = extractSimRun(out, label, forwardAxis)
%     out          a Simulink.SimulationOutput (or a plain struct loaded
%                  from a .mat file) with out.simout as nested bus
%                  structs:
%                    simout.plant_bus.eom_bus
%                      posNed_m     Nx3   position [north, east, down] [m]
%                      q_na         Nx4   quaternion [q0 q1 q2 q3]
%                                         (scalar-first, body<-NED)
%                      velBdy_mps   Nx3   body-axis velocity   [m/s]
%                      wBdy_rps     Nx3   body-axis angular rate
%                                         [p, q, r]   [rad/s]
%                    simout.plant_bus.aero_bus.body_bus
%                      aoa_deg      Nx1   total angle of attack, as
%                                         logged by the model
%                    simout.navigation_bus   optional
%                      {phi,theta,psi}Est_rad  Nx1 estimated 3-2-1 Euler
%                                         angles [rad]
%                      {p,q,r}Est_rps     Nx1 estimated body rates [rad/s]
%                      {x,y,z}AccEst_mps2 Nx1 estimated body accel [m/s^2]
%                      {x,y,z}PosEst_m    Nx1 estimated NED position [m]
%                      {x,y,z}VelEst_mps  Nx1 estimated NED velocity [m/s]
%                      qEst_na            Nx4 estimated quaternion
%                      flightMode_enum    Nx1 flightMode enum
%                      accelBias_mps2     Nx3 estimated accel bias [m/s^2]
%                      gyroBias_rps       Nx3 estimated gyro bias  [rad/s]
%                    simout.sensor_bus.truth_bus   optional -- found by
%                                         leaf name anywhere under it,
%                                         so sub-bus names don't matter
%                      accBiasTrue        Nx3 true accel bias [m/s^2]
%                      gyroBias           Nx3 true gyro bias  [rad/s]
%                    simout.controller_bus   optional -- older logs
%                                         without it read back as zeros
%                                         (see below for defaults)
%                      control_deg  Nx4   commanded fin deflection
%                                         [fin1 fin2 fin3 fin4] [deg]
%                      outerLoop_bus.{pitch,yaw,roll}OuterLoop_bus
%                        rateCmd_rps    Nx1 commanded body rate [rad/s]
%                        rateLimited_b  Nx1 rate limiter active [bool]
%                        saturated_b    Nx1 saturation active   [bool]
%                      innerLoop_bus.{pitch,yaw,roll}InnerLoop_bus
%                        control_deg      Nx1 per-axis fin command [deg]
%                        controlMoment_Nm Nx1 commanded moment    [N*m]
%                        rateLimted_b     Nx1 rate limiter active [bool]
%                        saturated_b      Nx1 saturation active   [bool]
%     label        run label, used in error messages and for run legends
%     forwardAxis  3x1 unit vector, the nose/forward direction expressed
%                  in BODY axes (e.g. [1;0;0])
%
%   Returns a struct r with fields:
%     label, t, pos_plot, vel_plot, nose_plot (all in plot frame: north,
%     east, up), tilt_deg, roll_deg, aoa_deg, omega_body (rad/s), q_na,
%     eulEst_rad (Nx3 nav-estimated [phi theta psi], 3-2-1, NaN if not
%     logged), omegaEst_rps (Nx3 nav-estimated body rates [p q r], NaN
%     if not logged), qEst_na (Nx4 nav-estimated quaternion, sign-matched
%     to q_na, NaN if not logged), acc_body (Nx3 true body-axis
%     acceleration [m/s^2]), accEst_mps2 (Nx3 nav-estimated body-axis
%     acceleration, NaN if not logged), posEst_plot / velEst_plot (Nx3
%     nav-estimated position [m] / velocity [m/s], plot frame like
%     pos_plot/vel_plot, NaN if not logged), accelBiasEst_mps2 /
%     gyroBiasEst_rps (Nx3 nav-estimated sensor biases, NaN if not
%     logged), accelBiasTrue_mps2 / gyroBiasTrue_rps (Nx3 true sensor
%     biases from sensor_bus.truth_bus, NaN if not logged), flightMode_int (Nx1 nav flight mode as
%     its flightMode enum integer value, NaN if not logged),
%     control_deg (Nx4, zeros if not logged),
%     outerRateCmd_rps, outerRateLimited_b, outerSaturated_b (Nx3,
%     columns [pitch yaw roll], zeros if not logged),
%     innerControl_deg, innerMoment_Nm, innerRateLimited_b,
%     innerSaturated_b (Nx3, columns [pitch yaw roll], zeros if not
%     logged)
%
%   NOTES
%     - Position/velocity are NED; "down" is flipped in pos_plot/vel_plot
%       so altitude increases upward.
%     - velBdy_mps is body-axis velocity: at t=0 it equals the 6DOF
%       block's Vm_0 IC directly, with no rotation applied. It is
%       rotated into NED here (via q_na) for plotting/animation, which
%       need NED.

try
    simout = out.simout;
catch
    error('extractSimRun:noSimout', ...
        '%s: out.simout not found -- out must be a Simulink sim output.', label);
end

if ~isstruct(simout) || ~isfield(simout, 'plant_bus')
    error('extractSimRun:badSimout', ...
        '%s: simout must have field plant_bus (a bus struct).', label);
end
plant = simout.plant_bus;

requiredBuses = {'eom_bus','aero_bus'};
if ~all(isfield(plant, requiredBuses))
    error('extractSimRun:badPlant', ...
        '%s: simout.plant_bus must have fields eom_bus, aero_bus (each a bus struct).', label);
end

eom  = plant.eom_bus;

requiredEom = {'velBdy_mps','posNed_m','q_na','wBdy_rps', 'wDotBdy_rps2', 'accBdy_mps2'};
if ~all(isfield(eom, requiredEom))
    error('extractSimRun:badEom', ...
        '%s: simout.plant_bus.eom_bus must have fields velBdy_mps, posNed_m, q_na, wBdy_rps (each a timeseriesp).', label);
end
if ~isfield(plant.aero_bus, 'body_bus') || ~isfield(plant.aero_bus.body_bus, 'aoa_deg')
    error('extractSimRun:badAero', ...
        '%s: simout.plant_bus.aero_bus.body_bus must have field aoa_deg (a timeseries).', label);
end
aero = plant.aero_bus.body_bus;

ts_vel   = eom.velBdy_mps;
ts_pos   = eom.posNed_m;
ts_q     = eom.q_na;
ts_aoa   = aero.aoa_deg;
ts_omega = eom.wBdy_rps;

t = ts_vel.Time(:);
N = numel(t);

vel_body   = alignRows_local(ts_vel.Data, N, 3);
pos_NED    = alignRows_local(ts_pos.Data, N, 3);
q_na       = alignRows_local(ts_q.Data, N, 4);
aoa_deg    = alignRows_local(ts_aoa.Data, N, 1);
omega_body = alignRows_local(ts_omega.Data, N, 3);

% Guard against slightly mismatched time vectors across signals (can
% happen with variable-step solvers).
if numel(ts_pos.Time) ~= N || any(ts_pos.Time(:) ~= t)
    pos_NED = alignRows_local(resample(ts_pos, t).Data, N, 3);
end
if numel(ts_q.Time) ~= N || any(ts_q.Time(:) ~= t)
    q_na = alignRows_local(resample(ts_q, t).Data, N, 4);
end
if numel(ts_aoa.Time) ~= N || any(ts_aoa.Time(:) ~= t)
    aoa_deg = alignRows_local(resample(ts_aoa, t).Data, N, 1);
end
if numel(ts_omega.Time) ~= N || any(ts_omega.Time(:) ~= t)
    omega_body = alignRows_local(resample(ts_omega, t).Data, N, 3);
end

if isfield(simout, 'controller_bus') && isfield(simout.controller_bus, 'control_deg')
    control_deg = extractHeld_local(simout.controller_bus.control_deg, t, N, 4);
else
    control_deg = zeros(N, 4);
end

if isfield(simout, 'controller_bus')
    ctrl = simout.controller_bus;
    outer = ctrl.outerLoop_bus;
    inner = ctrl.innerLoop_bus;

    outerRateCmd_rps   = extractAxis3_local(outer, 'rateCmd_rps',   t, N);
    outerRateLimited_b = extractAxis3_local(outer, 'rateLimited_b', t, N);
    outerSaturated_b   = extractAxis3_local(outer, 'saturated_b',   t, N);

    innerControl_deg   = extractAxis3_local(inner, 'control_deg',      t, N);
    innerMoment_Nm      = extractAxis3_local(inner, 'controlMoment_Nm', t, N);
    innerRateLimited_b  = extractAxis3_local(inner, 'rateLimted_b',     t, N);
    innerSaturated_b    = extractAxis3_local(inner, 'saturated_b',      t, N);
else
    outerRateCmd_rps   = zeros(N, 3);
    outerRateLimited_b = zeros(N, 3);
    outerSaturated_b   = zeros(N, 3);
    innerControl_deg   = zeros(N, 3);
    innerMoment_Nm      = zeros(N, 3);
    innerRateLimited_b  = zeros(N, 3);
    innerSaturated_b    = zeros(N, 3);
end

% Navigation estimate of the Euler angles -- what the controller actually
% tracks against. NaN (plots as nothing) for older logs without it.
if isfield(simout, 'navigation_bus')
    nav = simout.navigation_bus;
    eulEst_rad = [extractHeld_local(nav.phiEst_rad,   t, N, 1), ...
                  extractHeld_local(nav.thetaEst_rad, t, N, 1), ...
                  extractHeld_local(nav.psiEst_rad,   t, N, 1)];
    omegaEst_rps = [extractHeld_local(nav.pEst_rps, t, N, 1), ...
                    extractHeld_local(nav.qEst_rps, t, N, 1), ...
                    extractHeld_local(nav.rEst_rps, t, N, 1)];
else
    eulEst_rad   = nan(N, 3);
    omegaEst_rps = nan(N, 3);
end
% The nav bus names its quaternion qEst_na; older logs used q_na.
qEst_na = nan(N, 4);
if isfield(simout, 'navigation_bus')
    for qField = {'qEst_na', 'q_na'}
        if isfield(simout.navigation_bus, qField{1})
            qEst_na = extractHeld_local(simout.navigation_bus.(qField{1}), t, N, 4);
            break;
        end
    end
end

% Body-axis acceleration: truth from the EOM, estimate from the nav bus
% (NaN if not logged).
acc_body = extractHeld_local(eom.accBdy_mps2, t, N, 3);
if isfield(simout, 'navigation_bus') && isfield(simout.navigation_bus, 'xAccEst_mps2')
    nav = simout.navigation_bus;
    accEst_mps2 = [extractHeld_local(nav.xAccEst_mps2, t, N, 1), ...
                   extractHeld_local(nav.yAccEst_mps2, t, N, 1), ...
                   extractHeld_local(nav.zAccEst_mps2, t, N, 1)];
else
    accEst_mps2 = nan(N, 3);
end

% Position/velocity estimate from the nav bus, NED like posNed_m (NaN if
% not logged).
posEst_NED = nan(N, 3);
velEst_NED = nan(N, 3);
if isfield(simout, 'navigation_bus') && isfield(simout.navigation_bus, 'xPosEst_m')
    nav = simout.navigation_bus;
    posEst_NED = [extractHeld_local(nav.xPosEst_m, t, N, 1), ...
                  extractHeld_local(nav.yPosEst_m, t, N, 1), ...
                  extractHeld_local(nav.zPosEst_m, t, N, 1)];
end
if isfield(simout, 'navigation_bus') && isfield(simout.navigation_bus, 'xVelEst_mps')
    nav = simout.navigation_bus;
    velEst_NED = [extractHeld_local(nav.xVelEst_mps, t, N, 1), ...
                  extractHeld_local(nav.yVelEst_mps, t, N, 1), ...
                  extractHeld_local(nav.zVelEst_mps, t, N, 1)];
end

% Sensor biases: estimate from the nav bus, truth from the sensor model's
% truth_bus (NaN if not logged).
accelBiasEst_mps2 = nan(N, 3);
gyroBiasEst_rps   = nan(N, 3);
if isfield(simout, 'navigation_bus')
    nav = simout.navigation_bus;
    if isfield(nav, 'accelBias_mps2')
        accelBiasEst_mps2 = extractHeld_local(nav.accelBias_mps2, t, N, 3);
    end
    if isfield(nav, 'gyroBias_rps')
        gyroBiasEst_rps = extractHeld_local(nav.gyroBias_rps, t, N, 3);
    end
end
accelBiasTrue_mps2 = nan(N, 3);
gyroBiasTrue_rps   = nan(N, 3);
if isfield(simout, 'sensor_bus') && isfield(simout.sensor_bus, 'truth_bus')
    ts_accBias = findLeaf_local(simout.sensor_bus.truth_bus, 'accBiasTrue');
    if ~isempty(ts_accBias)
        accelBiasTrue_mps2 = extractHeld_local(ts_accBias, t, N, 3);
    end
    ts_gyroBias = findLeaf_local(simout.sensor_bus.truth_bus, 'gyroBias');
    if ~isempty(ts_gyroBias)
        gyroBiasTrue_rps = extractHeld_local(ts_gyroBias, t, N, 3);
    end
end

% Flight mode from the nav state machine, as its integer value (see
% models/navigation/flightMode.m). NaN if not logged.
if isfield(simout, 'navigation_bus') && isfield(simout.navigation_bus, 'flightMode_enum')
    ts_mode = simout.navigation_bus.flightMode_enum;
    % Enum data can't be resampled directly; convert to double and
    % zero-order hold it onto t, since it's a discrete state.
    ts_mode = timeseries(double(squeeze(ts_mode.Data)), ts_mode.Time);
    ts_mode = setinterpmethod(ts_mode, 'zoh');
    flightMode_int = extractHeld_local(ts_mode, t, N, 1);
else
    flightMode_int = nan(N, 1);
end

q_na = q_na ./ vecnorm(q_na, 2, 2);

% q and -q are the same attitude; flip the estimate onto the truth's
% hemisphere so the overlaid traces don't jump by sign alone.
flipSign = sum(qEst_na .* q_na, 2) < 0;
qEst_na(flipSign,:) = -qEst_na(flipSign,:);

% ---------------------------------------------------------- derived signals
fwd_body = forwardAxis(:);

world_north = [1;0;0];   % fixed NED reference for "zero roll"

% Reference body axis for measuring roll: derived from the INITIAL
% attitude so that roll always starts at 0deg, rather than picking some
% fixed body axis (e.g. body Y) that lands at an arbitrary offset (e.g.
% -90deg) depending on the vehicle's initial orientation.
R_bn1 = quat2dcm_local(q_na(1,:));
R_nb1 = R_bn1';
nose1_NED = (R_nb1 * fwd_body)';
right1_NED = cross(nose1_NED, world_north');
if norm(right1_NED) < 1e-6
    right1_NED = cross(nose1_NED, [0,1,0]);
end
right1_NED = right1_NED / norm(right1_NED);
up1_NED = cross(right1_NED, nose1_NED);
ref_body = R_bn1 * up1_NED';
ref_body = ref_body / norm(ref_body);

roll_deg = zeros(N,1);   % spin about the nose axis, deg
nose_NED = zeros(N,3);   % body forward-axis expressed in NED
vel_NED  = zeros(N,3);   % body velocity rotated into NED, for plotting

for k = 1:N
    R_bn = quat2dcm_local(q_na(k,:));   % body <- NED
    R_nb = R_bn';                       % body -> NED

    nose_NED(k,:) = (R_nb * fwd_body)';
    vel_NED(k,:)  = (R_nb * vel_body(k,:)')';

    % Roll about the nose, measured against a local frame built from a
    % fixed world reference (North) rather than a 321-Euler sequence --
    % the latter has a coordinate singularity (gimbal lock) exactly at
    % 90deg tilt, which a straight-up rocket tipping over at apogee hits
    % directly, causing a spurious discontinuity in the roll trace.
    ref_NED = (R_nb * ref_body)';
    right_NED = cross(nose_NED(k,:), world_north');
    if norm(right_NED) < 1e-6   % nose ~parallel to North; fall back
        right_NED = cross(nose_NED(k,:), [0,1,0]);
    end
    right_NED = right_NED / norm(right_NED);
    up_NED_local = cross(right_NED, nose_NED(k,:));
    roll_deg(k) = rad2deg(atan2(dot(ref_NED, right_NED), dot(ref_NED, up_NED_local)));
end

% Tilt from vertical: angle between the nose axis and local up. More
% intuitive than separate pitch/yaw for an axisymmetric rocket, where
% only "how far off vertical" and "which way it's spinning" matter.
up_NED = [0;0;-1];   % unit "up" vector expressed in NED
tilt_deg = rad2deg(acos(max(-1, min(1, nose_NED * up_NED))));

% NED -> plot frame (north, east, up)
toPlot = @(v) [v(:,1), v(:,2), -v(:,3)];

r = struct( ...
    'label',     label, ...
    't',         t, ...
    'pos_plot',  toPlot(pos_NED), ...
    'vel_plot',  toPlot(vel_NED), ...
    'nose_plot', toPlot(nose_NED), ...
    'tilt_deg',  tilt_deg, ...
    'roll_deg',  roll_deg, ...
    'aoa_deg',   aoa_deg, ...
    'omega_body', omega_body, ...
    'q_na',      q_na, ...
    'eulEst_rad', eulEst_rad, ...
    'omegaEst_rps', omegaEst_rps, ...
    'qEst_na',   qEst_na, ...
    'acc_body',  acc_body, ...
    'accEst_mps2', accEst_mps2, ...
    'posEst_plot', toPlot(posEst_NED), ...
    'velEst_plot', toPlot(velEst_NED), ...
    'accelBiasEst_mps2',  accelBiasEst_mps2, ...
    'gyroBiasEst_rps',    gyroBiasEst_rps, ...
    'accelBiasTrue_mps2', accelBiasTrue_mps2, ...
    'gyroBiasTrue_rps',   gyroBiasTrue_rps, ...
    'flightMode_int', flightMode_int, ...
    'control_deg', control_deg, ...
    'outerRateCmd_rps',   outerRateCmd_rps, ...
    'outerRateLimited_b', outerRateLimited_b, ...
    'outerSaturated_b',   outerSaturated_b, ...
    'innerControl_deg',   innerControl_deg, ...
    'innerMoment_Nm',     innerMoment_Nm, ...
    'innerRateLimited_b', innerRateLimited_b, ...
    'innerSaturated_b',   innerSaturated_b);
end

% ==========================================================================
function out = alignRows_local(data, N, ncols)
    % squeeze() on a logged timeseries can leave data as Nxncols OR
    % ncolsxN depending on how the signal was dimensioned in Simulink. A
    % blind reshape(data,N,ncols) does not transpose -- it just re-reads
    % memory linearly, silently scrambling rows/columns when the
    % orientation is wrong. Check shape explicitly instead.
    data = squeeze(data);
    if isvector(data)
        data = data(:)';
    end
    if size(data,1) == N && size(data,2) == ncols
        out = data;
    elseif size(data,2) == N && size(data,1) == ncols
        out = data';
    else
        error('alignRows_local:shape', ...
            'Expected data shaped %dx%d or %dx%d, got %s.', ...
            N, ncols, ncols, N, mat2str(size(data)));
    end
end

% ==========================================================================
function out3 = extractAxis3_local(loopBus, fieldName, t, N)
    % Pull `fieldName` (a scalar-per-sample timeseries) out of the
    % pitch/yaw/roll sub-buses of an outerLoop_bus or innerLoop_bus and
    % horzcat into an Nx3 [pitch yaw roll] matrix.
    axisBuses = {'pitchOuterLoop_bus','yawOuterLoop_bus','rollOuterLoop_bus'};
    if ~isfield(loopBus, axisBuses{1})
        axisBuses = {'pitchInnerLoop_bus','yawInnerLoop_bus','rollInnerLoop_bus'};
    end
    out3 = zeros(N, 3);
    for j = 1:3
        out3(:,j) = extractHeld_local(loopBus.(axisBuses{j}).(fieldName), t, N, 1);
    end
end

% ==========================================================================
function data = extractHeld_local(ts, t, N, ncols)
    % Align a logged timeseries onto time vector t (resampling if its own
    % time vector doesn't match), holding its value across every frame if
    % it was logged as a single unchanging sample (e.g. a flag that never
    % flips, or fins held constant with feedback off) rather than one per
    % timestep.
    if numel(ts.Time) <= 1
        data = repmat(reshape(ts.Data, 1, []), N, 1);
        return;
    end
    data = alignRows_local(ts.Data, N, ncols);
    if numel(ts.Time) ~= N || any(ts.Time(:) ~= t)
        data = alignRows_local(resample(ts, t).Data, N, ncols);
    end
end

% ==========================================================================
function ts = findLeaf_local(bus, name)
    % Depth-first search of a nested bus struct for a field called name.
    % truth_bus's sub-buses come from unnamed lines, so they log under
    % default names (signal1, signal2, ...) that may change; matching the
    % leaf name keeps this independent of them. [] if not found.
    ts = [];
    if ~isstruct(bus)
        return;
    end
    if isfield(bus, name)
        ts = bus.(name);
        return;
    end
    fn = fieldnames(bus);
    for k = 1:numel(fn)
        ts = findLeaf_local(bus.(fn{k}), name);
        if ~isempty(ts)
            return;
        end
    end
end

% ==========================================================================
function R = quat2dcm_local(q)
    % scalar-first quaternion [q0 q1 q2 q3], body <- NED
    q0=q(1); q1=q(2); q2=q(3); q3=q(4);
    R = [1-2*(q2^2+q3^2),   2*(q1*q2+q0*q3),   2*(q1*q3-q0*q2);
         2*(q1*q2-q0*q3),   1-2*(q1^2+q3^2),   2*(q2*q3+q0*q1);
         2*(q1*q3+q0*q2),   2*(q2*q3-q0*q1),   1-2*(q1^2+q2^2)];
end
