#include <stdio.h>
#include <stdlib.h>
#include "threads.h"

int a[3];
typedef struct semaphore_t {
     pthread_mutex_t mutex;
     pthread_cond_t cond;
     int count;
} semaphore_t;

void init_sem(semaphore_t *s, int i)
{   
    s->count = i;
    pthread_mutex_init(&(s->mutex), NULL);
    pthread_cond_init(&(s->cond), NULL);
}

void P(semaphore_t *sem)
{   
    pthread_mutex_lock (&(sem->mutex)); 
    sem->count--;
    if (sem->count < 0) pthread_cond_wait(&(sem->cond), &(sem->mutex));
    pthread_mutex_unlock (&(sem->mutex)); 
}

void V(semaphore_t * sem)
{   
    pthread_mutex_lock (&(sem->mutex)); 
    sem->count++;
    if (sem->count <= 0) {
	pthread_cond_signal(&(sem->cond));
    }
    pthread_mutex_unlock (&(sem->mutex)); 
    pthread_yield_np();
}


semaphore_t mutex;

void function_1(void)
{
        P(&mutex);
        a[0]++;
        printf("in Child 1 a[0] is %d \n",a[0]);
        sleep(1);
	    V(&mutex);
}    

void function_2(void)
{ 
        P(&mutex);
        a[1]++;
        printf("in Child 2 a[1] is %d \n",a[1]);
        sleep(1);
	    V(&mutex);
    
}    

void function_3(void)
{
        P(&mutex);
        a[2]++;
        printf("in Child 3 a[2] is %d \n",a[2]);
        sleep(1);
	    V(&mutex);
    
}    

int main()
{
    a[0] = a[1] = a[2] = 0;
    init_sem(&mutex, 1);
    start_thread(function_1, NULL);
    sleep(1);
    start_thread(function_2, NULL);
    sleep(1);
    start_thread(function_3, NULL);
    sleep(1);
    printf(" array in main %d %d %d \n",a[0],a[1],a[2]);
    
    while(1) {
        
        function_1();
        function_2();
        function_3();
        printf(" array in main %d %d %d \n",a[0],a[1],a[2]);
    }

    return 0;
}




