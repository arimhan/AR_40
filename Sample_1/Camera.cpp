#include "Camera.h"


bool ACamera::Init() 
{
    T::D3DXMatrixLookAtLH(&m_matView, &m_vCamera, &m_vTarget, &m_vUp);
    //m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vUp);
    // Projection
    T::D3DXMatrixPerspectiveFovLH(&m_matProj, XM_PI * 0.25f,
        (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.0f);
    //m_matProj.PerspectiveFovLH(0.1f, 5000.0f, ABASIS_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);
    UpdateVector();
    return true;
}
bool ACamera::Frame()
{
    T::D3DXMatrixLookAtLH(
        &m_matView, &m_vCamera, &m_vTarget, &m_vDefaultUp);
    
    return UpdateVector();
}

bool ACamera::Update(T::TVector4 vDirValue)
{
    T::TMatrix matRot;
    T::D3DXQuaternionRotationYawPitchRoll(
        &m_qRoration, vDirValue.y, vDirValue.x, vDirValue.z);
    //w값을 곱한 뒤, 이후 정규화를 해줄 예정.(?)
    m_vCamera += m_vLook * vDirValue.w;
    m_fRadius += vDirValue.w;

    T::D3DXMatrixAffineTransformation(
        &matRot, 1.0f, NULL, &m_qRoration, &m_vCamera);
    T::D3DXMatrixInverse(&m_matView, NULL, &matRot);

    return UpdateVector();
}
void ACamera::MoveLook(float fValue) { m_vCamera += m_vLook * fValue; }
void ACamera::MoveSide(float fValue) { m_vCamera += m_vRight * fValue; }
void ACamera::MoveUp(float fValue) { m_vCamera += m_vUp * fValue; }
bool ACamera::UpdateVector() 
{
    //카메라 행렬값 세팅
    m_vRight.x = m_matView._11;
    m_vRight.y = m_matView._21;
    m_vRight.z = m_matView._31;

    m_vUp.x = m_matView._12;
    m_vUp.y = m_matView._22;
    m_vUp.z = m_matView._32;

    m_vLook.x = m_matView._13;
    m_vLook.y = m_matView._23;
    m_vLook.z = m_matView._33;

    return true;
}

ACamera::ACamera() 
{
    m_vCamera.x = 0.0f;
    m_vCamera.y = 0.0f;
    m_vCamera.z = 0.0f;
    m_vTarget.x = 0;
    m_vTarget.y = 0;
    m_vTarget.z = 100;
    m_vUp = m_vDefaultUp = T::TVector3(0, 1, 0);
}
ACamera:: ~ACamera() {}