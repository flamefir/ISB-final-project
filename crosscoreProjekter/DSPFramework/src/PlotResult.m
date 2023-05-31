close all;
load('x_signal.txt')
load('y_signal.txt')

figure, 
subplot(2,1,1);
len = size(y_signal,1);
plot(x_signal(1:len))
title('Sweep input');
hold on;
subplot(2,1,2);
plot(y_signal)
title('Filtered output');
