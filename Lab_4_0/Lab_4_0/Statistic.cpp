#include "Statistic.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

Statistic::Statistic() {}

Statistic::Statistic(const std::string& data) {
    std::istringstream iss(data);
    int value;
    while (iss >> value)
        data_.push_back(value);
}

Statistic::Statistic(const std::vector<int>& data) : data_(data) {}

const int Statistic::operator[](size_t index) const {
    if (index >= data_.size())
        throw std::out_of_range("index out of range");
    return data_[index];
}

int& Statistic::operator[](size_t index) {
    if (index >= data_.size())
        throw std::out_of_range("index out of range");
    return data_[index];
}

Statistic Statistic::getSlice(size_t start, size_t finish) const {
    if (start > finish)
        throw std::invalid_argument("invalid data format");
    if (start >= data_.size() || finish >= data_.size())
        throw std::out_of_range("index out of range");
    Statistic result;
    for (size_t i = start; i <= finish; ++i)
        result.data_.push_back(data_[i]);
    return result;
}

Statistic& Statistic::operator+=(const Statistic& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    return *this;
}

size_t Statistic::size() const {
    return data_.size();
}

std::ostream& operator<<(std::ostream& os, const Statistic& s) {
    for (size_t i = 0; i < s.data_.size(); ++i)
        os << s.data_[i] << " ";
    return os;
}

std::istream& operator>>(std::istream& is, Statistic& s) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    int val;
    s.data_.clear();
    while (iss >> val)
        s.data_.push_back(val);
    return is;
}