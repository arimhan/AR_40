#include "DxObject.h"

void ADxObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
}
void ADxObject::Convert(AVector2 center, float fWidth, float fHeight, vector<SimpleVertex>& retList)
{
	vector<SimpleVertex> list(6);
	float halfWidth = fWidth / 2.0f;
	float halfHeight = fHeight / 2.0f;
	list[0].v = { center.x - halfWidth, center.y - halfHeight };
	list[1].v = { center.x + halfWidth, center.y - halfHeight };
	list[2].v = { center.x - halfWidth, center.y + halfHeight };

	list[3].v = list[2].v;
	list[4].v = list[1].v;
	list[5].v = { center.x + halfWidth, center.y + halfHeight };

	Convert(list, retList);
}
void ADxObject::Convert(vector<SimpleVertex>& list, vector<SimpleVertex>& retList)
{
	retList.resize(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		retList[i].v.x = list[i].v.x / g_rtClient.right;
		retList[i].v.y = list[i].v.y / g_rtClient.bottom;

		retList[i].v.x = list[i].v.x * 2.0f - 1.0f;
		retList[i].v.y = -1.0f * (retList[i].v.y * 2.0f - 1.0f);
	}
}
bool ADxObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, AVector2 vPos, float fWidth, float fHeight)
{
	//if ((vPos.x - fWidth / 2.0f) < 0) return false; //vPos.x - (400/2) = -100 - 200 = -300 vPos값 확인
	//if ((vPos.x + fWidth / 2.0f) > g_rtClient.right) return false;
	//if ((vPos.y - fHeight / 2.0f) < 0) return false;
	//if ((vPos.y - fHeight / 2.0f) > g_rtClient.bottom) return false;
	SetDevice(pd3dDevice, pContext);
	HRESULT hr;

	m_vPos = vPos;
	Convert(m_vPos, fWidth, fHeight, m_VertexList);

	D3D11_BUFFER_DESC bd; //GUP 메모리에 원하는 할당 크기 만큼 버퍼 할당
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(SimpleVertex)* m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexList.at(0); //VertexList의 0번배열 주소값

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer))) { return false; };

	//txt - 쉐이더 컴파일 -> 오브젝트 파일을 통해서 쉐이더객체 생성
	ID3DBlob* pVSCodeResult = nullptr;
	ID3DBlob* pErrorMsgs = nullptr;
	hr = D3DCompileFromFile(L"VertexShader.txt", NULL, NULL, "VS", "vs_5_0", 0, 0, &pVSCodeResult, &pErrorMsgs);
	if (FAILED(hr)) 
	{
		MessageBoxA(NULL, (char*)pErrorMsgs->GetBufferPointer(), "ERROR", MB_OK); 
		return false;
	}
	hr = m_pd3dDevice->CreateVertexShader(pVSCodeResult->GetBufferPointer(), pVSCodeResult->GetBufferSize(), NULL, &m_pVertexShader);
	if (FAILED(hr)) { return false; };

	ID3DBlob* pPSCodeResult = nullptr;
	hr = D3DCompileFromFile(L"PixelShader.txt", NULL, NULL, "PS", "ps_5_0", 0, 0, &pPSCodeResult, &pErrorMsgs);

	if (FAILED(hr)) {
		MessageBoxA(NULL, (char*)pErrorMsgs->GetBufferPointer(), "ERROR", MB_OK);
		return false;
	}

	hr = m_pd3dDevice->CreatePixelShader(pPSCodeResult->GetBufferPointer(), pPSCodeResult->GetBufferSize(), NULL, &m_pPixelShader);
	if (FAILED(hr)) { return false; };

	//정점쉐이더의 결과를 통해서 정점레이아웃을 생성, 정점버퍼의 각 정점의 어떤 성분을 정점쉐이더에 전달할지.
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	hr = m_pd3dDevice->CreateInputLayout(layout, NumElements, pVSCodeResult->GetBufferPointer(), pVSCodeResult->GetBufferSize(), &m_pVertexLayout);
	if (FAILED(hr)) { return false; };
	return true;
}

bool ADxObject::Init()
{
	return true;
}
bool ADxObject::Frame()
{
	m_VertexList[0].v.x += m_fSpeed;
	m_VertexList[1].v.x += m_fSpeed;
	m_VertexList[2].v.x += m_fSpeed;
	m_VertexList[3].v.x += m_fSpeed;
	m_VertexList[4].v.x += m_fSpeed;
	m_VertexList[5].v.x += m_fSpeed;
	m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);

	return true;
}
bool ADxObject::Render()
{
	m_pContext->IASetInputLayout(m_pVertexLayout);
	m_pContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pContext->PSSetShader(m_pPixelShader, NULL, 0);

	UINT StartSlot;
	UINT NumBuffers;
	UINT Strides = sizeof(SimpleVertex);
	UINT Offsets = 0;  
	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer,&Strides, &Offsets);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw 전 값 세팅 후 화면에 출력
	m_pContext->Draw(m_VertexList.size(), 0);
	return true;
}
bool ADxObject::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	m_pVertexBuffer = nullptr;
	m_pVertexLayout = nullptr;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
	return true;
}
ADxObject::ADxObject() { m_fSpeed = 0.0001f; }
ADxObject::~ADxObject() { }