#pragma once

template <class T>
class ANode
{
public:
	T* m_pData;
	ANode* g_Next;
	ANode* g_Prev;
	void Delete()
	{
		delete m_pData;
	}
	ANode() {}
	~ANode() {}
};

template <class T>
ANode<T>::ANode()
{
	m_pData = NULL;
	g_Next = g_Prev = 0;
}
template <class T>
ANode<T>::~ANode()
{
	delete m_pData;
}


