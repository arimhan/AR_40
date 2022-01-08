#include "Network.h"
#define PORT_NUM 9110 
//#define ADRESS_NUM "127.0.0.1" 
list<ANetUser> UserList;

int SendMsg(SOCKET sock, char* msg, WORD type)
{
	// 1. 패킷 생성
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE; //규칙을 정해서 동일하게 처리해야함.
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg)); //txt 메모리 카피 처리
	// 2. 패킷 전송 : 운영체제는 sendbuffer(short byte), recvbuffer 내 크기가 정해져 있음.
	//packet은 구조체 -> 문자열로 캐스팅하여 전송한다.
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
	//생성된 UPACKET 전송 구조
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
	else //정상 작동 -> usercount, ip , port 정보 출력
	{
		ANetUser user;
		user.Set(CSock, CAddr);
		UserList.push_back(user);

		cout << "IP: " << inet_ntoa(CAddr.sin_addr) << ",  Port: " << ntohs(CAddr.sin_port) << " " << endl;
		cout << UserList.size() << "명 접속중 입니다." << endl;
	}
	return 1;
}
int RecvUser(ANetUser& user)
{
	char szRecvBuffer[1024] = { 0, }; //2048의 절반
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
	cout << "서버 가동중 . . . . . . ." << endl;

	FD_SET rSet;
	FD_SET wSet;
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1;

	while (1) //키 입력 안함. 받은 메시지 출력
	{
		//rSet, wSet 값 초기화 및 LSock을 rSet으로 세팅
		FD_ZERO(&rSet);
		FD_ZERO(&wSet);
		FD_SET(net.m_LSock, &rSet);

		list<ANetUser>::iterator UserIter;

		for (UserIter = UserList.begin(); UserIter != UserList.end();)
		{
			if ((*UserIter).m_bConnect == false)
			{
				cout << (*UserIter).m_csName << "님이 접속 종료 하였습니다." << endl;
				UserIter = UserList.erase(UserIter);
				continue;
			}
			FD_SET((*UserIter).m_Sock, &rSet);
			//만약 user에서 보낸 패킷이 있으면 아래 처리
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
