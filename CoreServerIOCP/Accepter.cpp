#include "Accepter.h"
#include "Server.h"
#include <WS2tcpip.h> //inet_ntop

bool AAccepter::RunServer()
{
	AServer* pServer = (AServer*)m_pObject;
	SOCKET sock = pServer->m_LSock;
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

AAccepter::AAccepter() {}
AAccepter::AAccepter(LPVOID value) : AThread(value) {}