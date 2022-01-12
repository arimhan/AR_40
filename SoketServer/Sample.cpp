#pragma comment (lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <WS2tcpip.h>
using namespace std;
#define PORT_NUM 9110 // ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!
#define ADRESS_NUM "127.0.0.1" // ��ǻ�� IP �ּ� , ���� 48, 192.168.219.101
// Soket_Server

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	//Server ����
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(9110); // ���� ��Ʈ ��ȣ, �� ��Ʈ��ȣ�� �����ϴ� �ֵ� �� ���� �����ϵ��� ����
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //��� IP ���� ���
	int iRet = bind(ListenSock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return;
	iRet = listen(ListenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return;

	SOCKADDR_IN ClientAddr;
	int iLen = sizeof(ClientAddr);
	cout << "���� ������ ... " << endl;

	while (1) //������ �ʵ��� �ݺ��� ó��
	{
		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &iLen);
		//accept�Ǹ� ListenSock�� ��ȯ�ȴ�. ���� �����ߴ���(&ClientAddr), ��ȯ���� Ȯ�� ����.
		//�� ������ &iLen���� ���� �ƴ� �ּҸ� ���ϱ� ������ sizeof�Լ��� ����ϸ� �ȵ�. �׷��� ������ �޾Ƽ� �ּҸ� �Ѱܾ� ��.

		if (ClientSock == SOCKET_ERROR) //Client�� ��ȿ�� ������ �ƴ� ���
		{
			int iError = WSAGetLastError();
			cout << "ErrorCode: " << iError << endl;
			if (iError != WSAEWOULDBLOCK) //������ �ƴ� ��� ó��
			{
				break;
			}
			continue;
		}
		cout << "IP: "<< inet_ntoa(ClientAddr.sin_addr)<<", Port: "<<ntohs(ClientAddr.sin_port) << endl; //ip, port ���

		u_long on = 1;
		ioctlsocket(ClientSock, FIONBIO, &on);

		while (1)
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(ClientSock, szRecvBuffer, 256, 0);
			if (iRecvByte == 0)
			{
				cout << "IP: " << inet_ntoa(ClientAddr.sin_addr) << ", Port: " << ntohs(ClientAddr.sin_port) << endl; //ip, port ���
				//ip, port ���
				break;
			}
			if (iRecvByte == SOCKET_ERROR)
			{
				int iError = WSAGetLastError();
				//cout << "ErrorCode: " << iError << endl;
				if (iError != WSAEWOULDBLOCK)
				{
					break;
				}
			}
			else 				// msg ����, ���� ó��
			{
				cout << "<= ���� : " << szRecvBuffer << " " << endl;
				// data ����
				int iSendByte = send(ClientSock, szRecvBuffer, iRecvByte, 0);
				//sizeof(szRecvBuffer) �� �κ� �߿��ѵ� sizeof�� �ƴ� iRecvByte��ŭ �Ѱܾ� �Ѵ�.
				cout << "  =>���� : " << iSendByte << " [byte]" << endl;
			}
		}
		closesocket(ClientSock);
	}
	WSACleanup();
}