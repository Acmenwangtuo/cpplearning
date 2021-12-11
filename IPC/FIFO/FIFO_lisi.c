#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/select.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h> // read write
int main()
{
    int i,rfd,wfd,len = 0,fd_in;
    char str[32];
    int flag, stdinflag;
    fd_set write_fd , read_fd;
    struct timeval net_timer;
    mkfifo("fifo1",S_IWUSR|S_IRUSR|S_IROTH); // mkfifo函数创建命名管道
    mkfifo("fifo2",S_IWUSR|S_IRUSR|S_IROTH); // mkfifo函数创建命名管道
    rfd = open("fifo1",O_RDONLY); // 阻塞读
    wfd = open("fifo2",O_WRONLY); // 阻塞写
    if(rfd <= 0 || wfd <= 0) return 0;
    printf("这是李四端!\n");
    while (1)
    {
        FD_ZERO(&read_fd); // 清除一个文件描述符
        FD_SET(rfd,&read_fd);// 将文件描述符rfd加入文件描述符号集read_fd
        FD_SET(fileno(stdin),&read_fd);
        net_timer.tv_sec = 5;
        net_timer.tv_usec = 0;
        memset(str,0,sizeof(str));
        if(i=select(rfd+1,&read_fd,NULL,NULL,&net_timer) < 0) continue;
        if(FD_ISSET(rfd,&read_fd)){
            read(rfd,str,sizeof(str)); // 读取管道
            printf("-------------------\n");
            printf("张三: %s\n",str); 
        }
        if(FD_ISSET(fileno(stdin),&read_fd))
        {
            printf("---------------------\n");
            fgets(str,sizeof(str),stdin);
            len = write(wfd,str,strlen(str)); // 写入管道
        }
    }
    close(rfd);
    close(wfd);
    
}