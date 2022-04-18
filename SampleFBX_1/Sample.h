#pragma once
#include "Core.h"
#include "FbxObj.h"
#include "Map.h"
#include "Quadtree.h"
#include "QuadObject.h"

#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

class ASampleMap :public AMap
{
public:
	virtual float GetHeight(int index) override;
	virtual ~ASampleMap();
};


class ASample : public ACore
{
	vector<AFbxObj>		m_FbxObj;
	ATexture*			m_pLightTex;
	ATexture*			m_pNormalMap;
	ASampleMap			m_pMapObj;
	AQuadtree			m_QuadTree;
	AQuadObject			m_QuadObj;
public:
	virtual bool	Init() override;
	virtual bool	Render()override;
	virtual bool	Frame()override;
	virtual bool	Release()override;
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
public:
	void			RenderIntoBuffer(ID3D11DeviceContext* pContext);
	void			RenderMTR(ID3D11DeviceContext* pContext);

	ASample();
	virtual ~ASample();
};