#pragma once
#include <iostream>
#include "Vector.h"
class AObject
{
public:
	AVector2 m_Pos;

	AObject(int x, int y) //Node내 AddObject 인자값으로 받음
	{
		m_Pos.x = x; //m_iX = fX;
		m_Pos.y = y; //m_iY = fY;
	}
public:
	void SetPos();
	void SetRect();
};

