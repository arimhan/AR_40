#pragma once
#include "DxObject.h"
class AObject2D :public ADxObject
{
public:
	RECT			m_rtSource;
	RECT			m_rtDraw;
	AVector4		m_vColor;	
public:
	float			m_fAlpha = 0.0f;
	bool			m_bFadeIn = false;
	bool			m_bFadeOut = false;
	virtual void	FadeIn();
	virtual void	FadeOut();
public:
	virtual void	SetRectSource(RECT rt);
	virtual void	SetRectDraw(RECT rt);
	virtual void	AddPosition(AVector2 vPos);
	virtual void	SetPosition(AVector2 vPos);
	virtual void	UpDateRectDraw(RECT rt);

	//ȭ����ǥ ��ġ�� �������� NDC ��ȯ
	virtual void	Convert(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList);
	virtual void	ConvertIndex(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList);
	//ȭ����ǥ�踦 NDC�� ��ȯ
	virtual void	Convert(vector<ASimplevertex>& list, vector<ASimplevertex>& retList);
	virtual void	ConvertIndex(vector<ASimplevertex>& list, vector<ASimplevertex>& retList);

	virtual bool	SetVertexData() override;
	virtual bool	SetIndexData() override;
	virtual bool	Frame() override;

	AObject2D() {};
	virtual ~AObject2D() {};
};

