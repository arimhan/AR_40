#pragma once

class Sample : public AWindow // 클래스 생성해서 연결
{
	//I~~ interface란뜻~~
	//ID3D11Device* m_pd3dDevice; 
	//ID3D11DeviceContext* m_pImmediateContext;
	//IDXGISwapChain* m_pSwapChain; 
	// 	// Device, SwapChain 동시에 생성, 함수 기능 보고 기능 전부 넣기!
	//	// 아답터 : 어떤 그래픽 카드 사용? , NULL: 주 그래픽카드 사용
		// DriverType : hardware -> 차선책 warp : 고성능CPU - Reference : GPU가 할 일을 CPU가 처리하기 때문에 1프레임 나옴..ㅠ
		// Flags : 정수값 , 뭔지 모를땐 =0값으로 우선 넣기.
		// FeatureLevel * : DXD ver - 11.0 사용 (포인터로 되어있다 => 필요한 ver 전부 다 가져올 수 있음) => 상단에서 배열 만들고 해당배열변수명 넣어도 OK 상단에서 하단으로 우선순위
		// Swapchaindesc 포인터 값 애들은 뭔지 잘 모르면 우선 빼둔 뒤 주소값으로 넣기
		// 

	//ID3D11RenderTargetView* m_pRenderTargetView;
	//D3D_FEATURE_LEVEL m_FeatureLevel; 
	//D3D_DRIVER_TYPE m_DriverType;
	//DXGI_SWAP_CHAIN_DESC m_SwapChainDesc; 
	//D3D11_VIEWPORT m_ViewPort; 
};

