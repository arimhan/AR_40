#include "Server.h"

//void AServer::LoginReq(APacket& a, ANetUser* user){	}
bool AServer::Init(int iPort)
{
	m_Accept.Set(iPort);
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
	//LobbyServer���� ����������!!
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
	//���� �Ϸ� �� ��Ŷ ����
	char* pMsg = (char*)&packet;
	//packet�� ����ü -> ���ڿ��� ĳ�����Ͽ� �����Ѵ�.
	int iSendSize = 0;
	do {
		// 2. ��Ŷ ���� : �ü���� sendbuffer(short byte), recvbuffer �� ũ�Ⱑ ������ ����.
		int iSendByte = send(Csock, &pMsg[iSendSize],packet.ph.len - iSendSize, 0);//- iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int AServer::SendMsg(SOCKET Csock, char* msg, WORD type)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));

	char* pMsg = (char*)&packet;
	//packet�� ����ü -> ���ڿ��� ĳ�����Ͽ� �����Ѵ�.
	int iSendSize = 0;
	do {
		// 2. ��Ŷ ���� : �ü���� sendbuffer(short byte), recvbuffer �� ũ�Ⱑ ������ ����.
		int iSendByte = send(Csock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);//- iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
/*int AServer::BroadcastPool(ANetUser* user)
{
	if (user->m_PacketPool.size() > 0)
	{
		list<APacket>::iterator iter;
		for (iter = user->m_PacketPool.begin(); iter != user->m_PacketPool.end();)
		{
			for (ANetUser* senduser : m_UserList)
			{
				int iRet = SendMsg(senduser->m_Sock, (*iter).m_uPacket);
				if (iRet <= 0)
				{
					senduser->m_bConnect = false;
				}
			}
			iter = user->m_PacketPool.erase(iter);
		}
	}
	return 1;
}*/
int AServer::Broadcast(ANetUser* user)
//userlist��� ���Ƽ� send
{
	if (user->m_PacketPool.size() > 0)
	{
		list<APacket>::iterator iter;
		for (iter = user->m_PacketPool.begin(); iter != user->m_PacketPool.end();)
		{
			for (ANetUser* senduser : m_UserList)
			{
				int iRet = SendMsg(senduser->m_Sock, (*iter).m_uPacket);
				if (iRet <= 0) 
				{
					senduser->m_bConnect = false;
				}
			}
			iter = user->m_PacketPool.erase(iter);
		}
	}
	return 1;
}

