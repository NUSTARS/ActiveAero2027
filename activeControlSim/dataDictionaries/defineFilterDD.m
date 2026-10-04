function F = defineFilterDD()


% % same as in plant
% eulIC_rad     = [0, 0.1, 0.1];   % [rad], in the rotated frame (not bdy or NED)
% quatIC_na = eul2quat(eulIC_rad, "ZYX");
% quatRotIC_na = quatmultiply(quatIC_na, [0.7071, 0, 0.7071, 0]);
% P.icParams.eul_rad = quat2eul(quatRotIC_na, "ZYX");  % [rad], rotated-frame Euler angles

F.filterParams.P0 = [0 0 0; 0 0 0; 0 0 0];
F.filterParams.delx0 = [0 0 0 0 0 0 0]; % 0 errors in euler angles, 0 bias



end