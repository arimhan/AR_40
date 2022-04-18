#include "Sample.h"
#include "ObjectMgr.h"
#include "BoxObj.h"
#include "DxState.h"

float ASampleMap::GetHeight(int index) { return AMap::GetHeight(index) * 0.1f; }

bool ASample::Init()
{
    vector<wstring> listname;
    
    //------------Load Map
    m_pMapObj->Init();
    m_pMapObj->SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
    m_pMapObj->CreateHeightMap(L"../../map/heightmap.bmp"); //heightMap513.bmp
    m_pMapObj->CreateMap(m_pMapObj->m_iNumCols, m_pMapObj->m_iNumRows, 10.0f);
    if (!m_pMapObj->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"MapRT.hlsl", L"../../data/map/020.bmp")); //map Texture
    { return false; }
    
    m_QuadTree.m_pCamera = m_pMainCamera;
    m_QuadTree.Build(&m_pMapObj, 5);



    //------------Load Fbx
    //Greystone.fbx LOD Mesh 5개
    //Greystone -> character, idel -> anim
    //listname.push_back(L"../../data/fbx/Greystone.FBX");
    //listname.push_back(L"../../data/fbx/idle.fbx");
        // 0 ~ 60  idel
        // 61 ~91  walk;
        // 92 ~ 116	  run
        // 120 ~205 jump
        // 	205 ~289  attack
    listname.push_back(L"../../data/fbx/Man.FBX");
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

        //-------------FbxObj Render Set 다수 렌더링 시 좌우 열 맞춰 렌더링 하도록 계산
        int iRow = iObj / 10;
        int iCol = iObj / 10;
        int iOffRow = iObj % 10;
        int iOffCol = iObj % 10;

        pFbx->SetPosition(T::TVector3(iOffCol * 300.0f, 0, iRow * 300.0f));

        for (int iDraw = 0; iDraw < pFbx->m_pMeshImp->m_pDrawList.size(); iDraw++)
        {
            pFbx->m_pMeshImp->m_pDrawList[iDraw]->m_pContext = m_pImmediateContext.Get();
        }
    }

    //m_pAnimImp에 해당하는 Mesh를 연결.
    m_FbxObj[0].m_pAnimImp = m_FbxObj[1].m_pMeshImp;


    //-----------MainCamera, Light, Normal Map Set

    //QuadObj Set
    m_QuadObj.CreateTextures(m_pd3dDevice.Get(), m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
    m_QuadObj.SetBuffer(m_pd3dDevice.Get());


    m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f), T::TVector3(0, 0.0f, 0));
    m_pMainCamera->CreateProjMatrix(XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 1000.0f);
    m_pLightTex = I_Texture.Load(L"../../data/pung00.dds");
    m_pNormalMap = I_Texture.Load(L"../../data/NormalMap/tileADOT3.jpg");

    return true;
}

bool ASample::Frame()
{

    m_QuadObj.Frame();
    m_pMapObj->Frame();
    m_QuadTree.Update(m_pMainCamera);
    
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

    //Debug Mode Render Set
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
    m_QuadTree.Render();

    if (m_pLightTex)
        m_pImmediateContext->PSSetShaderResources(1, 1, m_pLightTex->m_pSRV.GetAddressOf());
    if(m_pNormalMap)
        m_pImmediateContext->PSSetShaderResources(4, 1, m_pNormalMap->m_pSRV.GetAddressOf());
    for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
    {
        m_FbxObj[iObj].SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
        m_FbxObj[iObj].Render();

        TVector3 vLight = TVector3(1000, 2000, 0);
        TMatrix matRotation;
        D3DXMatrixRotationY(&matRotation, g_fGameTimer);
        D3DXVec3TransformCoord(&vLight, &vLight, &matRotation);
        D3DXVec3Normalize(&vLight, &vLight);

        TVector4 pLight = TVector4(vLight.x, vLight.y, vLight.z, 1.0f);
        TPlane pPlane = TPlane(0, 1, 0, - (m_FbxObj[iObj].m_vPos.y + 1.1f)); //FBXObj의 Y위치 + 1.1f 
        
        TVector4 p(pPlane.x, pPlane.y, pPlane.z, pPlane.w);
        TMatrix matShadow;
        D3DXMatrixShadow(&matShadow, &pLight, &pPlane);
        
        //렌더 후 이전 Shadow로 바꿔치기 해줘야 함. 안그러면 두 번째 렌더링부터 Fbxobj가 Shadow로 렌더링 됨.....
        TMatrix matSaveShadow = m_FbxObj[iObj].m_matWorld;
        matShadow = m_FbxObj[iObj].m_matWorld * matShadow;
        m_FbxObj[iObj].SetMatrix(&matShadow, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
        m_FbxObj[iObj].


    }

}


ASample::ASample() {}
ASample::~ASample() {}
void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

SIMPLE_ARUN();