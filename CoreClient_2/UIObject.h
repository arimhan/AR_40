#pragma once
#include "ObjectMgr.h"
#include "UIModelMgr.h"

class AUIObject : public AUIModel
{
public:
	AUIModel* Clone()
	{
		AUIModel* pCopy = new AUIObject(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		return pCopy;
	};
	void  UpdateData() override
	{
		m_rtCollision = ARect(m_vPos, m_fWidth, m_fHeight);
		SetCollisionType(ACollisionType::Ignore,
			ASelectType::Select_Overlap);
		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&ABaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&ABaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}

public:
	bool	Frame()			override;
	bool	Render()		override;
	bool	SetVertexData() override;
	bool	SetIndexData()	override;
	void HitSelect(ABaseObject* pObj, DWORD dwState) override { int C = 0; }
	AUIObject()
	{
		m_rtOffsetTex.left = 0;
		m_rtOffsetTex.top = 0;
		m_rtOffsetTex.right = 1;
		m_rtOffsetTex.bottom = 1;
	}
};
class AImageObject : public AUIObject
{
	AUIModel* Clone()
	{
		AUIModel* pCopy = new AImageObject(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		return pCopy;
	};
public:
	bool	Init()		override;
	bool	Frame()		override;
	bool	Render()	override;
	virtual void HitSelect(ABaseObject* pObj, DWORD dwState) override { int H = 0; }

};
class AButtonObject : public AUIObject
{
public:
	AUIModel* Clone()
	{
		AUIModel* pCopy = new AButtonObject(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		return pCopy;
	};
public:
	virtual void HitSelect(ABaseObject* pObj, DWORD dwState) override;
	bool Init()			override;
	bool Frame()		override;
	bool Render()		override;
	AButtonObject() {}
	virtual ~AButtonObject() {}
};

class AListCtrlObject : public AUIModelComposed
{
public:
	AUIModel* Clone()
	{
		AUIModelComposed* pModel = new AListCtrlObject;
		std::list<AUIModel*>::iterator iter;
		for (iter = m_Components.begin(); iter != m_Components.end();
			iter++)
		{
			pModel->Add((*iter)->Clone());
		}
		return pModel;
	};
	bool   Create(int xCount, int yCount);
	void  UpdateData() override
	{
		m_rtCollision = ARect(m_vPos, m_fWidth, m_fHeight);
		SetCollisionType(ACollisionType::Ignore,
			ASelectType::Select_Overlap);

		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&ABaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&ABaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}
	virtual void HitSelect(ABaseObject* pObj, DWORD dwState) override;
public:
	AListCtrlObject() {}
	virtual ~AListCtrlObject() {}
};