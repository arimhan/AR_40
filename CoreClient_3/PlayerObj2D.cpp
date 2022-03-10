#include "PlayerObj2D.h"
#include "Input.h"
void APlayerObj2D::HitOverlap(ABaseObject* pObj, DWORD dwState)
{
	if (dwState == ACollisionType::Overlap)	{	}	
}
bool APlayerObj2D::Frame()
{	
	if (AInput::Get().GetKey('W') == KEY_HOLD)
	{
		AVector2 pos;
		// 시간의 동기화
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
	m_fSpeed = 300.0f; // 속력
	m_dwCollisionType = ACollisionType::Overlap;
	m_dwSelectType = ASelectType::Select_Overlap;
}

APlayerObj2D::~APlayerObj2D(){	}