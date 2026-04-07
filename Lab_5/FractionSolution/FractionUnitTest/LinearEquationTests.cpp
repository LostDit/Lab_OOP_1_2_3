#include "pch.h"
#include "../FractionLib/LinearEquation.h"
#include <sstream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FractionUnitTest
{
    TEST_CLASS(LinearEquationTests)
    {
    public:
        // Проверка конструктора по умолчанию (0 переменных)
        TEST_METHOD(DefaultConstructor)
        {
            LinearEquation eq;
            Assert::AreEqual((size_t)0, eq.size());
            Assert::AreEqual(0.0, eq[0]); // свободный член
        }

        // Конструктор с количеством переменных
        TEST_METHOD(ConstructorWithSize)
        {
            LinearEquation eq(3);
            Assert::AreEqual((size_t)3, eq.size());
            Assert::AreEqual(0.0, eq[0]);
            Assert::AreEqual(0.0, eq[1]);
            Assert::AreEqual(0.0, eq[2]);
            Assert::AreEqual(0.0, eq[3]);
        }

        // Конструктор из вектора коэффициентов и свободного члена
        TEST_METHOD(ConstructorFromVector)
        {
            std::vector<double> coeffs = { 1.5, -2.0, 3.0 };
            LinearEquation eq(coeffs, 4.0);
            Assert::AreEqual(1.5, eq[0]);
            Assert::AreEqual(-2.0, eq[1]);
            Assert::AreEqual(3.0, eq[2]);
            Assert::AreEqual(4.0, eq[3]);
        }

        // Конструктор из initializer_list
        TEST_METHOD(ConstructorFromInitializerList)
        {
            LinearEquation eq({ 2.0, -3.0, 4.0, 5.0 }); // последний - свободный член
            Assert::AreEqual((size_t)3, eq.size());
            Assert::AreEqual(2.0, eq[0]);
            Assert::AreEqual(-3.0, eq[1]);
            Assert::AreEqual(4.0, eq[2]);
            Assert::AreEqual(5.0, eq[3]);
        }

        // Конструктор из строки
        TEST_METHOD(ConstructorFromString)
        {
            LinearEquation eq("1.5 2.5 -3.5 10");
            Assert::AreEqual((size_t)3, eq.size());
            Assert::AreEqual(1.5, eq[0]);
            Assert::AreEqual(2.5, eq[1]);
            Assert::AreEqual(-3.5, eq[2]);
            Assert::AreEqual(10.0, eq[3]);
        }

        // Конструктор копирования и присваивание
        TEST_METHOD(CopyConstructorAndAssignment)
        {
            LinearEquation eq1({ 1, 2, 3 });
            LinearEquation eq2(eq1);
            Assert::IsTrue(eq1 == eq2);
            LinearEquation eq3;
            eq3 = eq1;
            Assert::IsTrue(eq1 == eq3);
        }

        // Метод randomize
        TEST_METHOD(Randomize)
        {
            LinearEquation eq(4);
            eq.randomize(-5.0, 5.0);
            // Проверяем, что значения в заданном диапазоне
            for (size_t i = 0; i <= eq.size(); ++i) {
                double val = eq[i];
                Assert::IsTrue(val >= -5.0 && val <= 5.0);
            }
        }

        // Унарный минус
        TEST_METHOD(UnaryMinus)
        {
            LinearEquation eq({ 1, -2, 3 });
            LinearEquation neg = -eq;
            Assert::AreEqual(-1.0, neg[0]);
            Assert::AreEqual(2.0, neg[1]);
            Assert::AreEqual(-3.0, neg[2]);
        }

        // Составные операторы += и -=
        TEST_METHOD(CompoundAssignment)
        {
            LinearEquation eq1({ 1, 2, 3 });
            LinearEquation eq2({ 4, -1, 5 });
            eq1 += eq2;
            Assert::AreEqual(5.0, eq1[0]);
            Assert::AreEqual(1.0, eq1[1]);
            Assert::AreEqual(8.0, eq1[2]);

            eq1 -= eq2;
            Assert::AreEqual(1.0, eq1[0]);
            Assert::AreEqual(2.0, eq1[1]);
            Assert::AreEqual(3.0, eq1[2]);
        }

        // Бинарные операторы +, -, *
        TEST_METHOD(BinaryOperators)
        {
            LinearEquation eq1({ 1, 2, 3 });
            LinearEquation eq2({ 4, -1, 5 });
            LinearEquation sum = eq1 + eq2;
            Assert::IsTrue(sum == LinearEquation({ 5, 1, 8 }));
            LinearEquation diff = eq1 - eq2;
            Assert::IsTrue(diff == LinearEquation({ -3, 3, -2 }));
            LinearEquation prod = eq1 * 2.0;
            Assert::IsTrue(prod == LinearEquation({ 2, 4, 6 }));
            LinearEquation prod2 = 3.0 * eq1;
            Assert::IsTrue(prod2 == LinearEquation({ 3, 6, 9 }));
        }

        // Операторы сравнения
        TEST_METHOD(Comparison)
        {
            LinearEquation eq1({ 1, 2, 3 });
            LinearEquation eq2({ 1, 2, 3 });
            LinearEquation eq3({ 1, 2, 4 });
            Assert::IsTrue(eq1 == eq2);
            Assert::IsTrue(eq1 != eq3);
        }

        // Оператор[] для доступа и изменения
        TEST_METHOD(IndexOperator)
        {
            LinearEquation eq(3);
            eq[0] = 5.0;
            eq[1] = -2.0;
            eq[2] = 1.0;
            eq[3] = 7.0; // свободный член
            Assert::AreEqual(5.0, eq[0]);
            Assert::AreEqual(-2.0, eq[1]);
            Assert::AreEqual(1.0, eq[2]);
            Assert::AreEqual(7.0, eq[3]);
        }

        // Неявное преобразование к vector<double>
        TEST_METHOD(ConversionToVector)
        {
            LinearEquation eq({ 1, 2, 3 });
            std::vector<double> v = static_cast<std::vector<double>>(eq);
            Assert::AreEqual(eq.size() + 1, v.size()); // было (size_t)4
            Assert::AreEqual(1.0, v[0]);
            Assert::AreEqual(2.0, v[1]);
            Assert::AreEqual(3.0, v[2]);
        }

        // Операторы ввода/вывода
        TEST_METHOD(StreamOperators)
        {
            LinearEquation eq({ 2.5, -1.5, 7.0 });
            std::ostringstream out;
            out << eq;
            // Примерный вывод: "2.5*x1 + -1.5*x2 + 7 = 0"
            std::string str = out.str();
            Assert::IsTrue(str.find("2.5*x1") != std::string::npos);

            std::istringstream in("3.0 4.0 -5.0 10");
            LinearEquation eq2;
            in >> eq2;
            Assert::AreEqual(3.0, eq2[0]);
            Assert::AreEqual(4.0, eq2[1]);
            Assert::AreEqual(-5.0, eq2[2]);
            Assert::AreEqual(10.0, eq2[3]);
        }
    };
}