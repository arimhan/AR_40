#pragma once
#include "Std.h"
class Object
{
public:
	int m_NodeIndex;
	float m_Mass;
	Vector3 m_Pos;
	Vector3 m_Velocity; //속도
	Vector3 m_Acceleration; //가속도
	Vector3 m_Forces; //합산
	Box m_Rect;

	Object();
	Object(Vector3 Pos, Vector3 rect);

};

