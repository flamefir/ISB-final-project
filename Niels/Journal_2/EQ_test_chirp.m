clc; clear; close all;

%% Chirp

fs = 48000;
time = 0.05;
t = 0:1/fs:time;
f1 = 100;
f2 = 10000;
chirp_sig = chirp(t, f1, time, f2);
chirp_sig = chirp_sig *0.5;
%figure()
%plot(chirp_sig)

N = length(chirp_sig);


%% Main

fs = 48000;
fc1 = 200;
fc2 = 600;
fc3 = 2000;
fc4 = 6000;
Q = 10;
A = 0.3;

%N = 10000;

%t = [0:N-1]/fs;

%X = 2 * cos( 2 * pi * 500 * t ) +  cos( 2 * pi * 700 * t ) + cos( 3 * pi * 10000 * t )
% %sound(X,fs)
% figure()
% plot(t,X)
% grid on;
% xlabel('Tid [s]','FontSize', 15);
% ylabel('Magnitude','FontSize', 15);
% title('Tids-signalet','FontSize', 16);

%[X, fs] = audioread('lkh_plus_tone_48000hz.wav');


[ b1, a1 ] = makePeakEQ( fs, fc1, Q, A );
[ b2, a2 ] = makePeakEQ( fs, fc2, Q, A );
[ b3, a3 ] = makePeakEQ( fs, fc3, Q, A );
[ b4, a4 ] = makePeakEQ( fs, fc4, Q, A );

%figure()
%freqz( b, a, fs )
%xlim([0 0.1])

chirp_filtered = biquadFilter( b1, a1, chirp_sig );
chirp_filtered = biquadFilter( b2, a2, chirp_filtered );
chirp_filtered = biquadFilter( b3, a3, chirp_filtered );
chirp_filtered = biquadFilter( b4, a4, chirp_filtered );
chirp_filtered = quantize(chirp_filtered,16);

chirp_filtered_fft = fft(chirp_filtered, N);
f_res = fs/N;
f_axis = [0:N-1]*f_res;

figure()
subplot(2,1,1)
plot(chirp_sig);
grid on;
subplot(2,1,2)
plot(chirp_filtered);
grid on;

figure()
plot(f_axis(1:end/2),abs(chirp_filtered_fft(1:end/2)))
grid on;
xlim([0 10000]);
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Amplitude-spektrum','FontSize', 16)

%sound(Y,fs);



%% Functions

function [ b, a ] = makePeakEQ( fs, fc, Q, A )

    % fs = sampling frequency
    % fc = Center EQ frequence
    % Q = bandwidth of EQ
    % A = gain

    % Computes coefficients for peaking Equalizer
    w0 = 2 * pi * fc / fs;
    alpha = sin( w0 ) / ( 2 * Q );

    b0 = 1 + alpha * A;
    b1 = -2 * cos( w0 );
    b2 = 1 - alpha * A;

    a0 = 1 + alpha / A;
    a1 = -2 * cos( w0 );
    a2 = 1 - alpha / A;

    b = [quantize(b0,16) quantize(b1,16) quantize(b2,16)]./(a0*2); % Nominator
    a = [quantize(a0,16) quantize(a1,16) quantize(a2,16)]./(a0*2); % Denominator
end

% Based on the Audio-EQ-Cookbook:
% http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt 


function [ y ] = biquadFilter( b, a, x )
    % Biquad coefficients
    %b = [b0 b1 b2] Nominator
    %a = [a0 a1 a2] Denominator
    % x - sample input vector
    
    % Number of samples
    N = length(x);

    y = zeros(1,N)';

    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    %Performs Biquad filtering
    % IIR 2. order, Direct Form 1
    for i = 1 : N
        x0 = x(i);

        y(i) = ( b(1) * x0 + b(2) * x1 + b(3) * x2 - a(2) * y1 - a(3) * y2 ) / a(1);
        
        x2 = x1;
        x1 = x0;
        y2 = y1;
        y1 = y(i);
    end
end

function k = quantize(x, bits)

    k = round(x*2^(bits-1))*2^-(bits-1);

end