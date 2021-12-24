#pragma once
#include "Vector2.h"
//enum class : c++11���� , ��� �����ڸ� ������ �Ϻη� �����ϹǷ� ���������ڸ� �� ����� ��!
enum class ACollisionType {  RECT_OUT = 0, RECT_IN = 1, RECT_OVERLAP = 3,};

struct ARect
{
	AVector2 vMin;
	AVector2 vMax;
	AVector2 middle;
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
		middle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	};
	ARect(AVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + AVector2(w,h);
		middle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	};
};
class ACollision
{
public:
	static bool RectToPoint(ARect rt, int x, int y); //IsRect -> RectToRect
	static bool RectToPoint(ARect rt, AVector2 v);
	static ACollisionType RectToRect(ARect, ARect); //Rect�浹�� ��ȯ�� 0, 1, 2�� ó�� => enum 
	static ARect UnionRect(ARect r1, ARect r2); //������
	static bool IntersectRect(ARect rt1, ARect rt2, ARect* rt); //������
};


