#include "StateAttack.h"

void AStateAttack::Process(AObject2D* pPlayer)
{
	//�Ÿ� ����� ������ �� �ֵ���
	AVector2 vPC = pPlayer->m_vPos;
	AVector2 vNPC = m_pOwner->m_vPos;
	float fDistance = (vPC - vNPC).Length();
	if (fDistance > 300.0f)
	{
		//�Ÿ��� ����� Ÿ�� ����
		m_pOwner->SetTransition(STATE_LOST_TARGET);
		return;
	}
	AVector2 vAdd = (vPC - vNPC).Normal() * g_fSecPerFrame * 300.0f;
	m_pOwner->AddPosition(vAdd);
}
