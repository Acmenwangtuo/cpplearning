//装饰器模式 允许向一个现有的对象添加新的功能，同时又不改变其结构
//这种类型的设计模式属于结构型模式，他是作为现有的类的一个包装
//代码没有改变Car类的内部结构，还为其增加了新的功能，这就是装饰器模式的作用

#include<iostream>
#include<list>
#include<memory>

using namespace std;

// 抽象构建类 Transform（变形金刚）
class Transform{
public:
    virtual void move() = 0; //纯虚函数
};

class Car : public Transform{
public:
    Car(){
        std::cout << "变形金钢是一辆车！" << endl;
    }
    void move(){
        std::cout << "在陆地上移动"  << endl;
    }
};

// 抽象装饰类
class Changer : public Transform{
public:
    Changer(shared_ptr<Transform> transform){
        this->transform = transform;
    }
    void move(){
        transform->move();
    }
private:
    shared_ptr<Transform> transform;

};

// 具体装饰类
class Robot : public Changer{
public:
    Robot(shared_ptr<Transform> transform) : Changer(transform){
        std::cout << "变成机器人" << std::endl;
    }
    void say(){
        std::cout << "说话!"  << std::endl;
    }
};

// 具体装饰类AirPlane
class Airplane : public Changer{
public:
    Airplane(shared_ptr<Transform> transform) : Changer(transform){
        cout << "变成飞机！" << endl;
    }
    void say(){
        cout << "在天空中飞翔!" << endl; 
    }
};

int main(){
    shared_ptr<Transform> camaro = make_shared<Car>() ; //使用make_shared可以可以减少内存的分配
    camaro->move();
    cout << "----------------" << endl;
    shared_ptr<Robot> bumblebee = make_shared<Robot>(camaro);
    bumblebee->move();
    bumblebee->say();
    return 0;
}
