#pragma once
#include "Object2D.h"

class AState;

enum A_EnemyState
{
	//상태값
	STATE_STOP = 0,		//정지
	STATE_MOVE,			//이동
	STATE_ATTACK,		//공격
	//회피 (도망)
	//소멸 (사망)
};

enum A_EnemyEvent
{
	//상태 변경 전 발생 EVENT
	STATE_STOP_TIMER = 0,		//STOP 전 대기시간
	STATE_MOVE_TIMER,			//MOVE전 대기시간
	STATE_FIND_TARGET,			//타겟 추적
	STATE_LOST_TARGET,			//타겟 해제
	//STATE_RUN_TARGET			
	//STATE_DEAD_DEMAGE
};

class AObjectAI : public AObject2D
{
public:
	AState* m_pStateArray[3];
	AState* m_pStateAction = nullptr;
	DWORD m_dwStateAction;
	float m_fMoveTimer = 0.0f;
	float m_fStopTimer = 0.0f;
public:
	virtual void SetTransition(DWORD dwEvent) = 0;
};

class AState
{
public:
	AObjectAI*	m_pOwner;
	DWORD		m_dwStateAI;
public:
	virtual void Process(AObject2D* pPlayer) = 0; //순수가상함수. 다른곳에서 재정의
	AState(AObjectAI* owner) : m_pOwner(owner) {};
};

