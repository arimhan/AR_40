#include "Sample.h"
//#include "Object3D.h"


bool ASample::Init()
{
    //ī�޶� ���
    m_Camera.Init();

    ATexture* pTex = I_Texture.Load(L"../../data/ui/save_0000_O-K.png");
    AShader* pVSShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"Box.hlsl", "VS");
    AShader* pPSShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"Box.hlsl", "PS");

    //Map Obj �ҷ�����
    m_MapObj.Init();
    m_MapObj.m_pColorTex = pTex;
    m_MapObj.m_pVSShader = pVSShader;
    m_MapObj.m_pPSShader = pPSShader;
    //���� Obj X�� ȸ������ �ٴڿ� ���
    AMatrix matRotate, matScale; //matTrans;
    matRotate.XRotate(DegreeToRadian(90)); //X������ 90�� ����
    matScale.Scale(10, 10.0f, 10.0f);
    m_MapObj.m_matWorld = matScale * matRotate; // SRT������
    if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }

    //Map Obj������ �����̴� PlayerObj �ҷ�����
    m_PlayerObj_1.Init();
    m_PlayerObj_1.m_pColorTex = pTex;
    m_PlayerObj_1.m_pVSShader = pVSShader;
    m_PlayerObj_1.m_pPSShader = pPSShader;
    m_PlayerObj_1.SetPosition(AVector3(0.0f, 1.0f, 0.0f));
    if (!m_PlayerObj_1.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }

    //Z���۸� ���� Obj ���
    m_BackObj.Init();
    m_BackObj.m_pColorTex = I_Texture.Load(L"../../data/ui/_exit_lg.bmp");
    m_BackObj.m_pVSShader = pVSShader;
    m_BackObj.m_pPSShader = pPSShader;
    m_BackObj.SetPosition(AVector3(0.0f, 1.0f, 0.0f));
    if (!m_BackObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get())) { return false; }
    m_BackObj.m_matWorld.Translation(1.0f, 0.0f, 0.0f);

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
    //Ű ����
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
    m_PlayerObj_1.Frame();
    //m_BackObj.Frame();
    return true;
}

bool ASample::Render()
{
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
    m_MapObj.Release();
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