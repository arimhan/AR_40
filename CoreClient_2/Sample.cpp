#include "Sample.h"
#define PORT_NUM 9110 //9110
#define ADRESS_NUM "127.0.0.1" //"127.0.0.1"
void ASample::CreateResizeDevice(UINT iWidth, UINT iHeight)
{
    int k = 0;
}
void ASample::DeleteResizeDevice(UINT iWidth, UINT iHeight)
{
    int k = 0;
}
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
            aPacket << 77 << "<ArimHan>" << (short)10 << buffer;
            m_Net.SendMsg(m_Net.m_Sock, aPacket.m_uPacket);

            SendMessageA(m_hEdit, WM_SETTEXT, 0, (LPARAM)"<ArimHan>: ");
        }break;
        }
    }break;
    }
    return m_Net.MsgProc(hWnd, msg, wParam, lParam);
}

bool ASample::Init()
{
    //I_Fsm.AddTransition(STATE_STOP, STATE_STOP_TIMER, STATE_MOVE);
    //I_Fsm.AddTransition(STATE_STOP, STATE_FIND_TARGET, STATE_ATTACK);

    //I_Fsm.AddTransition(STATE_MOVE, STATE_STOP_TIMER, STATE_STOP);
    //I_Fsm.AddTransition(STATE_MOVE, STATE_FIND_TARGET, STATE_ATTACK);
    //I_Fsm.AddTransition(STATE_MOVE, STATE_LOST_TARGET, STATE_STOP);

    //I_Fsm.AddTransition(STATE_ATTACK, STATE_LOST_TARGET, STATE_STOP);

    I_Sound.Init();

    m_IntroWorld.Init();
    m_IntroWorld.m_pd3dDevice = m_pd3dDevice.Get();
    m_IntroWorld.m_pContext = m_pImmediateContext.Get();
    m_IntroWorld.Load(L"intro.txt");
    m_IntroWorld.m_pNextWorld = &m_ZoneWorld;
    m_ZoneWorld.m_pd3dDevice = m_pd3dDevice.Get();
    m_ZoneWorld.m_pContext = m_pImmediateContext.Get();

    AWorld::m_pCurWorld = &m_IntroWorld;

    m_Net.InitNetwork();
    m_Net.Connect(g_hWnd, SOCK_STREAM, PORT_NUM, ADRESS_NUM);// "127.0.0.1"); //IP
    return true;
}
bool ASample::Frame()
{
    //if (AInput::Get().GetKey(VK_F1) == KEY_PUSH)
    //{
    //    AWorld::m_pCurWorld = &m_ZoneWorld;
    //}
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
    //각 클래스별로 Release재정의한것 불러오기
    I_Sound.Release();
    m_IntroWorld.Release();
    m_ZoneWorld.Release();
    m_Net.CloseNetWork();
    return true;
}
ASample::ASample() {}
ASample::~ASample() {}
//SIMPLE_ARUN();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	ASample core;

	if (core.SetWinClass(hInstance) == FALSE) return 1;
	if (core.SetWindow(L"KGCA_2DGAME_ARHAN") == FALSE) return 1;
	core.GameRun();
	return 1;
}

