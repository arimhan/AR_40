#include "LinkedList.h"
template <class T>
void ALinkedList<T>::AddLink(ANodeBox<AStudent>* const pUser)
{
	if (g_pHeadUserList == NULL)
	{
		g_pHeadUserList = pUser;
		g_pEndUser = pUser;
		g_iMaxUserCounter++;
		return;
	}
	g_pEndUser->m_pNext = pUser;
	g_pEndUser = pUser;
	g_iMaxUserCounter++;
}
template <class T>
void ALinkedList<T>::DeleteAll()
{
	ANodeBox* m_pNext = g_pHeadUserList;
	while (m_pNext)
	{
		ANodeBox* pDeleteUser = m_pNext;
		m_pNext = pDeleteUser->m_pNext;
		delete pDeleteUser;
		pDeleteUser = NULL;
		g_iMaxUserCounter--;
	}
	g_pHeadUserList = NULL;
}