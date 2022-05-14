#include<pthread.h>
// class single
// {
// private:
//     single(/* args */){}
//     ~single();
// public:
//     static single* getinstance();
// };
// single* single:: getinstance(){
//     static single obj;
//     return &obj;
// }

//C++0X以后 要求编译器内部静态变量的线程安全性，故C++0x以后该实现的安全的
//C++0x之前仍需加锁，其中C++0x是c++11 标准常委标准执勤的草案临时名字所以还得加锁

class single{
private:
    static pthread_mutex_t lock;
    single(){
        pthread_mutex_init(&lock,NULL);
    }
    ~single(){}
public:
    static single* getinstance();
};
pthread_mutex_t single::lock;

single* single::getinstance(){
    pthread_mutex_lock(&lock);
    static single obj;
    pthread_mutex_unlock(&lock);
    return &obj;
}