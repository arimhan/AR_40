#pragma comment (lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <WS2tcpip.h>
using namespace std;
#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101
// Soket_Client
//<소켓 생성>
// 연결형, TCP프로토콜(SOCK_STREAM,IPPROTO_TCP)
// 비연결형, UDP 프로토콜(SOCK_DGRAM,IPPROTO_UDP)

void main()
{
	unsigned short iPort = PORT_NUM;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ClientSock = socket (AF_INET,SOCK_STREAM,0);
	//프로토콜 지정 그런데 중간 TYPE값 명시되면 0으로 설정해도 OK
	//SOCK_STREAM : TCP
	//SOCK_DGRAM : UDP

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port= htons(PORT_NUM); // 서버 포트 번호
	sa.sin_addr.s_addr = inet_addr(ADRESS_NUM);
	//inet_addr("ADRESS_NUM");
	//IP 매크로로 지정한 곳에 넣음. 원래는 S_un.S_addr에 넣음.
	//inet_addr문자열을 4byte로 바꿔서 저장

	//연결한다~
	int iRet = connect(ClientSock, (sockaddr*)&sa, sizeof(sa));

	//int iSendCount = 3; //3번만 보냄
	while(1)//(iSendCount--> 0)
	{ 
		//보내는~ 받는 버퍼 생성
		char szBuffer[] = "Client입니다."; // [] 비워두면 해당한 사이즈대로 전송됨.
		int iSendByte = send(ClientSock, szBuffer, sizeof(szBuffer), 0);


		char szRecvBuffer[256] = { 0, };

		if(iSendByte == SOCKET_ERROR)
		{
			cout << "비정상 서버 종료" << endl;
			break;
		}
		//서버는 에코시스템이 있음 (리시브 가능)
		int iRetByte = recv(ClientSock, szRecvBuffer, 256, 0);
		cout << szRecvBuffer << endl;
	}
	Sleep(1000);

	//닫기~
	closesocket(ClientSock);
	WSACleanup();
}