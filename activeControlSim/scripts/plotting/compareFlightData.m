function stats = compareFlightData(varargin)
%COMPAREFLIGHTDATA  Overlay a simulated run against a flight-computer log
%   and report per-channel error statistics.
%
%   compareFlightData()                    results/simResults.mat vs
%                                           data/FL000006.csv
%   compareFlightData(matFile)             matFile vs data/FL000006.csv
%   compareFlightData(matFile, csvFile)    matFile vs csvFile
%   compareFlightData(..., Name, Value)    options below
%   stats = compareFlightData(...)         also return the stats table
%
%   matFile must contain an `out` variable, e.g. as saved by
%   scripts/runModel.m. csvFile is a flight-computer log with columns
%     timestamp_us                                       [us]
%     {bmi,lsm}_accel_{x,y,z}                            [m/s^2]
%     {bmi,lsm}_gyro_{x,y,z}                             (see GyroUnits)
%     bmp581_pressure, bmp585_pressure                   [Pa or hPa]
%     altitude, gnss_fix_type                            [m], enum
%   A column that is all zeros is treated as "sensor not logged" and
%   skipped. GNSS altitude is NaN wherever gnss_fix_type == 0.
%
%   OPTIONS
%     'Imu'                  'lsm' | 'bmi' | 'auto' (default 'auto':
%                            whichever IMU actually has data)
%     'GyroUnits'            'dps' | 'rps' (default 'dps')
%     'LaunchThreshold_mps2' specific-force magnitude that marks launch
%                            in both logs (default 20)
%     'TimeOffset_s'         flight time [s since log start] to align
%                            with sim t = 0. Overrides launch detection.
%
%   ALIGNMENT
%     Both time axes are shifted so launch is t = 0, where launch is the
%     first sample whose |specific force| stays above
%     LaunchThreshold_mps2 for 0.1 s. If no launch is found in the flight
%     log (e.g. a pad/bench log) the flight log is aligned start-to-start
%     with the sim and a warning is issued -- pass TimeOffset_s to align
%     it manually.
%
%   Body axes are assumed to match between the sim and the flight IMU
%   (X = nose; both read ~+9.8 m/s^2 on X at rest).
%
%   OUTPUT
%     Figure 104: IMU comparison (accel X/Y/Z, gyro P/Q/R)
%     Figure 105: Barometer / altitude comparison (if logged)
%     stats: table of RMSE, mean error (flight - sim), and peak values
%            per channel, over the time window both logs cover.


% ------------------------------------------------------- parse arguments
repoRoot = fileparts(fileparts(mfilename('fullpath')));
matFile = fullfile(repoRoot, 'results', 'simResults.mat');
csvFile = fullfile(repoRoot, 'data', 'FL000006.csv');

i = 1;
while i <= numel(varargin) && (ischar(varargin{i}) || isstring(varargin{i})) ...
        && (endsWith(varargin{i}, '.mat', 'IgnoreCase', true) ...
            || endsWith(varargin{i}, '.csv', 'IgnoreCase', true))
    a = char(varargin{i});
    if endsWith(a, '.mat', 'IgnoreCase', true)
        matFile = a;
    else
        csvFile = a;
    end
    i = i + 1;
end

p = inputParser;
p.addParameter('Imu', 'auto', @(s) any(strcmpi(s, {'auto','lsm','bmi'})));
p.addParameter('GyroUnits', 'dps', @(s) any(strcmpi(s, {'dps','rps'})));
p.addParameter('LaunchThreshold_mps2', 20, @(x) isscalar(x) && x > 0);
p.addParameter('TimeOffset_s', [], @(x) isempty(x) || isscalar(x));
p.parse(varargin{i:end});
opt = p.Results;

% flightMode etc. are enum classes on the repo path -- without them
% load() warns and drops those signals.
if isempty(which('flightMode'))
    run(fullfile(repoRoot, 'setupPaths.m'));
end

sim = loadSim_local(matFile);
fl  = loadFlight_local(csvFile, opt);

% --------------------------------------------------------------- align
simT0 = detectLaunch_local(sim.t, sim.f, opt.LaunchThreshold_mps2);
if isnan(simT0)
    simT0 = 0;
end

if ~isempty(opt.TimeOffset_s)
    flT0 = opt.TimeOffset_s;
else
    flT0 = detectLaunch_local(fl.t, fl.f, opt.LaunchThreshold_mps2);
    if isnan(flT0)
        warning('compareFlightData:noLaunch', ...
            ['No launch found in %s (max |a| = %.1f m/s^2 < %g threshold). ', ...
             'Aligning start-to-start; pass ''TimeOffset_s'' to align manually.'], ...
            fl.label, max(vecnorm(fl.f, 2, 2)), opt.LaunchThreshold_mps2);
        flT0 = fl.t(1) - (sim.t(1) - simT0);
    end
end
sim.t = sim.t - simT0;
fl.t  = fl.t  - flT0;
fprintf('Sim launch at %.3f s; flight launch at %.3f s (log time).\n', simT0, flT0);

% ============================================================ IMU WINDOW
simColor = [0 0.4470 0.7410];
flColor  = [0.8500 0.3250 0.0980];

figure(104); clf(104); set(104, 'Name', 'Sim vs Flight: IMU', 'Color', 'w');
accLbl  = {'X','Y','Z'};
rateLbl = {'P','Q','R'};
for j = 1:3
    ax = subplot(3, 2, 2*j - 1); hold(ax, 'on'); grid(ax, 'on');
    plot(ax, sim.t, sim.f(:,j), '-', 'Color', simColor, 'DisplayName', sim.label);
    plot(ax, fl.t,  fl.f(:,j),  '-', 'Color', flColor,  'DisplayName', fl.label);
    ylabel(ax, sprintf('f_%s [m/s^2]', accLbl{j}));
    if j == 1, title(ax, 'Accelerometer'); legend(ax, 'Location', 'best'); end
    if j == 3, xlabel(ax, 'Time from launch [s]'); end

    ax = subplot(3, 2, 2*j); hold(ax, 'on'); grid(ax, 'on');
    plot(ax, sim.t, sim.w(:,j), '-', 'Color', simColor, 'DisplayName', sim.label);
    plot(ax, fl.t,  fl.w(:,j),  '-', 'Color', flColor,  'DisplayName', fl.label);
    ylabel(ax, sprintf('%s [rad/s]', rateLbl{j}));
    if j == 1, title(ax, 'Gyroscope'); end
    if j == 3, xlabel(ax, 'Time from launch [s]'); end
end
linkaxes(findobj(104, 'Type', 'axes'), 'x');
xlim(findobj(104, 'Type', 'axes'), [sim.t(1) sim.t(end)]);

% ===================================================== BARO/ALT WINDOW
hasFlBaro = any(~isnan(fl.baro));
hasFlAlt  = any(~isnan(fl.alt));
if hasFlBaro || hasFlAlt
    figure(105); clf(105); set(105, 'Name', 'Sim vs Flight: Baro/Altitude', 'Color', 'w');

    ax = subplot(2, 1, 1); hold(ax, 'on'); grid(ax, 'on');
    plot(ax, sim.t, sim.baro, '-', 'Color', simColor, 'DisplayName', sim.label);
    if hasFlBaro
        plot(ax, fl.t, fl.baro, '-', 'Color', flColor, 'DisplayName', fl.label);
    end
    ylabel(ax, 'Pressure [Pa]'); title(ax, 'Barometer'); legend(ax, 'Location', 'best');

    ax = subplot(2, 1, 2); hold(ax, 'on'); grid(ax, 'on');
    plot(ax, sim.t, sim.altTrue, '-', 'Color', simColor, 'DisplayName', [sim.label ' (truth AGL)']);
    if hasFlAlt
        plot(ax, fl.t, fl.alt, '.', 'Color', flColor, 'DisplayName', [fl.label ' (GNSS AGL)']);
    end
    ylabel(ax, 'Altitude [m]'); xlabel(ax, 'Time from launch [s]');
    title(ax, 'Altitude'); legend(ax, 'Location', 'best');
    linkaxes(findobj(105, 'Type', 'axes'), 'x');
end

% ================================================================ STATS
% Compare on the sim's time grid, inside the window both logs cover.
inWin = sim.t >= fl.t(1) & sim.t <= fl.t(end);
tc = sim.t(inWin);

names = {'fX_mps2','fY_mps2','fZ_mps2','wP_rps','wQ_rps','wR_rps','baro_Pa','alt_m'};
simCols = [sim.f, sim.w, sim.baro, sim.altTrue];
flCols  = [fl.f,  fl.w,  fl.baro,  fl.alt];

nCh = numel(names);
rmse = nan(nCh,1); bias = nan(nCh,1); simPeak = nan(nCh,1); flPeak = nan(nCh,1); nPts = zeros(nCh,1);
for k = 1:nCh
    ok = ~isnan(flCols(:,k));
    if nnz(ok) < 2 || isempty(tc)
        continue;
    end
    flOnSim = interp1(fl.t(ok), flCols(ok,k), tc, 'linear', NaN);
    e = flOnSim - simCols(inWin,k);
    e = e(~isnan(e));
    nPts(k)    = numel(e);
    rmse(k)    = sqrt(mean(e.^2));
    bias(k)    = mean(e);
    simPeak(k) = max(abs(simCols(inWin,k)));
    flPeak(k)  = max(abs(flCols(ok & fl.t >= tc(1) & fl.t <= tc(end), k)), [], 'omitnan');
end
T = table(rmse, bias, simPeak, flPeak, nPts, ...
    'RowNames', names, ...
    'VariableNames', {'RMSE','MeanErr_flMinusSim','SimPeakAbs','FlightPeakAbs','N'});

if isempty(tc)
    warning('compareFlightData:noOverlap', 'Sim and flight time windows do not overlap.');
else
    fprintf('\nSim vs flight over t = [%.2f, %.2f] s from launch:\n', tc(1), tc(end));
end
disp(T);

if nargout > 0
    stats = T;
end

end

% ======================================================================
function s = loadSim_local(matFile)
    % Pull the sensor-bus measurements (what the flight computer would
    % have recorded) plus truth altitude out of a saved sim run.
    S = load(matFile, 'out');
    if ~isfield(S, 'out')
        error('compareFlightData:noOutInFile', ...
            '%s does not contain an ''out'' variable.', matFile);
    end
    try
        simout = S.out.simout;
    catch
        error('compareFlightData:noSimout', ...
            '%s: out.simout not found -- out must be a Simulink sim output.', matFile);
    end
    if ~isstruct(simout) || ~isfield(simout, 'sensor_bus')
        error('compareFlightData:badSimout', ...
            '%s: simout must have field sensor_bus.', matFile);
    end
    sensors = simout.sensor_bus;

    tsF = sensors.fBdyMeas_mps2;
    t = tsF.Time(:);
    N = numel(t);

    s.label = 'Sim';
    s.t     = t;
    s.f     = alignRows_local(tsF.Data, N, 3);
    s.w     = alignRows_local(resampleIfNeeded_local(sensors.wBdyMeas_rps, t, 'zoh').Data, N, 3);
    s.baro  = alignRows_local(resampleIfNeeded_local(sensors.baroMeas_Pa,  t, 'zoh').Data, N, 1);

    s.altTrue = nan(N, 1);
    if isfield(simout, 'plant_bus') && isfield(simout.plant_bus, 'eom_bus') ...
            && isfield(simout.plant_bus.eom_bus, 'posNed_m')
        pos = alignRows_local(resampleIfNeeded_local( ...
            simout.plant_bus.eom_bus.posNed_m, t, 'linear').Data, N, 3);
        s.altTrue = -(pos(:,3) - pos(1,3));
    end
end

% ======================================================================
function f = loadFlight_local(csvFile, opt)
    % Read the flight-computer CSV into the same shape/units as the sim:
    % accel [m/s^2], gyro [rad/s], pressure [Pa], GNSS altitude AGL [m].
    T = readtable(csvFile);
    [~, f.label] = fileparts(csvFile);
    f.t = (T.timestamp_us - T.timestamp_us(1)) * 1e-6;

    imu = lower(opt.Imu);
    if strcmp(imu, 'auto')
        if any([T.lsm_accel_x; T.lsm_accel_y; T.lsm_accel_z] ~= 0)
            imu = 'lsm';
        else
            imu = 'bmi';
        end
    end
    f.f = [T.([imu '_accel_x']), T.([imu '_accel_y']), T.([imu '_accel_z'])];
    f.w = [T.([imu '_gyro_x']),  T.([imu '_gyro_y']),  T.([imu '_gyro_z'])];
    if strcmpi(opt.GyroUnits, 'dps')
        f.w = deg2rad(f.w);
    end
    fprintf('Flight IMU: %s (gyro in %s)\n', upper(imu), opt.GyroUnits);

    % Barometer: first BMP with any nonzero data. Pressure < 2000 can't
    % be Pa at any altitude a rocket reaches, so treat it as hPa.
    f.baro = nan(height(T), 1);
    for name = {'bmp581_pressure', 'bmp585_pressure'}
        P = T.(name{1});
        if any(P ~= 0)
            P(P == 0) = NaN;
            if median(P, 'omitnan') < 2000
                P = P * 100;
            end
            f.baro = P;
            fprintf('Flight baro: %s\n', name{1});
            break;
        end
    end

    % GNSS altitude, AGL relative to the first fixed sample.
    alt = T.altitude;
    alt(T.gnss_fix_type == 0) = NaN;
    firstFix = find(~isnan(alt), 1);
    if ~isempty(firstFix)
        alt = alt - alt(firstFix);
    end
    f.alt = alt;
end

% ======================================================================
function t0 = detectLaunch_local(t, f, threshold)
    % First sample where |specific force| stays above threshold for at
    % least 0.1 s -- long enough to reject handling bumps, short enough
    % to catch any real motor burn. NaN if never.
    above = vecnorm(f, 2, 2) > threshold;
    t0 = NaN;
    idx = find(above);
    for k = idx(:)'
        j = find(t >= t(k) + 0.1, 1);
        if isempty(j)
            return;
        end
        if all(above(k:j))
            t0 = t(k);
            return;
        end
    end
end

% ======================================================================
function tsOut = resampleIfNeeded_local(tsIn, t, method)
    % Resample tsIn onto t only if it isn't already on that grid. 'zoh'
    % for sensor measurements (sample-and-hold), 'linear' for truth.
    if numel(tsIn.Time) == numel(t) && all(tsIn.Time(:) == t(:))
        tsOut = tsIn;
    else
        tsOut = resample(tsIn, t, method);
    end
end

% ======================================================================
function out = alignRows_local(data, N, ncols)
    % squeeze() on a logged timeseries can leave data as Nxncols OR
    % ncolsxN -- check shape explicitly rather than blind reshape.
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
