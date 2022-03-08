#include "Object.h"
//Player
bool AObjectPlayer2D::Frame()
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
	//Get Key 조작 wasd 처리
	return 0;
}
void AObjectPlayer2D::HitOverlap(ABaseObject* pObj, DWORD dwState)
{
	if(dwState==ACollisionType::Overlap)
	{ 
		//Player와 충돌 시 처리하거나 Npc에서 충돌처리
	}
}
AObjectPlayer2D::AObjectPlayer2D()
{
	//생성자 호출 시 Player의 속력과 충돌타입(Overlap), 선택타입(Overlap)을 세팅한다.
	m_fSpeed = 300.0f;
	m_dwCollisionType = ACollisionType::Overlap;
	m_dwSelectType = ASelectType::Select_Overlap;
}
AObjectPlayer2D::~AObjectPlayer2D() {}


//NPC
bool AObjectNPC2D::Frame()
{
	//NPC frame호출 시 처음 출력될 위치~이동위치를 세팅할 수 있다.
	AVector2 p;
	if (m_vPos.x > g_rtClient.right - 50.0f)
	{
		m_vDirection.x *= -1.0f;
		m_vPos.x = g_rtClient.right - 50.0f;
	}
	if (m_vPos.x < g_rtClient.left + 50.0f)
	{
		m_vDirection.x *= -1.0f;
		m_vPos.x = g_rtClient.left + 50.0f;
	}
	if (m_vPos.y > g_rtClient.bottom - 50.0f)
	{
		m_vDirection.y *= -1.0f;
		m_vPos.y = g_rtClient.bottom - 50.0f;
	}
	if (m_vPos.y > g_rtClient.top - 50.0f)
	{
		m_vDirection.y *= -1.0f;
		m_vPos.y = g_rtClient.top - 50.0f;
	}
	p = m_vDirection * (m_fSpeed * g_fSecPerFrame);
	AddPosition(p);
	return true;
}

void AObjectNPC2D::HitOverlap(ABaseObject* pObj, DWORD dwState)
{
	if (dwState == ACollisionType::Overlap)
	{
		//NPC와 충돌 시 처리하거나 Player에서 충돌처리
	}
}
void AObjectNPC2D::HitSelect(ABaseObject* pObj, DWORD dwState)
{
	//마우스 선택 시 처리
	if (m_dwSelectState & M_HOVER)
	{
		INT A = 0;
	}
	if (m_dwSelectState & M_FOCUS)
	{
		INT A = 0;
	}
	if (m_dwSelectState & M_ACTIVE)
	{
		INT A = 0;
	}
	if (m_dwSelectState & M_SELECTED)
	{
		m_bSelect = true;
		m_bDead = true;
	}
}

AObjectNPC2D::AObjectNPC2D()
{
	//NPC 초기값 세팅, 속도 및 위치를 npc 별로 다르게 설정하기 위해 rand를 사용한다.
	m_fSpeed = 20.0f * (rand() % 300); //기본 속력 * 랜덤값
	m_vDirection.x = (rand() % 2 == 0) ? 1.0f: - 1.0f;
	m_vDirection.y = (rand() % 2 == 0) ? 1.0f: - 1.0f;
	m_dwCollisionType = ACollisionType::Overlap;
	m_dwSelectType = ASelectType::Select_Overlap;
}
AObjectNPC2D::~AObjectNPC2D() {}