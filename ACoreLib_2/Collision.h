#pragma once
#include "AMath.h"

enum ACollisionResult
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
// È­¸éÁÂÇ¥°è+¿ÞÂÊ»ó´ÜÀÌ ¿øÁ¡
struct ARect2D
{
	T::TVector2 vMin;
	T::TVector2 vMax;
	T::TVector2 vMiddle;
	T::TVector2 size;
	bool operator == (const ARect2D& v)
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
	ARect2D() {};
	ARect2D(T::TVector2 vMin, T::TVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	ARect2D(T::TVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + T::TVector2(w, h);
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
// È­¸éÁÂÇ¥°è+Áß¾ÓÀÌ ¿øÁ¡
struct ARect
{
	T::TVector2 vMin;
	T::TVector2 vMax;
	T::TVector2 vMiddle;
	T::TVector2 size;
	bool operator == (const ARect& v)
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
	ARect(T::TVector2 vMin, T::TVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	ARect(T::TVector2 pos, float w, float h)
	{
		vMiddle = pos;
		this->vMin = vMiddle - T::TVector2(w/2.0f, h/2.0f);
		this->vMax = vMiddle + T::TVector2(w / 2.0f, h / 2.0f);		
		this->size.x = w;
		this->size.y = h;
	}
};
struct ABox
{
	T::TVector3 vList[8];
	T::TVector3	vAxis[3];

	T::TVector3 vMin;
	T::TVector3 vMax;
	T::TVector3 vMiddle;
	T::TVector3 size;
	bool operator == (const ABox& v)
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
	ABox(T::TVector3 vMin, T::TVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	ABox(T::TVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + T::TVector3(w, h,q);
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
struct ASphere
{
	T::TVector3		vCenter;
	float			fRadius;
	ASphere() { fRadius = 3.0f; }
};
class ACollision
{
public:
	static bool   SphereToPoint(ASphere rt, int x, int y, float z);
	static bool   SphereToPoint(ASphere rt, T::TVector3 v);
	static bool   RectToPoint(ARect rt, int x, int y);
	static bool   RectToPoint(ARect rt, T::TVector2 v);
	static ACollisionResult    RectToRect(ARect, ARect);
	static ACollisionResult    ToRect(ARect rt1, ARect rt2);
	static ARect  UnionRect(ARect rt1, ARect rt2);
	static bool  IntersectRect(ARect rt1, ARect rt2, ARect* rt);
	
	static bool   BoxToPoint(ABox rt, int x, int y, int z);
	static bool   BoxToPoint(ABox rt, T::TVector3 v);
	static ACollisionResult    BoxToBox(ABox, ABox);
	static ABox   UnionBox(ABox rt1, ABox rt2);
	static bool  IntersectBox(ABox rt1, ABox rt2, ABox* rt);
};

