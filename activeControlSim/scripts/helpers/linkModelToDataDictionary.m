function linkModelToDataDictionary(modelPath, sdddPath)
%LINKMODELTODATADICTIONARY  Point a model's DataDictionary property at an
%   existing .sldd. Works for any .slx.
%
%   linkModelToDataDictionary(modelPath, sdddPath)
%     modelPath  path to the .slx
%     sdddPath   path to the .sldd to link. DataDictionary resolves by bare
%                filename via MATLAB's cwd/path, not a stored path, so the
%                dictionary's folder is added to the path here, and must
%                also be on the path whenever the model is opened later.

[modelDir, modelName] = fileparts(modelPath);
[dictDir, dictName, dictExt] = fileparts(sdddPath);

if ~isempty(dictDir)
    addpath(dictDir);
end

startDir = pwd;
cleanupObj = onCleanup(@() cd(startDir));
cd(modelDir);

wasLoaded = bdIsLoaded(modelName);
if ~wasLoaded
    load_system(modelPath);
end

sdddFile = [dictName, dictExt];
if strcmp(get_param(modelName, 'DataDictionary'), sdddFile)
    fprintf('%s already linked to %s\n', modelPath, sdddFile);
else
    set_param(modelName, 'DataDictionary', sdddFile);
    save_system(modelName, [], 'OverwriteIfChangedOnDisk', true);
    fprintf('Linked %s to %s\n', sdddFile, modelPath);
end

if ~wasLoaded
    close_system(modelName);
end

end
