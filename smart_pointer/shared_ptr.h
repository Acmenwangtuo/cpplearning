#ifndef WT_SharedPtr_H
#define WT_SharedPtr_H


#include <iostream>
#include <memory>
#include <cstring>
using namespace std;

template <typename T> // 模板类
class SharedPtr {
	private:
		T *m_p;
		int *m_refCount; // 计数
		void decr() {
			--*m_refCount;
			if (*m_refCount == 0) {
				cout << "free" << endl;
				delete m_p;
				delete m_refCount;
				m_p = NULL;
				m_refCount = NULL;
			}
		}
	public:
		//指针构造
		SharedPtr(T *p = NULL) { //这个指针一定是刚刚分配的堆内存的值
			m_refCount = new int(1);
			m_p = p;
		}
		// 复制构造
		SharedPtr(const SharedPtr &sp) {
			m_p = sp.m_p;
			m_refCount = sp.m_refCount;
			++*m_refCount;
		}
		SharedPtr &operator=(SharedPtr &p) { //指向新的其他对象
			if (this == &p)
				return *this;
			decr(); // 释放原来的资源
			m_p = p.m_p;
			m_refCount = p.m_refCount;
			++*p.m_refCount;
			return *this;
		}
		//获取指针
		T *operator->() {
			if (m_p)
				return m_p;
			throw runtime_error("null pointer1");
		}
		//取地址
		T &operator*() {
			if (m_p)
				return *m_p;
			throw runtime_error("null pointer2");
		}
		~SharedPtr() {
			decr();
			cout << "deconstructor" << endl;
		}
		int getRefCount() {
			return *m_refCount;
		}
};

#endif //WT_SharedPtr_H