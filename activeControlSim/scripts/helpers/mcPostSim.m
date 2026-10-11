function s = mcPostSim(simOut)
%MCPOSTSIM  PostSimFcn for runMonteCarlo.m: reduce one run's output to
%   summary metrics, so parsim workers don't ship full logged timeseries
%   back to the client.
%
%   Each field of the returned struct becomes a property of that run's
%   Simulink.SimulationOutput (e.g. out(i).apogee_m), replacing the
%   logged data. ErrorMessage and SimulationMetadata are kept.
%
%   Lives in its own file (not a local function in runMonteCarlo.m) so
%   parsim workers can resolve it from the path.

s.apogee_m = NaN;

if ~isempty(simOut.ErrorMessage)
    return
end

posNed_m = simOut.simout.plant_bus.eom_bus.posNed_m.Data;
s.apogee_m = -min(posNed_m(:,3));

end
