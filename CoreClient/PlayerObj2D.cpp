#include "PlayerObj2D.h"
#include "Input.h"

//CoreLib - timer 내 연결이 되어야 하는데 안돼서 임시 처리.
//float g_fSecPerFrame = 0.0f;

bool APlayerObj2D::Frame()
{
    if (AInput::Get().GetKey('W') == KEY_HOLD) //상
    {
        AVector2 pos;
        pos.y -= m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    if (AInput::Get().GetKey('A') == KEY_HOLD) //좌
    {
        AVector2 pos;
        pos.x -= m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    if (AInput::Get().GetKey('S') == KEY_HOLD) //하
    {
        AVector2 pos;
        pos.y += m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    if (AInput::Get().GetKey('D') == KEY_HOLD) //우
    {
        AVector2 pos;
        pos.x += m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    return false;
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
    m_fSpeed = 300.0f;  //속력
}
APlayerObj2D::~APlayerObj2D(){}
