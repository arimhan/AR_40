#include "Object3D.h"

void AObject3D::AddPosition(AVector3 vPos)
{
	m_vPos += vPos;

	SetVertexData();
	SetIndexData();
	if (m_pContext != nullptr)
	{
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	}
}

void AObject3D::SetPosition(AVector3 vPos)
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
	m_IndexList.push_back(1); m_IndexList.push_back(3); m_IndexList.push_back(2);
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
	m_ConstantList.Timer = AVector4(g_fGameTimer, 0, 0, 1.0f);
	//m_pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);
	return true;
}

bool AObject3D::Load(ID3D11Device* pd3dDevice, wstring filename) { return true; };
void AObject3D::UpdateData() {}
void AObject3D::SetMatrix(AMatrix* matWorld, AMatrix* matView, AMatrix* matProj)
{
	//각 월드 전환 시 필요한 값 세팅 
	//상수버퍼리스트 내 월드행렬 전치시킨다.해당하는 행렬이 존재하면 현재 받은 행렬을 전치시킨다.
	m_ConstantList.matWorld = m_matWorld.Transpose();
	if (matWorld != nullptr)
	{
		m_ConstantList.matWorld = matWorld->Transpose();
	}
	if (matView != nullptr)
	{
		m_ConstantList.matView = matView->Transpose();
	}
	if (matProj != nullptr)
	{
		m_ConstantList.matProj = matProj->Transpose();
	}

	//카메라 행렬 세팅
	m_vLight.x = m_matWorld._11;
	m_vLight.y = m_matWorld._12;
	m_vLight.z = m_matWorld._13;

	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;

	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;

}



AObject3D::AObject3D()
{
	m_fAlpha = 1.0f;
	m_vColor = AVector4(1, 1, 1, 1);

	//카메라 행렬 세팅
	m_vLight.x = 1;
	m_vLight.y = 0;
	m_vLight.z = 0;

	m_vUp.x = 0;
	m_vUp.y = 1;
	m_vUp.z = 0;

	m_vLook.x = 0;
	m_vLook.y = 0;
	m_vLook.z = 1;
}
AObject3D::~AObject3D() {}