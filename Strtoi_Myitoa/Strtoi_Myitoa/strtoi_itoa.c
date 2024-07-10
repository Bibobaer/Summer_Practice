#include "strtoi_itoa.h"

int strtoi(const char* str, char** p, int* ret) {
	if (p == NULL || *p == NULL || str == NULL || LenString(str) == 0) {
		*p = (char*)str;
		return 1;
	}
	*ret = 0;
	int sign = *str == '-' ? -1 : 1;
	int has_prefix = 0;
	int CC = GetNumberSystem(str, sign, p, &has_prefix);
	if (CC == 1) {
		return 1;
	}

	int i = has_prefix == 1 ? sign == -1 ? 3 : 2 : sign == -1 ? 1 : 0;

	int len = LenString(str);
	int N = len - i - 1;
	int TempleI = i;
	if (CheckNumbersInString(str, p, CC, TempleI)) {
		*ret = 0;
		return 1;
	}

	for (; i < len; i++) {
		if (str[i] >= '0' && str[i] <= '9') {

			if ((Degree(CC, N) == -1 && (str[i] - '0') != 0) || MultiplyOverFlow((str[i] - '0'), Degree(CC, N)) || SumOverFlow(*ret, (str[i] - '0') * Degree(CC, N))) { *ret = 0; return 2; }
			*ret += (str[i] - '0') * Degree(CC, N);
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			if ((Degree(CC, N) == -1 && (str[i] - 'A' + 10) != 0) || MultiplyOverFlow((str[i] - 'A' + 10), Degree(CC, N)) || SumOverFlow(*ret, (str[i] - 'A' + 10) * Degree(CC, N))) { *ret = 0; return 2; }
			*ret += (str[i] - 'A' + 10) * Degree(CC, N);
		}
		else if (str[i] >= 'a' && str[i] <= 'z') {
			if ((Degree(CC, N) == -1 && (str[i] - 'a' + 36) != 0) || MultiplyOverFlow((str[i] - 'a' + 36), Degree(CC, N)) || SumOverFlow(*ret, (str[i] - 'a' + 36) * Degree(CC, N))) { *ret = 0; return 2; }
			*ret += (str[i] - 'a' + 36) * Degree(CC, N);
		}
		else {
			*ret = 0;
			*p = (char*)(str + i);
			return 1;
		}
		N--;

	}
	if (sign == -1)
		*ret *= -1;
	return 0;
}

int my_itoa(char* buf, int bufSize, int value, int p) {
	int Sign = value < 0 ? -1 : 1;
	int ValueTmp = value;
	char* alfabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	if (bufSize < 0)
		return 0;
	if (p < 2 || p > 62)
		return 0;

	int cnt = 0;
	while (ValueTmp != 0) {
		ValueTmp /= p;
		cnt++;
	}
	if (buf == NULL) {
		return cnt;
	}
	if (cnt > bufSize) {
		return 0;
	}

	int index = 0;
	if (value == 0) {
		buf[index++] = '0';
		buf[index] = '\0';
		return 2;
	}
	value = Sign == -1 ? -value : value;
	while (value != 0) {
		buf[index++] = alfabet[ABS(value % p)];
		value = ABS(value / p);
	}
	if (Sign == -1) {
		buf[index] = '-';
		index++;
	}

	for (int i = 0; i < index / 2; i++) {
		buf[i] ^= buf[index - i - 1] ^= buf[i] ^= buf[index - i - 1];
	}
	buf[index] = '\0';
	return index;
}