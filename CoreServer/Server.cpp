#include "Server.h"
void AServer::LoginReq(APacket& a, ANetUser* user){	}
bool AServer::Init(int iPort)
{
	m_fnExecutePacket[PACKET_LOGIN_REQ] = bind(&AServer::LoginReq, this, placeholders::_1, placeholders::_2);
	m_Accept.Set(9110);
	m_Accept.Create(this);
	m_Accept.Detach();

	return true;
}
bool AServer::RunServer()
{
	return true;
}
bool AServer::AddUser(SOCKET Csock, SOCKADDR_IN CAddr)
{
	//LobbyServer에서 실제구현함!!
	return true;
}
bool AServer::DelUser(SOCKET sock)
{
	return true;
}
bool AServer::DelUser(ANetUser* pUser)
{
	pUser->DisConnect();
	return true;
}
bool AServer::DelUser(m_UserIter& iter)
{
	DelUser((ANetUser*)*iter);
	return true;
}
bool AServer::Release()
{
	AObjectPool<ANetUser>::AllFree();
	AObjectPool<AOV>::AllFree();
	//DeleteCriticalSection(&g_CS);
	return true;
}
int AServer::SendMsg(SOCKET Csock, UPACKET& packet)
{
	//생성 완료 된 패킷 전송
	char* pMsg = (char*)&packet;
	//packet은 구조체 -> 문자열로 캐스팅하여 전송한다.
	int iSendSize = 0;
	do {
		// 2. 패킷 전송 : 운영체제는 sendbuffer(short byte), recvbuffer 내 크기가 정해져 있음.
		int iSendByte = send(Csock, &pMsg[iSendSize], 11, 0); //packet.ph.len, 0);//- iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int AServer::SendMsg(ANetUser* pUser, char* msg, int iSize, WORD type)
{
	//보내는 패킷 -> packetpool에 저장 후 한꺼번에 전송
	pUser->SendMsg(msg, iSize, type);
	return 0;
}
int AServer::SendMsg(ANetUser* pUser, UPACKET& packet)
{
	pUser->SendMsg(packet);
	return 0;
}
/*int AServer::Broadcast(ANetUser* user)
{
	if (user->m_PacketPool.size() > 0)
	{
		list<APacket>::iterator iter;
		for (iter = user->m_PacketPool.begin(); iter != user->m_PacketPool.end();)
		{
			for (ANetUser* senduser : m_UserList)
			{
				int iRet = SendMsg(senduser->m_Sock, (*iter).m_uPacket);
				if (iRet <= 0) { 
					senduser->m_bConnect = false; 
				}
			}
			iter = user->m_PacketPool.erase(iter);
		}
	}
	return 1;
}*/
int AServer::Broadcast(APacket& a)
{
	for (ANetUser* senduser : m_UserList)
	{
		int iRet = SendMsg(senduser->m_Sock, a.m_uPacket);
		if (iRet <= 0) {
			senduser->m_bConnect = false;
		}
	}
	return 1;
}
/*int AServer::BroadcasePool(ANetUser* user)
{
	if (user->m_PacketPool.size() > 0)
	{
		list<APacket>::iterator iter;
		for (iter = user->m_PacketPool.begin(); iter != user->m_PacketPool.end(); )
		{
			for(ANetUser* senduser : m_UserList)
			{
				int iRet = SendMsg(senduser->m_Sock, (*iter).m_uPacket);
				if (iRet < 0)
				{
					senduser->m_bConnect == false;
				}
			}
			iter = user->m_PacketPool.erase(iter);
		}
	}
	return 1;
}*/



