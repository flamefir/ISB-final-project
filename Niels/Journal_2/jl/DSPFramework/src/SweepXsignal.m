clc;
clear;
close all;
% Creates a sweep from 500Hz to 2000Hz in 50 ms 
fs = 48000; % Samplings frequency
time = 0.05; % Sec, equal to 2400 samples
t = 0:1/fs:time;
f1 = 100; % Hz
f2 = 10000; % Hz
y = chirp(t, f1, time, f2);
y = y.*0.7; % Gain 0.9
plot(y);

% gem i fil
y16 = y*2^15;
fid = fopen('x_signal.txt', 'w');
for i=1:length(y16)
    xtext = num2str(round(y16(i)));
    fprintf(fid, '%s,\r\n', xtext);
end
fclose(fid);
