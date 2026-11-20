function [flapTable, cdiTable, baseTable] = parseDatcomOut(datcomPath)
% PARSEDATCOMOUT  Parse a Digital DATCOM datcom.out file into MATLAB tables.
%
%   [flapTable, cdiTable, baseTable] = parseDatcomOut(datcomPath)
%
%   flapTable : control-deflection increments, one row per (Mach, Delta)
%       Mach, Delta [deg], dCL, dCM, dCLmax, dCDmin, CLA_D, CH_A, CH_D
%       (CLA_D, CH_A, CH_D are per degree; NDM / blank entries -> NaN.
%        CH_A is printed once per Mach and is copied to every Delta row.)
%
%   cdiTable  : induced drag increment due to deflection,
%       one row per (Mach, Delta, Alpha)
%       Mach, Delta [deg], Alpha [deg], dCDi, dCL, dCDmin, dCD, dCN, dCA
%       dCD = dCDmin + dCDi is the total drag increment from deflection.
%       dCN / dCA are the body-axis normal / axial increments, found by
%       rotating (dCL, dCD) from the wind frame through alpha:
%           dCN =  dCL*cos(a) + dCD*sin(a)
%           dCA = -dCL*sin(a) + dCD*cos(a)
%       (DATCOM's dCL does not vary with alpha, so it is repeated across alpha.)
%
%   baseTable : (optional) undeflected wing-body coefficients,
%       one row per (Mach, Alpha)
%       Mach, Alpha, CD, CL, CM, CN, CA, XCP, CLA, CMA, CYB, CNB, CLB
%       (DATCOM overflow fields '*******' -> NaN; CYB/CNB only printed at
%        the first alpha and are copied down.)
%
%   Example (gridded lookup):
%       [flap, cdi] = parseDatcomOut('datcom.out');
%       M = unique(flap.Mach); d = unique(flap.Delta);
%       dCL = reshape(flap.dCL, numel(d), numel(M)).';      % [Mach x Delta]
%       F = griddedInterpolant({M, d}, dCL);
%       F(0.35, 12.5)

if nargin < 1 || isempty(datcomPath)
    datcomPath = fullfile(fileparts(mfilename('fullpath')), '..', '..', 'data', 'datcom.out');
end

lines = readlines(datcomPath);
nLines = numel(lines);

flapRows = zeros(0, 9);
cdiRows  = zeros(0, 4);
baseRows = zeros(0, 13);

mach = NaN;
i = 1;
while i <= nLines
    ln = lines(i);

    % --- Flight-condition line: Mach is the first number after the units row
    if contains(ln, "IN/SEC") || contains(ln, "FT/SEC") || contains(ln, "M/SEC")
        vals = sscanf(extractAfter(lines(i+1), 1), '%f');
        mach = vals(1);
        i = i + 2;
        continue
    end

    % --- Wing-body alpha sweep
    if startsWith(ln, "0 ALPHA")
        i = i + 2;                               % skip header + "0" spacer
        cyb = NaN; cnb = NaN;
        while i <= nLines && isNumericRow(lines(i))
            v = parseFixedRow(lines(i), 12);
            if ~isnan(v(10)), cyb = v(10); end
            if ~isnan(v(11)), cnb = v(11); end
            v(10) = cyb; v(11) = cnb;
            baseRows(end+1, :) = [mach, v]; %#ok<AGROW>
            i = i + 1;
        end
        continue
    end

    % --- Flap increments vs delta
    if contains(ln, "D(CL)") && contains(ln, "DELTA")
        i = i + 1;
        while i <= nLines && ~isNumericRow(lines(i)), i = i + 1; end
        chA = NaN;
        while i <= nLines && isNumericRow(lines(i))
            tok = split(strtrim(lines(i)));
            num = str2double(tok);                % 'NDM' -> NaN
            % Columns: DELTA dCL dCM dCLmax dCDmin CLA_D [CH_A] CH_D
            if numel(tok) >= 8
                chA = num(7);
                chD = num(8);
            else
                chD = num(end);
            end
            flapRows(end+1, :) = [mach, num(1:6).', chA, chD]; %#ok<AGROW>
            i = i + 1;
        end
        % CH_A is a per-Mach value: fill it for all deltas at this Mach
        flapRows(flapRows(:,1) == mach, 8) = chA;
        continue
    end

    % --- Induced drag increment table
    if contains(ln, "INDUCED DRAG COEFFICIENT INCREMENT")
        deltas = sscanf(extractAfter(lines(i+1), "="), '%f').';
        i = i + 2;
        while i <= nLines && ~isNumericRow(lines(i)), i = i + 1; end
        while i <= nLines && isNumericRow(lines(i))
            v = sscanf(lines(i), '%f').';
            alpha = v(1);
            cdi = v(2:end);
            n = numel(deltas);
            cdiRows = [cdiRows; repmat(mach, n, 1), deltas(:), repmat(alpha, n, 1), cdi(:)]; %#ok<AGROW>
            i = i + 1;
        end
        continue
    end

    i = i + 1;
end

flapTable = array2table(flapRows, 'VariableNames', ...
    {'Mach', 'Delta', 'dCL', 'dCM', 'dCLmax', 'dCDmin', 'CLA_D', 'CH_A', 'CH_D'});
cdiTable = array2table(cdiRows, 'VariableNames', {'Mach', 'Delta', 'Alpha', 'dCDi'});
baseTable = array2table(baseRows, 'VariableNames', ...
    {'Mach', 'Alpha', 'CD', 'CL', 'CM', 'CN', 'CA', 'XCP', 'CLA', 'CMA', 'CYB', 'CNB', 'CLB'});

flapTable = sortrows(flapTable, {'Mach', 'Delta'});
cdiTable  = sortrows(cdiTable,  {'Mach', 'Delta', 'Alpha'});
baseTable = sortrows(baseTable, {'Mach', 'Alpha'});

% --- Body-axis increments: rotate (dCL, dCD) from wind frame to body frame
cdiTable = join(cdiTable, flapTable(:, {'Mach', 'Delta', 'dCL', 'dCDmin'}), ...
    'Keys', {'Mach', 'Delta'});
cdiTable.dCD = cdiTable.dCDmin + cdiTable.dCDi;
a = deg2rad(cdiTable.Alpha);
cdiTable.dCN =  cdiTable.dCL .* cos(a) + cdiTable.dCD .* sin(a);
cdiTable.dCA = -cdiTable.dCL .* sin(a) + cdiTable.dCD .* cos(a);

flapTable.Properties.VariableUnits = {'', 'deg', '', '', '', '', '1/deg', '1/deg', '1/deg'};
cdiTable.Properties.VariableUnits  = {'', 'deg', 'deg', '', '', '', '', '', ''};
end


function tf = isNumericRow(ln)
% True for data rows: first token parses as a number and line isn't a
% DATCOM carriage-control-only line ("0" / "1").
s = strtrim(ln);
if strlength(s) == 0 || s == "0" || startsWith(ln, ["0", "1"])
    tf = false;
    return
end
tok = split(s);
tf = ~isnan(str2double(tok(1)));
end


function v = parseFixedRow(ln, nCols)
% Parse a wing-body alpha-sweep row using the fixed DATCOM column layout,
% so blank CYB/CNB fields and '*******' overflows map to NaN.
%   ALPHA  CD  CL  CM  CN  CA  XCP  CLA  CMA  CYB  CNB  CLB
edges = [1 8 17 26 36 44 53 62 75 88 101 114 127];
s = char(ln);
s(end+1:edges(end)) = ' ';
v = NaN(1, nCols);
for k = 1:nCols
    v(k) = str2double(s(edges(k):edges(k+1)-1));
end
end
