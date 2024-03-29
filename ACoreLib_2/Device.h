#pragma once
#include "Window.h"

class ADevice : public AWindow
{
public:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;	//�������ٽǺ�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV;			//���ҽ���
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pDsvSRV;			//�������ٽ� ���ҽ���
public:
	// windows runtime c++ template library(wrl)
	ComPtr<ID3D11Device> m_pd3dDevice;
	//ID3D11Device* m_pd3dDevice;	// ����̽� ��ü
	ComPtr<ID3D11DeviceContext> m_pImmediateContext;
	//ID3D11DeviceContext* m_pImmediateContext;// �ٺ��̽� ���ؽ�Ʈ ��ü
	//IDXGISwapChain* m_pSwapChain;	// ����ü�� ��ü
	ComPtr<IDXGISwapChain> m_pSwapChain;
	//ID3D11RenderTargetView* m_pRenderTargetView;// ���� ����Ÿ�� ��
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	D3D_FEATURE_LEVEL       m_FeatureLevel;	// Direct3D Ư������ �Ӽ���	
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;	// ����ü�� �Ӽ���
	D3D11_VIEWPORT			m_ViewPort;	// �� ��Ʈ �Ӽ���
public:
	HRESULT		    InitDeivice();
	virtual bool	CreateDevice();
	virtual bool	CreateRenderTargetView();
	virtual bool	CreateDepthStencilView();
	virtual bool	SetViewport();
	virtual bool	CleapupDevice();
	void			ResizeDevice(UINT iWidth, UINT iHeight);
	void			ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
public:
	ADevice();
	virtual ~ADevice();
};

