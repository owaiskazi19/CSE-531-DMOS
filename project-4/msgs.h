#include<stdio.h>
#include<stdlib.h>
#include "sem.h"

struct port
{
    Semaphore_t *mutex;
    Semaphore_t *full;
    Semaphore_t *empty;
    int message[10];
}p[100];


void init_port(){

    int i;
    for(int i=0;i<99;i++)
    {
        p[i].full = CreateSem(0);
        p[i].empty = CreateSem(10);
        p[i].mutex = CreateSem(1);
    }
}

void send(int portNo, int buffer[])
{
    P(p[portNo].mutex);
    printf("acquired locks in send \n");
    for(int i=0;i<10;i++)
    {
        p[portNo].message[i] = buffer[i];
    }
    printf("releasing locks in send \n");
    V(p[portNo].mutex);
    V(p[portNo].full);
}


void receive(int portNo, int buffer[])
{
    printf("In receieve \n");
    P(p[portNo].full);
    P(p[portNo].mutex);
    printf("acquired locks in receieve \n");
    for(int i=0;i<10;i++)
    {
         buffer[i] = p[portNo].message[i];
    }
    printf("releasing locks in receieve \n");
    V(p[portNo].mutex);
    V(p[portNo].full);
}
