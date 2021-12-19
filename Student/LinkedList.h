#pragma once
#include <iostream>
#include <stdlib.h>
#include "Node.h"

template <class T>
class ALinkedList
{
public:
	int			m_iCount;
	ANode<T>*	g_Start;
	ANode<T>*	g_End;

	int		Size() { return m_iCount; }
	bool	AddLink(T* pStud);
	bool	DelLink(T* pStud);
	void	Delete();
	T*		GetData(int iIndex);
	ANode<T>*	GetStart() { return g_Start; };
	bool	Sort(bool bUP);

	ALinkedList(void);
	~ALinkedList(void);
};

