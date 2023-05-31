close all;
load('x_signal.txt')
load('y_signal.txt')

%% Konstanter til plotvinduesstørrelser
x0=10;
y0=10;
width=1100;
height=600;
%%

%y_signal = y_signal * 2^-15;

figure, 
subplot(2,2,1:2);
len = size(y_signal,1);
plot(x_signal(1:len))
grid on
title('Sweep input (100 Hz - 10 kHz)', 'FontSize', 16)
xlabel('Samples [N]','FontSize', 15);
ylabel('Amplitude','FontSize', 15)

hold on;
subplot(2,2,3);
plot(y_signal)
grid on
title('Filtered output - Blackfin', 'FontSize', 16)
xlabel('Samples [N]','FontSize', 15);
ylabel('Amplitude','FontSize', 15)
% 
% fs = 48000;
% N = length(y_signal);
% f_res = fs/N;
% 
% f_axis = [0:N-1]*f_res;
% 
% y_out_sig = fft(y_signal, N);
% 
% figure()
% plot(f_axis(1:end/2), abs(y_out_sig(1:end/2)));
% xlim([0 10000])
% grid on






theta = 1000;
fs = 48000;
rp = 0.8; % pol-radius meget t�t ved cirkel.. (fx. 0.999)
rz = 1;

b_koeff = [1 -2*rz*cos(2*pi*theta/fs) rz^2]/2; % skalerer med 2 for at blive i (1.15) format
a_koeff = [1 -2*rp*cos(2*pi*theta/fs) rp^2]/2;
bq = round(b_koeff*2^15)*2^-15
aq = round(a_koeff*2^15)*2^-15

% filteredAudio = filter(bq, aq, x_signal);
% figure();
% subplot(2,1,1);
% len = size(y_signal,1);
% plot(x_signal(1:len))
% title('Sweep input');
% grid on;
hold on;
subplot(2,2,4);
plot(filteredAudio)
title('Filtered output - Matlab', 'FontSize', 16)
xlabel('Samples [N]','FontSize', 15);
ylabel('Amplitude','FontSize', 15)
grid on


set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'matlab_vs_blackfin.png')

%%

diffAudio = filteredAudio(1: end - 1) - y_signal;

subplot(2,1,1);
plot(diffAudio)
title('Differens mellem de to signaler', 'FontSize', 16)
xlabel('Samples [N]','FontSize', 15);
ylabel('Amplitude','FontSize', 15)
grid on



subplot(2,1,2);
plot(diffAudio)
title('Differens mellem de to signaler, ny skala', 'FontSize', 16)
ylim([-3*10^4 3*10^4])
xlabel('Samples [N]','FontSize', 15);
ylabel('Amplitude','FontSize', 15)
grid on

set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'differens_matlab_vs_blackfin.png')