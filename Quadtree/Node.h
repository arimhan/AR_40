#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include "Object.h"
using namespace std;
//����������, �迭����

// (x1,y1)			 - w
//
//				-m
//	h -				(x2,y2)  

struct ARect
{
	float x1, y1; //(Rect ������)
	float x2, y2; //(Rect ����)
	float mx, my;
	float w, h;
};
class ANode
{
public:
	ANode*	m_pParent;
	ARect	m_rt;
	int		m_iDepth;
	ANode*	m_pChildNode[4]; //�迭�� �����ؾ� 2, 4, 8�� Ʈ�� ���� ������
	list<AObject*> m_ObjectList;
	void	AddObject(int fX, int fY);
	bool	IsRect(int x, int y);

	ANode();
	ANode(float x, float y, float w, float h);
	~ANode();
};