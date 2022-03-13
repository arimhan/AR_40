#include "DxObject.h"
#include "ObjectMgr.h"
void ABaseObject::HitOverlap(ABaseObject* pObj, DWORD dwState){}
void ABaseObject::HitSelect(ABaseObject* pObj, DWORD dwState) { int k = 0; }
void ADxObject::SetDevice(ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext   = pContext;
}
bool ADxObject::LoadTexture(const TCHAR* szColorFileName,
	const TCHAR* szMaskFileName)
{
	m_pColorTex = I_Texture.Load(szColorFileName);
	if (szMaskFileName != nullptr)
	{
		m_pMaskTex = I_Texture.Load(szMaskFileName);
	}
	m_TextureDesc = m_pColorTex->m_TextureDesc;
	return true;
}
bool ADxObject::SetVertexData() { return true; }
bool ADxObject::SetIndexData() { return true; }
bool ADxObject::SetConstantData()
{
	ZeroMemory(&m_ConstantList, sizeof(AConstantData));
	m_ConstantList.Color.x = 0.0f;
	m_ConstantList.Color.y = 1.0f;
	m_ConstantList.Color.z = 0.0f;
	m_ConstantList.Color.w = 1.0f;
	m_ConstantList.Timer.x = 0.0f;
	m_ConstantList.Timer.y = 1.0f;
	m_ConstantList.Timer.z = 0.0f;
	m_ConstantList.Timer.w = 0.0f;
	return true;
}
bool ADxObject::CreateVertexShader(const TCHAR* szFile)
{
	m_pVSShader = I_Shader.CreateVertexShader(m_pd3dDevice, szFile, "VS");
	return true;
}
bool ADxObject::CreatePixelShader(const TCHAR* szFile)
{
	m_pPSShader = I_Shader.CreatePixelShader(m_pd3dDevice, szFile, "PS");
	return true;
}
bool ADxObject::CreateVertexBuffer()
{
	if (m_VertexList.size() <= 0) return false;
	HRESULT hr;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(ASimpleVertex) * m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer)))
	{
		return false;
	}
	return true;
}
bool ADxObject::CreateIndexBuffer()
{
	HRESULT hr;
	if (m_IndexList.size() <= 0) return true;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_IndexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer)))
	{
		return false;
	}
	return true;
}
bool ADxObject::CreateConstantBuffer()
{
	HRESULT hr;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(AConstantData);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_ConstantList;

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pConstantBuffer)))
	{
		return false;
	}
	return true;
}
bool ADxObject::CreateInputLayout()
{

	// 정점쉐이더의 결과를 통해서 정점레이아웃을 생성한다.	
	// 정점버퍼의 각 정점의 어떤 성분을 정점쉐이더에 전달할건지
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0, DXGI_FORMAT_R32G32_FLOAT, 0,0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT, 0,8,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = m_pd3dDevice->CreateInputLayout(
		layout,
		NumElements,
		m_pVSShader->m_pVSCodeResult->GetBufferPointer(),
		m_pVSShader->m_pVSCodeResult->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool ADxObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext,
	const TCHAR* szShaderFileName, const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{
	HRESULT hr;

	SetDevice(pd3dDevice, pContext);
	if (szColorFileName !=nullptr && !LoadTexture(szColorFileName, szMaskFileName))
	{
		return false;
	}
	if (!SetVertexData())
	{
		return false;
	}
	if (!SetIndexData())
	{
		return false;
	}
	if (!SetConstantData())
	{
		return false;
	}
	if (!CreateVertexBuffer())
	{
		return false;
	}
	if (!CreateIndexBuffer())
	{
		return false;
	}
	if (!CreateConstantBuffer())
	{
		return false;
	}
	if (szShaderFileName!= nullptr && 	!CreateVertexShader(szShaderFileName))
	{
		return false;
	}
	if (szShaderFileName != nullptr &&	!CreatePixelShader(szShaderFileName))
	{
		return false;
	}
	if (!CreateInputLayout())
	{
		return false;
	}
	return true;
}
bool ADxObject::Init()
{
	
	return true;
}
bool ADxObject::Frame()
{
	return true;
}
bool ADxObject::Render()
{	
	if(m_pColorTex!=nullptr)
		m_pContext->PSSetShaderResources(0, 1, 
			m_pColorTex->m_pSRV.GetAddressOf());
	if (m_pMaskTex != nullptr)
		m_pContext->PSSetShaderResources(1, 1, 
			m_pMaskTex->m_pSRV.GetAddressOf());
	if (m_pVSShader != nullptr)
	{
		m_pContext->VSSetShader(m_pVSShader->m_pVertexShader, NULL, 0);
	}
	if (m_pPSShader != nullptr)
	{
		m_pContext->PSSetShader(m_pPSShader->m_pPixelShader, NULL, 0);
	}

	if (m_bAlphaBlend)
	{
		m_pContext->OMSetBlendState(ADxState::m_AlphaBlend, 0, -1);
	}
	else
	{
		m_pContext->OMSetBlendState(ADxState::m_AlphaBlendDisable, 0, -1);
	}

	m_pContext->IASetInputLayout(m_pVertexLayout);
	

	UINT StartSlot;
	UINT NumBuffers;
	UINT Strides = sizeof(ASimpleVertex);
	UINT Offsets = 0;

	m_pContext->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer,
		&Strides, &Offsets);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		//D3D_PRIMITIVE_TOPOLOGY_POINTLIST
		//D3D_PRIMITIVE_TOPOLOGY_LINELIST
	);

	if( m_IndexList.size() <= 0)
		m_pContext->Draw(m_VertexList.size(), 0);
	else
		m_pContext->DrawIndexed(m_IndexList.size(), 0, 0);
	return true;
}
bool ADxObject::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();	
	if (m_pVertexLayout) m_pVertexLayout->Release();

	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_pConstantBuffer = nullptr;
	m_pVertexLayout = nullptr;
	return true;
}
ADxObject::ADxObject() { m_fSpeed = 0.0001f; }
ADxObject::~ADxObject(){}
