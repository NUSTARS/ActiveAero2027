function P = definePlantDD()
%DEFINEPLANTDD  Assemble the plant model's parameters into one
%   struct, grouped by field (vehicleParams, icParams, envParams,
%   aeroParams). No Simulink calls here -- just data.
%
%   mass_kg/area_m2 are PLACEHOLDERS -- edit to real values.

P.vehicleParams.mass_kg      = 18;                        % [kg]
P.vehicleParams.area_m2      = 0.018;                      % [m^2]
P.vehicleParams.inertia_kgm2 = diag([8.41, 8.41, 0.053]); % [kg*m^2]
P.vehicleParams.momentArm_m  = [0.384, 0, 0];              % [m]

P.icParams.velBdy_mps  = [150, 10, 0];   % [m/s]
P.icParams.eul_rad     = [0, pi/2, 0];   % [rad]
P.icParams.rateBdy_rps = [1, 0, 0];      % [rad/s]
P.icParams.posNed_m    = [0, 0, 0];      % [m]

P.envParams.gravityNed_mps2 = [0, 0, 9.81];   % [m/s^2]

% Wind Simulations
P.windParams.type       = 0;          % 0 = constant, 1 = stochastic
P.windParams.constantNed_mps = [5; 0; 0]; % [m/s]

P.aeroParams.cnBreakpoints_na    = -1:0.1:1;
P.aeroParams.cnTable_na          = sin(-1:0.1:1)*10;
P.aeroParams.cdBreakpoints_na    = -1:0.1:1;
P.aeroParams.cdTable_na    = ones(size(-1:0.1:1))*0.5;

end
