#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <list>
#include <string>
#include "Packet.h"
#pragma comment (lib, "ws2_32.lib")
using namespace std;


class ANetUser
{
public:
	bool			m_bConnect = false;
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	string			m_csName;
	short			m_iPort;
	
	//buffer ฐüทร
	char			m_szRecvBuffer[2048];
	int				m_iPacketPos;
	int				m_iWritePos;
	int				m_iReadPos;
	list<APacket>	m_PacketPool;
	int				DispatchRead(char* szRecvBuffer, int iRecvByte);
	void			Set(SOCKET LSock, SOCKADDR_IN LAddr);
};

