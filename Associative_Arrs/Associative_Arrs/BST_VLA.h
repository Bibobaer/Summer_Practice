#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char* KeyType;
typedef int ValueType;

typedef struct _treenode {
    KeyType key;
    ValueType value;
    struct _treenode* left;
    struct _treenode* right;
}TreeNode;


typedef struct _tree {
    TreeNode* root;
}Tree;

void InsertTreeNode(Tree* tree, TreeNode* newNode);
Tree* CreateTree(void);
TreeNode* CreateAndInitTreeNode(KeyType key, ValueType value);
TreeNode* SearchValueByKey(Tree* tree, KeyType key);//����� �������� �� �����
void InsertTreeValueByKey(Tree* tree, KeyType key, ValueType value);//������� ����

void DeleteNode(Tree* tree, KeyType key);//�������� ����
void FreeTree(TreeNode* root);//������� ����������

void PrintTree(TreeNode* root, int level);

typedef struct _keyvalue {
    KeyType key;
    ValueType value;
}KeyValue;

typedef struct _vla {
    KeyValue* data;
    int size;
    size_t countelement;
}VLA;

VLA* CreateVLA(int size);
void InsertElemToVLA(VLA* vla, KeyType key, ValueType value);//������� ����
KeyValue* SearchValueByKeyVLA(VLA* vla, KeyType key);//����� �������� �� �����

void DeleteCell(VLA* vla, KeyType key);//�������� ����
void FreeVLA(VLA* vla);//������� ����������

void PrintVLA(VLA* vla);