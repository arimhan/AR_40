#include "Sample.h"
//#include "Object3D.h"

//#define DegreeToRadian(degree)((degree)*(ABASIS_PI/180.0f))


bool ASample::Init()
{
    //카메라 기능
    m_Camera.Init();


    ATexture* pTex = I_Texture.Load(L"../../data/ui/save_0000_O-K.png");
    AShader* pVSShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    AShader* pPSShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PS");

    //지형 Obj X축 회전으로 바닥에 깔기
    m_MapObj.Init();
    m_MapObj.m_pColorTex = pTex;
    m_MapObj.m_pVSShader = pVSShader;
    m_MapObj.m_pPSShader = pPSShader;

    AMatrix matRotate, matScale; //matTrans;
    matRotate.XRotate(DegreeToRadian(90)); //X축으로 90도 눕기
    matScale.Scale(10, 10.0f, 10.0f);
    m_MapObj.m_matWorld = matScale * matRotate; // SRT순으로
    if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }

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
        m_Camera.m_vCamera.z += g_fSecPerFrame * 1.0f;
    }
    if (AInput::Get().GetKey('S'))
    {
        m_Camera.m_vCamera.z -= g_fSecPerFrame * 1.0f;
    }
    if (AInput::Get().GetKey('A'))
    {
        m_Camera.m_vCamera.x -= g_fSecPerFrame * 1.0f;
    }
    if (AInput::Get().GetKey('D'))
    {
        m_Camera.m_vCamera.x += g_fSecPerFrame * 1.0f;
    }
    m_Camera.m_vTarget = m_MapObj.m_vPos;
    m_Camera.m_vCamera = m_MapObj.m_vPos + AVector3(0, 5.0f, -3.0f);

    ////TVector3 vEye= m_vCamera;
    //AVector3 vTarget(0, 0, 0);
    //vTarget.x = m_Camera.m_vCamera.x;
    //AVector3 vUp(0, 1, 0);

    m_Camera.Frame();
    m_MapObj.Frame();
    return true;
}
bool ASample::Render()
{
    //m_Obj.Render();
    m_MapObj.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
    m_MapObj.Render();

    wstring msg = L"[FPS: ";
    msg += to_wstring(m_GameTimer.m_iFPS);
    msg += L"   GT: ";
    msg += L" ]";
    msg += to_wstring(m_GameTimer.m_fTimer);
    m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(1, 1, 1, 1));

    return true;
}


bool ASample::Release()
{
    m_MapObj.Release();
    return true;
}


ASample::ASample() {}
ASample::~ASample() {}

SIMPLE_ARUN();