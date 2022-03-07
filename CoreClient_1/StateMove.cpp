#include "StateMove.h"

void AStateMove::Process(AObject2D* pPlayer)
{
	//�Ÿ� ������ Ÿ�� ����
	m_pOwner->m_fStopTimer += g_fSecPerFrame;
	AVector2 vPC = pPlayer->m_vPos;
	AVector2 vNPC = m_pOwner->m_vPos;
	float fDistance = (vPC - vNPC).Length();

	//�Ÿ� �ȿ� ���� ��� Ÿ�� ã��
	if (fDistance < 200.0f)
	{
		m_pOwner->SetTransition(STATE_FIND_TARGET);
		m_pOwner->m_fMoveTimer = 0;
		return;
	}

	//2�� �� ����
	if (m_pOwner->m_fMoveTimer > 2.0f)
	{
		m_pOwner->SetTransition(STATE_STOP_TIMER);
		m_pOwner->m_fMoveTimer = 0;
		return;
	}
	m_pOwner->AddPosition(AVector2(30 * g_fSecPerFrame, 30 * g_fSecPerFrame));
}
