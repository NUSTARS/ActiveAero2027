%BUILDDATADICTIONARIES  Build and link a data dictionary to a model, for
%   each entry in CONFIG below.

% modelFile (relative to repo root)   dictName        defineFcn
CONFIG = {
    'models/plant/plant.slx',         'plantParams',  @definePlantDD
};

repoRoot = fileparts(fileparts(mfilename('fullpath')));
addpath(fullfile(repoRoot, 'scripts', 'helpers'));
addpath(fullfile(repoRoot, 'dataDictionaries'));

for i = 1:size(CONFIG,1)
    modelFile = CONFIG{i,1};
    dictName  = CONFIG{i,2};
    defineFcn = CONFIG{i,3};

    modelPath = fullfile(repoRoot, modelFile);
    modelPath = char(java.io.File(modelPath).getCanonicalPath());
    sdddPath  = fullfile(fileparts(modelPath), [dictName, '.sldd']);

    P = defineFcn();
    linkDataDictionary(modelPath, sdddPath, P);
end
