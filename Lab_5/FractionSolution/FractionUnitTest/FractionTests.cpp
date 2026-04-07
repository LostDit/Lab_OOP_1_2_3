#include "pch.h"
#include "../FractionLib/Fraction.h"
#include <stdexcept>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FractionUnitTest
{
    TEST_CLASS(FractionTests)
    {
    public:
        // Проверка конструктора без параметров (значения по умолчанию 0/1)
        TEST_METHOD(TestConstructorWithoutArgs)
        {
            Fraction f;
            Assert::AreEqual(0, f.getNumerator());
            Assert::AreEqual(1, f.getDenominator());
        }

        // Проверка конструктора с одним параметром (числитель, знаменатель = 1)
        TEST_METHOD(TestConstructorWithOneArg)
        {
            Fraction f(-5);
            Assert::AreEqual(-5, f.getNumerator());
            Assert::AreEqual(1, f.getDenominator());
        }

        // Проверка конструктора с двумя параметрами, включая отрицательный знаменатель
        TEST_METHOD(TestConstructorWithTwoArg)
        {
            Fraction f(2, -5);
            Assert::AreEqual(-2, f.getNumerator());
            Assert::AreEqual(5, f.getDenominator());
        }

        // Проверка автоматического сокращения дроби при создании
        TEST_METHOD(TestFractionReduction)
        {
            Fraction f(200, 400);
            Assert::AreEqual(1, f.getNumerator());
            Assert::AreEqual(2, f.getDenominator());
        }

        // Проверка выброса исключения при знаменателе равном нулю
        TEST_METHOD(TestConstructorException)
        {
            auto func = [] { Fraction f(20, 0); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Проверка конструктора из строки вида "a/b"
        TEST_METHOD(TestStringConstructor)
        {
            Fraction f1("3/4");
            Assert::AreEqual(3, f1.getNumerator());
            Assert::AreEqual(4, f1.getDenominator());

            Fraction f2("-5/2");
            Assert::AreEqual(-5, f2.getNumerator());
            Assert::AreEqual(2, f2.getDenominator());

            Fraction f3("7");
            Assert::AreEqual(7, f3.getNumerator());
            Assert::AreEqual(1, f3.getDenominator());

            auto func = [] { Fraction f("1/0"); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Проверка оператора +=
        TEST_METHOD(TestPlusEquals)
        {
            Fraction f1(1, 2);
            f1 += Fraction(1, 3);
            Assert::AreEqual(5, f1.getNumerator());
            Assert::AreEqual(6, f1.getDenominator());
        }

        // Проверка оператора -=
        TEST_METHOD(TestMinusEquals)
        {
            Fraction f1(1, 2);
            f1 -= Fraction(1, 3);
            Assert::AreEqual(1, f1.getNumerator());
            Assert::AreEqual(6, f1.getDenominator());
        }

        // Проверка оператора *=
        TEST_METHOD(TestMultiplyEquals)
        {
            Fraction f1(2, 3);
            f1 *= Fraction(3, 4);
            Assert::AreEqual(1, f1.getNumerator());
            Assert::AreEqual(2, f1.getDenominator());
        }

        // Проверка оператора /= и деления на ноль
        TEST_METHOD(TestDivideEquals)
        {
            Fraction f1(2, 3);
            f1 /= Fraction(3, 4);
            Assert::AreEqual(8, f1.getNumerator());
            Assert::AreEqual(9, f1.getDenominator());

            auto func = [] { Fraction f(1, 2); f /= Fraction(0, 1); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Проверка унарного минуса
        TEST_METHOD(TestUnaryMinus)
        {
            Fraction f(2, 3);
            Fraction neg = -f;
            Assert::AreEqual(-2, neg.getNumerator());
            Assert::AreEqual(3, neg.getDenominator());
        }

        // Проверка бинарных арифметических операторов +, -, *, /
        TEST_METHOD(TestBinaryOperators)
        {
            Fraction a(1, 2), b(1, 3);
            Assert::IsTrue(Fraction(5, 6) == a + b);
            Assert::IsTrue(Fraction(1, 6) == a - b);
            Assert::IsTrue(Fraction(1, 6) == a * b);
            Assert::IsTrue(Fraction(3, 2) == a / b);
        }

        // Проверка операторов сравнения
        TEST_METHOD(TestComparisonOperators)
        {
            Fraction a(1, 2), b(2, 4), c(3, 4);
            Assert::IsTrue(a == b);
            Assert::IsTrue(a != c);
            Assert::IsTrue(a < c);
            Assert::IsTrue(a <= c);
            Assert::IsTrue(c > a);
            Assert::IsTrue(c >= a);
        }

        // Проверка возведения в натуральную степень
        TEST_METHOD(TestPowNatural)
        {
            Fraction f(2, 3);
            Fraction res = f.pow(3);
            Assert::AreEqual(8, res.getNumerator());
            Assert::AreEqual(27, res.getDenominator());
        }

        // Проверка получения обратной дроби и исключения для нуля
        TEST_METHOD(TestInverse)
        {
            Fraction f(2, 3);
            Fraction inv = f.inverse();
            Assert::AreEqual(3, inv.getNumerator());
            Assert::AreEqual(2, inv.getDenominator());

            Fraction zero(0, 1);
            auto func = [zero] { zero.inverse(); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Проверка умножения дроби на целое число (и слева, и справа)
        TEST_METHOD(TestMultiplyByInt)
        {
            Fraction f(2, 3);
            Fraction r1 = f * 2;
            Fraction r2 = 3 * f;
            Assert::IsTrue(Fraction(4, 3) == r1);
            Assert::IsTrue(Fraction(2, 1) == r2);
        }

        // Проверка возведения в целую (в том числе отрицательную) степень
        TEST_METHOD(TestPowInteger)
        {
            Fraction f(2, 3);
            Fraction pos = f.pow(2);
            Fraction neg = f.pow(-2);
            Assert::IsTrue(Fraction(4, 9) == pos);
            Assert::IsTrue(Fraction(9, 4) == neg);

            Fraction zero(0, 1);
            auto func = [zero] { zero.pow(-1); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Проверка операторов приведения к double и к string
        TEST_METHOD(TestConversionOperators)
        {
            Fraction f(1, 2);
            double d = f;
            Assert::AreEqual(0.5, d, 1e-9);

            std::string s = static_cast<std::string>(f);
            Assert::AreEqual(std::string("1/2"), s);
        }

        // Проверка отсутствия переполнения при сокращении до выполнения умножения
        TEST_METHOD(TestOverflowSafety)
        {
            Fraction f1(100000, 200000);  // сократится до 1/2
            Fraction f2(200000, 100000);  // сократится до 2/1
            try {
                Fraction res = f1 * f2;
                Assert::AreEqual(1, res.getNumerator());
                Assert::AreEqual(1, res.getDenominator());
            }
            catch (const std::overflow_error&) {
                Assert::Fail(L"Overflow exception should not occur after reduction.");
            }
        }

        // Проверка операторов ввода и вывода в поток
        TEST_METHOD(TestInputOutput)
        {
            std::stringstream ss("3/4");
            Fraction f;
            ss >> f;
            Assert::AreEqual(3, f.getNumerator());
            Assert::AreEqual(4, f.getDenominator());

            std::stringstream out;
            out << f;
            Assert::AreEqual(std::string("3/4"), out.str());
        }

        // Проверка конструктора из строки с пробелами (ожидается исключение)
        TEST_METHOD(TestConstructorStringWithSpaces)
        {
            Fraction f(" 3/4 ");
            Assert::AreEqual(3, f.getNumerator());
            Assert::AreEqual(4, f.getDenominator());
        }

        // Проверка конструктора из строки с отрицательным знаменателем
        TEST_METHOD(TestConstructorStringNegativeDenominator)
        {
            Fraction f("3/-4");
            Assert::AreEqual(-3, f.getNumerator());
            Assert::AreEqual(4, f.getDenominator());
        }

        // Проверка конструктора из строки с нулевым числителем (должен сократиться до 0/1)
        TEST_METHOD(TestConstructorStringZeroNumerator)
        {
            Fraction f("0/5");
            Assert::AreEqual(0, f.getNumerator());
            Assert::AreEqual(1, f.getDenominator());
        }

        // Проверка конструктора из некорректной строки (исключение)
        TEST_METHOD(TestConstructorStringInvalidFormat)
        {
            auto func1 = [] { Fraction f("abc"); };
            Assert::ExpectException<std::invalid_argument>(func1);
        }

        // Проверка сокращения дробей с отрицательными значениями
        TEST_METHOD(TestReductionWithNegativeValues)
        {
            Fraction f1(-4, 6);
            Assert::AreEqual(-2, f1.getNumerator());
            Assert::AreEqual(3, f1.getDenominator());

            Fraction f2(5, -15);
            Assert::AreEqual(-1, f2.getNumerator());
            Assert::AreEqual(3, f2.getDenominator());

            Fraction f3(-9, -12);
            Assert::AreEqual(3, f3.getNumerator());
            Assert::AreEqual(4, f3.getDenominator());
        }

        // Проверка оператора += с отрицательными числами
        TEST_METHOD(TestPlusEqualsWithNegative)
        {
            Fraction f(-1, 2);
            f += Fraction(1, 2);
            Assert::AreEqual(0, f.getNumerator());
            Assert::AreEqual(1, f.getDenominator());
        }

        // Проверка оператора -= с отрицательными числами
        TEST_METHOD(TestMinusEqualsWithNegative)
        {
            Fraction f(1, 2);
            f -= Fraction(3, 2);
            Assert::AreEqual(-1, f.getNumerator());
            Assert::AreEqual(1, f.getDenominator());
        }

        // Проверка оператора *= с отрицательными числами
        TEST_METHOD(TestMultiplyEqualsWithNegative)
        {
            Fraction f(2, 3);
            f *= Fraction(-3, 4);
            Assert::AreEqual(-1, f.getNumerator());
            Assert::AreEqual(2, f.getDenominator());
        }

        // Проверка оператора /= с отрицательными числами
        TEST_METHOD(TestDivideEqualsWithNegative)
        {
            Fraction f(1, 2);
            f /= Fraction(-2, 3);
            Assert::AreEqual(-3, f.getNumerator());
            Assert::AreEqual(4, f.getDenominator());
        }

        // Проверка цепочки составных присваиваний
        TEST_METHOD(TestCompoundAssignmentChain)
        {
            Fraction f(1, 2);          // 1/2
            f += Fraction(1, 3);       // 1/2 + 1/3 = 5/6
            f -= Fraction(1, 6);       // 5/6 - 1/6 = 4/6 = 2/3
            f *= Fraction(4, 3);       // (2/3) * (4/3) = 8/9
            f /= Fraction(2, 1);       // (8/9) / 2 = 8/18 = 4/9
            Assert::IsTrue(Fraction(4, 9) == f);
        }

        // Проверка сложения с нулём
        TEST_METHOD(TestAddZero)
        {
            Fraction a(3, 4);
            Fraction zero;
            Assert::IsTrue(a == a + zero);
            Assert::IsTrue(a == zero + a);
        }

        // Проверка вычитания нуля
        TEST_METHOD(TestSubtractZero)
        {
            Fraction a(3, 4);
            Fraction zero;
            Assert::IsTrue(a == a - zero);
            Assert::IsTrue(-a == zero - a);
        }

        // Проверка умножения на ноль
        TEST_METHOD(TestMultiplyByZero)
        {
            Fraction a(3, 4);
            Fraction zero;
            Assert::IsTrue(zero == a * zero);
            Assert::IsTrue(zero == zero * a);
        }

        // Проверка деления нуля на дробь
        TEST_METHOD(TestDivideZeroByFraction)
        {
            Fraction zero;
            Fraction a(3, 4);
            Assert::IsTrue(zero == zero / a);
        }

        // Проверка деления на ноль (исключение)
        TEST_METHOD(TestDivideByZeroThrows)
        {
            Fraction a(1, 2);
            Fraction zero;
            auto func = [&] { a / zero; };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Проверка двойного применения унарного минуса
        TEST_METHOD(TestUnaryMinusTwice)
        {
            Fraction f(2, 3);
            Fraction neg1 = -f;
            Fraction neg2 = -neg1;
            Assert::IsTrue(f == neg2);
        }

        // Проверка унарного минуса для нуля
        TEST_METHOD(TestUnaryMinusOfZero)
        {
            Fraction zero;
            Assert::IsTrue(zero == -zero);
        }

        // Проверка сравнения дробей с большими числами
        TEST_METHOD(TestComparisonWithLargeNumbers)
        {
            Fraction a(12345, 67890);
            Fraction b(12346, 67891);
            Assert::IsTrue(a < b);
        }

        // Проверка сравнения отрицательных и положительных дробей
        TEST_METHOD(TestComparisonWithNegative)
        {
            Fraction a(-1, 2);
            Fraction b(1, 3);
            Assert::IsTrue(a < b);
            Assert::IsTrue(a <= b);
            Assert::IsFalse(a > b);
            Assert::IsFalse(a >= b);
        }

        // Проверка равенства дробей после сокращения
        TEST_METHOD(TestComparisonEqualAfterReduction)
        {
            Fraction a(4, 6);
            Fraction b(2, 3);
            Assert::IsTrue(a == b);
            Assert::IsTrue(a <= b);
            Assert::IsTrue(a >= b);
        }

        // Проверка возведения в нулевую степень
        TEST_METHOD(TestPowZero)
        {
            Fraction f(5, 7);
            Fraction res = f.pow(0);
            Assert::AreEqual(1, res.getNumerator());
            Assert::AreEqual(1, res.getDenominator());
        }

        // Проверка возведения в первую степень
        TEST_METHOD(TestPowOne)
        {
            Fraction f(5, 7);
            Fraction res = f.pow(1);
            Assert::IsTrue(f == res);
        }

        // Проверка возведения в чётную отрицательную степень
        TEST_METHOD(TestPowNegativeEven)
        {
            Fraction f(2, 3);
            Fraction res = f.pow(-2);
            Assert::IsTrue(Fraction(9, 4) == res);
        }

        // Проверка возведения в нечётную отрицательную степень
        TEST_METHOD(TestPowNegativeOdd)
        {
            Fraction f(2, 3);
            Fraction res = f.pow(-3);
            Assert::IsTrue(Fraction(27, 8) == res);
        }

        // Проверка возведения отрицательной дроби в степень
        TEST_METHOD(TestPowOfNegativeFraction)
        {
            Fraction f(-2, 3);
            Fraction res1 = f.pow(2);
            Assert::IsTrue(Fraction(4, 9) == res1);
            Fraction res2 = f.pow(3);
            Assert::IsTrue(Fraction(-8, 27) == res2);
        }

        // Проверка возведения нуля в отрицательную степень (исключение)
        TEST_METHOD(TestPowNegativeExponentOfZero)
        {
            Fraction zero;
            auto func = [zero] { zero.pow(-1); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Проверка обратной дроби для отрицательной дроби
        TEST_METHOD(TestInverseOfNegativeFraction)
        {
            Fraction f(-2, 3);
            Fraction inv = f.inverse();
            Assert::AreEqual(-3, inv.getNumerator());
            Assert::AreEqual(2, inv.getDenominator());
        }

        // Проверка обратной дроби для единицы
        TEST_METHOD(TestInverseOfOne)
        {
            Fraction f(1, 1);
            Fraction inv = f.inverse();
            Assert::IsTrue(f == inv);
        }

        // Проверка обратной дроби для минус единицы
        TEST_METHOD(TestInverseOfMinusOne)
        {
            Fraction f(-1, 1);
            Fraction inv = f.inverse();
            Assert::IsTrue(f == inv);
        }

        // Проверка умножения дроби на ноль (целое)
        TEST_METHOD(TestMultiplyByZeroInt)
        {
            Fraction f(3, 4);
            Fraction res = f * 0;
            Assert::IsTrue(Fraction(0, 1) == res);
        }

        // Проверка умножения дроби на отрицательное целое
        TEST_METHOD(TestMultiplyByNegativeInt)
        {
            Fraction f(3, 4);
            Fraction res1 = f * -2;
            Fraction res2 = -2 * f;
            Assert::IsTrue(Fraction(-3, 2) == res1);
            Assert::IsTrue(res1 == res2);
        }

        // Проверка умножения дроби на целое с последующим сокращением
        TEST_METHOD(TestMultiplyIntThenReduce)
        {
            Fraction f(3, 6);
            Fraction res = f * 4;  // (1/2)*4 = 2/1
            Assert::AreEqual(2, res.getNumerator());
            Assert::AreEqual(1, res.getDenominator());
        }

        // Проверка приведения отрицательной дроби к double
        TEST_METHOD(TestDoubleConversionOfNegative)
        {
            Fraction f(-1, 4);
            double d = f;
            Assert::AreEqual(-0.25, d, 1e-9);
        }

        // Проверка приведения дроби с большими числами к double
        TEST_METHOD(TestDoubleConversionOfLarge)
        {
            Fraction f(1000000, 3);
            double d = f;
            Assert::AreEqual(1000000.0 / 3.0, d, 1e-9);
        }

        // Проверка явного приведения отрицательной дроби к строке
        TEST_METHOD(TestStringConversion)
        {
            Fraction f(-7, 9);
            std::string s = static_cast<std::string>(f);
            Assert::AreEqual(std::string("-7/9"), s);
        }

        // Проверка явного приведения нулевой дроби к строке
        TEST_METHOD(TestStringConversionOfZero)
        {
            Fraction f;
            std::string s = static_cast<std::string>(f);
            Assert::AreEqual(std::string("0/1"), s);
        }

        // Проверка ввода отрицательной дроби из потока
        TEST_METHOD(TestInputNegativeFraction)
        {
            std::stringstream ss("-5/8");
            Fraction f;
            ss >> f;
            Assert::AreEqual(-5, f.getNumerator());
            Assert::AreEqual(8, f.getDenominator());
        }

        // Проверка ввода дроби с пробелами (ожидается исключение)
        TEST_METHOD(TestInputFractionWithSpaces)
        {
            std::stringstream ss(" -5/8");
            Fraction f;
            ss >> f;
            Assert::AreEqual(-5, f.getNumerator());
            Assert::AreEqual(8, f.getDenominator());
        }

        // Проверка вывода отрицательной дроби в поток
        TEST_METHOD(TestOutputOfNegativeFraction)
        {
            Fraction f(-3, 5);
            std::stringstream out;
            out << f;
            Assert::AreEqual(std::string("-3/5"), out.str());
        }

        // Проверка вывода целого числа в виде дроби
        TEST_METHOD(TestOutputOfInteger)
        {
            Fraction f(4, 1);
            std::stringstream out;
            out << f;
            Assert::AreEqual(std::string("4/1"), out.str());
        }

        // Проверка сложного выражения с несколькими операциями
        TEST_METHOD(TestComplexExpression)
        {
            Fraction a(1, 2);
            Fraction b(2, 3);
            Fraction c(3, 4);
            Fraction result = (a + b) * c - (a / b);
            // a+b = 7/6, *c = 21/24 = 7/8, a/b = 3/4 = 6/8, результат = 1/8
            Assert::IsTrue(Fraction(1, 8) == result);
        }

        // Проверка длинной цепочки умножений с сокращением
        TEST_METHOD(TestLargeChainWithReduction)
        {
            Fraction f(2, 3);
            for (int i = 0; i < 5; ++i) {
                f *= Fraction(3, 2);
            }
            // (2/3)*(3/2)^5 = (2/3)*(243/32) = 486/96 = 81/16
            Assert::IsTrue(Fraction(81, 16) == f);
        }
    };
}