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

        //완료 큐에 데이터가 있으면 작업시작
        BOOL bReturn = ::GetQueuedCompletionStatus(pServer->g_hIOCP, &dwTransfer, &KeyValue, &pOverlapped, 1);
        AChatUser* pUser = (AChatUser*)KeyValue;
        TOV* pOV = (TOV*)pOverlapped;

        if (bReturn == TRUE && pUser && pOV)      //작업
        {
            if (dwTransfer == 0 && pOV->type == 1000)
            {
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

bool ALobbyServer::AddUser(SOCKET sock, SOCKADDR_IN CAddr)
{
    //실구현
    //chat user의 user 동적할당 후 queue방식으로 활용
    // user->set, 논블로킹 처리
    //criticalsection을 이용해 userlist push 할것.
    //createiocompletionport활용 -> (ULONG_PTR)user넘길 것
    //ip, port번호 넘길 시 inet_ntop함수사용으로 ip를 담는 buffer생성 필요

    AChatUser* pUser = new AChatUser;
    pUser->Set(sock, CAddr);
    u_long on = 1;
    ioctlsocket(sock, FIONBIO, &on);

    EnterCriticalSection(&m_cs);
    m_UserList.push_back(pUser);
    LeaveCriticalSection(&m_cs);

    ::CreateIoCompletionPort((HANDLE)sock, g_hIOCP, (ULONG_PTR)pUser, 0);
    pUser->Recv();

    char ipbuf[INET_ADDRSTRLEN];
    cout << "IP: " << inet_ntop(AF_INET, &(CAddr.sin_addr), ipbuf, INET_ADDRSTRLEN) << "Port: " << ntohs(CAddr.sin_port) << " " << endl;

    return true;
}
bool ALobbyServer::Init(int iPort)
{
    InitializeCriticalSection(&m_cs);

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return false; }
    m_LSock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN Addr;
    ZeroMemory(&Addr, sizeof(Addr));
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(iPort); // 서버 포트 번호
    Addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int iRet = bind(m_LSock, (sockaddr*)&Addr, sizeof(Addr));
    if (iRet == SOCKET_ERROR) { return false; }
    iRet = listen(m_LSock, SOMAXCONN);
    if (iRet == SOCKET_ERROR) { return false; }

    cout << "서버 접속 성공!" << endl;

    u_long on = 1;
    ioctlsocket(m_LSock, FIONBIO, &on);

    return true;
}
bool ALobbyServer::RunServer()
{
    while (1) //Client accept 후 정보 출력
    {
        EnterCriticalSection(&m_cs);
        for (ANetUser* tUser : m_UserList)
        {
            AChatUser* pChat = (AChatUser*)tUser;
            if (pChat->m_PacketPool.size() > 0)
            {
                Broadcast(tUser);
            }
        }
        list<ANetUser*>::iterator iter;
        for (iter = m_UserList.begin(); iter != m_UserList.end();)
        {
            if ((*iter)->m_bConnect == false) //User가 나갈 경우 list에서 삭제 처리
            {
                (*iter)->DisConnect();
                delete (*iter);
                iter = m_UserList.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        LeaveCriticalSection(&m_cs);
        Sleep(1);
    }
    return true;
}
bool ALobbyServer::Release()
{
    closesocket(m_LSock);
    WSACleanup();
    //DeleteCriticalSection(&g_CS);

    return true;
}

