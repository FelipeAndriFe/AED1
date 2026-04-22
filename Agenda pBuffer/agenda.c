#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <crtdbg.h>

//pessoa = char nome[10], int idade, char email[20];
#define TAM_PESSOA (sizeof(char)*10 + sizeof(int) + sizeof(char)*20)
#define HEADER (sizeof(int)*3 + sizeof(char)*10)

void Adicionar(void *pBuffer);
void Listar(void *pBuffer);
void Buscar(void *pBuffer);

int main() {
    void *pBuffer, *temp;
    
    //pBuffer = int i, int qnt, int menu, char alvo[10]
    pBuffer = malloc(sizeof(int)*3 + sizeof(char)*10);
    if ( !pBuffer ) {
        exit(1);
    }

    *((int *)pBuffer+1) = 0;

    printf("--AGENDA PBUFFER MENU--\n");
    for( ;; ) {
        do {
            printf("\n1. Adicionar pessoa\n");
            printf("2. Remover pessoa\n");
            printf("3. Buscar pessoa\n");
            printf("4. Listar todas\n");
            printf("5. Sair\n");
            scanf("%d", (int *)pBuffer+2);
        } while ( *((int *)pBuffer+2) > 5 || *((int *)pBuffer+2) < 1 );

        switch( *((int *)pBuffer+2) ) {
            case 1:
                (*((int *)pBuffer+1))++;
                temp = realloc(pBuffer, sizeof(int)*3 + sizeof(char)*10 + TAM_PESSOA*(*((int *)pBuffer+1)));
                if ( !temp ) {
                    exit(1);
                } 
                pBuffer = temp;
                Adicionar(pBuffer);
                break;
            case 2:

                break;
            case 3:
                Buscar(pBuffer);
                break;
            case 4:
                Listar(pBuffer);
                break;
            case 5:
                free(pBuffer);
                _CrtDumpMemoryLeaks();
                exit(0);
                break;
        }
    }
}

void Adicionar(void *pBuffer) {
    printf("--Digite o nome: ");
    scanf("%9s", (char *) pBuffer + HEADER + (TAM_PESSOA * ((*((int *)pBuffer+1)) - 1)));
    scanf("%*[^\n]%*c");
    printf("--Digite a idade: ");
    scanf("%d", (int *)((char*) pBuffer + HEADER + 10 + (TAM_PESSOA * ((*((int *)pBuffer+1)) - 1))));
    printf("--Digite o email: ");
    scanf("%19s", (char *) pBuffer + HEADER + sizeof(int) + 10 + (TAM_PESSOA * ((*((int *)pBuffer+1)) - 1)));
    scanf("%*[^\n]%*c");
}

void Listar(void *pBuffer) {
    for ( *(int *)pBuffer = 0; *(int *)pBuffer < *((int *)pBuffer+1); (*(int *)pBuffer)++ ) {
        printf("\n--Pessoa %d\n", (*(int *)pBuffer) + 1);
        printf("%s\n", (char *) pBuffer + HEADER + (TAM_PESSOA * (*(int *)pBuffer)));
        printf("%d\n", *(int *)((char*) pBuffer + HEADER + 10 + (TAM_PESSOA * (*(int *)pBuffer))));
        printf("%s\n", (char *) pBuffer + HEADER + sizeof(int) + 10 + (TAM_PESSOA * (*(int *)pBuffer)));
    }
}

void Buscar(void *pBuffer) {
    printf("--Digite o nome: ");
    scanf("%9s", (char *) pBuffer + sizeof(int) * 3);
    scanf("%*[^\n]%*c");

    for ( *(int *)pBuffer = 0; *(int *)pBuffer < *((int *)pBuffer+1); (*(int *)pBuffer)++ ) {
        if ( strcmp((char *) pBuffer + sizeof(int) * 3, (char *) pBuffer + HEADER + (TAM_PESSOA * (*(int *)pBuffer))) == 0 ) {
            printf("\n--Pessoa %d\n", (*(int *)pBuffer) + 1);
            printf("%s\n", (char *) pBuffer + HEADER + (TAM_PESSOA * (*(int *)pBuffer)));
            printf("%d\n", *(int *)((char*) pBuffer + HEADER + 10 + (TAM_PESSOA * (*(int *)pBuffer))));
            printf("%s\n", (char *) pBuffer + HEADER + sizeof(int) + 10 + (TAM_PESSOA * (*(int *)pBuffer)));
            break;
        }
    }

    if ( *(int *)pBuffer == *((int *)pBuffer+1) ) {
        printf("Nome nao encontrado\n");
    }
}