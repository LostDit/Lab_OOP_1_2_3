#include "Statistic.h"
#include <sstream>
#include <stdexcept>

Statistic::Statistic() {}

Statistic::Statistic(const std::string& data) {
    std::istringstream iss(data);
    int value;
    while (iss >> value) {
        data_.push_back(value);
    }
}

const int Statistic::operator[](size_t index) const {
    if (index >= data_.size()) {
        throw std::out_of_range("index out of range");
    }
    return data_[index];
}

int& Statistic::operator[](size_t index) {
    if (index >= data_.size()) {
        throw std::out_of_range("index out of range");
    }
    return data_[index];
}

Statistic Statistic::getSlice(size_t start, size_t finish) const {
    if (start > finish) {
        throw std::invalid_argument("invalid data format");
    }
    if (start >= data_.size() || finish >= data_.size()) {
        throw std::out_of_range("index out of range");
    }
    Statistic result;
    for (size_t i = start; i <= finish; ++i) {
        result.data_.push_back(data_[i]);
    }
    return result;
}

Statistic& Statistic::operator+=(const Statistic& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    return *this;
}

size_t Statistic::size() const {
    return data_.size();
}