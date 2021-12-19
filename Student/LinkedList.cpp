#include "LinkedList.h"

template <class T>
T* ALinkedList<T>::GetData(int iIndex)
{
	ANode<T>* pNode = g_Start;
	while (pNode != NULL)
	{
		if (pNode->m_pData->GetIndex() == iIndex)
		{
			T* pData = pNode->m_pData;
			return pData;
		}
		pNode = pNode->g_Next;
	}
	return 0; //null
}

template <class T>
bool ALinkedList<T>::AddLink(T* pData)
{
	ANode<T>* pNode = new ANode<T>();
	pNode->m_pData = pData;
	if (g_Start == NULL)
	{
		g_Start = pNode;
		g_End = pNode;
	}
	else
	{
		ANode<T>* pFirst = g_Start;
		g_Start = pNode;
		g_Start->g_Next = pFirst;
		pFirst->g_Prev = pNode;
	}
	m_iCount++;
	return true;
}