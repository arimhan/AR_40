#pragma once
#include "Object3D.h"
#define Tex_Size	6

class ASkyObj : public AObject3D
{
public:
	AMatrix			m_matViewSky;
	ATexture*		m_pTexArray[Tex_Size];
	ATexture*		m_pTexCube;
	ComPtr<ID3D11ShaderResourceView>	m_pSRVArray[Tex_Size];
public:
	virtual bool	SetVertexData();
	virtual bool	SetIndexData();
	virtual bool	LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
	bool			PostRender();
public:
	ASkyObj();
	virtual ~ASkyObj();
};

