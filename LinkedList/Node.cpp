#include "Node.h"

ANode* ANode::begin()
{
	m_pCurrnet = m_pHead->m_;
	m_pCurrent = m_pHead->m_pNext;
	return m_pHead->m_pNext;
}
ANode* ANode::End()
{
	return m_pNext;
}

ANode* ANode::operator++(int)
{
	return nullptr;
	//return m_pCurrent->m_pNext;
}
ANode* ANode::operator++(void)
{
	return nullptr;
	//return m_pCurrent->m_pNext;
}