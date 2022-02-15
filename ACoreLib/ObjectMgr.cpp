#include "ObjectMgr.h"

void AObjectMgr::AddCollisionExecute(ABaseObject* owner, CollisionFunction func)
{
	owner->m_iCollisionID = m_iExcueteCollisionID++;
	m_ObjectList.insert(make_pair(owner->m_iCollisionID, owner));
	m_fnCollisionExecute.insert(make_pair(owner->m_iCollisionID, func));
}
void AObjectMgr::DeleteExecute(ABaseObject* owner){	}
bool AObjectMgr::Init()
{
	return true;
}
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
	return true;
}
bool AObjectMgr::Release()
{
	return true;
}
