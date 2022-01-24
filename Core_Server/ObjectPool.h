#pragma once
#include <string>
//#include "winnt.h" interlock�Լ�
#define		POOL_MAX_SIZE 2 //1024�� ����
#define		POOL_SIZE_MASK (POOL_MAX_SIZE-1)

template <class T>
class AObjectPool
{
	/* volatile = > �����Ϸ� ����ȭ ����, ������ ĳ�� ����
	static const int a = 0;
	if(a) {}
	-> �����Ϸ� ���忡�� ����ȭ �ؼ� �ؼ��Ѵ�. if(0) {} (a�� ���� �ʴ´�)
	a��� ������ �о �������°� �ƴ� ������ 0�� �־ �о������.
	�ַ� �ϵ���� ����Ҷ� ���� ����Ѵ�.
	*/
	static void* volatile m_Pool[POOL_MAX_SIZE];
	static long long volatile g_iHead; // ���� �� �Ҵ� �ε���
	static long long volatile g_iTail; // �Ҹ� �� ���� �ε���
	//�غ�Ǿ� ������ �غ�� ������Ʈ ��ȯ, �غ�� ������Ʈ ������ �űԷ� ���� �� ��ȯ

public:
	static void AllFree()
	{
		for (int i = 0; i<POOL_MAX_SIZE; i++)
		{
			void* data = InterlockedExchangePointer(&m_Pool[i], nullptr);
			if (data != nullptr)
			{
				_aligned_free(m_Pool[i]);
			}
		}
	}

public:
	/*thread���� run�ϴ� �κ�����, ������ �߻���.
	�޸� ���� -> ���� ���� -> �޸𸮿� '����' �� Ȯ�� -> //ĳ��//-> Ȯ��
	ĳ�������Ϳ� �޸� �ּҰ��� �ٸ��� ������ ���⼭ thread�� ���ư��� ū ������ �߻��Ѵ�. �׷��� ĳ������� ���ƾ� �Ѵ�.
	(ĳ�� : ���� �޸� �ּҿ� ���°� �ƴ� �ֱٿ� ��ȸ�� ���� �ּҿ� ���� ������ ���� �޸� �ּҰ� �ƴϴ�!!)
	volatile (ĳ������) �� ����Ѵ�.
	*/
	static void* operator new(size_t size) //new�� void*�� return
	{
		long long iCurrent = InterlockedIncrement64(&g_iHead)-1; //g_iHead++;
		//InterlockIncrement64 ���� ���� ����Ǹ� ����� ���� �������ش�.

		long long iPos = iCurrent & POOL_SIZE_MASK;
		void* pObj = InterlockedExchangePointer(&m_Pool[iPos], nullptr);
		//m_Pool[iPos] = nullptr;
		//InterlockedExchangePointer �� ������ �ִ� ���� �̰ɷ� ��ü. (�� ���� ���� ��ȯ �� null�� �ִ´�.)

		if (pObj != nullptr) return pObj;
		//������̴� return�� �� �迭�� null�� ��.
		return _aligned_malloc(size, MEMORY_ALLOCATION_ALIGNMENT);
	}
	static void operator delete(void* deleteObj)
	{
		int iCurrent = InterlockedIncrement64(&g_iTail) -1; //g_iTail++;
		int iPos = iCurrent & POOL_SIZE_MASK;
		void* pObj = InterlockedExchangePointer(&m_Pool[iPos], deleteObj);
		if (pObj != nullptr)
		{
			_aligned_free(pObj);
			//return pObj; 
			//null �� �ƴѰ� �� ��� �޸�(��� �� �� ����, ���� �迭 ����X ������ ����)}
		}
	}
};

//������ ��� ���� �߸� -> staticó�� �� �ۿ��� �ʱ�ȭ ó��
	template <typename T>
void* volatile		AObjectPool<T>::m_Pool[POOL_MAX_SIZE] = {};
	template <typename T>
long long volatile  AObjectPool<T>::g_iHead = 0; // ���� �� �Ҵ� �ε���
	template <typename T>
long long volatile  AObjectPool<T>::g_iTail = 0; // �Ҹ� �� ���� �ε���