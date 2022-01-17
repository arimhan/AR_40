#pragma once
#include "Server.h"
#include "ChatUser.h"
#define MAX_WORKER_THREAD 3

class ALobbyServer :   public AServer
{
public:
	//IOCP
	HANDLE g_hIOCP;
	HANDLE g_hWorkThread[MAX_WORKER_THREAD];
	
public:
	virtual bool AddUser(SOCKET Csock, SOCKADDR_IN CAddr);
	virtual bool Init(int iPort) override;
	virtual bool RunServer();
	virtual bool Release();
	
};

