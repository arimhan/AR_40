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

	SetVertexData();
	SetIndexData();
	if (m_pContext != nullptr)
	{
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	}
}

bool AObject3D::SetVertexData()
{
	return true;
}
bool AObject3D::SetIndexData()
{
	m_IndexList.clear();
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	return true;
}
void AObject3D::FadeIn()
{
	m_fAlpha += g_fSecPerFrame * 0.5f;
	m_fAlpha = min(m_fAlpha, 1.0f);
	if (m_fAlpha >= 1.0f)
	{
		m_bFadeIn = false;
	}
}
void AObject3D::FadeOut()
{
	m_fAlpha = m_fAlpha - g_fSecPerFrame * 0.5f;
	m_fAlpha = max(m_fAlpha, 0.0f);
	if (m_fAlpha <= 0.0f)
	{
		m_bFadeOut = false;
	}
}
bool AObject3D::Frame()
{
	if (m_bFadeIn)	FadeIn();
	if (m_bFadeOut)	FadeOut();
	m_ConstantList.Color = m_vColor;
	m_ConstantList.Timer = AVector4(g_fGameTimer, 0, 0, 1.0f);
	m_pContext->UpdateSubresource(
		m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);
	return true;
}


bool AObject3D::Load(ID3D11Device* pd3dDevice, wstring filename) { return true; };
void AObject3D::UpdateData() {}
void AObject3D::SetMatrix(AMatrix* matWorld, AMatrix* matView, AMatrix* matProj)
{
	//각 월드 전환 시 필요한 값 세팅
	m_ConstantList.matWorld = m_matWorld.Transpose();
	if(matWorld != nullptr) 
	{ 
		m_ConstantList.matWorld = matWorld->Transpose(); 
	}
	if(matView != nullptr)
	{ 
		m_ConstantList.matView = matView->Transpose();
	}
	if (matProj != nullptr)
	{ 
		m_ConstantList.matProj = matProj->Transpose();
	}
}



AObject3D::AObject3D()
{
	m_fAlpha = 1.0f;
	m_vColor = AVector4(1, 1, 1, 1);
}
AObject3D::~AObject3D() {}