#include "LinkedList.h"
template <class A>
void ALinkedList<A>::AddLink(ANodeBox<AStudent>* const pNode)
{
	if (m_pHeadNode == NULL)
	{
		m_pHeadNode = pNode;
		m_pEndNode = pNode;
		m_iNumNode++;
		return;
	}
	m_pEndNode->m_pNext = pNode;
	m_pEndNode = pNode;
	m_iNumNode++;
}
template <class A>
void ALinkedList<A>::DeleteAll()
{
	ANodeBox<A>* m_pNext = m_pHeadNode;
	while (m_pNext)
	{
		ANodeBox<A>* pDeleteUser = m_pNext;
		m_pNext = pDeleteUser->m_pNext;
		delete pDeleteUser;
		pDeleteUser = NULL;
		m_iNumNode--;
	}
	m_pHeadNode = NULL;
}

