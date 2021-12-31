#include <WinSock2.h>
#include <iostream>

#pragma comment (lib, "ws_32.lib")
using namespace std;
#define PORT_NUM 9190				// 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!
#define ADRESS_NUM "192.168.0.44"	// 컴퓨터 IP 주소 , 수호 44, 48
// Soket_Client2

void main()
{
	unsigned short iPort = PORT_NUM;
	WSADATA wsa;
	int iRet;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET clSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(iPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	//소켓을 해당 ip에 연결

	iRet = bind(clSock, (SOCKADDR*)&sa, sizeof(sa));
	//(SOCKADDR*)&sa => *name으로(&sa) 받아야 하는데 SOCKADDR_IN * 형식의 인수가 const sockaddr* 형식의 매개변수와 호환이 안됨.
	
	

}