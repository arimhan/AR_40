#include "Object3D.h"

void AObject3D::AddPosition(A::AVector3 vPos)
{
	m_vPos += vPos;

	SetVertexData();
	SetIndexData();
	if (m_pContext != nullptr)
	{
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	}
}

void AObject3D::SetPosition(A::AVector3 vPos)
{
	m_vPos = vPos;
	//행렬의 이동성분이 들어가는 41~43성분에 각 x,y,z값을 넣어 이동처리를 할 수 있도록 한다.
	m_matWorld._41 = m_vPos.x;
	m_matWorld._42 = m_vPos.y;
	m_matWorld._43 = m_vPos.z;
}

bool AObject3D::SetVertexData() { return true; }
bool AObject3D::SetIndexData()
{
	m_IndexList.clear();
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	//m_IndexList.push_back(1); m_IndexList.push_back(3); m_IndexList.push_back(2);
	return true;
}
void AObject3D::FadeIn()
{
	m_fAlpha += g_fSecPerFrame * 0.5f;
	m_fAlpha = min(m_fAlpha, 1.0f);
	if (m_fAlpha >= 1.0f) { m_bFadeIn = false; }
}
void AObject3D::FadeOut()
{
	m_fAlpha = m_fAlpha - g_fSecPerFrame * 0.5f;
	m_fAlpha = max(m_fAlpha, 0.0f);
	if (m_fAlpha <= 0.0f) { m_bFadeOut = false; }
}
bool AObject3D::Frame()
{
	if (m_bFadeIn)	FadeIn();
	if (m_bFadeOut)	FadeOut();
	m_ConstantList.Color = m_vColor;
	m_ConstantList.Timer = A::AVector4(g_fGameTimer, 0, 0, 1.0f);
	//m_pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);
	return true;
}

bool AObject3D::Load(ID3D11Device* pd3dDevice, wstring filename) { return true; };
void AObject3D::UpdateData() 
{
	//카메라 행렬 세팅
	//Right(우측, 사이드), Up(Top), Look(eye) 3가지 관점에서의 벡터값
	//Right -> Light?
	m_vRight.x = m_matWorld._11;
	m_vRight.y = m_matWorld._12;
	m_vRight.z = m_matWorld._13;

	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;

	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;

	A::D3DXVec3Normalize(&m_vRight, &m_vRight);
	A::D3DXVec3Normalize(&m_vUp, &m_vUp);
	A::D3DXVec3Normalize(&m_vLook, &m_vLook);
}
void AObject3D::SetMatrix(A::AMatrix* matWorld, A::AMatrix* matView, A::AMatrix* matProj)
{
	//각 월드 전환 시 필요한 값 세팅 
	//상수버퍼리스트 내 월드행렬 전치시킨다.해당하는 행렬이 존재하면 현재 받은 행렬을 전치시킨다.
	m_ConstantList.matWorld = m_matWorld.Transpose();
	if (matWorld != nullptr)
	{
		m_matWorld = *matWorld;
		m_ConstantList.matWorld = matWorld->Transpose();
	}
	if (matView != nullptr)
	{
		m_matWorld = *matView;
		m_ConstantList.matView = matView->Transpose();
	}
	if (matProj != nullptr)
	{
		m_matWorld = *matProj;
		m_ConstantList.matProj = matProj->Transpose();
	}

	A::D3DXMatrixInverse(&m_ConstantList.matNormal, NULL, &m_matWorld);
	A::D3DXMatrixTranspose(&m_ConstantList.matNormal, &m_ConstantList.matNormal);
	A::D3DXMatrixTranspose(&m_ConstantList.matNormal, &m_ConstantList.matNormal);
	UpdateData();
	UpdateCollision();
}

void AObject3D::UpdateCollision()
{
	m_BoxCollision.vAxis[0] = m_vRight;		//vLight로 변경하기?
	m_BoxCollision.vAxis[1] = m_vUp;
	m_BoxCollision.vAxis[2] = m_vLook;

	//GenAABB();
	m_BoxCollision.vMin = A::AVector3(100000, 100000, 100000);
	m_BoxCollision.vMax = A::AVector3(-100000, -100000, -100000);

	//m_VertexList.size();
	for (int i = 0; i < 8; i++)
	{
		A::AVector3 pos;
		A::D3DXVec3TransformCoord(&pos, &m_BoxCollision.vList[i], &m_matWorld);
		//박스 충돌값의 min, max의 x,y,z값을 비교한다. (충돌값 체크)
		if (m_BoxCollision.vMin.x > pos.x)
		{
			m_BoxCollision.vMin.x = pos.x;
		}
		if (m_BoxCollision.vMin.y > pos.y)
		{
			m_BoxCollision.vMin.y = pos.y;
		}
		if (m_BoxCollision.vMin.z > pos.z)
		{
			m_BoxCollision.vMin.z = pos.z;
		}
		//max 체크
		if (m_BoxCollision.vMax.x < pos.x)
		{
			m_BoxCollision.vMax.x = pos.x;
		}
		if (m_BoxCollision.vMax.y < pos.y)
		{
			m_BoxCollision.vMax.y = pos.y;
		}
		if (m_BoxCollision.vMax.z < pos.z)
		{
			m_BoxCollision.vMax.z = pos.z;
		}
	}
	A::AVector3 vHalf = m_BoxCollision.vMax - m_BoxCollision.vMiddle;	//Center;
	m_BoxCollision.size.x = fabs(A::D3DXVec3Dot(&m_BoxCollision.vAxis[0], &vHalf));
	m_BoxCollision.size.y = fabs(A::D3DXVec3Dot(&m_BoxCollision.vAxis[1], &vHalf));
	m_BoxCollision.size.z = fabs(A::D3DXVec3Dot(&m_BoxCollision.vAxis[2], &vHalf));
	m_BoxCollision.vMiddle = (m_BoxCollision.vMin + m_BoxCollision.vMax);
	m_BoxCollision.vMiddle /= 2.0f;
}

void AObject3D::GenAABB()
{
	//AABB구현
	m_BoxCollision.vMin = A::AVector3(100000, 100000, 100000);
	m_BoxCollision.vMax = A::AVector3(-100000, -100000, -100000);

	for (int i = 0; i < m_VertexList.size(); i++)
	{
		//박스 충돌값의 min, max의 x,y,z값을 비교한다. (충돌값 체크)
		if (m_BoxCollision.vMin.x > m_VertexList[i].p.x)
		{
			m_BoxCollision.vMin.x = m_VertexList[i].p.x;
		}
		if (m_BoxCollision.vMin.y > m_VertexList[i].p.y)
		{
			m_BoxCollision.vMin.y = m_VertexList[i].p.y;
		}
		if (m_BoxCollision.vMin.z > m_VertexList[i].p.z)
		{
			m_BoxCollision.vMin.z = m_VertexList[i].p.z;
		}
		//max 체크
		if (m_BoxCollision.vMax.x < m_VertexList[i].p.x)
		{
			m_BoxCollision.vMax.x = m_VertexList[i].p.x;
		}
		if (m_BoxCollision.vMax.y < m_VertexList[i].p.y)
		{
			m_BoxCollision.vMax.y = m_VertexList[i].p.y;
		}
		if (m_BoxCollision.vMax.z < m_VertexList[i].p.z)
		{
			m_BoxCollision.vMax.z = m_VertexList[i].p.z;
		}
	}

	// 4     5
	// 
	// 6     7

	// 0     1
	// 
	// 2     3
	m_BoxCollision.vList[0] = A::AVector3(//각VB의 좌표값을 위치 min,max로 표기한다. (-1,1,-1)
		m_BoxCollision.vMin.x, m_BoxCollision.vMax.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[1] = A::AVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMax.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[2] = A::AVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMin.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[3] = A::AVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMin.y, m_BoxCollision.vMin.z);

	m_BoxCollision.vList[4] = A::AVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMax.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[5] = A::AVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMax.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[6] = A::AVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMin.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[7] = A::AVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMin.y, m_BoxCollision.vMax.z);
}


AObject3D::AObject3D()
{
	m_fAlpha = 1.0f;
	m_vColor = A::AVector4(1, 1, 1, 1);

	//카메라 행렬 세팅
	m_vRight.x = 1;
	m_vRight.y = 0;
	m_vRight.z = 0;

	m_vUp.x = 0;
	m_vUp.y = 1;
	m_vUp.z = 0;

	m_vLook.x = 0;
	m_vLook.y = 0;
	m_vLook.z = 1;

	m_BoxCollision.vAxis[0] = A::AVector3(1, 0, 0);
	m_BoxCollision.vAxis[1] = A::AVector3(0, 1, 0);
	m_BoxCollision.vAxis[2] = A::AVector3(0, 0, 1);
	m_BoxCollision.size.x = 1.0f;
	m_BoxCollision.size.y = 1.0f;
	m_BoxCollision.size.z = 1.0f;
	m_BoxCollision.vMin = A::AVector3(-1.0f, -1.0f, -1.0f);
	m_BoxCollision.vMax = A::AVector3(1.0f, 1.0f, 1.0f);
}
AObject3D::~AObject3D() {}