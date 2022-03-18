#pragma once
#include "Core.h"
#include "Object3D.h"
//#include "Matrix.h"
//#include "Vector3.h"


class APlaneObj : public AObject3D
{
public:
	//������Ʈ ������ ������ ī�޶� �ִ� �� ó�� �����ش�.
	//ī�޶� X������ 10 ������ -> ������Ʈ ������ X������ -10 ������
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

