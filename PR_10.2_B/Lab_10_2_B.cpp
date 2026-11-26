// Lab_10_2_B.cpp
// Єфіменко Софія
// Лабораторна робота № 10.2 (Рівень В)
// Впорядкування та бінарний пошук в масиві структур. Рівень В.
// Варіант 8

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
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

const string profSubjectName[] = {
    "програмування",
    "чисельних методів",
    "педагогіки",
    "педагогіки",
    "педагогіки"
};

// Структура студента з анонімним об'єднанням для третьої оцінки.
// Усі поля union (int) займають одну й ту саму область пам'яті.
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
void PrintHeader();
void PrintRow(const Student& s, int rowNum);
void Print(const Student* p, const int N);
bool ShouldPrecede(const Student& a, const Student& b);
void Sort(Student* p, const int N);
int* IndexSort(const Student* p, const int N);
void PrintIndexSorted(const Student* p, const int* I, const int N);
int CompareStudents(const Student& s, int kurs, int thirdMark, const string& prizv);
int BinSearch(const Student* p, const int N, const string& prizv, const int kurs, const int thirdMark);

// Умова впорядкування для Варіанту 8:
// 1-й ключ: курс за зростанням
// 2-й ключ: оцінка з 3-го предмету за зростанням (береться напряму з union)
// 3-й ключ: прізвище за спаданням (у зворотному до алфавітного порядку)
bool ShouldPrecede(const Student& a, const Student& b) {
    if (a.kurs != b.kurs)
        return a.kurs < b.kurs;
    if (a.programuvannya != b.programuvannya) // спільна область пам'яті union
        return a.programuvannya < b.programuvannya;
    return a.prizv > b.prizv;
}

// Введення даних
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

// Шапка таблиці
void PrintHeader() {
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
}

// Вивід одного рядка таблиці (без дублювання коду в Print та PrintIndexSorted)
void PrintRow(const Student& s, int rowNum) {
    int thirdMark = s.programuvannya; // зчитуємо один раз із спільної пам'яті union
    cout << "| " << setw(3)  << right << rowNum
         << " | " << setw(14) << left  << s.prizv
         << " | " << setw(4)  << right << s.kurs
         << " | " << setw(18) << left  << specStr[s.spec]
         << " | " << setw(6)  << right << s.fizyka
         << " | " << setw(6)  << right << s.matematika
         << " | " << setw(6)  << right << (s.spec == KN ? to_string(thirdMark) : "-")
         << " | " << setw(8)  << right << (s.spec == IN ? to_string(thirdMark) : "-")
         << " | " << setw(6)  << right << (s.spec > IN  ? to_string(thirdMark) : "-")
         << " |\n";
}

// Табличний вивід основного масиву
void Print(const Student* p, const int N) {
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[i], i + 1);
    cout << "========================================================================================================\n";
}

// Фізичне впорядкування масиву структур (бульбашкове сортування з оптимізацією та std::swap)
void Sort(Student* p, const int N) {
    for (int i0 = 0; i0 < N - 1; i0++) {
        bool swapped = false;
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            if (ShouldPrecede(p[i1 + 1], p[i1])) {
                swap(p[i1], p[i1 + 1]); // переміщення без зайвого копіювання string
                swapped = true;
            }
        }
        if (!swapped) break;
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

// Вивід масиву за індексним масивом
void PrintIndexSorted(const Student* p, const int* I, const int N) {
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[I[i]], i + 1);
    cout << "========================================================================================================\n";
}

// Порівняння елемента зі значеннями пошуку:
// повертає < 0 якщо s передує шуканому, > 0 якщо s слідує за шуканим, 0 якщо знайдено точний збіг
int CompareStudents(const Student& s, int kurs, int thirdMark, const string& prizv) {
    if (s.kurs != kurs)
        return (s.kurs < kurs) ? -1 : 1;
    if (s.programuvannya != thirdMark) // спільна область пам'яті union
        return (s.programuvannya < thirdMark) ? -1 : 1;
    if (s.prizv > prizv) return -1;    // більше прізвище стоїть раніше при спаданні
    if (s.prizv < prizv) return 1;
    return 0;
}

// Бінарний пошук у фізично впорядкованому масиві
int BinSearch(const Student* p, const int N, const string& prizv, const int kurs, const int thirdMark) {
    int L = 0, R = N - 1;
    while (L <= R) {
        int m = L + (R - L) / 2;
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
            cout << "Введіть прізвище: ";
            getline(cin >> ws, searchPrizv);
            cout << "Введіть курс: ";
            cin >> searchKurs;
            cout << "Введіть оцінку з 3-го (профільного) предмету: ";
            cin >> searchMark;

            int foundIdx = BinSearch(p, N, searchPrizv, searchKurs, searchMark);
            if (foundIdx != -1) {
                cout << "\nСтудента ЗНАЙДЕНО під номером " << foundIdx + 1 << " у впорядкованому масиві:" << endl;
                cout << "  Прізвище:       " << p[foundIdx].prizv << endl;
                cout << "  Курс:           " << p[foundIdx].kurs << endl;
                cout << "  Спеціальність:  " << specStr[p[foundIdx].spec] << endl;
                cout << "  Оцінка 3 предм: " << p[foundIdx].programuvannya << endl;
            } else {
                cout << "\nСтудента із зазначеними даними НЕ знайдено (переконайтеся, що масив попередньо впорядковано [3])!" << endl;
            }
            break;
        }
        case 5:
            delete[] I;
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

    delete[] I;
    delete[] p;
    return 0;
}
