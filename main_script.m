% --- Ввод данных ---
mode = input('Выберите режим (1 - вручную, 2 - рандом): ');

if mode == 1
    x = input('Введите вектор x (например, [157, 5054, 25789, 13214]): ');
    if length(x) ~= 4
        error('Вектор x должен содержать ровно 4 элемента!');
    end
elseif mode == 2
    min_x = input('Минимальное значение x: ');
    max_x = input('Максимальное значение x: ');
    if max_x - min_x < 3
        error('Диапазон менее 4 чисел!');
    end
    x = randi([min_x, max_x], 1, 4);
    fprintf('Сгенерированный x: [%d %d %d %d]\n', x);
else
    error('Некорректный режим!');
end

% --- Поиск параметров ---
found = false;
for m = max(x)+1 : 65535
    d1 = mod(x(2)-x(1),m);
    d2 = mod(x(3)-x(2),m);
    d3 = mod(x(4)-x(3),m);

    % Проверяем, обратимы ли d1 и d2 по модулю m
    if gcd(d1,m)==1 && gcd(d2,m)==1
        inv_d1 = modinv(d1,m);
        inv_d2 = modinv(d2,m);

        A_candidate1 = mod(d2 * inv_d1, m);
        A_candidate2 = mod(d3 * inv_d2, m);

        if A_candidate1 == A_candidate2
            A=A_candidate1;
            C=mod(x(2)-A*x(1),m);

            % Проверка на известных четырёх
            if mod(A*x(3)+C,m)==x(4)
                next_x=mod(A*x(4)+C,m);
                fprintf('m=%d, A=%d, C=%d\n',m,A,C);
                fprintf('Следующее число: %d\n',next_x);
                found = true;
                break;
            end
        end
    end
end


if ~found
    disp('Решение не найдено в диапазоне m = max(x)+1..65535.');
end
