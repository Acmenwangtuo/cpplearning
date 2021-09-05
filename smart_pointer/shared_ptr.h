#ifndef WT_SharedPtr_H
#define WT_SharedPtr_H


#include <iostream>
#include <memory>
#include <cstring>
using namespace std;

template <typename T> // ģ����
class SharedPtr {
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
};

#endif //WT_SharedPtr_H