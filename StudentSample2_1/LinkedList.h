#pragma once
#include "NodeBox.h"
template <class T>
class ALinkedList
{
public:
	int					g_iMaxUserCounter;
	ANodeBox<AStudent>*	g_pHeadUserList;
	ANodeBox<AStudent>*	g_pEndUser;

	ANodeBox<T>* GerHeadUserList()
	{
		return g_pHeadUserList;
	}

	void	AddLink(ANodeBox<AStudent>* const pUser);
	void	DeleteAll();
	ALinkedList()
	{
		g_iMaxUserCounter = 0 ;
		g_pHeadUserList = 0;
		g_pEndUser = 0;
	}
};

