#include "Network.h"
#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101 "127.0.0.1"
bool	ANetwork::InitNetwork()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return false; }
	return true;
}
bool	ANetwork::InitServer(int protocol, int iport, const char* ip)
{
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(iport);
	if(ip==nullptr)	{ sa.sin_addr.s_addr = htonl(INADDR_ANY);	}
	else	{ sa.sin_addr.s_addr = inet_addr(ip);	}


	int iRet = bind(m_Sock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return false;
	iRet = listen(m_Sock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return false;
	return true;
}
bool	ANetwork::CloseNetWork()
{
	closesocket(m_Sock);
	WSACleanup();
	return true;
}
int ANetwork::SendMsg(SOCKET sock, char* msg, WORD type)
{
	// create packet
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));

	//send packet : sendbuffer (short byte), recvbuffer
	char* pMsg = (char*)&packet;
	int iSendSize = 0;
	do 
	{
		int iSendByte = send(sock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int ANetwork::SendMsg(SOCKET sock, UPACKET& packet)
{
	//send packet : sendbuffer (short byte), recvbuffer
	char* pMsg = (char*)&packet;
	int iSendSize = 0;
	do
	{
		int iSendByte = send(sock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int ANetwork::AddUser(SOCKET sock)
{
	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);
	SOCKET CSock = accept(sock, (sockaddr*)&CAddr, &iLen);
	if (CSock == SOCKET_ERROR) { return -1; }
	else 
	{
		ANetUser user;
		user.Set(CSock, CAddr);
		UserList.push_back(user);
		cout << "IP:" << inet_ntoa(CAddr.sin_addr) << "Port:" << ntohs(CAddr.sin_port) << " " << endl;
	}
	return 1;
}
int ANetwork::RecvUser(ANetUser& user)
{
	char szRecvBuffer[1024] = { 0, };
	int iRecvByte = recv(user.m_Sock, szRecvBuffer, 1024, 0);
	if (iRecvByte == 0) { return 0; }
	if (iRecvByte == SOCKET_ERROR) { return -1; }
	user.DispatchRead(szRecvBuffer, iRecvByte);
	return 1;
}
