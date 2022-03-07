#include "StateAttack.h"

void AStateAttack::Process(AObject2D* pPlayer)
{
	//거리 계산후 추적할 수 있도록
	AVector2 vPC = pPlayer->m_vPos;
	AVector2 vNPC = m_pOwner->m_vPos;
	float fDistance = (vPC - vNPC).Length();
	if (fDistance > 300.0f)
	{
		//거리를 벗어나면 타겟 해제
		m_pOwner->SetTransition(STATE_LOST_TARGET);
		return;
	}
	AVector2 vAdd = (vPC - vNPC).Normal() * g_fSecPerFrame * 300.0f;
	m_pOwner->AddPosition(vAdd);
}
