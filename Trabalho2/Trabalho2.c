#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>

int* NextGreaterElements( int* nums, int numsSize, int* returnSize ) {
    if ( !nums ) {
        *returnSize = 0;
        return NULL;
    }

    int *result = ( int * ) malloc ( sizeof( int ) * numsSize );
    if ( !result ) {
        *returnSize = 0;
        return NULL;
    }

    int looped, j, c = 0;

    *returnSize = numsSize;

    for ( int i = 0; i < numsSize; i++ ) {
        j = i + 1;
        looped = 0;
        while ( looped == 0 ) {
            if ( j >= numsSize ) {
                j = 0;
            }
            if ( j == i ) {
                looped = 1;
            }
            if ( looped == 1 ) {
                result[c] = -1;
                c++;
                break;
            }
            if ( nums[j] > nums[i] ) {
                result[c] = nums[j];
                c++;
                break;
            }
            j++;
        }
    }

    return result;
}

int main() {
    int *nums = ( int * ) malloc ( sizeof(int) * 5 ), numsSize = 5, returnSize, *result;

    nums[0] = 1;
    nums[1] = 2;
    nums[2] = 3;
    nums[3] = 4;
    nums[4] = 3;

    result = NextGreaterElements( nums, numsSize, &returnSize );

    printf( "nums: " );
    for ( int i = 0; i < numsSize; i++ ) {
        printf( "%d ", nums[i] );
    }
    printf( "\nresult: " );
    for ( int i = 0; i < returnSize; i++ ) {
        printf( "%d ", result[i] );
    }

    free( nums );
    free( result );
    _CrtDumpMemoryLeaks();
    return 0;
}