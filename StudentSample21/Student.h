#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory.h>
#include <stdlib.h>
using namespace std;

class AStudent
{
public:
	int m_iIndex;
	int m_iKor;
	int m_iEng;

	AStudent* m_pNext;

	int& operator[] (int id);
	friend ostream& operator << (ostream& os, AStudent& data);

	AStudent()
	{
		m_iIndex = 0;
		m_iKor = 0;
		m_iEng = 0;
		m_pNext = NULL;
	}
	AStudent(int i, int kor)
	{
		m_iIndex = i;
		m_iKor = kor;
		//m_iEng = 0;
		m_pNext = NULL;
	}
	~AStudent(){}
};

