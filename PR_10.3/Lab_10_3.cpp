// Lab_10_3.cpp
// Єфіменко Софія
// Лабораторна робота № 10.3
// Опрацювання масиву структур (коригування списку, сортування, робота з файлами).
// Варіант 8

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#if defined(_WIN32)
#include <Windows.h>
#endif

using namespace std;

// Елемент списку студентської групи: прізвище та 3 екзаменаційні оцінки
struct StudentGroup {
    string prizv;
    int mark1; // Оцінка 1
    int mark2; // Оцінка 2
    int mark3; // Оцінка 3

    double GetAverage() const {
        return (mark1 + mark2 + mark3) / 3.0;
    }
};

// Прототипи функцій
void CreateList(StudentGroup*& p, int& N);
void PrintList(const StudentGroup* p, const int N);
void AddStudent(StudentGroup*& p, int& N, const StudentGroup& newStudent);
bool RemoveStudent(StudentGroup*& p, int& N, const int index);
bool EditStudent(StudentGroup* p, const int N, const int index, const StudentGroup& updated);
void SortByAverage(StudentGroup* p, const int N, bool descending = true);
void SortByPrizv(StudentGroup* p, const int N, bool ascending = true);
void SortBySubject(StudentGroup* p, const int N, const int subjectIndex, bool descending = true);
bool SaveToFile(const StudentGroup* p, const int N, const string& filename);
bool LoadFromFile(StudentGroup*& p, int& N, const string& filename);

// Введення початкового списку
void CreateList(StudentGroup*& p, int& N) {
    if (p != nullptr) {
        delete[] p;
        p = nullptr;
    }

    cout << "Введіть кількість студентів N: ";
    cin >> N;
    while (N <= 0) {
        cout << "Кількість студентів має бути > 0! Повторіть введення: ";
        cin >> N;
    }

    p = new StudentGroup[N];
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << "  Прізвище: ";
        getline(cin, p[i].prizv);

        cout << "  Оцінка 1 (наприклад, Математика): ";
        cin >> p[i].mark1;

        cout << "  Оцінка 2 (наприклад, Фізика):     ";
        cin >> p[i].mark2;

        cout << "  Оцінка 3 (наприклад, Інформатика):";
        cin >> p[i].mark3;
    }
}

// Вивід списку у вигляді таблиці
void PrintList(const StudentGroup* p, const int N) {
    if (p == nullptr || N <= 0) {
        cout << "\nСписок студентів порожній!" << endl;
        return;
    }

    cout << "\n========================================================================\n";
    cout << "| " << setw(3)  << right << "№"
         << " | " << setw(18) << left  << "Прізвище"
         << " | " << setw(7)  << right << "Оцінка 1"
         << " | " << setw(7)  << right << "Оцінка 2"
         << " | " << setw(7)  << right << "Оцінка 3"
         << " | " << setw(8)  << right << "Сер. бал"
         << " |\n";
    cout << "------------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3)  << right << i + 1
             << " | " << setw(18) << left  << p[i].prizv
             << " | " << setw(7)  << right << p[i].mark1
             << " | " << setw(7)  << right << p[i].mark2
             << " | " << setw(7)  << right << p[i].mark3
             << " | " << setw(8)  << fixed << setprecision(2) << right << p[i].GetAverage()
             << " |\n";
    }
    cout << "========================================================================\n";
}

// Додавання студента (Add)
void AddStudent(StudentGroup*& p, int& N, const StudentGroup& newStudent) {
    StudentGroup* newArr = new StudentGroup[N + 1];
    for (int i = 0; i < N; i++) {
        newArr[i] = p[i];
    }
    newArr[N] = newStudent;

    if (p != nullptr) delete[] p;
    p = newArr;
    N++;
}

// Вилучення студента за номером індексу 0..N-1 (Remove)
bool RemoveStudent(StudentGroup*& p, int& N, const int index) {
    if (index < 0 || index >= N || N <= 0)
        return false;

    if (N == 1) {
        delete[] p;
        p = nullptr;
        N = 0;
        return true;
    }

    StudentGroup* newArr = new StudentGroup[N - 1];
    int k = 0;
    for (int i = 0; i < N; i++) {
        if (i == index) continue;
        newArr[k++] = p[i];
    }

    delete[] p;
    p = newArr;
    N--;
    return true;
}

// Редагування даних студента (Edit)
bool EditStudent(StudentGroup* p, const int N, const int index, const StudentGroup& updated) {
    if (p == nullptr || index < 0 || index >= N)
        return false;
    p[index] = updated;
    return true;
}

// Сортування за середнім балом (за спаданням або зростанням)
void SortByAverage(StudentGroup* p, const int N, bool descending) {
    if (p == nullptr || N <= 1) return;
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            bool condition = descending ? (p[i1].GetAverage() < p[i1 + 1].GetAverage())
                                        : (p[i1].GetAverage() > p[i1 + 1].GetAverage());
            if (condition) {
                StudentGroup tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}

// Сортування за прізвищами в алфавітному порядку (або зворотному)
void SortByPrizv(StudentGroup* p, const int N, bool ascending) {
    if (p == nullptr || N <= 1) return;
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            bool condition = ascending ? (p[i1].prizv > p[i1 + 1].prizv)
                                       : (p[i1].prizv < p[i1 + 1].prizv);
            if (condition) {
                StudentGroup tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}

// Сортування за оцінками із заданого предмету (1, 2 або 3)
void SortBySubject(StudentGroup* p, const int N, const int subjectIndex, bool descending) {
    if (p == nullptr || N <= 1) return;
    auto getMark = [](const StudentGroup& s, int idx) {
        if (idx == 1) return s.mark1;
        if (idx == 2) return s.mark2;
        return s.mark3;
    };

    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            int m1 = getMark(p[i1], subjectIndex);
            int m2 = getMark(p[i1 + 1], subjectIndex);
            bool condition = descending ? (m1 < m2) : (m1 > m2);
            if (condition) {
                StudentGroup tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}

// Запис масиву структур у файл
bool SaveToFile(const StudentGroup* p, const int N, const string& filename) {
    ofstream f(filename);
    if (!f.is_open()) return false;

    f << N << "\n";
    for (int i = 0; i < N; i++) {
        f << p[i].prizv << "\n";
        f << p[i].mark1 << " " << p[i].mark2 << " " << p[i].mark3 << "\n";
    }
    f.close();
    return true;
}

// Зчитування масиву структур із файлу
bool LoadFromFile(StudentGroup*& p, int& N, const string& filename) {
    ifstream f(filename);
    if (!f.is_open()) return false;

    if (p != nullptr) {
        delete[] p;
        p = nullptr;
    }

    f >> N;
    if (N <= 0) {
        f.close();
        return false;
    }

    f.ignore(1000, '\n');
    p = new StudentGroup[N];
    for (int i = 0; i < N; i++) {
        getline(f, p[i].prizv);
        f >> p[i].mark1 >> p[i].mark2 >> p[i].mark3;
        f.ignore(1000, '\n');
    }
    f.close();
    return true;
}

int main() {
#if defined(_WIN32)
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    StudentGroup* group = nullptr;
    int N = 0;
    int menuItem;

    do {
        cout << "\n======================== МЕНЮ ========================" << endl;
        cout << "  [1]  - Введення початкового списку студентів" << endl;
        cout << "  [2]  - Вивід списку студентів на екран" << endl;
        cout << "  [3]  - Додавання нового студента (коригування)" << endl;
        cout << "  [4]  - Вилучення студента за номером (коригування)" << endl;
        cout << "  [5]  - Редагування даних студента (коригування)" << endl;
        cout << "  [6]  - Сортування за середнім балом (за спаданням)" << endl;
        cout << "  [7]  - Сортування за прізвищами (в алфавітному порядку)" << endl;
        cout << "  [8]  - Сортування за оцінками з обраного предмету" << endl;
        cout << "  [9]  - Збереження списку у файл" << endl;
        cout << "  [10] - Завантаження списку з файлу" << endl;
        cout << "  [0]  - Вихід та завершення роботи програми" << endl;
        cout << "======================================================" << endl;
        cout << "Ваш вибір: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            CreateList(group, N);
            break;
        case 2:
            PrintList(group, N);
            break;
        case 3: {
            StudentGroup newS;
            cout << "\n--- Додавання студента ---" << endl;
            cin.get();
            cin.sync();
            cout << "  Прізвище: ";
            getline(cin, newS.prizv);
            cout << "  Оцінка 1: "; cin >> newS.mark1;
            cout << "  Оцінка 2: "; cin >> newS.mark2;
            cout << "  Оцінка 3: "; cin >> newS.mark3;
            AddStudent(group, N, newS);
            cout << "Студента успішно додано! Загальна кількість: " << N << endl;
            break;
        }
        case 4: {
            if (N == 0) {
                cout << "Список порожній!" << endl;
                break;
            }
            int delIdx;
            cout << "Введіть номер студента для вилучення (1.." << N << "): ";
            cin >> delIdx;
            if (RemoveStudent(group, N, delIdx - 1)) {
                cout << "Студента № " << delIdx << " успішно вилучено. Залишилось: " << N << endl;
            } else {
                cout << "Помилка: невірний номер студента!" << endl;
            }
            break;
        }
        case 5: {
            if (N == 0) {
                cout << "Список порожній!" << endl;
                break;
            }
            int editIdx;
            cout << "Введіть номер студента для редагування (1.." << N << "): ";
            cin >> editIdx;
            if (editIdx < 1 || editIdx > N) {
                cout << "Помилка: невірний номер студента!" << endl;
                break;
            }
            StudentGroup editS;
            cin.get();
            cin.sync();
            cout << "  Нове прізвище: ";
            getline(cin, editS.prizv);
            cout << "  Нова оцінка 1: "; cin >> editS.mark1;
            cout << "  Нова оцінка 2: "; cin >> editS.mark2;
            cout << "  Нова оцінка 3: "; cin >> editS.mark3;
            EditStudent(group, N, editIdx - 1, editS);
            cout << "Дані студента № " << editIdx << " оновлено!" << endl;
            break;
        }
        case 6:
            SortByAverage(group, N, true);
            cout << "\nСписок відсортовано за середнім балом (за спаданням):" << endl;
            PrintList(group, N);
            break;
        case 7:
            SortByPrizv(group, N, true);
            cout << "\nСписок відсортовано за прізвищами в алфавітному порядку:" << endl;
            PrintList(group, N);
            break;
        case 8: {
            int subj;
            cout << "Виберіть предмет для сортування (1, 2 або 3): ";
            cin >> subj;
            if (subj < 1 || subj > 3) subj = 1;
            SortBySubject(group, N, subj, true);
            cout << "\nСписок відсортовано за оцінками з предмету " << subj << " (за спаданням):" << endl;
            PrintList(group, N);
            break;
        }
        case 9: {
            string filename;
            cout << "Введіть ім'я файлу для збереження (наприклад, students.txt): ";
            cin >> filename;
            if (SaveToFile(group, N, filename)) {
                cout << "Дані успішно збережено у файл " << filename << endl;
            } else {
                cout << "Помилка відкриття файлу для запису!" << endl;
            }
            break;
        }
        case 10: {
            string filename;
            cout << "Введіть ім'я файлу для завантаження: ";
            cin >> filename;
            if (LoadFromFile(group, N, filename)) {
                cout << "Дані успішно завантажено з файлу " << filename << "! Завантажено студентів: " << N << endl;
                PrintList(group, N);
            } else {
                cout << "Помилка відкриття або зчитування файлу!" << endl;
            }
            break;
        }
        case 0:
            cout << "\nЗавершення роботи програми." << endl;
            break;
        default:
            cout << "Невірний вибір! Оберіть пункт від 0 до 10." << endl;
            break;
        }
    } while (menuItem != 0);

    if (group != nullptr) delete[] group;
    return 0;
}
