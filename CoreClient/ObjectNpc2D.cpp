#include "ObjectNpc2D.h"

bool AObjectNpc2D::Frame()
{
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
    if (m_vPos.y < g_rtClient.top + 50.0f)
    {
        m_vDirection.y *= -1.0f;
        m_vPos.y = g_rtClient.top + 50.0f;
    }
    p = m_vDirection * (m_fSpeed * g_fSecPerFrame);
    AddPosition(p);
    return true;
}
void AObjectNpc2D::HitOverlap(ABaseObject* pObj, DWORD dwState)
{
    if (dwState == ACollisionType::Overlap)
    {
        //pObj->m_bAlphaBlend = !pObj->m_bAlphaBlend;
    }
}
void AObjectNpc2D::HitSelect(ABaseObject* pObj, DWORD dwState)
{
    if (m_dwSelectState & ASelectState::M_HOVER)    { INT C = 0; }
    if (m_dwSelectState & ASelectState::M_FOCUS)    { INT C = 0; }
    if (m_dwSelectState & ASelectState::M_ACTIVE)   { INT C = 0; }
    if (m_dwSelectState & ASelectState::M_SELECTED) { m_bSelect = true; m_bDead = true; }
}
AObjectNpc2D::AObjectNpc2D()
{
    m_fSpeed = 20.0f + (rand() % 300); //¼Ó·Â
    m_vDirection.x = (rand() % 2 == 0) ? 1.0f : -1.0f;
    m_vDirection.y = (rand() % 2 == 0) ? 1.0f : -1.0f;
}
AObjectNpc2D::~AObjectNpc2D(){}
