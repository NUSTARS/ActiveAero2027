%PLOTMONTECARLOCORRELATION  Spearman rank correlation between every
%   dispersed input and every output metric of a saved Monte Carlo run.
%
%   Edit the CONFIG block below, then run the script.
%
%   Reads the `mc` struct saved by scripts/runMonteCarlo.m:
%     mc.input.dispNames{d}       dispersed parameter name
%     mc.input.dispHalfWidth{d}   its +/- half-width (parameter-sized)
%     mc.input.dispOffset{d}      nRuns x numel(param) offsets drawn
%     mc.output.<metric>          nRuns x 1, one per mcPostSim metric
%     mc.output.failed            nRuns x 1, excluded from the analysis
%
%   INPUT NAMES
%     Each dispersed element with a nonzero half-width is one input,
%     named after its parameter, with an element index for arrays:
%       vehicleParams.mass_kg            scalar
%       icParams.eulIC_rad(2)            vector element
%       vehicleParams.inertia_kgm2(2,2)  matrix element
%     Inputs are the offsets from nominal (rank correlation doesn't
%     care, and the nominal isn't saved).
%
%   OPTIONS
%     matFile       results file to analyse
%     matFile2      second results file to overlay ('' = off). Each run
%                   gets its own heatmap; scatter plots overlay both,
%                   colour-coded. Inputs are offsets from each run's own
%                   nominal, so if the nominals differ the x positions
%                   aren't directly comparable.
%     runLabels     legend names for the two runs ({} = file names)
%     scatterPairs  N x 2 cell of {input name, output name} to scatter
%                   plot, input on x. Names are listed in the console on
%                   every run, so copy them from there.
%     alpha         significance level; cells with p >= alpha are blanked
%                   ('n.s.') in the heatmap. With many pairs expect about
%                   alpha * nPairs false hits -- treat this as a screen.
%     outputNames   {} = every metric (in both runs, when overlaying);
%                   otherwise only these, in this order
%     nTop          number of strongest pairs printed to the console
%
%   OUTPUT
%     Figure 303: heatmap of Spearman rho, outputs x inputs (matFile)
%     Figure 305: same for matFile2, when overlaying
%     Figure 304: scatter plots for scatterPairs, runs overlaid
%     Workspace: outputNames, runLabels, and R(s) per run with fields
%     rho, pval (outputs x inputs), inputNames, X (runs x inputs),
%     Y (runs x outputs), nRuns, nFailed
%
%   NOTES
%     - Spearman rho is computed here directly, so the Statistics and
%       Machine Learning Toolbox isn't required. p-values use the usual
%       t approximation, which is reliable for roughly 10+ runs.
%     - Spearman only sees monotonic trends: an output that rises for
%       either sign of an input (a V shape) reads near 0. Check suspected
%       pairs with scatterPairs.

% =============================================================== CONFIG
matFile      = 'monteCarloResults';   % bare names resolve against resultsDir, .mat optional
matFile2     = '';                    % second run to overlay; '' = single run
runLabels    = {};                    % legend names, e.g. {'baseline', 'new fins'}; {} = file names
resultsDir   = fullfile(fileparts(fileparts(mfilename('fullpath'))), 'results');
alpha        = 0.05;
outputNames  = {};
nTop         = 15;
scatterPairs = {
    % input                          output
    'icParams.eulIC_rad(2)',  'olPitchErrMax_pct'
    'icParams.eulIC_rad(2)',  'olPitchErrAvg_pct'
    'icParams.eulIC_rad(2)',  'olYawErrMax_pct'
    'icParams.eulIC_rad(2)',  'olYawErrAvg_pct'
};

% ------------------------------------------------------------- load
files = {matFile};
if ~isempty(matFile2)
    files{end+1} = matFile2;
end
nSets = numel(files);
mcs = cell(1, nSets);
for s = 1:nSets
    matPath = resolveMatFile_local(files{s}, resultsDir);
    S = load(matPath, 'mc');
    if ~isfield(S, 'mc') || ~isfield(S.mc, 'input') || ~isfield(S.mc, 'output')
        error('plotMonteCarloCorrelation:badFile', ...
            '%s has no mc.input / mc.output -- rerun scripts/runMonteCarlo.m.', matPath);
    end
    mcs{s} = S.mc;
    if numel(runLabels) < s
        [~, runLabels{s}] = fileparts(matPath); %#ok<SAGROW>
    end
end

% ------------------------------------------------------------- outputs
% Default: every metric present in all loaded runs.
if isempty(outputNames)
    outputNames = setdiff(fieldnames(mcs{1}.output), {'failed'}, 'stable')';
    for s = 2:nSets
        outputNames = outputNames(isfield(mcs{s}.output, outputNames));
    end
end
for s = 1:nSets
    for j = 1:numel(outputNames)
        if ~isfield(mcs{s}.output, outputNames{j})
            error('plotMonteCarloCorrelation:badOutput', 'No output metric ''%s'' in %s.', ...
                outputNames{j}, runLabels{s});
        end
    end
end

% ------------------------------------------------------------- per-run analysis
% R(s) holds run s's inputs, outputs and correlations.
R = cellfun(@(m) analyzeRun_local(m, outputNames), mcs, 'UniformOutput', false);
R = [R{:}];
for s = 1:nSets
    fprintf('\n===== %s =====\n', runLabels{s});
    fprintf('Inputs:\n');  fprintf('  %s\n', R(s).inputNames{:});
    if s == 1
        fprintf('Outputs:\n'); fprintf('  %s\n', outputNames{:});
    end
    fprintf('%d successful runs (%d failed excluded)\n', R(s).nRuns, R(s).nFailed);
    if R(s).nRuns < 10 * numel(R(s).inputNames)
        warning('plotMonteCarloCorrelation:fewRuns', ...
            ['%s: %d runs for %d inputs -- correlations are noisy below ~10 runs per input ', ...
             '(|rho| < %.2f is indistinguishable from 0 here).'], ...
            runLabels{s}, R(s).nRuns, numel(R(s).inputNames), 2/sqrt(R(s).nRuns));
    end

    % Strongest pairs, by |rho|.
    rho = R(s).rho; pval = R(s).pval;
    [~, order] = sort(abs(rho(:)), 'descend', 'MissingPlacement', 'last');
    order = order(1:min(nTop, sum(~isnan(rho(:)))));
    [iOut, iIn] = ind2sub(size(rho), order);
    topTable = table(R(s).inputNames(iIn)', outputNames(iOut)', rho(order), pval(order), ...
        'VariableNames', {'Input', 'Output', 'Rho', 'P'});
    fprintf('\nStrongest %d correlations:\n', numel(order));
    disp(topTable);
end

% ============================================================ HEATMAP
% One figure per run: 303 for the first, 305 for the overlay run.
% heatmap labels are TeX -- escape underscores so names don't subscript.
texEsc = @(c) strrep(c, '_', '\_');
heatFigNums = [303 305];
for s = 1:nSets
    fig1 = figure(heatFigNums(s)); clf(fig1);
    set(fig1, 'Name', ['Spearman Correlation - ', runLabels{s}], 'Color', 'w');
    rhoShown = R(s).rho;
    rhoShown(R(s).pval >= alpha) = NaN;
    h = heatmap(fig1, texEsc(R(s).inputNames), texEsc(outputNames), round(rhoShown, 2), ...
        'Colormap', redBlue_local(256), 'ColorLimits', [-1 1], ...
        'MissingDataLabel', 'n.s.', 'MissingDataColor', [0.94 0.94 0.94]);
    h.Title = sprintf('%s: Spearman \\rho (n = %d runs, blank if p \\geq %.2g)', ...
        texEsc(runLabels{s}), R(s).nRuns, alpha);
    h.XLabel = 'Input (offset from nominal)';
    h.YLabel = 'Output';
    h.FontSize = 8;
end

% ============================================================ SCATTER
% Runs overlaid in one tile per pair, colour-coded; the title gives each
% run's rho in its own colour. A run without that input is left out.
if ~isempty(scatterPairs)
    fig2 = figure(304); clf(fig2); set(fig2, 'Name', 'Monte Carlo Scatter', 'Color', 'w');
    runColors = lines(nSets);
    nP = size(scatterPairs, 1);
    nCol = ceil(sqrt(nP));
    tiledlayout(fig2, ceil(nP / nCol), nCol, 'TileSpacing', 'compact', 'Padding', 'compact');
    for p = 1:nP
        iOut = find(strcmp(outputNames, scatterPairs{p,2}), 1);
        if isempty(iOut)
            error('plotMonteCarloCorrelation:badPair', ...
                'scatterPairs row %d: no output ''%s'' (see the Outputs list printed above).', p, scatterPairs{p,2});
        end
        ax = nexttile; hold(ax, 'on');
        titleParts = {};
        plotted = gobjects(0);
        plottedLabels = {};
        for s = 1:nSets
            iIn = find(strcmp(R(s).inputNames, scatterPairs{p,1}), 1);
            if isempty(iIn)
                continue
            end
            plotted(end+1) = scatter(ax, R(s).X(:, iIn), R(s).Y(:, iOut), 18, runColors(s,:), ...
                'filled', 'MarkerFaceAlpha', 0.6); %#ok<SAGROW>
            plottedLabels{end+1} = runLabels{s}; %#ok<SAGROW>
            titleParts{end+1} = sprintf('{\\color[rgb]{%.3f %.3f %.3f}\\rho = %.2f, p = %.2g}', ...
                runColors(s,:), R(s).rho(iOut, iIn), R(s).pval(iOut, iIn)); %#ok<SAGROW>
        end
        if isempty(plotted)
            error('plotMonteCarloCorrelation:badPair', ...
                'scatterPairs row %d: no input ''%s'' in any run (see the Inputs lists printed above).', p, scatterPairs{p,1});
        end
        hold(ax, 'off'); grid(ax, 'on');
        xlabel(ax, [char(916), ' ', scatterPairs{p,1}], 'Interpreter', 'none');   % char(916) = Delta
        ylabel(ax, scatterPairs{p,2}, 'Interpreter', 'none');
        title(ax, strjoin(titleParts, '   '), 'FontWeight', 'normal', 'FontSize', 9);
        if nSets > 1 && p == 1
            legend(ax, plotted, plottedLabels, 'Interpreter', 'none', 'Location', 'best');
        end
    end
end

% ======================================================================
function r = analyzeRun_local(mc, outputNames)
    % Inputs (one column per dispersed element with a nonzero half-width),
    % outputs, and Spearman rho/p for one saved Monte Carlo run.
    X = [];
    inputNames = {};
    for d = 1:numel(mc.input.dispNames)
        hw = mc.input.dispHalfWidth{d};
        for k = find(hw(:)' ~= 0)
            X(:, end+1) = mc.input.dispOffset{d}(:, k); %#ok<AGROW>
            inputNames{end+1} = [mc.input.dispNames{d}, elemSuffix_local(size(hw), k)]; %#ok<AGROW>
        end
    end
    Y = cell2mat(cellfun(@(n) mc.output.(n), outputNames, 'UniformOutput', false));

    ok = ~mc.output.failed;
    r.X = X(ok, :);
    r.Y = Y(ok, :);
    r.inputNames = inputNames;
    r.nRuns = sum(ok);
    r.nFailed = sum(~ok);

    % Computed directly (no Statistics Toolbox needed). Pairwise: a metric
    % that's NaN for some runs (e.g. never reached ACTIVE) only drops those
    % runs from its own pairs.
    r.rho  = nan(numel(outputNames), numel(inputNames));
    r.pval = nan(size(r.rho));
    for j = 1:numel(outputNames)
        for i = 1:numel(inputNames)
            [r.rho(j,i), r.pval(j,i)] = spearman_local(r.X(:,i), r.Y(:,j));
        end
    end
end

% ======================================================================
function [r, p] = spearman_local(x, y)
    % Spearman rho = Pearson correlation of the (tie-averaged) ranks, over
    % rows where both are non-NaN. Two-sided p from the t approximation,
    % t = r*sqrt((n-2)/(1-r^2)) with n-2 dof, for n >= 10; below that the
    % approximation is badly overconfident, so p comes from a permutation
    % test instead.
    keep = ~isnan(x) & ~isnan(y);
    n = sum(keep);
    r = NaN; p = NaN;
    if n < 3
        return
    end
    rx = rank_local(x(keep));
    ry = rank_local(y(keep));
    rx = rx - mean(rx); ry = ry - mean(ry);
    den = sqrt(sum(rx.^2) * sum(ry.^2));
    if den == 0   % constant input or output
        return
    end
    r = sum(rx .* ry) / den;
    if n < 10
        % Fraction of random rank shufflings at least as correlated. Own
        % fixed-seed stream: repeatable, and leaves the global rng alone.
        nPerm = 20000;
        rs = RandStream('mt19937ar', 'Seed', 0);
        [~, perm] = sort(rand(rs, n, nPerm), 1);
        rPerm = (rx(perm)' * ry) / den;
        p = (sum(abs(rPerm) >= abs(r) - 1e-12) + 1) / (nPerm + 1);
        return
    end
    dof = n - 2;
    t2 = r^2 * dof / max(1 - r^2, eps);
    p = betainc(dof / (dof + t2), dof/2, 0.5);   % = 2*(1 - tcdf(|t|, dof))
end

% ======================================================================
function rk = rank_local(v)
    % Ranks 1..n, ties get the average of the ranks they span.
    [vs, idx] = sort(v);
    n = numel(v);
    rs = (1:n)';
    i = 1;
    while i <= n
        j = i;
        while j < n && vs(j+1) == vs(i)
            j = j + 1;
        end
        rs(i:j) = (i + j) / 2;
        i = j + 1;
    end
    rk = zeros(n, 1);
    rk(idx) = rs;
end

% ======================================================================
function s = elemSuffix_local(sz, k)
    % '' for a scalar, '(k)' for a vector, '(r,c)' for a matrix.
    if prod(sz) == 1
        s = '';
    elseif any(sz == 1)
        s = sprintf('(%d)', k);
    else
        [r, c] = ind2sub(sz, k);
        s = sprintf('(%d,%d)', r, c);
    end
end

% ======================================================================
function cmap = redBlue_local(n)
    % Diverging blue (-1) -> white (0) -> red (+1).
    t = linspace(0, 1, n/2)';
    blue = [0.13 0.40 0.67];
    red  = [0.70 0.09 0.17];
    cmap = [blue + t.*(1 - blue); 1 - t.*(1 - red)];
end

% ======================================================================
function p = resolveMatFile_local(name, resultsDir)
    % Bare name (no folder, .mat optional) resolves against resultsDir; a
    % path that already exists as given is used unchanged.
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
