#include "Sample.h"


bool ASample::Init()
{
    //MAP 만들기
    map.init;
    map.setdevice;
    map.createmap;
    if (!mapobj.create(, 경로설정 map.hlsl, img파일));
    quadtree.카메라설정;
    quadtree.build. (LOD);

    return true;
}

bool ASample::Frame()
{
    return true;
}

bool ASample::Render()
{


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
    return true;
}


ASample::ASample() {}
ASample::~ASample() {}
void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { }

SIMPLE_ARUN();