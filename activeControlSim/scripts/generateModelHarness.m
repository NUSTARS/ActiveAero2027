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
    setupBody = [setupBody '    ' strtrim(initStatement) newline];

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
        '#include "%s.h"\n\n' ...
        'void %s_setup(void);\n' ...
        'void rt_OneStep_%s(%s *const %s);\n' ...
        'void %s_oneStep(void);\n' ...
        '%s' ...
        '%s *%s_getModel(void);\n\n' ...
        '#endif /* %s */\n'], ...
        modelName, guard, guard, modelName, modelName, modelName, ...
        modelType, modelVar, modelName, shutdownDeclaration, modelType, modelName, guard);

    source = sprintf([ ...
        '/* Auto-extracted from %s/ert_main.c. Never compile ert_main.c into CubeIDE. */\n' ...
        '#include <stddef.h>\n' ...
        '#include "%s"\n\n' ...
        '%s\n\n%s\n\n' ...
        'void %s_setup(void)\n{\n%s}\n\n' ...
        'void %s_oneStep(void)\n{\n' ...
        '    rt_OneStep_%s(%s);\n}\n\n' ...
        '%s' ...
        '%s *%s_getModel(void)\n{\n    return %s;\n}\n'], ...
        modelName, headerName, declarations, oneDefinition, ...
        modelName, setupBody, modelName, modelName, modelPtr, shutdownDefinition, ...
        modelType, modelName, modelPtr);

    srcDir = fullfile(buildDir, 'toIDE', 'Src');
    incDir = fullfile(buildDir, 'toIDE', 'Inc');
    if ~isfolder(srcDir) || ~isfolder(incDir)
        error('%s: toIDE/Src and toIDE/Inc must exist before harness export.', modelName);
    end
    writeFile(fullfile(srcDir, sourceName), source);
    writeFile(fullfile(incDir, headerName), header);
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
