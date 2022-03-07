#pragma once
#include "State.h"
class AFsmState
{
public:
	DWORD				m_dwState;		//����
	map<DWORD, DWORD>	m_mapEvent;		//���� ��ȯ �� �۵��� �̺�Ʈ
	AFsmState(DWORD state) : m_dwState(state) {}	//�����ڸ� Ȱ���� ���°� ó��
};

class AFsm : public ASingleton<AFsm>
{
	friend class ASingleton<AFsm>;
public:
	map<DWORD, AFsmState*> m_mapStateClass;		//���� Ŭ����ȭ
	void AddTransition(DWORD dwState, DWORD dwEvent, DWORD dwOutput);	
	//���� ���� �Լ�ȭ (������� - �ߵ�����(�̺�Ʈ) - ������ ����)
	DWORD GetTransition(DWORD dwState, DWORD dwOutput);
	//���¸� �޾� output���·� ����
};
#define I_Fsm AFsm::Get()