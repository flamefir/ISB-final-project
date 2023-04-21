clc; clear; close all;

%%
% Note til hastighed. Lyd rejser med 343 m/s, dvs. hvis lyden skal rejse
% 20mm mellem ref-mic og loud-speaker, så tager det 0.058ms,
% dvs. at vi skal spytte 1s/0.000058s = 17200 samples ud i sekundet.
%% Active noise cancelling
%              +-----------+                       +   
% x(k) ---+--->|   P(z)    |--yp(k)----------------> sum --+---> e(k)
%         |    +-----------+                          ^-   |
%         |                                           |    |
%         |        \                                ys(k)  |     
%         |    +-----------+          +-----------+   |    |
%         +--->|   W(z)    |--yw(k)-->|   S(z)    |---+    |
%         |    +-----------+          +-----------+        |
%         |            \                                   |
%         |             \----------------\                 |
%         |                               \                |
%         |    +-----------+          +-----------+        |
%         +--->|   Sh(z)   |--xs(k)-->|   LMS     |<-------+
%              +-----------+          +-----------+        
% 
%% White noise generator
fs = 8000;              % Samplingsfrekvens
N = 20000;              % Antal samples
n = 1:N;                % Sample
f_res = fs/N;           % Frekvensopløsning
f_axis = [0:N-1]*f_res; % Frekvensakse

% Generer hvid støj mellem 150Hz og 2000Hz
x = randn(1,N);
x = bandpass(x,[150,2000],fs);

% Fast-fourier-transformation af støjen
X = fft(x, N);

% Plot af signalet og dets frekvensspektrum
figure()
subplot(2,1,1)
plot(n,x)
grid on;
xlabel('n','FontSize', 15);
ylabel('x(n)','FontSize', 15);
title('Signal','FontSize', 16);
subplot(2,1,2)
plot(f_axis(1:end/2), abs(X(1:end/2)))
grid on;
xlabel('Frekvens [Hz]','FontSize', 15)
ylabel('Magnitude','FontSize', 15)
title('Frekvensspektrum','FontSize', 16)
xlim([0 2500])

%% LMS
M = 100;        % et M-tap filter
u = 0.001;      % stepsize
%eps = 0.5;
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
    e(n) = x(n) - y(n);
    
    % Adjust weights
    for k=1:M
        if (n > k)
            %w(k) = w(k) + (1/(x(n-k)'*x(n-k)+eps))*u*e(n)*x(n-k); 
            w(k) = w(k) + 2*u*e(n)*x(n-k);
        end
    end 
end
%%
n = 1:N;
figure()
plot(n,x)
hold on;
plot(n,y)
plot(n,e)
legend('x(t)', 'y(t)', 'e(t)')
grid on;
xlabel('n','FontSize', 15);
ylabel('Amplitude','FontSize', 15);
title('Signal','FontSize', 16);

%sound(e,fs)