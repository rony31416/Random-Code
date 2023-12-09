#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>


#define NUMBER_OF_THREAD 20
pthread_mutex_t mutx;


int buffer[10];
int count = 0;
int start = 0;
sem_t semEmpty;
sem_t semFull;

void* barber(void* args)
{
    // int num = *(int*)args;

    while(1)
    {
        int num ;
        sem_wait(&semFull);
        pthread_mutex_lock(&mutx);

        num = buffer[start];
        start++;

        pthread_mutex_unlock(&mutx);
        printf("barber busy with %d  \n",num);

        sem_post(&semEmpty);
        sleep(1);
        printf("barber done with %d \n",num);
        buffer[num] = 0;

    }
}

void* customer(void* args)
{
    int y = *(int*)args;
    y%=10;
    int k = y;
    y++;

    while(1)
    {


        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutx);

        if(buffer[k] == 0)
        {

            buffer[count] = y;
            count++;
            printf("customer set on %d\n",y);

        }
        pthread_mutex_unlock(&mutx);

        sem_post(&semFull);
    }

}

int main(int argc,char* argv[])
{
    for(int i = 0 ; i < 10 ; i++ )
    {
        buffer[i] = 0;
    }

    srand(time(NULL));
    pthread_t th[NUMBER_OF_THREAD],bar;
    pthread_mutex_init(&mutx,NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);


    int i;

    for(i = 0  ; i < NUMBER_OF_THREAD ; i++)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(th+i,NULL,&customer,a) != 0)
        {
            perror("failed to create thread\n");
        }
    }

    if(pthread_create(&bar,NULL,&barber,NULL) != 0)
    {
        perror("failed to create thread\n");
    }

    if( pthread_join(bar,NULL) != 0 )
    {
        perror("hoy nai jouin\n");
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
    pthread_mutex_destroy(&bar);
    return;
}


