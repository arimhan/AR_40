#include "LinkedList.h"

template <class A>
void ALinkedList<A>::AddData(A* pUser)
{
	if (m_iHeadNode == nullptr)
	{
		m_iHeadNode = pUser;
		m_iEndNode = pUser;
		m_iCount++;
	}
	m_iEndNode->m_pNext = pUser;
	m_iEndNode = pUser;
	m_iCount++;
}
template <class A>
void ALinkedList<A>::DeleteAll()
{
	cout << "DeleteAll" << endl;
}