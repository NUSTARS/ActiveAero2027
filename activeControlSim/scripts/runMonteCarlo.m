%RUNMONTECARLO  Run a batch of sims with dispersed parameters and save the
%   results.
%
%   A script, not a function -- leaves `out`, `simIn`, and `mc` in the
%   workspace, and clears its own bookkeeping variables.
%
%   Dispersions are applied per run with Simulink.SimulationInput/
%   setVariable, which overrides a data dictionary entry for that run
%   only -- nothing is written to the .sldd. Each override replaces a
%   whole top-level entry (e.g. vehicleParams) with a copy of the nominal
%   struct, so only values change and every run reuses the Fast Restart
%   compile. Only disperse values, never sizes/types/struct fields.
%
%   Current dispersions:
%     vehicleParams.mass_kg   uniform, nominal * (1 +/- massDispersion)
%
%   OPTIONS (set these in the workspace before running to override)
%     modelName       model to simulate (default 'activeControlSim')
%     nRuns           number of runs (default 100)
%     rngSeed         seed for the dispersion draws (default 0)
%     massDispersion  fractional half-width of the mass spread
%                     (default 0.10, i.e. +/-10%)
%     useParallel     run with parsim instead of sim (default false,
%                     needs Parallel Computing Toolbox)
%     forceRebuild    passed through to buildDataDictionaries.m
%                     (default false)
%     keepFullOutput  keep every run's full logged output instead of
%                     reducing it to summary metrics with
%                     helpers/mcPostSim.m (default false -- full output
%                     is slow to transfer back from parsim workers and
%                     to save)
%
%   OUTPUT
%     out   1xnRuns Simulink.SimulationOutput -- holds only the
%           mcPostSim.m metrics (e.g. out(i).apogee_m) unless
%           keepFullOutput is true
%     simIn 1xnRuns Simulink.SimulationInput (exact inputs of each run)
%     mc    struct of per-run dispersed values and summary metrics
%   all saved to results/monteCarloResults.mat, overwriting any previous
%   batch.

if ~exist('modelName','var'), modelName = 'activeControlSim'; end
if ~exist('nRuns','var'), nRuns = 100; end
if ~exist('rngSeed','var'), rngSeed = 0; end
if ~exist('massDispersion','var'), massDispersion = 0.10; end
if ~exist('useParallel','var'), useParallel = false; end
if ~exist('forceRebuild','var'), forceRebuild = false; end
if ~exist('keepFullOutput','var'), keepFullOutput = false; end

repoRoot = fileparts(fileparts(mfilename('fullpath')));
run(fullfile(repoRoot, 'setupPaths.m'));

fprintf('Building data dictionaries...\n');
buildDataDictionaries;

% Nominal values -- same source the dictionaries are built from.
P0 = definePlantDD();

%% Draw dispersions
rng(rngSeed);
mc.mass_kg = P0.vehicleParams.mass_kg * (1 + massDispersion*(2*rand(nRuns,1) - 1));

%% Build per-run inputs
simIn(1:nRuns) = Simulink.SimulationInput(modelName);
for i = 1:nRuns
    vp = P0.vehicleParams;   % not named vehicleParams -- this script runs in the base
                             % workspace, which the models can see, so that name would
                             % clash with the dictionary entry
    vp.mass_kg = mc.mass_kg(i);

    simIn(i) = simIn(i).setVariable('vehicleParams', asParam_local(vp));
    if ~keepFullOutput
        simIn(i) = simIn(i).setPostSimFcn(@mcPostSim);
    end
end

%% Simulate
fprintf('Simulating %d runs of %s...\n', nRuns, modelName);
if useParallel
    out = parsim(simIn, 'UseFastRestart', 'on', 'ShowProgress', 'on', ...
        'TransferBaseWorkspaceVariables', 'off');
else
    out = sim(simIn, 'UseFastRestart', 'on', 'ShowProgress', 'on');
end

%% Summary metrics
mc.apogee_m = nan(nRuns, 1);
mc.failed   = false(nRuns, 1);
for i = 1:nRuns
    if ~isempty(out(i).ErrorMessage)
        mc.failed(i) = true;
        fprintf('Run %d failed: %s\n', i, out(i).ErrorMessage);
        continue
    end
    if keepFullOutput
        s = mcPostSim(out(i));
    else
        s = out(i);
    end
    mc.apogee_m(i) = s.apogee_m;
end

fprintf('Apogee: mean %.1f m, std %.1f m, range [%.1f, %.1f] m (%d failed)\n', ...
    mean(mc.apogee_m, 'omitnan'), std(mc.apogee_m, 'omitnan'), ...
    min(mc.apogee_m), max(mc.apogee_m), sum(mc.failed));

figure(201); clf;
scatter(mc.mass_kg, mc.apogee_m, 'filled');
xlabel('Mass [kg]'); ylabel('Apogee [m]'); grid on;
title(sprintf('Monte Carlo: %d runs', nRuns));

%% Save
resultsDir = fullfile(repoRoot, 'results');
if ~exist(resultsDir, 'dir')
    mkdir(resultsDir);
end
resultFile = fullfile(resultsDir, 'monteCarloResults.mat');
save(resultFile, 'out', 'simIn', 'mc', 'modelName', 'rngSeed', '-v7.3');
fprintf('Saved results to %s\n', resultFile);

clear repoRoot nRuns rngSeed massDispersion useParallel forceRebuild keepFullOutput ...
    P0 i vp s resultsDir resultFile

% ======================================================================
function prm = asParam_local(value)
    % Wrap an override in a Simulink.Parameter matching
    % buildDataDictionaryFile.m, so the override has the same type as
    % the dictionary entry it replaces.
    prm = Simulink.Parameter(value);
    prm.CoderInfo.StorageClass = 'Auto';
end
