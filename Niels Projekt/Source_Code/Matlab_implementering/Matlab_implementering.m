clc; clear; close all;
%% Konstanter til plotvinduesstørrelser
x0=10;
y0=10;
width=1100;
height=600;

%% Path-estimering: White noise generator
fs = 48000;                 % Samplingsfrekvens
N = 1024;                   % Antal samples
N_s = 20000;                % Antal samples til path-estimering
n = 1:N;                    % Sample
n_s = 1:N_s;                 % Sample til path
f_res = fs/N;               % Frekvensopløsning
f_res_s = fs/N_s;           % Frekvensopløsning til path
f_axis = [0:N-1]*f_res;     % Frekvensakse
f_axis_s = [0:N_s-1]*f_res_s; % Frekvensakse

%%
% Generer hvid støj mellem 150Hz og 2000Hz
x = randn(1,N_s);
x = bandpass(x,[150,2000],fs);

% Fast-fourier-transformation af støjen
X = fft(x, N_s);

% Plot af signalet og dets frekvensspektrum
figure()
subplot(2,1,1)
plot(n_s,x)
grid on;
xlabel('n','FontSize', 15);
ylabel('x(n)','FontSize', 15);
title('Signal','FontSize', 16);
subplot(2,1,2)
plot(f_axis_s(1:end/2), abs(X(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Frekvensspektrum','FontSize', 16)
xlim([0 2500])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'White_nose_generator.png');

%% Path-estimering: LMS
M = 20;        % et M-tap filter
mu = 0.002;     % stepsize
help LMS
[y, e, w] = LMS(x, x, N_s, M, mu);

%% Path-estimering: Plot af LMS
figure()
plot(n_s,x)
hold on;
plot(n_s,y)
plot(n_s,e)
legend('x(t)', 'y(t)', 'e(t)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('Path-estimering: LMS','FontSize', 16);
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'path_est_LMS.png');

%% Path-estimering: Plot af estimeret filter
figure()
stem(w)
grid on;
xlabel('m','FontSize', 15);
ylabel('w(m)','FontSize', 15);
title('Path-estimering: Filter-weights','FontSize', 16);
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'path_est_weights.png');

%% Path-estimering: Plot af frekvensresponset for estimeret filter
figure()
freqz(w,1,20000,'half',fs)
title('Path-estimering: Frekvensrespons', 'FontSize', 16)
grid on;
xlim([0 2000])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'path_est_freqz.png');

%% ANC: Støjsignalet

t = [0:N-1]/fs;
x_noise = 0.5*(sin(2*pi*500*t) + sin(2*pi*200*t));
X_noise = fft(x_noise, N);


figure()
subplot(2,1,1)
plot(n,x_noise)
xlim([0 N])
grid on;
xlabel('n','FontSize', 15);
ylabel('x_{noise}','FontSize', 15);
title('Noisy signal','FontSize', 16);
subplot(2,1,2)
plot(f_axis(1:end/2), abs(X_noise(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Amplitude-spektrum','FontSize', 16)
xlim([0 N])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'noise_signal.png');

%% ANC: LMS 50 taps

M = 50;         % et M-tap filter
mu = 0.001;     % stepsize
[y, e, w] = LMS(x_noise, -x_noise, N, M, mu);

%% ANC: Plot af LMS 50 taps
figure()
plot(n,x_noise, 'b')
hold on;
plot(n,y, 'r')
plot(n,e,'y', 'LineWidth',2)
legend('x(n)', 'y(n)', 'e(n)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('ANC: LMS 50 taps','FontSize', 16);
xlim([0 N])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'ANC_LMS_50_taps.png');

%% Plot af filter-weights 50 taps
figure()
stem(w)
grid on;
xlabel('m','FontSize', 15);
ylabel('w(m)','FontSize', 15);
title('ANC: Filter-weights 50 taps','FontSize', 16);
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'anc_weights_50_taps.png');


%% ANC: LMS 100 taps

M = 100;         % et M-tap filter
mu = 0.001;     % stepsize
[y, e, w] = LMS(x_noise, -x_noise, N, M, mu);

e_rms = rms(e(500:end))

%% ANC: Plot af LMS 100 taps
figure()
plot(n,x_noise, 'b')
hold on;
plot(n,y, 'r')
plot(n,e,'y', 'LineWidth',2)
legend('x(n)', 'y(n)', 'e(n)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('ANC: LMS 100 taps','FontSize', 16);
xlim([0 N])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'ANC_LMS_100_taps.png');

%% Plot af filter-weights 100 taps
figure()
stem(w)
grid on;
xlabel('m','FontSize', 15);
ylabel('w(m)','FontSize', 15);
title('ANC: Filter-weights 100 taps','FontSize', 16);
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'anc_weights_100_taps.png');

%% ANC: LMS 200 taps

M = 200;         % et M-tap filter
mu = 0.001;     % stepsize
[y, e, w] = LMS(x_noise, -x_noise, N, M, mu);

e_rms = rms(e(500:end))

%% ANC: Plot af LMS 200 taps
figure()
plot(n,x_noise, 'b')
hold on;
plot(n,y, 'r')
plot(n,e,'y', 'LineWidth',2)
legend('x(n)', 'y(n)', 'e(n)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('ANC: LMS 200 taps','FontSize', 16);
xlim([0 N])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'ANC_LMS_200_taps.png');

%% Plot af filter-weights 200 taps
figure()
stem(w)
grid on;
xlabel('m','FontSize', 15);
ylabel('w(m)','FontSize', 15);
title('ANC: Filter-weights 200 taps','FontSize', 16);
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'anc_weights_200_taps.png');

%% Airplane noise
[y,Fs] = audioread('Airplane.mp3');
audiowrite('Airplane_48k.wav', y, fs);
[x_plane,fs_plane] = audioread('Airplane_48k.wav');

x_plane = x_plane(1:end);

N_plane = length(x_plane);

%% ANC airplane frekvensrespons
f_res_plane = fs_plane/N_plane;           % Frekvensopløsning til path
f_axis_plane = [0:N_plane-1]*f_res_plane;     % Frekvensakse

% Fast-fourier-transformation af støjen
X = fft(x_plane, N_plane);

% Plot af signalet og dets frekvensspektrum
n = 1:N_plane;
figure()
subplot(2,1,1)
plot(n,x_plane)
grid on;
xlabel('n','FontSize', 15);
ylabel('x(n)','FontSize', 15);
title('Signal','FontSize', 16);
subplot(2,1,2)
plot(f_axis_plane(1:end/2), abs(X(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Frekvensspektrum','FontSize', 16)
xlim([0 2500])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'cafe_noise_signal.png');

%% ANC Airplane: LMS 200 taps

M = 200;        % et M-tap filter
mu = 0.001;     % stepsize
[y, e, w] = LMS(x_plane, -x_plane, N_plane, M, mu);

%% ANC Airplane: Plot af LMS 200 taps
n = 1:N_plane;
figure()
plot(n,x_plane, 'b', 'LineWidth',1)
hold on;
plot(n,y, 'r', 'LineWidth',1)
plot(n,e,'y', 'LineWidth',2)
legend('x(n)', 'y(n)', 'e(n)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('ANC of airplane noise: LMS 200 taps','FontSize', 16);
xlim([0 N_plane])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'ANC_airplane_LMS_200_taps.png');

%%
sound(x_plane(1:end/5),fs)
audiowrite('airplane_no_ANC.wav',x_plane,fs)
%%
sound(e(1:end/5),fs)
audiowrite('airplane_ANC.wav',e,fs)

%% ANC Airplane, ZOOM: Plot af LMS 200 taps
n = 1:N_plane;
figure()
plot(n,x_plane, 'b', 'LineWidth',1)
hold on;
plot(n,y, 'r', 'LineWidth',1)
plot(n,e,'y', 'LineWidth',2)
legend('x(n)', 'y(n)', 'e(n)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('ANC of airplane noise: LMS 200 taps, Zoom','FontSize', 16);
xlim([10000 11000])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'ANC_zoom_airplane_LMS_200_taps.png');

%% ANC Airplane: LMS 50 taps

M = 50;        % et M-tap filter
mu = 0.001;     % stepsize
[y, e, w] = LMS(x_plane, -x_plane, N_plane, M, mu);

%% ANC Airplane: Plot af LMS 50 taps
n = 1:N_plane;
figure()
plot(n,x_plane, 'b', 'LineWidth',1)
hold on;
plot(n,y, 'r', 'LineWidth',1)
plot(n,e,'y', 'LineWidth',2)
legend('x(n)', 'y(n)', 'e(n)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('ANC of airplane noise: LMS 50 taps','FontSize', 16);
xlim([0 N_plane])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'ANC_airplane_LMS_50_taps.png');

%%
sound(x_plane(1:end/5),fs)
%%
sound(e(1:end/5),fs)

%% ANC airplane, ZOOM: Plot af LMS 50 taps
n = 1:N_plane;
figure()
plot(n,x_plane, 'b', 'LineWidth',1)
hold on;
plot(n,y, 'r', 'LineWidth',1)
plot(n,e,'y', 'LineWidth',2)
legend('x(n)', 'y(n)', 'e(n)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('ANC of airplane noise: LMS 50 taps, Zoom','FontSize', 16);
xlim([10000 11000])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'ANC_zoom_airplane_LMS_50_taps.png');