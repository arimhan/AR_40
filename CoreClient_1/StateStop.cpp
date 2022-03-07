#include "StateStop.h"

void AStateStop::Process(AObject2D* pPlayer)
{
	//2초 뒤 정지하도록 설정
	m_pOwner->m_fMoveTimer += g_fSecPerFrame;
	if (m_pOwner->m_fMoveTimer > 2.0f)
	{
		m_pOwner->SetTransition(STATE_STOP_TIMER);
		m_pOwner->m_fMoveTimer = 0;
		return;
	}

//타겟선택 프로세스
	//유저와 npc의 거리 계산 -> 반지름
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
