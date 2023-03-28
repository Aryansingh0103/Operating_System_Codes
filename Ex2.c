#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 1000

/* Function to merge two sub-arrays */
void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
    }

    while (i < leftSize) {
        arr[k++] = left[i++];
    }

    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

/* Function to perform merge sort recursively */
void* mergeSort(void *arg) {
    int *arr = (int*) arg;
    int size = arr[0];
    int *data = &arr[1];

    if (size < 2) {
        return NULL;
    }

    int mid = size / 2;
    int *left = (int*) malloc((mid + 1) * sizeof(int));
    int *right = (int*) malloc((size - mid + 1) * sizeof(int));

    left[0] = mid;
    right[0] = size - mid;

    for (int i = 0; i < mid; i++) {
        left[i + 1] = data[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid + 1] = data[i];
    }

    /* Sorting left and right sub-arrays using threads */
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, mergeSort, left);
    pthread_create(&tid2, NULL, mergeSort, right);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    /* Merging left and right sub-arrays */
    merge(data, left + 1, mid, right + 1, size - mid);

    free(left);
    free(right);

    return NULL;
}

/* Function to print the sorted array */
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* Driver function to test above functions */
int main() {
    int arr[MAX_SIZE + 1];
    int size;

    printf("Enter the number of elements to be sorted (max 1000): ");
    scanf("%d", &size);

    printf("Enter the elements to be sorted:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i + 1]);
    }

    arr[0] = size;

    printf("Given array is: ");
    printArray(arr + 1, size);

    pthread_t tid;
    pthread_create(&tid, NULL, mergeSort, arr);
    pthread_join(tid, NULL);

    printf("Sorted array is: ");
    printArray(arr + 1, size);

    return 0;
}
