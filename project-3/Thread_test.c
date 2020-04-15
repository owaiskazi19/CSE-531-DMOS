//Sai Uttej Thunuguntla - 1217167991
//Owais Kazi - 1215161454

#define _XOPEN_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include<unistd.h>
#include "sem.h"

int global=0;
Semaphore_t *mutex;

void functionA()
{
   int local = 0;
    while (1){
        P(mutex);
        global++; 
        local ++;
        printf("Thread(%d)>>>>>>FunctionA incremented global:= %d local:= %d <<<<<<-----\n", Curr_Thread->thread_id, global, local); 
        usleep(1 * 1000000);
        V(mutex);      
    }
}  

void functionB()
{
   int local = 0;
    while (1){
        P(mutex);
        global++; 
        local ++;
        printf("Thread(%d)>>>>>>FunctionB incremented global:= %d local:= %d <<<<<<-----\n",Curr_Thread->thread_id, global, local);       
        usleep(1 * 1000000); 
        V(mutex);
    }
}

// void functionC()
// {
//    int local = 0;
//     while (1){
//         global++; 
//         local ++;
//         printf("Thread(%d)>>>>>>FunctionC incremented global:= %d local:= %d <<<<<<-----\n",Curr_Thread->thread_id, global, local);       
//         usleep(1 * 1000000); 
//         yield();
//     }
// }

int main()
{  
    mutex = CreateSem(1);
    printf("Starting thread \"functionA\"... \n");
    start_thread(functionA);
    printf("Starting thread \"functionB\"... \n");
    start_thread(functionB);
    //printf("Starting thread \"functionC\"... \n");
    //start_thread(functionC);
    run();
    return 1;
}