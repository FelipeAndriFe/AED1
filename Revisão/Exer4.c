//Descrição: implementar a função realloc

#pragma warning( disable : 5045 )

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

void *Realloc(void *pont, size_t newSize);

int main(void){
    
    int *vetor, newSize;
    vetor = (int *)malloc(sizeof(int)*5);
    if ( !vetor ) exit(1);

    printf("Digite os numeros do vetor (tamanho 5): ");
    for ( int i = 0; i < 5; i++ ) {
        scanf_s("%d", &vetor[i]);
    }
    printf("Digite o novo tamanho do vetor: ");
    scanf_s("%d", &newSize);

    vetor = (int *)Realloc(vetor, newSize*sizeof(int));

    if ( newSize > 5 ) {
        printf("Complete o vetor (%d elementos): ", newSize - 5);

        for ( int i = 5; i < newSize; i++ ) {
            scanf_s("%d", &vetor[i]);
        }
    }

    printf("Vetor:");
    for ( int i = 0; i < newSize; i++) {
        printf(" %d", vetor[i]);
    }
    free(vetor);

    _CrtDumpMemoryLeaks();
    return 0;
}

void *Realloc(void *pont, size_t newSize) {

    void *novo;
    novo = malloc(newSize);
    if ( !novo ) exit(1);

    memcpy(novo, pont, newSize);

    free(pont);
    return novo;
}