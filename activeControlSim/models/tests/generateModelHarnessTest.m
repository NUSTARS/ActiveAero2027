function tests = generateModelHarnessTest
% Regression tests for extracting generated ERT C functions.
tests = functiontests(localfunctions);
end

function testEscapedQuoteDoesNotEndFunction(testCase)
    projectModelsDir = fileparts(fileparts(mfilename('fullpath')));
    scriptsDir = fullfile(fileparts(projectModelsDir), 'scripts');
    addpath(scriptsDir);
    cleanupPath = onCleanup(@() rmpath(scriptsDir));

    buildDir = tempname;
    mkdir(buildDir);
    cleanupBuild = onCleanup(@() rmdir(buildDir, 's'));
    generatedDir = fullfile(buildDir, 'fixture_ert_rtw');
    srcDir = fullfile(buildDir, 'toIDE', 'Src');
    incDir = fullfile(buildDir, 'toIDE', 'Inc');
    mkdir(generatedDir);
    mkdir(srcDir);
    mkdir(incDir);

    ertMain = sprintf([ ...
        'static Model model_;\n' ...
        'static Model *const modelPtr = &model_;\n' ...
        'void rt_OneStep(Model *const model);\n' ...
        'void rt_OneStep(Model *const model)\n' ...
        '{\n' ...
        '  puts("a\\\"}b");\n' ...
        '  puts("after");\n' ...
        '}\n' ...
        'int main(void)\n' ...
        '{\n' ...
        '  Model *const local = modelPtr;\n' ...
        '  local->field = 0;\n' ...
        '  fixture_initialize(local);\n' ...
        '  return 0;\n' ...
        '}\n']);
    writeText(fullfile(generatedDir, 'ert_main.c'), ertMain);

    generateModelHarness('fixture', buildDir);

    generated = fileread(fullfile(srcDir, 'fixture_initialize.c'));
    verifyTrue(testCase, contains(generated, 'puts("a\"}b");'));
    verifyTrue(testCase, contains(generated, 'puts("after");'));
    verifyTrue(testCase, contains(generated, 'void fixture_setup(void)'));
end

function writeText(path, text)
    fid = fopen(path, 'w');
    if fid < 0
        error('Cannot write test fixture: %s', path);
    end
    cleanup = onCleanup(@() fclose(fid));
    fwrite(fid, text, 'char');
end
