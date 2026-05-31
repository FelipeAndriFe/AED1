#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int *array, int low, int high) {
    int pivotIndex = low + (rand() % (high - low + 1));

    if (pivotIndex != high)
        Swap(&array[pivotIndex], &array[high]);

    int pivotValue = array[high];

    int i = low;
    for (int j = low; j < high; j++) {
        if (array[j] <= pivotValue) {
            Swap(&array[i], &array[j]);
            i++;
        }
    }

    Swap(&array[i], &array[high]);
    return i;
}

void Quicksort_r(int *array, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(array, low, high);

        Quicksort_r(array, low, pivotIndex - 1);
        Quicksort_r(array, pivotIndex + 1, high);
    }
}

void Quicksort(int *array, int length) {
    srand(time(NULL));
    
    Quicksort_r(array, 0, length - 1);
}

int main() {
    int array[] = {15, 7, 15, 1, 0, 3, 8, 15, 19, 17, 0, 3};

    Quicksort(array, 12);

    for (int i = 0; i < 12; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}