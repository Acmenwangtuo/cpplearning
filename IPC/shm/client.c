#include"comm.h"
int main()
{
    int shmid = GetShm(4096);
    sleep(1);
    //第一次创建共享内存段的时候，它不能被任何进程访问。要想启用对该共享内存的访问，必须将其连接到第一个进程的地址空间中 shmat实现
    char* addr = shmat(shmid,NULL,0);
    sleep(2);
    int i = 0;
    while(i < 26){
        addr[i] =  'A' + i;
        i++;
        addr[i] = 0 ;
        sleep(1);
    }
    //共享内存从当前进程中分离
    shmdt(addr);
    sleep(2);
    return 0;
}