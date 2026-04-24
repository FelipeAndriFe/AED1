#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <crtdbg.h>

//pessoa = char nome[10], int idade, char email[20];
#define TAM_PESSOA (sizeof(char)*10 + sizeof(int) + sizeof(char)*20)
#define HEADER (sizeof(int)*3 + sizeof(char)*10)
#define I ((int *) pBuffer)
#define QNT ((int *) pBuffer + 1)
#define MENU ((int *) pBuffer + 2)
#define ALVO ((char *) pBuffer + (sizeof(int) * 3))

void Adicionar(void *pBuffer);
void Listar(void *pBuffer);
void Buscar(void *pBuffer);
void Remover(void *pBuffer);

int main() {
    void *pBuffer, *temp;
    
    //pBuffer = int i, int qnt, int menu, char alvo[10]
    pBuffer = malloc(HEADER);
    if ( !pBuffer ) {
        exit(1);
    }

    *QNT = 0;

    printf("--AGENDA PBUFFER MENU--\n");
    for( ;; ) {
        do {
            printf("\n1. Adicionar pessoa\n");
            printf("2. Remover pessoa\n");
            printf("3. Buscar pessoa\n");
            printf("4. Listar todas\n");
            printf("5. Sair\n");
            scanf("%d", MENU);
        } while ( *MENU > 5 || *MENU < 1 );

        switch( *MENU ) {
            case 1:
                (*QNT)++;
                temp = realloc(pBuffer, HEADER + TAM_PESSOA * (*QNT));
                if ( !temp ) {
                    exit(1);
                } 
                pBuffer = temp;
                Adicionar(pBuffer);
                break;
            case 2:
                Remover(pBuffer);
                temp = realloc(pBuffer, HEADER + TAM_PESSOA * (*QNT));
                if ( !temp ) {
                    exit(1);
                } 
                pBuffer = temp;
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
    scanf("%9s", (char *) pBuffer + HEADER + (TAM_PESSOA * ((*QNT) - 1)));
    scanf("%*[^\n]%*c");
    printf("--Digite a idade: ");
    scanf("%d", (int *)((char*) pBuffer + HEADER + 10 + (TAM_PESSOA * ((*QNT) - 1))));
    printf("--Digite o email: ");
    scanf("%19s", (char *) pBuffer + HEADER + sizeof(int) + 10 + (TAM_PESSOA * ((*QNT) - 1)));
    scanf("%*[^\n]%*c");
    printf("Nome adicionado\n");
}

void Listar(void *pBuffer) {
    for ( *I = 0; *I < *QNT; (*I)++ ) {
        printf("\n--Pessoa %d\n", (*I) + 1);
        printf("%s\n", (char *) pBuffer + HEADER + (TAM_PESSOA * (*I)));
        printf("%d\n", *(int *)((char*) pBuffer + HEADER + 10 + (TAM_PESSOA * (*I))));
        printf("%s\n", (char *) pBuffer + HEADER + sizeof(int) + 10 + (TAM_PESSOA * (*I)));
    }
}

void Buscar(void *pBuffer) {
    printf("--Digite o nome: ");
    scanf("%9s", ALVO);
    scanf("%*[^\n]%*c");

    for ( *I = 0; *I < *QNT; (*I)++ ) {
        if ( strcmp(ALVO, (char *) pBuffer + HEADER + (TAM_PESSOA * (*I))) == 0 ) {
            printf("\n--Pessoa %d\n", (*(int *)pBuffer) + 1);
            printf("%s\n", (char *) pBuffer + HEADER + (TAM_PESSOA * (*I)));
            printf("%d\n", *(int *)((char*) pBuffer + HEADER + 10 + (TAM_PESSOA * (*I))));
            printf("%s\n", (char *) pBuffer + HEADER + sizeof(int) + 10 + (TAM_PESSOA * (*I)));
            break;
        }
    }

    if ( *I == *QNT ) {
        printf("Nome nao encontrado\n");
    }
}

void Remover(void *pBuffer) {
    printf("--Digite o nome: ");
    scanf("%9s", ALVO);
    scanf("%*[^\n]%*c");

    for ( *I = 0; *I < *QNT; (*I)++ ) {
        if ( strcmp(ALVO, (char *) pBuffer + HEADER + (TAM_PESSOA * (*I))) == 0 ) {
            if ( *I == (*QNT) - 1 ) {
                break;
            } else {
                memmove((char *) pBuffer + HEADER + (TAM_PESSOA * (*I)), 
                        (char *) pBuffer + HEADER + (TAM_PESSOA * ((*I) + 1)),
                        TAM_PESSOA * (((*QNT) - 1) - *I));
                break;
            }
        }
    }

    if ( *I == *QNT ) {
        printf("Nome nao encontrado\n");
    } else {
        (*QNT)--;
        printf("Nome removido\n");
    }
}