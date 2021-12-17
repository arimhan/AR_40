#pragma once
#include "Object.h"
enum Subject {	Index = 0, Name =1, Kor =2, Eng =3,  Mat =4, Total, Average, };

class AStudent :public AObject
{
public:
	int m_iIndex;
	string	m_szName;
	int m_iKor;
	int m_iEng;
	int m_iMat;
	int m_iTotal;
	int m_fAverage;
public:
	//가상함수 : 가상테이블 생성됨
	virtual void Show();
	virtual void Save();
	virtual void Load() override;
	virtual void SetData(int iIndex);
public:
	template <class A>
	A operator [] (int id);
	template <>
	float operator [] (int id);

	friend ostream& operator << (ostream& os, AStudent& data);
public:
	AStudent()
	{
		m_iIndex = 1;
		m_szName = "name";
		m_iKor = 0;
		m_iEng = 0;
		m_iMat = 0;
	}
	AStudent(string name, int Kor, int Eng, int Mat)
	{
		m_iIndex = 1;
		m_szName = name;
		m_iKor = Kor;
		m_iEng = Eng;
		m_iMat = Mat;
		m_iTotal = Kor + Eng + Mat;
		m_fAverage = m_iTotal / 3;
	}
	virtual ~AStudent()
	{
		int k = 0;
	}
};