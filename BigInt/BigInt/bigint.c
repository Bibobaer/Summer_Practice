#include "bigint.h"

static _Bool CheckString(char* str);
static int CompareBigInt(BigInt* A, BigInt* B);
static int CountingSign(char** str);

int Flag = 0;

BigInt* InitializationBigInt(char* number) {
	BigInt* res = (BigInt*)malloc(sizeof(BigInt));
	if (!res)
		return NULL;
	
	short SignInStr = 0;
	res->Sign = CountingSign(&number);

	if (CheckString(number))
		return NULL;

	size_t NumberLen = strlen(number);
	size_t Whole_Part = NumberLen / 8; 
	size_t Fractional_Part = NumberLen % 8;

	res->CountWords = Fractional_Part == 0 ? Whole_Part : Whole_Part + 1;

	res->Data = (unsigned*)malloc(res->CountWords * sizeof(unsigned));
	if (!res->Data)
		return NULL;

	size_t j = 0;
	char TempleBuffer[9];

	for (size_t i = 0; i < Whole_Part; i++){
		memcpy(TempleBuffer, number + NumberLen - ((i + 1) * 8), 8);
		TempleBuffer[8] = '\0';
		res->Data[j++] = strtoul(TempleBuffer, NULL, 16);
	}

	if (Fractional_Part != 0) {
		memcpy(TempleBuffer, number, Fractional_Part);
		TempleBuffer[Fractional_Part] = '\0';
		res->Data[j] = strtoul(TempleBuffer, NULL, 16);
	}
	return res;
}

BigInt* Addition(BigInt* Number_1, BigInt* Number_2) {
	if (!Number_1 || !Number_2 || !Number_1->Data || !Number_2->Data)
		return NULL;
	BigInt* Result = (BigInt*)malloc(sizeof(BigInt));
	if (!Result)
		return NULL;

	Result->Sign = 0;

	int CheckNums = CompareBigInt(Number_1, Number_2);

	if (Number_1->Sign == Number_2->Sign)
		Result->Sign = Number_1->Sign;
	else {
		if (Flag == 0) {
			Flag = 1;
			short SignTmp = 0;
			if ((CheckNums == 1 && Number_1->Sign == -1) || (CheckNums == -1 && Number_2->Sign == -1))
				SignTmp = -1;
			else
				SignTmp = 1;

			if (CheckNums == 1)
				Result = Substraction(Number_1, Number_2);
			else
				Result = Substraction(Number_2, Number_1);
			Result->Sign = SignTmp;
			Flag = 0;
			return Result;
		}
	}

	Result->CountWords = CheckNums == -1 ? Number_2->CountWords + 1 : Number_1->CountWords + 1;
	
	Result->Data = (unsigned*)malloc(Result->CountWords*sizeof(unsigned));
	if (!Result->Data)
		return NULL;

	int ToNextNumber = 0;
	size_t CWNum_1 = Number_1->CountWords;
	size_t CWNum_2 = Number_2->CountWords;

	for (int i = 0; i < Result->CountWords - 1; ++i) {
		if (CWNum_1 && CWNum_2) {
			Result->Data[i] = Number_1->Data[i] + Number_2->Data[i] + ToNextNumber;

			if (Result->Data[i] < Number_1->Data[i] ||
				Result->Data[i] < Number_2->Data[i] ||
				(Result->Data[i] == Number_1->Data[i] && Number_2->Data[i] != 0) ||
				(Result->Data[i] == Number_2->Data[i] && Number_1->Data[i] != 0)) {
				ToNextNumber = 1;
			}
			else
				ToNextNumber = 0;

			CWNum_1--;
			CWNum_2--;
		}
		else if (CWNum_1 == 0 && CWNum_2 != 0) {
			Result->Data[i] = Number_2->Data[i] + ToNextNumber;
			if (Result->Data[i] < Number_2->Data[i] || Result->Data[i] < (unsigned)ToNextNumber) {
				ToNextNumber = 1;
			}
			else
				ToNextNumber = 0;
			CWNum_2--;
		}
		else if (CWNum_1 != 0 && CWNum_2 == 0) {
			Result->Data[i] = Number_1->Data[i] + ToNextNumber;
			if (Result->Data[i] < Number_1->Data[i] || Result->Data[i] < (unsigned)ToNextNumber) {
				ToNextNumber = 1;
			}
			else
				ToNextNumber = 0;
			CWNum_1--;
		}
		else {
			break;
		}
	}
	if (ToNextNumber) {
		Result->Data[Result->CountWords - 1] = ToNextNumber;
	}
	else {
		Result->CountWords--;
		unsigned* NewData = (unsigned*)malloc(Result->CountWords * sizeof(unsigned));
		if (!NewData)
			return NULL;
		for (int j = 0; j < Result->CountWords; ++j)
			NewData[j] = Result->Data[j];
		free(Result->Data);
		Result->Data = NewData;
	}

	return Result;
}

BigInt* Substraction(BigInt* Number_1, BigInt* Number_2) {
	if (!Number_1 || !Number_2 || !Number_1->Data || !Number_2->Data)
		return NULL;
	BigInt* Result = (BigInt*)malloc(sizeof(BigInt));
	if (!Result)
		return NULL;

	Result->Sign = 0;

	int CheckNums = CompareBigInt(Number_1, Number_2);

	if (CheckNums == 0 && (Number_1->Sign == Number_2->Sign)) {
		Result->Sign = 1;
		Result->CountWords = 1;
		Result->Data = (unsigned*)malloc(Result->CountWords * sizeof(unsigned));
		if (!Result->Data)
			return NULL;
		Result->Data[0] = 0;
		return Result;
	}

	if (Number_1->Sign != Number_2->Sign) {
		if (Flag == 0) {
			Flag = 1;
			short SignTmp = 0;
			if ((CheckNums == 1 && Number_1->Sign == -1) || (CheckNums == -1 && Number_1->Sign == -1))
				SignTmp = -1;
			else
				SignTmp = 1;
			Result = Addition(Number_1, Number_2);
			Result->Sign = SignTmp;
			Flag = 0;
			return Result;
		}
	}
	else {
		if ((CheckNums == 1 && Number_1->Sign == 1) || (CheckNums == -1 && Number_1->Sign == -1)) {
			Result->Sign = 1;
		}
		else {
			Result->Sign = -1;
		}

		if (CheckNums == -1) {
			BigInt* temple = Number_1;
			Number_1 = Number_2;
			Number_2 = temple;
		}
	}

	Result->CountWords = Number_1->CountWords;

	Result->Data = (unsigned*)malloc(Result->CountWords * sizeof(unsigned));
	if (!Result->Data)
		return NULL;

	size_t CWMinimalNumber = Number_2->CountWords;

	unsigned* MaximumNumber = (unsigned*)malloc(Result->CountWords*sizeof(unsigned));
	if (!MaximumNumber)
		return NULL;
	memcpy(MaximumNumber, Number_1->Data, Number_1->CountWords * sizeof(unsigned));

	for (int i = 0; i < Result->CountWords; i++) {
		if (CWMinimalNumber) {
			int ToPrevNum = i;
			if ((MaximumNumber[i] - Number_2->Data[i]) > Number_1->Data[i]) {
				ToPrevNum++;
				while (MaximumNumber[ToPrevNum] == 0)
					ToPrevNum++;

				--MaximumNumber[ToPrevNum--];

				while (ToPrevNum != i)
					MaximumNumber[ToPrevNum--] = 0xffffffff;
			}
			Result->Data[i] = MaximumNumber[i] - Number_2->Data[i];
			CWMinimalNumber--;
		}
		else {
			Result->Data[i] = MaximumNumber[i];
		}
	}
	return Result; 
}

void PrintBigInt(BigInt* Number) {
	if (!Number || !Number->Data)
		return;

	if (Number->Sign == -1) { printf("-"); }

	printf("%x", Number->Data[Number->CountWords - 1]);

	for (int i = (int)(Number->CountWords) - 2; i >= 0; i--) {
		printf("%08x", Number->Data[i]);
	}

	printf("\n");
	return;
}

void FreeBigInt(BigInt* Number) {
	if (!Number) {
		return;
	}
	if (!Number->Data) {
		free(Number);
		return;
	}
	free(Number->Data);
	free(Number);
	return;
}

static _Bool CheckString(char* str) {
	size_t Len = strlen(str);
	for (size_t i = 0; i < Len; i++)
		if (!((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 70) || (str[i] >= 97 && str[i] <= 102)))
			return 1;
	return 0;
}

static int CompareBigInt(BigInt* A, BigInt* B) {
	if (!A || !B || !A->Data || !B->Data)
		return -23;

	if ((A->CountWords > B->CountWords) || B->Sign == '-')
		return 1;
	if ((A->CountWords < B->CountWords) || A->Sign == '-')
		return -1;
	if (A->CountWords == B->CountWords) {
		for (int i = (int)(A->CountWords) - 1; i >= 0; i--)
		{
			if (A->Data[i] > B->Data[i])
				return 1;
			if (A->Data[i] < B->Data[i])
				return -1;
		}
	}
	return 0;
}

static int CountingSign(char** str) {
	if (str == NULL)
		return -5;
	int CountMinus = 0;
	while ((*str)[0] == '-' || (*str)[0] == '+') {
		if ((*str)[0] == '-')
			CountMinus++;
		(*str)++;
	}
	if (CountMinus % 2 == 0)
		return 1;
	else
		return -1;
	return 1;
}