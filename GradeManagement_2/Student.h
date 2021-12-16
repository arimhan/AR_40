#pragma once
//#include "StudentManager.h"
#include "Object.h"

class AStudent :public AObject
{
public:
	string	m_csName;
	int		m_iGA; //m_iGameArchitecture;
	int		m_iGD; //m_iGameDesign;
	int		m_iGP; //m_iGameProgramming;
	int		m_iTotal;
	int		m_fAverage;

public:
	//가상함수 : 가상테이블 생성됨
	virtual void Show();
	virtual void Save();
	virtual void Load() override;
	virtual void SetData(char* m_csName);
public:
	template <typename T>
	T operator [] (int id);
	template <>
	float operator [] (int id);

	friend ostream& operator << (ostream& os, AStudent& data);
public:
	AStudent()
	{
		m_csName = "name";
		m_iGA = 0;
		m_iGD = 0;
		m_iGP = 0;
	}
	AStudent(string Name, int GA, int GD, int GP)
	{
		m_csName = Name;
		m_iGA = GA;
		m_iGD = GD;
		m_iGP = GP;
	}
	virtual ~AStudent()
	{
		m_iGA = 0;
		m_iGD = 0;
		m_iGP = 0;
	}
};