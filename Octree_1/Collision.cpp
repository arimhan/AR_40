#include "Collision.h"

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

	rt.vSize = rt.vMax - rt.vMin; // rect와 달리 size는 vMax - vMin만 계산해도 된다
	rt.vMiddle = (rt.vMin + rt.vMax) / 2.0f;
	return rt;
}
bool ACollision::IntersectBox(ABox rt1, ABox rt2, ABox* pRect)
{
	ABox rt;
	ABox rtUnion = UnionBox(rt1, rt2);
	if (rtUnion.vSize.x <= (rt1.vSize.x + rt2.vSize.x) &&
		rtUnion.vSize.y <= (rt1.vSize.y + rt2.vSize.y) &&
		rtUnion.vSize.z <= (rt1.vSize.z + rt2.vSize.z))
	{
		if (pRect != nullptr)
		{
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ? rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ? rt2.vMin.y : rt1.vMin.y;
			pRect->vMin.z = rt1.vMin.z < rt2.vMin.z ? rt2.vMin.z : rt1.vMin.z;

			pRect->vMax.x = rt1.vMax.x < rt2.vMax.x ? rt1.vMax.x : rt2.vMax.x;
			pRect->vMax.y = rt1.vMax.y < rt2.vMax.y ? rt1.vMax.y : rt2.vMax.y;
			pRect->vMax.z = rt1.vMax.z < rt2.vMax.z ? rt1.vMax.z : rt2.vMax.z;

			pRect->vSize = pRect->vMax - pRect->vMin;
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

