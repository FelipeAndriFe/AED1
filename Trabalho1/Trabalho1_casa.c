#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

/*
======================
FindDiagonalOrder
    Returns the vector of a given matrix read in diagonal order
======================
*/
int* FindDiagonalOrder( int** mat, int matSize, int* matColSize, int* returnSize ) {
    int *result, k, c = 0, diagonals, i = 0, j = 0;

    diagonals = ( matSize + ( *matColSize ) ) - 1;
    *returnSize = ( matSize * ( *matColSize ) );

    result = ( int * ) malloc ( sizeof( int ) * ( matSize * ( *matColSize ) ) );
    if ( !result ) {
        return NULL;
    }

    for ( k = 0; k < diagonals; k++ ) {
        result[c] = mat[i][j];
        c++;
        if ( k % 2 == 0 ) {
            if ( j + 1 >= *matColSize ) {
                i++;
            } else if ( i - 1 < 0 ) {
                j++;
            } else {
                i--;
                j++;
                k--;
            }
        } else {
            if ( i + 1 >= matSize ) {
                j++;
            } else if ( j - 1 < 0 ) {
                i++;
            } else {
                i++;
                j--;
                k--;
            }
        }
    }

    return result;
}

int main() {
    int rows = 3, cols = 3, returnSize, **mat, c = 1, *result;

    mat = ( int ** ) malloc ( sizeof( int * ) * rows );
    if ( !mat ) {
        exit(1);
    }

    for ( int i = 0; i < rows; i++ ) {
        mat[i] = ( int * ) malloc ( sizeof( int ) * cols );
        if ( !mat[i] ) {
            exit(1);
        }
    }

    for ( int i = 0; i < rows; i++ ) {
        for ( int j = 0; j < cols; j++ ) {
            mat[i][j] = c;
            c++;
            printf( "%d ", mat[i][j] );
        }
        printf( "\n" );
    }

    result = FindDiagonalOrder( mat, rows, &cols, &returnSize );

    for ( int i = 0; i < returnSize; i++ ) {
        printf( "%d ", result[i] );
    }

    for ( int i = 0; i < rows; i++ ) {
        free( mat[i] );
    }
    free( mat );
    free( result );

    _CrtDumpMemoryLeaks();
    return 0;
}