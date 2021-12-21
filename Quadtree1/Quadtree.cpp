#include "Quadtree.h"
void AQuadtree::Init(int iWidth, int iHeight, int iMaxDepth) 
{
	m_iMaxDepth = iMaxDepth;
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	m_pRootNode = CreateNode(nullptr, 0, 0, m_iWidth, m_iHeight);
	BuildTree(m_pRootNode);
}
ANode* AQuadtree::CreateNode(ANode* pParent, float x, float y, float w, float h) 
{
	ANode* pNode = new ANode(x, y, w, h);
	if (pParent != nullptr)
	{
		pNode->m_iDepth = pParent->m_iDepth + 1;
	}
	return pNode; 
}
void AQuadtree::BuildTree(ANode* pParent) 
{
	if (pParent->m_iDepth == m_iMaxDepth) return;

	pParent->pChild[0] = CreateNode(pParent, pParent->m_rt.x1, pParent->m_rt.y1, pParent->m_rt.w / 2.0f, pParent->m_rt.h / 2.0f);
	BuildTree(pParent->pChild[0]);

	pParent->pChild[1] = CreateNode(pParent, pParent->m_rt.mx, pParent->m_rt.y1, pParent->m_rt.w / 2.0f, pParent->m_rt.h / 2.0f);
	BuildTree(pParent->pChild[1]);

	pParent->pChild[2] = CreateNode(pParent, pParent->m_rt.mx, pParent->m_rt.my, pParent->m_rt.w / 2.0f, pParent->m_rt.h / 2.0f);
	BuildTree(pParent->pChild[2]);

	pParent->pChild[3] = CreateNode(pParent, pParent->m_rt.x1, pParent->m_rt.my, pParent->m_rt.w / 2.0f, pParent->m_rt.h / 2.0f);
	BuildTree(pParent->pChild[3]);
}
bool AQuadtree::AddObject(int fX, int fY) 
{
	ANode* pFindNode = FindNode(m_pRootNode, fX, fY);
	if (pFindNode != nullptr)
	{
		pFindNode->AddObject(fX, fY); return true;
	}
	return false;
}
ANode* AQuadtree::FindNode(ANode* pNode, int x, int y) 
{ 
	do {
		for (int iNode = 0; iNode < 4; iNode++)
		{
			if (pNode->pChild[iNode] != nullptr)
			{
				if (pNode->pChild[iNode]->IsRect(x, y))
				{
					g_Queue.push(pNode->pChild[iNode]);
					break;
				}
			}
		}
		if (g_Queue.empty()) break;
		pNode = g_Queue.front();
		g_Queue.pop();
	} while (pNode);
	return pNode;
 }
void AQuadtree::PrintList(ANode* pNode) 
{
	if (pNode == nullptr) return;

	for (list<AObject*>::iterator iter = pNode->m_ObjList.begin(); iter != pNode->m_ObjList.end(); iter++)
	{
		AObject* pObj = *iter;
		cout << "[" << pNode->m_iDepth << "]" << pObj->m_iX << ":" << pObj->m_iY << " ";
	}
	cout << endl;
	for (int iNode = 0; iNode < 4; iNode++)
	{
		PrintList(pNode->pChild[iNode]);
	}
}