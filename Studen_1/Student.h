#pragma once
#include "Object.h"
//과목  => Student 내 연산자 재정의에서 id체크로 사용
enum Subject {
	Index = 0, Type = 1, 
	Kor = 2, Graphic = 2,
	Eng = 3, Physics = 3,
	Mat = 4, AI = 4,
	Total = 5, Average = 6,
};

class AStudent : public AObject
{

	// Object를 상속받아 해당 user의 index, total, average (공통)
	//show, save, load => override
	//setdata
	//생성자 - index , (object)type 초기화
	//소멸자 - (object)과목점수 초기화  -> 왜 과목만 초기화....
public:
	int m_iIndex;
	int m_iTotal;
	float m_fAverage;

public:
	virtual void Show();
	virtual void Save();
	virtual void Load();
	void SetData();

	template <class T>
	T operator [] (int id);
	template <>
	float operator [] (int id);

	friend ostream& operator << (ostream& os, AStudent& data);

	AStudent()
	{
		m_iIndex = 0;
		m_iType = 0;
	}
	AStudent(int i, int t)
	{
		m_iIndex = i;
		m_iType = t;
	}
	~AStudent()
	{
		int k = 0;
	}
};

