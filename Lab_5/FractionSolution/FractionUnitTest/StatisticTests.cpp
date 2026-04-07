#include "pch.h"
#include "../FractionLib/Statistic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FractionUnitTest
{
    TEST_CLASS(StatisticTests)
    {
    public:
        TEST_METHOD(DefaultConstructor)
        {
            Statistic s;
            Assert::AreEqual((size_t)0, s.size());
        }

        TEST_METHOD(ConstructorWithSize)
        {
            Statistic s(5);
            Assert::AreEqual((size_t)5, s.size());
            for (size_t i = 0; i < 5; ++i)
                Assert::AreEqual(0, s[i]);
        }

        TEST_METHOD(ConstructorFromArray)
        {
            int arr[] = { 1, 2, 3, 4 };
            Statistic s(arr, 4);
            Assert::AreEqual((size_t)4, s.size());
            Assert::AreEqual(2, s[1]);
        }

        TEST_METHOD(CopyAndMove)
        {
            Statistic s1(3);
            s1[0] = 10; s1[1] = 20; s1[2] = 30;
            Statistic s2 = s1;
            Assert::IsTrue(s1.size() == s2.size());
            Assert::AreEqual(s1[1], s2[1]);
            Statistic s3 = std::move(s2);
            Assert::AreEqual((size_t)3, s3.size());
            Assert::AreEqual((size_t)0, s2.size());
        }

        TEST_METHOD(AddElement)
        {
            Statistic s;
            s.add(5);
            s.add(7);
            Assert::AreEqual((size_t)2, s.size());
            Assert::AreEqual(5, s[0]);
            Assert::AreEqual(7, s[1]);
        }

        TEST_METHOD(Mean)
        {
            Statistic s;
            s.add(1); s.add(2); s.add(3);
            Assert::AreEqual(2.0, s.mean(), 1e-9);
        }

        TEST_METHOD(Median)
        {
            Statistic s;
            s.add(5); s.add(1); s.add(3); s.add(2); s.add(4);
            Assert::AreEqual(3.0, s.median());
            s.add(6);
            Assert::AreEqual(3.5, s.median());
        }

        TEST_METHOD(MinMax)
        {
            Statistic s;
            s.add(10); s.add(-5); s.add(7); s.add(0);
            Assert::AreEqual(-5, s.min());
            Assert::AreEqual(10, s.max());
        }
    };
}