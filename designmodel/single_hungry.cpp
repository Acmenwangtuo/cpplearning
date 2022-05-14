#include<pthread.h>
#include<iostream>
using namespace std;
class single{
private:
    static single* p;
    single(){}
    ~single(){}
public:
    static single* getinstance();
};
single* single::p = new single();
single* single::getinstance(){
    return p;
}

int main(){
    single* p1 = single::getinstance();
    single* p2 = single::getinstance();
    if(p1 == p2) cout << "same" << endl;
    return 0;
}