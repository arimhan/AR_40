#pragma once
#include "Window.h"

class ADevice : public AWindow
{
public:

	ComPtr<ID3D11Device>			m_pd3dDevice;			// 디바이스 객체
	ComPtr<ID3D11DeviceContext>		m_pImmediateContext;	// 디바이스 컨텍스트 객체
	ComPtr<IDXGISwapChain>			m_pSwapChain;			// 스왑체인 객체
	ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;	// 메인 랜더타켓 뷰

	D3D_FEATURE_LEVEL				m_FeatureLevel;			// Direct3D 특성레벨 속성값	
	DXGI_SWAP_CHAIN_DESC			m_SwapChainDesc;		// 스왑체인 속성값
	D3D11_VIEWPORT					m_ViewPort;				// 뷰 포트 속성값
public:
	HRESULT		    InitDeivice();
	virtual bool	CreateDevice();
	virtual bool	CreateRenderTargetView();
	virtual bool	SetViewport();
	virtual bool	CleapupDevice();
	void			ResizeDevice(UINT iWidth, UINT iHeight);
public:
	ADevice();
	virtual ~ADevice();
};

