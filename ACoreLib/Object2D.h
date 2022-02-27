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

	//화면좌표 위치를 중점으로 NDC 변환
	virtual void	Convert(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList);
	virtual void	ConvertIndex(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList);
	//화면좌표계를 NDC로 변환
	virtual void	Convert(vector<ASimplevertex>& list, vector<ASimplevertex>& retList);
	virtual void	ConvertIndex(vector<ASimplevertex>& list, vector<ASimplevertex>& retList);

	virtual bool	SetVertexData() override;
	virtual bool	SetIndexData() override;
	virtual bool	Frame() override;

	AObject2D() {};
	virtual ~AObject2D() {};
};

