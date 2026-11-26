// calc.cpp
// Єфіменко Софія
// Лабораторна робота № 10.1 (Рівень В)
// Реалізація функцій обчислення середніх балів та підрахунку оцінок
// Варіант 8

#include "calc.h"

// Обчислення середнього балу для всіх 5 предметів за один прохід по масиву:
// 0 - Фізика, 1 - Математика, 2 - Програмування, 3 - Чис. методи, 4 - Педагогіка
void CalcAverages(const Student* p, const int N, double avg[5], int cnt[5]) {
    double sum[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
    for (int j = 0; j < 5; j++) {
        avg[j] = 0.0;
        cnt[j] = 0;
    }

    for (int i = 0; i < N; i++) {
        sum[0] += p[i].fizyka;
        cnt[0]++;

        sum[1] += p[i].matematika;
        cnt[1]++;

        // Прямий доступ до спільної області пам'яті union
        int profIdx = (p[i].spec == KN) ? 2 : (p[i].spec == IN ? 3 : 4);
        sum[profIdx] += p[i].programuvannya;
        cnt[profIdx]++;
    }

    for (int j = 0; j < 5; j++) {
        if (cnt[j] > 0)
            avg[j] = sum[j] / cnt[j];
    }
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
