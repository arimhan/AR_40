#pragma once
#include "Server.h"
#include "ChatUser.h"
#include <functional> // function STL
#include <map>
using namespace std;
#define MAX_WORKER_THREAD 3

class ALobbyServer : public AServer
{
public:
	//IOCP
	HANDLE g_hWorkThread[MAX_WORKER_THREAD];
	HANDLE g_hIOCP;
public:
	/* 1¹ø*/
	//typedef void(AServer::*CallFunction)(APacket& a, ANetUser* user);
	using CallFunction = function<void(APacket& a, ANetUser* user)>;
	typedef map<int, CallFunction>::iterator FunctionIterator;
	map<int, CallFunction> m_fnExecutePacket;
	//*/
public:
	void LoginReq(APacket& a, ANetUser* user);
	void ChatMsg(APacket& a, ANetUser* user);
	void LogoutUser(APacket& a, ANetUser* user);
	
public:
	virtual bool Init(int iPort) override;
	virtual bool RunServer();
	virtual bool Release();
	virtual bool AddUser(SOCKET Csock, SOCKADDR_IN CAddr);
};

