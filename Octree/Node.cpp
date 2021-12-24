#include "Node.h"

void ANode::AddObject(AObject* obj)
{
	m_ObjList.push_back(new AObject(
		obj->m_vPos.x,
		obj->m_vPos.y));
	//Node.h 생성자 내 int fX, int fY값
}

ANode::ANode()
{
	m_pParent = nullptr;
	m_iDepth = 0;
	pChild[0] = nullptr;
	pChild[1] = nullptr;
	pChild[2] = nullptr;
	pChild[3] = nullptr;

	for (list<AObject*>::iterator iter = m_ObjList.begin(); iter != m_ObjList.end(); iter++)
	{
		AObject* pObj = *iter;
		delete pObj;
	}
	m_ObjList.clear();
}
ANode::ANode(float x, float y, float w, float h)
{
	m_rt.vMin.x = x;
	m_rt.vMin.y = y;
	m_rt.vMax.x = x + w;
	m_rt.vMax.y = y + h;
	m_rt.middle.x = x + (w / 2.0f);
	m_rt.middle.y = y + (h / 2.0f);
	m_rt.size.x = w;
	m_rt.size.y = h;

	pChild[0] = nullptr;
	pChild[1] = nullptr;
	pChild[2] = nullptr;
	pChild[3] = nullptr;
}
ANode::~ANode()
{
	delete pChild[0];
	delete pChild[1];
	delete pChild[2];
	delete pChild[3];
}