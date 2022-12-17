#include "Node.h"

void AMapObj::UpdateData()
{
	m_vRight.x = matWorld._11;
	m_vRight.y = matWorld._12;
	m_vRight.z = matWorld._13;

	m_vUp.x = matWorld._21;
	m_vUp.y = matWorld._22;
	m_vUp.z = matWorld._23;

	m_vLook.x = matWorld._31;
	m_vLook.y = matWorld._32;
	m_vLook.z = matWorld._33;

	A::D3DXVec3Normalize(&m_vRight, &m_vRight);
	A::D3DXVec3Normalize(&m_vUp, &m_vUp);
	A::D3DXVec3Normalize(&m_vLook, &m_vLook);
}

void AMapObj::UpdateCollision()
{
	box.vAxis[0] = m_vRight;
	box.vAxis[1] = m_vUp;
	box.vAxis[2] = m_vLook;

	//GenAABB();
	box.vMin = A::AVector3(100000, 100000, 100000);
	box.vMax = A::AVector3(-100000, -100000, -100000);

	for (int i = 0; i < 8; i++)
	{
		A::AVector3 pos;
		A::D3DXVec3TransformCoord(&pos, &box.vList[i], &matWorld);
		//박스 충돌값의 min, max의 x,y,z값을 비교한다. (충돌값 체크)
		if (box.vMin.x > pos.x)
		{
			box.vMin.x = pos.x;
		}
		if (box.vMin.y > pos.y)
		{
			box.vMin.y = pos.y;
		}
		if (box.vMin.z > pos.z)
		{
			box.vMin.z = pos.z;
		}
		//max 체크
		if (box.vMax.x < pos.x)
		{
			box.vMax.x = pos.x;
		}
		if (box.vMax.y < pos.y)
		{
			box.vMax.y = pos.y;
		}
		if (box.vMax.z < pos.z)
		{
			box.vMax.z = pos.z;
		}
	}
	A::AVector3 vHalf = box.vMax - box.vMiddle;
	box.size.x = fabs(A::D3DXVec3Dot(&box.vAxis[0], &vHalf));
	box.size.y = fabs(A::D3DXVec3Dot(&box.vAxis[1], &vHalf));
	box.size.z = fabs(A::D3DXVec3Dot(&box.vAxis[2], &vHalf));
	box.vMiddle = (box.vMin + box.vMax);
	box.vMiddle /= 2.0f;
}

void ANode::AddObject(AMapObj* pObj)
{
	m_pStaticObjList.push_back(pObj);
}

void ANode::AddDynamicObject(AMapObj* pObj)
{
	m_pDynamicObjList.push_back(pObj);
}

void ANode::DelDynamicObject(AMapObj* pObj)
{
	m_pDynamicObjList.clear();
}


ANode::ANode() 
{
	m_pParent = nullptr;
	m_iDepth = 0;
	for (list<AMapObj*>::iterator iter = m_pStaticObjList.begin(); 
		iter != m_pStaticObjList.end(); iter++)
	{
		AMapObj* pObj = *iter;
		delete pObj;
	}
	m_pStaticObjList.clear();
}
ANode::ANode(float x, float y, float w, float h) 
{
	m_CornerList.push_back(x);		m_CornerList.push_back(y);
	m_CornerList.push_back(w);		m_CornerList.push_back(h);

	m_pChild.resize(4);
	m_pChild[0], m_pChild[1], m_pChild[2], m_pChild[3] = nullptr;
	//m_pChild[0] = nullptr;  
	//m_pChild[1] = nullptr;  
	//m_pChild[2] = nullptr;  
	//m_pChild[3] = nullptr;
}
ANode::~ANode() 
{
	delete m_pChild[0], m_pChild[1], m_pChild[2], m_pChild[3];
	//delete m_pChild[0];
	//delete m_pChild[1];
	//delete m_pChild[2];
	//delete m_pChild[3];
}