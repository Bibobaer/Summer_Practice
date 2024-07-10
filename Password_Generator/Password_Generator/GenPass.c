#include "GenPass.h"

_Bool CheckFlags_and_GeneratePasswords(int argc, char** argv) {//Проверка флагов и генерация паролей
	short m1Flag = 0, m2Flag = 0, nFlag = 0, ncFlag = 0, aFlag = 0, CFlag = 0;
	int minLen = 0, maxLen = 0, Len = 0;
	int CountPass = 1;
	char* Alpha = NULL;

	for (int i = 1; i < argc; i++) {
		if (!strcmp("-m1", argv[i])) {
			if (i != argc - 1) {//проверка что после флага есть вырожение 
				if (strlen(argv[i + 1]) != 0 && atoi(argv[i + 1]) != 0 && nFlag == 0 && m1Flag == 0) {//проверка флагов и проверка аргумента после флага
					m1Flag++;
					minLen = atoi(argv[i + 1]);
					if (minLen <= 0) {
						printf("Value of minimum length can`t me less than zero\n");
						return 1;
					}
					i++;
				}
				else {
					if (strlen(argv[i + 1]) != 0 && atoi(argv[i + 1]) == 0)
						printf("The argument should be integer\n");
					else if (m1Flag != 0)
						printf("The flag \'-m1\' should be the only one\n");
					else if (nFlag != 0)
						printf("The flags \'-m1\', \'-m2\' and \'-n\' are not compatible together\n");
					else 
						printf("Problem with length\n");
					return 1;
				}
			}
			else {
				printf("There is no varible for \'-m1\'\n");
				return 1;//и так со всеми флагами
			}
		}
		else if (!strcmp("-m2", argv[i])) {
			if (i != argc - 1) {
				if (strlen(argv[i + 1]) != 0 && atoi(argv[i + 1]) != 0 && nFlag == 0 && m2Flag == 0) {
					m2Flag++;
					maxLen = atoi(argv[i + 1]);
					if (maxLen <= 0) {
						printf("Value of maximum length can`t me less than zero\n");
						return 1;
					}
					i++;
				}
				else {
					if (strlen(argv[i + 1]) != 0 && atoi(argv[i + 1]) == 0)
						printf("The argument should be integer\n");
					else if (m2Flag != 0)
						printf("The flag \'-m2\' should be the only one\n");
					else if (nFlag != 0)
						printf("The flags \'-m1\', \'-m2\' and \'-n\' are not compatible together\n");
					else
						printf("Problem with length\n");
					return 1;
				}
			}
			else {
				printf("There is no varible for \'-m2\'\n");
				return 1;
			}
		}
		else if (!strcmp("-n", argv[i])) {
			if (i != argc - 1) {
				if (strlen(argv[i + 1]) != 0 && atoi(argv[i + 1]) != 0 && nFlag == 0 && m2Flag == 0 && m1Flag == 0) {
					nFlag++;
					Len = atoi(argv[i + 1]);
					if (Len <= 0) {
						printf("Length should be positive value\n");
						return 1;
					}
					i++;
				}
				else {
					if (strlen(argv[i + 1]) != 0 && atoi(argv[i + 1]) == 0)
						printf("The argument should be integer\n");
					else if (m1Flag != 0 || m2Flag != 0)
						printf("The flags \'-m1\', \'-m2\' and \'-n\' are not compatible together\n");
					else if (nFlag != 0)
						printf("The flag \'-n\' should be the only one\n");
					else
						printf("Problem with length\n");
					return 1;
				}
			}else{
				printf("There is no varible for \'-n\'\n");
				return 1;
			}
		}
		else if (!strcmp("-a", argv[i])) {
			if (i != argc - 1) {
				if (aFlag == 0 && CFlag == 0) {
					aFlag++;
					Alpha = argv[i + 1];
					i++;
				}
				else {
					if (aFlag != 0)
						printf("The flag \'-a\' should be the only one\n");
					else if (CFlag != 0)
						printf("The flags \'-a\' and \'-C\' are not compatible together\n");
					else
						printf("Problem with alphabet\n");
					return 1;
				}
			}
			else {
				printf("There is no varible for \'-a\'\n");
				return 1;
			}
		}
		else if (!strcmp("-C", argv[i])) {
			if (i != argc - 1) {
				if (aFlag == 0 && CFlag == 0) {
					CFlag++;
					Alpha = GetAlphabet(argv[i + 1]);
					if (Alpha == NULL) {
						printf("Not correct alphabet\n");
						return 1;
					}
					i++;
				}
				else {
					if (CFlag != 0)
						printf("The flag \'-C\' should be the only one\n");
					else if (aFlag != 0)
						printf("The flags \'-a\' and \'-C\' are not compatible together\n");
					else
						printf("Problem with alphabet\n");
					return 1;
				}
			}
			else {
				printf("There is no varible for \'-C\'\n");
				return 1;
			}
		}
		else if (!strcmp("-c", argv[i])) {
			if (i != argc - 1) {
				if (strlen(argv[i + 1]) != 0 && atoi(argv[i + 1]) != 0 && ncFlag == 0) {
					ncFlag++;
					CountPass = atoi(argv[i + 1]);
					if (CountPass <= 0) {
						printf("Count of passwords can`t me less than zero\n");
						return 1;
					}
					i++;
				}
				else {
					if (strlen(argv[i + 1]) != 0 && atoi(argv[i + 1]) == 0)
						printf("Count of passwords can`t be equal zero\n");
					else if (ncFlag != 0)
						printf("The flag \'-c\' should be the only one\n");
					else
						printf("Problem with count passwords\n");
					return 1;
				}
			}
			else {
				printf("There is no varible for \'-c\'\n");
				return 1;
			}
		}
		else {
			continue;
		}
	}

	if (m1Flag == 0 && m2Flag == 0 && nFlag == 0) {
		printf("Flags \'-m1\', \'-m2\' or flag \'-n\' must be present when creating passwords\n");
		return 1;
	}
	if (m1Flag == 0 && m2Flag != 0 || m2Flag == 0 && m1Flag != 0) {
		printf("The \'-m1\' and \'-m2\' flags must be included together\n");
		return 1;
	}
	if (minLen > maxLen) {
		printf("Minimum length can`t be more than maximum length\n");
		return 1;
	}

	for (int i = 0; i < CountPass; ++i) {
		char* tmp = GeneratePassword(minLen, maxLen, Len, Alpha);
		if (!tmp) {
			printf("The length is very big to create a password\n");
			return 1;
		}
		printf("%d) %s\n", i + 1, tmp);
		free(tmp);
	}
	return 0;
}

char* GeneratePassword(int MinLen, int MaxLen, int Len, char* Alphabet) {//Генерация пароля
	int SizePassword = Len != 0 ? Len : MinLen == MaxLen ? MaxLen : rand() % (MaxLen - MinLen + 1) + MinLen;
	char* Password = (char*)malloc((SizePassword+1)*sizeof(char));
	if (!Password)
		return NULL;
	for (int i = 0; i < SizePassword; i++)
		Password[i] = Alphabet[rand() % strlen(Alphabet)];
	Password[SizePassword] = '\0';
	return Password;
}

char* GetAlphabet(char* EnteredSymbols) {//Получаем алфавит из флага -С
	char* UpperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* LowerCase = "abcdefghijklmnopqrstuvwxyz";
	char* DigitCase = "0123456789";
	char* SpecialSimbolsCase = "!@#$\\%^&*()\"_;:?_-=+~|/[]{}\'";

	int len = (int)strlen(EnteredSymbols);
	int ArrayCountSimbols[4] = { 0 };
	if (len > 4)
		return NULL;
	for (int i = 0; i < len; i++) {
		if (EnteredSymbols[i] == 'a') {
			ArrayCountSimbols[LOWER]++;
		}
		else if (EnteredSymbols[i] == 'A') {
			ArrayCountSimbols[UPPER]++;
		}
		else if (EnteredSymbols[i] == 'D') {
			ArrayCountSimbols[DIGIT]++;
		}
		else if (EnteredSymbols[i] == 'S') {
			ArrayCountSimbols[SPECIAL_SIM]++;
		}
		else {
			return NULL;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (ArrayCountSimbols[i] > 1) {
			return NULL;
		}
	}

	char TempleAlpha[100] = "";
	if (ArrayCountSimbols[LOWER]) {
		strcat_s(TempleAlpha, 100, LowerCase);
	}
	if (ArrayCountSimbols[UPPER]) {
		strcat_s(TempleAlpha, 100, UpperCase);
	}
	if (ArrayCountSimbols[DIGIT]) {
		strcat_s(TempleAlpha, 100, DigitCase);
	}
	if (ArrayCountSimbols[SPECIAL_SIM]) {
		strcat_s(TempleAlpha, 100, SpecialSimbolsCase);
	}
	int TotalLength = (int)strlen(TempleAlpha);
	char* Alphabet = (char*)malloc(sizeof(char)*(TotalLength +1));
	if (!Alphabet) {
		return NULL;
	}
	for (int i = 0; i < TotalLength; i++) {
		Alphabet[i] = TempleAlpha[i];
	}
	Alphabet[TotalLength] = '\0';

	return Alphabet;
}