#include "Camera.h"


bool ACamera::Init() 
{
    m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vUp);
    // Projection
    m_matProj.PerspectiveFovLH(0.1f, 5000.0f, ABASIS_PI * 0.25f, 
        (float)g_rtClient.right / (float)g_rtClient.bottom);

    return true;
}
bool ACamera::Frame()
{
 
    m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vDefaultUp);//m_vUp);

    //카메라 행렬값 세팅
    m_vLight.x = m_matView._11;
    m_vLight.y = m_matView._21;
    m_vLight.z = m_matView._31;

    m_vUp.x = m_matView._12;
    m_vUp.y = m_matView._22;
    m_vUp.z = m_matView._32;

    m_vLook.x = m_matView._13;
    m_vLook.y = m_matView._23;
    m_vLook.z = m_matView._33;

    return true;
}

bool ACamera::Update(AVector4 vValue)
{
    return true;
}
ACamera::ACamera() 
{
    m_vCamera.x = 0.0f;
    m_vCamera.y = 9.0f;
    m_vCamera.z = -15.0f;
    m_vDefaultUp = AVector3(0, 1, 0);
}
ACamera:: ~ACamera() {}