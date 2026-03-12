#include "Statistic.h"
#include <algorithm>

Statistic::Statistic(std::vector<int> const& a) : sales(a) {}

Statistic::~Statistic() = default;

long long Statistic::sum_sales() const {
    long long sum = 0;
    for (int val : sales)
        sum += val;
    return sum;
}

int Statistic::average_sales() const {
    if (sales.empty()) return 0;
    return static_cast<int>(sum_sales() / sales.size());
}

std::vector<int> Statistic::max_sales() const {
    std::vector<int> result;
    if (sales.empty()) return result;

    int maxVal = *std::max_element(sales.begin(), sales.end());
    for (size_t i = 0; i < sales.size(); ++i) {
        if (sales[i] == maxVal)
            result.push_back(static_cast<int>(i + 1)); // нумерация месяцев с 1
    }
    return result;
}

std::vector<int> Statistic::min_sales() const {
    std::vector<int> result;
    if (sales.empty()) return result;

    int minVal = *std::min_element(sales.begin(), sales.end());
    for (size_t i = 0; i < sales.size(); ++i) {
        if (sales[i] == minVal)
            result.push_back(static_cast<int>(i + 1));
    }
    return result;
}

int Statistic::months_sales_below_average() const {
    if (sales.empty()) return 0;
    int avg = average_sales();
    int count = 0;
    for (int val : sales) {
        if (val < avg)
            ++count;
    }
    return count;
}

int Statistic::months_sales_above_average() const {
    if (sales.empty()) return 0;
    int avg = average_sales();
    int count = 0;
    for (int val : sales) {
        if (val > avg)
            ++count;
    }
    return count;
}