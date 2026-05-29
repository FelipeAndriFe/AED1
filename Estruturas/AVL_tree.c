#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

typedef struct Node {
    int val;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int Max(int a, int b) {
    if (a > b) return a;
    return b;
}

int GetHeight(Node *root) {
    if (!root) return 0;
    return root->height;
}

int SetHeight(Node *root) {
    return 1 + Max(GetHeight(root->left), GetHeight(root->right));
}

int GetFB(Node *root) {
    if (!root) return 0;
    return GetHeight(root->left) - GetHeight(root->right);
}

int GetMin(Node *root) {
    Node *p = root;

    while (p->left)
        p = p->left;

    return p->val;
}

Node *RR(Node *root) {
    Node *n1 = root->right;
    Node *n2 = n1->left;

    n1->left = root;
    root->right = n2;

    root->height = SetHeight(root);
    n1->height = SetHeight(n1);

    return n1;
}

Node *LL(Node *root) {
    Node *n1 = root->left;
    Node *n2 = n1->right;

    n1->right = root;
    root->left = n2;

    root->height = SetHeight(root);
    n1->height = SetHeight(n1);

    return n1;
}

Node *RL(Node *root) {
    root->right = LL(root->right);
    root = RR(root);
    return root;
}

Node *LR(Node *root) {
    root->left = RR(root->left);
    root = LL(root);
    return root;
}

Node *Insert(Node *root, int key) {
    if (!root) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (!newNode) return NULL;

        newNode->left = newNode->right = NULL;
        newNode->val = key;
        newNode->height = 1;

        return newNode;
    }

    if (key > root->val)
        root->right = Insert(root->right, key);
    else if (key < root->val)
        root->left = Insert(root->left, key);
    else
        return root;

    root->height = SetHeight(root);
    
    int balance = GetFB(root);

    if (balance > 1 && GetFB(root->left) >= 0)
        return LL(root);

    if (balance > 1 && GetFB(root->left) < 0)
        return LR(root);

    if (balance < -1 && GetFB(root->right) <= 0)
        return RR(root);

    if (balance < -1 && GetFB(root->right) > 0)
        return RL(root);

    return root;
}

Node *Remove(Node *root, int key) {
    if (!root) return NULL;

    if (key > root->val)
        root->right = Remove(root->right, key);
    else if (key < root->val)
        root->left = Remove(root->left, key);
    else {
        if (root->left && root->right) {
            int newVal = GetMin(root->right);
            root->val = newVal;
            root->right = Remove(root->right, newVal);
        } else if (root->left || root->right) {
            Node *temp = root;
            root = root->left ? root->left : root->right;
            free(temp);
        } else {
            Node *temp = root;
            root = NULL;
            free(temp);
        }
    }

    if (!root) return NULL;

    root->height = SetHeight(root);
    
    int balance = GetFB(root);

    if (balance > 1 && GetFB(root->left) >= 0)
        return LL(root);

    if (balance > 1 && GetFB(root->left) < 0)
        return LR(root);

    if (balance < -1 && GetFB(root->right) <= 0)
        return RR(root);

    if (balance < -1 && GetFB(root->right) > 0)
        return RL(root);

    return root;
}

void FreeTree(Node *root) {
    if (!root) return;

    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

void PreOrder(Node *root) {
    if (!root) return;

    printf("%d ", root->val);
    PreOrder(root->left);
    PreOrder(root->right);
}

int main() {
    Node *root = NULL;

    root = Insert(root, 1);
    root = Insert(root, 2);
    root = Insert(root, 3);
    root = Insert(root, 4);
    root = Insert(root, 5);
    root = Insert(root, 6);

    PreOrder(root);
    printf("\n");

    root = Remove(root, 4);
    root = Remove(root, 5);

    PreOrder(root);

    FreeTree(root);
    _CrtDumpMemoryLeaks();
    return 0;
}