#pragma once
#include "Object.h"
enum Subject {	Index = 0, Type, 
				Kor =2, Graphic =2, 
				Eng =3, Physics =3, 
				Mat =4, AI =4, 
				Total, Average,
};
class AStudent :public AObject
{
public:
	int m_iIndex;
	int m_iTotal;
	int m_fAverage;
public:
	//가상함수 : 가상테이블 생성됨 (부모클래스만 virtual, 자식클래스 override)
	virtual void Show();
	virtual void Save();
	virtual void Load() override;
	virtual void SetData(int iIndex);
public:
	template <typename A>
	A operator [] (int id);
	template <>
	float operator [] (int id);

	friend ostream& operator << (ostream& os, AStudent& data);
public:
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