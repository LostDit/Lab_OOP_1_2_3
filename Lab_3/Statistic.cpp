#include "Statistic.h"
#include <iostream>
#include <sstream>
#include <vector>

Statistic::Statistic() : data(nullptr), size(0) {}

Statistic::~Statistic() {
    delete[] data;
}

Statistic::Statistic(const int* a, const size_t& n) : data(nullptr), size(0) {
    if (n > 0 && a != nullptr) {
        size = n;
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = a[i];
    }
}

Statistic::Statistic(const std::string& str) : data(nullptr), size(0) {
    std::istringstream iss(str);
    int value;
    std::vector<int> tmp;
    while (iss >> value) {
        tmp.push_back(value);
    }
    if (!tmp.empty()) {
        size = tmp.size();
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = tmp[i];
    }
}

Statistic::Statistic(const Statistic& other) : data(nullptr), size(0) {
    if (other.size > 0) {
        copyFrom(other);
    }
}

Statistic& Statistic::operator=(const Statistic& other) {
    if (this != &other) {
        freeMemory();
        if (other.size > 0) {
            copyFrom(other);
        }
    }
    return *this;
}

void Statistic::freeMemory() {
    delete[] data;
    data = nullptr;
    size = 0;
}

void Statistic::copyFrom(const Statistic& other) {
    size = other.size;
    data = new int[size];
    for (size_t i = 0; i < size; ++i)
        data[i] = other.data[i];
}

void Statistic::print() const {
    for (size_t i = 0; i < size; ++i)
        std::cout << data[i] << ' ';
    std::cout << '\n';
}