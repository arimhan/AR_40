#include "LobbyServer.h"

/*void ALobbyServer::LoginReq(APacket& a, ANetUser* user)
{
    ALoginReq loginreq;
    memcpy(&loginreq, a.m_uPacket.msg, sizeof(ALoginReq));
    ALoginAck loginack;
    loginack.iRet = 1;
    SendMsg(user, (char*)&loginack, sizeof(ALoginAck), PACKET_LOGIN_ACK);
}*/
/*void ALobbyServer::ChatMsg(APacket& a, ANetUser* user)
{
    Broadcast(a);
}*/
/*void ALobbyServer::LogoutUser(APacket& a, ANetUser* user)
{
    //packetpool에 addpacket처리(packet)
    //userlist -> deluser (packet.user)

    m_SendBroadcastPacketPool.AddPacket(t);
    m_pSessionMgr->DelUser(t.pUser);
}*/
bool ALobbyServer::RunServer()
{
    while (1) //Client accept 후 정보 출력
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
        //패킷 처리
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