#include "function.h"

_Bool SumOverFlow(int a, int b) {
	if (((b > 0) && (a > (INT_MAX - b))) || ((b < 0) && (a < (INT_MIN - b)))) {
		return 1;
	}
	return 0;
}

_Bool MultiplyOverFlow(int a, int b) {
	if (a > INT_MAX / b || a < INT_MIN / b) {
		return 1;
	}
	return 0;
}

int GetNumberSystem(const char* str, int sign, char** p, int* has_prefix) {
	int index_CC = sign == -1 ? 1 : 0;
	if ((sign == 1 && str[1] == 'x') || (sign == -1 && str[2] == 'x')) {
		*has_prefix = 1;
		if (str[index_CC] >= 50 && str[index_CC] <= 57)
			return str[index_CC] - '0';
		else if (str[index_CC] >= 65 && str[index_CC] <= 90)
			return str[index_CC] - 'A' + 10;
		else if (str[index_CC] >= 97 && str[index_CC] <= 122)
			return str[index_CC] - 'a' + 36;
		else if (str[index_CC] == 33)
			return 62;
		else {
			*p = (char*)(str + index_CC);
			return 1;
		}
	}
	else {
		*has_prefix = 0;
		return 10;
	}
}

int CheckNumbersInString(const char* str, char** p, int CC, int i) {
	for (; i < LenString(str); i++) {
		if ((str[i] >= '0' && str[i] <= '9' && str[i] - '0' < CC) || (str[i] >= 'A' && str[i] <= 'Z' && str[i] - 'A' + 10 < CC) ||
			(str[i] >= 'a' && str[i] <= 'z' && str[i] - 'a' + 36 < CC))
			continue;
		else {
			*p = (char*)(str + i);
			return 1;
		}
	}
	return 0;
}

int ABS(int number) {
	return number < 0 ? -number : number;
}

int Degree(int number, int deg) {
	int Res = number;
	if (deg == 0)
		return 1;
	for (int i = 1; i < deg; i++) {
		if (MultiplyOverFlow(Res, number)) {
			return -1;
		}
		Res *= number;
	}
	return Res;
}

int LenString(const char* String) {
	if (!String) {
		return -1;
	}
	int i = 0;
	while (String[i] != '\0')
		i++;
	return i;
}