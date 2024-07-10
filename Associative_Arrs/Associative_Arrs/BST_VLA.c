#include "BST_VLA.h"

_Bool check = 0;
//BST

void InsertTreeNode(Tree* tree, TreeNode* newNode) {
    if (tree == NULL || newNode == NULL)
        return;

    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    TreeNode* Current = tree->root;

    while (1) {
        if (strcmp(newNode->key, Current->key) == 0) {
            Current->value = newNode->value;
            return;
        }
        if ((strcmp(newNode->key, Current->key) > 0) && Current->right != NULL) {
            Current = Current->right;
        }
        else if ((strcmp(newNode->key, Current->key) > 0) && Current->right == NULL) {
            Current->right = newNode;
            return;
        }
        else if ((strcmp(newNode->key, Current->key) < 0) && Current->left != NULL) {
            Current = Current->left;
        }
        else {
            Current->left = newNode;
            return;
        }
    }
    return;
}

Tree* CreateTree(void) {
    Tree* res = (Tree*)malloc(sizeof(Tree));
    if (!res)
        return NULL;
    res->root = NULL;
    return res;
}

TreeNode* CreateAndInitTreeNode(KeyType key, ValueType value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node)
        return NULL;

    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

TreeNode* SearchValueByKey(Tree* tree, KeyType key) {
    if (tree == NULL || tree->root == NULL)
        return NULL;

    TreeNode* Current = tree->root;

    while (1){
        if (strcmp(key, Current->key) == 0) {
            return Current;
        }
        else if ((strcmp(key, Current->key) > 0) && Current->right != NULL) {
            Current = Current->right;
        }
        else if ((strcmp(key, Current->key) < 0) && Current->left != NULL) {
            Current = Current->left;
        }
        else {
            return NULL;
        }
    }
}

void InsertTreeValueByKey(Tree* tree, KeyType key, ValueType value) {
    TreeNode* node = CreateAndInitTreeNode(key, value);
    if (node == NULL)
        return;
    InsertTreeNode(tree, node);
    return;
}

void DeleteNode(Tree* tree, KeyType key) {
    if (!tree || !tree->root)
        return;
    TreeNode* CurrentNode = tree->root;
    TreeNode* ParrentNode = NULL;

    while (CurrentNode != NULL) {
        if (!strcmp(key, CurrentNode->key))
            break;
        else if (strcmp(key, CurrentNode->key) < 0) {
            ParrentNode = CurrentNode;
            CurrentNode = CurrentNode->left;
        }
        else {
            ParrentNode = CurrentNode;
            CurrentNode = CurrentNode->right;
        }
    }

    if (!CurrentNode)
        return;

    if (CurrentNode->left == NULL && CurrentNode->right == NULL) {
        if (ParrentNode == NULL)
            tree->root = NULL;
        else if (ParrentNode->left == CurrentNode)
            ParrentNode->left = NULL;
        else
            ParrentNode->right = NULL;
        free(CurrentNode);
    }
    else if (CurrentNode->left == NULL) {
        if (ParrentNode == NULL)
            tree->root = CurrentNode->right;
        else if (ParrentNode->left == CurrentNode)
            ParrentNode->left = CurrentNode->right;
        else
            ParrentNode->right = CurrentNode->right;
        free(CurrentNode);
    }
    else if (CurrentNode->right == NULL) {
        if (ParrentNode == NULL)
            tree->root = CurrentNode->left;
        else if (ParrentNode->left == CurrentNode)
            ParrentNode->left = CurrentNode->left;
        else
            ParrentNode->right = CurrentNode->left;
        free(CurrentNode);
    }
    else {
        TreeNode* MinNode = CurrentNode->right;
        ParrentNode = CurrentNode;

        while (MinNode->left != NULL) {
            ParrentNode = MinNode;
            MinNode = MinNode->left;
        }
        CurrentNode->key = MinNode->key;
        CurrentNode->value = MinNode->value;
        if (ParrentNode->left == MinNode)
            ParrentNode->left = MinNode->right;
        else
            ParrentNode->right = MinNode->right;
        free(MinNode);
    }
    return;
}

void FreeTree(TreeNode* root) {
    if (root == NULL)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

void PrintTree(TreeNode* root, int level) {
    int i;
    if (root == NULL)
        return;
    PrintTree(root->right, level + 1);
    for (i = 0; i < level; i++)
        printf("\t");
    printf("(%s, %d)\n", root->key, root->value);
    PrintTree(root->left, level + 1);
}
//VLA
VLA* CreateVLA(int size) {
    if (size <= 0)
        return NULL;
    VLA* Res = (VLA*)malloc(sizeof(VLA));
    if (!Res)
        return NULL;
    Res->size = size;

    Res->data = (KeyValue*)malloc(Res->size*sizeof(KeyValue));
    if (!Res->data)
        return NULL;
    Res->countelement = 0;
    return Res;
}

void InsertElemToVLA(VLA* vla, KeyType key, ValueType value) {
    if (vla == NULL || vla->data == NULL)
        return;

    if (vla->countelement == vla->size) {
        KeyValue* NewData = (KeyValue*)realloc(vla->data, sizeof(KeyValue)*(vla->size+1));
        if (!NewData)
            return;
        NewData[vla->countelement] = (KeyValue){ key, value };
        vla->data = NewData;
        vla->size++;
        vla->countelement++;
    }
    else {
        vla->data[vla->countelement] = (KeyValue){ key, value };
        vla->countelement++;
        return;
    }
    return;
}

KeyValue* SearchValueByKeyVLA(VLA* vla, KeyType key) {
    if (!vla || !vla->data)
        return NULL;

    for (int i = 0; i < vla->countelement; i++) {
        if (strcmp(key, vla->data[i].key) == 0)
            return &(vla->data[i]);
    }
    return NULL;
}

void DeleteCell(VLA* vla, KeyType key) {
    if (!vla || !vla->data)
        return;
    KeyValue* tmp = SearchValueByKeyVLA(vla, key);
    if (tmp == NULL)
        return;
    int index = (int)(tmp - vla->data);
    KeyValue* NewBuf = malloc((vla->countelement - 1) * sizeof(KeyValue));
    if (!NewBuf)
        return;

    int j = 0;
    for (int i = 0; i < vla->countelement; ++i) {
        if (i == index)
            continue;
        NewBuf[j++] = vla->data[i];
    }
    free(vla->data);
    vla->data = NewBuf;
    vla->countelement--;
    return;
}

void FreeVLA(VLA* vla) {
    if (vla == NULL)
        return;
    if (vla->data == NULL) {
        free(vla);
        return;
    }
    free(vla->data);
    free(vla);
}

void PrintVLA(VLA* vla) {
    if (!vla || !vla->data)
        return;
    for (int i = 0; i < vla->countelement; i++)
        printf("(%s, %d) ", vla->data[i].key, vla->data[i].value);
    printf("\n");
}