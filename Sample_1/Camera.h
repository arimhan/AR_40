#pragma once
#include "Std.h"

class ACamera
{
public:
	//오브젝트 정점을 움직여 카메라가 있는 것 처럼 보여준다.
	//카메라를 X축으로 10 움직임 -> 오브젝트 정점을 X축으로 -10 움직임

	float				m_fRadius = 10.0f;
	T::TQuaternion		m_qRoration;

	T::TVector3			m_vRight;	//X
	T::TVector3			m_vUp;		//Y
	T::TVector3			m_vLook;	//Z

	//카메라 벡터
	T::TVector3			m_vCamera;
	T::TVector3			m_vTarget;
	T::TVector3			m_vDefaultUp;

	//행렬
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
