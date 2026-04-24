#include <stdlib.h>

int* findDiagonalOrder(int** mat, int matSize, int* matColSize, int* returnSize) {
    int *result, c = 0, diagonals, i = 0, j = 0;

    diagonals = (matSize + (*matColSize)) - 1;
    *returnSize = (matSize * (*matColSize));

    result = (int *)malloc(sizeof(int) * (matSize * (*matColSize)));
    if ( !result ) {
        return NULL;
    }

    for ( c = 0; c < *returnSize; c++ ) {
        result[c] = mat[i][j];
        if ( (i + j) % 2 == 0 ) {
            if ( j + 1 >= *matColSize ) {
                i++;
            } else if ( i - 1 < 0 ) {
                j++;
            } else {
                i--;
                j++;
            }
        } else {
            if ( i + 1 >= matSize ) {
                j++;
            } else if ( j - 1 < 0 ) {
                i++;
            } else {
                i++;
                j--;
            }
        }
    }

    return result;
}