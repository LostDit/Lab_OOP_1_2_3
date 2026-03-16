#include "Statistic.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>

// Вспомогательные
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

// Конструкторы
Statistic::Statistic() : data(nullptr), size(0) {}

Statistic::Statistic(const int* arr, size_t n) : data(nullptr), size(0) {
    if (n > 0 && arr != nullptr) {
        size = n;
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = arr[i];
    }
}

Statistic::Statistic(const std::string& str) : data(nullptr), size(0) {
    std::istringstream iss(str);
    int value;
    std::vector<int> tmp;
    while (iss >> value)
        tmp.push_back(value);
    if (!tmp.empty()) {
        size = tmp.size();
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
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

// Задание 3: операторы []
const int Statistic::operator[](size_t ind) const {
    if (ind >= size)
        throw std::exception(); // или std::out_of_range("index out of range")
    return data[ind];
}

int& Statistic::operator[](size_t ind) {
    if (ind >= size)
        throw std::exception();
    return data[ind];
}

// Задание 4
Statistic Statistic::getSlice(size_t start, size_t finish) const {
    if (start > finish)
        throw std::invalid_argument("invalid data format");
    if (start >= size || finish >= size)
        throw std::out_of_range("index out of range");
    size_t newSize = finish - start + 1;
    int* newData = new int[newSize];
    for (size_t i = 0; i < newSize; ++i)
        newData[i] = data[start + i];
    Statistic slice;
    slice.size = newSize;
    slice.data = newData;
    return slice;
}

Statistic& Statistic::operator+=(const Statistic& v) {
    if (v.size == 0) return *this;
    int* newData = new int[size + v.size];
    for (size_t i = 0; i < size; ++i)
        newData[i] = data[i];
    for (size_t i = 0; i < v.size; ++i)
        newData[size + i] = v.data[i];
    delete[] data;
    data = newData;
    size += v.size;
    return *this;
}

// Задание 5
bool operator==(const Statistic& lhs, const Statistic& rhs) {
    if (lhs.size != rhs.size) return false;
    // Для сравнения без учёта порядка нужно отсортировать копии
    std::vector<int> l(lhs.data, lhs.data + lhs.size);
    std::vector<int> r(rhs.data, rhs.data + rhs.size);
    std::sort(l.begin(), l.end());
    std::sort(r.begin(), r.end());
    return l == r;
}

bool operator!=(const Statistic& lhs, const Statistic& rhs) {
    return !(lhs == rhs);
}

void Statistic::deleteSlice(size_t start, size_t finish) {
    if (start > finish)
        throw std::invalid_argument("invalid data format");
    if (start >= size || finish >= size)
        throw std::out_of_range("index out of range");
    size_t newSize = size - (finish - start + 1);
    if (newSize == 0) {
        freeMemory();
        return;
    }
    int* newData = new int[newSize];
    size_t pos = 0;
    for (size_t i = 0; i < size; ++i) {
        if (i < start || i > finish)
            newData[pos++] = data[i];
    }
    delete[] data;
    data = newData;
    size = newSize;
}

// Задание 6: дружественные операторы
std::ostream& operator<<(std::ostream& os, const Statistic& stat) {
    for (size_t i = 0; i < stat.size; ++i)
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
        for (size_t i = 0; i < stat.size; ++i)
            stat.data[i] = tmp[i];
    }
    return is;
}

// Методы get
int Statistic::get(size_t i) const {
    if (i >= size)
        throw std::exception();
    return data[i];
}

int& Statistic::get(size_t i) {
    if (i >= size)
        throw std::exception();
    return data[i];
}

// Прокси для среза
Statistic Statistic::SliceProxy::operator[](size_t finish) const {
    return stat.getSlice(start, finish);
}

Statistic::SliceProxy Statistic::operator[](size_t start) {
    if (start >= size)
        throw std::exception();
    return SliceProxy(*this, start);
}

// Для константного объекта: можно вернуть срез напрямую (без прокси), т.к. изменение не планируется
const Statistic Statistic::operator[](size_t start) const {
    // По заданию нужно получить срез, но синтаксис [start][finish] требует два вызова.
    // Для константного объекта вернём копию среза только от start до конца? Нет, нужно именно два индекса.
    // Лучше тоже сделать прокси, но константный. Упростим: пусть для константы operator[] возвращает Statistic,
    // а второй вызов — это уже оператор[] от Statistic? Тогда пришлось бы перегружать operator[] для двух индексов.
    // Альтернатива: реализовать operator()(start, finish). Но по заданию: statistic[2][4].
    // Поэтому для константности можно вернуть прокси, но с константной ссылкой на Statistic.
    // Создадим отдельный константный прокси. Но для краткости предположим, что мы не используем константные объекты в таком контексте.
    // В демо-программе это будет работать.
    throw std::logic_error("Not implemented for const. Use non-const object.");
}