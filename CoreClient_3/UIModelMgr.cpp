#include "UIModelMgr.h"
#include "ObjectMgr.h"
bool AUIModelComposed::Frame()
{
	std::list<AUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{
		(*iter)->Frame();
	}
	return true;
}
bool AUIModelComposed::Render()
{
	std::list<AUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{
		(*iter)->Render();
	}
	return true;
}
bool AUIModelComposed::Release()
{
	std::list<AUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{
		(*iter)->Release();
	}
	return true;
}
void AUIModelComposed::Add(AUIModel* pObj)
{
	_ASSERT(pObj);
	pObj->m_pParent = this;
	m_Components.push_back(pObj);
}
AUIModel* AUIModelComposed::Clone()
{
	AUIModelComposed* pModel = new AUIModelComposed;
	std::list<AUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{
		pModel->Add((*iter)->Clone());
	}
	return pModel;
};
void  AUIModelComposed::UpdateData()
{
	std::list<AUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{		
		(*iter)->UpdateData();
		(*iter)->SetCollisionType(ACollisionType::Ignore,
			ASelectType::Select_Overlap);
	}
}