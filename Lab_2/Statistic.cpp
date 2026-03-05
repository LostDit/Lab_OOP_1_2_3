#include "Statistic.h"
#include <algorithm>
#include <numeric>

Statistic::Statistic(std::vector<int> const & a) : sales(a) {}

Statistic::~Statistic() = default;

long long Statistic::sum_sales() const {
    return std::accumulate(sales.begin(), sales.end(), 0LL);
}

int Statistic::average_sales() const {
    if (sales.empty()) return 0;
    return static_cast<int>(sum_sales() / sales.size());
}

std::vector<int> Statistic::max_sales() const {
    if (sales.empty()) return {};
    int maxVal = *std::ranges::max_element(sales);
    std::vector<int> months;
    for (size_t i = 0; i < sales.size(); ++i) {
        if (sales[i] == maxVal) months.push_back(static_cast<int>(i + 1));  // 1-based
    }
    return months;
}

std::vector<int> Statistic::min_sales() const {
    if (sales.empty()) return {};
    int minVal = *std::ranges::min_element(sales);
    std::vector<int> months;
    for (size_t i = 0; i < sales.size(); ++i) {
        if (sales[i] == minVal) months.push_back(static_cast<int>(i + 1));
    }
    return months;
}

int Statistic::months_sales_below_average() const {
    int avg = average_sales();
    return static_cast<int>(std::ranges::count_if(sales, [avg](int s) { return s < avg; }));
}

int Statistic::months_sales_above_average() const {
    int avg = average_sales();
    return static_cast<int>(std::ranges::count_if(sales, [avg](int s) { return s > avg; }));
}