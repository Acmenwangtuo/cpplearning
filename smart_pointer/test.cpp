#include <iostream>
#include <memory>
#include <cstring>
#include "smart_ptr.h"

class Test {
	public:
		Test() {
			name = "";
		};
		Test(char *i) {
			name = i;
		}
		void showName() {
			cout << name << endl;
		}
		string &getName() {
			return name;
		}
	private:
		string name;
};

class A {
	public:
		~A() {
			cout << "kill A\n";
		}
};

//如果程序执行过程中抛出了异常，unique_ptr就会释放它所指向的对象
//传统的new则不行
unique_ptr<A> fun1() {
	unique_ptr<A> p(new A());
	return p;
}

void test_ptr() {
	SharedPtr<Test> p1(new Test("abcd"));
	p1->showName();
	SharedPtr<Test> p2(p1);
	*p2 = Test("defg");
	p1->showName();
	cout << "@1: " << p1.getRefCount() << endl;


	SharedPtr<Test> p3(new Test("xxx"));
	p3 = p2;
	cout << "@2: " << p1.getRefCount() << endl;
}

void test_ptr_2() {
	UniquePtr<Test> p1(new Test("abcd"));
	p1->showName();
	p1.reset(new Test("124"));
	p1->showName();

	Test *t = p1.release();
	cout << "t: " << t->getName() << endl;
	// 这里做了一个很顽皮的实验，如果把 unique_ptr指向的元素取出来，然后获取它的指针，然后让另外一个unique_ptr接管，那么就出问题了
//    p1.reset( &(*p2)); // 报错了pointer being freed was not allocated
//    UniquePrt<Test> p3 (new Test("xxx"));

}

int main() {
	//test_ptr();
	/*
	打印结果为：
	abcd
	defg
	@1: 2
	free
	@2: 3
	deconstructor
	deconstructor
	free
	deconstructor
	说明三个对象都会让引用的个数+1，每析构一次引用数减1，当引用数为0的时候，释放内存
	*/
	test_ptr_2();
}