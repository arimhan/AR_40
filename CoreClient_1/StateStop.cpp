#include "StateStop.h"

void AStateStop::Process(AObject2D* pPlayer)
{
	//2�� �� �����ϵ��� ����
	m_pOwner->m_fMoveTimer += g_fSecPerFrame;
	if (m_pOwner->m_fMoveTimer > 2.0f)
	{
		m_pOwner->SetTransition(STATE_STOP_TIMER);
		m_pOwner->m_fMoveTimer = 0;
		return;
	}

//Ÿ�ټ��� ���μ���
	//������ npc�� �Ÿ� ��� -> ������
	AVector2 vPC = pPlayer->m_vPos;
	AVector2 vNPC = m_pOwner->m_vPos;
	float fDistance = (vPC - vNPC).Length();
	if (fDistance < 200.0f)
	{
		m_pOwner->SetTransition(STATE_FIND_TARGET);
		m_pOwner->m_fMoveTimer = 0;
		return;
	}
}
