data = definePlantDD();

% Constants
grav_m_s2 = 9.81; % [m/s^2] Gravitational constant close to Earth's surface 

% Rocket Physical Parameters
mass_kg = data.vehicleParams.mass_kg; % [kg] Mass of the rocket
weight_N = mass_kg*grav_m_s2; % [N] Weight of the rocket
Iyy_kgm2 = data.vehicleParams.inertia_kgm2(2,2); % [kgm^2] Moment of inertia
Sref_m2 = data.vehicleParams.area_m2; % [m^2] Reference Area
cg_m = data.vehicleParams.cg_m; % Center of Gravity
cpData = data.aeroParams.CpBase_m;
cpBase_m = cpData(1,3); % [m] extracting x coordinate of center pressure
lengthChar_m = cpBase_m-cg_m; % [m] Reference length d, difference between center grav and pressure

% Stuff
density_kg_m3 = 1.225; % kg/m^3

% State Variables
% aoa_deg = 
% forceNormal_N = 
% moment_Nm = forceNormal_N * lengthChar_m;
% normalAccel_m_s2 = forceNormal_N*grav_m_s2*weight_N;
dynamicPressure_Pa = 50000; % [Pa]
windVelocity_m_s = sqrt(2*dynamicPressure_Pa/density_kg_m3); % [m/s]
% control_deg =

% Calculating Normal Derivatives
machPoints = data.aeroParams.machBreakpoints_na; % [unitless] velocity breakpoints
aoaPoints_deg = data.aeroParams.aoaBreakpoints_deg; % [degree] alpha breakpoints
controlPoints_deg = data.aeroParams.controlBreakpoints_deg; % [degree] delta breakpoints
Cn = data.aeroParams.CnFin_na; % [unitless] Normal coefficient 3D lookup table
aoaPoints_rad = deg2rad(aoaPoints_deg); % [radians] converting alpha breakpoints to radians
controlPoints_rad = deg2rad(controlPoints_deg); % [radians] converting delta breakpoints to radians

[dCn_alpha, dCn_mach, dCn_control] =gradient(Cn, aoaPoints_rad,machPoints, controlPoints_rad); % computes the gradient
Cn_alpha_rad = dCn_alpha; % [1/radians] 3D lookup table with Mach x AoA x Delta for C_{N_\alpha}
Cn_delta_rad = dCn_control; % [1/radians] 3D lookup table with Mach x AoA x Delta for C_{N_\delta}
CnAvg_alpha_rad= mean(Cn_alpha_rad, 'all')*4; % [1/radians] Average over all the Cn_alpha in the table
CnAvg_delta_rad = mean(Cn_delta_rad,'all')*2; % [1/radians] Average over all the Cn_delta in the table
CmAvg_alpha_mrad = CnAvg_alpha_rad * lengthChar_m; % [m/radians] Pitching Moment Derivative wrt AoA
CmAvg_delta_mrad = CnAvg_delta_rad * lengthChar_m; % [m/radians] Pitching Moment Derivative wrt Delta

% Normal Force and Pitching Coefficients
Zalpha =-1*grav_m_s2*dynamicPressure_Pa*Sref_m2*CnAvg_alpha_rad/(weight_N*windVelocity_m_s);% [radian/s] DimensionalNormalForceDerivativeAlpha
Zdelta =-1*grav_m_s2*dynamicPressure_Pa*Sref_m2*CnAvg_delta_rad/(weight_N*windVelocity_m_s);% [radian/s] DimensionalNormalForceDerivativeDelta
Malpha = dynamicPressure_Pa*Sref_m2*CmAvg_alpha_mrad/Iyy_kgm2; % [radians/s^2]
Mdelta = dynamicPressure_Pa*Sref_m2*CmAvg_delta_mrad/Iyy_kgm2; % [radians/s^2]

% Transfer Function
bWrapper = Malpha*Zdelta - Mdelta*Zalpha; % [radians/s^3] Grouping it into a constant 
transferNum = [-Mdelta, -1*bWrapper];
transferDenom = [-1, Zalpha, Malpha];
omegaDeltaTF = tf(transferNum, transferDenom); % [radians/s] \omega = \dot{theta} so this is theta dot/delta
timeConstant_s = .02; % [s] Time Constant
fastPoleTF = tf(1,[timeConstant_s,1]); % Fast Pole Transfer Function
omegaDeltaInvTF = inv(omegaDeltaTF); % Inverse of our Transfer Function
omegaDeltaInvTFFP = omegaDeltaInvTF*fastPoleTF; % Inverse Transfer Function with Fast Pole
omegDeltaTF_deg = omegaDeltaTF*pi/180;

%step(omegaDeltaInvTFFP);
