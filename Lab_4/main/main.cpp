#include <iostream>
#include "Radio.h"
#include "Field.h"
#include "Fifteen.h"
#include "Statistic.h"

int main() {
    Radio r;
    r.addStation("Европа Плюс");
    r.addStation("Русское Радио");
    r.addStation("Авторадио");
    std::cout << "=== Radio ===\n";
    r.showCurrent();
    ++r;
    r.showCurrent();
    r--;
    r.showCurrent();

    std::cout << "\n=== Statistic ===\n";
    Statistic stat("10 20 30 40 50");
    std::cout << "Исходная статистика: " << stat;

    std::cout << "stat[2] = " << stat[2] << "\n";
    stat[2] = 99;
    std::cout << "После stat[2]=99: " << stat;

    try {
        Statistic slice = stat.getSlice(1, 3);
        std::cout << "Срез [1..3]: " << slice;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }

    Statistic stat2("5 6 7");
    stat += stat2;
    std::cout << "После +=: " << stat;

    stat.deleteSlice(0, 2);
    std::cout << "После удаления [0..2]: " << stat;

    Statistic a("1 2 3");
    Statistic b("3 1 2");
    std::cout << "a == b ? " << (a == b ? "Правда" : "Ложь") << "\n";

    Statistic c("10 20 30 40 50 60");
    Statistic slice2 = c[1][3];
    std::cout << "c[1][3] = " << slice2;

    return 0;
}