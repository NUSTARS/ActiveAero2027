function P = definePlantDD()
%DEFINEPLANTDD  Assemble the plant model's parameters into one
%   struct, grouped by field (vehicleParams, icParams, envParams,
%   aeroParams). No Simulink calls here -- just data.
%

%% Constants
in2m = 1/39.37;

%% Vehicle Params
P.vehicleParams.mass_kg      = 18;                        % [kg]
P.vehicleParams.area_m2      = 0.018;                      % [m^2]
P.vehicleParams.cg_m = 71.33*in2m;                          % [m]
P.vehicleParams.inertia_kgm2 = diag([0.053, 8.41, 8.41]); % [kg*m^2]

%% ICs
P.icParams.velBdy_mps  = [300, 0, 0];   % [m/s]
P.icParams.eul_rad     = [0, pi/2, 0];   % [rad]
P.icParams.rateBdy_rps = [0, 0, 0];      % [rad/s]
P.icParams.posNed_m    = [0, 0, 0];      % [m]

%% Enviornment
P.envParams.gravityNed_mps2 = [0, 0, 9.81];   % [m/s^2]

% Wind Simulations
P.windParams.type       = 0;          % 0 = constant, 1 = stochastic
P.windParams.constantNed_mps = [5; 0; 0]; % [m/s]


%% Aero Lookup Tables
load('aeroTables.mat', 'aeroTables')
P.aeroParams.machBreakpoints_na = aeroTables.machPoints;
P.aeroParams.aoaBreakpoints_deg = aeroTables.aoaPoints;
P.aeroParams.controlBreakpoints_deg = aeroTables.controlPoints;
P.aeroParams.CpBase_m = in2m.*aeroTables.CpBase;
P.aeroParams.CaBase_na = aeroTables.CaBase;
P.aeroParams.CnBase_na = aeroTables.CnBase;
P.aeroParams.CnFin_na = aeroTables.CnFinControl;
P.aeroParams.CaFin_na = aeroTables.CaFinControl;


%% Fin Moments
% Convention for Fins 1-4: +Y, +Z, -Y, -Z
finCP_m = in2m*[105; 5; 0]; % should be in +Y

% Calculate moment arms for each individual fun (going CCW)
rot90Matrix = [1 0 0; 0 0 -1; 0 1 0];

P.aeroParams.finCP1_m = finCP_m;
P.aeroParams.finCP2_m = rot90Matrix*P.aeroParams.finCP1_m;
P.aeroParams.finCP3_m = rot90Matrix*P.aeroParams.finCP2_m;
P.aeroParams.finCP4_m = rot90Matrix*P.aeroParams.finCP3_m;

P.aeroParams.finAngles1_rad = [0, 0, 0];
P.aeroParams.finAngles2_rad = [pi/2, 0, 0];
P.aeroParams.finAngles3_rad = [pi, 0, 0];
P.aeroParams.finAngles4_rad = [3*pi/2, 0, 0];


% sensor params 

% fill in later for lever arm:
% Also, assuming body coords centered on CG (or is it CP?)
P.sensorParams.imuPosBdy_m = [0, 0, 0]; % [m]
% scale factor and coupling matrix measuring the components of the body
% specific force along other axes. Used to correct that. Setting to perfect
% scale and no coupling for now
accScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0]; % [dimensionless][[0, 0, 0], [0, 0, 0], [0, 0, 0]]
P.sensorParams.accScaleCoupling_na = eye(3) + accScaleCoupling_na;
% noise density for random white noise (not gauss markov)
accnoiseDensity_microgpsqHz = [75, 75, 75]; % [microg/sqrt(Hz)]
accnoiseDensity_mps2psqHz = accnoiseDensity_microgpsqHz * 9.81e-6; % [m/s^2 / sqrt(Hz)]
P.sensorParams.accPSDWhite = accnoiseDensity_mps2psqHz .* accnoiseDensity_mps2psqHz;
% time constant for gauss markov. longer -> better stability
P.sensorParams.accTau_s = 200; % [s]
% uncertainty for white noise in dynamic bias
accSigmaBias_mg = [0.2, 0.2, 0.2]; % [millig]
P.sensorParams.accSigmaBias_mps2 = accSigmaBias_mg * 0.00981; % [m/s^2]
% power spectral density for the gauss markov noise
P.sensorParams.accPSDGM = 2 * P.sensorParams.accSigmaBias_mps2 .* ...
    P.sensorParams.accSigmaBias_mps2 / P.sensorParams.accTau_s;
% should probably be set to a 0 mean random value with some std. Not
% critical and can do later
accSigmaBiasTurnOn_mg = [0.5, 0.5, 0.5]; % [millig]
P.sensorParams.accSigmaBiasTurnOn_mps2 = accSigmaBiasTurnOn_mg * 0.00981; % [m/s^2]
accRate_Hz = 100; % [Hz]
P.sensorParams.accSampleTime_s = 1 / accRate_Hz; % [s]


% scale factor and coupling matrix measuring the components of the body
gyroScaleCoupling_na = [0 0 0; 0 0 0; 0 0 0]; % [dimensionless]
P.sensorParams.gyroScaleCoupling_na = eye(3) + gyroScaleCoupling_na;
% noise density for random white noise (not gauss markov)
gyroNoiseDensity_degpspsqHz = [0.0035, 0.0035, 0.0035]; % [deg / s / sqrt(Hz)]
gryoNoiseDensity_radpspsqHz = gyroNoiseDensity_degpspsqHz * 0.01745; % [rad / s / sqrt(Hz)]
P.sensorParams.gyroPSDWhite = gryoNoiseDensity_radpspsqHz .* gryoNoiseDensity_radpspsqHz;
% time constant for gauss markov
P.sensorParams.gyroTau_s = 200; % [s]
% uncertainty for white noise in dynamic bias aka in-run bias instability
gyroSigmaBias_degphr = [5, 5, 5]; % [deg / hr]
P.sensorParams.gyroSigmaBias_rps = gyroSigmaBias_degphr * 4.848e-6; % [rad / s]
% power spectral density for the gauss markov noise
P.sensorParams.gyroPSDGM = 2 * P.sensorParams.gyroSigmaBias_rps .* ...
    P.sensorParams.gyroSigmaBias_rps / P.sensorParams.gyroTau_s;
% should probably be set to a 0 mean random value with some std. Not
% critical and can do later
P.sensorParams.gyroSigmaBiasTurnOn_rps = [0.0005, 0.0005, 0.0005]; 
gyroRate_Hz = 100; % [Hz]
P.sensorParams.gyroSampleTime_s = 1 / gyroRate_Hz; % [s]
% g sensitivity of the gyroscope
gyroG = [[0.1, 0, 0], [0, 0.1, 0], [0, 0, 0.1]]; % [deg / s / g
P.sensorParams.gyroG = gyroG * 0.01745 * 9.8065; % [rad / s / (m/s)]
% not consider g^2 sensitivity at least for now



end
