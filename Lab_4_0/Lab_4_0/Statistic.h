#pragma once
#include <vector>
#include <string>
#include <iostream>

class Statistic {
public:
    Statistic();
    explicit Statistic(const std::string& data);
    explicit Statistic(const std::vector<int>& data);  // удобство
    const int operator[](size_t index) const;
    int& operator[](size_t index);
    Statistic getSlice(size_t start, size_t finish) const;
    Statistic& operator+=(const Statistic& other);
    size_t size() const;

    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Statistic& s);
    friend std::istream& operator>>(std::istream& is, Statistic& s);

private:
    std::vector<int> data_;
};