#if defined(_MSC_VER)
#include "pch.h"
#include "CppUnitTest.h"
#define main prog_main
#include "Lab_10_3.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest103
{
    TEST_CLASS(UnitTest103)
    {
    public:
        TEST_METHOD(TestGroupOperations)
        {
            int N = 2;
            StudentGroup* group = new StudentGroup[N];

            group[0].prizv = "Іваненко";
            group[0].mark1 = 4; group[0].mark2 = 4; group[0].mark3 = 4;

            group[1].prizv = "Петренко";
            group[1].mark1 = 5; group[1].mark2 = 5; group[1].mark3 = 5;

            StudentGroup s3;
            s3.prizv = "Сидоренко";
            s3.mark1 = 3; s3.mark2 = 3; s3.mark3 = 3;
            AddStudent(group, N, s3);
            Assert::AreEqual(3, N);

            SortByAverage(group, N, true);
            Assert::AreEqual(std::string("Петренко"), group[0].prizv);

            delete[] group;
        }
    };
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest.h"
#define main prog_main
#include "Lab_10_3.cpp"
#undef main

TEST_CASE("Тестування 10.3") {
    int N = 2;
    StudentGroup* group = new StudentGroup[N];

    group[0].prizv = "Іваненко";
    group[0].mark1 = 4; group[0].mark2 = 4; group[0].mark3 = 4;

    group[1].prizv = "Петренко";
    group[1].mark1 = 5; group[1].mark2 = 5; group[1].mark3 = 5;

    StudentGroup s3;
    s3.prizv = "Сидоренко";
    s3.mark1 = 3; s3.mark2 = 3; s3.mark3 = 3;
    AddStudent(group, N, s3);
    CHECK(N == 3);

    SortByAverage(group, N, true);
    CHECK(group[0].prizv == "Петренко");

    delete[] group;
}
#endif
