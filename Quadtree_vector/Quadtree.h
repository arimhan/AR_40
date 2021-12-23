#pragma once
#include "Node.h"
class AQuadtree
{
public:
	int m_iWidth;
	int m_iHeight;
	int m_iMaxDepth;
	ANode* m_pRootNode;

	vector<ANode*> g_ppArray;
	queue<ANode*> g_Queue;
	int g_iValue = 0;

	void Init(int iWidth, int iHeight, int iMaxDepth);
	ANode* CreateNode(ANode* pParenct, float x, float y, float w, float h);
	void BuildTree(ANode* pParent);
	bool AddObject(int fX, int fY);
	ANode* FindNode(ANode* pNode, int x, int y);
	void PrintList(ANode* pNode);
};

