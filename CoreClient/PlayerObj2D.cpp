#include "PlayerObj2D.h"
#include "Input.h"

bool APlayerObj2D::Frame()
{
    if (AInput::Get().GetKey('W') == KEY_HOLD) //��
    {
        AVector2 pos;
        pos.y -= m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    if (AInput::Get().GetKey('A') == KEY_HOLD) //��
    {
        AVector2 pos;
        pos.x -= m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    if (AInput::Get().GetKey('S') == KEY_HOLD) //��
    {
        AVector2 pos;
        pos.y += m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    if (AInput::Get().GetKey('D') == KEY_HOLD) //��
    {
        AVector2 pos;
        pos.x += m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    return true;
}
void APlayerObj2D::HitOverlap(ABaseObject* pObj, DWORD dwState)
{
    if (dwState == ACollisionType::Overlap)
    {
        pObj->m_bAlphaBlend = false;
    }
}
APlayerObj2D::APlayerObj2D()
{
    m_fSpeed = 300.0f;  //�ӷ�
}
APlayerObj2D::~APlayerObj2D(){}
