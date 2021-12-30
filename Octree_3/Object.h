#pragma once
#include "Std.h"
class AObject
{
public:
	int			m_NodeIndex;
	float		m_Mass;
	AVector3	m_Pos;
	AVector3	m_Velocity; //속도
	AVector3	m_Acceleration; //가속도
	AVector3	m_Forces; //합산
	ABox		m_Rect;

	AObject();
	AObject(AVector3 Pos, AVector3 rect);

};

