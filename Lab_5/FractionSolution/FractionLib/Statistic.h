#pragma once
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <cmath>

class Statistic {
private:
    int* data;
    size_t sz;
    size_t capacity;

    void reallocate(size_t newCap);

public:
    Statistic();
    explicit Statistic(size_t n);                 // создаёт массив из n нулей
    Statistic(const int* arr, size_t n);          // копирует массив
    Statistic(const Statistic& other);
    Statistic(Statistic&& other) noexcept;
    ~Statistic();

    Statistic& operator=(const Statistic& other);
    Statistic& operator=(Statistic&& other) noexcept;

    void add(int value);                          // добавляет элемент в конец
    size_t size() const { return sz; }
    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    double mean() const;
    double median() const;
    int min() const;
    int max() const;
};

// Реализация в .cpp