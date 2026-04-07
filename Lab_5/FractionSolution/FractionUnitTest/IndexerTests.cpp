#include "pch.h"
#include "../FractionLib/Indexer.h"
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FractionUnitTest
{
    TEST_CLASS(IndexerTests)
    {
    public:
        // Проверка некорректных параметров конструктора (начальный индекс вне границ)
        TEST_METHOD(IndexerInvalidConstructorStartOutOfBounds)
        {
            int size = 7;
            double* a = new double[size] { 1, 2, 3, 4, 5, 6, 7 };
            auto func1 = [a, size] { Indexer ind(a, size, -1, 3); };
            Assert::ExpectException<std::out_of_range>(func1);
            auto func2 = [a, size] { Indexer ind(a, size, 7, 1); };
            Assert::ExpectException<std::out_of_range>(func2);
            delete[] a;
        }

        // Проверка некорректной длины подмассива (отрицательная или выход за границы)
        TEST_METHOD(IndexerInvalidConstructorLengthInvalid)
        {
            int size = 5;
            double* a = new double[size] { 1, 2, 3, 4, 5 };
            auto func1 = [a, size] { Indexer ind(a, size, 2, -1); };
            Assert::ExpectException<std::invalid_argument>(func1);
            auto func2 = [a, size] { Indexer ind(a, size, 2, 4); }; // 2+4=6 > 5
            Assert::ExpectException<std::out_of_range>(func2);
            delete[] a;
        }

        // Проверка конструктора с нулевой длиной подмассива (должен работать)
        TEST_METHOD(IndexerZeroLengthSubarray)
        {
            int size = 5;
            double* a = new double[size] { 1, 2, 3, 4, 5 };
            Indexer ind(a, size, 2, 0);
            Assert::AreEqual(2, ind.getStart());
            Assert::AreEqual(0, ind.getLength());
            // Доступ по индексу должен выбрасывать исключение
            auto func = [&ind] { ind[0]; };
            Assert::ExpectException<std::out_of_range>(func);
            delete[] a;
        }

        // Проверка конструктора с nullptr массивом
        TEST_METHOD(IndexerNullArray)
        {
            auto func = [] { Indexer ind(nullptr, 5, 0, 2); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // Проверка конструктора с неположительным размером массива
        TEST_METHOD(IndexerInvalidArraySize)
        {
            double* a = new double[3] { 1, 2, 3 };
            auto func1 = [a] { Indexer ind(a, 0, 0, 1); };
            Assert::ExpectException<std::invalid_argument>(func1);
            auto func2 = [a] { Indexer ind(a, -5, 0, 1); };
            Assert::ExpectException<std::invalid_argument>(func2);
            delete[] a;
        }

        // Проверка успешного создания и получения элемента через оператор[]
        TEST_METHOD(IndexerGetElementByIndex)
        {
            int size = 5;
            double* a = new double[size] { 10, 20, 30, 40, 50 };
            Indexer ind(a, size, 2, 2);
            Assert::AreEqual(30.0, ind[0]);
            Assert::AreEqual(40.0, ind[1]);
            delete[] a;
        }

        // Проверка установки элемента через оператор[] (уже был, но оставим)
        TEST_METHOD(IndexerSetElementByIndex)
        {
            int size = 7;
            double* a = new double[size] { 1, 2, 3, 4, 5, 6, 7 };
            Indexer ind(a, size, 1, 3);
            ind[1] = 100.0;
            Assert::AreEqual(100.0, a[2]);
            delete[] a;
        }

        // Проверка модификации нескольких элементов и отражения в исходном массиве
        TEST_METHOD(IndexerModifyMultipleElements)
        {
            int size = 6;
            double* a = new double[size] { 0, 0, 0, 0, 0, 0 };
            Indexer ind(a, size, 2, 3);
            ind[0] = 1.1;
            ind[1] = 2.2;
            ind[2] = 3.3;
            Assert::AreEqual(1.1, a[2]);
            Assert::AreEqual(2.2, a[3]);
            Assert::AreEqual(3.3, a[4]);
            delete[] a;
        }

        // Проверка доступа за пределами подмассива (индекс >= length)
        TEST_METHOD(IndexerOutOfRangeAccess)
        {
            int size = 5;
            double* a = new double[size] { 1, 2, 3, 4, 5 };
            Indexer ind(a, size, 1, 2);
            auto func1 = [&ind] { ind[2]; };
            Assert::ExpectException<std::out_of_range>(func1);
            auto func2 = [&ind] { ind[-1]; };
            Assert::ExpectException<std::out_of_range>(func2);
            delete[] a;
        }

        // Проверка константного доступа (через константную ссылку)
        TEST_METHOD(IndexerConstAccess)
        {
            int size = 4;
            double* a = new double[size] { 5.5, 6.6, 7.7, 8.8 };
            const Indexer ind(a, size, 1, 2);
            Assert::AreEqual(6.6, ind[0]);
            Assert::AreEqual(7.7, ind[1]);
            // Попытка изменения через константный объект невозможна на этапе компиляции
            delete[] a;
        }

        // Проверка геттеров getStart и getLength
        TEST_METHOD(IndexerGetters)
        {
            int size = 10;
            double* a = new double[size];
            Indexer ind(a, size, 3, 4);
            Assert::AreEqual(3, ind.getStart());
            Assert::AreEqual(4, ind.getLength());
            delete[] a;
        }

        // Проверка, что изменения в исходном массиве видны через Indexer
        TEST_METHOD(IndexerReflectsChangesInOriginalArray)
        {
            int size = 5;
            double* a = new double[size] { 1, 2, 3, 4, 5 };
            Indexer ind(a, size, 1, 3);
            a[2] = 99.9; // меняем элемент, соответствующий ind[1]
            Assert::AreEqual(99.9, ind[1]);
            delete[] a;
        }

        // Проверка, что разные объекты Indexer могут работать с разными частями одного массива
        TEST_METHOD(IndexerMultipleIndexersOnSameArray)
        {
            int size = 8;
            double* a = new double[size] { 10, 20, 30, 40, 50, 60, 70, 80 };
            Indexer ind1(a, size, 1, 3); // 20,30,40
            Indexer ind2(a, size, 4, 2); // 50,60
            ind1[1] = 33.3;
            ind2[0] = 55.5;
            Assert::AreEqual(33.3, a[2]);
            Assert::AreEqual(55.5, a[4]);
            delete[] a;
        }

        // Проверка работы с подмассивом, начинающимся с индекса 0
        TEST_METHOD(IndexerStartsAtZero)
        {
            int size = 3;
            double* a = new double[size] { 100, 200, 300 };
            Indexer ind(a, size, 0, 3);
            Assert::AreEqual(100.0, ind[0]);
            Assert::AreEqual(200.0, ind[1]);
            Assert::AreEqual(300.0, ind[2]);
            ind[0] = 111.0;
            Assert::AreEqual(111.0, a[0]);
            delete[] a;
        }

        // Проверка работы с подмассивом, заканчивающимся последним элементом массива
        TEST_METHOD(IndexerEndsAtLastElement)
        {
            int size = 5;
            double* a = new double[size] { 1, 2, 3, 4, 5 };
            Indexer ind(a, size, 3, 2);
            Assert::AreEqual(4.0, ind[0]);
            Assert::AreEqual(5.0, ind[1]);
            delete[] a;
        }

        // Проверка, что деструктор не удаляет исходный массив (не должен)
        TEST_METHOD(IndexerDoesNotDeleteOriginalArray)
        {
            int size = 3;
            double* a = new double[size] { 1, 2, 3 };
            {
                Indexer ind(a, size, 0, 2);
                ind[0] = 9.9;
            } // ind выходит из области видимости
            Assert::AreEqual(9.9, a[0]);
            Assert::AreEqual(2.0, a[1]);
            Assert::AreEqual(3.0, a[2]);
            delete[] a;
        }
    };
}