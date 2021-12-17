#pragma once
#include "NodeBox.h"
template <class A>
class ALinkedList
{
public:
	// 연결리스트 노드 추가
	// 연결리스트 노드 삭제
	// Data 반환
	// 연결리스트 노드 검색
	int					m_iNumNode;
	ANodeBox<AStudent>* m_pHeadNode;
	ANodeBox<AStudent>* m_pEndNode;
public:
	ANodeBox<A>* GetHead() //헤드노드 반환
	{
		return m_pHeadNode;
	}
public:
	void	AddLink(ANodeBox<AStudent>* const pNode);//pNode);
	void	AddData(A*);
	void	DeleteAll();
	ALinkedList()
	{
		m_iNumNode = 0;
		m_pHeadNode = 0;
		m_pEndNode = 0;
	}
};



