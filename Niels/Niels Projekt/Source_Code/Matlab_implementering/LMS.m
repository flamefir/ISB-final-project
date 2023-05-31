function [y, e, w] = LMS(x , d , N, M, mu)
    % LMS takes 5 parameters:
    %   x:  Input signal
    %   d:  Desired signal
    %   N:  Number of samples
    %   M:  Number of filter-taps
    %   mu: Adaption stepsize
    %
    % And returns 3 vectors [y, e, w]
    %   y: Filtered signal
    %   e: Error signal
    %   w: Filter-weights
    
    w = zeros(1,M); % Weights
    y = zeros(1,N); % Filtreret signal
    e = zeros(1,N); % error-signal
    
    for n=1:N

        % Filtering
        for m=1:M
            if (n > m) 
                y(n) = y(n) + quantize(w(m)*x(n-m+1),32);
            end
            y(n) = quantize(y(n),32);
        end
        
        % Error calculation
        e(n) = quantize(d(n) - y(n),16);
        
        % Weight adaption
        for m=1:M
            if (n > m)
                w(m) = w(m) + quantize(mu*e(n)*x(n-m),32); 
            end
            w(m) = quantize(w(m),32);
        end

    end
    
end