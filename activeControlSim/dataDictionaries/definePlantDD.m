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
P.icParams.velBdy_mps  = [300, 10, 0];   % [m/s]
P.icParams.eul_rad     = [0, pi/2, 0];   % [rad]
P.icParams.rateBdy_rps = [0, 0, 0];      % [rad/s]
P.icParams.posNed_m    = [0, 0, 0];      % [m]

%% Enviornment
P.envParams.gravityNed_mps2 = [0, 0, 9.81];   % [m/s^2]

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


end
