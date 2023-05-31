clc; clear; close all;
%%
fs = 48000;

N = 1024;

t = [0:N-1]/fs;

x = 0.2 * cos( 2 * pi * 5000 * t ) +  0.5 * cos( 2 * pi * 9375 * t ) + 0.2* cos( 2 * pi * 1000 * t );
%sound(X,fs)
figure()
plot(t,x)
grid on;
xlabel('Tid [s]','FontSize', 15);
ylabel('x_signal','FontSize', 15);
title('Tids-signalet','FontSize', 16);

% Frekvensopløsning
f_res = fs/N;

% Frekvensakse
f_axis = [0:N-1]*f_res;

X = fft(x, N);

figure()
plot(f_axis(1:end/2), abs(X(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Amplitude-spektrum','FontSize', 16)
%xlim([0 ])

x16 = x*2^15;
fid = fopen('x_signal.txt','w');
for i=1:length(x16)
    xtext = num2str(round(x16(i)));
    fprintf(fid, '%s,\r\n', xtext);
end
fclose(fid);

%%
load('y_signal.txt');
load('fft_mag.txt');

figure()
subplot(2,1,1)
plot(t,x)
grid on;
xlabel('Tid [s]','FontSize', 15);
ylabel('x','FontSize', 15);
title('input','FontSize', 16);
subplot(2,1,2)
plot(t,y_signal)
grid on;
xlabel('Tid [s]','FontSize', 15);
ylabel('y_{signal}','FontSize', 15);
title('output','FontSize', 16);

%%
figure()
subplot(2,1,1)
plot(f_axis(1:end/2), abs(X(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Amplitude-spektrum - Input','FontSize', 16)
xlim([0 15000])
subplot(2,1,2)
plot(f_axis(1:end/2), abs(fft_mag(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Amplitude-spektrum - fft_{mag}','FontSize', 16)
xlim([0 15000])

Y = fft(y_signal,N);

figure()
subplot(2,1,1)
plot(f_axis(1:end/2), abs(Y(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Y','FontSize', 16)
xlim([0 15000])
subplot(2,1,2)
plot(f_axis(1:end/2), abs(fft_mag(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Amplitude-spektrum','FontSize', 16)
xlim([0 15000])



%%
a = [1 -0.64 0.902]
b = [1 -0.673 1]

freqz(b, a, N, 'half', fs)

