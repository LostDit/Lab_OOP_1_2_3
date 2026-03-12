#pragma once
#include <vector>

class Statistic {
private:
    std::vector<int> sales;

public:
    Statistic(std::vector<int> const& a);
    ~Statistic();

    long long sum_sales() const;
    int average_sales() const;
    std::vector<int> max_sales() const;
    std::vector<int> min_sales() const;
    int months_sales_below_average() const;
    int months_sales_above_average() const;
};