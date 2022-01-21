#pragma once
#include "Server.h"
#include "ChatUser.h"
#define MAX_WORKER_THREAD 3

class ALobbyServer : public AServer
{
public:
	HANDLE g_hWorkThread[MAX_WORKER_THREAD];
	HANDLE g_hIOCP;
public:
	virtual void LoginReq(APacket& a, ANetUser* user) override;
	virtual void ChatMsg(APacket& a, ANetUser* user);
	virtual void LogoutUser(APacket& a, ANetUser* user);
	
public:
	virtual bool Init(int iPort) override;
	virtual bool RunServer();
	virtual bool Release();
	virtual bool AddUser(SOCKET Csock, SOCKADDR_IN CAddr);
};

