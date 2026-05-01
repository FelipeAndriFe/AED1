#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <crtdbg.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

Queue *Create();
bool Enqueue(Queue *queue, int x);
bool Dequeue(Queue *queue, int *x);
bool IsEmpty(Queue *queue);
void Destroy(Queue *queue);

int main() {
    int x;
    Queue *queue = Create();
    if (!queue) exit(1);

    if (IsEmpty(queue)) printf("Queue Empty\n");

    if (!Enqueue(queue, 2)) printf("Enqueue Failed\n");
    if (!Enqueue(queue, 8)) printf("Enqueue Failed\n");
    if (!Enqueue(queue, 6)) printf("Enqueue Failed\n");
    if (!Enqueue(queue, 4)) printf("Enqueue Failed\n");

    for (int i = 0; i < 5; i++) {
        bool test = Dequeue(queue, &x);
        if (test) {
            printf("%d\n", x);
        } else {
            printf("Dequeue Failed\n");
        }
    }

    if (!Enqueue(queue, 2)) printf("Enqueue Failed\n");
    if (!Enqueue(queue, 8)) printf("Enqueue Failed\n");

    Destroy(queue);
    _CrtDumpMemoryLeaks();
    return 0;
}

Queue *Create() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue) return NULL;

    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

bool Enqueue(Queue *queue, int x) {
    Node *new = (Node *)malloc(sizeof(Node));
    if (!new) return false;

    new->val = x;
    new->next = NULL;

    if (IsEmpty(queue)) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }

    return true;
}

bool Dequeue(Queue *queue, int *x) {
    Node *temp;

    if (IsEmpty(queue)) return false;

    temp = queue->head;
    *x = temp->val;
    queue->head = queue->head->next;
    free(temp);

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    return true;
}

bool IsEmpty(Queue *queue) {
    return queue->head == NULL;
}

void Destroy(Queue *queue) {
    Node *temp;

    if (!queue) return;
    
    while (queue->head) {
        temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }

    free(queue);
}