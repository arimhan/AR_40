#include "LobbyServer.h"


DWORD WINAPI WorkerThread(LPVOID param)
{
    ALobbyServer* pServer = (ALobbyServer*)param;
    DWORD dwTransfer;
    ULONG_PTR KeyValue; //�Ϸ�� ��ȯ�ϴ� ��Ʈ�� ex 1000 : Read..
    OVERLAPPED* pOverlapped;


    while (1)
    {
        if (WaitForSingleObject(pServer->m_hKillEvent, 1) == WAIT_OBJECT_0)
        {
            break;
        }

        //�Ϸ� ť�� �����Ͱ� ������ �۾�����
        BOOL bReturn = ::GetQueuedCompletionStatus(pServer->g_hIOCP, &dwTransfer, &KeyValue, &pOverlapped, 1);
        AChatUser* pUser = (AChatUser*)KeyValue;
        TOV* pOV = (TOV*)pOverlapped;

        if (bReturn == TRUE && pUser && pOV)      //�۾�
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
    //�Ǳ���
    //chat user�� user �����Ҵ� �� queue������� Ȱ��
    // user->set, ����ŷ ó��
    //criticalsection�� �̿��� userlist push �Ұ�.
    //createiocompletionportȰ�� -> (ULONG_PTR)user�ѱ� ��
    //ip, port��ȣ �ѱ� �� inet_ntop�Լ�������� ip�� ��� buffer���� �ʿ�

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
    Addr.sin_port = htons(iPort); // ���� ��Ʈ ��ȣ
    Addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int iRet = bind(m_LSock, (sockaddr*)&Addr, sizeof(Addr));
    if (iRet == SOCKET_ERROR) { return false; }
    iRet = listen(m_LSock, SOMAXCONN);
    if (iRet == SOCKET_ERROR) { return false; }

    cout << "���� ���� ����!" << endl;

    u_long on = 1;
    ioctlsocket(m_LSock, FIONBIO, &on);

    return true;
}
bool ALobbyServer::RunServer()
{
    while (1) //Client accept �� ���� ���
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
            if ((*iter)->m_bConnect == false) //User�� ���� ��� list���� ���� ó��
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

