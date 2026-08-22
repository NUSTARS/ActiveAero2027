function linkDataDictionary(modelPath, sdddPath, P)
%LINKDATADICTIONARY  Write struct P into a data dictionary (one entry per
%   top-level field) and link it to a model's DataDictionary property.
%   Works for any .slx and any parameter struct.
%
%   linkDataDictionary(modelPath, sdddPath, P)
%     modelPath  path to the .slx
%     sdddPath   path to the .sldd to create (must be in the same folder
%                as the model -- DataDictionary resolves by bare
%                filename via MATLAB's cwd/path, not a stored path)
%     P          struct whose top-level fields become dictionary entries

[modelDir, modelName] = fileparts(modelPath);
[dictDir, dictName, dictExt] = fileparts(sdddPath);

if ~strcmp(modelDir, dictDir)
    error('linkDataDictionary:mismatch', ...
        'Model and dictionary must be in the same folder.');
end

% --------------------------------------------------------- build the sldd
% Update in place rather than delete+recreate -- deleting and rebuilding
% the file churns its internal generation/identity, which corrupts the
% master table if anything (this session, the GUI, a stale handle) still
% references the old one.
if ~exist(sdddPath, 'file')
    Simulink.data.dictionary.create(sdddPath);
end
dictObj = Simulink.data.dictionary.open(sdddPath);
designData = getSection(dictObj, 'Design Data');

existing = find(designData);
for i = 1:numel(existing)
    deleteEntry(designData, existing(i).Name);
end

fn = fieldnames(P);
for i = 1:numel(fn)
    prm = Simulink.Parameter;
    prm.Value = P.(fn{i});
    prm.CoderInfo.StorageClass = 'Auto';
    addEntry(designData, fn{i}, prm);
end

saveChanges(dictObj);
close(dictObj);

fprintf('Wrote %d entries to %s\n', numel(fn), sdddPath);

% ------------------------------------------------------------ link model
startDir = pwd;
cleanupObj = onCleanup(@() cd(startDir));
cd(modelDir);

wasLoaded = bdIsLoaded(modelName);
if ~wasLoaded
    load_system(modelPath);
end

set_param(modelName, 'DataDictionary', [dictName, dictExt]);
save_system(modelName, [], 'OverwriteIfChangedOnDisk', true);

if ~wasLoaded
    close_system(modelName);
end

fprintf('Linked %s to %s\n', [dictName, dictExt], modelPath);

end
