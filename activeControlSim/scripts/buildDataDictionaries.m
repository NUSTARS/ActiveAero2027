%BUILDDATADICTIONARIES  Build and link a data dictionary to a model, for
%   each entry in CONFIG below -- but only if the dictionary is out of
%   date (its .sldd is older than the define*.m that generates it).
%
%   OPTIONS (set in the workspace before running to override)
%     forceRebuild   rebuild every dictionary regardless of timestamps
%                    (default false)

if ~exist('forceRebuild','var'), forceRebuild = false; end

% modelFile (relative to repo root)   dictName        defineFcn
CONFIG = {
    'models/plant/plant.slx',         'plantParams',  @definePlantDD
};

repoRoot = fileparts(fileparts(mfilename('fullpath')));
addpath(fullfile(repoRoot, 'scripts', 'helpers'));
addpath(fullfile(repoRoot, 'dataDictionaries'));

for i = 1:size(CONFIG,1)
    modelFile = CONFIG{i,1};
    dictName  = CONFIG{i,2};
    defineFcn = CONFIG{i,3};

    modelPath = fullfile(repoRoot, modelFile);
    modelPath = char(java.io.File(modelPath).getCanonicalPath());
    sdddPath  = fullfile(fileparts(modelPath), [dictName, '.sldd']);

    defineFile = functions(defineFcn).file;

    if ~forceRebuild && isUpToDate_local(sdddPath, defineFile)
        fprintf('%s is up to date, skipping.\n', sdddPath);
        continue;
    end

    P = defineFcn();
    linkDataDictionary(modelPath, sdddPath, P);
end

clear CONFIG i modelFile dictName defineFcn modelPath sdddPath defineFile P

% ======================================================================
function tf = isUpToDate_local(sdddPath, defineFile)
    % True iff sdddPath exists and is newer than defineFile.
    if ~exist(sdddPath, 'file')
        tf = false;
        return;
    end
    sdddInfo = dir(sdddPath);
    defInfo  = dir(defineFile);
    tf = sdddInfo.datenum >= defInfo.datenum;
end
