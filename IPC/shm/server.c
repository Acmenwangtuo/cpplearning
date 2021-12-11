#include "comm.h"
int main(){
    int shmid = CreateShm(4096); // 共享内存标志符
    char* addr = shmat(shmid,NULL,0);
    int i = 0;
    while(i++ < 26){
        printf("client# %s\n",addr);
        sleep(1);
    }
    shmdt(addr);
    sleep(2);
    DestoryShm(shmid);
    return 0;
}