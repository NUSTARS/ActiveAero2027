function P = definePlantDD()
%DEFINEPLANTDD  Assemble the plant model's parameters into one
%   struct, grouped by field (vehicleParams, icParams, envParams,
%   aeroParams). No Simulink calls here -- just data.
%

%% Vehicle Params
P.vehicleParams.mass_kg      = 18;                        % [kg]
P.vehicleParams.area_m2      = 0.018;                      % [m^2]
P.vehicleParams.inertia_kgm2 = diag([8.41, 8.41, 0.053]); % [kg*m^2]
P.vehicleParams.momentArm_m  = [0.384, 0, 0];              % [m]

%% ICs
P.icParams.velBdy_mps  = [150, 10, 0];   % [m/s]
P.icParams.eul_rad     = [0, pi/2, 0];   % [rad]
P.icParams.rateBdy_rps = [1, 0, 0];      % [rad/s]
P.icParams.posNed_m    = [0, 0, 0];      % [m]

%% Enviornment
P.envParams.gravityNed_mps2 = [0, 0, 9.81];   % [m/s^2]

%% Aero Lookup Tables
load('aeroTables.mat', 'aeroTables')
P.aeroParams.machBreakpoints_na = aeroTables.machPoints;
P.aeroParams.aoaBreakpoints_deg = aeroTables.aoaPoints;
P.aeroParams.controlBreakpoints_deg = aeroTables.controlPoints;
P.aeroParams.CpBase_in = aeroTables.CpBase;
P.aeroParams.CaBase_na = aeroTables.CaBase;
P.aeroParams.CnBase_na = aeroTables.CnBase;
P.aeroParams.CnFin_na = aeroTables.CnFinControl;
P.aeroParams.CaFin_na = aeroTables.CaFinControl;


%% Fin Moments
% Convention for Fins 1-4: +Y, +Z, -Y, -Z
finMomentArm_m = [-0.5; 0.1; 0]; % should be in +Y

% Calculate moment arms for each individual fun (going CCW)
rot90Matrix = [1 0 0; 0 0 -1; 0 1 0];

P.aeroParams.finMomentArm1_m = finMomentArm_m;
P.aeroParams.finMomentArm2_m = rot90Matrix*P.aeroParams.finMomentArm1_m;
P.aeroParams.finMomentArm3_m = rot90Matrix*P.aeroParams.finMomentArm2_m;
P.aeroParams.finMomentArm4_m = rot90Matrix*P.aeroParams.finMomentArm3_m;



end
