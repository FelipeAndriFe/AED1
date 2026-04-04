//Armazenar vários nomes na mesma string, podendo listar e remover também

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

int menu(void);
void inserir(char **str, int *charCount);
void remover(char **str, int *charCount);

int main(){

    int op = 0, charCount = 0;
    char *lista = NULL;

    for(;;){
        op = menu();
        switch(op){
            case 1:
                inserir(&lista, &charCount);
                break;
            case 2:
                remover(&lista, &charCount);
                break;
            case 3:
                printf("%s", lista);
                break;
            case 4:
                free(lista);
                _CrtDumpMemoryLeaks();
                exit(0);
                break;
        }
    }
}

int menu(void){

    int c = 0;

    do {
        printf("1. Adicionar nome\n");
        printf("2. Remover nome\n");
        printf("3. Listar\n");
        printf("4. Sair\n");
        scanf("%d", &c);
    } while (c <= 0 || c > 4);
    getchar();

    return c;
}

void inserir(char **str, int *charCount){

    char *temp = NULL, nome[50];
    int primeiro;
    
    printf("Digite o nome: ");
    fgets(nome, 50, stdin);

    primeiro = (*str == NULL);

    (*charCount) += strlen(nome);

    temp = (char *)realloc(*str, sizeof(char)*((*charCount) + 1));
    if (temp == NULL){
        exit(1);
    }
    *str = temp;

    if (primeiro){
        *str[0] = '\0';
    }
    strcat(*str, nome);
}

void remover(char **str, int *charCount){

    char nome[50], *p, *temp = NULL;
    int len, i = 0;

    printf("Digite o nome que deseja excluir: ");
    fgets(nome, 50, stdin);

    p = strstr(*str, nome);
    if (p == NULL){
        printf("Nome nao encontrado\n");
        return;
    }

    len = strlen(nome);

    while (p[i + len] != '\0'){
        p[i] = p[i + len];
        i++;
    }
    p[i] = '\0';

    *charCount -= len;

    temp = (char *)realloc(*str, sizeof(char)*(*charCount + 1));
    if (temp == NULL){
        exit(1);
    }
    *str = temp;
}