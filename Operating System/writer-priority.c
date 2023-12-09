#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_data = 0;
int readers = 0;
int write_requests = 0;
sem_t mutex, read_lock, write_lock;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        readers++;
        if (readers == 1) {
            sem_wait(&write_lock);
        }
        sem_post(&mutex);

        // Read from shared_data
        printf("Reader %d reads: %d\n", *(int*)arg, shared_data);

        sem_wait(&mutex);
        readers--;
        if (readers == 0) {
            sem_post(&write_lock);
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&mutex);
        write_requests++;
        if (write_requests == 1) {
            sem_wait(&read_lock);
        }
        sem_post(&mutex);

        sem_wait(&write_lock);

        // Write to shared_data
        shared_data++;
        printf("Writer %d writes: %d\n", *(int*)arg, shared_data);

        sem_post(&write_lock);

        sem_wait(&mutex);
        write_requests--;
        if (write_requests == 0) {
            sem_post(&read_lock);
        }
        sem_post(&mutex);
    }
}

int main() {
    pthread_t reader_threads[NUM_READERS], writer_threads[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&read_lock, 0, 1);
    sem_init(&write_lock, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    return 0;
}
