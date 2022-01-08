#pragma once
#include "NetUser.h"
class ANetwork
{
public:
	SOCKET			m_Sock;
	list<ANetUser>	UserList;
	ANetUser		m_PlayerUser;

	bool	InitNetwork();
	bool	InitServer(int protocol, int iport, const char* ip = nullptr);
	bool	CloseNetWork();

	int		SendMsg(SOCKET sock, char* msg, WORD type);
	int		SendMsg(SOCKET sock, UPACKET& packet);
	int		AddUser(SOCKET sock);
	int		RecvUser(ANetUser& user);
};

