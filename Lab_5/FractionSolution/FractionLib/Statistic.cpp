#include "pch.h"
#include "Statistic.h"

using namespace std;

void Statistic::reallocate(size_t newCap) {
    int* newData = new int[newCap];
    for (size_t i = 0; i < sz; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCap;
}

Statistic::Statistic() : data(nullptr), sz(0), capacity(0) {}

Statistic::Statistic(size_t n) : sz(n), capacity(n) {
    data = new int[n](); // инициализация нулями
}

Statistic::Statistic(const int* arr, size_t n) : sz(n), capacity(n) {
    data = new int[n];
    for (size_t i = 0; i < n; ++i)
        data[i] = arr[i];
}

Statistic::Statistic(const Statistic& other) : sz(other.sz), capacity(other.sz) {
    data = new int[capacity];
    for (size_t i = 0; i < sz; ++i)
        data[i] = other.data[i];
}

Statistic::Statistic(Statistic&& other) noexcept : data(other.data), sz(other.sz), capacity(other.capacity) {
    other.data = nullptr;
    other.sz = other.capacity = 0;
}

Statistic::~Statistic() {
    delete[] data;
}

Statistic& Statistic::operator=(const Statistic& other) {
    if (this != &other) {
        delete[] data;
        sz = other.sz;
        capacity = other.sz;
        data = new int[capacity];
        for (size_t i = 0; i < sz; ++i)
            data[i] = other.data[i];
    }
    return *this;
}

Statistic& Statistic::operator=(Statistic&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        sz = other.sz;
        capacity = other.capacity;
        other.data = nullptr;
        other.sz = other.capacity = 0;
    }
    return *this;
}

void Statistic::add(int value) {
    if (sz == capacity) {
        size_t newCap = (capacity == 0) ? 1 : capacity * 2;
        reallocate(newCap);
    }
    data[sz++] = value;
}

int& Statistic::operator[](size_t index) {
    if (index >= sz) throw out_of_range("Index out of range.");
    return data[index];
}

const int& Statistic::operator[](size_t index) const {
    if (index >= sz) throw out_of_range("Index out of range.");
    return data[index];
}

double Statistic::mean() const {
    if (sz == 0) throw runtime_error("Empty collection.");
    long long sum = 0;
    for (size_t i = 0; i < sz; ++i) sum += data[i];
    return static_cast<double>(sum) / sz;
}

double Statistic::median() const {
    if (sz == 0) throw runtime_error("Empty collection.");
    int* temp = new int[sz];
    copy(data, data + sz, temp);
    sort(temp, temp + sz);
    double med;
    if (sz % 2 == 0)
        med = (temp[sz / 2 - 1] + temp[sz / 2]) / 2.0;
    else
        med = temp[sz / 2];
    delete[] temp;
    return med;
}

int Statistic::min() const {
    if (sz == 0) throw runtime_error("Empty collection.");
    int m = data[0];
    for (size_t i = 1; i < sz; ++i)
        if (data[i] < m) m = data[i];
    return m;
}

int Statistic::max() const {
    if (sz == 0) throw runtime_error("Empty collection.");
    int m = data[0];
    for (size_t i = 1; i < sz; ++i)
        if (data[i] > m) m = data[i];
    return m;
}