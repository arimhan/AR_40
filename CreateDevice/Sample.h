#pragma once
#include "Core.h"
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")
class Sample : public ACore // Ŭ���� �����ؼ� ����
{
	ID3D11Device*				m_pd3dDevice;				// ����̽� ��ü ����
	ID3D11DeviceContext*		m_pImmediateContext;		// ����̽� ���ؽ�Ʈ ��ü
	IDXGISwapChain*				m_pSwapChain;				// ����ü�� ��ü

	ID3D11RenderTargetView*		m_pRenderTargetView;		// ���� ����Ÿ�� ��
	D3D_FEATURE_LEVEL			m_FeatureLevel;				// Direct 3D  Ư�� ���� �Ӽ� ��
	D3D_DRIVER_TYPE				m_DriverType;				// ����̽� Ÿ�� (�׻� �ϵ�����)
	DXGI_SWAP_CHAIN_DESC		m_SwapChainDesc;			// ����ü�� �Ӽ� ��
	D3D11_VIEWPORT				m_ViewPort;					// ����Ʈ �Ӽ� ��
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;

	Sample(); //�����ڷ� �ʱ�ȭ �� ����
};
