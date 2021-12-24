#pragma once
#include "Vector.h"
struct ARect
{
	AVector2 p1;
	AVector2 p2;
	AVector2 middle;
	AVector2 size;
	ARect() {};
	ARect(AVector2 p1, AVector2 p2)
	{
		this->p1 = p1;
		this->p2 = p2;



	};
	ARect m_rt;
	//int m_iX;
	//int m_iY;
};
class ACollision
{
public:
	static bool IsRect(ARect rt, int x, int y);
	static bool IsRect(int x, int y);
	static bool RectToRect(ARect, ARect); 
	static bool UnionRect(ARect r1, ARect r2); //합집합
	static bool IntersectRect(ARect rt1, ARect rt2 ,ARect *rt); //교집합
};


