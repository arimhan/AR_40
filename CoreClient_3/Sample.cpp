#include "Sample.h"
#include "ObjectMgr.h"

void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight) { int k = 0; }

LRESULT ASample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 200:
		{
			char buffer[MAX_PATH] = { 0, };
			SendMessageA(m_hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)buffer);
			APacket aPacket(PACKET_CHAT_MSG);
			//tPacket.m_uPacket.ph.time = timeGetTime();
			aPacket << 77 << "<ArimHan>" << buffer;
			m_Net.SendMsg(m_Net.m_Sock, aPacket.m_uPacket);

			SendMessageA(m_hEdit, WM_SETTEXT, 0, (LPARAM)"<ArimHan>:");
		}break;
		}
	}break;
	}
	return m_Net.MsgProc(hWnd, msg, wParam, lParam);
}

bool ASample::Init()
{	
	I_Sound.Init();

	m_IntroWorld.Init();
	m_IntroWorld.m_pd3dDevice = m_pd3dDevice.Get();
	m_IntroWorld.m_pContext = m_pImmediateContext.Get();
	m_IntroWorld.Load(L"INTRO.txt");
	m_IntroWorld.m_pNextWorld = &m_ZoneWorld;
	m_ZoneWorld.m_pd3dDevice = m_pd3dDevice.Get();
	m_ZoneWorld.m_pContext = m_pImmediateContext.Get();

	AWorld::m_pCurWorld = &m_IntroWorld;

	return true;
}
bool ASample::Frame()
{	
	AWorld::m_pCurWorld->Frame();
	return true;
}
bool ASample::Render()
{	
	//화면 상단 FPS, GameTimer 출력

	AWorld::m_pCurWorld->Render();
	wstring msg = L"[ FPS: ";
	msg += to_wstring(m_GameTimer.m_iFPS);
	msg += L",  GT: ";
	msg += to_wstring(m_GameTimer.m_fTimer);
	msg += L" ]";
	m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(1, 1, 1, 1.0f));
	
	return true;
}
bool ASample::Release()
{	
	I_Sound.Release();
	m_IntroWorld.Release();
	m_ZoneWorld.Release();
	m_Net.CloseNetWork();
	return true;
}
ASample::ASample(){}
ASample::~ASample()
{}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	ASample core;

	if (core.SetWinClass(hInstance) == FALSE) return 1;
	if (core.SetWindow(L"KGCA_2DGAME_ARHAN") == FALSE) return 1;
	core.GameRun();
	return 1;
}