% Eksempel p� koefficient kvantisering

clear
close all;

% frekvens som skal fjernes..
theta = 1000;
fs = 48000;
rp = 0.8; % pol-radius meget t�t ved cirkel.. (fx. 0.999)
rz = 1;

b = [1 -2*rz*cos(2*pi*theta/fs) rz^2]/2 % skalerer med 2 for at blive i (1.15) format
a = [1 -2*rp*cos(2*pi*theta/fs) rp^2]/2
%bq = round(b*2^7)*2^-7;
%aq = round(a*2^7)*2^-7;
%Koefficienter benyttet til test af IIRFilter
bq = round(b*2^15)*2^-15;
aq = round(a*2^15)*2^-15;

% pol-nulpunkter
figure, zplane([roots(b) roots(bq)],[roots(a) roots(aq)] )

% freq respons
[f, h]=freqz(b, a, 10000, fs);
[fq, hq]=freqz(bq, aq, 10000, fs);
figure, plot(h, abs(f)), hold on, plot(hq, abs(fq), 'r')
title('Frequency response (blue) with coefficient quatization (red)');



