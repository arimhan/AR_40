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
	T::TQuaternion		m_qRoration;

	T::TVector3			m_vRight;	//X
	T::TVector3			m_vUp;		//Y
	T::TVector3			m_vLook;	//Z

	//ī�޶� ����
	T::TVector3			m_vCamera;
	T::TVector3			m_vTarget;
	T::TVector3			m_vDefaultUp;

	//���
	T::TMatrix			m_matWorld;
	T::TMatrix			m_matView;
	T::TMatrix			m_matProj;

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Update(T::TVector4 vDirValue);
	void			MoveLook(float fValue);
	void			MoveSide(float fValue);
	void			MoveUp(float fValue);
	bool			UpdateVector();
public:
	void	CreateViewMatrix(T::TVector3 p, T::TVector3 t = T::TVector3(0, 0, 0), 
							T::TVector3 u = T::TVector3(0, 1, 0));
	void	CreateProjMatrix(float fovy = XM_PI * 0.25f, float Aspect = 1.44f,
							float zn = 0.1f, float zf = 5000.f);
public:
	ACamera();
	virtual ~ACamera();
};
