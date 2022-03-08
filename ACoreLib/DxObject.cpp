#include "DxObject.h"
#include "ObjectMgr.h" //I_ObjectMgr. 사용
void ABaseObject::HitOverlap(ABaseObject* pObj, DWORD dwState) {}
void ABaseObject::HitSelect(ABaseObject* pObj, DWORD dwState){}
void ADxObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
}
bool ADxObject::LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
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
	ZeroMemory(&m_ConstantList, sizeof(AConstanceData));
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
//VertexBuffer, IndexBuffer, ConstantBuffer 생성 방법 동일------------
bool ADxObject::CreateVertexBuffer()
{
	if (m_VertexList.size() <= 0) return false;
	HRESULT hr;
	//m_vPos = vPos;
	//Convert(m_vPos, fWidth, fHeight, m_VertexList);
	//GPU메모리에 버퍼 할당 (원하는 크기로)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(ASimplevertex) * m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer))) { return false; }
	return true;
}
bool ADxObject::CreateIndexBuffer()
{
	HRESULT hr;
	if (m_IndexList.size() <= 0) return true;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_IndexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer))) { return false; }
	return true;
}
bool ADxObject::CreateConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(AConstanceData);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_ConstantList;

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pConstantBuffer))) { return false; }
	return true;
}
//Vertex, IndexBuffer 생성 ----------- 끝
bool ADxObject::CreateInputLayout()
{
	//정점쉐이더의 결과를 통해서 정점레이아웃을 생성한다.
	//정점버퍼의 각 정점의 어떤 성분을 정점쉐이더에 전달할건지 
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = m_pd3dDevice->CreateInputLayout(layout, NumElements,
		m_pVSShader->m_pVSCodeResult->GetBufferPointer(), 
		m_pVSShader->m_pVSCodeResult->GetBufferSize(), &m_pVertexLayout);
	if (FAILED(hr)) { return false; }
	return true;
}
bool ADxObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, 
	const TCHAR* szShaderFileName,const TCHAR* szColorFileName , const TCHAR* szMaskFileName )
{
	HRESULT hr;
	m_rtCollision = ARect(m_vPos, m_fWidth, m_fHeight);
	I_ObjectMgr.AddCollisionExecute(this, bind(&ABaseObject::HitOverlap, this, placeholders::_1, placeholders::_2));
	I_ObjectMgr.AddSelectExecute(this, bind(&ABaseObject::HitSelect, this, placeholders::_1, placeholders::_2));

	SetDevice(pd3dDevice, pContext);
	if (szColorFileName != nullptr && !LoadTexture(szColorFileName, szMaskFileName)) 
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
	if (szShaderFileName != nullptr && !CreateVertexShader(szShaderFileName))
	{
		return false;
	}
	if (szShaderFileName != nullptr && !CreatePixelShader(szShaderFileName))
	{
		return false;
	}
	if (!CreateInputLayout())
	{
		return false;
	}

	D3D11_BLEND_DESC blenddesc;
	ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
	//blenddesc.AlphaToCoverageEnable;
	//blenddesc.IndependentBlendEnable;
	blenddesc.RenderTarget[0].BlendEnable = TRUE;
	blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	// 알파 연산 저장
	blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blenddesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_AlphaBlend);
	blenddesc.RenderTarget[0].BlendEnable = FALSE;
	hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_AlphaBlendDisable);
	return true;
}
bool ADxObject::Init() { return true; }
bool ADxObject::Frame() { return true; }
bool ADxObject::Render() 
{
	if( m_pColorTex != nullptr)
		m_pContext->PSSetShaderResources(0, 1, m_pColorTex->m_pSRV.GetAddressOf());
	if(m_pMaskTex != nullptr)
		m_pContext->PSSetShaderResources(1, 1, m_pMaskTex->m_pSRV.GetAddressOf());
	if (m_pVSShader != nullptr)
		m_pContext->VSSetShader(m_pVSShader->m_pVertexShader, NULL, 0);
	if (m_pPSShader != nullptr)
		m_pContext->PSSetShader(m_pPSShader->m_pPixelShader, NULL, 0);

	if (m_bAlphaBlend)
	{
		m_pContext->OMSetBlendState(ADxState::m_AlphaBlend, 0, -1);
	}
	else
	{
		m_pContext->OMSetBlendState(ADxState::m_AlphaBlendDisable, 0, -1);
	}
	m_pContext->IASetInputLayout(m_pVertexLayout);

	UINT startslot;
	UINT numbuffers;
	UINT strides = sizeof(ASimplevertex);
	UINT Offsets = 0;

	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &Offsets);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	/*D3D11_PRIMITIVE_TOPOLOGY_POINTLIST
	D3D11_PRIMITIVE_TOPOLOGY_LINELIST*/

	if (m_IndexList.size() <= 0)
		m_pContext->Draw(m_VertexList.size(), 0);
	else
		m_pContext->DrawIndexed(m_IndexList.size(), 0, 0);
	return true;
}
bool ADxObject::Release() 
{
	if (m_pVertexBuffer)	m_pVertexBuffer		->Release();
	if (m_pIndexBuffer)		m_pIndexBuffer		->Release();
	if (m_pConstantBuffer)	m_pConstantBuffer	->Release();
	if (m_pVertexLayout)	m_pVertexLayout		->Release();

	m_pVertexBuffer			= nullptr;
	m_pVertexLayout			= nullptr;
	m_pConstantBuffer		= nullptr;
	m_pIndexBuffer			= nullptr;
	return true;
}
