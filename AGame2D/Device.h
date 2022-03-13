#pragma once
#include "Window.h"

class ADevice : public AWindow
{
public:

	ComPtr<ID3D11Device>			m_pd3dDevice;			// ����̽� ��ü
	ComPtr<ID3D11DeviceContext>		m_pImmediateContext;	// ����̽� ���ؽ�Ʈ ��ü
	ComPtr<IDXGISwapChain>			m_pSwapChain;			// ����ü�� ��ü
	ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;	// ���� ����Ÿ�� ��

	D3D_FEATURE_LEVEL				m_FeatureLevel;			// Direct3D Ư������ �Ӽ���	
	DXGI_SWAP_CHAIN_DESC			m_SwapChainDesc;		// ����ü�� �Ӽ���
	D3D11_VIEWPORT					m_ViewPort;				// �� ��Ʈ �Ӽ���
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

