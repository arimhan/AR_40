#include "Sample.h"

void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

bool ASample::Init()
{
    //ATexture* pTex = I_Texture.Load(L"../../data/ui/save_0000_O-K.png");

    //카메라 기능
    m_CameraTopView.CreateViewMatrix(T::TVector3(0, 3000.0f, -1), T::TVector3(0, 0.0f, 0));
    m_CameraTopView.CreateProjMatrix(XM_PI * 0.25f, 
        (float)g_rtClient.right / (float)g_rtClient.bottom, 1.0f, 30000.0f);
    
    m_Camera.Init();

    //Frustum 추가하면서 카메라 위치 세팅 추가 (TopView)
    m_Camera.CreateViewMatrix(T::TVector3(0, 500.0f, -100.0f), T::TVector3(0, 0.0f, 0));
    m_Camera.CreateProjMatrix(XM_PI * 0.25f,
        (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.0f);
    m_Camera.m_pColorTex = I_Texture.Load(L"../../data/Img/ship.png");
    m_Camera.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VSColor");
    m_Camera.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PSColor");
    m_Camera.SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
    if (!m_Camera.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) 
    { return false;}



    AShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    AShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PS");
    //Map Obj위에서 움직이는 PlayerObj 불러오기
    m_PlayerObj_1.Init();
    m_PlayerObj_1.m_pColorTex = I_Texture.Load(L"../../data/Img/charport.bmp"); //enemy.png
    m_PlayerObj_1.m_pVShader = pVShader;
    m_PlayerObj_1.m_pPShader = pPShader;
    m_PlayerObj_1.SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
    if (!m_PlayerObj_1.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }

    m_SkyObj.Init();
    m_SkyObj.SetPosition(T::TVector3(0.0f, 0.0f, 0.0f));
    if (!m_SkyObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"Sky.hlsl", 
        L"../../data/sky/skycubemap.dds")) { return false; }

     //Map Obj 불러오기
    m_MapObj.Init();
    m_MapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
    m_MapObj.CreateHeightMap(L"../../data/map/heightmap.bmp");   
    ATexture* pTexMap = I_Texture.Load(L"../../data/map/020.bmp");  //전체지형 이미지
    m_MapObj.m_pColorTex = pTexMap;
    m_MapObj.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Map.hlsl", "VS");
    m_MapObj.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Map.hlsl", "PS");

    //정점개수 (2n승 +1. ex 8 +1 = 9..)
    m_MapObj.CreateMap(m_MapObj.m_iNumCols, m_MapObj.m_iNumRows, 20.0f);
    if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }

    m_Quadtree.m_pCamera = &m_Camera;
    m_Quadtree.Build(&m_MapObj, 3);
    CreateMapObject();
    for (int iObj = 0; iObj < MAX_NUM_OBJECTS; iObj++)
    {
        m_Quadtree.AddObject(m_pObjList[iObj]);
    }

    //Frustum 확인용 ObjList 추가
    //m_pObjList.resize(100);
    //for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
    //{
    //    m_ObjList[iObj].Init();
    //    m_ObjList[iObj].m_pColorTex = I_Texture.Load(L"../../data/Img/KGCABK.bmp");
    //    m_ObjList[iObj].m_pVShader = pVShader;
    //    m_ObjList[iObj].m_pPShader = pPShader;
    //    m_ObjList[iObj].SetPosition(T::TVector3(-300.0f + rand() % 600, 100.0f, -300.0f + rand() % 600));
    //    if(!m_ObjList[iObj].Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
    //    {
    //        return false;
    //    }
    //}

    return true;
}

bool ASample::Frame()
{
    T::TVector2 dir = AInput::Get().GetDelta();
    T::TMatrix matRotate, matScale;
    T::D3DXMatrixRotationY(&matRotate, -dir.y);
    T::D3DXMatrixScaling(&matScale, 50, 50, 50);

    m_PlayerObj_1.m_matWorld = matScale * matRotate;
    m_PlayerObj_1.m_vPos.y = m_MapObj.GetHeight(m_PlayerObj_1.m_vPos.x, m_PlayerObj_1.m_vPos.z) + 50;
    m_PlayerObj_1.SetPosition(m_PlayerObj_1.m_vPos);
   
    m_Camera.m_vTarget = m_PlayerObj_1.m_vPos;
    float y = m_MapObj.GetHeight(m_Camera.m_vCamera.x, m_Camera.m_vCamera.z);

    if (AInput::Get().GetKey('W')) { m_Camera.MoveLook(g_fSecPerFrame * 100.0f); }
    if (AInput::Get().GetKey('S')) { m_Camera.MoveLook(-g_fSecPerFrame * 100.0f); }
    if (AInput::Get().GetKey('A')) { m_Camera.MoveSide(-g_fSecPerFrame * 100.0f); }
    if (AInput::Get().GetKey('D')) { m_Camera.MoveSide(g_fSecPerFrame * 100.0f); }

    m_Camera.Update(T::TVector4(-dir.x, -dir.y, 0, 0));
    m_MapObj.Frame();
    m_Quadtree.Update(&m_Camera);
    m_PlayerObj_1.Frame();

    ////Frustum 출력 용 m_ObjList 세팅
    //T::TMatrix matRotObjList;
    //for (auto& obj : m_ObjList)
    //{
    //    T::D3DXMatrixScaling(&matScale,
    //        10 * cosf(g_fGameTimer), 10 * cosf(g_fGameTimer), 10 * cosf(g_fGameTimer));
    //    T::D3DXMatrixRotationYawPitchRoll(&matRotObjList,
    //        cosf(g_fGameTimer * obj.m_vPos.x * 0.001f) * XM_PI,
    //        sinf(g_fGameTimer * obj.m_vPos.y * 0.001f) * XM_PI, 1.0f);
    //    obj.m_matWorld = matScale * matRotObjList;
    //    obj.m_vPos.y = m_MapObj.GetHeight(obj.m_vPos.x, obj.m_vPos.z) + 50;
    //    obj.SetPosition(obj.m_vPos);
    //    obj.Frame();
    //}
    return true;
}

bool ASample::Render()
{
    //m_SkyObj 세팅 및 렌더링

    m_SkyObj.SetMatrix(NULL, &m_Camera.m_matWorld, &m_Camera.m_matProj);
    m_SkyObj.Render();

    if (m_bWireFrame)
        m_pImmediateContext->RSSetState(ADxState::g_pRSBackCullWireFrame);
    else
        m_pImmediateContext->RSSetState(ADxState::g_pRSBackCullSolid);
    m_pImmediateContext->PSSetSamplers(0, 1, &ADxState::m_pSSLinear);

    m_MapObj.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
    //m_MapObj.Render();

    m_PlayerObj_1.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
    m_PlayerObj_1.Render();


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
    m_SkyObj.Release();
    m_MapObj.Release();
    m_PlayerObj_1.Release();
    m_Camera.Release();
    //for(auto& obj : m_pObjList)
    //{
    //    obj.Release();
    //}
    return true;
}


//bool ASample::GetIntersection(T::TVector3 vStart, T::TVector3 vEnd, T::TVector3 v0, T::TVector3 v1, T::TVector3 v2, T::TVector3 vNormal) {}
//bool ASample::PointInPolygon(T::TVector3 vert, T::TVector3 faceNormal,T::TVector3 v0, T::TVector3 v1, T::TVector3 v2) {}

void ASample::CreateMapObject() 
{
    srand(time(NULL));
    //ATexture* pTex = I_Texture.Load(L"../../data/ui/save_0000_O-K.png");
    AShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    AShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PS");

    m_pBoxObj = new ABoxObj;
    m_pBoxObj->m_pColorTex = I_Texture.Load(L"../../data/Img/KGCABK.bmp");
    m_pBoxObj->m_pVShader = pVShader;
    m_pBoxObj->m_pPShader = pPShader;
    if(!m_pBoxObj->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
    {
        return;
    }
    T::TMatrix matScale;
    T::TMatrix matRotateObj;
    for (int iObj = 0; iObj < MAX_NUM_OBJECTS; iObj++)
    {
        AMapObj* pObj = new AMapObj;
        for (int iv = 0; iv < 8; iv++)
        {
            pObj->box.vList[iv] = m_pBoxObj->m_BoxCollision.vList[iv];
        }
        pObj->vPos = T::TVector3(randstep(m_MapObj.m_BoxCollision.vMin.x, m_MapObj.m_BoxCollision.vMax.x),
            0.0f, randstep(m_MapObj.m_BoxCollision.vMin.z, m_MapObj.m_BoxCollision.vMax.z));

        T::D3DXMatrixScaling(&matScale, randstep(10.0f, 100.0f), randstep(10.0f, 100.0f), randstep(10.0f, 100.0f));
        T::D3DXMatrixRotationYawPitchRoll(&matRotateObj, 
            cosf(randstep(0.0f, 360.f)) * XM_PI, sinf(randstep(0.0f, 360.f)) * XM_PI, 1.0f);
        pObj->matWorld = matScale * matRotateObj;
        pObj->vPos.y = m_MapObj.GetHeight(pObj->vPos.x, pObj->vPos.z);
        pObj->matWorld._41 = pObj->vPos.x;
        pObj->matWorld._42 = pObj->vPos.y;
        pObj->matWorld._43 = pObj->vPos.z;
        pObj->UpdateData();
        pObj->UpdateCollision();
        pObj->pObject = m_pBoxObj;
        m_pObjList.push_back(pObj);
    }
}

bool ASample::MiniMapRender()
{
    //Frustum 출력 용 m_ObjList 세팅
    for (auto pObj: m_pObjList) //vector<AMapObj*>::iterator::value_type=AMapObj*
    {
        pObj->pObject->SetMatrix(&pObj->matWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
        pObj->pObject->m_ConstantList.Color = T::TVector4(0, 0, 0, 1);
        pObj->pObject->Render();
    }
    m_Camera.SetMatrix(nullptr, &m_CameraTopView.m_matView, &m_CameraTopView.m_matProj);
    m_Camera.Render();

    return true;
}


ASample::ASample() {}
ASample::~ASample() {}

SIMPLE_ARUN();