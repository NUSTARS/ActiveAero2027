function S = defineSensorDD()

% setup
rng(42);
biasOn = false;

% Lever Arm (relative to CG
S.sensorParams.imuPosBdy_m = [0, 0, 0];

%% Accelerometer %%

% Sampling Rate
accRate_Hz = 100;

% scale factor and coupling matrix measuring the components of the body
% specific force along other axes
accScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0];

% noise density for random white noise (not gauss markov)
accnoiseDensity_microgpsqHz = [75, 75, 75];

% scaling factor for gauss markov
S.sensorParams.accMarkovGain_na = 0.99995;

% uncertainty for white noise in dynamic bias
accSigmaBias_mg = [0.2, 0.2, 0.2];

% should probably be set to a 0 mean random value with some std. Not
% critical and can do later
accSigmaBiasTurnOn_mg = [2.0, 2.0, 2.0];

%% Processing (nothing to change here)

% Bias
accSigmaBiasTurnOn_mps2 = accSigmaBiasTurnOn_mg * 0.00981;
S.sensorParams.accTurnOnBias_mps2 = accSigmaBiasTurnOn_mps2 * randn(1, 1);

S.sensorParams.accSigmaBias_mps2 = accSigmaBias_mg * 0.00981; % [m/s^2]
% PSDs
accnoiseDensity_mps2psqHz = accnoiseDensity_microgpsqHz * 9.81e-6; % [m/s^2 / sqrt(Hz)]
S.sensorParams.accPSDGM = 2 * S.sensorParams.accSigmaBias_mps2 .* S.sensorParams.accSigmaBias_mps2 / (-1/(log(S.sensorParams.accMarkovGain_na)*accRate_Hz));
S.sensorParams.accPSDWhite = accnoiseDensity_mps2psqHz .* accnoiseDensity_mps2psqHz;

% Misc
S.sensorParams.accScaleCoupling_na = eye(3) + accScaleCoupling_na;
S.sensorParams.accSampleTime_s = 1 / accRate_Hz;

%% Gyroscope %%

% Sampling Rate
gyroRate_Hz = 100; % [Hz]

% uncertainty for white noise in dynamic bias aka in-run bias instability
gyroSigmaBias_degphr = [100, 100, 100];

% scale factor and coupling matrix measuring the components of the body
gyroScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0];

% scaling factor for gauss markov
S.sensorParams.gyroMarkovGain_na = 0.99995;

% Turn on Bias
S.sensorParams.gyroSigmaBiasTurnOn_rps = [0.009, 0.009, 0.009];

% g sensitivity of the gyroscope
gyroG = [0.05 0 0; 0 0.05 0; 0 0 0.05]; % [deg / s / g]

% turn on bias
gyroSigmaBiasTurnOn_rps = [0.009, 0.009, 0.009];


%% Processing (nothing to change here)

% Bias
S.sensorParams.gyroSigmaBias_rps = gyroSigmaBias_degphr * 4.848e-6; % [rad / s]
S.sensorParams.gyroTurnOnBias_rps = gyroSigmaBiasTurnOn_rps * randn(1, 1);

% PSDs
gyroNoiseDensity_degpspsqHz = [0.00035, 0.00035, 0.00035]; % [deg / s / sqrt(Hz)]
gryoNoiseDensity_radpspsqHz = gyroNoiseDensity_degpspsqHz * 0.01745; % [rad / s / sqrt(Hz)]
S.sensorParams.gyroPSDWhite = gryoNoiseDensity_radpspsqHz .* gryoNoiseDensity_radpspsqHz;
S.sensorParams.gyroPSDGM = 2 * S.sensorParams.gyroSigmaBias_rps .* S.sensorParams.gyroSigmaBias_rps / (-1/(log(S.sensorParams.gyroMarkovGain_na)*gyroRate_Hz));

% Misc
S.sensorParams.gyroG = gyroG * 0.01745 / 9.8065; % [rad / s / (m/s)]
S.sensorParams.gyroScaleCoupling_na = eye(3) + gyroScaleCoupling_na;
S.sensorParams.gyroSampleTime_s = 1 / gyroRate_Hz;

%% Magnetometer %%

% Soft iron scale factor and coupling matrix
magSI = [0.08 0.05 -0.03; 0.04 -0.07 0.02; -0.03 0.02 0.05];

% hard iron bias in body
S.sensorParams.magBiasHIBdy_nT = 1000 * [1.2, -0.8, 0.5];

% Noise
magNoiseDensity_nTpsqHz = [14, 14, 14];

% Sampling rate
magRate_Hz = 100; % [Hz]

%% Processing (nothing to change here)
S.sensorParams.magSampleTime_s = 1 / magRate_Hz; % [s]
S.sensorParams.magPSDWhite = magNoiseDensity_nTpsqHz .* magNoiseDensity_nTpsqHz;


%% Barometer %%
baroNoiseDensity_PapsqHz = 0.02;
S.sensorParams.baroBiasTurnOn_Pa = 40;
baroBiasSigma_Pa = 6; % [Pa]

S.sensorParams.baroMarkovGain_na = 0.99998;

% Sampling rate
baroRate_Hz = 100;

% flight regime depended pressure offset derived via CFD ie C(M) * q. Not adding yet

%% Processing (nothing to change here)
S.sensorParams.baroSampleTime_s = 1 / baroRate_Hz;

S.sensorParams.magSI = eye(3) + magSI;

S.sensorParams.baroPSDWhite = baroNoiseDensity_PapsqHz^2;
S.sensorParams.baroPSDGM = 2 * baroBiasSigma_Pa^2 / (-1/(log(S.sensorParams.baroMarkovGain_na)*baroRate_Hz));


%% End Processing

if biasOn == false
    S.sensorParams.accPSDWhite = zeros(3,1);
    S.sensorParams.accPSDGM = zeros(3,1);
    S.sensorParams.accTurnOnBias_mps2 = zeros(3,1);
    S.sensorParams.gyroPSDWhite = zeros(3,1);
    S.sensorParams.gyroPSDGM = zeros(3,1);
    S.sensorParams.gyroTurnOnBias_rps = zeros(3,1);
    S.sensorParams.gyroG = zeros(3,3);
end

end
