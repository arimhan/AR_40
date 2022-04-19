#pragma once
#include "BaseMgr.h"
//#include <wincodec.h>
//#include <wincodecsdk.h>
//#include <ScreenGrab.h> - dds.h(direct TX�ȿ� �ִ� ȭ�� ĸ��, �����ϴ� ���)
//Shadow�� �ؽ��ķ� �����ؼ� ����� ������ �ʿ��ϴ�.
//TextureMgr ����
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