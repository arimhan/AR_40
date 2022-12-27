#pragma once
#include "Frustum.h"

class ACamera	:public AFrustum
{
public:
	//������Ʈ ������ ������ ī�޶� �ִ� �� ó�� �����ش�.
	//ī�޶� X������ 10 ������ -> ������Ʈ ������ X������ -10 ������

	float				m_fNearDistance = 0.01f;
	float				m_fFarDistance = 1000.0f;

	float				m_fPitch = 0.0f;
	float				m_fYaw = 0.0f;
	float				m_fRoll = 0.0f;
	float				m_fRadius = 10.0f;

	A::AQuaternion		m_qRoration;
	A::AVector3			m_vRight;	//X
	A::AVector3			m_vUp;		//Y
	A::AVector3			m_vLook;	//Z

	//ī�޶� ����
	A::AVector3			m_vCamera;
	A::AVector3			m_vTarget;
	A::AVector3			m_vDefaultUp;

	//���
	A::AMatrix			m_matWorld;
	A::AMatrix			m_matView;
	A::AMatrix			m_matProj;

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Update(A::AVector4 vDirValue);
	void			MoveLook(float fValue);
	void			MoveSide(float fValue);
	void			MoveUp(float fValue);
	bool			UpdateVector();
public:
	void	CreateViewMatrix(A::AVector3 p, A::AVector3 t = A::AVector3(0, 0, 0),
								A::AVector3 u = A::AVector3(0, 1, 0));
	void	CreateProjMatrix(float fovy = XM_PI * 0.25f, float Aspect = 1.44f,
							float zn = 0.1f, float zf = 5000.f);
public:
	ACamera();
	virtual ~ACamera();
};
