#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Radio.h"
#include "Field.h"
#include "Statistic.h"
#include "Fifteen.h"

using namespace std;

// ---------------------- Radio интерактив ----------------------
void runRadio() {
    system("cls");
    Radio r;
    cout << "=== Радио ===" << endl;
    cout << "Текущая станция: " << r.getStation() << endl;
    cout << "Управление: '+' (увеличить), '-' (уменьшить), 'q' - выход" << endl;
    char key;
    while (true) {
        key = _getch();
        if (key == '+') {
            ++r;
            cout << "Станция: " << r.getStation() << endl;
        }
        else if (key == '-') {
            --r;
            cout << "Станция: " << r.getStation() << endl;
        }
        else if (key == 'q') break;
    }
}

// ---------------------- Field демонстрация ----------------------
void runFieldDemo() {
    system("cls");
    cout << "=== Демонстрация Field ===" << endl;
    vector<int> tiles1 = { 1,2,3,4,5,6,7,8,0 };
    Field f1(3, 3, tiles1, 2, 2);
    Field f2(3, 3, tiles1, 2, 2);
    Field f3(3, 3, tiles1, 1, 1);
    cout << "f1 == f2: " << (f1 == f2 ? "истина" : "ложь") << endl;
    cout << "f1 != f2: " << (f1 != f2 ? "истина" : "ложь") << endl;
    cout << "f1 == f3: " << (f1 == f3 ? "истина" : "ложь") << endl;
    cout << "f1 != f3: " << (f1 != f3 ? "истина" : "ложь") << endl;
    cout << "\nНажмите любую клавишу для возврата в меню...";
    _getch();
}

// ---------------------- Statistic демонстрация ----------------------
void runStatisticDemo() {
    system("cls");
    cout << "=== Статистика ===" << endl;
    cout << "Введите числа через пробел (например: 10 20 30 40): ";
    Statistic s;
    cin >> s;  // используем operator>>
    cin.ignore(32767, '\n'); // очистка буфера

    cout << "Введённая статистика: " << s << endl;
    cout << "Размер: " << s.size() << endl;

    // Проверка operator[]
    try {
        cout << "Первый элемент: " << s[0] << endl;
        cout << "Последний элемент: " << s[s.size() - 1] << endl;
        // cout << s[100] << endl; // раскомментировать для проверки исключения
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    // getSlice
    try {
        size_t start, finish;
        cout << "Введите начало и конец среза (включительно, от 0): ";
        cin >> start >> finish;
        Statistic slice = s.getSlice(start, finish);
        cout << "Срез: " << slice << endl;

        // operator+=
        Statistic s2;
        cout << "Введите ещё одну статистику для добавления: ";
        cin >> s2;
        s += s2;
        cout << "Результат объединения: " << s << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка формата: " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cout << "Выход за границы: " << e.what() << endl;
    }
    cout << "\nНажмите любую клавишу...";
    _getch();
}

// ---------------------- Пятнашки ----------------------
void runFifteen() {
    system("cls");
    cout << "=== Игра Пятнашки ===" << endl;
    cout << "Введите размер поля (3 или 4): ";
    int size;
    cin >> size;
    if (size < 2) size = 3;

    Fifteen game(static_cast<size_t>(size));
    game.run();
    cout << "\nУправление: стрелки (↑ ↓ ← →). ESC - выход в меню." << endl;
    system("pause");
    system("cls");
    game.draw();
    cout << "Ходов: " << game.getCount() << endl;

    while (!game.isGameOver()) {
        int key = _getch();
        if (key == 224) {
            key = _getch();
            game.onKeyPressed(key);
            system("cls");
            game.draw();
            cout << "Ходов: " << game.getCount() << endl;
        }
        else if (key == 27) break;
    }
    if (game.isGameOver()) {
        cout << "\nПоздравляем! Вы собрали головоломку за " << game.getCount() << " ходов!" << endl;
        cout << "Нажмите любую клавишу...";
        _getch();
    }
}

// ---------------------- Главное меню ----------------------
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    while (true) {
        system("cls");
        cout << "========== ГЛАВНОЕ МЕНЮ ==========" << endl;
        cout << "1. Радио (интерактивное переключение)" << endl;
        cout << "2. Field (демонстрация == и !=)" << endl;
        cout << "3. Statistic (ввод, вывод, срезы, объединение)" << endl;
        cout << "4. Пятнашки (игра)" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите пункт: ";
        char choice = _getch();
        cout << endl;

        switch (choice) {
        case '1': runRadio(); break;
        case '2': runFieldDemo(); break;
        case '3': runStatisticDemo(); break;
        case '4': runFifteen(); break;
        case '0': return 0;
        default: break;
        }
    }
}