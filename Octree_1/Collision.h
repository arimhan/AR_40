#pragma once
#include "Vector3.h"
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
struct ABox //3D
{
	AVector3 vMin;
	AVector3 vMax;
	AVector3 vMiddle;
	AVector3 size;

	bool operator ==(const ABox& v) //���⼭ �� �� �� p1 (�������κ���) p2(����, ũ�����)�� ���ϵ��� �Ѵ�.
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
	static bool RectToPoint(ABox rt, int x, int y); //IsRect -> RectToRect
	static bool RectToPoint(ABox rt, AVector3 v);
	static ACollisionType RectToRect(ABox, ABox); //Rect�浹�� ��ȯ�� 0, 1, 2�� ó�� => enum 
	static ABox UnionRect(ABox r1, ABox r2); //������
	static bool IntersectRect(ABox rt1, ABox rt2, ABox* rt); //������

	//3D (ABox)
	static bool BoxToPoint(ABox rt, int x, int y); //IsRect -> RectToRect
	static bool BoxToPoint(ABox rt, AVector3 v);
	static ACollisionType BoxToBox(ABox, ABox); //Rect�浹�� ��ȯ�� 0, 1, 2�� ó�� => enum 
	static ABox UnionBox(ABox r1, ABox r2); //������
	static bool IntersectBox(ABox rt1, ABox rt2, ABox* rt); //������

	//������� ������
};



