#include "DxState.h"

ID3D11BlendState*	ADxState::m_AlphaBlend = nullptr;
ID3D11BlendState*	ADxState::m_AlphaBlendDisable = nullptr;
//ID3D11SamplerState*			ADxState::m_pSamplerState			= nullptr;

ID3D11BlendState* ADxState::m_BSNoneColor = nullptr;
ID3D11SamplerState* ADxState::m_pSSLinear = nullptr;
ID3D11SamplerState* ADxState::m_pSSPoint = nullptr;

ID3D11SamplerState* ADxState::g_pSSMirrorLinear = nullptr;
ID3D11SamplerState* ADxState::g_pSSMirrorPoint = nullptr;
ID3D11SamplerState* ADxState::g_pSSClampLinear = nullptr;
ID3D11SamplerState* ADxState::g_pSSClampPoint = nullptr;


ID3D11RasterizerState* ADxState::g_pRSBackCullSolid = nullptr;
ID3D11RasterizerState* ADxState::g_pRSNoneCullSolid = nullptr;

ID3D11RasterizerState*		ADxState::g_pRSBackCullWireFrame	= nullptr;
ID3D11RasterizerState*		ADxState::g_pRSNoneCullWireFrame	= nullptr;
ID3D11DepthStencilState*	ADxState::g_pDSSDepthEnable			= nullptr;
ID3D11DepthStencilState*	ADxState::g_pDSSDepthDisable		= nullptr;

ID3D11DepthStencilState* ADxState::g_pDSSDepthEnableWirteDisable = nullptr;
ID3D11DepthStencilState* ADxState::g_pDSSDepthDisableWirteDisable = nullptr;




bool ADxState::SetState(ID3D11Device* pd3dDevice)
{
	HRESULT hr;

	D3D11_BLEND_DESC  blenddesc;
	ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));

	blenddesc.RenderTarget[0].BlendEnable = TRUE;
	blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//// A ���� ����
	blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blenddesc.RenderTarget[0].RenderTargetWriteMask =
		D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = pd3dDevice->CreateBlendState(&blenddesc, &m_AlphaBlend);

	blenddesc.RenderTarget[0].BlendEnable = FALSE;
	hr = pd3dDevice->CreateBlendState(&blenddesc, &m_AlphaBlendDisable);

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.MinLOD = FLT_MAX;
	sd.MaxLOD = FLT_MIN;
	hr = pd3dDevice->CreateSamplerState(&sd, &m_pSSLinear);//&m_pSamplerState);
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	hr = pd3dDevice->CreateSamplerState(&sd, &m_pSSPoint);//&m_pSamplerState);

	//g_pSSMirror
	sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &ADxState::g_pSSMirrorLinear))) return hr;

	sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &ADxState::g_pSSMirrorPoint))) return hr;

	//g_pSSClamp
	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &ADxState::g_pSSClampLinear))) return hr;

	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &ADxState::g_pSSClampPoint))) return hr;


	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(rsDesc));
	rsDesc.DepthClipEnable = TRUE;
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_BACK;
	if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &ADxState::g_pRSBackCullSolid))) return hr;

	rsDesc.DepthClipEnable = TRUE;
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_NONE;
	if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &ADxState::g_pRSNoneCullSolid))) return hr;

	rsDesc.DepthClipEnable = TRUE;
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;
	rsDesc.CullMode = D3D11_CULL_BACK;
	if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &ADxState::g_pRSBackCullWireFrame))) return hr;

	rsDesc.DepthClipEnable = TRUE;
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;
	rsDesc.CullMode = D3D11_CULL_NONE;
	if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &ADxState::g_pRSNoneCullWireFrame))) return hr;

	D3D11_DEPTH_STENCIL_DESC dsDescDepth;
	ZeroMemory(&dsDescDepth, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsDescDepth.DepthEnable = TRUE;
	dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDescDepth.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dsDescDepth.StencilEnable = FALSE;
	dsDescDepth.StencilReadMask = 1;
	dsDescDepth.StencilWriteMask = 1;
	dsDescDepth.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsDescDepth.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	
	//BackFace ����Ʈ ��
	dsDescDepth.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthEnable))) return hr;

	dsDescDepth.DepthEnable = FALSE;
	if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthDisable))) return hr;

	dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthDisableWirteDisable))) return hr;

	dsDescDepth.DepthEnable = TRUE;
	dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthEnableWirteDisable))) return hr;


	return true;
}
bool ADxState::Release()
{
	if (g_pRSBackCullSolid)					g_pRSBackCullSolid->Release();
	if (g_pRSNoneCullSolid)					g_pRSNoneCullSolid->Release();
	if (g_pRSBackCullWireFrame)				g_pRSBackCullWireFrame->Release();
	if (g_pRSNoneCullWireFrame)				g_pRSNoneCullWireFrame->Release();

	if (g_pDSSDepthEnable)					g_pDSSDepthEnable->Release();
	if (g_pDSSDepthDisable)					g_pDSSDepthDisable->Release();
	if (g_pDSSDepthDisableWirteDisable)		g_pDSSDepthDisableWirteDisable->Release();
	if (g_pDSSDepthEnableWirteDisable)		g_pDSSDepthEnableWirteDisable->Release();

	if (m_AlphaBlend)						m_AlphaBlend->Release();
	if (m_AlphaBlendDisable)				m_AlphaBlendDisable->Release();

	m_AlphaBlend = nullptr;
	m_AlphaBlendDisable = nullptr;

	if (m_pSSLinear)			m_pSSLinear->Release();
	if (m_pSSPoint)				m_pSSPoint->Release();
	if (g_pSSMirrorLinear)		g_pSSMirrorLinear->Release();
	if (g_pSSMirrorPoint)		g_pSSMirrorPoint->Release();
	if (g_pSSClampLinear)		g_pSSClampLinear->Release();
	if (g_pSSClampPoint)		g_pSSClampPoint->Release();
	return true;
}


//void ADxState::ApplyRS(ID3D11DeviceContext* pContext, ID3D11RasterizerState* pState)
//{
//	assert(pContext);
//	pContext->RSSetState(pState);
//}
//void ADxState::ApplyDSS(ID3D11DeviceContext* pContext, ID3D11DepthStencilState* pDepthStencilState,
//	UINT iRef)
//{
//	assert(pContext);
//	pContext->OMSetDepthStencilState(pDepthStencilState, iRef);
//
//}
//
//void ADxState::ApplyBS(ID3D11DeviceContext* pContext, ID3D11BlendState* pBlendState,
//	const FLOAT fBlendFactor[]=0, UINT iMask)
//{
//	assert(pContext);
//	pContext->OMSetBlendState(pBlendState, fBlendFactor, iMask);
//}
//
//void ADxState::ApplySS(ID3D11DeviceContext* pContext, ID3D11SamplerState* pSamplerState,
//	UINT iSlot, UINT iArray)
//{
//	assert(pContext);
//	pContext->PSSetSamplers(iSlot, iArray, &pSamplerState);
//}
