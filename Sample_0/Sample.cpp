#include "Sample.h"


bool APlaneObj::SetVertexData()
{
    m_VertexList.resize(4);
    // -Z plane
    m_VertexList[0].p = AVector3(-1.0f, 1.0f, 0.5f);
    m_VertexList[0].n = AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[0].c = AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[0].t = AVector2(0.0f, 0.0f);

    m_VertexList[1].p = AVector3(1.0f, 1.0f, 0.5f);
    m_VertexList[1].n = AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[1].c = AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[1].t = AVector2(1.0f, 0.0f);


    m_VertexList[2].p = AVector3(-1.0f, -1.0f, 0.5f);
    m_VertexList[2].n = AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[2].c = AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[2].t = AVector2(0.0f, 1.0f);


    m_VertexList[3].p = AVector3(1.0f, -1.0f, 0.5f);
    m_VertexList[3].n = AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[3].c = AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[3].t = AVector2(1.0f, 1.0f);
    return true;
}
bool APlaneObj::SetIndexData()
{
    m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
    m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
    return true;
}
bool ASample::Frame()
{

    return true;
}

bool ASample::Init()
{
    return true;
}
bool ASample::Render()
{
    //m_Obj.Render();

    wstring msg = L"FPS: ";
    msg += to_wstring(m_GameTimer.m_iFPS);
    msg += L"   GT: ";
    msg += to_wstring(m_GameTimer.m_fTimer);
    m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(1, 1, 1, 1));

    return true;
}
bool APlaneObj::Frame()
{
    //m_Obj.Frame();
            // world
    AMatrix matRotate, matScale, matTrans;
    matRotate.ZRotate(g_fGameTimer);
    matScale.Scale(cos(g_fGameTimer) * 0.5f + 0.5f, 1.0f, 1.0f);
    matTrans.Translation(0,
        cos(g_fGameTimer) * 0.5f + 0.5f, 0);
    //m_matWorld = matRotate;
    m_matWorld.Transpose();
    // view
    if (AInput::Get().GetKey(VK_LEFT))
    {
        m_vCamera.x -= g_fSecPerFrame * 1.0f;
    }
    if (AInput::Get().GetKey(VK_RIGHT))
    {
        m_vCamera.x += g_fSecPerFrame * 1.0f;
    }
    //TVector3 vEye= m_vCamera;
    AVector3 vTarget(0, 0, 0);
    vTarget.x = m_vCamera.x;
    AVector3 vUp(0, 1, 0);
    m_matView.CreateViewLook(m_vCamera, vTarget, vUp);
    m_matView.Transpose();
    // Projection
    m_matProj.PerspectiveFovLH(
        1.0f, 100.0f, ABASIS_PI * 0.5f, 800.0f / 600.0f);
    m_matProj.Transpose();


    m_ConstantList.matWorld = m_matWorld;// matScale* matRotate* matTrans;
    m_ConstantList.matView = m_matView;
    m_ConstantList.matProj = m_matProj;


    if (m_pContext != nullptr)
    {
        m_pContext->UpdateSubresource(
            m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);
    }
    return true;
}

bool ASample::Release()
{
    m_Obj.Release();
    return true;
}


APlaneObj::APlaneObj()
{
    
}