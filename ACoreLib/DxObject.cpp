#include "DxObject.h"

void ADxObject::SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext)
{
	m_pd3dDevice = m_pd3dDevice;
	m_pContext = m_pContext;
}
bool ADxObject::LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(m_pd3dDevice,
		szColorFileName,
		(ID3D11Resource**)&m_pTexture0,
		&m_pSRV0);
	if (FAILED(hr))
	{
		DirectX::CreateDDSTextureFromFile(m_pd3dDevice,
			szColorFileName,
			(ID3D11Resource**)&m_pTexture0,
			&m_pSRV0);
		if (FAILED(hr)) { return false; }

	}
	m_pTexture0->GetDesc(&m_TextureDesc);
	hr = DirectX::CreateDDSTextureFromFile(m_pd3dDevice, szMaskFileName, (ID3D11Resource**)&m_pTexture0, &m_pSRV0);
	if (FAILED(hr))
	{
		DirectX::CreateDDSTextureFromFile(m_pd3dDevice,
			szColorFileName,
			(ID3D11Resource**)&m_pTexture0,
			&m_pSRV0);
		if (FAILED(hr)) { return false; }

	}
	return true;
}
bool ADxObject::SetVertexData()
{
	return true;
}
bool ADxObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, const TCHAR* szColorFileName , const TCHAR* szMaskFileNmae )
{
	HRESULT hr;
	SetDevice(pd3dDevice, pContext);
	if (!LoadTexture(szColorFileName, szMaskFileNmae)) { return false; }
	if (!SetVertexData()) { return false; }
	

	//m_vPos = vPos;
	//Convert(m_vPos, fWidth, fHeight, m_VertexList);

	//GPU메모리에 버퍼 할당 (원하는 크기로)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(ASimplevertex) * m_VertexList.size();
	bd.Usage=D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer))) { return false; }

	//txt파일 생성 및 작성
	//쉐이더 컴파일 -> 오브젝트 파일을 통해서 쉐이더 객체 생성

	hr = D3DCompileFromFile(L"VertexShader.txt", NULL, NULL, "VS", "vs_5_0", 0, 0, &m_pVSCodeResult, &m_pErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)m_pErrorMsgs->GetBufferPointer(), "ERROR", MB_OK);
		if (m_pErrorMsgs) m_pErrorMsgs->Release();
		return false;
	}
	hr = m_pd3dDevice->CreateVertexShader(    
		m_pVSCodeResult->GetBufferPointer(),
		m_pVSCodeResult->GetBufferSize(),
		NULL,
		&m_pVertexShader);
	if (FAILED(hr)) { return false; }

	hr = D3DCompileFromFile(L"PixelShader.txt", NULL, NULL, "PS", "ps_5_0", 0, 0, &m_pPSCodeResult, &m_pErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)m_pErrorMsgs->GetBufferPointer(), "ERROR", MB_OK);
		if (m_pErrorMsgs) m_pErrorMsgs->Release();
		return false;
	}
	hr = m_pd3dDevice->CreateVertexShader(m_pVSCodeResult->GetBufferPointer(),m_pVSCodeResult->GetBufferSize(),
		NULL,&m_pVertexShader);
	if (FAILED(hr)) { return false; }

	//정점쉐이더의 결과를 통해서 정점레이아웃을 생성한다.
	//정점버퍼의 각 정점의 어떤 성분을 정점쉐이더에 전달할건지 
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	hr = m_pd3dDevice->CreateInputLayout(layout, NumElements,
		m_pVSCodeResult->GetBufferPointer(), m_pVSCodeResult->GetBufferSize(), &m_pVertexLayout);
	if (FAILED(hr)) { return false; }

	D3D11_BLEND_DESC blenddesc;
	ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
	//blenddesc.AlphaToCoverageEnable;
	//blenddesc.IndependentBlendEnable;
	blenddesc.RenderTarget[0].BlendEnable = TRUE;
	blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC1_ALPHA;
	blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	// 알파 연산 저장
	blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blenddesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_AlphaBlend);
	return true;
}
void ADxObject::Convert(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList)
{
	//화면좌표 위치를 중심으로 NDC 변환
	vector<ASimplevertex> list(6);
	float halfWidth = fWidth / 2.0f;
	float halfHeight = fHeight / 2.0f;

	//(0,0)부터 시계방향으로 0,1,2
	//2번부터 3,4,5
	list[0].v = { center.x - halfWidth, center.y - halfHeight };
	list[1].v = { center.x + halfWidth, center.y - halfHeight };
	list[2].v = { center.x - halfWidth, center.y + halfHeight };

	list[3].v = list[2].v;
	list[4].v = list[1].v;
	//(0,0)을 기준으로
	list[5].v = { center.x + halfWidth, center.y + halfHeight };
	Convert(list, retList);
}
void ADxObject::Convert(vector<ASimplevertex>& list, vector<ASimplevertex>& retList)
{
	//화면좌표계를 NDC로 변환
	retList.resize(list.size());
	for(int i=0; i < list.size(); i++)
	{
		// 0~ 800 -> 0~1 -> -1 ~ +1
		retList[i].v.x = list[i].v.x / g_rtClient.right;
		retList[i].v.y = list[i].v.y / g_rtClient.bottom;

		// 0 ~ 1 -> -1 ~ +1 .... -1 ~ +1 -> 0 ~ 1
		// x = x * 2 + -1  .... x = x * 0.5f + 0.5f
		retList[i].v.x = retList[i].v.x * 2.0f - 1.0f;
		retList[i].v.y = -1.0f * (retList[i].v.y * 2.0f - 1.0f);
	}

}

bool ADxObject::Init() { return true; }
bool ADxObject::Frame() { return true; }
bool ADxObject::Render() 
{
	m_pContext->PSSetShaderResources(0, 1, &m_pSRV0);
	m_pContext->PSSetShaderResources(1, 1, &m_pSRV1);
	m_pContext->OMSetBlendState(m_AlphaBlend, 0, -1);

	m_pContext->IASetInputLayout(m_pVertexLayout);
	m_pContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pContext->PSSetShader(m_pPixelShader, NULL, 0);

	UINT StartSlot;
	UINT NumBuffers;
	UINT strides = sizeof(ASimplevertex);
	UINT Offsets = 0;

	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &Offsets);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	/*D3D11_PRIMITIVE_TOPOLOGY_POINTLIST
	D3D11_PRIMITIVE_TOPOLOGY_LINELIST*/
	m_pContext->Draw(m_VertexList.size(), 0);
	return true;
}
bool ADxObject::Release() 
{
	if (m_AlphaBlend) m_AlphaBlend->Release();
	if (m_pTexture0)  m_pTexture0 ->Release();
	if (m_pTexture1)  m_pTexture1 ->Release();
	if (m_pSRV0)      m_pSRV0     ->Release();
	if (m_pSRV1)      m_pSRV1     ->Release();
	m_AlphaBlend   = nullptr;
	m_pTexture0	   = nullptr;
	m_pTexture1	   = nullptr;
	m_pSRV0		   = nullptr;
	m_pSRV1		   = nullptr;

	if (m_pVSCodeResult) m_pVSCodeResult->Release();
	if (m_pPSCodeResult) m_pPSCodeResult->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader)  m_pPixelShader ->Release();

	m_pVSCodeResult	   = nullptr;
	m_pPSCodeResult	   = nullptr;
	m_pVertexBuffer	   = nullptr;
	m_pVertexLayout	   = nullptr;
	m_pVertexShader	   = nullptr;
	m_pPixelShader	   = nullptr;

	return true;

}

ADxObject::ADxObject() { m_fSpeed = 0.0001f; }
ADxObject::~ADxObject() {}