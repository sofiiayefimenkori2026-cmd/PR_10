// student.h
// Єфіменко Софія
// Лабораторна робота № 10.1 (Рівень В)
// Модуль опису структур даних з анонімним об'єднанням union
// Варіант 8

#pragma once
#include <string>

// Перелік спеціальностей (Рівень В)
enum Spec { KN, IN, ME, FI, TN };

extern const std::string specStr[5];
extern const std::string profSubjectName[5];
extern const std::string subjectTitles[5];

// Структура студента з анонімним об'єднанням для третьої оцінки.
// Усі поля union (int) займають одну й ту саму область пам'яті.
struct Student {
    std::string prizv;
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
