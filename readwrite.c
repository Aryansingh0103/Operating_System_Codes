#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_READERS 5

pthread_mutex_t mutex;
pthread_cond_t can_read, can_write;
int readers = 0;
bool writing = false;

void *reader(void *arg) {
    int id = *((int *) arg);
    printf("Reader %d started.\n", id);
    pthread_mutex_lock(&mutex);

    while (writing) {
        pthread_cond_wait(&can_read, &mutex);
    }
    readers++;
    pthread_mutex_unlock(&mutex);
    printf("Reader %d is reading.\n", id);
    pthread_mutex_lock(&mutex);
    readers--;

    if (readers == 0) {
        pthread_cond_signal(&can_write);
    }

    pthread_mutex_unlock(&mutex);
    printf("Reader %d finished.\n", id);
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *) arg);
    printf("Writer %d started.\n", id);

    pthread_mutex_lock(&mutex);

    while (readers > 0 || writing) {
        pthread_cond_wait(&can_write, &mutex);
    }
    writing = true;
    pthread_mutex_unlock(&mutex);
    printf("Writer %d is writing.\n", id);

    pthread_mutex_lock(&mutex);
    writing = false;
    pthread_cond_signal(&can_read);
    pthread_cond_signal(&can_write);
    pthread_mutex_unlock(&mutex);
    printf("Writer %d finished.\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t reader_threads[MAX_READERS], writer_thread;
    int reader_ids[MAX_READERS], writer_id = 1;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&can_read, NULL);
    pthread_cond_init(&can_write, NULL);

    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    pthread_create(&writer_thread, NULL, writer, &writer_id);
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    pthread_join(writer_thread, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&can_read);
    pthread_cond_destroy(&can_write);

    return 0;
}
