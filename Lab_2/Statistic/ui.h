#ifndef UI_H
#define UI_H

#include <vector>
#include "Statistic.h"

int inputMonths();

std::vector<int> inputSales(int months);

void runMenu(Statistic& stat);

#endif // UI_H