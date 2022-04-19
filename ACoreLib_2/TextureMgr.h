#pragma once
#include "BaseMgr.h"
//#include <wincodec.h>
//#include <wincodecsdk.h>
//#include <ScreenGrab.h> - dds.h(direct TX안에 있는 화면 캡쳐, 저장하는 기능)
//Shadow를 텍스쳐로 저장해서 만들기 때문에 필요하다.
//TextureMgr 참조
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
private:
	ATextureMgr() {};
public:
	~ATextureMgr() {};
};
#define I_Texture ATextureMgr::Get()