#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
#define PORT_NUM 9090				// ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!
#define ADRESS_NUM "192.168.219.101"	// ��ǻ�� IP �ּ� , ��ȣ 44, 48
// Soket_Server1

int main()
{
	unsigned short iPort = PORT_NUM;

	//������ ���� �ʱ�ȭ
	WSADATA wsa;
	int iRet;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return 1; }

	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));

	sa.sin_family = AF_INET;
	sa.sin_port = htons(iPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	//������ ��� ip�� ����

	iRet = bind(server, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return-1;
	iRet = listen(server, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return-1;
	
	SOCKADDR_IN clientaddr;
	SOCKET client;
	while(1)
	{
		int addlen = sizeof(clientaddr);
		client = accept(server, (sockaddr*)&clientaddr, &addlen);
		cout << "Ŭ���̾�Ʈ ���� IP: " << inet_ntoa(clientaddr.sin_addr) << " ,PORT: " << ntohs(clientaddr.sin_port) << endl;

		while (1)
		{
			char buf[256] = { 0, };
			int iRecvByte = recv(client, buf, 256, 0);
			if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) 
			{
				cout <<"Ŭ���̾�Ʈ ���� ���� IP: "<< inet_ntoa(clientaddr.sin_addr) << " ,PORT: " << ntohs(clientaddr.sin_port) << endl;
				break; //Ŭ���̾�Ʈ ����
			}
			cout << " " << buf;
			int iSendByte = send(client, buf, iRecvByte, 0);
		}
		closesocket(client);
	}
	closesocket(server);
	//������ ���� �Ҹ� (����)
	iRet = WSACleanup();
	return iRet;
}