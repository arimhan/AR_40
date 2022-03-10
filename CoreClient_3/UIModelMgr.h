#pragma once
#include "BaseMgr.h"
#include "Object2D.h"
#include "SoundMgr.h"

struct AStatePlayData
{
	ATexture* pTex;
	ASound* pSound;
	AStatePlayData(const AStatePlayData& data)
	{
		pTex = data.pTex;
		pSound = data.pSound;
		DisplayText("AStatePlayDataCopy\n");
	}
	AStatePlayData()
	{
		DisplayText("AStatePlayData\n");
	}
	AStatePlayData(ATexture* a, ASound* b)
	{
		pTex = a;
		pSound = b;
		DisplayText("AStatePlayData\n");
	}
};

// 0�� - ����̹��� Ÿ�� -> Red
// 1�� - ��ȭ����(�г�)  -> Green
// 2�� - ��ưŸ��        -> Blue
class AUIModel : public AObject2D
{

public:
	vector<AStatePlayData> m_pStatePlayList;
	RECT	m_rtOffset;
	RECT	m_rtOffsetTex;
public:
	virtual AUIModel*	Clone() {	return nullptr;	};

	virtual void  UpdateData(){}
};
class AUIModelComposed : public AUIModel
{
public:
	list<AUIModel*> m_Components;
public:
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
	virtual void	Add(AUIModel* pObj);
	virtual AUIModel* Clone();
	virtual void  UpdateData();
};
class AUIModelMgr : public ABaseMgr<AUIModel, AUIModelMgr>
{
	friend class ASingleton<AUIModelMgr>;
private:
	AUIModelMgr() {};
public:
	~AUIModelMgr() {};
};
#define I_UI AUIModelMgr::Get()

