#include "Collision.h"

bool ACollision::IsRect(int x, int y)
{
	if (m_rt.p1.x <= x && m_rt.p2.x >= x && m_rt.p1.y <= y && m_rt.p2.y >= y)
	{
		return true;
	}
	return false;
}

bool ACollision::RectToRect(ARect rt1, ARect rt2);
bool ACollision::UnionRect(ARect rt1, ARect rt2) //������
{
	//ȭ�� �� ���� W ���� rt1�� ���� + rt2�� ������ ���� ũ�ų� ������ �浹ó��
	ARect rt;

	return true;
}
bool ACollision::IntersectRect(ARect rt1, ARect rt2, ARect* pRect) //������
{

	return true;
}