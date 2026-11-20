function buildDataDictionaryFile(sdddPath, P)
%BUILDDATADICTIONARYFILE  Write struct P into a data dictionary (one entry
%   per top-level field), creating the .sldd if it doesn't exist yet.
%   Works for any parameter struct.
%
%   buildDataDictionaryFile(sdddPath, P)
%     sdddPath   path to the .sldd to create/update
%     P          struct whose top-level fields become dictionary entries

% A dictionary's referenced data sources (see addDataSource in
% buildDataDictionaries.m) are resolved by bare filename via MATLAB's
% cwd/path, not a stored path -- same constraint as a model's
% DataDictionary property (see linkModelToDataDictionary.m). cd into the
% dictionary's own folder so any referenced .sldd sitting next to it
% resolves regardless of the caller's cwd.
startDir = pwd;
cleanupObj = onCleanup(@() cd(startDir));
cd(fileparts(sdddPath));

% Update in place rather than delete+recreate -- deleting and rebuilding
% the file churns its internal generation/identity, which corrupts the
% master table if anything (this session, the GUI, a stale handle) still
% references the old one.
if ~exist(sdddPath, 'file')
    Simulink.data.dictionary.create(sdddPath);
end
dictObj = Simulink.data.dictionary.open(sdddPath);
designData = getSection(dictObj, 'Design Data');

% Entries are also updated in place (only the Value of an existing
% Simulink.Parameter is changed) so a rebuild is a pure value change to
% any model compiled in Fast Restart -- deleting and re-adding entries
% looks like a structural change and forces a recompile/error. Fast
% Restart still can't absorb a change to an entry's size, data type, or
% struct field layout; those need Fast Restart turned off once.
% StorageClass 'Auto' is tunable in Normal mode (what the models use); if
% a referenced model moves to Accelerator, set its Default parameter
% behavior to 'Tunable' or these may get inlined.
fn = fieldnames(P);

existing = find(designData);
existingNames = {existing.Name};
stale = setdiff(existingNames, fn);
for i = 1:numel(stale)
    deleteEntry(designData, stale{i});
end

nAdded = 0; nUpdated = 0;
for i = 1:numel(fn)
    newValue = P.(fn{i});
    % Bus objects are data types, not parameters -- store them as-is.
    if isa(newValue, 'Simulink.Bus')
        if ismember(fn{i}, existingNames)
            entry = getEntry(designData, fn{i});
            if ~isequal(getValue(entry), newValue)
                setValue(entry, newValue);
                nUpdated = nUpdated + 1;
            end
        else
            addEntry(designData, fn{i}, newValue);
            nAdded = nAdded + 1;
        end
        continue
    end
    if ismember(fn{i}, existingNames)
        entry = getEntry(designData, fn{i});
        prm = getValue(entry);
        if isa(prm, 'Simulink.Parameter')
            if ~isequal(prm.Value, newValue)
                prm.Value = newValue;
                setValue(entry, prm);
                nUpdated = nUpdated + 1;
            end
            continue
        end
        % Not a Simulink.Parameter (e.g. hand-added raw value) -- replace it.
        deleteEntry(designData, fn{i});
    end
    prm = Simulink.Parameter;
    prm.Value = newValue;
    prm.CoderInfo.StorageClass = 'Auto';
    addEntry(designData, fn{i}, prm);
    nAdded = nAdded + 1;
end

saveChanges(dictObj);
close(dictObj);

fprintf('%s: %d added, %d updated, %d removed, %d unchanged\n', sdddPath, ...
    nAdded, nUpdated, numel(stale), numel(fn) - nAdded - nUpdated);

end
