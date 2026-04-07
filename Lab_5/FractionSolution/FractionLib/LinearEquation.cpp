#include "pch.h"
#include "LinearEquation.h"
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// ---------- Конструкторы ----------
LinearEquation::LinearEquation() : freeTerm(0.0) {}

LinearEquation::LinearEquation(int n) : coeffs(n, 0.0), freeTerm(0.0) {
    if (n < 0) throw invalid_argument("Number of variables cannot be negative.");
}

LinearEquation::LinearEquation(const vector<double>& coeffs, double freeTerm)
    : coeffs(coeffs), freeTerm(freeTerm) {
}

LinearEquation::LinearEquation(initializer_list<double> list) {
    if (list.size() < 1)
        throw invalid_argument("At least free term must be provided.");
    auto it = list.begin();
    for (size_t i = 0; i < list.size() - 1; ++i, ++it)
        coeffs.push_back(*it);
    freeTerm = *it;
}

LinearEquation::LinearEquation(const string& str) {
    istringstream iss(str);
    double val;
    while (iss >> val) {
        coeffs.push_back(val);
    }
    if (coeffs.empty())
        throw invalid_argument("No numbers found in string.");
    freeTerm = coeffs.back();
    coeffs.pop_back();
}

// ---------- Случайное заполнение ----------
void LinearEquation::randomize(double min, double max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<double> dis(min, max);
    for (auto& c : coeffs)
        c = dis(gen);
    freeTerm = dis(gen);
}

// ---------- Операторы ----------
LinearEquation LinearEquation::operator-() const {
    LinearEquation result = *this;
    for (auto& c : result.coeffs) c = -c;
    result.freeTerm = -result.freeTerm;
    return result;
}

LinearEquation& LinearEquation::operator+=(const LinearEquation& other) {
    if (coeffs.size() != other.coeffs.size())
        throw invalid_argument("Equations have different number of variables.");
    for (size_t i = 0; i < coeffs.size(); ++i)
        coeffs[i] += other.coeffs[i];
    freeTerm += other.freeTerm;
    return *this;
}

LinearEquation& LinearEquation::operator-=(const LinearEquation& other) {
    return *this += -other;
}

LinearEquation operator+(const LinearEquation& lhs, const LinearEquation& rhs) {
    LinearEquation result = lhs;
    result += rhs;
    return result;
}

LinearEquation operator-(const LinearEquation& lhs, const LinearEquation& rhs) {
    LinearEquation result = lhs;
    result -= rhs;
    return result;
}

LinearEquation operator*(const LinearEquation& eq, double val) {
    LinearEquation result = eq;
    for (auto& c : result.coeffs) c *= val;
    result.freeTerm *= val;
    return result;
}

LinearEquation operator*(double val, const LinearEquation& eq) {
    return eq * val;
}

// ---------- Сравнение ----------
bool LinearEquation::operator==(const LinearEquation& other) const {
    return coeffs == other.coeffs && freeTerm == other.freeTerm;
}

bool LinearEquation::operator!=(const LinearEquation& other) const {
    return !(*this == other);
}

// ---------- Доступ по индексу ----------
double LinearEquation::operator[](size_t index) const {
    if (index < coeffs.size())
        return coeffs[index];
    else if (index == coeffs.size())
        return freeTerm;
    else
        throw out_of_range("Index out of range.");
}

double& LinearEquation::operator[](size_t index) {
    if (index < coeffs.size())
        return coeffs[index];
    else if (index == coeffs.size())
        return freeTerm;
    else
        throw out_of_range("Index out of range.");
}

// ---------- Приведение к vector<double> ----------
LinearEquation::operator std::vector<double>() const {
    vector<double> result = coeffs;
    result.push_back(freeTerm);
    return result;
}

// ---------- Ввод/вывод ----------
ostream& operator<<(ostream& os, const LinearEquation& eq) {
    for (size_t i = 0; i < eq.coeffs.size(); ++i) {
        if (i > 0) os << " + ";
        os << eq.coeffs[i] << "*x" << (i + 1);
    }
    os << " + " << eq.freeTerm << " = 0";
    return os;
}

istream& operator>>(istream& is, LinearEquation& eq) {
    vector<double> temp;
    double val;
    while (is >> val) {
        temp.push_back(val);
    }
    if (temp.empty()) {
        is.setstate(ios::failbit);
        return is;
    }
    eq.freeTerm = temp.back();
    temp.pop_back();
    eq.coeffs = temp;
    return is;
}