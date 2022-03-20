#pragma once
#include "Matrix.h"

enum ACollisionResult
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
// È­¸éÁÂÇ¥°è+¿ÞÂÊ»ó´ÜÀÌ ¿øÁ¡
struct ARect2D
{
	AVector2 vMin;
	AVector2 vMax;
	AVector2 vMiddle;
	AVector2 size;
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
	ARect2D(AVector2 vMin, AVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	ARect2D(AVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + AVector2(w, h);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
// È­¸éÁÂÇ¥°è+Áß¾ÓÀÌ ¿øÁ¡
struct ARect
{
	AVector2 vMin;
	AVector2 vMax;
	AVector2 vMiddle;
	AVector2 size;
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
	ARect(AVector2 vMin, AVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	ARect(AVector2 pos, float w, float h)
	{
		vMiddle = pos;
		this->vMin = vMiddle - AVector2(w/2.0f, h/2.0f);
		this->vMax = vMiddle + AVector2(w / 2.0f, h / 2.0f);		
		this->size.x = w;
		this->size.y = h;
	}
};
struct ABox
{
	AVector3 vMin;
	AVector3 vMax;
	AVector3 vMiddle;
	AVector3 size;
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
	ABox(AVector3 vMin, AVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	ABox(AVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + AVector3(w, h,q);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
struct ASphere
{
	AVector2 vCenter;
	float    fRadius;
	ASphere()
	{
		fRadius = 3.0f;
	}
};
class ACollision
{
public:
	static bool   SphereToPoint(ASphere rt, int x, int y);
	static bool   SphereToPoint(ASphere rt, AVector2 v);
	static bool   RectToPoint(ARect rt, int x, int y);
	static bool   RectToPoint(ARect rt, AVector2 v);
	static ACollisionResult    RectToRect(ARect, ARect);
	static ACollisionResult    ToRect(ARect rt1, ARect rt2);
	static ARect  UnionRect(ARect rt1, ARect rt2);
	static bool  IntersectRect(ARect rt1, ARect rt2, ARect* rt);
	
	static bool   BoxToPoint(ABox rt, int x, int y, int z);
	static bool   BoxToPoint(ABox rt, AVector3 v);
	static ACollisionResult    BoxToBox(ABox, ABox);
	static ABox   UnionBox(ABox rt1, ABox rt2);
	static bool  IntersectBox(ABox rt1, ABox rt2, ABox* rt);
};

