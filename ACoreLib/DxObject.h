#pragma once
#include "Std.h"
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"
#pragma comment (lib, "d3dcompiler.lib")
struct ASimplevertex
{
	AVector2 v;
	AVector2 t;
};
class ADxObject
{
public:
	ID3D11ShaderResourceView*	m_pSRV0; //���� SRV 0��
	ID3D11ShaderResourceView*	m_pSRV1;
	ID3D11Texture2D*			m_pTexture0;
	ID3D11Texture2D*			m_pTexture1;
	ID3D11BlendState*			m_AlphaBlend;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;

public:
	float		m_fSpeed;
	AVector2	m_vPos;
	float		m_fWidth;
	float		m_fHeight;

public:
	vector<ASimplevertex>	m_InitScreenList;
	vector<ASimplevertex>	m_VertexList;
	ID3D11Buffer*			m_pVertexBuffer;
	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11PixelShader*		m_pPixelShader;

	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pContext;

	ID3DBlob*	m_pVSCodeResult = nullptr;
	ID3DBlob*	m_pErrorMsgs = nullptr;
	ID3DBlob*	m_pPSCodeResult = nullptr;

public:
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
	virtual bool LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
	virtual bool SetVertexData();
	virtual bool Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, 
		const TCHAR* szColorFileName =nullptr, const TCHAR* szMaskFileNmae= nullptr);

	void Convert(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList);
	//ȭ����ǥ ��ġ�� �������� NDC ��ȯ
	void Convert(vector<ASimplevertex>& list, vector<ASimplevertex>& retList);
	//ȭ����ǥ�踦 NDC�� ��ȯ

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	ADxObject();
	~ADxObject();
};

