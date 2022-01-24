#include "LobbyServer.h"


DWORD WINAPI WorkerThread(LPVOID param)
{
    ALobbyServer* pServer = (ALobbyServer*)param;
    DWORD dwTransfer;
    ULONG_PTR KeyValue; //완료시 반환하는 포트값 ex 1000 : Read..
    OVERLAPPED* pOverlapped;

    while (1)
    {
        if (WaitForSingleObject(pServer->m_hKillEvent, 1) == WAIT_OBJECT_0)
        {
            break;
        }
        //완료 큐에 데이터가 있으면 작업 시작하기.
        BOOL bReturn = ::GetQueuedCompletionStatus(pServer->g_hIOCP, &dwTransfer, &KeyValue, &pOverlapped, 1);
        AChatUser* pUser = (AChatUser*)KeyValue;
        AOV* pOV = (AOV*)pOverlapped;

        if (bReturn == TRUE && pUser && pOV)      //작업
        {
            //if(dwTransfer == 0)
            if (dwTransfer == 0 && pOV->type == AOV::MODE_EXIT)
            {
                //pOV->type == AOV::MODE_EXIT;
                pUser->m_bConnect = false;
            }
            else
            {
                pUser->Dispatch(dwTransfer, pOV);
            }
        }
        else
        {
            if (GetLastError() != WAIT_TIMEOUT)
            {
                ::SetEvent(pServer->m_hKillEvent);
                break;
            }
        }
    }
    return 1;
}
bool ALobbyServer::AddUser(SOCKET Csock, SOCKADDR_IN CAddr)
{
    //실구현
    //chat user의 user 동적할당 후 queue방식으로 활용
    // user->set, 논블로킹 처리
    //criticalsection을 이용해 userlist push 할것.
    //createiocompletionport활용 -> (ULONG_PTR)user넘길 것
    //ip, port번호 넘길 시 inet_ntop함수사용으로 ip를 담는 buffer생성 필요

    AChatUser* pUser = new AChatUser;
    pUser->Set(Csock, CAddr, this);
    u_long on = 1;
    ioctlsocket(Csock, FIONBIO, &on);

    EnterCriticalSection(&m_cs);
    m_UserList.push_back(pUser);
    LeaveCriticalSection(&m_cs);

    ::CreateIoCompletionPort((HANDLE)Csock, g_hIOCP, (ULONG_PTR)pUser, 0);
    pUser->Recv();

    char ipbuf[INET_ADDRSTRLEN];
    cout << "IP: " << inet_ntop(AF_INET, &(CAddr.sin_addr), ipbuf, INET_ADDRSTRLEN) << "Port: " << ntohs(CAddr.sin_port) << " " << endl;

    return true;
}
bool ALobbyServer::Init(int iPort)
{
    AServer::Init(iPort);
    g_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

    for (int iThread = 0; iThread < MAX_WORKER_THREAD; iThread++)
    {
        DWORD id;
        g_hWorkThread[iThread] = ::CreateThread(0, 0, WorkerThread, this, 0, &id);
    }
    //m_fnExecutePacket.insert(make_pair(PACKET_CHAT_MSG, bind(&ALobbyServer::ChatMsg, this, placeholders::_1, placeholders::_2)));

    return true;
}
bool ALobbyServer::Release()
{
    CloseHandle(g_hIOCP);
    AServer::Release();
    return true;
}
//void ALobbyServer::SendLogout(ANetUser* user)
//{
//    //UPACKET
//    //NetResult -> 연결결과 struct
//    //NR를 기준으로 makepacket();
//    //system : UName님이 나가셨습니다.
//}
//void ALobbyServer::CreateAccount(ANetUser* user)
//{
//    //Login -> packet msg
//    //string -> id /pw 
//    TCHAR szUName = ();
//}