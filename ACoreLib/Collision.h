#pragma once
#include "Vector3.h"
//enum class : c++11지원 , 모든 열거자를 열거형 일부로 간주하므로 범위한정자를 꼭 사용할 것!
enum class ACollisionType {  RECT_OUT = 0, RECT_IN = 1, RECT_OVERLAP = 3,};

struct ARect
{
	AVector2 vMin;
	AVector2 vMax;
	AVector2 vMiddle;
	AVector2 size;

	bool operator ==(const ARect& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	ARect() {};
	ARect(AVector2 vMin, AVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	};
	ARect(AVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + AVector2(w,h);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	};
};
struct ABox //3D
{
	AVector3 vMin;
	AVector3 vMax;
	AVector3 vMiddle;
	AVector3 size;

	bool operator ==(const ABox& v) //여기서 값 비교 시 p1 (원점으로부터) p2(끝점, 크기결정)만 비교하도록 한다.
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	ABox() {};
	ABox(AVector3 vMin, AVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	};
	ABox(AVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + AVector3(w, h, q);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	};
};
class ACollision
{
public:
	//2D (ARect)
	static bool RectToPoint(ARect rt, int x, int y); //IsRect -> RectToRect
	static bool RectToPoint(ARect rt, AVector2 v);
	static ACollisionType RectToRect(ARect, ARect); //Rect충돌값 반환값 0, 1, 2로 처리 => enum 
	static ARect UnionRect(ARect rt1, ARect rt2); //합집합
	static bool IntersectRect(ARect rt1, ARect rt2, ARect* rt); //교집합

	//3D (ABox)
	static bool BoxToPoint(ABox rt, int x, int y, int z); //3D box와 point 충돌 체크
	static bool BoxToPoint(ABox rt, AVector3 v); //rect와 vector 비교
	static ACollisionType BoxToBox(ABox, ABox); //Rect충돌값 반환값 0, 1, 2로 처리 => enum 
	static ABox UnionBox(ABox rt1, ABox rt2); //합집합
	static bool IntersectBox(ABox rt1, ABox rt2, ABox* rt); //교집합
};



