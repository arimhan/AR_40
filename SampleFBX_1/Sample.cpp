#include "Sample.h"
#include "ObjectMgr.h"
#include "BoxObj.h"


void ASample::RenderShadow(A::AMatrix* pmatView, A::AMatrix* pmatProj)
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
    //Greystone.fbx LOD Mesh 5��
    //Greystone -> character, idel -> anim
    listname.push_back(L"../../data/fbx/Greystone.FBX");//(L"Greystone.FBX");
    listname.push_back(L"../../data/fbx/idle.FBX");//(L"idle.fbx");
        // 0 ~ 60  idel
        // 61 ~91  walk;
        // 92 ~ 116	  run
        // 120 ~205 jump
        // 	205 ~289  attack
    //listname.push_back(L"../../data/fbx/Man.FBX");
    //("../../data/fbx/Turret_Deploy1/Turret_Deploy1.FBX");
    //listname.push_back(L"../../data/fbx/Turret_Deploy1/Turret_Deploy1.FBX");

    I_ObjectMgr.Set(m_pd3dDevice.Get(), m_pImmediateContext.Get());
    m_FbxObj.resize(listname.size());
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        AFbxObj* pFbx = &m_FbxObj[iObj];
        pFbx->Init();
        pFbx->m_iShadowID = (iObj * 2) + 1;
        pFbx->m_vShadowColor = A::AVector4(pFbx->m_iShadowID / 255.0f, 1, 1, 1);   //id�� 255(�ִ밪) ������ �÷����
        pFbx->m_pMainCamera = m_pMainCamera;
        pFbx->m_pd3dDevice = m_pd3dDevice.Get();
        pFbx->m_pContext = m_pImmediateContext.Get();
        pFbx->m_pMeshImp = I_ObjectMgr.Load((listname[iObj]));
        pFbx->m_pVShader = I_Shader.CreateVertexShader(g_pd3dDevice, L"../../data/shader/Character.hlsl", "VS");
        pFbx->m_pPShader = I_Shader.CreatePixelShader(g_pd3dDevice, L"../../data/shader/Character.hlsl", "PSMRT");
        pFbx->m_DrawList.resize(pFbx->m_pMeshImp->m_pDrawList.size());

        //-------------FbxObj Render Set �ټ� ������ �� �¿� �� ���� ������ �ϵ��� ���
        int iRow = iObj / 10;
        int iCol = iObj / 10;
        int iOffRow = iObj % 10;
        int iOffCol = iObj % 10;
        AVector3 vPos = { -2000.0f + iOffCol * 300.0f,0, -2000.0f + iRow * 300.0f };
        vPos.y = m_pMapObj.AMap::GetHeight(vPos.x, vPos.z);
        //float fHeight = m_pMapObj.AMap::GetHeight(m_FbxObj[iObj].m_vPos.x, m_FbxObj[iObj].m_vPos.z);
        pFbx->SetPosition(vPos);//(A::AVector3(iOffCol * 300.0f, 0, iRow * 300.0f));

        for (int iDraw = 0; iDraw < pFbx->m_pMeshImp->m_pDrawList.size(); iDraw++)
        {
            pFbx->m_pMeshImp->m_pDrawList[iDraw]->m_pContext = m_pImmediateContext.Get();
        }
    }

    //m_pAnimImp�� �ش��ϴ� Mesh�� ����.
    m_FbxObj[0].m_pAnimImp = m_FbxObj[1].m_pMeshImp;

    return true;
}

bool ASample::Init()
{
    HRESULT hr;

    D3D11_RASTERIZER_DESC rsDesc;
    ZeroMemory(&rsDesc, sizeof(rsDesc));
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_BACK;
    //rsDesc.FrontCounterClockwise;
    rsDesc.DepthBias = 10000;
    rsDesc.DepthBiasClamp = 0.0f;
    rsDesc.SlopeScaledDepthBias = 1.0f;
    rsDesc.DepthClipEnable = TRUE;
    //rsDesc.ScissorEnable;
    //rsDesc.MultisampleEnable;
    //rsDesc.AntialiasedLineEnable;

    if (FAILED(hr = m_pd3dDevice->CreateRasterizerState(&rsDesc, m_pRSSlopeScaledDepthBias.GetAddressOf())))
        return false;

    if (FAILED(m_QuadObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"Quad.hlsl")))
    {
        MessageBox(0, _T("m_QuadObj ����"), _T("Fatal Error"), MB_OK);
        return 0;
    }
    m_pShadowPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"PlaneShadowCharacter.hlsl", "PSColor");

    LoadMap();
    LoadFbx();

    //-----------MainCamera, Light, Normal Map Set

    //QuadObj Set
    m_QuadObj.CreateTextures(m_pd3dDevice.Get(), m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
    m_QuadObj.SetBuffer(m_pd3dDevice.Get());
    m_QuadObj.ComputeKernel(9);

    m_pMainCamera->CreateViewMatrix(A::AVector3(0, 1000.0f, -10.0f), A::AVector3(0, 0.0f, 0));
    m_pMainCamera->CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 30000.0f);
    m_pLightTex = I_Texture.Load(L"../../data/pung00.dds");
    m_pNormalMap = I_Texture.Load(L"../../data/NormalMap/tileADOT3.jpg");

    m_vLightPos = A::AVector3(5000, 8000, 100);
    A::D3DXVec3Normalize(&m_vLightDir, &m_vLightPos);

    if (m_bDepthShadoe)
    {
        m_dxRT.Create(m_pd3dDevice.Get(), 4096 * 4, 4096 * 4, DXGI_FORMAT_R24G8_TYPELESS);//1024, 1024);
        m_pProjShadowVSShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"../../data/shader/DepthShadow.hlsl", "VS");
        m_pProjShadowPSShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"../../data/shader/DepthShadow.hlsl", "PS");
    }
    else
    {
        m_dxRT.Create(m_pd3dDevice.Get(), 4096 * 4, 4096 * 4, DXGI_FORMAT_R24G8_TYPELESS);//1024, 1024);
        m_pProjShadowVSShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"../../data/shader/ProjShadow.hlsl", "VS");
        m_pProjShadowPSShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"../../data/shader/ProjShadow.hlsl", "PS");
    }
   
    m_matTex = A::AMatrix( 0.5f,  0.0f,  0.0f,  0.0f,
                        0.0f,  -0.5f, 0.0f,  0.0f,
                        0.0f,  0.0f,  1.0f,  0.0f,
                        0.5f,  0.5f,  0.0f,  1.0f);

    return true;
}

bool ASample::Frame()
{
    A::AMatrix matRotation;
    A::AVector3 vLight = m_vLightPos;
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

    A::AVector4 vClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    if(m_dxRT.Begin(m_pImmediateContext.Get(), vClearColor))
    {
        // 1path �׸��ڸ� ����
        A::AVector3 vEye = vLight;
        A::AVector3 vLookAt = { 0,0,0 };
        A::AVector3 vUp = A::AVector3(0.0f, 1.0f, 0.0f);

        D3DXMatrixLookAtLH(&m_matViewLight, &vEye, &vLookAt, &vUp);
        D3DXMatrixPerspectiveFovLH(&m_matProjLight, XM_PI / 4, 1, 0.1f, 30000.0f);
        RenderShadow(&m_matViewLight, &m_matProjLight);
        m_dxRT.End(m_pImmediateContext.Get());
    }

    if (AInput::Get().GetKey('5') == KEY_PUSH)  //8��Ű -> saveproj.bmp�� �׸��� img����
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

    //LightTex�� NormalMap�� �Ѱ� ������ �Ѵ�.
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


//Rendering �� buffer�� RT�� �ʱ�ȭ �����ش�.
void ASample::RenderIntoBuffer(ID3D11DeviceContext* pContext)
{
    //Get the old RenderTargets, Depth StencilView
    ID3D11RenderTargetView* pOldRTV;
    ID3D11DepthStencilView* pOldDSV;
    pContext->OMGetRenderTargets(1, &pOldRTV, &pOldDSV);

    //���� ����� ������ �����->SkyBox ����ϱ� ���� ���� ���
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
    //���ĺ��� ����
    m_pImmediateContext->OMSetDepthStencilState(ADxState::g_pDSSDepthEnable, 0x00);
    ApplyBS(m_pImmediateContext.Get(), ADxState::m_AlphaBlendDisable);

    m_pMapObj.m_bAlphaBlend = false;
    m_pMapObj.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
    m_pMapObj.m_LightConstantList.matLight = m_matViewLight * m_matProjLight * m_matTex;
    A::D3DXMatrixTranspose(&m_pMapObj.m_LightConstantList.matLight, &m_pMapObj.m_LightConstantList.matLight);
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
        A::D3DXMatrixTranspose(&m_FbxObj[iObj].m_LightConstantList.matLight, &m_FbxObj[iObj].m_LightConstantList.matLight);
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
        //TPlane pPlane = TPlane(0, 1, 0, - (m_FbxObj[iObj].m_vPos.y + 1.1f)); //FBXObj�� Y��ġ + 1.1f 
        //
        //TVector4 p(pPlane.x, pPlane.y, pPlane.z, pPlane.w);
        //TMatrix matShadow;
        //D3DXMatrixShadow(&matShadow, &pLight, &pPlane);
        //
        ////���� �� ���� Shadow�� �ٲ�ġ�� ����� ��. �ȱ׷��� �� ��° ���������� Fbxobj�� Shadow�� ������ ��.....
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