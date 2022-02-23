#include "UIObject.h"

bool AUIObject::Frame()
{
    ADxObject::Frame();
    return true;
}
bool AUIObject::Render()
{
    ADxObject::Render();
    return true;
}
bool AImageIObject::Init()
{
    m_bFadeIn = true;
    return true;
}
bool AImageIObject::Frame()
{
    ADxObject::Frame();
    if (m_bFadeIn) FadeIn();
    if (m_bFadeOut) FadeOut();
    m_ConstantList.Color = AVector4(m_fAlpha, m_fAlpha, m_fAlpha, 1.0f);
    m_ConstantList.Timer = AVector4(g_fGameTimer, 0, 0, 1.0f);
    m_pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);
    return true;
}
bool AImageIObject::Render()
{
    ADxObject::Render();
    return true;
}

void AImageIObject::FadeIn()
{
    m_fAlpha += g_fSecPerFrame * 0.5f;
    m_fAlpha = min(m_fAlpha, 1.0f);
    if (m_fAlpha >= 1.0f) { m_bFadeIn = false; }
}

void AImageIObject::FadeOut()
{
    m_fAlpha = m_fAlpha- g_fSecPerFrame * 0.5f;
    m_fAlpha = max(m_fAlpha, 1.0f);
    if (m_fAlpha <= 1.0f) { m_bFadeOut = false; }
}

bool AButtonObject::Frame()
{
    ADxObject::Frame();
    return true;
}

bool AButtonObject::Render()
{
    ADxObject::Render();
    return true;
}
