#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Radio.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Radio myRadio;
    char key;
    std::cout << "Управление радио:\n";
    std::cout << "  W / S - увеличить/уменьшить громкость\n";
    std::cout << "  A / D - предыдущая/следующая станция\n";
    std::cout << "  Q - выход\n\n";

    do {
        std::cout << "Текущая станция: " << myRadio.getStation()
                  << ", громкость: " << myRadio.getVolume() << std::endl;

        key = _getch();
        switch (key) {
            case 'w': case 'W':
                myRadio.incVolume();
                break;
            case 's': case 'S':
                myRadio.decVolume();
                break;
            case 'a': case 'A':
                myRadio.previousStation();
                break;
            case 'd': case 'D':
                myRadio.nextStation();
                break;
            case 'q': case 'Q':
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неизвестная команда.\n";
        }
    } while (key != 'q' && key != 'Q');

    return 0;
}