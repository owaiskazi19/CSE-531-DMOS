#include<stdio.h>
#include<stdlib.h>
#include "sem.h"

#define N 10

struct port
{
    Semaphore_t *mutex;
    Semaphore_t *full;
    Semaphore_t *empty;
    int message[N][N];
    int in;
    int out;
}p[100];


void init_port(){

    int i;
    for(int i=0;i<99;i++)
    {
        p[i].full = CreateSem(0);
        p[i].empty = CreateSem(N);
        p[i].mutex = CreateSem(1);
        p[i].in = 0;
        p[i].out = 0;
    }
}

void send(int portNo, int buffer[])
{
   
    P(p[portNo].empty);
    P(p[portNo].mutex);
    for(int i=0;i<N;i++)
    {
        p[portNo].message[p[portNo].in][i] = buffer[i];
    }
    p[portNo].in =  (p[portNo].in +1)% N;

    V(p[portNo].mutex);
    V(p[portNo].full);
}


void receive(int portNo, int buffer[])
{
    
    P(p[portNo].full);
    P(p[portNo].mutex);
    for(int i=0;i<N;i++)
    {
         buffer[i] = p[portNo].message[p[portNo].out][i];
    }
    p[portNo].out =  (p[portNo].out+1) % N;
    V(p[portNo].mutex);
    V(p[portNo].empty);
}