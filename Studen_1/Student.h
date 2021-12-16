#pragma once
#include <iostream>
#include "LinkedList.h"
#include "FileIO.h"
using namespace std;

class AStudent
{
public:
	string	m_name; 
	int		m_iGA; //m_iGameArchitecture;
	int		m_iGD; //m_iGameDesign;
	int		m_iGP; //m_iGameProgramming;
	int		m_iTotal;
	int		m_fAverage;

public:
	AStudent()
	{
		m_name = "name";
		m_iGA = 0;
		m_iGD = 0;
		m_iGP = 0;
		m_iTotal = 0;
		m_fAverage = 0;
	}
	AStudent(string Name, int GA, int GD, int GP)
	{
		m_name = Name;
		m_iGA = GA;
		m_iGD = GD;
		m_iGP = GP;
		m_iTotal = GA + GD + GP;
		m_fAverage = m_iTotal /3;
	}
	virtual ~AStudent()
	{
		m_iGA = 0;
		m_iGD = 0;
		m_iGP = 0;
		m_iTotal = 0;
		m_fAverage = 0;
	}

public:

};

