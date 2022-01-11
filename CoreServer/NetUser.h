#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "ServerStd.h" //winsock등 헤더때문에 먼저 돌려야 함.
#include "Packet.h"

class ANetUser
{
public:
	bool			m_bConnect = false;
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	string			m_csName;
	short			m_iPort;
	
	//buffer 관련
	char			m_szRecvBuffer[2048];
	int				m_iPacketPos;
	int				m_iWritePos;
	int				m_iReadPos;
	list<APacket>	m_PacketPool;
	int				DispatchRead(char* szRecvBuffer, int iRecvByte);
	void			Set(SOCKET LSock, SOCKADDR_IN LAddr);
};

