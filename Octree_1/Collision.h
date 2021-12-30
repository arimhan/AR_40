#pragma once
#include "Vector3.h"
//enum class : c++11지원 , 모든 열거자를 열거형 일부로 간주하므로 범위한정자를 꼭 사용할 것!
enum class ACollisionType { RECT_OUT = 0, RECT_IN = 1, RECT_OVERLAP = 3, };

struct ABox //3D
{
	AVector3 vMin;
	AVector3 vMax;
	AVector3 vMiddle;
	AVector3 vSize;

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
	static bool BoxToPoint(ABox rt, int x, int y, int z); //3D box와 point 충돌 체크
	static bool BoxToPoint(ABox rt, AVector3 v); //rect와 vector 비교
	static ACollisionType BoxToBox(ABox, ABox); //Rect충돌값 반환값 0, 1, 2로 처리 => enum 
	static ABox UnionBox(ABox rt1, ABox rt2); //합집합
	static bool IntersectBox(ABox rt1, ABox rt2, ABox* rt); //교집합
};



