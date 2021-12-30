#pragma once

#include "Node.h"
#include "Collision.h"
#include "Object.h"
#include <queue>

class Octree
{
public:
	Node*				m_RootNode;
	Vector3				m_vSize;
	queue<Node*>		m_Queue;
	Object*				m_Player;
	map<int, Object*>	m_ObjectList;

	bool Init(float fX, float fY, float fZ);
	Node* CreateNode(Node* Parent, Vector3 vPivot, Vector3 vSize);
	int CheckRect(Node* pNode, Object* pObj);
	void Buildtree(Node*);
	bool AddObject(Object* obj);
	Node* FindNode(Node* pNode, Object* pObj);
	void Release();

	void Frame(float time);

	Octree();
	virtual ~Octree();
};

