#pragma once
#include <string>
//#include "winnt.h" interlock함수
#define		POOL_MAX_SIZE 2 //1024로 변경
#define		POOL_SIZE_MASK (POOL_MAX_SIZE-1)

template <class T>
class AObjectPool
{
	/* volatile = > 컴파일러 최적화 방지, 변수의 캐쉬 방지
	static const int a = 0;
	if(a) {}
	-> 컴파일러 입장에서 최적화 해서 해석한다. if(0) {} (a를 읽지 않는다)
	a라는 변수를 읽어서 가져오는게 아닌 강제로 0을 넣어서 읽어버린다.
	주로 하드웨어 통신할때 많이 사용한다.
	*/
	static void* volatile m_Pool[POOL_MAX_SIZE];
	static long long volatile g_iHead; // 생성 및 할당 인덱스
	static long long volatile g_iTail; // 소멸 및 해제 인덱스
	//준비되어 있으면 준비된 오브젝트 반환, 준비된 오브젝트 없으면 신규로 생성 후 반환

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
	/*thread에서 run하는 부분으로, 문제가 발생함.
	메모리 변수 -> 값을 갱신 -> 메모리에 '가서' 값 확인 -> //캐쉬//-> 확인
	캐쉬데이터와 메모리 주소값은 다르기 때문에 여기서 thread가 돌아가면 큰 문제가 발생한다. 그래서 캐쉬사용을 막아야 한다.
	(캐쉬 : 실제 메모리 주소에 들어가는게 아닌 최근에 조회한 값의 주소에 가기 때문에 실제 메모리 주소가 아니다!!)
	volatile (캐쉬방지) 을 사용한다.
	*/
	static void* operator new(size_t size) //new시 void*를 return
	{
		long long iCurrent = InterlockedIncrement64(&g_iHead)-1; //g_iHead++;
		//InterlockIncrement64 기존 값이 변경되면 변경된 값을 리턴해준다.

		long long iPos = iCurrent & POOL_SIZE_MASK;
		void* pObj = InterlockedExchangePointer(&m_Pool[iPos], nullptr);
		//m_Pool[iPos] = nullptr;
		//InterlockedExchangePointer 이 변수에 있는 값을 이걸로 대체. (이 전의 값을 반환 후 null로 넣는다.)

		if (pObj != nullptr) return pObj;
		//사용중이니 return후 그 배열은 null이 들어감.
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
			//null 이 아닌건 미 사용 메모리(사용 후 재 저장, 사용시 배열 저장X 무조건 리턴)}
		}
	}
};

//비정적 멤버 참조 잘못 -> static처리 후 밖에서 초기화 처리
	template <typename T>
void* volatile		AObjectPool<T>::m_Pool[POOL_MAX_SIZE] = {};
	template <typename T>
long long volatile  AObjectPool<T>::g_iHead = 0; // 생성 및 할당 인덱스
	template <typename T>
long long volatile  AObjectPool<T>::g_iTail = 0; // 소멸 및 해제 인덱스