#include "Object.h"
bool AObject::Update(AVector3 vVelocity, float time)
{
	AVector3 pos = m_vPos;
	pos = m_vPos + vVelocity * time * m_fSpeed;
	SetPosition(pos.x, pos.y, pos.z);
	return true;
}
void AObject::SetPos(AVector3 pos)
{
	m_vPos = pos;
}
void AObject::SetPos(float x, float y, float z)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
}
void AObject::SetPosition(float x, float y, float z)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
	AVector3 vMin;
	vMin.x = m_vPos.x - (m_rt.vSize.x / 2);
	vMin.y = m_vPos.y - (m_rt.vSize.y / 2);
	vMin.z = m_vPos.z - (m_rt.vSize.z / 2);
	ABox rt(vMin, (m_rt.vSize.x / 2) * 2.0f, (m_rt.vSize.y / 2) * 2.0f, (m_rt.vSize.z / 2) * 2.0f);
	SetBox(rt);
}
void AObject::SetBox(ABox rt)
{
	m_rt = rt;
}
