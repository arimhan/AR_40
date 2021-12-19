#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

class Node
{
public:
	int m_iData;
	Node* m_pNext;
	Node* m_pPrev;

	int GetData() { return m_iData; }
	Node* GetNext() { return m_pNext; }

	Node() 
	{
		m_iData = 0;
		m_pNext = nullptr;
		m_pPrev = nullptr;
	};
	Node(int data)
	{
		m_iData = data;
	};
	~Node() {};
};

