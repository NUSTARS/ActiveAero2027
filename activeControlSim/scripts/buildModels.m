%% Build both models and post-process generated constants for STM32CubeIDE
buildModelNames = {'autocodePlant', 'autocodeModel'};
sharedSymbol = 'rtCP_pooled_JIXvzcabvSoM';

% Resolve project paths from this script's location, not the MATLAB current folder.
scriptDir = fileparts(mfilename('fullpath'));
projectRoot = fileparts(scriptDir);
modelsDir = fullfile(projectRoot, 'models');
if ~isfolder(modelsDir)
    error('Cannot locate models directory relative to buildModels.m: %s', modelsDir);
end
fprintf('Project root: %s\n', projectRoot);
addpath(scriptDir);
addpath(genpath(modelsDir));
addpath(fullfile(projectRoot, 'data'));
addpath(fullfile(projectRoot, 'dataDictionaries'));

buildDataDictionaries;

% Keep Simulink's generated files unchanged so incremental builds remain valid.
% Only the independent toIDE copies are renamed and patched for linking.
buildModelsInSeparateFolders(buildModelNames, modelsDir, projectRoot);
exportToIDE(projectRoot, buildModelNames);
plantFile = fullfile(projectRoot, 'build_autocodePlant', 'toIDE', 'Src', ...
    'const_params_autocodePlant.c');
modelFile = fullfile(projectRoot, 'build_autocodeModel', 'toIDE', 'Src', ...
    'const_params_autocodeModel.c');
if ~isfile(plantFile) || ~isfile(modelFile)
    error('Missing exported constant files after code generation: %s, %s', ...
        plantFile, modelFile);
end

% Make sure the shared symbol definitions have the same array initializer.
plantText = fileread(plantFile);
modelText = fileread(modelFile);
pattern = ['(?m)^[ \t]*const\s+real_T\s+' sharedSymbol ...
    '\s*\[\s*9\s*\]\s*=\s*\{[^}]*\}\s*;'];
plantDef = regexp(plantText, pattern, 'match', 'once');
modelDef = regexp(modelText, pattern, 'match', 'once');
if isempty(plantDef) || isempty(modelDef)
    error('Expected definition of %s in both constant files.', sharedSymbol);
end
plantValues = regexp(plantDef, '\{([^}]*)\}', 'tokens', 'once');
modelValues = regexp(modelDef, '\{([^}]*)\}', 'tokens', 'once');
normalize = @(s) regexprep(s, '\s+', '');
if ~strcmp(normalize(plantValues{1}), normalize(modelValues{1}))
    error('%s differs between models; refusing to share a definition.', sharedSymbol);
end

% autocodeModel is PRIMARY; it owns the shared definition.
% autocodePlant is optional and must only refer to the primary definition.
plantText = regexprep(plantText, pattern, '');
externDecl = ['extern const real_T ' sharedSymbol '[9];'];
if ~contains(plantText, externDecl)
    plantText = strrep(plantText, '#include "rtwtypes.h"', ...
        sprintf('#include "rtwtypes.h"\n\n%s', externDecl));
end
writeText(plantFile, plantText);

fprintf('Done. %s defined in Model and extern in Plant exports.\n', sharedSymbol);

% Extract each generated ERT example main into a reusable MCU harness.
% Requires generateModelHarness.m beside buildModels.m.
addpath(scriptDir);
for k = 1:numel(buildModelNames)
    mdl = char(buildModelNames(k));
    generateModelHarness(mdl, fullfile(projectRoot, ['build_' mdl]));
end

% Install the optional controller callback only into the exported plant copy.
installPlantFeedbackHook(fullfile(projectRoot, 'build_autocodePlant'));

% Refresh the copied CubeIDE CM7 project after code generation succeeds.
copyGeneratedToCubeIDE(projectRoot, buildModelNames);


%% Local helper functions
function writeText(path, contents)
    fid = fopen(path, 'w');
    if fid < 0
        error('Cannot write %s', path);
    end
    cleanup = onCleanup(@() fclose(fid));
    fwrite(fid, contents, 'char');
end


function hex = sha256File(path)
    fid = fopen(path, 'rb');
    if fid < 0
        error('Cannot read file %s', path);
    end
    cleanup = onCleanup(@() fclose(fid));
    digest = java.security.MessageDigest.getInstance('SHA-256');
    while ~feof(fid)
        data = fread(fid, 1024*1024, '*uint8');
        if ~isempty(data)
            digest.update(typecast(data, 'int8'));
        end
    end
    bytes = typecast(digest.digest(), 'uint8');
    hex = lower(reshape(dec2hex(bytes, 2).', 1, []));
end


function exportToIDE(projectRoot, models)
    % Collect each model's generated C/H plus recursively needed MATLAB
    % Simulink include files. Export to toIDE/Src and toIDE/Inc.
    matlabIncludes = fullfile(matlabroot, 'simulink', 'include');
    if ~isfolder(matlabIncludes)
        warning('MATLAB Simulink include folder not found: %s', matlabIncludes);
    end

    exports = cell(size(models));
    for k = 1:numel(models)
        mdl = models{k};
        buildDir = fullfile(projectRoot, ['build_' mdl]);
        sharedDir = fullfile(buildDir, 'slprj', 'ert', '_sharedutils');
        modelDir = fullfile(buildDir, [mdl '_ert_rtw']);
        if ~isfolder(sharedDir) || ~isfolder(modelDir)
            error('Missing generated folders for %s; cannot export toIDE.', mdl);
        end
        sourceMap = collectCodeFiles({modelDir, sharedDir}, matlabIncludes);
        if ~isKey(sourceMap, 'const_params.c')
            error('Missing generated const_params.c for %s under %s.', mdl, buildDir);
        end
        sourceMap(['const_params_' mdl '.c']) = sourceMap('const_params.c');
        remove(sourceMap, 'const_params.c');
        exports{k} = sourceMap;
    end

    % Names in the PRIMARY model always win. A secondary file with the
    % same basename is not copied even if its content differs: doing so
    % would cause file/symbol overlap. Warn for mismatches.
    primaryIdx = find(strcmp(models, 'autocodeModel'), 1);
    if isempty(primaryIdx)
        error('Primary model autocodeModel not found.');
    end
    primary = exports{primaryIdx};
    for k = 1:numel(models)
        mdl = models{k};
        sourceMap = exports{k};
        destDir = fullfile(projectRoot, ['build_' mdl], 'toIDE');
        if isfolder(destDir)
            rmdir(destDir, 's'); % Prevent stale exports surviving a rebuild.
        end
        mkdir(destDir);
        srcDir = fullfile(destDir, 'Src');
        incDir = fullfile(destDir, 'Inc');
        mkdir(srcDir);
        mkdir(incDir);
        keys = sourceMap.keys;
        copied = 0;
        skipped = 0;
        for j = 1:numel(keys)
            key = keys{j};
            src = sourceMap(key);
            if k ~= primaryIdx && isKey(primary, key)
                skipped = skipped + 1;
                primarySrc = primary(key);
                if ~strcmp(sha256File(src), sha256File(primarySrc))
                    warning(['Shared filename %s differs between %s and ' ...
                        'autocodeModel; exporting ONLY the primary copy. ' ...
                        'Verify compatibility.'], key, mdl);
                end
                continue;
            end
            [~, ~, ext] = fileparts(key);
            if strcmpi(ext, '.c')
                targetDir = srcDir;
            elseif strcmpi(ext, '.h')
                targetDir = incDir;
            else
                error('Unexpected export file type: %s', key);
            end
            contents = fileread(src);
            contents = strrep(contents, 'const_params.c', ['const_params_' mdl '.c']);
            writeText(fullfile(targetDir, key), contents);
            copied = copied + 1;
        end
        fprintf('Exported %d files to %s (%d shared files omitted).\n', ...
            copied, destDir, skipped);
    end
end

function files = collectCodeFiles(generatedDirs, matlabIncludes)
    % Map a filename to its absolute source path. MATLAB-created files
    % take precedence over toolchain-provided fallback headers.
    files = containers.Map('KeyType', 'char', 'ValueType', 'char');
    for d = 1:numel(generatedDirs)
        folder = generatedDirs{d};
        for extension = {'.c', '.h'}
            hits = dir(fullfile(folder, '**', ['*' extension{1}]));
            for j = 1:numel(hits)
                if hits(j).isdir || strcmpi(hits(j).name, 'ert_main.c')
                    continue;
                end
                key = hits(j).name;
                path = fullfile(hits(j).folder, key);
                if isKey(files, key)
                    prior = files(key);
                    if ~strcmp(sha256File(prior), sha256File(path))
                        error('Two different generated files named %s:\n%s\n%s', ...
                            key, prior, path);
                    end
                else
                    files(key) = path;
                end
            end
        end
    end

    % Resolve quoted and angle-bracket includes against generated files
    % and MATLAB's simulink/include directory; recursively follow newly
    % discovered headers. Pair MATLAB headers with same-name .c sources
    % where available so dependencies are linkable in CubeIDE.
    pending = files.values;
    scanned = containers.Map('KeyType', 'char', 'ValueType', 'logical');
    while ~isempty(pending)
        path = pending{end};
        pending(end) = [];
        if isKey(scanned, path)
            continue;
        end
        scanned(path) = true;
        if ~isfile(path)
            error('Missing export dependency: %s', path);
        end
        contents = fileread(path);
        matches = regexp(contents, '(?m)^\s*#\s*include\s*[<"]([^>"]+)[>"]', ...
            'tokens');
        for i = 1:numel(matches)
            inc = strrep(matches{i}{1}, '\', '/');
            [~, base, ext] = fileparts(inc);
            key = [base ext];
            if isKey(files, key)
                continue;
            end
            candidate = fullfile(matlabIncludes, strrep(inc, '/', filesep));
            if ~isfile(candidate)
                candidate = fullfile(matlabIncludes, key);
            end
            if ~isfile(candidate)
                continue; % Third-party/system include; STM32 handles it.
            end
            files(key) = candidate;
            pending{end+1} = candidate; %#ok<AGROW>
            if strcmpi(ext, '.h')
                companion = fullfile(fileparts(candidate), [base '.c']);
                if isfile(companion) && ~isKey(files, [base '.c'])
                    files([base '.c']) = companion;
                    pending{end+1} = companion; %#ok<AGROW>
                end
            end
        end
    end
end
function buildModelsInSeparateFolders(modelNames, modelsDir, projectRoot)
    currentDir = pwd;
    currentDirCleanup = onCleanup(@() cd(currentDir));
    cd(projectRoot);
    originalFileGen = Simulink.fileGenControl('getConfig');
    fileGenCleanup = onCleanup(@() Simulink.fileGenControl('setConfig', ...
        'config', originalFileGen));
    for k = 1:numel(modelNames)
        mdl = char(modelNames(k));
        buildDir = fullfile(projectRoot, ['build_' mdl]);
        % Repair output from older script versions that renamed cached files.
        % Remove only model-owned generated artifacts, retaining the old exports.
        legacyFile = fullfile(buildDir, 'slprj', 'ert', '_sharedutils', ...
            ['const_params_' mdl '.c']);
        if isfile(legacyFile)
            expectedDir = char(java.io.File(fullfile(projectRoot, ['build_' mdl])).getCanonicalPath());
            actualDir = char(java.io.File(buildDir).getCanonicalPath());
            assert(strcmp(actualDir, expectedDir) && ...
                any(strcmp(mdl, {'autocodePlant', 'autocodeModel'})), ...
                'Refusing to clear an unexpected build directory: %s', buildDir);
            fprintf('Repairing legacy renamed code-generation cache for %s.\n', mdl);
            for artifact = {'slprj', [mdl '_ert_rtw']}
                generatedDir = fullfile(buildDir, artifact{1});
                if isfolder(generatedDir)
                    rmdir(generatedDir, 's');
                end
            end
            cacheFile = fullfile(buildDir, [mdl '.slxc']);
            if isfile(cacheFile), delete(cacheFile); end
        end
        Simulink.fileGenControl('set', 'CodeGenFolder', buildDir, ...
            'CacheFolder', buildDir, 'createDir', true);
        load_system(fullfile(modelsDir, [mdl '.slx']));
        slbuild(mdl, 'ForceTopModelBuild', true);
    end
end
function copyGeneratedToCubeIDE(projectRoot, modelNames)
    cm7Dir = fullfile(fileparts(projectRoot), 'STM32AutocodeLib', 'CM7');
    if ~isfolder(cm7Dir)
        error('Cannot locate copied CM7 library: %s', cm7Dir);
    end

    % autocodePlant is secondary; copy it first so autocodeModel wins shared names.
    for k = 1:numel(modelNames)
        modelName = modelNames{k};
        exportDir = fullfile(projectRoot, ['build_' modelName], 'toIDE');
        for subdirs = {'Src', 'Inc'}
            subdir = subdirs{1};
            sourceDir = fullfile(exportDir, subdir);
            destinationDir = fullfile(cm7Dir, subdir);
            if ~isfolder(sourceDir)
                error('Cannot locate generated export directory: %s', sourceDir);
            end
            if ~isfolder(destinationDir)
                error('Cannot locate CubeIDE output directory: %s', destinationDir);
            end
            files = dir(fullfile(sourceDir, '*'));
            files = files(~[files.isdir]);
            for j = 1:numel(files)
                sourceFile = fullfile(files(j).folder, files(j).name);
                destinationFile = fullfile(destinationDir, files(j).name);
                [ok, msg] = copyfile(sourceFile, destinationFile, 'f');
                if ~ok
                    error('Cannot copy %s to %s: %s', ...
                        sourceFile, destinationFile, msg);
                end
            end
            fprintf('Copied %d generated files to %s.\n', ...
                numel(files), destinationDir);
        end
    end
end
