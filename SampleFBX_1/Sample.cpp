#include "Sample.h"
#include "ObjectMgr.h"
#include "BoxObj.h"

void ASample::DisplayErrorBox(const WCHAR* lpszFunction)
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}


void ASample::RenderShadow(TMatrix* pmatView, TMatrix* pmatProj) 
{
    ApplyDSS(m_pImmediateContext.Get(), ADxState::g_pDSSDepthEnable);
    ApplyRS(m_pImmediateContext.Get(), ADxState::g_pRSNoneCullSolid);

    ApplyBS(m_pImmediateContext.Get(), ADxState::m_AlphaBlend);

    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].SetMatrix(nullptr, pmatView, pmatProj);
        m_FbxObj[iObj].RenderShadow(m_pProjShadowPSShader);
    }
}

bool ASample::LoadMap() 
{
    //------------Load Map
    m_pMapObj.Init();
    m_pMapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
    m_pMapObj.CreateHeightMap(L"../../data/map/heightMap513.bmp"); //heightMap513.bmp  heightmap
    m_pMapObj.CreateMap(m_pMapObj.m_iNumCols, m_pMapObj.m_iNumRows, 10.0f);
    if (!m_pMapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"MapRT.hlsl", L"../../data/map/002.jpg")) //map Texture
    {
        return false;
    }

    m_QuadTree.m_pCamera = m_pMainCamera;
    m_QuadTree.Build(&m_pMapObj, 5);

    return true;
}

bool ASample::LoadFbx() 
{
    vector<wstring> listname;
    //------------Load Fbx
    //Greystone.fbx LOD Mesh 5개
    //Greystone -> character, idel -> anim
    listname.push_back(L"../../data/fbx/Greystone.FBX");
    listname.push_back(L"../../data/fbx/idle.fbx");
        // 0 ~ 60  idel
        // 61 ~91  walk;
        // 92 ~ 116	  run
        // 120 ~205 jump
        // 	205 ~289  attack
    //listname.push_back(L"../../data/fbx/Man.FBX");
    //("../../data/fbx/Turret_Deploy1/Turret_Deploy1.FBX");

    I_ObjectMgr.Set(m_pd3dDevice.Get(), m_pImmediateContext.Get());
    m_FbxObj.resize(listname.size());
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        AFbxObj* pFbx = &m_FbxObj[iObj];
        pFbx->Init();
        pFbx->m_iShadowID = (iObj * 2) + 1;
        pFbx->m_vShadowColor = TVector4(pFbx->m_iShadowID / 255.0f, 1, 1, 1);   //id를 255(최대값) 나누어 컬러배분
        pFbx->m_pMainCamera = m_pMainCamera;
        pFbx->m_pd3dDevice = m_pd3dDevice.Get();
        pFbx->m_pContext = m_pImmediateContext.Get();
        pFbx->m_pMeshImp = I_ObjectMgr.Load((listname[iObj]));
        pFbx->m_pVShader = I_Shader.CreateVertexShader(g_pd3dDevice, L"../../data/shader/Character.hlsl", "VS");
        pFbx->m_pPShader = I_Shader.CreatePixelShader(g_pd3dDevice, L"../../data/shader/Character.hlsl", "PSMRT");
        pFbx->m_DrawList.resize(pFbx->m_pMeshImp->m_pDrawList.size());

        //-------------FbxObj Render Set 다수 렌더링 시 좌우 열 맞춰 렌더링 하도록 계산
        int iRow = iObj / 10;
        int iCol = iObj / 10;
        int iOffRow = iObj % 10;
        int iOffCol = iObj % 10;
        float fHeight = m_pMapObj.AMap::GetHeight(m_FbxObj[iObj].m_vPos.x, m_FbxObj[iObj].m_vPos.z);

        pFbx->SetPosition(T::TVector3(iOffCol * 300.0f, 0, iRow * 300.0f));

        for (int iDraw = 0; iDraw < pFbx->m_pMeshImp->m_pDrawList.size(); iDraw++)
        {
            pFbx->m_pMeshImp->m_pDrawList[iDraw]->m_pContext = m_pImmediateContext.Get();
        }
    }

    //m_pAnimImp에 해당하는 Mesh를 연결.
    m_FbxObj[0].m_pAnimImp = m_FbxObj[1].m_pMeshImp;

    return true;
}

bool ASample::Init()
{
    HRESULT hr;
    if (FAILED(m_QuadObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"Quad.hlsl")))
    {
        MessageBox(0, _T("m_QuadObj 실패"), _T("Fatal Error"), MB_OK);
        return 0;
    }

    //m_pShadowPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"PlaneShadowCharacter.hlsl", "PSColor");

    LoadMap();
    LoadFbx();

    //-----------MainCamera, Light, Normal Map Set

    //QuadObj Set
    m_QuadObj.CreateTextures(m_pd3dDevice.Get(), m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
    m_QuadObj.SetBuffer(m_pd3dDevice.Get());
    m_QuadObj.ComputeKernel(9);

    m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f), T::TVector3(0, 0.0f, 0));
    m_pMainCamera->CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 1000.0f);
    m_pLightTex = I_Texture.Load(L"../../data/pung00.dds");
    m_pNormalMap = I_Texture.Load(L"../../data/NormalMap/tileADOT3.jpg");

    m_vLightPos = TVector3(500, 8000, 100);
    T::D3DXVec3Normalize(&m_vLightDir, &m_vLightPos);
    m_dxRT.Create(m_pd3dDevice.Get(), 4096 * 4, 4096 * 4);
    m_pProjShadowVSShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Projection.hlsl", "VS");
    m_pProjShadowPSShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Projection.hlsl", "PS");

    m_matTex = TMatrix( 0.5f,  0.0f,  0.0f,  0.0f,
                        0.0f,  -0.5f, 0.0f,  0.0f,
                        0.0f,  0.0f,  1.0f,  0.0f,
                        0.5f,  0.5f,  0.0f,  1.0f);

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
    m_pMapObj.Frame();
    m_QuadTree.Update(m_pMainCamera);
    
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].Frame();
    }

    TVector4 vClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    if(m_dxRT.Begin(m_pImmediateContext.Get(), vClearColor))
    {
        // 1path 그림자맵 생성
        TVector3 vEye = vLight;
        TVector3 vLookAt = { 0,0,0 };
        TVector3 vUp = TVector3(0.0f, 1.0f, 0.0f);

        D3DXMatrixLookAtLH(&m_matViewLight, &vEye, &vLookAt, &vUp);
        D3DXMatrixPerspectiveFovLH(&m_matProjLight, XM_PI / 4, 1, 0.1f, 30000.0f);
        RenderShadow(&m_matViewLight, &m_matProjLight);
        m_dxRT.End(m_pImmediateContext.Get());
    }

    if (AInput::Get().GetKey('5') == KEY_PUSH)  //8번키 -> saveproj.bmp로 그림자 img저장
    {
        ATextureMgr::SaveFile(m_pImmediateContext.Get(), m_dxRT.m_pTexture.Get(), L"saveproj.bmp");
    }

    return true;
}

bool ASample::Render()
{
    ApplyRS(m_pImmediateContext.Get(), ADxState::g_pRSBackCullSolid);
    RenderIntoBuffer(m_pImmediateContext.Get());
    
    ApplySS(m_pImmediateContext.Get(), ADxState::m_pSSLinear);
    ApplySS(m_pImmediateContext.Get(), ADxState::g_pSSClampLinear);
    m_QuadObj.SetMatrix(nullptr, nullptr, nullptr);
    m_QuadObj.Render();

    //LightTex와 NormalMap을 넘겨 렌더링 한다.
    //m_pImmediateContext->PSSetShaderResources(1, 1, m_pLightTex->m_pSRV.GetAddressOf());
    //m_pImmediateContext->PSSetShaderResources(4, 1, m_pNormalMap->m_pSRV.GetAddressOf());
    //for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    //{
    //    m_FbxObj[iObj].SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
    //    m_FbxObj[iObj].Render();
    //}

//#ifdef _DEBUG
//        //Debug Mode Render Set
//    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
//    {
//        for (int iDraw = 0; iDraw < m_FbxObj[iObj].m_DrawList.size(); iDraw++)
//        {
//            g_pBoxDebug->SetMatrix(&m_FbxObj[iObj].m_pMeshImp->m_pDrawList[iDraw]->m_matWorld,
//                &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
//            g_pBoxDebug->DrawDebugRender(&m_FbxObj[iObj].m_pMeshImp->m_pDrawList[iDraw]->m_BoxCollision);
//        }
//    }
//#endif // _DEBUG

    wstring msg = L"[ FPS: ";
    msg += std::to_wstring(m_GameTimer.m_iFPS);
    msg += L"  GT: ";
    msg += std::to_wstring(m_GameTimer.m_fTimer);
    msg += L"]";
    m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(1, 1, 1, 1));

    ClearD3D11DeviceContext(m_pImmediateContext.Get());

    return true;
}

bool ASample::Release()
{
    m_dxRT.Release();
    m_QuadObj.Release();
    m_pMapObj.Release();

    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].Release();
    }
    return true;
}


//Rendering 후 buffer내 RT를 초기화 시켜준다.
void ASample::RenderIntoBuffer(ID3D11DeviceContext* pContext)
{
    //Get the old RenderTargets, Depth StencilView
    ID3D11RenderTargetView* pOldRTV;
    ID3D11DepthStencilView* pOldDSV;
    pContext->OMGetRenderTargets(1, &pOldRTV, &pOldDSV);

    //이전 백버퍼 렌더링 결과물->SkyBox 사용하기 위해 알파 사용
    float color[4] = { 0, 0, 0, 0 };
    pContext->ClearRenderTargetView(m_QuadObj.m_pColorRTV.Get(), color);
    pContext->ClearRenderTargetView(m_QuadObj.m_pNormalDepthRTV.Get(), color);
    pContext->ClearDepthStencilView(m_QuadObj.m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);

    //Set New Render Targets
    ID3D11RenderTargetView* pNewViews[2];
    pNewViews[0] = m_QuadObj.m_pColorRTV.Get();
    pNewViews[1] = m_QuadObj.m_pNormalDepthRTV.Get();
    pContext->OMSetRenderTargets(2, pNewViews, m_QuadObj.m_pDepthStencilView.Get());

    RenderMTR(pContext);

    //Restore the Original Render Targets
    pNewViews[0] = pOldRTV;
    pNewViews[1] = NULL;
    pContext->OMSetRenderTargets(2, pNewViews, pOldDSV);

    SAFE_RELEASE(pOldRTV);
    SAFE_RELEASE(pOldDSV);

}

void ASample::RenderMTR(ID3D11DeviceContext* pContext)
{
    //알파블렌딩 해제
    m_pImmediateContext->OMSetDepthStencilState(ADxState::g_pDSSDepthEnable, 0x00);
    ApplyBS(m_pImmediateContext.Get(), ADxState::m_AlphaBlendDisable);

    m_pMapObj.m_bAlphaBlend = false;
    m_pMapObj.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
    m_pMapObj.m_LightConstantList.matLight = m_matViewLight * m_matProjLight * m_matTex;
    T::D3DXMatrixTranspose(&m_pMapObj.m_LightConstantList.matLight, &m_pMapObj.m_LightConstantList.matLight);
    m_pImmediateContext->PSSetSamplers(1, 1, &ADxState::g_pSSClampLinear);
  
    m_QuadTree.PreRender();
    pContext->PSSetShaderResources(1, 1, m_dxRT.m_pSRV.GetAddressOf());
    m_QuadTree.PostRender();

    if (m_pLightTex)      pContext->PSSetShaderResources(1, 1, m_pLightTex->m_pSRV.GetAddressOf());
    if(m_pNormalMap)      pContext->PSSetShaderResources(4, 1, m_pNormalMap->m_pSRV.GetAddressOf());
    if (m_dxRT.m_pSRV)    pContext->PSSetShaderResources(5, 1, m_dxRT.m_pSRV.GetAddressOf());


    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].m_LightConstantList.matLight = m_matViewLight * m_matProjLight * m_matTex;
        T::D3DXMatrixTranspose(&m_FbxObj[iObj].m_LightConstantList.matLight, &m_FbxObj[iObj].m_LightConstantList.matLight);
        m_FbxObj[iObj].SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
        m_FbxObj[iObj].Render();

        //Plane Shadow
        //TVector4 vLight = TVector4(m_vLightDir.x, m_vLightDir.y, m_vLightDir.z, 1.0f);
        //TPlane plane = TPlane(0, 1, 0, -(m_FbxObj[iObj].m_vPos.y + 1.1f));
        //TVector4 p(plane.x, plane.y, plane.z, plane.w);
        //TMatrix matShadow;
        //D3DXMatrixShadow(&matShadow, &vLight, &plane);

        //TMatrix matSaveWorld = m_FbxObj[iObj].m_matWorld;
        //matShadow = m_FbxObj[iObj].m_matWorld * matShadow;
        //m_FbxObj[iObj].SetMatrix(&matShadow, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
        //m_FbxObj[iObj].RenderShadow(m_pShadowPShader);
        //m_FbxObj[iObj].m_matWorld = matSaveWorld;

        //TVector3 vLight = TVector3(1000, 2000, 0);
        //TMatrix matRotation;
        //D3DXMatrixRotationY(&matRotation, g_fGameTimer);
        //D3DXVec3TransformCoord(&vLight, &vLight, &matRotation);
        //D3DXVec3Normalize(&vLight, &vLight);
        //TVector4 pLight = TVector4(vLight.x, vLight.y, vLight.z, 1.0f);
        //TPlane pPlane = TPlane(0, 1, 0, - (m_FbxObj[iObj].m_vPos.y + 1.1f)); //FBXObj의 Y위치 + 1.1f 
        //
        //TVector4 p(pPlane.x, pPlane.y, pPlane.z, pPlane.w);
        //TMatrix matShadow;
        //D3DXMatrixShadow(&matShadow, &pLight, &pPlane);
        //
        ////렌더 후 이전 Shadow로 바꿔치기 해줘야 함. 안그러면 두 번째 렌더링부터 Fbxobj가 Shadow로 렌더링 됨.....
        //TMatrix matSaveShadow = m_FbxObj[iObj].m_matWorld;
        //matShadow = m_FbxObj[iObj].m_matWorld * matShadow;
        //m_FbxObj[iObj].SetMatrix(&matShadow, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
        //m_FbxObj[iObj].RenderShadoe(m_pShadowPShader);
        //m_FbxObj[iObj].m_matWorld = matSaveShadow;
    }
    ClearD3D11DeviceContext(pContext);
}


ASample::ASample() {}
ASample::~ASample() {}
ASampleMap::~ASampleMap() {}

void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

SIMPLE_ARUN();