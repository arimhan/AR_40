#pragma once
#include "Object2D.h"

using CollisionFunction = function<void(ABaseObject*, DWORD)>;
using SelectFunction = function<void(ABaseObject*, DWORD)>;

class AObjectMgr : public ASingleton<AObjectMgr>
{
private:
	int m_iExcueteCollisionID;
	map<int, ABaseObject*> m_ObjectList;
	map<int, ABaseObject*> m_SelectList;
public:
	friend ASingleton<AObjectMgr>;
	typedef map<int, CollisionFunction>::iterator FunctionIterator;
	map<int, CollisionFunction> m_fnCollisionExecute;
	typedef map<int, SelectFunction>::iterator FunctionIterator;
	map<int, SelectFunction> m_fnSelectExecute;
public:
	void AddCollisionExecute(ABaseObject* owner, CollisionFunction func);
	void DeleteExecute(ABaseObject* owner);
	bool Init();
	bool Frame();
	bool Release();

	AObjectMgr() { m_iExcueteCollisionID = 0; };
	virtual ~AObjectMgr();
};
#define I_ObjectMgr AObjectMgr::Get()
//인터페이스

