%RUNMODEL  Rebuild out-of-date data dictionaries, simulate a model, and
%   save the result.
%
%   A script, not a function -- it leaves `out` in the workspace so you
%   can immediately run scripts/plotRocketTrajectory.m against it, and
%   clears its own bookkeeping variables (repoRoot, resultsDir, ...) so
%   only `out` is left behind.
%
%   OPTIONS
%     modelName      model to simulate (default 'activeControlSim')
%     forceRebuild   passed through to buildDataDictionaries.m --
%                    rebuild every dictionary regardless of timestamps
%                    (default true)
%     simInput       (optional, set in the workspace before running) a
%                    scalar Simulink.SimulationInput to simulate instead
%                    of the bare model -- e.g. to replay one Monte Carlo
%                    run:
%                        load results/monteCarloResults.mat simIn
%                        simInput = simIn(42);
%                        runModel
%                    modelName is taken from simInput.ModelName. simInput
%                    is cleared afterwards, so the next runModel goes back
%                    to the nominal model. Any PostSimFcn on simInput
%                    (e.g. mcPostSim) is dropped so `out` keeps the full
%                    logs for plotRocketTrajectory.m.
%
%   Rebuilds/links any out-of-date data dictionary in
%   scripts/buildDataDictionaries.m's CONFIG (so parameter edits are
%   always picked up before simulating), runs the model, and saves `out`
%   to results/simResults.mat, overwriting any previous run.

modelName = 'activeControlSim';
forceRebuild = true;

if exist('simInput', 'var')
    if ~isa(simInput, 'Simulink.SimulationInput') || ~isscalar(simInput)
        error('runModel:badSimInput', ...
            'simInput must be a scalar Simulink.SimulationInput (got a %s %s).', ...
            mat2str(size(simInput)), class(simInput));
    end
    modelName = simInput.ModelName;
    % Drop any PostSimFcn (e.g. mcPostSim from runMonteCarlo) -- it
    % replaces the logged simout with summary metrics, and the plotting
    % scripts need the full logs.
    simInput.PostSimFcn = [];
end

repoRoot = fileparts(fileparts(mfilename('fullpath')));
run(fullfile(repoRoot, 'setupPaths.m'));

fprintf('Building data dictionaries...\n');
buildDataDictionaries;

if exist('simInput', 'var')
    fprintf('Simulating %s from simInput...\n', modelName);
    out = sim(simInput);
    % sim(SimulationInput) captures errors instead of throwing -- rethrow
    % so a failed run behaves like sim(modelName) would.
    if ~isempty(out.ErrorMessage)
        error('runModel:simFailed', 'Simulation of %s failed: %s', modelName, out.ErrorMessage);
    end
else
    fprintf('Simulating %s...\n', modelName);
    out = sim(modelName);
end

resultsDir = fullfile(repoRoot, 'results');
if ~exist(resultsDir, 'dir')
    mkdir(resultsDir);
end

resultFile = fullfile(resultsDir, 'simResults.mat');
save(resultFile, 'out', 'modelName');

fprintf('Saved results to %s\n', resultFile);

clear repoRoot modelName forceRebuild resultsDir resultFile simInput
