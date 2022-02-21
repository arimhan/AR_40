#include "ObjectMgr.h"
#include "Input.h"

void AObjectMgr::AddCollisionExecute(ABaseObject* owner, CollisionFunction func)
{
	owner->m_iCollisionID = m_iExcueteCollisionID++;
	m_ObjectList.insert(make_pair(owner->m_iCollisionID, owner));
	m_fnCollisionExecute.insert(make_pair(owner->m_iCollisionID, func));
}
void AObjectMgr::DeleteCollisionExecute(ABaseObject* owner)
{
	map<int, ABaseObject*>::iterator Objiter;
	Objiter = m_ObjectList.find(owner->m_iCollisionID);
	if (Objiter != m_ObjectList.end())
	{
		m_ObjectList.erase(Objiter);
	}
	FunctionIterator colliter = m_fnCollisionExecute.find(owner->m_iCollisionID);
	if (colliter != m_fnCollisionExecute.end())
	{
		m_fnCollisionExecute.erase(colliter);
	}
}		
void AObjectMgr::AddSelectExecute(ABaseObject* owner, CollisionFunction func)
{
	owner->m_iSelectID = m_iExcuteSelectID++;
	m_SelectList.insert(make_pair(owner->m_iSelectID, owner));
	m_fnSelectExecute.insert(make_pair(owner->m_iSelectID, func));
}		
void AObjectMgr::DeleteSelectExecute(ABaseObject* owner)
{
	map<int, ABaseObject*>::iterator Objiter;
	Objiter = m_SelectList.find(owner->m_iCollisionID);
	if (Objiter != m_SelectList.end())
	{
		m_SelectList.erase(Objiter);
	}
	FunctionIterator colliter = m_fnSelectExecute.find(owner->m_iCollisionID);
	if (colliter != m_fnSelectExecute.end())
	{
		m_fnSelectExecute.erase(colliter);
	}
}
bool AObjectMgr::Init() { return true; }
bool AObjectMgr::Frame()
{
	for (auto src : m_ObjectList)
	{
		ABaseObject* pObjSrc = (ABaseObject*)src.second; //map의 두 번째 인자
		if (pObjSrc->m_dwCollisionType == ACollisionType::Ignore) continue;
		DWORD dwState = ACollisionType::Overlap;
		for (auto dest : m_ObjectList)
		{
			ABaseObject* pObjDest = (ABaseObject*)dest.second;
			if (pObjSrc == pObjDest) continue;
			if (ACollision::ToRect(pObjSrc->m_rtCollision, pObjDest->m_rtCollision))
			{
				FunctionIterator colliter = m_fnCollisionExecute.find(pObjSrc->m_iCollisionID);
				if (colliter != m_fnCollisionExecute.end())
				{
					CollisionFunction call = colliter->second;
					call(pObjDest, dwState);
				}
			}
		}
	}
	//마우스 셀렉기능
	for (auto src : m_SelectList)
	{
		ABaseObject* pObjsrc = (ABaseObject*)src.second;
		if (pObjsrc->m_dwSelectType == Ignore) continue;
		DWORD dwState = Overlap;
		if (ACollision::RectToPoint(pObjsrc->m_rtCollision, (float)g_ptMouse.x, (float)g_ptMouse.y))
		{
			DWORD dwKeyState = AInput::Get().m_dwMouseState[0];
			pObjsrc->m_dwSelectState = M_HOVER;
			if (dwKeyState == KEY_PUSH)
			{
				pObjsrc->m_dwSelectState = M_ACTIVE;
			}
			if (dwKeyState == KEY_HOLD)
			{
				pObjsrc->m_dwSelectState = M_FOCUS;
			}
			if (dwKeyState == KEY_UP)
			{
				pObjsrc->m_dwSelectState = M_SELECTED;
			}

			FunctionIterator colliter = m_fnSelectExecute.find(pObjsrc->m_iSelectID);
			if (colliter != m_fnSelectExecute.end())
			{
				CollisionFunction call = colliter->second;
				call(pObjsrc, dwState);
			}
		}
	}
	return true;
}
bool AObjectMgr::Release() { return true; }
