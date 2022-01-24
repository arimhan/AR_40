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
        //�Ϸ� ť�� �����Ͱ� ������ �۾� �����ϱ�.
        BOOL bReturn = ::GetQueuedCompletionStatus(pServer->g_hIOCP, &dwTransfer, &KeyValue, &pOverlapped, 1);
        AChatUser* pUser = (AChatUser*)KeyValue;
        AOV* pOV = (AOV*)pOverlapped;

        if (bReturn == TRUE && pUser && pOV)      //�۾�
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
    //�Ǳ���
    //chat user�� user �����Ҵ� �� queue������� Ȱ��
    // user->set, ����ŷ ó��
    //criticalsection�� �̿��� userlist push �Ұ�.
    //createiocompletionportȰ�� -> (ULONG_PTR)user�ѱ� ��
    //ip, port��ȣ �ѱ� �� inet_ntop�Լ�������� ip�� ��� buffer���� �ʿ�

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
//    //NetResult -> ������ struct
//    //NR�� �������� makepacket();
//    //system : UName���� �����̽��ϴ�.
//}
//void ALobbyServer::CreateAccount(ANetUser* user)
//{
//    //Login -> packet msg
//    //string -> id /pw 
//    TCHAR szUName = ();
//}