#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include <random>

class LinearEquation {
private:
    std::vector<double> coeffs; // коэффициенты a1..an
    double freeTerm;            // b

public:
    // Конструкторы
    LinearEquation();
    explicit LinearEquation(int n);                       // нулевые коэффициенты
    LinearEquation(const std::vector<double>& coeffs, double freeTerm);
    LinearEquation(std::initializer_list<double> list);   // последний элемент - свободный член
    explicit LinearEquation(const std::string& str);      // парсинг строки вида "a1 a2 ... an b"

    // Конструктор копирования и оператор присваивания (генерируются автоматически, но явно укажем)
    LinearEquation(const LinearEquation&) = default;
    LinearEquation& operator=(const LinearEquation&) = default;

    // Метод для заполнения случайными значениями в диапазоне [min, max]
    void randomize(double min = -10.0, double max = 10.0);

    // Доступ к числу переменных
    size_t size() const { return coeffs.size(); }

    // Операторы
    LinearEquation operator-() const;                     // унарный минус
    LinearEquation& operator+=(const LinearEquation& other);
    LinearEquation& operator-=(const LinearEquation& other);

    // Бинарные арифметические операторы (дружественные или свободные)
    friend LinearEquation operator+(const LinearEquation& lhs, const LinearEquation& rhs);
    friend LinearEquation operator-(const LinearEquation& lhs, const LinearEquation& rhs);
    friend LinearEquation operator*(const LinearEquation& eq, double val);
    friend LinearEquation operator*(double val, const LinearEquation& eq);

    // Сравнение
    bool operator==(const LinearEquation& other) const;
    bool operator!=(const LinearEquation& other) const;

    // Доступ к коэффициентам и свободному члену
    double operator[](size_t index) const;                // индекс: 0..n-1 - коэффициенты, n - свободный член
    double& operator[](size_t index);

    // Приведение к vector<double> (коэффициенты + свободный член)
    explicit operator std::vector<double>() const;

    // Ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const LinearEquation& eq);
    friend std::istream& operator>>(std::istream& is, LinearEquation& eq);
};