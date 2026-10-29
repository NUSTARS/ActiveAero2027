function F = defineFilterDD()

% ICs
F.filterParams.P0 = 1e-4 * eye(15,15);%[0 0 0; 0 0 0; 0 0 0];
errEuler0 = [0 0 0];
errVel0 = [0 0 0];
errPos0 = [0 0 0];
errAccBias0 = [0 0 0];
errGyroBias0 = [0 0 0];
F.filterParams.errx0 = [errEuler0, errVel0, errPos0, errAccBias0, errGyroBias0];
F.filterParams.order = 1;

% GNSS measurement model
sigDummyPosNE_m = 0.1; % [m]
sigDummyPosD_m = 0.2; % [m]
sigDummyVelNE_mps = 0.002; % [mps]
sigDummyVelD_mps = 0.004; % [mps]
varDummyPos_m = [sigDummyPosNE_m^2, sigDummyPosNE_m^2, sigDummyPosD_m^2]; % [m^2]
varDummyVel_mps = [sigDummyVelNE_mps^2, sigDummyVelNE_mps^2, sigDummyVelD_mps^2]; % [m^2/s^2]
varDummyGNSS = blkdiag(diag(varDummyPos_m), diag(varDummyVel_mps)); 
F.filterParams.R_GNSS = varDummyGNSS; % see if it's not diagonal

% QUEST measurement model
sigDummyQUEST_amin = 5; % [arcmin]
sigDummyQUEST_rad = sigDummyQUEST_amin * 0.0002908; % [rad]
varDummyQUEST_rad = sigDummyQUEST_rad^2 * [1 1 1]; % [rad^2]
F.filterParams.R_QUEST = diag(varDummyQUEST_rad);

end