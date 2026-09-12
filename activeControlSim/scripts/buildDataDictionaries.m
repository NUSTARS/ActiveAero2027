%BUILDDATADICTIONARIES  Build and link a data dictionary to one or more
%   models, for each entry in CONFIG below -- but only if the dictionary
%   is out of date (its .sldd is older than any of its defineFcns, or
%   older than any extra data dependency, e.g. a .mat file one of them
%   loads).
%
%   A model can only have one .sldd set as its own DataDictionary, so a
%   dictionary whose models need entries from more than one define*.m
%   file lists all of those functions in defineFcns -- their output
%   structs are merged (top-level fields must be unique across them)
%   before being written to the one .sldd. (Simulink.data.Dictionary's
%   addDataSource, which links one dictionary as a referenced data source
%   of another, looked like the more direct way to share entries across
%   dictionaries, but reliably wiped the referenced dictionary's own
%   entries on saveChanges when tried here -- do not use it.)
%
%   OPTIONS (set in the workspace before running to override)
%     forceRebuild   rebuild every dictionary regardless of timestamps
%                    (default false)

if ~exist('forceRebuild','var'), forceRebuild = false; end

% dictName        defineFcns                          modelFiles (relative to repo root)  extraDeps (relative to repo root)
CONFIG = {
    'plantParams',  {@definePlantDD, @defineSensorDD}, {'models/plant/plant.slx', 'models/plant/finModel.slx', 'models/plant/aeroModel.slx', 'models/plant/bodyModel.slx', 'models/plant/eomModel.slx', 'models/plant/environmentModel.slx', 'models/plant/windModel.slx', 'models/plant/sensorModels.slx'}, {'dataDictionaries/aeroTables.mat'}
    'navParams',  {@defineNavDD}, {'models/activeControlSim.slx'}, {}
    'controllerParams',  {@defineControllerDD}, {'models/control/Guidance.slx', 'models/control/controller.slx', 'models/control/pitchYawInnerLoop.slx', 'models/control/rollInnerLoop.slx', 'models/control/pitchYawOuterLoop.slx', 'models/control/rollOuterLoop.slx'}, {}
};

repoRoot = fileparts(fileparts(mfilename('fullpath')));
addpath(fullfile(repoRoot, 'scripts', 'helpers'));
addpath(fullfile(repoRoot, 'dataDictionaries'));

for i = 1:size(CONFIG,1)
    dictName   = CONFIG{i,1};
    defineFcns = CONFIG{i,2};
    modelFiles = CONFIG{i,3};
    extraDeps  = CONFIG{i,4};

    firstModelPath = fullfile(repoRoot, modelFiles{1});
    firstModelPath = char(java.io.File(firstModelPath).getCanonicalPath());
    sdddPath = fullfile(fileparts(firstModelPath), [dictName, '.sldd']);

    defineFiles = cellfun(@(f) functions(f).file, defineFcns, 'UniformOutput', false);
    depFiles = [defineFiles, cellfun(@(f) fullfile(repoRoot, f), extraDeps, 'UniformOutput', false)];

    if forceRebuild || ~isUpToDate_local(sdddPath, depFiles)
        P = mergeParamStructs_local(defineFcns);
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

clear CONFIG i j dictName defineFcns modelFiles extraDeps firstModelPath sdddPath defineFiles depFiles P modelPath

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

% ======================================================================
function M = mergeParamStructs_local(defineFcns)
    % Call each defineFcn and merge their output structs' top-level
    % fields into one. Errors if two functions define the same field.
    M = struct();
    for i = 1:numel(defineFcns)
        S = defineFcns{i}();
        fn = fieldnames(S);
        for j = 1:numel(fn)
            if isfield(M, fn{j})
                error('mergeParamStructs_local:duplicateField', ...
                    'Field ''%s'' is defined by more than one defineFcn.', fn{j});
            end
            M.(fn{j}) = S.(fn{j});
        end
    end
end
