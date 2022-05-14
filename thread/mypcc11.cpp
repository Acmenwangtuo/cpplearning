#include <iostream>           
#include <queue>
#include <thread>             
#include <mutex>              
#include <condition_variable> 
using namespace std;

mutex mtx;
condition_variable cv;  // 条件变量是一种同步机制，要和mutex以及lock一起使用
queue<int> q;

void product(int id){
    while(1){
        unique_lock<mutex> lck(mtx);
        //lck.lock(); 是RAII 不用再锁
        q.push(id);
        printf("product id = %d\n",id);
        lck.unlock();
        cv.notify_all();
    }
}

void consumer(){
    while(1){
        unique_lock<mutex> lck(mtx);
        //lck.lock();
        //while(q.empty()) cv.wait(lck);
        cv.wait(lck,[&]{return q.size() != 0;});
        int id = q.front();
        printf("consumer id = %d\n",id);
        q.pop();
        lck.unlock();
    }
}

int main(){
    thread consumers[2], producers[2];

    // thread a = thread(product,1);
    // thread b = thread(consumer);
    // a.join();
    // b.join();
    // spawn 2 consumers and 2 producers:
    for (int i = 0; i < 2; ++i)
    {
       
        producers[i] = thread(product, i + 1);
        consumers[i] = thread(consumer);
    }

    //join them back: (in this program, never join...)
    for (int i = 0; i < 2; ++i)
    {
        consumers[i].join();
        producers[i].join();
        
    }

    //system("pause");
    return 0;
}