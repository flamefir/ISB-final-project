clc; clear; close all;
%% Støjsignalet
fs = 8000;

N = 1024*1;

t = [0:N-1]/fs;

x = 0.2 * cos( 2 * pi * 600 * t ) +  0.5 * cos( 2 * pi * 200 * t ) + 0.2* cos( 2 * pi * 1000 * t );

% Frekvensopløsning
f_res = fs/N;

% Frekvensakse
f_axis = [0:N-1]*f_res;

X = fft(x, N);

figure()
subplot(2,1,1)
plot(t,x)
grid on;
xlabel('Tid [s]','FontSize', 15);
ylabel('x','FontSize', 15);
title('Signal','FontSize', 16);
subplot(2,1,2)
plot(f_axis(1:end/2), abs(X(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Amplitude-spektrum','FontSize', 16)
xlim([0 1500])

%% LMS
M = 100; % et M-tap filter
u = 0.004; % stepsize
w = zeros(1,M); % Weights
y = zeros(1,N); % Filtreret signal
e = zeros(1,N); % error-signal
for n=1:N
    
    % FIR filter input vector
    for l=1:M
        if (n > l) 
            y(n) = y(n) + w(l)*x(n-l+1);
        end
    end
    
    % Estimate error
    e(n) = -x(n) - y(n);
    
    % Adjust weights
    for k=1:M
        if (n > k)
            w(k) = w(k) + 2*u*e(n)*x(n-k); 
        end
    end
    
end
%%
figure()
plot(t,x)
hold on;
plot(t,y)
plot(t,e)
legend('x(t)', 'y(t)', 'e(t)')
grid on;
xlabel('Time [s]','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('Signal','FontSize', 16);
% subplot(2,1,2)
% plot(t,y)
% grid on;
% xlabel('Tid [s]','FontSize', 15);
% ylabel('y','FontSize', 15);
% title('Filtered signal','FontSize', 16);
% subplot(2,1,2)
% plot(t,e)
% grid on;
% xlabel('Tid [s]','FontSize', 15);
% ylabel('e = x + y','FontSize', 15);
% title('error signal','FontSize', 16);
