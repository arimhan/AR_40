#include "Core.h"

bool ACore::CoreInit()
{
    CreateDevice();
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
    Frame();
    return true;
}
bool ACore::CoreRender()
{
    float color[4] = { 0.1154, 0.222f, 0.0f, 1.0f };
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
