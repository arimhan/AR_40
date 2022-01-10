#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "NetUser.h"

#define PORT_NUM 9110 // ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!9110
#define ADRESS_NUM "127.0.0.1" // ��ǻ�� IP �ּ� , ���� 48, 192.168.219.101 "127.0.0.1"

list<ANetUser>		g_UserList;
CRITICAL_SECTION	g_CS;
HANDLE				g_hMutex;


int SendMsg(SOCKET Csock, char* msg, WORD type)
{
	// 1. ��Ŷ ����
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE; //��Ģ�� ���ؼ� �����ϰ� ó���ؾ���.
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg)); //txt �޸� ī�� ó��
	char* pMsg = (char*)&packet;
	//packet�� ����ü -> ���ڿ��� ĳ�����Ͽ� �����Ѵ�.

	int iSendSize = 0;
	do {
		// 2. ��Ŷ ���� : �ü���� sendbuffer(short byte), recvbuffer �� ũ�Ⱑ ������ ����.
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
	//���� �Ϸ� �� ��Ŷ ����

	char* pMsg = (char*)&packet;
	//packet�� ����ü -> ���ڿ��� ĳ�����Ͽ� �����Ѵ�.
	int iSendSize = 0;
	do {
		// 2. ��Ŷ ���� : �ü���� sendbuffer(short byte), recvbuffer �� ũ�Ⱑ ������ ����.
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
DWORD WINAPI RecvThread(LPVOID param) // sendthread ó�� �� ��ȯ. 1��ü 1������ ��ȯ����
{
	SOCKET sock = (SOCKET)param; //�Ķ���͸� �������� ����ȯ
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
DWORD WINAPI SendThread(LPVOID param) // sendthread ó�� �� ��ȯ. 1��ü 1������ ��ȯ����
{
	SOCKET sock = (SOCKET)param; //�Ķ���͸� �������� ����ȯ
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
	Addr.sin_port = htons(PORT_NUM); // ���� ��Ʈ ��ȣ
	Addr.sin_addr.s_addr = inet_addr(ADRESS_NUM);

	int iRet = bind(LSock, (sockaddr*)&Addr, sizeof(Addr));
	if (iRet == SOCKET_ERROR) { return; }
	iRet = listen(LSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) { return; }

	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);

	cout << "���� ���� ����!" << endl;

	u_long on = 1;
	ioctlsocket(LSock, FIONBIO, &on);

	// ������ ����
	//  1) window api
	// ::�ٱ��� �ִ� �Լ� ���ڴ�. ���� �ذ���.

	 //���޹޴� ������ ó��
	DWORD ThreadId;
	HANDLE hThreadRecv = ::CreateThread( // ��ȯ���� �ڵ���
		0,
		0,
		RecvThread,
		(LPVOID)LSock, //data type (LPVOID)�� �����ֱ�
		0, //��������. ���� ���� ��ų��? => ����� ���� �������� ��~ ���� ������.
		&ThreadId);  //������ ���̵�. ������ �����ְڴ�.

	CloseHandle(hThreadRecv);
	DWORD ThreadIdSend;
	HANDLE hThreadSend = ::CreateThread( // ��ȯ���� �ڵ���
		0,
		0,
		SendThread, //��ȯ => �ʼ������� �Ѱ��� ��? ����
		(LPVOID)LSock, //data type (LPVOID)�� �����ֱ�
		0, //��������. ���� ���� ��ų��? => ����� ���� �������� ��~ ���� ������.
		&ThreadIdSend);  //������ ���̵�. ������ �����ְڴ�.
	CloseHandle(hThreadSend);

	while (1) //Ű �Է� ����. ���� �޽��� ���
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
			cout << g_UserList.size() << "�� ������..." << endl;
		}
		Sleep(1);
	}
	closesocket(LSock);
	WSACleanup();

	//DeleteCriticalSection(&g_CS);
	CloseHandle(g_hMutex);
}