#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <cstddef>
#include <string>

class Statistic {
private:
    int* data;
    size_t size;

    void freeMemory();
    void copyFrom(const Statistic& other);

public:
    Statistic();
    ~Statistic();

    explicit Statistic(const int* a, const size_t& n);
    explicit Statistic(const std::string& str);
    Statistic(const Statistic& other);
    Statistic& operator=(const Statistic& other);

    void print() const; // для демонстрации
};

#endif