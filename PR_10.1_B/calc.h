// calc.h
// Єфіменко Софія
// Лабораторна робота № 10.1 (Рівень В)
// Заголовочний файл модуля обчислень та послідовного пошуку
// Варіант 8

#pragma once
#include "student.h"

void CalcAverages(const Student* p, const int N, double avg[5], int cnt[5]);
int CountPhysics5or4(const Student* p, const int N);
