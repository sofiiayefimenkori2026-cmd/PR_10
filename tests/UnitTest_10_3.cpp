#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#define main prog_main
#include "../PR_10.3/Lab_10_3.cpp"
#undef main

TEST_CASE("Тестування коригування списку (Add, Remove, Edit) (10.3)") {
    int N = 2;
    StudentGroup* group = new StudentGroup[N];

    group[0].prizv = "Іваненко";
    group[0].mark1 = 4;
    group[0].mark2 = 4;
    group[0].mark3 = 4;

    group[1].prizv = "Петренко";
    group[1].mark1 = 5;
    group[1].mark2 = 5;
    group[1].mark3 = 5;

    // Add
    StudentGroup s3;
    s3.prizv = "Сидоренко";
    s3.mark1 = 3;
    s3.mark2 = 3;
    s3.mark3 = 3;
    AddStudent(group, N, s3);
    CHECK(N == 3);
    CHECK(group[2].prizv == "Сидоренко");

    // Edit
    StudentGroup updated;
    updated.prizv = "Сидоренко-Оновлений";
    updated.mark1 = 5;
    updated.mark2 = 5;
    updated.mark3 = 5;
    CHECK(EditStudent(group, N, 2, updated) == true);
    CHECK(group[2].prizv == "Сидоренко-Оновлений");
    CHECK(group[2].mark1 == 5);

    // Remove
    CHECK(RemoveStudent(group, N, 1) == true); // Remove Петренко
    CHECK(N == 2);
    CHECK(group[0].prizv == "Іваненко");
    CHECK(group[1].prizv == "Сидоренко-Оновлений");

    delete[] group;
}

TEST_CASE("Тестування сортування та файлових операцій (10.3)") {
    int N = 3;
    StudentGroup* group = new StudentGroup[N];

    group[0].prizv = "Яковенко";
    group[0].mark1 = 3; group[0].mark2 = 3; group[0].mark3 = 3; // avg = 3.0

    group[1].prizv = "Бойко";
    group[1].mark1 = 5; group[1].mark2 = 5; group[1].mark3 = 5; // avg = 5.0

    group[2].prizv = "Шевченко";
    group[2].mark1 = 4; group[2].mark2 = 4; group[2].mark3 = 4; // avg = 4.0

    // Сортування за середнім балом (за спаданням)
    SortByAverage(group, N, true);
    CHECK(group[0].prizv == "Бойко");
    CHECK(group[1].prizv == "Шевченко");
    CHECK(group[2].prizv == "Яковенко");

    // Сортування за прізвищем (в алфавітному порядку)
    SortByPrizv(group, N, true);
    CHECK(group[0].prizv == "Бойко");
    CHECK(group[1].prizv == "Шевченко");
    CHECK(group[2].prizv == "Яковенко");

    // Сортування за оцінкою з предмету 1 (за спаданням)
    group[0].mark1 = 3;
    group[1].mark1 = 5;
    group[2].mark1 = 4;
    SortBySubject(group, N, 1, true);
    CHECK(group[0].mark1 == 5);
    CHECK(group[1].mark1 == 4);
    CHECK(group[2].mark1 == 3);

    // Робота з файлом
    const string testFile = "/tmp/test_students_10_3.txt";
    CHECK(SaveToFile(group, N, testFile) == true);

    StudentGroup* loaded = nullptr;
    int loadedN = 0;
    CHECK(LoadFromFile(loaded, loadedN, testFile) == true);
    CHECK(loadedN == 3);
    if (loaded != nullptr) {
        CHECK(loaded[0].mark1 == 5);
        delete[] loaded;
    }

    delete[] group;
    std::remove(testFile.c_str());
}
