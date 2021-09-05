#ifndef WT_SmartPtr_H
#define WT_SmartPtr_H


#include <iostream>
#include <memory>
#include <cstring>
using namespace std;
template<class T> class WeakPtr;
template <class T> // 模板类
class SharedPtr {
		friend class WeakPtr<T>;
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
//		friend class WeakPtr<T>;
};
//再封装一层
template<class T>

class WeakPtr {
	public:
		WeakPtr(const SharedPtr<T> &s): ptr(s.m_p) {};
		T &operator*() {
			return *ptr;
		}
		T *operator->() {
			return ptr;
		}
	private:
		T *ptr;
};

template <class T>
class UniquePtr {
	private:
		T *m_p;
	public:
		UniquePtr(T *p = nullptr): m_p(p) {}; // 列表表达式
		UniquePtr(const UniquePtr &sp) = delete;
		UniquePtr &operator=(UniquePtr &p) = delete;

		UniquePtr(const UniquePtr &&other): m_p(other.m_p) {
			other.m_p = nullptr;
		};
		UniquePtr<T> &operator=(UniquePtr<T> &&other) {
			cout << "move assign" << endl;
			swap(other);
			return *this;
		};

		~UniquePtr() {
			if (m_p)
				delete m_p;
			cout << "deconstructor" << endl;
		}
		T *operator->() const { // 箭头重载
			cout << "-> reload" << endl;
			return m_p;
		};
		T &operator*() const { //指针解析运算符重载
			return *m_p;
		}
		T *release() { // 释放指针并返回原来的指针
			T *ret = m_p;
			m_p = nullptr;
			return ret;
		}
		void reset(T *p = nullptr) { // 释放以前的指针，换一个新的
			T *old = m_p;
			if (p != m_p) {
				if (m_p)
					delete m_p;
			}
			m_p = p;
		}
		void swap(UniquePtr &p) {
			using std::swap;
			swap(m_p, p.m_p);
		}
		explicit operator bool() const noexcept {
			return m_p != nullptr;
		}
};
#endif //WT_SmartPtr_H