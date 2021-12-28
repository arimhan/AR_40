#pragma once
#include "Std.h"
#include <d3dcompiler.h>
#pragma comment (lib, "d3dcompiler.lib")
struct SimpleVertex
{
	AVector2 v;
};
class ADxObject
{
	float					m_fSpeed;
	AVector2				m_vPos;
	vector<SimpleVertex>	m_InitScreenList;
	vector<SimpleVertex>	m_VertexList;
	ID3D11Buffer*			m_pVertexBuffer;
	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11PixelShader*		m_pPixelShader;

	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pContext;

public:
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
	bool Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, AVector2 pos, float fWidth, float fHeight);
	void Convert(AVector2 center, float fWidth, float fHeight, vector<SimpleVertex>& retList);
	void Convert(vector<SimpleVertex> & list, vector<SimpleVertex>& retlist);

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	ADxObject();
	~ADxObject();

};

