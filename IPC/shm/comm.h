#ifndef _COMM_H__
#define _COMM_H__
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#define PATHNAME "."
#define PROJ_ID 0x6666

int CreateShm(int size);
int DestoryShm(int shmid);
int GetShm(int size);
#endif