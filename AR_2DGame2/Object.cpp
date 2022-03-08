#include "Object.h"
//Player
bool AObjectPlayer2D::Frame()
{
	if (AInput::Get().GetKey('W') == KEY_HOLD)
	{
		AVector2 pos;
		// �ð��� ����ȭ
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
	//Get Key ���� wasd ó��
	return 0;
}
void AObjectPlayer2D::HitOverlap(ABaseObject* pObj, DWORD dwState)
{
	if(dwState==ACollisionType::Overlap)
	{ 
		//Player�� �浹 �� ó���ϰų� Npc���� �浹ó��
	}
}
AObjectPlayer2D::AObjectPlayer2D()
{
	//������ ȣ�� �� Player�� �ӷ°� �浹Ÿ��(Overlap), ����Ÿ��(Overlap)�� �����Ѵ�.
	m_fSpeed = 300.0f;
	m_dwCollisionType = ACollisionType::Overlap;
	m_dwSelectType = ASelectType::Select_Overlap;
}
AObjectPlayer2D::~AObjectPlayer2D() {}


//NPC
bool AObjectNPC2D::Frame()
{
	//NPC frameȣ�� �� ó�� ��µ� ��ġ~�̵���ġ�� ������ �� �ִ�.
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
		//NPC�� �浹 �� ó���ϰų� Player���� �浹ó��
	}
}
void AObjectNPC2D::HitSelect(ABaseObject* pObj, DWORD dwState)
{
	//���콺 ���� �� ó��
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
	//NPC �ʱⰪ ����, �ӵ� �� ��ġ�� npc ���� �ٸ��� �����ϱ� ���� rand�� ����Ѵ�.
	m_fSpeed = 20.0f * (rand() % 300); //�⺻ �ӷ� * ������
	m_vDirection.x = (rand() % 2 == 0) ? 1.0f: - 1.0f;
	m_vDirection.y = (rand() % 2 == 0) ? 1.0f: - 1.0f;
	m_dwCollisionType = ACollisionType::Overlap;
	m_dwSelectType = ASelectType::Select_Overlap;
}
AObjectNPC2D::~AObjectNPC2D() {}