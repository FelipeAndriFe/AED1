#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

void MergeSort(int *array, int low, int high);
void Merge(int *array, int low, int mid, int high);

int main() {
    int *array = (int *)malloc(sizeof(int) * 10);
    array[0] = 12;
    array[1] = 1;
    array[2] = 24;
    array[3] = 6;
    array[4] = 9;
    array[5] = 34;
    array[6] = -2;
    array[7] = 0;
    array[8] = 11;
    array[9] = 40;

    MergeSort(array, 0, 9);

    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }

    free(array);
    _CrtDumpMemoryLeaks();
    return 0;
}

void MergeSort(int *array, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        MergeSort(array, low, mid);
        MergeSort(array, mid + 1, high);

        Merge(array, low, mid, high);
    }
}

void Merge(int *array, int low, int mid, int high) {
    int sizeLeft = mid - low + 1;
    int sizeRight = high - mid;

    int *tempL = (int *)malloc(sizeof(int) * sizeLeft);
    if (!tempL) return;
    int *tempR = (int *)malloc(sizeof(int) * sizeRight);
    if (!tempR) {
        free(tempL);
        return;
    }

    for (int i = 0; i < sizeLeft; i++) tempL[i] = array[low + i];
    for (int i = 0; i < sizeRight; i++) tempR[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = low;
    while (i < sizeLeft && j < sizeRight) {
        if (tempL[i] < tempR[j]) {
            array[k++] = tempL[i++];
        } else {
            array[k++] = tempR[j++];
        }
    }
    while (i < sizeLeft) array[k++] = tempL[i++];
    while (j < sizeRight) array[k++] = tempR[j++];

    free(tempL);
    free(tempR);
}