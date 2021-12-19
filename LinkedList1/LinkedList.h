#pragma once
#include "Node.h"

class LinkedList
{
private: // �ܺο��� ��� ���� ���ϵ��� ����
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

