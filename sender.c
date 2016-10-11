#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st{
  long int my_msg_type;
  char some_text[MAX_TEXT];
};

int main()
{
  int running = 1;
  int msgid;
  int num=0;
  char buffer[BUFSIZ];
  char numtoc[10];
  struct my_msg_st some_data;
 
  msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

  if(msgid == -1){
    fprintf(stderr, "msgget failed with error: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  while(running){

    sleep(1);
    some_data.my_msg_type = 1;
    strcpy(buffer, "msg");
    sprintf(numtoc, "%d", num);
    printf("%s ", numtoc);
    strcat(buffer, numtoc);
    printf("send %s now\n", buffer);
    strcpy(some_data.some_text, buffer);    
      
    if(msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1){
      fprintf(stderr, "msgrcv failed with error : %d\n", errno);
      exit(EXIT_FAILURE);
    }
    num++;
  }
}

    
