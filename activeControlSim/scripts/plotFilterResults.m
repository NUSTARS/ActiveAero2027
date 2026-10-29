%PLOTFILTERRESULTS  Evaluate Kalman filter (error-state EKF) performance for
%   one or more logged runs: estimation errors against the filter's own
%   covariance, NEES, innovations (pre-/post-fit residuals), residual
%   ratios, NIS, innovation whiteness, and covariance health.
%
%   Edit the CONFIG block below, then run the script.
%     matFiles = {}                    evaluate `out` already in the workspace
%     matFiles = {matFile}             evaluate `out` saved in matFile
%     matFiles = {matFile1, ...}       overlay several saved runs; a file
%                                      whose `out` is an array (e.g.
%                                      runMonteCarlo.m with keepFullOutput)
%                                      contributes one run per element
%
%   With more than one run on a common time grid, Monte Carlo averaged
%   NEES / NIS are also computed and tested against their (tighter)
%   chi-square bounds.
%
%   ERROR STATE ORDER (matches filterParams.errx0 / Correct Nominal State)
%     1-3   attitude error   [rad]     (frame set by attErrFrame)
%     4-6   velocity error   [m/s]     NED
%     7-9   position error   [m]       NED
%     10-12 accel bias error [m/s^2]   body
%     13-15 gyro bias error  [rad/s]   body
%   Errors are truth - estimate, the same sign the filter injects
%   (x_true ~ x_est + errx).
%
%   WHAT IS NEEDED
%     Truth-based errors use the same buses as plotRocketTrajectory.m
%     (via helpers/extractSimRun.m): plant_bus.eom_bus truth,
%     navigation_bus estimates, sensor_bus.truth_bus biases.
%
%     Everything involving the filter's covariance or measurements also
%     needs filter_bus in out.logsout (Simulink signal logging on the
%     filter subsystem's output line in navigation.slx, named kfLogName
%     below). It carries one sub-bus per measurement update
%     (defineBusDD.m), listed in `sensors` below:
%       kf_bus_gnss   GNSS position + velocity, nz = 6, flag kf_gnssFlag
%       kf_bus_quest  QUEST attitude,          nz = 3, flag kf_questFlag
%     each with
%       kf_Pplus     15x15  posterior covariance
%       kf_Pminus    15x15  prior covariance
%       kf_errxPlus  15x1   posterior error state
%       kf_innov     nz x1  innovation errz
%       kf_K         15xnz  Kalman gain
%       kf_H         nzx15  measurement matrix
%       kf_S         nzxnz  innovation covariance
%       <flag>       1x1    true on steps where that update ran
%     Each sub-bus comes out of a Merge that takes the update branch on
%     its measurement steps and Pass Through (placeholder values)
%     otherwise, so a sub-bus is only used at its own flag epochs. The
%     covariance (sigma envelopes, NEES, covariance health) is taken at
%     the union of every sensor's epochs; where two updates share a step,
%     the smaller P+ (the later of the sequential updates) is kept. A
%     missing field is skipped with a warning; S is rebuilt as
%     H*P-*H' + R when kf_S is absent. R comes from
%     filterParams.R_GNSS / R_QUEST (defineFilterDD.m) unless measR
%     overrides it.
%
%   OUTPUT
%     Figure 108: KF State Errors -- truth - estimate per error state with
%                 the filter's +/-1 sigma (dotted) and +/-3 sigma (dashed)
%                 envelopes (at update epochs), flight mode along the
%                 bottom.
%     Figure 109: KF Normalized Errors -- error / sigma per state against
%                 +/-1 and +/-3.
%     Figure 110: KF NEES -- full-state and per-block NEES with chi-square
%                 bounds, running average NEES, Monte Carlo average.
%     Figure 111: KF Innovations -- pre-fit residuals (innovations) and
%                 post-fit residuals per measurement channel (GNSS
%                 position, GNSS velocity, QUEST attitude rows) with
%                 +/-sqrt(S_ii) envelopes.
%     Figure 112: KF Residual Ratios -- innovation / sqrt(S_ii) (pre-fit)
%                 and post-fit residual ratios, histograms vs N(0,1) per
%                 block, per-channel mean / std.
%     Figure 113: KF NIS & Whiteness -- per-sensor NIS and per-block NIS
%                 with chi-square bounds, running average NIS,
%                 innovation autocorrelation per block with white-noise
%                 bounds.
%     Figure 114: KF Covariance Health -- per-state sigma (log), P
%                 symmetry error, min eigenvalue, condition numbers of P
%                 and S, trace(P), trace reduction per update, Kalman
%                 gain row norms (S, trace reduction and gains marked
%                 per sensor).
%     Figure 115: KF Consistency Summary -- % of samples inside 1/2/3
%                 sigma per state vs the Gaussian 68.3/95.4/99.7 %, and
%                 RMS error / RMS sigma per state (1 = consistent).
%     A per-run text summary (bias, RMS, sigma ratio, sigma-bound
%     coverage, ANEES/ANIS pass/fail, whiteness) is printed to the
%     command window.
%
%   NOTES
%     - NEES > upper bound: the filter is overconfident (P too small /
%       Q or R too small). NEES < lower bound: overly conservative.
%       Same reading for NIS against S.
%     - Chi-square quantiles use gammaincinv (base MATLAB), so the
%       Statistics Toolbox is not required.
%     - Attitude error is the small-angle vector of the rotation between
%       true and estimated attitude. attErrFrame = 'nav' is the psi-angle
%       (NED) convention the F matrix in stateTransition uses
%       (C_nb_true = (I + [dpsi x]) C_nb_est); 'body' is
%       C_nb_true = C_nb_est (I + [dtheta x]). It must match how Correct
%       quaternion injects errpsi, or attitude NEES will be meaningless.
%     - A singular P (e.g. P0 = 1e-4*ones(15)) is inverted with pinv, so
%       NEES then only covers the directions P actually spans.

% =============================================================== CONFIG
resultsDir  = fullfile(fileparts(fileparts(mfilename('fullpath'))), 'results');
matFiles    = {'simResults'};   % {} = use `out` already in the workspace; bare names resolve against resultsDir, .mat optional
forwardAxis = [1;0;0];
confLevel   = 0.95;             % two-sided confidence for chi-square / whiteness bounds
attErrFrame = 'nav';            % 'nav' (psi-angle, NED) or 'body'
maxLag      = 25;               % autocorrelation lags (in measurement updates)
measR       = struct();         % R overrides by sensor name, e.g. measR.GNSS = eye(6); unset = filterParams.R_<name>

kfLogName   = 'filter_bus';     % logged bus holding the kf_bus_* sub-buses

% ------------------------------------------------------------ load runs
outs = {};
labels = {};
if isempty(matFiles)
    if ~exist('out', 'var')
        error('plotFilterResults:noOut', ...
            ['No .mat file given and `out` not found in the workspace -- ', ...
             'run scripts/runModel.m first.']);
    end
    [outs, labels] = expandOut_local(out, 'workspace');
else
    for k = 1:numel(matFiles)
        matFilePath = resolveMatFile_local(matFiles{k}, resultsDir);
        S = load(matFilePath, 'out');
        if ~isfield(S, 'out')
            error('plotFilterResults:noOutInFile', ...
                '%s does not contain an ''out'' variable.', matFilePath);
        end
        [~, label] = fileparts(matFilePath);
        [o, l] = expandOut_local(S.out, label);
        outs = [outs, o]; %#ok<AGROW>
        labels = [labels, l]; %#ok<AGROW>
    end
end

% ------------------------------------------------------- state metadata
grpNames = {'Attitude', 'Velocity', 'Position', 'Accel Bias', 'Gyro Bias'};
grpUnits = {'deg', 'm/s', 'm', 'm/s^2', 'deg/s'};
grpScale = [180/pi, 1, 1, 1, 180/pi];     % plotting scale from SI
if strcmpi(attErrFrame, 'nav')
    attLbl = {'N','E','D'};
else
    attLbl = {'x','y','z'};
end
grpComp  = {attLbl, {'N','E','D'}, {'N','E','D'}, {'x','y','z'}, {'x','y','z'}};
stateLbl = cell(1, 15);
stateScale = zeros(1, 15);
for g = 1:5
    for j = 1:3
        stateLbl{(g-1)*3 + j} = sprintf('%s %s [%s]', grpNames{g}, grpComp{g}{j}, grpUnits{g});
        stateScale((g-1)*3 + j) = grpScale(g);
    end
end
% Measurement updates, one per kf_bus_* sub-bus of filter_bus. Each is
% found by its flag element, not its name. scale converts the innovation
% to plotting units; blocks group channels into 3-vectors for the
% per-block NIS, histograms and autocorrelation.
sensors = struct( ...
    'name',   {'GNSS', 'QUEST'}, ...
    'flag',   {'kf_gnssFlag', 'kf_questFlag'}, ...
    'rField', {'R_GNSS', 'R_QUEST'}, ...
    'lbl',    {{'Pos N','Pos E','Pos D','Vel N','Vel E','Vel D'}, strcat('Att', {' '}, attLbl)}, ...
    'units',  {{'m','m','m','m/s','m/s','m/s'}, {'deg','deg','deg'}}, ...
    'scale',  {ones(1, 6), (180/pi) * ones(1, 3)}, ...
    'blocks', {{'Position', 1:3; 'Velocity', 4:6}, {'Attitude', 1:3}}, ...
    'R',      {[], []});
nSens = numel(sensors);

try
    F = defineFilterDD();
catch
    F = [];
end
for s = 1:nSens
    if isfield(measR, sensors(s).name)
        sensors(s).R = measR.(sensors(s).name);
    elseif ~isempty(F) && isfield(F.filterParams, sensors(s).rField)
        sensors(s).R = F.filterParams.(sensors(s).rField);
    else
        warning('plotFilterResults:noR', ...
            'Could not read filterParams.%s from defineFilterDD.m -- %s S can only come from kf_S.', ...
            sensors(s).rField, sensors(s).name);
    end
end

% Every measurement channel and 3-channel block, in plotting order
% (k = the block's index within its sensor).
chan = struct('s', {}, 'm', {}, 'lbl', {});
blk  = struct('s', {}, 'k', {}, 'name', {}, 'idx', {});
for s = 1:nSens
    for m = 1:numel(sensors(s).lbl)
        chan(end+1) = struct('s', s, 'm', m, 'lbl', sensors(s).lbl{m}); %#ok<SAGROW>
    end
    for b = 1:size(sensors(s).blocks, 1)
        blk(end+1) = struct('s', s, 'k', b, 'name', sensors(s).blocks{b,1}, ...
            'idx', sensors(s).blocks{b,2}); %#ok<SAGROW>
    end
end
nChan = numel(chan);
nBlk  = numel(blk);
sensMk = {'o', '^', 's', 'd'};   % per-sensor marker where sensors share an axes
sensMk = sensMk(1 + mod(0:nSens-1, numel(sensMk)));
sensKey = strjoin(strcat(sensMk, {' '}, {sensors.name}), ', ');

% ------------------------------------------------------------ evaluate
nRuns = numel(outs);
kfRuns = cell(1, nRuns);
for k = 1:nRuns
    kfRuns{k} = evalRun_local(outs{k}, labels{k}, forwardAxis, kfLogName, ...
        sensors, attErrFrame, maxLag);
end
noPMsg = 'no covariance at update epochs (no kf_bus_* sub-bus logged, or no updates)';

% Negative NEES/NIS on log axes warn while plotting; fixLogAxes_local
% switches those axes to linear afterwards, so the warning is noise.
logWarn = warning('off', 'MATLAB:Axes:NegativeDataInLogAxis');

runColors = [{[0 0.4470 0.7410], [0.8500 0.3250 0.0980]}, ...
    num2cell(lines(max(nRuns, 2)), 2)'];
runColors = runColors(1:max(nRuns, 2));

alpha = 1 - confLevel;
zConf = sqrt(2) * erfinv(confLevel);

% ======================================================= STATE ERRORS
fig1 = figure(108); clf(fig1); set(fig1, 'Name', 'KF State Errors', 'Color', 'w');
tErr = tiledlayout(fig1, 6, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tErr, 'Truth - Estimate  (dotted \pm1\sigma, dashed \pm3\sigma)');
axErr = gobjects(5, 3);
for g = 1:5
    for j = 1:3
        axErr(g,j) = nexttile(tErr); hold(axErr(g,j), 'on'); grid(axErr(g,j), 'on');
        title(axErr(g,j), grpComp{g}{j}, 'FontWeight', 'normal', 'FontSize', 8);
        if j == 1, ylabel(axErr(g,j), {grpNames{g}, ['[' grpUnits{g} ']']}, 'FontSize', 8); end
    end
end
axErrMode = addModeAxis_local(tErr, [1 3]);

for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    for g = 1:5
        for j = 1:3
            i = (g-1)*3 + j;
            plot(axErr(g,j), kf.t, kf.dx(:,i) * stateScale(i), '-', 'Color', c, 'LineWidth', 1.1);
            if kf.hasP
                plotEnvelope_local(axErr(g,j), kf.tP, kf.sig(:,i) * stateScale(i), c);
            end
        end
    end
    stairs(axErrMode, kf.t, kf.flightMode_int, '-', 'Color', c, 'LineWidth', 1.5);
end
linkaxes([axErr(:)', axErrMode], 'x');
addColorKeyLegend_local(kfRuns, runColors);

% ================================================== NORMALIZED ERRORS
fig2 = figure(109); clf(fig2); set(fig2, 'Name', 'KF Normalized Errors', 'Color', 'w');
tNrm = tiledlayout(fig2, 5, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tNrm, 'Normalized Error  (truth - estimate) / \sigma');
axNrm = gobjects(5, 3);
for g = 1:5
    for j = 1:3
        i = (g-1)*3 + j;
        axNrm(g,j) = nexttile(tNrm); hold(axNrm(g,j), 'on'); grid(axNrm(g,j), 'on');
        if j == 1, ylabel(axNrm(g,j), {grpNames{g}, '[\sigma]'}, 'FontSize', 8); end
        if g == 5, xlabel(axNrm(g,j), 'Time [s]'); end
        cov3 = nan(1, nRuns);
        for k = 1:nRuns
            kf = kfRuns{k};
            if kf.hasP
                plot(axNrm(g,j), kf.tP, kf.nrm(:,i), updStyle_local(kf.M), 'Color', runColors{k}, 'MarkerSize', 4, 'LineWidth', 0.8);
                cov3(k) = kf.inSig(i, 3);
            end
        end
        title(axNrm(g,j), sprintf('%s  (%.1f%% in 3\\sigma)', grpComp{g}{j}, mean(cov3, 'omitnan')), ...
            'FontWeight', 'normal', 'FontSize', 8);
        addLevels_local(axNrm(g,j), [1 3]);
        if ~any(cellfun(@(r) r.hasP, kfRuns))
            noData_local(axNrm(g,j), noPMsg);
        end
    end
end
linkaxes(axNrm(:)', 'x');
addColorKeyLegend_local(kfRuns, runColors);

% ================================================================ NEES
fig3 = figure(110); clf(fig3); set(fig3, 'Name', 'KF NEES', 'Color', 'w');
tNees = tiledlayout(fig3, 5, 2, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tNees, sprintf('NEES with %.0f%% chi-square bounds', 100*confLevel));

axNeesAll = nexttile(tNees, [1 2]); hold(axNeesAll, 'on'); grid(axNeesAll, 'on');
set(axNeesAll, 'YScale', 'log');
ylabel(axNeesAll, {'Full-state','NEES'}, 'FontSize', 8);
axNeesBlk = gobjects(1, 5);
for b = 1:5
    axNeesBlk(b) = nexttile(tNees); hold(axNeesBlk(b), 'on'); grid(axNeesBlk(b), 'on');
    set(axNeesBlk(b), 'YScale', 'log');
    title(axNeesBlk(b), sprintf('%s NEES (dof 3)', grpNames{b}), 'FontWeight', 'normal', 'FontSize', 8);
end
axNeesMC = nexttile(tNees); hold(axNeesMC, 'on'); grid(axNeesMC, 'on');
set(axNeesMC, 'YScale', 'log');
axNeesMode = addModeAxis_local(tNees, [1 2]);

for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    stairs(axNeesMode, kf.t, kf.flightMode_int, '-', 'Color', c, 'LineWidth', 1.5);
    if ~kf.hasP, continue; end
    plot(axNeesAll, kf.tP, kf.nees, updStyle_local(kf.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
    plot(axNeesAll, kf.tP, runningMean_local(kf.nees), '--', 'Color', c, 'LineWidth', 1.6);
    for b = 1:5
        plot(axNeesBlk(b), kf.tP, kf.neesBlk(:,b), updStyle_local(kf.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
        plot(axNeesBlk(b), kf.tP, runningMean_local(kf.neesBlk(:,b)), '--', 'Color', c, 'LineWidth', 1.6);
    end
end
if any(cellfun(@(r) r.hasP, kfRuns))
    nDofAll = mode(kfRuns{find(cellfun(@(r) r.hasP, kfRuns), 1)}.neesDof);
    addBounds_local(axNeesAll, chi2Bounds_local(nDofAll, 1, alpha), nDofAll);
    for b = 1:5
        addBounds_local(axNeesBlk(b), chi2Bounds_local(3, 1, alpha), 3);
    end
    legend(axNeesAll, {'NEES', 'Running avg'}, 'Location', 'best');
else
    noData_local(axNeesAll, noPMsg);
end

% Monte Carlo average NEES across runs, when they share a time grid
mc = mcAverage_local(kfRuns, 'nees', 'tP');
if ~isempty(mc)
    plot(axNeesMC, mc.t, mc.avg, '-', 'Color', [0.2 0.2 0.2], 'LineWidth', 1.2);
    nDofAll = mode(kfRuns{1}.neesDof);
    addBounds_local(axNeesMC, chi2Bounds_local(nDofAll, mc.n, alpha), nDofAll);
    title(axNeesMC, sprintf('Monte Carlo avg NEES (%d runs)', mc.n), 'FontWeight', 'normal', 'FontSize', 8);
else
    title(axNeesMC, 'Monte Carlo avg NEES', 'FontWeight', 'normal', 'FontSize', 8);
    noData_local(axNeesMC, 'needs 2+ runs with the same update epochs');
end
linkaxes([axNeesAll, axNeesBlk, axNeesMC, axNeesMode], 'x');
addColorKeyLegend_local(kfRuns, runColors);

% ========================================================= INNOVATIONS
fig4 = figure(111); clf(fig4); set(fig4, 'Name', 'KF Innovations', 'Color', 'w');
tInn = tiledlayout(fig4, nBlk + 1, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tInn, 'Pre-fit (o) and post-fit (x) residuals  (dotted \pm1\surdS_{ii}, dashed \pm3\surdS_{ii})');
axInn = chanTiles_local(tInn, sensors, blk, @(u) {'Residual', ['[' u ']']});
axInnMode = addModeAxis_local(tInn, [1 3]);

for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    stairs(axInnMode, kf.t, kf.flightMode_int, '-', 'Color', c, 'LineWidth', 1.5);
    for s = 1:nSens
        mz = kf.meas{s};
        if ~mz.hasInnov, continue; end
        sc = sensors(s).scale;
        for m = 1:min(numel(axInn{s}), mz.nz)
            ax = axInn{s}(m);
            plot(ax, mz.tu, mz.nu(:,m) * sc(m), updStyle_local(mz.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
            if mz.hasPost
                plot(ax, mz.tu, mz.post(:,m) * sc(m), 'x', 'Color', c * 0.6, 'MarkerSize', 4);
            end
            if mz.hasS
                plotEnvelope_local(ax, mz.tu, mz.sigS(:,m) * sc(m), c);
            end
        end
    end
end
for s = 1:nSens
    if ~any(cellfun(@(r) r.meas{s}.hasInnov, kfRuns))
        for ax = axInn{s}
            noData_local(ax, measMissingMsg_local(kfRuns, s));
        end
    end
end
linkaxes([axInn{:}, axInnMode], 'x');
addColorKeyLegend_local(kfRuns, runColors);

% ===================================================== RESIDUAL RATIOS
fig5 = figure(112); clf(fig5); set(fig5, 'Name', 'KF Residual Ratios', 'Color', 'w');
tRat = tiledlayout(fig5, nBlk + ceil(nBlk/3) + 1, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tRat, 'Residual ratio  \nu_i / \surdS_{ii}  (o pre-fit, x post-fit / \surd(R - HP^+H^T)_{ii})');
axRat = chanTiles_local(tRat, sensors, blk, @(u) {'Ratio', '[\sigma]'});
for ax = [axRat{:}]
    addLevels_local(ax, [1 3]);
end
axHist = gobjects(1, nBlk);
for b = 1:nBlk
    axHist(b) = nexttile(tRat, 3*nBlk + b); hold(axHist(b), 'on'); grid(axHist(b), 'on');
    title(axHist(b), sprintf('%s %s ratios vs N(0,1)', sensors(blk(b).s).name, blk(b).name), ...
        'FontWeight', 'normal', 'FontSize', 8);
end
axRatStat = nexttile(tRat, [1 3]); hold(axRatStat, 'on'); grid(axRatStat, 'on');
title(axRatStat, 'Pre-fit ratio mean / std per channel', 'FontWeight', 'normal', 'FontSize', 8);

ratPool = cell(1, nSens);
for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    for s = 1:nSens
        mz = kf.meas{s};
        if ~(mz.hasInnov && mz.hasS), continue; end
        nm = min(numel(axRat{s}), mz.nz);
        for m = 1:nm
            plot(axRat{s}(m), mz.tu, mz.ratio(:,m), updStyle_local(mz.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
            if mz.hasPostSig
                plot(axRat{s}(m), mz.tu, mz.postRatio(:,m), 'x', 'Color', c * 0.6, 'MarkerSize', 4);
            end
        end
        ratPool{s} = [ratPool{s}; mz.ratio(:, 1:nm)];
    end
end
for b = 1:nBlk
    pool = ratPool{blk(b).s};
    if size(pool, 2) >= max(blk(b).idx)
        plotHistVsNormal_local(axHist(b), pool(:, blk(b).idx));
    else
        noData_local(axHist(b), measMissingMsg_local(kfRuns, blk(b).s));
    end
end
for s = 1:nSens
    if isempty(ratPool{s})
        for ax = axRat{s}
            noData_local(ax, measMissingMsg_local(kfRuns, s));
        end
    end
end
mu = nan(1, nChan);
sd = nan(1, nChan);
for i = 1:nChan
    pool = ratPool{chan(i).s};
    if size(pool, 2) >= chan(i).m
        mu(i) = mean(pool(:, chan(i).m), 'omitnan');
        sd(i) = std(pool(:, chan(i).m), 0, 'omitnan');
    end
end
if any(isfinite(mu))
    plot(axRatStat, 1:nChan, mu, 's', 'MarkerSize', 7, 'MarkerFaceColor', [0 0.447 0.741], 'Color', [0 0.447 0.741]);
    plot(axRatStat, 1:nChan, sd, 'o', 'MarkerSize', 7, 'MarkerFaceColor', [0.85 0.325 0.098], 'Color', [0.85 0.325 0.098]);
    yline(axRatStat, 1, 'k--', 'HandleVisibility', 'off');
    yline(axRatStat, 0, 'k-', 'HandleVisibility', 'off');
    legend(axRatStat, {'mean (want 0)', 'std (want 1)'}, 'Location', 'best', 'FontSize', 7);
else
    noData_local(axRatStat, 'no measurement updates with innovations and S');
end
xlim(axRatStat, [0.5, nChan + 0.5]);
xticks(axRatStat, 1:nChan); xticklabels(axRatStat, {chan.lbl});
for ax = [axRat{:}]
    xlabel(ax, 'Time [s]');
end
linkaxes([axRat{:}], 'x');
addColorKeyLegend_local(kfRuns, runColors);

% ===================================================== NIS & WHITENESS
fig6 = figure(113); clf(fig6); set(fig6, 'Name', 'KF NIS & Whiteness', 'Color', 'w');
tNis = tiledlayout(fig6, 3, nBlk, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tNis, sprintf('NIS with %.0f%% chi-square bounds, innovation whiteness', 100*confLevel));

% One NIS tile per sensor, spanning the columns of its blocks below
axNisS = gobjects(1, nSens);
for s = 1:nSens
    axNisS(s) = nexttile(tNis, [1 sum([blk.s] == s)]); hold(axNisS(s), 'on'); grid(axNisS(s), 'on');
    set(axNisS(s), 'YScale', 'log');
    title(axNisS(s), sprintf('%s NIS (dof %d)', sensors(s).name, numel(sensors(s).lbl)), ...
        'FontWeight', 'normal', 'FontSize', 8);
end
axNisB = gobjects(1, nBlk);
for b = 1:nBlk
    axNisB(b) = nexttile(tNis); hold(axNisB(b), 'on'); grid(axNisB(b), 'on');
    set(axNisB(b), 'YScale', 'log'); xlabel(axNisB(b), 'Time [s]');
    title(axNisB(b), sprintf('%s %s NIS (dof %d)', sensors(blk(b).s).name, blk(b).name, numel(blk(b).idx)), ...
        'FontWeight', 'normal', 'FontSize', 8);
end
axAc = gobjects(1, nBlk);
for b = 1:nBlk
    axAc(b) = nexttile(tNis); hold(axAc(b), 'on'); grid(axAc(b), 'on');
    title(axAc(b), sprintf('%s %s innovation autocorrelation', sensors(blk(b).s).name, blk(b).name), ...
        'FontWeight', 'normal', 'FontSize', 8);
    xlabel(axAc(b), 'Lag [updates]');
end

compStyles = {'-', '--', ':'};
for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    for s = 1:nSens
        mz = kf.meas{s};
        if ~(mz.hasInnov && mz.hasS), continue; end
        plot(axNisS(s), mz.tu, mz.nis, updStyle_local(mz.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
        plot(axNisS(s), mz.tu, runningMean_local(mz.nis), '--', 'Color', c, 'LineWidth', 1.6);
        for b = find([blk.s] == s)
            plot(axNisB(b), mz.tu, mz.nisBlk(:, blk(b).k), updStyle_local(mz.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
            for j = 1:numel(blk(b).idx)
                m = blk(b).idx(j);
                if size(mz.acf, 2) >= m
                    plot(axAc(b), 0:size(mz.acf,1)-1, mz.acf(:,m), compStyles{j}, 'Color', c, 'LineWidth', 1.1, ...
                        'DisplayName', dispName_local(sensors(s).lbl{m}, kf.label, nRuns > 1));
                end
            end
        end
    end
end
for s = 1:nSens
    iRun = find(cellfun(@(r) r.meas{s}.hasInnov && r.meas{s}.hasS, kfRuns), 1);
    bs = find([blk.s] == s);
    if isempty(iRun)
        for ax = [axNisS(s), axNisB(bs), axAc(bs)]
            noData_local(ax, measMissingMsg_local(kfRuns, s));
        end
        continue
    end
    mz1 = kfRuns{iRun}.meas{s};
    addBounds_local(axNisS(s), chi2Bounds_local(mz1.nz, 1, alpha), mz1.nz);
    legend(axNisS(s), {'NIS', 'Running avg'}, 'Location', 'best');
    for b = bs
        dof = numel(blk(b).idx);
        addBounds_local(axNisB(b), chi2Bounds_local(dof, 1, alpha), dof);
        acBound = zConf / sqrt(max(mz1.M, 1));
        yline(axAc(b), acBound, 'k--', 'HandleVisibility', 'off');
        yline(axAc(b), -acBound, 'k--', 'HandleVisibility', 'off');
        legend(axAc(b), 'Location', 'best', 'FontSize', 7);
    end
end
linkaxes([axNisS, axNisB], 'x');
addColorKeyLegend_local(kfRuns, runColors);

% =================================================== COVARIANCE HEALTH
fig7 = figure(114); clf(fig7); set(fig7, 'Name', 'KF Covariance Health', 'Color', 'w');
tCov = tiledlayout(fig7, 4, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tCov, 'Covariance health');

axSig = gobjects(1, 5);
for g = 1:5
    axSig(g) = nexttile(tCov); hold(axSig(g), 'on'); grid(axSig(g), 'on'); set(axSig(g), 'YScale', 'log');
    title(axSig(g), {sprintf('%s \\sigma [%s]', grpNames{g}, grpUnits{g}), ...
        sprintf('solid %s, dashed %s, dotted %s', grpComp{g}{:})}, 'FontWeight', 'normal', 'FontSize', 8);
end
axSym   = newTile_local(tCov, '||P - P^T|| / ||P||', true);
axEig   = newTile_local(tCov, 'min eig(P)  (must stay > 0)', false);
axCondP = newTile_local(tCov, 'cond(P)', true);
axTrace = newTile_local(tCov, 'trace(P^-) dashed, trace(P^+) solid', true);
axCondS = newTile_local(tCov, sprintf('cond(S)  (%s)', sensKey), true);
axTrRed = newTile_local(tCov, sprintf('trace(P^-) - trace(P^+) at updates  (%s)', sensKey), false);
axKn    = newTile_local(tCov, sprintf('Kalman gain row norm ||K_{i,:}|| per state  (%s)', sensKey), true);

for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    if kf.hasP
        for g = 1:5
            for j = 1:3
                i = (g-1)*3 + j;
                plot(axSig(g), kf.tP, kf.sig(:,i) * stateScale(i), compStyles{j}, 'Color', c, 'LineWidth', 1.1);
            end
        end
        plot(axSym,   kf.tP, kf.symErr, '-', 'Color', c, 'LineWidth', 1.1);
        plot(axEig,   kf.tP, kf.minEig, '-', 'Color', c, 'LineWidth', 1.1);
        plot(axCondP, kf.tP, kf.condP,  '-', 'Color', c, 'LineWidth', 1.1);
        plot(axTrace, kf.tP, kf.traceP, '-', 'Color', c, 'LineWidth', 1.1);
    end
    if kf.hasPm
        plot(axTrace, kf.tP, kf.traceM, '--', 'Color', c, 'LineWidth', 1.1);
    end
    for s = 1:nSens
        mz = kf.meas{s};
        mk = measStyle_local(mz.M, sensMk{s});
        if mz.hasInnov && mz.hasS
            plot(axCondS, mz.tu, mz.condS, mk, 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
        end
        if mz.hasTrRed
            stem(axTrRed, mz.tu, mz.traceRed, 'Color', c, 'Marker', sensMk{s}, 'MarkerSize', 4);
        end
        if mz.hasK
            for i = 1:15
                plot(axKn, mz.tu, mz.Knorm(:,i), mk, 'Color', c, 'MarkerSize', 3, 'LineWidth', 0.8);
            end
        end
    end
end
yline(axEig, 0, 'r--', 'HandleVisibility', 'off');
if ~any(cellfun(@(r) r.hasP, kfRuns))
    for ax = [axSig, axSym, axEig, axCondP, axTrace]
        noData_local(ax, noPMsg);
    end
end
anyMeas_local = @(fld) any(cellfun(@(r) any(cellfun(@(mz) mz.(fld), r.meas)), kfRuns));
if ~anyMeas_local('hasS'), noData_local(axCondS, 'needs kf_innov and S from at least one update'); end
if ~anyMeas_local('hasTrRed')
    noData_local(axTrRed, 'needs kf_Pminus, kf_Pplus and update epochs');
end
if ~anyMeas_local('hasK'), noData_local(axKn, 'no gain logged (kf_K) or no updates'); end
linkaxes([axSig, axSym, axEig, axCondP, axTrace, axCondS, axTrRed, axKn], 'x');
addColorKeyLegend_local(kfRuns, runColors);

% ================================================= CONSISTENCY SUMMARY
fig8 = figure(115); clf(fig8); set(fig8, 'Name', 'KF Consistency Summary', 'Color', 'w');
tSum = tiledlayout(fig8, 2, 1, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tSum, sprintf('Consistency summary, pooled over %d run(s)', nRuns));
axCov = nexttile(tSum); hold(axCov, 'on'); grid(axCov, 'on');
ylabel(axCov, 'Samples inside k\sigma [%]');
axRms = nexttile(tSum); hold(axRms, 'on'); grid(axRms, 'on');
ylabel(axRms, 'RMS error / RMS \sigma');

shortLbl = cellfun(@(s) regexprep(s, '\s*\[.*\]$', ''), stateLbl, 'UniformOutput', false);
pooled = poolStates_local(kfRuns);
if ~isempty(pooled)
    bar(axCov, pooled.inSig, 'grouped');
    expect = 100 * erf((1:3) / sqrt(2));
    labelAlign = {'left', 'left', 'right'};   % 95.4 and 99.7 sit close together
    for s = 1:3
        yline(axCov, expect(s), '--', sprintf('%.1f%%', expect(s)), 'HandleVisibility', 'off', ...
            'LabelHorizontalAlignment', labelAlign{s}, 'FontSize', 7);
    end
    legend(axCov, {'1\sigma', '2\sigma', '3\sigma'}, 'Location', 'eastoutside');
    ylim(axCov, [0 105]);
    bar(axRms, pooled.rmsRatio);
    yline(axRms, 1, 'k--', 'consistent', 'HandleVisibility', 'off', 'FontSize', 7);
    set(axRms, 'YScale', 'log');
else
    noData_local(axCov, noPMsg);
    noData_local(axRms, noPMsg);
end
for ax = [axCov, axRms]
    xticks(ax, 1:15); xticklabels(ax, shortLbl); xtickangle(ax, 35);
end

% Log axes can't show values <= 0. A negative NEES/NIS or quadratic form
% means P or S is not positive definite, so keep those points visible.
fixLogAxes_local([fig3, fig6, fig7, fig8]);
warning(logWarn);

% ======================================================== TEXT SUMMARY
for k = 1:nRuns
    printSummary_local(kfRuns{k}, stateLbl, stateScale, sensors, alpha, zConf);
end
if ~isempty(mc)
    b = chi2Bounds_local(mode(kfRuns{1}.neesDof), mc.n, alpha);
    fprintf('Monte Carlo (%d runs): %.1f%% of epochs have avg NEES inside [%.2f, %.2f]\n\n', ...
        mc.n, 100*mean(mc.avg >= b(1) & mc.avg <= b(2), 'omitnan'), b(1), b(2));
end

% ======================================================================
function kf = evalRun_local(out, label, forwardAxis, busName, sensors, attErrFrame, maxLag)
    % Truth errors for one run on the simout time grid t, each
    % measurement update's statistics at its own update epochs
    % (kf.meas{s}), and the filter covariance at the union of those
    % epochs. On all other steps each sub-bus's Merge passes Pass
    % Through's placeholder values, so those samples are dropped rather
    % than held or plotted.
    r = extractSimRun(out, label, forwardAxis);
    t = r.t;
    N = numel(t);
    toNed = @(v) [v(:,1), v(:,2), -v(:,3)];   % plot frame (Up) -> NED

    qEst = r.qEst_na ./ vecnorm(r.qEst_na, 2, 2);
    dx = [attError_local(r.q_na, qEst, attErrFrame), ...
          toNed(r.vel_plot - r.velEst_plot), ...
          toNed(r.pos_plot - r.posEst_plot), ...
          r.accelBiasTrue_mps2 - r.accelBiasEst_mps2, ...
          r.gyroBiasTrue_rps - r.gyroBiasEst_rps];

    fb = getFilterBus_local(out, busName);
    nS = numel(sensors);
    meas = cell(1, nS);
    found = false(1, nS);
    for s = 1:nS
        kb = findSubBus_local(fb, sensors(s).flag);
        found(s) = ~isempty(kb);
        meas{s} = evalMeas_local(kb, sensors(s), maxLag, label);
    end
    if ~any(found)
        warning('plotFilterResults:noKfBus', ...
            ['%s: no kf_bus_* sub-bus found -- only truth errors are plotted. out.logsout must have ', ...
             'a signal named ''%s'' (navigation.slx: name the filter subsystem''s output line ', ...
             'and Log Selected Signals; if the model is open, the in-memory copy is what runs) ', ...
             'containing sub-buses with %s. Logged: %s'], ...
            label, busName, strjoin({sensors.flag}, ' / '), strjoin(loggedNames_local(out), ', '));
    elseif ~all(found)
        warning('plotFilterResults:noMeasBus', '%s: no sub-bus with %s in %s -- skipped.', ...
            label, strjoin({sensors(~found).flag}, ', '), busName);
    end

    % Covariance at every sensor's update epochs. Where two updates share
    % a step they ran one after the other, so keep the smaller P+ (the
    % one after both). Posterior covariance is the one that matches the
    % corrected estimate; fall back to the prior if that is all there is.
    upd = cellfun(@(mz) mz.M > 0, meas);
    hasPp = any(upd) && all(cellfun(@(mz) mz.hasPp, meas(upd)));
    hasPm = any(upd) && all(cellfun(@(mz) mz.hasPm, meas(upd)));
    hasP = hasPp || (any(upd) && all(cellfun(@(mz) mz.hasPp || mz.hasPm, meas(upd))));
    tP = zeros(0, 1); P = zeros(15, 15, 0); Pm = zeros(15, 15, 0);
    if hasP
        for s = find(upd)
            mz = meas{s};
            if hasPp, Ps = mz.Pp; else, Ps = mz.Pm; end
            if hasPm, Pms = mz.Pm; else, Pms = nan(15, 15, mz.M); end
            tP = [tP; mz.tu]; %#ok<AGROW>
            P = cat(3, P, Ps);
            Pm = cat(3, Pm, Pms);
        end
        Pd = reshape(P, 225, []);
        trP = sum(Pd(1:16:225, :), 1).';
        [~, ord] = sortrows([tP, trP], [1, -2]);   % by time, larger trace first
        [tP, keep] = unique(tP(ord), 'last');
        P = P(:, :, ord(keep));
        Pm = Pm(:, :, ord(keep));
        if ~hasPp
            warning('plotFilterResults:priorOnly', ...
                '%s: kf_Pplus not logged -- NEES uses the prior covariance.', label);
        end
    end
    M = numel(tP);

    % Covariance-based quantities live on tP; with no covariance, fall
    % back to the full grid so the summary still reports the raw errors.
    if hasP
        iu = discretize(tP, [t; inf]);   % simout sample at or before each update
        iu(isnan(iu)) = 1;
        dxP = dx(iu, :);
    else
        tP = t; dxP = dx;
    end
    kf = struct('label', label, 't', t, 'flightMode_int', r.flightMode_int, 'dx', dx, ...
        'tP', tP, 'dxP', dxP, 'hasP', hasP, 'hasPp', hasPp, 'hasPm', hasPm, 'M', M, ...
        'meas', {meas});

    % ------------------------------------------- covariance-based metrics
    if hasP
        Pd = reshape(P, 225, M);
        sig = sqrt(max(Pd(1:16:225, :), 0)).';
        nrm = dxP ./ sig;
        nrm(~isfinite(nrm)) = NaN;

        nees = nan(M, 1); neesDof = zeros(M, 1); neesBlk = nan(M, 5);
        symErr = nan(M, 1); minEig = nan(M, 1); condP = nan(M, 1); traceP = nan(M, 1);
        for k = 1:M
            Pk = P(:,:,k);
            nP = norm(Pk, 'fro');
            if nP > 0, symErr(k) = norm(Pk - Pk.', 'fro') / nP; end
            Ps = (Pk + Pk.') / 2;
            minEig(k) = min(eig(Ps));
            condP(k)  = cond(Ps);
            traceP(k) = trace(Ps);

            v = ~isnan(dxP(k,:)) & sig(k,:) > 0;
            if any(v)
                nees(k) = quadForm_local(Ps(v,v), dxP(k,v).');
                neesDof(k) = sum(v);
            end
            for b = 1:5
                ib = (b-1)*3 + (1:3);
                if all(v(ib))
                    neesBlk(k,b) = quadForm_local(Ps(ib,ib), dxP(k,ib).');
                end
            end
        end
        inSig = zeros(15, 3);
        for i = 1:15
            ok = ~isnan(nrm(:,i));
            for s = 1:3
                inSig(i,s) = 100 * mean(abs(nrm(ok,i)) <= s);
            end
        end
        kf.P = P; kf.sig = sig; kf.nrm = nrm; kf.nees = nees; kf.neesDof = neesDof;
        kf.neesBlk = neesBlk; kf.inSig = inSig; kf.symErr = symErr; kf.minEig = minEig;
        kf.condP = condP; kf.traceP = traceP;
    else
        kf.sig = nan(N, 15); kf.nrm = nan(N, 15); kf.nees = nan(N, 1); kf.neesDof = 15*ones(N,1);
        kf.neesBlk = nan(N, 5); kf.inSig = nan(15, 3);
    end
    if hasPm
        PmD = reshape(Pm, 225, M);
        kf.traceM = sum(PmD(1:16:225, :), 1).';
    end
end

% ======================================================================
function mz = evalMeas_local(kb, sen, maxLag, label)
    % One measurement update's sub-bus (kf_bus_gnss, kf_bus_quest, ...)
    % at the samples where its flag is true. Without the flag there is no
    % way to tell real values from Pass Through's placeholders, so
    % nothing from the sub-bus is used.
    mz = struct('name', sen.name, 'M', 0, 'tu', zeros(0, 1), 'nz', 0, ...
        'hasPp', false, 'hasPm', false, 'hasInnov', false, 'hasS', false, ...
        'hasPost', false, 'hasPostSig', false, 'hasK', false, 'hasTrRed', false);
    if isempty(kb), return; end
    fn = {'kf_Pplus', 'kf_Pminus', 'kf_errxPlus', 'kf_innov', 'kf_K', 'kf_H', 'kf_S'};
    missing = fn(~isfield(kb, fn));
    if ~isempty(missing)
        warning('plotFilterResults:missingKfFields', ...
            '%s: not in the %s sub-bus (skipped): %s', label, sen.name, strjoin(missing, ', '));
    end

    [fl, tLog] = busSignal_local(kb.(sen.flag));
    iuLog = find(squeeze(fl(1,1,:)) > 0.5);
    M = numel(iuLog);
    mz.M = M;
    mz.tu = tLog(iuLog);
    if M == 0, return; end

    [Pp, mz.hasPp] = busAtUpdates_local(kb, 'kf_Pplus', iuLog);
    [Pm, mz.hasPm] = busAtUpdates_local(kb, 'kf_Pminus', iuLog);
    [ex, hasEx]    = busAtUpdates_local(kb, 'kf_errxPlus', iuLog);
    [nuA, hasNu]   = busAtUpdates_local(kb, 'kf_innov', iuLog);
    [K, hasK]      = busAtUpdates_local(kb, 'kf_K', iuLog);
    [H, hasH]      = busAtUpdates_local(kb, 'kf_H', iuLog);
    [Sl, hasSl]    = busAtUpdates_local(kb, 'kf_S', iuLog);
    mz.Pp = Pp; mz.Pm = Pm;

    if mz.hasPm && mz.hasPp
        mz.hasTrRed = true;
        mz.traceRed = arrayfun(@(k) trace(Pm(:,:,k)) - trace(Pp(:,:,k)), (1:M).');
    end
    if hasK
        mz.hasK = true;
        Kn = zeros(M, size(K, 1));
        for j = 1:M
            Kn(j,:) = vecnorm(K(:,:,j), 2, 2).';
        end
        mz.Knorm = Kn;
    end
    if ~hasNu
        return
    end

    nu = reshape(nuA, [], M).';
    nz = size(nu, 2);
    mz.hasInnov = true; mz.nz = nz; mz.nu = nu;
    R = sen.R;
    hasR = ~isempty(R) && isequal(size(R), [nz nz]);

    % Innovation covariance: logged S, else H*P-*H' + R
    S = [];
    if hasSl
        S = Sl;
    elseif hasH && mz.hasPm && hasR
        S = zeros(nz, nz, M);
        for j = 1:M
            S(:,:,j) = H(:,:,j) * Pm(:,:,j) * H(:,:,j).' + R;
        end
    end
    if ~isempty(S)
        mz.hasS = true;
        nBk = size(sen.blocks, 1);
        sigS = zeros(M, nz); nis = zeros(M, 1); nisBlk = nan(M, nBk); condS = zeros(M, 1);
        for j = 1:M
            Sj = (S(:,:,j) + S(:,:,j).') / 2;
            sigS(j,:) = sqrt(max(diag(Sj), 0)).';
            nis(j) = quadForm_local(Sj, nu(j,:).');
            condS(j) = cond(Sj);
            for b = 1:nBk
                ib = sen.blocks{b,2};
                if max(ib) <= nz
                    nisBlk(j,b) = quadForm_local(Sj(ib,ib), nu(j,ib).');
                end
            end
        end
        mz.sigS = sigS; mz.nis = nis; mz.nisBlk = nisBlk; mz.condS = condS;
        ratio = nu ./ sigS;
        ratio(~isfinite(ratio)) = NaN;   % S_ii <= 0 (indefinite P) has no meaningful ratio
        mz.ratio = ratio;
        mz.acf = autocorr_local(ratio, maxLag);
    end

    % Post-fit residuals: nu - H*errx+ (errx- is reset to zero each step)
    if hasEx && hasH
        mz.hasPost = true;
        post = zeros(M, nz);
        for j = 1:M
            post(j,:) = (nu(j,:).' - H(:,:,j) * reshape(ex(:,:,j), [], 1)).';
        end
        mz.post = post;
        if mz.hasPp && hasR
            mz.hasPostSig = true;
            postSig = zeros(M, nz);
            for j = 1:M
                postSig(j,:) = sqrt(max(diag(R - H(:,:,j) * Pp(:,:,j) * H(:,:,j).'), 0)).';
            end
            r0 = post ./ postSig;
            r0(~isfinite(r0)) = NaN;
            mz.postRatio = r0;
        end
    end
end

% ======================================================================
function dAtt = attError_local(qTrue, qEst, frame)
    % Small-angle attitude error vector (rotation vector of the error
    % DCM), truth relative to estimate. q are scalar-first body<-NED.
    N = size(qTrue, 1);
    dAtt = nan(N, 3);
    for k = 1:N
        if any(isnan(qEst(k,:))), continue; end
        Ct = quat2dcm_local(qTrue(k,:));   % body <- NED
        Ce = quat2dcm_local(qEst(k,:));
        if strcmpi(frame, 'nav')
            E = Ct.' * Ce;     % C_nb_true * C_bn_est = I + [dpsi x]
        else
            E = Ce * Ct.';     % C_bn_est * C_nb_true = I + [dtheta x]
        end
        v = [E(3,2) - E(2,3); E(1,3) - E(3,1); E(2,1) - E(1,2)] / 2;
        s = norm(v);
        ang = atan2(s, (trace(E) - 1) / 2);
        if s > 1e-12
            v = v * ang / s;
        end
        dAtt(k,:) = v.';
    end
end

% ======================================================================
function v = getFilterBus_local(out, name)
    % The logged bus `name` in out.logsout as a struct of timeseries, or
    % empty when it is not there.
    v = [];
    try
        ds = out.logsout;
    catch
        return;
    end
    if ~isa(ds, 'Simulink.SimulationData.Dataset') || ~any(strcmp(ds.getElementNames, name))
        return;
    end
    el = ds.getElement(name);
    if isa(el, 'Simulink.SimulationData.Dataset')
        el = el.getElement(1);
    end
    if isstruct(el.Values)
        v = el.Values;
    end
end

% ======================================================================
function kb = findSubBus_local(v, flag)
    % The sub-bus of v that carries the element `flag` (or v itself when
    % that sub-bus was logged on its own). Found by contents, not name:
    % an unnamed line into filter_bus's Bus Creator logs as signal<N>.
    % Empty when absent.
    kb = [];
    if ~isstruct(v), return; end
    if isfield(v, flag)
        kb = v;
        return;
    end
    f = fieldnames(v);
    for i = 1:numel(f)
        if isstruct(v.(f{i})) && isfield(v.(f{i}), flag)
            kb = v.(f{i});
            return;
        end
    end
end

% ======================================================================
function names = loggedNames_local(out)
    % Names of everything in out.logsout, '<unnamed>' for blank ones.
    names = {'(no logsout)'};
    try
        names = out.logsout.getElementNames';
    catch
        return;
    end
    names(cellfun(@isempty, names)) = {'<unnamed>'};
    if isempty(names), names = {'(nothing)'}; end
end

% ======================================================================
function [d, tt] = busSignal_local(ts)
    % One logged bus element as an n x m x Nt array (vectors are n x 1 x
    % Nt) on its own time vector, keeping the last value at duplicated
    % time stamps.
    d  = double(ts.Data);
    tt = ts.Time(:);
    Nt = numel(tt);
    if ndims(d) == 3 && size(d, 3) == Nt
        % already n x m x Nt
    elseif ismatrix(d) && size(d, 1) == Nt
        d = reshape(d.', size(d, 2), 1, Nt);
    else
        error('plotFilterResults:shape', '%s: unexpected data size %s.', ts.Name, mat2str(size(d)));
    end
    [tt, iu] = unique(tt, 'last');
    d = d(:, :, iu);
end

% ======================================================================
function [A, ok] = busAtUpdates_local(kb, field, iuLog)
    % kf_bus element `field` at the update samples iuLog (indices into
    % the bus's own logged time vector, shared by every element).
    A = []; ok = false;
    if ~isfield(kb, field) || isempty(iuLog), return; end
    d = busSignal_local(kb.(field));
    A = d(:, :, iuLog);
    ok = true;
end

% ======================================================================
function q = quadForm_local(A, e)
    % e' * inv(A) * e, falling back to the pseudo-inverse when A is
    % singular or badly conditioned (e.g. a rank-deficient P0).
    if rcond(A) > 1e-12
        q = e.' * (A \ e);
    else
        q = e.' * pinv(A) * e;
    end
end

% ======================================================================
function b = chi2Bounds_local(dof, nAvg, alpha)
    % Two-sided bounds for the average of nAvg independent chi-square(dof)
    % variables: chi2inv(p, nAvg*dof) / nAvg. gammaincinv keeps this free
    % of the Statistics Toolbox (chi2inv(p,k) = 2*gammaincinv(p,k/2)).
    k = nAvg * dof;
    b = 2 * gammaincinv([alpha/2, 1 - alpha/2], k/2) / nAvg;
end

% ======================================================================
function addBounds_local(ax, b, dof)
    yline(ax, b(1), 'k--', 'HandleVisibility', 'off');
    yline(ax, b(2), 'k--', sprintf('%.2f-%.2f', b(1), b(2)), 'HandleVisibility', 'off', ...
        'FontSize', 7, 'LabelHorizontalAlignment', 'left');
    yline(ax, dof, 'k:', 'HandleVisibility', 'off');   % expected value
end

% ======================================================================
function addLevels_local(ax, levels)
    for L = levels
        style = ':';
        if L >= 3, style = '--'; end
        yline(ax,  L, ['k' style], 'HandleVisibility', 'off');
        yline(ax, -L, ['k' style], 'HandleVisibility', 'off');
    end
end

% ======================================================================
function plotEnvelope_local(ax, t, sig, c)
    % +/-1 sigma dotted, +/-3 sigma dashed, in a lightened run color.
    cl = c + (1 - c) * 0.45;
    plot(ax, t,  sig,   ':',  'Color', cl, 'LineWidth', 1, 'HandleVisibility', 'off');
    plot(ax, t, -sig,   ':',  'Color', cl, 'LineWidth', 1, 'HandleVisibility', 'off');
    plot(ax, t,  3*sig, '--', 'Color', cl, 'LineWidth', 1, 'HandleVisibility', 'off');
    plot(ax, t, -3*sig, '--', 'Color', cl, 'LineWidth', 1, 'HandleVisibility', 'off');
end

% ======================================================================
function plotHistVsNormal_local(ax, x)
    x = x(:);
    x = x(isfinite(x));
    if isempty(x), return; end
    histogram(ax, x, 'Normalization', 'pdf', 'FaceColor', [0.6 0.7 0.85], 'EdgeColor', 'none');
    xs = linspace(min(-4, min(x)), max(4, max(x)), 200);
    plot(ax, xs, exp(-xs.^2/2) / sqrt(2*pi), 'k-', 'LineWidth', 1.4);
    xlabel(ax, sprintf('ratio  (mean %.2f, std %.2f, n=%d)', mean(x), std(x), numel(x)), 'FontSize', 8);
end

% ======================================================================
function acf = autocorr_local(X, maxLag)
    % Sample autocorrelation of each column of X (mean removed), lags
    % 0..maxLag. Columns with fewer than 3 finite samples are NaN.
    nLag = min(maxLag, size(X, 1) - 1);
    acf = nan(max(nLag, 0) + 1, size(X, 2));
    for c = 1:size(X, 2)
        x = X(:, c);
        x = x(isfinite(x));
        if numel(x) < 3, continue; end
        x = x - mean(x);
        d = sum(x.^2);
        for L = 0:min(nLag, numel(x) - 1)
            acf(L+1, c) = sum(x(1:end-L) .* x(1+L:end)) / d;
        end
    end
end

% ======================================================================
function y = runningMean_local(x)
    ok = isfinite(x);
    y = cumsum(x .* ok) ./ max(cumsum(ok), 1);
    y(cumsum(ok) == 0) = NaN;
end

% ======================================================================
function mc = mcAverage_local(kfRuns, field, tField)
    % Average `field` across runs at each epoch, when 2+ runs with that
    % field share one time grid. Empty otherwise.
    mc = [];
    ok = cellfun(@(r) r.hasP, kfRuns);
    runs = kfRuns(ok);
    if numel(runs) < 2, return; end
    t0 = runs{1}.(tField);
    for k = 2:numel(runs)
        tk = runs{k}.(tField);
        if numel(tk) ~= numel(t0) || max(abs(tk - t0)) > 1e-9, return; end
    end
    X = cell2mat(cellfun(@(r) r.(field)(:), runs, 'UniformOutput', false));
    mc = struct('t', t0, 'avg', mean(X, 2), 'n', numel(runs));
end

% ======================================================================
function p = poolStates_local(kfRuns)
    % Pool normalized errors / errors / sigmas across runs for the summary.
    ok = cellfun(@(r) r.hasP, kfRuns);
    if ~any(ok), p = []; return; end
    nrm = cell2mat(cellfun(@(r) r.nrm, kfRuns(ok)', 'UniformOutput', false));
    dx  = cell2mat(cellfun(@(r) r.dxP, kfRuns(ok)', 'UniformOutput', false));
    sig = cell2mat(cellfun(@(r) r.sig, kfRuns(ok)', 'UniformOutput', false));
    p.inSig = zeros(15, 3);
    p.rmsRatio = zeros(15, 1);
    for i = 1:15
        v = isfinite(nrm(:,i));
        for s = 1:3
            p.inSig(i,s) = 100 * mean(abs(nrm(v,i)) <= s);
        end
        p.rmsRatio(i) = sqrt(mean(dx(v,i).^2)) / sqrt(mean(sig(v,i).^2));
    end
end

% ======================================================================
function printSummary_local(kf, stateLbl, stateScale, sensors, alpha, zConf)
    fprintf('\n================ Kalman filter evaluation: %s ================\n', kf.label);
    fprintf('%-22s %11s %11s %11s %8s %6s %6s %6s\n', 'State', 'Mean err', 'RMS err', ...
        'RMS sigma', 'RMS/sig', '<1s%', '<2s%', '<3s%');
    for i = 1:15
        e = kf.dxP(:,i);
        v = isfinite(e);
        sg = kf.sig(v,i);
        rmsE = sqrt(mean(e(v).^2)) * stateScale(i);
        rmsS = sqrt(mean(sg.^2)) * stateScale(i);
        fprintf('%-22s %11.4g %11.4g %11.4g %8.3g %6.1f %6.1f %6.1f\n', stateLbl{i}, ...
            mean(e(v)) * stateScale(i), rmsE, rmsS, rmsE / rmsS, kf.inSig(i,1), kf.inSig(i,2), kf.inSig(i,3));
    end
    if kf.hasP
        fprintf('(at the %d update epochs; Gaussian expectation: 68.3 / 95.4 / 99.7 %%)\n', kf.M);
    else
        fprintf('(Gaussian expectation: 68.3 / 95.4 / 99.7 %%)\n');
    end

    if kf.hasP
        dof = mode(kf.neesDof);
        v = isfinite(kf.nees);
        n = sum(v);
        b = chi2Bounds_local(dof, n, alpha);
        b1 = chi2Bounds_local(dof, 1, alpha);
        fprintf('\nNEES (dof %d): ANEES = %.3g, bounds [%.3g, %.3g] -> %s; %.1f%% of samples inside per-sample bounds [%.3g, %.3g]\n', ...
            dof, mean(kf.nees(v)), b(1), b(2), verdict_local(mean(kf.nees(v)), b), ...
            100 * mean(kf.nees(v) >= b1(1) & kf.nees(v) <= b1(2)), b1(1), b1(2));
        blkNames = {'Attitude', 'Velocity', 'Position', 'Accel Bias', 'Gyro Bias'};
        for bI = 1:5
            x = kf.neesBlk(:, bI);
            x = x(isfinite(x));
            if isempty(x), continue; end
            bb = chi2Bounds_local(3, numel(x), alpha);
            fprintf('  %-11s ANEES = %9.3g  bounds [%.3g, %.3g] -> %s\n', blkNames{bI}, mean(x), bb(1), bb(2), ...
                verdict_local(mean(x), bb));
        end
    else
        fprintf('\nNEES: no covariance logged.\n');
    end

    anyNis = false;
    for s = 1:numel(kf.meas)
        mz = kf.meas{s};
        sen = sensors(s);
        if mz.hasInnov && mz.hasS
            anyNis = true;
            b = chi2Bounds_local(mz.nz, mz.M, alpha);
            fprintf('\n%s NIS (dof %d, %d updates): ANIS = %.3g, bounds [%.3g, %.3g] -> %s\n', ...
                sen.name, mz.nz, mz.M, mean(mz.nis), b(1), b(2), verdict_local(mean(mz.nis), b));
            fprintf('%-8s %10s %10s %12s %14s\n', 'Channel', 'ratio mean', 'ratio std', '|ratio|>3 %', 'ACF out of bnd');
            acB = zConf / sqrt(mz.M);
            for m = 1:mz.nz
                rm = mz.ratio(:,m);
                rm = rm(isfinite(rm));
                if size(mz.acf, 1) > 1
                    acOut = 100 * mean(abs(mz.acf(2:end, m)) > acB);
                else
                    acOut = NaN;
                end
                nm = sprintf('z%d', m);
                if m <= numel(sen.lbl), nm = sen.lbl{m}; end
                fprintf('%-8s %10.3g %10.3g %12.1f %13.1f%%\n', nm, mean(rm), std(rm), 100 * mean(abs(rm) > 3), acOut);
            end
        elseif mz.hasInnov
            fprintf('\n%s NIS: innovations logged but no S (log kf_S, or kf_H + kf_Pminus with filterParams.%s).\n', ...
                sen.name, sen.rField);
        else
            fprintf('\n%s NIS: no measurement updates in this run.\n', sen.name);
        end
    end
    if anyNis
        fprintf('(want ratio mean ~0, std ~1, ~0.3%% beyond 3, ~%.0f%% of ACF lags out of bounds)\n', 100 * (1 - erf(zConf/sqrt(2))));
    end
    fprintf('\n');
end

% ======================================================================
function s = verdict_local(val, b)
    if val > b(2)
        s = 'OVERCONFIDENT (P/S too small)';
    elseif val < b(1)
        s = 'CONSERVATIVE (P/S too large)';
    else
        s = 'consistent';
    end
end

% ======================================================================
function msg = measMissingMsg_local(kfRuns, s)
    name = kfRuns{1}.meas{s}.name;
    if all(cellfun(@(r) r.meas{s}.M, kfRuns) == 0)
        msg = sprintf('no %s updates (flag never true, or its sub-bus not logged)', name);
    else
        msg = sprintf('needs %s kf_innov and S (kf_S, or kf_H + kf_Pminus + R)', name);
    end
end

% ======================================================================
function axCh = chanTiles_local(tl, sensors, blk, yLabelFcn)
    % One tile per measurement channel, one row of three per block.
    % axCh{s}(m) is channel m of sensor s; yLabelFcn(unit) is the y label
    % of each row's first tile.
    axCh = arrayfun(@(sen) gobjects(1, numel(sen.lbl)), sensors, 'UniformOutput', false);
    for b = 1:numel(blk)
        s = blk(b).s;
        for j = 1:numel(blk(b).idx)
            m = blk(b).idx(j);
            ax = nexttile(tl, 3*(b-1) + j); hold(ax, 'on'); grid(ax, 'on');
            title(ax, sprintf('%s %s', sensors(s).name, sensors(s).lbl{m}), 'FontWeight', 'normal', 'FontSize', 8);
            if j == 1
                ylabel(ax, yLabelFcn(sensors(s).units{m}), 'FontSize', 8);
            end
            axCh{s}(m) = ax;
        end
    end
end

% ======================================================================
function ax = newTile_local(tl, ttl, logY)
    ax = nexttile(tl); hold(ax, 'on'); grid(ax, 'on');
    title(ax, ttl, 'FontWeight', 'normal', 'FontSize', 8);
    if logY, set(ax, 'YScale', 'log'); end
end

% ======================================================================
function fixLogAxes_local(figs)
    % Switch a log-scaled axes to linear (and say so in its title) when
    % any of its plotted data is <= 0.
    for ax = findobj(figs, 'Type', 'axes', 'YScale', 'log')'
        y = get(findobj(ax, '-property', 'YData'), 'YData');
        if iscell(y), y = [y{:}]; end
        y = y(isfinite(y));
        if any(y <= 0)
            set(ax, 'YScale', 'linear');
            ttl = cellstr(ax.Title.String);
            ttl{end} = [ttl{end}, '  (linear: data \leq 0)'];
            ax.Title.String = ttl;
        end
    end
end

% ======================================================================
function s = updStyle_local(M)
    % Connected markers for sparse updates; dots alone once dense enough
    % that connecting lines would fill the axes.
    if M > 200
        s = '.';
    else
        s = 'o-';
    end
end

% ======================================================================
function s = measStyle_local(M, mk)
    % updStyle_local with a per-sensor marker, for axes several sensors
    % share.
    if M > 200
        s = mk;
    else
        s = [mk '-'];
    end
end

% ======================================================================
function noData_local(ax, msg)
    text(ax, 0.5, 0.5, msg, 'Units', 'normalized', 'HorizontalAlignment', 'center', ...
        'Color', [0.5 0.5 0.5], 'FontSize', 8, 'Interpreter', 'none');
end

% ======================================================================
function axM = addModeAxis_local(tl, span)
    % Flight-mode lane across the bottom, as in plotRocketTrajectory.m.
    axM = nexttile(tl, span); hold(axM, 'on'); grid(axM, 'on');
    try
        [modeEnums, modeNames] = enumeration('flightMode');
        modeVals = double(modeEnums);
        yticks(axM, modeVals); yticklabels(axM, modeNames);
        ylim(axM, [min(modeVals) - 0.5, max(modeVals) + 0.5]);
    catch
    end
    ylabel(axM, 'Flight Mode', 'FontSize', 8); xlabel(axM, 'Time [s]');
end

% ======================================================================
function [outs, labels] = expandOut_local(out, label)
    % One run per element of `out` (a Monte Carlo batch is an array).
    n = numel(out);
    outs = cell(1, n);
    labels = cell(1, n);
    for i = 1:n
        outs{i} = out(i);
        if n == 1
            labels{i} = label;
        else
            labels{i} = sprintf('%s #%d', label, i);
        end
    end
end

% ======================================================================
function s = dispName_local(base, runLabel, multiRun)
    if multiRun
        s = sprintf('%s (%s)', base, runLabel);
    else
        s = base;
    end
end

% ======================================================================
function addColorKeyLegend_local(runs, runColors)
    % One legend, in the current figure, mapping each run's label to its
    % color. No-op for a single run.
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
function R = quat2dcm_local(q)
    % scalar-first quaternion [q0 q1 q2 q3], body <- NED
    q0=q(1); q1=q(2); q2=q(3); q3=q(4);
    R = [1-2*(q2^2+q3^2),   2*(q1*q2+q0*q3),   2*(q1*q3-q0*q2);
         2*(q1*q2-q0*q3),   1-2*(q1^2+q3^2),   2*(q2*q3+q0*q1);
         2*(q1*q3+q0*q2),   2*(q2*q3-q0*q1),   1-2*(q1^2+q2^2)];
end

% ======================================================================
function p = resolveMatFile_local(name, resultsDir)
    % Accepts a bare run name (no folder, .mat optional) and resolves it
    % against resultsDir; a path that already exists as given is used
    % unchanged.
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
