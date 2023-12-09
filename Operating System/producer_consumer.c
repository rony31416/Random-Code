#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>


#define NUMBER_OF_THREAD 2
pthread_mutex_t mutx;


int buffer[10];
int count = 0;
sem_t semEmpty;
sem_t semFull;

void* producer(void* args)
{

    while(1)
    {
        int x;
        x = rand() % 30;
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutx);

        buffer[count] = x;
        count++;

        printf("produced by producer = %d \n",x);


        pthread_mutex_unlock(&mutx);

        sem_post(&semFull);
    }


}


void* consumer(void* args)
{
    while(1)
    {
        int y;



        pthread_mutex_lock(&mutx);
         sem_wait(&semFull);


        y = buffer[count - 1] ;
        count--;

        printf("consume by consumer = %d\n",y);

        sem_post(&semEmpty);

        pthread_mutex_unlock(&mutx);



        sleep(1);

    }


}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    pthread_t th[NUMBER_OF_THREAD];
    pthread_mutex_init(&mutx,NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);




    int i;
    for(i = 0  ; i < NUMBER_OF_THREAD ; i++)
    {
        if(i % 2  == 0 )
        {
            if(pthread_create(th+i,NULL,&producer,NULL) != 0)
            {
                perror("failed to create thread\n");
            }

        }
        else
        {
            if(pthread_create(th+i,NULL,&consumer,NULL) != 0)
            {
                perror("failed to create thread\n");
            }
        }

    }

    for(i = 0 ; i < NUMBER_OF_THREAD ; i++)
    {
        if(pthread_join(th[i],NULL) != 0)
        {
            perror("error to join thread\n");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutx);
    return;
}

