#include "Frustum.h"
//#include "DxObject.h"

bool AFrustum::Init() 
{
	// 0	1
	//
	// 3	2
	// 
	// 4	5
	//
	// 7	6

	m_vFrustum[0] = TVector3(-1.0f, -1.0f,  0.0f);
	m_vFrustum[1] = TVector3(-1.0f,  1.0f,  0.0f);
	m_vFrustum[2] = TVector3( 1.0f,  1.0f,  0.0f);
	m_vFrustum[3] = TVector3( 1.0f, -1.0f,  0.0f);

	m_vFrustum[4] = TVector3(-1.0f, -1.0f,  1.0f);
	m_vFrustum[5] = TVector3(-1.0f,  1.0f,  1.0f);
	m_vFrustum[6] = TVector3( 1.0f,  1.0f,  1.0f);
	m_vFrustum[7] = TVector3( 1.0f, -1.0f,  1.0f);

	return true;
}
void AFrustum::CreateFrustum(T::TMatrix& matView, T::TMatrix& matProj) 
{
	m_vFrustum[0] = TVector3(-1.0f, -1.0f, 0.0f);
	m_vFrustum[1] = TVector3(-1.0f,  1.0f, 0.0f);
	m_vFrustum[2] = TVector3( 1.0f,  1.0f, 0.0f);
	m_vFrustum[3] = TVector3( 1.0f, -1.0f, 0.0f);

	m_vFrustum[4] = TVector3(-1.0f, -1.0f, 1.0f);
	m_vFrustum[5] = TVector3(-1.0f,  1.0f, 1.0f);
	m_vFrustum[6] = TVector3( 1.0f,  1.0f, 1.0f);
	m_vFrustum[7] = TVector3( 1.0f, -1.0f, 1.0f);

	//역행렬 처리
	T::TMatrix matInverse;
	T::D3DXMatrixMultiply(&matInverse, &matView, &matProj);
	T::D3DXMatrixInverse(&matInverse, NULL, &matInverse);

	for (int iVer = 0; iVer < 8; iVer++)
	{
		T::D3DXVec3TransformCoord(&m_vFrustum[iVer], &m_vFrustum[iVer], &matInverse);
		//m_vFrustum[iVer] = &m_vFrustum[iVer].xyz, w = 1.0f * matInverse;
	}
	if (m_VertexList.size() > 0)
	{
		int index = 0;
		m_VertexList[index].  p = m_vFrustum[6];
		m_VertexList[++index].p = m_vFrustum[5];
		m_VertexList[++index].p = m_vFrustum[7];
		m_VertexList[++index].p = m_vFrustum[4];
		// -Z plane
		m_VertexList[++index].p = m_vFrustum[1];
		m_VertexList[++index].p = m_vFrustum[2];
		m_VertexList[++index].p = m_vFrustum[0];
		m_VertexList[++index].p = m_vFrustum[3];
		// +X plane
		m_VertexList[++index].p = m_vFrustum[2];
		m_VertexList[++index].p = m_vFrustum[6];
		m_VertexList[++index].p = m_vFrustum[3];
		m_VertexList[++index].p = m_vFrustum[7];
		// -X plane
		m_VertexList[++index].p = m_vFrustum[5];
		m_VertexList[++index].p = m_vFrustum[1];
		m_VertexList[++index].p = m_vFrustum[4];
		m_VertexList[++index].p = m_vFrustum[0];
		// -y plane
		m_VertexList[++index].p = m_vFrustum[0];
		m_VertexList[++index].p = m_vFrustum[3];
		m_VertexList[++index].p = m_vFrustum[4];
		m_VertexList[++index].p = m_vFrustum[7];
		// +y plane
		m_VertexList[++index].p = m_vFrustum[5];
		m_VertexList[++index].p = m_vFrustum[6];
		m_VertexList[++index].p = m_vFrustum[1];
		m_VertexList[++index].p = m_vFrustum[2];
		
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	}

	m_Plane[0] = T::TPlane(m_vFrustum[0], m_vFrustum[1], m_vFrustum[2]);
	m_Plane[1] = T::TPlane(m_vFrustum[6], m_vFrustum[5], m_vFrustum[4]);
	m_Plane[2] = T::TPlane(m_vFrustum[5], m_vFrustum[1], m_vFrustum[0]);
	m_Plane[3] = T::TPlane(m_vFrustum[2], m_vFrustum[6], m_vFrustum[7]);
	m_Plane[4] = T::TPlane(m_vFrustum[7], m_vFrustum[4], m_vFrustum[0]);
	m_Plane[5] = T::TPlane(m_vFrustum[5], m_vFrustum[6], m_vFrustum[1]);

}

BOOL AFrustum::ClassifyPoint(T::TVector3* v) 
{
	for (int i = 0; i < 6; i++)
	{
		float pToc = 
			m_Plane[i].x * v->x +
			m_Plane[i].y * v->y +
			m_Plane[i].z * v->z +
			m_Plane[i].w;
		if (pToc > 0.0f)
		{
			return FALSE;
		}
	}
	return TRUE;
}
BOOL AFrustum::ClassifySphere(ASphere* v)
{
	for (int i = 0; i < 6; i++)
	{
		float pToc = 
			m_Plane[i].x * v->vCenter.x +
			m_Plane[i].y * v->vCenter.y +
			m_Plane[i].z * v->vCenter.z + 
			m_Plane[i].w;
		if (pToc >= v->fRadius)
		{
			return FALSE;
		}
	}
	return TRUE;
}
BOOL AFrustum::ClassifyOBB(ABox* v) 
{
	float sum = 0.0f;
	T::TVector3 vDir;	//3점이 있어야 Direction을 구할 수 있음

	for (int i = 0; i < 6; i++)
	{
		//0,1,2(즉 x,y,z축일 때 마다 같은 계산공식을 실행한다)
		vDir = v->vAxis[0] * v->size.x;
		sum = fabs(m_Plane[i].x * vDir.x + m_Plane[i].y * vDir.y + m_Plane[i].z * vDir.z);
		vDir = v->vAxis[1] * v->size.y;
		sum += fabs(m_Plane[i].x * vDir.x + m_Plane[i].y * vDir.y + m_Plane[i].z * vDir.z);
		vDir = v->vAxis[2] * v->size.z;
		sum += fabs(m_Plane[i].x * vDir.x + m_Plane[i].y * vDir.y + m_Plane[i].z * vDir.z);

		float pToc = m_Plane[i].x * v->vMiddle.x + m_Plane[i].y * v->vMiddle.y + 
			m_Plane[i].z * v->vMiddle.z + m_Plane[i].w;

		if (pToc >= sum) { return FALSE; }
	}
	return TRUE;
}

bool AFrustum::SetVertexData() 
{
	// 0   1
	//
	// 3   2
	m_VertexList.resize(24); // VB 4 * 6면 = 24
	//-Z

	int index = 0;
	//+Z
	m_VertexList[index].p = T::	 TVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::	 TVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = T::	 TVector4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::	 TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::	 TVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = T::	 TVector4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::	 TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::	 TVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = T::	 TVector4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::	 TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::	 TVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = T::	 TVector4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::	 TVector2(1.0f, 1.0f);

	// -Z plane
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 1.0f);


	// +X plane
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::  TVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::  TVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 1.0f);

	// -X plane
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::  TVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(0.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(0.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::  TVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(0.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(0.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 1.0f);

	// -y plane
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(0.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(0.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(0.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(0.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 1.0f);

	// +y plane
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::  TVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = T::  TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::  TVector2(1.0f, 1.0f);

	return true;
}
bool AFrustum::SetIndexData() 
{
	m_IndexList.push_back(0);   m_IndexList.push_back(1);   m_IndexList.push_back(2);
	m_IndexList.push_back(2);   m_IndexList.push_back(1);   m_IndexList.push_back(3);
	m_IndexList.push_back(4);   m_IndexList.push_back(5);   m_IndexList.push_back(6);
	m_IndexList.push_back(6);   m_IndexList.push_back(5);   m_IndexList.push_back(7);
	m_IndexList.push_back(8);   m_IndexList.push_back(9);   m_IndexList.push_back(10);
	m_IndexList.push_back(10);  m_IndexList.push_back(9);   m_IndexList.push_back(11);
	m_IndexList.push_back(12);  m_IndexList.push_back(13);  m_IndexList.push_back(14);
	m_IndexList.push_back(14);  m_IndexList.push_back(13);  m_IndexList.push_back(15);
	m_IndexList.push_back(16);  m_IndexList.push_back(17);  m_IndexList.push_back(18);
	m_IndexList.push_back(18);  m_IndexList.push_back(17);  m_IndexList.push_back(19);
	m_IndexList.push_back(20);  m_IndexList.push_back(21);  m_IndexList.push_back(22);
	m_IndexList.push_back(22);  m_IndexList.push_back(21);  m_IndexList.push_back(23);

	return true;
}
bool AFrustum::PostRender() 
{
	if (m_IndexList.size() <= 0)
	{
		m_pContext->Draw(m_VertexList.size(), 0);
	}
	else
	{
		m_pContext->DrawIndexed(m_IndexList.size(), 0, 0);
	}
	return true;
}