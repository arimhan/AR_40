#include "Core.h"

bool ACore::CoreInit()
{
    //InitDevice();
    Init();
    return true;
}
bool ACore::GameRun()
{
    CoreInit();
    while(WinRun())
    {
        CoreFrame();
        //CoreRender();
    }
    CoreRelease();
    return true;
}
bool ACore::CoreFrame()
{
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
    m_pSwapChain->Present(0, 0);
    return true;
}
bool ACore::CoreRelease()
{
    Release();
    CleanUpDevice();
    return true;
}

ACore::ACore() {}
ACore::~ACore() {}