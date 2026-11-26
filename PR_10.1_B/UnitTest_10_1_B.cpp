#if defined(_MSC_VER)
#include "pch.h"
#include "CppUnitTest.h"
#include "calc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101B
{
    TEST_CLASS(UnitTest101B)
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

            double avg[5];
            int cnt[5];
            CalcAverages(students, N, avg, cnt);

            Assert::AreEqual(4.0, avg[0], 0.001);
            Assert::AreEqual(4.0, avg[1], 0.001);
            Assert::AreEqual(5.0, avg[2], 0.001);
            Assert::AreEqual(4.0, avg[3], 0.001);
            Assert::AreEqual(5.0, avg[4], 0.001);
            Assert::AreEqual(2, CountPhysics5or4(students, N));
        }
    };
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest.h"
#include "calc.h"

TEST_CASE("Тестування 10.1 (Рівень В)") {
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

    double avg[5];
    int cnt[5];
    CalcAverages(students, N, avg, cnt);

    CHECK(avg[0] == doctest::Approx(4.0));
    CHECK(avg[1] == doctest::Approx(4.0));
    CHECK(avg[2] == doctest::Approx(5.0));
    CHECK(avg[3] == doctest::Approx(4.0));
    CHECK(avg[4] == doctest::Approx(5.0));
    CHECK(CountPhysics5or4(students, N) == 2);
}
#endif
