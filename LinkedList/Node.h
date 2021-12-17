#pragma once
//#include "LinkedList.h"
class ALinkedList;
class ANode 
{
private:
	int		m_iValue;
	ANode* m_pNext;
	ANode* m_pPrev;
	friend ALinkedList;

	ANode* operator++(int); //pNode++
	ANode* operator++(void);
public:
	ANode* Next() { return m_pNext; }

	ANode() {}
	~ANode() {}
};

