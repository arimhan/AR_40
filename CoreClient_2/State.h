#pragma once
#include "Object2D.h"

class AState;

enum A_EnemyState
{
	//���°�
	STATE_STOP = 0,		//����
	STATE_MOVE,			//�̵�
	STATE_ATTACK,		//����
	//ȸ�� (����)
	//�Ҹ� (���)
};

enum A_EnemyEvent
{
	//���� ���� �� �߻� EVENT
	STATE_STOP_TIMER = 0,		//STOP �� ���ð�
	STATE_MOVE_TIMER,			//MOVE�� ���ð�
	STATE_FIND_TARGET,			//Ÿ�� ����
	STATE_LOST_TARGET,			//Ÿ�� ����
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
	virtual void Process(AObject2D* pPlayer) = 0; //���������Լ�. �ٸ������� ������
	AState(AObjectAI* owner) : m_pOwner(owner) {};
};

