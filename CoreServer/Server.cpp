#include "Server.h"
bool AServer::Init(int iPort)
{
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
	closesocket(m_LSock);
	WSACleanup();
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
		int iSendByte = send(Csock, &pMsg[iSendSize], 11, 0); //packet.ph.len, 0);//- iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
/*int AServer::SendMsg(ANetUser* pUser, char* msg, int iSize, WORD type)
{
	//������ ��Ŷ -> packetpool�� ���� �� �Ѳ����� ����
	pUser->SendMsg(msg, iSize, type);
	return 0;
}
int AServer::SendMsg(ANetUser* pUser, UPACKET& packet)
{
	pUser->SendMsg(packet);
	return 0;
}*/
int AServer::Broadcast(ANetUser *user)
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
}
//int AServer::Broadcast(APacket& a)
//{
//	for (ANetUser* senduser : m_UserList)
//	{
//		int iRet = SendMsg(senduser->m_Sock, a.m_uPacket);
//		if (iRet <= 0) {
//			senduser->m_bConnect = false;
//		}
//	}
//	return 1;
//}
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



