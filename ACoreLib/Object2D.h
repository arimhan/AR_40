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
	//ȭ����ǥ ��ġ�� �������� NDC ��ȯ
	virtual void Convert(vector<ASimplevertex>& list, vector<ASimplevertex>& retList);
	//ȭ����ǥ�踦 NDC�� ��ȯ
	virtual bool	SetVertexData() override;

};

