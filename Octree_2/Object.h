#pragma once
#include "Std.h"
class Object
{
public:
	int m_NodeIndex;
	float m_Mass;
	Vector3 m_Pos;
	Vector3 m_Velocity; //�ӵ�
	Vector3 m_Acceleration; //���ӵ�
	Vector3 m_Forces; //�ջ�
	Box m_Rect;

	Object();
	Object(Vector3 Pos, Vector3 rect);

};

