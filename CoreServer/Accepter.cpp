#include "Accepter.h"
#include "Server.h"
#include <WS2tcpip.h> //inet_ntop

bool AAccepter::RunServer()
{
	AServer* pServer = (AServer*)m_pObject;
	SOCKET sock = m_LSock;
	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);

	while (1) 
	{
		SOCKET CSock = accept(sock, (sockaddr*)&CAddr, &iLen);
		if (CSock == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				cout << "Error : " << iError << endl; //ERROR : 10038 // 10035 정상진행
				break;
			}
		}
		else
		{
			pServer->AddUser(CSock, CAddr);
			cout << pServer->m_UserList.size() << "명 접속중..." << endl;
		}
		Sleep(1);
	}
	return 1;
}

bool AAccepter::Set(int iPort)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}
	m_LSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(iPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	int iRet = ::bind(m_LSock,(sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	iRet = listen(m_LSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	cout << "서버 정상 가동중 . . . . . !" << endl;
	u_long on = 1;
	ioctlsocket(m_LSock, FIONBIO, &on);
	return true;
}
AAccepter::AAccepter() {}
AAccepter::AAccepter(LPVOID value) : AThread(value) {}
AAccepter::~AAccepter() {}