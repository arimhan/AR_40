#include "Sample.h"


bool ASample::Init()
{
    ATexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
    AShader* pVShader = I_Shader.CreateVertexShader(
        m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    AShader* pPShader = I_Shader.CreatePixelShader(
        m_pd3dDevice.Get(), L"Box.hlsl", "PS");
    return true;
}

bool ASample::Frame()
{
    return true;
}

bool ASample::Render()
{


    wstring msg = L"[ FPS: ";
    msg += std::to_wstring(m_GameTimer.m_iFPS);
    msg += L"  GT: ";
    msg += std::to_wstring(m_GameTimer.m_fTimer);
    msg += L"]";
    m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(1, 1, 1, 1));
    return true;
}

bool ASample::Release()
{
    return true;
}


ASample::ASample() {}
ASample::~ASample() {}
void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

SIMPLE_ARUN();