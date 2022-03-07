#pragma once
#include "State.h"
class AFsmState
{
public:
	DWORD				m_dwState;		//상태
	map<DWORD, DWORD>	m_mapEvent;		//상태 변환 시 작동할 이벤트
	AFsmState(DWORD state) : m_dwState(state) {}	//생성자를 활용해 상태값 처리
};

class AFsm : public ASingleton<AFsm>
{
	friend class ASingleton<AFsm>;
public:
	map<DWORD, AFsmState*> m_mapStateClass;		//상태 클래스화
	void AddTransition(DWORD dwState, DWORD dwEvent, DWORD dwOutput);	
	//상태 변경 함수화 (현재상태 - 발동조건(이벤트) - 변경할 상태)
	DWORD GetTransition(DWORD dwState, DWORD dwOutput);
	//상태를 받아 output상태로 변경
};
#define I_Fsm AFsm::Get()