#pragma once
#include <iostream>
class AObject
{
public:
	int m_iX;
	int m_iY;
	AObject(int fX, int fY) //Node내 AddObject 인자값으로 받음
	{
		m_iX = fX;
		m_iY = fY;
	}
};

