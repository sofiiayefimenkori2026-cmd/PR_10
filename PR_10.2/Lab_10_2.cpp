// Lab_10_2.cpp
// Єфіменко Софія
// Лабораторна робота № 10.2
// Впорядкування та бінарний пошук в масиві структур. Рівень В.
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

// Структура студента
struct Student {
    string prizv;
    int kurs;
    Spec spec;
    int fizyka;
    int matematika;
    union {
        int programuvannya;   // для KN
        int chyselni_metody;  // для IN
        int pedagogika;       // для ME, FI, TN
    };
};

// Прототипи функцій
void Create(Student* p, const int N);
void Print(const Student* p, const int N);
int GetThirdMark(const Student& s);
bool ShouldPrecede(const Student& a, const Student& b);
void Sort(Student* p, const int N);
int* IndexSort(const Student* p, const int N);
void PrintIndexSorted(const Student* p, const int* I, const int N);
int CompareStudents(const Student& s, int kurs, int thirdMark, const string& prizv);
int BinSearch(const Student* p, const int N, const string& prizv, const int kurs, const int thirdMark);

// Отримання оцінки з 3-го (профільного) предмету
int GetThirdMark(const Student& s) {
    switch (s.spec) {
    case KN:
        return s.programuvannya;
    case IN:
        return s.chyselni_metody;
    case ME:
    case FI:
    case TN:
    default:
        return s.pedagogika;
    }
}

// Умова впорядкування для Варіанту 8:
// 1-й ключ: курс за зростанням
// 2-й ключ: оцінка з 3-го предмету за зростанням
// 3-й ключ: прізвище за спаданням (у зворотному до алфавітного порядку)
bool ShouldPrecede(const Student& a, const Student& b) {
    if (a.kurs != b.kurs)
        return a.kurs < b.kurs;
    int ma = GetThirdMark(a);
    int mb = GetThirdMark(b);
    if (ma != mb)
        return ma < mb;
    return a.prizv > b.prizv; // за спаданням прізвища
}

// Введення даних
void Create(Student* p, const int N) {
    int ispec;
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент № " << i + 1 << ":" << endl;
        cin.get();
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

// Табличний вивід
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

// Фізичне впорядкування масиву структур (бульбашкове сортування)
void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            if (ShouldPrecede(p[i1 + 1], p[i1])) {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}

// Індексне впорядкування масиву структур (сортування вставками)
int* IndexSort(const Student* p, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    for (int i = 1; i < N; i++) {
        int value = I[i];
        int j = i - 1;
        while (j >= 0 && ShouldPrecede(p[value], p[I[j]])) {
            I[j + 1] = I[j];
            j--;
        }
        I[j + 1] = value;
    }
    return I;
}

// Вивід масиву за індексами
void PrintIndexSorted(const Student* p, const int* I, const int N) {
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
        int idx = I[i];
        cout << "| " << setw(3)  << right << i + 1
             << " | " << setw(14) << left  << p[idx].prizv
             << " | " << setw(4)  << right << p[idx].kurs
             << " | " << setw(18) << left  << specStr[p[idx].spec]
             << " | " << setw(6)  << right << p[idx].fizyka
             << " | " << setw(6)  << right << p[idx].matematika;

        switch (p[idx].spec) {
        case KN:
            cout << " | " << setw(6)  << right << p[idx].programuvannya
                 << " | " << setw(8)  << right << "-"
                 << " | " << setw(6)  << right << "-"
                 << " |\n";
            break;
        case IN:
            cout << " | " << setw(6)  << right << "-"
                 << " | " << setw(8)  << right << p[idx].chyselni_metody
                 << " | " << setw(6)  << right << "-"
                 << " |\n";
            break;
        case ME:
        case FI:
        case TN:
        default:
            cout << " | " << setw(6)  << right << "-"
                 << " | " << setw(8)  << right << "-"
                 << " | " << setw(6)  << right << p[idx].pedagogika
                 << " |\n";
            break;
        }
    }
    cout << "========================================================================================================\n";
}

// Порівняння елемента зі значеннями пошуку:
// повертає < 0 якщо s передує шуканому, > 0 якщо s слідує за шуканим, 0 якщо знайдено точний збіг
int CompareStudents(const Student& s, int kurs, int thirdMark, const string& prizv) {
    if (s.kurs != kurs)
        return (s.kurs < kurs) ? -1 : 1;
    int tm = GetThirdMark(s);
    if (tm != thirdMark)
        return (tm < thirdMark) ? -1 : 1;
    if (s.prizv > prizv) return -1; // більше прізвище стоїть раніше при спаданні
    if (s.prizv < prizv) return 1;
    return 0;
}

// Бінарний пошук у фізично впорядкованому масиві
int BinSearch(const Student* p, const int N, const string& prizv, const int kurs, const int thirdMark) {
    int L = 0, R = N - 1, m;
    while (L <= R) {
        m = (L + R) / 2;
        int cmp = CompareStudents(p[m], kurs, thirdMark, prizv);
        if (cmp == 0)
            return m;
        if (cmp < 0)
            L = m + 1;
        else
            R = m - 1;
    }
    return -1;
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
    int* I = nullptr;

    int menuItem;
    do {
        cout << "\n================= МЕНЮ =================" << endl;
        cout << "  [1] - Введення даних з клавіатури" << endl;
        cout << "  [2] - Вивід даних на екран" << endl;
        cout << "  [3] - Фізичне впорядкування даних" << endl;
        cout << "  [4] - Бінарний пошук студента" << endl;
        cout << "  [5] - Індексне впорядкування та вивід" << endl;
        cout << "  [0] - Вихід та завершення роботи" << endl;
        cout << "========================================" << endl;
        cout << "Ваш вибір: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "\nМасив успішно фізично впорядковано (курс зрост. -> оцінка 3-го предм. зрост. -> прізвище спад.):" << endl;
            Print(p, N);
            break;
        case 4: {
            string searchPrizv;
            int searchKurs, searchMark;
            cout << "\n--- Бінарний пошук студента ---" << endl;
            cin.get();
            cin.sync();
            cout << "Введіть прізвище: ";
            getline(cin, searchPrizv);
            cout << "Введіть курс: ";
            cin >> searchKurs;
            cout << "Введіть оцінку з 3-го (профільного) предмету: ";
            cin >> searchMark;

            int foundIdx = BinSearch(p, N, searchPrizv, searchKurs, searchMark);
            if (foundIdx != -1) {
                cout << "\nСтудента ЗНАЙДЕНО під номером " << foundIdx + 1 << " у впорядкованому масиві:" << endl;
                cout << "  Прізвище:      " << p[foundIdx].prizv << endl;
                cout << "  Курс:          " << p[foundIdx].kurs << endl;
                cout << "  Спеціальність: " << specStr[p[foundIdx].spec] << endl;
                cout << "  Оцінка 3 предм: " << GetThirdMark(p[foundIdx]) << endl;
            } else {
                cout << "\nСтудента із зазначеними даними НЕ знайдено (переконайтеся, що масив попередньо впорядковано [3])!" << endl;
            }
            break;
        }
        case 5:
            if (I != nullptr) delete[] I;
            I = IndexSort(p, N);
            cout << "\nРезультат індексного впорядкування:" << endl;
            PrintIndexSorted(p, I, N);
            break;
        case 0:
            cout << "\nЗавершення роботи програми." << endl;
            break;
        default:
            cout << "Помилкове значення! Виберіть номер від 0 до 5." << endl;
            break;
        }
    } while (menuItem != 0);

    if (I != nullptr) delete[] I;
    delete[] p;
    return 0;
}
