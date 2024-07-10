#include "GenPass.h"

int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));

	if (argc <= 1)
		return -1;

	if (CheckFlags_and_GeneratePasswords(argc, argv))
		return -1;
	return 0;
}