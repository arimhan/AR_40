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
	ATexture*		m_pLightTex;
	TMatrix			m_matLightView;
	TMatrix			m_matLightProj;
	TMatrix			m_matTex;
	
	//Shadow
	AShader*		m_pProjShadowVShader = nullptr;
	AShader*		m_pProjShadowPShader = nullptr;

	//Map
	ADxRT			m_dxRT;

	//Mapping
	ATexture*		m_pNormalMap;
	
public:
	void			RenderShadow(TMatrix* pMatView, TMatrix* pMatProj);
	void			RenderMRT(ID3D11DeviceContext* pContext);
	void			RenderIntoBuffer(ID3D11DeviceContext* pContext);

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