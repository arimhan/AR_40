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
	AVector2 p1;
	AVector2 p2;
	AVector2 middle;
	AVector2 size;
	/*float p1, p1;
	float p2, p2;
	float size, my;
	float w, h;*/
};

class ANode
{
public:
	ANode* m_pParent;
	ARect m_rt;
	int m_iDepth;
	ANode* pChild[4];
	list<AObject*> m_ObjList;

	void AddObject(int x, int y);
	bool IsRect(int x, int y);

	ANode();
	ANode(float x, float y, float w, float h);
	~ANode();
};

