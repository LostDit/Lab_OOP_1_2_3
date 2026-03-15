#include <iostream>
#include <conio.h>   // для _getch()
#include <cstdlib>   // для system

#include "Field.h"
#include "Fifteen.h"
#include "Statistic.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Игра Пятнашки\n";
    std::cout << "Управление: стрелки, ESC для выхода\n";
    std::cout << "Введите размер поля (например, 3 или 4): ";
    int sz;
    std::cin >> sz;
    std::cin.ignore();

    Fifteen game(sz);
    game.run();

    int key;
    bool gameOver = false;

    while (!gameOver) {
        system("cls"); // очистка экрана (для Windows)
        game.draw();
        std::cout << "Ходов: " << game.getCount() << "\n";

        key = _getch();
        if (key == 224) { // стрелки дают два кода
            key = _getch();
            game.onKeyPressed(key);
        } else if (key == 27) { // ESC
            break;
        }

        gameOver = game.isGameOver();
        if (gameOver) {
            system("cls");
            game.draw();
            std::cout << "\nПОБЕДА! Вы собрали головоломку за " << game.getCount() << " ходов.\n";
        }
    }

    // Демонстрация работы Statistic
    std::cout << "\n--- Тест класса Statistic ---\n";
    int arr[] = {1, 2, 3, 4, 5};
    Statistic stat1(arr, 5);
    std::cout << "stat1: ";
    stat1.print();

    Statistic stat2(stat1); // копирование
    std::cout << "stat2 (копия): ";
    stat2.print();

    Statistic stat3("10 20 30 40");
    std::cout << "stat3 (из строки): ";
    stat3.print();

    stat1 = stat3; // присваивание
    std::cout << "stat1 после присваивания stat3: ";
    stat1.print();

    return 0;
}