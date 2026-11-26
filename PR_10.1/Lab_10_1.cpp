// Lab_10_1.cpp
// Єфіменко Софія
// Лабораторна робота № 10.1
// Послідовний пошук в масиві структур. Рівень В.
// Варіант 8

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#if defined(_WIN32)
#include <Windows.h>
#endif

using namespace std;

// Перелік спеціальностей (Рівень В)
enum Spec { KN, IN, ME, FI, TN };

const string specStr[] = {
    "Комп'ютерні науки",
    "Інформатика",
    "Математика та ек.",
    "Фізика та інф.",
    "Трудове навчання"
};

// Структура студента з об'єднанням для третьої оцінки
struct Student {
    string prizv;
    int kurs;
    Spec spec;
    int fizyka;
    int matematika;
    union {
        int programuvannya;   // для спеціальності KN
        int chyselni_metody;  // для спеціальності IN
        int pedagogika;       // для спеціальностей ME, FI, TN
    };
};

// Прототипи функцій
void Create(Student* p, const int N);
void Print(const Student* p, const int N);
double AvgPhysics(const Student* p, const int N);
double AvgMath(const Student* p, const int N);
double AvgProg(const Student* p, const int N, int& count);
double AvgNumMethods(const Student* p, const int N, int& count);
double AvgPedagogy(const Student* p, const int N, int& count);
int CountPhysics5or4(const Student* p, const int N);

// Реалізація введення даних
void Create(Student* p, const int N) {
    int ispec;
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент № " << i + 1 << ":" << endl;
        cin.get(); // очищення буфера
        cin.sync();

        cout << "  Прізвище: ";
        getline(cin, p[i].prizv);

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

        switch (p[i].spec) {
        case KN:
            cout << "  Оцінка з програмування: ";
            cin >> p[i].programuvannya;
            break;
        case IN:
            cout << "  Оцінка з чисельних методів: ";
            cin >> p[i].chyselni_metody;
            break;
        case ME:
        case FI:
        case TN:
        default:
            cout << "  Оцінка з педагогіки: ";
            cin >> p[i].pedagogika;
            break;
        }
    }
}

// Вивід масиву у вигляді таблиці (9 стовпців)
void Print(const Student* p, const int N) {
    cout << "\n========================================================================================================\n";
    cout << "| " << setw(3)  << right << "№"
         << " | " << setw(14) << left  << "Прізвище"
         << " | " << setw(4)  << right << "Курс"
         << " | " << setw(18) << left  << "Спеціальність"
         << " | " << setw(6)  << right << "Фізика"
         << " | " << setw(6)  << right << "Матем."
         << " | " << setw(6)  << right << "Прогр."
         << " | " << setw(6)  << right << "Чис.мет."
         << " | " << setw(6)  << right << "Педаг."
         << " |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3)  << right << i + 1
             << " | " << setw(14) << left  << p[i].prizv
             << " | " << setw(4)  << right << p[i].kurs
             << " | " << setw(18) << left  << specStr[p[i].spec]
             << " | " << setw(6)  << right << p[i].fizyka
             << " | " << setw(6)  << right << p[i].matematika;

        switch (p[i].spec) {
        case KN:
            cout << " | " << setw(6)  << right << p[i].programuvannya
                 << " | " << setw(8)  << right << "-"
                 << " | " << setw(6)  << right << "-"
                 << " |\n";
            break;
        case IN:
            cout << " | " << setw(6)  << right << "-"
                 << " | " << setw(8)  << right << p[i].chyselni_metody
                 << " | " << setw(6)  << right << "-"
                 << " |\n";
            break;
        case ME:
        case FI:
        case TN:
        default:
            cout << " | " << setw(6)  << right << "-"
                 << " | " << setw(8)  << right << "-"
                 << " | " << setw(6)  << right << p[i].pedagogika
                 << " |\n";
            break;
        }
    }
    cout << "========================================================================================================\n";
}

// Середній бал з фізики
double AvgPhysics(const Student* p, const int N) {
    if (N <= 0) return 0.0;
    double s = 0.0;
    for (int i = 0; i < N; i++) {
        s += p[i].fizyka;
    }
    return s / N;
}

// Середній бал з математики
double AvgMath(const Student* p, const int N) {
    if (N <= 0) return 0.0;
    double s = 0.0;
    for (int i = 0; i < N; i++) {
        s += p[i].matematika;
    }
    return s / N;
}

// Середній бал з програмування (тільки спеціальність KN)
double AvgProg(const Student* p, const int N, int& count) {
    count = 0;
    double s = 0.0;
    for (int i = 0; i < N; i++) {
        if (p[i].spec == KN) {
            s += p[i].programuvannya;
            count++;
        }
    }
    return (count > 0) ? (s / count) : 0.0;
}

// Середній бал з чисельних методів (тільки спеціальність IN)
double AvgNumMethods(const Student* p, const int N, int& count) {
    count = 0;
    double s = 0.0;
    for (int i = 0; i < N; i++) {
        if (p[i].spec == IN) {
            s += p[i].chyselni_metody;
            count++;
        }
    }
    return (count > 0) ? (s / count) : 0.0;
}

// Середній бал з педагогіки (інші спеціальності: ME, FI, TN)
double AvgPedagogy(const Student* p, const int N, int& count) {
    count = 0;
    double s = 0.0;
    for (int i = 0; i < N; i++) {
        if (p[i].spec == ME || p[i].spec == FI || p[i].spec == TN) {
            s += p[i].pedagogika;
            count++;
        }
    }
    return (count > 0) ? (s / count) : 0.0;
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

    cout << fixed << setprecision(2);
    cout << "\nСередній бал для кожного предмету:" << endl;
    cout << "  1. Фізика:             " << AvgPhysics(p, N) << endl;
    cout << "  2. Математика:         " << AvgMath(p, N) << endl;

    int cProg = 0, cNum = 0, cPed = 0;
    double avgP = AvgProg(p, N, cProg);
    double avgN = AvgNumMethods(p, N, cNum);
    double avgPed = AvgPedagogy(p, N, cPed);

    if (cProg > 0)
        cout << "  3. Програмування (KN): " << avgP << " (студентів: " << cProg << ")" << endl;
    else
        cout << "  3. Програмування (KN): немає студентів цієї спеціальності" << endl;

    if (cNum > 0)
        cout << "  4. Чис. методи (IN):   " << avgN << " (студентів: " << cNum << ")" << endl;
    else
        cout << "  4. Чис. методи (IN):   немає студентів цієї спеціальності" << endl;

    if (cPed > 0)
        cout << "  5. Педагогіка:         " << avgPed << " (студентів: " << cPed << ")" << endl;
    else
        cout << "  5. Педагогіка:         немає студентів цих спеціальностей" << endl;

    int countPhys = CountPhysics5or4(p, N);
    cout << "\nКількість студентів, які отримали з фізики оцінки '5' або '4': " << countPhys << endl;

    delete[] p;
    return 0;
}
