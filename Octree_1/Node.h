#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<queue>
#include "Object.h"
using namespace std;

class ANode
{
public:
	ANode* m_pParent;
	ABox	m_rt;
	int		m_iDepth;
	int		m_iIndex;

	ANode*	pChild[8];
	list<AObject*>	m_ObjList;
	//list<AObject*> m_DynamicObjList; // µ¿Àû obj
public:
	void AddObject(AObject* obj);

	ANode();
	ANode(float x, float y, float z,float w, float h, float q);
	~ANode();
};

