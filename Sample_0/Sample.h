#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "Camera.h"
//#include "Object3D.h"
//#include "Matrix.h"
//#include "Vector3.h"


class ASample : public ACore
{
	ACamera			m_Camera;
	APlaneObj		m_MapObj;
	APlaneObj		m_PlayerObj_1;
	APlaneObj		m_PlayerObj_2;
	APlaneObj		m_BackObj;

	//APlaneObj		m_Obj;
public:
	virtual bool	Init() override;
	virtual bool	Render()override;
	virtual bool	Frame()override;
	virtual bool	Release()override;
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;

	ASample();
	virtual ~ASample();
};