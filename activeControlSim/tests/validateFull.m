%% Monte Carlo validation of accelerometer noise model

model = 'sensorPlantValidation';  % Your standalone model name
nRuns = 30;
simDuration = 600;

% Adjust these to the actual block names/paths
biasNoiseBlock = [model '/w(t)'];
whiteNoiseBlock = [model '/w2(t)'];

%% Initialize sensor parameters
S = defineSensorDD();
sensorParams = S.sensorParams;

load_system(model);

%% Load experimental measurements
data = readtable('activeControlSim/scripts/flight.csv');

tReal = double(data{:,1}) * 1e-6;
valid = tReal >= 0.3;

tReal = tReal(valid);
accReal = data{valid,9:11};

% Remove stationary bias and gravity
accReal = accReal - mean(accReal,1);

fsReal = 1/median(diff(tReal));

%% Welch configuration
windowDuration = 128;  % seconds

nReal = round(windowDuration*fsReal);
overlapReal = floor(nReal/2);
nfftReal = 2^nextpow2(nReal);

[psdReal, fReal] = pwelch( ...
    accReal, hann(nReal), overlapReal, ...
    nfftReal, fsReal, 'onesided');

% Use the experimental frequency grid for all simulations
fGrid = fReal;
nFreq = numel(fGrid);

% Frequency x axis x realization
allPSD = NaN(nFreq,3,nRuns);

%% Monte Carlo simulations
for r = 1:nRuns

    fprintf('Running simulation %d/%d...\n',r,nRuns);

    % Three independent seeds for each noise source
    biasSeeds  = [1000 2000 3000] + r;
    whiteSeeds = [4000 5000 6000] + r;

    % Configure this run without modifying the saved model
    in = Simulink.SimulationInput(model);

    in = in.setVariable('sensorParams',sensorParams);

    in = in.setModelParameter( ...
        'StopTime',num2str(simDuration));

    in = in.setBlockParameter( ...
        biasNoiseBlock, 'Seed',mat2str(biasSeeds));

    in = in.setBlockParameter( ...
        whiteNoiseBlock, 'Seed',mat2str(whiteSeeds));

    % Run simulation
    result = sim(in);

    % Extract logged signal
    ts = result.get('simAccNoise');

    tSim = ts.Time;
    accSim = squeeze(ts.Data);
    accSim = accSim - mean(accSim,1);

    fsSim = 1/median(diff(tSim));

    nSim = round(windowDuration*fsSim);
    overlapSim = floor(nSim/2);
    nfftSim = 2^nextpow2(nSim);

    [P, fSim] = pwelch( ...
        accSim, hann(nSim), overlapSim, ...
        nfftSim, fsSim, 'onesided');

    % Interpolate onto common frequency grid
    for axis = 1:3
        allPSD(:,axis,r) = interp1( ...
            fSim, P(:,axis), fGrid, ...
            'linear', NaN);
    end
end

%% Monte Carlo statistics
meanPSD = mean(allPSD,3,'omitnan');

lowPSD = NaN(nFreq,3);
highPSD = NaN(nFreq,3);

for axis = 1:3
    samples = squeeze(allPSD(:,axis,:));

    lowPSD(:,axis) = prctile(samples,10,2);
    highPSD(:,axis) = prctile(samples,90,2);
end

%% Original fitted PSD model
K = [7.0144e-9, 6.6878e-9, 2.6823e-9];
C = [3.4956e-6, 2.2448e-6, 1.6336e-6];


%% Publication-style Monte Carlo PSD comparison

% Color palette
navy   = [0.09 0.15 0.33];
teal   = [0.03 0.57 0.70];
cyan   = [0.65 0.89 0.92];
orange = [0.85 0.40 0.05];
gray   = [0.88 0.89 0.91];

fig = figure( ...
    'Color','w', ...
    'Position',[100 100 1100 850]);

tl = tiledlayout(3,1, ...
    'TileSpacing','compact', ...
    'Padding','compact');

labels = {'Accelerometer X', ...
          'Accelerometer Y', ...
          'Accelerometer Z'};

for axis = 1:3

    ax = nexttile;
    hold(ax,'on');

    % Consistent white background and dark text
    ax.Color = [1 1 1];
    ax.XColor = [0.25 0.28 0.32];
    ax.YColor = [0.25 0.28 0.32];
    ax.GridColor = gray;
    ax.MinorGridColor = gray;
    ax.GridAlpha = 0.6;
    ax.MinorGridAlpha = 0.25;
    ax.FontSize = 11;
    ax.LineWidth = 0.8;

    % Frequency range
    validF = fGrid >= 0.02 & fGrid <= 2;
    f = fGrid(validF);

    lower = lowPSD(validF,axis);
    upper = highPSD(validF,axis);

    % Simulated 10th-90th percentile band
    hBand = fill( ...
        [f; flipud(f)], ...
        [lower; flipud(upper)], ...
        cyan, ...
        'FaceAlpha',0.45, ...
        'EdgeColor','none');

    % Simulated mean
    hMean = loglog( ...
        f,meanPSD(validF,axis), ...
        'Color',teal, ...
        'LineWidth',2.2);

    % Fitted model
    fitted = K(axis)./f.^2 + C(axis);

    hFit = loglog( ...
        f,fitted,'--', ...
        'Color',orange, ...
        'LineWidth',1.6);

    % Experimental PSD on top
    hReal = loglog( ...
        f,psdReal(validF,axis), ...
        'Color',navy, ...
        'LineWidth',1.7);

    set(ax,'XScale','log','YScale','log');

    xlim([0.02 2]);

    grid on;
    box off;

    title(labels{axis}, ...
        'FontSize',12, ...
        'FontWeight','bold', ...
        'Color',navy);

    ylabel('PSD ((m/s^2)^2/Hz)');

    if axis == 3
        xlabel('Frequency (Hz)');
    end
end

sgtitle(tl, ...
    'Accelerometer Noise — Experimental vs Monte Carlo', ...
    'FontSize',16, ...
    'FontWeight','bold', ...
    'Color',navy);

lgd = legend([hReal hMean hBand hFit], ...
    {'Measured', ...
     'Simulated mean', ...
     'Simulated 10–90%', ...
     'Original fit'}, ...
    'Orientation','horizontal');

lgd.Layout.Tile = 'south';
lgd.Box = 'off';
lgd.FontSize = 11;
lgd.TextColor = navy;
lgd.Color = 'none';
