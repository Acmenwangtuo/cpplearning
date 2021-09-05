#ifndef WT_SmartPtr_H
#define WT_SmartPtr_H


#include <iostream>
#include <memory>
#include <cstring>
using namespace std;
template<class T> class WeakPtr;
template <class T> // ģ����
class SharedPtr {
		friend class WeakPtr<T>;
	public:
		//ָ�빹��
		SharedPtr(T *p = NULL) { //���ָ��һ���Ǹոշ���Ķ��ڴ��ֵ
			m_refCount = new int(1);
			m_p = p;
		}
		// ���ƹ���
		SharedPtr(const SharedPtr &sp) {
			m_p = sp.m_p;
			m_refCount = sp.m_refCount;
			++*m_refCount;
		}
		SharedPtr &operator=(SharedPtr &p) { //ָ���µ���������
			if (this == &p)
				return *this;
			decr(); // �ͷ�ԭ������Դ
			m_p = p.m_p;
			m_refCount = p.m_refCount;
			++*p.m_refCount;
			return *this;
		}
		//��ȡָ��
		T *operator->() {
			if (m_p)
				return m_p;
			throw runtime_error("null pointer1");
		}
		//ȡ��ַ
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
		int *m_refCount; // ����
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
//�ٷ�װһ��
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
		UniquePtr(T *p = nullptr): m_p(p) {}; // �б���ʽ
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
		T *operator->() const { // ��ͷ����
			cout << "-> reload" << endl;
			return m_p;
		};
		T &operator*() const { //ָ��������������
			return *m_p;
		}
		T *release() { // �ͷ�ָ�벢����ԭ����ָ��
			T *ret = m_p;
			m_p = nullptr;
			return ret;
		}
		void reset(T *p = nullptr) { // �ͷ���ǰ��ָ�룬��һ���µ�
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