#pragma once
#include "BaseMgr.h"
#include "Object2D.h"
#include "SoundMgr.h"

struct APlayerStateData
{
	ATexture* m_pTex;
	ASound* m_pSound;
	APlayerStateData(const APlayerStateData& data);
	APlayerStateData(ATexture* ptex, ASound* psound);
	APlayerStateData();
};

//0 - 배경이미지		Red
//1 - 대화상자(패널)	Green
//2 - 버튼			Blue
class AUIModel :public AObject2D
{
public:
	vector<APlayerStateData> m_pPlayerStateList;
	RECT	m_rtOffset;
	RECT	m_rtOffsetTex;
public:
	virtual AUIModel* Clone() { return nullptr; }
	virtual void UpdateData() {}
};
class AUIModelComposed : public AUIModel
{
public:
	list<AUIModel*> m_Components;
public:
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
	virtual bool	Add(AUIModel* pObj);
	virtual AUIModel* Clone();
	virtual void	UpdateData();
};

class AUIMgr : public ABaseMgr<AUIModel, AUIMgr>
{
	friend class ASingleton<AUIMgr>;
private:
	AUIMgr() {};
public:
	~AUIMgr() {};
};
#define I_UI AUIMgr::Get()

