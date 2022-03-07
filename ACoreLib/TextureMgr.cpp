#include "TextureMgr.h"

bool ATexture::Load(ID3D11Device* pd3dDevice, wstring filename)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(pd3dDevice,
		filename.c_str(),
		(ID3D11Resource**)m_pTexture.GetAddressOf(), m_pSRV.GetAddressOf());
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(pd3dDevice,
			filename.c_str(),
			(ID3D11Resource**)m_pTexture.GetAddressOf(), m_pSRV.GetAddressOf());
		if (FAILED(hr)) { return false; }
	}
	m_pTexture->GetDesc(&m_TextureDesc);
	return true;
}
bool ATexture::Init() { return true; }
bool ATexture::Frame() { return true; }
bool ATexture::Render() { return true; }
bool ATexture::Release() { return true; }

