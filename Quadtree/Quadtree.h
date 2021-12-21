#pragma once
#include "Node.h"

class AQuadtree
{
public:
	int m_iWidth;
	int m_iHeight;
	int m_iMaxDepth;
	ANode* m_pRootNode;
public:
	vector<ANode*> g_ppArray;
	//ANode** g_ppArray = nullptr;
	queue<ANode*> g_Queue;
	int g_iValue = 0;
public:
	void	Init(int iWidth, int iHeight, int iMaxDepth);
	ANode*	CreateNode(ANode* pParent, float x, float y, float w, float h); 
	void	BuildTree(ANode* pParent);
	bool	AddObject(int fX, int fY);
	ANode*	FindNode(ANode* pNode, int x, int y);
	void	PrintList(ANode* pNode);

	//void CreateBinaryNode(ANode* pNode);
	//void PreOrderPrint(ANode* pNode);
	//void InOrderPrint(ANode* pNode);
	//void PostOrderPrint(ANode* pNode);
	//void LevelOrderPrint(ANode* pNode);
};

