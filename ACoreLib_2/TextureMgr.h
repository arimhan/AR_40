#pragma once
#include "BaseMgr.h"

//TextureMgr ÂüÁ¶
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"
#pragma comment	(lib, "d3dcompiler.lib")

class ATexture
{
public:
	int									m_iIndex;
	wstring								m_csName;
	wstring								m_szMsg;
	TCHAR								m_szBuffer[256];
	ComPtr<ID3D11Texture2D>				m_pTexture;
	ComPtr<ID3D11ShaderResourceView>	m_pSRV;
	D3D11_TEXTURE2D_DESC				m_TextureDesc;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool	Load(ID3D11Device* pd3dDevice, wstring filename);
public:
	ATexture();
	virtual ~ATexture();
};

class ATextureMgr : public ABaseMgr<ATexture, ATextureMgr>
{
	friend class ASingleton<ATextureMgr>;
public:
	static HRESULT SaveFile(ID3D11DeviceContext* pContext, ID3D11Texture2D* pRes, T_STR name);
	static HRESULT SaveFile(ID3D11DeviceContext* pContext, IDXGISwapChain* pSwapChain, T_STR name);
private:
	ATextureMgr() {};
public:
	~ATextureMgr() {};
};
#define I_Texture ATextureMgr::Get()