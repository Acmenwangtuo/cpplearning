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
	int i,rfd,wfd,len = 0 ,fd_in;
	char str[32];
	int flag, stdinflag;
	fd_set write_fd, read_fd;
	struct timeval net_timer;
	mkfifo("fifo1",S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH); // mkfifo 函数创建命名管道
	mkfifo("fifo2",S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);// mkfifo 函数创建命名管道
	wfd = open("fifo1",O_WRONLY); // 以写方式打开管道文件 
	rfd = open("fifo2",O_RDONLY); // 以只读方式打开管道文件
	if(rfd <= 0 || wfd <= 0) return 0;
	printf("这是张三端!\r\n");
	while(1){
		FD_ZERO(&read_fd); // 清空一个文件描述符集
		FD_SET(rfd,&read_fd); // 将一个文件描述符rfd加入文件描述符集 read_fd
		FD_SET(fileno(stdin),&read_fd);
		net_timer.tv_sec = 5;
		net_timer.tv_usec = 0; 
		memset(str,0,sizeof(str)); // 初始化清空
		if(i = select(rfd + 1,&read_fd,NULL,NULL,&net_timer) <= 0){
			continue;
		}
		if(FD_ISSET(rfd,&read_fd))
		{
			read(rfd,str,sizeof(str)); // 读取管道，将管道内容存入str变量
			printf("------------------------------\n");
			printf("李四:%s\n",str); // 打印出str内容
			
		}
		if(FD_ISSET(fileno(stdin),&read_fd))
		{
			printf("-----------------------------\n");
			fgets(str,sizeof(str),stdin);
			len = write(wfd,str,strlen(str));
		}
	}
	close(rfd);
	close(wfd);
}