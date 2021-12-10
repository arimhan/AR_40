#pragma once
#include<iostream>
#include<tchar.h>
#include"Node.h"

template <class T>
class ALinkedList
{
public:
	int m_iCount;
	ANode<T>* g_Start;
	ANode<T>* g_End;

	int Size() { return m_iCount; }
	bool AddLink(T* pStud);
	bool DelLink(T* pStud);
	void Delete();
	T* GetData(int iIndex);
	ANode<T>* GetStart() { return g_Start; };
	bool Sort(bool bUP);

	ALinkedList(void);
	~ALinkedList(void);
};
template <class T>
T* ALinkedList<T>::GetData(int iIndex)
{
	ANode<T>* pNode = g_Start;
	while (pNode != NULL)
	{
		if (pNode->m_pData->GetInder() == iIndex)
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

