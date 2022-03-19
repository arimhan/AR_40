#pragma once
#include "Object3D.h"

class APlaneObj : public AObject3D
{
public:
	//APlaneObj			m_Obj;
	//AMatrix			m_matWorld;
	//AMatrix			m_matView;
	//AMatrix			m_matProj;
public:
	virtual bool	SetVertexData() override;
	virtual bool	SetIndexData() override;

public:
	APlaneObj();
	virtual ~APlaneObj();
};

class PlaneObj
{
};
