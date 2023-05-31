function k = quantize(x, bits)

    k = round(x*2^(bits-1))*2^-(bits-1);

end