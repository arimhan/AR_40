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
//Rect m_rt가 변경이 되어야 pNode가 변경된다 (depth 변경)
//이걸 main에서 처리하던 setpos에서 처리하던 값 변경 처리 필요
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
