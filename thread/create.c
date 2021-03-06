#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
pthread_t ntid;

void printids(const char *s)
{
	pid_t  pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
	  (unsigned long)tid, (unsigned long)tid);
}

void * thr_fn(void *arg)
{
	printids("new thread: ");
	return((void *)0);
}

int main(void)
{
	int	err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL); //  指向ntid的内存单元，从thr_fn这个函数指针执行，最后一个是他的参数
	if (err != 0)
        printf("can't create thread");
		// err_exit(err, "can't create thread");
	printids("main thread:");
	sleep(1);
	exit(0);
}
