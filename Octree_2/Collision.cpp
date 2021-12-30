#include "Collision.h"

Box Collision::UnionRegion(const Box& r1, const Box& r2)
{
	Box rt;
	rt.vMin.x = r1.vMin.x < r2.vMin.x ? r1.vMin.x : r2.vMin.x; 
	// (조건)? A : B ; 삼항연산자
	//rt.vMin.x의 값은
	//r1.vMin.x의 값보다 r2.vMin.x 값이 크다? -> r1.vMinx.2의 값을 넣어주고
	//아니면 r2.Min.x의 값을 넣어줌.
	rt.vMin.y = r1.vMin.y < r2.vMin.y ? r1.vMin.y : r2.vMin.y;
	rt.vMin.z = r1.vMin.z < r2.vMin.z ? r1.vMin.z : r2.vMin.z;
	//마찬가지로 rt.vMin, Max의 x,y,z의 값이 모두 r2가 크면 r1을, r1이 크면 r2를 넣어준다.

	rt.vMax.x = r1.vMax.x < r2.vMax.x ? r1.vMax.x : r2.vMax.x;
	rt.vMax.y = r1.vMax.y < r2.vMax.y ? r1.vMax.y : r2.vMax.y;
	rt.vMax.z = r1.vMax.z < r2.vMax.z ? r1.vMax.z : r2.vMax.z;

	//사이즈 비교. rt.vSize.x는 rt.vMax.x - rt.vMin.x 의 값
	rt.vSize.x = rt.vMax.x - rt.vMin.x;
	rt.vSize.y = rt.vMax.y - rt.vMin.y;
	rt.vSize.z = rt.vMax.z - rt.vMin.z;

	return rt;
}
bool Collision::IntersectRegion(const Box& r1, const Box& r2, Box* rtIntersect) //교집합
{
	Box rtUnion = UnionRegion(r1, r2); //합집합의 r1, r2값을 이용해서

	if (rtUnion.vSize.x > (r1.vSize.x + r2.vSize.x) &&
		rtUnion.vSize.y > (r1.vSize.y + r2.vSize.y) &&
		rtUnion.vSize.z > (r1.vSize.z + r2.vSize.z))
	{
		if (rtIntersect != nullptr)
			//rtIntersect이 비어있지 않으면 (null이 아니면 아래 조건 진행)
		{
			//rtIntersect->vMin.x, y, z값에
			// r1.vMin.x값이 r2.vMin.x보다 크면 r1.vMin.x를 넣고, 작으면 r2.vMin.x값을 넣음.
			rtIntersect->vMin.x = r1.vMin.x > r2.vMin.x ? r1.vMin.x : r2.vMin.x;
			rtIntersect->vMin.y = r1.vMin.y > r2.vMin.y ? r1.vMin.y : r2.vMin.y;
			rtIntersect->vMin.z = r1.vMin.z > r2.vMin.z ? r1.vMin.z : r2.vMin.z;
			rtIntersect->vMax.x = r1.vMax.x > r2.vMax.x ? r2.vMax.x : r1.vMax.x;
			rtIntersect->vMax.y = r1.vMax.y > r2.vMax.y ? r2.vMax.y : r1.vMax.y;
			rtIntersect->vMax.z = r1.vMax.z > r2.vMax.z ? r2.vMax.z : r1.vMax.z;

			rtIntersect->vSize = rtIntersect->vMax - rtIntersect->vMin;
			rtIntersect->vCenter = (rtIntersect->vMax + rtIntersect->vMin) / 2.0f;

			rtIntersect->vPivot.x = rtIntersect->vMin.x;
			rtIntersect->vPivot.y = rtIntersect->vMin.y;
			rtIntersect->vPivot.z = rtIntersect->vMax.z;
		}
		return true;
	}
	return false;
}