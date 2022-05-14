#include<iostream>
#include<string>
#include<list>
using namespace std;
class Subject;
// 观察者 基类（内部实例化了被观察者的对象sub）
class Observer{
protected:
    string name;
    Subject *sub;
public:
    Observer(string name,Subject *sub){
        this->name = name;
        this->sub = sub;
    }
    virtual void update() = 0;
};

class StockObserver : public Observer{
public:
    StockObserver(string name,Subject *sub) : Observer(name,sub){}
    void update();
};

class NBAObserver : public Observer{
public:
    NBAObserver(string name,Subject *sub) : Observer(name, sub){}
    void update();
};

class Subject{
protected:
    std::list<Observer* > observers;
public:
    string action;
    virtual void attach(Observer *) = 0;
    virtual void detach(Observer *) = 0;
    virtual void notify() = 0;
};

class Secretary : public Subject {
    void attach(Observer *observer) {
        observers.push_back(observer);
    }
    void detach(Observer *observer) {
        list<Observer *>::iterator iter = observers.begin();
        while (iter != observers.end()) {
            if ((*iter) == observer) {
                observers.erase(iter);
                return;
            }   
            ++iter;
        }
    }
    void notify(){
        list<Observer *> :: iterator iter = observers.begin();
        while(iter != observers.end()){
            (*iter) -> update();
            ++iter;
        }
    }
};

void StockObserver::update(){
    cout << name << " 收到消息: " << sub->action << endl;
    if(sub->action == "老板来了!"){
        cout << "我马上关闭股票，装作很认真工作的样子!" << endl;
    }
}

void NBAObserver::update(){
    cout << name << " 收到消息: " << sub->action << endl;
    if(sub->action == "老板来了!"){
        cout << "我马上关闭NBA,装做工作很认真的样子!" << endl;
    }
}

int main()
{
    Subject* BOSS = new Secretary();
    Observer *xa = new NBAObserver("xa",BOSS);
    Observer *xb = new NBAObserver("xb",BOSS);
    Observer *xc = new StockObserver("xc",BOSS);

    BOSS->attach(xa);
    BOSS->attach(xb);
    BOSS->attach(xc);

    BOSS->action = "去吃饭了!" ;
    BOSS->notify();
    cout << endl;
    BOSS->action = "老板来了!";
    BOSS->notify();
    return 0;

}