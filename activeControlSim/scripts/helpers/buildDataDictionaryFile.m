function buildDataDictionaryFile(sdddPath, P)
%BUILDDATADICTIONARYFILE  Write struct P into a data dictionary (one entry
%   per top-level field), creating the .sldd if it doesn't exist yet.
%   Works for any parameter struct.
%
%   buildDataDictionaryFile(sdddPath, P)
%     sdddPath   path to the .sldd to create/update
%     P          struct whose top-level fields become dictionary entries

% Update in place rather than delete+recreate -- deleting and rebuilding
% the file churns its internal generation/identity, which corrupts the
% master table if anything (this session, the GUI, a stale handle) still
% references the old one.
if ~exist(sdddPath, 'file')
    Simulink.data.dictionary.create(sdddPath);
end
dictObj = Simulink.data.dictionary.open(sdddPath);
designData = getSection(dictObj, 'Design Data');

existing = find(designData);
for i = 1:numel(existing)
    deleteEntry(designData, existing(i).Name);
end

fn = fieldnames(P);
for i = 1:numel(fn)
    prm = Simulink.Parameter;
    prm.Value = P.(fn{i});
    prm.CoderInfo.StorageClass = 'Auto';
    addEntry(designData, fn{i}, prm);
end

saveChanges(dictObj);
close(dictObj);

fprintf('Wrote %d entries to %s\n', numel(fn), sdddPath);

end
