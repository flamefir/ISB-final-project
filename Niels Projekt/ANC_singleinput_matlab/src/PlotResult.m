clc; clear; close all;
%% Konstanter til plotvinduesstørrelser
x0=10;
y0=10;
width=1100;
height=600;
%% Load filer
load('x_signal.txt')
load('y_signal.txt')
load('w_signal.txt')
load('e_signal.txt')

%%
n = 1:size(x_signal,1);
figure()
plot(n,x_signal*2^-15,'b')
hold on;
plot(n,y_signal*2^-15, 'r')
plot(n,e_signal*2^-15, 'y', 'LineWidth',2)
legend('x(n)', 'y(n)', 'e(n)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('ANC: Blackfin LMS','FontSize', 16);
xlim([0 1024])
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'ANC_Blackfin.png');

%% Plot af filter weights
figure()
stem(w_signal(1:50)*2^-15)
grid on;
xlabel('m','FontSize', 15);
ylabel('w(m)','FontSize', 15);
title('ANC: Blackfin weights','FontSize', 16);
set(gcf,'position',[x0,y0,width,height])
saveas(gcf,'weights_blackfin_ANC.png');

h = myd2h(w_signal(1),1,15)
myh2d(h,1,15)