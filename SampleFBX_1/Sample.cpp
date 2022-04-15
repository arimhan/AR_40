#include "Sample.h"
#include "ObjectMgr.h"
#include "BoxObj.h"

bool ASample::Init()
{
    vector<wstring> listname;
    
    //Greystone.fbx LOD Mesh 5개
    //Greystone -> character, idel -> anim
    listname.push_back(L"../../data/fbx/Greystone.fbx");
    //listname.push_back(L"../../data/fbx/idle.fbx");
        // 0 ~ 60  idel
        // 61 ~91  walk;
        // 92 ~ 116	  run
        // 120 ~205 jump
        // 	205 ~289  attack

    //listname.push_back(L"../../data/fbx/Man.fbx");
    //("../../data/fbx/Turret_Deploy1/Turret_Deploy1.FBX");
    
    I_ObjectMgr.Set(m_pd3dDevice.Get(), m_pImmediateContext.Get());
    m_FbxObj.resize(listname.size());
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        AFbxObj* pFbx = &m_FbxObj[iObj];
        pFbx->Init();
        pFbx->m_pMainCamera = m_pMainCamera;
        pFbx->m_pd3dDevice = m_pd3dDevice.Get();
        pFbx->m_pContext = m_pImmediateContext.Get();
        pFbx->m_pMeshImp = I_ObjectMgr.Load((listname[iObj]));
        pFbx->m_DrawList.resize(pFbx->m_pMeshImp->m_pDrawList.size());
        pFbx->SetPosition(T::TVector3(iObj * 100.0f, 0, 0));

        for (int iDraw = 0; iDraw < pFbx->m_pMeshImp->m_pDrawList.size(); iDraw++)
        {
            pFbx->m_pMeshImp->m_pDrawList[iDraw]->m_pContext = m_pImmediateContext.Get();
        }
    }
    //m_FbxObj[0].m_pAnimImp = m_FbxObj[1].m_pMeshImp;
    m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f), T::TVector3(0, 0.0f, 0));
    m_pMainCamera->CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 1000.0f);
    m_pLightTex = I_Texture.Load(L"../../data/pung00.dds");
    m_pNormalMap = I_Texture.Load(L"../../data/NormalMap/tileADOT3.jpg");

    return true;
}

bool ASample::Frame()
{
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].Frame();
    }
    return true;
}

bool ASample::Render()
{
    //LightTex와 NormalMap을 넘겨 렌더링 한다.
    m_pImmediateContext->PSSetShaderResources(1, 1, m_pLightTex->m_pSRV.GetAddressOf());
    m_pImmediateContext->PSSetShaderResources(4, 1, m_pNormalMap->m_pSRV.GetAddressOf());

    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
        m_FbxObj[iObj].Render();
    }

    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        for (int iDraw = 0; iDraw < m_FbxObj[iObj].m_DrawList.size(); iDraw++)
        { 
            g_pBoxDebug->SetMatrix(&m_FbxObj[iObj].m_pMeshImp->m_pDrawList[iDraw]->m_matWorld,
                &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
            g_pBoxDebug->DrawDebugRender(&m_FbxObj[iObj].m_pMeshImp->m_pDrawList[iDraw]->m_BoxCollision);
        }

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
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].Release();
    }
    return true;
}


ASample::ASample() {}
ASample::~ASample() {}
void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

SIMPLE_ARUN();