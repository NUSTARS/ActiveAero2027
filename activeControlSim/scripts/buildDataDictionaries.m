%BUILDDATADICTIONARIES  Build and link a data dictionary to one or more
%   models, for each entry in CONFIG below -- but only if the dictionary
%   is out of date (its .sldd is older than the define*.m that generates
%   it, or older than any of that define function's extra data
%   dependencies, e.g. a .mat file it loads).
%
%   OPTIONS (set in the workspace before running to override)
%     forceRebuild   rebuild every dictionary regardless of timestamps
%                    (default false)

if ~exist('forceRebuild','var'), forceRebuild = false; end

% dictName        defineFcn        modelFiles (relative to repo root)  extraDeps (relative to repo root)
CONFIG = {
    'plantParams',  @definePlantDD, {'models/plant/plant.slx', 'models/plant/finModel.slx'}, {'dataDictionaries/aeroTables.mat'}
};

repoRoot = fileparts(fileparts(mfilename('fullpath')));
addpath(fullfile(repoRoot, 'scripts', 'helpers'));
addpath(fullfile(repoRoot, 'dataDictionaries'));

for i = 1:size(CONFIG,1)
    dictName   = CONFIG{i,1};
    defineFcn  = CONFIG{i,2};
    modelFiles = CONFIG{i,3};
    extraDeps  = CONFIG{i,4};

    firstModelPath = fullfile(repoRoot, modelFiles{1});
    firstModelPath = char(java.io.File(firstModelPath).getCanonicalPath());
    sdddPath = fullfile(fileparts(firstModelPath), [dictName, '.sldd']);

    defineFile = functions(defineFcn).file;
    depFiles = [{defineFile}, cellfun(@(f) fullfile(repoRoot, f), extraDeps, 'UniformOutput', false)];

    if forceRebuild || ~isUpToDate_local(sdddPath, depFiles)
        P = defineFcn();
        buildDataDictionaryFile(sdddPath, P);
    else
        fprintf('%s is up to date, skipping.\n', sdddPath);
    end

    for j = 1:numel(modelFiles)
        modelPath = fullfile(repoRoot, modelFiles{j});
        modelPath = char(java.io.File(modelPath).getCanonicalPath());
        linkModelToDataDictionary(modelPath, sdddPath);
    end
end

clear CONFIG i j dictName defineFcn modelFiles extraDeps firstModelPath sdddPath defineFile depFiles P modelPath

% ======================================================================
function tf = isUpToDate_local(sdddPath, depFiles)
    % True iff sdddPath exists and is newer than every file in depFiles.
    if ~exist(sdddPath, 'file')
        tf = false;
        return;
    end
    sdddInfo = dir(sdddPath);
    for k = 1:numel(depFiles)
        depInfo = dir(depFiles{k});
        if isempty(depInfo) || sdddInfo.datenum < depInfo.datenum
            tf = false;
            return;
        end
    end
    tf = true;
end
