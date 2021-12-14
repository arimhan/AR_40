#pragma once

template <class T>
class ALinkedList
{
public:

	int					m_iNumNode;
	ANode<AStudent>*	m_pHeadNode;
	ANode<AStudent>*	m_pEndNode;

	ANode<T>* GetHeadNode()
	{
		return m_pHeadNode;
	}
	void AddLink(ANode<AStudent>* const pNode);
	void DeleteAll();
	ALinkedList()
	{
		m_iNumNode = 0;
		m_pHeadNode = 0;
		m_pEndNode = 0;
	}

};
template <class T>
class ANode
{
public:
	T* m_data;
	ANode* m_pNext;
	template <class T>
	ANode<T>::ANode()
	{
		m_pData = nullptr;
	}
	template <class T>
	ANode<T>::ANode(T* data)
	{
		m_pData = data;
	}
	template <class T>
	ANode<T>::~ANode()
	{
		delete m_pData;
	}
};

