#include "pch.h"
#include "Fraction.h"

using namespace std;

// ---------- Вспомогательные приватные методы ----------
int Fraction::gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int Fraction::lcm(int a, int b) {
    return a / gcd(a, b) * b;   // осторожно с переполнением – далее используем long long
}

void Fraction::reduce() {
    if (den == 0)
        throw invalid_argument("Denominator cannot be zero.");
    if (den < 0) {
        num = -num;
        den = -den;
    }
    int g = gcd(num, den);
    num /= g;
    den /= g;
}

// ---------- Конструкторы ----------
Fraction::Fraction(int numerator, int denominator)
    : num(numerator), den(denominator)
{
    if (den == 0)
        throw invalid_argument("Denominator cannot be zero.");
    reduce();
}

Fraction::Fraction(const std::string& str) {
    size_t slash = str.find('/');
    if (slash == string::npos) {
        num = stoi(str);
        den = 1;
    }
    else {
        string numStr = str.substr(0, slash);
        string denStr = str.substr(slash + 1);
        num = stoi(numStr);
        den = stoi(denStr);
        if (den == 0)
            throw invalid_argument("Denominator cannot be zero.");
    }
    reduce();
}

// ---------- Составные операторы (с контролем переполнения) ----------
Fraction& Fraction::operator+=(const Fraction& other) {
    long long new_num = static_cast<long long>(num) * other.den
        + static_cast<long long>(other.num) * den;
    long long new_den = static_cast<long long>(den) * other.den;
    long long g = gcd(static_cast<int>(abs(new_num)), static_cast<int>(abs(new_den)));
    new_num /= g;
    new_den /= g;
    if (new_num < numeric_limits<int>::min() || new_num > numeric_limits<int>::max() ||
        new_den < numeric_limits<int>::min() || new_den > numeric_limits<int>::max())
        throw overflow_error("Fraction overflow in operator+=");
    num = static_cast<int>(new_num);
    den = static_cast<int>(new_den);
    if (den < 0) {
        num = -num;
        den = -den;
    }
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    return *this += -other;
}

Fraction& Fraction::operator*=(const Fraction& other) {
    long long new_num = static_cast<long long>(num) * other.num;
    long long new_den = static_cast<long long>(den) * other.den;
    long long g = gcd(static_cast<int>(abs(new_num)), static_cast<int>(abs(new_den)));
    new_num /= g;
    new_den /= g;
    if (new_num < numeric_limits<int>::min() || new_num > numeric_limits<int>::max() ||
        new_den < numeric_limits<int>::min() || new_den > numeric_limits<int>::max())
        throw overflow_error("Fraction overflow in operator*=");
    num = static_cast<int>(new_num);
    den = static_cast<int>(new_den);
    if (den < 0) {
        num = -num;
        den = -den;
    }
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
    if (other.num == 0)
        throw invalid_argument("Division by zero.");
    return *this *= other.inverse();
}

// ---------- Унарный минус ----------
Fraction Fraction::operator-() const {
    return Fraction(-num, den);
}

// ---------- Бинарные операторы (свободные функции) ----------
Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    Fraction result = lhs;
    result += rhs;
    return result;
}
Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    Fraction result = lhs;
    result -= rhs;
    return result;
}
Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    Fraction result = lhs;
    result *= rhs;
    return result;
}
Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    Fraction result = lhs;
    result /= rhs;
    return result;
}

// ---------- Операторы сравнения ----------
bool Fraction::operator==(const Fraction& other) const {
    return num == other.num && den == other.den;
}
bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}
bool Fraction::operator<(const Fraction& other) const {
    long long left = static_cast<long long>(num) * other.den;
    long long right = static_cast<long long>(other.num) * den;
    return left < right;
}
bool Fraction::operator<=(const Fraction& other) const {
    return !(*this > other);
}
bool Fraction::operator>(const Fraction& other) const {
    return other < *this;
}
bool Fraction::operator>=(const Fraction& other) const {
    return !(*this < other);
}

// ---------- Возведение в степень ----------
Fraction Fraction::pow(unsigned int n) const {
    Fraction result(1);
    Fraction base = *this;
    while (n > 0) {
        if (n & 1)
            result *= base;
        base *= base;
        n >>= 1;
    }
    return result;
}

Fraction Fraction::pow(int n) const {
    if (n >= 0)
        return pow(static_cast<unsigned int>(n));
    else {
        if (num == 0)
            throw invalid_argument("Cannot raise zero to negative power.");
        Fraction inv = inverse();
        return inv.pow(static_cast<unsigned int>(-n));
    }
}

// ---------- Обратная дробь ----------
Fraction Fraction::inverse() const {
    if (num == 0)
        throw invalid_argument("Cannot invert zero fraction.");
    return Fraction(den, num);
}

// ---------- Умножение на целое ----------
Fraction Fraction::operator*(int value) const {
    return Fraction(num * value, den);
}
Fraction operator*(int value, const Fraction& f) {
    return f * value;
}

// ---------- Приведения типов ----------
Fraction::operator double() const {
    return static_cast<double>(num) / den;
}
Fraction::operator std::string() const {
    return to_string(num) + "/" + to_string(den);
}

// ---------- Ввод/вывод ----------
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.num << "/" << f.den;
    return os;
}
std::istream& operator>>(std::istream& is, Fraction& f) {
    string line;
    is >> line;
    f = Fraction(line);
    return is;
}