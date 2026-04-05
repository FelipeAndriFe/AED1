//Descrição: programa que utiliza uma matriz com vetor de ponteiros 

#pragma warning( disable : 5045 )

#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

int** CriaMatriz(int m, int n);
void LeiaMatriz(int **mat, int m, int n);
int SomaMatriz(int **mat, int m, int n);
int* ColunaMatriz(int **mat, int m, int nColuna);
void LiberaMatriz(int **mat, int m);
void ImprimeMatriz(int **mat, int m, int n);
void ImprimeVetor(int *vet, int m);
int Menu(void);

int main(void){

    int op = 0, m = 0, n = 0, **mat = NULL, soma = 0, *coluna = NULL, nColuna = 0;

    for( ;; ) {
        op = Menu();
        switch( op ) { 
            case 1:
                if ( mat != NULL ) {
                    LiberaMatriz(mat, m);
                }
                printf("Digite as dimensoes da matriz:\n");
                scanf_s("%d", &m);
                scanf_s("%d", &n);
                mat = CriaMatriz(m, n);
                break;
            case 2:
                LeiaMatriz(mat, m, n);
                break;
            case 3:
                soma = SomaMatriz(mat, m, n);
                printf("Soma: %d\n", soma);
                break;
            case 4:
                if ( coluna != NULL ) {
                    free(coluna);
                }
                do {
                    printf("Digite qual coluna quer resgatar: ");
                    scanf_s("%d", &nColuna);
                } while (nColuna < 0 || nColuna > n);
                coluna = ColunaMatriz(mat, m, nColuna-1);
                printf("Coluna %d:", nColuna);
                ImprimeVetor(coluna, m);
                break;
            case 5:
                ImprimeMatriz(mat, m, n);
                break;
            case 6:
                LiberaMatriz(mat, m);
                free(coluna);
                _CrtDumpMemoryLeaks();
                exit(0);
                break;
        }
    }
}

void ImprimeVetor(int *vet, int m) {

    for ( int i = 0; i < m; i++ ) {
        printf(" %d", vet[i]);
    }
    printf("\n");
}

int* ColunaMatriz(int **mat, int m, int nColuna) {

    int *coluna = NULL;
    coluna = (int *)malloc(sizeof(int)*m);
    if ( !coluna ) exit(1);

    for ( int i = 0; i < m; i++ ) {
        coluna[i] = mat[i][nColuna];
    }
    return coluna;
}

int Menu(void) {

    int op = 0;

    do {
        printf("1- Definir matriz\n2- Preencher matriz\n3- Soma dos elementos\n4- Retornar coluna\n5- Imprimir matriz\n6- Sair\n");
        scanf_s("%d", &op);
    } while ( op > 6 || op <= 0 );
    getchar();

    return op;
}

int** CriaMatriz(int m, int n) {

    int **mat;
    
    mat = (int **)malloc(sizeof(int*)*m);
    if ( !mat ) exit(1);

    for ( int i = 0; i < m; i++ ) {
        mat[i] = (int *)malloc(sizeof(int)*n);
        if ( !mat[i] ) exit(1);
    } 

    return mat;
}

void LeiaMatriz(int **mat, int m, int n){

    printf("Digite os numeros da matriz:\n");

    for ( int i = 0; i < m; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            scanf_s("%d", &mat[i][j]);
        }
    }
}

void ImprimeMatriz(int **mat, int m, int n) {

    printf("Matriz:\n");
    for ( int i = 0; i < m; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void LiberaMatriz(int **mat, int m){

    for ( int i = 0; i < m; i++ ) {
        free(mat[i]);
    }
    free(mat);
}

int SomaMatriz(int **mat, int m, int n) {

    int soma = 0;

    for ( int i = 0; i < m; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            soma += mat[i][j];
        }
    }
    return soma;
}