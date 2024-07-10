#include "bigint.h"

int main(int argc, char** argv) {
	if (argc != 4)
		return -1;
	BigInt* A = InitializationBigInt(argv[1]);
	BigInt* B = InitializationBigInt(argv[3]);
	if (A == NULL || B == NULL)
		return -1;

	char operation = argv[2][0];

	BigInt* C = NULL;

	switch (operation)
	{
	case '+':
		C = Addition(A, B);
		if (C == NULL)
			return -1;
		printf("A = ");
		PrintBigInt(A);
		printf("B = ");
		PrintBigInt(B);
		printf("A + B = ");
		PrintBigInt(C);
		break;
	case '-':
		C = Substraction(A, B);
		if (C == NULL)
			return -1;
		printf("A = ");
		PrintBigInt(A);
		printf("B = ");
		PrintBigInt(B);
		printf("A - B = ");
		PrintBigInt(C);
		break;
	default:
		printf("Unknow operation\n");
		return 1;
		break;
	}

	FreeBigInt(A);
	FreeBigInt(B);
	FreeBigInt(C);
	return 0;
}