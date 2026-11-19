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
[calibrationFiles, assignmentNotes, symbolValues] = configureDictionaryExports(modelsDir);

% Keep Simulink's generated files unchanged so incremental builds remain valid.
% Only the independent toIDE copies are renamed and patched for linking.
buildModelsInSeparateFolders(buildModelNames, modelsDir, projectRoot);
exportToIDE(projectRoot, buildModelNames, calibrationFiles);
exportDictionaryHeaders(projectRoot, buildModelNames, calibrationFiles, assignmentNotes, symbolValues);
sharePooledConstant(projectRoot, sharedSymbol);

% Extract each generated ERT example main into a reusable MCU harness.
for k = 1:numel(buildModelNames)
    mdl = char(buildModelNames(k));
    generateModelHarness(mdl, fullfile(projectRoot, ['build_' mdl]));
end

installPlantFeedbackHook(fullfile(projectRoot, 'build_autocodePlant'));
copyGeneratedToCubeIDE(projectRoot, buildModelNames);

%% Local helper functions
function sharePooledConstant(projectRoot, sharedSymbol)
plantFile = fullfile(projectRoot, 'build_autocodePlant', 'toIDE', 'Src', ...
    'const_params_autocodePlant.c');
modelFile = fullfile(projectRoot, 'build_autocodeModel', 'toIDE', 'Src', ...
    'const_params_autocodeModel.c');
if ~isfile(plantFile) || ~isfile(modelFile)
    return; % A model can generate no pooled constants after remapping.
end

% Make sure the shared symbol definitions have the same array initializer.
plantText = fileread(plantFile);
modelText = fileread(modelFile);
pattern = ['(?m)^[ \t]*const\s+real_T\s+' sharedSymbol ...
    '\s*\[\s*9\s*\]\s*=\s*\{[^}]*\}\s*;'];
plantDef = regexp(plantText, pattern, 'match', 'once');
modelDef = regexp(modelText, pattern, 'match', 'once');
if isempty(plantDef) || isempty(modelDef)
    return; % No duplicate of this symbol to remove.
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

end

function [sourceFiles, assignmentNotes, symbolValues] = configureDictionaryExports(modelsDir)
    % Use each entry's owning dictionary. Referenced entries appear in find()
    % too, so only configure an entry while visiting its own dictionary.
    dictionaries = dir(fullfile(modelsDir, '**', '*.sldd'));
    names = sort({dictionaries.name});
    assert(numel(unique(lower(string(names)))) == numel(names), ...
        'Dictionary basenames must be unique to produce distinct C headers.');
    sourceFiles = {};
    assignmentNotes = containers.Map('KeyType', 'char', 'ValueType', 'char');
    symbolOwners = containers.Map('KeyType', 'char', 'ValueType', 'char');
    symbolValues = containers.Map('KeyType', 'char', 'ValueType', 'any');
    for i = 1:numel(names)
        info = dictionaries(strcmp({dictionaries.name}, names{i}));
        dictionary = Simulink.data.dictionary.open(fullfile(info.folder, info.name));
        cleanup = onCleanup(@() close(dictionary));
        assert(~dictionary.HasUnsavedChanges, ...
            'Save changes to %s before exporting its parameters.', info.name);
        section = getSection(dictionary, 'Design Data');
        entries = find(section);
        [~, base] = fileparts(info.name);
        assert(isvarname(base), 'Dictionary basename %s must be a valid C identifier.', base);
        dictionarySource = [base '_calibration.c'];
        parameterNames = {};
        hasExport = false;
        changed = false;
        for j = 1:numel(entries)
            entry = entries(j);
            [~, owner, ext] = fileparts(entry.DataSource);
            if ~strcmp([owner ext], info.name)
                continue;
            end
            parameter = getValue(entry);
            if ~isa(parameter, 'Simulink.Parameter')
                continue; % Bus and other type definitions are not values.
            end
            % Top-level and linked-model dictionaries can contain identical
            % copies. Give the first dictionary in sorted order ownership so
            % all copies have the same C type and definition file.
            if isKey(symbolOwners, entry.Name)
                owner = symbolOwners(entry.Name);
            else
                owner = base;
                symbolOwners(entry.Name) = owner;
            end
            sourceFile = [owner '_calibration.c'];
            declarationFile = [owner '_calibration.h'];
            if strcmp(owner, base)
                parameterNames{end+1} = entry.Name; %#ok<AGROW>
                hasExport = true;
            end
            needsType = false;
            if isstruct(parameter.Value)
                [parameter.Value, typeName] = exportParameterType( ...
                    section, parameter.Value, ['cal_' owner '_' entry.Name], ...
                    [owner '_calibration_types.h']);
                parameter.DataType = ['Bus: ' typeName];
                needsType = true;
            end
            if isKey(symbolValues, entry.Name)
                assert(isequaln(symbolValues(entry.Name), parameter.Value), ...
                    'Conflicting values for %s in %s.sldd and %s.', entry.Name, owner, info.name);
            else
                symbolValues(entry.Name) = parameter.Value;
            end
            needsStorageClass = ~strcmp(parameter.CoderInfo.StorageClass, 'Custom') || ...
                ~strcmp(parameter.CoderInfo.CustomStorageClass, 'ExportToFile');
            if needsStorageClass
                parameter.CoderInfo.StorageClass = 'Custom';
                parameter.CoderInfo.CustomStorageClass = 'ExportToFile';
            end
            attributes = parameter.CoderInfo.CustomAttributes;
            if needsType || needsStorageClass || ~strcmp(attributes.HeaderFile, declarationFile) || ...
                    ~strcmp(attributes.DefinitionFile, sourceFile)
                attributes.HeaderFile = declarationFile;
                attributes.DefinitionFile = sourceFile;
                setValue(entry, parameter);
                changed = true;
            end
        end
        if changed
            saveChanges(dictionary);
        end
        if hasExport
            sourceFiles{end+1} = dictionarySource; %#ok<AGROW>
            assignmentNotes(dictionarySource) = dictionaryAssignmentNotes( ...
                fullfile(fileparts(modelsDir), 'dataDictionaries'), parameterNames);
        end
        clear cleanup
    end
    if isempty(sourceFiles)
        fprintf('No Simulink.Parameter entries found in model dictionaries.\n');
    end
end

function [value, typeName] = exportParameterType(section, value, typeName, headerFile)
    % Explicit shared types are required when ERT puts parameter structures
    % into a definition file separate from the model source.
    assert(numel(typeName) <= namelengthmax, 'Parameter type name is too long: %s', typeName);
    assert(isscalar(value), 'Parameter structure arrays need an explicit bus type: %s', typeName);
    fields = fieldnames(value);
    elements = Simulink.BusElement.empty;
    for i = 1:numel(fields)
        field = fields{i};
        item = value.(field);
        element = Simulink.BusElement;
        element.Name = field;
        if isstruct(item)
            [item, nestedType] = exportParameterType(section, item, ...
                [typeName '_' field], headerFile);
            element.DataType = ['Bus: ' nestedType];
        else
            if ischar(item)
                item = uint8(item); % C stores file-name metadata as byte arrays.
            end
            assert(isnumeric(item) || islogical(item), ...
                'Unsupported parameter field type %s in %s.%s.', class(item), typeName, field);
            element.DataType = class(item);
            if islogical(item)
                element.DataType = 'boolean';
            end
        end
        element.Dimensions = size(item);
        if ~isstruct(item) && ~isreal(item)
            element.Complexity = 'complex';
        end
        elements(end+1) = element; %#ok<AGROW>
        value.(field) = item;
    end
    bus = Simulink.Bus;
    bus.Elements = elements;
    bus.DataScope = 'Exported';
    bus.HeaderFile = headerFile;
    if exist(section, typeName)
        setValue(getEntry(section, typeName), bus);
    else
        addEntry(section, typeName, bus);
    end
end

function notes = dictionaryAssignmentNotes(definitionsDir, parameterNames)
    % Preserve source formulas and their intermediate variable assignments.
    % Values are evaluated by MATLAB before ERT emits the C initializers.
    notes = '';
    files = dir(fullfile(definitionsDir, '*.m'));
    [~, order] = sort({files.name});
    for i = order
        text = fileread(fullfile(files(i).folder, files(i).name));
        belongs = false;
        for j = 1:numel(parameterNames)
            pattern = ['\<\w+\.' regexptranslate('escape', parameterNames{j}) '\>'];
            if ~isempty(regexp(text, pattern, 'once'))
                belongs = true;
                break;
            end
        end
        if ~belongs
            continue;
        end
        assignments = regexp(text, ...
            '(?m)^[ \t]*[A-Za-z]\w*(?:\.\w+)*(?:\([^=\r\n]*\))?[ \t]*=[^\r\n]*(?:\r?\n[ \t]+[^\r\n]*)*', 'match');
        % Store as comments only. Derived values are independent C
        % initializers and are not recomputed when another field is edited.
        if ~isempty(assignments)
            body = strjoin(assignments, newline);
            body = strrep(body, '*/', '* /');
            notes = [notes sprintf('/* MATLAB assignments from %s:\n%s\n */\n', ...
                files(i).name, body)]; %#ok<AGROW>
        end
    end
end

function exportDictionaryHeaders(projectRoot, models, sourceFiles, assignmentNotes, symbolValues)
    % Keep the generated declarations separate. Include definitions in
    % exactly one translation unit by retaining a .c wrapper in the export.
    for i = 1:numel(sourceFiles)
        sourceFile = sourceFiles{i};
        [~, base] = fileparts(sourceFile);
        valuesFile = [base '_values.h'];
        found = false;
        for j = 1:numel(models)
            exportDir = fullfile(projectRoot, ['build_' models{j}], 'toIDE');
            sourcePath = fullfile(exportDir, 'Src', sourceFile);
            if ~isfile(sourcePath)
                continue;
            end
            valuesPath = fullfile(exportDir, 'Inc', valuesFile);
            assert(~isfile(valuesPath), 'Generated header name already in use: %s', valuesPath);
            guard = upper([base '_VALUES_H']);
            definitions = fileread(sourcePath);
            if isKey(assignmentNotes, sourceFile)
                definitions = macroInitializers(definitions, assignmentNotes(sourceFile), symbolValues);
            end
            writeText(valuesPath, sprintf([ ...
                '/* Edit the parameter macros here for STM32 builds.\n' ...
                ' * Included only by %s. Regenerated from the dictionary on MATLAB build.\n' ...
                ' * Sample times, delay lengths, dimensions and inlined expressions remain\n' ...
                ' * compiled into the model. See the MATLAB tunability warnings. */\n' ...
                '#ifndef %s\n#define %s\n\n%s\n#endif\n'], ...
                sourceFile, guard, guard, definitions));
            writeText(sourcePath, sprintf('#include "%s"\n', valuesFile));
            fprintf('Exported %s parameters to %s\n', models{j}, valuesPath);
            found = true;
        end
        if ~found
            warning(['No generated %s found in either export. Check that the ' ...
                'dictionary parameters are used in generated code and their mapping ' ...
                'does not override ExportToFile.'], sourceFile);
        end
    end
end

function text = macroInitializers(text, notes, values)
    [~, ends, symbols] = regexp(text, ...
        '(?m)^\s*\w+\s+(\w+)\s*(?:\[[^\]\r\n]*\]\s*)*\s*=\s*', ...
        'start', 'end', 'tokens');
    macros = {};
    names = {};
    for i = numel(ends):-1:1
        name = symbols{i}{1};
        if ~isKey(values, name)
            continue;
        end
        first = ends(i)+1;
        [offsets, tokens] = initializerTokens(text(first:end));
        semicolon = find(strcmp(tokens, ';'), 1);
        assert(~isempty(semicolon), 'Missing initializer terminator for %s.', name);
        last = first+offsets(semicolon)-2;
        [ranges, paths] = initializerFields(text, first, last, values(name), name);
        for j = size(ranges, 1):-1:1
            path = paths{j};
            macro = ['CAL_' upper(strrep(path, '.', '_'))];
            assert(~any(strcmp(names, macro)), 'Duplicate calibration macro %s.', macro);
            names{end+1} = macro; %#ok<AGROW>
            startValue = ranges(j, 1);
            endValue = ranges(j, 2);
            initializer = text(startValue:endValue);
            % Keep multiline arrays readable with preprocessor continuations.
            initializer = strrep(initializer, sprintf('\r\n'), newline);
            initializer = strrep(initializer, newline, [' ' char(92) newline]);
            macros{end+1} = sprintf('#define %s %s%s\n', ...
                macro, assignmentComment(path, notes), initializer); %#ok<AGROW>
            text = [text(1:startValue-1) macro text(endValue+1:end)];
        end
    end
    if ~isempty(macros)
        text = [strjoin(macros(end:-1:1), '') newline text];
    end
end

function [ranges, paths] = initializerFields(text, first, last, value, path)
    while first < last && isspace(text(first))
        first = first+1;
    end
    while last > first && isspace(text(last))
        last = last-1;
    end
    ranges = [first last];
    paths = {path};
    if ~isstruct(value) || text(first) ~= '{'
        return;
    end

    [offsets, tokens] = initializerTokens(text(first:last));
    depth = 0;
    starts = first+1;
    stops = [];
    for i = 1:numel(tokens)
        position = first+offsets(i)-1;
        switch tokens{i}
            case '{'
                depth = depth+1;
            case '}'
                depth = depth-1;
                if depth == 0
                    stops(end+1) = position-1;
                    break;
                end
            case ','
                if depth == 1
                    stops(end+1) = position-1; %#ok<AGROW>
                    starts(end+1) = position+1; %#ok<AGROW>
                end
        end
    end
    fields = fieldnames(value);
    % A compact aggregate such as { 0 } still gets a macro for the object.
    if depth ~= 0 || numel(stops) ~= numel(fields) || numel(starts) ~= numel(fields)
        return;
    end
    ranges = zeros(0, 2);
    paths = {};
    for i = 1:numel(fields)
        field = fields{i};
        [childRanges, childPaths] = initializerFields(text, starts(i), stops(i), ...
            value.(field), [path '.' field]);
        ranges = [ranges; childRanges]; %#ok<AGROW>
        paths = [paths childPaths]; %#ok<AGROW>
    end
end

function [offsets, tokens] = initializerTokens(text)
    [offsets, ~, tokens] = regexp(text, ...
        '(?s)/\*.*?\*/|//[^\r\n]*|"[^"\r\n]*"|[{},;]', 'start', 'end', 'match');
end

function comment = assignmentComment(path, notes)
    pattern = ['(?m)^\s*(?:\w+\.)?' regexptranslate('escape', path) ...
        '[ \t]*=[^\r\n]*'];
    matches = regexp(notes, pattern, 'match');
    if isempty(matches)
        comment = ['/* ' path ' */ '];
    else
        comment = ['/* MATLAB: ' strtrim(matches{end}) ' */ '];
    end
end

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


function exportToIDE(projectRoot, models, calibrationFiles)
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
        if isKey(sourceMap, 'const_params.c')
            sourceMap(['const_params_' mdl '.c']) = sourceMap('const_params.c');
            remove(sourceMap, 'const_params.c');
        end
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
                    if any(strcmp(key, calibrationFiles)) || ...
                            any(strcmp(strrep(key, '.h', '.c'), calibrationFiles))
                        error(['Dictionary export %s differs between %s and autocodeModel. ' ...
                            'Use a single code-generation owner for shared parameter definitions.'], key, mdl);
                    end
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
        % Structural uses (sample times and mask dimensions) must stay
        % compiled in. Keep ERT's diagnostic visible while exporting data
        % for all other uses of the same parameter objects.
        oldDiagnostic = get_param(mdl, 'ParameterTunabilityLossMsg');
        set_param(mdl, 'ParameterTunabilityLossMsg', 'warning');
        restoreDiagnostic = onCleanup(@() set_param(mdl, ...
            'ParameterTunabilityLossMsg', oldDiagnostic));
        slbuild(mdl, 'ForceTopModelBuild', true);
        clear restoreDiagnostic
    end
end
function copyGeneratedToCubeIDE(projectRoot, modelNames)
    cm7Dir = fullfile(fileparts(projectRoot), 'STM32AutocodeLib', 'CM7');
    if ~isfolder(cm7Dir)
        error('Cannot locate copied CM7 library: %s', cm7Dir);
    end

    calibrationDir = fullfile(cm7Dir, 'Inc', 'Calibration');
    if ~isfolder(calibrationDir)
        mkdir(calibrationDir);
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
                if strcmp(subdir, 'Inc') && endsWith(files(j).name, '_calibration_values.h')
                    destinationFile = fullfile(calibrationDir, files(j).name);
                elseif strcmp(subdir, 'Src') && endsWith(files(j).name, '_calibration.c')
                    [~, base] = fileparts(files(j).name);
                    valuesFile = [base '_values.h'];
                    if isfile(fullfile(exportDir, 'Inc', valuesFile))
                        writeText(destinationFile, sprintf('#include "Calibration/%s"\n', valuesFile));
                        continue;
                    end
                end
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
