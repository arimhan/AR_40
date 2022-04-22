#pragma once
//Library
#include "Core.h"

//FBX
#include "FbxObj.h"

//MAP
#include "Map.h"
#include "Quadtree.h"
#include "QuadObject.h"
#include "DxRT.h"

class ASampleMap : public AMap
{
public:
	virtual float	GetHeight(int index) override
	{
		return AMap::GetHeight(index) * 0.1f;
	}
	virtual ~ASampleMap() {}
};

class ASample : public ACore
{
	ASampleMap		m_MapObj;
	AQuadtree		m_QuadTree;
	vector<AFbxObj>	m_FbxObj;
	AQuadObject		m_QuadObj;

public:
	//Light
	TVector3		m_vLightPos;
	TVector3		m_vLightDir;
	TMatrix			m_matLightView;
	TMatrix			m_matLightProj;
	
	//Shadow
	AShader*		m_pProjShadowVShader = nullptr;
	AShader*		m_pProjShadowPShader = nullptr;

	//Map
	ADxRT			m_dxRT;
	
public:
	void			RenderShadow(TMatrix* pMatView, TMatrix* pMatProj);

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