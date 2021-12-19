#pragma once
#include "Node.h"

class LinkedList
{
private: // 외부에서 노드 접근 못하도록 설정
	Node* m_pHead;
	Node* m_pTail;
public:

	int	m_iCount;

public:

	int GetDataCount() { return m_iCount; }
	bool AddNode(int pData);
	bool DeleteNode(int pData);
	void SearchNode();
	void EditNode();
	void Draw();
	Node* GetHead() { return m_pHead; }

	LinkedList() {};
	~LinkedList() {};



};

