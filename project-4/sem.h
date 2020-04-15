// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include "Threads.h"

//Semaphore structure with a counter variable and a queue assosciated with it
typedef struct Semaphore_t {
     //pthread_mutex_t mutex;
     struct queue* semQ;
     int count;
} Semaphore_t;

//Accepts the initial count value of the semaphore as a argument, 
//Defines a semaphore variable and allocates memory for it 
//Initializes the seamphore Queue and points the head pointer to null
Semaphore_t* CreateSem(int inputValue)
{   
    Semaphore_t *s;
    s = (Semaphore_t *)malloc(sizeof(Semaphore_t));
    s->count = inputValue;
    s->semQ =  newQueue(s->semQ);
    return s; 
}


/*
 * The P routine decrements the semaphore, and if the value is less than
 * zero then blocks the process by putting the current thread in the semaphore Queue
 * Takes the next process from the ready Q and swaps the context of current process with next process
 */
void P(Semaphore_t *s)
{ 
    printf("entered P \n");
   s->count--;
   if(s->count<0)
    {
        struct TCB_t *prev_thread;
        printf("in P before addQ  \n");
        addQueue(s->semQ, Curr_Thread); //adding the current process to semaphore queue
        printf("in P after addQ  \n");
        prev_thread = Curr_Thread;
        Curr_Thread = delQueue(Q);  // taking the next process from ready Q and swapping its contect with current process
        printf("in P after delQ  %d %d\n",Curr_Thread->thread_id,prev_thread->thread_id);
        swapcontext(&(prev_thread->context), &(Curr_Thread->context));
        printf("in P after swapContext \n");
    }
    printf("Finsihed  P \n");
}


/*
 * The V routine increments the semaphore, and if the value is 0 or
 * negative, wakes up a process from seamphore queue put it into the ready Q and yield to the next runnable thread
 */

void V(Semaphore_t * s)
{    
    s->count++;
    if(s->count<=0)
    {
        addQueue(Q,delQueue(s->semQ));  //deleting the top process from semaphore Q and adding it to theready Q
    }
    yield();
}


