#pragma once
#include "NetUser.h"


#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!9110
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101 "127.0.0.1"
class AServer
{
public:
	list<ANetUser>		g_UserList;
	CRITICAL_SECTION	g_CS;
	HANDLE				g_hMutex;
	//HANDLE				g_hConnectEvent;
	SOCKET				m_LSock;

public:
	int SendMsg(SOCKET Csock, char* msg, WORD type);
	int SendMsg(SOCKET Csock, UPACKET& packet);
	int Broadcast(ANetUser& user);
	int RecvUser(ANetUser& user);

public:
	bool Init();
	bool RunServer();
	bool Release();
};


