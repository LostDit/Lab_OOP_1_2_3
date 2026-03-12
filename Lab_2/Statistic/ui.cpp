#include "ui.h"
#include <iostream>
#include <limits>

using namespace std;

static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void printVector(const vector<int>& v, const string& prefix) {
    cout << prefix;
    if (v.empty()) {
        cout << "нет данных";
    } else {
        for (size_t i = 0; i < v.size(); ++i) {
            cout << v[i];
            if (i != v.size() - 1) cout << ", ";
        }
    }
    cout << endl;
}

int inputMonths() {
    int months;
    cout << "Введите количество месяцев: ";
    while (!(cin >> months) || months <= 0) {
        cout << "Ошибка! Введите положительное целое число: ";
        clearInput();
    }
    return months;
}

vector<int> inputSales(int months) {
    vector<int> sales(months);
    cout << "Введите продажи для каждого месяца:\n";
    for (int i = 0; i < months; ++i) {
        cout << "Месяц " << i + 1 << ": ";
        while (!(cin >> sales[i])) {
            cout << "Ошибка! Введите целое число: ";
            clearInput();
        }
    }
    return sales;
}

void runMenu(Statistic& stat) {
    int choice;
    do {
        cout << "\n=== Меню статистики продаж ===\n";
        cout << "1. Сумма всех продаж\n";
        cout << "2. Среднее значение продаж\n";
        cout << "3. Количество месяцев с продажами ниже среднего\n";
        cout << "4. Количество месяцев с продажами выше среднего\n";
        cout << "5. Номера месяцев с максимальными продажами\n";
        cout << "6. Номера месяцев с минимальными продажами\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            choice = -1;
        }

        switch (choice) {
            case 1:
                cout << "Сумма за период времени равна: " << stat.sum_sales() << endl;
                break;
            case 2:
                cout << "Среднее значение продаж: " << stat.average_sales() << endl;
                break;
            case 3:
                cout << "Количество месяцев с продажами ниже среднего: " << stat.months_sales_below_average() << endl;
                break;
            case 4:
                cout << "Количество месяцев с продажами выше среднего: " << stat.months_sales_above_average() << endl;
                break;
            case 5:
                printVector(stat.max_sales(), "Номера месяцев с максимальными продажами: ");
                break;
            case 6:
                printVector(stat.min_sales(), "Номера месяцев с минимальными продажами: ");
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный ввод, попробуйте снова.\n";
        }
    } while (choice != 0);
}