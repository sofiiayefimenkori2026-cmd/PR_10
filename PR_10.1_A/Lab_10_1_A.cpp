// Lab_10_1_A.cpp
// Єфіменко Софія
// Лабораторна робота № 10.1 (Рівень А)
// Послідовний пошук в масиві структур.
// Варіант 8

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#if defined(_WIN32)
#include <Windows.h>
#endif

using namespace std;

// Перелік спеціальностей (Рівень А)
enum Spec { KN, IN, ME, FI, TN };

const string specStr[] = {
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

// Структура студента (Рівень А: 3 предмети без об'єднання)
struct Student {
    string prizv;
    int kurs;
    Spec spec;
    int fizyka;
    int matematika;
    int informatyka;
};

// Прототипи функцій
void Create(Student* p, const int N);
void Print(const Student* p, const int N);
void CalcAverages(const Student* p, const int N, double avg[3]);
int CountPhysics5or4(const Student* p, const int N);

// Введення даних про студентів
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

// Вивід масиву у вигляді таблиці (7 стовпців)
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

// Обчислення середнього балу для кожного з 3 предметів за один прохід по масиву:
// індекси: 0 - Фізика, 1 - Математика, 2 - Інформатика
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
        if (p[i].fizyka == 5 || p[i].fizyka == 4) {
            k++;
        }
    }
    return k;
}

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

    double avg[3];
    CalcAverages(p, N, avg);

    cout << fixed << setprecision(2);
    cout << "\nСередній бал для кожного предмету:" << endl;
    for (int j = 0; j < 3; j++) {
        cout << "  " << j + 1 << ". " << subjectTitles[j] << ": " << avg[j] << endl;
    }

    int countPhys = CountPhysics5or4(p, N);
    cout << "\nКількість студентів, які отримали з фізики оцінки '5' або '4': " << countPhys << endl;

    delete[] p;
    return 0;
}
