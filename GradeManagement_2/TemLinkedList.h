#pragma once
#include "NodeBox.h"
//Template LinkedList 

template <class R>
class ALinkedList
{
public:
	int					m_iNumNode;
	ANodeBox<AStudent>* m_pHeadNode;
	ANodeBox<AStudent>* m_pEndNode;

	void	AddData(R*);
	//void	AddLink(ANodeBox<AStudent>* const pNode);//pNode);
	void	DeleteAll();
public:
	/*ANodeBox<T>* GetHead() //헤드노드 반환
	{
		return m_pHeadNode;
	}*/
public:
	ALinkedList(){}
	~ALinkedList() 
	{
		delete m_pEndNode;
		m_pEndNode = nullptr;
		delete m_pHeadNode;
		m_pHeadNode = nullptr;
	}
};




