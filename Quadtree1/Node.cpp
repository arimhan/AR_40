#include "Node.h"
bool ANode::IsRect(int x, int y)
{
	if (m_rt.x1 <= x && m_rt.x2 >= x && m_rt.y1 <= y && m_rt.y2 >= y)
	{
		return true;
	}
	return false;
}
void ANode::AddObject(int fX, int fY)
{
	m_ObjList.push_back(new AObject(fX, fY)); //Node.h 생성자 내 int fX, int fY값
}

ANode::ANode() 
{
	m_pParent = nullptr;
	m_iDepth = 0;
	pChild[0] = nullptr;
	pChild[1] = nullptr;
	pChild[2] = nullptr;
	pChild[3] = nullptr;
}
ANode::ANode(float x, float y, float w, float h) 
{
	m_rt.x1 = x;
	m_rt.y1 = y;
	m_rt.x2 = x + w;
	m_rt.y2 = y + h;
	m_rt.mx = x + (w / 2.0f);
	m_rt.my = y + (h / 2.0f);
	m_rt.w = w;
	m_rt.h = h;

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