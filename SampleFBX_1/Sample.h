#pragma once
#include "Core.h"
#include "FbxObj.h"
#include "Map.h"
#include "Quadtree.h"
#include "QuadObject.h"
#include "DxRT.h"

#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

class ASampleMap :public AMap
{
public:
	virtual float GetHeight(int index) override
	{
		return AMap::GetHeight(index) * 0.1f;
	}
	virtual ~ASampleMap();
};


class ASample : public ACore
{
	vector<AFbxObj>		m_FbxObj;
	ASampleMap			m_pMapObj;
	AQuadtree			m_QuadTree;
	AQuadObject			m_QuadObj;
	AShader*			m_pShadowPShader = nullptr;

	ATexture*			m_pLightTex;
	ATexture*			m_pNormalMap;
public:
	AShader*			m_pProjShadowVSShader = nullptr;
	AShader*			m_pProjShadowPSShader = nullptr;
	ADxRT				m_dxRT;
	TVector3			m_vLightPos;
	TVector3			m_vLightDir;
	TMatrix				m_matShadow;
	TMatrix				m_matViewLight;
	TMatrix				m_matProjLight;
	TMatrix				m_matTex;
public:
	void				RenderShadow(TMatrix* pmatView, TMatrix* pmatProj);
	bool				LoadMap();
	bool				LoadFbx();

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
	void			DisplayErrorBox(const WCHAR* lpszFunction);

	ASample();
	virtual ~ASample();
};