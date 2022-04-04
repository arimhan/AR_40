#include "FbxLoader.h"

//FbxObject.cpp
bool AFbxObject::SetIndexData() { return true; }
bool AFbxObject::CreateVertexBuffer()	
{
	if (m_pSubVertexList.size() <= 0) return false;
	HRESULT hr;

	for(int iMtrl = 0; iMtrl < m_pSubVertexList.size(); iMtrl++)
	{ 
		if (m_pSubVertexList[iMtrl].size() <= 0) continue;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(AVertex) * m_pSubVertexList[iMtrl].size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &m_pSubVertexList.at(0);

		if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVBList[iMtrl])))
		{
			return false;
		}
	}
	return true;
}
bool AFbxObject::SetVertexData()		
{
	//m_pVBList 를 m_pSubVertexList크기만큼 리사이즈 하여 사용한다.
	if (m_pSubVertexList.size() > 0)
	{
		m_pVBList.resize(m_pSubVertexList.size());
	}
	return true;
}
bool AFbxObject::PostRender()			
{
	UINT StartSlot;
	UINT NumBuffers;
	UINT Strides = sizeof(AVertex);
	UINT Offset = 0;

	for(int iMtrl = 0; iMtrl < m_pSubVertexList.size(); iMtrl++)
	{
		if (m_pTextureList.size() > 0 && m_pTextureList[iMtrl] != nullptr)
		{
			m_pContext->PSSetShaderResources(0, 1, m_pTextureList[iMtrl]->m_pSRV.GetAddressOf());
		}
		m_pContext->IASetVertexBuffers(0, 1, &m_pVBList[iMtrl], &Strides, &Offset);

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
bool AFbxObject::Release()				
{
	AObject3D::Release();
	for (int iVb = 0; iVb < m_pVBList.size(); iVb++)
	{
		if (m_pVBList[iVb] != nullptr)
		{
			m_pVBList[iVb]->Release();
		}
	}
	return true;
}