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
bool ACollision::UnionRect(ARect rt1, ARect rt2) //합집합
{
	//화면 내 지름 W 보다 rt1의 지름 + rt2의 지름의 합이 크거나 같으면 충돌처리
	ARect rt;

	return true;
}
bool ACollision::IntersectRect(ARect rt1, ARect rt2, ARect* pRect) //교집합
{

	return true;
}