function P = derivePlantDD(P)
%DERIVEPLANTDD  Recompute plant parameters that are derived from other
%   parameters in P. Called at the end of definePlantDD, and again by
%   runMonteCarlo.m after dispersing inputs, so derived values always
%   match the (possibly dispersed) inputs they come from.
%
%   P = derivePlantDD(P)
%     P   plant parameter struct (may also hold other dictionaries'
%         entries, e.g. sensorParams -- only the fields below are touched)

%% Constants
in2m = 1/39.37;

% Motor Thrust
P.motorParams.thrust = P.motorParams.thrustScaling_na.*P.motorParams.thrustData(:,2);

% Initial attitude: eulIC_rad is [roll pitch yaw] (3-2-1) in the rotated
% (launch) frame, where a vertical rocket is ~0; rotate by 90deg about Y
% into NED. q_bodyNED = q_launchNED (x) q_bodyLaunch -- quatmultiply(a,b)
% applies a first, so the frame rotation goes on the left (the inverse of
% what plotRocketTrajectory/mcPostSim do to get back to the launch frame).
quatIC_na = eul2quat(fliplr(P.icParams.eulIC_rad), "ZYX");
quatRotIC_na = quatmultiply([0.707106781187, 0, 0.707106781187, 0], quatIC_na);
% eul2quat/quat2eul use [yaw pitch roll], hence the fliplr's; the 6DOF
% block's eul_0 is [roll pitch yaw].
P.icParams.eul_rad = fliplr(quat2eul(quatRotIC_na, "ZYX"));  % [rad], NED Euler angles


% Aero Tables
load(P.aeroParams.aeroFileName, 'aeroTables')
P.aeroParams.machBreakpoints_na = aeroTables.machPoints;
P.aeroParams.aoaBreakpoints_deg = aeroTables.aoaPoints;
P.aeroParams.controlBreakpoints_deg = aeroTables.controlPoints;
P.aeroParams.CpBase_m = in2m.*aeroTables.CpBase + P.aeroParams.CpBaseShift_m;
P.aeroParams.CaBase_na = P.aeroParams.bodyScale_na.*aeroTables.CaBase;
P.aeroParams.CnBase_na = P.aeroParams.bodyScale_na.*aeroTables.CnBase;
CnFinRaw_na = aeroTables.CnFinControl;
CaFinRaw_na = aeroTables.CaFinControl;

% Rescale AoA/control inputs (tables are ndgrid-ordered: mach x aoa x control;
% linear extrapolation so input scales > 1 don't produce NaN at the edges)
gridRaw = {P.aeroParams.machBreakpoints_na, P.aeroParams.aoaBreakpoints_deg, P.aeroParams.controlBreakpoints_deg};
gridScaled = {P.aeroParams.machBreakpoints_na, ...
              P.aeroParams.finStaticInputScale_na.*P.aeroParams.aoaBreakpoints_deg, ...
              P.aeroParams.finControlInputScale_na.*P.aeroParams.controlBreakpoints_deg};

CnFinInterp = griddedInterpolant(gridRaw, CnFinRaw_na, 'linear', 'linear');
CaFinInterp = griddedInterpolant(gridRaw, CaFinRaw_na, 'linear', 'linear');
CnFinScaled_na = CnFinInterp(gridScaled);
CaFinScaled_na = CaFinInterp(gridScaled);

% Find AOA/Control effect by looking at 0 Control/AOA (linear)
zeroAoaIndex = find(P.aeroParams.aoaBreakpoints_deg == 0);
zeroControlIndex = find(P.aeroParams.controlBreakpoints_deg == 0);

aoaEffectCn = CnFinScaled_na - CnFinScaled_na(:,zeroAoaIndex,:);
aoaEffectCa = CaFinScaled_na - CaFinScaled_na(:,zeroAoaIndex,:);

controlEffectCn = CnFinScaled_na - CnFinScaled_na(:,:,zeroControlIndex);
controlEffectCa = CaFinScaled_na - CaFinScaled_na(:,:,zeroControlIndex);

P.aeroParams.CnFin_na = CnFinScaled_na + (P.aeroParams.finStaticScale_na - 1).*aoaEffectCn + (P.aeroParams.finControlScale_na - 1).*controlEffectCn;
P.aeroParams.CaFin_na = CaFinScaled_na + (P.aeroParams.finStaticScale_na - 1).*aoaEffectCa + (P.aeroParams.finControlScale_na - 1).*controlEffectCa;
end
