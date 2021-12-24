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
	ARect m_rt;
	int m_iDepth;
	ANode* pChild[4];
	list<AObject*> m_ObjList;
public:
	void AddObject(AObject* obj);

	ANode();
	ANode(float x, float y, float w, float h);
	~ANode();
};

