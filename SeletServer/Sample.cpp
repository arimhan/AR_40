#include "Network.h"
#define PORT_NUM 9110 
//#define ADRESS_NUM "127.0.0.1" 
list<ANetUser> UserList;

int SendMsg(SOCKET sock, char* msg, WORD type)
{
	// 1. ��Ŷ ����
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE; //��Ģ�� ���ؼ� �����ϰ� ó���ؾ���.
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg)); //txt �޸� ī�� ó��
	// 2. ��Ŷ ���� : �ü���� sendbuffer(short byte), recvbuffer �� ũ�Ⱑ ������ ����.
	//packet�� ����ü -> ���ڿ��� ĳ�����Ͽ� �����Ѵ�.
	char* pMsg = (char*)&packet;
	int iSendSize = 0;
	do {
		int iSendByte = send(sock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int SendMsg(SOCKET Sock, UPACKET &packet)
{
	//������ UPACKET ���� ����
	char* pMsg = (char*)&packet;
	int iSendSize = 0;
	do {
		int iSendByte = send(Sock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int AddUser(SOCKET sock)
{
	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);
	SOCKET CSock = accept(sock, (sockaddr*)&CAddr, &iLen);
		
	if (CSock == SOCKET_ERROR)	{return -1; }
	else //���� �۵� -> usercount, ip , port ���� ���
	{
		ANetUser user;
		user.Set(CSock, CAddr);
		UserList.push_back(user);

		cout << "IP: " << inet_ntoa(CAddr.sin_addr) << ",  Port: " << ntohs(CAddr.sin_port) << " " << endl;
		cout << UserList.size() << "�� ������ �Դϴ�." << endl;
	}
	return 1;
}
int RecvUser(ANetUser& user)
{
	char szRecvBuffer[1024] = { 0, }; //2048�� ����
	int iRecvByte = recv(user.m_Sock, szRecvBuffer, 1024, 0);
	if (iRecvByte == 0) { return 0; }
	if (iRecvByte == SOCKET_ERROR) { return -1; }
	user.DispatchRead(szRecvBuffer, iRecvByte);
	return 1;
}
void main()
{
	ANetwork net;
	net.InitNetwork();
	net.InitServer(SOCK_STREAM, PORT_NUM);

	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);
	cout << "���� ������ . . . . . . ." << endl;

	FD_SET rSet;
	FD_SET wSet;
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1;

	while (1) //Ű �Է� ����. ���� �޽��� ���
	{
		//rSet, wSet �� �ʱ�ȭ �� LSock�� rSet���� ����
		FD_ZERO(&rSet);
		FD_ZERO(&wSet);
		FD_SET(net.m_LSock, &rSet);

		list<ANetUser>::iterator UserIter;

		for (UserIter = UserList.begin(); UserIter != UserList.end();)
		{
			if ((*UserIter).m_bConnect == false)
			{
				cout << (*UserIter).m_csName << "���� ���� ���� �Ͽ����ϴ�." << endl;
				UserIter = UserList.erase(UserIter);
				continue;
			}
			FD_SET((*UserIter).m_Sock, &rSet);
			//���� user���� ���� ��Ŷ�� ������ �Ʒ� ó��
			if ((*UserIter).m_PacketPool.size() > 0) { FD_SET((*UserIter).m_Sock, &wSet); }
			UserIter++;
		}
		int iRet = select(0, &rSet, &wSet, NULL, &timeout);
		if (iRet == 0) { continue; }
		if (FD_ISSET(net.m_LSock, &rSet))
		{
			if (AddUser(net.m_LSock) <= 0) { break; }
		}
		for (ANetUser& user : UserList)
		{
			if (FD_ISSET(user.m_Sock, &rSet))
			{
				int iRet = RecvUser(user);
				if (iRet <= 0) { user.m_bConnect = false; }
			}
		}
		for (ANetUser& user : UserList)
		{
			if (FD_ISSET(user.m_Sock, &wSet))
			{
				if (user.m_PacketPool.size() > 0)
				{
					list<APacket>::iterator iter;
					for (iter = user.m_PacketPool.begin(); iter != user.m_PacketPool.end();)
					{
						for (ANetUser& senduser : UserList)
						{
							int iRet = SendMsg(senduser.m_Sock, (*iter).m_uPacket);
							if (iRet <= 0) { senduser.m_bConnect = false; }
						}
						iter = user.m_PacketPool.erase(iter);
					}
					
				}
			}
		}
	}
	net.CloseNetWork();
}
