#pragma once
#include <iostream>
#include "Collision.h"
class AObject
{
public:
	AVector3	m_vPos;
	ABox		m_rt;
	int			m_iNodeIndex;
public:
	float		m_fSpeed;
	AVector3	m_vVelocity;
public:
	void SetPosition(float x, float y, float z);
	void SetPos(AVector3 pos);
	void SetPos(float x, float y, float z);
	void SetBox(ABox rt);
	bool Update(AVector3 vVelocity, float time);
public:
	AObject(int x, int y, int z) //Node내 AddObject 인자값으로 받음
	{
		m_vPos.x = x; //m_iX = fX;
		m_vPos.y = y; //m_iY = fY;
		m_vPos.y = y; //m_iY = fY;
		//m_fSpeed = 3.0f
	}
	AObject() //Node내 AddObject 인자값으로 받음
	{
		m_vPos.x = 0;
		m_vPos.y = 0;
		m_vPos.z = 0;
		//m_fSpeed = 3.0f
	}
};

