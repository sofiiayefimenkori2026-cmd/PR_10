// calc.cpp
// Єфіменко Софія
// Лабораторна робота № 10.1 (Рівень А)
// Реалізація функцій обчислення середніх балів та підрахунку оцінок
// Варіант 8

#include "calc.h"

// Обчислення середнього балу для кожного з 3 предметів за один прохід
void CalcAverages(const Student* p, const int N, double avg[3]) {
    avg[0] = avg[1] = avg[2] = 0.0;
    if (N <= 0) return;

    double sum[3] = { 0.0, 0.0, 0.0 };
    for (int i = 0; i < N; i++) {
        sum[0] += p[i].fizyka;
        sum[1] += p[i].matematika;
        sum[2] += p[i].informatyka;
    }

    for (int j = 0; j < 3; j++)
        avg[j] = sum[j] / N;
}

// Кількість студентів, які отримали з фізики оцінки "5" або "4"
int CountPhysics5or4(const Student* p, const int N) {
    int k = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].fizyka == 5 || p[i].fizyka == 4)
            k++;
    }
    return k;
}
