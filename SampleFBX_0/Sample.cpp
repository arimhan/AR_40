#include "Sample.h"


void ASample::RenderShadow(TMatrix* pMatView, TMatrix* pMatProj)
{
    ApplyDSS(m_pImmediateContext.Get(), ADxState::g_pDSSDepthEnable);
    ApplyRS(m_pImmediateContext.Get(), ADxState::g_pRSNoneCullSolid);
    ApplyBS(m_pImmediateContext.Get(), ADxState::m_AlphaBlend);
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].SetMatrix(nullptr, pMatView, pMatProj);
        //m_FbxObj[iObj].RenderShadow(&m_pProjShadowPShader);
    }
}

bool ASample::Init()
{
    //Map Loader
    m_MapObj.Init();
    m_MapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
    m_MapObj.CreateHeightMap(L"../../data/map/heightMap513.bmp");
    m_MapObj.CreateMap(m_MapObj.m_iNumCols, m_MapObj.m_iNumRows, 5.0f);    //HeightMap Size (작을수록 폭이 좁고 높이가 높아짐)
    if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"MapRT.hlsl", L"../../data/map/HR01.bmp"))
    {
        return false;
    }
    //Map Build, Set Main Camera
    m_QuadTree.m_pCamera = m_pMainCamera;
    m_QuadTree.Build(&m_MapObj, 3);

    //Create QuadTree Texture ->BufferSize
    m_QuadObj.CreateTextures(m_pd3dDevice.Get(), m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
    m_QuadObj.SetBuffer(m_pd3dDevice.Get());
    m_QuadObj.ComputeKernel(9);

    //Set Camera
    m_pMainCamera->CreateViewMatrix(T::TVector3(0, 1000.0f, -10.0f), T::TVector3(0, 0.0f, 0.0f));
    m_pMainCamera->CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 30000.0f);

    //Set Light and Shadow
    m_vLightPos = TVector3(500, 8000, 100);
    T::D3DXVec3Normalize(&m_vLightDir, &m_vLightPos);
    m_dxRT.Create(m_pd3dDevice.Get(), 1024, 1024);  //RT Size (원래는 4096 * 4를 사용했었다.

    //m_FbxObj.Init();
    ////m_FbxObj.Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.FBX");
    //
    //AShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    //AShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PS");
    //for (int iObj = 0; iObj < m_FbxObj.m_pDrawList.size(); iObj++)
    //{
    //    m_FbxObj.m_pDrawList[iObj]->Init();
    //    m_FbxObj.m_pDrawList[iObj]->m_pColorTex = I_Texture.Load(m_FbxObj.m_pDrawList[iObj]->m_szTexFileName);
    //    m_FbxObj.m_pDrawList[iObj]->m_pVShader = pVShader;
    //    m_FbxObj.m_pDrawList[iObj]->m_pPShader = pPShader;
    //    if(!m_FbxObj.m_pDrawList[iObj]->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
    //    { return false;}
    //}
    //m_pMainCamera->CreateViewMatrix(T::TVector3(0.0f, 25.0f, -50.0f), T::TVector3(0, 0.0f, 0));

    return true;
}

bool ASample::Frame()
{
    TMatrix matRotation;
    TVector3 vLight = m_vLightPos;
    D3DXMatrixRotationY(&matRotation, g_fGameTimer);
    D3DXVec3TransformCoord(&vLight, &vLight, &matRotation);
    D3DXVec3Normalize(&m_vLightDir, &vLight);

    m_QuadObj.Frame();
    m_MapObj.Frame();
    m_QuadTree.Update(m_pMainCamera);
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].Frame();
    }
    TVector4 vClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    if(m_dxRT.Begin(m_pImmediateContext.Get(), vClearColor))
    {
        TVector3 vEye = vLight;
        TVector3 vLookAT = { 0,0,0 };
        TVector3 vUp = TVector3(0.0f, 1.0f, 0.0f);
        D3DXMatrixLookAtLH(&m_matLightView, &vEye, &vLookAT, &vUp);
        D3DXMatrixPerspectiveFovLH(&m_matLightProj, XM_PI / 4, 1, 0.1f, 30000.0f);
        //m_FbxObj[iObj].RenderShadow(&m_matLightProj);
        m_dxRT.End(m_pImmediateContext.Get());
    }
    if (AInput::Get().GetKey('8') == KEY_PUSH)
    {
        ATextureMgr::SaveFile(m_pImmediateContext.Get(), m_dxRT.m_pTexture.Get(), L"proj.bmp");
    }

    ////Animation 기능 : 시간의 흐름에 따라 월드행렬이 변경, 적용되어야 한다.
    //static float fDir = 1.0f;
    //static float fTime = 0.0f;
    //fTime += g_fSecPerFrame * 30 * fDir * 1.0f; //30 Frame
    //if (fTime >= 50.0f)
    //{
    //    fDir *= -1.0f;
    //}
    //if (fTime <= 0.0f)
    //{
    //    fDir *= -1.0f;
    //}
    //int iFrame = fTime;
    ////iFrame = min(50, iFrame);
    //iFrame = max(0, min(50, iFrame));
    //for (int iObj = 0; iObj < m_FbxObj.m_pTreeList.size(); iObj++)
    //{
    //    AFbxObj* pObj = m_FbxObj.m_pTreeList[iObj];
    //    m_FbxObj.m_pTreeList[iObj]->m_matAnim = pObj->m_AnimTrack[iFrame].matTrack;
    //}
    return true;
}

bool ASample::Render()
{
    ApplyRS(m_pImmediateContext.Get(), ADxState::g_pRSBackCullSolid);
    
    ApplySS(m_pImmediateContext.Get(), ADxState::m_pSSLinear);
    ApplySS(m_pImmediateContext.Get(), ADxState::g_pSSClampLinear);
    m_QuadObj.SetMatrix(nullptr, nullptr, nullptr);
    m_QuadObj.Render();
    //for (int iObj = 0; iObj < m_FbxObj.m_pDrawList.size(); iObj++)
    //{
    //    T::TVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
    //    T::D3DXVec3Normalize(&vLight, &vLight);
    //    vLight = vLight * -1.0f;
    //    m_FbxObj.m_pDrawList[iObj]->m_LightConstantList.vLightDir.x = vLight.x;
    //    m_FbxObj.m_pDrawList[iObj]->m_LightConstantList.vLightDir.y = vLight.y;
    //    m_FbxObj.m_pDrawList[iObj]->m_LightConstantList.vLightDir.z = vLight.z;
    //    m_FbxObj.m_pDrawList[iObj]->m_LightConstantList.vLightDir.w = 1.0f;
    //    //m_FbxObj.m_DrawList[iObj]->m_bAlphaBlend = false;
    //    /*m_pImmediateContext->OMSetDepthStencilState(
    //    TDxState::g_pDSSDepthEnableWriteDisable, 0x00);*/
    //    /*m_FbxObj.m_DrawList[iObj]->SetMatrix(
    //    &m_FbxObj.m_DrawList[iObj]->m_matWorld,
    //    &m_pMainCamera->m_matView,
    //    &m_pMainCamera->m_matProj);*/
    //    m_FbxObj.m_pDrawList[iObj]->SetMatrix(&m_FbxObj.m_pDrawList[iObj]->m_matAnim,
    //        &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
    //    m_FbxObj.m_pDrawList[iObj]->Render();
    //}

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
//void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
//void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

SIMPLE_ARUN();