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
            aPacket << 77 << "<ArimHan>" << (short)10 << buffer;
            m_Net.SendMsg(m_Net.m_Sock, aPacket.m_uPacket);

            SendMessageA(m_hEdit, WM_SETTEXT, 0, (LPARAM)"<ArimHan>: ");//
        }break;
        }
    }break;
    }
    return m_Net.MsgProc(hWnd, msg, wParam, lParam);
}
bool ASample::Init()
{
    m_PlayerObj.Init();
    m_PlayerObj.SetPosition(AVector2(400, 500));
    m_PlayerObj.SetRectSource({ 91,1,42,56 });
    m_PlayerObj.SetRectDraw({ 0,0,42,56 });

    if (!m_PlayerObj.Create(m_pd3dDevice, m_pImmediateContext, L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp"))
    {
        return false;
    }
    for (int iNpc = 0; iNpc < 5; iNpc++)
    {
        AObjectNpc2D* npc = new AObjectNpc2D;
        npc->Init();
        if (iNpc % 2 == 0)
        {
            npc->SetRectSource({ 46,63,69,79 });
            npc->SetRectDraw({ 0,0,69,79 });
        }
        else
        {
            npc->SetRectSource({ 1,63,42,76 });
            npc->SetRectDraw({ 0,0,42,76 });
        }
        npc->SetPosition(AVector2(50 + iNpc * 50, 50));
        if (!npc->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp"))
        {
            return false;
        }
        m_NpcList.push_back(npc);
    }
    m_Net.InitNetwork();
    m_Net.Connect(g_hWnd, SOCK_STREAM, PORT_NUM, ADRESS_NUM);// "127.0.0.1"); //IP
    return true;
}
bool ASample::Frame()
{
    m_PlayerObj.Frame();

    for (int iObj = 0; iObj < m_NpcList.size(); iObj++)
    {
        /*RECT rt = m_NpcList[iObj].m_rtDraw;
        rt.right = rt.right + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
        rt.bottom = rt.bottom + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
        m_NpcList[iObj].UpDateRectDraw(rt);*/
        m_NpcList[iObj]->Frame();
    }
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
    for (int iObj = 0; iObj < m_NpcList.size(); iObj++)
    {
        if (m_NpcList[iObj]->m_bDead == false)
        {
            m_NpcList[iObj]->Render();
        }
    }
    m_PlayerObj.Render();

    wstring msg = L"FPS: ";
    msg += to_wstring(m_GameTimer.m_iFPS);
    msg += L"   GT: ";
    msg += to_wstring(m_GameTimer.m_fTimer);
    m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(0,0,1,1));

    RECT rt = g_rtClient;
    rt.top = 300;
    rt.left = 0;
    m_dxWrite.Draw(L"KGCA ArimHan", rt, D2D1::ColorF(0, 0, 1, 1), m_dxWrite.m_pd2dMTShadowTF);
    return true;
}
bool ASample::Release()
{
    //각 클래스별로 Release재정의한것 불러오기
    for (int iObj = 0; iObj < m_NpcList.size(); iObj++)
    {
        m_NpcList[iObj]->Release();
        delete m_NpcList[iObj];
    }
    m_PlayerObj.Release();
    m_NpcList.clear();
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

