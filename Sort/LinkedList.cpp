#include "LinkedList.h"
template <class T>
void ALinkedList<T>::AddLink(ANodeBox<AStudent>* const pNode)
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
template <class T>
void ALinkedList<T>::DeleteAll()
{
	ANodeBox<T>* m_pNext = m_pHeadNode;
	while (m_pNext)
	{
		ANodeBox<T>* pDeleteUser = m_pNext;
		m_pNext = pDeleteUser->m_pNext;
		delete pDeleteUser;
		pDeleteUser = NULL;
		m_iNumNode--;
	}
	m_pHeadNode = NULL;
}

