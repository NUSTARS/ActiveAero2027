function exportSimDataCsv(varargin)
%EXPORTSIMDATACSV  Write one logged run's truth + sensor data to a CSV.
%
%   exportSimDataCsv()                   export `out` from the base
%                                         workspace to results/simData.csv
%   exportSimDataCsv(matFile)            export `out` saved in matFile to
%                                         results/simData.csv
%   exportSimDataCsv(csvFile)            export `out` from the base
%                                         workspace to csvFile
%   exportSimDataCsv(matFile, csvFile)   export `out` saved in matFile to
%                                         csvFile
%
%   Each matFile must contain an `out` variable, e.g. as saved by
%   scripts/runModel.m (results/simResults.mat).
%
%   Time base is the first available field of simout.eom_bus (checked in
%   the order posNed_m, velBdy_mps, q_na, wBdy_rps, accBdy_mps2) -- i.e.
%   the trajectory integrator's own samples. Every other signal
%   (aeroParams_bus, enviornment_bus, sensor_bus) is resampled onto that
%   time base: truth/state signals with linear interpolation, sensor
%   measurements with zero-order hold (a real sensor holds its last
%   reading between updates, since sensors sample at their own
%   independent rates -- see plotSensorData.m). A bus or field that
%   isn't present in `out` is simply skipped -- its columns are omitted,
%   not filled with NaN placeholders.
%
%   COLUMNS (all in the buses' native units)
%     t_s
%     posNedN_m, posNedE_m, posNedD_m        (eom_bus.posNed_m)          truth
%     q0, q1, q2, q3                         (eom_bus.q_na)              truth
%     velBdyU_mps, velBdyV_mps, velBdyW_mps  (eom_bus.velBdy_mps)        truth
%     wBdyP_rps, wBdyQ_rps, wBdyR_rps        (eom_bus.wBdy_rps)          truth
%     accBdyX_mps2, accBdyY_mps2, accBdyZ_mps2 (eom_bus.accBdy_mps2)     truth
%     alpha_rad                              (aeroParams_bus.alpha_rad)  truth
%     pressureTrue_Pa                        (enviornment_bus.pressure_Pa) truth
%     fMeasX_mps2, fMeasY_mps2, fMeasZ_mps2  (sensor_bus.fBdyMeas_mps2)  sensor
%     wMeasP_rps, wMeasQ_rps, wMeasR_rps     (sensor_bus.wBdyMeas_rps)   sensor
%     magMeasX_nT, magMeasY_nT, magMeasZ_nT  (sensor_bus.magBdyMeas_nT)  sensor
%     baroMeas_Pa                            (sensor_bus.baroMeas_Pa)    sensor

% ------------------------------------------------------- parse arguments
fileArg = '';
csvArg  = '';
for k = 1:numel(varargin)
    a = varargin{k};
    if ~(ischar(a) || isstring(a))
        error('exportSimDataCsv:badArg', 'Arguments must be file path strings.');
    end
    a = char(a);
    if endsWith(a, '.mat', 'IgnoreCase', true)
        fileArg = a;
    elseif endsWith(a, '.csv', 'IgnoreCase', true)
        csvArg = a;
    else
        error('exportSimDataCsv:badArg', ...
            'Arguments must end in .mat or .csv, got ''%s''.', a);
    end
end

repoRoot = fileparts(fileparts(mfilename('fullpath')));
if isempty(csvArg)
    csvArg = fullfile(repoRoot, 'results', 'simData.csv');
end

% ------------------------------------------------------------- load run
if isempty(fileArg)
    if ~evalin('base', 'exist(''out'', ''var'')')
        error('exportSimDataCsv:noOut', ...
            ['No .mat file given and `out` not found in the base ', ...
             'workspace -- run scripts/runModel.m first.']);
    end
    out = evalin('base', 'out');
else
    S = load(fileArg, 'out');
    if ~isfield(S, 'out')
        error('exportSimDataCsv:noOutInFile', ...
            '%s does not contain an ''out'' variable.', fileArg);
    end
    out = S.out;
end

try
    simout = out.simout;
catch
    error('exportSimDataCsv:noSimout', ...
        'out.simout not found -- out must be a Simulink sim output.');
end

if ~isstruct(simout) || ~isfield(simout, 'eom_bus')
    error('exportSimDataCsv:noEom', ...
        'simout.eom_bus not found -- need at least the trajectory truth bus.');
end
eom = simout.eom_bus;

% -------------------------------------------------------- pick time base
baseFieldOrder = {'posNed_m','velBdy_mps','q_na','wBdy_rps','accBdy_mps2'};
tsBase = [];
for k = 1:numel(baseFieldOrder)
    if isfield(eom, baseFieldOrder{k})
        tsBase = eom.(baseFieldOrder{k});
        break;
    end
end
if isempty(tsBase)
    error('exportSimDataCsv:noEomFields', ...
        'simout.eom_bus has none of the expected fields (%s).', ...
        strjoin(baseFieldOrder, ', '));
end
t = tsBase.Time(:);
N = numel(t);

% ------------------------------------------------------------ build table
T = table(t, 'VariableNames', {'t_s'});

T = addCols_local(T, t, N, getField_local(eom, 'posNed_m'), ...
    {'posNedN_m','posNedE_m','posNedD_m'}, 'linear');
T = addCols_local(T, t, N, getField_local(eom, 'q_na'), ...
    {'q0','q1','q2','q3'}, 'linear');
T = addCols_local(T, t, N, getField_local(eom, 'velBdy_mps'), ...
    {'velBdyU_mps','velBdyV_mps','velBdyW_mps'}, 'linear');
T = addCols_local(T, t, N, getField_local(eom, 'wBdy_rps'), ...
    {'wBdyP_rps','wBdyQ_rps','wBdyR_rps'}, 'linear');
T = addCols_local(T, t, N, getField_local(eom, 'accBdy_mps2'), ...
    {'accBdyX_mps2','accBdyY_mps2','accBdyZ_mps2'}, 'linear');

if isfield(simout, 'aeroParams_bus')
    T = addCols_local(T, t, N, getField_local(simout.aeroParams_bus, 'alpha_rad'), ...
        {'alpha_rad'}, 'linear');
end

if isfield(simout, 'enviornment_bus')
    T = addCols_local(T, t, N, getField_local(simout.enviornment_bus, 'pressure_Pa'), ...
        {'pressureTrue_Pa'}, 'linear');
end

if isfield(simout, 'sensor_bus')
    sensors = simout.sensor_bus;
    T = addCols_local(T, t, N, getField_local(sensors, 'fBdyMeas_mps2'), ...
        {'fMeasX_mps2','fMeasY_mps2','fMeasZ_mps2'}, 'zoh');
    T = addCols_local(T, t, N, getField_local(sensors, 'wBdyMeas_rps'), ...
        {'wMeasP_rps','wMeasQ_rps','wMeasR_rps'}, 'zoh');
    T = addCols_local(T, t, N, getField_local(sensors, 'magBdyMeas_nT'), ...
        {'magMeasX_nT','magMeasY_nT','magMeasZ_nT'}, 'zoh');
    T = addCols_local(T, t, N, getField_local(sensors, 'baroMeas_Pa'), ...
        {'baroMeas_Pa'}, 'zoh');
end

% ------------------------------------------------------------- write csv
csvDir = fileparts(csvArg);
if ~isempty(csvDir) && ~exist(csvDir, 'dir')
    mkdir(csvDir);
end
writetable(T, csvArg);
fprintf('Wrote %d rows x %d columns to %s\n', height(T), width(T), csvArg);

end

% ======================================================================
function v = getField_local(bus, name)
    % Returns bus.(name) if present, [] otherwise -- lets callers pass
    % the result straight to addCols_local without an isfield check at
    % every call site.
    if ~isempty(bus) && isstruct(bus) && isfield(bus, name)
        v = bus.(name);
    else
        v = [];
    end
end

% ======================================================================
function T = addCols_local(T, t, N, ts, colNames, method)
    % Resample ts (a timeseries) onto t if needed, then append one
    % column per component to T. No-op if ts is [] (field absent from
    % this run's log) -- the columns are simply omitted rather than
    % filled with NaN placeholders.
    if isempty(ts)
        return;
    end
    data = alignRows_local(resampleIfNeeded_local(ts, t, method).Data, N, numel(colNames));
    for j = 1:numel(colNames)
        T.(colNames{j}) = data(:,j);
    end
end

% ======================================================================
function tsOut = resampleIfNeeded_local(tsIn, t, method)
    % Resample tsIn onto time vector t, but only if it isn't already on
    % that grid -- avoids gratuitously reinterpolating (and risking a
    % type/units change) when a signal already matches. Comparing
    % ts.Time to t directly (rather than just numel) also catches the
    % case where two signals happen to share a sample count but not the
    % same instants.
    %
    % method 'zoh' (zero-order hold) is for sensor measurements, which
    % are sample-and-hold and sampled at their own independent rates;
    % 'linear' is for truth/state signals from the integrator.
    if numel(tsIn.Time) == numel(t) && all(tsIn.Time(:) == t(:))
        tsOut = tsIn;
    else
        tsOut = resample(tsIn, t, method);
    end
end

% ======================================================================
function out = alignRows_local(data, N, ncols)
    % squeeze() on a logged timeseries can leave data as Nxncols OR
    % ncolsxN depending on how the signal was dimensioned in Simulink.
    % A blind reshape(data,N,ncols) does not transpose -- it just
    % re-reads memory linearly, silently scrambling rows/columns when
    % the orientation is wrong. Check shape explicitly instead.
    data = squeeze(data);
    if isvector(data)
        data = data(:)';
    end
    if size(data,1) == N && size(data,2) == ncols
        out = data;
    elseif size(data,2) == N && size(data,1) == ncols
        out = data';
    else
        error('alignRows_local:shape', ...
            'Expected data shaped %dx%d or %dx%d, got %s.', ...
            N, ncols, ncols, N, mat2str(size(data)));
    end
end
