#include "Core.h"
#include "ObjectMgr.h"
#include "SoundMgr.h"

ABoxObj* g_pBoxDebug = nullptr;

bool ACore::CoreInit()
{
	m_GameTimer.Init();	
	AInput::Get().Init();
	if( SUCCEEDED(InitDeivice()))
	{
		I_Shader.Set(m_pd3dDevice.Get());
		I_Texture.Set(m_pd3dDevice.Get());
		ADxState::SetState(m_pd3dDevice.Get());
		if (m_dxWrite.Init())
		{
			IDXGISurface1* pSurface = nullptr;
			HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pSurface);
			if (SUCCEEDED(hr))
			{
				m_dxWrite.SetRenderTarget(pSurface);
			}
			if (pSurface) pSurface->Release();
		}
	}

	//m_DefaultCamera를 세팅한 후 메인카메라로 지정.
	m_DefaultCamera.Init();
	m_DefaultCamera.CreateViewMatrix(A::AVector3(0, 500.0f, -100.0f), A::AVector3(0, 0.0f, 0));
	m_DefaultCamera.CreateProjMatrix(XM_PI * 0.25f, 
		(float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 5000.0f);
	m_DefaultCamera.m_pColorTex = I_Texture.Load(L"../../data/Img/charport.bmp");
	m_DefaultCamera.m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"../../data/shader/Box.hlsl", "VSColor");
	m_DefaultCamera.m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"../../data/shader/Box.hlsl", "PSColor");
	m_DefaultCamera.SetPosition(A::AVector3(0.0f, 1.0f, 0.0f));
	if(!m_DefaultCamera.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}
	m_pMainCamera = &m_DefaultCamera;

	m_SkyObj.Init();
	m_SkyObj.SetPosition(A::AVector3(0.0f, 0.0f, 0.0f));

	if (!m_SkyObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(),
		L"../../data/shader/sky.hlsl", L"../../data/sky/skybox02.dds"))
	{
		return false;
	}

	DrawDebugInit(m_pd3dDevice.Get(), m_pImmediateContext.Get());

	g_pBoxDebug = &m_BoxDebug;

	Init();

	return true;
}
bool ACore::GameRun()
{
	CoreInit();
	while(WinRun())
	{
		CoreFrame();
		CoreRender();
	}
	CoreRelease();

	MemoryReporting();
	return true;
}
bool ACore::CoreFrame()
{
	//V키 누르면 와이어프레임 나오도록
	if (AInput::Get().GetKey('V') == KEY_PUSH) { m_bWireFrame = !m_bWireFrame; }

	m_GameTimer.Frame();
	AInput::Get().Frame();
	m_pMainCamera->Frame();
	m_SkyObj.Frame();
	I_ObjectMgr.Frame();
	I_Sound.Frame();
	Frame();
	m_dxWrite.Frame();
	return true;
}
bool ACore::CoreRender()
{	

	float color[4] = { 0.8,0.75,0.8,1.0f };//{ 0.9, 0.9, 0.7, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->OMSetRenderTargets(1, 
		m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
	
	m_pImmediateContext->PSSetSamplers(0, 1, &ADxState::m_pSSLinear);
	m_pImmediateContext->PSSetSamplers(1, 1, &ADxState::m_pSSPoint);
	m_pImmediateContext->OMSetDepthStencilState(ADxState::g_pDSSDepthEnable, 0x00);

	//V키 누르면 와이어프레임 모드로 변환 기능 추가함.
	if (m_bWireFrame) 
		m_pImmediateContext->RSSetState(ADxState::g_pRSBackCullWireFrame);
	else 
		m_pImmediateContext->RSSetState(ADxState::g_pRSBackCullSolid);

	//---------------------------SkyObj Render Set
	//Skybox안에 camera를 넣을 경우 이동성분은 0으로 고정한다. (회전만 가능하도록)
	m_SkyObj.m_matView = m_pMainCamera->m_matView;
	m_SkyObj.m_matView._41 = 0;
	m_SkyObj.m_matView._42 = 0;
	m_SkyObj.m_matView._43 = 0;
	A::AMatrix matRotation, matScale;
	m_SkyObj.SetMatrix(NULL, &m_SkyObj.m_matView, &m_pMainCamera->m_matProj);
	m_pImmediateContext->RSSetState(ADxState::g_pRSNoneCullSolid);
	m_SkyObj.Render();
	m_pImmediateContext->RSSetState(ADxState::g_pRSBackCullSolid);

	// 백버퍼에 랜더링 한다.
	Render();

	m_GameTimer.Render();
	AInput::Get().Render();
	m_dxWrite.Render();
	m_pSwapChain->Present(0, 0);
	return true;
}

bool ACore::CoreRelease()
{
	Release();
	m_DefaultCamera.Release();
	ADxState::Release();
	m_dxWrite.Release();
	m_GameTimer.Release();
	AInput::Get().Release();
	CleapupDevice();	
	return true;
}
void ACore::ResizeDevice(UINT iWidth, UINT iHeight)
{
	if (m_pd3dDevice == nullptr) return;
	DeleteResizeDevice(iWidth, iHeight);

	m_dxWrite.DeleteDeviceResize();
		
	ADevice::ResizeDevice(iWidth, iHeight);
	
	IDXGISurface1* pSurface = nullptr;
	HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pSurface);
	if (SUCCEEDED(hr))
	{
		m_dxWrite.SetRenderTarget(pSurface);
	}
	if (pSurface) pSurface->Release();

	CreateResizeDevice(iWidth, iHeight);
}

//디버그 모드일때만 사용함.
void ACore::DrawDebugInit(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	m_BoxDebug.m_pColorTex = I_Texture.Load(L"../../data/charport.bmp");
	m_BoxDebug.m_pVShader = I_Shader.CreateVertexShader(pd3dDevice, L"Box.hlsl", "VSColor");
	m_BoxDebug.m_pPShader = I_Shader.CreatePixelShader(pd3dDevice, L"Box.hlsl", "PSColor");
	m_BoxDebug.SetPosition(A::AVector3(0.0f, 1.0f, 0.0f));
	if (!m_BoxDebug.Create(pd3dDevice, pContext)) { return; }
}

bool ACore::Init() { return true; }
bool ACore::Frame() { return true; }
bool ACore::Render() { return true; }
bool ACore::Release() { return true; }

ACore::ACore(){}
ACore::~ACore(){}