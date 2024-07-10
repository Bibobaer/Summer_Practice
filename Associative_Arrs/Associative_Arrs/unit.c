#include "unit.h"

char* GenerateString(int Len, char* Alphabet) {
	int SizePassword = Len;
	char* Password = (char*)malloc((SizePassword + 1) * sizeof(char));
	if (!Password)
		return NULL;
	for (int i = 0; i < SizePassword; i++)
		Password[i] = Alphabet[rand() % strlen(Alphabet)];
	Password[SizePassword] = '\0';
	return Password;
}

void SimpleTests(void) {
	Tree* tree = CreateTree();

	InsertTreeValueByKey(tree, "Ivan", 23);
	InsertTreeValueByKey(tree, "Jimmy", 17);
	InsertTreeValueByKey(tree, "Alex", 6);
	InsertTreeValueByKey(tree, "Mark", 63);
	InsertTreeValueByKey(tree, "John", 15);

	PrintTree(tree->root, 0);
	printf("\n");

	InsertTreeValueByKey(tree, "Mark", 37);
	PrintTree(tree->root, 0);
	printf("\n");

	TreeNode* search = SearchValueByKey(tree, "Alex");
	printf("(%s, %d)\n", search->key, search->value);
	search = SearchValueByKey(tree, "Zsd");
	if (search == NULL)
		printf("Not Found\n");
	DeleteNode(tree, "Zsd");
	PrintTree(tree->root, 0);
	printf("\n");
	DeleteNode(tree, "Mark");
	PrintTree(tree->root, 0);

	FreeTree(tree->root);
	free(tree);

	system("pause");
	system("cls");

	VLA* vla = CreateVLA(2);

	InsertElemToVLA(vla, "qwerty", 19);
	InsertElemToVLA(vla, "sdsd", 64);
	PrintVLA(vla);

	InsertElemToVLA(vla, "terrv", 92);
	InsertElemToVLA(vla, "htn", 14);
	InsertElemToVLA(vla, "u,yjb", 0);

	PrintVLA(vla);

	KeyValue* tmp = SearchValueByKeyVLA(vla, "terrv");
	printf("(%s, %d)\n", tmp->key, tmp->value);

	tmp = SearchValueByKeyVLA(vla, "123");
	if (tmp == NULL)
		printf("Not Found\n");

	DeleteCell(vla, "htn");
	PrintVLA(vla);
	FreeVLA(vla);
	return;
}

void Tests(void) {
	Tree* tree = CreateTree();

	//BST Test
	printf("BST\n");
	TreeNode* node = NULL;
	clock_t start_1 = clock();
	for (int i = 0; i < 10000000; ++i) {
		InsertTreeValueByKey(tree, GenerateString(3, "abcde321"), i);
	}
	clock_t end_1 = clock();
	printf("Insert to Tree\n10.000.000 Elements. time: %f\n",(double)(end_1 - start_1)/CLOCKS_PER_SEC);
	
	clock_t start_2 = clock();
	char* search_1 = GenerateString(3, "abcde321");
	node = SearchValueByKey(tree, search_1);
	if (!node)
		printf("Not found\n");
	else {
		printf("(%s, %d)\n", node->key, node->value);
	}
	clock_t end_2 = clock();
	printf("Search random key in Tree\n10.000.000 Elements. time: %f\n", (double)(end_2-start_2)/CLOCKS_PER_SEC);
	
	clock_t start_3 = clock();
	DeleteNode(tree, search_1);
	clock_t end_3 = clock();
	printf("Delete random node in Tree\n10.000.000 Elements. time: %f\n", (double)(end_3 - start_3) / CLOCKS_PER_SEC);
	FreeTree(tree->root);
	free(tree);
	//VLA Test
	printf("VLA\n");
	VLA* vla = CreateVLA(10000000);
	start_1 = clock();
	for (int i = 0; i < 10000000; ++i) {
		InsertElemToVLA(vla, GenerateString(5, "asdf"), i);
	}
	end_1 = clock();
	printf("Insert to Array\n10.000.000 Elements. time: %f\n", (double)(end_1 - start_1) / CLOCKS_PER_SEC);
	start_2 = clock();
	char* search_2 = GenerateString(5, "asdf");
	KeyValue* tmp = SearchValueByKeyVLA(vla, search_2);
	if (!tmp)
		printf("Not found\n");
	else {
		printf("(%s, %d)\n", tmp->key, tmp->value);
	}
	end_2 = clock();
	printf("Search random key in Array\n10.000.000 Elements. time: %f\n", (double)(end_2 - start_2) / CLOCKS_PER_SEC);
	start_3 = clock();
	DeleteCell(vla, search_2);
	end_3 = clock();
	printf("Delete random node in Array\n10.000.000 Elements. time: %f\n", (double)(end_3 - start_3) / CLOCKS_PER_SEC);
	FreeVLA(vla);
	return;
}