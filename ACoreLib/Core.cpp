#include "Core.h"
#include "ObjectMgr.h" //I_ObjectMgr 

bool ACore::CoreInit()
{
    m_GameTimer.Init();
    AInput::Get().Init();
    InitDevice();
    Init();
    return true;
}
bool ACore::GameRun()
{
    CoreInit();
    while(WinRun())
    {
        CoreFrame();
        CoreRender();
    }
    CoreRelease();
    return true;
}
bool ACore::CoreFrame()
{
    m_GameTimer.Frame();
    AInput::Get().Frame();
    I_ObjectMgr.Frame();
    Frame();
    return true;
}
bool ACore::CoreRender()
{
    //float color[4] = { 102.0f, 204.0f, 255.0f, 1.0f }; // 102 204 255
    //float color[4] = { 0.5f, 0.5f, 1.0f, 1.0f }; // RGB 컬러명 적용 안됨
    float color[4] = { 1.0f, 1.0f, 0.8f, 1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
    Render();
    m_GameTimer.Render();
    AInput::Get().Render();
    m_pSwapChain->Present(0, 0);
    return true;
}
bool ACore::CoreRelease()
{
    Release();
    m_GameTimer.Release();
    AInput::Get().Release();
    CleanUpDevice();
    return true;
}
ACore::ACore() {}
ACore::~ACore() {}