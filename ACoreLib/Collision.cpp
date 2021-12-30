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
ARect ACollision::UnionRect(ARect rt1, ARect rt2) //������
{
	//ȭ�� �� ���� W ���� rt1�� ���� + rt2�� ������ ���� ũ�ų� ������ �浹ó��
	ARect rt;

	//rect�� min.x���� (���� ���� �� ã�� �ֱ�) : rt1�� rt2�� min.x�� �� rt1�� x���� ������ �װ� �ְ� false�� rt2�� x�� ��ȯ
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
//������ : rt1,rt2�� �������� ����� rect�� ��ġ���� ��ȯ�Ѵٰ� ����
//�׷��Ƿ� rt1�� vMin.x,y < rt2�� v.Min.x,y�� ��, �������� ����� ��ġ�� �ּҰ�(��������)�� rt2�� vMin.x,y��
//�׸��� rt1�� vMax.x,y < rt2�� vMax.x,y�� ��, �������� ����� �ִ밪(������ ����)�� vMax.x,y���� rt1�� vMax.x,y���� ��ȯ�Ѵ�
{
	ARect rt;
	ARect rtUnion = UnionRect(rt1, rt2);
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) && rtUnion.size.y <= (rt1.size.y + rt2.size.y))
	{
		if (pRect != nullptr)
		{
			//�������� ���������� �� ū ���� vMin.x,y���� ��ȯ�Ѵ�
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ? rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ? rt2.vMin.y : rt1.vMin.y;

			//�������� �� ������ �� ���� ���� vMax.x,y���� ��ȯ�Ѵ�
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
//Rect�浹�� ��ȯ�� 0, 1, 2�� ó�� => enum 
//IntersectRect���� �������� ���� ��, �浹üũ�� �Ѵ�.
{
	ARect rtInterection;
	int iRet = IntersectRect(rt1, rt2, &rtInterection);
	if (iRet <= 0) //�浹X
	{
		return ACollisionType::RECT_OUT;
	}
	if (rtInterection == rt2) return ACollisionType::RECT_OVERLAP;
	//rt2�� rtInterection�� ������ ������. (Ȯ�� �ʿ�)
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

	rt.size = rt.vMax - rt.vMin; // rect�� �޸� size�� vMax - vMin�� ����ص� �ȴ�
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

