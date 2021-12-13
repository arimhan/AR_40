#pragma once
#include "MiddleStudent.h"
#include "HighStudent.h"
#include "CollegeStudent.h"
class ANodeBox
{
public:
	AStudent* m_pData;
	AStudent* NewData(int iIndex);
	friend ostream& operator << (ostream& os, ANodeBox& data);

public:
	ANodeBox* m_pNext;
	ANodeBox();
	ANodeBox(int iIndex);
	~ANodeBox();
};

