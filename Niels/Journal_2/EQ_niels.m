clc; clear; close all;

%% Main

fs = 15000;
fc = 10000;
Q = 5;
A = 2;

N = 10000;

t = [0:N-1]/fs;

X = 2 * cos( 2 * pi * 500 * t ) +  cos( 2 * pi * 700 * t ) + cos( 3 * pi * 10000 * t )
%sound(X,fs)
figure()
plot(t,X)
grid on;
xlabel('Tid [s]','FontSize', 15);
ylabel('Magnitude','FontSize', 15);
title('Tids-signalet','FontSize', 16);

%[X, fs] = audioread('lkh_plus_tone_48000hz.wav');


[ b, a ] = makePeakEQ( fs, fc, Q, A );

figure()
freqz( b, a, fs )
%xlim([0 0.1])

Y = biquadFilter( b, a, X );
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

    b = [b0 b1 b2]; % Nominator
    a = [a0 a1 a2]; % Denominator
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
