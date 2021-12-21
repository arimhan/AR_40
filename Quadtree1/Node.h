#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<queue>
#include "Object.h"
using namespace std;
struct ARect
{
	float x1, y1;
	float x2, y2;
	float mx, my;
	float w, h;
};

class ANode
{
public:
	ANode* m_pParent;
	ARect m_rt;
	int m_iDepth;
	ANode* pChild[4];
	list<AObject*> m_ObjList;

	void AddObject(int fX, int fY);
	bool IsRect(int x, int y);

	ANode();
	ANode(float x, float y, float w, float h);
	~ANode();
};

