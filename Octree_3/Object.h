#pragma once
#include "Std.h"
class AObject
{
public:
	int			m_NodeIndex;
	float		m_Mass;
	AVector3	m_Pos;
	AVector3	m_Velocity; //�ӵ�
	AVector3	m_Acceleration; //���ӵ�
	AVector3	m_Forces; //�ջ�
	ABox		m_Rect;

	AObject();
	AObject(AVector3 Pos, AVector3 rect);

};

