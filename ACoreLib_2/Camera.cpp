#include "Camera.h"
#include "Input.h"


bool ACamera::Init() 
{
    AFrustum::Init();
    CreateViewMatrix(m_vCamera, m_vTarget, m_vUp);
    CreateProjMatrix(XM_PI * 0.25f, 
        (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.f);
    UpdateVector();

    return true;
}
bool ACamera::Frame()
{
    A::AVector2 dir = AInput::Get().GetDelta();
    if (AInput::Get().GetKey('W')) { MoveLook(g_fSecPerFrame * m_fSpeed); }
    if (AInput::Get().GetKey('S')) { MoveLook(-g_fSecPerFrame * m_fSpeed); }
    if (AInput::Get().GetKey('A')) { MoveSide(-g_fSecPerFrame * m_fSpeed); }
    if (AInput::Get().GetKey('D')) { MoveSide(g_fSecPerFrame * m_fSpeed); }
    //if (m_fSpeed < 100.0f) m_fSpeed = 100.0f;
    Update(A::AVector4(-dir.x, -dir.y, 0, 0));
    
    return true;
}

bool ACamera::Update(A::AVector4 vDirValue)
{
    m_fPitch += vDirValue.x;
    m_fYaw += vDirValue.y;
    m_fRoll += vDirValue.z;

    A::AMatrix matRot;
    A::D3DXQuaternionRotationYawPitchRoll(
        &m_qRoration, m_fYaw, m_fPitch, m_fRoll);
    //w값을 곱한 뒤, 이후 정규화를 해줄 예정.(?)
    m_vCamera += m_vLook * vDirValue.w;
    m_fRadius += vDirValue.w;

    A::D3DXMatrixAffineTransformation(
        &matRot, 1.0f, NULL, &m_qRoration, &m_vCamera);
    A::D3DXMatrixInverse(&m_matView, NULL, &matRot);

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

    CreateFrustum(m_matView, m_matProj);

    return true;
}


void ACamera::CreateViewMatrix(A::AVector3 p, A::AVector3 t, A::AVector3 u)
{
    m_vCamera = p;
    m_vTarget = t;
    m_vUp = u;
    A::D3DXMatrixLookAtLH(&m_matView, &m_vCamera, &m_vTarget, &m_vUp);

    A::AMatrix matInvView;
    D3DXMatrixInverse(&matInvView, NULL, &m_matView);
    A::AVector3* pZBasis = (A::AVector3*)&matInvView._31;
    m_fYaw = atan2f(pZBasis->x, pZBasis->z);
    float fLen = sqrtf(pZBasis->z * pZBasis->z + pZBasis->x * pZBasis->x);
    m_fPitch = -atan2f(pZBasis->y, fLen);

    UpdateVector();
}
void ACamera::CreateProjMatrix(float fovy, float Aspect, float zn, float zf)
{
    m_fFarDistance = zf;
    m_fNearDistance = zn;
    A::D3DXMatrixPerspectiveFovLH(&m_matProj, fovy, Aspect, zn, zf);
}

ACamera::ACamera() 
{
    m_vCamera.x = 0.0f;
    m_vCamera.y = 0.0f;
    m_vCamera.z = 0.0f;
    m_vTarget.x = 0;
    m_vTarget.y = 0;
    m_vTarget.z = 100;
    m_vUp = m_vDefaultUp = A::AVector3(0, 1, 0);
    m_fSpeed = 100.0f;
}
ACamera:: ~ACamera() {}