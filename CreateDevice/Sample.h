#pragma once
#include "Core.h"
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")
class Sample : public ACore // 클래스 생성해서 연결
{
	ID3D11Device*				m_pd3dDevice;				// 디바이스 객체 생성
	ID3D11DeviceContext*		m_pImmediateContext;		// 디바이스 컨텍스트 객체
	IDXGISwapChain*				m_pSwapChain;				// 스왑체인 객체

	ID3D11RenderTargetView*		m_pRenderTargetView;		// 메인 랜더타겟 뷰
	D3D_FEATURE_LEVEL			m_FeatureLevel;				// Direct 3D  특성 레벨 속성 값
	D3D_DRIVER_TYPE				m_DriverType;				// 디바이스 타입 (항상 하드웨어로)
	DXGI_SWAP_CHAIN_DESC		m_SwapChainDesc;			// 스왑체인 속성 값
	D3D11_VIEWPORT				m_ViewPort;					// 뷰포트 속성 값
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;

	Sample(); //생성자로 초기화 값 지정
};

