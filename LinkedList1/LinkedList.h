#pragma once
#include "Node.h"

class LinkedList
{
private: // 외부에서 노드 접근 못하도록 설정
	Node* m_pHead;
	Node* m_pTail;
	int	m_iCount;
public:
	LinkedList();
	~LinkedList();

public:

	int GetDataCount();
	void Insert(int data);
	bool Delete(int deldata);
	void Display();
};

