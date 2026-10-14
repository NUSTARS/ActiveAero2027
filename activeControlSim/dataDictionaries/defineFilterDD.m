function F = defineFilterDD()

F.filterParams.P0 = [0 0 0; 0 0 0; 0 0 0];
errEuler0 = [0 0 0];
errVel0 = [0 0 0];
errPos0 = [0 0 0];
errAccBias0 = [0 0 0];
errGyroBias0 = [0 0 0];
F.filterParams.errx0 = [errEuler0, errVel0, errPos0, errAccBias0, errGyroBias0];
F.filterParams.order = 3;
F.filterParams.R = eye(15); % fill in with actual measurement uncertainty matrix


end