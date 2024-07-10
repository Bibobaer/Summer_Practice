#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _bigint {
	unsigned* Data;
	size_t CountWords;
	short Sign;
}BigInt;

BigInt* InitializationBigInt(char* number);

BigInt* Addition(BigInt* Number_1, BigInt* Number_2);
BigInt* Substraction(BigInt* Number_1, BigInt* Number_2);

void PrintBigInt(BigInt* Number);

void FreeBigInt(BigInt* Number);