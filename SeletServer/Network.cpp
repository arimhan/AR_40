#include "Network.h"
#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101 "127.0.0.1"
bool	ANetwork::InitNetwork()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return false; }
	return true;
}
bool	ANetwork::InitServer(int protocol, int iport, const char* ip)
{
	m_LSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN LAddr;
	ZeroMemory(&LAddr, sizeof(LAddr));
	LAddr.sin_family = AF_INET;
	LAddr.sin_port = htons(iport);
	if(ip==nullptr)	{ LAddr.sin_addr.s_addr = htonl(INADDR_ANY);	}
	else	{ LAddr.sin_addr.s_addr = inet_addr(ip);	}


	int iRet = bind(m_LSock, (sockaddr*)&LAddr, sizeof(LAddr));
	if (iRet == SOCKET_ERROR) return false;
	iRet = listen(m_LSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return false;
	return true;
}
bool	ANetwork::CloseNetWork()
{
	closesocket(m_LSock);
	WSACleanup();
	return true;
}
