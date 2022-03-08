#pragma once
//UI와 Object 구분하여 작업
#include "ObjectMgr.h"
#include "UIMgr.h"
//#include "SoundMgr.h"
//#include "World.h"

class AUI : public AUIModel
{
	AUIModel* Clone()
	{
		AUIModel* pCopy = new AUI(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		return pCopy;
	}
	void UpdateData() override;
public:
	bool	Frame()		override;
	bool	Render()	override;
	bool	SetVertexData() override;
	bool	SetIndexData() override;
	void	HitSelect(ABaseObject* pObj, DWORD dwState) override;
	AUI()
	{
		m_rtOffsetTex.left = 0;
		m_rtOffsetTex.right = 1;
		m_rtOffsetTex.top = 0;
		m_rtOffsetTex.bottom = 1;
	}
};

class AImgObject : public AUI
{
	AUIModel* Clone()
	{
		AUIModel* pCopy = new AImgObject(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		return pCopy;
	}
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	void HitSelect(ABaseObject* pObj, DWORD dwState); // override;
};

class AButton : public AUI
{

};
class AListObj : public AUIModelComposed
{
public:
	AUIModel* Clone()
	{
		AUIModelComposed* pModel = new AListObj;
		list<AUIModel*>::iterator iter;
		for (iter = m_Components.begin(); iter != m_Components.end(); iter++)
		{
			pModel->Add((*iter)->Clone());
		}
		return pModel;
	}
public:
	bool Create(int xCount, int yCount);
	void UpdateData() override;
	virtual void HitSelect(ABaseObject* pObj, DWORD dwState) override;
	AListObj() {};
	virtual ~AListObj() {};
};