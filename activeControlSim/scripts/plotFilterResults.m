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
%     below). Its kf_bus sub-bus (defineBusDD.m) carries:
%       kf_Pplus     15x15  posterior covariance
%       kf_Pminus    15x15  prior covariance
%       kf_errxPlus  15x1   posterior error state
%       kf_innov     6x1    innovation errz
%       kf_K         15x6   Kalman gain
%       kf_H         6x15   measurement matrix
%       kf_S         6x6    innovation covariance
%       kf_gnssFlag  1x1    true on steps where the Update branch ran
%     kf_bus comes out of Merge2, which takes Kalman Filter/Update on
%     measurement steps and Kalman Filter/Pass Through (placeholder
%     values) otherwise, so every kf_bus quantity -- including P for the
%     sigma envelopes and NEES -- is only used at the kf_gnssFlag epochs.
%     A missing kf_bus field is skipped with a warning; S is rebuilt as
%     H*P-*H' + R when kf_S is absent. R comes from filterParams.R
%     (defineFilterDD.m) unless measR is set.
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
%                 post-fit residuals per measurement with +/-sqrt(S_ii)
%                 envelopes.
%     Figure 112: KF Residual Ratios -- innovation / sqrt(S_ii) (pre-fit)
%                 and post-fit residual ratios, histograms vs N(0,1),
%                 per-channel mean / std.
%     Figure 113: KF NIS & Whiteness -- full and per-block NIS with
%                 chi-square bounds, running average NIS, innovation
%                 autocorrelation with white-noise bounds.
%     Figure 114: KF Covariance Health -- per-state sigma (log), P
%                 symmetry error, min eigenvalue, condition numbers of P
%                 and S, trace(P), trace reduction per update, Kalman
%                 gain row norms.
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
measR       = [];               % [] = filterParams.R from defineFilterDD.m

kfLogName   = 'filter_bus';     % logged bus holding the kf_bus sub-bus (or kf_bus itself)

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

if isempty(measR)
    try
        F = defineFilterDD();
        measR = F.filterParams.R;
    catch
        warning('plotFilterResults:noR', ...
            'Could not read filterParams.R from defineFilterDD.m -- S can only come from kf_S.');
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
measLbl   = {'Pos N','Pos E','Pos D','Vel N','Vel E','Vel D'};
measUnits = {'m','m','m','m/s','m/s','m/s'};

% ------------------------------------------------------------ evaluate
nRuns = numel(outs);
kfRuns = cell(1, nRuns);
for k = 1:nRuns
    kfRuns{k} = evalRun_local(outs{k}, labels{k}, forwardAxis, kfLogName, ...
        measR, attErrFrame, maxLag);
end
noPMsg = 'no covariance at update epochs (kf_bus not logged, or no updates)';

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
tInn = tiledlayout(fig4, 3, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tInn, 'Pre-fit (o) and post-fit (x) residuals  (dotted \pm1\surdS_{ii}, dashed \pm3\surdS_{ii})');
axInn = gobjects(2, 3);
for m = 1:6
    row = ceil(m/3); col = m - 3*(row-1);
    axInn(row,col) = nexttile(tInn); hold(axInn(row,col), 'on'); grid(axInn(row,col), 'on');
    title(axInn(row,col), measLbl{m}, 'FontWeight', 'normal', 'FontSize', 8);
    if col == 1
        ylabel(axInn(row,col), {'Residual', ['[' measUnits{m} ']']}, 'FontSize', 8);
    end
end
axInnMode = addModeAxis_local(tInn, [1 3]);

anyInnov = false;
for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    stairs(axInnMode, kf.t, kf.flightMode_int, '-', 'Color', c, 'LineWidth', 1.5);
    if ~kf.hasInnov, continue; end
    anyInnov = true;
    for m = 1:min(6, kf.nz)
        row = ceil(m/3); col = m - 3*(row-1);
        ax = axInn(row,col);
        plot(ax, kf.tu, kf.nu(:,m), updStyle_local(kf.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
        if kf.hasPost
            plot(ax, kf.tu, kf.post(:,m), 'x', 'Color', c * 0.6, 'MarkerSize', 4);
        end
        if kf.hasS
            plotEnvelope_local(ax, kf.tu, kf.sigS(:,m), c);
        end
    end
end
if ~anyInnov
    for ax = axInn(:)'
        noData_local(ax, innovMissingMsg_local(kfRuns));
    end
end
linkaxes([axInn(:)', axInnMode], 'x');
addColorKeyLegend_local(kfRuns, runColors);

% ===================================================== RESIDUAL RATIOS
fig5 = figure(112); clf(fig5); set(fig5, 'Name', 'KF Residual Ratios', 'Color', 'w');
tRat = tiledlayout(fig5, 3, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tRat, 'Residual ratio  \nu_i / \surdS_{ii}  (o pre-fit, x post-fit / \surd(R - HP^+H^T)_{ii})');
axRat = gobjects(2, 3);
for m = 1:6
    row = ceil(m/3); col = m - 3*(row-1);
    axRat(row,col) = nexttile(tRat); hold(axRat(row,col), 'on'); grid(axRat(row,col), 'on');
    title(axRat(row,col), measLbl{m}, 'FontWeight', 'normal', 'FontSize', 8);
    if col == 1, ylabel(axRat(row,col), {'Ratio', '[\sigma]'}, 'FontSize', 8); end
    addLevels_local(axRat(row,col), [1 3]);
end
axHistPos = nexttile(tRat); hold(axHistPos, 'on'); grid(axHistPos, 'on');
title(axHistPos, 'Position ratios vs N(0,1)', 'FontWeight', 'normal', 'FontSize', 8);
axHistVel = nexttile(tRat); hold(axHistVel, 'on'); grid(axHistVel, 'on');
title(axHistVel, 'Velocity ratios vs N(0,1)', 'FontWeight', 'normal', 'FontSize', 8);
axRatStat = nexttile(tRat); hold(axRatStat, 'on'); grid(axRatStat, 'on');
title(axRatStat, 'Pre-fit ratio mean / std per channel', 'FontWeight', 'normal', 'FontSize', 8);

ratPool = [];
for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    if ~(kf.hasInnov && kf.hasS), continue; end
    for m = 1:min(6, kf.nz)
        row = ceil(m/3); col = m - 3*(row-1);
        plot(axRat(row,col), kf.tu, kf.ratio(:,m), updStyle_local(kf.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
        if kf.hasPostSig
            plot(axRat(row,col), kf.tu, kf.postRatio(:,m), 'x', 'Color', c * 0.6, 'MarkerSize', 4);
        end
    end
    ratPool = [ratPool; kf.ratio(:, 1:min(6, kf.nz))]; %#ok<AGROW>
end
if ~isempty(ratPool)
    plotHistVsNormal_local(axHistPos, ratPool(:, 1:min(3, end)));
    if size(ratPool, 2) >= 6
        plotHistVsNormal_local(axHistVel, ratPool(:, 4:6));
    end
    mu = mean(ratPool, 1, 'omitnan');
    sd = std(ratPool, 0, 1, 'omitnan');
    plot(axRatStat, 1:numel(mu), mu, 's', 'MarkerSize', 7, 'MarkerFaceColor', [0 0.447 0.741], 'Color', [0 0.447 0.741]);
    plot(axRatStat, 1:numel(sd), sd, 'o', 'MarkerSize', 7, 'MarkerFaceColor', [0.85 0.325 0.098], 'Color', [0.85 0.325 0.098]);
    xlim(axRatStat, [0.5, numel(mu) + 0.5]);
    yline(axRatStat, 1, 'k--', 'HandleVisibility', 'off');
    yline(axRatStat, 0, 'k-', 'HandleVisibility', 'off');
    xticks(axRatStat, 1:numel(mu)); xticklabels(axRatStat, measLbl(1:numel(mu)));
    legend(axRatStat, {'mean (want 0)', 'std (want 1)'}, 'Location', 'best', 'FontSize', 7);
else
    for ax = [axRat(:)', axHistPos, axHistVel, axRatStat]
        noData_local(ax, innovMissingMsg_local(kfRuns));
    end
end
for ax = axRat(:)'
    xlabel(ax, 'Time [s]');
end
linkaxes(axRat(:)', 'x');
addColorKeyLegend_local(kfRuns, runColors);

% ===================================================== NIS & WHITENESS
fig6 = figure(113); clf(fig6); set(fig6, 'Name', 'KF NIS & Whiteness', 'Color', 'w');
tNis = tiledlayout(fig6, 3, 2, 'TileSpacing', 'compact', 'Padding', 'compact');
title(tNis, sprintf('NIS with %.0f%% chi-square bounds, innovation whiteness', 100*confLevel));

axNisAll = nexttile(tNis, [1 2]); hold(axNisAll, 'on'); grid(axNisAll, 'on');
set(axNisAll, 'YScale', 'log'); ylabel(axNisAll, {'Full NIS'}, 'FontSize', 8);
axNisPos = nexttile(tNis); hold(axNisPos, 'on'); grid(axNisPos, 'on'); set(axNisPos, 'YScale', 'log');
title(axNisPos, 'Position NIS (dof 3)', 'FontWeight', 'normal', 'FontSize', 8);
axNisVel = nexttile(tNis); hold(axNisVel, 'on'); grid(axNisVel, 'on'); set(axNisVel, 'YScale', 'log');
title(axNisVel, 'Velocity NIS (dof 3)', 'FontWeight', 'normal', 'FontSize', 8);
axAcPos = nexttile(tNis); hold(axAcPos, 'on'); grid(axAcPos, 'on');
title(axAcPos, 'Position innovation autocorrelation', 'FontWeight', 'normal', 'FontSize', 8);
xlabel(axAcPos, 'Lag [updates]');
axAcVel = nexttile(tNis); hold(axAcVel, 'on'); grid(axAcVel, 'on');
title(axAcVel, 'Velocity innovation autocorrelation', 'FontWeight', 'normal', 'FontSize', 8);
xlabel(axAcVel, 'Lag [updates]');

compStyles = {'-', '--', ':'};
anyNis = false;
for k = 1:nRuns
    kf = kfRuns{k};
    c = runColors{k};
    if ~(kf.hasInnov && kf.hasS), continue; end
    anyNis = true;
    plot(axNisAll, kf.tu, kf.nis, updStyle_local(kf.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
    plot(axNisAll, kf.tu, runningMean_local(kf.nis), '--', 'Color', c, 'LineWidth', 1.6);
    plot(axNisPos, kf.tu, kf.nisBlk(:,1), updStyle_local(kf.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
    plot(axNisVel, kf.tu, kf.nisBlk(:,2), updStyle_local(kf.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
    for j = 1:3
        if size(kf.acf, 2) >= j
            plot(axAcPos, 0:size(kf.acf,1)-1, kf.acf(:,j), compStyles{j}, 'Color', c, 'LineWidth', 1.1, ...
                'DisplayName', dispName_local(measLbl{j}, kf.label, nRuns > 1));
        end
        if size(kf.acf, 2) >= j + 3
            plot(axAcVel, 0:size(kf.acf,1)-1, kf.acf(:,j+3), compStyles{j}, 'Color', c, 'LineWidth', 1.1, ...
                'DisplayName', dispName_local(measLbl{j+3}, kf.label, nRuns > 1));
        end
    end
end
if anyNis
    kf1 = kfRuns{find(cellfun(@(r) r.hasInnov && r.hasS, kfRuns), 1)};
    addBounds_local(axNisAll, chi2Bounds_local(kf1.nz, 1, alpha), kf1.nz);
    addBounds_local(axNisPos, chi2Bounds_local(3, 1, alpha), 3);
    addBounds_local(axNisVel, chi2Bounds_local(3, 1, alpha), 3);
    legend(axNisAll, {'NIS', 'Running avg'}, 'Location', 'best');
    for ax = [axAcPos, axAcVel]
        acBound = zConf / sqrt(max(kf1.M, 1));
        yline(ax, acBound, 'k--', 'HandleVisibility', 'off');
        yline(ax, -acBound, 'k--', 'HandleVisibility', 'off');
        legend(ax, 'Location', 'best', 'FontSize', 7);
    end
else
    for ax = [axNisAll, axNisPos, axNisVel, axAcPos, axAcVel]
        noData_local(ax, innovMissingMsg_local(kfRuns));
    end
end
linkaxes([axNisAll, axNisPos, axNisVel], 'x');
xlabel(axNisPos, 'Time [s]'); xlabel(axNisVel, 'Time [s]');
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
axCondS = newTile_local(tCov, 'cond(S)', true);
axTrRed = newTile_local(tCov, 'trace(P^-) - trace(P^+) at updates', false);
axKn    = newTile_local(tCov, 'Kalman gain row norm ||K_{i,:}|| (per state)', true);

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
    if kf.hasInnov && kf.hasS
        plot(axCondS, kf.tu, kf.condS, updStyle_local(kf.M), 'Color', c, 'MarkerSize', 4, 'LineWidth', 0.8);
    end
    if kf.hasInnov && kf.hasPm && kf.hasPp
        stem(axTrRed, kf.tu, kf.traceRed, 'Color', c, 'Marker', '.');
    end
    if kf.hasK
        for i = 1:15
            plot(axKn, kf.tu, kf.Knorm(:,i), '-', 'Color', c, 'LineWidth', 0.8);
        end
    end
end
yline(axEig, 0, 'r--', 'HandleVisibility', 'off');
if ~any(cellfun(@(r) r.hasP, kfRuns))
    for ax = [axSig, axSym, axEig, axCondP, axTrace]
        noData_local(ax, noPMsg);
    end
end
if ~any(cellfun(@(r) r.hasInnov && r.hasS, kfRuns)), noData_local(axCondS, innovMissingMsg_local(kfRuns)); end
if ~any(cellfun(@(r) r.hasInnov && r.hasPm && r.hasPp, kfRuns))
    noData_local(axTrRed, 'needs kf_Pminus, kf_Pplus and update epochs');
end
if ~any(cellfun(@(r) r.hasK, kfRuns)), noData_local(axKn, 'no gain logged (kf_K) or no updates'); end
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
    printSummary_local(kfRuns{k}, stateLbl, stateScale, measLbl, alpha, zConf);
end
if ~isempty(mc)
    b = chi2Bounds_local(mode(kfRuns{1}.neesDof), mc.n, alpha);
    fprintf('Monte Carlo (%d runs): %.1f%% of epochs have avg NEES inside [%.2f, %.2f]\n\n', ...
        mc.n, 100*mean(mc.avg >= b(1) & mc.avg <= b(2), 'omitnan'), b(1), b(2));
end

% ======================================================================
function kf = evalRun_local(out, label, forwardAxis, busName, R, attErrFrame, maxLag)
    % Truth errors for one run on the simout time grid t, plus every
    % kf_bus statistic at the measurement-update epochs only. On all
    % other steps Merge2 passes Kalman Filter/Pass Through's placeholder
    % values, so those samples are dropped rather than held or plotted.
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

    kb = getKfBus_local(out, busName);
    if isempty(kb)
        warning('plotFilterResults:noKfBus', ...
            ['%s: no kf_bus found -- only truth errors are plotted. out.logsout must have ', ...
             'a signal named ''%s'' (navigation.slx: name the filter subsystem''s output line ', ...
             'and Log Selected Signals; if the model is open, the in-memory copy is what runs) ', ...
             'containing kf_bus. Logged: %s'], ...
            label, busName, strjoin(loggedNames_local(out), ', '));
    else
        fn = {'kf_Pplus', 'kf_Pminus', 'kf_errxPlus', 'kf_innov', 'kf_K', 'kf_H', 'kf_S', 'kf_gnssFlag'};
        missing = fn(~isfield(kb, fn));
        if ~isempty(missing)
            warning('plotFilterResults:missingKfFields', ...
                '%s: not in kf_bus (skipped): %s', label, strjoin(missing, ', '));
        end
    end

    % Update epochs: logged samples where the Update branch drove Merge2.
    % Without the flag there is no way to tell real values from
    % placeholders, so nothing from kf_bus is used.
    iuLog = [];
    tu = zeros(0, 1);
    if isfield(kb, 'kf_gnssFlag')
        [fl, tLog] = busSignal_local(kb.kf_gnssFlag);
        iuLog = find(squeeze(fl(1,1,:)) > 0.5);
        tu = tLog(iuLog);
    end
    M = numel(tu);
    iu = discretize(tu, [t; inf]);   % simout sample at or before each update
    iu(isnan(iu)) = 1;

    [Pp, hasPp] = busAtUpdates_local(kb, 'kf_Pplus', iuLog);
    [Pm, hasPm] = busAtUpdates_local(kb, 'kf_Pminus', iuLog);
    [ex, hasEx] = busAtUpdates_local(kb, 'kf_errxPlus', iuLog);
    [nuA, hasNu] = busAtUpdates_local(kb, 'kf_innov', iuLog);
    [K, hasK]   = busAtUpdates_local(kb, 'kf_K', iuLog);
    [H, hasH]   = busAtUpdates_local(kb, 'kf_H', iuLog);
    [Sl, hasSl] = busAtUpdates_local(kb, 'kf_S', iuLog);
    hasPp = hasPp && M > 0; hasPm = hasPm && M > 0;

    % Posterior covariance is the one that matches the corrected estimate;
    % fall back to the prior if that is all there is.
    hasP = hasPp || hasPm;
    if hasPp
        P = Pp;
    elseif hasPm
        P = Pm;
        warning('plotFilterResults:priorOnly', ...
            '%s: kf_Pplus not logged -- NEES uses the prior covariance.', label);
    else
        P = [];
    end

    % Covariance-based quantities live on tP; with no covariance, fall
    % back to the full grid so the summary still reports the raw errors.
    if hasP
        tP = tu; dxP = dx(iu, :);
    else
        tP = t; dxP = dx;
    end
    kf = struct('label', label, 't', t, 'flightMode_int', r.flightMode_int, 'dx', dx, ...
        'tP', tP, 'dxP', dxP, 'hasP', hasP, 'hasPp', hasPp, 'hasPm', hasPm, 'hasK', false, ...
        'hasInnov', false, 'hasS', false, 'hasPost', false, 'hasPostSig', false, 'nz', 0, 'M', M, ...
        'tu', tu);

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

    % ----------------------------------------------- measurement updates
    if ~hasNu || M == 0
        return
    end

    nu = reshape(nuA, [], M).';
    nz = size(nu, 2);
    kf.hasInnov = true; kf.nz = nz; kf.nu = nu;

    % Innovation covariance: logged S, else H*P-*H' + R
    S = [];
    if hasSl
        S = Sl;
    elseif hasH && hasPm && ~isempty(R) && isequal(size(R), [nz nz])
        S = zeros(nz, nz, M);
        for j = 1:M
            S(:,:,j) = H(:,:,j) * Pm(:,:,j) * H(:,:,j).' + R;
        end
    end
    if ~isempty(S)
        kf.hasS = true;
        sigS = zeros(M, nz); nis = zeros(M, 1); nisBlk = nan(M, 2); condS = zeros(M, 1);
        for j = 1:M
            Sj = (S(:,:,j) + S(:,:,j).') / 2;
            sigS(j,:) = sqrt(max(diag(Sj), 0)).';
            nis(j) = quadForm_local(Sj, nu(j,:).');
            condS(j) = cond(Sj);
            if nz >= 6
                nisBlk(j,1) = quadForm_local(Sj(1:3,1:3), nu(j,1:3).');
                nisBlk(j,2) = quadForm_local(Sj(4:6,4:6), nu(j,4:6).');
            end
        end
        kf.sigS = sigS; kf.nis = nis; kf.nisBlk = nisBlk; kf.condS = condS;
        ratio = nu ./ sigS;
        ratio(~isfinite(ratio)) = NaN;   % S_ii <= 0 (indefinite P) has no meaningful ratio
        kf.ratio = ratio;
        kf.acf = autocorr_local(kf.ratio, maxLag);
    end

    % Post-fit residuals: nu - H*errx+ (errx- is reset to zero each step)
    if hasEx && hasH
        kf.hasPost = true;
        post = zeros(M, nz);
        for j = 1:M
            post(j,:) = (nu(j,:).' - H(:,:,j) * reshape(ex(:,:,j), [], 1)).';
        end
        kf.post = post;
        if hasPp && ~isempty(R) && isequal(size(R), [nz nz])
            kf.hasPostSig = true;
            postSig = zeros(M, nz);
            for j = 1:M
                postSig(j,:) = sqrt(max(diag(R - H(:,:,j) * Pp(:,:,j) * H(:,:,j).'), 0)).';
            end
            r0 = post ./ postSig;
            r0(~isfinite(r0)) = NaN;
            kf.postRatio = r0;
        end
    end

    if hasPm && hasPp
        kf.traceRed = arrayfun(@(k) trace(Pm(:,:,k)) - trace(Pp(:,:,k)), (1:M).');
    end
    if hasK
        kf.hasK = true;
        Kn = zeros(M, size(K, 1));
        for j = 1:M
            Kn(j,:) = vecnorm(K(:,:,j), 2, 2).';
        end
        kf.Knorm = Kn;
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
function kb = getKfBus_local(out, name)
    % The kf_bus struct of timeseries from logged signal `name` in
    % out.logsout: either filter_bus (kf_bus is its sub-bus) or kf_bus
    % logged on its own. Empty when neither is there.
    kb = [];
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
    v = el.Values;
    if ~isstruct(v), return; end
    if isfield(v, 'kf_gnssFlag')
        kb = v;
        return;
    end
    % Find the sub-bus by its contents, not its name: an unnamed line
    % into filter_bus's Bus Creator logs it as signal<N>, not kf_bus.
    f = fieldnames(v);
    for i = 1:numel(f)
        if isstruct(v.(f{i})) && isfield(v.(f{i}), 'kf_gnssFlag')
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
function printSummary_local(kf, stateLbl, stateScale, measLbl, alpha, zConf)
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

    if kf.hasInnov && kf.hasS
        b = chi2Bounds_local(kf.nz, kf.M, alpha);
        fprintf('\nNIS (dof %d, %d updates): ANIS = %.3g, bounds [%.3g, %.3g] -> %s\n', ...
            kf.nz, kf.M, mean(kf.nis), b(1), b(2), verdict_local(mean(kf.nis), b));
        fprintf('%-8s %10s %10s %12s %14s\n', 'Channel', 'ratio mean', 'ratio std', '|ratio|>3 %', 'ACF out of bnd');
        acB = zConf / sqrt(kf.M);
        for m = 1:kf.nz
            rm = kf.ratio(:,m);
            rm = rm(isfinite(rm));
            if size(kf.acf, 1) > 1
                acOut = 100 * mean(abs(kf.acf(2:end, m)) > acB);
            else
                acOut = NaN;
            end
            nm = sprintf('z%d', m);
            if m <= numel(measLbl), nm = measLbl{m}; end
            fprintf('%-8s %10.3g %10.3g %12.1f %13.1f%%\n', nm, mean(rm), std(rm), 100 * mean(abs(rm) > 3), acOut);
        end
        fprintf('(want ratio mean ~0, std ~1, ~0.3%% beyond 3, ~%.0f%% of ACF lags out of bounds)\n', 100 * (1 - erf(zConf/sqrt(2))));
    elseif kf.hasInnov
        fprintf('\nNIS: innovations logged but no S (log kf_S, or kf_H + kf_Pminus with filterParams.R).\n');
    else
        fprintf('\nNIS: no measurement updates in this run (%d update epochs).\n', kf.M);
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
function msg = innovMissingMsg_local(kfRuns)
    if any(cellfun(@(r) r.M, kfRuns) == 0)
        msg = 'no measurement updates (GNSS flag never true, or kf_innov not logged)';
    else
        msg = 'needs kf_innov and S (kf_S, or kf_H + kf_Pminus + R)';
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
