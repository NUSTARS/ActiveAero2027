function setupPaths()
%SETUPPATHS  Add this repo's folders to the MATLAB path so scripts,
%   models, and data dictionaries all resolve regardless of the current
%   folder.
%
%   Run once per MATLAB session (from anywhere):
%       run('<repoRoot>/setupPaths.m')
%   or cd into activeControlSim/ and call setupPaths.
%
%   Adds: scripts/, scripts/helpers/, dataDictionaries/, and every
%   models/<name>/ subfolder -- the last is required because a model's
%   DataDictionary property resolves by bare filename via MATLAB's
%   cwd/path, not a stored path (see README.md).

repoRoot = fileparts(mfilename('fullpath'));

addpath(fullfile(repoRoot, 'scripts'));
addpath(fullfile(repoRoot, 'scripts', 'helpers'));
addpath(fullfile(repoRoot, 'dataDictionaries'));

modelsRoot = fullfile(repoRoot, 'models');
modelDirs = dir(modelsRoot);
modelDirs = modelDirs([modelDirs.isdir] & ~startsWith({modelDirs.name}, '.'));
for i = 1:numel(modelDirs)
    addpath(fullfile(modelsRoot, modelDirs(i).name));
end

fprintf('activeControlSim paths added.\n');

end
