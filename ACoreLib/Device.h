#pragma once
#include "Window.h"
class ADevice : public AWindow
{
public:
	ID3D11Device*				m_pd3dDevice;				// 디바이스 객체 생성
	ID3D11DeviceContext*		m_pImmediateContext;		// 디바이스 컨텍스트 객체
	IDXGISwapChain*				m_pSwapChain;				// 스왑체인 객체
	ID3D11RenderTargetView*		m_pRenderTargetView;		// 메인 랜더타겟 뷰
	D3D_FEATURE_LEVEL			m_FeatureLevel;				// Direct 3D  특성 레벨 속성 값
	DXGI_SWAP_CHAIN_DESC		m_SwapChainDesc;			// 스왑체인 속성 값
	D3D11_VIEWPORT				m_ViewPort;					// 뷰포트 속성 값
public:
	HRESULT			InitDevice();
	virtual bool	CreateDevice();
	virtual bool	CleanUpDevice();
	virtual bool	CreateRenderTargetView();
	virtual bool	SetViewPort();
public:
	ADevice();
	virtual ~ADevice();
};

