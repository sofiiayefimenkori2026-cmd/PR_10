#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#define main prog_main
#include "../PR_10.1/Lab_10_1.cpp"
#undef main

TEST_CASE("Тестування розрахунку середнього балу для предметів (10.1)") {
    const int N = 3;
    Student students[N];

    // Студент 1: KN
    students[0].prizv = "Іваненко";
    students[0].kurs = 2;
    students[0].spec = KN;
    students[0].fizyka = 5;
    students[0].matematika = 4;
    students[0].programuvannya = 5;

    // Студент 2: IN
    students[1].prizv = "Петренко";
    students[1].kurs = 1;
    students[1].spec = IN;
    students[1].fizyka = 4;
    students[1].matematika = 5;
    students[1].chyselni_metody = 4;

    // Студент 3: ME
    students[2].prizv = "Сидоренко";
    students[2].kurs = 3;
    students[2].spec = ME;
    students[2].fizyka = 3;
    students[2].matematika = 3;
    students[2].pedagogika = 5;

    CHECK(AvgPhysics(students, N) == doctest::Approx(4.0));
    CHECK(AvgMath(students, N) == doctest::Approx(4.0));

    int cProg = 0, cNum = 0, cPed = 0;
    CHECK(AvgProg(students, N, cProg) == doctest::Approx(5.0));
    CHECK(cProg == 1);

    CHECK(AvgNumMethods(students, N, cNum) == doctest::Approx(4.0));
    CHECK(cNum == 1);

    CHECK(AvgPedagogy(students, N, cPed) == doctest::Approx(5.0));
    CHECK(cPed == 1);
}

TEST_CASE("Тестування підрахунку студентів з оцінками 5 або 4 з фізики (10.1)") {
    const int N = 4;
    Student students[N];

    students[0].fizyka = 5;
    students[1].fizyka = 4;
    students[2].fizyka = 3;
    students[3].fizyka = 2;

    CHECK(CountPhysics5or4(students, N) == 2);
}
