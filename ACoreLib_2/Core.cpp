#include "Core.h"
#include "ObjectMgr.h"
#include "SoundMgr.h"


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
	m_GameTimer.Frame();
	AInput::Get().Frame();
	I_ObjectMgr.Frame();
	I_Sound.Frame();
	Frame();
	m_dxWrite.Frame();
	return true;
}
bool ACore::CoreRender()
{	

	float color[4] = { 1,0,0,1.0f };//{ 0.9, 0.9, 0.7, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
	m_pImmediateContext->PSSetSamplers(0, 1, &ADxState::m_pSamplerState);

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
ACore::ACore(){}
ACore::~ACore(){}