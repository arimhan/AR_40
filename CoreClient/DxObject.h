#pragma once
#include "Std.h"
#include <d3dcompiler.h>
#pragma comment (lib, "d3dcompiler.lib")
struct ASimplevertex
{
	AVector2 v;
};
class ADxObject
{
	float					m_fSpeed;
	AVector2				m_vPos;
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
	bool Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, AVector2 vPos, float fWidth, float fHeight);

	void Convert(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList);
	//화면좌표 위치를 중점으로 NDC 변환
	void Convert(vector<ASimplevertex>& list, vector<ASimplevertex>& retList);
	//화면좌표계를 NDC로 변환

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	ADxObject();
	~ADxObject();
};

