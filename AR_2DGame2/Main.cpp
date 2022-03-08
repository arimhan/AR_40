#include "Main.h"


LRESULT AMain::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
			aPacket << 77 << "<ArimHan>" << (short)10 << buffer;
			m_Net.SendMsg(m_Net.m_Sock, aPacket.m_uPacket);

			SendMessageA(m_hEdit, WM_SETTEXT, 0, (LPARAM)"<ArimHan>: ");
		}break;
		}
	}break;
	}
	return m_Net.MsgProc(hWnd, msg, wParam, lParam);
}

bool AMain::Init()
{
	I_Sound.Init();

	m_Intro.Init();
	m_Intro.m_pd3dDevice = m_pd3dDevice.Get();
	m_Intro.m_pContext = m_pImmediateContext.Get();
	m_Intro.Load(L"Intro.txt"); //Intro내 Load로 이동
	m_Intro.m_pNextWorld = &m_Zone;
	m_Zone.m_pd3dDevice = m_pd3dDevice.Get();
	m_Zone.m_pContext = m_pImmediateContext.Get();

	AWorld::m_pCurWorld = &m_Intro;
	m_Net.InitNetwork();
	m_Net.Connect(g_hWnd, SOCK_STREAM, PORT_NUM, ADRESS_NUM);

	return true;
}

bool AMain::Frame()
{
	AWorld::m_pCurWorld->Frame();

#pragma region
	int iChatCnt = m_Net.m_PlayerUser.m_PacketPool.size();
	if (iChatCnt > 0 && m_iChatCnt != iChatCnt)
	{
		m_iChatCnt = iChatCnt;
		SendMessage(m_hListBox, LB_RESETCONTENT, 0, 0);

		list<APacket> ::iterator iter;
		if (m_Net.m_PlayerUser.m_PacketPool.size() > 20) //size가 크면 앞에서부터 pop한다.
		{
			m_Net.m_PlayerUser.m_PacketPool.pop_front();
		}
		for (iter = m_Net.m_PlayerUser.m_PacketPool.begin(); iter != m_Net.m_PlayerUser.m_PacketPool.end(); iter++)
		{
			UPACKET& uPacket = (*iter).m_uPacket;
			switch ((*iter).m_uPacket.ph.type)
			{
			case PACKET_LOGIN_ACK:
			{
				DWORD dwCurrent = timeGetTime();
				DWORD dwEnd = 0;
				dwEnd = dwCurrent - uPacket.ph.time;
				ALoginAck ack;
				memcpy(&ack, (*iter).m_uPacket.msg, sizeof(ALoginAck));
				if (ack.iRet == 1)
				{
					int k = 0;
				}
			}break;
			case PACKET_CHAT_MSG:
			{
				DWORD dwCurrent = timeGetTime();
				DWORD dwEnd = 0;
				dwEnd = dwCurrent - uPacket.ph.time;
				if (dwEnd >= 1)
				{
					string data = to_string(dwEnd);
					data += "\n";
					OutputDebugStringA(data.c_str());
				}
				AChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));
				(*iter) >> recvdata.index >> recvdata.name >> recvdata.message;
				SendMessageA(m_hListBox, LB_ADDSTRING, 0, (LPARAM)recvdata.message);
				(*iter).Reset();
			}break;
			}
		}
		m_Net.m_PlayerUser.m_PacketPool.clear();
	}
#pragma endregion NetProcess
	//Network ver 필요없으므로 블럭처리

	return true;
}

bool AMain::Render()
{
	//화면 상단 FPS, GameTimer 출력
	AWorld::m_pCurWorld->Render();
	wstring msg = L"[ FPS: ";
	msg += to_wstring(m_GameTimer.m_iFPS);
	msg += L",  GT: ";
	msg += to_wstring(m_GameTimer.m_fTimer);
	msg += L" ]";
	m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(1, 1, 1, 0));

	return true;
}

bool AMain::Release()
{
	I_Sound.Release();
	m_Intro.Release();
	m_Zone.Release();
	m_Net.CloseNetWork();
	return true;
}



//SIMPLE_ARUN();
////WinMain   wWinMain
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	AMain core;

	if (core.SetWinClass(hInstance) == FALSE) return 1;
	if (core.SetWindow(L"KGCA_2DGAME_ARHAN") == FALSE) return 1;
	core.GameRun();
	return 1;
}
