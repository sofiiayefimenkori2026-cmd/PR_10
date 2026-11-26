// io.cpp
// Єфіменко Софія
// Лабораторна робота № 10.1 (Рівень А)
// Реалізація функцій введення та виведення таблиці
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

const string subjectTitles[3] = {
    "Фізика     ",
    "Математика ",
    "Інформатика"
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

        cout << "  Оцінка з інформатики: ";
        cin >> p[i].informatyka;
    }
}

void Print(const Student* p, const int N) {
    cout << "\n===================================================================================\n";
    cout << "| " << setw(3)  << right << "№"
         << " | " << setw(14) << left  << "Прізвище"
         << " | " << setw(4)  << right << "Курс"
         << " | " << setw(18) << left  << "Спеціальність"
         << " | " << setw(6)  << right << "Фізика"
         << " | " << setw(6)  << right << "Матем."
         << " | " << setw(8)  << right << "Інформ."
         << " |\n";
    cout << "-----------------------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3)  << right << i + 1
             << " | " << setw(14) << left  << p[i].prizv
             << " | " << setw(4)  << right << p[i].kurs
             << " | " << setw(18) << left  << specStr[p[i].spec]
             << " | " << setw(6)  << right << p[i].fizyka
             << " | " << setw(6)  << right << p[i].matematika
             << " | " << setw(8)  << right << p[i].informatyka
             << " |\n";
    }
    cout << "===================================================================================\n";
}
