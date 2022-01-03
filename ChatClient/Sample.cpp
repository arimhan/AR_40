#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <WS2tcpip.h>
#include <conio.h> //_kbhit();
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define PORT_NUM 9110 // ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!
#define ADRESS_NUM "127.0.0.1" // ��ǻ�� IP �ּ� , ���� 48, 192.168.219.101

// Soket_Client
// chat client : string�Է� �� ���� �Է� �� string�� ������ ����

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT_NUM); // ���� ��Ʈ ��ȣ
	sa.sin_addr.s_addr = inet_addr(ADRESS_NUM);
	int iRet = connect(ClientSock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}
	cout << "���� ���� ����!" << endl;

	u_long on = 1; 
	//	u_long nonblockingoff = 0; //0, 1�� ��� ����.
	ioctlsocket(ClientSock, FIONBIO, &on);
	//------------------���� ���� ������� Ȯ�� �� string �Է� ó�� ����
	char szBuffer[256] = { 0, };	//string ���� ����
	int iECount = 0;				// ���ۿ� ���� �� �� �Է°�(Ŀ��)�� ��Ÿ��.
	while (1)
	{
		if (_kbhit() == 1)
			//_kbhit : 0�� �ƴ� ���� ��ȯ�ϸ� Ű �Է��� ���ۿ��� ������� ����, Ű �Է� �� ó��
		{
			int iValue = _getche(); // ���� ���� ��ȯ
			if (iValue == '\r' && strlen(szBuffer) == 0) //
			{
				break;
				//continue;
			}
			if (iValue == '\r') // ���� �Է� �� string �߼�
			{
				int iSendByte = send(ClientSock, szBuffer, iECount, 0);

				if (iSendByte == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) //Soket ������ nonblock���°� �ƴ� ��� == ��¥ ������ ���
					{
						cout << "������ ���� ����" << endl;
						break;
					}
					//���� ���� �Ǹ鼭 �Է¹��� string buffer �ʱ�ȭ ó��
				}
				iECount = 0;
				ZeroMemory(szBuffer, sizeof(char) * 256);
			}
			else // ���� �� ������ string �Է� ������ �� �κ� ����~~
			{
				szBuffer[iECount++] = iValue;
			}
		}
		else // Ű �Է� �� ���� ��� ���� �޽��� ó��
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(ClientSock, szRecvBuffer, 256, 0);

			if (iRecvByte == 0)
			{
				cout << "������ ����Ǿ����ϴ�." << endl; //���� ���� �� ó��
				break;
			}
			if (iRecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK) //Soket ������ nonblock���°� �ƴ� ��� == ��¥ ������ ���
				{
					cout << "������ ���� ����" << endl;
					break;
				}
			}
			else //string ��� ó��
			{
				cout << " " <<szRecvBuffer<< endl;
				ZeroMemory(szRecvBuffer, sizeof(char) * 256);
			}
		}
	}
	cout << "line 98" << endl; //while�ݺ��� ���� �� ���
	closesocket(ClientSock);
	WSACleanup();
	_getch();
}