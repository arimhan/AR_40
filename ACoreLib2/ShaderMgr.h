#pragma once
#include "BaseMgr.h"
#include <d3dcompiler.h>
class AShader
{
public:
	int						m_iIndex;
	wstring					m_csName;
	wstring					m_szMsg;
	TCHAR					m_szBuffer[256];
	ID3D11VertexShader*		m_pVertexShader = nullptr;
	ID3D11PixelShader*		m_pPixelShader = nullptr;
	ID3DBlob*				m_pVSCodeResult = nullptr;
	ID3DBlob*				m_pErrorMsgs = nullptr;
	ID3DBlob*				m_pPSCodeResult = nullptr;
public:	
	virtual bool    CreateVertexShader(ID3D11Device* pd3dDevice, 
		wstring filename, string entry="VS");
	virtual bool    CreatePixelShader(ID3D11Device* pd3dDevice, 
		wstring filename, string entry="PS");
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool	Load(ID3D11Device* pd3dDevice, std::wstring filename);
public:
	AShader();
	virtual ~AShader();
};

class AShaderMgr :  public ABaseMgr<AShader, AShaderMgr>
{
	friend class ASingleton<AShaderMgr>;
public:
	AShader* CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry);
	AShader* CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry);
private:
	AShaderMgr();
public:
	~AShaderMgr();
};
#define I_Shader AShaderMgr::Get()