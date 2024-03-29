#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000000
#define SORT_THRESHOLD 10

void insertionSort(int arr[], int low, int high, int *count) {
    int i, j, key;
    for (i = low + 1; i <= high; i++) {
        key = arr[i]; // number to insert to the sorted array
        j = i - 1;

        // check elements from the right of sorted array whether it's larger than key,
        // shift element to the right by one slot if larger
        while (j >= low && arr[j] > key) {
            (*count)++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // insert number into the right slot of the sorted array
        arr[j + 1] = key;
    }

    // for (int i = 1; i <= high; i++) {
    //     for (int j = i; j > 0; j--) {
    //         if (arr[j] < arr[j-1]) {
    //             int temp = arr[j];
    //             arr[j] = arr[j-1];
    //             arr[j-1] = temp;
    //         }
    //     }
    // }
}

void merge(int* arr, int low, int mid, int high, int *count) {
    int i, j, k;
    int n1 = mid - low + 1; // size of Left Array
    int n2 = high - mid; // size of Right Array (high - mid + 1 - 1) = high - mid

    int* L = (int*)malloc(sizeof(int) * n1); // initialise left array
    int* R = (int*)malloc(sizeof(int) * n2); // initialise right array

    // copy over items from left sorted array
    for (i = 0; i < n1; i++)
        L[i] = arr[low + i];

    // copy over items from right sorted array
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = low;

    while (i < n1 && j < n2) {
        (*count)++;
        // compare first item from left array with first item from right array, copy smaller item over
        // repeats until either left or right array is empty
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // copy remaining items from left array
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // copy remaining items from right array
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void hybridSort(int* arr, int low, int high, int *count) {
    // use insertion sort if array is smaller than SORT_THRESHOLD
    if (high - low <= SORT_THRESHOLD) {
        insertionSort(arr, low, high, count);
    // use merge sort if array is bigger than SORT_THRESHOLD
    } else {
        int mid = (low + high) / 2;
        hybridSort(arr, low, mid, count);
        hybridSort(arr, mid + 1, high, count);
        merge(arr, low, mid, high, count);
    }
}

void mergeSort(int* arr, int low, int high, int* count) {
    if (high - low <= 1) {
        return;
    }
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid, count);
    mergeSort(arr, mid + 1, high, count);
    merge(arr, low, mid, high, count);
}

int main() {
    int n, i, count = 0;
    for (n = 1000; n <= MAX; n *= 10) {
        int* arr = (int*)malloc(sizeof(int) * n);
        srand(time(NULL));
        for (i = 0; i < n; i++) {
            arr[i] = rand() % n + 1;
        }
        count = 0;
        hybridSort(arr, 0, n - 1, &count);
        printf("For n = %d, number of key comparisons = %d\n", n, count);
        free(arr);
    }
    return 0;
}
