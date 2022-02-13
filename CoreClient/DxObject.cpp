#include "DxObject.h"

void ADxObject::SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext)
{
	m_pd3dDevice = m_pd3dDevice;
	m_pContext = m_pContext;
}
bool ADxObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, AVector2 vPos, float fWidth, float fHeight)
{
	SetDevice(pd3dDevice, pContext);
	HRESULT hr;
	m_vPos = vPos;
	Convert(m_vPos, fWidth, fHeight, m_VertexList);

	//GPU메모리에 버퍼 할당 (원하는 크기로)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(ASimplevertex) * m_VertexList.size();
	bd.Usage=D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer)))
	{
		return false;
	}

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
	if (FAILED(hr))
	{
		return false;
	}

	hr = D3DCompileFromFile(L"PixelShader.txt", NULL, NULL, "PS", "ps_5_0", 0, 0, &m_pPSCodeResult, &m_pErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)m_pErrorMsgs->GetBufferPointer(), "ERROR", MB_OK);
		if (m_pErrorMsgs) m_pErrorMsgs->Release();
		return false;
	}
	hr = m_pd3dDevice->CreateVertexShader(m_pVSCodeResult->GetBufferPointer(),m_pVSCodeResult->GetBufferSize(),
		NULL,&m_pVertexShader);
	if (FAILED(hr))
	{
		return false;
	}

	//정점쉐이더의 결과를 통해서 정점레이아웃을 생성한다.
	//정점버퍼의 각 정점의 어떤 성분을 정점쉐이더에 전달할건지 


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

bool ADxObject::Init() {}
bool ADxObject::Frame() {}
bool ADxObject::Render() {}
bool ADxObject::Release() {}

ADxObject::ADxObject() {}
ADxObject::~ADxObject() {}