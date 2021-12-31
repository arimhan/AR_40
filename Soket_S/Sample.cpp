#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
#define PORT_NUM 9090				// 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!
#define ADRESS_NUM "192.168.219.101"	// 컴퓨터 IP 주소 , 수호 44, 48
// Soket_Server1

int main()
{
	unsigned short iPort = PORT_NUM;

	//윈도우 소켓 초기화
	WSADATA wsa;
	int iRet;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return 1; }

	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));

	sa.sin_family = AF_INET;
	sa.sin_port = htons(iPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	//소켓을 대상 ip에 연결

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
		cout << "클라이언트 접속 IP: " << inet_ntoa(clientaddr.sin_addr) << " ,PORT: " << ntohs(clientaddr.sin_port) << endl;

		while (1)
		{
			char buf[256] = { 0, };
			int iRecvByte = recv(client, buf, 256, 0);
			if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) 
			{
				cout <<"클라이언트 접속 종료 IP: "<< inet_ntoa(clientaddr.sin_addr) << " ,PORT: " << ntohs(clientaddr.sin_port) << endl;
				break; //클라이언트 종료
			}
			cout << " " << buf;
			int iSendByte = send(client, buf, iRecvByte, 0);
		}
		closesocket(client);
	}
	closesocket(server);
	//윈도우 소켓 소멸 (서버)
	iRet = WSACleanup();
	return iRet;
}