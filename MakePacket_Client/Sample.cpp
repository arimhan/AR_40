#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <conio.h> //_kbhit();
#include "Packet.h"
#pragma comment (lib, "ws2_32.lib")
//using namespace std;

#define PORT_NUM 9110 // ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!
#define ADRESS_NUM "127.0.0.1" // ��ǻ�� IP �ּ� , ���� 48, 192.168.219.101 "127.0.0.1"

// Soket_Client
// chat client : string�Է� �� ���� �Է� �� string�� ������ ����
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
	aPacket << 12 <<"Arim"<<(short)50 << msg;
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
			if (WSAGetLastError() != WSAEWOULDBLOCK) {return -1;}
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
	do{
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
				cout << "������ ���� ���� Error "<< iError << endl;
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
	//------------------���� ���� ������� Ȯ�� �� string �Է� ó�� ����
	char szBuffer[256] = { 0, };	//string ���� ����
	int iECount = 0;				// ���ۿ� ���� �� �� �Է°�(Ŀ��)�� ��Ÿ��.
	while (1)
	{
		if (_kbhit() == 1)
			//_kbhit : 0�� �ƴ� ���� ��ȯ�ϸ� Ű �Է��� ���ۿ��� ������� ����, Ű �Է� �� ó��
		{
			int iValue = _getche(); // ���� ���� ��ȯ
			if (iValue == '\r' && strlen(szBuffer) == 0) //msg�� �Է����� �ʰ� ���͸� ģ ��� ����ó�� �Ѵ�.
			{
				cout << "���� ����" << endl;
				break;
			}
			if (iValue == '\r') // ���� �Է� �� string �߼�
			{
				//��� 1
				//int iSendByte = SendMsg(Csock, szBuffer, PACKET_CHAT_MSG);
				//���2
				int iSendByte = SendPacket(Csock, szBuffer, PACKET_CHAT_MSG);
				if (iSendByte <0)
				{
					cout << "������ ���� ����" << endl;
					break;
				}
				//���� ���� �Ǹ鼭 �Է¹��� string buffer �ʱ�ȭ ó��
				iECount = 0;
				ZeroMemory(szBuffer, sizeof(char) * 256);
			}
			else // ���� �� ������ string �Է� ������ �� �κ� ����~~
			{	szBuffer[iECount++] = iValue;	}
		}
		else //Ű �Է� ����. ���� �޽��� ���
		{
			//ù ��° �Ѿ�� �� -1 -> 0�̹Ƿ� ó���� �ȵ�
			UPACKET packet;
			int iRet = RecvPacketHeader(Csock, packet);
			if (iRet < 0) break;
			if (iRet == 1)
			{
				int iRet = RecvPacketData(Csock, packet);
				if (iRet < 0) break;
				if (iRet == 0) continue;

				APacket data;
				data.m_uPacket = packet;
				AChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));
				
				//�޽��� ���
				data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
				cout << "\n" << "[ " << recvdata.name << " ]" << recvdata.message;
			}
		}
	}
	cout << "�������� 191" << endl; //while�ݺ��� ���� �� ���
	closesocket(Csock);
	WSACleanup();
	//_getch();
}