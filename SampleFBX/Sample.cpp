#include "Sample.h"


bool ASample::Init()
{
    m_FbxObj.Init();
    //m_FbxObj.Load("../../data/fbx/SM_Rock.fbx");
    //m_FbxObj.Load("../../data/fbx/SM_Barrel.fbx");
    m_FbxObj.Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.FBX");

    ATexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
    AShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    AShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PS");
    for (int iObj = 0; iObj < m_FbxObj.m_pDrawList.size(); iObj++)
    {
        m_FbxObj.m_pDrawList[iObj]->Init();
        m_FbxObj.m_pDrawList[iObj]->m_pColorTex = I_Texture.Load(m_FbxObj.m_pDrawList[iObj]->m_szTexFileName);
        m_FbxObj.m_pDrawList[iObj]->m_pVShader = pVShader;
        m_FbxObj.m_pDrawList[iObj]->m_pPShader = pPShader;
        if(!m_FbxObj.m_pDrawList[iObj]->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
        { return false;}
    }

    m_pMainCamera->CreateViewMatrix(T::TVector3(0.0f, 25.0f, -50.0f), T::TVector3(0, 0.0f, 0));

    return true;
}

bool ASample::Frame()
{
    //Animation 기능 : 시간의 흐름에 따라 월드행렬이 변경, 적용되어야 한다.
    static float fDir = 1.0f;
    static float fTime = 0.0f;
    fTime += g_fSecPerFrame * 30 * fDir * 1.0f; //30 Frame
    if (fTime >= 50.0f)
    {
        fDir *= -1.0f;
    }
    if (fTime <= 0.0f)
    {
        fDir *= -1.0f;
    }
    int iFrame = fTime;
    //iFrame = min(50, iFrame);
    iFrame = max(0, min(50, iFrame));
    for (int iObj = 0; iObj < m_FbxObj.m_pTreeList.size(); iObj++)
    {
        AFbxObject* pObj = m_FbxObj.m_pTreeList[iObj];
        m_FbxObj.m_pTreeList[iObj]->m_matAnim = pObj->m_AnimTrack[iFrame].matTrack;
    }
    return true;
}

bool ASample::Render()
{
    for (int iObj = 0; iObj < m_FbxObj.m_pDrawList.size(); iObj++)
    {
        T::TVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
        T::D3DXVec3Normalize(&vLight, &vLight);
        vLight = vLight * -1.0f;

        m_FbxObj.m_pDrawList[iObj]->m_LightConstantList.vLightDir.x = vLight.x;
        m_FbxObj.m_pDrawList[iObj]->m_LightConstantList.vLightDir.y = vLight.y;
        m_FbxObj.m_pDrawList[iObj]->m_LightConstantList.vLightDir.z = vLight.z;
        m_FbxObj.m_pDrawList[iObj]->m_LightConstantList.vLightDir.w = 1.0f;

        //m_FbxObj.m_DrawList[iObj]->m_bAlphaBlend = false;
        /*m_pImmediateContext->OMSetDepthStencilState(
        TDxState::g_pDSSDepthEnableWriteDisable, 0x00);*/

        /*m_FbxObj.m_DrawList[iObj]->SetMatrix(
        &m_FbxObj.m_DrawList[iObj]->m_matWorld,
        &m_pMainCamera->m_matView,
        &m_pMainCamera->m_matProj);*/

        m_FbxObj.m_pDrawList[iObj]->SetMatrix(&m_FbxObj.m_pDrawList[iObj]->m_matAnim,
            &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
        m_FbxObj.m_pDrawList[iObj]->Render();
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