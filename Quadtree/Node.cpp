#include "Node.h"

void ANode::AddObject(int fX, int fY)
{
	m_ObjectList.push_back(new AObject(fX, fY));
}
bool ANode::IsRect(int x, int y)
{
	// (x1,y1) �꺸�� ũ��			 
	//
	//				
	//			�꺸�� ������ ����	(x2,y2)  

	if (m_rt.x1 <= x && m_rt.x2 >= x && m_rt.y1 <= y && m_rt.y2 >= y)
		//���� �ȿ� ������ x,y�� ���Ե� ������ ����
	{
		return true;
	}
	return false;
}
ANode::ANode()
{
	m_pParent = nullptr;
	m_iDepth = 0;
	m_pChildNode[0] = nullptr;
	m_pChildNode[1] = nullptr;
	m_pChildNode[2] = nullptr;
	m_pChildNode[3] = nullptr;

	for (list<AObject*>::iterator iter = m_ObjectList.begin(); iter != m_ObjectList.end(); iter++)
	{
		AObject* pObj = *iter;
		delete pObj;
	}
	m_ObjectList.clear();
	//delete�� clear�� �ؾ� �����Ͱ� ������. ���� clear�ϸ� delete �Ұ�....
}	
ANode::ANode(float x, float y, float w, float h) : ANode()
{
	m_rt.x1 = x;
	m_rt.y1 = y;
	m_rt.x2 = x + w;
	m_rt.y2 = y + h;
	m_rt.mx = x + ( w / 2.0f);
	m_rt.my = y + ( h / 2.0f);
	m_rt.w = w;
	m_rt.h = h;

	m_pChildNode[0] = nullptr;
	m_pChildNode[1] = nullptr;
	m_pChildNode[2] = nullptr;
	m_pChildNode[3] = nullptr;
}
ANode::~ANode()
{
	delete m_pChildNode[0];
	delete m_pChildNode[1];
	delete m_pChildNode[2];
	delete m_pChildNode[3];
}