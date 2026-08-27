function linkModelToDataDictionary(modelPath, sdddPath)
%LINKMODELTODATADICTIONARY  Point a model's DataDictionary property at an
%   existing .sldd. Works for any .slx.
%
%   linkModelToDataDictionary(modelPath, sdddPath)
%     modelPath  path to the .slx
%     sdddPath   path to the .sldd to link (must be in the same folder as
%                the model -- DataDictionary resolves by bare filename
%                via MATLAB's cwd/path, not a stored path)

[modelDir, modelName] = fileparts(modelPath);
[dictDir, dictName, dictExt] = fileparts(sdddPath);

if ~strcmp(modelDir, dictDir)
    error('linkModelToDataDictionary:mismatch', ...
        'Model and dictionary must be in the same folder.');
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
