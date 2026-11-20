simBias = out.simBias;

t = simBias.Time;
b = squeeze(simBias.Data);

figure;
plot(t, b);
xlabel('Time (s)');
ylabel('Bias (m/s^2)');
title('Simulated Accelerometer Bias');
legend('X', 'Y', 'Z');
grid on;


% Model parameters
Ts = 0.01;
tau = 200;
a = exp(-Ts/tau);

% Experimental PSD coefficients
K = [7.0144e-9, 6.6878e-9, 2.6823e-9];

% Random-walk diffusion strength
q = 2*pi^2*K;

% Recover the Gauss-Markov driving noise
epsilon = b(2:end,:) - a*b(1:end-1,:);

% Expected variance of innovations
expectedVar = q*tau/2*(1-a^2);

% Measured variance
measuredVar = var(epsilon, 0, 1);

% Compare
results = table( ...
    ["X";"Y";"Z"], ...
    expectedVar', measuredVar', ...
    (measuredVar'./expectedVar'), ...
    'VariableNames', ...
    {'Axis','ExpectedVariance','MeasuredVariance','Ratio'});

disp(results);