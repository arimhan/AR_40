#pragma once

class Sample : public AWindow // Ŭ���� �����ؼ� ����
{
	//I~~ interface����~~
	//ID3D11Device* m_pd3dDevice; 
	//ID3D11DeviceContext* m_pImmediateContext;
	//IDXGISwapChain* m_pSwapChain; 
	// 	// Device, SwapChain ���ÿ� ����, �Լ� ��� ���� ��� ���� �ֱ�!
	//	// �ƴ��� : � �׷��� ī�� ���? , NULL: �� �׷���ī�� ���
		// DriverType : hardware -> ����å warp : ����CPU - Reference : GPU�� �� ���� CPU�� ó���ϱ� ������ 1������ ����..��
		// Flags : ������ , ���� �𸦶� =0������ �켱 �ֱ�.
		// FeatureLevel * : DXD ver - 11.0 ��� (�����ͷ� �Ǿ��ִ� => �ʿ��� ver ���� �� ������ �� ����) => ��ܿ��� �迭 ����� �ش�迭������ �־ OK ��ܿ��� �ϴ����� �켱����
		// Swapchaindesc ������ �� �ֵ��� ���� �� �𸣸� �켱 ���� �� �ּҰ����� �ֱ�
		// 

	//ID3D11RenderTargetView* m_pRenderTargetView;
	//D3D_FEATURE_LEVEL m_FeatureLevel; 
	//D3D_DRIVER_TYPE m_DriverType;
	//DXGI_SWAP_CHAIN_DESC m_SwapChainDesc; 
	//D3D11_VIEWPORT m_ViewPort; 
};

