#include "Sample.h"


bool ASample::SetVertexData()
{
    ConvertIndex(m_vPos, m_fWidth, m_fHeight, m_VertexList);
    return true;
}
bool ASample::SetIndexData()
{
    m_IndexList.clear();

    m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
    m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
    return true;
}
bool ASample::Frame()
{
    if (m_bFadeIn)	FadeIn();
    if (m_bFadeOut)	FadeOut();
    m_ConstantList.Color = m_vColor;
    m_ConstantList.Timer = AVector4(g_fGameTimer, 0, 0, 1.0f);
    m_pContext->UpdateSubresource(
        m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);
    return true;
}

bool ASample::Init()
{
    I_Sound.Init();

    m_IntroWorld.Init();
    m_IntroWorld.m_pd3dDevice = m_pd3dDevice;
    m_IntroWorld.m_pContext = m_pImmediateContext;
    m_IntroWorld.Load(L"intro.txt");
    m_IntroWorld.m_pNextWorld = &m_ZoneWorld;
    m_ZoneWorld.m_pd3dDevice = m_pd3dDevice;
    m_ZoneWorld.m_pContext = m_pImmediateContext;
    //m_ZoneWorld.Load(L"zone.txt");

    AWorld::m_pCurWorld = &m_IntroWorld;

    m_Net.InitNetwork();
    m_Net.Connect(g_hWnd, SOCK_STREAM, PORT_NUM, ADRESS_NUM);// "127.0.0.1"); //IP
    return true;
}
bool ASample::Frame()
{

    AWorld::m_pCurWorld->Frame();

   
    return true;
}
bool ASample::Render()
{
    AWorld::m_pCurWorld->Render();

    wstring msg = L"FPS: ";
    msg += to_wstring(m_GameTimer.m_iFPS);
    msg += L"   GT: ";
    msg += to_wstring(m_GameTimer.m_fTimer);
    m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(1, 1, 1, 1));

    return true;
}
bool ASample::Release()
{
    //각 클래스별로 Release재정의한것 불러오기
    I_Sound.Release();
    m_IntroWorld.Release();
    m_ZoneWorld.Release();
    m_Net.CloseNetWork();
    return true;
}


APlaneObj::APlaneObj()
{
    
}