#include "Timer.h"

float   g_fSecPerFrame = 0.0f;
float   g_fGameTimer = 0.0f;

bool ATimer::Init()
{
    m_fSecondPerFrame = 0.0f;
    m_fTimer = 0.0f;
    m_dwBeforeTime = timeGetTime();
    return false;
}

bool ATimer::Frame()
{
    //FPS : timeGetTime 함수로 현재 시간을 구함.
    DWORD dwCurrentTime = timeGetTime();

    //dwElapseTime (실행 시간)은 = 현재 시간 - 이전 시간
    DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
    m_fSecondPerFrame = min(0.1f, dwElapseTime / 1000.0f);
    
    m_fTimer += m_fSecondPerFrame;

    g_fSecPerFrame  = m_fSecondPerFrame;
    g_fGameTimer    = m_fTimer;

    m_fFPSTimer += m_fSecondPerFrame;

    //m_fFPSTimer 값이 지나지 않았을 경우, 카운터와 m_fFPSTimer를 초기화 한다.
    //여기서 float인 최소단위 1.0을 기준으로 한다. 즉, 1초당 1초가 증가하도록 한다.
    if (m_fFPSTimer >= 1.0f)
    {
        m_iFPS = m_iFPSCounter;
        m_iFPSCounter = 0;
        m_fFPSTimer -= 1.0f;
    }
    //시간이 지났다면 증가시킨다.
    m_iFPSCounter++;
    //그리고 이전 시간을 현재 시간으로 변경하면 다시 이 소스가 돌아갈 때 실행시간이 누적된다.
    m_dwBeforeTime = dwCurrentTime;
    return false;
}

bool ATimer::Render() { return false; }
bool ATimer::Release() { return false; }
