#pragma once
#include "Core.h"
#include "Object3D.h"
//#include "Matrix.h"
//#include "Vector3.h"


class APlaneObj : public AObject3D
{
public:
	//오브젝트 정점을 움직여 카메라가 있는 것 처럼 보여준다.
	//카메라를 X축으로 10 움직임 -> 오브젝트 정점을 X축으로 -10 움직임
	AVector3		m_vCamera;
	AMatrix			m_matWorld;
	AMatrix			m_matView;
	AMatrix			m_matProj;
public:
	virtual bool	SetVertexData() override;
	virtual bool	SetIndexData() override;
	virtual bool	Frame() override;

public:
	APlaneObj();
};


class ASample : public ACore
{
	APlaneObj		m_Obj;
public:
	virtual bool	Init() override;
	virtual bool	Render()override;
	virtual bool	Frame()override;
	virtual bool	Release()override;
};

