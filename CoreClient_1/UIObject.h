#pragma once
#include "Object2D.h"
#include "SoundMgr.h"

struct AStatePlayData
{
	ATexture*	pTex;
	ASound*		pSound;
	AStatePlayData(const AStatePlayData& data)
	{
		pTex = data.pTex;
		pSound = data.pSound;
		DisplayText("AStatePlayDataCopy\n");
	}
	AStatePlayData(ATexture* a, ASound* b)
	{
		pTex = a;
		pSound = b;
		DisplayText("AStatePlayDataCopy\n");
	}
	AStatePlayData()
	{
		DisplayText("AStatePlayDataCopy\n");
	}
};

class AUIObject : public AObject2D
{
public:
	vector<AStatePlayData> m_pStatePlayList;
	RECT					m_rtOffset;
	RECT					m_rtOffsetTex;
public:
	bool	Frame()			override;
	bool	Render()		override;
	bool	SetVertexData() override;
	bool	SetIndexData()	override;
	AUIObject()
	{
		m_rtOffsetTex.left = 0;
		m_rtOffsetTex.top = 0;
		m_rtOffsetTex.right = 1;
		m_rtOffsetTex.bottom = 1;
	}
};
class AImageIObject : public AUIObject
{
public:
	bool	Init()		override;
	bool	Frame()		override;
	bool	Render()	override;
};
class AButtonObject : public AUIObject
{
public:
	virtual void HitSelect(ABaseObject* pObj, DWORD dwState) override;
	bool Init()			override;
	bool Frame()		override;
	bool Render()		override;
};

