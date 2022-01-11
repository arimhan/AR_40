#include "Server.h"

int AServer::SendMsg(SOCKET Csock, char* msg, WORD type)
{
	// 1. 패킷 생성
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE; //규칙을 정해서 동일하게 처리해야함.
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg)); //txt 메모리 카피 처리
	char* pMsg = (char*)&packet;
	//packet은 구조체 -> 문자열로 캐스팅하여 전송한다.

	int iSendSize = 0;
	do {
		// 2. 패킷 전송 : 운영체제는 sendbuffer(short byte), recvbuffer 내 크기가 정해져 있음.
		int iSendByte = send(Csock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int AServer::SendMsg(SOCKET Csock, UPACKET& packet)
{
	//생성 완료 된 패킷 전송

	char* pMsg = (char*)&packet;
	//packet은 구조체 -> 문자열로 캐스팅하여 전송한다.
	int iSendSize = 0;
	do {
		// 2. 패킷 전송 : 운영체제는 sendbuffer(short byte), recvbuffer 내 크기가 정해져 있음.
		int iSendByte = send(Csock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int AServer::Broadcast(ANetUser& user)
{
	if (user.m_PacketPool.size() > 0)
	{
		list<APacket>::iterator iter;
		for (iter = user.m_PacketPool.begin(); iter != user.m_PacketPool.end();)
		{
			for (ANetUser& senduser : g_UserList)
			{
				int iRet = SendMsg(senduser.m_Sock, (*iter).m_uPacket);
				if (iRet <= 0) { senduser.m_bConnect = false; }
			}
			iter = user.m_PacketPool.erase(iter);
		}
	}
	return 1;
}
int AServer::RecvUser(ANetUser& user)
{
	char szRecvBuffer[1024] = { 0, };
	int iRecvByte = recv(user.m_Sock, szRecvBuffer, 1024, 0);
	if (iRecvByte == 0) { return 0; }
	if (iRecvByte == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		return 2;
	}
	user.DispatchRead(szRecvBuffer, iRecvByte);
	return 1;
}
bool AServer::Init()
{
	InitializeCriticalSection(&g_CS);
	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return false; }
	m_LSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN Addr;
	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(PORT_NUM); // 서버 포트 번호
	Addr.sin_addr.s_addr = inet_addr(ADRESS_NUM);

	int iRet = bind(m_LSock, (sockaddr*)&Addr, sizeof(Addr));
	if (iRet == SOCKET_ERROR) { return false; }
	iRet = listen(m_LSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) { return false; }

	cout << "서버 접속 성공!" << endl;

	u_long on = 1;
	ioctlsocket(m_LSock, FIONBIO, &on);

	return true;
}
bool AServer::RunServer()
{
	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);

	while (1) //Client accept 후 정보 출력
	{

		SOCKET CSock = accept(m_LSock, (sockaddr*)&CAddr, &iLen);
		if (CSock == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				cout << "Error : " << iError << endl; //ERROR : 10038 // 10035 정상진행
				break;
			}
		}
		else
		{
			ANetUser user;
			user.Set(CSock, CAddr);
			//EnterCriticalSection(&g_CS);
			WaitForSingleObject(g_hMutex, INFINITE);

			g_UserList.push_back(user);
			//LeaveCriticalSection(&g_CS);
			ReleaseMutex(g_hMutex);

			cout << "IP: " << inet_ntoa(CAddr.sin_addr) << "Port: " << ntohs(CAddr.sin_port) << " " << endl;
			cout << g_UserList.size() << "명 접속중..." << endl;
		}
		Sleep(1);
	}
	return true;
}
bool AServer::Release()
{
	closesocket(m_LSock);
	WSACleanup();
	//DeleteCriticalSection(&g_CS);
	CloseHandle(g_hMutex);

	return true;
}