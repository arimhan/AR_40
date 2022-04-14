#include "FbxImporter.h"


void AWeight::InsertWeight(int iBoneIndex, float fBoneWeight)
{
	for (DWORD i = 0; i < Index.size(); ++i)
	{
		if (fBoneWeight > Weight[i])
		{
			for (DWORD j = (Index.size() - 1); j > i; --j)
			{
				Index[j] = Index[j - 1];
				Weight[j] = Weight[j - 1];
			}
			Index[i] = iBoneIndex;
			Weight[i] = fBoneWeight;
			break;
		}
	}
}

bool AFbxModel::SetVertexData()
{
	//m_pVBList 를 m_pSubVertexList크기만큼 리사이즈 하여 사용한다.
	if (m_pSubVertexList.size() > 0)
	{
		m_pVBList.resize(m_pSubVertexList.size());
	}
	if (m_pSubIWVertexList.size() > 0)
	{
		m_pVBWeightList.resize(m_pSubIWVertexList.size());
	}
	return true;
}

bool AFbxModel::CreateVertexBuffer()
{
	if (m_pSubVertexList.size() <= 0) return false;
	HRESULT hr;

	for (int iMtrl = 0; iMtrl < m_pSubVertexList.size(); iMtrl++)
	{
		if (m_pSubVertexList[iMtrl].size() <= 0) continue;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(AVertex) * m_pSubVertexList[iMtrl].size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &m_pSubVertexList[iMtrl].at(0);

		if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVBList[iMtrl])))
		{
			return false;
		}
	}
	for (int iMtrl = 0; iMtrl < m_pSubIWVertexList.size(); iMtrl++)
	{
		if (m_pSubIWVertexList[iMtrl].size() <= 0) continue;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(AVertexIW) * m_pSubIWVertexList[iMtrl].size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &m_pSubIWVertexList[iMtrl].at(0);

		if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVBWeightList[iMtrl])))
		{
			return false;
		}
	}
	return true;
}

bool AFbxModel::SetIndexData() { return true; }

bool AFbxModel::CreateIndexBuffer()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,		0,0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,12,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,24,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT,		0,40,	D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{"INDEX",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1,0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"WEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1,16,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT,		1,32,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = m_pd3dDevice->CreateInputLayout(
		layout,
		NumElements,
		m_pVShader->m_pVSCodeResult->GetBufferPointer(),
		m_pVShader->m_pVSCodeResult->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool AFbxModel::PostRender()
{
	UINT StartSlot;
	UINT NumBuffers;
	UINT Strides[2] = { sizeof(AVertex), sizeof(AVertexIW) };
	UINT Offsets[2] = { 0, };

	for (int iMtrl = 0; iMtrl < m_pSubVertexList.size(); iMtrl++)
	{
		if (m_pTextureList.size() > 0 && m_pTextureList[iMtrl] != nullptr)
		{
			m_pContext->PSSetShaderResources(0, 1, m_pTextureList[iMtrl]->m_pSRV.GetAddressOf());
		}

		ID3D11Buffer* buffer[2] = { m_pVBList[iMtrl], m_pVBWeightList[iMtrl] };
		m_pContext->IASetVertexBuffers(0, 2, buffer, Strides, Offsets);

		if (m_IndexList.size() <= 0)
		{
			m_pContext->Draw(m_pSubVertexList[iMtrl].size(), 0);
		}
		else
		{
			m_pContext->DrawIndexed(m_IndexList.size(), 0, 0);
		}
	}
	return true;
}

bool AFbxModel::Release()
{
	AObject3D::Release();
	for (int iVb = 0; iVb < m_pVBList.size(); iVb++)
	{
		if (m_pVBList[iVb] != nullptr)
		{
			m_pVBList[iVb]->Release();
		}
	}
	for (int iVb = 0; iVb < m_pVBWeightList.size(); iVb++)
	{
		if (m_pVBWeightList[iVb] != nullptr)
		{
			m_pVBWeightList[iVb]->Release();
		}
	}
	return true;
}

void AFbxModel::GenAABB()
{
	m_BoxCollision.vMin = T::TVector3(100000, 100000, 100000);
	m_BoxCollision.vMax = T::TVector3(-100000, -100000, -100000);

	for (int iMtrl = 0; iMtrl < m_pSubVertexList.size(); iMtrl++)
	{
		for(int i = 0; i<m_pSubVertexList[iMtrl].size(); i++)
		{
			//박스 충돌값의 min, max의 x,y,z값을 비교한다. (충돌값 체크)
			if (m_BoxCollision.vMin.x > m_pSubVertexList[iMtrl][i].p.x)
			{
				m_BoxCollision.vMin.x = m_pSubVertexList[iMtrl][i].p.x;
			}
			if (m_BoxCollision.vMin.y > m_pSubVertexList[iMtrl][i].p.y)
			{
				m_BoxCollision.vMin.y = m_pSubVertexList[iMtrl][i].p.y;
			}
			if (m_BoxCollision.vMin.z > m_pSubVertexList[iMtrl][i].p.z)
			{
				m_BoxCollision.vMin.z = m_pSubVertexList[iMtrl][i].p.z;
			}
			//max 체크
			if (m_BoxCollision.vMax.x < m_pSubVertexList[iMtrl][i].p.x)
			{
				m_BoxCollision.vMax.x = m_pSubVertexList[iMtrl][i].p.x;
			}
			if (m_BoxCollision.vMax.y < m_pSubVertexList[iMtrl][i].p.y)
			{
				m_BoxCollision.vMax.y = m_pSubVertexList[iMtrl][i].p.y;
			}
			if (m_BoxCollision.vMax.z < m_pSubVertexList[iMtrl][i].p.z)
			{
				m_BoxCollision.vMax.z = m_pSubVertexList[iMtrl][i].p.z;
			}
		}
	}

	m_BoxCollision.vList[0] = T::TVector3(//각VB의 좌표값을 위치 min,max로 표기한다. (-1,1,-1)
		m_BoxCollision.vMin.x, m_BoxCollision.vMax.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[1] = T::TVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMax.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[2] = T::TVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMin.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[3] = T::TVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMin.y, m_BoxCollision.vMin.z);

	m_BoxCollision.vList[4] = T::TVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMax.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[5] = T::TVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMax.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[6] = T::TVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMin.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[7] = T::TVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMin.y, m_BoxCollision.vMax.z);
}
