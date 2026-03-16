#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <cstddef>
#include <string>
#include <iostream>

class Statistic {
private:
    int* data;
    size_t size;

    void freeMemory();
    void copyFrom(const Statistic& other);

public:
    Statistic();
    explicit Statistic(const int* arr, size_t n);
    explicit Statistic(const std::string& str);
    Statistic(const Statistic& other);
    ~Statistic();

    Statistic& operator=(const Statistic& other);

    const int operator[](size_t ind) const;
    int& operator[](size_t ind);

    // Задание 4: срез и +=
    Statistic getSlice(size_t start, size_t finish) const;
    Statistic& operator+=(const Statistic& v);

    friend bool operator==(const Statistic& lhs, const Statistic& rhs);
    friend bool operator!=(const Statistic& lhs, const Statistic& rhs);
    void deleteSlice(size_t start, size_t finish);

    friend std::ostream& operator<<(std::ostream& os, const Statistic& stat);
    friend std::istream& operator>>(std::istream& is, Statistic& stat);

    int get(size_t i) const;
    int& get(size_t i);

    class SliceProxy {
        Statistic& stat;
        size_t start;
    public:
        SliceProxy(Statistic& s, size_t st) : stat(s), start(st) {}
        Statistic operator[](size_t finish) const;
    };

    SliceProxy operator[](size_t start);
    const Statistic operator[](size_t start) const;

    size_t getSize() const { return size; }
};

#endif