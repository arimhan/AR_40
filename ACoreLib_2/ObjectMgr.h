#pragma once
#include "Object2D.h"
#include "FbxImporter.h"

using CollisionFunction = function<void(ABaseObject*, DWORD)>;
using SelectFunction = function<void(ABaseObject*, DWORD)>;

class AObjectMgr : public ABaseMgr<AFbxImporter, AObjectMgr>
{
private:
	int			m_iExcueteCollisionID;
	int			m_iExcueteSelectID;
	map<int, ABaseObject*>  m_ObjectList;
	map<int, ABaseObject*>  m_SelectList;
	
public:
	friend ASingleton<AObjectMgr>;

public:	
	typedef map<int, CollisionFunction>::iterator FuncionIterator;
	map<int, CollisionFunction> m_fnCollisionExecute;
	typedef map<int, SelectFunction>::iterator FuncionIterator;
	map<int, SelectFunction> m_fnSelectExecute;

public:
	void  AddCollisionExecute(ABaseObject* owner, CollisionFunction func);
	void  DeleteCollisionExecute(ABaseObject* owner);
	void  AddSelectExecute(ABaseObject* owner, CollisionFunction func);
	void  DeleteSelectExecute(ABaseObject* owner);

	bool  Init();
	bool  Frame();
	bool  Release();
	void  CallRecursive(ABaseObject* pSrcObj, DWORD dwState);
private:
	AObjectMgr();
public:
	virtual ~AObjectMgr();
};
#define I_ObjectMgr   AObjectMgr::Get()
