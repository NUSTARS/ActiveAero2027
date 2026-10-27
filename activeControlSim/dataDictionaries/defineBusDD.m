function B = defineBusDD()
%DEFINEBUSDD  Simulink.Bus objects for every bus built by a Bus Creator in
%   activeControlSim. In the full sim these are virtual buses and need no
%   object, but a root Inport (e.g. sensor_bus into autocodeModel) has to
%   be typed 'Bus: <name>' to output a bus at all, and code generation
%   needs named types for buses crossing a model boundary.
%
%   Element names/sizes/types must match the Bus Creators that build these
%   buses. Bus names follow the Outport each Bus Creator feeds. Where
%   several Bus Creators build the same structure (the three inner/outer
%   loop axes, the four fins, the three PID gain sets) they share one type.
%   Bus Creators inside library blocks (Dryden wind, World Magnetic Model)
%   are skipped. To regenerate after a model change, load activeControlSim
%   and run:
%       blks = find_system('activeControlSim', 'FollowLinks','off', ...
%           'LookUnderMasks','all', 'BlockType','BusCreator');
%       Simulink.Bus.createObject('activeControlSim', blks);
%   then read the resulting Simulink.Bus entries out of navParams.sldd
%   (and discard the dictionary changes).

% ---------------------------------------------------------------- sensors
% models/plant/sensorModels.slx
B.truth_bus = makeBus_local({
    'gyroBiasTrue_rps',  3, 'double'
    'accBiasTrue_mps2',  3, 'double'
});

B.sensor_bus = makeBus_local({
    'truth_bus',         1, 'Bus: truth_bus'
    'fBdyMeas_mps2',     3, 'double'
    'wBdyMeas_rps',      3, 'double'
    'magBdyMeas_nT',     3, 'double'
    'baroMeas_Pa',       1, 'double'
});

% ------------------------------------------------------------------ plant
% models/plant/*.slx
B.environment_bus = makeBus_local({
    'gravityForceBdy_N', 3, 'double'
    'temp_K',            1, 'double'
    'a_mps',             1, 'double'
    'pressure_Pa',       1, 'double'
    'rho_kgpm3',         1, 'double'
    'onRail_b',          1, 'boolean'
    'airspeed_mps',      3, 'double'
    'windBdy_mps',       3, 'double'
    'airW_rps',          3, 'double'
});

B.fin_bus = makeBus_local({
    'finMoment_Nm',      3, 'double'
    'finForce_N',        3, 'double'
    'aoa_deg',           1, 'double'
    'liftSign_na',       1, 'double'
    'airspeedFin_mps',   3, 'double'
});

B.body_bus = makeBus_local({
    'bodyMoment_Nm',     3, 'double'
    'bodyForce_N',       3, 'double'
    'aoa_deg',           1, 'double'
});

B.aero_bus = makeBus_local({
    'aeroMoment_Nm',     3, 'double'
    'aeroForce_N',       3, 'double'
    'fin1_bus',          1, 'Bus: fin_bus'
    'fin2_bus',          1, 'Bus: fin_bus'
    'fin3_bus',          1, 'Bus: fin_bus'
    'fin4_bus',          1, 'Bus: fin_bus'
    'body_bus',          1, 'Bus: body_bus'
});

B.eom_bus = makeBus_local({
    'posNed_m',          3, 'double'
    'q_na',              4, 'double'
    'velBdy_mps',        3, 'double'
    'wBdy_rps',          3, 'double'
    'accBdy_mps2',       3, 'double'
    'wDotBdy_rps2',      3, 'double'
});

B.motor_bus = makeBus_local({
    'thrust_N',          3, 'double'
});

% element name keeps the model's 'enviroment' spelling -- it must match
% the signal name on the Bus Creator input
B.plant_bus = makeBus_local({
    'enviroment_bus',    1, 'Bus: environment_bus'
    'aero_bus',          1, 'Bus: aero_bus'
    'eom_bus',           1, 'Bus: eom_bus'
});

% ------------------------------------------------------------- navigation
% models/navigation/navigation.slx
B.sensorEst_bus = makeBus_local({
    'accBdyEst_mps2',    3, 'double'
    'fBdyEst_mps2',      3, 'double'
    'wBdyEst_rps',       3, 'double'
});

B.noiseFiltered_bus = makeBus_local({
    'accelFilt_mps2',    3, 'double'
    'gyroFilt_rps',      3, 'double'
});

B.bias_bus = makeBus_local({
    'accelBias_mps2',    3, 'double'
    'gyroBias_rps',      3, 'double'
});

B.complementaryFilter_bus = makeBus_local({
    'qEst_na',           4, 'double'
    'velEst_mps',        3, 'double'
    'posEst_m',          3, 'double'
});

B.filter_bus = makeBus_local({
    'eulerAnglesEst_rad', 3, 'double'
    'qEst_na',           4, 'double'
    'velEst_mps',        3, 'double'
    'posEst_m',          3, 'double'
    'accelFilt_mps2',    3, 'double'
    'gyroFilt_rps',      3, 'double'
    'accelBias_mps2',    3, 'double'
    'gyroBias_rps',      3, 'double'
});

B.deadReckoning_bus = makeBus_local({
    'qEst_na',           4, 'double'
    'posEst_m',          3, 'double'
    'velEst_mps',        3, 'double'
});

B.navigation_bus = makeBus_local({
    'flightMode_enum',   1, 'Enum: flightMode'
    'qEst_na',           4, 'double'
    'phiEst_rad',        1, 'double'
    'thetaEst_rad',      1, 'double'
    'psiEst_rad',        1, 'double'
    'pEst_rps',          1, 'double'
    'qEst_rps',          1, 'double'
    'rEst_rps',          1, 'double'
    'xAccEst_mps2',      1, 'double'
    'yAccEst_mps2',      1, 'double'
    'zAccEst_mps2',      1, 'double'
    'accelBias_mps2',    3, 'double'
    'gyroBias_rps',      3, 'double'
    'dynPressureEst_Pa', 1, 'double'
    'xVelEst_mps',       1, 'double'
    'yVelEst_mps',       1, 'double'
    'zVelEst_mps',       1, 'double'
    'xPosEst_m',         1, 'double'
    'yPosEst_m',         1, 'double'
    'zPosEst_m',         1, 'double'
});

% --------------------------------------------------------------- guidance
% models/control/Guidance.slx
B.guidance_bus = makeBus_local({
    'phiCmd_rad',        1, 'double'
    'thetaCmd_rad',      1, 'double'
    'psiCmd_rad',        1, 'double'
});

% ------------------------------------------------------------- controller
% models/control/*.slx
B.pidGains_bus = makeBus_local({
    'P',                 3, 'double'
    'I',                 3, 'double'
    'D',                 3, 'double'
    'N',                 3, 'double'
});

B.outerLoopAxis_bus = makeBus_local({
    'rateCmd_rps',       1, 'double'
    'rateLimited_b',     1, 'boolean'
    'saturated_b',       1, 'boolean'
});

B.outerLoop_bus = makeBus_local({
    'pitchOuterLoop_bus', 1, 'Bus: outerLoopAxis_bus'
    'yawOuterLoop_bus',  1, 'Bus: outerLoopAxis_bus'
    'rollOuterLoop_bus', 1, 'Bus: outerLoopAxis_bus'
});

% 'rateLimted_b' spelling matches the model's signal name
B.innerLoopAxis_bus = makeBus_local({
    'control_deg',       1, 'double'
    'controlMoment_Nm',  1, 'double'
    'rateLimted_b',      1, 'boolean'
    'saturated_b',       1, 'boolean'
});

B.innerLoop_bus = makeBus_local({
    'pitchInnerLoop_bus', 1, 'Bus: innerLoopAxis_bus'
    'yawInnerLoop_bus',  1, 'Bus: innerLoopAxis_bus'
    'rollInnerLoop_bus', 1, 'Bus: innerLoopAxis_bus'
});

B.controller_bus = makeBus_local({
    'outerLoop_bus',     1, 'Bus: outerLoop_bus'
    'innerLoop_bus',     1, 'Bus: innerLoop_bus'
    'control_deg',       4, 'double'
});

% -------------------------------------------------------------- top level
% models/activeControlSim.slx -- logged to workspace
B.simOut_bus = makeBus_local({
    'navigation_bus',    1, 'Bus: navigation_bus'
    'controller_bus',    1, 'Bus: controller_bus'
    'plant_bus',         1, 'Bus: plant_bus'
    'sensor_bus',        1, 'Bus: sensor_bus'
});

end

% ======================================================================
function bus = makeBus_local(spec)
    % spec: one row per element -- {name, dimensions, dataType}
    elems = Simulink.BusElement.empty;
    for i = 1:size(spec, 1)
        e = Simulink.BusElement;
        e.Name = spec{i,1};
        e.Dimensions = spec{i,2};
        e.DataType = spec{i,3};
        elems(i) = e;
    end
    bus = Simulink.Bus;
    bus.Elements = elems;
end
