#include "Octree.h"
int AOctree::g_iCount = 0;

ANode* AOctree::CreateNode(ANode* pParent, float x, float y, float z, float w, float h, float q)
{
	ANode* pNode = new ANode(x, y, z, w, h, q);
	pNode->m_iIndex = g_iCount++;
	if (pParent != nullptr)
	{
		pNode->m_iDepth = pParent->m_iDepth+1;
	}
	return pNode;
}
void AOctree::Init(int iWidth, int iHeight, int iDepthint, int iMaxDepth)
{
	m_iSizeX = iWidth;
	m_iSizeY = iHeight;
	m_iSizeZ = iHeight; // iHeight;
	m_iMaxDepth = iMaxDepth;
	//m_vSize = {iXSize, iYSize, iZSize};
	m_pRootNode = CreateNode(nullptr, 0, 0, 0, m_iSizeX, m_iSizeY, m_iSizeZ);
	BuildTree(m_pRootNode);
}
void AOctree::BuildTree(ANode* pParent)
{
	if (pParent->m_iDepth == m_iMaxDepth) return;

	pParent->pChild[0] = CreateNode(pParent, pParent->m_rt.vMin.x, pParent->m_rt.vMin.y, pParent->m_rt.vMin.z, 
									pParent->m_rt.vSize.x / 2.0f, pParent->m_rt.vSize.y / 2.0f, pParent->m_rt.vSize.z / 2.0f);
	BuildTree(pParent->pChild[0]);
	pParent->pChild[1] = CreateNode(pParent, pParent->m_rt.vMiddle.x, pParent->m_rt.vMin.y, pParent->m_rt.vMin.z, 
									pParent->m_rt.vSize.x / 2.0f, pParent->m_rt.vSize.y / 2.0f, pParent->m_rt.vSize.z / 2.0f);
	BuildTree(pParent->pChild[1]);
	pParent->pChild[2] = CreateNode(pParent, pParent->m_rt.vMiddle.x, pParent->m_rt.vMiddle.y, pParent->m_rt.vMin.z, 
									pParent->m_rt.vSize.x / 2.0f, pParent->m_rt.vSize.y / 2.0f, pParent->m_rt.vSize.z / 2.0f);
	BuildTree(pParent->pChild[2]);
	pParent->pChild[3] = CreateNode(pParent, pParent->m_rt.vMin.x, pParent->m_rt.vMiddle.y, pParent->m_rt.vMin.z, 
									pParent->m_rt.vSize.x / 2.0f, pParent->m_rt.vSize.y / 2.0f, pParent->m_rt.vSize.z / 2.0f);
	BuildTree(pParent->pChild[3]);

	pParent->pChild[4] = CreateNode(pParent, pParent->m_rt.vMin.x, pParent->m_rt.vMin.y, pParent->m_rt.vMiddle.z, 
									pParent->m_rt.vSize.x / 2.0f, pParent->m_rt.vSize.y / 2.0f, pParent->m_rt.vSize.z / 2.0f);
	BuildTree(pParent->pChild[4]);
	pParent->pChild[5] = CreateNode(pParent, pParent->m_rt.vMiddle.x, pParent->m_rt.vMin.y, pParent->m_rt.vMiddle.z, 
									pParent->m_rt.vSize.x / 2.0f, pParent->m_rt.vSize.y / 2.0f, pParent->m_rt.vSize.z / 2.0f);
	BuildTree(pParent->pChild[5]);
	pParent->pChild[6] = CreateNode(pParent, pParent->m_rt.vMiddle.x, pParent->m_rt.vMiddle.y, pParent->m_rt.vMiddle.z, 
									pParent->m_rt.vSize.x / 2.0f, pParent->m_rt.vSize.y / 2.0f, pParent->m_rt.vSize.z / 2.0f);
	BuildTree(pParent->pChild[6]);
	pParent->pChild[7] = CreateNode(pParent, pParent->m_rt.vMin.x, pParent->m_rt.vMiddle.y, pParent->m_rt.vMiddle.z, 
									pParent->m_rt.vSize.x / 2.0f, pParent->m_rt.vSize.y / 2.0f, pParent->m_rt.vSize.z / 2.0f);
	BuildTree(pParent->pChild[7]);
}
bool AOctree::AddObject(AObject* obj)
{
	ANode* pFindNode = FindNode(m_pRootNode, obj->m_rt);
	if (pFindNode != nullptr)
	{
		pFindNode->AddObject(obj);
		return true;
	}
	return false;
}
ANode* AOctree::FindNode(ANode* pNode, ABox rt)
{
	do {
		for (int iNode = 0; iNode < 8; iNode++)
		{
			if (pNode->pChild[iNode] != nullptr)
			{
				ABox intersect;
				ACollisionType iRet = ACollision::BoxToBox(pNode->pChild[iNode]->m_rt, rt);
				if (iRet == ACollisionType::RECT_IN)
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
void AOctree::PrintObjList(ANode* pNode)
{
	if (pNode == nullptr) return;

	for (list<AObject*>::iterator iter = pNode->m_ObjList.begin(); iter != pNode->m_ObjList.end(); iter++)
	{
		AObject* pObj = *iter;
		cout << "[" << pNode->m_iDepth << "]" << pObj->m_vPos.x << ":" << pObj->m_vPos.y << " ";
	}
	cout << endl;
	for (int iNode = 0; iNode < 8; iNode++)
	{
		PrintObjList(pNode->pChild[iNode]);
	}
}