#pragma once
#include "LinearEquation.h"
#include <vector>
#include <stdexcept>

class SystemOfLinearEquation {
private:
    std::vector<LinearEquation> equations;
    size_t numVars; // количество переменных (для контроля)

public:
    // Конструктор с заданным количеством переменных (система пустая)
    explicit SystemOfLinearEquation(size_t n = 0);

    // Добавление уравнения
    void addEquation(const LinearEquation& eq);
    size_t equationCount() const { return equations.size(); }
    size_t variableCount() const { return numVars; }

    // Доступ к уравнению по индексу
    LinearEquation& operator[](size_t index);
    const LinearEquation& operator[](size_t index) const;

    // Приведение к ступенчатому виду (прямой ход метода Гаусса)
    void toRowEchelonForm();

    // Решение системы. Возвращает:
    // - вектор решений, если единственное решение
    // - пустой вектор, если нет решений
    // - вектор с одним элементом - специальное значение (например, NaN) для бесконечного множества решений
    // Для простоты используем структуру Solution
    struct Solution {
        enum class Type { Unique, Infinite, None };
        Type type;
        std::vector<double> values; // при Unique
    };
    Solution solve();
};