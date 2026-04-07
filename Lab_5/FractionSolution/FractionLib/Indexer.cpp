#include "pch.h"
#include "Indexer.h"

Indexer::Indexer(double* array, int arraySize, int startIndex, int subLength)
    : arr(array), size(arraySize), start(startIndex), length(subLength)
{
    if (array == nullptr)
        throw std::invalid_argument("Array pointer is null.");
    if (arraySize <= 0)
        throw std::invalid_argument("Array size must be positive.");
    if (startIndex < 0 || startIndex >= arraySize)
        throw std::out_of_range("Start index out of bounds.");
    if (subLength < 0)
        throw std::invalid_argument("Subarray length cannot be negative.");
    if (startIndex + subLength > arraySize)
        throw std::out_of_range("Subarray exceeds array bounds.");
}

double& Indexer::operator[](int index) {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index out of subarray range.");
    return arr[start + index];
}

const double& Indexer::operator[](int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index out of subarray range.");
    return arr[start + index];
}