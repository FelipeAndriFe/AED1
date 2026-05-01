#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <crtdbg.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack *Create(void);
bool IsEmpty(Stack *stack);
bool Push(Stack *stack, int x);
int Pop(Stack *stack);
void Destroy(Stack *stack);

int main() {
    Stack *stack;
    stack = Create();
    if (!stack) exit(1);

    if (IsEmpty(stack)) printf("Stack Empty\n");

    if (!Push(stack, 2)) printf("Push Failed\n");
    if (!Push(stack, 4)) printf("Push Failed\n");
    if (!Push(stack, 9)) printf("Push Failed\n");
    if (!Push(stack, 8)) printf("Push Failed\n");
    if (!Push(stack, 7)) printf("Push Failed\n");

    for (int i = 0; i < 6; i++) {
        printf("%d\n", Pop(stack));
    }

    if (!Push(stack, 2)) printf("Push Failed\n");
    if (!Push(stack, 4)) printf("Push Failed\n");

    Destroy(stack);
    _CrtDumpMemoryLeaks();
    return 0;
}

Stack *Create(void) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->top = NULL;
    return stack;
}

bool IsEmpty(Stack *stack) {
    return stack->top == NULL;
}

bool Push(Stack *stack, int x) {
    Node *new = (Node *)malloc(sizeof(Node));
    if (!new) return false;

    new->val = x;
    new->next = stack->top;
    stack->top = new;

    return true;
}

int Pop(Stack *stack) {
    int val;
    Node *temp;

    if (IsEmpty(stack)) {
        printf("Pop Failed\n");
        return -1;
    }

    temp = stack->top;
    val = temp->val;
    stack->top = stack->top->next;
    free(temp);
    
    return val;
}

void Destroy(Stack *stack) {
    Node *temp;

    while (stack->top) {
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    free(stack);
}