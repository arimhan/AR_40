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
                //��Ŷ ó�� �ʿ�
                //1. ���� ��Ŷ�� m_UserList-packet��� ���鼭 üũ
                //2. m_PacketPool or m_UserList�� �� �ش��ϴ� ���� �����͸� �ֵ��� ó��
                //Broadcast(tUser);
            }
        }

        //��Ŷ ó��
        list<ANetUser*>::iterator iter;
        for (iter = m_UserList.begin(); iter != m_UserList.end();)
        {
            XPacket* xp = (XPacket*)&(*iter);
            switch (xp->packet.m_uPacket.ph.type)
            {
                case PACKET_LOGIN_REQ:
                {
                    ALoginReq login;
                    memcpy(&login, xp->packet.m_uPacket.msg, sizeof(ALoginReq));

                    ALoginAck logack;
                    logack.iRet = 1;
                    SendMsg(xp->pUser, (char*)&logack, sizeof(ALoginAck), PACKET_LOGIN_ACK);
                }break;
                case PACKET_CHAT_MSG:
                {
                }break;
                case PACKET_CHAT_NAME_REQ: {}break;
                case PACKET_CHAT_NAME_ACK: {}break;
                case PACKET_LOGOUT_REQ: {}break;
                case PACKET_LOGOUT_ACK: {}break;
                case PACKET_LOGOUT_USER: {}break;
            }
            iter = m_packetPool.erase(iter);
        }
        //�ֱ����� ����ȭ
        for (ANetUser* aUser : m_UserList)
        {
            AChatUser* pChat = (AChatUser*)aUser;
            if (pChat->m_PacketPool.size() > 0)
            {
                Broadcast(aUser);
            }
        }
        for (m_UserIter iter = m_UserList.begin(); iter != m_UserList.end();)
        {
        }
            

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
        LeaveCriticalSection(&m_cs);
        Sleep(1);
    }
    return true;
}