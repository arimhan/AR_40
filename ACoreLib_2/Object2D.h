#pragma once
#include "DxObject.h"
class AObject2D : public ADxObject
{
public:
	vector<ASimpleVertex> m_VertexList2D;
	A::AVector2			m_vPos;
	A::AVector2			m_vDirection;
	RECT				m_rtSource;
	RECT				m_rtDraw;	
	A::AVector4			m_vColor;
public:
	float			m_fAlpha = 0.0f;
	bool			m_bFadeIn = false;
	bool			m_bFadeOut = false;
	virtual void    FadeIn();
	virtual void    FadeOut();
public:	
	virtual void		SetRectSource(RECT rt);
	virtual void		SetRectDraw(RECT rt);
	virtual void		AddPosition(A::AVector2 vPos);
	virtual void		SetPosition(A::AVector2 vPos);		
	virtual void		UpdateRectDraw(RECT rt);


	// 화면좌표 위치를 중점으로 NDC 변환
	virtual void	Convert(A::AVector2 center, float fWidth, float fHeight,
		vector<ASimpleVertex>& retList);

	// 화면좌표계를 NDC 변환
	virtual void	Convert(vector<ASimpleVertex>& list,
		vector<ASimpleVertex>& retList);
	virtual void	ConvertIndex(A::AVector2 center, float fWidth, float fHeight,
		vector<ASimpleVertex>& retList);

	// 화면좌표계를 NDC 변환
	virtual void	ConvertIndex(vector<ASimpleVertex>& list,
		vector<ASimpleVertex>& retList);

public:
	virtual bool		SetVertexData() override;
	virtual bool		SetIndexData() override;
	virtual bool		Frame() override;
	bool	Load(ID3D11Device* pd3dDevice, wstring filename) {
		return true;
	};
	virtual void  UpdateData() {}
public:
	AObject2D();
	virtual ~AObject2D();
};

