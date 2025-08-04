% Функция для поиска обратного элемента по модулю
function y=modinv(a,m)
    [g,u,v]=gcd(a,m);
    if g==1
        y=mod(u,m);
    else
        y=NaN;
    end
end