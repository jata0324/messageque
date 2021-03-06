#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int val;
int arg1=0, arg2=1;

void *Thread(void* arg)
{

  int i, j;
  for(i=0; ; i++)
    {
      pthread_mutex_lock(&mutex);
      val = *(int*)arg;
      printf("thread %dth iteration: val = %d\n", *(int*)arg, i , val);
      pthread_mutex_unlock(&mutex);
      sleep(1);
    }
}

int main(void){
  pthread_t thread1, thread2;
  pthread_attr_t attr;

  struct sched_param param;
  int policy;

  pthread_getschedparam(pthread_self(), &policy, &param);
  param.sched_priority =1;
  policy = SCHED_RR;
  pthread_setschedparam(pthread_self(), policy, &param);
  pthread_attr_init(&attr);
  pthread_attr_setschedpolicy(&attr, SCHED_RR);

  pthread_create(&thread1, &attr, (void*(*)(void*))Thread, &arg1);
  pthread_create(&thread2, &attr, (void*(*)(void*))Thread, &arg2);

  pthread_exit(0);
  return 0;
}
