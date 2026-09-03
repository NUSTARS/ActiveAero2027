function plotSensorData(varargin)
%PLOTSENSORDATA  Plot logged sensor measurements against truth.
%
%   plotSensorData()                     plot `out` from the base
%                                         workspace
%   plotSensorData(matFile)              plot `out` saved in matFile
%   plotSensorData(matFile1, matFile2)   overlay two saved runs
%
%   Each matFile must contain an `out` variable, e.g. as saved by
%   scripts/runModel.m (results/simResults.mat).
%
%   Each `out` must have `out.simout`, a struct of nested bus structs,
%   each field a 1x1 timeseries:
%     simout.sensor_bus
%       fBdyMeas_mps2    Nx3   measured specific force (accelerometer) [m/s^2]
%       wBdyMeas_rps     Nx3   measured angular rate (gyro)            [rad/s]
%       magBdyMeas_nT    Nx3   measured magnetic field (magnetometer)  [nT]
%       baroMeas_Pa      Nx1   measured pressure (barometer)           [Pa]
%     simout.eom_bus
%       accBdy_mps2      Nx3   true body-axis acceleration             [m/s^2]
%       wBdy_rps         Nx3   true body-axis angular rate             [rad/s]
%     simout.enviornment_bus
%       pressure_Pa      Nx1   true ambient pressure                   [Pa]
%
%   Truth signals (eom_bus / enviornment_bus) are optional -- if a run's
%   `out` doesn't have them, only the measured sensor traces are drawn
%   for that run.
%
%   OUTPUT
%     Figure 103: Sensors (accelerometer/gyro/magnetometer/barometer)
%     Fixed figure number (deliberately not 1/2, to stay clear of other
%     figures) so re-running overwrites the same window instead of
%     piling up new ones.

% ------------------------------------------------------- parse arguments
fileArgs = {};
i = 1;
while i <= numel(varargin) && ischar(varargin{i}) ...
        && endsWith(varargin{i}, '.mat', 'IgnoreCase', true)
    fileArgs{end+1} = varargin{i}; %#ok<AGROW>
    i = i + 1;
end
if numel(fileArgs) > 2
    error('plotSensorData:tooManyFiles', ...
        'Pass at most two .mat files to overlay.');
end

% ------------------------------------------------------------ load runs
if isempty(fileArgs)
    if ~evalin('base', 'exist(''out'', ''var'')')
        error('plotSensorData:noOut', ...
            ['No .mat file given and `out` not found in the base ', ...
             'workspace -- run scripts/runModel.m first.']);
    end
    runs = {extractRun_local(evalin('base', 'out'), 'workspace')};
else
    runs = cell(1, numel(fileArgs));
    for k = 1:numel(fileArgs)
        S = load(fileArgs{k}, 'out');
        if ~isfield(S, 'out')
            error('plotSensorData:noOutInFile', ...
                '%s does not contain an ''out'' variable.', fileArgs{k});
        end
        [~, label] = fileparts(fileArgs{k});
        runs{k} = extractRun_local(S.out, label);
    end
end

% Axis components get a fixed color each, shared across the
% accelerometer/gyro/magnetometer subplots so "red = X" reads the same
% everywhere. The barometer has no axis, so it gets its own color.
axisColors = {[0.8500 0.3250 0.0980], [0.4660 0.6740 0.1880], [0 0.4470 0.7410]};  % X, Y, Z
baroColor  = [0.4940 0.1840 0.5560];

% With more than one run, color alone can't also distinguish runs (it's
% already spoken for by axis component), so runs are told apart by line
% style instead: solid for the first run, dash-dot for the second. Truth
% uses a lighter/thinner version of the same per-run style.
measStyles  = {'-', '-.'};
truthStyles = {'--', ':'};

% ======================================================== SENSORS WINDOW
figure(103); clf(103); set(103,'Name','Sensors','Color','w');

axAcc  = subplot(2,2,1); hold(axAcc,'on');  grid(axAcc,'on');
xlabel(axAcc,'Time [s]');  ylabel(axAcc,'Specific Force [m/s^2]'); title(axAcc,'Accelerometer');

axGyro = subplot(2,2,2); hold(axGyro,'on'); grid(axGyro,'on');
xlabel(axGyro,'Time [s]'); ylabel(axGyro,'Angular Rate [rad/s]'); title(axGyro,'Gyroscope');

axMag  = subplot(2,2,3); hold(axMag,'on');  grid(axMag,'on');
xlabel(axMag,'Time [s]');  ylabel(axMag,'Field [nT]'); title(axMag,'Magnetometer');

axBaro = subplot(2,2,4); hold(axBaro,'on'); grid(axBaro,'on');
xlabel(axBaro,'Time [s]'); ylabel(axBaro,'Pressure [Pa]'); title(axBaro,'Barometer');

axisLbl = {'X','Y','Z'};
multiRun = numel(runs) > 1;

for k = 1:numel(runs)
    r = runs{k};
    mStyle = measStyles{k};
    tStyle = truthStyles{k};

    plotAxes3_local(axAcc, r.t, r.fMeas, r.hasTruthAcc, r.accTrue, ...
        axisColors, axisLbl, mStyle, tStyle, r.label, multiRun);

    plotAxes3_local(axGyro, r.t, r.wMeas, r.hasTruthGyro, r.wTrue, ...
        axisColors, axisLbl, mStyle, tStyle, r.label, multiRun);

    plotAxes3_local(axMag, r.t, r.magMeas, false, [], ...
        axisColors, axisLbl, mStyle, tStyle, r.label, multiRun);

    plotScalar_local(axBaro, r.t, r.baroMeas, r.hasTruthBaro, r.pressureTrue, ...
        baroColor, 'Baro', mStyle, tStyle, r.label, multiRun);
end

legend(axAcc,  'Location','best');
legend(axGyro, 'Location','best');
legend(axMag,  'Location','best');
legend(axBaro, 'Location','best');

end

% ======================================================================
function plotAxes3_local(ax, t, meas, hasTruth, truth, colors, lbl, mStyle, tStyle, runLabel, multiRun)
    % Plot one 3-axis sensor (X/Y/Z) into ax: a colored, styled measured
    % line per axis (in the legend), plus a matching truth line in the
    % same color (dashed/dotted, excluded from the legend individually).
    for j = 1:3
        if hasTruth
            plot(ax, t, truth(:,j), tStyle, 'Color', colors{j}, ...
                'LineWidth', 1, 'HandleVisibility', 'off');
        end
        plot(ax, t, meas(:,j), mStyle, 'Color', colors{j}, 'LineWidth', 1.3, ...
            'DisplayName', dispName_local(lbl{j}, runLabel, multiRun));
    end
    if hasTruth
        % One dummy entry so the truth line style is explained once,
        % rather than tripling it (one per axis) or leaving it silent.
        plot(ax, nan, nan, tStyle, 'Color', [0.3 0.3 0.3], 'LineWidth', 1, ...
            'DisplayName', dispName_local('Truth', runLabel, multiRun));
    end
end

% ======================================================================
function plotScalar_local(ax, t, meas, hasTruth, truth, color, name, mStyle, tStyle, runLabel, multiRun)
    % Plot one scalar sensor (barometer) into ax, same measured/truth
    % convention as plotAxes3_local.
    if hasTruth
        plot(ax, t, truth, tStyle, 'Color', color, 'LineWidth', 1, ...
            'DisplayName', dispName_local('Truth', runLabel, multiRun));
    end
    plot(ax, t, meas, mStyle, 'Color', color, 'LineWidth', 1.3, ...
        'DisplayName', dispName_local(name, runLabel, multiRun));
end

% ======================================================================
function s = dispName_local(base, runLabel, multiRun)
    % Legend text stays just the component name ("X", "Truth", ...) for
    % the common single-run case; the run label is only appended once a
    % second run makes it necessary to disambiguate.
    if multiRun
        s = sprintf('%s (%s)', base, runLabel);
    else
        s = base;
    end
end

% ======================================================================
function r = extractRun_local(out, label)
    % Pull one run's sensor data out of a Simulink sim output. `out` may
    % be a Simulink.SimulationOutput object (isstruct is false for it,
    % but out.simout works via property access) or a plain struct
    % loaded from a .mat file, so probe with try/catch rather than
    % isstruct/isfield.
    try
        simout = out.simout;
    catch
        error('plotSensorData:noSimout', ...
            '%s: out.simout not found -- out must be a Simulink sim output.', label);
    end

    if ~isstruct(simout) || ~isfield(simout, 'sensor_bus')
        error('plotSensorData:badSimout', ...
            '%s: simout must have field sensor_bus (a bus struct).', label);
    end
    sensors = simout.sensor_bus;

    requiredSensors = {'fBdyMeas_mps2','wBdyMeas_rps','magBdyMeas_nT','baroMeas_Pa'};
    if ~all(isfield(sensors, requiredSensors))
        error('plotSensorData:badSensorBus', ...
            ['%s: simout.sensor_bus must have fields fBdyMeas_mps2, ', ...
             'wBdyMeas_rps, magBdyMeas_nT, baroMeas_Pa (each a timeseries).'], label);
    end

    ts_fMeas   = sensors.fBdyMeas_mps2;
    ts_wMeas   = sensors.wBdyMeas_rps;
    ts_magMeas = sensors.magBdyMeas_nT;
    ts_baro    = sensors.baroMeas_Pa;

    t = ts_fMeas.Time(:);
    N = numel(t);

    % Each sensor samples at its own rate (accRate_Hz, gyroRate_Hz,
    % magRate_Hz, baroRate_Hz are independent in the sensor params), so
    % their timeseries generally do NOT share the accelerometer's time
    % vector/length. Resample onto it -- with zero-order hold, since a
    % real sensor's output is sample-and-hold, not something to smoothly
    % interpolate between updates -- before touching row counts at all.
    fMeas    = alignRows_local(ts_fMeas.Data, N, 3);
    wMeas    = alignRows_local(resampleIfNeeded_local(ts_wMeas, t).Data, N, 3);
    magMeas  = alignRows_local(resampleIfNeeded_local(ts_magMeas, t).Data, N, 3);
    baroMeas = alignRows_local(resampleIfNeeded_local(ts_baro, t).Data, N, 1);

    % Truth signals are optional -- older/partial logs may not have them.
    accTrue = []; wTrue = []; pressureTrue = [];
    hasTruthAcc = false; hasTruthGyro = false; hasTruthBaro = false;

    if isfield(simout, 'eom_bus')
        eom = simout.eom_bus;
        if isfield(eom, 'accBdy_mps2')
            accTrue = alignRows_local(resampleIfNeeded_local(eom.accBdy_mps2, t, 'linear').Data, N, 3);
            hasTruthAcc = true;
        end
        if isfield(eom, 'wBdy_rps')
            wTrue = alignRows_local(resampleIfNeeded_local(eom.wBdy_rps, t, 'linear').Data, N, 3);
            hasTruthGyro = true;
        end
    end
    if isfield(simout, 'enviornment_bus')
        env = simout.enviornment_bus;
        if isfield(env, 'pressure_Pa')
            pressureTrue = alignRows_local(resampleIfNeeded_local(env.pressure_Pa, t, 'linear').Data, N, 1);
            hasTruthBaro = true;
        end
    end

    r = struct( ...
        'label',        label, ...
        't',            t, ...
        'fMeas',        fMeas, ...
        'wMeas',        wMeas, ...
        'magMeas',      magMeas, ...
        'baroMeas',     baroMeas, ...
        'accTrue',      accTrue, ...
        'wTrue',        wTrue, ...
        'pressureTrue', pressureTrue, ...
        'hasTruthAcc',  hasTruthAcc, ...
        'hasTruthGyro', hasTruthGyro, ...
        'hasTruthBaro', hasTruthBaro);
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
    % method defaults to 'zoh' (zero-order hold): sensor measurements
    % are sample-and-hold, so the value between updates is whatever was
    % last measured, not a linear ramp to the next sample. Truth/state
    % signals from the integrator should pass 'linear' instead.
    if nargin < 3
        method = 'zoh';
    end
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
