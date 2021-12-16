#pragma once
#include "NodeBox.h"
template <class A>
class ALinkedList
{
public:
	int m_iCount;
	ANodeBox<A>* m_iHeadNode;
	ANodeBox<A>* m_iEndNode;
	ALinkedList<A>	m_List;
	//AFileIO					m_FileIO;

	void AddData(A*);
	void DeleteAll();

public:
	ALinkedList()
	{
		m_iCount = 0;
		m_iHeadNode = 0;
		m_iEndNode = 0;
	}

	~ALinkedList(){	}
};

