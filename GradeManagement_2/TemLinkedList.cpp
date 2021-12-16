#include "TemLinkedList.h"
#include "NodeBox.h"
//Template LinkedList 

template <class A>
void ALinkedList<A>::AddData(A* pUser)
{
	if (m_pHeadNode == nullptr) //head data������� ����
	{
		ANodeBox<A>* pNode;
		m_pHeadNode = pNode;
		m_pEndNode = pNode;
		m_iNumNode++;
	}
	//else if (m_pHeadNode->m_pNext != nullptr) //next�� ������ ��� (data 1���� ������) ó��
	//{
	//	ANodeBox* <R> Add = new ANodeBox<R>;
	//	ANodeBox* <R> Save = m_pHeadNode->m_pNext;
	//	m_pHeadNode->m_pNext = add;
	//	Add->m_pNext = Save;
	//	Add->m_iData = result;
	//}
	else
	{
		cout << "error : TemLinkedList_AddData";
	}
}
//void ALinkedList<T>::AddLink(ANodeBox<AStudent>* const pNode)
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

