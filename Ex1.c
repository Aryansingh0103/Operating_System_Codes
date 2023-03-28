#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void *thread_func(void *arg) {
    int *thread_num = (int*) arg;

    sem_wait(&semaphore);

    printf("Thread %d is in the critical section.\n", *thread_num);

    sem_post(&semaphore);

    printf("Thread %d is in the non-critical section.\n", *thread_num);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int thread_num1 = 1, thread_num2 = 2;

    // Initialize semaphore with value 1
    sem_init(&semaphore, 0, 1);

    // Create two threads
    pthread_create(&thread1, NULL, thread_func, &thread_num1);
    pthread_create(&thread2, NULL, thread_func, &thread_num2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore);

    return 0;
}
