#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

void P(int semid){
    struct sembuf my_buff;
    memset(&my_buff,0,sizeof(my_buff));
    my_buff.sem_num = 0; // 除非使用一组信号量否则都为0
    my_buff.sem_op = -1; // 每次需要改变的数值 P = -1 V = 1
    my_buff.sem_flg = SEM_UNDO; // 一般默认为这个 操作系统将跟踪这个值退出时清理
    semop(semid,&my_buff,1);// semid 为信号量标识符  用于改变信号量的值
}

void V(int semid){
    struct sembuf my_buff;
    memset(&my_buff,0,sizeof(my_buff));
    my_buff.sem_num = 0; // 除非使用一组信号量否则都为0
    my_buff.sem_op = 1; // 每次需要改变的数值 P = -1 V = 1
    my_buff.sem_flg = SEM_UNDO; // 一般默认为这个 操作系统将跟踪这个值退出时清理
    semop(semid,&my_buff,1);// semid 为信号量标识符  用于改变信号量的值   
}

int main(int argc, char const *argv[])
{
    key_t mykey = 1234;
    int my_sem;
    my_sem = semget(mykey,1,0666 | IPC_CREAT);
    if(my_sem == -1){
        printf("segment error!\n");
        exit(1);
    }
    printf("getval:%d\n",semctl(my_sem,0,GETVAL));
    printf("p.....\n");
    P(my_sem); //在等那边结束
    printf("sem1 finished!\n");
    V(my_sem);
    return 0;
}
