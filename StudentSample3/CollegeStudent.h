#pragma once
#include "Student.h"

class ACollegeStudent : public AStudent
{
public:
	int m_iGraphic;
	int m_iPhysics;
	int m_iAI;

public:
	void Show() override;
	void Save() override;
	void Load() override;
	void SetData(int iIndex) override;
public:
	ACollegeStudent()
	{
		m_iType = 3;
	}
	ACollegeStudent(int i, int phy)
	{
		m_iIndex = i;
		int m_iPhysics = phy;
		m_iType = 3;
	}
	~ACollegeStudent()
	{
		int k = 0;
	}
};
