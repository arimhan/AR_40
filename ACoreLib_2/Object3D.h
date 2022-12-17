#pragma once
#include "DxObject.h"

class AObject3D : public ADxObject
{
public:
	A::AVector3			m_vRight;		//X
	A::AVector3			m_vUp;			//Y
	A::AVector3			m_vLook;		//Z

	A::AVector3			m_vPos;
	A::AVector3			m_vDirection;
	A::AVector4			m_vColor;

	A::AMatrix			m_matWorld;
	A::AMatrix			m_matView;
	A::AMatrix			m_matProj;

	float				m_fAlpha = 0.0f;
	bool				m_bFadeIn = false;
	bool				m_bFadeOut = false;

	virtual void		FadeIn();
	virtual void		FadeOut();
public:
	virtual void		AddPosition(A::AVector3 vPos);
	virtual void		SetPosition(A::AVector3 vPos);
public:
	virtual bool		SetVertexData() override;
	virtual bool		SetIndexData() override;
	virtual bool		Frame() override;
	bool				Load(ID3D11Device* pd3dDevice, wstring filename);
	virtual void		UpdateData();
	virtual void		SeAMatrix(A::AMatrix* matWorld, A::AMatrix* matView, A::AMatrix* matProj);
public:
	virtual void		UpdateCollision();
	virtual void		GenAABB();
public:
	AObject3D();
	virtual ~AObject3D();
};

