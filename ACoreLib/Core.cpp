#include "Core.h"
#include "ObjectMgr.h" //I_ObjectMgr 

bool ACore::CoreInit()
{
    m_GameTimer.Init();
    AInput::Get().Init();
    if (SUCCEEDED(InitDevice()))
    {
        if (m_dxWrite.Init())
        {
            IDXGISurface1* pSurface = nullptr;
            HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pSurface);
            if (SUCCEEDED(hr))
            {
                m_dxWrite.SetRenderTarget(pSurface);
            }
            if (pSurface) pSurface->Release();
        }
    }
    //InitDevice();
    Init();

    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.MinLOD = FLT_MAX;
    sd.MaxLOD = FLT_MIN;
    HRESULT hr = m_pd3dDevice->CreateSamplerState(&sd, &m_pSamplerState);
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
    m_dxWrite.Frame();
    Frame();
    return true;
}
bool ACore::CoreRender()
{
    //float color[4] = { 102.0f, 204.0f, 255.0f, 1.0f }; // 102 204 255
    //float color[4] = { 0.5f, 0.5f, 1.0f, 1.0f }; // RGB 컬러명 적용 안됨
    float color[4] = { 1.0f, 1.0f, 0.8f, 1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);

    Render(); //백버퍼에 랜더링
    m_GameTimer.Render();
    AInput::Get().Render();

    m_dxWrite.Render();
    m_pSwapChain->Present(0, 0);
    return true;
}
bool ACore::CoreRelease()
{
    Release();
    if (m_pSamplerState) m_pSamplerState->Release();

    m_dxWrite.Release();
    m_GameTimer.Release();
    AInput::Get().Release();
    CleanUpDevice();
    return true;
}
ACore::ACore() {}
ACore::~ACore() {}