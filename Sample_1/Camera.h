#pragma once
#include "Std.h"

class ACamera
{
public:
	//������Ʈ ������ ������ ī�޶� �ִ� �� ó�� �����ش�.
	//ī�޶� X������ 10 ������ -> ������Ʈ ������ X������ -10 ������

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
	ACamera();
	virtual ~ACamera();
};
