#pragma once
#include "Student.h"

class AMiddleStudent : public AStudent
{
public:
	int m_iKor;
	int m_iEng;
	int m_iMat;
public:
	void Show() override;
	void Save() override;
	void Load() override;
	void SetData(int iIndex) override;

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
