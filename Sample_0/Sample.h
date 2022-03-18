#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "Camera.h"

//#include "Matrix.h"
//#include "Vector3.h"


class ASample : public ACore
{
	ACamera			m_Camera;
	APlaneObj		m_MapObj;
	APlaneObj		m_PlayerObj_1;
	APlaneObj		m_PlayerObj_2;

public:
	virtual bool	Init() override;
	virtual bool	Render()override;
	virtual bool	Frame()override;
	virtual bool	Release()override;

	ASample();
	virtual ~ASample();
};

