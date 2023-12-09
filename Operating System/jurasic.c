#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

sem_t sem_visitor, sem_car;
int CYCLES;

void *Visitor(void *);
void *Car(void *);

int main() {
    printf("\t\t------------Operating System Project------------\n\n");
    printf("\t\tJurrassic Park Problem Using Semaphores\n\n");
    
    int VISITORS, CARS;

    printf("Enter the No of passengers:\n");
    scanf("%d", &VISITORS);
    if (VISITORS < 0) {
        printf("Enter Positive no passengers only\n Try again\n");
        exit(0);
    }

    printf("Enter the No of cars:\n");
    scanf("%d", &CARS);
    if (CARS < 0) {
        printf("Enter Positive no cars only\n Try again\n");
        exit(0);
    }

    printf("Enter the No of cycles:\n");
    scanf("%d", &CYCLES);
    if (CYCLES < 0) {
        printf("Enter Positive no cycles only\n Try again\n");
        exit(0);
    }

    pthread_t visi[VISITORS], car[CARS];
    int i, v[VISITORS];

    sem_init(&sem_car, 0, 1);
    sem_init(&sem_visitor, 0, 1);

    srand(time(NULL));

    for (i = 0; i < VISITORS; i++) {
        v[i] = i;
        printf("visitor %d", i);
         int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&visi[i], NULL, Visitor, a)) {
            printf("Thread created Vis %d ", i);
            exit(1);
        }
    }

    for (i = 0; i < CARS; i++) {
        v[i] = i;
        printf("Car %d", i);
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&car[i], NULL, Car, a)) {
            printf("Car Thread created %d\n", i);
            exit(1);
        }
    }

    for (i = 0; i < VISITORS; i++) {
        printf("visitors waiting %d\n", i);
        pthread_join(visi[i], NULL);
    }

    printf("\n\t---- All Passengers are done with all cycles completed---- \n");

    return 0;
}

void *Visitor(void *p) {
    extern sem_t sem_car, sem_visitor;
    int i, *index;

    index = (int*)p;

    for (i = 0; i < CYCLES; i++) {
        fprintf(stdout, "Passengers Thread No:% d in the museum\n", *index + 1);
        sleep(rand() % 4);

        sem_post(&sem_car);
        printf("gari barse..\n");

        sem_wait(&sem_visitor);
        printf("vistor komse..\n");

        fprintf(stdout, "Passengers Thread No:% d is in the car\n", *index + 1);
        sleep(rand() % 3);
    }

    fprintf(stdout, "Passengers Thread No:% d has finished his% d CYCLES.\n", *index + 1, CYCLES);
    return NULL;
}

void *Car(void *p) {
    int *index;
    extern sem_t sem_car, sem_visitor;
    index = (int*)p;

    printf(" car %p  waiting for passengers %d\n", (void *)&sem_car, *index + 1);


    while (1) {
        sem_wait(&sem_car);
        printf("gari komtese..\n");

        sleep(rand() % 3);

        sem_post(&sem_visitor);
        printf("visitor barse..\n");
    }

  printf("Car %p  finish with museum %d\n", (void *)&sem_car, *index + 1);

    return NULL;
}

