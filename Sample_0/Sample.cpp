#include "Sample.h"


bool ASample::Init()
{
    //카메라 기능
    m_Camera.Init();

    /**/
    ATexture* pTex = I_Texture.Load(L"../../data/ui/save_0000_O-K.png");
    AShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    AShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PS");

    //Map Obj 불러오기
    m_MapObj.Init();
    m_MapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
    //m_MapObj.CreateHeightMap(L"../../data/map/129.jpg");            //높이맵 (그림자) 이미지
    m_MapObj.CreateHeightMap(L"../../data/map/HEIGHT_MOUNTAIN.bmp");  //heightMap513.bmp     
    ATexture* pTexMap = I_Texture.Load(L"../../data/map/020.bmp");  //전체지형 이미지
    m_MapObj.m_pColorTex = pTexMap;

    m_MapObj.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Map.hlsl", "VS");
    m_MapObj.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Map.hlsl", "PS");

    //정점개수 (2n승 +1. ex 8 +1 = 9..)
    m_MapObj.CreateMap(m_MapObj.m_iNumCols, m_MapObj.m_iNumRows, 20.0f);
    if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }

    /*
    //지형 Obj X축 회전으로 바닥에 깔기
    m_MapObj.m_matWorld = matScale * matRotate; // SRT순으로
    AMatrix matRotate, matScale; //matTrans;
    matRotate.XRotate(DegreeToRadian(90)); //X축으로 90도 눕기
    matScale.Scale(10, 10.0f, 10.0f);
    */


    //Map Obj위에서 움직이는 PlayerObj 불러오기
    m_PlayerObj_1.Init();
    m_PlayerObj_1.m_pColorTex = I_Texture.Load(L"../../data/Img/charport.bmp"); //enemy.png
    m_PlayerObj_1.m_pVShader = pVShader;
    m_PlayerObj_1.m_pPShader = pPShader;
    m_PlayerObj_1.SetPosition(AVector3(0.0f, 1.0f, 0.0f));
    if (!m_PlayerObj_1.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }

    m_SkyObj.Init();
    //m_PlayerObj_1.m_pColorTex = I_Texture.Load(L"../../data/sky/skt_1/enemy.png");
    m_SkyObj.SetPosition(AVector3(0.0f, 0.0f, 0.0f));
    if (!m_SkyObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"Sky.hlsl", L"../../data/sky/LobbyCube.dds")) { return false; }
    //m_pTexCube = I_Texture.Load(L"../../data/sky/LobbyCube.dds");
  /*
    //Z버퍼링 비교할 Obj 출력
    m_BackObj.Init();
    m_BackObj.m_pColorTex = I_Texture.Load(L"../../data/ui/_exit_lg.bmp");
    m_BackObj.m_pVShader = pVShader;
    m_BackObj.m_pPShader = pPShader;
    m_BackObj.SetPosition(AVector3(0.0f, 1.0f, 0.0f));
    if (!m_BackObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }
    m_BackObj.m_matWorld.Translation(1.0f, 0.0f, 0.0f);
    */
    //world
   /* AMatrix matRotate, matScale, matTrans;
    matRotate.ZRotate(g_fGameTimer);
    matScale.Scale(cos(g_fGameTimer) * 0.5f + 0.5f, 1.0f, 1.0f);
    matTrans.Translation(0,
        cos(g_fGameTimer) * 0.5f + 0.5f, 0);
    m_matWorld = matRotate;
    matRotate.XRotate(DegreeToRadian(90));*/

    return true;
}

bool ASample::Frame()
{
    //키 조작
    if (AInput::Get().GetKey('W'))
    {
        m_PlayerObj_1.m_vPos.z += g_fSecPerFrame * 100.0f;
    }
    if (AInput::Get().GetKey('S'))
    {
        m_PlayerObj_1.m_vPos.z -= g_fSecPerFrame * 100.0f;
    }
    if (AInput::Get().GetKey('A'))
    {
        m_PlayerObj_1.m_vPos.x -= g_fSecPerFrame * 100.0f;
    }
    if (AInput::Get().GetKey('D'))
    {
        m_PlayerObj_1.m_vPos.x += g_fSecPerFrame * 100.0f;
    }

    AMatrix matRorate, matScale;
    //AMatrix matScale;
    static float fRadian = 0.0f;
    fRadian += (AInput::Get().m_ptDeltaMouse.x / (float)g_rtClient.right) * ABASIS_PI;
    matRorate.YRotate(fRadian);
    matScale.Scale(50, 50, 50);

    m_PlayerObj_1.m_matWorld = matScale * matRorate;
    m_PlayerObj_1.m_vPos.y = m_MapObj.GetHeight(m_PlayerObj_1.m_vPos.x, m_PlayerObj_1.m_vPos.z) + 50;
    m_PlayerObj_1.SetPosition(m_PlayerObj_1.m_vPos);

    m_Camera.m_vTarget = m_PlayerObj_1.m_vPos;

    float y = m_MapObj.GetHeight(m_Camera.m_vCamera.x, m_Camera.m_vCamera.z);
    m_Camera.m_vCamera = m_PlayerObj_1.m_vPos + m_PlayerObj_1.m_vLook * -1.0f * 5.0f + m_PlayerObj_1.m_vUp * 5.0f;//AVector3(0, 1500.0f, -300.0f);

    ////TVector3 vEye= m_vCamera;
    //AVector3 vTarget(0, 0, 0);
    //vTarget.x = m_Camera.m_vCamera.x;
    //AVector3 vUp(0, 1, 0);

    m_Camera.Frame();
    m_MapObj.Frame();
    m_PlayerObj_1.Frame();
    //m_BackObj.Frame();
    return true;
}

bool ASample::Render()
{
    //m_SkyObj 세팅 및 렌더링
    m_SkyObj.m_matViewSky = m_Camera.m_matView;
    m_SkyObj.m_matViewSky._41 = 0;
    m_SkyObj.m_matViewSky._42 = 0;
    m_SkyObj.m_matViewSky._43 = 0;
    AMatrix matRotation, matScale;
    matScale.Scale(3000.0f, 3000.0f, 3000.0f);
    matRotation.YRotate(g_fGameTimer * 0.00f);

    m_SkyObj.m_matWorld = matScale * matRotation;
    m_SkyObj.SetMatrix(NULL, &m_SkyObj.m_matViewSky, &m_Camera.m_matProj);
    m_pImmediateContext->RSSetState(ADxState::g_pRSNoneCullSolid);
    m_pImmediateContext->PSSetSamplers(0, 1, &ADxState::m_pSSLinear);
    m_pImmediateContext->PSSetSamplers(1, 1, &ADxState::m_pSSPoint);
    m_SkyObj.Render();

    //m_pImmediateContext->PSSetSamplers(0, 1, &ADxState::m_pSSLinear);
    m_pImmediateContext->RSSetState(ADxState::g_pRSBackCullSolid);
    m_MapObj.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
    m_MapObj.Render();

    m_PlayerObj_1.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
    m_PlayerObj_1.Render();

    //m_BackObj.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
    //m_BackObj.Render();

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
    //m_BackObj.Release();

    return true;
}


ASample::ASample() {}
ASample::~ASample() {}
void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

SIMPLE_ARUN();