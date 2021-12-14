#pragma once
#include "MiddleStudent.h"
#include "HighStudent.h"
#include "CollegeStudent.h"
template<class T>
class ANodeBox
{
public:
	T* m_pData;
	friend ostream& operator << (ostream& os, ANodeBox<T>& data)
	{
		os << *data.m_pData;
		return os;
	}
public:
	ANodeBox* m_pNext;
	ANodeBox();
	ANodeBox(T* data);
	~ANodeBox();
};

template<class T>
ANodeBox<T>::ANodeBox()
{
	m_pData = nullptr;
}
template<class T>
ANodeBox<T>::ANodeBox(T* data)
{
	m_pData = data;
}
template<class T>
ANodeBox<T>::~ANodeBox()
{
	delete m_pData;
}