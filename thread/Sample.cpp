#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <conio.h> //_kbhit();
#include "Packet.h"
#pragma comment (lib, "ws2_32.lib")


#define PORT_NUM 9110 // ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!
#define ADRESS_NUM "127.0.0.1" // ��ǻ�� IP �ּ� , ���� 48, 192.168.219.101 "127.0.0.1"


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
int SendPacket(SOCKET Csock, char* msg, WORD type)
{
	// 1. ��Ŷ ����
	APacket aPacket(type);
	aPacket << 12 << "Arim" << (short)50 << msg;
	APacket aPacketTest(aPacket);
	AChatMsg recvdata;
	ZeroMemory(&recvdata, sizeof(recvdata));
	aPacketTest >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
	char* pData = (char*)&aPacket.m_uPacket;
	int iSendSize = 0;
	do {
		// 2. ��Ŷ ���� : �ü���� sendbuffer(short byte), recvbuffer �� ũ�Ⱑ ������ ����.
		int iSendByte = send(Csock, &pData[iSendSize], aPacket.m_uPacket.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
		//packet�� ����ü -> ���ڿ��� ĳ�����Ͽ� �����Ѵ�.
	} while (iSendSize < aPacket.m_uPacket.ph.len);
	return iSendSize;
}
int RecvPacketHeader(SOCKET Csock, UPACKET& recvPacket)
{
	// ��Ŷ ��� ����
	char szRecvBuffer[256] = { 0, };
	ZeroMemory(&recvPacket, sizeof(recvPacket));
	bool bRun = true;
	int iRecvSize = 0;
	do {
		int iRecvByte = recv(Csock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
		iRecvSize += iRecvByte;
		//�� �������� ���� ������� -1�� �߻�
		if (iRecvByte == 0)
		{
			closesocket(Csock);
			cout << "������ ����Ǿ����ϴ�." << endl; //���� ���� �� ó��
			return -1;
		}
		if (iRecvByte == SOCKET_ERROR) // -1�϶�
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK) //Soket ������ nonblock���°� �ƴ� ��� == ��¥ ������ ���
			{
				cout << "������ ���� ���� Error " << iError << endl;
				return -1;
			}
			else { return 0; }
		}
	} while (iRecvSize < PACKET_HEADER_SIZE);
	memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
	return 1;
}
int RecvPacketData(SOCKET Csock, UPACKET& recvPacket)
{
	//������ ����
	int iRecvSize = 0;
	do {
		int iRecvByte = recv(Csock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
		iRecvSize += iRecvByte;
		if (iRecvByte == 0)
		{
			closesocket(Csock);
			cout << "������ ����Ǿ����ϴ�." << endl; //���� ���� �� ó��
			return -1;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				cout << "������ ���� ����" << endl;
				return -1;
			}
			else { return 0; }
		}
	} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
	return 1;
}

DWORD WINAPI SendThread(LPVOID lpThreadParameter) // sendthread ó�� �� ��ȯ. 1��ü 1������ ��ȯ����
{
	SOCKET Csock = (SOCKET)lpThreadParameter; //�Ķ���͸� �������� ����ȯ
	char szBuffer[256] = { 0, };

	while (1)
	{
		ZeroMemory(szBuffer, sizeof(char) * 256);
		fgets(szBuffer, 256, stdin); // ���� �ľ� ��ȯ�Լ�

		if (strlen(szBuffer) == 0) //msg�� �Է����� �ʰ� ���͸� ģ ��� ����ó�� �Ѵ�.
		{
			cout << "\n���� ����" << endl;
			break;
		}
		int iSendByte = SendPacket(Csock, szBuffer, PACKET_CHAT_MSG);
		if (iSendByte < 0)
		{
			cout << "������ ���� ����" << endl;
			break;
		}
	}
	return 0;
}
DWORD WINAPI RecvThread(LPVOID param) // sendthread ó�� �� ��ȯ. 1��ü 1������ ��ȯ����
{
	SOCKET Csock = (SOCKET)param; //�Ķ���͸� �������� ����ȯ
	char szBuffer[256] = { 0, };

	while (1)
	{
		UPACKET packet;
		int iRet = RecvPacketHeader(Csock, packet);
		if (iRet < 0) continue;
		if (iRet == 1)
		{
			int iRet = RecvPacketData(Csock, packet);
			if (iRet < 0) break;
			if (iRet == 0) continue;

			APacket data;
			data.m_uPacket = packet;
			AChatMsg recvdata;
			ZeroMemory(&recvdata, sizeof(recvdata));
			data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
			cout << "\n" << "[" << recvdata.name<<"]" << recvdata.message;
		}
	}
	return 0;
}


void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return; }
	SOCKET Csock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN CAddr;
	ZeroMemory(&CAddr, sizeof(CAddr));
	CAddr.sin_family = AF_INET;
	CAddr.sin_port = htons(PORT_NUM); // ���� ��Ʈ ��ȣ
	CAddr.sin_addr.s_addr = inet_addr(ADRESS_NUM);
	int iRet = connect(Csock, (sockaddr*)&CAddr, sizeof(CAddr));
	if (iRet == SOCKET_ERROR) { return; }
	cout << "���� ���� ����!" << endl;

	u_long on = 1;
	ioctlsocket(Csock, FIONBIO, &on);

	// ������ ����
	//  1) window api
	// ::�ٱ��� �ִ� �Լ� ���ڴ�. ���� �ذ���.
	DWORD ThreadId;
	HANDLE hThread = ::CreateThread( // ��ȯ���� �ڵ���
		0,
		0,
		SendThread, //��ȯ => �ʼ������� �Ѱ��� ��? ����
		(LPVOID)Csock, //data type (LPVOID)�� �����ֱ�
		0, //��������. ���� ���� ��ų��? => ����� ���� �������� ��~ ���� ������.
		&ThreadId);  //������ ���̵�. ������ �����ְڴ�.

	DWORD ThreadIdRecv;
	HANDLE hThreadRecv = ::CreateThread( // ��ȯ���� �ڵ���
		0,
		0,
		RecvThread,
		(LPVOID)Csock, 
		0, 
		&ThreadIdRecv); 

	while (1)
	{
		Sleep(1);
		// return -1���� ��� ���ѷ��� �߻�
	}
	cout << "���� ����" << endl;

	CloseHandle(hThread);
	closesocket(Csock);
	WSACleanup();
	//_getch();
}