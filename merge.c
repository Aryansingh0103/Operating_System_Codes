#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

int arr[MAX_SIZE], n;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void* merge_sort_thread(void* arg) {
    int* data = (int*) arg;
    int l = data[0];
    int r = data[1];

    if (l < r) {
        int m = l + (r - l) / 2;

        // Create two threads for left and right sub-arrays
        pthread_t left_thread, right_thread;
        int left_data[2] = {l, m};
        int right_data[2] = {m + 1, r};

        pthread_create(&left_thread, NULL, merge_sort_thread, left_data);
        pthread_create(&right_thread, NULL, merge_sort_thread, right_data);

        // Wait for both threads to finish
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        // Merge the left and right sub-arrays
        merge(arr, l, m, r);
    }

    pthread_exit(NULL);
}

int main() {
    int i;
    pthread_t sort_thread;

    printf("Enter the number of elements in the array (maximum %d): ", MAX_SIZE);
    scanf("%d", &n);

    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Create a thread for the entire array
    int data[2] = {0, n-1};
    pthread_create(&sort_thread, NULL, merge_sort_thread, data);

    // Wait for the thread to finish
    pthread_join(sort_thread, NULL);

    // Display the sorted array
    printf("The sorted array is:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
