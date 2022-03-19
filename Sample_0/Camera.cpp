#include "Camera.h"


bool ACamera::Init() 
{
    m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vUp);
    // Projection
    m_matProj.PerspectiveFovLH(1.0f, 100.0f, ABASIS_PI * 0.25f, 
        (float)g_rtClient.right / (float)g_rtClient.bottom);

    return true;
}
bool ACamera::Frame() 
{
    m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vUp);
    return true;
}
ACamera::ACamera() 
{
    m_vCamera.x = 0.0f;
    m_vCamera.y = 5.0f;
    m_vCamera.z = -5.0f;
}
ACamera:: ~ACamera() {}