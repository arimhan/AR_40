#pragma once
#include "Student.h"

class AMiddleStudent : public AStudent
{
public:
	int m_iKor;
	int m_iEng;
	int m_iMat;
public:
	virtual void Show() override;
	virtual void Save() override;
	virtual void Load() override;
	virtual void SetData(int iIndex) override;

public:
	AMiddleStudent()
	{
		m_iType = 1;
	}
	AMiddleStudent(int i, int kor)
	{
		m_iType = 1;
		m_iIndex = i;
		m_iKor = kor;
	}
	~AMiddleStudent()
	{
		int k = 0;
	}

};
