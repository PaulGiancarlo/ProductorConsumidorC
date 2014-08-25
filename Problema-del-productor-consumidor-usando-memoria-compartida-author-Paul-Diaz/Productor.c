/**
 * Problema del productor consumidor
 * usando memoria compartida
 * @author Paul Diaz
 * 
 * 
 * 
 * 
 * */
 
 
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#define N 5


struct buffer
{
int b[N]; 
sem_t empty,full;
int in,out;
}buf;

void *Productor()
{
int i=1;
while(1)
{
sem_wait(&(buf.empty));
buf.b[buf.in]=i;
buf.in=(buf.in+1)%N;
printf("\nProducido :%d",i++);
sleep(2);
sem_post(&(buf.full));
}
}

void *Consumidor()
{
int item;
while(1)
{
sem_wait(&(buf.full));
item=buf.b[buf.out];
buf.out=(buf.out+1)%N;
printf("\nConsumido :%d",item);
sem_post(&(buf.empty));
}
}

void main()
{
pthread_t t1,t2;
sem_init(&(buf.empty),0,N);
sem_init(&(buf.full),0,0);
buf.in=0;
buf.out=0;
pthread_create(&t1,NULL,Productor,NULL);
pthread_create(&t2,NULL,Consumidor,NULL);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
}
