%RUNMONTECARLO  Run a batch of sims with dispersed parameters and save the results.

modelName = 'activeControlSim';
nRuns = 500;
rngSeed = 1;

% Any numeric parameter in plantParams.sldd (definePlantDD +
% defineSensorDD), as '<entry>.<field>[.<subfield>...]', with its
% absolute dispersion in the parameter's own units. Each run adds a
% uniform random offset in [-halfWidth, +halfWidth] to the nominal value,
% drawn independently per element. halfWidth is either a scalar (same
% half-width on every element) or an array the same size as the
% parameter (per-element; 0 leaves that element fixed, e.g. the
% off-diagonals of the inertia matrix).
% Plant values computed from other parameters are recomputed after
% dispersing (see dataDictionaries/derivePlantDD.m -- e.g. disperse the
% rail angle icParams.eulIC_rad, and icParams.eul_rad follows). Anything
% derived outside derivePlantDD is not (e.g. dispersing accSigmaBias_mps2
% doesn't change accPSDGM), so disperse the value the model actually uses.
dispersions = {
    % parameter                          +/- half-width [param units]
    'vehicleParams.mass_kg',             1.0
    'vehicleParams.inertia_kgm2',        diag([0.005, 1.0, 1.0])
    'vehicleParams.cg_m',                0.06
    'icParams.eulIC_rad',                [1.0, 0.2, 0.2]   % [roll pitch yaw]
    'windParams.constantNed_mps',        [5; 5; 0]
    'aeroParams.finStaticScale_na'       0.1
    'aeroParams.finControlScale_na'      0.2
    'aeroParams.finStaticInputScale_na'  0.1
    'aeroParams.finControlInputScale_na' 0.2
    'aeroParams.bodyScale_na',           0.1
    'aeroParams.CpBaseShift_m',          0.06
    'aeroParams.finAngles1_rad'          [0.01, 0.01, 0.01]
    'aeroParams.finAngles2_rad'          [0.01, 0.01, 0.01]
    'aeroParams.finAngles3_rad'          [0.01, 0.01, 0.01]
    'aeroParams.finAngles4_rad'          [0.01, 0.01, 0.01]
    'motorParams.thrustScaling_na'       0.05
    % 'sensorParams.gyroTurnOnBias_rps',   0.009
};

useParallel = false;
keepFullOutput = false;

fprintf('Building data dictionaries...\n');
buildDataDictionaries;

% Nominal values -- same sources plantParams.sldd is built from. Not named
% after the dictionary entries -- this script runs in the base workspace,
% which the models can see, so those names would clash.
% defineSensorDD reseeds rng, so this has to come before rng(rngSeed).
P0 = mergeStructs_local(definePlantDD(), defineSensorDD());

dispNames = dispersions(:,1);
dispHalf  = dispersions(:,2);
dispPath  = cellfun(@(n) strsplit(n, '.'), dispNames, 'UniformOutput', false);
dispSize  = cell(size(dispNames));
for d = 1:numel(dispNames)
    nominal = getPath_local(P0, dispPath{d}, dispNames{d});
    if ~isnumeric(nominal)
        error('runMonteCarlo:notNumeric', ...
            '%s is a %s, not numeric -- it can''t be dispersed.', dispNames{d}, class(nominal));
    end
    dispSize{d} = size(nominal);
    if isscalar(dispHalf{d})
        dispHalf{d} = repmat(dispHalf{d}, dispSize{d});
    elseif ~isequal(size(dispHalf{d}), dispSize{d})
        error('runMonteCarlo:badHalfWidth', ...
            '%s is %s, but its half-width is %s -- use a scalar or a matching array.', ...
            dispNames{d}, mat2str(dispSize{d}), mat2str(size(dispHalf{d})));
    end
end

%% Draw dispersions
% mc.input holds what each run was given, mc.output what it produced.
% mc.input.dispOffset{d}(i,:) is run i's offset on parameter
% mc.input.dispNames{d}, one column per element (column-major, reshape to
% the parameter's size).
rng(rngSeed);
mc.input.dispNames     = dispNames;
mc.input.dispHalfWidth = dispHalf;
mc.input.dispOffset    = cell(size(dispNames));
for d = 1:numel(dispNames)
    mc.input.dispOffset{d} = dispHalf{d}(:)' .* (2*rand(nRuns, numel(dispHalf{d})) - 1);
end

%% Build per-run inputs
simIn(1:nRuns) = Simulink.SimulationInput(modelName);
for i = 1:nRuns
    runPrm = P0;
    for d = 1:numel(dispNames)
        runPrm = setfield(runPrm, dispPath{d}{:}, getfield(P0, dispPath{d}{:}) ...
            + reshape(mc.input.dispOffset{d}(i,:), dispSize{d})); %#ok<GFLD,SFLD>
    end
    runPrm = derivePlantDD(runPrm);

    % Override every dictionary entry that differs from nominal (dispersed
    % directly or via a derived value) as a whole struct.
    entryNames = fieldnames(runPrm);
    for e = 1:numel(entryNames)
        if ~isequal(runPrm.(entryNames{e}), P0.(entryNames{e}))
            simIn(i) = simIn(i).setVariable(entryNames{e}, asParam_local(runPrm.(entryNames{e})));
        end
    end
    if ~keepFullOutput
        simIn(i) = simIn(i).setPostSimFcn(@mcPostSim);
    end
    simIn(i) = simIn(i).setModelParameter('SimulationMode', 'accelerator');
end

%% Simulate
fprintf('Simulating %d runs of %s...\n', nRuns, modelName);
if useParallel
    out = parsim(simIn, 'UseFastRestart', 'on', 'TransferBaseWorkspaceVariables', 'off');
else
    out = sim(simIn, 'UseFastRestart', 'on');
end

%% Summary metrics
% Every field mcPostSim returns, taken from its all-NaN failed-run
% output so the list doesn't depend on any run succeeding.
metricNames = fieldnames(mcPostSim(struct('ErrorMessage', 'none')));
for f = 1:numel(metricNames)
    mc.output.(metricNames{f}) = nan(nRuns, 1);
end
mc.output.failed = false(nRuns, 1);
for i = 1:nRuns
    if ~isempty(out(i).ErrorMessage)
        mc.output.failed(i) = true;
        fprintf('Run %d failed: %s\n', i, out(i).ErrorMessage);
        continue
    end
    if keepFullOutput
        s = mcPostSim(out(i));
    else
        s = out(i);
    end
    for f = 1:numel(metricNames)
        mc.output.(metricNames{f})(i) = s.(metricNames{f});
    end
end

% One row per metric, statistics across the successful runs, with the
% run index each min/max came from (NaN if every run is NaN).
stats = nan(numel(metricNames), 6);
for f = 1:numel(metricNames)
    v = mc.output.(metricNames{f});
    [vMin, iMin] = min(v);
    [vMax, iMax] = max(v);
    if isnan(vMin), iMin = NaN; iMax = NaN; end
    stats(f,:) = [mean(v, 'omitnan'), std(v, 'omitnan'), vMin, iMin, vMax, iMax];
end
summaryTable = array2table(stats, 'RowNames', metricNames, ...
    'VariableNames', {'Mean', 'Std', 'Min', 'MinRun', 'Max', 'MaxRun'});

fprintf('\nMonte Carlo summary: %d runs (%d failed)\n', nRuns, sum(mc.output.failed));
disp(summaryTable);

%% Save
resultsDir = fullfile(repoRoot, 'results');
if ~exist(resultsDir, 'dir')
    mkdir(resultsDir);
end
resultFile = fullfile(resultsDir, 'monteCarloResults.mat');
save(resultFile, 'out', 'simIn', 'mc', 'summaryTable', 'modelName', 'rngSeed', '-v7.3');
fprintf('Saved results to %s\n', resultFile);

% ======================================================================
function prm = asParam_local(value)
    % Wrap an override in a Simulink.Parameter matching
    % buildDataDictionaryFile.m, so the override has the same type as
    % the dictionary entry it replaces.
    prm = Simulink.Parameter(value);
    prm.CoderInfo.StorageClass = 'Auto';
end

% ======================================================================
function M = mergeStructs_local(varargin)
    % Merge the top-level fields of each input struct into one.
    M = struct();
    for k = 1:numel(varargin)
        fn = fieldnames(varargin{k});
        for j = 1:numel(fn)
            M.(fn{j}) = varargin{k}.(fn{j});
        end
    end
end

% ======================================================================
function v = getPath_local(S, path, name)
    % Value at nested field path {f1, f2, ...} of S, with a clear error
    % naming the bad field if any level doesn't exist.
    v = S;
    for k = 1:numel(path)
        if ~isstruct(v) || ~isfield(v, path{k})
            error('runMonteCarlo:badParam', ...
                '%s: no field ''%s'' -- check the name against definePlantDD.m / defineSensorDD.m.', ...
                name, path{k});
        end
        v = v.(path{k});
    end
end
