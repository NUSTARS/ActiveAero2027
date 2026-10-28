function F = defineFilterDD()

F.filterParams.P0 = 1e-4 * eye(15,15);%[0 0 0; 0 0 0; 0 0 0];
errEuler0 = [0 0 0];
errVel0 = [0 0 0];
errPos0 = [0 0 0];
errAccBias0 = [0 0 0];
errGyroBias0 = [0 0 0];
F.filterParams.errx0 = [errEuler0, errVel0, errPos0, errAccBias0, errGyroBias0];
F.filterParams.order = 1;
sigDummyPosNE_m = 0.1; % [m]
sigDummyPosD_m = 0.2; % [m]
sigDummyVelNE_mps = 0.002; % [mps]
sigDummyVelD_mps = 0.004; % [mps]
varDummyPos_m = [sigDummyPosNE_m^2, sigDummyPosNE_m^2, sigDummyPosD_m^2]; % [m^2]
varDummyVel_mps = [sigDummyVelNE_mps^2, sigDummyVelNE_mps^2, sigDummyVelD_mps^2]; % [m^2/s^2]
varDummyGNSS = blkdiag(diag(varDummyPos_m), diag(varDummyVel_mps)); 
F.filterParams.R = varDummyGNSS; % next add QUEST part of R. Also see if it's not diagonal

%blkdiag(0.5^2 * eye(3), 0.5*eye(3));%eye(6,6); % fill in with actual measurement uncertainty matrix


end