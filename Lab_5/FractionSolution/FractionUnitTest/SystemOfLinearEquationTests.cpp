#include "pch.h"
#include "../FractionLib/SystemOfLinearEquation.h"
#include "../FractionLib/LinearEquation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FractionUnitTest
{
    TEST_CLASS(SystemOfLinearEquationTests)
    {
    public:
        // Конструктор с количеством переменных
        TEST_METHOD(ConstructorWithVariableCount)
        {
            SystemOfLinearEquation sys(3);
            Assert::AreEqual((size_t)3, sys.variableCount());
            Assert::AreEqual((size_t)0, sys.equationCount());
        }

        // Добавление уравнения и доступ по индексу
        TEST_METHOD(AddAndAccessEquation)
        {
            SystemOfLinearEquation sys(2);
            LinearEquation eq1({ 1, 2, 5 }); // x1 + 2x2 + 5 = 0
            sys.addEquation(eq1);
            Assert::AreEqual((size_t)1, sys.equationCount());
            Assert::IsTrue(sys[0] == eq1);
            LinearEquation eq2({ 3, -1, 2 });
            sys.addEquation(eq2);
            Assert::AreEqual((size_t)2, sys.equationCount());
            Assert::IsTrue(sys[1] == eq2);
        }

        // Добавление уравнения с неверным числом переменных вызывает исключение
        TEST_METHOD(AddWrongSizeEquation)
        {
            SystemOfLinearEquation sys(2);
            LinearEquation eq({ 1, 2, 3, 4 }); // 3 переменные
            auto func = [&] { sys.addEquation(eq); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Решение системы с единственным решением
        TEST_METHOD(SolveUniqueSolution)
        {
            SystemOfLinearEquation sys(2);
            sys.addEquation(LinearEquation({ 2, 1, 5 }));  // 2x1 + x2 + 5 = 0
            sys.addEquation(LinearEquation({ 1, -1, 1 })); // x1 - x2 + 1 = 0
            auto sol = sys.solve();
            Assert::IsTrue(sol.type == SystemOfLinearEquation::Solution::Type::Unique);
            // Решение: x1 = -2, x2 = -1
            Assert::AreEqual(-2.0, sol.values[0], 1e-9);
            Assert::AreEqual(-1.0, sol.values[1], 1e-9);
        }

        // Система без решений (несовместная)
        TEST_METHOD(SolveNoSolution)
        {
            SystemOfLinearEquation sys(2);
            sys.addEquation(LinearEquation({ 1, 1, 2 }));  // x1 + x2 + 2 = 0
            sys.addEquation(LinearEquation({ 1, 1, 3 }));  // x1 + x2 + 3 = 0
            auto sol = sys.solve();
            Assert::IsTrue(sol.type == SystemOfLinearEquation::Solution::Type::None);
        }

        // Система с бесконечным множеством решений
        TEST_METHOD(SolveInfiniteSolutions)
        {
            SystemOfLinearEquation sys(2);
            sys.addEquation(LinearEquation({ 1, 1, 2 }));   // x1 + x2 + 2 = 0
            sys.addEquation(LinearEquation({ 2, 2, 4 }));   // 2x1 + 2x2 + 4 = 0 (пропорционально)
            auto sol = sys.solve();
            Assert::IsTrue(sol.type == SystemOfLinearEquation::Solution::Type::Infinite);
        }

        // Приведение к ступенчатому виду (проверка через решение)
        TEST_METHOD(RowEchelonForm)
        {
            SystemOfLinearEquation sys(3);
            sys.addEquation(LinearEquation({ 1, 2, -1, 1 }));
            sys.addEquation(LinearEquation({ 2, 5, 1, 3 }));
            sys.addEquation(LinearEquation({ 1, 3, 2, 2 }));
            sys.toRowEchelonForm();
            auto sol = sys.solve();
            Assert::IsTrue(sol.type == SystemOfLinearEquation::Solution::Type::Infinite);
        }
    };
}