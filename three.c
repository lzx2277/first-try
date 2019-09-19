#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t sem1;
sem_t sem2;
sem_t sem3;
void* deal_fun1(void *arg)
{
    sem_wait(&sem1);

    printf("A");
    fflush(stdout);

    sem_post(&sem2);
}
void* deal_fun2(void *arg)
{
    sem_wait(&sem2);

    printf("B");
    fflush(stdout);
    
    sem_post(&sem3);
}
void* deal_fun3(void *arg)
{
    sem_wait(&sem3);

    printf("C");
    fflush(stdout);
    
    sem_post(&sem1);
}
int main(int argc, char const *argv[])
{
    sem_init(&sem1,0,1);
    sem_init(&sem2,0,0);
    sem_init(&sem3,0,0);

    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;

    int i=0;
    for(i=0; i<10;i++)
    {
        pthread_create(&tid1,NULL,deal_fun1,NULL);
        pthread_create(&tid2,NULL,deal_fun2,NULL);
        pthread_create(&tid2,NULL,deal_fun3,NULL);
    }
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);

    return 0;
}
