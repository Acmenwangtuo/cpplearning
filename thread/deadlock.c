//实现死锁
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
/**
 * @brief 死锁的必要条件
 * 1.互斥条件
 * 2.请求和保持条件
 * 3.不可抢占
 * 4.循环等待
 * @param arg 
 * @return void* 
 */
void* func1(void* arg){
    
    pthread_mutex_lock(&mutex1);
    printf("func1 lock mutex1 ok...\n");
    pthread_mutex_lock(&mutex2);
    printf("func1 lock mutex2 ok...\n");
    while(1)
        printf("---func1 running---\n");
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
    return NULL;
}

void* func2(void* arg){
    while(1){
    pthread_mutex_lock(&mutex2);
    printf("func2 lock mutex2 ok...\n");
    pthread_mutex_lock(&mutex1);
    printf("func2 lock mutex1 ok...\n");

    printf("---func2 running---\n");
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

int main(){
    pthread_t tid1 , tid2;
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);

    pthread_create(&tid1,NULL,func1,NULL);
    pthread_create(&tid2,NULL,func2,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    return 0;
}