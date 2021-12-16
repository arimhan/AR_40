#pragma once
#include "Student.h"

template<class R>
class ANodeBox
{
public:
	R* m_pData;
	friend ostream& operator << (ostream& os, ANodeBox<R>& data)
	{
		os << *data.m_pData;
		return os;
	}
public:
	ANodeBox* m_pNext;
	ANodeBox();
	ANodeBox(R* data);
	~ANodeBox();
};

template<class R>
ANodeBox<R>::ANodeBox()
{
	m_pData = nullptr;
}
template<class R>
ANodeBox<R>::ANodeBox(R* data)
{
	m_pData = data;
}
template<class R>
ANodeBox<R>::~ANodeBox()
{
	delete m_pData;
}