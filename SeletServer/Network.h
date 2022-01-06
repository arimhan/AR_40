#pragma once
#include "NetUser.h"
class ANetwork
{
public:
	SOCKET	m_LSock;

	bool	InitNetwork();
	bool	InitServer(int protocol, int iport, const char* ip = nullptr);
	bool	CloseNetWork();

};

