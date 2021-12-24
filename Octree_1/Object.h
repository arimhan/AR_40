#pragma once
#include <iostream>
#include "Collision.h"
class AObject
{
public:
	AVector2	m_vPos;
	ARect		m_rt;
public:
	void SetPos(AVector2 pos);
	void SetPos(float x, float y);
	void SetRect(ARect rt);
public:
	AObject(int x, int y) //Node내 AddObject 인자값으로 받음
	{
		m_vPos.x = x; //m_iX = fX;
		m_vPos.y = y; //m_iY = fY;
	}
	AObject() //Node내 AddObject 인자값으로 받음
	{
		m_vPos.x = 0;
		m_vPos.y = 0;
	}
};

