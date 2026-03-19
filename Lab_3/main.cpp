#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdexcept>
#include <windows.h>

#include "Field.h"
#include "Fifteen.h"
#include "Statistic.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    setlocale(LC_ALL, "Russian");
    std::cout << "Игра Пятнашки\n";
    std::cout << "Управление: стрелки, ESC для выхода\n";

    int sz = 0;
    while (sz <= 0) {
        std::cout << "Введите размер поля (положительное число, например 3 или 4): ";
        std::cin >> sz;
        if (std::cin.fail() || sz <= 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод. Попробуйте снова.\n";
            sz = 0;
        }
    }
    std::cin.ignore();

    try {
        Fifteen game(sz);
        game.run();

        int key;
        bool gameOver = false;

        while (!gameOver) {
            for (int i = 0; i < 50; ++i) std::cout << '\n';

            game.draw();
            std::cout << "Ходов: " << game.getCount() << "\n";

            key = _getch();
            if (key == 224) {
                key = _getch();
                game.onKeyPressed(key);
            }
            else if (key == 27) { // ESC
                break;
            }

            gameOver = game.isGameOver();
            if (gameOver) {
                for (int i = 0; i < 50; ++i) std::cout << '\n';
                game.draw();
                std::cout << "\nПОБЕДА! Вы собрали головоломку за " << game.getCount() << " ходов.\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nДля Statistic\n";
    int arr[] = { 1, 2, 3, 4, 5 };
    Statistic stat1(arr, 5);
    std::cout << "stat1: ";
    stat1.print();

    Statistic stat2(stat1);
    std::cout << "stat2 (копия): ";
    stat2.print();

    Statistic stat3("10 20 30 40");
    std::cout << "stat3 (из строки): ";
    stat3.print();

    stat1 = stat3;
    std::cout << "stat1 после присваивания stat3: ";
    stat1.print();

    return 0;
}