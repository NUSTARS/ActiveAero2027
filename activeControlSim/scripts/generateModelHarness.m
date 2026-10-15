function generateModelHarness(modelName, buildDir)
%GENERATEMODELHARNESS Extract the generated ERT example main into a reusable
% STM32 application harness. Exports toIDE/Src/<model>_initialize.c and
% toIDE/Inc/<model>_initialize.h. Does not modify ert_main.c.
%
% The parser intentionally fails closed if it cannot recognize the model's
% generated main/one-step/init structure. Review the outputs after changes
% to code-generation settings, especially scheduling and multi-rate models.

    generatedDir = fullfile(buildDir, [modelName '_ert_rtw']);
    mainFile = fullfile(generatedDir, 'ert_main.c');
    if ~isfile(mainFile)
        error('Cannot locate generated ERT example main: %s', mainFile);
    end
    code = fileread(mainFile);
    nameEsc = regexptranslate('escape', modelName);

    % Identify the generated one-step DEFINITION (not its prototype).
    onePat = '(?m)^\s*void\s+rt_OneStep\s*\('; 
    starts = regexp(code, onePat, 'start');
    if isempty(starts)
        error('%s: no rt_OneStep found in ert_main.c.', modelName);
    end
    oneStart = [];
    oneBrace = [];
    oneClose = [];
    for k = 1:numel(starts)
        [brace, closing] = getFunctionBraces(code, starts(k));
        if ~isempty(brace)
            oneStart = starts(k);
            oneBrace = brace;
            oneClose = closing;
            break;
        end
    end
    if isempty(oneStart)
        error('%s: no rt_OneStep definition found.', modelName);
    end
    oneHeader = code(oneStart:oneBrace-1);
    oneBody = code(oneBrace:oneClose);
    % Rename the function itself, without rewriting its implementation.
    oneHeader = regexprep(oneHeader, '(?<![A-Za-z0-9_])rt_OneStep(?![A-Za-z0-9_])', ...
        ['rt_OneStep_' modelName], 'once');
    oneDefinition = [strtrim(oneHeader) newline oneBody];

    mainStarts = regexp(code, '(?m)^\s*(?:int_T|int|void)\s+main\s*\(', 'start');
    if numel(mainStarts) ~= 1
        error('%s: expected exactly one generated main() definition.', modelName);
    end
    [mainBrace, mainClose] = getFunctionBraces(code, mainStarts(1));
    if isempty(mainBrace)
        error('%s: cannot parse generated main().', modelName);
    end
    mainBody = code(mainBrace+1:mainClose-1);

    % Locate the model instance by its relationship to the generated
    % model pointer, not by a fixed symbol name. Identifier-format options
    % can rename the type, instance, and pointer independently.
    ptrPattern = ['(?m)^\s*static\s+([A-Za-z_]\w*)\s*' ...
        '\*\s*const\s+([A-Za-z_]\w*)\s*=\s*&\s*' ...
        '([A-Za-z_]\w*)\s*;'];
    ptrTokens = regexp(code(1:oneStart-1), ptrPattern, 'tokens');
    if numel(ptrTokens) ~= 1
        error(['%s: expected one static model pointer initialized from ' ...
            'a model instance. Inspect ert_main.c and provide the static ' ...
            'declarations for an unsupported layout.'], modelName);
    end
    modelType = ptrTokens{1}{1};
    modelPtr = ptrTokens{1}{2};
    modelInstance = ptrTokens{1}{3};
    instancePat = ['(?m)^\s*static\s+' regexptranslate('escape', modelType) ...
        '\s+' regexptranslate('escape', modelInstance) '\s*;'];
    if isempty(regexp(code(1:oneStart-1), instancePat, 'once'))
        error('%s: model pointer references %s but its static declaration is missing.', ...
            modelName, modelInstance);
    end
    % Get the local alias used by the code-generated main() assignments.
    aliasTokens = regexp(mainBody, ...
        ['(?<![A-Za-z0-9_])' regexptranslate('escape', modelType) ...
         '\s*\*\s*const\s+([A-Za-z_]\w*)\s*=\s*' ...
         regexptranslate('escape', modelPtr) '\s*;'], 'tokens', 'once');
    if isempty(aliasTokens)
        error('%s: cannot locate the model-pointer alias in main().', modelName);
    end
    modelVar = aliasTokens{1};
    % Extract all file-scope static variables directly from the generated
    % main harness, preserving input/output declarations and initialization.
    declarationStart = regexp(code, '(?m)^\s*static\s+', 'start', 'once');
    if isempty(declarationStart) || declarationStart > oneStart
        error('%s: expected generated static declarations before rt_OneStep.', modelName);
    end
    headerCode = code(declarationStart:oneStart-1);
    % Drop the rt_OneStep prototype and commentary from the declaration region.
    firstProto = regexp(headerCode, '(?m)^\s*void\s+rt_OneStep\s*\(', 'start', 'once');
    if ~isempty(firstProto)
        headerCode = headerCode(1:firstProto-1);
    end
    % Retain static declarations and associated root-port comments, but
    % trim the introductory rt_OneStep commentary.
    stepComment = strfind(headerCode, 'Associating rt_OneStep');
    if ~isempty(stepComment)
        lastOpen = findstr(headerCode(1:stepComment(1)), '/*'); %#ok<FSTR>
        if ~isempty(lastOpen)
            headerCode = headerCode(1:lastOpen(end)-1);
        end
    end
    declarations = strtrim(headerCode);
    if isempty(regexp(declarations, instancePat, 'once'))
        error('%s: cannot verify expected static model instance.', modelName);
    end

    % Bus input storage passed to generated initialize() is zeroed there.
    % Keep that default storage for initialization, then route each step to
    % the caller-owned bus supplied to this harness's setup function.
    modelHeader = fileread(fullfile(generatedDir, [modelName '.h']));
    inputTokens = regexp(declarations, ...
        '(?m)^\s*static\s+([A-Za-z_]\w*)\s+(rtU_[A-Za-z_]\w*)\s*;', 'tokens');
    busTypes = {};
    busParameters = {};
    busPointerDeclarations = {};
    busSetupAssignments = {};
    for k = 1:numel(inputTokens)
        busType = inputTokens{k}{1};
        busVariable = inputTokens{k}{2};
        typePattern = ['(?s)typedef\s+struct\s*\{.*?\}\s*' ...
            regexptranslate('escape', busType) '\s*;'];
        if isempty(regexp(modelHeader, typePattern, 'once'))
            continue;
        end
        busPointer = [busVariable '_inputPtr'];
        busParameter = ['input_' regexprep(busVariable, '^rtU_', '')];
        busTypes{end+1} = busType; %#ok<AGROW>
        busParameters{end+1} = busParameter; %#ok<AGROW>
        busPointerDeclarations{end+1} = sprintf( ...
            'static %s *%s = &%s;', busType, busPointer, busVariable); %#ok<AGROW>
        busSetupAssignments{end+1} = sprintf( ...
            '    %s = %s;\n', busPointer, busParameter); %#ok<AGROW>
        oneDefinition = regexprep(oneDefinition, ...
            ['&\s*' regexptranslate('escape', busVariable) '(?![A-Za-z0-9_])'], ...
            busPointer);
    end
    if ~isempty(busPointerDeclarations)
        declarations = sprintf('%s\n%s', declarations, ...
            strjoin(busPointerDeclarations, newline));
    end
    setupParameters = cell(size(busTypes));
    for k = 1:numel(busTypes)
        setupParameters{k} = sprintf('%s *%s', busTypes{k}, busParameters{k});
    end
    if isempty(setupParameters)
        setupParameterList = 'void';
    else
        setupParameterList = strjoin(setupParameters, ', ');
    end
    setupDeclaration = sprintf('void %s_setup(%s);', modelName, setupParameterList);
    setupDefinition = sprintf('void %s_setup(%s)', modelName, setupParameterList);
    setupArguments = strjoin(busSetupAssignments, '');
    if isempty(busTypes)
        setupDocumentation = '';
    else
        setupDocumentation = ['/* Pass caller-owned bus inputs; setup initializes ' ...
            'the model before binding them. Keep them valid while stepping. */' newline];
    end

    sensorBusInitializerDeclaration = '';
    sensorBusInputParameter = '';
    sensorBusInitializerDefinition = '';
    sensorMainIncludeDeclaration = '';
    sensorFieldPatterns = { ...
        '(?m)truth_bus\s+truth_bus\s*;', ...
        '(?m)real_T\s+fBdyMeas_mps2\s*\[\s*3\s*\]\s*;', ...
        '(?m)real_T\s+wBdyMeas_rps\s*\[\s*3\s*\]\s*;', ...
        '(?m)real_T\s+magBdyMeas_nT\s*\[\s*3\s*\]\s*;', ...
        '(?m)real_T\s+baroMeas_Pa\s*;'};
    sensorBusIndex = find(strcmp(busTypes, 'sensor_bus'), 1);
    hasSensorBusInput = ~isempty(sensorBusIndex);
    hasSensorFields = all(cellfun(@(pattern) ...
        ~isempty(regexp(modelHeader, pattern, 'once')), sensorFieldPatterns));
    if hasSensorBusInput && hasSensorFields
        sensorBusInputParameter = busParameters{sensorBusIndex};
        sensorMainIncludeDeclaration = sprintf( ...
            '#include <stddef.h>\n#include "main.h"\n');
        sensorBusInitializerDeclaration = sprintf([ ...
            '/* Copy accel in m/s^2 and gyro in deg/s (converted to rad/s); pass NULL mag. */\n' ...
            'void %s_initializeSensorBus(sensor_bus *bus, ' ...
            'const Vector3f_t *accel, const Vector3f_t *gyro, ' ...
            'const Vector3f_t *mag, real_T baroMeas_Pa);\n'], modelName);
        sensorBusInitializerDefinition = sprintf([ ...
            'void %s_initializeSensorBus(sensor_bus *bus, ' ...
            'const Vector3f_t *accel, const Vector3f_t *gyro, ' ...
            'const Vector3f_t *mag, real_T baroMeas_Pa)\n{\n' ...
            '    const real_T DEG_TO_RAD = 3.14159265358979323846 / 180.0;\n' ...
            '    size_t i;\n\n' ...
            '    for (i = 0U; i < 3U; ++i) {\n' ...
            '        bus->truth_bus.gyroBiasTrue_rps[i] = 0.0;\n' ...
            '        bus->truth_bus.accBiasTrue_mps2[i] = 0.0;\n' ...
            '        bus->magBdyMeas_nT[i] = 0.0;\n' ...
            '    }\n' ...
            '    if (mag != NULL) {\n' ...
            '        bus->magBdyMeas_nT[0] = mag->x;\n' ...
            '        bus->magBdyMeas_nT[1] = mag->y;\n' ...
            '        bus->magBdyMeas_nT[2] = mag->z;\n' ...
            '    }\n' ...
            '    bus->fBdyMeas_mps2[0] = accel->x;\n' ...
            '    bus->fBdyMeas_mps2[1] = accel->y;\n' ...
            '    bus->fBdyMeas_mps2[2] = accel->z;\n' ...
            '    bus->wBdyMeas_rps[0] = gyro->x * DEG_TO_RAD;\n' ...
            '    bus->wBdyMeas_rps[1] = gyro->y * DEG_TO_RAD;\n' ...
            '    bus->wBdyMeas_rps[2] = gyro->z * DEG_TO_RAD;\n' ...
            '    bus->baroMeas_Pa = baroMeas_Pa;\n' ...
            '}\n\n'], modelName);
    end

    % Copy the model setup assignments and generated initialize call from
    % main() rather than manufacturing a signature from the model's ports.
    % These are extracted as balanced C statements ending in semicolons.
    initStart = regexp(mainBody, ['(?<![A-Za-z0-9_])' nameEsc '_initialize\s*\('], 'start', 'once');
    if isempty(initStart)
        calls = regexp(mainBody, '[A-Za-z_]\w*\s*\(', 'match');
        error(['%s: no call to %s_initialize(...) inside generated main(). ' ...
            'Calls found: %s'], modelName, modelName, strjoin(calls, ', '));
    end
    initStatement = getCallStatement(mainBody, initStart);
    assignments = regexp(mainBody, ...
        [regexptranslate('escape', modelVar) '\s*->\s*[A-Za-z_]\w*\s*=\s*[^;]+;'], 'match');
    if isempty(assignments)
        error('%s: no model data bindings found in main().', modelName);
    end
    % Bindings should refer to the same local alias as in generated main().
    setupBody = sprintf('    %s *const %s = %s;\n', modelType, modelVar, modelPtr);
    for k = 1:numel(assignments)
        setupBody = [setupBody '    ' strtrim(assignments{k}) newline]; %#ok<AGROW>
    end
    setupBody = [setupBody '    ' strtrim(initStatement) newline setupArguments];

    terminateStart = regexp(mainBody, ['(?<![A-Za-z0-9_])' nameEsc '_terminate\s*\('], 'start', 'once');
    shutdownDeclaration = '';
    shutdownDefinition = '';
    if ~isempty(terminateStart)
        terminateStatement = getCallStatement(mainBody, terminateStart);
        shutdownDeclaration = sprintf('void %s_shutdown(void);\n', modelName);
        shutdownDefinition = sprintf([ ...
            'void %s_shutdown(void)\n{\n' ...
            '    %s *const %s = %s;\n' ...
            '    %s\n}\n\n'], ...
            modelName, modelType, modelVar, modelPtr, strtrim(terminateStatement));
    end
    guard = upper(regexprep([modelName '_initialize_H'], '[^a-zA-Z0-9_]', '_'));
    headerName = [modelName '_initialize.h'];
    sourceName = [modelName '_initialize.c'];

    header = sprintf([ ...
        '/* Auto-extracted from %s. Do not edit; regenerate via buildModels.m. */\n' ...
        '#ifndef %s\n#define %s\n\n' ...
        '#include "%s.h"\n' ...
        '%s\n' ...
        '%s%s\n' ...
        '%s' ...
        'void rt_OneStep_%s(%s *const %s);\n' ...
        'void %s_oneStep(void);\n' ...
        '%s' ...
        '%s *%s_getModel(void);\n\n' ...
        '#endif /* %s */\n'], ...
        modelName, guard, guard, modelName, sensorMainIncludeDeclaration, ...
        setupDocumentation, setupDeclaration, sensorBusInitializerDeclaration, ...
        modelName, modelType, modelVar, modelName, shutdownDeclaration, ...
        modelType, modelName, guard);

    source = sprintf([ ...
        '/* Auto-extracted from %s/ert_main.c. Never compile ert_main.c into CubeIDE. */\n' ...
        '#include <stddef.h>\n' ...
        '#include "%s"\n\n' ...
        '%s\n\n%s\n\n' ...
        '%s\n{\n%s}\n\n' ...
        '%s' ...
        'void %s_oneStep(void)\n{\n' ...
        '    rt_OneStep_%s(%s);\n}\n\n' ...
        '%s' ...
        '%s *%s_getModel(void)\n{\n    return %s;\n}\n'], ...
        modelName, headerName, declarations, oneDefinition, ...
        setupDefinition, setupBody, sensorBusInitializerDefinition, ...
        modelName, modelName, modelPtr, shutdownDefinition, ...
        modelType, modelName, modelPtr);

    srcDir = fullfile(buildDir, 'toIDE', 'Src');
    incDir = fullfile(buildDir, 'toIDE', 'Inc');
    if ~isfolder(srcDir) || ~isfolder(incDir)
        error('%s: toIDE/Src and toIDE/Inc must exist before harness export.', modelName);
    end
    writeFile(fullfile(srcDir, sourceName), source);
    writeFile(fullfile(incDir, headerName), header);

    guide = sprintf([ ...
        '# STM32 integration: %s\n\n' ...
        'Compile the generated C sources under `Src/` and include headers ' ...
        'from `Inc/`. Do not compile `ert_main.c`.\n\n' ...
        'Call `%s_setup` once during startup, then call `%s_oneStep` once ' ...
        'per generated base-rate interval from the STM32 timer/task. ' ...
        'Do not step concurrently or re-entrantly.\n\n'], ...
        modelName, modelName, modelName);
    guide = [guide sprintf('```c\n#include "%s_initialize.h"\n', modelName)];
    for k = 1:numel(busTypes)
        guide = [guide sprintf('static %s %s;\n', ...
            busTypes{k}, busParameters{k})];
    end
    if ~isempty(sensorBusInitializerDeclaration)
        guide = [guide ...
            '/* Include the STM32 directory containing main.h in the include path. */' newline ...
            'static FlightData_t polledSensors;' newline];
    end
    guide = [guide sprintf('\nvoid initializeModel(void)\n{\n    %s_setup(', modelName)];
    setupCallArgs = cellfun(@(parameter) ['&' parameter], ...
        busParameters, 'UniformOutput', false);
    guide = [guide strjoin(setupCallArgs, ', ') sprintf(');\n}\n\n')];
    guide = [guide sprintf('void modelTick(void)\n{\n')];
    if ~isempty(sensorBusInitializerDeclaration)
        guide = [guide ...
            '    /* Accel in m/s^2 and gyro in deg/s; helper converts gyro to rad/s. */' newline ...
            sprintf(['    %s_initializeSensorBus(&%s, ' ...
            '&polledSensors.bmi_accel, &polledSensors.bmi_gyro, NULL, ' ...
            'polledSensors.bmp581_pressure);\n'], modelName, sensorBusInputParameter)];
    elseif ~isempty(busTypes)
        guide = [guide '    /* Update caller-owned bus fields from polled data. */' newline];
    end
    guide = [guide sprintf('    %s_oneStep();\n}\n```\n', modelName)];
    if isempty(busTypes)
        guide = [guide newline 'This model has no caller-owned bus inputs. Its ' ...
            'bus outputs use model-owned storage.' newline];
    elseif ~isempty(sensorBusInitializerDeclaration)
        guide = [guide newline '`initializeSensorBus` copies x/y/z from ' ...
            'caller-selected `Vector3f_t` accel/gyro fields, converts gyro ' ...
            'values from deg/s to rad/s, and copies pressure in Pa. Use BMI088 ' ...
            'or LSM6DSO fields and BMP581 or BMP585 pressure as appropriate. ' ...
            '`FlightData_t` has no magnetometer field, so pass `NULL` for now; ' ...
            'later pass a pointer to a `Vector3f_t` magnetometer reading. A NULL ' ...
            'magnetometer and unavailable `truth_bus` bias fields are zeroed.' newline];
        guide = [guide newline '## STM32CubeIDE project settings' newline newline ...
            'Keep `autocodeLib_CM7` imported in the same workspace as the ' ...
            'application, add it under the application project''s ' ...
            '`Project References`, and build the library for the same CM7 ' ...
            'target, configuration, and floating-point ABI as the application.' newline newline ...
            'Because `autocodeModel_initialize.h` includes `main.h`, add the ' ...
            'consumer application''s `Core/Inc` directory to the library compiler ' ...
            'include paths (`autocodeLib_CM7` > `Properties > C/C++ Build > ' ...
            'Settings > MCU GCC Compiler > Include paths`): ' ...
            '`${workspace_loc:/{Project}/Core/Inc}`. Replace `{Project}` with ' ...
            'the consumer CubeIDE project name. In the application compiler ' ...
            'include paths, include both its own `Core/Inc` and ' ...
            '`${workspace_loc:/autocodeLib/CM7/Inc}` for the generated API headers.' newline newline ...
            'In the application''s `Properties > C/C++ Build > Settings > MCU GCC Linker > Libraries`, ' ...
            'set the Debug library search path to ' ...
            '`${workspace_loc:/autocodeLib/CM7/Debug}` and add library ' ...
            '`autocodeLib_CM7` (omit the `lib` prefix and `.a` suffix). For ' ...
            'Release, build the library''s Release configuration and use its ' ...
            'matching `Release` output directory. Link the archive or compile ' ...
            'the generated model sources directly, but do not do both.' newline];
    else
        guide = [guide newline 'Populate caller-owned buses using the types in ' ...
            sprintf('`%s.h`', modelName) ' and keep their storage valid while stepping.' newline];
    end
    if strcmp(modelName, 'autocodePlant')
        guide = [guide newline '## Shared generated dependencies' newline newline ...
            '`autocodePlant` is secondary in `buildModels.m`; its `toIDE/` ' ...
            'export omits shared headers and sources. In STM32CubeIDE, also ' ...
            'add `build_autocodeModel/toIDE/Inc` to the include paths and ' ...
            'compile the primary utility sources from ' ...
            '`build_autocodeModel/toIDE/Src` exactly once: ' ...
            '`rtGetInf.c`, `rtGetNaN.c`, `rt_atan2d_snf.c`, and ' ...
            '`rt_nonfinite.c`. If these sources are already in the project, ' ...
            'do not add duplicate entries.' newline];
    end
    writeFile(fullfile(buildDir, 'toIDE', 'README.md'), guide);
    fprintf('Generated harness: %s, %s\n', sourceName, headerName);
end

function [brace, closing] = getFunctionBraces(source, pos)
    brace = [];
    closing = [];
    % Function prototypes end in a semicolon before their first brace.
    openParen = find(source(pos:end) == '(', 1);
    if isempty(openParen), return; end
    openParen = openParen + pos - 1;
    closeParen = findClosing(source, openParen, '(', ')');
    next = skipCTrivia(source, closeParen + 1);
    if isempty(next) || source(next) ~= '{', return; end
    brace = next;
    closing = findClosing(source, brace, '{', '}');
end

function statement = getCallStatement(source, start)
    openParen = find(source(start:end) == '(', 1);
    if isempty(openParen)
        error('Malformed generated call near: %s', source(start:min(end,start+65)));
    end
    openParen = openParen + start - 1;
    closeParen = findClosing(source, openParen, '(', ')');
    after = skipCTrivia(source, closeParen + 1);
    if isempty(after) || source(after) ~= ';'
        error('Malformed generated call near: %s', source(start:min(end,start+65)));
    end
    statement = source(start:after);
end

function ending = findClosing(source, opening, openToken, closeToken)
    depth = 0;
    ending = [];
    idx = opening;
    while idx <= numel(source)
        ch = source(idx);
        if ch == '/' && idx < numel(source) && source(idx + 1) == '/'
            newlinePos = find(source(idx+2:end) == newline, 1);
            if isempty(newlinePos), return; end
            idx = idx + newlinePos + 1;
            continue;
        elseif ch == '/' && idx < numel(source) && source(idx + 1) == '*'
            closeComment = strfind(source(idx+2:end), '*/');
            if isempty(closeComment)
                error('Unterminated comment in ert_main.c.');
            end
            idx = idx + closeComment(1) + 3;
            continue;
        elseif ch == '"' || ch == ''''
            quote = ch;
            idx = idx + 1;
            while idx <= numel(source)
                if source(idx) == '\'
                    idx = idx + 2;
                elseif source(idx) == quote
                    break;
                else
                    idx = idx + 1;
                end
            end
        elseif ch == openToken
            depth = depth + 1;
        elseif ch == closeToken
            depth = depth - 1;
            if depth == 0
                ending = idx;
                return;
            end
        end
        idx = idx + 1;
    end
    error('Unmatched delimiter in ert_main.c.');
end

function next = skipCTrivia(source, idx)
    next = [];
    while idx <= numel(source)
        if isspace(source(idx))
            idx = idx + 1;
        elseif source(idx) == '/' && idx < numel(source) && source(idx + 1) == '/'
            newlinePos = find(source(idx+2:end) == newline, 1);
            if isempty(newlinePos), return; end
            idx = idx + newlinePos + 1;
        elseif source(idx) == '/' && idx < numel(source) && source(idx + 1) == '*'
            closeComment = strfind(source(idx+2:end), '*/');
            if isempty(closeComment)
                error('Unterminated comment in ert_main.c.');
            end
            idx = idx + closeComment(1) + 3;
        else
            next = idx;
            return;
        end
    end
end

function writeFile(file, text)
    fid = fopen(file, 'w');
    if fid == -1, error('Cannot write: %s', file); end
    closer = onCleanup(@() fclose(fid));
    fwrite(fid, text, 'char');
end
