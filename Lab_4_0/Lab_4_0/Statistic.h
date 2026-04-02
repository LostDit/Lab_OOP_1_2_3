#pragma once
#include <vector>
#include <string>

class Statistic {
public:
    Statistic();
    explicit Statistic(const std::string& data);
    const int operator[](size_t index) const;
    int& operator[](size_t index);
    Statistic getSlice(size_t start, size_t finish) const;
    Statistic& operator+=(const Statistic& other);
    size_t size() const;
private:
    std::vector<int> data_;
};