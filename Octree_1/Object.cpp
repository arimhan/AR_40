#include "Object.h"
void AObject::SetPos(AVector3 pos)
{
	m_vPos = pos;
}
void AObject::SetPos(float x, float y, float z)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.y = z;
//Rect m_rt�� ������ �Ǿ�� pNode�� ����ȴ� (depth ����)
//�̰� main���� ó���ϴ� setpos���� ó���ϴ� �� ���� ó�� �ʿ�
	//vMin.x = m_vPos.x - (m_rt.size.x / 2);
	//ARect rt(vMin.(m_rt.size.x / 2) * 2.0f);
	//SetRect(rt);

}
void AObject::SetRect(ARect rt)
{
	m_rt = rt;
}
void AObject::SetBox(ABox box)
{
	m_box = box;
}
