#pragma once
#include <iostream>
using namespace std;


class APoint
{
public:
	int x, y;
	void SetPosition(int _x, int _y);
	void Move(int _x, int _y);
	void Show();
public:
	APoint* operator->() { return this; }
	APoint& operator*() { return *this; }
	APoint& operator++(void); // ++p1
	APoint& operator++(int); // p1++

	APoint operator+(const APoint& pt) const;
	APoint operator-(const APoint& pt) const;
	APoint operator*(const APoint& c);
	APoint operator/(const APoint& c);

	APoint operator*(int mag) const;
	APoint operator/(int div) const;

	// *, / 의 A, B의 객체 위치가 바뀔 경우를 위해 friend처리
	friend APoint operator*(int mag, const APoint& pt); 
	friend APoint operator/(int div, const APoint& pt);

	APoint& operator=(const APoint& pt);
	APoint& operator+=(const APoint& pt);
	APoint& operator-=(const APoint& pt);
	APoint& operator*=(const APoint& pt);
	APoint& operator/=(const APoint& pt);
	APoint& operator*=(int mag);
	APoint& operator/=(int div);

	bool operator==(const APoint& pt) const;
	bool operator!=(const APoint& pt) const;

	//인덱싱 처리 p6[1] , p6(1)
	int& operator[](int index);
	int& operator()(int index);

	void* operator new(size_t size);
	void operator delete(void* p);

	friend ostream& operator<< (ostream& os, const APoint& pt);
	friend istream& operator>> (istream& is, APoint& pt);

	void (APoint::* m_fp)();
	void Execute()
	{
		if (m_fp != NULL)
		{
			(this->*m_fp)();
		}
	}
	void operator > (APoint* the)
	{
		if (m_fp != NULL)
		{
			(the->*m_fp)();
		}
	}
public:
	APoint();
	APoint(int x, int y);
	~APoint();
};

