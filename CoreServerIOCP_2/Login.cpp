#include "LobbyServer.h"
void ALobbyServer::LoginReq(APacket& a, ANetUser* user)
{
    ALoginReq loginreq;
    memcpy(&loginreq, a.m_uPacket.msg, sizeof(ALoginReq));
    ALoginAck loginack;
    loginack.iRet = 1;
    SendMsg(user, (char*)&loginack, sizeof(ALoginAck), PACKET_LOGIN_ACK);
}
void ALobbyServer::ChatMsg(APacket& a, ANetUser* user)
{
    Broadcast(a);
}
void ALobbyServer::LogoutUser(APacket& a, ANetUser* user)
{
    //packetpool에 addpacket처리(packet)
    //userlist -> deluser (packet.user)
    /*
    m_SendBroadcastPacketPool.AddPacket(t);
    m_pSessionMgr->DelUser(t.pUser);*/
}
bool ALobbyServer::RunServer()
{
    while (1) //Client accept 후 정보 출력
    {
        EnterCriticalSection(&m_cs);
        /*for (ANetUser* tUser : m_UserList)
        {
            AChatUser* pChat = (AChatUser*)tUser;
            if (pChat->m_PacketPool.size() > 0)
            {
                //패킷 처리 필요
                //1. 받은 패킷을 m_UserList-packet대로 돌면서 체크
                //2. m_PacketPool or m_UserList둘 중 해당하는 곳에 데이터를 넣도록 처리
                //Broadcast(tUser);
                cout << "LobbyServer::RunServer_01"
            }
        }*/
        //패킷 처리
        list<XPacket>::iterator iter;
        for (iter = m_packetPool.begin(); iter != m_packetPool.end(); iter++)
        {
            XPacket* xp = (XPacket*)&(*iter);
            FunctionIterator iter = m_fnExecutePacket.find(xp->packet.m_uPacket.ph.type);
            if (iter != m_fnExecutePacket.end())
            {
                CallFunction call = iter->second;
                call(xp->packet, xp->pUser);
            }
            /*
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
            iter = m_packetPool.erase(iter);*/
        }
        m_packetPool.clear();
        /*
        //주기적인 동기화
        for (ANetUser* aUser : m_UserList)
        {
            AChatUser* pChat = (AChatUser*)aUser;
            if (pChat->m_PacketPool.size() > 0)
            {
                Broadcast(aUser);
            }
        }
        */
        for(m_UserIter iter = m_UserList.begin(); iter != m_UserList.end();)
        {
            if ((*iter)->m_bConnect == false) //User가 나갈 경우 list에서 삭제 처리
            {
                DelUser((*iter));
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