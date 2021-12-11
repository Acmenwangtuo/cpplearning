src = $(wildcard *.c) # 来获取工作目录下的所有的.c文件列表
obj = $(patsubst %.c,%.o,$(src)) #用所有.o 替换.c
#my first makefile
CC = gcc
CFLAGS = -Wall 
all: server client
server: server.o comm.o
	$(CC) server.o comm.o -o server $(CFLAGS)
client: client.o comm.o
	$(CC) client.o comm.o -o client $(CFLAGS)
%.o: %.c
	$(CC) -c $< -Wall
.PHONY: clean all #伪目标
clean:
	-rm -rf server client $(obj)
