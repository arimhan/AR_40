#pragma once
#include "Core.h"
#include "FbxObj.h"

#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>



class ASample : public ACore
{
	vector<AFbxObj>		m_FbxObj;
	ATexture*			m_pLightTex;
	ATexture*			m_pNormalMap;
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