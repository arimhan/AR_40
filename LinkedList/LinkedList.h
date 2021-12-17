#pragma once
#include "Node.h"

class ALinkedList// : public ANode
{
public:
	ANode* m_pHead;
	ANode* m_pTail;
	ANode* m_pCurrnet;
public:
	ANode* begin();
	ANode* End();

	void PushBack(ANode* pNode);
	void PushFront(ANode* pNewNode);

	ALinkedList() {}
	~ALinkedList() {}
};

