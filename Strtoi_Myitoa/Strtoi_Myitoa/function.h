#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

_Bool SumOverFlow(int a, int b);
_Bool MultiplyOverFlow(int a, int b);

int GetNumberSystem(const char* str, int sign, char** p, int* has_prefix);
int CheckNumbersInString(const char* str, char** p, int CC, int i);

int ABS(int number);

int Degree(int number, int deg);
int LenString(const char* String);