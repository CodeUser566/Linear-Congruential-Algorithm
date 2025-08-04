#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>

//возвращает gcd(a,b) и коэффициенты x,y такие, что a*x + b*y = gcd(a,b)
long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return std::llabs(a);
    }
    long long x1, y1;
    long long g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Обратный элемент a^(-1) по модулю m, если он существует; иначе возвращаем 0 и ставим flag=false
long long modinv(long long a, long long m, bool &flag) {
    long long x, y;
    long long g = ext_gcd(a, m, x, y);
    if (g != 1) {
        flag = false;
        return 0;
    }
    flag = true;
    long long inv = x % m;
    if (inv < 0) inv += m;
    return inv;
}

int main() {
    std::srand(std::time(nullptr));

    std::vector<long long> x(4);
    int mode;
    std::cout << "Режим (1 - вручную, 2 - рандом): ";
    std::cin >> mode;
    if (mode == 1) {
        std::cout << "Введите 4 числа, разделённые пробелом: ";
        for (int i = 0; i < 4; ++i) {
            std::cin >> x[i];
        }
    }
    else if (mode == 2) {
        long long mn, mx;
        std::cout << "Минимальное значение для генерации: ";
        std::cin >> mn;
        std::cout << "Максимальное значение для генерации: ";
        std::cin >> mx;
        if (mx - mn < 3) {
            std::cerr << "Диапазон должен содержать как минимум 4 числа!\n";
            return 1;
        }
        for (int i = 0; i < 4; ++i) {
            x[i] = mn + std::rand() % (mx - mn + 1);
        }
        std::cout << "Сгенерированный вектор x: [";
        for (int i = 0; i < 4; ++i) {
            std::cout << x[i] << (i < 3 ? ", " : "");
        }
        std::cout << "]\n";
    }
    else {
        std::cerr << "Неверный режим\n";
        return 1;
    }

    long long x_max = *std::max_element(x.begin(), x.end());
    bool found = false;
    long long final_m = 0, final_A = 0, final_C = 0, next_x = 0;

    for (long long m = x_max + 1; m <= 65535; ++m) {
        long long d1 = (x[1] - x[0]) % m; if (d1 < 0) d1 += m;
        long long d2 = (x[2] - x[1]) % m; if (d2 < 0) d2 += m;
        long long d3 = (x[3] - x[2]) % m; if (d3 < 0) d3 += m;

        // проверяем обратимость d1 и d2
        long long g1 = std::gcd(d1, m);
        long long g2 = std::gcd(d2, m);
        if (g1 != 1 || g2 != 1) continue;

        bool ok1, ok2;
        long long inv1 = modinv(d1, m, ok1);
        long long inv2 = modinv(d2, m, ok2);
        if (!ok1 || !ok2) continue;

        long long A1 = (d2 * inv1) % m;
        long long A2 = (d3 * inv2) % m;
        if (A1 != A2) continue;
        long long A = A1;

        // находим C
        long long C = (x[1] - A * x[0]) % m;
        if (C < 0) C += m;

        // проверка на третьем элементе
        if ((A * x[2] + C) % m != x[3] % m) continue;

        // нашли решение
        final_m = m;
        final_A = A;
        final_C = C;
        next_x = (A * x[3] + C) % m;
        found = true;
        break;
    }

    if (found) {
        std::cout << "Найдены параметры:\n";
        std::cout << "  m = " << final_m << "\n";
        std::cout << "  A = " << final_A << "\n";
        std::cout << "  C = " << final_C << "\n";
        std::cout << "Следующее число: " << next_x << "\n";
    }
    else {
        std::cout << "Решение не найдено в диапазоне m = max(x)+1..65535\n";
    }

    return 0;
}
