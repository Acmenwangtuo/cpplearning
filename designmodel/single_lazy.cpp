#include<pthread.h>
#include <unistd.h>
class single{
private:
    // 私有静态指针变量指向唯一实例
    static single *p ;
    // 静态锁 是由于静态函数只能访问静态成员
    static pthread_mutex_t lock;
    single(){
        pthread_mutex_init(&lock,NULL);
    }
    ~single(){}
public:
    //公有静态方法获取实例
    static single* getinstance();
};
pthread_mutex_t single::lock;

single* single::p = NULL;
// 线程安全的单例模式
// 为什么使用双检测？只检测一次不行吗
// 如果只检测一次，在每次调用获取实例的方法时，都需要加锁，这将严重影响程序性能。
//  双层检测可以有效避免这种情况，仅在第一次创建单例的时候加锁，其他时候都不再符合NULL == p的情况，直接返回已创建好的实例
single* single::getinstance(){
    if(p == NULL){
        pthread_mutex_lock(&lock);
        if(p == NULL){
            p = new single;
        }
        pthread_mutex_unlock(&lock);
    }
    return p;
}
int main(){
    single* p = single::getinstance();
    // cout << "heheh" << endl;
}