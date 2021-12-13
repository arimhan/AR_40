#pragma once
#include "Student.h"

class ACollegeStudent : public AStudent
{
public:
	int m_iGraphic;
	int m_iPhysics;
	int m_iAI;

public:
	virtual void Show() override;
	virtual void Save() override;
	virtual void Load() override;
	virtual void SetData(int iIndex) override;
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
