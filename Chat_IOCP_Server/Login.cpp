#include "LobbyServer.h"

bool ALobbyServer::RunServer()
{
    while (1) //Client accept �� ���� ���
    {
        EnterCriticalSection(&m_cs);
        for (ANetUser* pUser : m_UserList)
        {
            AChatUser* pChat = (AChatUser*)pUser;
            if (pChat->m_PacketPool.size() > 0)
            {
                Broadcast(pUser);
            }
        }
        //��Ŷ ó��
        list<ANetUser*>::iterator iter;
        for (iter = m_UserList.begin(); iter != m_UserList.end(); )
        {
            if((*iter)->m_bConnect == false)
            {
                (*iter)->DisConnect();
                delete(*iter);
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