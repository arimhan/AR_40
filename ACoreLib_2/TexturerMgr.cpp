#include "TextureMgr.h"
#include <wincodec.h>
#include <wincodecsdk.h>
#include <ScreenGrab.h> //- dds.h(direct TX안에 있는 화면 캡쳐, 저장하는 기능)
//Shadow를 텍스쳐로 저장해서 만들기 때문에 필요하다.


bool ATexture::Load(ID3D11Device* pd3dDevice, wstring filename)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(pd3dDevice, filename.c_str(),
		(ID3D11Resource**)m_pTexture.GetAddressOf(), m_pSRV.GetAddressOf());
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(pd3dDevice, filename.c_str(),
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


//SaveFile 함수
HRESULT ATextureMgr::SaveFile(ID3D11DeviceContext* pContext, ID3D11Texture2D* pRes, T_STR name) 
{
	HRESULT hr = S_OK;
	ComPtr<ID3D11Texture2D> tex = pRes;
	GUID fileformat = GUID_ContainerFormatPng;
	WCHAR ext[_MAX_EXT];
	_wsplitpath_s(name.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
	T_STR tExt = ext;

	//확장자가 dds, 그 외 일 경우 분리해서 저장
	if (tExt == L".dds" || tExt.empty())
	{
		if (tExt.empty())
		{
			hr = DirectX::SaveDDSTextureToFile(pContext, tex.Get(), (name + L".dds").c_str());
		}
		else
		{
			hr = DirectX::SaveDDSTextureToFile(pContext, tex.Get(), name.c_str());
		}
	}
	else
	{
		if (tExt == L".bmp") fileformat = GUID_ContainerFormatBmp;
		if (tExt == L".png") fileformat = GUID_ContainerFormatPng;
		if (tExt == L".ico") fileformat = GUID_ContainerFormatIco;
		if (tExt == L".jpg") fileformat = GUID_ContainerFormatJpeg;
		if (tExt == L".tif") fileformat = GUID_ContainerFormatTiff;
		hr = DirectX::SaveWICTextureToFile(pContext, tex.Get(), fileformat, name.c_str());
	}

	if (pRes == nullptr) { tex->Release(); }

	return hr;
}
HRESULT ATextureMgr::SaveFile(ID3D11DeviceContext* pContext, IDXGISwapChain* pSwapChain, T_STR name) 
{
	HRESULT hr = S_OK;
	ComPtr<ID3D11Texture2D> tex;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)tex.GetAddressOf());

	if (SUCCEEDED(hr))
	{
		GUID fileformat = GUID_ContainerFormatPng;
		WCHAR ext[_MAX_EXT];
		_wsplitpath_s(name.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
		T_STR tExt = ext;

		//확장자가 dds, 그 외 일 경우 분리해서 저장
		if (tExt == L".dds" || tExt.empty())
		{
			if (tExt.empty())
			{
				hr = DirectX::SaveDDSTextureToFile(pContext, tex.Get(), (name + L".dds").c_str());
			}
			else
			{
				hr = DirectX::SaveDDSTextureToFile(pContext, tex.Get(), name.c_str());
			}
		}
		else
		{
			if (tExt == L".bmp") fileformat = GUID_ContainerFormatBmp;
			if (tExt == L".png") fileformat = GUID_ContainerFormatPng;
			if (tExt == L".ico") fileformat = GUID_ContainerFormatIco;
			if (tExt == L".jpg") fileformat = GUID_ContainerFormatJpeg;
			if (tExt == L".tif") fileformat = GUID_ContainerFormatTiff;
			hr = DirectX::SaveWICTextureToFile(pContext, tex.Get(), fileformat, name.c_str());
		}
	}
	
	return hr;
}

ATexture::ATexture(){}
ATexture::~ATexture(){}

