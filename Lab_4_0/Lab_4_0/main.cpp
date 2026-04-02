#include <iostream>
#include <windows.h>
#include "Radio.h"
#include "Field.h"
#include "Statistic.h"

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Задача 1: Radio
    std::cout << "=== Радио ===" << std::endl;
    Radio r;
    std::cout << "Начальная станция: " << r.getStation() << std::endl;
    ++r;
    std::cout << "После префиксного ++: " << r.getStation() << std::endl;
    r++;
    std::cout << "После постфиксного ++: " << r.getStation() << std::endl;
    --r;
    std::cout << "После префиксного --: " << r.getStation() << std::endl;
    r--;
    std::cout << "После постфиксного --: " << r.getStation() << std::endl;

    // Задача 2: Field
    std::cout << "\n=== Поле ===" << std::endl;
    std::vector<int> tiles1 = { 1,2,3,4,5,6,7,8,0 };
    Field f1(3, 3, tiles1, 2, 2);
    Field f2(3, 3, tiles1, 2, 2);
    Field f3(3, 3, tiles1, 1, 1);
    std::cout << "f1 == f2: " << (f1 == f2 ? "истина" : "ложь") << std::endl;
    std::cout << "f1 != f2: " << (f1 != f2 ? "истина" : "ложь") << std::endl;
    std::cout << "f1 == f3: " << (f1 == f3 ? "истина" : "ложь") << std::endl;
    std::cout << "f1 != f3: " << (f1 != f3 ? "истина" : "ложь") << std::endl;

    // Задача 3: Statistic operator[]
    std::cout << "\n=== Статистика: оператор [] ===" << std::endl;
    Statistic stat("12 34 56 13 43");
    try {
        std::cout << "stat[0] = " << stat[0] << std::endl;
        std::cout << "stat[4] = " << stat[4] << std::endl;
        std::cout << "stat[100] = " << stat[100] << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Перехвачено исключение: " << e.what() << std::endl;
    }

    // Задача 4: getSlice и operator+=
    std::cout << "\n=== Статистика: getSlice и operator+= ===" << std::endl;
    Statistic stat2("10 20 30 40 50 60 70");
    try {
        Statistic slice = stat2.getSlice(1, 3);
        std::cout << "Срез (1,3): ";
        for (size_t i = 0; i < slice.size(); ++i) {
            std::cout << slice[i] << " ";
        }
        std::cout << std::endl;

        Statistic stat3("100 200");
        stat3 += slice;
        std::cout << "После +=: ";
        for (size_t i = 0; i < stat3.size(); ++i) {
            std::cout << stat3[i] << " ";
        }
        std::cout << std::endl;

        Statistic badSlice = stat2.getSlice(5, 2);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено invalid_argument: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Перехвачено out_of_range: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Перехвачено исключение: " << e.what() << std::endl;
    }

    try {
        Statistic stat4("1 2 3");
        Statistic slice2 = stat4.getSlice(0, 5);
    }
    catch (const std::exception& e) {
        std::cout << "Перехвачено исключение (выход за границы): " << e.what() << std::endl;
    }

    return 0;
}