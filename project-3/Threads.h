#define _XOPEN_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include<unistd.h>
#include "Q.h"
#define SIZE 131072

struct TCB_t *Curr_Thread;
struct queue* Q=NULL;
int count1 = 1;

void start_thread(void (*function)(void))
{
    char *stack = (char *) malloc(SIZE*sizeof(char));
    struct TCB_t *tcb = newitem();
    init_TCB(tcb, function, (void *) stack, SIZE);
    tcb->thread_id=count1;
    count1++;
    if(Q==NULL)
        Q=newQueue(Q);
    addQueue(Q,tcb);
}

void run()
{  
    Curr_Thread =  delQueue(Q);
    ucontext_t parent;     
    getcontext(&parent);   
    swapcontext(&parent,&(Curr_Thread->context));
}

void yield()
{
   struct TCB_t *prev_thread;
   addQueue(Q, Curr_Thread); 
   prev_thread = Curr_Thread;
   Curr_Thread = delQueue(Q);
   swapcontext(&(prev_thread->context), &(Curr_Thread->context));
}