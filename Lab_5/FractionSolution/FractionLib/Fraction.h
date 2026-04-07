#pragma once
#include <stdexcept>
#include <string>
#include <iostream>

class Fraction {
private:
    int num;   // числитель (может быть отрицательным)
    int den;   // знаменатель (всегда > 0)

    void reduce();                           // сокращение дроби
    static int gcd(int a, int b);            // НОД
    static int lcm(int a, int b);            // НОК (используется при сложении/вычитании)

public:
    // Конструкторы
    Fraction(int numerator = 0, int denominator = 1);
    explicit Fraction(const std::string& str); // из строки "a/b"

    // Геттеры
    int getNumerator() const { return num; }
    int getDenominator() const { return den; }

    // Составные операторы
    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    // Унарный минус
    Fraction operator-() const;

    // Операторы сравнения
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    // Возведение в степень
    Fraction pow(unsigned int n) const;       // натуральная степень
    Fraction pow(int n) const;                // целая степень

    // Обратная дробь
    Fraction inverse() const;

    // Умножение на целое число
    Fraction operator*(int value) const;
    friend Fraction operator*(int value, const Fraction& f);

    // Приведения типов
    operator double() const;                  // неявное к double
    explicit operator std::string() const;    // явное к строке

    // Ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
    friend std::istream& operator>>(std::istream& is, Fraction& f);
};

// Бинарные арифметические операторы (реализованы через составные)
Fraction operator+(const Fraction& lhs, const Fraction& rhs);
Fraction operator-(const Fraction& lhs, const Fraction& rhs);
Fraction operator*(const Fraction& lhs, const Fraction& rhs);
Fraction operator/(const Fraction& lhs, const Fraction& rhs);