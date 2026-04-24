#include <stdlib.h>

int* findDiagonalOrder(int** mat, int matSize, int* matColSize, int* returnSize) {
    int *result, k, c = 0, diagonals, i = 0, j = 0;

    diagonals = (matSize + (*matColSize)) - 1;
    *returnSize = (matSize * (*matColSize));

    result = (int *)malloc(sizeof(int) * (matSize * (*matColSize)));
    if ( !result ) {
        return NULL;
    }

    for ( k = 0; k < diagonals; k++ ) {
        result[c] = mat[i][j];
        c++;
        if ( k % 2 == 0 ) {
            if ( i - 1 < 0 ) {
                if ( j + 1 >= *matColSize ) {
                    i++;
                } else {
                    j++;
                }
            } else {
                i--;
                j++;
            }
        } else {
            if ( j - 1 < 0 ) {
                if ( i + 1 >= matSize ) {
                    j++;
                } else {
                    i++;
                }
            } else {
                i++;
                j--;
            }
        }
    }

    return result;
}