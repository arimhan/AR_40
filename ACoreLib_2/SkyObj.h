#pragma once
#include "Object3D.h"

class ASkyObj : public AObject3D
{
public:
	//T::TMatrix		m_matViewSky;
	ATexture*		m_pTexArray[6];
	ATexture*		m_pTexCube;
	ComPtr<ID3D11ShaderResourceView>	m_pSRVArray[6];
public:
	virtual void	SetMatrix(A::AMatrix* matWorld, A::AMatrix* matView, A::AMatrix* matProj);
	virtual bool	SetVertexData();
	virtual bool	SetIndexData();
	virtual bool	LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);

	bool			Render();
	bool			PostRender();
public:
	ASkyObj();
	virtual ~ASkyObj();
};

