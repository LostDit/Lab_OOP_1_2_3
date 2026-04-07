#include "pch.h"
#include "SystemOfLinearEquation.h"
#include <cmath>
#include <algorithm>

using namespace std;

SystemOfLinearEquation::SystemOfLinearEquation(size_t n) : numVars(n) {}

void SystemOfLinearEquation::addEquation(const LinearEquation& eq) {
    if (eq.size() != numVars)
        throw invalid_argument("Equation has different number of variables.");
    equations.push_back(eq);
}

LinearEquation& SystemOfLinearEquation::operator[](size_t index) {
    if (index >= equations.size())
        throw out_of_range("Equation index out of range.");
    return equations[index];
}

const LinearEquation& SystemOfLinearEquation::operator[](size_t index) const {
    if (index >= equations.size())
        throw out_of_range("Equation index out of range.");
    return equations[index];
}

// Прямой ход метода Гаусса (приведение к верхнетреугольному виду)
void SystemOfLinearEquation::toRowEchelonForm() {
    size_t n = equations.size();
    size_t m = numVars;
    size_t row = 0;
    for (size_t col = 0; col < m && row < n; ++col) {
        // Поиск строки с максимальным элементом в столбце для устойчивости
        size_t maxRow = row;
        for (size_t i = row + 1; i < n; ++i) {
            if (fabs(equations[i][col]) > fabs(equations[maxRow][col]))
                maxRow = i;
        }
        if (fabs(equations[maxRow][col]) < 1e-12) // почти ноль
            continue;

        if (maxRow != row)
            std::swap(equations[row], equations[maxRow]);

        // Нормируем строку
        double pivot = equations[row][col];
        for (size_t j = col; j <= m; ++j)
            equations[row][j] /= pivot;

        // Обнуляем элементы в столбце col во всех остальных строках
        for (size_t i = 0; i < n; ++i) {
            if (i == row) continue;
            double factor = equations[i][col];
            if (fabs(factor) < 1e-12) continue;
            for (size_t j = col; j <= m; ++j)
                equations[i][j] -= factor * equations[row][j];
        }
        ++row;
    }

    // Удаляем полностью нулевые строки (все коэффициенты И свободный член равны 0)
    equations.erase(std::remove_if(equations.begin(), equations.end(),
        [this](const LinearEquation& eq) {
            bool allZero = true;
            for (size_t i = 0; i < numVars; ++i)
                if (fabs(eq[i]) > 1e-12) { allZero = false; break; }
            return allZero && (fabs(eq[numVars]) < 1e-12); // свободный член тоже ноль
        }), equations.end());
}

SystemOfLinearEquation::Solution SystemOfLinearEquation::solve() {
    toRowEchelonForm();

    size_t n = equations.size();
    size_t m = numVars;

    Solution sol;
    // Проверка на несовместность
    for (const auto& eq : equations) {
        bool allZero = true;
        for (size_t i = 0; i < m; ++i)
            if (fabs(eq[i]) > 1e-12) { allZero = false; break; }
        if (allZero && fabs(eq[m]) > 1e-12) {
            sol.type = Solution::Type::None;
            return sol;
        }
    }

    if (n < m) {
        sol.type = Solution::Type::Infinite;
        return sol;
    }

    // Единственное решение
    std::vector<double> x(m, 0.0);
    for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
        size_t lead = 0;
        while (lead < m && fabs(equations[i][lead]) < 1e-12) ++lead;
        if (lead == m) continue;
        double sum = 0.0;
        for (size_t j = lead + 1; j < m; ++j)
            sum += equations[i][j] * x[j];
        // Уравнение: x[lead] + sum + free = 0  =>  x[lead] = -free - sum
        x[lead] = -equations[i][m] - sum;
    }
    sol.type = Solution::Type::Unique;
    sol.values = x;
    return sol;
}