#pragma comment (lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <WS2tcpip.h>
using namespace std;
#define PORT_NUM 9110 // ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!
#define ADRESS_NUM "127.0.0.1" // ��ǻ�� IP �ּ� , ���� 48, 192.168.219.101
// Soket_Client
//<���� ����>
// ������, TCP��������(SOCK_STREAM,IPPROTO_TCP)
// �񿬰���, UDP ��������(SOCK_DGRAM,IPPROTO_UDP)

void main()
{
	unsigned short iPort = PORT_NUM;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ClientSock = socket (AF_INET,SOCK_STREAM,0);
	//�������� ���� �׷��� �߰� TYPE�� ��õǸ� 0���� �����ص� OK
	//SOCK_STREAM : TCP
	//SOCK_DGRAM : UDP

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port= htons(PORT_NUM); // ���� ��Ʈ ��ȣ
	sa.sin_addr.s_addr = inet_addr(ADRESS_NUM);
	//inet_addr("ADRESS_NUM");
	//IP ��ũ�η� ������ ���� ����. ������ S_un.S_addr�� ����.
	//inet_addr���ڿ��� 4byte�� �ٲ㼭 ����

	//�����Ѵ�~
	int iRet = connect(ClientSock, (sockaddr*)&sa, sizeof(sa));

	//int iSendCount = 3; //3���� ����
	while(1)//(iSendCount--> 0)
	{ 
		//������~ �޴� ���� ����
		char szBuffer[] = "Client�Դϴ�."; // [] ����θ� �ش��� �������� ���۵�.
		int iSendByte = send(ClientSock, szBuffer, sizeof(szBuffer), 0);


		char szRecvBuffer[256] = { 0, };

		if(iSendByte == SOCKET_ERROR)
		{
			cout << "������ ���� ����" << endl;
			break;
		}
		//������ ���ڽý����� ���� (���ú� ����)
		int iRetByte = recv(ClientSock, szRecvBuffer, 256, 0);
		cout << szRecvBuffer << endl;
	}
	Sleep(1000);

	//�ݱ�~
	closesocket(ClientSock);
	WSACleanup();
}