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
		NULL, // �ƴ��� : � �׷��� ī�� ���? , NULL: �� �׷���ī�� ���
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		Flags,
		fl,
		1,
		D3D11_SDK_VERSION,
		&m_SwapChainDesc,
		m_pSwapChain.GetAddressOf(),
		m_pd3dDevice.GetAddressOf(),		
		&m_FeatureLevel,
		m_pImmediateContext.GetAddressOf());

	if (FAILED(hr)) { return false; }

	return true;
}
bool ADevice::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	m_pd3dDevice->CreateRenderTargetView(backBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());
	if (backBuffer)backBuffer->Release();
	m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL);
	return true;
}
bool ADevice::SetViewPort()
{
	//����Ʈ ���� 
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

	//�׳� Release�ϱ� ��, omset�Լ��� Ȱ���� 1(Ǯ���ֱ�), null�� ���� �� release�� ���� �� ������ �Ѵ�!
	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	//RenderTargetView�Լ����� Create�� �ϰ� �ֱ� ������ ����� ���� ������ �� ������ ������ �� �� �ֵ��� �Ѵ�.
	if (m_pRenderTargetView)m_pRenderTargetView->Release();
	HRESULT hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount, iWidth, iHeight, //ũ�⸸ �����Ѵ�
												m_SwapChainDesc.BufferDesc.Format,
												m_SwapChainDesc.Flags);
	if (SUCCEEDED(hr))
	{
		m_pSwapChain->GetDesc(&m_SwapChainDesc);
	}
	//iWidth, iHeight���� �����߱� ������ �Ʒ� �Լ����� ũ����� ��������� �Ѵ�. 
	//�׷��� �Լ����� �� ȣ���Ѵ�!
	CreateRenderTargetView();
	SetViewPort();
}
bool ADevice::CleanUpDevice()
{
	//if (m_pd3dDevice) m_pd3dDevice->Release();
	//if (m_pImmediateContext)m_pImmediateContext->Release();
	//if (m_pSwapChain)m_pSwapChain->Release();
	//if (m_pRenderTargetView)m_pRenderTargetView->Release();
	//m_pd3dDevice = nullptr;
	//m_pImmediateContext = nullptr;
	//m_pSwapChain = nullptr;
	//m_pRenderTargetView = nullptr;

	return true;
}

ADevice::ADevice()
{
	m_pd3dDevice =			nullptr;	//����̽� ��ü
	m_pImmediateContext =	nullptr;	//����̽� ���ؽ�Ʈ ��ü
	m_pSwapChain =			nullptr;	//����ü�� ��ü
	m_pRenderTargetView =	nullptr;	//����Ÿ�ٺ�
}
ADevice::~ADevice(){}