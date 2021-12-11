#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#define BUF_SIZE 30
int main(int argc, char const *argv[])
{
    fd_set reads,temps;
    int result , str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    FD_ZERO(&reads); // 将所有位置都初始化为0
    FD_SET(0,&reads); // 0 is standard input  将fd0 置为1
    /*
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;
    */
   while(1){
       temps = reads;
       timeout.tv_sec = 5;
       timeout.tv_usec = 0;
       // select 函数
       // @parm1: maxfd 文件描述符的数量
       // @parm2: readset 将所有关注“是否存在待读取数据”的文件描述符注册到fd_set 变量 传递地址
       // @parm3: writeset 将所有关注“是否传输无阻塞数据”的文件描述符注册到fd_set 变量 传递地址
       // @parm4: except 将所有关注“是否传输无阻塞数据”的文件描述符注册到fd_set 变量 传递地址
       // @parm5: timeout 调用select函数后，为防止无限阻塞 ，传递超时信息
       // return ： 发生错误返回-1 ， 超时返回0 发生关注的事件返回大于0的值 = 发生事件的文件描述符数
       result = select(1,&temps,0,0,&timeout);
       if(result == -1){
           puts("Select() errorr!");
           break;
       }
       else if(result==0) {
           puts("Time--Out");
       }
       else{
           if(FD_ISSET(0,&temps)){ // 包含id信息
               str_len = read(0,buf,BUF_SIZE);
               buf[str_len] = 0;
               printf("message from console: %s",buf);
           }
       }
   }
    return 0;
}