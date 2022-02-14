#include "PlayerObj2D.h"
#include "Input.h"

bool APlayerObj2D::Frame()
{
    if (AInput::Get().GetKey('W') == KEY_HOLD)
    {
        AVector2 pos;
        pos.y -= m_fSpeed * g_fSecPerFrame;
        AddPosition(pos);
    }
    return false;
}

APlayerObj2D::APlayerObj2D()
{
}

APlayerObj2D::~APlayerObj2D()
{
}
