#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <memory.h>
#include <stdlib.h>
using namespace std;

class AStudent
{
public:
	int			m_iIndex;
	int			m_iKor;
	AStudent*	pNext;

	int& operator [] (int id);
	friend ostream& operator<< (ostream& os, AStudent& data);

	AStudent()
	{
		m_iIndex = 0;
		m_iKor = 0;
		pNext = NULL;
	}
	AStudent(int i, int Kor)
	{
		m_iIndex = i;
		m_iKor = Kor;
		pNext = NULL;
	}
	~AStudent() {}
};


