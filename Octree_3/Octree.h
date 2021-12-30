#pragma once

#include "Node.h"
#include "Collision.h"
#include "Object.h"
#include <queue>

class AOctree
{
public:
	ANode*				m_RootNode;
	AVector3			m_vSize;
	queue<ANode*>		m_Queue;
	AObject*			m_Player;
	map<int, AObject*>	m_ObjectList;

	bool				Init(float fX, float fY, float fZ);
	ANode*				CreateNode(ANode* Parent, AVector3 vPivot, AVector3 vSize);
	int					CheckRect(ANode* pNode, AObject* pObj);
	void				Buildtree(ANode*);
	bool				AddObject(AObject* obj);
	ANode*				FindNode(ANode* pNode, AObject* pObj);
	void				Release();

	void				Frame(float time);

	AOctree();
	virtual ~AOctree();
};

