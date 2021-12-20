#pragma once
#include "NodeBox.h"
template <class T>
class ALinkedList
{
public:
	// ���Ḯ��Ʈ ��� �߰�
	// ���Ḯ��Ʈ ��� ����
	// Data ��ȯ
	// ���Ḯ��Ʈ ��� �˻�
	int					m_iNumNode;
	ANodeBox<AStudent>* m_pHeadNode;
	ANodeBox<AStudent>* m_pEndNode;
public:
	ANodeBox<T>* GetHead() //����� ��ȯ
	{
		return m_pHeadNode;
	}
public:
	void	AddLink(ANodeBox<AStudent>* const pNode);//pNode);
	void	DeleteAll();
	ALinkedList()
	{
		m_iNumNode = 0;
		m_pHeadNode = 0;
		m_pEndNode = 0;
	}
};


