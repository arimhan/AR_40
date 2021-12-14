#pragma once
#include "Object.h"
//����  => Student �� ������ �����ǿ��� idüũ�� ���
enum Subject {
	Index = 0, Type = 1, 
	Kor = 2, Graphic = 2,
	Eng = 3, Physics = 3,
	Mat = 4, AI = 4,
	Total = 5, Average = 6,
};

class AStudent : public AObject
{

	// Object�� ��ӹ޾� �ش� user�� index, total, average (����)
	//show, save, load => override
	//setdata
	//������ - index , (object)type �ʱ�ȭ
	//�Ҹ��� - (object)�������� �ʱ�ȭ  -> �� ���� �ʱ�ȭ....
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

