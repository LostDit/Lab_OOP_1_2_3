#include "ui.h"
#include "Statistic.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int months = inputMonths();
    std::vector<int> sales = inputSales(months);
    Statistic stat(sales);
    runMenu(stat);
    return 0;
}