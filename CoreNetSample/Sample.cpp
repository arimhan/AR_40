#include "Sample.h"
#define PORT_NUM 9110 //9110
#define ADRESS_NUM "127.0.0.1" //"127.0.0.1"
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
            aPacket << 77 << "arimhan" << (short)30 << buffer;
            m_Net.SendMsg(m_Net.m_Sock, aPacket.m_uPacket);

            SendMessageA(m_hEdit, WM_SETTEXT, 0, (LPARAM)"");
        }break;
        }
    }break;
    }
    return m_Net.MsgProc(hWnd, msg, wParam, lParam);
}
bool ASample::Init()
{
    DWORD style = WS_CHILD | WS_VISIBLE | ES_MULTILINE;
    m_hEdit = CreateWindow(L"Edit", NULL, style, 0, g_rtClient.bottom - 50, 300, 50, m_hWnd, (HMENU)100, m_hInstance, NULL);
    style = WS_CHILD | WS_VISIBLE;
    m_hButton = CreateWindow(L"Button", L"전송", style, 310, g_rtClient.bottom - 50, 50, 50, m_hWnd, (HMENU)200, m_hInstance, NULL);
    m_hListBox = CreateWindow(L"ListBox", NULL, style, 0, 0, 300, g_rtClient.bottom - 70, m_hWnd, (HMENU)300, m_hInstance, NULL);

    SendMessageA(m_hListBox, LB_ADDSTRING, 0, (LPARAM)"< 채팅이 가능합니다! >");
    m_Net.InitNetwork();
    m_Net.Connect(g_hWnd, SOCK_STREAM, PORT_NUM, ADRESS_NUM);// "127.0.0.1"); //IP
    return true;
}
bool ASample::Frame()
{
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
            AChatMsg recvdata;
            ZeroMemory(&recvdata, sizeof(recvdata));
            (*iter) >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
            SendMessageA(m_hListBox, LB_ADDSTRING, 0, (LPARAM)recvdata.message);
            //iter = m_Net.m_PlayerUser.m_PacketPool.erase(iter);
            (*iter).Reset();
        }
    }
    return true;
}
bool ASample::Render()
{
    return true;
}
bool ASample::Release()
{
    m_Net.CloseNetWork();
    return true;
}
ASample::ASample() {}
ASample::~ASample() {}
SIMPLE_ARUN();

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//	ASample core;
//
//	if (core.SetWinClass(hInstance) == FALSE) return 1;
//	if (core.SetWindow(L"SelectClient Chat") == FALSE) return 1;
//	core.GameRun();
//	return 1;
//}

