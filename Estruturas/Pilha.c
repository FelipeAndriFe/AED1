#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <crtdbg.h>

typedef struct {
    int *items;
    int size;
    int cap;
} stack_t;

stack_t *Create( int cap );
void Destroy( stack_t *stack );
bool IsEmpty( stack_t *stack );
bool IsFull( stack_t *stack );
bool Push( stack_t *stack, int item );
bool Pop( stack_t *stack, int *item );

int main(){
    stack_t *stack = Create( 5 );
    int item;

    if ( IsEmpty ) printf( "Pilha vazia\n" );

    bool tryPop = Pop( stack, &item );
    if ( !tryPop ) printf( "Erro no Pop\n" );

    Push( stack, 2 );
    Push( stack, 5 );
    Push( stack, 4 );
    Push( stack, 9 );
    Push( stack, 7 );

    bool tryPush = Push( stack, 2 );
    if ( !tryPush ) printf( "Erro no Push\n");

    if ( IsFull ) printf( "Pilha cheia\n" );

    for (int i = 0; i < stack->cap; i++ ) {
        Pop( stack, &item );
        printf( "%d\n", item );
    }

    Destroy( stack );
    _CrtDumpMemoryLeaks();
    return 0;
}

stack_t *Create( int cap ) {
    stack_t *stack = (stack_t *) malloc ( sizeof( stack_t ) );
    if ( !stack ) return NULL;

    stack->items = (int *) malloc ( sizeof( int ) * cap );
    if ( !stack->items ) return NULL;

    stack->size = 0;
    stack->cap = cap;

    return stack;
}

void Destroy( stack_t *stack ) {
    free( stack->items );
    free( stack );
}

bool IsEmpty( stack_t *stack ) {
    return stack->size == 0;
}

bool IsFull( stack_t *stack ) {
    return stack->size == stack->cap;
}

bool Push( stack_t *stack, int item ) {
    if ( IsFull( stack ) ) return false;
    stack->items[stack->size] = item;
    stack->size++;

    return true;
}

bool Pop( stack_t *stack, int *item ) {
    if ( IsEmpty( stack ) ) return false;
    stack->size--;
    *item = stack->items[stack->size];

    return true;
}