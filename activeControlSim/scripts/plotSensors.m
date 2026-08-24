function plotSensors(varargin)

fileArgs = {};
i = 1;
while i <= numel(varargin) && ischar(varargin{i}) ...
        && endsWith(varargin{i}, '.mat', 'IgnoreCase', true)
    fileArgs{end+1} = varargin{i}; %#ok<AGROW>
    i = i + 1;
end
if numel(fileArgs) > 2
    error('plotSensors:tooManyFiles', ...
        'Pass at most two .mat files to overlay.');
end

optArgs = varargin(i:end);
if mod(numel(optArgs), 2) ~= 0
    error('plotSensors:badOptions', ...
        'Options must be name-value pairs.');
end
opts = struct('numFrames', 5, 'bodyScale', [], 'forwardAxis', [1;0;0]);
for k = 1:2:numel(optArgs)
    opts.(optArgs{k}) = optArgs{k+1};
end

if isempty(fileArgs)
    if ~evalin('base', 'exist(''out'', ''var'')')
        error('plotSensors:noOut', ...
            ['No .mat file given and `out` not found in the base ', ...
            'workspace -- run scripts/runModel.m first.']);
    end
    runs = {extractRun_local(evalin('base', 'out'), 'workspace', opts.forwardAxis)};
else
    runs = cell(1, numel(fileArgs));
    for k = 1:numel(fileArgs)
        S = load(fileArgs{k}, 'out');
        if ~isfield(S, 'out')
            error('plotSensors:noOutInFile', ...
                '%s does not contain an ''out'' variable.', fileArgs{k});
        end
        [~, label] = fileparts(fileArgs{k});
        runs{k} = extractRun_local(S.out, label, opts.forwardAxis);
    end
end

if isempty(opts.bodyScale)
    span = max(max(runs{1}.pos_plot) - min(runs{1}.pos_plot));
    if span == 0 || isnan(span), span = 1; end
    opts.bodyScale = 0.05 * span;
end

runColors = {[0 0.4470 0.7410], [0.8500 0.3250 0.0980]};   % blue, orange, per run
noseColor = 'r';                                            % fixed across runs
velColor  = [0 0.6 0];    

