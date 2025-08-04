% Данные
x = [157, 5054, 25789, 13214];

% Перебор возможных значений m от max(x)+1 до 65535 (минимум должен быть больше всех чисел
for m = max(x)+1:65535
    d1 = mod(x(2)-x(1),m);
    d2 = mod(x(3)-x(2),m);
    d3 = mod(x(4)-x(3),m);

% Проверяем обратимость d1 и d2 по модулю m для поиска A через обратный элемент
    if gcd(d1,m)==1 && gcd(d2,m)==1
        
        % Находим обратный элемент по модулю для d1 и d2
        inv_d1 = modinv(d1,m);
        inv_d2 = modinv(d2,m);

        % Находим кандидатов на A по двум способам:
        A_candidate1 = mod(d2 * inv_d1, m);
        A_candidate2 = mod(d3 * inv_d2, m);

        if A_candidate1 == A_candidate2
            A=A_candidate1;

            %Находим С
            C=mod(x(2)-A*x(1),m);

            % Проверим на всех известных числах:
            if mod(A*x(3)+C,m)==x(4)
                next_x=mod(A*x(4)+C,m);
                fprintf('m=%d, A=%d, C=%d\n',m,A,C);
                fprintf('Следующее число: %d\n',next_x);
                break;
            end
        end
    end
end