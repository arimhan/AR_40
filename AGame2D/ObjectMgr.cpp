#include "ObjectMgr.h"
#include "Input.h"

void  AObjectMgr::AddCollisionExecute(ABaseObject* owner, CollisionFunction func)
{
	owner->m_iCollisionID = m_iExcueteCollisionID++;
	m_ObjectList.insert(make_pair(owner->m_iCollisionID, owner));
	m_fnCollisionExecute.insert(std::make_pair(owner->m_iCollisionID, func));
}
void  AObjectMgr::DeleteCollisionExecute(ABaseObject* owner)
{
	map<int, ABaseObject*>::iterator objiter;
	objiter = m_ObjectList.find(owner->m_iCollisionID);
	if (objiter != m_ObjectList.end())
	{
		m_ObjectList.erase(objiter);
	}

	FuncionIterator colliter = m_fnCollisionExecute.find(owner->m_iCollisionID);
	if (colliter != m_fnCollisionExecute.end())
	{
		m_fnCollisionExecute.erase(colliter);
	}
}
void  AObjectMgr::AddSelectExecute(ABaseObject* owner, CollisionFunction func)
{
	owner->m_iSelectID = m_iExcueteSelectID++;
	m_SelectList.insert(make_pair(owner->m_iSelectID, owner));
	m_fnSelectExecute.insert(std::make_pair(owner->m_iSelectID, func));
}
void  AObjectMgr::DeleteSelectExecute(ABaseObject* owner)
{
	std::map<int, ABaseObject*>::iterator objiter;
	objiter = m_SelectList.find(owner->m_iCollisionID);
	if (objiter != m_SelectList.end())
	{
		m_SelectList.erase(objiter);
	}

	FuncionIterator colliter = m_fnSelectExecute.find(owner->m_iCollisionID);
	if (colliter != m_fnSelectExecute.end())
	{
		m_fnSelectExecute.erase(colliter);
	}
}
bool  AObjectMgr::Init()
{
	return true;
}
void  AObjectMgr::CallRecursive(ABaseObject* pSrcObj,DWORD dwState)
{
	if (pSrcObj->m_pParent == nullptr)
	{		
		return;
	}
	CallRecursive(pSrcObj->m_pParent, dwState);
	pSrcObj->HitSelect(pSrcObj, dwState);
}
bool  AObjectMgr::Frame()
{
	// Object
	for (auto src : m_ObjectList)
	{
		ABaseObject* pObjSrc = (ABaseObject*)src.second;
		if (pObjSrc->m_dwCollisionType == ACollisionType::Ignore) continue;
		DWORD dwState= ACollisionType::Overlap;
		for (auto dest : m_ObjectList)
		{
			ABaseObject* pObjDest = (ABaseObject*)dest.second;
			if (pObjSrc == pObjDest) continue;
			if (ACollision::ToRect(pObjSrc->m_rtCollision, pObjDest->m_rtCollision))
			{
				FuncionIterator colliter = m_fnCollisionExecute.find(pObjSrc->m_iCollisionID);
				if (colliter != m_fnCollisionExecute.end())
				{
					CollisionFunction call = colliter->second;
					call(pObjDest, dwState);
				}
			}
		}
	}

	// 마우스 선택 관련
	for (auto src : m_SelectList)
	{
		ABaseObject* pObjSrc = (ABaseObject*)src.second;
		//if (pObjSrc->m_dwSelectType == TSelectType::Select_Ignore) continue;
		DWORD dwState = ASelectState::M_DEFAULT;

		if (pObjSrc->m_dwSelectType != ASelectType::Select_Ignore &&
			ACollision::RectToPoint(pObjSrc->m_rtCollision, (float)g_ptMouse.x, (float)g_ptMouse.y))
		{
			DWORD dwKeyState = AInput::Get().m_dwMouseState[0];
			pObjSrc->m_dwSelectState = ASelectState::M_HOVER;
			if (dwKeyState == KEY_PUSH)
			{
				pObjSrc->m_dwSelectState = ASelectState::M_ACTIVE;
			}
			if (dwKeyState == KEY_HOLD)
			{
				pObjSrc->m_dwSelectState = ASelectState::M_FOCUS;
			}
			if (dwKeyState == KEY_UP)
			{
				pObjSrc->m_dwSelectState = ASelectState::M_SELECTED;
			}

			CallRecursive(pObjSrc, dwState);
			FuncionIterator colliter = m_fnSelectExecute.find(pObjSrc->m_iSelectID);
			if (colliter != m_fnSelectExecute.end())
			{			
				CollisionFunction call = colliter->second;
				call(pObjSrc, dwState);					
			}
		}
		else
		{
			if (pObjSrc->m_dwSelectState != ASelectState::M_DEFAULT)
			{
				pObjSrc->m_dwSelectState = ASelectState::M_DEFAULT;
				FuncionIterator colliter = m_fnSelectExecute.find(pObjSrc->m_iSelectID);
				if (colliter != m_fnSelectExecute.end())
				{
					CollisionFunction call = colliter->second;
					call(pObjSrc, dwState);
				}
			}
		}		
	}	
	return true;
}
bool  AObjectMgr::Release()
{
	m_ObjectList.clear();
	m_SelectList.clear();
	return true;
}

AObjectMgr::AObjectMgr()
{
	m_iExcueteCollisionID = 0;
	m_iExcueteSelectID = 0;
};
AObjectMgr::~AObjectMgr() { Release(); };
