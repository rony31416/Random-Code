#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CHAIRS 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ta_condition = PTHREAD_COND_INITIALIZER;
pthread_cond_t student_condition = PTHREAD_COND_INITIALIZER;

int waiting_students = 0;

void *ta_function(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        
        // If no students are waiting, TA takes a nap
        if (waiting_students == 0) {
            printf("TA is sleeping.\n");
            pthread_cond_wait(&ta_condition, &mutex);
            printf("TA is awakened.\n");
        }

        // Helping a student
      //  printf("TA is helping a student.\n");
        sleep(0.5); // Simulating TA helping a student

        // Notify the waiting student that TA is available
        pthread_cond_signal(&student_condition);

        pthread_mutex_unlock(&mutex);
    }
}

void *student_function(void *arg) {
    int student_id = *(int *)arg;

    pthread_mutex_lock(&mutex);

    // If all chairs are occupied, student comes back later
    if (waiting_students == NUM_CHAIRS) {
        printf("Student %d leaves because no chairs are available.\n", student_id);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    // Student takes a chair
    waiting_students++;
    printf("Student %d takes a chair. (%d chairs occupied)\n", student_id, waiting_students);

    // If TA is sleeping, wake up the TA
    if (waiting_students == 1) {
        printf("Student %d wakes up the TA.\n", student_id);
        pthread_cond_signal(&ta_condition);
    }

    // Wait until TA is available
    pthread_cond_wait(&student_condition, &mutex);

    // Student is getting help
    waiting_students--;
    printf("Student %d is getting help. (%d chairs occupied)\n", student_id, waiting_students);

    pthread_mutex_unlock(&mutex);

    // Simulating student getting help
    sleep(1);

    return NULL;
}

int main() {
    pthread_t ta_thread, student_threads[NUM_CHAIRS];
    int student_ids[NUM_CHAIRS];

    // Create TA thread
    pthread_create(&ta_thread, NULL, ta_function, NULL);

    // Create student threads
    for (int i = 0; i < NUM_CHAIRS; i++) {
        student_ids[i] = i + 1;
        pthread_create(&student_threads[i], NULL, student_function, &student_ids[i]);
        sleep(1); // Introducing delay between student arrivals
    }

    // Join TA thread
    pthread_join(ta_thread, NULL);

    // Join student threads
    for (int i = 0; i < NUM_CHAIRS; i++) {
        pthread_join(student_threads[i], NULL);
    }

    return 0;
}

