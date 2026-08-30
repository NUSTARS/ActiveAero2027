%PLOTROCKETTRAJECTORY  Plot one or two logged 6DOF runs.
%
%   Edit the CONFIG block below, then run the script.
%     matFiles = {}                    plot `out` already in the workspace
%     matFiles = {matFile}             plot `out` saved in matFile
%     matFiles = {matFile1, matFile2}  overlay two saved runs
%
%   Each matFile must contain an `out` variable, e.g. as saved by
%   scripts/runModel.m (results/simResults.mat).
%
%   OPTIONS
%     numFrames    number of attitude/velocity triads drawn along each
%                  trajectory (default 5)
%     bodyScale    length of the plotted body/velocity vectors, in plot
%                  units (default: auto, ~5% of the first run's
%                  trajectory span)
%     forwardAxis  3x1 unit vector, the nose/forward direction expressed
%                  in BODY axes (default [1;0;0], the aerospace-standard
%                  X-forward convention)
%
%   Each `out` must have `out.simout`, a struct of nested bus structs,
%   each field a 1x1 timeseries:
%     simout.eom_bus
%       posNed_m     Nx3   position [north, east, down] [m]
%       q_na         Nx4   quaternion [q0 q1 q2 q3] (scalar-first,
%                          body<-NED)
%       velBdy_mps   Nx3   body-axis velocity   [m/s]
%       wBdy_rps     Nx3   body-axis angular rate [p, q, r]   [rad/s]
%     simout.aero_bus.body_bus
%       aoa_deg      Nx1   total angle of attack, as logged by the model
%     simout.control_deg  Nx4   commanded fin deflection [fin1..fin4]
%                          [deg], optional -- older logs without it plot
%                          as all zeros
%
%   OUTPUT
%     Figure 101: States (position/velocity/tilt&roll/AoA/omega/raw attitude),
%                 each vector component split into its own subplot, grouped
%                 into the same 2x3 layout the combined plots used to occupy.
%     Figure 102: Trajectory
%     Fixed figure numbers (deliberately not 1/2, to stay clear of other
%     figures) so re-running overwrites the same windows instead of
%     piling up new ones.
%
%   NOTES
%     - Position/velocity are NED; "down" is flipped for plotting so
%       altitude increases upward.
%     - Total AoA is plotted straight from the logged aoa_deg signal,
%       not recomputed here.
%     - velBdy_mps is body-axis velocity: at t=0 it equals the 6DOF
%       block's Vm_0 IC directly, with no rotation applied. It is
%       rotated into NED here (via q_na) for the state/trajectory plots,
%       which need NED.

% =============================================================== CONFIG
resultsDir  = fullfile(fileparts(fileparts(mfilename('fullpath'))), 'results');
matFiles    = {'simResults'};   % {} = use `out` already in the workspace; bare names resolve against resultsDir, .mat optional
numFrames   = 5;
bodyScale   = [];
forwardAxis = [1;0;0];

% ------------------------------------------------------------ load runs
if isempty(matFiles)
    if ~exist('out', 'var')
        error('plotRocketTrajectory:noOut', ...
            ['No .mat file given and `out` not found in the workspace -- ', ...
             'run scripts/runModel.m first.']);
    end
    runs = {extractSimRun(out, 'workspace', forwardAxis)};
else
    if numel(matFiles) > 2
        error('plotRocketTrajectory:tooManyFiles', ...
            'List at most two .mat files in matFiles to overlay.');
    end
    runs = cell(1, numel(matFiles));
    for k = 1:numel(matFiles)
        matFilePath = resolveMatFile_local(matFiles{k}, resultsDir);
        S = load(matFilePath, 'out');
        if ~isfield(S, 'out')
            error('plotRocketTrajectory:noOutInFile', ...
                '%s does not contain an ''out'' variable.', matFilePath);
        end
        [~, label] = fileparts(matFilePath);
        runs{k} = extractSimRun(S.out, label, forwardAxis);
    end
end

if isempty(bodyScale)
    span = max(max(runs{1}.pos_plot) - min(runs{1}.pos_plot));
    if span == 0 || isnan(span), span = 1; end
    bodyScale = 0.05 * span;
end

runColors = {[0 0.4470 0.7410], [0.8500 0.3250 0.0980]};   % blue, orange, per run
noseColor = 'r';                                            % fixed across runs
velColor  = [0 0.6 0];                                       % fixed across runs

% ========================================================= STATES WINDOW
fig1 = figure(101); clf(fig1); set(fig1,'Name','States','Color','w');
tOuter = tiledlayout(fig1, 2, 4, 'TileSpacing','compact', 'Padding','compact');
if numel(runs) > 1
    % Leave headroom above the grid for the run color-key legend added
    % below, so it doesn't overlap the group titles.
    tOuter.OuterPosition = [0, 0, 1, 0.93];
end

posLbl     = {'North','East','Up'};
omegaLbl   = {'p','q','r'};
eulerLbl   = {'Roll','Pitch','Yaw'};
controlLbl = {'Fin1','Fin2','Fin3','Fin4'};

% Each group below used to be one subplot with several lines on it
% (color per run, text label per component). Each component now gets its
% own subplot instead, via a tiledlayout nested inside the outer tile --
% that keeps the whole group confined to the same figure real estate the
% single combined subplot used to occupy.
axPos = makeGroup_local(tOuter, 1, 3, 'Position', posLbl, 'Position [m]');
axVel = makeGroup_local(tOuter, 2, 3, 'Velocity', posLbl, 'Velocity [m/s]');
axTilt = makeGroup_local(tOuter, 3, 2, 'Tilt & Roll', {'Tilt','Roll'}, 'Angle [deg]');
axControl = makeGroup_local(tOuter, 4, 4, 'Fin Control', controlLbl, 'Deflection [deg]');

axAoa = nexttile(tOuter, 5); hold(axAoa,'on'); grid(axAoa,'on');
xlabel(axAoa,'Time [s]'); ylabel(axAoa,'Total AoA [deg]'); title(axAoa,'Angle of Attack');

axOmega = makeGroup_local(tOuter, 6, 3, 'Omega (Body)', omegaLbl, 'Angular Rate [deg/s]');
% Yaw-roll-pitch (Z-X-Y) sequence rather than the aircraft-standard
% yaw-pitch-roll (321, Z-Y-X): gimbal lock always hits whichever angle
% is the MIDDLE rotation, and 321 puts pitch there -- which pegs near
% +/-90deg for a rocket whose nose (roll axis) points vertical. Putting
% roll in the middle instead avoids this: roll-about-nose stays small
% for this vehicle (see Tilt & Roll), nowhere near its own singularity.
% (A literal roll-pitch-yaw/123 ordering still puts pitch in the middle
% and was checked to hit the same gimbal lock -- reordering which axis
% is singular, not just which is named first, is what actually matters.)
axEuler = makeGroup_local(tOuter, 7, 3, 'Euler Angles (yaw-roll-pitch)', eulerLbl, 'Angle [deg]');

for k = 1:numel(runs)
    r = runs{k};
    c = runColors{k};

    for j = 1:3
        plot(axPos(j), r.t, r.pos_plot(:,j), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axVel(j), r.t, r.vel_plot(:,j), '-', 'Color', c, 'LineWidth', 1.2);
    end

    plot(axTilt(1), r.t, r.tilt_deg, '-', 'Color', c, 'LineWidth', 1.2);
    plot(axTilt(2), r.t, r.roll_deg, '-', 'Color', c, 'LineWidth', 1.2);

    for j = 1:4
        plot(axControl(j), r.t, r.control_deg(:,j), '-', 'Color', c, 'LineWidth', 1.2);
    end

    plot(axAoa, r.t, r.aoa_deg, '-', 'Color', c, 'LineWidth', 1.5);

    for j = 1:3
        plot(axOmega(j), r.t, rad2deg(r.omega_body(:,j)), '-', 'Color', c, 'LineWidth', 1.2);
    end

    eul_deg = quat2eulerZXY_local(r.q_na);
    for j = 1:3
        plot(axEuler(j), r.t, eul_deg(:,j), '-', 'Color', c, 'LineWidth', 1.2);
    end
end

% Combined run color key, shown once for the whole figure rather than
% repeated per subplot.
addColorKeyLegend_local(runs, runColors);

% ===================================================== TRAJECTORY WINDOW
fig2 = figure(102); clf(fig2); set(fig2,'Name','Trajectory','Color','w');
ax = axes(fig2); hold(ax,'on'); grid(ax,'on'); axis(ax,'equal'); view(ax,3);
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
    frameIdx = round(linspace(1, N, min(numFrames, N)));
    for f = frameIdx
        o = r.pos_plot(f,:);
        quiver3(ax, o(1), o(2), o(3), r.nose_plot(f,1), r.nose_plot(f,2), r.nose_plot(f,3), ...
            bodyScale, 'Color', noseColor, 'LineWidth', 1.5, 'MaxHeadSize', 0.8, ...
            'HandleVisibility', 'off');
        vhat = r.vel_plot(f,:) / max(norm(r.vel_plot(f,:)), eps);
        quiver3(ax, o(1), o(2), o(3), vhat(1), vhat(2), vhat(3), ...
            bodyScale, 'Color', velColor, 'LineWidth', 1.2, 'MaxHeadSize', 0.8, ...
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

fprintf("Apogee: %.1fm\n",max(r.pos_plot(:,3)))

% ======================================================================
function axArr = makeGroup_local(tOuter, tileIdx, n, groupTitle, compLbls, yLbl)
    % Build a nested 1-column tiledlayout inside outer tile `tileIdx`,
    % with one subplot per component in `compLbls` -- occupies the exact
    % footprint the single combined subplot used to occupy.
    tGroup = tiledlayout(tOuter, n, 1, 'TileSpacing','compact', 'Padding','compact');
    tGroup.Layout.Tile = tileIdx;
    title(tGroup, groupTitle);
    ylabel(tGroup, yLbl);
    xlabel(tGroup, 'Time [s]');

    axArr = gobjects(1, n);
    for i = 1:n
        axArr(i) = nexttile(tGroup);
        hold(axArr(i), 'on'); grid(axArr(i), 'on');
        title(axArr(i), compLbls{i}, 'FontWeight','normal', 'FontSize', 8);
    end
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
function eul_deg = quat2eulerZXY_local(q_na)
    % Yaw-roll-pitch (Z-X-Y) Euler angles from a scalar-first quaternion
    % [q0 q1 q2 q3], body<-NED -- consistent with the DCM convention
    % used elsewhere for tilt/roll (same quaternion-to-DCM formula as
    % quat2dcm_local in extractSimRun.m, just extracted with this
    % sequence's formulas). Gimbal lock is always at the MIDDLE
    % rotation's +/-90deg; putting roll there (rather than pitch, as in
    % the standard yaw-pitch-roll/321 sequence) keeps this rocket's
    % near-vertical flight away from the singularity, since roll-about-
    % nose stays small while pitch would otherwise sit near 90deg. See
    % the caveat where this is called.
    q0 = q_na(:,1); q1 = q_na(:,2); q2 = q_na(:,3); q3 = q_na(:,4);
    roll  = asin(max(-1, min(1, 2*(q2.*q3 + q0.*q1))));
    pitch = atan2(2*(q0.*q2 - q1.*q3), 1 - 2*(q1.^2 + q2.^2));
    yaw   = atan2(2*(q0.*q3 - q1.*q2), 1 - 2*(q1.^2 + q3.^2));
    eul_deg = rad2deg([roll, pitch, yaw]);
end

% ======================================================================
function p = resolveMatFile_local(name, resultsDir)
    % Accepts a bare run name (no folder, .mat optional) and resolves it
    % against resultsDir; a path that already exists as given (relative
    % or absolute, with or without .mat) is used unchanged.
    candidates = {name, [name, '.mat'], ...
        fullfile(resultsDir, name), fullfile(resultsDir, [name, '.mat'])};
    for i = 1:numel(candidates)
        if isfile(candidates{i})
            p = candidates{i};
            return;
        end
    end
    error('resolveMatFile_local:notFound', ...
        'Could not find ''%s'' -- tried it as-is, with .mat appended, and under %s.', ...
        name, resultsDir);
end

