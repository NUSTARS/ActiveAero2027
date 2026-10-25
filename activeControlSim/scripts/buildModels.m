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
addpath(modelsDir);

buildDataDictionaries;

% Generate both top models afresh in separate output roots. Post-processing
% renames their const_params.c files, so incremental reuse is unsafe here.
buildModelsInSeparateFolders(buildModelNames, modelsDir, projectRoot);

% Locate each const_params.c wherever Simulink placed it. With shared
% utility code enabled, R2026a may put it in slprj/ert/_sharedutils,
% rather than <model>_ert_rtw.
plantBuild = fullfile(projectRoot, 'build_autocodePlant');
modelBuild = fullfile(projectRoot, 'build_autocodeModel');
plantFile = findConstFile(plantBuild, 'const_params.c', true);
modelFile = findConstFile(modelBuild, 'const_params.c', true);
if isempty(plantFile) || isempty(modelFile)
    error(['Cannot find fresh const_params.c for both builds. ' ...
        'Clear their build directories and rebuild if Simulink reused ' ...
        'already-renamed generated files.']);
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

% Rename each file *at its discovered location*, and fix filename
% references across generated makefiles and source/headers.
for k = 1:numel(buildModelNames)
    mdl = char(buildModelNames(k));
    buildDir = fullfile(projectRoot, ['build_' mdl]);
    if strcmp(mdl, 'autocodePlant')
        oldFile = plantFile;
    else
        oldFile = modelFile;
    end
    [containingDir, ~, ~] = fileparts(oldFile);
    newName = ['const_params_' mdl '.c'];
    newFile = fullfile(containingDir, newName);
    if isfile(newFile)
        delete(newFile);
    end
    [ok, msg] = movefile(oldFile, newFile);
    if ~ok
        error('Cannot rename %s: %s', oldFile, msg);
    end

    exts = {'.c', '.h', '.mk', '.d', '.txt', '.rsp', '.bat'};
    for e = 1:numel(exts)
        matches = dir(fullfile(buildDir, '**', ['*' exts{e}]));
        for j = 1:numel(matches)
            path = fullfile(matches(j).folder, matches(j).name);
            if contains(['/' strrep(matches(j).folder, char(92), '/') '/'], ...
                    '/toIDE/', 'IgnoreCase', true)
                continue; % Ignore stale exports from earlier runs.
            end
            original = fileread(path);
            updated = strrep(original, 'const_params.c', newName);
            if ~strcmp(original, updated)
                writeText(path, updated);
            end
        end
    end
    fprintf('Post-processed: %s\n', newFile);
end

fprintf('Done. %s defined in Model and extern in Plant.\n', sharedSymbol);


% Export generated code to per-model toIDE folders.
exportToIDE(projectRoot, buildModelNames);

% Extract each generated ERT example main into a reusable MCU harness.
% Requires generateModelHarness.m beside buildModels.m.
addpath(scriptDir);
for k = 1:numel(buildModelNames)
    mdl = char(buildModelNames(k));
    generateModelHarness(mdl, fullfile(projectRoot, ['build_' mdl]));
end


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


function path = findConstFile(buildDir, filename, preferShared)
    matches = dir(fullfile(buildDir, '**', filename));
    matches = matches(~[matches.isdir]);
    % toIDE is an exported copy, not a code-generation output. Never
    % consider it while locating files for caching or post-processing.
    isExport = arrayfun(@(f) contains(['/' strrep(f.folder, char(92), '/') '/'], ...
        '/toIDE/', 'IgnoreCase', true), matches);
    matches = matches(~isExport);
    if isempty(matches)
        path = '';
        return;
    end
    paths = arrayfun(@(f) fullfile(f.folder, f.name), matches, ...
        'UniformOutput', false);
    % Prefer the shared utility directory, which is the normal location
    % for const_params.c with shared code placement enabled.
    shared = contains(strrep(paths, '\', '/'), '/_sharedutils/');
    if preferShared && any(shared)
        paths = paths(shared);
    end
    if numel(paths) ~= 1
        error('Ambiguous %s under %s:\n%s', filename, buildDir, ...
            strjoin(paths, newline));
    end
    path = paths{1};
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
        exports{k} = collectCodeFiles({modelDir, sharedDir}, matlabIncludes);
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
            [ok, msg] = copyfile(src, fullfile(targetDir, key));
            if ~ok
                error('Failed to export %s: %s', src, msg);
            end
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
    for k = 1:numel(modelNames)
        mdl = char(modelNames(k));
        buildDir = fullfile(projectRoot, ['build_' mdl]);
        Simulink.fileGenControl('set', 'CodeGenFolder', buildDir, ...
            'CacheFolder', buildDir, 'createDir', true);
        load_system(fullfile(modelsDir, [mdl '.slx']));
        slbuild(mdl, 'ForceTopModelBuild', true);
    end
end
