#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include<sys/types.h>
int main()
{
	pid_t result;
	int r_num;
	int pipe_fd[2];
	char buf_r[100] , buf_w[100];
	memset(buf_r,0,sizeof(buf_r)); // 清空
	if(pipe(pipe_fd) < 0){
		printf("创建管道失败\r\n");
		return -1;	
	}
	result = fork(); // 复制一个进程 返回值存在变量result中
	if(result < 0){ // 通过result的值来判断fork函数的返回状况,在这进行出错处理
		perror("创建子进程失败\r\n");
		exit(0);
	}
	else if(result == 0){ //  子进程在这运行
		close(pipe_fd[1]);
		if((r_num = read(pipe_fd[0],buf_r,100)) > 0) {
			printf("子进程从管道读取%d个字符，读取的字符串是:%s\n",r_num,buf_r);
			close(pipe_fd[0]);
			exit(0);
		}
	}
	else // 父进程在这运行
	{
		close(pipe_fd[0]);
		printf("请写入\n");
		scanf("%s",buf_w);
		if(write(pipe_fd[1],buf_w,strlen(buf_w)) != -1){
			printf("父进程向管道写入:  %s\n",buf_w);
		}
		close(pipe_fd[1]);
		waitpid(result,NULL,0);// 调用waitpid 阻塞父进程 等待子进程退出
		exit(0);
	}
	
}