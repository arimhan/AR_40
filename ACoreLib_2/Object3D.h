#pragma once
#include "DxObject.h"

class AObject3D : public ADxObject
{
public:
	T::TVector3			m_vRight;		//X
	T::TVector3			m_vUp;			//Y
	T::TVector3			m_vLook;		//Z

	T::TVector3			m_vPos;
	T::TVector3			m_vDirection;
	T::TVector4			m_vColor;

	T::TMatrix			m_matWorld;

	float				m_fAlpha = 0.0f;
	bool				m_bFadeIn = false;
	bool				m_bFadeOut = false;

	virtual void		FadeIn();
	virtual void		FadeOut();
public:
	virtual void		AddPosition(T::TVector3 vPos);
	virtual void		SetPosition(T::TVector3 vPos);
public:
	virtual bool		SetVertexData() override;
	virtual bool		SetIndexData() override;
	virtual bool		Frame() override;
	bool				Load(ID3D11Device* pd3dDevice, wstring filename);
	virtual void		UpdateData();
	virtual void		SetMatrix(T::TMatrix* matWorld, T::TMatrix* matView, T::TMatrix* matProj);
public:
	virtual void		GenAABB();
public:
	AObject3D();
	virtual ~AObject3D();
};

