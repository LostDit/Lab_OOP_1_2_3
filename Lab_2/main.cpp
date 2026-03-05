#include "Radio.cpp"
#include "Statistic.cpp"
#include <iostream>
#include <string>

int main() {
    // Задача 1: Radio (используем std::cin для ввода команд, т.к. conio.h не кросс-платформенный)
    Radio radio;
    std::cout << "Initial volume: " << radio.getVolume() << ", Station: " << radio.getStation() << std::endl;
    std::cout << "Commands: w - inc volume, s - dec volume, d - next station, a - prev station, q - quit" << std::endl;
    std::string command;
    while (std::cin >> command && command != "q") {
        if (command == "w") radio.incVolume();
        else if (command == "s") radio.decVolume();
        else if (command == "d") radio.nextStation();
        else if (command == "a") radio.previousStation();
        std::cout << "Volume: " << radio.getVolume() << ", Station: " << radio.getStation() << std::endl;
    }

    // Задача 3: Statistic
    std::vector<int> data = {8, 15, 13, 15, 17, 20, 19, 20, 7, 14, 14, 18};
    Statistic stat(data);
    std::cout << "Сумма за период времени равна: " << stat.sum_sales() << std::endl;
    std::cout << "Среднее значение продаж: " << stat.average_sales() << std::endl;
    std::cout << "Количество месяцев ниже среднего: " << stat.months_sales_below_average() << std::endl;
    std::cout << "Количество месяцев выше среднего: " << stat.months_sales_above_average() << std::endl;
    std::cout << "Месяцы с максимальными продажами: ";
    auto maxMonths = stat.max_sales();
    for (int m : maxMonths) std::cout << m << " ";
    std::cout << std::endl;
    std::cout << "Месяцы с минимальными продажами: ";
    auto minMonths = stat.min_sales();
    for (int m : minMonths) std::cout << m << " ";
    std::cout << std::endl;

    // Меню для выбора метода (по желанию)
    int choice;
    do {
        std::cout << "Statistic menu:\n1: Sum\n2: Average\n3: Exit\nChoice: ";
        std::cin >> choice;
        if (choice == 1) std::cout << "Sum: " << stat.sum_sales() << std::endl;
        else if (choice == 2) std::cout << "Average: " << stat.average_sales() << std::endl;
    } while (choice != 3);

    return 0;
}