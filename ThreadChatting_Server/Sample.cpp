#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "NetUser.h"

#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!9110
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101 "127.0.0.1"

list<ANetUser>		g_UserList;
CRITICAL_SECTION	g_CS;
HANDLE				g_hMutex;


int SendMsg(SOCKET Csock, char* msg, WORD type)
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
int SendMsg(SOCKET Csock, UPACKET &packet)
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
int Broadcast(ANetUser& user)
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
int RecvUser(ANetUser& user)
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
DWORD WINAPI RecvThread(LPVOID param) // sendthread 처리 후 반환. 1개체 1스레드 반환받음
{
	SOCKET sock = (SOCKET)param; //파라미터를 소켓으로 형변환
	while (1)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		//EnterCriticalSection(&g_CS);
		list<ANetUser>::iterator Useriter;
		for (Useriter = g_UserList.begin(); Useriter != g_UserList.end();)
		{
			int iRet = RecvUser(*Useriter);
			if (iRet <= 0) { Useriter = g_UserList.erase(Useriter); }
			else { Useriter++; }
		}
		//LeaveCriticalSection(&g_CS);
		ReleaseMutex(g_hMutex);
		Sleep(1);
	}
}
DWORD WINAPI SendThread(LPVOID param) // sendthread 처리 후 반환. 1개체 1스레드 반환받음
{
	SOCKET sock = (SOCKET)param; //파라미터를 소켓으로 형변환
	char szBuffer[256] = { 0, };

	while (1)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		//EnterCriticalSection(&g_CS);
		list<ANetUser>::iterator Useriter;
		for (Useriter = g_UserList.begin(); Useriter != g_UserList.end();)
		{
			int iRet = Broadcast(*Useriter);
			if (iRet <= 0) { Useriter = g_UserList.erase(Useriter); }
			else { Useriter++; }
		}
		//LeaveCriticalSection(&g_CS);
		ReleaseMutex(g_hMutex);
		Sleep(1);
	}
}



void main()
{
	//InitializeCriticalSection(&g_CS);
	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return; }
	SOCKET LSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN Addr;
	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(PORT_NUM); // 서버 포트 번호
	Addr.sin_addr.s_addr = inet_addr(ADRESS_NUM);

	int iRet = bind(LSock, (sockaddr*)&Addr, sizeof(Addr));
	if (iRet == SOCKET_ERROR) { return; }
	iRet = listen(LSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) { return; }

	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);

	cout << "서버 접속 성공!" << endl;

	u_long on = 1;
	ioctlsocket(LSock, FIONBIO, &on);

	// 스레드 생성
	//  1) window api
	// ::바깥에 있는 함수 쓰겠다. 범위 해결자.

	 //전달받는 스레드 처리
	DWORD ThreadId;
	HANDLE hThreadRecv = ::CreateThread( // 반환값이 핸들임
		0,
		0,
		RecvThread,
		(LPVOID)LSock, //data type (LPVOID)로 맞춰주기
		0, //서스펜디드. 일을 언제 시킬지? => 만들고 아직 진행하지 마~ 등을 세팅함.
		&ThreadId);  //스레드 아이디. 리턴을 시켜주겠다.

	CloseHandle(hThreadRecv);
	DWORD ThreadIdSend;
	HANDLE hThreadSend = ::CreateThread( // 반환값이 핸들임
		0,
		0,
		SendThread, //반환 => 필수적으로 넘겨줄 값? 소켓
		(LPVOID)LSock, //data type (LPVOID)로 맞춰주기
		0, //서스펜디드. 일을 언제 시킬지? => 만들고 아직 진행하지 마~ 등을 세팅함.
		&ThreadIdSend);  //스레드 아이디. 리턴을 시켜주겠다.
	CloseHandle(hThreadSend);

	while (1) //키 입력 안함. 받은 메시지 출력
	{
		SOCKET CSock = accept(LSock, (sockaddr*)&CAddr, &iLen);
		if (CSock == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				cout << "Error : " << iError << endl;
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
	closesocket(LSock);
	WSACleanup();

	//DeleteCriticalSection(&g_CS);
	CloseHandle(g_hMutex);
}