function S = defineSensorDD()
%DEFINESENSORDD  Assemble the sensor model's parameters into one
%   struct, grouped by field. No Simulink calls here -- just data.
%

% sensor params
% fill in later for lever arm:
% Also, assuming body coords centered on CG (or is it CP?)
S.sensorParams.imuPosBdy_m = [0, 0, 0]; % [m]

%%% Accelerometer %%%
% scale factor and coupling matrix measuring the components of the body
% specific force along other axes. Used to correct that. Setting to perfect
% scale and no coupling for now
accScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0]; % [dimensionless][[0, 0, 0], [0, 0, 0], [0, 0, 0]]
S.sensorParams.accScaleCoupling_na = eye(3) + accScaleCoupling_na;
% noise density for random white noise (not gauss markov)
accnoiseDensity_microgpsqHz = [75, 75, 75]; % [microg/sqrt(Hz)]
accnoiseDensity_mps2psqHz = accnoiseDensity_microgpsqHz * 9.81e-6; % [m/s^2 / sqrt(Hz)]
S.sensorParams.accPSDWhite = accnoiseDensity_mps2psqHz .* accnoiseDensity_mps2psqHz;
% time constant for gauss markov. longer -> better stability
S.sensorParams.accTau_s = 200; % [s]
% uncertainty for white noise in dynamic bias
accSigmaBias_mg = [0.2, 0.2, 0.2]; % [millig]
S.sensorParams.accSigmaBias_mps2 = accSigmaBias_mg * 0.00981; % [m/s^2]
% power spectral density for the gauss markov noise
S.sensorParams.accPSDGM = 2 * S.sensorParams.accSigmaBias_mps2 .* ...
    S.sensorParams.accSigmaBias_mps2 / S.sensorParams.accTau_s;
% should probably be set to a 0 mean random value with some std. Not
% critical and can do later
accSigmaBiasTurnOn_mg = [0.5, 0.5, 0.5]; % [millig]
S.sensorParams.accSigmaBiasTurnOn_mps2 = accSigmaBiasTurnOn_mg * 0.00981; % [m/s^2]
accRate_Hz = 100; % [Hz]
S.sensorParams.accSampleTime_s = 1 / accRate_Hz; % [s]

%%% Gyroscope %%%
% scale factor and coupling matrix measuring the components of the body
gyroScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0]; % [dimensionless]
S.sensorParams.gyroScaleCoupling_na = eye(3) + gyroScaleCoupling_na;
% noise density for random white noise (not gauss markov)
gyroNoiseDensity_degpspsqHz = [0.0035, 0.0035, 0.0035]; % [deg / s / sqrt(Hz)]
gryoNoiseDensity_radpspsqHz = gyroNoiseDensity_degpspsqHz * 0.01745; % [rad / s / sqrt(Hz)]
S.sensorParams.gyroPSDWhite = gryoNoiseDensity_radpspsqHz .* gryoNoiseDensity_radpspsqHz;
% time constant for gauss markov
S.sensorParams.gyroTau_s = 200; % [s]
% uncertainty for white noise in dynamic bias aka in-run bias instability
gyroSigmaBias_degphr = [5, 5, 5]; % [deg / hr]
S.sensorParams.gyroSigmaBias_rps = gyroSigmaBias_degphr * 4.848e-6; % [rad / s]
% power spectral density for the gauss markov noise
S.sensorParams.gyroPSDGM = 2 * S.sensorParams.gyroSigmaBias_rps .* ...
    S.sensorParams.gyroSigmaBias_rps / S.sensorParams.gyroTau_s;
% should probably be set to a 0 mean random value with some std. Not
% critical and can do later
S.sensorParams.gyroSigmaBiasTurnOn_rps = [0.0005, 0.0005, 0.0005];
gyroRate_Hz = 100; % [Hz]
S.sensorParams.gyroSampleTime_s = 1 / gyroRate_Hz; % [s]
% g sensitivity of the gyroscope
gyroG = [0.1 0 0; 0 0.1 0; 0 0 0.1]; % [deg / s / g
S.sensorParams.gyroG = gyroG * 0.01745 * 9.8065; % [rad / s / (m/s)]
% not consider g^2 sensitivity at least for now

%%% Magnetometer %%%
% values to be estimated via calibration method called swinging. Not a
% perfect model rn but can refine later on especially when working with
% actual sensors. e.g. some conflicting sources on biases and whether the
% SI matrix should be inverted for meas model or when compensating
% soft iron scale factor and coupling matrix
magSI = [0.08 0.05 -0.03; 0.04 -0.07 0.02; -0.03 0.02 0.05]; % [dimensionless]
S.sensorParams.magSI = eye(3) + magSI;
% hard iron bias in body. Example. Is this constant? Worth knowing if it
% might just significantly during flight
S.sensorParams.magBiasHIBdy_nT = 1000 * [1.2, -0.8, 0.5]; % [nT]
magNoiseDensity_nTpsqHz = [14, 14, 14]; % [nT / sqrt(Hz)]
S.sensorParams.magPSDWhite = magNoiseDensity_nTpsqHz .* magNoiseDensity_nTpsqHz;
magRate_Hz = 100; % [Hz]
S.sensorParams.magSampleTime_s = 1 / magRate_Hz; % [s]

%%% Barometer %%%
baroNoiseDensity_PapsqHz = 0.02; % [Pa /sqrt(Hz)]
S.sensorParams.baroPSDWhite = baroNoiseDensity_PapsqHz^2;
S.sensorParams.baroBiasTurnOn_Pa = 40; % [Pa]
baroBiasSigma_Pa = 6; % [Pa]
S.sensorParams.baroTau_s = 500; % [s]
S.sensorParams.baroPSDGM = 2 * baroBiasSigma_Pa^2 / S.sensorParams.baroTau_s;
baroRate_Hz = 100; % [Hz]
S.sensorParams.baroSampleTime_s = 1 / baroRate_Hz; % [s]
% flight regime depended pressure offset derived via CFD ie C(M) * q. Not adding yet

end
