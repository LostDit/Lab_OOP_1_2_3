#pragma once
#include <stdexcept>

class Indexer {
private:
    double* arr;      // указатель на исходный массив
    int size;         // размер исходного массива
    int start;        // начальный индекс подмассива
    int length;       // длина подмассива

public:
    Indexer(double* array, int arraySize, int startIndex, int subLength);

    double& operator[](int index);
    const double& operator[](int index) const;

    int getStart() const { return start; }
    int getLength() const { return length; }
};