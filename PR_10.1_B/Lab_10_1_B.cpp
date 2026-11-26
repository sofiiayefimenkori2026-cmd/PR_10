// Lab_10_1_B.cpp
// Єфіменко Софія
// Лабораторна робота № 10.1 (Рівень В)
// Головний модуль програми
// Варіант 8

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#if defined(_WIN32)
#include <Windows.h>
#endif

#include "student.h"
#include "io.h"
#include "calc.h"

using namespace std;

int main() {
#if defined(_WIN32)
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    if (N <= 0) {
        cout << "Кількість студентів має бути більшою за 0!" << endl;
        return 1;
    }

    Student* p = new Student[N];

    Create(p, N);
    Print(p, N);

    double avg[5];
    int cnt[5];
    CalcAverages(p, N, avg, cnt);

    cout << fixed << setprecision(2);
    cout << "\nСередній бал для кожного предмету:" << endl;
    for (int j = 0; j < 5; j++) {
        cout << "  " << j + 1 << ". " << subjectTitles[j] << ": ";
        if (cnt[j] > 0)
            cout << avg[j] << " (студентів: " << cnt[j] << ")" << endl;
        else
            cout << "немає студентів" << endl;
    }

    int countPhys = CountPhysics5or4(p, N);
    cout << "\nКількість студентів, які отримали з фізики оцінки '5' або '4': " << countPhys << endl;

    delete[] p;
    return 0;
}
