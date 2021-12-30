#pragma once
#include "Window.h"
class ADevice : public AWindow
{
public:
	ID3D11Device*				m_pd3dDevice;				// ����̽� ��ü ����
	ID3D11DeviceContext*		m_pImmediateContext;		// ����̽� ���ؽ�Ʈ ��ü
	IDXGISwapChain*				m_pSwapChain;				// ����ü�� ��ü
	ID3D11RenderTargetView*		m_pRenderTargetView;		// ���� ����Ÿ�� ��
	D3D_FEATURE_LEVEL			m_FeatureLevel;				// Direct 3D  Ư�� ���� �Ӽ� ��
	DXGI_SWAP_CHAIN_DESC		m_SwapChainDesc;			// ����ü�� �Ӽ� ��
	D3D11_VIEWPORT				m_ViewPort;					// ����Ʈ �Ӽ� ��
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

