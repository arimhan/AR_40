#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "Camera.h"
#include "Map.h"
#include "SkyObj.h"
#include "BoxObj.h"


class ASample : public ACore
{
	ACamera			m_Camera;
	AMap			m_MapObj;
	ABoxObj			m_PlayerObj_1;
	APlaneObj		m_PlayerObj_2;
	APlaneObj		m_BackObj;
	ASkyObj			m_SkyObj;

public:
	virtual bool	Init() override;
	virtual bool	Render()override;
	virtual bool	Frame()override;
	virtual bool	Release()override;
	//virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	//virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;

	ASample();
	virtual ~ASample();
};