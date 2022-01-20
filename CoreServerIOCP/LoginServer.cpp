#include "LobbyServer.h"

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
                /*패킷 처리 필요
                1. 받은 패킷을 m_UserList-packet대로 돌면서 체크
                2. m_PacketPool or m_UserList둘 중 해당하는 곳에 데이터를 넣도록 처리*/
                Broadcast(tUser);
            }
        }
        //패킷 처리
        /*
        list<XPacket>::iterator iter;
        for (iter = m_packetPool.begin(); iter != m_packetPool.end(); )
        {
            XPacket* xp = (XPacket*)&(*iter);
            FunctionIterator iter = m_fnExecutePacket.find(xp->packet.m_uPacket.ph.type);
            if (iter != m_fnExecutePacket.end())
            {
                //STL map에서 <key, value> 이고, 우리가 사용하고자 하는 값은 second이니 이걸 반환받아
                CallFunction call = iter->second;

                //packet과 user값을 넘겨 해당하는 값을 찾는다
                call(xp->packet, xp->pUser);
            }
        }
        m_packetPool.clear();

        for (m_UserIter iter = m_UserList.begin(); iter != m_UserList.end();)
        {
            if ((*iter)->m_bConnect == false)
            {
                (*iter)->DisConnect();
                delete (*iter);
                iter = m_UserList.erase(iter);
            }
            else
            {
                iter++;
            }
        }*/

        list<ANetUser*>::iterator iter;
        for (iter = m_UserList.begin(); iter != m_UserList.end();)
        {
            if ((*iter)->m_bConnect == false)
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
