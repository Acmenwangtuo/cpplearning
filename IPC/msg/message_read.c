#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
typedef struct _msg
{
    long mtype; // 长整型判断类型
    char mtext[50];
}MSG;
int main(int argc, char const *argv[])
{
    key_t key;
    int msgqid;
    MSG msg;
    key = ftok(".",2012);
    msgqid = msgget(key,IPC_CREAT|0666);
    if(msgqid == -1){
        perror("msgget");
        exit(-1);
    }
    msgrcv(msgqid,&msg,sizeof(msg.mtext),10,0);
    printf("msg.mtext=%s\n",msg.mtext);
    msgctl(msgqid,IPC_RMID,NULL);
    return 0;
}
