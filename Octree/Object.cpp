#include "Object.h"
void AObject::SetPos(AVector2 pos)
{
	m_vPos = pos;
}
void AObject::SetPos(float x, float y)
{
	m_vPos.x = x;
	m_vPos.y = y;
}
void AObject::SetRect(ARect rt)
{
	m_rt = rt;
}
