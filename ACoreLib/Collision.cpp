#include "Collision.h"

bool ACollision::RectToPoint(ARect rt, int x, int y)
{
	if (rt.vMin.x <= x && rt.vMax.x >= x && rt.vMin.y <= y && rt.vMax.y >= y)
	{
		return true;
	}
	return false;
}
bool ACollision::RectToPoint(ARect rt, AVector2 v)
{
	if (rt.vMin.x <= v.x && rt.vMax.x >= v.x && rt.vMin.y <= v.y && rt.vMax.y >= v.y)
	{
		return true;
	}
	return false;
}
ARect ACollision::UnionRect(ARect rt1, ARect rt2) //합집합
{
	//화면 내 지름 W 보다 rt1의 지름 + rt2의 지름의 합이 크거나 같으면 충돌처리
	ARect rt;

	//rect의 min.x값은 (가장 작은 값 찾아 넣기) : rt1과 rt2의 min.x값 중 rt1의 x값이 작으면 그거 넣고 false면 rt2의 x값 반환
	rt.vMin.x = rt1.vMin.x < rt2.vMin.x ? rt1.vMin.x : rt2.vMin.x;
	rt.vMin.y = rt1.vMin.y < rt2.vMin.y ? rt1.vMin.y : rt2.vMin.y;
	rt.vMax.x = rt1.vMax.x < rt2.vMax.x ? rt2.vMax.x : rt1.vMax.x;
	rt.vMax.y = rt1.vMax.y < rt2.vMax.y ? rt2.vMax.y : rt1.vMax.y;
	rt.size.x = rt.vMax.x - rt.vMin.x;
	rt.size.y = rt.vMax.y - rt.vMin.y;
	rt.vMiddle = (rt.vMin + rt.vMax) / 2.0f;
	return rt;
}
bool ACollision::IntersectRect(ARect rt1, ARect rt2, ARect* pRect) 
//교집합 : rt1,rt2의 교집합이 생기는 rect의 위치값을 반환한다고 생각
//그러므로 rt1의 vMin.x,y < rt2의 v.Min.x,y일 때, 교집합이 생기는 위치는 최소값(시작지점)인 rt2의 vMin.x,y값
//그리고 rt1의 vMax.x,y < rt2의 vMax.x,y일 때, 교집합이 생기는 최대값(마지막 지점)인 vMax.x,y값인 rt1의 vMax.x,y값을 반환한다
{
	ARect rt;
	ARect rtUnion = UnionRect(rt1, rt2);
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) && rtUnion.size.y <= (rt1.size.y + rt2.size.y))
	{
		if (pRect != nullptr)
		{
			//교집합의 시작지점은 더 큰 쪽의 vMin.x,y값을 반환한다
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ? rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ? rt2.vMin.y : rt1.vMin.y;

			//교집합의 끝 지점은 더 작은 쪽의 vMax.x,y값을 반환한다
			pRect->vMax.x = rt1.vMax.x < rt2.vMax.x ? rt1.vMax.x : rt2.vMax.x;
			pRect->vMax.y = rt1.vMax.y < rt2.vMax.y ? rt1.vMax.y : rt2.vMax.y;

			pRect->size.x = pRect->vMax.x - pRect->vMin.x;
			pRect->size.y = pRect->vMax.y - pRect->vMin.y;
			pRect->vMiddle = (pRect->vMax + pRect->vMin) / 2.0f;
		}
		return true;
	}
	return false;
}
ACollisionType ACollision::RectToRect(ARect rt1, ARect rt2) 
//Rect충돌값 반환값 0, 1, 2로 처리 => enum 
//IntersectRect에서 교집합을 만든 뒤, 충돌체크를 한다.
{
	ARect rtInterection;
	int iRet = IntersectRect(rt1, rt2, &rtInterection);
	if (iRet <= 0) //충돌X
	{
		return ACollisionType::RECT_OUT;
	}
	if (rtInterection == rt2) return ACollisionType::RECT_OVERLAP;
	//rt2와 rtInterection가 같으면 겹쳐짐. (확인 필요)
	return ACollisionType::RECT_IN;
}
bool ACollision::BoxToPoint(ABox rt, int x, int y, int z) 
{
	if (rt.vMin.x <= x && rt.vMax.x >= x &&
		rt.vMin.y <= y && rt.vMax.y >= y &&
		rt.vMin.z <= z && rt.vMax.z >= z)
	{
		return true;
	}
	return false;
}
bool ACollision::BoxToPoint(ABox rt, AVector3 v) 
{
	if (rt.vMin.x <= v.x && rt.vMax.x >= v.x &&
		rt.vMin.y <= v.y && rt.vMax.y >= v.y &&
		rt.vMin.z <= v.z && rt.vMax.z >= v.z)
	{
		return true;
	}
	return false;
}
ABox ACollision::UnionBox(ABox rt1, ABox rt2) 
{
	ABox rt;
	rt.vMin.x = rt1.vMin.x < rt2.vMin.x ? rt1.vMin.x : rt2.vMin.x;
	rt.vMin.y = rt1.vMin.y < rt2.vMin.y ? rt1.vMin.y : rt2.vMin.y;
	rt.vMin.z = rt1.vMin.z < rt2.vMin.z ? rt1.vMin.z : rt2.vMin.z;

	rt.vMax.x = rt1.vMax.x < rt2.vMax.x ? rt2.vMax.x : rt1.vMax.x;
	rt.vMax.y = rt1.vMax.y < rt2.vMax.y ? rt2.vMax.y : rt1.vMax.y;
	rt.vMax.z = rt1.vMax.z < rt2.vMax.z ? rt2.vMax.z : rt1.vMax.z;

	rt.size = rt.vMax - rt.vMin; // rect와 달리 size는 vMax - vMin만 계산해도 된다
	rt.vMiddle = (rt.vMin + rt.vMax) / 2.0f;
	return rt;
}
bool ACollision::IntersectBox(ABox rt1, ABox rt2, ABox* pRect) 
{ 
	ABox rt;
	ABox rtUnion = UnionBox(rt1, rt2);
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) &&
		rtUnion.size.y <= (rt1.size.y + rt2.size.y) &&
		rtUnion.size.z <= (rt1.size.z + rt2.size.z))
	{
		if (pRect != nullptr)
		{
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ? rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ? rt2.vMin.y : rt1.vMin.y;
			pRect->vMin.z = rt1.vMin.z < rt2.vMin.z ? rt2.vMin.z : rt1.vMin.z;

			pRect->vMax.x = rt1.vMax.x < rt2.vMax.x ? rt1.vMax.x : rt2.vMax.x;
			pRect->vMax.y = rt1.vMax.y < rt2.vMax.y ? rt1.vMax.y : rt2.vMax.y;
			pRect->vMax.z = rt1.vMax.z < rt2.vMax.z ? rt1.vMax.z : rt2.vMax.z;

			pRect->size = pRect->vMax - pRect->vMin;
			pRect->vMiddle = (pRect->vMax + pRect->vMin) / 2.0f;
		}
		return true;
	}
	return false;
}
ACollisionType ACollision::BoxToBox(ABox rt1, ABox rt2) 
{
	ABox rtInterction;
	int iRet = IntersectBox(rt1, rt2, &rtInterction);
	if (iRet <= 0)
	{
		return ACollisionType::RECT_OUT;
	}
	if (rtInterction == rt2) return ACollisionType::RECT_OVERLAP;
	return ACollisionType::RECT_IN;
}

