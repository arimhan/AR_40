#include "LinkedList.h"

template <class A>
void ALinkedList<A>::Init()
{
	m_pHeadNode = new ANodeBox<A>;
	m_pHeadNode->m_pNext = nullptr;
	m_pHeadNode->m_pData = 0;
	m_pEndNode = new ANodeBox<A>;
	m_pEndNode->m_pNext = nullptr;
	m_pHeadNode->m_pNext = m_pEndNode;
	m_pEndNode->m_pData = 0;
}
//template <class A>
//void ALinkedList<A>::AddLink(ANodeBox<AStudent>* const pNode)
//{
//	if (m_pHeadNode == NULL)
//	{
//		m_pHeadNode = pNode;
//		m_pEndNode = pNode;
//		m_iNumNode++;
//		return;
//	}
//	m_pEndNode->m_pNext = pNode;
//	m_pEndNode = pNode;
//	m_iNumNode++;
//}
template <class A>
void ALinkedList<A>::AddData(A* data)
{
	if (m_pHeadNode->m_pNext != nullptr)
	{
		ANodeBox<A>* add = new ANodeBox<A>;
		ANodeBox<A>* temp = m_pHeadNode->m_pNext;
		m_pHeadNode->m_pNext = add;
		add->m_pNext = temp;
		add->m_pData = data;
	}
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

template <class A>
int ALinkedList<A>::NodeCounter()
{
	int iCount = 0;
	for (ANodeBox<A>* pNode = m_pHeadNode->m_pNext; pNode != m_pEndNode; pNode = pNode->m_pNext)
	{
		iCount++;
	}
	return iCount;
}