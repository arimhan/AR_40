#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
using namespace std;


void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(9110); // 서버 포트 번호, 내 포트번호에 접속하는 애들 다 접속 가능하도록 설정
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //모든 IP 접속 허용

	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return;

	SOCKADDR_IN ClientAddr;
	int iLen = sizeof(ClientAddr);
	char buf[256] = {};
	while (1)
	{
		recvfrom(sock, buf, 256, 0, (SOCKADDR*)&ClientAddr, &iLen);





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
		cout << "IP: " << inet_ntoa(ClientAddr.sin_addr) << ", Port: " << ntohs(ClientAddr.sin_port) << endl; //ip, port 출력
	}

	WSACleanup();
}