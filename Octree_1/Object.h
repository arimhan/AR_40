#pragma once
#include <iostream>
#include "Collision.h"
class AObject
{
public:
	AVector3	m_vPos;
	ARect		m_rt;
	ABox		m_box;
public:
	void SetPos(AVector3 pos);
	void SetPos(float x, float y, float z);
	void SetRect(ARect rt);
	void SetBox(ABox box);
public:
	AObject(int x, int y, int z) //Node내 AddObject 인자값으로 받음
	{
		m_vPos.x = x; //m_iX = fX;
		m_vPos.y = y; //m_iY = fY;
		m_vPos.y = y; //m_iY = fY;
	}
	AObject() //Node내 AddObject 인자값으로 받음
	{
		m_vPos.x = 0;
		m_vPos.y = 0;
		m_vPos.z = 0;
	}
};

