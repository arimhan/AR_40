#pragma once
#include "BaseMgr.h"
#include <d3dcompiler.h>

class AShader
{
public:
	int					m_iIndex;
	wstring				m_csName;
	wstring				m_szMsg;
	TCHAR				m_szBuffer[256];
	ID3D11VertexShader*	m_pVertexShader = nullptr;
	ID3D11PixelShader*	m_pPixelShader	= nullptr;
	ID3DBlob*			m_pVSCodeResult = nullptr;
	ID3DBlob*			m_pErrorMsgs	= nullptr;
	ID3DBlob*			m_pPSCodeResult = nullptr;
public:
	//Shader생성 시 entry를 지정하면 편리하다.
	virtual bool	CreateVertexShader(ID3D11Device* pd3dDevice, wstring filename, string entry="VS");
	virtual bool	CreatePixelShader(ID3D11Device* pd3dDevice, wstring filename, string entry = "PS");
	bool	Load(ID3D11Device* pd3dDevice, wstring filename);
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	AShader() {};
	virtual ~AShader() {};
};

class AShaderMgr :public ABaseMgr<AShader, AShaderMgr>
{
	friend class ASingleton<AShaderMgr>;
public:
	//Shader생성 시 entry를 지정하면 편리하다.
	AShader*	CreateVertexShader(ID3D11Device* pd3dDevice, wstring filename, string entry = "VS");
	AShader*	CreatePixelShader(ID3D11Device* pd3dDevice, wstring filename, string entry = "PS");
public:
	AShaderMgr() { m_iIndex = 0; };
	~AShaderMgr() { Release(); };
};
#define I_Shader AShaderMgr::Get()