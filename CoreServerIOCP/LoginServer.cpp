#include "LobbyServer.h"

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
                /*��Ŷ ó�� �ʿ�
                1. ���� ��Ŷ�� m_UserList-packet��� ���鼭 üũ
                2. m_PacketPool or m_UserList�� �� �ش��ϴ� ���� �����͸� �ֵ��� ó��*/
                Broadcast(tUser);
            }
        }
        //��Ŷ ó��
        /*
        list<XPacket>::iterator iter;
        for (iter = m_packetPool.begin(); iter != m_packetPool.end(); )
        {
            XPacket* xp = (XPacket*)&(*iter);
            FunctionIterator iter = m_fnExecutePacket.find(xp->packet.m_uPacket.ph.type);
            if (iter != m_fnExecutePacket.end())
            {
                //STL map���� <key, value> �̰�, �츮�� ����ϰ��� �ϴ� ���� second�̴� �̰� ��ȯ�޾�
                CallFunction call = iter->second;

                //packet�� user���� �Ѱ� �ش��ϴ� ���� ã�´�
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