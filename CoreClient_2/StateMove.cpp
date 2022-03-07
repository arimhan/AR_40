#include "StateMove.h"

void AStateMove::Process(AObject2D* pPlayer)
{
	//거리 가까우면 타겟 선택
	m_pOwner->m_fStopTimer += g_fSecPerFrame;
	AVector2 vPC = pPlayer->m_vPos;
	AVector2 vNPC = m_pOwner->m_vPos;
	float fDistance = (vPC - vNPC).Length();

	//거리 안에 있을 경우 타겟 찾음
	if (fDistance < 200.0f)
	{
		m_pOwner->SetTransition(STATE_FIND_TARGET);
		m_pOwner->m_fMoveTimer = 0;
		return;
	}

	//2초 뒤 정지
	if (m_pOwner->m_fMoveTimer > 2.0f)
	{
		m_pOwner->SetTransition(STATE_STOP_TIMER);
		m_pOwner->m_fMoveTimer = 0;
		return;
	}
	m_pOwner->AddPosition(AVector2(30 * g_fSecPerFrame, 30 * g_fSecPerFrame));
}
