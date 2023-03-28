#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

int arr[MAX_SIZE], sum = 0, n;

void* add_from_beginning(void* arg) {
    int i, s = 0;
    for (i = 0; i < n/2; i++) {
        s += arr[i];
    }
    sum += s;
    return NULL;
}

void* add_from_end(void* arg) {
    int i, s = 0;
    for (i = n-1; i >= n/2; i--) {
        s += arr[i];
    }
    sum += s;
    return NULL;
}

int main() {
    int i;
    pthread_t t1, t2;

    printf("Enter the number of elements in the array (maximum %d): ", MAX_SIZE);
    scanf("%d", &n);

    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pthread_create(&t1, NULL, add_from_beginning, NULL);
    pthread_create(&t2, NULL, add_from_end, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Sum of all the elements in the array is %d\n", sum);

    return 0;
}
