#pragma once
#include "Student.h"

template <class A>
class ANodeBox //:public ALinkedList
{
public:
	A* m_pData;
	ANodeBox* m_pNext;
};

