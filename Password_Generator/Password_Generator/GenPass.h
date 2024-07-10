#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum _alphacase {
	LOWER = 0,
	UPPER,
	DIGIT,
	SPECIAL_SIM
}AlphaCase;

_Bool CheckFlags_and_GeneratePasswords(int argc, char** argv);
char* GeneratePassword(int MinLen, int MaxLen, int Len, char* Alphabet);
char* GetAlphabet(char* EnteredSymbols);