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
    //FPS : timeGetTime �Լ��� ���� �ð��� ����.
    DWORD dwCurrentTime = timeGetTime();

    //dwElapseTime (���� �ð�)�� = ���� �ð� - ���� �ð�
    DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
    m_fSecondPerFrame = min(0.1f, dwElapseTime / 1000.0f);
    
    m_fTimer += m_fSecondPerFrame;

    g_fSecPerFrame  = m_fSecondPerFrame;
    g_fGameTimer    = m_fTimer;

    m_fFPSTimer += m_fSecondPerFrame;

    //m_fFPSTimer ���� ������ �ʾ��� ���, ī���Ϳ� m_fFPSTimer�� �ʱ�ȭ �Ѵ�.
    //���⼭ float�� �ּҴ��� 1.0�� �������� �Ѵ�. ��, 1�ʴ� 1�ʰ� �����ϵ��� �Ѵ�.
    if (m_fFPSTimer >= 1.0f)
    {
        m_iFPS = m_iFPSCounter;
        m_iFPSCounter = 0;
        m_fFPSTimer -= 1.0f;
    }
    //�ð��� �����ٸ� ������Ų��.
    m_iFPSCounter++;
    //�׸��� ���� �ð��� ���� �ð����� �����ϸ� �ٽ� �� �ҽ��� ���ư� �� ����ð��� �����ȴ�.
    m_dwBeforeTime = dwCurrentTime;
    return false;
}

bool ATimer::Render() { return false; }
bool ATimer::Release() { return false; }
