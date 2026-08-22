function plotRocketTrajectory(varargin)
%PLOTROCKETTRAJECTORY  Plot one or two logged 6DOF runs.
%
%   plotRocketTrajectory()                     plot `out` from the base
%                                               workspace
%   plotRocketTrajectory(matFile)              plot `out` saved in
%                                               matFile
%   plotRocketTrajectory(matFile1, matFile2)   overlay two saved runs
%
%   Each matFile must contain an `out` variable, e.g. as saved by
%   scripts/runModel.m (results/simResults.mat).
%
%   OPTIONS (name-value, after any file args)
%     'numFrames'    number of attitude/velocity triads drawn along each
%                    trajectory (default 15)
%     'bodyScale'    length of the plotted body/velocity vectors, in
%                    plot units (default: auto, ~5% of the first run's
%                    trajectory span)
%     'forwardAxis'  3x1 unit vector, the nose/forward direction
%                    expressed in BODY axes (default [1;0;0], the
%                    aerospace-standard X-forward convention)
%
%   Each `out` must have `out.simout`, a struct of nested bus structs,
%   each field a 1x1 timeseries:
%     simout.eom_bus
%       posNed_m     Nx3   position [north, east, down] [m]
%       q_na         Nx4   quaternion [q0 q1 q2 q3] (scalar-first,
%                          body<-NED)
%       velBdy_mps   Nx3   body-axis velocity   [m/s]
%       wBdy_rps     Nx3   body-axis angular rate [p, q, r]   [rad/s]
%     simout.aeroParams_bus
%       alpha_rad    Nx1   total angle of attack, as logged by the model
%
%   OUTPUT
%     Figure 101: States (position/velocity/tilt&roll/AoA/omega/raw attitude)
%     Figure 102: Trajectory
%     Fixed figure numbers (deliberately not 1/2, to stay clear of other
%     figures) so re-running overwrites the same windows instead of
%     piling up new ones.
%
%   NOTES
%     - Position/velocity are NED; "down" is flipped for plotting so
%       altitude increases upward.
%     - Total AoA is plotted straight from the logged alpha_rad signal,
%       not recomputed here.
%     - velBdy_mps is body-axis velocity: at t=0 it equals the 6DOF
%       block's Vm_0 IC directly, with no rotation applied. It is
%       rotated into NED here (via q_na) for the state/trajectory plots,
%       which need NED.

% ------------------------------------------------------- parse arguments
fileArgs = {};
i = 1;
while i <= numel(varargin) && ischar(varargin{i}) ...
        && endsWith(varargin{i}, '.mat', 'IgnoreCase', true)
    fileArgs{end+1} = varargin{i}; %#ok<AGROW>
    i = i + 1;
end
if numel(fileArgs) > 2
    error('plotRocketTrajectory:tooManyFiles', ...
        'Pass at most two .mat files to overlay.');
end

optArgs = varargin(i:end);
if mod(numel(optArgs), 2) ~= 0
    error('plotRocketTrajectory:badOptions', ...
        'Options must be name-value pairs.');
end
opts = struct('numFrames', 5, 'bodyScale', [], 'forwardAxis', [1;0;0]);
for k = 1:2:numel(optArgs)
    opts.(optArgs{k}) = optArgs{k+1};
end

% ------------------------------------------------------------ load runs
if isempty(fileArgs)
    if ~evalin('base', 'exist(''out'', ''var'')')
        error('plotRocketTrajectory:noOut', ...
            ['No .mat file given and `out` not found in the base ', ...
             'workspace -- run scripts/runModel.m first.']);
    end
    runs = {extractRun_local(evalin('base', 'out'), 'workspace', opts.forwardAxis)};
else
    runs = cell(1, numel(fileArgs));
    for k = 1:numel(fileArgs)
        S = load(fileArgs{k}, 'out');
        if ~isfield(S, 'out')
            error('plotRocketTrajectory:noOutInFile', ...
                '%s does not contain an ''out'' variable.', fileArgs{k});
        end
        [~, label] = fileparts(fileArgs{k});
        runs{k} = extractRun_local(S.out, label, opts.forwardAxis);
    end
end

if isempty(opts.bodyScale)
    span = max(max(runs{1}.pos_plot) - min(runs{1}.pos_plot));
    if span == 0 || isnan(span), span = 1; end
    opts.bodyScale = 0.05 * span;
end

runColors = {[0 0.4470 0.7410], [0.8500 0.3250 0.0980]};   % blue, orange, per run
noseColor = 'r';                                            % fixed across runs
velColor  = [0 0.6 0];                                       % fixed across runs

% ========================================================= STATES WINDOW
figure(101); clf(101); set(101,'Name','States','Color','w');

axPos = subplot(2,3,1); hold(axPos,'on'); grid(axPos,'on');
xlabel(axPos,'Time [s]'); ylabel(axPos,'Position [m]'); title(axPos,'Position');

axVel = subplot(2,3,2); hold(axVel,'on'); grid(axVel,'on');
xlabel(axVel,'Time [s]'); ylabel(axVel,'Velocity [m/s]'); title(axVel,'Velocity');

axTilt = subplot(2,3,3); hold(axTilt,'on'); grid(axTilt,'on');
xlabel(axTilt,'Time [s]'); ylabel(axTilt,'Angle [deg]'); title(axTilt,'Tilt & Roll');

axAoa = subplot(2,3,4); hold(axAoa,'on'); grid(axAoa,'on');
xlabel(axAoa,'Time [s]'); ylabel(axAoa,'Total AoA [deg]'); title(axAoa,'Angle of Attack');

axOmega = subplot(2,3,5); hold(axOmega,'on'); grid(axOmega,'on');
xlabel(axOmega,'Time [s]'); ylabel(axOmega,'Angular Rate [deg/s]'); title(axOmega,'Omega (Body)');

axQuat = subplot(2,3,6); hold(axQuat,'on'); grid(axQuat,'on');
xlabel(axQuat,'Time [s]'); ylabel(axQuat,'Quaternion'); title(axQuat,'Raw Attitude (Quaternion)');

posLbl = {'North','East','Up'};
omegaLbl = {'p','q','r'};
quatLbl = {'q0','q1','q2','q3'};

% Color distinguishes runs (see the combined color key below). Within an
% axes, each component is instead named with a small text label at the
% end of its own line -- clearer than dash/dot linestyles or a cluster
% of marker shapes, and it scales fine to 3-4 lines per subplot.
for k = 1:numel(runs)
    r = runs{k};
    c = runColors{k};

    for j = 1:3
        plotLabeled_local(axPos, r.t, r.pos_plot(:,j), c, posLbl{j});
        plotLabeled_local(axVel, r.t, r.vel_plot(:,j), c, posLbl{j});
    end

    plotLabeled_local(axTilt, r.t, r.tilt_deg, c, 'Tilt');
    plotLabeled_local(axTilt, r.t, r.roll_deg, c, 'Roll');

    plot(axAoa, r.t, rad2deg(r.alpha_rad), '-', 'Color', c, 'LineWidth', 1.5);

    for j = 1:3
        plotLabeled_local(axOmega, r.t, rad2deg(r.omega_body(:,j)), c, omegaLbl{j});
    end

    for j = 1:4
        plotLabeled_local(axQuat, r.t, r.q_na(:,j), c, quatLbl{j});
    end
end

% End labels sit just past the last data point -- widen xlim so they
% aren't clipped at the axes edge.
expandXlim_local(axPos); expandXlim_local(axVel); expandXlim_local(axTilt);
expandXlim_local(axOmega); expandXlim_local(axQuat);

% Combined run color key, shown once for the whole figure rather than
% repeated per subplot.
addColorKeyLegend_local(runs, runColors);

% ===================================================== TRAJECTORY WINDOW
figure(102); clf(102); set(102,'Name','Trajectory','Color','w');
ax = axes; hold(ax,'on'); grid(ax,'on'); axis(ax,'equal'); view(ax,3);
xlabel(ax,'North [m]'); ylabel(ax,'East [m]'); zlabel(ax,'Up [m]');
title(ax,'Trajectory with Attitude / Velocity Triads');

% Same scheme as the States window: color distinguishes runs, so only
% the first run's Trajectory/Launch/End lines get legend entries, and
% which run is which color is named once via the shared color key
% rather than tagged onto every entry.
for k = 1:numel(runs)
    r = runs{k};
    c = runColors{k};
    showInLegend = (k == 1);

    plot3(ax, r.pos_plot(:,1), r.pos_plot(:,2), r.pos_plot(:,3), '-', 'Color', c, 'LineWidth', 1.5, ...
        'DisplayName', 'Trajectory', 'HandleVisibility', onoff_local(showInLegend));
    plot3(ax, r.pos_plot(1,1), r.pos_plot(1,2), r.pos_plot(1,3), 'o', 'Color', c, 'MarkerFaceColor', c, ...
        'DisplayName', 'Launch', 'HandleVisibility', onoff_local(showInLegend));
    plot3(ax, r.pos_plot(end,1), r.pos_plot(end,2), r.pos_plot(end,3), 's', 'Color', c, 'MarkerFaceColor', c, ...
        'DisplayName', 'End', 'HandleVisibility', onoff_local(showInLegend));

    N = size(r.pos_plot, 1);
    frameIdx = round(linspace(1, N, min(opts.numFrames, N)));
    for f = frameIdx
        o = r.pos_plot(f,:);
        quiver3(ax, o(1), o(2), o(3), r.nose_plot(f,1), r.nose_plot(f,2), r.nose_plot(f,3), ...
            opts.bodyScale, 'Color', noseColor, 'LineWidth', 1.5, 'MaxHeadSize', 0.8, ...
            'HandleVisibility', 'off');
        vhat = r.vel_plot(f,:) / max(norm(r.vel_plot(f,:)), eps);
        quiver3(ax, o(1), o(2), o(3), vhat(1), vhat(2), vhat(3), ...
            opts.bodyScale, 'Color', velColor, 'LineWidth', 1.2, 'MaxHeadSize', 0.8, ...
            'HandleVisibility', 'off');
    end
end

% Nose/velocity triads use one fixed color each across runs, so give
% them one legend entry each (via invisible dummy lines) rather than a
% per-run entry -- the real quiver3 calls above are excluded from the
% legend via HandleVisibility.
plot3(ax, nan, nan, nan, '-', 'Color', noseColor, 'LineWidth', 1.5, 'DisplayName', 'Nose');
plot3(ax, nan, nan, nan, '-', 'Color', velColor, 'LineWidth', 1.2, 'DisplayName', 'Velocity');

legend(ax, 'Location','best');

addColorKeyLegend_local(runs, runColors);

end

% ======================================================================
function addColorKeyLegend_local(runs, runColors)
    % One legend, in the current figure, mapping each run's label to its
    % color -- added once per figure rather than tagging every entry in
    % every subplot's own legend. No-op for a single run (nothing to
    % disambiguate).
    if numel(runs) <= 1
        return;
    end
    axKey = axes('Position', [0 0 0.01 0.01], 'Visible', 'off');
    hold(axKey, 'on');
    hKey = gobjects(1, numel(runs));
    keyLabels = cell(1, numel(runs));
    for k = 1:numel(runs)
        hKey(k) = plot(axKey, nan, nan, '-', 'Color', runColors{k}, 'LineWidth', 2);
        keyLabels{k} = runs{k}.label;
    end
    lgdKey = legend(axKey, hKey, keyLabels, 'Orientation', 'horizontal', 'Box', 'off');
    lgdKey.Position(1:2) = [0.5 - lgdKey.Position(3)/2, 0.965];
end

% ======================================================================
function s = onoff_local(tf)
    if tf, s = 'on'; else, s = 'off'; end
end

% ======================================================================
function plotLabeled_local(ax, t, y, color, label)
    % A solid line with its component name written directly at its end
    % (in the same color as the line), instead of a legend entry --
    % avoids a cluttered legend/marker combination when several
    % same-color lines share an axes.
    plot(ax, t, y, '-', 'Color', color, 'LineWidth', 1.2, 'HandleVisibility', 'off');
    dt = max(t) - min(t);
    if dt == 0, dt = 1; end
    text(ax, t(end) + 0.015*dt, y(end), label, 'Color', color, 'FontSize', 8, ...
        'HorizontalAlignment', 'left', 'VerticalAlignment', 'middle', 'Clipping', 'off');
end

% ======================================================================
function expandXlim_local(ax)
    % Widen the x-axis so end-of-line text labels (drawn just past the
    % last data point) aren't clipped at the axes edge.
    xl = xlim(ax);
    xlim(ax, [xl(1), xl(2) + 0.12*(xl(2) - xl(1))]);
end

% ======================================================================
function r = extractRun_local(out, label, forwardAxis)
    % Pull one run's data out of a Simulink sim output and derive the
    % plotted quantities (tilt/roll/nose/velocity in NED, etc.). `out`
    % may be a Simulink.SimulationOutput object (isstruct is false for
    % it, but out.simout works via property access) or a plain struct
    % loaded from a .mat file, so probe with try/catch rather than
    % isstruct/isfield.
    try
        simout = out.simout;
    catch
        error('plotRocketTrajectory:noSimout', ...
            '%s: out.simout not found -- out must be a Simulink sim output.', label);
    end

    requiredBuses = {'eom_bus','aeroParams_bus'};
    if ~isstruct(simout) || ~all(isfield(simout, requiredBuses))
        error('plotRocketTrajectory:badSimout', ...
            '%s: simout must have fields eom_bus, aeroParams_bus (each a bus struct).', label);
    end

    eom  = simout.eom_bus;
    aero = simout.aeroParams_bus;

    requiredEom = {'velBdy_mps','posNed_m','q_na','wBdy_rps'};
    if ~all(isfield(eom, requiredEom))
        error('plotRocketTrajectory:badEom', ...
            '%s: simout.eom_bus must have fields velBdy_mps, posNed_m, q_na, wBdy_rps (each a timeseries).', label);
    end
    if ~isfield(aero, 'alpha_rad')
        error('plotRocketTrajectory:badAero', ...
            '%s: simout.aeroParams_bus must have field alpha_rad (a timeseries).', label);
    end

    ts_vel   = eom.velBdy_mps;
    ts_pos   = eom.posNed_m;
    ts_q     = eom.q_na;
    ts_alpha = aero.alpha_rad;
    ts_omega = eom.wBdy_rps;

    t = ts_vel.Time(:);
    N = numel(t);

    vel_body   = alignRows_local(ts_vel.Data, N, 3);
    pos_NED    = alignRows_local(ts_pos.Data, N, 3);
    q_na       = alignRows_local(ts_q.Data, N, 4);
    alpha_rad  = alignRows_local(ts_alpha.Data, N, 1);
    omega_body = alignRows_local(ts_omega.Data, N, 3);

    % Guard against slightly mismatched time vectors across signals (can
    % happen with variable-step solvers).
    if numel(ts_pos.Time) ~= N || any(ts_pos.Time(:) ~= t)
        pos_NED = alignRows_local(resample(ts_pos, t).Data, N, 3);
    end
    if numel(ts_q.Time) ~= N || any(ts_q.Time(:) ~= t)
        q_na = alignRows_local(resample(ts_q, t).Data, N, 4);
    end
    if numel(ts_alpha.Time) ~= N || any(ts_alpha.Time(:) ~= t)
        alpha_rad = alignRows_local(resample(ts_alpha, t).Data, N, 1);
    end
    if numel(ts_omega.Time) ~= N || any(ts_omega.Time(:) ~= t)
        omega_body = alignRows_local(resample(ts_omega, t).Data, N, 3);
    end

    q_na = q_na ./ vecnorm(q_na, 2, 2);

    % ---------------------------------------------------- derived signals
    fwd_body = forwardAxis(:);

    world_north = [1;0;0];   % fixed NED reference for "zero roll"

    % Reference body axis for measuring roll: derived from the INITIAL
    % attitude so that roll always starts at 0deg, rather than picking
    % some fixed body axis (e.g. body Y) that lands at an arbitrary
    % offset (e.g. -90deg) depending on the vehicle's initial orientation.
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

        % Roll about the nose, measured against a local frame built from
        % a fixed world reference (North) rather than a 321-Euler
        % sequence -- the latter has a coordinate singularity (gimbal
        % lock) exactly at 90deg tilt, which a straight-up rocket
        % tipping over at apogee hits directly, causing a spurious
        % discontinuity in the roll trace.
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
        'alpha_rad', alpha_rad, ...
        'omega_body', omega_body, ...
        'q_na',      q_na);
end

% ======================================================================
function out = alignRows_local(data, N, ncols)
    % squeeze() on a logged timeseries can leave data as Nxncols OR
    % ncolsxN depending on how the signal was dimensioned in Simulink.
    % A blind reshape(data,N,ncols) does not transpose -- it just
    % re-reads memory linearly, silently scrambling rows/columns when
    % the orientation is wrong. Check shape explicitly instead.
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

% ======================================================================
function R = quat2dcm_local(q)
    % scalar-first quaternion [q0 q1 q2 q3], body <- NED
    q0=q(1); q1=q(2); q2=q(3); q3=q(4);
    R = [1-2*(q2^2+q3^2),   2*(q1*q2+q0*q3),   2*(q1*q3-q0*q2);
         2*(q1*q2-q0*q3),   1-2*(q1^2+q3^2),   2*(q2*q3+q0*q1);
         2*(q1*q3+q0*q2),   2*(q2*q3-q0*q1),   1-2*(q1^2+q2^2)];
end
