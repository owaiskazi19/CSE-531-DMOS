//Sai Uttej Thunuguntla - 1217167991
//Owais Kazi - 1215161454

#define _XOPEN_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include<unistd.h>
#include "Threads.h"

int global=0;

void functionA()
{
   int local = 0;
    while (1){
        global++; 
        local ++;
        printf("Thread(%d)>>>>>>FunctionA incremented global:= %d local:= %d <<<<<<-----\n", Curr_Thread->thread_id, global, local); 
        usleep(1 * 1000000);
        yield();       
    }
}  

void functionB()
{
   int local = 0;
    while (1){
        global++; 
        local ++;
        printf("Thread(%d)>>>>>>FunctionB incremented global:= %d local:= %d <<<<<<-----\n",Curr_Thread->thread_id, global, local);       
        usleep(1 * 1000000); 
        yield();
    }
}

void functionC()
{
   int local = 0;
    while (1){
        global++; 
        local ++;
        printf("Thread(%d)>>>>>>FunctionC incremented global:= %d local:= %d <<<<<<-----\n",Curr_Thread->thread_id, global, local);       
        usleep(1 * 1000000); 
        yield();
    }
}

int main()
{  
    printf("Starting thread \"functionA\"... \n");
    start_thread(functionA);
    printf("Starting thread \"functionB\"... \n");
    start_thread(functionB);
    printf("Starting thread \"functionC\"... \n");
    start_thread(functionC);
    run();
    return 1;
}