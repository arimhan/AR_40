#pragma once
#include "Vector3.h"
//enum class : c++11���� , ��� �����ڸ� ������ �Ϻη� �����ϹǷ� ���������ڸ� �� ����� ��!
enum class ACollisionType { RECT_OUT = 0, RECT_IN = 1, RECT_OVERLAP = 3, };

struct ABox //3D
{
	AVector3 vMin;
	AVector3 vMax;
	AVector3 vMiddle;
	AVector3 vSize;

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
		vSize.x = vMax.x - vMin.x;
		vSize.y = vMax.y - vMin.y;
		vSize.z = vMax.z - vMin.z;
	};
	ABox(AVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + AVector3(w, h, q);
		vMiddle = (vMax + vMin) / 2.0f;
		this->vSize.x = w;
		this->vSize.y = h;
		this->vSize.z = q;
	};
};
class ACollision
{
public:
	//3D (ABox)
	static bool BoxToPoint(ABox rt, int x, int y, int z); //3D box�� point �浹 üũ
	static bool BoxToPoint(ABox rt, AVector3 v); //rect�� vector ��
	static ACollisionType BoxToBox(ABox, ABox); //Rect�浹�� ��ȯ�� 0, 1, 2�� ó�� => enum 
	static ABox UnionBox(ABox rt1, ABox rt2); //������
	static bool IntersectBox(ABox rt1, ABox rt2, ABox* rt); //������
};



