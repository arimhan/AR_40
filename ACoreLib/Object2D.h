#pragma once
#include "DxObject.h"
class AObject2D :public ADxObject
{
public:
	RECT	m_rtSource;
	RECT	m_rtDraw;

	virtual void	SetRectSource(RECT rt);
	virtual void	SetRectDraw(RECT rt);
	virtual void	AddPosition(AVector2 vPos);
	virtual void	SetPosition(AVector2 vPos);
	virtual void	UpDateRectDraw(RECT rt);

	virtual void Convert(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList);
	//화면좌표 위치를 중점으로 NDC 변환
	virtual void Convert(vector<ASimplevertex>& list, vector<ASimplevertex>& retList);
	//화면좌표계를 NDC로 변환
	virtual bool	SetVertexData() override;

};

