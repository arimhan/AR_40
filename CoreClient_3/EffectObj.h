#pragma once
#include "Object2D.h"
#include "Sprite.h"

class AEffectObj : public AObject2D
{
public:
	ASprite*		m_pSprite;
	int				m_iCurrentIndex = 0;
	float			m_fChangeTime;// = m_pSprite->m_fAnimTime / m_pSprite->m_rtArray.size();
	float			m_fTimer = 0.0f;

public:
	virtual void	HitSelect(ABaseObject* pObj, DWORD dwState) override;
	virtual void	Reset();
	virtual bool	Init() override;
	virtual bool	Frame()override;
	virtual bool	Render()override;
	virtual bool	Release()override;
};

