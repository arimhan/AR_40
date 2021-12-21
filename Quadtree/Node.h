#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include "Object.h"
using namespace std;
//이중포인터, 배열버전

// (x1,y1)			 - w
//
//				-m
//	h -				(x2,y2)  

struct ARect
{
	float x1, y1; //(Rect 시작점)
	float x2, y2; //(Rect 끝점)
	float mx, my;
	float w, h;
};
class ANode
{
public:
	ANode*	m_pParent;
	ARect	m_rt;
	int		m_iDepth;
	ANode*	m_pChildNode[4]; //배열로 선언해야 2, 4, 8진 트리 변형 수월함
	list<AObject*> m_ObjectList;
	void	AddObject(int fX, int fY);
	bool	IsRect(int x, int y);

	ANode();
	ANode(float x, float y, float w, float h);
	~ANode();
};