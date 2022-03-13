#include "ObjectNpc2D.h"
void AObjectNpc2D::HitOverlap(ABaseObject* pObj, DWORD dwState)
{
	if (dwState == ACollisionType::Overlap)	
	{	
	}
}

void AObjectNpc2D::HitSelect(ABaseObject* pObj, DWORD dwState)
{
	if (m_dwSelectState & M_HOVER)
	{
		INT K = 0;
	}
	if (m_dwSelectState & M_FOCUS)
	{
		INT K = 0;
	}
	if (m_dwSelectState & M_ACTIVE)
	{
		INT K = 0;
	}
	if (m_dwSelectState & M_SELECTED)
	{
		//INT K = 0;
		m_bSelect = true;
		m_bDead = true;
	}
}
bool AObjectNpc2D::Frame()
{
	AVector2 p;
	if (m_vPos.x > g_rtClient.right - 50.0f)
	{
		m_vDirection.x *= -1.0f;
		m_vPos.x = g_rtClient.right - 50.0f;
	}
	if (m_vPos.x < g_rtClient.left+ 50.0f)
	{
		m_vDirection.x *= -1.0f;
		m_vPos.x = g_rtClient.left + 50.0f;
	}
	if (m_vPos.y > g_rtClient.bottom - 50.0f)
	{
		m_vDirection.y *= -1.0f;
		m_vPos.y = g_rtClient.bottom - 50.0f;
	}
	if (m_vPos.y < g_rtClient.top + 50.0f)
	{
		m_vDirection.y *= -1.0f;
		m_vPos.y = g_rtClient.top + 50.0f;
	}
	p = m_vDirection * (m_fSpeed * g_fSecPerFrame);
	AddPosition(p);
	return true;
}
AObjectNpc2D::AObjectNpc2D()
{
	m_fSpeed = 20.0f + (rand() % 300); // ¼Ó·Â
	m_vDirection.x = (rand()%2 == 0) ? 0.8f : -0.8f;
	m_vDirection.y = (rand() % 2 == 0) ? 0.8f : -0.8f;
	m_dwCollisionType = ACollisionType::Overlap;
	m_dwSelectType = ASelectType::Select_Overlap;
}
AObjectNpc2D::~AObjectNpc2D(){}