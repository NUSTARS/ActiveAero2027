% ------------------------------------------------------------------
% Build aero lookup tables (base coefficients + fin/control contributions)
% for interpolated use in flight simulation.
% ------------------------------------------------------------------

noFinsPath   = 'C:\Users\maxhu\Downloads\atlas-nofins.CSV';   % airframe without fins
withFinsPath = 'C:\Users\maxhu\Downloads\atlas-aero-plots.CSV'; % airframe with fins

% --- Grid sample points for output tables ---
machSamples    = linspace(0.1, 1, 10);   % Mach numbers to interpolate at
alphaSamples   = [0 2 4];                % angles of attack (deg) to interpolate at
controlPoints  = [-4 -2 0 2 4];          % control input angles (deg), must stay ascending
controlFactor  = 0.2;                    % scales control input's effect on Ca/Cn

noFinsData   = readtable(noFinsPath);
withFinsData = readtable(withFinsPath);

% Split control input samples so negative angles can be evaluated using the
% positive-side data and sign flipped (Cn is odd, Ca is even about alpha/control = 0)
posControl = controlPoints(controlPoints >= 0);
negControl = controlPoints(controlPoints < 0);

% --- Base airframe coefficients (no fins), at the alpha/Mach sample grid ---
CpBase = interpGrid(noFinsData.Alpha, noFinsData.Mach, noFinsData.CP, alphaSamples, machSamples);
CpFull = interpGrid(withFinsData.Alpha, withFinsData.Mach, withFinsData.CP, alphaSamples, machSamples);

% --- Fin contribution to Ca/Cn at zero control input ---
[CaFin, CnFin, CaBase, CnBase] = findFinForce(alphaSamples, machSamples, noFinsData, withFinsData);

% --- Fin contribution due to control input, split by sign ---
% Positive control inputs queried directly; negative control inputs queried by
% mirroring to the positive side and flipping sign (see symmetry note above).
[posCaControl, posCnControl] = findFinForce(posControl, machSamples, noFinsData, withFinsData);
[negCaControl, negCnControl] = findFinForce(-1*negControl, machSamples, noFinsData, withFinsData);

% --- Assemble Cn: baseline fin force + control input contribution ---
CnFinControl = repmat(CnFin, [1 1 numel(controlPoints)]);   % broadcast baseline across all control inputs
cnControl = controlFactor * [-1*negCnControl, posCnControl];  % Cn is odd -> negate negative-side values
cnControl = repmat(cnControl, [1 1 numel(alphaSamples)]);
cnControl = permute(cnControl, [1 3 2]);                     % align dims to [Mach x ControlInput x Alpha]
CnFinControl = CnFinControl + cnControl;

% --- Assemble Ca: baseline fin force + control input contribution ---
CaFinControl = repmat(CaFin, [1 1 numel(controlPoints)]);
caControl = controlFactor * [negCaControl, posCaControl];     % Ca is even -> no sign flip
caControl = repmat(caControl, [1 1 numel(alphaSamples)]);
caControl = permute(caControl, [1 3 2]);
CaFinControl = CaFinControl + caControl;

% --- Package and save ---
aeroTables.machPoints     = machSamples;
aeroTables.aoaPoints      = alphaSamples;
aeroTables.controlPoints  = controlPoints;
aeroTables.CpBase         = CpBase;
aeroTables.CaBase         = CaBase;
aeroTables.CnBase         = CnBase;
aeroTables.CnFinControl   = CnFinControl;
aeroTables.CaFinControl   = CaFinControl;
aeroTables.CnFull   = CnFin + CnBase;
aeroTables.CaFull   = CaFin + CaBase;
aeroTables.CpFull   = CpFull;

save('activecontrolSim/dataDictionaries/aeroTables.mat', "aeroTables")


% ------------------------------------------------------------------
% findFinForce: compute the fin's contribution to Ca and Cn by
% differencing "with fins" vs "no fins" coefficients (split by 2 fins),
% and pass back the base coefficients too so callers don't need to
% call interpGrid a second time for the same data.
% ------------------------------------------------------------------
function [CaFin, CnFin, CaBase, CnBase] = findFinForce(alphaSamples, machSamples, noFinsData, withFinsData)
    CaBase = interpGrid(noFinsData.Alpha, noFinsData.Mach, noFinsData.CAPower_Off, alphaSamples, machSamples);
    CaFull = interpGrid(withFinsData.Alpha, withFinsData.Mach, withFinsData.CAPower_Off, alphaSamples, machSamples);
    CaFin = (CaFull - CaBase) / 2;   % divide by 2: two fins assumed to contribute equally

    CnBase = interpGrid(noFinsData.Alpha, noFinsData.Mach, noFinsData.CN, alphaSamples, machSamples);
    CnFull = interpGrid(withFinsData.Alpha, withFinsData.Mach, withFinsData.CN, alphaSamples, machSamples);
    CnFin = (CnFull - CnBase) / 2;
end


% ------------------------------------------------------------------
% interpGrid: pivot scattered (dataX, dataY, dataZ) samples into a
% regular grid over unique dataX/dataY values, then bilinearly
% interpolate that grid at (xSamples, ySamples).
% ------------------------------------------------------------------
function gridOut = interpGrid(dataX, dataY, dataZ, xSamples, ySamples)
    xUnique = unique(dataX);
    yUnique = unique(dataY);

    gridValues = nan(numel(yUnique), numel(xUnique));
    for i = 1:height(dataX)
        row = yUnique == dataY(i);
        col = xUnique == dataX(i);
        gridValues(row, col) = dataZ(i);
    end

    [Xq, Yq] = meshgrid(xSamples, ySamples);
    gridOut = interp2(xUnique, yUnique, gridValues, Xq, Yq);
end