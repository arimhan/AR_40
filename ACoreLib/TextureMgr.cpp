#include "TextureMgr.h"

bool ATexture::Load(ID3D11Device* pd3dDevice, wstring filename)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(pd3dDevice,
		filename.c_str(),
		(ID3D11Resource**)&m_pTexture, &m_pSRV);
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(pd3dDevice,
			filename.c_str(),
			(ID3D11Resource**)&m_pTexture, &m_pSRV);
		if (FAILED(hr)) { return false; }
	}
	m_pTexture->GetDesc(&m_TextureDesc);
}
bool ATexture::Init() { return true; }
bool ATexture::Frame() { return true; }
bool ATexture::Render() { return true; }
bool ATexture::Release()
{
	if (m_pTexture) m_pTexture->Release();
	if (m_pSRV)		m_pSRV->Release();

    return true;
}
