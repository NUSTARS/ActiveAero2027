function T = mcRunDeviation(simIn, mc)
%MCRUNDEVIATION  Dispersed parameter deviations of one Monte Carlo run.
%
%   T = mcRunDeviation(simIn, mc)
%     simIn  one run's Simulink.SimulationInput from runMonteCarlo.m
%            (e.g. simIn(42) from results/monteCarloResults.mat)
%     mc     the mc struct saved alongside it, for the dispersed parameter
%            names and half-widths. Optional -- loaded from
%            results/monteCarloResults.mat if omitted.
%
%   Returns a table with one row per dispersed element (elements with a
%   zero half-width are skipped):
%     Parameter     '<entry>.<field>', as in runMonteCarlo's dispersions
%     Element       linear index into the parameter (1 for scalars)
%     Nominal       value from definePlantDD + defineSensorDD
%     Value         value this run was given
%     Deviation     Value - Nominal, in the parameter's own units
%     HalfWidth     dispersion half-width
%     PctOfRange    Deviation / HalfWidth * 100, i.e. where the draw
%                   landed in its +/- range (-100% .. +100%)
%   With no output argument, the table is printed instead.
%
%   The run's value is read back from simIn's variable overrides; an entry
%   simIn doesn't override was left at nominal.

%   Needs the repo on the path (setupPaths), as definePlantDD reads its
%   data files by bare name.

repoRoot = fileparts(fileparts(fileparts(mfilename('fullpath'))));

if nargin < 2
    S = load(fullfile(repoRoot, 'results', 'monteCarloResults.mat'), 'mc');
    mc = S.mc;
end
if numel(simIn) ~= 1
    error('mcRunDeviation:notScalar', ...
        'Pass one run''s SimulationInput, e.g. simIn(%d), not all %d.', 1, numel(simIn));
end

% Nominal values, as in runMonteCarlo.m. defineSensorDD reseeds rng, so
% the caller's rng state is put back afterwards.
rngState = rng;
P0 = mergeStructs_local(definePlantDD(), defineSensorDD());
rng(rngState);

% Dictionary entries this run overrides, by name.
overrides = struct();
for v = 1:numel(simIn.Variables)
    val = simIn.Variables(v).Value;
    if isa(val, 'Simulink.Parameter')
        val = val.Value;
    end
    overrides.(simIn.Variables(v).Name) = val;
end

Parameter = {}; Element = []; Nominal = []; Value = [];
Deviation = []; HalfWidth = []; PctOfRange = [];
for d = 1:numel(mc.input.dispNames)
    name = mc.input.dispNames{d};
    path = strsplit(name, '.');
    nom = getfield(P0, path{:}); %#ok<GFLD>
    if isfield(overrides, path{1})
        runPrm = overrides;
    else
        runPrm = P0;
    end
    val = getfield(runPrm, path{:}); %#ok<GFLD>
    hw = mc.input.dispHalfWidth{d};

    for k = find(hw(:)' ~= 0)
        Parameter{end+1,1} = name; %#ok<AGROW>
        Element(end+1,1)    = k;                                %#ok<AGROW>
        Nominal(end+1,1)    = nom(k);                           %#ok<AGROW>
        Value(end+1,1)      = val(k);                           %#ok<AGROW>
        Deviation(end+1,1)  = val(k) - nom(k);                  %#ok<AGROW>
        HalfWidth(end+1,1)  = hw(k);                            %#ok<AGROW>
        PctOfRange(end+1,1) = 100 * (val(k) - nom(k)) / hw(k);  %#ok<AGROW>
    end
end

T = table(Parameter, Element, Nominal, Value, Deviation, HalfWidth, PctOfRange);

if nargout == 0
    disp(T);
    clear T
end

end

% ======================================================================
function M = mergeStructs_local(varargin)
    % Merge the top-level fields of each input struct into one.
    M = struct();
    for k = 1:numel(varargin)
        fn = fieldnames(varargin{k});
        for j = 1:numel(fn)
            M.(fn{j}) = varargin{k}.(fn{j});
        end
    end
end
