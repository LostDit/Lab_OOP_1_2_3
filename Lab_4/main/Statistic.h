#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <cstddef>
#include <string>
#include <iostream>

class Statistic {
private:
    int* data;
    int size;

    void freeMemory();
    void copyFrom(const Statistic& other);

public:
    Statistic();
    explicit Statistic(const int* arr, int n);
    explicit Statistic(const std::string& str);
    Statistic(const Statistic& other);
    ~Statistic();

    Statistic& operator=(const Statistic& other);

    const int operator[](int ind) const;
    int& operator[](int ind);

    Statistic getSlice(int start, int finish) const;
    Statistic& operator+=(const Statistic& v);

    friend bool operator==(const Statistic& lhs, const Statistic& rhs);
    friend bool operator!=(const Statistic& lhs, const Statistic& rhs);
    void deleteSlice(int start, int finish);

    friend std::ostream& operator<<(std::ostream& os, const Statistic& stat);
    friend std::istream& operator>>(std::istream& is, Statistic& stat);

    int get(int i) const;
    int& get(int i);

    class SliceProxy {
        Statistic& stat;
        int start;
    public:
        SliceProxy(Statistic& s, int st) : stat(s), start(st) {}
        Statistic operator[](int finish) const;
    };

    SliceProxy operator[](size_t start);
    const Statistic operator[](size_t start) const;

    int getSize() const { return size; }
};

#endif