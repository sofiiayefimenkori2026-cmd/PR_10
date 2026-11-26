#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#define main prog_main
#include "../PR_10.2/Lab_10_2.cpp"
#undef main

TEST_CASE("Тестування фізичного впорядкування (Sort) та індексного сортування (IndexSort)") {
    const int N = 4;
    Student students[N];

    // Студент 0: курс 2, профіHard 5, "Бойко"
    students[0].prizv = "Бойко";
    students[0].kurs = 2;
    students[0].spec = KN;
    students[0].programuvannya = 5;

    // Студент 1: курс 1, профіHard 4, "Коваль"
    students[1].prizv = "Коваль";
    students[1].kurs = 1;
    students[1].spec = IN;
    students[1].chyselni_metody = 4;

    // Студент 2: курс 2, профіHard 5, "Шевченко" (той самий курс 2 і оцінка 5, але прізвище більше => має бути раніше)
    students[2].prizv = "Шевченко";
    students[2].kurs = 2;
    students[2].spec = KN;
    students[2].programuvannya = 5;

    // Студент 3: курс 2, профіHard 3, "Мельник"
    students[3].prizv = "Мельник";
    students[3].kurs = 2;
    students[3].spec = ME;
    students[3].pedagogika = 3;

    // Індексне сортування
    int* I = IndexSort(students, N);

    // Очікуваний порядок:
    // 1-й: курс 1 (Коваль) -> індекс 1
    // 2-й: курс 2, оцінка 3 (Мельник) -> індекс 3
    // 3-й: курс 2, оцінка 5, прізвище спадання -> "Шевченко" (індекс 2)
    // 4-й: курс 2, оцінка 5, прізвище спадання -> "Бойко" (індекс 0)

    CHECK(I[0] == 1);
    CHECK(I[1] == 3);
    CHECK(I[2] == 2);
    CHECK(I[3] == 0);

    // Тепер фізичне сортування
    Sort(students, N);

    CHECK(students[0].prizv == "Коваль");
    CHECK(students[1].prizv == "Мельник");
    CHECK(students[2].prizv == "Шевченко");
    CHECK(students[3].prizv == "Бойко");

    delete[] I;
}

TEST_CASE("Тестування бінарного пошуку (BinSearch)") {
    const int N = 3;
    Student students[N];

    students[0].prizv = "Коваль";
    students[0].kurs = 1;
    students[0].spec = IN;
    students[0].chyselni_metody = 4;

    students[1].prizv = "Шевченко";
    students[1].kurs = 2;
    students[1].spec = KN;
    students[1].programuvannya = 5;

    students[2].prizv = "Бойко";
    students[2].kurs = 2;
    students[2].spec = KN;
    students[2].programuvannya = 5;

    // Вже впорядкований масив
    CHECK(BinSearch(students, N, "Шевченко", 2, 5) == 1);
    CHECK(BinSearch(students, N, "Коваль", 1, 4) == 0);
    CHECK(BinSearch(students, N, "Бойко", 2, 5) == 2);
    CHECK(BinSearch(students, N, "Невідомий", 2, 5) == -1);
    CHECK(BinSearch(students, N, "Шевченко", 3, 5) == -1);
}
