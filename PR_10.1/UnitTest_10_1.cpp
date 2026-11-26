#if defined(_MSC_VER)
#include "pch.h"
#include "CppUnitTest.h"
#define main prog_main
#include "Lab_10_1.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101
{
    TEST_CLASS(UnitTest101)
    {
    public:
        TEST_METHOD(TestAveragesAndCount)
        {
            const int N = 3;
            Student students[N];

            students[0].prizv = "Іваненко";
            students[0].kurs = 2;
            students[0].spec = KN;
            students[0].fizyka = 5;
            students[0].matematika = 4;
            students[0].programuvannya = 5;

            students[1].prizv = "Петренко";
            students[1].kurs = 1;
            students[1].spec = IN;
            students[1].fizyka = 4;
            students[1].matematika = 5;
            students[1].chyselni_metody = 4;

            students[2].prizv = "Сидоренко";
            students[2].kurs = 3;
            students[2].spec = ME;
            students[2].fizyka = 3;
            students[2].matematika = 3;
            students[2].pedagogika = 5;

            Assert::AreEqual(4.0, AvgPhysics(students, N), 0.001);
            Assert::AreEqual(4.0, AvgMath(students, N), 0.001);

            int cProg = 0;
            Assert::AreEqual(5.0, AvgProg(students, N, cProg), 0.001);
            Assert::AreEqual(1, cProg);

            Assert::AreEqual(2, CountPhysics5or4(students, N));
        }
    };
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest.h"
#define main prog_main
#include "Lab_10_1.cpp"
#undef main

TEST_CASE("Тестування 10.1") {
    const int N = 3;
    Student students[N];

    students[0].prizv = "Іваненко";
    students[0].kurs = 2;
    students[0].spec = KN;
    students[0].fizyka = 5;
    students[0].matematika = 4;
    students[0].programuvannya = 5;

    students[1].prizv = "Петренко";
    students[1].kurs = 1;
    students[1].spec = IN;
    students[1].fizyka = 4;
    students[1].matematika = 5;
    students[1].chyselni_metody = 4;

    students[2].prizv = "Сидоренко";
    students[2].kurs = 3;
    students[2].spec = ME;
    students[2].fizyka = 3;
    students[2].matematika = 3;
    students[2].pedagogika = 5;

    CHECK(AvgPhysics(students, N) == doctest::Approx(4.0));
    CHECK(AvgMath(students, N) == doctest::Approx(4.0));
    CHECK(CountPhysics5or4(students, N) == 2);
}
#endif
