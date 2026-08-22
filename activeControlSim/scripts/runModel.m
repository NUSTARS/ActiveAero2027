%RUNMODEL  Rebuild out-of-date data dictionaries, simulate a model, and
%   save the result.
%
%   A script, not a function -- it leaves `out` in the workspace so you
%   can immediately run scripts/plotRocketTrajectory.m against it, and
%   clears its own bookkeeping variables (repoRoot, resultsDir, ...) so
%   only `out` is left behind.
%
%   OPTIONS (set these in the workspace before running to override)
%     modelName      model to simulate (default 'plant')
%     forceRebuild   passed through to buildDataDictionaries.m --
%                    rebuild every dictionary regardless of timestamps
%                    (default false)
%
%   Rebuilds/links any out-of-date data dictionary in
%   scripts/buildDataDictionaries.m's CONFIG (so parameter edits are
%   always picked up before simulating), runs the model, and saves `out`
%   to results/simResults.mat, overwriting any previous run.

if ~exist('modelName','var'), modelName = 'plant'; end
if ~exist('forceRebuild','var'), forceRebuild = false; end

repoRoot = fileparts(fileparts(mfilename('fullpath')));
run(fullfile(repoRoot, 'setupPaths.m'));

fprintf('Building data dictionaries...\n');
buildDataDictionaries;

fprintf('Simulating %s...\n', modelName);
out = sim(modelName);

resultsDir = fullfile(repoRoot, 'results');
if ~exist(resultsDir, 'dir')
    mkdir(resultsDir);
end

resultFile = fullfile(resultsDir, 'simResults.mat');
save(resultFile, 'out', 'modelName');

fprintf('Saved results to %s\n', resultFile);

clear repoRoot modelName forceRebuild resultsDir resultFile
