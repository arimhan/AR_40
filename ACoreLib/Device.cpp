#include "Device.h"

HRESULT ADevice::InitDevice()
{
	HRESULT hr = S_OK;
	CreateDevice();
	CreateRenderTargetView();
	SetViewPort();
	return hr;
}
bool ADevice::CreateDevice()
{
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL fl[]
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};

	ZeroMemory(&m_SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	m_SwapChainDesc.BufferDesc.Width = m_rtClient.right;
	m_SwapChainDesc.BufferDesc.Height = m_rtClient.bottom;
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //28
	m_SwapChainDesc.SampleDesc.Count = 1;
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_SwapChainDesc.BufferCount = 1;
	m_SwapChainDesc.OutputWindow = m_hWnd;
	m_SwapChainDesc.Windowed = true;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL, // 아답터 : 어떤 그래픽 카드 사용? , NULL: 주 그래픽카드 사용
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		Flags,
		fl,
		1,
		D3D11_SDK_VERSION,
		&m_SwapChainDesc,
		&m_pSwapChain,
		&m_pd3dDevice,
		&m_FeatureLevel,
		&m_pImmediateContext);

	if (FAILED(hr)) { return false; }

	return true;
}
bool ADevice::CreateRenderTargetView()
{
	ID3D11Texture2D* backBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	m_pd3dDevice->CreateRenderTargetView(backBuffer, NULL, &m_pRenderTargetView);
	if (backBuffer)backBuffer->Release();
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	return true;
}
bool ADevice::SetViewPort()
{
	//뷰포트 세팅 
	//DXGI_SWAP_CHAIN_DESC swapDesc;
	//m_pSwapChain->GetDesc(&swapDesc);
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = m_SwapChainDesc.BufferDesc.Width;
	m_ViewPort.Height = m_SwapChainDesc.BufferDesc.Height;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);

	return true;
}
void ADevice::ResizeDevice(UINT iWidth, UINT iHeight)
{

	//그냥 Release하기 전, omset함수를 활용해 1(풀어주기), null로 삭제 후 release로 지운 뒤 갱신을 한다!
	m_pImmediateContext->OMSetRenderTargets(1, NULL, NULL);
	//RenderTargetView함수에서 Create를 하고 있기 때문에 릴리즈를 먼저 시켜준 뒤 사이즈 갱신을 할 수 있도록 한다.
	if (m_pRenderTargetView)m_pRenderTargetView->Release();
	HRESULT hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount, iWidth, iHeight, //크기만 갱신한다
												m_SwapChainDesc.BufferDesc.Format,
												m_SwapChainDesc.Flags);
	if (SUCCEEDED(hr))
	{
		m_pSwapChain->GetDesc(&m_SwapChainDesc);
	}
	//iWidth, iHeight값을 갱신했기 때문에 아래 함수에서 크기들을 갱신해줘야 한다. 
	//그래서 함수들을 재 호출한다!
	CreateRenderTargetView();
	SetViewPort();
}
bool ADevice::CleanUpDevice()
{
	if (m_pd3dDevice) m_pd3dDevice->Release();
	if (m_pImmediateContext)m_pImmediateContext->Release();
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_pRenderTargetView)m_pRenderTargetView->Release();
	m_pd3dDevice = nullptr;
	m_pImmediateContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;

	return true;
}

ADevice::ADevice()
{
	m_pd3dDevice = nullptr;
	m_pImmediateContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
}
ADevice::~ADevice(){}