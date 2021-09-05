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

//�������ִ�й������׳����쳣��unique_ptr�ͻ��ͷ�����ָ��Ķ���
//��ͳ��new����
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
	// ��������һ������Ƥ��ʵ�飬����� unique_ptrָ���Ԫ��ȡ������Ȼ���ȡ����ָ�룬Ȼ��������һ��unique_ptr�ӹܣ���ô�ͳ�������
//    p1.reset( &(*p2)); // ������pointer being freed was not allocated
//    UniquePrt<Test> p3 (new Test("xxx"));

}

int main() {
	//test_ptr();
	/*
	��ӡ���Ϊ��
	abcd
	defg
	@1: 2
	free
	@2: 3
	deconstructor
	deconstructor
	free
	deconstructor
	˵���������󶼻������õĸ���+1��ÿ����һ����������1����������Ϊ0��ʱ���ͷ��ڴ�
	*/
	test_ptr_2();
}