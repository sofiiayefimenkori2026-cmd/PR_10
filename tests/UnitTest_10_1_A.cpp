#if defined(_MSC_VER)
#include "pch.h"
#include "CppUnitTest.h"
#include "calc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101A
{
    TEST_CLASS(UnitTest101A)
    {
    public:
        TEST_METHOD(TestAveragesAndCount)
        {
            const int N = 3;
            Student students[N] = {
                { "Іваненко", 2, KN, 5, 4, 5 },
                { "Петренко", 1, IN, 4, 5, 4 },
                { "Сидоренко", 3, ME, 3, 3, 5 }
            };

            double avg[3];
            CalcAverages(students, N, avg);

            Assert::AreEqual(4.0, avg[0], 0.001);
            Assert::AreEqual(4.0, avg[1], 0.001);
            Assert::AreEqual(4.6667, avg[2], 0.001);
            Assert::AreEqual(2, CountPhysics5or4(students, N));
        }
    };
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calc.h"

TEST_CASE("Тестування 10.1 (Рівень А)") {
    const int N = 3;
    Student students[N] = {
        { "Іваненко", 2, KN, 5, 4, 5 },
        { "Петренко", 1, IN, 4, 5, 4 },
        { "Сидоренко", 3, ME, 3, 3, 5 }
    };

    double avg[3];
    CalcAverages(students, N, avg);

    CHECK(avg[0] == doctest::Approx(4.0));
    CHECK(avg[1] == doctest::Approx(4.0));
    CHECK(avg[2] == doctest::Approx(14.0 / 3.0));
    CHECK(CountPhysics5or4(students, N) == 2);
}
#endif
