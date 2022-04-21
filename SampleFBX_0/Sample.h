#pragma once
#include "Core.h"
#include "FbxLoader.h"

class ASample : public ACore
{
	AFbxLoader		m_FbxObj;
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