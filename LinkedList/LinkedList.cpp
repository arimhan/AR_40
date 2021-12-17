#include "LinkedList.h"


void ALinkedList:: PushBack(ANode* pNode)
{
	ANode* pLink = m_pHead;
	m_pHead->m_pNext = pNewNode;
	pNewNode->m_pNext = pLink;
	pLink->m_pPrev = pNewNode;
	pNewNode->m_pPrev = m_pHead;
}
void ALinkedList::PushFront(ANode* pNewNode)
{
	ANode* pLink = m_pHead->m_pNext;
	m_pHead->m_pNext = pNewNode;
	pNewNode->m_pNext = pLink;
	pLink->m_pPrev = pNewNode;
	pNewNode->m_pPrev = m_pHead;
}
