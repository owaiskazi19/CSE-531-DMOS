#include"TCB.h"
#include<stdio.h>
#include<stdlib.h>


struct queue{
  struct TCB_t *head;
};

struct TCB_t* newitem(void)
{
    struct item *Item = (struct item *)malloc(sizeof(struct TCB_t));
    return Item;
}

struct queue* newQueue(struct queue *Q) {
   Q = (struct queue *)malloc(sizeof(struct queue));
   Q->head = NULL;
   return Q;
}


int isEmpty(struct queue *Q)
{
    if(Q->head==NULL)
        return 1;
    return 0;
}

void addQueue(struct queue *Q,struct TCB_t *tcb)
{
     if(isEmpty(Q)) {
         Q->head = tcb;
         Q->head->next = Q->head;
         Q->head->prev = Q->head;
     }
     else
     {
        tcb->prev = Q->head->prev;
        tcb->next = Q->head;
        Q->head->prev->next = tcb;
        Q->head->prev = tcb;
     }
}


struct TCB_t* delQueue(struct queue *Q) {
     if(isEmpty(Q))
     {
		 printf("error Queue already empty\n ");
         return NULL;
     }

    struct TCB_t *res = Q->head;
    if(res == res->next)
    {
        Q->head=NULL;
        return res;
    }
    
    Q->head = Q->head->next;
    Q->head->prev = res->prev;
    res->prev->next = Q->head;
    return res;
}