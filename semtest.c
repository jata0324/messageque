#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t sem;
pthread_t task[3];
int params[3]={1,2,3};
int arg;
int val;

void Thread(void *param){
  
  while(1){
    sem_wait(&sem);
    arg=*((int *)param);
    sem_post(&sem);
    sleep(1);
  }
}

void main(void)
{
  int i = 0;
  sem_init(&sem, 0, 1);
  for(i=0; i<3; i++)
    pthread_create(&task[i], NULL, (void*(*)(void*))Thread, &params[i]);

  while(1){
    sem_wait(&sem);
    sem_getvalue(&sem, &val);
    printf("arg=%d: value = %d\n", arg, val);
    sem_post(&sem);
    sleep(1);
  }
}
