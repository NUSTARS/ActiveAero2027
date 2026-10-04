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
%     simout.plant_bus.eom_bus
%       posNed_m     Nx3   position [north, east, down] [m]
%       q_na         Nx4   quaternion [q0 q1 q2 q3] (scalar-first,
%                          body<-NED)
%       velBdy_mps   Nx3   body-axis velocity   [m/s]
%       wBdy_rps     Nx3   body-axis angular rate [p, q, r]   [rad/s]
%     simout.plant_bus.aero_bus.body_bus
%       aoa_deg      Nx1   total angle of attack, as logged by the model
%     simout.navigation_bus  optional -- nav estimates (attitude, rates,
%                          body accel, NED position/velocity) and
%                          flightMode_enum
%     simout.controller_bus  optional -- older logs without it plot as
%                          all zeros
%       control_deg  Nx4   commanded fin deflection [fin1..fin4] [deg]
%       outerLoop_bus.{pitch,yaw,roll}OuterLoop_bus
%         rateCmd_rps, rateLimited_b, saturated_b
%       innerLoop_bus.{pitch,yaw,roll}InnerLoop_bus
%         control_deg, controlMoment_Nm, rateLimted_b, saturated_b
%
%   OUTPUT
%     Figure 101: States (position/velocity/tilt&roll/AoA/omega/quaternions),
%                 each vector component split into its own subplot, grouped
%                 into a 2x3 layout.
%     Figure 102: Trajectory
%     Figure 104: Controller Evaluation -- one column per axis (Pitch/
%                 Yaw/Roll), one row per quantity (Euler angle, outer-
%                 loop output, inner-loop moment, inner-loop output,
%                 outer- and inner-loop rate-limit/saturation flags in
%                 one row).
%     Figure 105: Attitude Navigation Evaluation -- Pitch/Yaw/Roll
%                 columns of launch-frame Euler angles and body rates,
%                 then x/y/z body acceleration (nav estimate vs actual),
%                 with the nav flight mode along the bottom.
%     Figure 106: PVT Navigation Evaluation -- North/East/Up columns of
%                 position, then velocity (nav estimate vs actual), with
%                 the nav flight mode along the bottom.
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
tOuter = tiledlayout(fig1, 2, 3, 'TileSpacing','compact', 'Padding','compact');
if numel(runs) > 1
    % Leave headroom above the grid for the run color-key legend added
    % below, so it doesn't overlap the group titles.
    tOuter.OuterPosition = [0, 0, 1, 0.93];
end

posLbl   = {'North','East','Up'};
omegaLbl = {'p','q','r'};
quatLbl  = {'q0','q1','q2','q3'};

% Each group below used to be one subplot with several lines on it
% (color per run, text label per component). Each component now gets its
% own subplot instead, via a tiledlayout nested inside the outer tile --
% that keeps the whole group confined to the same figure real estate the
% single combined subplot used to occupy.
axPos = makeGroup_local(tOuter, 1, 3, 'Position', posLbl, 'Position [m]');
axVel = makeGroup_local(tOuter, 2, 3, 'Velocity', posLbl, 'Velocity [m/s]');
axTilt = makeGroup_local(tOuter, 3, 2, 'Tilt & Roll', {'Tilt','Roll'}, 'Angle [deg]');

axAoa = nexttile(tOuter, 4); hold(axAoa,'on'); grid(axAoa,'on');
xlabel(axAoa,'Time [s]'); ylabel(axAoa,'Total AoA [deg]'); title(axAoa,'Angle of Attack');

axOmega = makeGroup_local(tOuter, 5, 3, 'Omega (Body)', omegaLbl, 'Angular Rate [deg/s]');
% Raw quaternion components -- avoids the Euler-angle gimbal-lock
% singularity entirely (see the Controller Evaluation figure for 3-2-1
% Euler angles in the launch frame, estimated vs actual).
axQuat = makeGroup_local(tOuter, 6, 4, 'Quaternion (body<-NED)', quatLbl, 'Component [-]');

for k = 1:numel(runs)
    r = runs{k};
    c = runColors{k};

    for j = 1:3
        plot(axPos(j), r.t, r.pos_plot(:,j), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axVel(j), r.t, r.vel_plot(:,j), '-', 'Color', c, 'LineWidth', 1.2);
    end

    plot(axTilt(1), r.t, r.tilt_deg, '-', 'Color', c, 'LineWidth', 1.2);
    plot(axTilt(2), r.t, r.roll_deg, '-', 'Color', c, 'LineWidth', 1.2);

    plot(axAoa, r.t, r.aoa_deg, '-', 'Color', c, 'LineWidth', 1.5);

    for j = 1:3
        % Solid = true value, dashed = nav estimate (what the controller sees).
        plot(axOmega(j), r.t, rad2deg(r.omega_body(:,j)), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axOmega(j), r.t, rad2deg(r.omegaEst_rps(:,j)), '--', 'Color', c, 'LineWidth', 1.2);
    end

    for j = 1:4
        % Solid = true value, dashed = nav estimate.
        plot(axQuat(j), r.t, r.q_na(:,j), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axQuat(j), r.t, r.qEst_na(:,j), '--', 'Color', c, 'LineWidth', 1.2);
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

% ================================================ LAUNCH-FRAME EULER ANGLES
% Shared by the Controller and Navigation Evaluation windows. Euler angles
% are measured against a launch frame L = [Up, East, North] instead of
% NED, so a vertical rocket reads (0,0,0) and the 3-2-1 gimbal lock moves
% to nose-horizontal. q_Ln is L <- NED; q_bL = conj(q_Ln) (x) q_na.
q_Ln = [sqrt(2)/2, 0, sqrt(2)/2, 0];
for k = 1:numel(runs)
    % Nav estimate as a quaternion: logged directly when available, else
    % rebuilt from the nav's NED Euler angles (older logs / dummyNav).
    qEst = runs{k}.qEst_na;
    if all(isnan(qEst(:)))
        qEst = euler3212quat_local(runs{k}.eulEst_rad);
    end
    runs{k}.eulL_deg    = quat2euler321_local(quatmult_local(quatconj_local(q_Ln), runs{k}.q_na));
    runs{k}.eulLEst_deg = quat2euler321_local(quatmult_local(quatconj_local(q_Ln), qEst));
end

axisLbl3 = {'Pitch','Yaw','Roll'};   % column order; matches the [pitch yaw roll]
                                      % column convention of outerLoop/innerLoop
                                      % fields returned by extractSimRun

% Euler angles ([phi theta psi]) and body rates ([p q r]) are both stored
% roll-first; map each Pitch/Yaw/Roll column to its matching component.
eulerColOf = [2, 3, 1];

% ============================================= CONTROLLER EVALUATION WINDOW
% One column per axis (Pitch/Yaw/Roll), one row per quantity -- lets you
% read straight down a column to see how one axis's loop is behaving.
fig3 = figure(104); clf(fig3); set(fig3,'Name','Controller Evaluation','Color','w');
tCtrl = tiledlayout(fig3, 5, 3, 'TileSpacing','compact', 'Padding','compact');
if numel(runs) > 1
    tCtrl.OuterPosition = [0, 0, 1, 0.93];
end

rowYLbl = {{'Euler','[deg]'}, {'Angular Rate','[deg/s]'}, ...
    {'Moment','[N*m]'}, {'deflection','[deg]'}, {'Limiting'}};

axEuler     = gobjects(1,3);
axOuterCmd  = gobjects(1,3);
axInnerMom  = gobjects(1,3);
axInnerDeg  = gobjects(1,3);
axFlag      = gobjects(1,3);

for j = 1:3
    axEuler(j) = nexttile(tCtrl); hold(axEuler(j),'on'); grid(axEuler(j),'on');
    title(axEuler(j), axisLbl3{j});
    if j == 1, ylabel(axEuler(j), rowYLbl{1}, 'FontSize', 8); end
end
for j = 1:3
    axOuterCmd(j) = nexttile(tCtrl); hold(axOuterCmd(j),'on'); grid(axOuterCmd(j),'on');
    if j == 1, ylabel(axOuterCmd(j), rowYLbl{2}, 'FontSize', 8); end
end
for j = 1:3
    axInnerMom(j) = nexttile(tCtrl); hold(axInnerMom(j),'on'); grid(axInnerMom(j),'on');
    if j == 1, ylabel(axInnerMom(j), rowYLbl{3}, 'FontSize', 8); end
end
for j = 1:3
    axInnerDeg(j) = nexttile(tCtrl); hold(axInnerDeg(j),'on'); grid(axInnerDeg(j),'on');
    if j == 1, ylabel(axInnerDeg(j), rowYLbl{4}, 'FontSize', 8); end
end
% Outer- and inner-loop rate-limit/saturation flags share one row: each
% flag gets its own labeled lane (see plotFlags_local), so they don't
% overlap and need no legend.
flagLaneLbl = {'OL Rate Lim','OL Sat','IL Rate Lim','IL Sat'};
for j = 1:3
    axFlag(j) = nexttile(tCtrl); hold(axFlag(j),'on');
    grid(axFlag(j),'on'); axFlag(j).YGrid = 'off';
    ylim(axFlag(j), [-0.2, numel(flagLaneLbl) - 0.1]);
    yticks(axFlag(j), (0:numel(flagLaneLbl)-1) + 0.4);
    if j == 1
        yticklabels(axFlag(j), flagLaneLbl);
        ylabel(axFlag(j), rowYLbl{5}, 'FontSize', 8);
    else
        yticklabels(axFlag(j), {});
    end
    axFlag(j).YAxis.FontSize = 7;
    xlabel(axFlag(j), 'Time [s]');
end

for k = 1:numel(runs)
    r = runs{k};
    c = runColors{k};

    for j = 1:3
        % Solid = true value, dashed = nav estimate, both in the launch frame.
        plot(axEuler(j), r.t, r.eulL_deg(:,eulerColOf(j)), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axEuler(j), r.t, r.eulLEst_deg(:,eulerColOf(j)), '--', 'Color', c, 'LineWidth', 1.2);

        plot(axOuterCmd(j), r.t, rad2deg(r.omega_body(:,eulerColOf(j))), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axOuterCmd(j), r.t, rad2deg(r.outerRateCmd_rps(:,j)), '--', 'Color', c, 'LineWidth', 1.2);

        plot(axInnerMom(j), r.t, r.innerMoment_Nm(:,j), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axInnerDeg(j), r.t, r.innerControl_deg(:,j), '-', 'Color', c, 'LineWidth', 1.2);

        % Lane order must match flagLaneLbl.
        plotFlags_local(axFlag(j), r.t, [r.outerRateLimited_b(:,j), r.outerSaturated_b(:,j), ...
            r.innerRateLimited_b(:,j), r.innerSaturated_b(:,j)], c);
    end
end

% Line styles are shared across runs/axes, so explain them once rather
% than per subplot.
legend(axEuler(1), {'Actual','Nav'}, 'Location','best');
legend(axOuterCmd(1), {'Actual','Cmd'}, 'Location','best');

addColorKeyLegend_local(runs, runColors);

% ==================================== ATTITUDE NAVIGATION EVALUATION WINDOW
% Same Pitch/Yaw/Roll columns as the Controller window: nav estimate vs
% truth for attitude and body rate, then body-axis acceleration (x/y/z
% columns, since it has no pitch/yaw/roll mapping), with the flight mode
% across the bottom.
fig4 = figure(105); clf(fig4); set(fig4,'Name','Attitude Navigation Evaluation','Color','w');
tNav = tiledlayout(fig4, 4, 3, 'TileSpacing','compact', 'Padding','compact');
if numel(runs) > 1
    tNav.OuterPosition = [0, 0, 1, 0.93];
end

rateLbl3 = {'q','r','p'};   % body rate matching each Pitch/Yaw/Roll column

axNavEul  = gobjects(1,3);
axNavRate = gobjects(1,3);
for j = 1:3
    axNavEul(j) = nexttile(tNav); hold(axNavEul(j),'on'); grid(axNavEul(j),'on');
    title(axNavEul(j), axisLbl3{j});
    if j == 1, ylabel(axNavEul(j), {'Euler','[deg]'}, 'FontSize', 8); end
end
for j = 1:3
    axNavRate(j) = nexttile(tNav); hold(axNavRate(j),'on'); grid(axNavRate(j),'on');
    title(axNavRate(j), rateLbl3{j}, 'FontWeight','normal', 'FontSize', 8);
    if j == 1, ylabel(axNavRate(j), {'Angular Rate','[deg/s]'}, 'FontSize', 8); end
end
accLbl3  = {'x','y','z'};
axNavAcc = gobjects(1,3);
for j = 1:3
    axNavAcc(j) = nexttile(tNav); hold(axNavAcc(j),'on'); grid(axNavAcc(j),'on');
    title(axNavAcc(j), accLbl3{j}, 'FontWeight','normal', 'FontSize', 8);
    if j == 1, ylabel(axNavAcc(j), {'Acceleration','[m/s^2]'}, 'FontSize', 8); end
end
axMode = nexttile(tNav, [1 3]); hold(axMode,'on'); grid(axMode,'on');
[modeEnums, modeNames] = enumeration('flightMode');
modeVals = double(modeEnums);
yticks(axMode, modeVals); yticklabels(axMode, modeNames);
ylim(axMode, [min(modeVals) - 0.5, max(modeVals) + 0.5]);
ylabel(axMode, 'Flight Mode', 'FontSize', 8); xlabel(axMode, 'Time [s]');

for k = 1:numel(runs)
    r = runs{k};
    c = runColors{k};
    for j = 1:3
        % Solid = true value, dashed = nav estimate.
        plot(axNavEul(j), r.t, r.eulL_deg(:,eulerColOf(j)), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axNavEul(j), r.t, r.eulLEst_deg(:,eulerColOf(j)), '--', 'Color', c, 'LineWidth', 1.2);

        plot(axNavRate(j), r.t, rad2deg(r.omega_body(:,eulerColOf(j))), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axNavRate(j), r.t, rad2deg(r.omegaEst_rps(:,eulerColOf(j))), '--', 'Color', c, 'LineWidth', 1.2);

        plot(axNavAcc(j), r.t, r.acc_body(:,j), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axNavAcc(j), r.t, r.accEst_mps2(:,j), '--', 'Color', c, 'LineWidth', 1.2);
    end
    stairs(axMode, r.t, r.flightMode_int, '-', 'Color', c, 'LineWidth', 1.5);
end

legend(axNavEul(1), {'Actual','Nav'}, 'Location','best');
linkaxes([axNavEul, axNavRate, axNavAcc, axMode], 'x');

addColorKeyLegend_local(runs, runColors);

% ========================================= PVT NAVIGATION EVALUATION WINDOW
% Same layout as the Attitude Navigation window, but North/East/Up
% columns of position and velocity (nav estimate vs truth, plot frame),
% with the flight mode across the bottom.
fig5 = figure(106); clf(fig5); set(fig5,'Name','PVT Navigation Evaluation','Color','w');
tPvt = tiledlayout(fig5, 3, 3, 'TileSpacing','compact', 'Padding','compact');
if numel(runs) > 1
    tPvt.OuterPosition = [0, 0, 1, 0.93];
end

pvtLbl3 = {'North','East','Up'};

axNavPos = gobjects(1,3);
axNavVel = gobjects(1,3);
for j = 1:3
    axNavPos(j) = nexttile(tPvt); hold(axNavPos(j),'on'); grid(axNavPos(j),'on');
    title(axNavPos(j), pvtLbl3{j});
    if j == 1, ylabel(axNavPos(j), {'Position','[m]'}, 'FontSize', 8); end
end
for j = 1:3
    axNavVel(j) = nexttile(tPvt); hold(axNavVel(j),'on'); grid(axNavVel(j),'on');
    title(axNavVel(j), pvtLbl3{j}, 'FontWeight','normal', 'FontSize', 8);
    if j == 1, ylabel(axNavVel(j), {'Velocity','[m/s]'}, 'FontSize', 8); end
end
axPvtMode = nexttile(tPvt, [1 3]); hold(axPvtMode,'on'); grid(axPvtMode,'on');
yticks(axPvtMode, modeVals); yticklabels(axPvtMode, modeNames);
ylim(axPvtMode, [min(modeVals) - 0.5, max(modeVals) + 0.5]);
ylabel(axPvtMode, 'Flight Mode', 'FontSize', 8); xlabel(axPvtMode, 'Time [s]');

for k = 1:numel(runs)
    r = runs{k};
    c = runColors{k};
    for j = 1:3
        % Solid = true value, dashed = nav estimate.
        plot(axNavPos(j), r.t, r.pos_plot(:,j), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axNavPos(j), r.t, r.posEst_plot(:,j), '--', 'Color', c, 'LineWidth', 1.2);

        plot(axNavVel(j), r.t, r.vel_plot(:,j), '-', 'Color', c, 'LineWidth', 1.2);
        plot(axNavVel(j), r.t, r.velEst_plot(:,j), '--', 'Color', c, 'LineWidth', 1.2);
    end
    stairs(axPvtMode, r.t, r.flightMode_int, '-', 'Color', c, 'LineWidth', 1.5);
end

legend(axNavPos(1), {'Actual','Nav'}, 'Location','best');
linkaxes([axNavPos, axNavVel, axPvtMode], 'x');

addColorKeyLegend_local(runs, runColors);

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
function plotFlags_local(ax, t, flags_b, c)
    % Plot each column of flags_b (NxK booleans) into its own lane of ax:
    % column i sits at baseline i-1 and steps up 0.8 when active, so K
    % flags share one axis without overlapping. 'stairs' since these are
    % boolean step signals rather than continuous ones. Lane labels are
    % set by the caller via yticklabels.
    for i = 1:size(flags_b, 2)
        stairs(ax, t, (i-1) + 0.8*double(flags_b(:,i)), '-', 'Color', c, 'LineWidth', 1.2);
    end
end

% ======================================================================
function s = onoff_local(tf)
    if tf, s = 'on'; else, s = 'off'; end
end

% ======================================================================
function eul_deg = quat2euler321_local(q)
    % Yaw-pitch-roll (3-2-1) Euler angles [phi theta psi] from a scalar-
    % first quaternion [q0 q1 q2 q3], body<-reference frame. Gimbal-locks
    % at theta = +/-90deg -- in NED that is near-vertical flight, which is
    % why the caller prerotates into the launch frame first.
    q0 = q(:,1); q1 = q(:,2); q2 = q(:,3); q3 = q(:,4);
    roll  = atan2(2*(q0.*q1 + q2.*q3), 1 - 2*(q1.^2 + q2.^2));
    pitch = asin(max(-1, min(1, 2*(q0.*q2 - q3.*q1))));
    yaw   = atan2(2*(q0.*q3 + q1.*q2), 1 - 2*(q2.^2 + q3.^2));
    eul_deg = rad2deg([roll, pitch, yaw]);
end

% ======================================================================
function q = euler3212quat_local(eul_rad)
    % Inverse of quat2euler321_local: [phi theta psi] (rad) -> scalar-first
    % quaternion, body<-reference. Matches Aerospace Toolbox angle2quat(psi,theta,phi).
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
    % Hamilton product a (x) b, scalar-first, row-wise; either input may be
    % a single 1x4 row applied to every row of the other. Same as
    % Aerospace Toolbox quatmultiply.
    n = max(size(a,1), size(b,1));
    a = repmat(a, n/size(a,1), 1); b = repmat(b, n/size(b,1), 1);
    q = [a(:,1).*b(:,1) - sum(a(:,2:4).*b(:,2:4), 2), ...
         a(:,1).*b(:,2:4) + b(:,1).*a(:,2:4) + cross(a(:,2:4), b(:,2:4), 2)];
end

% ======================================================================
function q = quatconj_local(q)
    q(:,2:4) = -q(:,2:4);
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

