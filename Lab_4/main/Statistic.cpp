#include "Statistic.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <vector>

void Statistic::freeMemory() {
    delete[] data;
    data = nullptr;
    size = 0;
}

void Statistic::copyFrom(const Statistic& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
}

Statistic::Statistic() : data(nullptr), size(0) {}

Statistic::Statistic(const int* arr, int n) : data(nullptr), size(0) {
    if (n > 0 && arr != nullptr) {
        size = n;
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = arr[i];
    }
}

Statistic::Statistic(const std::string& str) : data(nullptr), size(0) {
    std::istringstream iss(str);
    size_t value;
    std::vector<int> tmp;
    while (iss >> value)
        tmp.push_back(value);
    if (!tmp.empty()) {
        size = tmp.size();
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = tmp[i];
    }
}

Statistic::Statistic(const Statistic& other) : data(nullptr), size(0) {
    if (other.size > 0)
        copyFrom(other);
}

Statistic::~Statistic() {
    delete[] data;
}

Statistic& Statistic::operator=(const Statistic& other) {
    if (this != &other) {
        freeMemory();
        if (other.size > 0)
            copyFrom(other);
    }
    return *this;
}

const int Statistic::operator[](int ind) const {
    if (ind >= size)
        throw std::exception();
    return data[ind];
}

int& Statistic::operator[](int ind) {
    if (ind >= size)
        throw std::exception();
    return data[ind];
}

Statistic Statistic::getSlice(int start, int finish) const {
    if (start > finish)
        throw std::invalid_argument("invalid data format");
    if (start >= size || finish >= size)
        throw std::out_of_range("index out of range");
    int newSize = finish - start + 1;
    int* newData = new int[newSize];
    for (int i = 0; i < newSize; ++i)
        newData[i] = data[start + i];
    Statistic slice;
    slice.size = newSize;
    slice.data = newData;
    return slice;
}

Statistic& Statistic::operator+=(const Statistic& v) {
    if (v.size == 0) return *this;
    int* newData = new int[size + v.size];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];
    for (int i = 0; i < v.size; ++i)
        newData[size + i] = v.data[i];
    delete[] data;
    data = newData;
    size += v.size;
    return *this;
}

bool operator==(const Statistic& lhs, const Statistic& rhs) {
    if (lhs.size != rhs.size) return false;
    std::vector<size_t> l(lhs.data, lhs.data + lhs.size);
    std::vector<size_t> r(rhs.data, rhs.data + rhs.size);
    std::sort(l.begin(), l.end());
    std::sort(r.begin(), r.end());
    return l == r;
}

bool operator!=(const Statistic& lhs, const Statistic& rhs) {
    return !(lhs == rhs);
}

void Statistic::deleteSlice(int start, int finish) {
    if (start > finish)
        throw std::invalid_argument("invalid data format");
    if (start >= size || finish >= size)
        throw std::out_of_range("index out of range");
    int newSize = size - (finish - start + 1);
    if (newSize == 0) {
        freeMemory();
        return;
    }
    int* newData = new int[newSize];
    int pos = 0;
    for (int i = 0; i < size; ++i) {
        if (i < start || i > finish)
            newData[pos++] = data[i];
    }
    delete[] data;
    data = newData;
    size = newSize;
}

std::ostream& operator<<(std::ostream& os, const Statistic& stat) {
    for (int i = 0; i < stat.size; ++i)
        os << stat.data[i] << (i + 1 < stat.size ? ' ' : '\n');
    return os;
}

std::istream& operator>>(std::istream& is, Statistic& stat) {
    stat.freeMemory();
    std::vector<int> tmp;
    int val;
    while (is >> val)
        tmp.push_back(val);
    if (!tmp.empty()) {
        stat.size = tmp.size();
        stat.data = new int[stat.size];
        for (int i = 0; i < stat.size; ++i)
            stat.data[i] = tmp[i];
    }
    return is;
}

int Statistic::get(int i) const {
    if (i >= size)
        throw std::exception();
    return data[i];
}

int& Statistic::get(int i) {
    if (i >= size)
        throw std::exception();
    return data[i];
}

Statistic Statistic::SliceProxy::operator[](int finish) const {
    return stat.getSlice(start, finish);
}

Statistic::SliceProxy Statistic::operator[](size_t start) {
    if (start >= size)
        throw std::exception();
    return SliceProxy(*this, start);
}

const Statistic Statistic::operator[](size_t start) const {
    throw std::logic_error("Not implemented for const. Use non-const object.");
}