#include "Timer.h"
//float g_fSecPerFrame = 0.0f;
//float g_fGameTimer = 0.0f;

bool ATimer::Init()
{
    m_fSecondPerFrame = 0.0f;
    m_fTimer = 0.0f;
    m_dwBeforeTime = timeGetTime();
    return true;//false;
}
bool ATimer::Frame()
{
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
    m_fSecondPerFrame = dwElapseTime / 1000.0f;
    m_fTimer += m_fSecondPerFrame;

    m_fSecPerFrame = m_fSecondPerFrame;
    m_fGameTimer = m_fTimer;

    m_dwBeforeTime = dwCurrentTime;
    return true;//false;
}
bool ATimer::Render()
{
    return true;//false;
}
bool ATimer::Release()
{
    return true;//false;
}
