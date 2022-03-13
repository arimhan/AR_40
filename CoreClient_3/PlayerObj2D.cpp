#include "PlayerObj2D.h"
#include "Input.h"

void APlayerObj2D::HitOverlap(ABaseObject* pObj, DWORD dwState)
{
	if (dwState == ACollisionType::Overlap)	
	{	
		//pObj->m_bAlphaBlend = !pObj->m_bAlphaBlend;
		////pObj->m_bAlphaBlend = true;
		//m_bSelect = true;
		//m_bDead = true;
	}	
}
bool APlayerObj2D::Frame()
{	
	if (AInput::Get().GetKey('W') == KEY_HOLD)
	{
		// �ð��� ����ȭ
		AVector2 pos;

		pos.y -= m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);

	}
	if (AInput::Get().GetKey('A') == KEY_HOLD)
	{
		AVector2 pos;
		pos.x -= m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (AInput::Get().GetKey('S') == KEY_HOLD)
	{
		AVector2 pos;
		pos.y += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (AInput::Get().GetKey('D') == KEY_HOLD)
	{
		AVector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}	
	return true;
}

APlayerObj2D::APlayerObj2D()
{
	m_fSpeed = 200.0f;//300.0f; // �ӷ�
	m_dwCollisionType = ACollisionType::Overlap;
	m_dwSelectType = ASelectType::Select_Overlap;
}

APlayerObj2D::~APlayerObj2D(){	}