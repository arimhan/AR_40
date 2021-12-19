#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

class Node
{
private:
	int m_iData;
	Node* m_pNext;
	Node* m_pPrev;
public:
	int GetData() { return m_iData; }
	Node* GetNext() { return m_pNext; }
	void SetNext(Node* ptr) { m_pNext = ptr; }

	Node() {}; //���̳�� ������
	Node(int m_iData)
	{
		this->m_iData = m_iData; this->m_pNext = nullptr;
	}
	//data �޴� ������

	~Node() {};
};

