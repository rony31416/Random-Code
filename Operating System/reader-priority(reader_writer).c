#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;
sem_t wrt;

int readers_count = 0;
int data = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);

    pthread_mutex_lock(&mutex);
    readers_count++;

    // If the first reader, lock the writers
    if (readers_count == 1) {
        sem_wait(&wrt);
    }

    pthread_mutex_unlock(&mutex);

    // Read data
    printf("Reader %d reads: %d\n", reader_id, data);

    pthread_mutex_lock(&mutex);
    readers_count--;

    // If no more readers, unlock the writers
    if (readers_count == 0) {
        sem_post(&wrt);
    }

    pthread_mutex_unlock(&mutex);

    // Sleep for a while to simulate other work
    sleep(1);

   // return NULL;
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);

    sem_wait(&wrt);

    // Write data
    data++;
    printf("Writer %d writes: %d\n", writer_id, data);

    sem_post(&wrt);

    // Sleep for a while to simulate other work
    sleep(1);

   // return NULL;
}

int main() {

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    // Rest of the code...

    int no_r, no_w;
    printf("Enter the number of readers and writers: ");
    scanf("%d %d", &no_r, &no_w);

    pthread_t read[no_r], write[no_w];
    int reader_ids[no_r], writer_ids[no_w];

    for (int i = 0; i < no_r; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&read[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < no_w; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&write[i], NULL, writer, &writer_ids[i]);
    }

    // Let the simulation run for a while
    sleep(10);

    // Cancel threads (this is just for the example, in a real scenario, you'd need to manage threads more gracefully)
    for(int i = 0; i < no_r; i++) {
        pthread_cancel(read[i]);
    }

    for (int i = 0; i < no_w; i++) {
        pthread_cancel(write[i]);
    }

    // Join threads (again, in a real scenario, you'd need a more robust synchronization mechanism)
    for (int i = 0; i < no_r; i++) {
        pthread_join(read[i], NULL);
    }

    for (int i = 0; i < no_w; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
