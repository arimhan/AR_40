#include "Collision.h"

Box Collision::UnionRegion(const Box& r1, const Box& r2)
{
	Box rt;
	rt.vMin.x = r1.vMin.x < r2.vMin.x ? r1.vMin.x : r2.vMin.x; 
	// (����)? A : B ; ���׿�����
	//rt.vMin.x�� ����
	//r1.vMin.x�� ������ r2.vMin.x ���� ũ��? -> r1.vMinx.2�� ���� �־��ְ�
	//�ƴϸ� r2.Min.x�� ���� �־���.
	rt.vMin.y = r1.vMin.y < r2.vMin.y ? r1.vMin.y : r2.vMin.y;
	rt.vMin.z = r1.vMin.z < r2.vMin.z ? r1.vMin.z : r2.vMin.z;
	//���������� rt.vMin, Max�� x,y,z�� ���� ��� r2�� ũ�� r1��, r1�� ũ�� r2�� �־��ش�.

	rt.vMax.x = r1.vMax.x < r2.vMax.x ? r1.vMax.x : r2.vMax.x;
	rt.vMax.y = r1.vMax.y < r2.vMax.y ? r1.vMax.y : r2.vMax.y;
	rt.vMax.z = r1.vMax.z < r2.vMax.z ? r1.vMax.z : r2.vMax.z;

	//������ ��. rt.vSize.x�� rt.vMax.x - rt.vMin.x �� ��
	rt.vSize.x = rt.vMax.x - rt.vMin.x;
	rt.vSize.y = rt.vMax.y - rt.vMin.y;
	rt.vSize.z = rt.vMax.z - rt.vMin.z;

	return rt;
}
bool Collision::IntersectRegion(const Box& r1, const Box& r2, Box* rtIntersect) //������
{
	Box rtUnion = UnionRegion(r1, r2); //�������� r1, r2���� �̿��ؼ�

	if (rtUnion.vSize.x > (r1.vSize.x + r2.vSize.x) &&
		rtUnion.vSize.y > (r1.vSize.y + r2.vSize.y) &&
		rtUnion.vSize.z > (r1.vSize.z + r2.vSize.z))
	{
		if (rtIntersect != nullptr)
			//rtIntersect�� ������� ������ (null�� �ƴϸ� �Ʒ� ���� ����)
		{
			//rtIntersect->vMin.x, y, z����
			// r1.vMin.x���� r2.vMin.x���� ũ�� r1.vMin.x�� �ְ�, ������ r2.vMin.x���� ����.
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