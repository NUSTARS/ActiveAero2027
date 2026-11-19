%LINEARIZESYSTEM  Open-loop plant TF (fin combination -> body rate) at
%   several operating points along the coast phase, picked by airspeed.
%
%   1. Runs the model once to get airspeed vs time.
%   2. Finds the coast-phase time (after max speed, before apogee) where
%      the airspeed equals each value in velList_mps.
%   3. Linearizes at all of those snapshot times in one go, with the loop
%      opened at the servo output (controller doesn't act).
%   4. Splits off the slow trajectory modes and reduces each TF to the
%      short-period pair, then tabulates wn / zeta / gain vs airspeed.
%
%   Leaves in the workspace:
%     results  table: airspeed, time, Mach, qbar, wn, zeta, DC gain
%     Tfull    cell, full linear TF at each point (all states)
%     Tred     cell, reduced (nRed-order) short-period TF at each point
%
%   Any test step you add to the model shows up in the nominal run and the
%   snapshots after it -- disable it before running this.

mdl = "activeControlSim";
load_system(mdl);

velList_mps = [275 250 200 100 50];
outAxis     = 3;                        % body-rate output: 1 = p, 2 = q, 3 = r
outLabel    = 'r';
v           = [0; 1; 0; -1];            % fin combination [deg]: fins 2 & 4 -> yaw
nRed        = 2;                        % reduced model order (short-period pair)

inPt  = mdl + "/Plant/Servo Model/1";                            % control_deg after servo
outPt = mdl + "/Plant/Equatons of Motion/6DOF (Quaternion)/7";   % wBdy_rps

% ---- 1. Nominal run -> airspeed history -------------------------------
fprintf('Running nominal sim for the airspeed history...\n');
nominal = sim(mdl);
env  = nominal.simout.plant_bus.enviroment_bus;   % 'enviroment' spelling matches the bus
tEnv = env.airspeed_mps.Time;
Vair = vecnorm(tsData_local(env.airspeed_mps), 2, 2);
aSnd = tsData_local(env.a_mps);
rho  = tsData_local(env.rho_kgpm3);

% ---- 2. Coast-phase snapshot times ------------------------------------
[~, iMax] = max(Vair);
iApo = iMax + find(diff(Vair(iMax:end)) > 0, 1) - 1;    % first speed minimum after burnout
if isempty(iApo), iApo = numel(Vair); end
[Vc, ia] = unique(Vair(iMax:iApo));                    % monotonic for interp1
tc = tEnv(iMax:iApo);
tc = tc(ia);

tSnap = interp1(Vc, tc, velList_mps);
keep  = ~isnan(tSnap);
if any(~keep)
    warning('linearizeSystem:outOfRange', ...
        'Skipping airspeeds outside the coast range [%.0f, %.0f] m/s: %s', ...
        Vc(1), Vc(end), mat2str(velList_mps(~keep)));
end
velList_mps = velList_mps(keep);
tSnap = tSnap(keep);
nPts  = numel(tSnap);
if nPts == 0
    error('linearizeSystem:noPoints', 'No requested airspeed falls in the coast phase.');
end

% ---- 3. Linearize at every snapshot in one sim ------------------------
sllin = slLinearizer(mdl, [inPt, outPt]);
sllin.OperatingPoints = tSnap;
Tall = getIOTransfer(sllin, inPt, outPt, inPt);   % [3 x 4 x nPts], loop opened at the input

% ---- 4. Short-period model at each point ------------------------------
Tfull = cell(nPts, 1);
Tred  = cell(nPts, 1);
[wn, zeta, dcGain] = deal(nan(nPts, 1));
for k = 1:nPts
    Tk = minreal(Tall(outAxis, :, k) * v, [], false);
    Tfull{k} = Tk;

    % Short period = highest-frequency oscillatory pair. Split everything
    % well below it off (slow trajectory/attitude modes, some unstable),
    % then reduce what's left.
    p  = pole(Tk);
    pc = p(imag(p) > 1e-6);
    if isempty(pc)
        warning('linearizeSystem:noOsc', 'No oscillatory mode at %.0f m/s.', velList_mps(k));
        continue
    end
    wSp = max(abs(pc));
    [~, Tfast] = freqsep(Tk, wSp / 4);
    Tred{k} = balred(Tfast, nRed);

    [wnk, zk] = damp(Tred{k});
    [~, j] = max(wnk .* (zk < 1));              % the oscillatory pair
    wn(k)     = wnk(j);
    zeta(k)   = zk(j);
    dcGain(k) = dcgain(Tred{k});
end

Mach    = interp1(tEnv, aSnd, tSnap(:)).^-1 .* velList_mps(:);
qbar_Pa = 0.5 * interp1(tEnv, rho, tSnap(:)) .* velList_mps(:).^2;
results = table(velList_mps(:), tSnap(:), Mach, qbar_Pa, wn, zeta, rad2deg(dcGain), ...
    'VariableNames', {'airspeed_mps', 't_s', 'Mach', 'qbar_Pa', 'wn_rps', 'zeta', ...
                      ['dcGain_' outLabel '_degps_per_deg']});
fprintf('\nFin combination %s deg -> %s, loop opened at the servo output:\n', mat2str(v.'), outLabel);
disp(results)

% One row per operating point: num/den as [1 x nRed+1] coefficient rows
% (tfdata pads num to den's length), sorted by qbar so the column can be
% used directly as lookup-table breakpoints. Points with no oscillatory
% mode (empty Tred) are left out.
iOk = find(~cellfun(@isempty, Tred));
num = zeros(numel(iOk), nRed + 1);
den = zeros(numel(iOk), nRed + 1);
for i = 1:numel(iOk)
    [n, d] = tfdata(tf(Tred{iOk(i)}), 'v');
    num(i, :) = n;
    den(i, :) = d;
end
plantTable = table(qbar_Pa(iOk), velList_mps(iOk).', num, den, ...
    'VariableNames', {'dynPressure_Pa', 'airspeed_mps', 'num', 'den'});
plantTable = sortrows(plantTable, 'dynPressure_Pa');

outFile = fullfile(fileparts(fileparts(mfilename('fullpath'))), 'dataDictionaries', 'plantTable.mat');
save(outFile, "plantTable")
fprintf('Saved %s\n', outFile);


for k = 1:nPts
    if isempty(Tred{k}), continue, end
    [num, den] = tfdata(Tred{k}, 'v');
    fprintf('%4.0f m/s (t = %5.2f s):  %s(s) = (%s) / (%s)   [rad/s per unit combination]\n', ...
        velList_mps(k), tSnap(k), outLabel, poly2str_local(num), poly2str_local(den));
end

% ---- Plots ------------------------------------------------------------
names = compose('%.0f m/s', velList_mps(:));
ok = ~cellfun(@isempty, Tred);

figure('Name', 'Short-period step responses');
hold on; grid on
tStepPlot = (0:0.001:3)';
for k = find(ok).'
    plot(tStepPlot, rad2deg(step(Tred{k}, tStepPlot)), 'DisplayName', names{k});
end
xlabel('time after step [s]'); ylabel([outLabel ' [deg/s] per unit combination']);
title('Reduced plant step response vs airspeed'); legend('Location', 'best');

figure('Name', 'Short-period Bode');
bodeplot(Tred{ok});
legend(names(ok), 'Location', 'best'); grid on

figure('Name', 'Short-period parameters vs airspeed');
subplot(3, 1, 1); plot(velList_mps, wn, 'o-'); grid on; ylabel('\omega_n [rad/s]');
subplot(3, 1, 2); plot(velList_mps, zeta, 'o-'); grid on; ylabel('\zeta');
subplot(3, 1, 3); plot(velList_mps, rad2deg(dcGain), 'o-'); grid on;
ylabel('DC gain [deg/s per deg]'); xlabel('airspeed [m/s]');

clear velList_mps env tEnv Vair aSnd rho iMax iApo Vc ia tc keep p pc wSp Tfast wnk zk j k tStepPlot ok names num den iOk i n d

% ======================================================================
function s = poly2str_local(c)
    % polynomial coefficients -> 'a s^2 + b s + c', leading zeros dropped
    c = c(find(abs(c) > 1e-12, 1):end);
    n = numel(c) - 1;
    terms = strings(1, numel(c));
    for i = 1:numel(c)
        p = n - i + 1;
        if p == 0,     terms(i) = sprintf('%.4g', c(i));
        elseif p == 1, terms(i) = sprintf('%.4g s', c(i));
        else,          terms(i) = sprintf('%.4g s^%d', c(i), p);
        end
    end
    s = strjoin(terms, ' + ');
end

% ======================================================================
function d = tsData_local(ts)
    % timeseries Data as N x m regardless of how Simulink stacked it
    d = squeeze(ts.Data);
    if size(d, 1) ~= numel(ts.Time)
        d = d.';
    end
end
