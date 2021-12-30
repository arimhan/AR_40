#pragma once
#include "Node.h"
class AOctree
{
public:
	int m_iSizeX;
	int m_iSizeY;
	int m_iSizeZ;
	int m_iMaxDepth;
	static int g_iCount;
	AVector3 m_vSize;
	ANode* m_pRootNode;

	vector<ANode*> g_ppArray;
	queue<ANode*> g_Queue;
	int g_iValue = 0;

	void Init(int iXSize, int iYSize, int iZSize, int iMaxDepth);
	ANode* CreateNode(ANode* pParenct, float x, float y, float z, float w, float h, float q);
	void BuildTree(ANode* pParent);
	bool AddObject(AObject* obj);
	ANode* FindNode(ANode* pNode, ABox rt);
	void PrintObjList(ANode* pNode);
};

