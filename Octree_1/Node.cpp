#include "Node.h"

void ANode::AddObject(AObject* obj)
{
	m_ObjList.push_back(obj);
}
ANode::ANode()
{
	m_pParent = nullptr;
	m_iDepth = 0;
	m_iIndex = 0;
	pChild[0] = nullptr;
	pChild[1] = nullptr;
	pChild[2] = nullptr;
	pChild[3] = nullptr;
	pChild[4] = nullptr;
	pChild[5] = nullptr;
	pChild[6] = nullptr;
	pChild[7] = nullptr;

	for (list<AObject*>::iterator iter = m_ObjList.begin(); iter != m_ObjList.end(); iter++)
	{
		AObject* pObj = *iter;
		delete pObj;
	}
	m_ObjList.clear();
}
ANode::ANode(float x, float y, float z,float w, float h, float q) : ANode()
{
	m_rt.vMin.x = x;
	m_rt.vMin.y = y;
	m_rt.vMin.z = z;
	m_rt.vMax.x = x + w;
	m_rt.vMax.y = y + h;
	m_rt.vMax.z = z + q;
	m_rt.vMiddle.x = x + (w / 2.0f);
	m_rt.vMiddle.y = y + (h / 2.0f);
	m_rt.vMiddle.z = z + (h / 2.0f);
	m_rt.vSize.x = w;
	m_rt.vSize.y = h;
	m_rt.vSize.z = q;

	//Octree[] 8ea
	pChild[0] = nullptr;
	pChild[1] = nullptr;
	pChild[2] = nullptr;
	pChild[3] = nullptr;
	pChild[4] = nullptr;
	pChild[5] = nullptr;
	pChild[6] = nullptr;
	pChild[7] = nullptr;
}
ANode::~ANode()
{
	delete pChild[0];
	delete pChild[1];
	delete pChild[2];
	delete pChild[3];
	delete pChild[4];
	delete pChild[5];
	delete pChild[6];
	delete pChild[7];
}