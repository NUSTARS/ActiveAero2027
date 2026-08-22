function setupPaths()
%SETUPPATHS  Add every folder in this repo to the MATLAB path (skipping
%   generated/cache/build folders), so scripts, models, and data
%   dictionaries all resolve regardless of the current folder. New
%   folders (e.g. a future models/control/) are picked up automatically
%   -- nothing here needs to name them.
%
%   Run once per MATLAB session (from anywhere):
%       run('<repoRoot>/setupPaths.m')
%   or cd into activeControlSim/ and call setupPaths.
%
%   This is required for models in particular because a model's
%   DataDictionary property resolves by bare filename via MATLAB's
%   cwd/path, not a stored path (see README.md).

% Folder name substrings to skip anywhere in the tree: version control,
% generated Simulink/code-gen artifacts, saved sim results.
EXCLUDE = {'.git', 'slprj', 'codegen', '.metadata', '_rtw'};

repoRoot = fileparts(mfilename('fullpath'));

allPaths = strsplit(genpath(repoRoot), pathsep);
allPaths = allPaths(~cellfun(@isempty, allPaths));

isExcluded = @(p) any(cellfun(@(pat) contains(p, pat), EXCLUDE));
keep = ~cellfun(isExcluded, allPaths);

addpath(allPaths{keep});

fprintf('activeControlSim paths added (%d folders).\n', sum(keep));

end
