#include "Sample.h"


bool ASample::Init()
{
    m_FbxObj.Init();
    m_FbxObj.Load("../../data/fbx/SM_Rock.fbx");
    ATexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
    AShader* pVShader = I_Shader.CreateVertexShader(
        m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    AShader* pPShader = I_Shader.CreatePixelShader(
        m_pd3dDevice.Get(), L"Box.hlsl", "PS");
    for (int iObj = 0; iObj < m_FbxObj.m_ObjList.size(); iObj++)
    {
        m_FbxObj.m_ObjList[iObj]->Init();
        m_FbxObj.m_ObjList[iObj]->m_pColorTex = I_Texture.Load(m_FbxObj.m_ObjList[iObj]->m_szTexFileNmae);
        m_FbxObj.m_ObjList[iObj]->m_pVShader = pVShader;
        m_FbxObj.m_ObjList[iObj]->m_pPShader = pPShader;
        m_FbxObj.m_ObjList[iObj]->SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
        if(!m_FbxObj.m_ObjList[iObj]->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
        { return false;}
    }

    m_pMainCamera->CreateViewMatrix(T::TVector3(0.0f, 25.0f, -50.0f), T::TVector3(0, 0.0f, 0));

    return true;
}

bool ASample::Frame()
{
    return true;
}

bool ASample::Render()
{
    for (int iObj = 0; iObj < m_FbxObj.m_ObjList.size(); iObj++)
    {
        m_FbxObj.m_ObjList[iObj]->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
        m_FbxObj.m_ObjList[iObj]->Render();
    }

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
    m_FbxObj.Release();
    return true;
}


ASample::ASample() {}
ASample::~ASample() {}
void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

SIMPLE_ARUN();