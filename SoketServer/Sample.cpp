#pragma comment (lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <WS2tcpip.h>
using namespace std;
#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101
// Soket_Server

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	//Server 소켓
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(9110); // 서버 포트 번호, 내 포트번호에 접속하는 애들 다 접속 가능하도록 설정
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //모든 IP 접속 허용
	int iRet = bind(ListenSock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return;
	iRet = listen(ListenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return;

	SOCKADDR_IN ClientAddr;
	int iLen = sizeof(ClientAddr);
	cout << "서버 가동중 ... " << endl;

	while (1) //꺼지지 않도록 반복문 처리
	{
		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &iLen);
		//accept되면 ListenSock이 반환된다. 누가 접속했는지(&ClientAddr), 반환여부 확인 가능.
		//맨 마지막 &iLen에서 값이 아닌 주소를 원하기 때문에 sizeof함수를 사용하면 안됨. 그러니 변수로 받아서 주소를 넘겨야 함.

		if (ClientSock == SOCKET_ERROR) //Client가 유효한 소켓이 아닐 경우
		{
			int iError = WSAGetLastError();
			cout << "ErrorCode: " << iError << endl;
			if (iError != WSAEWOULDBLOCK) //에러가 아닐 경우 처리
			{
				break;
			}
			continue;
		}
		cout << "IP: "<< inet_ntoa(ClientAddr.sin_addr)<<", Port: "<<ntohs(ClientAddr.sin_port) << endl; //ip, port 출력

		u_long on = 1;
		ioctlsocket(ClientSock, FIONBIO, &on);

		while (1)
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(ClientSock, szRecvBuffer, 256, 0);
			if (iRecvByte == 0)
			{
				cout << "IP: " << inet_ntoa(ClientAddr.sin_addr) << ", Port: " << ntohs(ClientAddr.sin_port) << endl; //ip, port 출력
				//ip, port 출력
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
			else 				// msg 받음, 보냄 처리
			{
				cout << "<= 받음 : " << szRecvBuffer << " " << endl;
				// data 전송
				int iSendByte = send(ClientSock, szRecvBuffer, iRecvByte, 0);
				//sizeof(szRecvBuffer) 이 부분 중요한데 sizeof가 아닌 iRecvByte만큼 넘겨야 한다.
				cout << "  =>보냄 : " << iSendByte << " [byte]" << endl;
			}
		}
		closesocket(ClientSock);
	}
	WSACleanup();
}