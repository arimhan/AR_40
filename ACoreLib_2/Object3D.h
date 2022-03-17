#pragma once
#include "DxObject.h"
class AObject3D : public ADxObject
{
public:
	AVector3			m_vPos;
	AVector3			m_vDirection;
	AVector4			m_vColor;
public:
	float			m_fAlpha = 0.0f;
	bool			m_bFadeIn = false;
	bool			m_bFadeOut = false;
	virtual void    FadeIn();
	virtual void    FadeOut();
public:

	virtual void		AddPosition(AVector3 vPos);
	virtual void		SetPosition(AVector3 vPos);

public:
	virtual bool		SetVertexData() override;
	virtual bool		SetIndexData() override;
	virtual bool		Frame() override;
	bool	Load(ID3D11Device* pd3dDevice, wstring filename) {
		return true;
	};
	virtual void  UpdateData() {}
public:
	AObject3D();
	virtual ~AObject3D();
};

