%ANIMATEROCKETTRAJECTORY  Animate one or two logged 6DOF runs with a
%   chase camera zoomed on the vehicle -- a short trailing path plus a
%   nose/velocity vector triad tracking current attitude -- alongside a
%   live tilt/roll/AoA readout. A Play/Pause button controls playback.
%
%   Edit the CONFIG block below, then run the script.
%     matFiles = {}                    animate `out` already in the workspace
%     matFiles = {matFile}             animate `out` saved in matFile
%     matFiles = {matFile1, matFile2}  animate two runs side by side in time
%
%   Each matFile must contain an `out` variable, e.g. as saved by
%   scripts/runModel.m (results/simResults.mat). Uses the same
%   scripts/helpers/extractSimRun.m data extraction as
%   plotRocketTrajectory.m, so both stay in sync with the model's
%   logging structure.
%
%   OPTIONS
%     fps           output/playback frame rate (default 30)
%     playbackSpeed multiple of real (simulated) time per second of
%                    playback, e.g. 2 plays twice as fast as the sim ran
%                    (default 0.1, i.e. slow motion -- attitude dynamics
%                    are fast relative to the trajectory)
%     followCam     if true (default), the camera chases the vehicle,
%                    zoomed in to camSpan so orientation is clearly
%                    visible; if false, the view is a fixed wide shot of
%                    the whole trajectory (the old behavior)
%     camSpan       width/height/depth of the chase-cam view box, in plot
%                    units (default: auto, ~6% of the trajectory span)
%     trailSeconds  how much trailing path history to draw behind the
%                    vehicle in followCam mode, in sim seconds (default 3)
%     bodyScale     length of the plotted nose/velocity vectors, in plot
%                    units (default: auto, ~35% of camSpan)
%     forwardAxis   3x1 unit vector, the nose/forward direction expressed
%                    in BODY axes (default [1;0;0])
%     saveVideo     if true, render every frame straight to videoFile
%                    instead of opening an interactive Play/Pause window
%                    (default false)
%     videoFile     output video path when saveVideo is true (default
%                    results/trajectoryAnimation.mp4)
%     showLive      if true (default), open a visible figure; set false
%                    with saveVideo=true to render without a window
%                    popping up
%
%   INTERACTIVE USE
%     With saveVideo=false (default), the script builds the figure with a
%     Play/Pause button and returns immediately -- it does not block.
%     Click Play to start/resume, Pause to stop; it stops on its own at
%     the end of the run(s). Closing the figure cleans up its timer.
%
%   OUTPUT
%     Figure 103: chase-cam 3D view (left) and tilt/roll/AoA strip charts
%     (right) with a moving time cursor.
%     Fixed figure number (deliberately not 101/102, to stay clear of
%     plotRocketTrajectory.m's windows).

% =============================================================== CONFIG
if ~exist('matFiles', 'var'),      matFiles      = {};        end   % {} = use `out` already in the workspace
if ~exist('fps', 'var'),           fps           = 30;        end
if ~exist('playbackSpeed', 'var'), playbackSpeed = 0.1;       end
if ~exist('followCam', 'var'),     followCam     = true;      end
if ~exist('camSpan', 'var'),       camSpan       = [];        end
if ~exist('trailSeconds', 'var'),  trailSeconds  = 3;         end
if ~exist('bodyScale', 'var'),     bodyScale     = [];        end
if ~exist('forwardAxis', 'var'),   forwardAxis   = [1;0;0];   end
if ~exist('saveVideo', 'var'),     saveVideo     = false;     end
if ~exist('videoFile', 'var'),     videoFile     = '';        end
if ~exist('showLive', 'var'),      showLive      = true;      end

% ------------------------------------------------------------ load runs
if isempty(matFiles)
    if ~exist('out', 'var')
        error('animateRocketTrajectory:noOut', ...
            ['No .mat file given and `out` not found in the workspace -- ', ...
             'run scripts/runModel.m first.']);
    end
    runs = {extractSimRun(out, 'workspace', forwardAxis)};
else
    if numel(matFiles) > 2
        error('animateRocketTrajectory:tooManyFiles', ...
            'List at most two .mat files in matFiles to overlay.');
    end
    runs = cell(1, numel(matFiles));
    for k = 1:numel(matFiles)
        S = load(matFiles{k}, 'out');
        if ~isfield(S, 'out')
            error('animateRocketTrajectory:noOutInFile', ...
                '%s does not contain an ''out'' variable.', matFiles{k});
        end
        [~, label] = fileparts(matFiles{k});
        runs{k} = extractSimRun(S.out, label, forwardAxis);
    end
end

if isempty(videoFile)
    videoFile = fullfile(fileparts(fileparts(mfilename('fullpath'))), 'results', 'trajectoryAnimation.mp4');
end

runColors = {[0 0.4470 0.7410], [0.8500 0.3250 0.0980]};   % blue, orange, per run
noseColor = 'r';
velColor  = [0 0.6 0];

% --------------------------------------------------- resample onto frames
% Sim data is unevenly/finely spaced (solver steps); resample every run
% onto a common, evenly spaced frame clock so playback speed and fps are
% both exact and runs stay in sync when overlaid.
tEnd = max(cellfun(@(r) r.t(end), runs));
frameDt = playbackSpeed / fps;
tFrames = (0:frameDt:tEnd)';
if tFrames(end) < tEnd
    tFrames(end+1) = tEnd;
end
nFrames = numel(tFrames);

for k = 1:numel(runs)
    runs{k}.frames = resampleRun_local(runs{k}, tFrames);
end

% ----------------------------------------------------------- view scales
allPos = cell2mat(cellfun(@(r) r.pos_plot, runs(:), 'UniformOutput', false));
padFrac = 0.1;
lims = [min(allPos); max(allPos)];
span = max(lims(2,:) - lims(1,:));
if span == 0 || isnan(span), span = 1; end

if isempty(camSpan)
    camSpan = 0.06 * span;
end
if isempty(bodyScale)
    bodyScale = 0.35 * camSpan;
end

% Fixed wide-shot bounds, used only when followCam is false.
ctr = mean(lims, 1);
half = max(span * (0.5 + padFrac), eps);
xlWide = ctr(1) + [-half, half];
ylWide = ctr(2) + [-half, half];
zlWide = [lims(1,3) - padFrac*span, lims(2,3) + padFrac*span];

% ================================================================ FIGURE
fig = figure(103); clf(fig);
if ~showLive
    set(fig, 'Visible', 'off');
end
set(fig, 'Name', 'Trajectory Animation', 'Color', 'w', 'Position', [100 100 1200 650]);

tOuter = tiledlayout(fig, 1, 2, 'TileSpacing', 'compact', 'Padding', 'compact');

% ---- left: 3D chase-cam view
ax3d = nexttile(tOuter, 1);
hold(ax3d, 'on'); grid(ax3d, 'on'); axis(ax3d, 'equal'); view(ax3d, 3);
if followCam
    xlim(ax3d, [-1 1]); ylim(ax3d, [-1 1]); zlim(ax3d, [-1 1]);   % set for real each frame
else
    xlim(ax3d, xlWide); ylim(ax3d, ylWide); zlim(ax3d, zlWide);
end
xlabel(ax3d, 'North [m]'); ylabel(ax3d, 'East [m]'); zlabel(ax3d, 'Up [m]');
title(ax3d, 'Orientation Over Trajectory');

nRuns = numel(runs);
trailH  = gobjects(1, nRuns);
markerH = gobjects(1, nRuns);
noseH   = gobjects(1, nRuns);
velH    = gobjects(1, nRuns);
for k = 1:nRuns
    c = runColors{k};
    trailH(k)  = plot3(ax3d, nan, nan, nan, '-', 'Color', c, 'LineWidth', 1.5);
    markerH(k) = plot3(ax3d, nan, nan, nan, 'o', 'Color', c, 'MarkerFaceColor', c, 'MarkerSize', 8);
    noseH(k)   = quiver3(ax3d, 0,0,0, 0,0,0, bodyScale, 'Color', noseColor, 'LineWidth', 2, 'MaxHeadSize', 0.9);
    velH(k)    = quiver3(ax3d, 0,0,0, 0,0,0, bodyScale, 'Color', velColor, 'LineWidth', 1.5, 'MaxHeadSize', 0.9);
end
plot3(ax3d, nan, nan, nan, '-', 'Color', noseColor, 'LineWidth', 2, 'DisplayName', 'Nose');
plot3(ax3d, nan, nan, nan, '-', 'Color', velColor, 'LineWidth', 1.5, 'DisplayName', 'Velocity');
if nRuns > 1
    for k = 1:nRuns
        set(trailH(k), 'DisplayName', runs{k}.label);
    end
    legend(ax3d, [trailH, findobj(ax3d, 'DisplayName', 'Nose'), findobj(ax3d, 'DisplayName', 'Velocity')], ...
        'Location', 'best');
else
    legend(ax3d, [findobj(ax3d,'DisplayName','Nose'), findobj(ax3d,'DisplayName','Velocity')], 'Location', 'best');
end

timeText = text(ax3d, 0, 0, 0, '', 'FontWeight', 'bold', 'VerticalAlignment', 'top', 'Units', 'data');

% ---- right: tilt/roll/AoA strip charts with a moving time cursor
tRight = tiledlayout(tOuter, 3, 1, 'TileSpacing', 'compact', 'Padding', 'compact');
tRight.Layout.Tile = 2;

axTilt = nexttile(tRight); hold(axTilt,'on'); grid(axTilt,'on');
ylabel(axTilt, 'Tilt [deg]'); title(axTilt, 'Tilt');
axRoll = nexttile(tRight); hold(axRoll,'on'); grid(axRoll,'on');
ylabel(axRoll, 'Roll [deg]'); title(axRoll, 'Roll');
axAoa  = nexttile(tRight); hold(axAoa,'on'); grid(axAoa,'on');
xlabel(axAoa, 'Time [s]'); ylabel(axAoa, 'AoA [deg]'); title(axAoa, 'Total AoA');

for k = 1:nRuns
    c = runColors{k};
    plot(axTilt, runs{k}.t, runs{k}.tilt_deg, '-', 'Color', c, 'LineWidth', 1);
    plot(axRoll, runs{k}.t, runs{k}.roll_deg, '-', 'Color', c, 'LineWidth', 1);
    plot(axAoa,  runs{k}.t, runs{k}.aoa_deg,  '-', 'Color', c, 'LineWidth', 1);
end
cursorH = gobjects(1,3);
cursorH(1) = xline(axTilt, 0, 'k-', 'LineWidth', 1);
cursorH(2) = xline(axRoll, 0, 'k-', 'LineWidth', 1);
cursorH(3) = xline(axAoa,  0, 'k-', 'LineWidth', 1);

% -------------------------------------------------- shared render state
S = struct( ...
    'runs',         {runs}, ...
    'trailH',       trailH, ...
    'markerH',      markerH, ...
    'noseH',        noseH, ...
    'velH',         velH, ...
    'timeText',     timeText, ...
    'cursorH',      cursorH, ...
    'ax3d',         ax3d, ...
    'tFrames',      tFrames, ...
    'nFrames',      nFrames, ...
    'followCam',    followCam, ...
    'camSpan',      camSpan, ...
    'trailSeconds', trailSeconds, ...
    'frameIdx',     1);

% ==================================================================== RUN
if saveVideo
    [videoDir] = fileparts(videoFile);
    if ~isempty(videoDir) && ~exist(videoDir, 'dir')
        mkdir(videoDir);
    end
    vw = VideoWriter(videoFile, 'MPEG-4');
    vw.FrameRate = fps;
    open(vw);
    cleanupObj = onCleanup(@() close(vw));

    for f = 1:nFrames
        updateFrameGraphics_local(f, S);
        writeVideo(vw, getframe(fig));
    end

    clear cleanupObj;   % closes the VideoWriter
    fprintf('Saved animation to %s\n', videoFile);
else
    % Interactive: render the first frame, wire up a Play/Pause button
    % driven by a timer, and return without blocking -- the figure stays
    % live and responsive after this script finishes.
    updateFrameGraphics_local(1, S);
    setappdata(fig, 'animState', S);

    animTimer = timer('ExecutionMode', 'fixedRate', 'Period', max(1/fps, 0.01), ...
        'TimerFcn', @(~,~) onTimerTick_local(fig));
    setappdata(fig, 'animTimer', animTimer);
    set(fig, 'CloseRequestFcn', @(~,~) onFigureClose_local(fig));

    uicontrol(fig, 'Style', 'pushbutton', 'String', 'Play', 'FontSize', 11, ...
        'Units', 'normalized', 'Position', [0.46 0.01 0.08 0.05], ...
        'Callback', @(src,~) onPlayPause_local(fig, src));
end

% ======================================================================
function fr = resampleRun_local(r, tFrames)
    % Resample one run's plotted/derived signals onto a common frame
    % clock, clamping to the run's own extent past its end (rockets that
    % land/end sooner than the longest overlaid run just hold their last
    % state rather than extrapolating).
    tq = min(tFrames, r.t(end));
    fr.pos_plot  = interp1(r.t, r.pos_plot,  tq, 'linear');
    fr.vel_plot  = interp1(r.t, r.vel_plot,  tq, 'linear');
    fr.nose_plot = interp1(r.t, r.nose_plot, tq, 'linear');
    fr.nose_plot = fr.nose_plot ./ vecnorm(fr.nose_plot, 2, 2);
end

% ======================================================================
function updateFrameGraphics_local(f, S)
    % Update every graphics object for frame f. Shared by the video-export
    % loop and the interactive timer callback so both stay in sync.
    tNow = S.tFrames(f);
    centers = zeros(numel(S.runs), 3);

    for k = 1:numel(S.runs)
        fr = S.runs{k}.frames;
        p = fr.pos_plot(f,:);
        centers(k,:) = p;

        if S.followCam
            tStart = max(tNow - S.trailSeconds, S.tFrames(1));
            idx0 = find(S.tFrames(1:f) >= tStart, 1, 'first');
        else
            idx0 = 1;
        end
        set(S.trailH(k), 'XData', fr.pos_plot(idx0:f,1), 'YData', fr.pos_plot(idx0:f,2), 'ZData', fr.pos_plot(idx0:f,3));
        set(S.markerH(k), 'XData', p(1), 'YData', p(2), 'ZData', p(3));

        nose = fr.nose_plot(f,:);
        set(S.noseH(k), 'XData', p(1), 'YData', p(2), 'ZData', p(3), ...
            'UData', nose(1), 'VData', nose(2), 'WData', nose(3));

        vhat = fr.vel_plot(f,:) / max(norm(fr.vel_plot(f,:)), eps);
        set(S.velH(k), 'XData', p(1), 'YData', p(2), 'ZData', p(3), ...
            'UData', vhat(1), 'VData', vhat(2), 'WData', vhat(3));
    end

    if S.followCam
        c = mean(centers, 1);
        half = S.camSpan / 2;
        xlim(S.ax3d, c(1) + [-half, half]);
        ylim(S.ax3d, c(2) + [-half, half]);
        zlim(S.ax3d, c(3) + [-half, half]);
        set(S.timeText, 'Position', [c(1)-half, c(2)+half, c(3)+half]);
    end

    set(S.timeText, 'String', sprintf('t = %.2f s', tNow));
    set(S.cursorH, 'Value', tNow);

    drawnow limitrate;
end

% ======================================================================
function onPlayPause_local(fig, btn)
    tmr = getappdata(fig, 'animTimer');
    if strcmp(get(btn, 'String'), 'Play')
        set(btn, 'String', 'Pause');
        start(tmr);
    else
        set(btn, 'String', 'Play');
        stop(tmr);
    end
end

% ======================================================================
function onTimerTick_local(fig)
    if ~ishandle(fig)
        return;
    end
    S = getappdata(fig, 'animState');
    updateFrameGraphics_local(S.frameIdx, S);

    S.frameIdx = S.frameIdx + 1;
    if S.frameIdx > S.nFrames
        S.frameIdx = 1;
        stop(getappdata(fig, 'animTimer'));
        set(findobj(fig, 'Style', 'pushbutton'), 'String', 'Play');
    end
    setappdata(fig, 'animState', S);
end

% ======================================================================
function onFigureClose_local(fig)
    tmr = getappdata(fig, 'animTimer');
    if ~isempty(tmr) && isvalid(tmr)
        stop(tmr);
        delete(tmr);
    end
    delete(fig);
end
