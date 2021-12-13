#pragma once
#include "Object.h"

class AStudent :public AObject
{
public:
	int m_iIndex;
	int m_iTotal;
	int m_fAverage;

	//가상함수 : 가상테이블 생성됨
	virtual void Show() override;
	virtual void Save() override;
	virtual void Load() override;
	virtual void SetData(int iIndex);

	int& operator[] (int id);
	friend ostream& operator << (ostream& os, AStudent& data);

	AStudent()
	{
		m_iIndex = 0;
		m_iType = 0;
	}
	AStudent(int i, int kor)
	{
		m_iIndex = i;
		m_iType = 0;
	}
	virtual ~AStudent()
	{
		int k = 0;
	}
};