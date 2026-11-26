// io.cpp
// Єфіменко Софія
// Лабораторна робота № 10.1 (Рівень В)
// Реалізація введення даних і табличного виведення (9 стовпців)
// Варіант 8

#include "io.h"
#include <iostream>
#include <iomanip>

using namespace std;

const string specStr[5] = {
    "Комп'ютерні науки",
    "Інформатика",
    "Математика та ек.",
    "Фізика та інф.",
    "Трудове навчання"
};

const string profSubjectName[5] = {
    "програмування",
    "чисельних методів",
    "педагогіки",
    "педагогіки",
    "педагогіки"
};

const string subjectTitles[5] = {
    "Фізика            ",
    "Математика        ",
    "Програмування (KN)",
    "Чис. методи (IN)  ",
    "Педагогіка        "
};

void Create(Student* p, const int N) {
    int ispec;
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент № " << i + 1 << ":" << endl;

        cout << "  Прізвище: ";
        getline(cin >> ws, p[i].prizv);

        cout << "  Курс: ";
        cin >> p[i].kurs;

        cout << "  Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та ек., 3 - Фізика та інф., 4 - Трудове навчання): ";
        cin >> ispec;
        if (ispec < 0 || ispec > 4) ispec = 0;
        p[i].spec = (Spec)ispec;

        cout << "  Оцінка з фізики: ";
        cin >> p[i].fizyka;

        cout << "  Оцінка з математики: ";
        cin >> p[i].matematika;

        // Усі поля union (int) ділять спільну область пам'яті
        cout << "  Оцінка з " << profSubjectName[p[i].spec] << ": ";
        cin >> p[i].programuvannya;
    }
}

void Print(const Student* p, const int N) {
    cout << "\n========================================================================================================\n";
    cout << "| " << setw(3)  << right << "№"
         << " | " << setw(14) << left  << "Прізвище"
         << " | " << setw(4)  << right << "Курс"
         << " | " << setw(18) << left  << "Спеціальність"
         << " | " << setw(6)  << right << "Фізика"
         << " | " << setw(6)  << right << "Матем."
         << " | " << setw(6)  << right << "Прогр."
         << " | " << setw(8)  << right << "Чис.мет."
         << " | " << setw(6)  << right << "Педаг."
         << " |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {
        int thirdMark = p[i].programuvannya; // зчитуємо один раз із спільної пам'яті union
        cout << "| " << setw(3)  << right << i + 1
             << " | " << setw(14) << left  << p[i].prizv
             << " | " << setw(4)  << right << p[i].kurs
             << " | " << setw(18) << left  << specStr[p[i].spec]
             << " | " << setw(6)  << right << p[i].fizyka
             << " | " << setw(6)  << right << p[i].matematika
             << " | " << setw(6)  << right << (p[i].spec == KN ? to_string(thirdMark) : "-")
             << " | " << setw(8)  << right << (p[i].spec == IN ? to_string(thirdMark) : "-")
             << " | " << setw(6)  << right << (p[i].spec > IN  ? to_string(thirdMark) : "-")
             << " |\n";
    }
    cout << "========================================================================================================\n";
}
