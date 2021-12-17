#pragma once
#include "MiddleStudent.h"

template<class A>
class ANodeBox
{
public:
	A* m_pData;
	friend ostream& operator << (ostream& os, ANodeBox<A>& data)
	{
		os << *data.m_pData;
		return os;
	}
public:
	ANodeBox* m_pNext;
	ANodeBox();
	ANodeBox(A* data);
	~ANodeBox();
};

template<class A>
ANodeBox<A>::ANodeBox()
{
	m_pData = nullptr;
}
template<class A>
ANodeBox<A>::ANodeBox(A* data)
{
	m_pData = data;
}
template<class A>
ANodeBox<A>::~ANodeBox()
{
	delete m_pData;
}